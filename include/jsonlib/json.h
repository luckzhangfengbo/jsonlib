#ifndef JSONLIB_JSON_H
#define JSONLIB_JSON_H

#include <memory>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <initializer_list>

namespace jsonlib {

class JsonValue {
public:
    virtual ~JsonValue() = default;
    virtual std::string serialize() const = 0;
};

class JsonNull : public JsonValue {
public:
    std::string serialize() const override { return "null"; }
};

class JsonBool : public JsonValue {
public:
    explicit JsonBool(bool value) : value_(value) {}
    std::string serialize() const override { return value_ ? "true" : "false"; }
private:
    bool value_;
};

class JsonNumber : public JsonValue {
public:
    explicit JsonNumber(double value) : value_(value) {}
    std::string serialize() const override { return std::to_string(value_); }
private:
    double value_;
};

class JsonString : public JsonValue {
public:
    explicit JsonString(const std::string& value) : value_(value) {}
    std::string serialize() const override { return "\"" + value_ + "\""; }
private:
    std::string value_;
};

class JsonArray : public JsonValue {
public:
    explicit JsonArray(const std::vector<std::shared_ptr<JsonValue>>& values) : values_(values) {}
    std::string serialize() const override {
        std::string result = "[";
        for (size_t i = 0; i < values_.size(); ++i) {
            if (i > 0) result += ", ";
            result += values_[i]->serialize();
        }
        result += "]";
        return result;
    }
private:
    std::vector<std::shared_ptr<JsonValue>> values_;
};

class JsonObject : public JsonValue {
public:
    explicit JsonObject(const std::map<std::string, std::shared_ptr<JsonValue>>& values) : values_(values) {}
    std::string serialize() const override {
        std::string result = "{";
        size_t count = 0;
        for (const auto& pair : values_) {
            if (count++ > 0) result += ", ";
            result += "\"" + pair.first + "\": " + pair.second->serialize();
        }
        result += "}";
        return result;
    }
private:
    std::map<std::string, std::shared_ptr<JsonValue>> values_;
};

class Json {
public:
    Json() : value_(std::make_shared<JsonNull>()) {}
    Json(std::nullptr_t) : value_(std::make_shared<JsonNull>()) {}
    Json(bool value) : value_(std::make_shared<JsonBool>(value)) {}
    Json(int value) : value_(std::make_shared<JsonNumber>(value)) {}
    Json(double value) : value_(std::make_shared<JsonNumber>(value)) {}
    Json(const std::string& value) : value_(std::make_shared<JsonString>(value)) {}
    Json(const char* value) : value_(std::make_shared<JsonString>(value)) {}
    
    // 从 Json 对象的 vector 构造
    Json(const std::vector<Json>& values) {
        std::vector<std::shared_ptr<JsonValue>> jsonValues;
        for (const auto& val : values) {
            jsonValues.push_back(val.value_);
        }
        value_ = std::make_shared<JsonArray>(jsonValues);
    }

    // 从 Json 对象的 map 构造
    Json(const std::map<std::string, Json>& values) {
        std::map<std::string, std::shared_ptr<JsonValue>> jsonValues;
        for (const auto& pair : values) {
            jsonValues[pair.first] = pair.second.value_;
        }
        value_ = std::make_shared<JsonObject>(jsonValues);
    }

    // 新增：支持初始化列表的构造函数
    Json(std::initializer_list<std::pair<const std::string, Json>> init) {
        std::map<std::string, std::shared_ptr<JsonValue>> jsonValues;
        for (const auto& pair : init) {
            jsonValues[pair.first] = pair.second.value_;
        }
        value_ = std::make_shared<JsonObject>(jsonValues);
    }

    // 拷贝构造函数
    Json(const Json& other) : value_(other.value_) {}

    // 移动构造函数（可选，优化性能）
    Json(Json&& other) noexcept : value_(std::move(other.value_)) {}

    // 拷贝赋值操作符
    Json& operator=(const Json& other) {
        if (this != &other) {
            value_ = other.value_;
        }
        return *this;
    }

    // 移动赋值操作符（可选，优化性能）
    Json& operator=(Json&& other) noexcept {
        if (this != &other) {
            value_ = std::move(other.value_);
        }
        return *this;
    }

    std::string serialize() const {
        return value_->serialize();
    }

    static Json deserialize(const std::string& jsonString);

    friend std::ostream& operator<<(std::ostream& os, const Json& json) {
        os << json.serialize();
        return os;
    }

private:
    std::shared_ptr<JsonValue> value_;
};


} // namespace jsonlib

#endif // JSONLIB_JSON_H