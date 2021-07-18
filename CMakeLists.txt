cmake_minimum_required(VERSION 3.5)

project(uzume_gui_prototype VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        domain/entities/WaveformFragments.hpp
        domain/entities/WaveformFragments.cpp
        domain/usecases/EditVoice.hpp
        domain/usecases/EditVoice.cpp
        models/Contour.hpp
        models/Contour.cpp
        views/ContourWidget.hpp
        views/ContourWidget.cpp
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(uzume_gui_prototype
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(uzume_gui_prototype SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(uzume_gui_prototype
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(uzume_gui_prototype PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

include(ExternalProject)

ExternalProject_add(uzume_vocoder
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/uzume_vocoder
        GIT_REPOSITORY https://github.com/haruneko/uzume_vocoder
        GIT_TAG master
        INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}"
        )

add_dependencies(uzume_gui_prototype uzume_vocoder)
link_directories(uzume_gui_prototype PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/lib)
target_include_directories(uzume_gui_prototype PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include/uzume_vocoder)
if(MSVC)
    target_link_libraries(uzume_gui_prototype PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/lib/uzume_vocoder.lib)
else()
    target_link_libraries(uzume_gui_prototype PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/lib/libuzume_vocoder.a)
endif()

set_target_properties(uzume_gui_prototype PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(uzume_gui_prototype)
endif()
