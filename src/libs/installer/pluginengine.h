#pragma once

#include <QObject>
#include <QLibrary>
#include "installer_global.h"

class PluginContext;
class ControlPluginContext;
class ComponentPluginContext;

typedef bool(*IfwPluginControlInit)(ControlPluginContext*); // ifw_control_init
typedef bool(*IfwPluginComponentInit)(ComponentPluginContext*); // ifw_component_init
typedef bool(*IfwPluginComponentIsDefault)(); // ifw_component_is_default
typedef bool(*IfwPluginComponentCreateOperations)(); // ifw_component_create_operations
typedef bool(*IfwPluginComponentCreateOperationsForPath)(); // ifw_component_create_operations_for_path
typedef bool(*IfwPluginComponentCreateOperationsForArchive)(); // ifw_component_create_operations_for_archive
typedef void(*IfwPluginComponentBeginInstallation)(); // ifw_component_begin_installation

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

        bool isDefault() const;

        void callPageCallback(const QString& page_name);
        bool callCreateOperations() const;
        bool callCreateOperationsForPath(const QString& path) const;
        bool callCreateOperationsForArchive(const QString& archive) const;

        void callBeginInstallation() const;

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

        ControlPluginContext* controlPluginContext();
        ComponentPluginContext* componentPluginContext();
    };
}

//Q_DECLARE_METATYPE(QInstaller::PluginEngine*)
