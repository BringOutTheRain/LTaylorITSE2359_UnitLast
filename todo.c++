#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <string>

using namespace std;

void saveState(queue<string>& taskQueue, stack<string>& completedStack) {
    ofstream queueFile("queue.txt");
    ofstream stackFile("stack.txt");

    while (!taskQueue.empty()) {
        queueFile << taskQueue.front() << endl;
        taskQueue.pop();
    }
    
    while (!completedStack.empty()) {
        stackFile << completedStack.top() << endl;
        completedStack.pop();
    }

    queueFile.close();
    stackFile.close();
}

void loadState(queue<string>& taskQueue, stack<string>& completedStack) {
    ifstream queueFile("queue.txt");
    ifstream stackFile("stack.txt");
    string task;

    while (getline(queueFile, task)) {
        taskQueue.push(task);
    }
    
    while (getline(stackFile, task)) {
        completedStack.push(task);
    }

    queueFile.close();
    stackFile.close();
}

int main() {
    queue<string> taskQueue;
    stack<string> completedStack;
    int choice;
    string task;

    loadState(taskQueue, completedStack);  // Load state from files at the start

    do {
        cout << "\nTo-Do List Menu:\n";
        cout << "1. Add a task\n";
        cout << "2. View next task\n";
        cout << "3. Complete a task\n";
        cout << "4. Undo a task\n";
        cout << "5. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // To handle the newline after input

        switch (choice) {
            case 1: // Add a task
                cout << "Enter task: ";
                getline(cin, task);
                taskQueue.push(task);
                break;

            case 2: // View next task
                if (!taskQueue.empty()) {
                    cout << "Next task: " << taskQueue.front() << endl;
                } else {
                    cout << "No tasks in the queue." << endl;
                }
                break;

            case 3: // Complete a task
                if (!taskQueue.empty()) {
                    cout << "Completing task: " << taskQueue.front() << endl;
                    completedStack.push(taskQueue.front());
                    taskQueue.pop();
                } else {
                    cout << "No tasks to complete." << endl;
                }
                break;

            case 4: // Undo a task
                if (!completedStack.empty()) {
                    cout << "Undoing task: " << completedStack.top() << endl;
                    taskQueue.push(completedStack.top());
                    completedStack.pop();
                } else {
                    cout << "No tasks to undo." << endl;
                }
                break;

            case 5: // Save and exit
                saveState(taskQueue, completedStack);  // Save state before exit
                cout << "State saved. Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
                break;
        }
    } while (choice != 5);

    return 0;
}
