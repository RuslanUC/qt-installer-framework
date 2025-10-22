#pragma once

#include <cstdint>
#include <cstdlib>
#include <set>
#include <string>
#include <vector>
#include <functional>

#ifdef IFW_BUILDING_INSTALLER_FRAMEWORK
#include "packagemanagercore.h"
#include "packagemanagergui.h"
#endif

#define IFW_PLUGIN_API_VERSION 2

namespace QInstaller {
    class PackageManagerCore;
    class Component;

    namespace Plugin {
        enum Status {
            Success = EXIT_SUCCESS,
            Failure = EXIT_FAILURE,
            Running = 2,
            Canceled = 3,
            Unfinished = 4,
            ForceUpdate = 5,
            EssentialUpdated = 6,
            NoPackagesFound = 7,
            MetaDownloadFailure = 8
        };

        enum WizardPage {
            Introduction = 0x1000,
            TargetDirectory = 0x2000,
            ComponentSelection = 0x3000,
            LicenseCheck = 0x4000,
            StartMenuSelection = 0x5000,
            ReadyForInstallation = 0x6000,
            PerformInstallation = 0x7000,
            InstallationFinished = 0x8000,
            End = 0xffff
        };

        enum SpaceInfo {
            SpaceAvailable,
            SpaceExceeded,
            ExecutableSizeExceeded,
            RecommendedSizeExceeded
        };
    }
}

typedef struct SystemInfoProxy {
#ifdef IFW_BUILDING_INSTALLER_FRAMEWORK
    SystemInfoProxy();
#endif

    std::function<std::string()> currentCpuArchitecture;
    std::function<std::string()> buildCpuArchitecture;
    std::function<std::string()> kernelType;
    std::function<std::string()> kernelVersion;
    std::function<std::string()> productType;
    std::function<std::string()> productVersion;
    std::function<std::string()> prettyProductName;
} SystemInfoProxy;

typedef struct GuiProxy {
#ifdef IFW_BUILDING_INSTALLER_FRAMEWORK
    explicit GuiProxy(QInstaller::PackageManagerGui*);
#endif

    std::function<void*(int id)> pageById;
    std::function<void*(const std::string& name)> pageByObjectName;

    std::function<void*()> currentPageWidget;
    std::function<void*(const std::string& name)> pageWidgetByObjectName;

    std::function<std::string(int wizardButton)> defaultButtonText;
    std::function<void(int wizardButton, int delayInMs)> clickButtonById;
    std::function<void(const std::string& objectName, int delayInMs)> clickButtonByName;
    std::function<bool(int wizardButton)> isButtonEnabled;
    std::function<void(int pageId, int buttonId, const std::string& buttonText)> setWizardPageButtonText;

    std::function<void(bool show)> showSettingsButton;
    std::function<void(bool enable)> setSettingsButtonEnabled;

    std::function<void(bool silent)> setSilent;

    std::function<void()> cancelButtonClicked;
    std::function<void()> reject;
    std::function<void()> rejectWithoutPrompt;
    std::function<void()> showFinishedPage;
    std::function<void(bool value)> setModified;

    // Signals

    std::function<void(std::function<void()> callback)> setInterruptedCallback;
    std::function<void(std::function<void()> callback)> setLanguageChangedCallback;
    std::function<void(std::function<void()> callback)> setFinishButtonClickedCallback;
    std::function<void(std::function<void()> callback)> setGotRestartedCallback;
    std::function<void(std::function<void()> callback)> setSettingsButtonClickedCallback;
} GuiProxy;

