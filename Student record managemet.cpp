#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Define what a Student record looks like
struct Student {
    string id;
    string name;
    double gpa;
};

// Global filename for easy access
const string FILE_NAME = "students.txt";

// --- FILE OPERATIONS ---

// Save the entire vector of students back to the file
void saveToFile(const vector<Student>& students) {
    ofstream outFile(FILE_NAME);
    
    for (size_t i = 0; i < students.size(); i++) {
        outFile << students[i].id << " " 
                << students[i].name << " " 
                << students[i].gpa << endl;
    }
    outFile.close();
}

// Load all students from the file into our vector at startup
vector<Student> loadFromFile() {
    vector<Student> students;
    ifstream inFile(FILE_NAME);
    
    // If the file doesn't exist yet, just return an empty list
    if (!inFile) {
        return students;
    }

    Student s;
    // Read data row by row until the end of the file
    while (inFile >> s.id >> s.name >> s.gpa) {
        students.push_back(s);
    }
    
    inFile.close();
    return students;
}

// --- CORE FUNCTIONS ---

void addStudent(vector<Student>& students) {
    Student s;
    cout << "\nEnter Student ID (No spaces): ";
    cin >> s.id;
    cout << "Enter Student Name (No spaces): ";
    cin >> s.name;
    cout << "Enter Student GPA: ";
    cin >> s.gpa;

    students.push_back(s);
    saveToFile(students); // Save instantly
    cout << "Student added successfully!\n";
}

void displayRecords(const vector<Student>& students) {
    if (students.empty()) {
        cout << "\nNo records found.\n";
        return;
    }

    cout << "\n--- Student Records ---\n";
    for (size_t i = 0; i < students.size(); i++) {
        cout << "ID: " << students[i].id 
             << " | Name: " << students[i].name 
             << " | GPA: " << students[i].gpa << endl;
    }
}

void searchStudent(const vector<Student>& students) {
    string searchId;
    cout << "\nEnter Student ID to search: ";
    cin >> searchId;

    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].id == searchId) {
            cout << "\nRecord Found!\n";
            cout << "ID: " << students[i].id << "\nName: " << students[i].name << "\nGPA: " << students[i].gpa << endl;
            return;
        }
    }
    cout << "Student not found.\n";
}

void deleteStudent(vector<Student>& students) {
    string deleteId;
    cout << "\nEnter Student ID to delete: ";
    cin >> deleteId;

    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].id == deleteId) {
            // Remove student from vector
            students.erase(students.begin() + i); 
            saveToFile(students); // Save updated list
            cout << "Student deleted successfully.\n";
            return;
        }
    }
    cout << "Student not found.\n";
}

// --- SORTING (Bubble Sort) ---

void displayTopScorers(vector<Student> students) {
    if (students.empty()) {
        cout << "\nNo records to sort.\n";
        return;
    }

    // Classic Bubble Sort to sort by GPA descending (highest to lowest)
    for (size_t i = 0; i < students.size() - 1; i++) {
        for (size_t j = 0; j < students.size() - i - 1; j++) {
            if (students[j].gpa < students[j + 1].gpa) {
                // Swap the students
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    cout << "\n--- Top Scorers (Sorted by GPA) ---\n";
    displayRecords(students);
}

// --- MAIN MENU ---

int main() {
    // Load existing data at the start
    vector<Student> students = loadFromFile();
    int choice;

    while (true) {
        cout << "\n=== Student Record System ===\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Display Top Scorers\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) addStudent(students);
        else if (choice == 2) displayRecords(students);
        else if (choice == 3) searchStudent(students);
        else if (choice == 4) deleteStudent(students);
        else if (choice == 5) displayTopScorers(students);
        else if (choice == 6) {
            cout << "Goodbye!\n";
            break;
        } else {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}