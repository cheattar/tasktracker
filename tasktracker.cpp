#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#define PROJECT_NAME "tasktracker"

using json = nlohmann::json;

namespace tasks {
    struct task {
        int id; 
        std::string name;
        std::string contents;
    };

    void to_json(json& j, const task& t) {
        //j = json{{ "id", t.id}, {"name", t.name}, {"contents", t.contents}};
        j["id"] = t.id;
        j["name"] = t.name;
        j["contents"] = t.contents;
    }
    void from_json(const json& j, task t) {
        j.at("id").get_to(t.id);
        j.at("name").get_to(t.name);
        j.at("contents").get_to(t.contents);
    }

}

void newTask(std::vector<tasks::task> tasks) {
    std::cout << "Please enter your task name.\n? "; std::string utn; std::getline(std::cin, utn);
    std::cout << "Please enter your task contents.\n? "; std::string utc; std::getline(std::cin, utc);
    
    if (tasks.size() == 0){
        tasks.push_back(tasks::task{0, utn, utc});
    }
    else {
        int id = tasks.back().id + 1; 
        tasks.push_back(tasks::task{id, utn, utc});
    }
    
}

int main() {
    std::vector<tasks::task> taks(0);
    
    newTask(taks);
    newTask(taks);

    //std::stringstream s;

    json j = taks;

    std::cout << j << '\n';

    std::ofstream file("tasks.json");
    file << j;

    //std::cout << "Hello, world!" << std::endl;
    return 0;
}