typedef struct InstallerProxy {
    using Status = QInstaller::Plugin::Status;
    using WizardPage = QInstaller::Plugin::WizardPage;
    using SpaceInfo = QInstaller::Plugin::SpaceInfo;

#ifdef IFW_BUILDING_INSTALLER_FRAMEWORK
    explicit InstallerProxy(QInstaller::PackageManagerCore*);
#endif

    std::function<bool()> virtualComponentsVisible;

    std::function<bool()> noForceInstallation;

    std::function<bool()> noDefaultInstallation;

    std::function<void()> setDependsOnLocalInstallerBinary;
    std::function<bool()> localInstallerBinaryUsed;

    std::function<std::tuple<std::string, int>(const std::string &program, const std::vector<std::string> &arguments, const std::string &stdIn, const std::string &stdInCodec, const std::string &stdOutCodec)> execute;
    std::function<bool(const std::string &program, const std::vector<std::string> &arguments, const std::string &workingDirectory)> executeDetached;
    std::function<std::string(const std::string &name)> environmentVariable;

    std::function<bool(const std::string &name)> operationExists;
    std::function<bool(const std::string &name, const std::vector<std::string> &arguments)> performOperation;

    std::function<bool(const std::string &version, const std::string &requirement)> versionMatches;

    std::function<std::string(const std::string &name, const std::vector<std::string> &paths)> findLibrary;
    std::function<std::string(const std::string &name, const std::vector<std::string> &paths)> findPath;

    std::function<void(const std::string &path)> setInstallerBaseBinary;

    std::function<bool(const std::string &key)> containsValue;
    std::function<void(const std::string &key, const std::string &value)> setValue;
    std::function<std::string(const std::string &key, const std::string &defaultValue, const int &format)> value;
    std::function<std::vector<std::string>(const std::string &key, const std::vector<std::string> &defaultValue)> values;
    std::function<std::string(const std::string &value)> key;

    std::function<void(const std::vector<std::string> &repositories)> addUserRepositories;
    std::function<void(const std::vector<std::string> &repositories, bool replace, bool compressed)> setTemporaryRepositories;
    std::function<void(bool allow)> setAllowCompressedRepositoryInstall;

    std::function<void()> autoAcceptMessageBoxes;
    std::function<void()> autoRejectMessageBoxes;
    std::function<void(const std::string &identifier, int button)> setMessageBoxAutomaticAnswer;
    std::function<void()> acceptMessageBoxDefaultButton;

    std::function<void()> setAutoAcceptLicenses;
    std::function<void(const std::string &identifier, const std::string &value)> setFileDialogAutomaticAnswer;
    std::function<void(const std::string &identifier)> removeFileDialogAutomaticAnswer;
    std::function<bool(const std::string &identifier)> containsFileDialogAutomaticAnswer;

    std::function<bool(const std::string &extension)> isFileExtensionRegistered;
    std::function<bool(const std::string &filePath)> fileExists;
    std::function<std::string(const std::string &filePath, const std::string &codecName)> readFile;
    std::function<std::string(const std::string &title, int64_t maxlen)> readConsoleLine;

    std::function<std::string(const std::string &path)> toNativeSeparators;
    std::function<std::string(const std::string &path)> fromNativeSeparators;

    std::function<QInstaller::Component *(const std::string &identifier)> componentByName;
    std::function<std::vector<QInstaller::Component *>(const std::string &regexp)> components;

    std::function<bool()> calculateComponentsToInstall;

    std::function<bool()> recalculateAllComponents;

    std::function<bool()> calculateComponentsToUninstall;

    std::function<void()> setInstaller;
    std::function<bool()> isInstaller;
    std::function<bool()> isOfflineOnly;

    std::function<void()> setUninstaller;
    std::function<bool()> isUninstaller;

    std::function<void()> setUpdater;
    std::function<bool()> isUpdater;

    std::function<void()> setPackageManager;
    std::function<bool()> isPackageManager;

    std::function<bool()> isOfflineGenerator;

    std::function<bool()> isPackageViewer;

    std::function<bool()> isUserSetBinaryMarker;

    std::function<bool()> isCommandLineInstance;
    std::function<bool()> isCommandLineDefaultInstall;

    std::function<bool()> gainAdminRights;
    std::function<void()> dropAdminRights;
    std::function<bool()> hasAdminRights;

    std::function<int64_t()> requiredDiskSpace;
    std::function<uint64_t()> requiredTemporaryDiskSpace;

    std::function<bool(const std::string &name)> isProcessRunning;
    std::function<bool(const std::string &absoluteFilePath, int timeout)> killProcess;

    std::function<bool(const std::string &message, WizardPage page, const std::string &id, int position)> addWizardPageWarning;
    std::function<bool(const std::string &id)> removeWizardPageWarning;
    std::function<bool(int page, bool visible)> setDefaultPageVisible;
    std::function<void(QInstaller::Component *component, const std::string &name, const std::string &callbackName)> setValidatorForCustomPage;
    std::function<void(const std::string &id)> selectComponent;
    std::function<void(const std::string &id)> deselectComponent;

    std::function<bool()> runInstaller;
    std::function<bool()> runUninstaller;
    std::function<bool()> runPackageUpdater;
    std::function<bool()> runOfflineGenerator;
    std::function<void()> interrupt;
    std::function<void()> setCanceled;
    std::function<void()> languageChanged;
    std::function<void(bool complete)> setCompleteUninstallation;
    std::function<void()> cancelMetaInfoJob;

    // Signals

    std::function<void(std::function<void()> callback)> setAboutCalculateComponentsToInstallCallback;
    std::function<void(std::function<void()> callback)> setFinishedCalculateComponentsToInstallCallback;
    std::function<void(std::function<void()> callback)> setAboutCalculateComponentsToUninstallCallback;
    std::function<void(std::function<void()> callback)> setFinishedCalculateComponentsToUninstallCallback;
    std::function<void(std::function<void(QInstaller::Component *comp)> callback)> setComponentAddedCallback;
    std::function<void(std::function<void(const std::string &key, const std::string &value)> callback)> setValueChangedCallback;
    std::function<void(std::function<void(Status)> callback)> setStatusChangedCallback;
    std::function<void(std::function<void(int page)> callback)> setCurrentPageChangedCallback;
    std::function<void(std::function<void()> callback)> setFinishButtonClickedCallback;

    std::function<void(std::function<void(int progress)> callback)> setMetaJobProgressCallback;
    std::function<void(std::function<void(int progress)> callback)> setMetaJobTotalProgressCallback;
    std::function<void(std::function<void(const std::string &message)> callback)> setMetaJobInfoMessageCallback;

    std::function<void(std::function<void()> callback)> setStartAllComponentsResetCallback;
    std::function<void(std::function<void(const std::vector<QInstaller::Component*> &rootComponents)> callback)> setFinishAllComponentsResetCallback;

    std::function<void(std::function<void()> callback)> setStartUpdaterComponentsResetCallback;
    std::function<void(std::function<void(const std::vector<QInstaller::Component*> &componentsWithUpdates)> callback)> setFinishUpdaterComponentsResetCallback;

    std::function<void(std::function<void()> callback)> setInstallationStartedCallback;
    std::function<void(std::function<void()> callback)> setInstallationInterruptedCallback;
    std::function<void(std::function<void()> callback)> setInstallationFinishedCallback;
    std::function<void(std::function<void()> callback)> setUpdateFinishedCallback;
    std::function<void(std::function<void()> callback)> setUninstallationStartedCallback;
    std::function<void(std::function<void()> callback)> setUninstallationFinishedCallback;
    std::function<void(std::function<void()> callback)> setOfflineGenerationStartedCallback;
    std::function<void(std::function<void()> callback)> setOfflineGenerationFinishedCallback;
    std::function<void(std::function<void(const std::string &title)> callback)> setTitleMessageChangedCallback;
    std::function<void(std::function<void()> callback)> setDownloadArchivesFinishedCallback;

    std::function<void(std::function<void(void* /* QWidget */ widget, WizardPage page)> callback)> setWizardPageInsertionRequestedCallback;
    std::function<void(std::function<void(void* /* QWidget */ widget)> callback)> setWizardPageRemovalRequestedCallback;
    std::function<void(std::function<void(void* /* QWidget */ widget, WizardPage page, int position)> callback)> setWizardWidgetInsertionRequestedCallback;
    std::function<void(std::function<void(void* /* QWidget */ widget)> callback)> setWizardWidgetRemovalRequestedCallback;
    std::function<void(std::function<void(const std::string &message, WizardPage page, const std::string &id, int position)> callback)> setWizardPageWarningInsertionRequestedCallback;
    std::function<void(std::function<void(const std::string &id)> callback)> setWizardPageWarningRemovalRequestedCallback;
    std::function<void(std::function<void(bool visible, int page)> callback)> setWizardPageVisibilityChangeRequestedCallback;
    std::function<void(std::function<void(QInstaller::Component *component, const std::string &name, const std::string &callbackName)> callback)> setSetValidatorForCustomPageRequestedCallback;

    std::function<void(std::function<void(bool request)> callback)> setSetAutomatedPageSwitchEnabledCallback;
    std::function<void(std::function<void()> callback)> setCoreNetworkSettingsChangedCallback;

    std::function<void(std::function<void(void* /* QObject */ gui)> callback)> setGuiObjectChangedCallback;
    std::function<void(std::function<void(const std::string &type, const std::string &errorMessage, const std::string &component)> callback)> setUnstableComponentFoundCallback;
    std::function<void(std::function<void(int64_t magicMarker)> callback)> setInstallerBinaryMarkerChangedCallback;
    std::function<void(std::function<void()> callback)> setComponentsRecalculatedCallback;
    std::function<void(std::function<void()> callback)> setGuiElementsReadyCallback;
    std::function<void(std::function<void(const std::string &newDirectory)> callback)> setInstallDirectoryChangedCallback;
    std::function<void(std::function<void(SpaceInfo spaceInfo)> callback)> setAvailableSpaceChangedCallback;
    std::function<void(std::function<void()> callback)> setMetadataDownloadFailedCallback;
} InstallerProxy;

