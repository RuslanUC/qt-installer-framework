#include "plugin.h"
#include "packagemanagergui.h"
#include "packagemanagercore.h"
#include "component.h"

GuiProxy::GuiProxy(QInstaller::PackageManagerGui* gui) : QObject(static_cast<QObject*>(gui)) {
    m_gui = gui;

    connect(gui, &QInstaller::PackageManagerGui::interrupted, [this] {
        emit interrupted();
    });
    connect(gui, &QInstaller::PackageManagerGui::languageChanged, [this] {
        emit languageChanged();
    });
    connect(gui, &QInstaller::PackageManagerGui::finishButtonClicked, [this] {
        emit finishButtonClicked();
    });
    connect(gui, &QInstaller::PackageManagerGui::gotRestarted, [this] {
        emit gotRestarted();
    });
    connect(gui, &QInstaller::PackageManagerGui::settingsButtonClicked, [this] {
        emit settingsButtonClicked();
    });
}

QWidget* GuiProxy::pageById(const int id) const {
    return m_gui->pageById(id);
}

QWidget* GuiProxy::pageByObjectName(const QString& name) const {
    return m_gui->pageByObjectName(name);
}

QWidget* GuiProxy::currentPageWidget() const {
    return m_gui->currentPageWidget();
}

QWidget* GuiProxy::pageWidgetByObjectName(const QString& name) const {
    return m_gui->pageWidgetByObjectName(name);
}

QString GuiProxy::defaultButtonText(const int wizardButton) const {
    return m_gui->defaultButtonText(wizardButton);
}

void GuiProxy::clickButton(const int wizardButton, const int delayInMs) const {
    m_gui->clickButton(wizardButton, delayInMs);
}

void GuiProxy::clickButton(const QString& objectName, const int delayInMs) const {
    m_gui->clickButton(objectName, delayInMs);
}

bool GuiProxy::isButtonEnabled(const int wizardButton) const {
    return m_gui->isButtonEnabled(wizardButton);
}

void GuiProxy::setWizardPageButtonText(const int pageId, const int buttonId, const QString& buttonText) const {
    m_gui->setWizardPageButtonText(pageId, buttonId, buttonText);
}

void GuiProxy::showSettingsButton(const bool show) const {
    m_gui->showSettingsButton(show);
}

void GuiProxy::setSettingsButtonEnabled(const bool enable) const {
    m_gui->setSettingsButtonEnabled(enable);
}

void GuiProxy::setSilent(const bool silent) const {
    m_gui->setSilent(silent);
}

void GuiProxy::setTextItems(QObject* object, const QStringList& items) const {
    m_gui->setTextItems(object, items);
}

void GuiProxy::cancelButtonClicked() const {
    m_gui->cancelButtonClicked();
}

void GuiProxy::reject() const {
    m_gui->reject();
}

void GuiProxy::rejectWithoutPrompt() const {
    m_gui->rejectWithoutPrompt();
}

void GuiProxy::showFinishedPage() const {
    m_gui->showFinishedPage();
}

void GuiProxy::setModified(const bool value) const {
    m_gui->setModified(value);
}

