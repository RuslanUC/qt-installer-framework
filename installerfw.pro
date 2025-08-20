TEMPLATE = subdirs
SUBDIRS += src tools
tools.depends = src

requires(!cross_compile)

include (installerfw.pri)

BUILD_TESTS = $$(BUILDTESTS)
isEmpty(BUILD_TESTS):BUILD_TESTS=$${BUILDTESTS}
!isEmpty(BUILD_TESTS) {
    SUBDIRS += tests
    tests.depends = src
}

!minQtVersion(6, 7, 0) {
    message("Cannot build Qt Installer Framework with Qt version $${QT_VERSION}.")
    error("Use at least Qt 6.7.0.")
}
