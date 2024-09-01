#include<bits/stdc++.h>
#include <fstream>
#include <cstdlib>
#include <functional>

using namespace std;

int ID = 0;

struct todo {
    int id;
    string username;
    string task;
};

struct User {
    string username;
    string password;
};

unordered_map<string, User> users;

string hashPassword(string password) {
    return to_string(hash<string>{}(password));
}

void loadUsers() {
    ifstream userFile("users.txt");
    string username, password;
    while (getline(userFile, username) && getline(userFile, password)) {
        users[username] = {username, password};
    }
    userFile.close();
}

void saveUser(User user) {
    ofstream userFile("users.txt", ios::app);
    userFile << user.username << "\n" << user.password << "\n";
    userFile.close();
}

bool createUser(string username, string password) {
    if (users.find(username) != users.end()) {
        cout << "Username already exists. Please choose a different one." << endl;
        return false;
    }
    User user = {username, hashPassword(password)};
    users[username] = user;
    saveUser(user);
    return true;
}

bool authenticateUser(string username, string password) {
    if (users.find(username) != users.end()) {
        if (users[username].password == hashPassword(password)) {
            return true;
        }
    }
    return false;
}

void addTodoForUser(string username) {
    system("cls");
    todo todoItem;
    cout << "\n\tEnter new task: ";
    cin.get();
    getline(cin, todoItem.task);
    todoItem.username = username;
    ID++;
    
    ofstream write("todo.txt", ios::app);
    write << "\n" << ID;
    write << "\n" << todoItem.username;
    write << "\n" << todoItem.task;
    write.close();

    ofstream idFile("id.txt");
    idFile << ID;
    idFile.close();
    
    char ch;
    cout << "\n\tDo you want to add more tasks? (y/n): "; 
    cin >> ch;
    if (ch == 'y') {
        addTodoForUser(username);
    } else {
        cout << "\n\tTask added successfully.";
    }
}

void print(todo s) {
    cout << "\n\tID: " << s.id;
    cout << "\n\tTask: " << s.task << "\n";
}

void readDataForUser(string username) {
    system("cls");
    todo todoItem;
    ifstream read("todo.txt");
    cout << "\n\t\t\t------------------Your current Tasks--------------------\n";
    while (!read.eof()) {
        read >> todoItem.id;
        read.ignore();
        getline(read, todoItem.username);
        getline(read, todoItem.task);
        if (todoItem.username == username) {
            print(todoItem);
        }
    }
    read.close();
}

int searchDataForUser(string username) {
    system("cls");
    int id;
    cout << "\n\tEnter task ID: ";     
    cin >> id;
    todo todoItem;
    ifstream read("todo.txt");
    while (!read.eof()) {
        read >> todoItem.id;
        read.ignore();
        getline(read, todoItem.username);
        getline(read, todoItem.task);
        if (todoItem.username == username && todoItem.id == id) {
            print(todoItem);
            return id;
        }
    }
    return -1;
}

void deleteDataForUser(string username) {
    system("cls");
    int id = searchDataForUser(username);
    if (id == -1) {
        cout << "\n\tTask not found.";
        return;
    }

    cout << "\n\tDo you want to delete this task? (y/n): ";
    char choice;
    cin >> choice;
    if (choice == 'y') {
        todo todoItem;
        ofstream tempFile("temp.txt");
        ifstream read("todo.txt");
        
        while (!read.eof()) {
            read >> todoItem.id;
            read.ignore();
            getline(read, todoItem.username);
            getline(read, todoItem.task);
            if (todoItem.username != username || todoItem.id != id) {
                tempFile << "\n" << todoItem.id;
                tempFile << "\n" << todoItem.username;
                tempFile << "\n" << todoItem.task;
            }
        }
        read.close();
        tempFile.close();
        remove("todo.txt");
        rename("temp.txt", "todo.txt");
        cout << "\n\tTask deleted successfully.";
    } else {
        cout << "\n\tTask not deleted.";
    }
}

int main() {
    system("cls");
    system("Color E0"); 
    system("title todoapp @copyassignment");

    loadUsers();
    string username, password;

    cout << "\n\t1. Create Account";
    cout << "\n\t2. Login";
    int authChoice;
    cout << "\n\tEnter choice: ";
    cin >> authChoice;

    if (authChoice == 1) {
        cout << "\n\tEnter username: ";
        cin >> username;
        cout << "\n\tEnter password: ";
        cin >> password;
        if (!createUser(username, password)) {
            return 1;
        }
    } else if (authChoice == 2) {
        cout << "\n\tEnter username: ";
        cin >> username;
        cout << "\n\tEnter password: ";
        cin >> password;
        if (!authenticateUser(username, password)) {
            cout << "\n\tAuthentication failed!";
            return 1;
        }
    } else {
        cout << "\n\tInvalid choice!";
        return 1;
    }

    ifstream read("id.txt");
    if (!read.fail()) {
        read >> ID;
    }
    read.close();

    while (true) {
        cout << "\n\n\t1. Add Task";
        cout << "\n\t2. See Tasks";
        cout << "\n\t3. Search Task";
        cout << "\n\t4. Delete Task";
        cout << "\n\t5. Logout";

        int choice;
        cout << "\n\tEnter choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            addTodoForUser(username);
            break;
        case 2:
            readDataForUser(username);
            break;
        case 3:
            searchDataForUser(username);
            break;
        case 4:
            deleteDataForUser(username);
            break;
        case 5:
            main(); 
            break;
        default:
            cout << "\n\tEnter a valid choice between 1 to 5.";
        }
    }
}