InstallerProxy::InstallerProxy(QInstaller::PackageManagerCore* core) : QObject(core) {
    m_core = core;

    connect(core, &QInstaller::PackageManagerCore::aboutCalculateComponentsToInstall, [this] {
        emit aboutCalculateComponentsToInstall();
    });
    connect(core, &QInstaller::PackageManagerCore::finishedCalculateComponentsToInstall, [this] {
        emit finishedCalculateComponentsToInstall();
    });
    connect(core, &QInstaller::PackageManagerCore::aboutCalculateComponentsToUninstall, [this] {
        emit aboutCalculateComponentsToUninstall();
    });
    connect(core, &QInstaller::PackageManagerCore::finishedCalculateComponentsToUninstall, [this] {
        emit finishedCalculateComponentsToUninstall();
    });
    connect(core, &QInstaller::PackageManagerCore::componentAdded, [this](QInstaller::Component *comp) {
        emit componentAdded(comp);
    });
    connect(core, &QInstaller::PackageManagerCore::valueChanged, [this](const QString &key, const QString &value) {
        emit valueChanged(key, value);
    });
    connect(core, &QInstaller::PackageManagerCore::statusChanged, [this](const Status status) {
        emit statusChanged(status);
    });
    connect(core, &QInstaller::PackageManagerCore::defaultTranslationsLoadedForLanguage, [this](const QLocale lang) {
        emit defaultTranslationsLoadedForLanguage(lang);
    });
    connect(core, &QInstaller::PackageManagerCore::currentPageChanged, [this](const int page) {
        emit currentPageChanged(page);
    });
    connect(core, &QInstaller::PackageManagerCore::finishButtonClicked, [this] {
        emit finishButtonClicked();
    });
    connect(core, &QInstaller::PackageManagerCore::metaJobProgress, [this](const int progress) {
        emit metaJobProgress(progress);
    });
    connect(core, &QInstaller::PackageManagerCore::metaJobTotalProgress, [this](const int progress) {
        emit metaJobTotalProgress(progress);
    });
    connect(core, &QInstaller::PackageManagerCore::metaJobInfoMessage, [this](const QString &message) {
        emit metaJobInfoMessage(message);
    });
    connect(core, &QInstaller::PackageManagerCore::startAllComponentsReset, [this] {
        emit startAllComponentsReset();
    });
    connect(core, &QInstaller::PackageManagerCore::finishAllComponentsReset, [this](const QList<QInstaller::Component*> &rootComponents) {
        emit finishAllComponentsReset(rootComponents);
    });
    connect(core, &QInstaller::PackageManagerCore::startUpdaterComponentsReset, [this] {
        emit startUpdaterComponentsReset();
    });
    connect(core, &QInstaller::PackageManagerCore::finishUpdaterComponentsReset, [this](const QList<QInstaller::Component*> &componentsWithUpdates) {
        emit finishUpdaterComponentsReset(componentsWithUpdates);
    });
    connect(core, &QInstaller::PackageManagerCore::installationStarted, [this] {
        emit installationStarted();
    });
    connect(core, &QInstaller::PackageManagerCore::installationInterrupted, [this] {
        emit installationInterrupted();
    });
    connect(core, &QInstaller::PackageManagerCore::installationFinished, [this] {
        emit installationFinished();
    });
    connect(core, &QInstaller::PackageManagerCore::updateFinished, [this] {
        emit updateFinished();
    });
    connect(core, &QInstaller::PackageManagerCore::uninstallationStarted, [this] {
        emit uninstallationStarted();
    });
    connect(core, &QInstaller::PackageManagerCore::uninstallationFinished, [this] {
        emit uninstallationFinished();
    });
    connect(core, &QInstaller::PackageManagerCore::offlineGenerationStarted, [this] {
        emit offlineGenerationStarted();
    });
    connect(core, &QInstaller::PackageManagerCore::offlineGenerationFinished, [this] {
        emit offlineGenerationFinished();
    });
    connect(core, &QInstaller::PackageManagerCore::titleMessageChanged, [this](const QString &title) {
        emit titleMessageChanged(title);
    });
    connect(core, &QInstaller::PackageManagerCore::downloadArchivesFinished, [this] {
        emit downloadArchivesFinished();
    });
    connect(core, &QInstaller::PackageManagerCore::wizardPageInsertionRequested, [this](QWidget *widget, const WizardPage page) {
        emit wizardPageInsertionRequested(widget, page);
    });
    connect(core, &QInstaller::PackageManagerCore::wizardPageRemovalRequested, [this](QWidget *widget) {
        emit wizardPageRemovalRequested(widget);
    });
    connect(core, &QInstaller::PackageManagerCore::wizardWidgetInsertionRequested, [this](QWidget *widget, const WizardPage page, const int position) {
        emit wizardWidgetInsertionRequested(widget, page, position);
    });
    connect(core, &QInstaller::PackageManagerCore::wizardWidgetRemovalRequested, [this](QWidget *widget) {
        emit wizardWidgetRemovalRequested(widget);
    });
    connect(core, &QInstaller::PackageManagerCore::wizardPageWarningInsertionRequested, [this](const QString &message, const WizardPage page, const QString &id, int position) {
        emit wizardPageWarningInsertionRequested(message, page, id, position);
    });
    connect(core, &QInstaller::PackageManagerCore::wizardPageWarningRemovalRequested, [this](const QString &id) {
        emit wizardPageWarningRemovalRequested(id);
    });
    connect(core, &QInstaller::PackageManagerCore::wizardPageVisibilityChangeRequested, [this](const bool visible, const int page) {
        emit wizardPageVisibilityChangeRequested(visible, page);
    });
    connect(core, &QInstaller::PackageManagerCore::setValidatorForCustomPageRequested, [this](QInstaller::Component *component, const QString &name, const QString &callbackName) {
        emit setValidatorForCustomPageRequested(component, name, callbackName);
    });
    connect(core, &QInstaller::PackageManagerCore::setAutomatedPageSwitchEnabled, [this](const bool request) {
        emit setAutomatedPageSwitchEnabled(request);
    });
    connect(core, &QInstaller::PackageManagerCore::coreNetworkSettingsChanged, [this] {
        emit coreNetworkSettingsChanged();
    });
    connect(core, &QInstaller::PackageManagerCore::guiObjectChanged, [this](QObject *gui) {
        emit guiObjectChanged(gui);
    });
    connect(core, &QInstaller::PackageManagerCore::unstableComponentFound, [this](const QString &type, const QString &errorMessage, const QString &component) {
        emit unstableComponentFound(type, errorMessage, component);
    });
    connect(core, &QInstaller::PackageManagerCore::installerBinaryMarkerChanged, [this](const qint64 magicMarker) {
        emit installerBinaryMarkerChanged(magicMarker);
    });
    connect(core, &QInstaller::PackageManagerCore::componentsRecalculated, [this] {
        emit componentsRecalculated();
    });
    connect(core, &QInstaller::PackageManagerCore::guiElementsReady, [this] {
        emit guiElementsReady();
    });
    connect(core, &QInstaller::PackageManagerCore::installDirectoryChanged, [this](const QString &newDirectory) {
        emit installDirectoryChanged(newDirectory);
    });
    connect(core, &QInstaller::PackageManagerCore::availableSpaceChanged, [this](const SpaceInfo spaceInfo) {
        emit availableSpaceChanged(spaceInfo);
    });
    connect(core, &QInstaller::PackageManagerCore::metadataDownloadFailed, [this] {
        emit metadataDownloadFailed();
    });
}

