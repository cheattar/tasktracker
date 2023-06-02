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

void newTask(std::vector<tasks::task>& taskVector) {
    std::cout << "Please enter your task name.\n? "; std::string utn; std::getline(std::cin, utn);
    std::cout << "Please enter your task contents.\n? "; std::string utc; std::getline(std::cin, utc);
    
   if (taskVector.empty()){
       tasks::task t = { 0, utn, utc };
       taskVector.push_back(t);
    }
   else {
       int id = taskVector.back().id + 1; 
       tasks::task t = { id, utn, utc };
       taskVector.push_back(t);
   }
}



int main() {
    std::vector<tasks::task> taks;
    
    newTask(taks);
    newTask(taks);

    json j = taks;

    std::cout << j << '\n';

    std::ofstream file("tasks.json");
    file << j;

    return 0;
}
