# API 参考文档

## JsonValue

- `virtual std::string serialize() const`: 序列化 JSON 值为字符串。

## JsonObject

- `JsonObject()`: 构造函数。
- `~JsonObject()`: 析构函数。
- `void set(const std::string& key, std::shared_ptr<JsonValue> value)`: 设置键值对。
- `std::shared_ptr<JsonValue> get(const std::string& key) const`: 获取键对应的值。
- `std::string serialize() const`: 序列化对象为 JSON 字符串。

## JsonArray

- `JsonArray()`: 构造函数。
- `~JsonArray()`: 析构函数。
- `void add(std::shared_ptr<JsonValue> value)`: 添加元素。
- `std::shared_ptr<JsonValue> get(size_t index) const`: 获取指定索引的元素。
- `std::string serialize() const`: 序列化数组为 JSON 字符串。

## JsonParser

- `static std::shared_ptr<JsonValue> parse(const std::string& jsonString)`: 解析 JSON 字符串。

## JsonSerializer

- `static std::string serialize(const std::shared_ptr<JsonValue>& value)`: 序列化 JSON 值。 