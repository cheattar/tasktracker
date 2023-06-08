#include <fstream>
#include <iostream>
#include <fmt/core.h>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#define PROJECT_NAME "tasktracker"

using json = nlohmann::json;

// Copied from: https://stackoverflow.com/a/52895729
void clear() {
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
    system("clear");
#endif
}

namespace tasks {
    struct task {
        int id;
        std::string description;
        int urgency;
    };

    /* Urgency map:
        1: low,
        2: moderate,
        3: medium,
        4: high,
        5: critical 
    */

    void to_json(json& j, const task& t) {
        //j = json{{ "id", t.id}, {"name", t.name}, {"contents", t.contents}};
        j["id"] = t.id;
        j["description"] = t.description;
        j["urgency"] = t.urgency;
    }
    void from_json(const json& j, task& t) {
        j.at("id").get_to(t.id);
        j.at("description").get_to(t.description);
        j.at("urgency").get_to(t.urgency);
    }

}

void rearrangeIDs(std::vector<tasks::task>& taskVector) {
    int newID = 1;
        for (auto& task : taskVector) {
            task.id = newID++;
        }
}

void viewTasks(std::vector<tasks::task>& taskVector) {
    if (taskVector.size() == 0) {
        fmt::print("No tasks to show.\n");
        return;
    }
    
   fmt::print("|{:^9}|{:^9}|{:^9}|\n", "No.", "Task", "Urgency");
   for (const auto& task : taskVector) {
        fmt::print("|{:^9}|{:^9}|{:^9}|\n", task.id, task.description, task.urgency);
    }
}

void addTask(std::vector<tasks::task>& taskVector) {
    fmt::print("Please enter your task.\n? "); std::string utn; std::getline(std::cin, utn);
    fmt::print("From a scale from 1 to 5, how urgent is your task?\n? "); int utu; std::cin >> utu;
    if (taskVector.empty()){
       tasks::task t = { 0, utn, utu};
       taskVector.push_back(t);
    }
    else {
       int id = taskVector.back().id + 1; 
       tasks::task t = { id, utn, utu};
       taskVector.push_back(t);
   }
   // Clearing cin here fixes an bug with the if statements down below...
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void deleteTask(std::vector<tasks::task>& taskVector) {
    viewTasks(taskVector);

    fmt::print("Please input which task you want to remove.\n? "); std::string inpIDstr; std::getline(std::cin, inpIDstr);
    int inpID = std::stoi(inpIDstr);

    if (inpID >= 1 && inpID <= taskVector.size()) {
        // Find the task to delete using an iterator
        auto it = taskVector.begin() + (inpID - 1);
        taskVector.erase(it);

        // Rearrange IDs so that they match up with vector size
        rearrangeIDs(taskVector);

        fmt::print("Task deleted successfully.\n");
    } 
    else {
        fmt::print("Invalid task ID. Deletion aborted.\n");
    }
}

void loadTasks(std::vector<tasks::task>& taskList) {
    std::ifstream json_file("tasks.json");
    if (json_file) {
        json j = json::parse(json_file);
        taskList = j.get<std::vector<tasks::task>>();
        json_file.close();
    }
    else {
        fmt::print("tasks.json file not found in current directory or it doesn't exist!\nCreating new one...\n");
        std::vector<tasks::task> taskList;
    }
}

int main() {
    fmt::print("Welcome to TaskTracker!\n");
    
    std::vector<tasks::task> taskList;
    loadTasks(taskList);
    
    while (true) {
        fmt::print("Select option: (A)dd task, (D)elete task, (V)iew tasks, E(x)it.\n? ");
        std::string usrChoice; std::getline(std::cin, usrChoice);
        
        if (usrChoice == "A" || usrChoice == "a") {
            clear(); 
            addTask(taskList); 
            rearrangeIDs(taskList); // We rearrange ID's so they look pretty on print, 
                                                // and it's better when delete a task, 
                                                // because human start counting at 1,
                                                // arrays/vectors at 0 (unless you're programming in Lua or MATLAB...)
        }
        else if (usrChoice == "D" || usrChoice == "d") {
            clear(); 
            deleteTask(taskList);
        }
        else if (usrChoice == "V" || usrChoice == "v") {
            clear(); 
            viewTasks(taskList);
        }
        else if (usrChoice == "X" || usrChoice == "x") {
            break;
        }
        else {
            clear(); 
            fmt::print("Incorrect option. Please try again.\n");
        }
    }

    askToSave:
    fmt::print("Do you want to save your tasks file? (Y/N)\n? ");
    std::string usrExit; std::getline(std::cin, usrExit);

    if (usrExit == "Y" || usrExit == "y") {
        json j = taskList;
        fmt::print("Saving tasks file...\n");
        std::ofstream file("tasks.json");
        file << j;
        file.close();
    }
    else if(usrExit == "N" || usrExit == "n") {
        goto exit;
    }
    else {
        fmt::print("Incorrect option. Please try again.\n");
        goto askToSave;
    }
    
    exit:
    fmt::print("Goodbye.\n");

    return 0;
}