typedef struct ComponentProxy {
#ifdef IFW_BUILDING_INSTALLER_FRAMEWORK
    explicit ComponentProxy(QInstaller::Component*);
#endif

    std::function<void(const std::string &key, const std::string &value)> setValue;
    std::function<std::string(const std::string &key, const std::string &defaultValue)> value;

    std::function<void(const std::string &path, bool wipe)> registerPathForUninstallation;

    std::function<void(const std::string &path)> addDownloadableArchive;
    std::function<void(const std::string &path)> removeDownloadableArchive;

    std::function<void(const std::string &process)> addStopProcessForUpdateRequest;
    std::function<void(const std::string &process)> removeStopProcessForUpdateRequest;
    std::function<void(const std::string &process, bool requested)> setStopProcessForUpdateRequest;

    std::function<void(const std::string &newDependency)> addDependency;
    std::function<void(const std::string &newDependOn)> addAutoDependOn;

    std::function<bool()> isDefault;
    std::function<bool(const std::set<std::string> &componentsToInstall)> isAutoDependOn;

    std::function<void()> setInstalled;
    std::function<bool(const std::string &version)> isInstalled;
    std::function<bool()> installationRequested;

    std::function<void()> setUninstalled;
    std::function<bool()> isUninstalled;
    std::function<bool()> uninstallationRequested;

    std::function<bool()> isFromOnlineRepository;

    std::function<void(bool isUpdateAvailable)> setUpdateAvailable;
    std::function<bool()> isUpdateAvailable;
    std::function<bool()> updateRequested;

    std::function<bool()> componentChangeRequested;
    std::function<bool()> isForcedUpdate;

    std::function<bool(const std::string &operation, const std::vector<std::string> &parameters)> addOperation;

    std::function<void(bool autoCreateOperations)> setAutoCreateOperations;

    // Signals

    std::function<void(std::function<void()> callback)> setLoadedCallback;
    std::function<void(std::function<void()> callback)> setVirtualStateChangedCallback;
    std::function<void(std::function<void(const std::string &key, const std::string &value)> callback)> setValueChangedCallback;
} ComponentProxy;

