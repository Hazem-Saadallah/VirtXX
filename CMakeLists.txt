CMAKE_MINIMUM_REQUIRED(VERSION 3.31)

project(vmm LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBVIRT REQUIRED IMPORTED_TARGET libvirt)

set(VMM_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/LibvirtConnection.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/src/LibvirtDomain.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Deleters.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/src/ErrorBlock.cxx
)
set(COMMON_LIBS
  PkgConfig::LIBVIRT
)
set(VMM_BIN_NAME bin.out)
set(COMMON_COMPILE_OPTIONS -Wall -Wextra)

add_library(${PROJECT_NAME} SHARED ${VMM_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${CMAKE_CURRENT_SOURCE_DIR}/extern/libxml2/include
)

target_link_libraries(${PROJECT_NAME} PUBLIC ${COMMON_LIBS})
target_compile_options(${PROJECT_NAME} PRIVATE ${COMMON_COMPILE_OPTIONS})

# add_executable(${VMM_BIN_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cxx)
# target_link_libraries(${VMM_BIN_NAME} PRIVATE ${PROJECT_NAME})
