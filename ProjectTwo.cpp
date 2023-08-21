#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Course {
    string courseNumber;
    string name;
    vector<string> prerequisites;
};

vector<string> tokenize(string s, string del = " ") {
    vector<string> stringArray;
    size_t start = 0;
    size_t end = s.find(del);

    while (end != string::npos) {
        stringArray.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }

    stringArray.push_back(s.substr(start, end - start));
    return stringArray;
}

vector<Course> LoadDataStructure() {
    ifstream fin("abcu.txt", ios::in);
    vector<Course> courses;
    string line;

    while (true) {
        getline(fin, line);

        if (line == "-1")
            break;

        Course course;
        vector<string> tokenizedInformation = tokenize(line, ",");

        course.courseNumber = tokenizedInformation[0];
        course.name = tokenizedInformation[1];

        for (size_t i = 2; i < tokenizedInformation.size(); ++i) {
            course.prerequisites.push_back(tokenizedInformation[i]);
        }

        courses.push_back(course);
    }

    fin.close();
    return courses;
}

void printCourse(Course course) {
    cout << "Course Number: " << course.courseNumber << endl;
    cout << "Course Name: " << course.name << endl;
    cout << "Prerequisites: ";

    for (const string& prerequisite : course.prerequisites) {
        cout << prerequisite << " ";
    }

    cout << "\n\n";
}

void printCourseList(vector<Course>& courses) {
    size_t n = courses.size();

    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t j = 0; j < n - i - 1; ++j) {
            if (courses[j].courseNumber > courses[j + 1].courseNumber) {
                swap(courses[j], courses[j + 1]);
            }
        }
    }

    for (size_t i = 0; i < n; ++i) {
        printCourse(courses[i]);
    }
}

void searchCourse(vector<Course>& courses) {
    size_t n = courses.size();
    string courseNumber;
    int f = 0;
    cout << "Enter courseNumber: ";
    cin >> courseNumber;

    for (size_t i = 0; i < n; ++i) {
        if (courses[i].courseNumber == courseNumber) {
            f = 1;
            printCourse(courses[i]);
            break;
        }
    }

    if (f == 0) {
        cout << "Course with the given course number not found.\n";
    }
}

int main() {
    vector<Course> courses;
    cout << "1. Load Data Structure\n";
    cout << "2. Print Course List\n";
    cout << "3. Print Course\n";
    cout << "4. Exit\n";

    int ch;

    do {
        cout << "\nEnter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1: courses = LoadDataStructure(); break;
            case 2: printCourseList(courses); break;
            case 3: searchCourse(courses); break;
            case 4: cout << "Exit\n"; break;
            default: cout << "Invalid Choice\n";
        }
    } while (ch != 4);

    return 0;
}
