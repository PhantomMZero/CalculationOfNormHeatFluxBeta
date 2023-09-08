cmake_minimum_required(VERSION 3.5)

project(Calculation_of_thermal_insulation VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Charts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        SourceData.cpp
        normheatfluxdensity.cpp
        mainwindow.h
        normheatfluxdensity.h
        mainwindow.ui
        normheatfluxdensity.ui
        Functions.h
        Functions.cpp
        SourceData.h
        resources.qrc
        checkheat.h
        checkheat.cpp
        checkheat.ui
        lamdadialog.h lamdadialog.cpp lamdadialog.ui
        findlambda.h findlambda.cpp findlambda.ui
        closestelementsintables.h closestelementsintables.cpp
        linearregression.h linearregression.cpp
        charts.h charts.cpp charts.ui
        exponentialfitting.h exponentialfitting.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Calculation_of_thermal_insulation
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Calculation_of_thermal_insulation APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Calculation_of_thermal_insulation SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Calculation_of_thermal_insulation
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Calculation_of_thermal_insulation PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts)


set_target_properties(Calculation_of_thermal_insulation PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Calculation_of_thermal_insulation
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Calculation_of_thermal_insulation)
endif()
