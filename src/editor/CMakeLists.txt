set(EDITOR_SOURCES
        Main.cpp
        MainWindow.cpp
        LevelScene.cpp
        GraphicsTileItem.cpp
        TextureScene.cpp
        )

FIND_PACKAGE(Qt4 REQUIRED)
include_directories(${QT_INCLUDE_DIR})
include_directories(${QT_QTGUI_INCLUDE_DIR})
include_directories(${QT_QTCORE_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_definitions(-DQT_NO_KEYWORDS )
add_definitions(${QT_DEFINITIONS})

set(GUI_UIS LevelView.ui)
set(GUI_MOCS MainWindow.hpp)

set(GUI_DEPENDENCIES ${QT_QTCORE_LIBRARIES} ${QT_QTGUI_LIBRARIES})

qt_wrap_cpp(editor GUI_MOC_SRC ${GUI_MOCS})
qt_wrap_ui(editor GUI_UI_HDRS GUI_UI_SRC ${GUI_UIS})

add_executable(editor ${EDITOR_SOURCES} ${GUI_MOC_SRC} ${GUI_UI_HDRS})
target_link_libraries(editor ${GUI_DEPENDENCIES} xml)
