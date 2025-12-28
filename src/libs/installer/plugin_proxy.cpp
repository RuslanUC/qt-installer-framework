#include <iostream>

#include "plugin.h"
#include "packagemanagergui.h"
#include "packagemanagercore.h"
#include "component.h"

SystemInfoProxy::SystemInfoProxy() {
    currentCpuArchitecture = [] {
        return QSysInfo::currentCpuArchitecture().toStdString();
    };
    buildCpuArchitecture = [] {
        return QSysInfo::buildCpuArchitecture().toStdString();
    };
    kernelType = [] {
        return QSysInfo::kernelType().toStdString();
    };
    kernelVersion = [] {
        return QSysInfo::kernelVersion().toStdString();
    };
    productType = [] {
        return QSysInfo::productType().toStdString();
    };
    productVersion = [] {
        return QSysInfo::productVersion().toStdString();
    };
    prettyProductName = [] {
        return QSysInfo::prettyProductName().toStdString();
    };
}

GuiProxy::GuiProxy(QInstaller::PackageManagerGui* gui) {
    pageById = [gui](int id) {
        return gui->pageById(id);
    };
    pageByObjectName = [gui](const std::string& name) {
        return gui->pageByObjectName(QString::fromStdString(name));
    };

    currentPageWidget = [gui]() {
        return gui->currentPageWidget();
    };
    pageWidgetByObjectName = [gui](const std::string& name) {
        return gui->pageWidgetByObjectName(QString::fromStdString(name));
    };

    defaultButtonText = [gui](int wizardButton) {
        return gui->defaultButtonText(wizardButton).toStdString();
    };
    clickButtonById = [gui](int wizardButton, int delayInMs) {
        return gui->clickButton(wizardButton, delayInMs);
    };
    clickButtonByName = [gui](const std::string& objectName, int delayInMs) {
        return gui->clickButton(QString::fromStdString(objectName), delayInMs);
    };
    isButtonEnabled = [gui](int wizardButton) {
        return gui->isButtonEnabled(wizardButton);
    };
    setWizardPageButtonText = [gui](int pageId, int buttonId, const std::string& buttonText) {
        return gui->setWizardPageButtonText(pageId, buttonId, QString::fromStdString(buttonText));
    };

    showSettingsButton = [gui](bool show) {
        return gui->showSettingsButton(show);
    };
    setSettingsButtonEnabled = [gui](bool enable) {
        return gui->setSettingsButtonEnabled(enable);
    };

    setSilent = [gui](bool silent) {
        return gui->setSilent(silent);
    };

    cancelButtonClicked = [gui]() {
        return gui->cancelButtonClicked();
    };
    reject = [gui]() {
        return gui->reject();
    };
    rejectWithoutPrompt = [gui]() {
        return gui->rejectWithoutPrompt();
    };
    showFinishedPage = [gui]() {
        return gui->showFinishedPage();
    };
    setModified = [gui](bool value) {
        return gui->setModified(value);
    };
}

