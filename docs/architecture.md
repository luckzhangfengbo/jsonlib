# 项目架构说明

## 概述

`jsonlib` 是一个用于解析和序列化 JSON 数据的库，支持 C 和 C++。项目采用模块化设计，分为多个组件以实现不同的功能。

## 目录结构

- `include/jsonlib/`: 包含所有的头文件，定义了库的接口。
- `src/`: 包含库的实现文件。
- `tests/`: 包含单元测试文件。
- `examples/`: 包含示例代码，展示如何使用库。
- `docs/`: 包含项目的文档。

## 模块说明

- **JsonValue**: 所有 JSON 数据类型的基类。
- **JsonObject**: 表示 JSON 对象，支持键值对的存储和访问。
- **JsonArray**: 表示 JSON 数组，支持元素的存储和访问。
- **JsonParser**: 负责将 JSON 字符串解析为内部数据结构。
- **JsonSerializer**: 负责将内部数据结构序列化为 JSON 字符串。

## 设计原则

- **模块化**: 各个模块独立实现特定功能，易于维护和扩展。
- **兼容性**: 支持 C 和 C++，提供简单易用的接口。
- **性能**: 通过高效的内存管理和解析算法，确保性能。 