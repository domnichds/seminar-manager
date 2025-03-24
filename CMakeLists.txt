cmake_minimum_required(VERSION 3.19)
project(untitled1 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

# Добавляем ресурсный файл
qt_add_resources(RESOURCES font.qrc)

qt_add_executable(untitled1
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    secondwindow.cpp
    secondwindow.h
    ${RESOURCES}
    CSVHandler.hpp
    CSVHandler.cpp
    SeminarData.cpp
    SeminarData.hpp
    SeminarManager.cpp
    SeminarManager.hpp
    StudentData.cpp
    StudentData.hpp
    StudentManager.cpp
    StudentManager.hpp
    DateSortProxyModel.hpp
    DateSortProxyModel.cpp
)
target_link_libraries(untitled1 PRIVATE Qt6::Core Qt6::Widgets)
