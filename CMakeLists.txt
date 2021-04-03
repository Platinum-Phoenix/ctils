cmake_minimum_required(VERSION 3.10)
project(ctils VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED YES)
set(DEFAULT_BUILD_TYPE "Release")
option(CTILS_ENABLE_TESTS "Enable Tests" OFF)

add_library(${PROJECT_NAME} 
    "src/string.c"
)
set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    VERSION         ${PROJECT_VERSION} 
    SOVERSION       ${PROJECT_VERSION_MAJOR}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if (CTILS_ENABLE_TESTS)
    include(CTest)
    add_subdirectory(tests)
endif()

include(GNUInstallDirs)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

install(TARGETS ${PROJECT_NAME}
        EXPORT  ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY include/${PROJECT_NAME}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        PATTERN ".*" EXCLUDE
)

export(TARGETS   ${PROJECT_NAME}
       NAMESPACE ${PROJECT_NAME}::
       FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
)

install(EXPORT      ${PROJECT_NAME}
        FILE        "${PROJECT_NAME}Config.cmake"
        NAMESPACE   ${PROJECT_NAME}::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
