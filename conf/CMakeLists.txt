# Set the CMake minimum version
cmake_minimum_required(VERSION 3.31.5)

# Set the project name
project(Astra VERSION 0.1 LANGUAGES CXX)

# Generate `compile_commands.json` file
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add Qt's uic for processing .ui files
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Set the CMake C/C++ version
set(CMAKE_CXX_STANDARD 20)

# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Add source(s) files
set(SOURCES
  # @ZouariOmar part
  ${CMAKE_SOURCE_DIR}/../project/src/main.cpp
  ${CMAKE_SOURCE_DIR}/../project/src/MainWindow.cpp
  ${CMAKE_SOURCE_DIR}/../project/src/LoginUI.cpp
  ${CMAKE_SOURCE_DIR}/../project/src/EmployeesUI.cpp
  ${CMAKE_SOURCE_DIR}/../project/src/EmployeesUIUtils.cpp
  ${CMAKE_SOURCE_DIR}/../project/src/EmployeesUICharts.cpp
  ${CMAKE_SOURCE_DIR}/../project/src/EmailSender.cpp
  ${CMAKE_SOURCE_DIR}/../project/src/Employees.cpp
  ${CMAKE_SOURCE_DIR}/../project/src/EmployeesStatistics.cpp
  ${CMAKE_SOURCE_DIR}/../project/src/HtmlBodyFormatter.cpp
  ${CMAKE_SOURCE_DIR}/../project/src/PasswordGenerator.cpp
  ${CMAKE_SOURCE_DIR}/../project/src/Database.cpp
  ${CMAKE_SOURCE_DIR}/../project/src/PdfGenerator.cpp
  ${CMAKE_SOURCE_DIR}/../project/src/CSVGenerator.cpp
  ${CMAKE_SOURCE_DIR}/../project/src/FaceRecognizer.cpp
  ${CMAKE_SOURCE_DIR}/../project/src/MediaPlayer.cpp
  ${CMAKE_SOURCE_DIR}/../project/src/SerialPortManager.cpp
)

# Add header(s) files
set(HEADERS
  # @ZouariOmar part
  ${CMAKE_SOURCE_DIR}/../project/inc/MainWindow.hpp
  ${CMAKE_SOURCE_DIR}/../project/inc/LoginUI.hpp
  ${CMAKE_SOURCE_DIR}/../project/inc/EmployeesUI.hpp
  ${CMAKE_SOURCE_DIR}/../project/inc/EmployeesUIUtils.hpp
  ${CMAKE_SOURCE_DIR}/../project/inc/EmployeesUICharts.hpp
  ${CMAKE_SOURCE_DIR}/../project/inc/EmailSender.hpp
  ${CMAKE_SOURCE_DIR}/../project/inc/Employees.hpp
  ${CMAKE_SOURCE_DIR}/../project/inc/EmployeesStatistics.hpp
  ${CMAKE_SOURCE_DIR}/../project/inc/HtmlBodyFormatter.hpp
  ${CMAKE_SOURCE_DIR}/../project/inc/PasswordGenerator.hpp
  ${CMAKE_SOURCE_DIR}/../project/inc/Database.hpp
  ${CMAKE_SOURCE_DIR}/../project/inc/PdfGenerator.hpp
  ${CMAKE_SOURCE_DIR}/../project/inc/CSVGenerator.hpp
  ${CMAKE_SOURCE_DIR}/../project/inc/FaceRecognizer.hpp
  ${CMAKE_SOURCE_DIR}/../project/inc/MediaPlayer.hpp
  ${CMAKE_SOURCE_DIR}/../project/inc/SerialPortManager.hpp
)

# Add the templates files
set(TEMPLATES
  ${CMAKE_SOURCE_DIR}/../project/templates/Employees.tpp
)

# Specify the Oracle include and library directories
include_directories(/usr/local/include/oracle)
link_directories(/usr/local/lib/oracle)

# Find Qt6 packages
find_package(Qt6 REQUIRED COMPONENTS
  Core Gui Widgets
  Pdf WebEngineWidgets WebEngineCore
  Concurrent
  Charts
  Multimedia
  SerialPort
)

# Find libcurl package
find_package(CURL REQUIRED)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Add the executable target
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${TEMPLATES})

target_link_libraries(${PROJECT_NAME} PRIVATE
  Qt6::Core Qt6::Gui Qt6::Widgets                   # Link Qt6 libraries
  Qt6::Pdf Qt6::WebEngineWidgets Qt6::WebEngineCore
  Qt6::Concurrent
  Qt6::Charts
  Qt6::Multimedia
  Qt6::SerialPort
  clntsh occi                                       # Link oracle libraries
  CURL::libcurl                                     # Link libcurl libraries
  -lssl -lcrypto                                    # Link openssl libraries
  ${OpenCV_LIBS}                                    # Link OpenCV libraries
)

# Add the tests subdirectory
# add_subdirectory(test)

# Make this a GUI application on Windows
if(WIN32)
  set(CMAKE_WIN32_EXECUTABLE ON)
endif()
