#pragma once

#include <QObject>
#include <QWizard>
#include <QSettings>
#include "systeminfo.h"

namespace QInstaller {
    class PackageManagerGui;
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

class GuiProxy final : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(GuiProxy)

public:
    explicit GuiProxy(QInstaller::PackageManagerGui *gui);

    QWidget* pageById(int id) const;
    QWidget* pageByObjectName(const QString &name) const;

    QWidget* currentPageWidget() const;
    QWidget* pageWidgetByObjectName(const QString &name) const;

    QString defaultButtonText(int wizardButton) const;
    void clickButton(int wizardButton, int delayInMs = 0) const;
    void clickButton(const QString &objectName, int delayInMs = 0) const;
    bool isButtonEnabled(int wizardButton) const;
    void setWizardPageButtonText(int pageId, int buttonId, const QString &buttonText) const;

    void showSettingsButton(bool show) const;
    void setSettingsButtonEnabled(bool enable) const;

    void setSilent(bool silent) const;

    void setTextItems(QObject *object, const QStringList &items) const;

Q_SIGNALS:
    void interrupted();
    void languageChanged();
    void finishButtonClicked();
    void gotRestarted();
    void settingsButtonClicked();

public slots:
    void cancelButtonClicked() const;
    void reject() const;
    void rejectWithoutPrompt() const;
    void showFinishedPage() const;
    void setModified(bool value) const;

private:
    QInstaller::PackageManagerGui *m_gui;
};

class InstallerProxy final : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(InstallerProxy)

public:
    using Status = QInstaller::Plugin::Status;
    using WizardPage = QInstaller::Plugin::WizardPage;
    using SpaceInfo = QInstaller::Plugin::SpaceInfo;

    explicit InstallerProxy(QInstaller::PackageManagerCore *core);

    static bool virtualComponentsVisible();

    static bool noForceInstallation();

    static bool noDefaultInstallation();

    void setDependsOnLocalInstallerBinary();
    bool localInstallerBinaryUsed();

    QList<QVariant> execute(const QString &program,
        const QStringList &arguments = QStringList(), const QString &stdIn = QString(),
        const QString &stdInCodec = QLatin1String("latin1"),
        const QString &stdOutCodec = QLatin1String("latin1")) const;
    bool executeDetached(const QString &program,
        const QStringList &arguments = QStringList(),
        const QString &workingDirectory = QString()) const;
    QString environmentVariable(const QString &name) const;

    bool operationExists(const QString &name);
    bool performOperation(const QString &name, const QStringList &arguments);

    static bool versionMatches(const QString &version, const QString &requirement);

    static QString findLibrary(const QString &name, const QStringList &paths = QStringList());
    static QString findPath(const QString &name, const QStringList &paths = QStringList());

    void setInstallerBaseBinary(const QString &path);

    bool containsValue(const QString &key) const;
    void setValue(const QString &key, const QString &value);
    QString value(const QString &key, const QString &defaultValue = QString(), const int &format = QSettings::NativeFormat) const;
    QStringList values(const QString &key, const QStringList &defaultValue = QStringList()) const;
    QString key(const QString &value) const;

    void addUserRepositories(const QStringList &repositories);
    void setTemporaryRepositories(const QStringList &repositories,
                                              bool replace = false, bool compressed = false);
    void setAllowCompressedRepositoryInstall(bool allow);

    void autoAcceptMessageBoxes();
    void autoRejectMessageBoxes();
    void setMessageBoxAutomaticAnswer(const QString &identifier, int button);
    void acceptMessageBoxDefaultButton();

    void setAutoAcceptLicenses();
    void setFileDialogAutomaticAnswer(const QString &identifier, const QString &value);
    void removeFileDialogAutomaticAnswer(const QString &identifier);
    bool containsFileDialogAutomaticAnswer(const QString &identifier) const;

    bool isFileExtensionRegistered(const QString &extension) const;
    bool fileExists(const QString &filePath) const;
    QString readFile(const QString &filePath, const QString &codecName) const;
    QString readConsoleLine(const QString &title = QString(), qint64 maxlen = 0) const;

    QString toNativeSeparators(const QString &path);
    QString fromNativeSeparators(const QString &path);

    QInstaller::Component *componentByName(const QString &identifier) const;
    QList<QInstaller::Component *> components(const QString &regexp = QString()) const;

    bool calculateComponentsToInstall();

    bool recalculateAllComponents();

    bool calculateComponentsToUninstall();

    void setInstaller();
    bool isInstaller() const;
    bool isOfflineOnly() const;

    void setUninstaller();
    bool isUninstaller() const;

    void setUpdater();
    bool isUpdater() const;

    void setPackageManager();
    bool isPackageManager() const;

    bool isOfflineGenerator() const;

    bool isPackageViewer() const;

    bool isUserSetBinaryMarker() const;

    bool isCommandLineInstance() const;
    bool isCommandLineDefaultInstall() const;

    bool gainAdminRights();
    void dropAdminRights();
    bool hasAdminRights() const;

    qint64 requiredDiskSpace() const;
    quint64 requiredTemporaryDiskSpace() const;

    bool isProcessRunning(const QString &name) const;
    bool killProcess(const QString &absoluteFilePath, int timeout = 30000) const;

    bool addWizardPageWarning(const QString &message, WizardPage page, const QString &id, int position = 100);
    bool removeWizardPageWarning(const QString &id);
    bool setDefaultPageVisible(int page, bool visible);
    void setValidatorForCustomPage(QInstaller::Component *component, const QString &name,
                                               const QString &callbackName);
    void selectComponent(const QString &id);
    void deselectComponent(const QString &id);

