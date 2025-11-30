/**************************************************************************
**
** Copyright (C) 2025 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Installer Framework.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
**************************************************************************/

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QtCore/QString>
#include <QtCore/QStringList>

namespace QInstaller {

// constants used throughout several classes
static constexpr QLatin1String scTrue("true");
static constexpr QLatin1String scFalse("false");
static constexpr QLatin1String scScript("script");
static constexpr QLatin1String scAllUsersStartMenuProgramsPath("AllUsersStartMenuProgramsPath");
static constexpr QLatin1String scUserStartMenuProgramsPath("UserStartMenuProgramsPath");
static constexpr QLatin1String scUILanguage("UILanguage");
static constexpr QLatin1String scUpdatesXML("Updates.xml");

static constexpr QLatin1String scName("Name");
static constexpr QLatin1String scVersion("Version");
static constexpr QLatin1String scDefault("Default");
static constexpr QLatin1String scDisplayVersion("DisplayVersion");
static constexpr QLatin1String scRemoteDisplayVersion("RemoteDisplayVersion");
static constexpr QLatin1String scInheritVersion("inheritVersionFrom");
static constexpr QLatin1String scReplaces("Replaces");
static constexpr QLatin1String scDownloadableArchives("DownloadableArchives");
static constexpr QLatin1String scEssential("Essential");
static constexpr QLatin1String scForcedUpdate("ForcedUpdate");
static constexpr QLatin1String scTargetDir("TargetDir");
static constexpr QLatin1String scReleaseDate("ReleaseDate");
static constexpr QLatin1String scDescription("Description");
static constexpr QLatin1String scDisplayName("DisplayName");
static constexpr QLatin1String scTreeName("TreeName");
static constexpr QLatin1String scAutoTreeName("AutoTreeName");
static constexpr QLatin1String scDependencies("Dependencies");
static constexpr QLatin1String scAlias("Alias");
static constexpr QLatin1String scRequiredAliases("RequiredAliases");
static constexpr QLatin1String scRequiredComponents("RequiredComponents");
static constexpr QLatin1String scOptionalAliases("OptionalAliases");
static constexpr QLatin1String scOptionalComponents("OptionalComponents");
static constexpr QLatin1String scLocalDependencies("LocalDependencies");
static constexpr QLatin1String scAutoDependOn("AutoDependOn");
static constexpr QLatin1String scNewComponent("NewComponent");
static constexpr QLatin1String scRepositories("Repositories");
static constexpr QLatin1String scCompressedSize("CompressedSize");
static constexpr QLatin1String scInstalledVersion("InstalledVersion");
static constexpr QLatin1String scUncompressedSize("UncompressedSize");
static constexpr QLatin1String scUncompressedSizeSum("UncompressedSizeSum");
static constexpr QLatin1String scRequiresAdminRights("RequiresAdminRights");
static constexpr QLatin1String scOfflineBinaryName("OfflineBinaryName");
static constexpr QLatin1String scSHA1("SHA1");
static constexpr QLatin1String scMetadataName("MetadataName");
static constexpr QLatin1String scContentSha1("ContentSha1");

static const char * const scClearCacheHint = QT_TR_NOOP(
    "This may be solved by restarting the application after clearing the cache from:");

// symbols
static constexpr QLatin1String scCaretSymbol("^");
static constexpr QLatin1String scCommaWithSpace(", ");
static constexpr QLatin1String scBr("<br>");

// constants used throughout the components class
static constexpr QLatin1String scVirtual("Virtual");
static constexpr QLatin1String scSortingPriority("SortingPriority");
static constexpr QLatin1String scCheckable("Checkable");
static constexpr QLatin1String scScriptTag("Script");
static constexpr QLatin1String scUpdateText("UpdateText");
static constexpr QLatin1String scForcedInstallation("ForcedInstallation");
static constexpr QLatin1String scExpandedByDefault("ExpandedByDefault");
static constexpr QLatin1String scUnstable("Unstable");
static constexpr QLatin1String scTargetDirPlaceholder("@TargetDir@");
static constexpr QLatin1String scTargetDirPlaceholderWithArg("@TargetDir@%1");
static constexpr QLatin1String scLastUpdateDate("LastUpdateDate");
static constexpr QLatin1String scInstallDate("InstallDate");
static constexpr QLatin1String scTranslations("Translations");
static constexpr QLatin1String scLicenses("Licenses");
static constexpr QLatin1String scLicensesValue("licenses");
static constexpr QLatin1String scLicense("License");
static constexpr QLatin1String scOperations("Operations");
static constexpr QLatin1String scInstallScript("installScript");
static constexpr QLatin1String scPostLoadScript("postLoadScript");
static constexpr QLatin1String scComponent("Component");
static constexpr QLatin1String scComponentSmall("component");
static constexpr QLatin1String scRetranslateUi("retranslateUi");
static constexpr QLatin1String scEn("en");
static constexpr QLatin1String scIfw_("ifw_");
static constexpr QLatin1String scFile("file");
static constexpr QLatin1String scContent("content");
static constexpr QLatin1String scExtract("Extract");
static constexpr QLatin1String scSha1("sha1");
static constexpr QLatin1String scCreateOperationsForPath("createOperationsForPath");
static constexpr QLatin1String scCreateOperationsForArchive("createOperationsForArchive");
static constexpr QLatin1String scCreateOperations("createOperations");
static constexpr QLatin1String scBeginInstallation("beginInstallation");
static constexpr QLatin1String scMinimumProgress("MinimumProgress");
static constexpr QLatin1String scDelete("Delete");
static constexpr QLatin1String scCopy("Copy");
static constexpr QLatin1String scMkdir("Mkdir");
static constexpr QLatin1String scIsDefault("isDefault");
static constexpr QLatin1String scAdmin("admin");
static constexpr QLatin1String scTwoArgs("%1/%2/");
static constexpr QLatin1String scThreeArgs("%1/%2/%3");
static constexpr QLatin1String scComponentScriptTest("var component = installer.componentByName('%1'); component.name;");
static constexpr QLatin1String scInstallerPrefix("installer://");
static constexpr QLatin1String scInstallerPrefixWithOneArgs("installer://%1/");
static constexpr QLatin1String scInstallerPrefixWithTwoArgs("installer://%1/%2");
static constexpr QLatin1String scLocalesArgs("%1%2_%3.%4");

// constants used throughout the settings and package manager core class
static constexpr QLatin1String scTitle("Title");
static constexpr QLatin1String scPublisher("Publisher");
static constexpr QLatin1String scRunProgram("RunProgram");
static constexpr QLatin1String scRunProgramArguments("RunProgramArguments");
static constexpr QLatin1String scStartMenuDir("StartMenuDir");
static constexpr QLatin1String scRemoveTargetDir("RemoveTargetDir");
static constexpr QLatin1String scLocalCacheDir("LocalCacheDir");
static constexpr QLatin1String scPersistentLocalCache("PersistentLocalCache");
static constexpr QLatin1String scRunProgramDescription("RunProgramDescription");
static constexpr QLatin1String scTargetConfigurationFile("TargetConfigurationFile");
static constexpr QLatin1String scAllowNonAsciiCharacters("AllowNonAsciiCharacters");
static constexpr QLatin1String scDisableAuthorizationFallback("DisableAuthorizationFallback");
static constexpr QLatin1String scDisableCommandLineInterface("DisableCommandLineInterface");
static constexpr QLatin1String scRemoteRepositories("RemoteRepositories");
static constexpr QLatin1String scRepositoryCategories("RepositoryCategories");
static constexpr QLatin1String scRepositorySettingsPageVisible("RepositorySettingsPageVisible");
static constexpr QLatin1String scAllowSpaceInPath("AllowSpaceInPath");
static constexpr QLatin1String scAllowRepositoriesForOfflineInstaller("AllowRepositoriesForOfflineInstaller");
static constexpr QLatin1String scWizardStyle("WizardStyle");
static constexpr QLatin1String scStyleSheet("StyleSheet");
static constexpr QLatin1String scTitleColor("TitleColor");
static constexpr QLatin1String scWizardDefaultWidth("WizardDefaultWidth");
static constexpr QLatin1String scWizardDefaultHeight("WizardDefaultHeight");
static constexpr QLatin1String scWizardMinimumWidth("WizardMinimumWidth");
static constexpr QLatin1String scWizardMinimumHeight("WizardMinimumHeight");
static constexpr QLatin1String scWizardShowPageList("WizardShowPageList");
static constexpr QLatin1String scProductImages("ProductImages");
static constexpr QLatin1String scProductImage("ProductImage");
static constexpr QLatin1String scImage("Image");
static constexpr QLatin1String scInstallerApplicationIcon("InstallerApplicationIcon");
static constexpr QLatin1String scUrlQueryString("UrlQueryString");
static constexpr QLatin1String scProductUUID("ProductUUID");
static constexpr QLatin1String scAllUsers("AllUsers");
static constexpr QLatin1String scSupportsModify("SupportsModify");
static constexpr QLatin1String scAllowUnstableComponents("AllowUnstableComponents");
static constexpr QLatin1String scSaveDefaultRepositories("SaveDefaultRepositories");
static constexpr QLatin1String scRepositoryCategoryDisplayName("RepositoryCategoryDisplayName");
static constexpr QLatin1String scHighDpi("@2x.");
static constexpr QLatin1String scWatermark("Watermark");
static constexpr QLatin1String scBanner("Banner");
static constexpr QLatin1String scLogo("Logo");
static constexpr QLatin1String scBackground("Background");
static constexpr QLatin1String scPageListPixmap("PageListPixmap");
constexpr char scRelocatable[] = "@RELOCATABLE_PATH@";

constexpr quint64 scEstimatedMaintenancetoolSize = 56 * 1024 * 1024LL; // MT size is approximately 56 MB
constexpr quint64 scRecommendedMaxSize = 50 * 1024 * 1024 * 1024LL;

static constexpr QLatin1String scMetaElements[] = {
    QLatin1String("Script"),
    QLatin1String("Licenses"),
    QLatin1String("UserInterfaces"),
    QLatin1String("Translations")
};
}

