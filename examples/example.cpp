#include "jsonlib/json.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

int main() {
    // Define variables
    std::string name = "Alice";
    int age = 25;
    bool isStudent = false;
    std::string street = "123 Main St";
    std::string city = "Wonderland";
    std::string postalCode = "12345";
    std::vector<std::string> courses = {"Math", "Science", "History"};
    double score = 92.5;

    // Create a map of key-value pairs
    std::map<std::string, jsonlib::Json> jsonMap;

    // Add values to the map
    jsonMap["name"] = jsonlib::Json(name);
    jsonMap["age"] = jsonlib::Json(age);
    jsonMap["isStudent"] = jsonlib::Json(isStudent);
    jsonMap["address"] = jsonlib::Json{
        {"street", jsonlib::Json(street)},
        {"city", jsonlib::Json(city)},
        {"postalCode", jsonlib::Json(postalCode)}
    };
    jsonMap["courses"] = jsonlib::Json(std::vector<jsonlib::Json> {
        jsonlib::Json(courses[0]),
        jsonlib::Json(courses[1]),
        jsonlib::Json(courses[2])
    });
    jsonMap["score"] = jsonlib::Json(score);

    // Create JSON object using map
    jsonlib::Json jsonObject(jsonMap);

    // Serialize JSON object
    std::cout << "Serialized JSON: " << jsonObject << std::endl;

    // Deserialize JSON string
    std::string jsonString = R"({
        "name": "Alice",
        "age": 25,
        "isStudent": false,
        "address": {
            "street": "123 Main St",
            "city": "Wonderland",
            "postalCode": "12345"
        },
        "courses": ["Math", "Science", "History"],
        "score": 92.5
    })";

    try {
        jsonlib::Json parsedJson = jsonlib::Json::deserialize(jsonString);
        std::cout << "Parsed JSON: " << parsedJson << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
