#include "StudentDatabase.h"
#include <iostream>
#include <limits>
#include <iomanip>

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
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

void displayMainMenu() {
    std::cout << "\n=== STUDENT MARKS MANAGEMENT SYSTEM ===\n";
    std::cout << "1. Student Management\n";
    std::cout << "2. Course Management\n";
    std::cout << "3. Subject Management\n";
    std::cout << "4. Marks Management\n";
    std::cout << "5. Reports\n";
    std::cout << "6. System Administration\n";
    std::cout << "0. Exit\n";
    std::cout << "========================================\n";
}

void displayStudentMenu() {
    std::cout << "\n=== STUDENT MANAGEMENT ===\n";
    std::cout << "1. Add New Student\n";
    std::cout << "2. View All Students\n";
    std::cout << "3. Update Student Information\n";
    std::cout << "4. Delete Student\n";
    std::cout << "5. Search Student by Roll Number\n";
    std::cout << "0. Back to Main Menu\n";
    std::cout << "============================\n";
}

void displayCourseMenu() {
    std::cout << "\n=== COURSE MANAGEMENT ===\n";
    std::cout << "1. Add New Course\n";
    std::cout << "2. View All Courses\n";
    std::cout << "0. Back to Main Menu\n";
    std::cout << "========================\n";
}

void displaySubjectMenu() {
    std::cout << "\n=== SUBJECT MANAGEMENT ===\n";
    std::cout << "1. Add New Subject\n";
    std::cout << "2. View All Subjects\n";
    std::cout << "3. View Subjects by Course\n";
    std::cout << "0. Back to Main Menu\n";
    std::cout << "==========================\n";
}

void displayMarksMenu() {
    std::cout << "\n=== MARKS MANAGEMENT ===\n";
    std::cout << "1. Add/Update Marks\n";
    std::cout << "2. View All Marks\n";
    std::cout << "3. Update Marks\n";
    std::cout << "4. Delete Marks\n";
    std::cout << "0. Back to Main Menu\n";
    std::cout << "=======================\n";
}

void displayReportsMenu() {
    std::cout << "\n=== REPORTS ===\n";
    std::cout << "1. Student Report\n";
    std::cout << "2. Subject Report\n";
    std::cout << "3. Class Performance\n";
    std::cout << "4. Grade Distribution\n";
    std::cout << "0. Back to Main Menu\n";
    std::cout << "==================\n";
}

void displaySystemMenu() {
    std::cout << "\n=== SYSTEM ADMINISTRATION ===\n";
    std::cout << "1. Initialize Database\n";
    std::cout << "2. Database Status\n";
    std::cout << "0. Back to Main Menu\n";
    std::cout << "===========================\n";
}

