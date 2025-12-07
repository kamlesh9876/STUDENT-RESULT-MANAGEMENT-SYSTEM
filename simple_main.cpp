#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>

struct Student {
    int id;
    std::string rollNumber;
    std::string name;
    std::string email;
    std::string phone;
};

struct Course {
    int id;
    std::string code;
    std::string name;
    int credits;
};

struct Mark {
    int studentId;
    int courseId;
    std::string examType;
    int marksObtained;
    int maxMarks;
};

class SimpleStudentDatabase {
private:
    std::vector<Student> students;
    std::vector<Course> courses;
    std::vector<Mark> marks;
    int nextStudentId = 1;
    int nextCourseId = 1;

public:
    bool addStudent(const std::string& rollNumber, const std::string& name, 
                   const std::string& email, const std::string& phone) {
        // Check if roll number already exists
        for (const auto& student : students) {
            if (student.rollNumber == rollNumber) {
                return false;
            }
        }
        
        Student student;
        student.id = nextStudentId++;
        student.rollNumber = rollNumber;
        student.name = name;
        student.email = email;
        student.phone = phone;
        students.push_back(student);
        return true;
    }
    
    bool addCourse(const std::string& code, const std::string& name, int credits) {
        // Check if course code already exists
        for (const auto& course : courses) {
            if (course.code == code) {
                return false;
            }
        }
        
        Course course;
        course.id = nextCourseId++;
        course.code = code;
        course.name = name;
        course.credits = credits;
        courses.push_back(course);
        return true;
    }
    
    bool addMark(int studentId, int courseId, const std::string& examType, 
                int marksObtained, int maxMarks) {
        Mark mark;
        mark.studentId = studentId;
        mark.courseId = courseId;
        mark.examType = examType;
        mark.marksObtained = marksObtained;
        mark.maxMarks = maxMarks;
        marks.push_back(mark);
        return true;
    }
    
    void displayStudents() {
        std::cout << "\n=== STUDENTS ===\n";
        std::cout << std::left << std::setw(8) << "ID" 
                  << std::setw(12) << "Roll No" 
                  << std::setw(25) << "Name" 
                  << std::setw(25) << "Email" 
                  << std::setw(15) << "Phone" << std::endl;
        std::cout << std::string(85, '-') << std::endl;
        
        for (const auto& student : students) {
            std::cout << std::left << std::setw(8) << student.id
                      << std::setw(12) << student.rollNumber
                      << std::setw(25) << student.name
                      << std::setw(25) << student.email
                      << std::setw(15) << student.phone << std::endl;
        }
    }
    
    void displayCourses() {
        std::cout << "\n=== COURSES ===\n";
        std::cout << std::left << std::setw(8) << "ID" 
                  << std::setw(12) << "Code" 
                  << std::setw(30) << "Course Name" 
                  << std::setw(8) << "Credits" << std::endl;
        std::cout << std::string(58, '-') << std::endl;
        
        for (const auto& course : courses) {
            std::cout << std::left << std::setw(8) << course.id
                      << std::setw(12) << course.code
                      << std::setw(30) << course.name
                      << std::setw(8) << course.credits << std::endl;
        }
    }
    
    void displayMarks() {
        std::cout << "\n=== MARKS ===\n";
        std::cout << std::left << std::setw(12) << "Student ID" 
                  << std::setw(12) << "Course ID" 
                  << std::setw(10) << "Exam Type" 
                  << std::setw(8) << "Marks" 
                  << std::setw(8) << "Max" 
                  << std::setw(10) << "Percent" << std::endl;
        std::cout << std::string(60, '-') << std::endl;
        
        for (const auto& mark : marks) {
            float percentage = (mark.marksObtained * 100.0f) / mark.maxMarks;
            std::cout << std::left << std::setw(12) << mark.studentId
                      << std::setw(12) << mark.courseId
                      << std::setw(10) << mark.examType
                      << std::setw(8) << mark.marksObtained
                      << std::setw(8) << mark.maxMarks
                      << std::setw(10) << std::fixed << std::setprecision(1) << percentage << "%" << std::endl;
        }
    }
    