namespace CommandLineOptions {

// Help & version information
static constexpr QLatin1String scHelpShort("h");
static constexpr QLatin1String scHelpLong("help");
static constexpr QLatin1String scVersionShort("v");
static constexpr QLatin1String scVersionLong("version");

// Output related options
static constexpr QLatin1String scVerboseShort("d");
static constexpr QLatin1String scVerboseLong("verbose");
static constexpr QLatin1String scLoggingRulesShort("g");
static constexpr QLatin1String scLoggingRulesLong("logging-rules");

// Consumer commands
static constexpr QLatin1String scInstallShort("in");
static constexpr QLatin1String scInstallLong("install");
static constexpr QLatin1String scCheckUpdatesShort("ch");
static constexpr QLatin1String scCheckUpdatesLong("check-updates");
static constexpr QLatin1String scUpdateShort("up");
static constexpr QLatin1String scUpdateLong("update");
static constexpr QLatin1String scRemoveShort("rm");
static constexpr QLatin1String scRemoveLong("remove");
static constexpr QLatin1String scListShort("li");
static constexpr QLatin1String scListLong("list");
static constexpr QLatin1String scSearchShort("se");
static constexpr QLatin1String scSearchLong("search");
static constexpr QLatin1String scCreateOfflineShort("co");
static constexpr QLatin1String scCreateOfflineLong("create-offline");
static constexpr QLatin1String scClearCacheShort("cc");
static constexpr QLatin1String scClearCacheLong("clear-cache");
static constexpr QLatin1String scPurgeShort("pr");
static constexpr QLatin1String scPurgeLong("purge");

// Repository management options
static constexpr QLatin1String scAddRepositoryShort("ar");
static constexpr QLatin1String scAddRepositoryLong("add-repository");
static constexpr QLatin1String scAddTmpRepositoryShort("at");
static constexpr QLatin1String scAddTmpRepositoryLong("add-temp-repository");
static constexpr QLatin1String scSetTmpRepositoryShort("st");
static constexpr QLatin1String scSetTmpRepositoryLong("set-temp-repository");

// Proxy options
static constexpr QLatin1String scSystemProxyShort("sp");
static constexpr QLatin1String scSystemProxyLong("system-proxy");
static constexpr QLatin1String scNoProxyShort("np");
static constexpr QLatin1String scNoProxyLong("no-proxy");

// Starting mode options
static constexpr QLatin1String scStartUpdaterShort("su");
static constexpr QLatin1String scStartUpdaterLong("start-updater");
static constexpr QLatin1String scStartPackageManagerShort("sm");
static constexpr QLatin1String scStartPackageManagerLong("start-package-manager");
static constexpr QLatin1String scStartUninstallerShort("sr");
static constexpr QLatin1String scStartUninstallerLong("start-uninstaller");

// Message acceptance options
static constexpr QLatin1String scAcceptMessageQueryShort("am");
static constexpr QLatin1String scAcceptMessageQueryLong("accept-messages");
static constexpr QLatin1String scRejectMessageQueryShort("rm");
static constexpr QLatin1String scRejectMessageQueryLong("reject-messages");
static constexpr QLatin1String scMessageAutomaticAnswerShort("aa");
static constexpr QLatin1String scMessageAutomaticAnswerLong("auto-answer");
static constexpr QLatin1String scMessageDefaultAnswerShort("da");
static constexpr QLatin1String scMessageDefaultAnswerLong("default-answer");
static constexpr QLatin1String scAcceptLicensesShort("al");
static constexpr QLatin1String scAcceptLicensesLong("accept-licenses");
static constexpr QLatin1String scFileDialogAutomaticAnswer("file-query");
static constexpr QLatin1String scConfirmCommandShort("c");
static constexpr QLatin1String scConfirmCommandLong("confirm-command");

// Misc installation options
static constexpr QLatin1String scRootShort("t");
static constexpr QLatin1String scRootLong("root");
static constexpr QLatin1String scOfflineInstallerNameShort("oi");
static constexpr QLatin1String scOfflineInstallerNameLong("offline-installer-name");
static constexpr QLatin1String scCreateHybridShort("hb");
static constexpr QLatin1String scCreateHybridLong("hybrid");
static constexpr QLatin1String scPlatformShort("p");
static constexpr QLatin1String scPlatformLong("platform");
static constexpr QLatin1String scNoForceInstallationShort("nf");
static constexpr QLatin1String scNoForceInstallationLong("no-force-installations");
static constexpr QLatin1String scNoSizeCheckingShort("ns");
static constexpr QLatin1String scNoSizeCheckingLong("no-size-checking");
static constexpr QLatin1String scShowVirtualComponentsShort("sv");
static constexpr QLatin1String scShowVirtualComponentsLong("show-virtual-components");
static constexpr QLatin1String scInstallCompressedRepositoryShort("i");
static constexpr QLatin1String scInstallCompressedRepositoryLong("install-compressed-repository");
static constexpr QLatin1String scCreateLocalRepositoryShort("cl");
static constexpr QLatin1String scCreateLocalRepositoryLong("create-local-repository");
static constexpr QLatin1String scNoDefaultInstallationShort("nd");
static constexpr QLatin1String scNoDefaultInstallationLong("no-default-installations");
static constexpr QLatin1String scFilterPackagesShort("fp");
static constexpr QLatin1String scFilterPackagesLong("filter-packages");
static constexpr QLatin1String scLocalCachePathShort("cp");
static constexpr QLatin1String scLocalCachePathLong("cache-path");
static constexpr QLatin1String scTypeLong("type");

// Developer options
static constexpr QLatin1String scScriptShort("s");
static constexpr QLatin1String scScriptLong("script");
static constexpr QLatin1String scStartServerShort("ss");
static constexpr QLatin1String scStartServerLong("start-server");
static constexpr QLatin1String scStartClientShort("sc");
static constexpr QLatin1String scStartClientLong("start-client");
static constexpr QLatin1String scMaxConcurrentOperationsShort("mco");
static constexpr QLatin1String scMaxConcurrentOperationsLong("max-concurrent-operations");
static constexpr QLatin1String scCleanupUpdate("cleanup-update");
static constexpr QLatin1String scCleanupUpdateOnly("cleanup-update-only");
static constexpr QLatin1String scLanguage("lang");

// Options supposed to be used without graphical interface
static const QStringList scCommandLineInterfaceOptions = {
    scInstallShort,
    scInstallLong,
    scCheckUpdatesShort,
    scCheckUpdatesLong,
    scUpdateShort,
    scUpdateLong,
    scRemoveShort,
    scRemoveLong,
    scListShort,
    scListLong,
    scSearchShort,
    scSearchLong,
    scCreateOfflineShort,
    scCreateOfflineLong,
    scPurgeShort,
    scPurgeLong,
    scClearCacheShort,
    scClearCacheLong
};

} // namespace CommandLineOptions
#endif  // CONSTANTS_H
