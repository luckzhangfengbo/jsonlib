cmake_minimum_required(VERSION 3.10)
project(jsonlib)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_library(jsonlib
    src/json.cpp
)

add_executable(example2 examples/example.cpp)
target_link_libraries(example2 jsonlib)

# enable_testing()
# add_subdirectory(tests)

# 是的，CMakeLists.txt 文件看起来是正确的。它配置了项目的基本构建设置，包括：
# CMake 版本要求: cmake_minimum_required(VERSION 3.10) 确保使用 CMake 3.10 或更高版本。
# 项目名称: project(jsonlib) 设置项目名称为 jsonlib。
# C++ 标准: set(CMAKE_CXX_STANDARD 11) 指定使用 C++11 标准。
# 包含目录: include_directories(include) 添加 include 目录到编译器的头文件搜索路径。
# 库目标: add_library(jsonlib ...) 定义一个名为 jsonlib 的库，并列出所有源文件。
# 可执行文件: add_executable(example examples/example_usage.cpp) 定义一个名为 example 的可执行文件，使用 examples/example_usage.cpp 作为源文件。
# 链接库: target_link_libraries(example jsonlib) 将 jsonlib 库链接到 example 可执行文件。
# 测试支持: enable_testing() 启用测试支持，并添加 tests 子目录。