    void displayStudentReport(int studentId) {
        std::cout << "\n=== STUDENT REPORT ===\n";
        
        // Find student
        Student* student = nullptr;
        for (auto& s : students) {
            if (s.id == studentId) {
                student = &s;
                break;
            }
        }
        
        if (!student) {
            std::cout << "Student not found!\n";
            return;
        }
        
        std::cout << "Name: " << student->name << "\n";
        std::cout << "Roll Number: " << student->rollNumber << "\n";
        std::cout << "Email: " << student->email << "\n";
        std::cout << "Phone: " << student->phone << "\n\n";
        
        std::cout << "=== MARKS ===\n";
        std::cout << std::left << std::setw(12) << "Course ID" 
                  << std::setw(10) << "Exam Type" 
                  << std::setw(8) << "Marks" 
                  << std::setw(8) << "Max" 
                  << std::setw(10) << "Percent" << std::endl;
        std::cout << std::string(48, '-') << std::endl;
        
        float totalPercentage = 0;
        int markCount = 0;
        
        for (const auto& mark : marks) {
            if (mark.studentId == studentId) {
                float percentage = (mark.marksObtained * 100.0f) / mark.maxMarks;
                std::cout << std::left << std::setw(12) << mark.courseId
                          << std::setw(10) << mark.examType
                          << std::setw(8) << mark.marksObtained
                          << std::setw(8) << mark.maxMarks
                          << std::setw(10) << std::fixed << std::setprecision(1) << percentage << "%" << std::endl;
                totalPercentage += percentage;
                markCount++;
            }
        }
        
        if (markCount > 0) {
            float avgPercentage = totalPercentage / markCount;
            std::cout << std::string(48, '-') << std::endl;
            std::cout << "Average: " << std::fixed << std::setprecision(1) << avgPercentage << "%\n";
        }
    }
};

void clearScreen() {
    system("cls");
}

void pauseScreen() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

int getIntInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        } else {
            std::cout << "Invalid input. Please enter a valid integer.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

std::string getStringInput(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, value);
    return value;
}

int main() {
    SimpleStudentDatabase db;
    
    // Add sample data
    db.addStudent("CS001", "Alice Johnson", "alice@example.com", "1234567890");
    db.addStudent("IT002", "Bob Smith", "bob@example.com", "0987654321");
    db.addCourse("CS101", "Computer Science", 4);
    db.addCourse("IT201", "Information Technology", 4);
    db.addMark(1, 1, "Midterm", 85, 100);
    db.addMark(1, 1, "Final", 92, 100);
    db.addMark(2, 2, "Midterm", 88, 100);
    
    std::cout << "=== STUDENT MARKS MANAGEMENT SYSTEM ===\n";
    std::cout << "(Simple Version - In-Memory Database)\n\n";
    
    int choice;
    do {
        std::cout << "\n=== MAIN MENU ===\n";
        std::cout << "1. Add Student\n";
        std::cout << "2. Add Course\n";
        std::cout << "3. Add Marks\n";
        std::cout << "4. View Students\n";
        std::cout << "5. View Courses\n";
        std::cout << "6. View Marks\n";
        std::cout << "7. Student Report\n";
        std::cout << "0. Exit\n";
        std::cout << "================\n";
        
        choice = getIntInput("Enter your choice: ");
        
        switch (choice) {
            case 1: {
                clearScreen();
                std::cout << "=== ADD STUDENT ===\n";
                std::string rollNumber = getStringInput("Enter Roll Number: ");
                std::string name = getStringInput("Enter Student Name: ");
                std::string email = getStringInput("Enter Email: ");
                std::string phone = getStringInput("Enter Phone: ");
                
                if (db.addStudent(rollNumber, name, email, phone)) {
                    std::cout << "Student added successfully!\n";
                } else {
                    std::cout << "Failed to add student. Roll number might already exist.\n";
                }
                pauseScreen();
                break;
            }
            case 2: {
                clearScreen();
                std::cout << "=== ADD COURSE ===\n";
                std::string code = getStringInput("Enter Course Code: ");
                std::string name = getStringInput("Enter Course Name: ");
                int credits = getIntInput("Enter Credits: ");
                
                if (db.addCourse(code, name, credits)) {
                    std::cout << "Course added successfully!\n";
                } else {
                    std::cout << "Failed to add course. Course code might already exist.\n";
                }
                pauseScreen();
                break;
            }
            case 3: {
                clearScreen();
                std::cout << "=== ADD MARKS ===\n";
                int studentId = getIntInput("Enter Student ID: ");
                int courseId = getIntInput("Enter Course ID: ");
                std::string examType = getStringInput("Enter Exam Type (Midterm/Final/Practical): ");
                int marksObtained = getIntInput("Enter Marks Obtained: ");
                int maxMarks = getIntInput("Enter Maximum Marks: ");
                
                if (db.addMark(studentId, courseId, examType, marksObtained, maxMarks)) {
                    std::cout << "Marks added successfully!\n";
                } else {
                    std::cout << "Failed to add marks.\n";
                }
                pauseScreen();
                break;
            }
            case 4:
                clearScreen();
                db.displayStudents();
                pauseScreen();
                break;
            case 5:
                clearScreen();
                db.displayCourses();
                pauseScreen();
                break;
            case 6:
                clearScreen();
                db.displayMarks();
                pauseScreen();
                break;
            case 7: {
                clearScreen();
                int studentId = getIntInput("Enter Student ID: ");
                db.displayStudentReport(studentId);
                pauseScreen();
                break;
            }
            case 0:
                std::cout << "Thank you for using Student Marks Management System!\n";
                break;
            default:
                std::cout << "Invalid choice! Please try again.\n";
                pauseScreen();
        }
    } while (choice != 0);
    
    return 0;
}