InstallerProxy::InstallerProxy(QInstaller::PackageManagerCore* core, InstallerProxyCallbacks* callbacks) {
    virtualComponentsVisible = [core]() {
        return core->virtualComponentsVisible();
    };

    noForceInstallation = [core]() {
        return core->noForceInstallation();
    };

    noDefaultInstallation = [core]() {
        return core->noDefaultInstallation();
    };

    setDependsOnLocalInstallerBinary = [core]() {
        return core->setDependsOnLocalInstallerBinary();
    };
    localInstallerBinaryUsed = [core]() {
        return core->localInstallerBinaryUsed();
    };

    execute = [core](const std::string& program, const std::vector<std::string>& arguments, const std::string& stdIn,
                     const std::string& stdInCodec, const std::string& stdOutCodec) {
        QStringList args;
        for (const auto& arg : arguments)
            args.append(QString::fromStdString(arg));

        const auto result = core->execute(QString::fromStdString(program), args, QString::fromStdString(stdIn),
                                          QString::fromStdString(stdInCodec), QString::fromStdString(stdOutCodec));
        std::tuple<std::string, int> resultTup = {
            !result.empty() ? result[0].toString().toStdString() : "",
            result.size() > 1 ? result[1].toInt() : 0,
        };

        return resultTup;
    };
    executeDetached = [core](const std::string& program, const std::vector<std::string>& arguments,
                             const std::string& workingDirectory) {
        QStringList args;
        for (const auto& arg : arguments)
            args.append(QString::fromStdString(arg));
        return core->executeDetached(QString::fromStdString(program), args, QString::fromStdString(workingDirectory));
    };
    environmentVariable = [core](const std::string& name) {
        return core->environmentVariable(QString::fromStdString(name)).toStdString();
    };

    operationExists = [core](const std::string& name) {
        return core->operationExists(QString::fromStdString(name));
    };
    performOperation = [core](const std::string& name, const std::vector<std::string>& arguments) {
        QStringList args;
        for (const auto& arg : arguments)
            args.append(QString::fromStdString(arg));
        return core->performOperation(QString::fromStdString(name), args);
    };

    versionMatches = [core](const std::string& version, const std::string& requirement) {
        return core->versionMatches(QString::fromStdString(version), QString::fromStdString(requirement));
    };

    findLibrary = [core](const std::string& name, const std::vector<std::string>& paths) {
        QStringList pathsQt;
        for (const auto& path : paths)
            pathsQt.append(QString::fromStdString(path));
        return core->findLibrary(QString::fromStdString(name), pathsQt).toStdString();
    };
    findPath = [core](const std::string& name, const std::vector<std::string>& paths) {
        QStringList pathsQt;
        for (const auto& path : paths)
            pathsQt.append(QString::fromStdString(path));
        return core->findPath(QString::fromStdString(name), pathsQt).toStdString();
    };

    setInstallerBaseBinary = [core](const std::string& path) {
        return core->setInstallerBaseBinary(QString::fromStdString(path));
    };

    containsValue = [core](const std::string& key) {
        return core->containsValue(QString::fromStdString(key));
    };
    setValue = [core](const std::string& key, const std::string& value) {
        return core->setValue(QString::fromStdString(key), QString::fromStdString(value));
    };
    value = [core](const std::string& key, const std::string& defaultValue, const int& format) {
        return core->value(QString::fromStdString(key), QString::fromStdString(defaultValue), format).toStdString();
    };
    values = [core](const std::string& key, const std::vector<std::string>& defaultValue) {
        QStringList defaults;
        for (const auto& def : defaultValue)
            defaults.append(QString::fromStdString(def));

        const auto result = core->values(QString::fromStdString(key), defaults);
        std::vector<std::string> resultVec;
        for (const auto& item : result) {
            resultVec.push_back(item.toStdString());
        }

        return resultVec;
    };
    key = [core](const std::string& value) {
        return core->key(QString::fromStdString(value)).toStdString();
    };

    addUserRepositories = [core](const std::vector<std::string>& repositories) {
        QStringList repos;
        for (const auto& repo : repositories)
            repos.append(QString::fromStdString(repo));

        return core->addUserRepositories(repos);
    };
    setTemporaryRepositories = [core](const std::vector<std::string>& repositories, bool replace, bool compressed) {
        QStringList repos;
        for (const auto& repo : repositories)
            repos.append(QString::fromStdString(repo));
        return core->setTemporaryRepositories(repos, replace, compressed);
    };
    setAllowCompressedRepositoryInstall = [core](bool allow) {
        return core->setAllowCompressedRepositoryInstall(allow);
    };

    autoAcceptMessageBoxes = [core]() {
        return core->autoAcceptMessageBoxes();
    };
    autoRejectMessageBoxes = [core]() {
        return core->autoRejectMessageBoxes();
    };
    setMessageBoxAutomaticAnswer = [core](const std::string& identifier, int button) {
        return core->setMessageBoxAutomaticAnswer(QString::fromStdString(identifier), button);
    };
    acceptMessageBoxDefaultButton = [core]() {
        return core->acceptMessageBoxDefaultButton();
    };

    setAutoAcceptLicenses = [core]() {
        return core->setAutoAcceptLicenses();
    };
    setFileDialogAutomaticAnswer = [core](const std::string& identifier, const std::string& value) {
        return core->setFileDialogAutomaticAnswer(QString::fromStdString(identifier), QString::fromStdString(value));
    };
    removeFileDialogAutomaticAnswer = [core](const std::string& identifier) {
        return core->removeFileDialogAutomaticAnswer(QString::fromStdString(identifier));
    };
    containsFileDialogAutomaticAnswer = [core](const std::string& identifier) {
        return core->containsFileDialogAutomaticAnswer(QString::fromStdString(identifier));
    };

    isFileExtensionRegistered = [core](const std::string& extension) {
        return core->isFileExtensionRegistered(QString::fromStdString(extension));
    };
    fileExists = [core](const std::string& filePath) {
        return core->fileExists(QString::fromStdString(filePath));
    };
    readFile = [core](const std::string& filePath, const std::string& codecName) {
        return core->readFile(QString::fromStdString(filePath), QString::fromStdString(codecName)).toStdString();
    };
    readConsoleLine = [core](const std::string& title, int64_t maxlen) {
        return core->readConsoleLine(QString::fromStdString(title), maxlen).toStdString();
    };

    toNativeSeparators = [core](const std::string& path) {
        return core->toNativeSeparators(QString::fromStdString(path)).toStdString();
    };
    fromNativeSeparators = [core](const std::string& path) {
        return core->fromNativeSeparators(QString::fromStdString(path)).toStdString();
    };

    componentByName = [core](const std::string& identifier) {
        return core->componentByName(QString::fromStdString(identifier));
    };
    components = [core](const std::string& regexp) {
        const auto components = core->components(QString::fromStdString(regexp));
        std::vector<QInstaller::Component*> componentsVec;
        for (const auto& comp : components)
            componentsVec.push_back(comp);

        return componentsVec;
    };

    calculateComponentsToInstall = [core]() {
        return core->calculateComponentsToInstall();
    };

    recalculateAllComponents = [core]() {
        return core->recalculateAllComponents();
    };

    calculateComponentsToUninstall = [core]() {
        return core->calculateComponentsToUninstall();
    };

    setInstaller = [core]() {
        return core->setInstaller();
    };
    isInstaller = [core]() {
        return core->isInstaller();
    };
    isOfflineOnly = [core]() {
        return core->isOfflineOnly();
    };

    setUninstaller = [core]() {
        return core->setUninstaller();
    };
    isUninstaller = [core]() {
        return core->isUninstaller();
    };

    setUpdater = [core]() {
        return core->setUpdater();
    };
    isUpdater = [core]() {
        return core->isUpdater();
    };

    setPackageManager = [core]() {
        return core->setPackageManager();
    };
    isPackageManager = [core]() {
        return core->isPackageManager();
    };

    isOfflineGenerator = [core]() {
        return core->isOfflineGenerator();
    };

    isPackageViewer = [core]() {
        return core->isPackageViewer();
    };

    isUserSetBinaryMarker = [core]() {
        return core->isUserSetBinaryMarker();
    };

    isCommandLineInstance = [core]() {
        return core->isCommandLineInstance();
    };
    isCommandLineDefaultInstall = [core]() {
        return core->isCommandLineDefaultInstall();
    };

    gainAdminRights = [core]() {
        return core->gainAdminRights();
    };
    dropAdminRights = [core]() {
        return core->dropAdminRights();
    };
    hasAdminRights = [core]() {
        return core->hasAdminRights();
    };

    requiredDiskSpace = [core]() {
        return core->requiredDiskSpace();
    };
    requiredTemporaryDiskSpace = [core]() {
        return core->requiredTemporaryDiskSpace();
    };

    isProcessRunning = [core](const std::string& name) {
        return core->isProcessRunning(QString::fromStdString(name));
    };
    killProcess = [core](const std::string& absoluteFilePath, int timeout) {
        return core->killProcess(QString::fromStdString(absoluteFilePath), timeout);
    };

    addWizardPageWarning = [core](const std::string& message, WizardPage page, const std::string& id, int position) {
        return core->addWizardPageWarning(QString::fromStdString(message),
                                          (QInstaller::PackageManagerCore::WizardPage)page, QString::fromStdString(id),
                                          position);
    };
    removeWizardPageWarning = [core](const std::string& id) {
        return core->removeWizardPageWarning(QString::fromStdString(id));
    };
    setDefaultPageVisible = [core](int page, bool visible) {
        return core->setDefaultPageVisible(page, visible);
    };
    setValidatorForCustomPage = [core](QInstaller::Component* component, const std::string& name,
                                       const std::string& callbackName) {
        return core->setValidatorForCustomPage(component, QString::fromStdString(name),
                                               QString::fromStdString(callbackName));
    };
    selectComponent = [core](const std::string& id) {
        return core->selectComponent(QString::fromStdString(id));
    };
    deselectComponent = [core](const std::string& id) {
        return core->deselectComponent(QString::fromStdString(id));
    };

    runInstaller = [core]() {
        return core->runInstaller();
    };
    runUninstaller = [core]() {
        return core->runUninstaller();
    };
    runPackageUpdater = [core]() {
        return core->runPackageUpdater();
    };
    runOfflineGenerator = [core]() {
        return core->runOfflineGenerator();
    };
    interrupt = [core]() {
        return core->interrupt();
    };
    setCanceled = [core]() {
        return core->setCanceled();
    };
    languageChanged = [core]() {
        return core->languageChanged();
    };
    setCompleteUninstallation = [core](bool complete) {
        return core->setCompleteUninstallation(complete);
    };
    cancelMetaInfoJob = [core]() {
        return core->cancelMetaInfoJob();
    };

    setAboutCalculateComponentsToInstallCallback = [core, callbacks](std::function<void()> callback) {
        callbacks->aboutCalculateComponentsToInstallCallback = callback;
        callbacks->aboutCalculateComponentsToInstallConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::aboutCalculateComponentsToInstall, core,
            [callbacks] {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->aboutCalculateComponentsToInstallCallback();
            });
    };
    setFinishedCalculateComponentsToInstallCallback = [core, callbacks](std::function<void()> callback) {
        callbacks->finishedCalculateComponentsToInstallCallback = callback;
        callbacks->finishedCalculateComponentsToInstallConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::finishedCalculateComponentsToInstall, core,
            [callbacks] {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->finishedCalculateComponentsToInstallCallback();
            });
    };
    setAboutCalculateComponentsToUninstallCallback = [core, callbacks](std::function<void()> callback) {
        callbacks->aboutCalculateComponentsToUninstallCallback = callback;
        callbacks->aboutCalculateComponentsToUninstallConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::aboutCalculateComponentsToUninstall, core,
            [callbacks] {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->aboutCalculateComponentsToUninstallCallback();
            });
    };
    setFinishedCalculateComponentsToUninstallCallback = [core, callbacks](std::function<void()> callback) {
        callbacks->finishedCalculateComponentsToUninstallCallback = callback;
        callbacks->finishedCalculateComponentsToUninstallConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::finishedCalculateComponentsToUninstall, core,
            [callbacks]() {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->finishedCalculateComponentsToUninstallCallback();
            });
    };
    setComponentAddedCallback = [core, callbacks](std::function<void(QInstaller::Component* comp)> callback) {
        callbacks->componentAddedCallback = callback;
        callbacks->componentAddedConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::componentAdded, core,
            [callbacks](QInstaller::Component* comp) {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->componentAddedCallback(comp);
            });
    };
    setValueChangedCallback = [core, callbacks](
        std::function<void(const std::string& key, const std::string& value)> callback) {
            callbacks->valueChangedCallback = callback;
            callbacks->valueChangedConnection = QObject::connect(
                core, &QInstaller::PackageManagerCore::valueChanged, core,
                [callbacks](const QString& key, const QString& value) {
                    if (callbacks->alive.load(std::memory_order_acquire))
                        callbacks->valueChangedCallback(key.toStdString(), value.toStdString());
                });
        };
    setStatusChangedCallback = [core, callbacks](std::function<void(Status)> callback) {
        callbacks->statusChangedCallback = callback;
        callbacks->statusChangedConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::statusChanged, core,
            [callbacks](QInstaller::PackageManagerCore::Status status) {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->statusChangedCallback((Status)status);
            });
    };
    setCurrentPageChangedCallback = [core, callbacks](std::function<void(int page)> callback) {
        callbacks->currentPageChangedCallback = callback;
        callbacks->currentPageChangedConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::currentPageChanged, core,
            [callbacks](int page) {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->currentPageChangedCallback(page);
            });
    };
    setFinishButtonClickedCallback = [core, callbacks](std::function<void()> callback) {
        callbacks->finishButtonClickedCallback = callback;
        callbacks->finishButtonClickedConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::finishButtonClicked, core,
            [callbacks]() {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->finishButtonClickedCallback();
            });
    };

    setMetaJobProgressCallback = [core, callbacks](std::function<void(int progress)> callback) {
        callbacks->metaJobProgressCallback = callback;
        callbacks->metaJobProgressConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::metaJobProgress, core,
            [callbacks](int progress) {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->metaJobProgressCallback(progress);
            });
    };
    setMetaJobTotalProgressCallback = [core, callbacks](std::function<void(int progress)> callback) {
        callbacks->metaJobTotalProgressCallback = callback;
        callbacks->metaJobTotalProgressConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::metaJobTotalProgress, core,
            [callbacks](int progress) {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->metaJobTotalProgressCallback(progress);
            });
    };
    setMetaJobInfoMessageCallback = [core, callbacks](std::function<void(const std::string& message)> callback) {
        callbacks->metaJobInfoMessageCallback = callback;
        callbacks->metaJobInfoMessageConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::metaJobInfoMessage, core,
            [callbacks](const QString& message) {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->metaJobInfoMessageCallback(message.toStdString());
            });
    };

    setStartAllComponentsResetCallback = [core, callbacks](std::function<void()> callback) {
        callbacks->startAllComponentsResetCallback = callback;
        callbacks->startAllComponentsResetConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::startAllComponentsReset, core,
            [callbacks]() {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->startAllComponentsResetCallback();
            });
    };

    // TODO: rewrite using `callbacks`
    setFinishAllComponentsResetCallback = [core](
        std::function<void(const std::vector<QInstaller::Component*>& rootComponents)> callback) {
            QObject::connect(core, &QInstaller::PackageManagerCore::finishAllComponentsReset, core,
                             [callback](const QList<QInstaller::Component*>& rootComponents) {
                                 std::vector<QInstaller::Component*> componentsVec;
                                 for (const auto& comp : rootComponents)
                                     componentsVec.push_back(comp);
                                 callback(componentsVec);
                             });
        };

    setStartUpdaterComponentsResetCallback = [core, callbacks](std::function<void()> callback) {
        callbacks->startUpdaterComponentsResetCallback = callback;
        callbacks->startUpdaterComponentsResetConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::startUpdaterComponentsReset, core,
            [callbacks]() {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->startUpdaterComponentsResetCallback();
            });
    };
    // TODO: rewrite using `callbacks`
    setFinishUpdaterComponentsResetCallback = [core](
        std::function<void(const std::vector<QInstaller::Component*>& componentsWithUpdates)> callback) {
            QObject::connect(core, &QInstaller::PackageManagerCore::finishUpdaterComponentsReset, core,
                             [callback](const QList<QInstaller::Component*>& componentsWithUpdates) {
                                 std::vector<QInstaller::Component*> componentsVec;
                                 for (const auto& comp : componentsWithUpdates)
                                     componentsVec.push_back(comp);
                                 callback(componentsVec);
                             });
        };

    setInstallationStartedCallback = [core, callbacks](std::function<void()> callback) {
        callbacks->installationStartedCallback = callback;
        callbacks->installationStartedConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::installationStarted, core,
            [callbacks] {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->installationStartedCallback();
            });
    };
    setInstallationInterruptedCallback = [core, callbacks](std::function<void()> callback) {
        callbacks->installationInterruptedCallback = callback;
        callbacks->installationInterruptedConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::installationInterrupted, core,
            [callbacks]() {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->installationInterruptedCallback();
            });
    };
    setInstallationFinishedCallback = [core, callbacks](std::function<void()> callback) {
        callbacks->installationFinishedCallback = callback;
        callbacks->installationFinishedConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::installationFinished, core,
            [callbacks]() {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->installationFinishedCallback();
            });
    };
    setUpdateFinishedCallback = [core, callbacks](std::function<void()> callback) {
        callbacks->updateFinishedCallback = callback;
        callbacks->updateFinishedConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::updateFinished, core,
            [callbacks]() {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->updateFinishedCallback();
            });
    };
    setUninstallationStartedCallback = [core, callbacks](std::function<void()> callback) {
        callbacks->uninstallationStartedCallback = callback;
        callbacks->uninstallationStartedConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::uninstallationStarted, core,
            [callbacks]() {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->uninstallationStartedCallback();
            });
    };
    setUninstallationFinishedCallback = [core, callbacks](std::function<void()> callback) {
        callbacks->uninstallationFinishedCallback = callback;
        callbacks->uninstallationFinishedConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::uninstallationFinished, core,
            [callbacks]() {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->uninstallationFinishedCallback();
            });
    };
    setOfflineGenerationStartedCallback = [core, callbacks](std::function<void()> callback) {
        callbacks->offlineGenerationStartedCallback = callback;
        callbacks->offlineGenerationStartedConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::offlineGenerationStarted, core,
            [callbacks]() {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->offlineGenerationStartedCallback();
            });
    };
    setOfflineGenerationFinishedCallback = [core, callbacks](std::function<void()> callback) {
        callbacks->offlineGenerationFinishedCallback = callback;
        callbacks->offlineGenerationFinishedConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::offlineGenerationFinished, core,
            [callbacks]() {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->offlineGenerationFinishedCallback();
            });
    };
    setTitleMessageChangedCallback = [core, callbacks](std::function<void(const std::string& title)> callback) {
        callbacks->titleMessageChangedCallback = callback;
        callbacks->titleMessageChangedConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::titleMessageChanged, core,
            [callbacks](const QString& title) {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->titleMessageChangedCallback(title.toStdString());
            });
    };
    setDownloadArchivesFinishedCallback = [core, callbacks](std::function<void()> callback) {
        callbacks->downloadArchivesFinishedCallback = callback;
        callbacks->downloadArchivesFinishedConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::downloadArchivesFinished, core,
            [callbacks]() {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->downloadArchivesFinishedCallback();
            });
    };

    // TODO: rewrite using `callbacks`
    setWizardPageInsertionRequestedCallback = [core](
        std::function<void(void* /* QWidget */ widget, WizardPage page)> callback) {
            QObject::connect(core, &QInstaller::PackageManagerCore::wizardPageInsertionRequested, core,
                             [callback](void* /* QWidget */ widget, QInstaller::PackageManagerCore::WizardPage page) {
                                 callback(widget, (WizardPage)page);
                             });
        };
    // TODO: rewrite using `callbacks`
    setWizardPageRemovalRequestedCallback = [core, callbacks
        ](std::function<void(void* /* QWidget */ widget)> callback) {
            callbacks->wizardPageRemovalRequestedCallback = callback;
            callbacks->wizardPageRemovalRequestedConnection = QObject::connect(
                core, &QInstaller::PackageManagerCore::wizardPageRemovalRequested, core,
                [callbacks](void* /* QWidget */ widget) {
                    if (callbacks->alive.load(std::memory_order_acquire))
                        callbacks->wizardPageRemovalRequestedCallback(widget);
                });
        };
    // TODO: rewrite using `callbacks`
    setWizardWidgetInsertionRequestedCallback = [core](
        std::function<void(void* /* QWidget */ widget, WizardPage page, int position)> callback) {
            QObject::connect(core, &QInstaller::PackageManagerCore::wizardWidgetInsertionRequested, core,
                             [callback](void* /* QWidget */ widget, QInstaller::PackageManagerCore::WizardPage page,
                                        int position) {
                                 callback(widget, (WizardPage)page, position);
                             });
        };
    // TODO: rewrite using `callbacks`
    setWizardWidgetRemovalRequestedCallback = [core, callbacks
        ](std::function<void(void* /* QWidget */ widget)> callback) {
            callbacks->wizardWidgetRemovalRequestedCallback = callback;
            callbacks->wizardWidgetRemovalRequestedConnection = QObject::connect(
                core, &QInstaller::PackageManagerCore::wizardWidgetRemovalRequested, core,
                [callbacks](void* /* QWidget */ widget) {
                    if (callbacks->alive.load(std::memory_order_acquire))
                        callbacks->wizardWidgetRemovalRequestedCallback(widget);
                });
        };
    // TODO: rewrite using `callbacks`
    setWizardPageWarningInsertionRequestedCallback = [core](
        std::function<void(const std::string& message, WizardPage page, const std::string& id,
                           int position)> callback) {
            QObject::connect(core, &QInstaller::PackageManagerCore::wizardPageWarningInsertionRequested, core,
                             [callback](const QString& message, QInstaller::PackageManagerCore::WizardPage page,
                                        const QString& id,
                                        int position) {
                                 callback(message.toStdString(), (WizardPage)page, id.toStdString(), position);
                             });
        };
    // TODO: rewrite using `callbacks`
    setWizardPageWarningRemovalRequestedCallback = [core, callbacks
        ](std::function<void(const std::string& id)> callback) {
            callbacks->wizardPageWarningRemovalRequestedCallback = callback;
            callbacks->wizardPageWarningRemovalRequestedConnection = QObject::connect(
                core, &QInstaller::PackageManagerCore::wizardPageWarningRemovalRequested, core,
                [callbacks](const QString& id) {
                    if (callbacks->alive.load(std::memory_order_acquire))
                        callbacks->wizardPageWarningRemovalRequestedCallback(id.toStdString());
                });
        };
    // TODO: rewrite using `callbacks`
    setWizardPageVisibilityChangeRequestedCallback = [core, callbacks
        ](std::function<void(bool visible, int page)> callback) {
            callbacks->wizardPageVisibilityChangeRequestedCallback = callback;
            callbacks->wizardPageVisibilityChangeRequestedConnection = QObject::connect(
                core, &QInstaller::PackageManagerCore::wizardPageVisibilityChangeRequested, core,
                [callbacks](bool visible, int page) {
                    if (callbacks->alive.load(std::memory_order_acquire))
                        callbacks->wizardPageVisibilityChangeRequestedCallback(visible, page);
                });
        };
    // TODO: rewrite using `callbacks`
    setSetValidatorForCustomPageRequestedCallback = [core](
        std::function<void(QInstaller::Component* component, const std::string& name,
                           const std::string& callbackName)> callback) {
            QObject::connect(core, &QInstaller::PackageManagerCore::setValidatorForCustomPageRequested, core,
                             [callback](QInstaller::Component* component, const QString& name,
                                        const QString& callbackName) {
                                 callback(component, name.toStdString(), callbackName.toStdString());
                             });
        };

    setSetAutomatedPageSwitchEnabledCallback = [core, callbacks](std::function<void(bool request)> callback) {
        callbacks->setAutomatedPageSwitchEnabledCallback = callback;
        callbacks->setAutomatedPageSwitchEnabledConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::setAutomatedPageSwitchEnabled, core,
            [callbacks](bool request) {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->setAutomatedPageSwitchEnabledCallback(request);
            });
    };
    setCoreNetworkSettingsChangedCallback = [core, callbacks](std::function<void()> callback) {
        callbacks->coreNetworkSettingsChangedCallback = callback;
        callbacks->coreNetworkSettingsChangedConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::coreNetworkSettingsChanged, core,
            [callbacks]() {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->coreNetworkSettingsChangedCallback();
            });
    };

    setGuiObjectChangedCallback = [core, callbacks](std::function<void(void* /* QObject */ gui)> callback) {
        callbacks->guiObjectChangedCallback = callback;
        callbacks->guiObjectChangedConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::guiObjectChanged, core,
            [callbacks](void* /* QObject */ gui) {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->guiObjectChangedCallback(gui);
            });
    };
    // TODO: rewrite using `callbacks`
    setUnstableComponentFoundCallback = [core](
        std::function<void(const std::string& type, const std::string& errorMessage, const std::string& component)>
        callback) {
            QObject::connect(core, &QInstaller::PackageManagerCore::unstableComponentFound, core,
                             [callback](const QString& type, const QString& errorMessage,
                                        const QString& component) {
                                 callback(type.toStdString(), errorMessage.toStdString(), component.toStdString());
                             });
        };
    setInstallerBinaryMarkerChangedCallback = [core, callbacks](std::function<void(int64_t magicMarker)> callback) {
        callbacks->installerBinaryMarkerChangedCallback = callback;
        callbacks->installerBinaryMarkerChangedConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::installerBinaryMarkerChanged, core,
            [callbacks](int64_t magicMarker) {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->installerBinaryMarkerChangedCallback(magicMarker);
            });
    };
    setComponentsRecalculatedCallback = [core, callbacks](std::function<void()> callback) {
        callbacks->componentsRecalculatedCallback = callback;
        callbacks->componentsRecalculatedConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::componentsRecalculated, core,
            [callbacks]() {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->componentsRecalculatedCallback();
            });
    };
    setGuiElementsReadyCallback = [core, callbacks](std::function<void()> callback) {
        callbacks->guiElementsReadyCallback = callback;
        callbacks->guiElementsReadyConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::guiElementsReady, core,
            [callbacks]() {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->guiElementsReadyCallback();
            });
    };
    setInstallDirectoryChangedCallback = [core, callbacks](
        std::function<void(const std::string& newDirectory)> callback) {
            callbacks->installDirectoryChangedCallback = callback;
            callbacks->installDirectoryChangedConnection = QObject::connect(
                core, &QInstaller::PackageManagerCore::installDirectoryChanged, core,
                [callbacks](const QString& newDirectory) {
                    if (callbacks->alive.load(std::memory_order_acquire))
                        callbacks->installDirectoryChangedCallback(newDirectory.toStdString());
                });
        };
    setAvailableSpaceChangedCallback = [core, callbacks](std::function<void(SpaceInfo spaceInfo)> callback) {
        callbacks->availableSpaceChangedCallback = callback;
        callbacks->availableSpaceChangedConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::availableSpaceChanged, core,
            [callbacks](QInstaller::PackageManagerCore::SpaceInfo spaceInfo) {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->availableSpaceChangedCallback((SpaceInfo)spaceInfo);
            });
    };
    setMetadataDownloadFailedCallback = [core, callbacks](std::function<void()> callback) {
        callbacks->metadataDownloadFailedCallback = callback;
        callbacks->metadataDownloadFailedConnection = QObject::connect(
            core, &QInstaller::PackageManagerCore::metadataDownloadFailed, core,
            [callbacks]() {
                if (callbacks->alive.load(std::memory_order_acquire))
                    callbacks->metadataDownloadFailedCallback();
            });
    };
}

