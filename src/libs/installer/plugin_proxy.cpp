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

InstallerProxy::InstallerProxy(QInstaller::PackageManagerCore* core) {
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

    setAboutCalculateComponentsToInstallCallback = [core](std::function<void()> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::aboutCalculateComponentsToInstall, [core, callback]() {
            callback();
        });
    };
    setFinishedCalculateComponentsToInstallCallback = [core](std::function<void()> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::finishedCalculateComponentsToInstall,
                         [core, callback]() {
                             callback();
                         });
    };
    setAboutCalculateComponentsToUninstallCallback = [core](std::function<void()> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::aboutCalculateComponentsToUninstall, [core, callback]() {
            callback();
        });
    };
    setFinishedCalculateComponentsToUninstallCallback = [core](std::function<void()> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::finishedCalculateComponentsToUninstall,
                         [core, callback]() {
                             callback();
                         });
    };
    setComponentAddedCallback = [core](std::function<void(QInstaller::Component* comp)> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::componentAdded,
                         [core, callback](QInstaller::Component* comp) {
                             callback(comp);
                         });
    };
    setValueChangedCallback = [core](std::function<void(const std::string& key, const std::string& value)> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::valueChanged,
                         [core, callback](const QString& key, const QString& value) {
                             callback(key.toStdString(), value.toStdString());
                         });
    };
    setStatusChangedCallback = [core](std::function<void(Status)> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::statusChanged, [core, callback](QInstaller::PackageManagerCore::Status status) {
            callback((Status)status);
        });
    };
    setCurrentPageChangedCallback = [core](std::function<void(int page)> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::currentPageChanged, [core, callback](int page) {
            callback(page);
        });
    };
    setFinishButtonClickedCallback = [core](std::function<void()> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::finishButtonClicked, [core, callback]() {
            callback();
        });
    };

    setMetaJobProgressCallback = [core](std::function<void(int progress)> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::metaJobProgress, [core, callback](int progress) {
            callback(progress);
        });
    };
    setMetaJobTotalProgressCallback = [core](std::function<void(int progress)> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::metaJobTotalProgress, [core, callback](int progress) {
            callback(progress);
        });
    };
    setMetaJobInfoMessageCallback = [core](std::function<void(const std::string& message)> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::metaJobInfoMessage,
                         [core, callback](const QString& message) {
                             callback(message.toStdString());
                         });
    };

    setStartAllComponentsResetCallback = [core](std::function<void()> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::startAllComponentsReset, [core, callback]() {
            callback();
        });
    };
    setFinishAllComponentsResetCallback = [core](
        std::function<void(const std::vector<QInstaller::Component*>& rootComponents)> callback) {
            QObject::connect(core, &QInstaller::PackageManagerCore::finishAllComponentsReset,
                             [core, callback](const QList<QInstaller::Component*>& rootComponents) {
                                 std::vector<QInstaller::Component*> componentsVec;
                                 for(const auto& comp : rootComponents)
                                     componentsVec.push_back(comp);
                                 callback(componentsVec);
                             });
        };

    setStartUpdaterComponentsResetCallback = [core](std::function<void()> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::startUpdaterComponentsReset, [core, callback]() {
            callback();
        });
    };
    setFinishUpdaterComponentsResetCallback = [core](
        std::function<void(const std::vector<QInstaller::Component*>& componentsWithUpdates)> callback) {
            QObject::connect(core, &QInstaller::PackageManagerCore::finishUpdaterComponentsReset,
                             [core, callback](const QList<QInstaller::Component*>& componentsWithUpdates) {
                                 std::vector<QInstaller::Component*> componentsVec;
                                 for(const auto& comp : componentsWithUpdates)
                                     componentsVec.push_back(comp);
                                 callback(componentsVec);
                             });
        };

    setInstallationStartedCallback = [core](std::function<void()> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::installationStarted, [core, callback]() {
            callback();
        });
    };
    setInstallationInterruptedCallback = [core](std::function<void()> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::installationInterrupted, [core, callback]() {
            callback();
        });
    };
    setInstallationFinishedCallback = [core](std::function<void()> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::installationFinished, [core, callback]() {
            callback();
        });
    };
    setUpdateFinishedCallback = [core](std::function<void()> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::updateFinished, [core, callback]() {
            callback();
        });
    };
    setUninstallationStartedCallback = [core](std::function<void()> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::uninstallationStarted, [core, callback]() {
            callback();
        });
    };
    setUninstallationFinishedCallback = [core](std::function<void()> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::uninstallationFinished, [core, callback]() {
            callback();
        });
    };
    setOfflineGenerationStartedCallback = [core](std::function<void()> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::offlineGenerationStarted, [core, callback]() {
            callback();
        });
    };
    setOfflineGenerationFinishedCallback = [core](std::function<void()> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::offlineGenerationFinished, [core, callback]() {
            callback();
        });
    };
    setTitleMessageChangedCallback = [core](std::function<void(const std::string& title)> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::titleMessageChanged,
                         [core, callback](const QString& title) {
                             callback(title.toStdString());
                         });
    };
    setDownloadArchivesFinishedCallback = [core](std::function<void()> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::downloadArchivesFinished, [core, callback]() {
            callback();
        });
    };

    setWizardPageInsertionRequestedCallback = [core](
        std::function<void(void* /* QWidget */ widget, WizardPage page)> callback) {
            QObject::connect(core, &QInstaller::PackageManagerCore::wizardPageInsertionRequested,
                             [core, callback](void* /* QWidget */ widget, QInstaller::PackageManagerCore::WizardPage page) {
                                 callback(widget, (WizardPage)page);
                             });
        };
    setWizardPageRemovalRequestedCallback = [core](std::function<void(void* /* QWidget */ widget)> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::wizardPageRemovalRequested,
                         [core, callback](void* /* QWidget */ widget) {
                             callback(widget);
                         });
    };
    setWizardWidgetInsertionRequestedCallback = [core](
        std::function<void(void* /* QWidget */ widget, WizardPage page, int position)> callback) {
            QObject::connect(core, &QInstaller::PackageManagerCore::wizardWidgetInsertionRequested,
                             [core, callback](void* /* QWidget */ widget, QInstaller::PackageManagerCore::WizardPage page, int position) {
                                 callback(widget, (WizardPage)page, position);
                             });
        };
    setWizardWidgetRemovalRequestedCallback = [core](std::function<void(void* /* QWidget */ widget)> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::wizardWidgetRemovalRequested,
                         [core, callback](void* /* QWidget */ widget) {
                             callback(widget);
                         });
    };
    setWizardPageWarningInsertionRequestedCallback = [core](
        std::function<void(const std::string& message, WizardPage page, const std::string& id,
                           int position)> callback) {
            QObject::connect(core, &QInstaller::PackageManagerCore::wizardPageWarningInsertionRequested,
                             [core, callback](const QString& message, QInstaller::PackageManagerCore::WizardPage page, const QString& id,
                                              int position) {
                                 callback(message.toStdString(), (WizardPage)page, id.toStdString(), position);
                             });
        };
    setWizardPageWarningRemovalRequestedCallback = [core](std::function<void(const std::string& id)> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::wizardPageWarningRemovalRequested,
                         [core, callback](const QString& id) {
                             callback(id.toStdString());
                         });
    };
    setWizardPageVisibilityChangeRequestedCallback = [core](std::function<void(bool visible, int page)> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::wizardPageVisibilityChangeRequested,
                         [core, callback](bool visible, int page) {
                             callback(visible, page);
                         });
    };
    setSetValidatorForCustomPageRequestedCallback = [core](
        std::function<void(QInstaller::Component* component, const std::string& name,
                           const std::string& callbackName)> callback) {
            QObject::connect(core, &QInstaller::PackageManagerCore::setValidatorForCustomPageRequested,
                             [core, callback](QInstaller::Component* component, const QString& name,
                                              const QString& callbackName) {
                                 callback(component, name.toStdString(), callbackName.toStdString());
                             });
        };

    setSetAutomatedPageSwitchEnabledCallback = [core](std::function<void(bool request)> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::setAutomatedPageSwitchEnabled,
                         [core, callback](bool request) {
                             callback(request);
                         });
    };
    setCoreNetworkSettingsChangedCallback = [core](std::function<void()> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::coreNetworkSettingsChanged, [core, callback]() {
            callback();
        });
    };

    setGuiObjectChangedCallback = [core](std::function<void(void* /* QObject */ gui)> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::guiObjectChanged,
                         [core, callback](void* /* QObject */ gui) {
                             callback(gui);
                         });
    };
    setUnstableComponentFoundCallback = [core](
        std::function<void(const std::string& type, const std::string& errorMessage, const std::string& component)>
        callback) {
            QObject::connect(core, &QInstaller::PackageManagerCore::unstableComponentFound,
                             [core, callback](const QString& type, const QString& errorMessage,
                                              const QString& component) {
                                 callback(type.toStdString(), errorMessage.toStdString(), component.toStdString());
                             });
        };
    setInstallerBinaryMarkerChangedCallback = [core](std::function<void(int64_t magicMarker)> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::installerBinaryMarkerChanged,
                         [core, callback](int64_t magicMarker) {
                             callback(magicMarker);
                         });
    };
    setComponentsRecalculatedCallback = [core](std::function<void()> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::componentsRecalculated, [core, callback]() {
            callback();
        });
    };
    setGuiElementsReadyCallback = [core](std::function<void()> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::guiElementsReady, [core, callback]() {
            callback();
        });
    };
    setInstallDirectoryChangedCallback = [core](std::function<void(const std::string& newDirectory)> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::installDirectoryChanged,
                         [core, callback](const QString& newDirectory) {
                             callback(newDirectory.toStdString());
                         });
    };
    setAvailableSpaceChangedCallback = [core](std::function<void(SpaceInfo spaceInfo)> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::availableSpaceChanged,
                         [core, callback](QInstaller::PackageManagerCore::SpaceInfo spaceInfo) {
                             callback((SpaceInfo)spaceInfo);
                         });
    };
    setMetadataDownloadFailedCallback = [core](std::function<void()> callback) {
        QObject::connect(core, &QInstaller::PackageManagerCore::metadataDownloadFailed, [core, callback]() {
            callback();
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
        QObject::connect(component, &QInstaller::Component::loaded, [component, callback]() {
            callback();
        });
    };
    setVirtualStateChangedCallback = [component](std::function<void()> callback) {
        QObject::connect(component, &QInstaller::Component::virtualStateChanged, [component, callback]() {
            callback();
        });
    };
    setValueChangedCallback = [component](
        std::function<void(const std::string& key, const std::string& value)> callback) {
            QObject::connect(component, &QInstaller::Component::valueChanged,
                             [component, callback](const QString& key, const QString& value) {
                                 callback(key.toStdString(), value.toStdString());
                             });
        };
}