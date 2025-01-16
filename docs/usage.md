# 如何使用 JSON 库

## 安装

1. 克隆项目到本地：
   ```bash
   git clone https://github.com/yourusername/jsonlib.git
   cd jsonlib
   ```

2. 使用 CMake 构建项目：
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

## 使用示例

### 解析 JSON 字符串


cpp
#include "jsonlib/json.h"
#include <iostream>
int main() {
std::string jsonString = "{\"key\": \"value\"}";
auto jsonValue = jsonlib::parse(jsonString);
if (jsonValue) {
std::cout << "Parsed JSON: " << jsonValue->serialize() << std::endl;
} else {
std::cout << "Failed to parse JSON." << std::endl;
}
return 0;
}

### 创建和序列化 JSON 对象

cpp
#include "jsonlib/json_object.h"
#include <iostream>
int main() {
auto jsonObject = std::make_shared<jsonlib::JsonObject>();
jsonObject->set("name", std::make_shared<jsonlib::JsonString>("John Doe"));
jsonObject->set("age", std::make_shared<jsonlib::JsonNumber>(30));
std::cout << "Serialized JSON: " << jsonObject->serialize() << std::endl;
return 0;
}

## 注意事项

- 确保使用 C++11 或更高版本进行编译。
- 通过 `std::shared_ptr` 管理 JSON 数据结构的内存。