ComponentProxy::ComponentProxy(QInstaller::Component* component) {
    setValue = [component](const std::string& key, const std::string& value) {
        return component->setValue(QString::fromStdString(key), QString::fromStdString(value));
    };
    value = [component](const std::string& key, const std::string& defaultValue) {
        return component->value(QString::fromStdString(key), QString::fromStdString(defaultValue)).toStdString();
    };

    registerPathForUninstallation = [component](const std::string& path, bool wipe) {
        return component->registerPathForUninstallation(QString::fromStdString(path), wipe);
    };

    addDownloadableArchive = [component](const std::string& path) {
        return component->addDownloadableArchive(QString::fromStdString(path));
    };
    removeDownloadableArchive = [component](const std::string& path) {
        return component->removeDownloadableArchive(QString::fromStdString(path));
    };

    addStopProcessForUpdateRequest = [component](const std::string& process) {
        return component->addStopProcessForUpdateRequest(QString::fromStdString(process));
    };
    removeStopProcessForUpdateRequest = [component](const std::string& process) {
        return component->removeStopProcessForUpdateRequest(QString::fromStdString(process));
    };
    setStopProcessForUpdateRequest = [component](const std::string& process, bool requested) {
        return component->setStopProcessForUpdateRequest(QString::fromStdString(process), requested);
    };

    addDependency = [component](const std::string& newDependency) {
        return component->addDependency(QString::fromStdString(newDependency));
    };
    addAutoDependOn = [component](const std::string& newDependOn) {
        return component->addAutoDependOn(QString::fromStdString(newDependOn));
    };

    isDefault = [component]() {
        return component->isDefault();
    };
    isAutoDependOn = [component](const std::set<std::string>& componentsToInstall) {
        QSet<QString> components;
        for (const auto& comp : componentsToInstall)
            components.insert(QString::fromStdString(comp));
        return component->isAutoDependOn(components);
    };

    setInstalled = [component]() {
        return component->setInstalled();
    };
    isInstalled = [component](const std::string& version) {
        return component->isInstalled(QString::fromStdString(version));
    };
    installationRequested = [component]() {
        return component->installationRequested();
    };

    setUninstalled = [component]() {
        return component->setUninstalled();
    };
    isUninstalled = [component]() {
        return component->isUninstalled();
    };
    uninstallationRequested = [component]() {
        return component->uninstallationRequested();
    };

    isFromOnlineRepository = [component]() {
        return component->isFromOnlineRepository();
    };

    setUpdateAvailable = [component](bool isUpdateAvailable) {
        return component->setUpdateAvailable(isUpdateAvailable);
    };
    isUpdateAvailable = [component]() {
        return component->isUpdateAvailable();
    };
    updateRequested = [component]() {
        return component->updateRequested();
    };

    componentChangeRequested = [component]() {
        return component->componentChangeRequested();
    };
    isForcedUpdate = [component]() {
        return component->isForcedUpdate();
    };

    addOperation = [component](const std::string& operation, const std::vector<std::string>& parameters) {
        QStringList params;
        for (const auto& param : parameters)
            params.append(QString::fromStdString(param));
        return component->addOperation(QString::fromStdString(operation), params);
    };

    setAutoCreateOperations = [component](bool autoCreateOperations) {
        return component->setAutoCreateOperations(autoCreateOperations);
    };

    setLoadedCallback = [component](std::function<void()> callback) {
        QObject::connect(component, &QInstaller::Component::loaded, component, [callback]() {
            callback();
        });
    };
    setVirtualStateChangedCallback = [component](std::function<void()> callback) {
        QObject::connect(component, &QInstaller::Component::virtualStateChanged, component, [callback]() {
            callback();
        });
    };
    setValueChangedCallback = [component](
        std::function<void(const std::string& key, const std::string& value)> callback) {
            QObject::connect(component, &QInstaller::Component::valueChanged, component,
                             [callback](const QString& key, const QString& value) {
                                 callback(key.toStdString(), value.toStdString());
                             });
        };
}

