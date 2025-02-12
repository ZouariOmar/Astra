#!/bin/bash
# ====================================================================================
# Script: run.sh
# Purpose: This script automates the build, clean, and run processes
#          for a project using CMake and a specified build tool (make
#          or ninja). It allows users to perform operations like
#          configuring the project, building, cleaning the build
#          directory, and running the application.
# Usage: ./run.sh <build_tool> <command> [--root | --all | --test]
#
# Arguments:
#   <build_tool>   - The build tool to use. Supported values: 'make' or 'ninja'.
#   <command>      - The action to perform. Supported commands:
#                   'build', 'run', 'clean', or 'test'.
#   [--root]        - Optional flag for building from the root directory.
#   [--all]         - Optional flag for cleaning all files from the build directory.
#   [--test]        - Optional flag to run tests after building the project.
#
# Example Usage:
#   ./run.sh make build         - Build the project using make
#   ./run.sh ninja build        - Build the project using ninja
#   ./run.sh make clean --all   - Clean the project by removing all build files
#   ./run.sh make run           - Run the application after building it
#   ./run.sh make run --test    - Run the application and execute tests after building it
# ====================================================================================

# Define color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No color

if [ $1 == "start" -a $2 == "ds" ]; then
  /home/zouari_omar/Qt/Tools/QtDesignStudio/bin/qtdesignstudio
  exit 0
fi

#* Check if at least two arguments are provided
if [ "$#" -lt 2 ]; then
  echo -e "${RED}Error:${NC} Insufficient arguments."
  echo -e "${YELLOW}Usage${NC}: ./run.sh <build_tool> <command> [--root | --all | --test]"
  exit 1
fi

#* Define variables
APP_NAME="Astra"
BUILD_DIR="bin/build"
CMAKE_LIST_DIR="conf"
TEST_NAME="test"
TEST_BUILD_DIR="$BUILD_DIR/test"
BUILD_TOOL=$1
ARG=$2
OPTION=$3

#* Map build tool to CMake generator
case "$BUILD_TOOL" in
make)
  CMAKE_GENERATOR="Unix Makefiles"
  ;;
ninja)
  CMAKE_GENERATOR="Ninja"
  ;;
*)
  echo -e "${RED}Error:${NC} Invalid build tool. Supported tools: make, ninja."
  exit 1
  ;;
esac

#* Process commands
case "$ARG" in
build)
  #* Handle build with --root option
  if [ "$OPTION" == "--root" ]; then
    echo -e "${BLUE}Building project from root using CMake with generator '$CMAKE_GENERATOR'...${NC}"
    cmake -S "$CMAKE_LIST_DIR" -B "$BUILD_DIR" -G "$CMAKE_GENERATOR" || {
      echo -e "${RED}Error:${NC} CMake configuration failed."
      exit 1
    }
    $BUILD_TOOL -C "$BUILD_DIR" || {
      echo -e "${RED}Error:${NC} Build failed."
      exit 1
    }
    echo -e "${GREEN}Build from root completed successfully.${NC}"
    exit 0
  fi

  #* Handle regular build
  if [ -d "$BUILD_DIR" ]; then
    echo -e "${BLUE}Building project in '$BUILD_DIR'...${NC}"
    cd "$BUILD_DIR" || {
      echo -e "${RED}Error:${NC} Failed to enter build directory."
      exit 1
    }
    $BUILD_TOOL || {
      echo -e "${RED}Error:${NC} Build failed."
      exit 1
    }
    echo -e "${GREEN}Build completed successfully.${NC}"
  else
    echo -e "${RED}Error:${NC} Build directory '$BUILD_DIR' not found."
    exit 1
  fi
  ;;
run)
  #* Run the application if it exists
  if [ "$OPTION" == "--test" ]; then
    #* Run tests after building
    echo -e "${BLUE}Running tests after building the project...${NC}"
    cd "$TEST_BUILD_DIR" || {
      echo -e "${RED}Error:${NC} Failed to enter build directory."
      exit 1
    }
    ./$TEST_NAME || {
      echo -e "${RED}Error:${NC} Application run failed."
      exit 1
    }
    echo -e "${GREEN}Running tests...${NC}"
    # Run tests using ctest (or your test framework)
    ctest || {
      echo -e "${RED}Error:${NC} Test execution failed."
      exit 1
    }
    echo -e "${GREEN}Tests completed successfully.${NC}"
    exit 0
  fi

  #* Regular run (without tests)
  if [ -f "$BUILD_DIR/$APP_NAME" ]; then
    echo -e "${BLUE}Running application...${NC}"

    #* Run the application binary
    "$BUILD_DIR/$APP_NAME" || {
      echo -e "${RED}Error:${NC} Failed to run the application."
      exit 1
    }
  else
    echo -e "${RED}Error:${NC} Application '$APP_NAME' not found in '$BUILD_DIR'."
    exit 1
  fi
  ;;
clean)
  #* Handle clean with --all option
  if [ "$OPTION" == "--all" ]; then
    if [ -d "$BUILD_DIR" ]; then
      echo -e "${BLUE}Removing all contents (including hidden files) inside '$BUILD_DIR'...${NC}"
      rm -rf "$BUILD_DIR"/* "$BUILD_DIR"/.* 2>/dev/null || {
        echo -e "${RED}Error:${NC} Failed to delete contents of build directory."
        exit 1
      }
      echo -e "${GREEN}Clean operation completed successfully.${NC}"
    else
      echo -e "${RED}Error:${NC} Build directory '$BUILD_DIR' not found."
      exit 1
    fi
    exit 0
  fi

  #* Clean the build directory
  if [ -d "$BUILD_DIR" ]; then
    echo -e "${BLUE}Cleaning build directory...${NC}"
    cd "$BUILD_DIR" || {
      echo -e "${RED}Error:${NC} Failed to enter build directory."
      exit 1
    }
    $BUILD_TOOL clean || {
      echo -e "${RED}Error:${NC} Clean failed."
      exit 1
    }
    echo -e "${GREEN}Clean completed successfully.${NC}"
  else
    echo -e "${RED}Error:${NC} Build directory '$BUILD_DIR' not found."
    exit 1
  fi
  ;;
*)
  #* Invalid command
  echo -e "${RED}Error:${NC} Unknown command '$ARG'. Supported commands: build, run, clean, test."
  echo -e "${YELLOW}Usage:${NC} ./run.sh <build_tool> <command> [--root | --all | --test]"
  exit 1
  ;;
esac