public Q_SLOTS:
    bool runInstaller();
    bool runUninstaller();
    bool runPackageUpdater();
    bool runOfflineGenerator();
    void interrupt();
    void setCanceled();
    void languageChanged();
    void setCompleteUninstallation(bool complete);
    void cancelMetaInfoJob();

Q_SIGNALS:
    void aboutCalculateComponentsToInstall();
    void finishedCalculateComponentsToInstall();
    void aboutCalculateComponentsToUninstall();
    void finishedCalculateComponentsToUninstall();
    void componentAdded(QInstaller::Component *comp);
    void valueChanged(const QString &key, const QString &value);
    void statusChanged(Status);
    void defaultTranslationsLoadedForLanguage(QLocale lang);
    void currentPageChanged(int page);
    void finishButtonClicked();

    void metaJobProgress(int progress);
    void metaJobTotalProgress(int progress);
    void metaJobInfoMessage(const QString &message);

    void startAllComponentsReset();
    void finishAllComponentsReset(const QList<QInstaller::Component*> &rootComponents);

    void startUpdaterComponentsReset();
    void finishUpdaterComponentsReset(const QList<QInstaller::Component*> &componentsWithUpdates);

    void installationStarted();
    void installationInterrupted();
    void installationFinished();
    void updateFinished();
    void uninstallationStarted();
    void uninstallationFinished();
    void offlineGenerationStarted();
    void offlineGenerationFinished();
    void titleMessageChanged(const QString &title);
    void downloadArchivesFinished();

    void wizardPageInsertionRequested(QWidget *widget, WizardPage page);
    void wizardPageRemovalRequested(QWidget *widget);
    void wizardWidgetInsertionRequested(QWidget *widget, WizardPage page,
                                        int position);
    void wizardWidgetRemovalRequested(QWidget *widget);
    void wizardPageWarningInsertionRequested(const QString &message, WizardPage page, const QString &id, int position);
    void wizardPageWarningRemovalRequested(const QString &id);
    void wizardPageVisibilityChangeRequested(bool visible, int page);
    void setValidatorForCustomPageRequested(QInstaller::Component *component, const QString &name,
                                            const QString &callbackName);

    void setAutomatedPageSwitchEnabled(bool request);
    void coreNetworkSettingsChanged();

    void guiObjectChanged(QObject *gui);
    void unstableComponentFound(const QString &type, const QString &errorMessage, const QString &component);
    void installerBinaryMarkerChanged(qint64 magicMarker);
    void componentsRecalculated();
    void guiElementsReady();
    void installDirectoryChanged(const QString &newDirectory);
    void availableSpaceChanged(SpaceInfo spaceInfo);
    void metadataDownloadFailed();

private:
    QInstaller::PackageManagerCore* m_core;
};

class ComponentProxy final : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(ComponentProxy)

public:
    explicit ComponentProxy(QInstaller::Component *component);

    void setValue(const QString &key, const QString &value);
    QString value(const QString &key, const QString &defaultValue = QString()) const;

    void registerPathForUninstallation(const QString &path, bool wipe = false);

    void addDownloadableArchive(const QString &path);
    void removeDownloadableArchive(const QString &path);

    void addStopProcessForUpdateRequest(const QString &process);
    void removeStopProcessForUpdateRequest(const QString &process);
    void setStopProcessForUpdateRequest(const QString &process, bool requested);

    void addDependency(const QString &newDependency);
    void addAutoDependOn(const QString &newDependOn);

    bool isDefault() const;
    bool isAutoDependOn(const QSet<QString> &componentsToInstall) const;

    void setInstalled();
    bool isInstalled(const QString &version = QString()) const;
    bool installationRequested() const;

    void setUninstalled();
    bool isUninstalled() const;
    bool uninstallationRequested() const;

    bool isFromOnlineRepository() const;

    void setUpdateAvailable(bool isUpdateAvailable);
    bool isUpdateAvailable() const;
    bool updateRequested() const;

    bool componentChangeRequested();
    bool isForcedUpdate();

public Q_SLOTS:
    void setAutoCreateOperations(bool autoCreateOperations);

Q_SIGNALS:
    void loaded();
    void virtualStateChanged();
    void valueChanged(const QString &key, const QString &value);

private:
    QInstaller::Component* m_component;
};

class PluginContext {
public:
    using buttons = QWizard::WizardButton;

    PluginContext(GuiProxy* gui, InstallerProxy* installer);
    ~PluginContext();

    GuiProxy* gui() const;
    InstallerProxy* installer() const;
    QInstaller::SystemInfo systemInfo() const;

private:
    GuiProxy* gui_proxy;
    InstallerProxy* installer_proxy;
};

class ControlPluginContext : public PluginContext {
public:
    ControlPluginContext(GuiProxy* gui, InstallerProxy* installer);
};

class ComponentPluginContext : public PluginContext {
public:
    ComponentPluginContext(GuiProxy* gui, InstallerProxy* installer, ComponentProxy* component);
    ~ComponentPluginContext();

    ComponentProxy* component() const;

private:
    ComponentProxy* component_proxy;
};

#ifdef IFW_BUILDING_INSTALLER_FRAMEWORK
#include "packagemanagercore.h"

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

#   ifdef __cplusplus
}
#   endif

#endif