typedef struct ControlPluginContext {
#ifdef IFW_BUILDING_INSTALLER_FRAMEWORK
    ControlPluginContext(GuiProxy* gui, InstallerProxy* installer, SystemInfoProxy* systemInfo);
    ~ControlPluginContext();
#endif

    GuiProxy* gui;
    InstallerProxy* installer;
    SystemInfoProxy* systemInfo;
} ControlPluginContext;

typedef struct ComponentPluginContext {
#ifdef IFW_BUILDING_INSTALLER_FRAMEWORK
    ComponentPluginContext(GuiProxy* gui, InstallerProxy* installer, ComponentProxy* component, SystemInfoProxy* systemInfo);
    ~ComponentPluginContext();
#endif

    GuiProxy* gui;
    InstallerProxy* installer;
    ComponentProxy* component;
    SystemInfoProxy* systemInfo;
} ComponentPluginContext;

#ifdef IFW_BUILDING_INSTALLER_FRAMEWORK
// TODO: msvc
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wenum-compare"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wenum-compare"
#endif

static_assert(QInstaller::PackageManagerCore::Status::Success == QInstaller::Plugin::Status::Success);
static_assert(QInstaller::PackageManagerCore::Status::Failure == QInstaller::Plugin::Status::Failure);
static_assert(QInstaller::PackageManagerCore::Status::Running == QInstaller::Plugin::Status::Running);
static_assert(QInstaller::PackageManagerCore::Status::Canceled == QInstaller::Plugin::Status::Canceled);
static_assert(QInstaller::PackageManagerCore::Status::Unfinished == QInstaller::Plugin::Status::Unfinished);
static_assert(QInstaller::PackageManagerCore::Status::ForceUpdate == QInstaller::Plugin::Status::ForceUpdate);
static_assert(QInstaller::PackageManagerCore::Status::EssentialUpdated == QInstaller::Plugin::Status::EssentialUpdated);
static_assert(QInstaller::PackageManagerCore::Status::NoPackagesFound == QInstaller::Plugin::Status::NoPackagesFound);
static_assert(QInstaller::PackageManagerCore::Status::MetaDownloadFailure == QInstaller::Plugin::Status::MetaDownloadFailure);

