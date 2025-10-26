cmake_minimum_required(VERSION 3.10)
project(hex)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Основная библиотека
add_library(${CMAKE_PROJECT_NAME}_lib STATIC 
  src/array.cpp 
  src/hex.cpp
)
target_include_directories(${CMAKE_PROJECT_NAME}_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Основное приложение (если есть main.cpp)
if(EXISTS ${CMAKE_SOURCE_DIR}/main.cpp)
    add_executable(${CMAKE_PROJECT_NAME}_exe main.cpp)
    target_link_libraries(${CMAKE_PROJECT_NAME}_exe PRIVATE ${CMAKE_PROJECT_NAME}_lib)
endif()

# Добавление тестов
enable_testing()

add_executable(tests test/test.cpp)
target_link_libraries(tests ${CMAKE_PROJECT_NAME}_lib gtest_main)

# Добавление тестов в тестовый набор
add_test(NAME HexTests COMMAND tests)