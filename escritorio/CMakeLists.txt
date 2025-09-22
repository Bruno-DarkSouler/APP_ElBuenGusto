cmake_minimum_required(VERSION 3.16)

project(ElBuenGusto VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp

    # MainWindow
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    # Carrito
    carrito.cpp
    carrito.h
    carrito.ui

    # Cajero
    cajero.cpp
    cajero.h
    cajero.ui

    # Tarjeta especialidades
    tarjeta_especialidades.cpp
    tarjeta_especialidades.h
    tarjeta_especialidades.ui

    # Tarjeta comida principal
    tarjeta_comida_principal.cpp
    tarjeta_comida_principal.h
    tarjeta_comida_principal.ui

    # Recursos
    img.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ElBuenGusto
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        confirmacion_pedido.h confirmacion_pedido.cpp confirmacion_pedido.ui
    )
else()
    if(ANDROID)
        add_library(ElBuenGusto SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(ElBuenGusto
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ElBuenGusto PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ElBuenGusto)
endif()
set_target_properties(ElBuenGusto PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ElBuenGusto
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ElBuenGusto)
endif()
