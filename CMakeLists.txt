cmake_minimum_required(VERSION 3.2)
set(SOURCE_DIRECTORY src)

set(BUILD_NUMBER $ENV{TRAVIS_BUILD_NUMBER})

if(BUILD_NUMBER)
    project(ip_filter VERSION 0.0.${BUILD_NUMBER})
else()
    project(ip_filter VERSION 0.0.1)
endif()

add_subdirectory(${SOURCE_DIRECTORY})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_CONTACT alex.drozhak@me.com)

include(CPack)