void InstallerProxyCallbacks::disconnect() {
    alive.store(false, std::memory_order_release);

    QObject::disconnect(aboutCalculateComponentsToInstallConnection);
    QObject::disconnect(finishedCalculateComponentsToInstallConnection);
    QObject::disconnect(aboutCalculateComponentsToUninstallConnection);
    QObject::disconnect(finishedCalculateComponentsToUninstallConnection);
    QObject::disconnect(componentAddedConnection);
    QObject::disconnect(valueChangedConnection);
    QObject::disconnect(statusChangedConnection);
    QObject::disconnect(currentPageChangedConnection);
    QObject::disconnect(finishButtonClickedConnection);
    QObject::disconnect(metaJobProgressConnection);
    QObject::disconnect(metaJobTotalProgressConnection);
    QObject::disconnect(metaJobInfoMessageConnection);
    QObject::disconnect(startAllComponentsResetConnection);
    QObject::disconnect(finishAllComponentsResetConnection);
    QObject::disconnect(startUpdaterComponentsResetConnection);
    QObject::disconnect(finishUpdaterComponentsResetConnection);
    QObject::disconnect(installationStartedConnection);
    QObject::disconnect(installationInterruptedConnection);
    QObject::disconnect(installationFinishedConnection);
    QObject::disconnect(updateFinishedConnection);
    QObject::disconnect(uninstallationStartedConnection);
    QObject::disconnect(uninstallationFinishedConnection);
    QObject::disconnect(offlineGenerationStartedConnection);
    QObject::disconnect(offlineGenerationFinishedConnection);
    QObject::disconnect(titleMessageChangedConnection);
    QObject::disconnect(downloadArchivesFinishedConnection);
    QObject::disconnect(wizardPageInsertionRequestedConnection);
    QObject::disconnect(wizardPageRemovalRequestedConnection);
    QObject::disconnect(wizardWidgetInsertionRequestedConnection);
    QObject::disconnect(wizardWidgetRemovalRequestedConnection);
    QObject::disconnect(wizardPageWarningInsertionRequestedConnection);
    QObject::disconnect(wizardPageWarningRemovalRequestedConnection);
    QObject::disconnect(wizardPageVisibilityChangeRequestedConnection);
    QObject::disconnect(setValidatorForCustomPageRequestedConnection);
    QObject::disconnect(setAutomatedPageSwitchEnabledConnection);
    QObject::disconnect(coreNetworkSettingsChangedConnection);
    QObject::disconnect(guiObjectChangedConnection);
    QObject::disconnect(unstableComponentFoundConnection);
    QObject::disconnect(installerBinaryMarkerChangedConnection);
    QObject::disconnect(componentsRecalculatedConnection);
    QObject::disconnect(guiElementsReadyConnection);
    QObject::disconnect(installDirectoryChangedConnection);
    QObject::disconnect(availableSpaceChangedConnection);
    QObject::disconnect(metadataDownloadFailedConnection);

    aboutCalculateComponentsToInstallCallback = {};
    finishedCalculateComponentsToInstallCallback = {};
    aboutCalculateComponentsToUninstallCallback = {};
    finishedCalculateComponentsToUninstallCallback = {};
    componentAddedCallback = {};
    valueChangedCallback = {};
    statusChangedCallback = {};
    currentPageChangedCallback = {};
    finishButtonClickedCallback = {};
    metaJobProgressCallback = {};
    metaJobTotalProgressCallback = {};
    metaJobInfoMessageCallback = {};
    startAllComponentsResetCallback = {};
    finishAllComponentsResetCallback = {};
    startUpdaterComponentsResetCallback = {};
    finishUpdaterComponentsResetCallback = {};
    installationStartedCallback = {};
    installationInterruptedCallback = {};
    installationFinishedCallback = {};
    updateFinishedCallback = {};
    uninstallationStartedCallback = {};
    uninstallationFinishedCallback = {};
    offlineGenerationStartedCallback = {};
    offlineGenerationFinishedCallback = {};
    titleMessageChangedCallback = {};
    downloadArchivesFinishedCallback = {};
    wizardPageInsertionRequestedCallback = {};
    wizardPageRemovalRequestedCallback = {};
    wizardWidgetInsertionRequestedCallback = {};
    wizardWidgetRemovalRequestedCallback = {};
    wizardPageWarningInsertionRequestedCallback = {};
    wizardPageWarningRemovalRequestedCallback = {};
    wizardPageVisibilityChangeRequestedCallback = {};
    setValidatorForCustomPageRequestedCallback = {};
    setAutomatedPageSwitchEnabledCallback = {};
    coreNetworkSettingsChangedCallback = {};
    guiObjectChangedCallback = {};
    unstableComponentFoundCallback = {};
    installerBinaryMarkerChangedCallback = {};
    componentsRecalculatedCallback = {};
    guiElementsReadyCallback = {};
    installDirectoryChangedCallback = {};
    availableSpaceChangedCallback = {};
    metadataDownloadFailedCallback = {};
}
