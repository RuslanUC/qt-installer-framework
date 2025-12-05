#include "pluginengine.h"

#include <QLoggingCategory>
#include <systeminfo.h>

#include "globals.h"
#include "plugin.h"
#include "packagemanagergui.h"

#if defined(Q_OS_LINUX)
#   define SO_EXTENSION "so"
#elif defined(Q_OS_WINDOWS)
#   define SO_EXTENSION "dll"
#endif

namespace QInstaller {
    PluginEngine::PluginEngine(PackageManagerCore* parent) : QObject(reinterpret_cast<QObject*>(parent)) {
        core = parent;
        component = nullptr;
    }

    PluginEngine::~PluginEngine() {
        initialized = false;
        if(library.isLoaded())
            library.unload();

        delete context_control;
        delete context_component;
        delete tempFile;
    }

    void PluginEngine::setComponent(Component* component) {
        this->component = component;
    }

    bool PluginEngine::load(const QString& path) {
        if(initialized)
            return true;

        if(path.startsWith(QLatin1String(":/"))) {
            QFile resFile(path);
            if(!resFile.open(QIODevice::ReadOnly)) {
                qCCritical(QInstaller::lcInstallerPluginLog) << "Failed to open library: " << resFile.errorString();
                return false;
            }

            const auto tempName = QString(QDir::tempPath() + QLatin1String("/XXXXXXXX_")+QFileInfo(path).fileName() + QLatin1String("." SO_EXTENSION));
            tempFile = new QTemporaryFile(tempName);

            if(!tempFile->open()) {
                qCCritical(QInstaller::lcInstallerPluginLog) << "Failed to open tmp library: " << tempFile->errorString();
                return false;
            }

            tempFile->write(resFile.readAll());
            tempFile->flush();
            tempFile->setPermissions(QFile::ExeOwner | QFile::ReadOwner | QFile::WriteOwner | QFile::ExeGroup | QFile::ReadGroup | QFile::ExeOther | QFile::ReadOther);
            tempFile->setAutoRemove(true);
            tempFile->close();

            library.setFileName(tempFile->fileName());
            if(!library.load()) {
                qCCritical(QInstaller::lcInstallerPluginLog) << "Failed to load library: " << library.errorString();
                return false;
            }
        } else {
            if(!QLibrary::isLibrary(path)) {
                qCCritical(QInstaller::lcInstallerPluginLog) << "Failed to load library: Not a library";
                return false;
            }

            library.setFileName(path);
            if(!library.load()) {
                qCCritical(QInstaller::lcInstallerPluginLog) << "Failed to load library: " << library.errorString();
                return false;
            }
        }

        const auto api_version_func = reinterpret_cast<IfwPluginApiVersion>(library.resolve("__ifw_plugin_api_version"));
        if(!api_version_func) {
            qCWarning(QInstaller::lcInstallerPluginLog) << "Failed to load library: cannot resolve __ifw_plugin_api_version";
            library.unload();
            return false;
        }

        if (const auto plugin_api_version = api_version_func(); plugin_api_version != IFW_PLUGIN_API_VERSION) {
            qCWarning(QInstaller::lcInstallerPluginLog) << "Ifw plugin version mismatch: expected " << IFW_PLUGIN_API_VERSION << ", got " << plugin_api_version;
            library.unload();
            return false;
        }

        control_init_func = reinterpret_cast<IfwPluginControlInit>(library.resolve("ifw_control_init"));
        component_init_func = reinterpret_cast<IfwPluginComponentInit>(library.resolve("ifw_component_init"));
        if(!(!control_init_func ^ !component_init_func)) {
            library.unload();
            return false;
        }

        is_control = !!control_init_func;

        is_default_func = reinterpret_cast<IfwPluginComponentIsDefault>(library.resolve("ifw_component_is_default"));
        component_create_operations_func = reinterpret_cast<IfwPluginComponentCreateOperations>(library.resolve("ifw_component_create_operations"));
        component_create_operations_for_path_func = reinterpret_cast<IfwPluginComponentCreateOperationsForPath>(library.resolve("ifw_component_create_operations_for_path"));
        component_create_operations_for_archive_func = reinterpret_cast<IfwPluginComponentCreateOperationsForArchive>(library.resolve("ifw_component_create_operations_for_archive"));
        component_begin_installation_func = reinterpret_cast<IfwPluginComponentBeginInstallation>(library.resolve("ifw_component_begin_installation"));

        initialized = true;
        return true;
    }

    ControlPluginContext* PluginEngine::controlPluginContext() {
        if(context_control)
            return context_control;

        auto* guiObject = reinterpret_cast<PackageManagerGui*>(core->guiObject());
        context_control = new ControlPluginContext(
            guiObject ? new GuiProxy(guiObject) : nullptr,
            new InstallerProxy(core),
            new SystemInfoProxy());

        return context_control;
    }

    ComponentPluginContext* PluginEngine::componentPluginContext() {
        if(context_component)
            return context_component;

        auto* guiObject = reinterpret_cast<PackageManagerGui*>(core->guiObject());
        context_component = new ComponentPluginContext(
            guiObject ? new GuiProxy(guiObject) : nullptr,
            new InstallerProxy(core),
            component ? new ComponentProxy(component) : nullptr,
            new SystemInfoProxy());

        return context_component;
    }

    bool PluginEngine::init() {
        if(initialized && is_control && control_init_func)
            return control_init_func(controlPluginContext());
        if(initialized && !is_control && component_init_func)
            return component_init_func(componentPluginContext());
        return false;
    }

    bool PluginEngine::isDefault() {
        if(initialized && is_default_func)
            return is_default_func(componentPluginContext());
        return false;
    }

    void PluginEngine::callPageCallback(const QString& page_name) {
        const auto func_name = QLatin1String("ifw_installer_callback_")+page_name;
        if(const auto callback_func = library.resolve(func_name.toLatin1().constData()))
            callback_func();
    }

    bool PluginEngine::callCreateOperations() {
        if(initialized && component_create_operations_func)
            return component_create_operations_func(componentPluginContext());
        return false;
    }

    bool PluginEngine::callCreateOperationsForPath(const QString& path) {
        if(initialized && component_create_operations_for_path_func)
            return component_create_operations_for_path_func(componentPluginContext(), path);
        return false;
    }

    bool PluginEngine::callCreateOperationsForArchive(const QString& archive) {
        if(initialized && component_create_operations_for_archive_func)
            return component_create_operations_for_archive_func(componentPluginContext(), archive);
        return false;
    }

    void PluginEngine::callBeginInstallation() {
        if(initialized && component_begin_installation_func)
            return component_begin_installation_func(componentPluginContext());
    }
}

ControlPluginContext::ControlPluginContext(GuiProxy* gui, InstallerProxy* installer, SystemInfoProxy* systemInfo) : gui(gui), installer(installer), systemInfo(systemInfo) {
}

ControlPluginContext::~ControlPluginContext() {
    delete gui;
    delete installer;
    delete systemInfo;
}

ComponentPluginContext::ComponentPluginContext(GuiProxy* gui, InstallerProxy* installer, ComponentProxy* component, SystemInfoProxy* systemInfo) : gui(gui), installer(installer), component(component), systemInfo(systemInfo) {
}

ComponentPluginContext::~ComponentPluginContext() {
    delete gui;
    delete installer;
    delete component;
    delete systemInfo;
}
