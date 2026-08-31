cmake_minimum_required(VERSION 3.16)

project(libraryAPI VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_EXTENSIONS OFF)


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()


# --- PostgreSQL (libpqxx) ---
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

# --- Redis (redis++) ---
set(REDIS_PLUS_PLUS_LIB "/usr/local/lib/libredis++.so")
set(HIREDIS_LIB "/usr/local/lib/libhiredis.so")
set(REDIS_INCLUDE_DIRS "/usr/local/include/hiredis" "/usr/local/include/sw/redis++")

# --- Boost ---
find_package(Boost 1.66 REQUIRED COMPONENTS system)

# --- Crow (header-only) ---
set(CROW_INCLUDE_DIR "/opt/Crow/include")

# --- nlohmann/json ---
include(FetchContent)
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(json)

add_executable(library_server
    src/config.cpp
    src/cache/cacheManager.cpp
    src/db/dbPool.cpp
    src/db/bookRepository.cpp
    src/service/bookService.cpp
    src/main.cpp
)

target_include_directories(library_server PRIVATE
    src/
    ${PQXX_INCLUDE_DIRS}
    ${CROW_INCLUDE_DIR}
    ${REDIS_INCLUDE_DIRS} 
    ${json_SOURCE_DIR}/include 
)

target_link_libraries(library_server PRIVATE
    ${PQXX_LIBRARIES}
    ${REDIS_PLUS_PLUS_LIB}
    ${HIREDIS_LIB}
    Boost::system
    pthread  
    nlohmann_json::nlohmann_json
)

#enable_testing()
#add_subdirectory(tests)