static_assert(QInstaller::PackageManagerCore::WizardPage::Introduction == QInstaller::Plugin::WizardPage::Introduction);
static_assert(QInstaller::PackageManagerCore::WizardPage::TargetDirectory == QInstaller::Plugin::WizardPage::TargetDirectory);
static_assert(QInstaller::PackageManagerCore::WizardPage::ComponentSelection == QInstaller::Plugin::WizardPage::ComponentSelection);
static_assert(QInstaller::PackageManagerCore::WizardPage::LicenseCheck == QInstaller::Plugin::WizardPage::LicenseCheck);
static_assert(QInstaller::PackageManagerCore::WizardPage::StartMenuSelection == QInstaller::Plugin::WizardPage::StartMenuSelection);
static_assert(QInstaller::PackageManagerCore::WizardPage::ReadyForInstallation == QInstaller::Plugin::WizardPage::ReadyForInstallation);
static_assert(QInstaller::PackageManagerCore::WizardPage::PerformInstallation == QInstaller::Plugin::WizardPage::PerformInstallation);
static_assert(QInstaller::PackageManagerCore::WizardPage::InstallationFinished == QInstaller::Plugin::WizardPage::InstallationFinished);
static_assert(QInstaller::PackageManagerCore::WizardPage::End == QInstaller::Plugin::WizardPage::End);

static_assert(QInstaller::PackageManagerCore::SpaceInfo::SpaceAvailable == QInstaller::Plugin::SpaceInfo::SpaceAvailable);
static_assert(QInstaller::PackageManagerCore::SpaceInfo::SpaceExceeded == QInstaller::Plugin::SpaceInfo::SpaceExceeded);
static_assert(QInstaller::PackageManagerCore::SpaceInfo::ExecutableSizeExceeded == QInstaller::Plugin::SpaceInfo::ExecutableSizeExceeded);
static_assert(QInstaller::PackageManagerCore::SpaceInfo::RecommendedSizeExceeded == QInstaller::Plugin::SpaceInfo::RecommendedSizeExceeded);

// TODO: msvc
#if defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

#else

#   ifdef __cplusplus
extern "C" {
#   endif

    bool ifw_control_init(ControlPluginContext*);
    bool ifw_component_init(ComponentPluginContext*);
    bool ifw_component_is_default(ComponentPluginContext*);
    bool ifw_component_create_operations(ComponentPluginContext*);
    bool ifw_component_create_operations_for_path(ComponentPluginContext*, const std::string&);
    bool ifw_component_create_operations_for_archive(ComponentPluginContext*, const std::string&);
    void ifw_component_begin_installation(ComponentPluginContext*);

    int __ifw_plugin_api_version() {
        return IFW_PLUGIN_API_VERSION;
    }
#   ifdef __cplusplus
}
#   endif

#endif
