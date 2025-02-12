# Set the CMake minimum version
cmake_minimum_required(VERSION 3.31.5)

# Set the project name
project(Astra VERSION 0.1 LANGUAGES CXX)

# Add Qt's uic for processing .ui files
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Set the CMake C/C++ version
set(CMAKE_CXX_STANDARD 20)

# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Add the main window source files
set(SOURCES
  ${CMAKE_SOURCE_DIR}/../project/src/main.cpp
  ${CMAKE_SOURCE_DIR}/../project/src/login.cpp
)

# Add the main window header files
set(HEADERS
  ${CMAKE_SOURCE_DIR}/../project/inc/login.hpp
  ${CMAKE_SOURCE_DIR}/../project/inc/inc.hpp
)

# Add the UI file
set(UI_FILES
)

# Add the QML file
set(QML_FILES
  
)

# Specify the Oracle include and library directories
include_directories(/usr/local/include/oracle)
link_directories(/usr/local/lib/oracle)

# Find Qt6 packages
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Qml)

# Add the executable target
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${UI_FILES} ${QML_FILES})

# Link Qt libraries
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets Qt6::Qml)

# Link oracle libraries
target_link_libraries(${PROJECT_NAME} PRIVATE clntsh occi)

# Add the tests subdirectory
# add_subdirectory(test)

# Make this a GUI application on Windows
if(WIN32)
  set(CMAKE_WIN32_EXECUTABLE ON)
endif()
