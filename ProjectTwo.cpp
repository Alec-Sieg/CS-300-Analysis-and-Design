#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <sstream>

using namespace std;

// Course structure to hold course information
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
    
    // Default constructor
    Course() {}
    
    // Constructor
    Course(string number, string title) {
        courseNumber = number;
        courseTitle = title;
    }
};

// Hash table to store courses using unordered_map
class CourseHashTable {
private:
    unordered_map<string, Course> courseTable;
    
public:
    // Insert a course into the hash table
    void insert(const Course& course) {
        courseTable[course.courseNumber] = course;
    }
    
    // Search for a course by course number
    Course* search(const string& courseNumber) {
        auto it = courseTable.find(courseNumber);
        if (it != courseTable.end()) {
            return &(it->second);
        }
        return nullptr;
    }
    
    // Get all courses as a vector for sorting
    vector<Course> getAllCourses() {
        vector<Course> courses;
        for (const auto& pair : courseTable) {
            courses.push_back(pair.second);
        }
        return courses;
    }
    
    // Check if hash table is empty
    bool empty() const {
        return courseTable.empty();
    }
    
    // Clear all courses
    void clear() {
        courseTable.clear();
    }
    
    // Check if course exists
    bool exists(const string& courseNumber) {
        return courseTable.find(courseNumber) != courseTable.end();
    }
};

// Global hash table to store courses
CourseHashTable courses;

// Function to split a string by delimiter
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    
    while (getline(ss, token, delimiter)) {
        // Remove leading and trailing whitespace
        token.erase(0, token.find_first_not_of(" \t\r\n"));
        token.erase(token.find_last_not_of(" \t\r\n") + 1);
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    
    return tokens;
}

// Function to load course data from file
bool loadCourseData(const string& fileName) {
    ifstream file(fileName);
    
    if (!file.is_open()) {
        cout << "Error: Could not open file " << fileName << endl;
        return false;
    }
    
    // Clear existing courses
    courses.clear();
    
    // Temporary storage for validation
    vector<Course> tempCourses;
    string line;
    int lineNumber = 0;
    
    // Read file line by line
    while (getline(file, line)) {
        lineNumber++;
        
        // Skip empty lines
        if (line.empty()) {
            continue;
        }
        
        // Split line by comma
        vector<string> tokens = split(line, ',');
        
        // Check minimum required fields (course number and title)
        if (tokens.size() < 2) {
            cout << "Error on line " << lineNumber << ": Insufficient data. Need at least course number and title." << endl;
            file.close();
            return false;
        }
        
        // Create course object
        Course course(tokens[0], tokens[1]);
        
        // Add prerequisites if they exist
        for (size_t i = 2; i < tokens.size(); ++i) {
            if (!tokens[i].empty()) {
                course.prerequisites.push_back(tokens[i]);
            }
        }
        
        tempCourses.push_back(course);
    }
    
    file.close();
    
    // First pass: Add all courses to hash table
    for (const Course& course : tempCourses) {
        courses.insert(course);
    }
    
    // Second pass: Validate prerequisites exist
    for (const Course& course : tempCourses) {
        for (const string& prerequisite : course.prerequisites) {
            if (!courses.exists(prerequisite)) {
                cout << "Error: Prerequisite " << prerequisite << " for course " 
                     << course.courseNumber << " does not exist as a course." << endl;
                courses.clear();
                return false;
            }
        }
    }
    
    cout << "Successfully loaded " << tempCourses.size() << " courses." << endl;
    return true;
}

// Function to print all courses in alphanumeric order
void printCourseList() {
    if (courses.empty()) {
        cout << "No courses loaded. Please load course data first." << endl;
        return;
    }
    
    // Get all courses and sort them
    vector<Course> allCourses = courses.getAllCourses();
    
    // Sort courses by course number
    sort(allCourses.begin(), allCourses.end(), 
         [](const Course& a, const Course& b) {
             return a.courseNumber < b.courseNumber;
         });
    
    cout << "\nHere is a sample schedule:" << endl;
    cout << endl;
    
    // Print sorted course list
    for (const Course& course : allCourses) {
        cout << course.courseNumber << ", " << course.courseTitle << endl;
    }
    cout << endl;
}

// Function to print information for a specific course
void printCourseInfo(const string& courseNumber) {
    if (courses.empty()) {
        cout << "No courses loaded. Please load course data first." << endl;
        return;
    }
    
    // Convert input to uppercase for consistent searching
    string upperCourseNumber = courseNumber;
    transform(upperCourseNumber.begin(), upperCourseNumber.end(), 
              upperCourseNumber.begin(), ::toupper);
    
    Course* course = courses.search(upperCourseNumber);
    
    if (course == nullptr) {
        cout << "Course " << upperCourseNumber << " not found." << endl;
        return;
    }
    
    // Print course information
    cout << course->courseNumber << ", " << course->courseTitle << endl;
    
    // Print prerequisites if they exist
    if (!course->prerequisites.empty()) {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course->prerequisites.size(); ++i) {
            Course* prereq = courses.search(course->prerequisites[i]);
            if (prereq != nullptr) {
                cout << prereq->courseNumber << ", " << prereq->courseTitle;
                if (i < course->prerequisites.size() - 1) {
                    cout << "; ";
                }
            }
        }
        cout << endl;
    } else {
        cout << "No prerequisites" << endl;
    }
}

// Function to display menu
void displayMenu() {
    cout << "\nWelcome to the course planner." << endl;
    cout << endl;
    cout << "  1. Load Data Structure." << endl;
    cout << "  2. Print Course List." << endl;
    cout << "  3. Print Course." << endl;
    cout << "  9. Exit" << endl;
    cout << endl;
    cout << "What would you like to do? ";
}

// Function to get valid menu choice
int getMenuChoice() {
    string input;
    getline(cin, input);
    
    // Convert to integer
    try {
        return stoi(input);
    } catch (...) {
        return -1; // Invalid input
    }
}

// Main function
int main() {
    int choice;
    string fileName;
    string courseNumber;
    
    cout << "Welcome to the course planner." << endl;
    
    // Main program loop
    do {
        displayMenu();
        choice = getMenuChoice();
        
        switch (choice) {
            case 1:
                // Load data structure
                cout << "Enter file name: ";
                getline(cin, fileName);
                loadCourseData(fileName);
                break;
                
            case 2:
                // Print course list
                printCourseList();
                break;
                
            case 3:
                // Print course information
                cout << "What course do you want to know about? ";
                getline(cin, courseNumber);
                printCourseInfo(courseNumber);
                break;
                
            case 9:
                // Exit
                cout << "Thank you for using the course planner!" << endl;
                break;
                
            default:
                // Invalid choice
                cout << choice << " is not a valid option." << endl;
                break;
        }
        
    } while (choice != 9);
    
    return 0;
}