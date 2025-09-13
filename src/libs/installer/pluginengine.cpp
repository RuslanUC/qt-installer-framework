#include "pluginengine.h"
#include "plugin.h"
#include "packagemanagergui.h"

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
    }

    void PluginEngine::setComponent(Component* component) {
        this->component = component;
    }

    bool PluginEngine::load(const QString& path) {
        if(initialized)
            return true;

        if(!QLibrary::isLibrary(path))
            return false;

        library.setFileName(path);
        if(!library.load())
            return false;

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
            new InstallerProxy(core));

        return context_control;
    }

    ComponentPluginContext* PluginEngine::componentPluginContext() {
        if(context_component)
            return context_component;

        auto* guiObject = reinterpret_cast<PackageManagerGui*>(core->guiObject());
        context_component = new ComponentPluginContext(
            guiObject ? new GuiProxy(guiObject) : nullptr,
            new InstallerProxy(core),
            component ? new ComponentProxy(component) : nullptr);

        return context_component;
    }

    bool PluginEngine::init() {
        if(initialized && is_control && control_init_func)
            return control_init_func(controlPluginContext());
        if(initialized && !is_control && component_init_func)
            return component_init_func(componentPluginContext());
        return false;
    }

    bool PluginEngine::isDefault() const {
        if(initialized && is_default_func)
            return is_default_func();
        return false;
    }

    void PluginEngine::callPageCallback(const QString& page_name) {
        const auto func_name = QLatin1String("ifw_installer_callback_")+page_name;
        if(const auto callback_func = library.resolve(func_name.toLatin1().constData()))
            callback_func();
    }

    bool PluginEngine::callCreateOperations() const {
        if(initialized && component_create_operations_func)
            return component_create_operations_func();
        return false;
    }

    bool PluginEngine::callCreateOperationsForPath(const QString& path) const {
        if(initialized && component_create_operations_for_path_func)
            return component_create_operations_for_path_func();
        return false;
    }

    bool PluginEngine::callCreateOperationsForArchive(const QString& archive) const {
        if(initialized && component_create_operations_for_archive_func)
            return component_create_operations_for_archive_func();
        return false;
    }

    void PluginEngine::callBeginInstallation() const {
        if(initialized && component_begin_installation_func)
            return component_begin_installation_func();
    }
}

PluginContext::PluginContext(GuiProxy* gui, InstallerProxy* installer) : gui_proxy(gui), installer_proxy(installer) {
}

PluginContext::~PluginContext() {
    delete gui_proxy;
    delete installer_proxy;
}

GuiProxy* PluginContext::gui() const {
    return gui_proxy;
}

InstallerProxy* PluginContext::installer() const {
    return installer_proxy;
}

QInstaller::SystemInfo PluginContext::systemInfo() const {
    return QInstaller::SystemInfo();
}

ControlPluginContext::ControlPluginContext(GuiProxy* gui, InstallerProxy* installer) : PluginContext(gui, installer) {
}

ComponentPluginContext::ComponentPluginContext(GuiProxy* gui, InstallerProxy* installer, ComponentProxy* component) : PluginContext(gui, installer), component_proxy(component) {
}

ComponentPluginContext::~ComponentPluginContext() {
    delete component_proxy;
}

ComponentProxy* ComponentPluginContext::component() const {
    return component_proxy;
}
