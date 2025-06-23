cmake_minimum_required(VERSION 3.16)
project(ACT VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt5 components
find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

# Set Qt5 MOC, UIC, and RCC to automatic
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Source files
set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/sidebar.cpp
    src/settingsdialog.cpp
    src/moderncard.cpp
)

# Header files
set(HEADERS
    src/mainwindow.h
    src/sidebar.h
    src/settingsdialog.h
    src/moderncard.h
)

# Create executable
add_executable(ACT ${SOURCES} ${HEADERS})

# Link Qt5 libraries
target_link_libraries(ACT Qt5::Core Qt5::Widgets)

# Set output directory
set_target_properties(ACT PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Compiler-specific options
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(ACT PRIVATE -Wall -Wextra -pedantic)
endif()
   