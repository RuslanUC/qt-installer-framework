include(${PROJECT_SOURCE_DIR}/cmake/definitions.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/lto.cmake)

find_package(Qt6 REQUIRED COMPONENTS Core LinguistTools)

if (WIN32)
    enable_language(RC)
    set(WIN32_RESOURCES installerbase.rc)
else()
    set(WIN32_RESOURCES "")
endif()

add_executable(installerbase
        settingsdialog.ui

        tabcontroller.h
        installerbasecommons.h
        settingsdialog.h
        sdkapp.h
        commandlineinterface.h
        installerbase.h
        aboutapplicationdialog.h

        main.cpp
        installerbase.cpp
        tabcontroller.cpp
        installerbasecommons.cpp
        settingsdialog.cpp
        commandlineinterface.cpp
        aboutapplicationdialog.cpp

        ${WIN32_RESOURCES})
target_link_libraries(installerbase PUBLIC
        Qt6::Core
        installer)
target_compile_definitions(installerbase PUBLIC ${IFW_COMPILE_DEFINITIONS})
qt_add_translations(installerbase
        TS_FILES
        translations/ifw_ar.ts
        translations/ifw_hu.ts
        translations/ifw_ja.ts
        translations/ifw_fr.ts
        translations/ifw_ca.ts
        translations/ifw_zh_CN.ts
        translations/ifw_pt_PT.ts
        translations/ifw_ko.ts
        translations/ifw_hr.ts
        translations/ifw_it.ts
        translations/ifw_es.ts
        translations/ifw_de.ts
        translations/ifw_pl.ts
        translations/ifw_da.ts
        translations/ifw_sv.ts
        translations/ifw_ru.ts
        translations/ifw_pt_BR.ts)
target_enable_lto(installerbase)
if (WIN32)
    target_link_options(installerbase PRIVATE "/MANIFEST:NO")
endif()