bool InstallerProxy::virtualComponentsVisible() {
    return QInstaller::PackageManagerCore::virtualComponentsVisible();
}

bool InstallerProxy::noForceInstallation() {
    return QInstaller::PackageManagerCore::noForceInstallation();
}

bool InstallerProxy::noDefaultInstallation() {
    return QInstaller::PackageManagerCore::noDefaultInstallation();
}

void InstallerProxy::setDependsOnLocalInstallerBinary() {
    m_core->setDependsOnLocalInstallerBinary();
}

bool InstallerProxy::localInstallerBinaryUsed() {
    return m_core->localInstallerBinaryUsed();
}

QList<QVariant> InstallerProxy::execute(const QString& program, const QStringList& arguments, const QString& stdIn, const QString& stdInCodec, const QString& stdOutCodec) const {
    return m_core->execute(program, arguments, stdIn, stdInCodec, stdOutCodec);
}

bool InstallerProxy::executeDetached(const QString& program, const QStringList& arguments, const QString& workingDirectory) const {
    return m_core->executeDetached(program, arguments, workingDirectory);
}

QString InstallerProxy::environmentVariable(const QString& name) const {
    return m_core->environmentVariable(name);
}

bool InstallerProxy::operationExists(const QString& name) {
    return m_core->operationExists(name);
}

