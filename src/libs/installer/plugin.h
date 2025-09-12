#pragma once

#include <QObject>
#include <QWizard>
#include "systeminfo.h"
#include "packagemanagercore.h"

namespace QInstaller {
    class PackageManagerGui;
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
    using Status = QInstaller::PackageManagerCore::Status;
    using WizardPage = QInstaller::PackageManagerCore::WizardPage;
    using SpaceInfo = QInstaller::PackageManagerCore::SpaceInfo;

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

typedef bool(*IfwPluginControlInit)(ControlPluginContext*); // ifw_control_init
typedef bool(*IfwPluginComponentInit)(ComponentPluginContext*); // ifw_component_init

typedef bool(*IfwPluginComponentIsDefault)(); // ifw_component_is_default

//
