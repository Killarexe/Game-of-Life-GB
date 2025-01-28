cmake_minimum_required(VERSION 3.14)
project(GameOfLife C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# Define GBDK version and URL
set(GBDK_VERSION "4.3.0")
set(IS64BIT ${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "x86_64")
message(STATUS "Current OS: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Current architecture: ${CMAKE_HOST_SYSTEM_PROCESSOR}")
message(STATUS "Installing GBDK ${GBDK_VERSION}.")
if(WIN32)
  if(IS64BIT)
    set(GBDK_URL "https://github.com/gbdk-2020/gbdk-2020/releases/download/${GBDK_VERSION}/gbdk-win64.zip")
  else()
    set(GBDK_URL "https://github.com/gbdk-2020/gbdk-2020/releases/download/${GBDK_VERSION}/gbdk-win32.zip")
  endif()
elseif(UNIX AND NOT APPLE AND IS64BIT)
  set(GBDK_URL "https://github.com/gbdk-2020/gbdk-2020/releases/download/${GBDK_VERSION}/gbdk-linux64.tar.gz")
elseif(APPLE)
  if(IS64BIT)
    set(GBDK_URL "https://github.com/gbdk-2020/gbdk-2020/releases/download/${GBDK_VERSION}/gbdk-macos.tar.gz")
  else()
    set(GBDK_URL "https://github.com/gbdk-2020/gbdk-2020/releases/download/${GBDK_VERSION}/gbdk-macos-arm64.tar.gz")
  endif()
else()
  message(FATAL_ERROR "Your OS to deep in the iceberg to install GBDK. Please use Linux, Windows or Mac.")
endif()
# Download and extract GBDK
FetchContent_Declare(
    gbdk
    URL ${GBDK_URL}
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(gbdk)

# Set GBDK path
set(GBDK_PATH "${gbdk_SOURCE_DIR}")

# Find lcc compiler
if(WIN32)
  find_program(LCC "${GBDK_PATH}/bin/lcc.exe")
else()
  find_program(LCC "${GBDK_PATH}/bin/lcc")
endif()

if(NOT LCC)
    message(FATAL_ERROR "lcc compiler not found in GBDK")
endif()

# Set compile and link commands
set(CMAKE_C_COMPILE_OBJECT "<CMAKE_C_COMPILER> -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o <OBJECT> <SOURCE>")
set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_C_COMPILER> -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -o <TARGET> <OBJECTS>")

# Add your source files here
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.c")

# Create custom target for GameBoy ROM
add_custom_target(${PROJECT_NAME}.gb ALL
  COMMAND ${LCC} -Wl-l${CMAKE_CURRENT_LIST_DIR}/lib/hUGEDriver.lib -Wl-m -Wl-j -DUSE_SFR_FOR_REG -o ${PROJECT_NAME}.gb ${SOURCES} 
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  DEPENDS ${SOURCES}
  COMMENT "Building GameBoy ROM"
)

# Set include directories
include_directories(${GBDK_PATH}/include)
include_directories("src")

# Add custom clean target
add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/cmake/CleanAll.cmake
)