bool InstallerProxy::performOperation(const QString& name, const QStringList& arguments) {
    return m_core->performOperation(name, arguments);
}

bool InstallerProxy::versionMatches(const QString& version, const QString& requirement) {
    return QInstaller::PackageManagerCore::versionMatches(version, requirement);
}

QString InstallerProxy::findLibrary(const QString& name, const QStringList& paths) {
    return QInstaller::PackageManagerCore::findLibrary(name, paths);
}

QString InstallerProxy::findPath(const QString& name, const QStringList& paths) {
    return QInstaller::PackageManagerCore::findPath(name, paths);
}

void InstallerProxy::setInstallerBaseBinary(const QString& path) {
    return m_core->setInstallerBaseBinary(path);
}

bool InstallerProxy::containsValue(const QString& key) const {
    return m_core->containsValue(key);
}

void InstallerProxy::setValue(const QString& key, const QString& value) {
    return m_core->setValue(key, value);
}

QString InstallerProxy::value(const QString& key, const QString& defaultValue, const int& format) const {
    return m_core->value(key, defaultValue, format);
}

QStringList InstallerProxy::values(const QString& key, const QStringList& defaultValue) const {
    return m_core->values(key, defaultValue);
}

QString InstallerProxy::key(const QString& value) const {
    return m_core->key(value);
}

void InstallerProxy::addUserRepositories(const QStringList& repositories) {
    m_core->addUserRepositories(repositories);
}

void InstallerProxy::setTemporaryRepositories(const QStringList& repositories, bool replace, bool compressed) {
    m_core->setTemporaryRepositories(repositories, replace, compressed);
}

void InstallerProxy::setAllowCompressedRepositoryInstall(bool allow) {
    m_core->setAllowCompressedRepositoryInstall(allow);
}

void InstallerProxy::autoAcceptMessageBoxes() {
    m_core->autoAcceptMessageBoxes();
}

void InstallerProxy::autoRejectMessageBoxes() {
    m_core->autoRejectMessageBoxes();
}

void InstallerProxy::setMessageBoxAutomaticAnswer(const QString& identifier, int button) {
    m_core->setMessageBoxAutomaticAnswer(identifier, button);
}

void InstallerProxy::acceptMessageBoxDefaultButton() {
    m_core->acceptMessageBoxDefaultButton();
}

void InstallerProxy::setAutoAcceptLicenses() {
    m_core->setAutoAcceptLicenses();
}

void InstallerProxy::setFileDialogAutomaticAnswer(const QString& identifier, const QString& value) {
    m_core->setFileDialogAutomaticAnswer(identifier, value);
}

void InstallerProxy::removeFileDialogAutomaticAnswer(const QString& identifier) {
    m_core->removeFileDialogAutomaticAnswer(identifier);
}

bool InstallerProxy::containsFileDialogAutomaticAnswer(const QString& identifier) const {
    return m_core->containsFileDialogAutomaticAnswer(identifier);
}

bool InstallerProxy::isFileExtensionRegistered(const QString& extension) const {
    return m_core->isFileExtensionRegistered(extension);
}

bool InstallerProxy::fileExists(const QString& filePath) const {
    return m_core->fileExists(filePath);
}

QString InstallerProxy::readFile(const QString& filePath, const QString& codecName) const {
    return m_core->readFile(filePath, codecName);
}

QString InstallerProxy::readConsoleLine(const QString& title, qint64 maxlen) const {
    return m_core->readConsoleLine(title, maxlen);
}

QString InstallerProxy::toNativeSeparators(const QString& path) {
    return m_core->toNativeSeparators(path);
}

