cmake_minimum_required(VERSION 3.6)

project(microjson VERSION 0.1.0 LANGUAGES CXX)

set(TARGET microjson)
set(TARGET_STATIC ${TARGET}Static)
set(TARGET_EXPORT ${TARGET}Targets)
set(TARGET_CONFIG ${TARGET}Config)

# Conan support, optional
if(EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
endif()

include(GNUInstallDirs)

set(TARGET_INCLUDE_DIR ${CMAKE_INSTALL_INCLUDEDIR}/${TARGET})
set(TARGET_LIB_DIR ${CMAKE_INSTALL_LIBDIR})
set(TARGET_CMAKE_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
set(TARGET_BINDIR ${CMAKE_INSTALL_BINDIR})

set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MICROJSON_OBJECT_LIB_ONLY)
    add_library(${TARGET} OBJECT microjson.cpp)
    target_include_directories(${TARGET} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${TARGET}>
        $<INSTALL_INTERFACE:${TARGET_INCLUDE_DIR}>
    )
else()
    add_library(${TARGET} microjson.cpp)

    set_target_properties(${TARGET} PROPERTIES VERSION ${PROJECT_VERSION} PUBLIC_HEADER "microjson.h" OUTPUT_NAME ${TARGET})
    target_include_directories(${TARGET} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${TARGET}>
        $<INSTALL_INTERFACE:${TARGET_INCLUDE_DIR}>
    )

    install(TARGETS ${TARGET}
        EXPORT ${TARGET_EXPORT} COMPONENT dev
        ARCHIVE DESTINATION ${TARGET_LIB_DIR} COMPONENT lib
        PUBLIC_HEADER DESTINATION ${TARGET_INCLUDE_DIR} COMPONENT dev
        LIBRARY DESTINATION ${TARGET_LIB_DIR} COMPONENT lib
        RUNTIME DESTINATION ${TARGET_BINDIR} COMPONENT lib)

    install(EXPORT ${TARGET_EXPORT} FILE ${TARGET_EXPORT}.cmake DESTINATION ${TARGET_CMAKE_DIR} COMPONENT dev)

    include(CMakePackageConfigHelpers)
    configure_package_config_file(
        "${TARGET_CONFIG}.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/${TARGET_CONFIG}.cmake"
        INSTALL_DESTINATION "${TARGET_CMAKE_DIR}")

    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${TARGET_CONFIG}.cmake" DESTINATION "${TARGET_CMAKE_DIR}" COMPONENT dev)

    export(PACKAGE ${TARGET})
    export(TARGETS ${TARGET} FILE ${TARGET_EXPORT}.cmake)

    set(MICROJSON_MAKE_TESTS OFF CACHE BOOL "Enables tests")

    if(MICROJSON_MAKE_TESTS)
        find_package(GTest)
        if(GTest_FOUND)
            enable_testing()
            add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/tests")
        else()
            message(STATUS "Force disable test")
        endif()
    endif()
endif()
