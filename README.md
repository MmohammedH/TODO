# TODO List Application

## Overview

This is a command-line TODO list application implemented in C++ that supports user authentication and authorization. Each user can manage their own TODO list securely. The application allows users to create accounts, log in, and manage their tasks.

## Features

- User account creation and login
- Add new tasks
- View existing tasks
- Search for specific tasks
- Delete tasks
- Separate TODO lists for different users

## Usage
Create an Account:

Choose the option to create an account.
Enter a username and password.
If the username already exists, you'll be prompted to choose a different one.
Log In:

Choose the option to log in.
Enter your username and password.
If the credentials are correct, you will be logged in and can manage your TODO list.
Manage Tasks:

Add Task: Enter new tasks which will be saved to your TODO list.
See Tasks: View all your current tasks.
Search Task: Search for a specific task by its ID.
Delete Task: Remove a task by its ID.
Logout:Choose the logout option to return to the main menu for re-login or account creation.

## File Structure
main.cpp: The main C++ source file containing the application logic.
users.txt: Stores user credentials (username and hashed password).
todo.txt: Stores user tasks (ID, username, task description).
id.txt: Keeps track of the next task ID to ensure uniqueness.
