include(${PROJECT_SOURCE_DIR}/cmake/definitions.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/lto.cmake)

set(PLATFORM_SOURCES)

# TODO:
#win32 {
#
#LIBS += -ladvapi32 -lpsapi      # kdtools
#LIBS += -lole32 -lshell32       # createshortcutoperation
#
#win32-g++*:LIBS += -lmpr -luuid
#win32-g++*:QMAKE_CXXFLAGS += -Wno-missing-field-initializers
#}

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

find_package(Qt6 REQUIRED COMPONENTS Core Core5Compat UiTools Concurrent Qml Widgets Xml Widgets)

add_library(installer STATIC
        proxycredentialsdialog.ui
        serverauthenticationdialog.ui
        componentsummary.ui

        resources/installer.qrc

        packagemanagercore.cpp
        abstractarchive.cpp
        archivefactory.cpp
        aspectratiolabel.cpp
        calculatorbase.cpp
        componentalias.cpp
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
        scriptengine.cpp
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
        packagemanagerproxyfactory.cpp
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
        proxycredentialsdialog.cpp
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

        ${PLATFORM_SOURCES}

        ../ifwtools/resources/ifwtools.qrc
        ../ifwtools/rcc/rcc.cpp
        ../ifwtools/rcc/rccmain.cpp
        ../ifwtools/repositorygen.cpp
        ../ifwtools/binarycreator.cpp
        ../ifwtools/binarydump.cpp

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
target_compile_definitions(installer PRIVATE BUILD_SHARED_IFWTOOLS BUILD_SHARED_KDTOOLS ${IFW_COMPILE_DEFINITIONS})
target_include_directories(installer PUBLIC
        .
        ../ifwtools
        ../kdtools
        ${INCLUDE_DIRS}
        ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(installer PUBLIC
        Qt6::Core
        Qt6::Qml
        Qt6::QmlPrivate
        Qt6::Concurrent
        Qt6::Xml
        Qt6::Widgets
        archive)
target_enable_lto(installer)