QString InstallerProxy::fromNativeSeparators(const QString& path) {
    return m_core->fromNativeSeparators(path);
}

QInstaller::Component* InstallerProxy::componentByName(const QString& identifier) const {
    return m_core->componentByName(identifier);
}

QList<QInstaller::Component*> InstallerProxy::components(const QString& regexp) const {
    return m_core->components(regexp);
}

bool InstallerProxy::calculateComponentsToInstall() {
    return m_core->calculateComponentsToInstall();
}

bool InstallerProxy::recalculateAllComponents() {
    return m_core->recalculateAllComponents();
}

bool InstallerProxy::calculateComponentsToUninstall() {
    return m_core->calculateComponentsToUninstall();
}

void InstallerProxy::setInstaller() {
    m_core->setInstaller();
}

bool InstallerProxy::isInstaller() const {
    return m_core->isInstaller();
}

bool InstallerProxy::isOfflineOnly() const {
    return m_core->isOfflineOnly();
}

void InstallerProxy::setUninstaller() {
    m_core->setUninstaller();
}

bool InstallerProxy::isUninstaller() const {
    return m_core->isUninstaller();
}

void InstallerProxy::setUpdater() {
    m_core->setUpdater();
}

bool InstallerProxy::isUpdater() const {
    return m_core->isUpdater();
}

void InstallerProxy::setPackageManager() {
    m_core->setPackageManager();
}

bool InstallerProxy::isPackageManager() const {
    return m_core->isPackageManager();
}

bool InstallerProxy::isOfflineGenerator() const {
    return m_core->isOfflineGenerator();
}

bool InstallerProxy::isPackageViewer() const {
    return m_core->isPackageViewer();
}

bool InstallerProxy::isUserSetBinaryMarker() const {
    return m_core->isUserSetBinaryMarker();
}

bool InstallerProxy::isCommandLineInstance() const {
    return m_core->isCommandLineInstance();
}

bool InstallerProxy::isCommandLineDefaultInstall() const {
    return m_core->isCommandLineDefaultInstall();
}

bool InstallerProxy::gainAdminRights() {
    return m_core->gainAdminRights();
}

void InstallerProxy::dropAdminRights() {
    m_core->dropAdminRights();
}

bool InstallerProxy::hasAdminRights() const {
    return m_core->hasAdminRights();
}

qint64 InstallerProxy::requiredDiskSpace() const {
    return m_core->requiredDiskSpace();
}

quint64 InstallerProxy::requiredTemporaryDiskSpace() const {
    return m_core->requiredTemporaryDiskSpace();
}

bool InstallerProxy::isProcessRunning(const QString& name) const {
    return m_core->isProcessRunning(name);
}

bool InstallerProxy::killProcess(const QString& absoluteFilePath, int timeout) const {
    return m_core->killProcess(absoluteFilePath, timeout);
}

bool InstallerProxy::addWizardPageWarning(const QString& message, WizardPage page, const QString& id, int position) {
    return m_core->addWizardPageWarning(message, page, id, position);
}

bool InstallerProxy::removeWizardPageWarning(const QString& id) {
    return m_core->removeWizardPageWarning(id);
}

bool InstallerProxy::setDefaultPageVisible(int page, bool visible) {
    return m_core->setDefaultPageVisible(page, visible);
}

void InstallerProxy::setValidatorForCustomPage(QInstaller::Component* component, const QString& name, const QString& callbackName) {
    m_core->setValidatorForCustomPage(component, name, callbackName);
}

void InstallerProxy::selectComponent(const QString& id) {
    m_core->selectComponent(id);
}

void InstallerProxy::deselectComponent(const QString& id) {
    m_core->deselectComponent(id);
}

bool InstallerProxy::runInstaller() {
    return m_core->runInstaller();
}

bool InstallerProxy::runUninstaller() {
    return m_core->runUninstaller();
}

bool InstallerProxy::runPackageUpdater() {
    return m_core->runPackageUpdater();
}