void studentManagement(StudentDatabase& db) {
    int choice;
    do {
        clearScreen();
        displayStudentMenu();
        choice = getIntInput("Enter your choice: ");
        
        switch (choice) {
            case 1: {
                clearScreen();
                std::cout << "=== ADD NEW STUDENT ===\n";
                std::string rollNumber = getStringInput("Enter Roll Number: ");
                std::string name = getStringInput("Enter Student Name: ");
                std::string email = getStringInput("Enter Email (optional): ");
                std::string phone = getStringInput("Enter Phone (optional): ");
                std::string address = getStringInput("Enter Address (optional): ");
                
                if (db.addStudent(rollNumber, name, email, phone, address)) {
                    std::cout << "Student added successfully!\n";
                } else {
                    std::cout << "Failed to add student. Roll number might already exist.\n";
                }
                pauseScreen();
                break;
            }
            case 2: {
                clearScreen();
                std::cout << "=== ALL STUDENTS ===\n";
                std::vector<Student> students = db.getAllStudents();
                
                if (students.empty()) {
                    std::cout << "No students found!\n";
                } else {
                    std::cout << std::left << std::setw(8) << "ID" 
                              << std::setw(12) << "Roll No" 
                              << std::setw(25) << "Name" 
                              << std::setw(25) << "Email" 
                              << std::setw(15) << "Phone" << std::endl;
                    std::cout << std::string(85, '-') << std::endl;
                    
                    for (const auto& student : students) {
                        std::cout << std::left << std::setw(8) << student.student_id
                                  << std::setw(12) << student.roll_number
                                  << std::setw(25) << student.name
                                  << std::setw(25) << student.email
                                  << std::setw(15) << student.phone << std::endl;
                    }
                }
                pauseScreen();
                break;
            }
            case 3: {
                clearScreen();
                std::cout << "=== UPDATE STUDENT ===\n";
                int studentId = getIntInput("Enter Student ID: ");
                
                Student student = db.getStudentById(studentId);
                if (student.student_id == 0) {
                    std::cout << "Student not found!\n";
                } else {
                    std::cout << "Current Information:\n";
                    std::cout << "Name: " << student.name << "\n";
                    std::cout << "Roll Number: " << student.roll_number << "\n";
                    std::cout << "Email: " << student.email << "\n";
                    std::cout << "Phone: " << student.phone << "\n";
                    std::cout << "Address: " << student.address << "\n\n";
                    
                    std::string rollNumber = getStringInput("Enter new Roll Number (or press Enter to keep current): ");
                    std::string name = getStringInput("Enter new Name (or press Enter to keep current): ");
                    std::string email = getStringInput("Enter new Email (or press Enter to keep current): ");
                    std::string phone = getStringInput("Enter new Phone (or press Enter to keep current): ");
                    std::string address = getStringInput("Enter new Address (or press Enter to keep current): ");
                    
                    if (rollNumber.empty()) rollNumber = student.roll_number;
                    if (name.empty()) name = student.name;
                    if (email.empty()) email = student.email;
                    if (phone.empty()) phone = student.phone;
                    if (address.empty()) address = student.address;
                    
                    if (db.updateStudent(studentId, rollNumber, name, email, phone, address)) {
                        std::cout << "Student updated successfully!\n";
                    } else {
                        std::cout << "Failed to update student.\n";
                    }
                }
                pauseScreen();
                break;
            }
            case 4: {
                clearScreen();
                std::cout << "=== DELETE STUDENT ===\n";
                int studentId = getIntInput("Enter Student ID to delete: ");
                
                Student student = db.getStudentById(studentId);
                if (student.student_id == 0) {
                    std::cout << "Student not found!\n";
                } else {
                    std::cout << "Student to delete: " << student.name << " (" << student.roll_number << ")\n";
                    std::string confirm = getStringInput("Are you sure? (yes/no): ");
                    
                    if (confirm == "yes" || confirm == "YES") {
                        if (db.deleteStudent(studentId)) {
                            std::cout << "Student deleted successfully!\n";
                        } else {
                            std::cout << "Failed to delete student.\n";
                        }
                    } else {
                        std::cout << "Deletion cancelled.\n";
                    }
                }
                pauseScreen();
                break;
            }
            case 5: {
                clearScreen();
                std::cout << "=== SEARCH STUDENT ===\n";
                std::string rollNumber = getStringInput("Enter Roll Number: ");
                
                Student student = db.getStudentByRollNumber(rollNumber);
                if (student.student_id == 0) {
                    std::cout << "Student not found!\n";
                } else {
                    std::cout << "\nStudent Details:\n";
                    std::cout << "ID: " << student.student_id << "\n";
                    std::cout << "Roll Number: " << student.roll_number << "\n";
                    std::cout << "Name: " << student.name << "\n";
                    std::cout << "Email: " << student.email << "\n";
                    std::cout << "Phone: " << student.phone << "\n";
                    std::cout << "Address: " << student.address << "\n";
                    std::cout << "Admission Date: " << student.admission_date << "\n";
                }
                pauseScreen();
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Invalid choice! Please try again.\n";
                pauseScreen();
        }
    } while (choice != 0);
}

void courseManagement(StudentDatabase& db) {
    int choice;
    do {
        clearScreen();
        displayCourseMenu();
        choice = getIntInput("Enter your choice: ");
        
        switch (choice) {
            case 1: {
                clearScreen();
                std::cout << "=== ADD NEW COURSE ===\n";
                std::string courseCode = getStringInput("Enter Course Code: ");
                std::string courseName = getStringInput("Enter Course Name: ");
                int credits = getIntInput("Enter Credits: ");
                std::string department = getStringInput("Enter Department: ");
                
                if (db.addCourse(courseCode, courseName, credits, department)) {
                    std::cout << "Course added successfully!\n";
                } else {
                    std::cout << "Failed to add course. Course code might already exist.\n";
                }
                pauseScreen();
                break;
            }
            case 2: {
                clearScreen();
                std::cout << "=== ALL COURSES ===\n";
                std::vector<Course> courses = db.getAllCourses();
                
                if (courses.empty()) {
                    std::cout << "No courses found!\n";
                } else {
                    std::cout << std::left << std::setw(8) << "ID" 
                              << std::setw(12) << "Code" 
                              << std::setw(30) << "Course Name" 
                              << std::setw(8) << "Credits" 
                              << std::setw(20) << "Department" << std::endl;
                    std::cout << std::string(78, '-') << std::endl;
                    
                    for (const auto& course : courses) {
                        std::cout << std::left << std::setw(8) << course.course_id
                                  << std::setw(12) << course.course_code
                                  << std::setw(30) << course.course_name
                                  << std::setw(8) << course.credits
                                  << std::setw(20) << course.department << std::endl;
                    }
                }
                pauseScreen();
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Invalid choice! Please try again.\n";
                pauseScreen();
        }
    } while (choice != 0);
}

void subjectManagement(StudentDatabase& db) {
    int choice;
    do {
        clearScreen();
        displaySubjectMenu();
        choice = getIntInput("Enter your choice: ");
        
        switch (choice) {
            case 1: {
                clearScreen();
                std::cout << "=== ADD NEW SUBJECT ===\n";
                
                // Display available courses
                std::vector<Course> courses = db.getAllCourses();
                if (courses.empty()) {
                    std::cout << "No courses available. Please add a course first.\n";
                    pauseScreen();
                    break;
                }
                
                std::cout << "Available Courses:\n";
                for (const auto& course : courses) {
                    std::cout << course.course_id << ". " << course.course_name << " (" << course.course_code << ")\n";
                }
                
                int courseId = getIntInput("Enter Course ID: ");
                std::string subjectName = getStringInput("Enter Subject Name: ");
                int semester = getIntInput("Enter Semester: ");
                int maxMarks = getIntInput("Enter Maximum Marks: ");
                
                if (db.addSubject(subjectName, courseId, semester, maxMarks)) {
                    std::cout << "Subject added successfully!\n";
                } else {
                    std::cout << "Failed to add subject.\n";
                }
                pauseScreen();
                break;
            }
            case 2: {
                clearScreen();
                std::cout << "=== ALL SUBJECTS ===\n";
                std::vector<Subject> subjects = db.getAllSubjects();
                
                if (subjects.empty()) {
                    std::cout << "No subjects found!\n";
                } else {
                    std::cout << std::left << std::setw(8) << "ID" 
                              << std::setw(25) << "Subject Name" 
                              << std::setw(20) << "Course" 
                              << std::setw(8) << "Semester" 
                              << std::setw(10) << "Max Marks" << std::endl;
                    std::cout << std::string(71, '-') << std::endl;
                    
                    for (const auto& subject : subjects) {
                        std::cout << std::left << std::setw(8) << subject.subject_id
                                  << std::setw(25) << subject.subject_name
                                  << std::setw(20) << subject.course_name
                                  << std::setw(8) << subject.semester
                                  << std::setw(10) << subject.max_marks << std::endl;
                    }
                }
                pauseScreen();
                break;
            }
            case 3: {
                clearScreen();
                std::cout << "=== SUBJECTS BY COURSE ===\n";
                
                std::vector<Course> courses = db.getAllCourses();
                if (courses.empty()) {
                    std::cout << "No courses available.\n";
                    pauseScreen();
                    break;
                }
                
                std::cout << "Available Courses:\n";
                for (const auto& course : courses) {
                    std::cout << course.course_id << ". " << course.course_name << "\n";
                }
                
                int courseId = getIntInput("Enter Course ID: ");
                std::vector<Subject> subjects = db.getSubjectsByCourse(courseId);
                
                if (subjects.empty()) {
                    std::cout << "No subjects found for this course!\n";
                } else {
                    std::cout << "\nSubjects for " << subjects[0].course_name << ":\n";
                    std::cout << std::left << std::setw(8) << "ID" 
                              << std::setw(25) << "Subject Name" 
                              << std::setw(8) << "Semester" 
                              << std::setw(10) << "Max Marks" << std::endl;
                    std::cout << std::string(51, '-') << std::endl;
                    
                    for (const auto& subject : subjects) {
                        std::cout << std::left << std::setw(8) << subject.subject_id
                                  << std::setw(25) << subject.subject_name
                                  << std::setw(8) << subject.semester
                                  << std::setw(10) << subject.max_marks << std::endl;
                    }
                }
                pauseScreen();
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Invalid choice! Please try again.\n";
                pauseScreen();
        }
    } while (choice != 0);
}

void marksManagement(StudentDatabase& db) {
    int choice;
    do {
        clearScreen();
        displayMarksMenu();
        choice = getIntInput("Enter your choice: ");
        
        switch (choice) {
            case 1: {
                clearScreen();
                std::cout << "=== ADD/UPDATE MARKS ===\n";
                
                // Display students
                std::vector<Student> students = db.getAllStudents();
                if (students.empty()) {
                    std::cout << "No students available. Please add a student first.\n";
                    pauseScreen();
                    break;
                }
                
                std::cout << "Available Students:\n";
                for (const auto& student : students) {
                    std::cout << student.student_id << ". " << student.name << " (" << student.roll_number << ")\n";
                }
                
                int studentId = getIntInput("Enter Student ID: ");
                
                // Display subjects
                std::vector<Subject> subjects = db.getAllSubjects();
                if (subjects.empty()) {
                    std::cout << "No subjects available. Please add a subject first.\n";
                    pauseScreen();
                    break;
                }
                
                std::cout << "\nAvailable Subjects:\n";
                for (const auto& subject : subjects) {
                    std::cout << subject.subject_id << ". " << subject.subject_name 
                              << " (" << subject.course_name << ")\n";
                }
                
                int subjectId = getIntInput("Enter Subject ID: ");
                
                std::string examType;
                int examChoice;
                std::cout << "\nExam Types:\n";
                std::cout << "1. Midterm\n";
                std::cout << "2. Final\n";
                std::cout << "3. Practical\n";
                std::cout << "4. Assignment\n";
                examChoice = getIntInput("Enter Exam Type (1-4): ");
                
                switch (examChoice) {
                    case 1: examType = "Midterm"; break;
                    case 2: examType = "Final"; break;
                    case 3: examType = "Practical"; break;
                    case 4: examType = "Assignment"; break;
                    default: examType = "Midterm";
                }
                
                int marksObtained = getIntInput("Enter Marks Obtained: ");
                int maxMarks = getIntInput("Enter Maximum Marks: ");
                std::string examDate = getStringInput("Enter Exam Date (YYYY-MM-DD, or press Enter for today): ");
                
                if (examDate.empty()) {
                    examDate = db.getCurrentDate();
                }
                
                if (db.addMark(studentId, subjectId, examType, marksObtained, maxMarks, examDate)) {
                    std::cout << "Marks added/updated successfully!\n";
                } else {
                    std::cout << "Failed to add marks.\n";
                }
                pauseScreen();
                break;
            }
            case 2: {
                clearScreen();
                std::cout << "=== ALL MARKS ===\n";
                std::vector<Mark> marks = db.getAllMarks();
                
                if (marks.empty()) {
                    std::cout << "No marks found!\n";
                } else {
                    std::cout << std::left << std::setw(12) << "Roll No" 
                              << std::setw(20) << "Student" 
                              << std::setw(20) << "Subject" 
                              << std::setw(10) << "Exam" 
                              << std::setw(8) << "Marks" 
                              << std::setw(8) << "Max" 
                              << std::setw(10) << "Percent" 
                              << std::setw(6) << "Grade" << std::endl;
                    std::cout << std::string(94, '-') << std::endl;
                    
                    for (const auto& mark : marks) {
                        std::cout << std::left << std::setw(12) << mark.roll_number
                                  << std::setw(20) << mark.student_name
                                  << std::setw(20) << mark.subject_name
                                  << std::setw(10) << mark.exam_type
                                  << std::setw(8) << mark.marks_obtained
                                  << std::setw(8) << mark.max_marks
                                  << std::setw(10) << std::fixed << std::setprecision(1) << mark.percentage
                                  << std::setw(6) << mark.grade << std::endl;
                    }
                }
                pauseScreen();
                break;
            }
            case 3: {
                clearScreen();
                std::cout << "=== UPDATE MARKS ===\n";
                std::cout << "This feature requires mark ID. Please view all marks first.\n";
                
                int markId = getIntInput("Enter Mark ID to update: ");
                int newMarks = getIntInput("Enter new marks: ");
                
                if (db.updateMark(markId, newMarks)) {
                    std::cout << "Marks updated successfully!\n";
                } else {
                    std::cout << "Failed to update marks. Mark ID might not exist.\n";
                }
                pauseScreen();
                break;
            }
            case 4: {
                clearScreen();
                std::cout << "=== DELETE MARKS ===\n";
                int markId = getIntInput("Enter Mark ID to delete: ");
                
                std::string confirm = getStringInput("Are you sure? (yes/no): ");
                if (confirm == "yes" || confirm == "YES") {
                    if (db.deleteMark(markId)) {
                        std::cout << "Marks deleted successfully!\n";
                    } else {
                        std::cout << "Failed to delete marks. Mark ID might not exist.\n";
                    }
                } else {
                    std::cout << "Deletion cancelled.\n";
                }
                pauseScreen();
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Invalid choice! Please try again.\n";
                pauseScreen();
        }
    } while (choice != 0);
}

void reports(StudentDatabase& db) {
    int choice;
    do {
        clearScreen();
        displayReportsMenu();
        choice = getIntInput("Enter your choice: ");
        
        switch (choice) {
            case 1: {
                clearScreen();
                std::cout << "=== STUDENT REPORT ===\n";
                
                std::vector<Student> students = db.getAllStudents();
                if (students.empty()) {
                    std::cout << "No students available.\n";
                    pauseScreen();
                    break;
                }
                
                std::cout << "Available Students:\n";
                for (const auto& student : students) {
                    std::cout << student.student_id << ". " << student.name << " (" << student.roll_number << ")\n";
                }
                
                int studentId = getIntInput("Enter Student ID: ");
                db.printStudentReport(studentId);
                pauseScreen();
                break;
            }
            case 2: {
                clearScreen();
                std::cout << "=== SUBJECT REPORT ===\n";
                
                std::vector<Subject> subjects = db.getAllSubjects();
                if (subjects.empty()) {
                    std::cout << "No subjects available.\n";
                    pauseScreen();
                    break;
                }
                
                std::cout << "Available Subjects:\n";
                for (const auto& subject : subjects) {
                    std::cout << subject.subject_id << ". " << subject.subject_name << " (" << subject.course_name << ")\n";
                }
                
                int subjectId = getIntInput("Enter Subject ID: ");
                db.printSubjectReport(subjectId);
                pauseScreen();
                break;
            }
            case 3: {
                clearScreen();
                db.printClassPerformance();
                pauseScreen();
                break;
            }
            case 4: {
                clearScreen();
                db.printGradeDistribution();
                pauseScreen();
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Invalid choice! Please try again.\n";
                pauseScreen();
        }
    } while (choice != 0);
}

void systemAdministration(StudentDatabase& db) {
    int choice;
    do {
        clearScreen();
        displaySystemMenu();
        choice = getIntInput("Enter your choice: ");
        
        switch (choice) {
            case 1: {
                clearScreen();
                std::cout << "=== INITIALIZE DATABASE ===\n";
                std::cout << "This will create all necessary tables and insert sample data.\n";
                std::string confirm = getStringInput("Are you sure? (yes/no): ");
                
                if (confirm == "yes" || confirm == "YES") {
                    if (db.initializeDatabase()) {
                        std::cout << "Database initialized successfully!\n";
                    } else {
                        std::cout << "Failed to initialize database.\n";
                    }
                } else {
                    std::cout << "Initialization cancelled.\n";
                }
                pauseScreen();
                break;
            }
            case 2: {
                clearScreen();
                std::cout << "=== DATABASE STATUS ===\n";
                std::cout << "Database file: student_marks.db\n";
                std::cout << "Status: Connected\n";
                
                std::vector<Student> students = db.getAllStudents();
                std::vector<Course> courses = db.getAllCourses();
                std::vector<Subject> subjects = db.getAllSubjects();
                std::vector<Mark> marks = db.getAllMarks();
                
                std::cout << "\nRecords Summary:\n";
                std::cout << "Students: " << students.size() << "\n";
                std::cout << "Courses: " << courses.size() << "\n";
                std::cout << "Subjects: " << subjects.size() << "\n";
                std::cout << "Marks: " << marks.size() << "\n";
                pauseScreen();
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Invalid choice! Please try again.\n";
                pauseScreen();
        }
    } while (choice != 0);
}

int main() {
    StudentDatabase db;
    
    std::cout << "=== STUDENT MARKS MANAGEMENT SYSTEM ===\n";
    std::cout << "Initializing database...\n";
    
    if (!db.openDatabase()) {
        std::cerr << "Failed to open database. Exiting...\n";
        return 1;
    }
    
    std::cout << "Database connected successfully!\n";
    pauseScreen();
    
    int choice;
    do {
        clearScreen();
        displayMainMenu();
        choice = getIntInput("Enter your choice: ");
        
        switch (choice) {
            case 1:
                studentManagement(db);
                break;
            case 2:
                courseManagement(db);
                break;
            case 3:
                subjectManagement(db);
                break;
            case 4:
                marksManagement(db);
                break;
            case 5:
                reports(db);
                break;
            case 6:
                systemAdministration(db);
                break;
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
