cmake_minimum_required(VERSION 3.16)

project(ElBuenGusto VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Buscar Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network)

# Archivos del proyecto
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    cocina.cpp
    cocina.h
    cocina.ui
    tarjeta_especialidades.cpp
    tarjeta_especialidades.h
    tarjeta_especialidades.ui
    img.qrc
)

# Crear el ejecutable
if(WIN32)
    add_executable(ElBuenGusto WIN32 ${PROJECT_SOURCES})
elseif(APPLE)
    add_executable(ElBuenGusto MACOSX_BUNDLE ${PROJECT_SOURCES})
else()
    add_executable(ElBuenGusto ${PROJECT_SOURCES})
endif()

# Vincular librerías de Qt
target_link_libraries(ElBuenGusto PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
)

# Propiedades del ejecutable
set_target_properties(ElBuenGusto PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

# Instalación
install(TARGETS ElBuenGusto
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)