include(FetchContent)
CMAKE_MINIMUM_REQUIRED(VERSION 3.31)
project(virtxx LANGUAGES C CXX)

option(VIRTXX_BUILD_TESTS "Build the main.cxx test executable" OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(VIRTXX_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/VirtXX/Impl/LibvirtConnection.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/src/VirtXX/Impl/LibvirtDomain.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/src/VirtXX/Impl/LibvirtStoragePool.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/src/VirtXX/Impl/LibvirtStorageVolume.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/src/VirtXX/Impl/Deleters.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/src/VirtXX/Impl/ErrorBlock.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/src/VirtXX/Impl/XMLConfig.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/src/VirtXX/Impl/Global.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/src/VirtXX/Impl/Misc.cxx

  ${CMAKE_CURRENT_SOURCE_DIR}/src/VirtXX/Impl/Config/Base/BaseConfig.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/src/VirtXX/Impl/Config/StoragePoolConfig.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/src/VirtXX/Impl/Config/StorageVolumeConfig.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/src/VirtXX/Impl/Config/Datatype.cxx
)
set(COMMON_LIBS
  PkgConfig::LIBVIRT
  pugixml
)
set(VIRTXX_BIN_NAME bin.out)
set(COMMON_COMPILE_OPTIONS -Wall -Wextra)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBVIRT REQUIRED IMPORTED_TARGET libvirt)
set(PKG_CONFIG_USE_STATIC_LIBS ON)

add_library(${PROJECT_NAME} SHARED ${VIRTXX_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:include>
)

FetchContent_Declare(
  pugixml
  URL https://github.com/zeux/pugixml/releases/download/v1.15/pugixml-1.15.tar.gz
  DOWNLOAD_EXTRACT_TIMESTAMP true
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/pugixml
  BINARY_DIR ${CMAKE_BINARY_DIR}/extern/pugixml
)
FetchContent_MakeAvailable(pugixml)

target_link_libraries(${PROJECT_NAME} PUBLIC ${COMMON_LIBS})
target_compile_options(${PROJECT_NAME} PRIVATE ${COMMON_COMPILE_OPTIONS})

if(VIRTXX_BUILD_TESTS)
  add_executable(${VIRTXX_BIN_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cxx)
  target_link_libraries(${VIRTXX_BIN_NAME} PRIVATE ${PROJECT_NAME})
endif()
