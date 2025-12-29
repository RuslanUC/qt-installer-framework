#pragma once

#include <QObject>
#include <QLibrary>
#include <QTemporaryFile>

#include "installer_global.h"

class PluginContext;
class ControlPluginContext;
class ComponentPluginContext;
class InstallerProxyCallbacks;
class ComponentProxyCallbacks;

typedef bool(*IfwPluginControlInit)(ControlPluginContext*); // ifw_control_init
typedef bool(*IfwPluginComponentInit)(ComponentPluginContext*); // ifw_component_init
typedef bool(*IfwPluginComponentIsDefault)(ComponentPluginContext*); // ifw_component_is_default
typedef bool(*IfwPluginComponentCreateOperations)(ComponentPluginContext*); // ifw_component_create_operations
typedef bool(*IfwPluginComponentCreateOperationsForPath)(ComponentPluginContext*, const QString& path); // ifw_component_create_operations_for_path
typedef bool(*IfwPluginComponentCreateOperationsForArchive)(ComponentPluginContext*, const QString& archive); // ifw_component_create_operations_for_archive
typedef void(*IfwPluginComponentBeginInstallation)(ComponentPluginContext*); // ifw_component_begin_installation
typedef int(*IfwPluginApiVersion)(); // ifw_component_begin_installation

namespace QInstaller {
    class PackageManagerCore;
    class Component;

    class INSTALLER_EXPORT PluginEngine final : public QObject {
        Q_OBJECT

    public:
        explicit PluginEngine(PackageManagerCore* parent);
        ~PluginEngine();

        void setComponent(Component* component);

        bool load(const QString& path);
        bool init();

        bool isDefault();

        void callPageCallback(const QString& page_name);
        bool callCreateOperations();
        bool callCreateOperationsForPath(const QString& path);
        bool callCreateOperationsForArchive(const QString& archive);

        void callBeginInstallation();

    private:
        PackageManagerCore* core;
        Component* component;

        ControlPluginContext* context_control = nullptr;
        ComponentPluginContext* context_component = nullptr;

        QLibrary library;
        IfwPluginControlInit control_init_func = nullptr;
        IfwPluginComponentInit component_init_func = nullptr;

        IfwPluginComponentIsDefault is_default_func = nullptr;
        IfwPluginComponentCreateOperations component_create_operations_func = nullptr;
        IfwPluginComponentCreateOperationsForPath component_create_operations_for_path_func = nullptr;
        IfwPluginComponentCreateOperationsForArchive component_create_operations_for_archive_func = nullptr;
        IfwPluginComponentBeginInstallation component_begin_installation_func = nullptr;

        bool is_control = false;
        bool initialized = false;

        QTemporaryFile* tempFile = nullptr;

        // TODO: also add gui_callbacks
        InstallerProxyCallbacks* installer_callbacks = nullptr;
        ComponentProxyCallbacks* component_callbacks = nullptr;

        ControlPluginContext* controlPluginContext();
        ComponentPluginContext* componentPluginContext();
    };
}

//Q_DECLARE_METATYPE(QInstaller::PluginEngine*)
