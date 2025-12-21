include(${PROJECT_SOURCE_DIR}/cmake/definitions.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/lto.cmake)

set(PLATFORM_SOURCES)

set(INCLUDE_DIRS .)

if (WIN32 AND MSVC)
    list(APPEND PLATFORM_SOURCES
            adminauthorization_win.cpp
            sysinfo_win.cpp
            ../kdtools/lockfile_win.cpp
            ../kdtools/kdsysinfo_win.cpp)
elseif (APPLE)
    list(APPEND PLATFORM_SOURCES
            fileutils_mac.mm
            adminauthorization_mac.cpp
            ../kdtools/lockfile_unix.cpp
            ../kdtools/sysinfo_mac.cpp)
elseif (UNIX)
    list(APPEND PLATFORM_SOURCES
            adminauthorization_x11.cpp
            ../kdtools/lockfile_unix.cpp
            ../kdtools/sysinfo_x11.cpp)
endif()

find_package(Qt6 REQUIRED COMPONENTS Core Concurrent Widgets Xml Network)

add_library(installer ${IFW_LINK_TYPE}
        serverauthenticationdialog.ui
        componentsummary.ui

        resources/installer.qrc

        packagemanagercore.cpp
        abstractarchive.cpp
        archivefactory.cpp
        aspectratiolabel.cpp
        calculatorbase.cpp
        concurrentoperationrunner.cpp
        directoryguard.cpp
        fileguard.cpp
        componentsortfilterproxymodel.cpp
        componentselectedproxymodel.cpp
        genericdatacache.cpp
        loggingutils.cpp
        metadata.cpp
        metadatacache.cpp
        operationtracer.cpp
        packagemanagercore_p.cpp
        packagemanagergui.cpp
        binaryformat.cpp
        binaryformatengine.cpp
        binaryformatenginehandler.cpp
        repository.cpp
        fileutils.cpp
        stopprocessforupdateoperation.cpp
        utils.cpp
        component.cpp
        componentmodel.cpp
        qtpatch.cpp
        consumeoutputoperation.cpp
        replaceoperation.cpp
        linereplaceoperation.cpp
        copydirectoryoperation.cpp
        simplemovefileoperation.cpp
        extractarchiveoperation.cpp
        globalsettingsoperation.cpp
        createshortcutoperation.cpp
        createdesktopentryoperation.cpp
        registerfiletypeoperation.cpp
        environmentvariablesoperation.cpp
        installiconsoperation.cpp
        selfrestartoperation.cpp
        downloadarchivesjob.cpp
        init.cpp
        elevatedexecuteoperation.cpp
        fakestopprocessforupdateoperation.cpp
        progresscoordinator.cpp
        minimumprogressoperation.cpp
        performinstallationform.cpp
        messageboxhandler.cpp
        licenseoperation.cpp
        component_p.cpp
        qprocesswrapper.cpp
        qsettingswrapper.cpp
        settings.cpp
        permissionsettings.cpp
        createlocalrepositoryoperation.cpp
        link.cpp
        createlinkoperation.cpp
        packagemanagercoredata.cpp
        globals.cpp
        settingsoperation.cpp
        testrepository.cpp
        packagemanagerpagefactory.cpp
        abstractfiletask.cpp
        copyfiletask.cpp
        downloadfiletask.cpp
        observer.cpp
        metadatajob.cpp
        protocol.cpp
        remoteobject.cpp
        remoteclient.cpp
        remoteserver.cpp
        remotefileengine.cpp
        remoteserverconnection.cpp
        fileio.cpp
        binarycontent.cpp
        binarylayout.cpp
        installercalculator.cpp
        uninstallercalculator.cpp
        componentchecker.cpp
        serverauthenticationdialog.cpp
        keepaliveobject.cpp
        systeminfo.cpp
        packagesource.cpp
        repositorycategory.cpp
        componentselectionpage_p.cpp
        commandlineparser.cpp
        checkablecombobox.cpp
        clickablelabel.cpp
        categorycombobox.cpp
        horizontalruler.cpp
        spacewidget.cpp
        readyforinstallationpage_p.cpp
        labelwithpixmap.cpp
        libarchivearchive.cpp
        libarchivewrapper.cpp
        libarchivewrapper_p.cpp
        commandlineparser_p.cpp
        plugin.h
        pluginengine.cpp
        plugin_proxy.cpp

        ${PLATFORM_SOURCES}

        ../ifwtools/resources/ifwtools.qrc
        ../ifwtools/rcc/rcc.cpp
        ../ifwtools/rcc/rccmain.cpp
        ../ifwtools/repositorygen.cpp
        ../ifwtools/binarycreator.cpp

        ../kdtools/authenticationdialog.ui
        ../kdtools/job.cpp
        ../kdtools/selfrestarter.cpp
        ../kdtools/runoncechecker.cpp
        ../kdtools/lockfile.cpp
        ../kdtools/sysinfo.cpp
        ../kdtools/filedownloader.cpp
        ../kdtools/filedownloaderfactory.cpp
        ../kdtools/localpackagehub.cpp
        ../kdtools/update.cpp
        ../kdtools/updateoperation.cpp
        ../kdtools/updateoperationfactory.cpp
        ../kdtools/updateoperations.cpp
        ../kdtools/task.cpp
        ../kdtools/updatefinder.cpp
        ../kdtools/updatesinfo.cpp
        ../kdtools/environment.cpp)