bool InstallerProxy::runOfflineGenerator() {
    return m_core->runOfflineGenerator();
}

void InstallerProxy::interrupt() {
    m_core->interrupt();
}

void InstallerProxy::setCanceled() {
    m_core->setCanceled();
}

void InstallerProxy::languageChanged() {
    m_core->languageChanged();
}

void InstallerProxy::setCompleteUninstallation(bool complete) {
    m_core->setCompleteUninstallation(complete);
}

void InstallerProxy::cancelMetaInfoJob() {
    m_core->cancelMetaInfoJob();
}

ComponentProxy::ComponentProxy(QInstaller::Component* component) : QObject(component) {
    m_component = component;

    connect(component, &QInstaller::Component::loaded, [this] {
        emit loaded();
    });
    connect(component, &QInstaller::Component::virtualStateChanged, [this] {
        emit virtualStateChanged();
    });
    connect(component, &QInstaller::Component::valueChanged, [this](const QString& key, const QString& value) {
        emit valueChanged(key, value);
    });
}

void ComponentProxy::setValue(const QString& key, const QString& value) {
    m_component->setValue(key, value);
}

QString ComponentProxy::value(const QString& key, const QString& defaultValue) const {
    return m_component->value(key, defaultValue);
}

void ComponentProxy::registerPathForUninstallation(const QString& path, bool wipe) {
    m_component->registerPathForUninstallation(path, wipe);
}

void ComponentProxy::addDownloadableArchive(const QString& path) {
    m_component->addDownloadableArchive(path);
}

void ComponentProxy::removeDownloadableArchive(const QString& path) {
    m_component->removeDownloadableArchive(path);
}

void ComponentProxy::addStopProcessForUpdateRequest(const QString& process) {
    m_component->addStopProcessForUpdateRequest(process);
}

void ComponentProxy::removeStopProcessForUpdateRequest(const QString& process) {
    m_component->removeStopProcessForUpdateRequest(process);
}

void ComponentProxy::setStopProcessForUpdateRequest(const QString& process, bool requested) {
    m_component->setStopProcessForUpdateRequest(process, requested);
}

void ComponentProxy::addDependency(const QString& newDependency) {
    m_component->addDependency(newDependency);
}

void ComponentProxy::addAutoDependOn(const QString& newDependOn) {
    m_component->addAutoDependOn(newDependOn);
}

bool ComponentProxy::isDefault() const {
    return m_component->isDefault();
}

bool ComponentProxy::isAutoDependOn(const QSet<QString>& componentsToInstall) const {
    return m_component->isAutoDependOn(componentsToInstall);
}

void ComponentProxy::setInstalled() {
    m_component->setInstalled();
}

bool ComponentProxy::isInstalled(const QString& version) const {
    return m_component->isInstalled(version);
}

bool ComponentProxy::installationRequested() const {
    return m_component->installationRequested();
}

void ComponentProxy::setUninstalled() {
    m_component->setUninstalled();
}

bool ComponentProxy::isUninstalled() const {
    return m_component->isUninstalled();
}

bool ComponentProxy::uninstallationRequested() const {
    return m_component->uninstallationRequested();
}

bool ComponentProxy::isFromOnlineRepository() const {
    return m_component->isFromOnlineRepository();
}

void ComponentProxy::setUpdateAvailable(bool isUpdateAvailable) {
     m_component->setUpdateAvailable(isUpdateAvailable);
}

bool ComponentProxy::isUpdateAvailable() const {
    return m_component->isUpdateAvailable();
}

bool ComponentProxy::updateRequested() const {
    return m_component->updateRequested();
}

bool ComponentProxy::componentChangeRequested() {
    return m_component->componentChangeRequested();
}

bool ComponentProxy::isForcedUpdate() {
    return m_component->isForcedUpdate();
}

void ComponentProxy::setAutoCreateOperations(bool autoCreateOperations) {
    m_component->setAutoCreateOperations(autoCreateOperations);
}
