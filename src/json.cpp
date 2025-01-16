#include "jsonlib/json.h"
#include <sstream>
#include <stdexcept>
#include <cctype>

namespace jsonlib {

// 声明解析函数
Json parseValue(const std::string& jsonString, size_t& index);
void skipWhitespace(const std::string& jsonString, size_t& index);
Json parseNull(const std::string& jsonString, size_t& index);
Json parseBool(const std::string& jsonString, size_t& index);
Json parseNumber(const std::string& jsonString, size_t& index);
Json parseString(const std::string& jsonString, size_t& index);
Json parseArray(const std::string& jsonString, size_t& index);
Json parseObject(const std::string& jsonString, size_t& index);

Json Json::deserialize(const std::string& jsonString) {
    size_t index = 0;
    return parseValue(jsonString, index);
}

Json parseValue(const std::string& jsonString, size_t& index) {
    skipWhitespace(jsonString, index);
    if (index >= jsonString.size()) throw std::runtime_error("Unexpected end of JSON input");

    char c = jsonString[index];
    if (c == 'n') return parseNull(jsonString, index);
    if (c == 't' || c == 'f') return parseBool(jsonString, index);
    if (c == '-' || std::isdigit(c)) return parseNumber(jsonString, index);
    if (c == '"') return parseString(jsonString, index);
    if (c == '[') return parseArray(jsonString, index);
    if (c == '{') return parseObject(jsonString, index);

    throw std::runtime_error("Invalid JSON value");
}

void skipWhitespace(const std::string& jsonString, size_t& index) {
    while (index < jsonString.size() && std::isspace(jsonString[index])) {
        ++index;
    }
}

Json parseNull(const std::string& jsonString, size_t& index) {
    if (jsonString.compare(index, 4, "null") == 0) {
        index += 4;
        return Json(nullptr);
    }
    throw std::runtime_error("Invalid JSON null value");
}

Json parseBool(const std::string& jsonString, size_t& index) {
    if (jsonString.compare(index, 4, "true") == 0) {
        index += 4;
        return Json(true);
    }
    if (jsonString.compare(index, 5, "false") == 0) {
        index += 5;
        return Json(false);
    }
    throw std::runtime_error("Invalid JSON boolean value");
}

Json parseNumber(const std::string& jsonString, size_t& index) {
    size_t start = index;
    if (jsonString[index] == '-') ++index;
    while (index < jsonString.size() && std::isdigit(jsonString[index])) ++index;
    if (index < jsonString.size() && jsonString[index] == '.') {
        ++index;
        while (index < jsonString.size() && std::isdigit(jsonString[index])) ++index;
    }
    double number = std::stod(jsonString.substr(start, index - start));
    return Json(number);
}

Json parseString(const std::string& jsonString, size_t& index) {
    ++index; // skip opening quote
    std::string result;
    while (index < jsonString.size() && jsonString[index] != '"') {
        if (jsonString[index] == '\\') {
            ++index;
            if (index >= jsonString.size()) throw std::runtime_error("Invalid escape sequence in JSON string");
            char escaped = jsonString[index];
            switch (escaped) {
                case '"': result += '"'; break;
                case '\\': result += '\\'; break;
                case '/': result += '/'; break;
                case 'b': result += '\b'; break;
                case 'f': result += '\f'; break;
                case 'n': result += '\n'; break;
                case 'r': result += '\r'; break;
                case 't': result += '\t'; break;
                default: throw std::runtime_error("Invalid escape sequence in JSON string");
            }
        } else {
            result += jsonString[index];
        }
        ++index;
    }
    if (index >= jsonString.size() || jsonString[index] != '"') throw std::runtime_error("Unterminated JSON string");
    ++index; // skip closing quote
    return Json(result);
}

Json parseArray(const std::string& jsonString, size_t& index) {
    ++index; // skip opening bracket
    std::vector<Json> elements;
    skipWhitespace(jsonString, index);
    if (index < jsonString.size() && jsonString[index] == ']') {
        ++index; // empty array
        return Json(elements);
    }
    while (index < jsonString.size()) {
        elements.push_back(parseValue(jsonString, index));
        skipWhitespace(jsonString, index);
        if (index < jsonString.size() && jsonString[index] == ']') {
            ++index;
            break;
        }
        if (index >= jsonString.size() || jsonString[index] != ',') throw std::runtime_error("Expected ',' or ']' in JSON array");
        ++index;
    }
    return Json(elements);
}

Json parseObject(const std::string& jsonString, size_t& index) {
    ++index; // skip opening brace
    std::map<std::string, Json> members;
    skipWhitespace(jsonString, index);
    if (index < jsonString.size() && jsonString[index] == '}') {
        ++index; // empty object
        return Json(members);
    }
    while (index < jsonString.size()) {
        skipWhitespace(jsonString, index);
        if (index >= jsonString.size() || jsonString[index] != '"') throw std::runtime_error("Expected '\"' in JSON object");
        Json key = parseString(jsonString, index);
        skipWhitespace(jsonString, index);
        if (index >= jsonString.size() || jsonString[index] != ':') throw std::runtime_error("Expected ':' in JSON object");
        ++index;
        Json value = parseValue(jsonString, index);
        members[key.serialize()] = value;
        skipWhitespace(jsonString, index);
        if (index < jsonString.size() && jsonString[index] == '}') {
            ++index;
            break;
        }
        if (index >= jsonString.size() || jsonString[index] != ',') throw std::runtime_error("Expected ',' or '}' in JSON object");
        ++index;
    }
    return Json(members);
}

} // namespace jsonlib