target_compile_definitions(installer PRIVATE BUILD_SHARED_IFWTOOLS BUILD_SHARED_KDTOOLS ${IFW_COMPILE_DEFINITIONS} BUILD_LIB_INSTALLER)
target_include_directories(installer PUBLIC
        .
        ../ifwtools
        ../kdtools
        ${INCLUDE_DIRS}
        ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(installer PUBLIC
        Qt6::Core
        Qt6::CorePrivate
        Qt6::Concurrent
        Qt6::Xml
        Qt6::Widgets
        Qt6::Network
        archive)
target_enable_lto(installer)

add_library(ifw::installer ALIAS installer)

set(IFW_LIBINSTALLER_PUBLIC_HEADERS
        "${CMAKE_CURRENT_SOURCE_DIR}/packagemanagercoredata.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/constants.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/abstractfiletask.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/installer_global.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/fileguard.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/consumeoutputoperation.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/remoteserver.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/binarycontent.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/directoryguard.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/genericdatacache.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/runextensions.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/categorycombobox.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/operationtracer.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/qtpatch.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/qinstallerglobal.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/metadatajob.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/componentchecker.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/systeminfo.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/concurrentoperationrunner.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/permissionsettings.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/graph.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/abstracttask.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/remoteclient.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/installiconsoperation.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/registerfiletypeoperation.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/globalsettingsoperation.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/utils.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/linereplaceoperation.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/observer.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/createdesktopentryoperation.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/range.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/qprocesswrapper.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/init.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/performinstallationform.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/calculatorbase.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/packagemanagerpagefactory.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/environmentvariablesoperation.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/packagemanagergui.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/horizontalruler.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/protocol.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/minimumprogressoperation.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/binaryformatenginehandler.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/fileio.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/clickablelabel.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/fileutils.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/labelwithpixmap.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/elevatedexecuteoperation.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/remoteserverconnection.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/binaryformatengine.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/installercalculator.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/adminauthorization.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt"
        "${CMAKE_CURRENT_SOURCE_DIR}/binarylayout.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/abstractarchive.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/loggingutils.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/installer.pro"
        "${CMAKE_CURRENT_SOURCE_DIR}/pluginengine.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/settingsoperation.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/componentsortfilterproxymodel.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/createlocalrepositoryoperation.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/libarchivearchive.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/checkablecombobox.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/copyfiletask.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/settings.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/createlinkoperation.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/extractarchiveoperation.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/repository.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/componentmodel.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/selfrestartoperation.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/uninstallercalculator.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/simplemovefileoperation.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/binaryformat.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/metadatacache.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/replaceoperation.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/remoteobject.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/packagemanagercore.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/remotefileengine.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/libarchivewrapper.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/spacewidget.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/commandlineparser.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/downloadarchivesjob.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/messageboxhandler.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/errors.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/archivefactory.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/stopprocessforupdateoperation.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/componentselectedproxymodel.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/testrepository.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/globals.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/copydirectoryoperation.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/downloadfiletask.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/progresscoordinator.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/plugin.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/component.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/keepaliveobject.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/createshortcutoperation.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/qsettingswrapper.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/aspectratiolabel.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/licenseoperation.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/link.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/serverauthenticationdialog.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/metadata.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/repositorycategory.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/packagesource.h"
)

set_target_properties(installer PROPERTIES
    FRAMEWORK TRUE
    PUBLIC_HEADER "${IFW_LIBINSTALLER_PUBLIC_HEADERS}"
)
