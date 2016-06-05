PROJECT_ROOT_PATH = $${PWD}/

win32: OS_SUFFIX = win32
linux-g++: OS_SUFFIX = linux

CONFIG(debug, debug|release) {
    BUILD_FLAG = debug
    LIB_SUFFIX = d
} else {
    BUILD_FLAG = release
}

LIBS_PATH = $${PROJECT_ROOT_PATH}/lib.$${OS_SUFFIX}/
IMPORT_PATH = $${PROJECT_ROOT_PATH}/import/
BIN_PATH = $${PROJECT_ROOT_PATH}/bin/$${BUILD_FLAG}/

BUILD_PATH = $${PROJECT_ROOT_PATH}/build.$${OS_SUFFIX}/$${BUILD_FLAG}/$${TARGET}/
RCC_DIR = $${BUILD_PATH}/rcc/
UI_DIR = $${BUILD_PATH}/ui/
MOC_DIR = $${BUILD_PATH}/moc/
OBJECTS_DIR = $${BUILD_PATH}/obj/

linux-g++: QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += $${IMPORT_PATH}/QxtCore/ $${IMPORT_PATH}/QxtNetwork/
INCLUDEPATH += $${PROJECT_ROOT_PATH}/src/include/
LIBS += -L$${LIBS_PATH}/
