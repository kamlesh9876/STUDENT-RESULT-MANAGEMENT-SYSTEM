#include "StudentDatabase.h"
#include <sstream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <map>

StudentDatabase::StudentDatabase(const std::string& filename) : dbName(filename), db(nullptr) {}

StudentDatabase::~StudentDatabase() {
    closeDatabase();
}

bool StudentDatabase::openDatabase() {
    int rc = sqlite3_open(dbName.c_str(), &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    return true;
}

bool StudentDatabase::closeDatabase() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
        return true;
    }
    return false;
}

bool StudentDatabase::initializeDatabase() {
    if (!openDatabase()) return false;
    
    // Read and execute the SQL schema file
    std::ifstream sqlFile("database.sql");
    if (!sqlFile.is_open()) {
        std::cerr << "Cannot open database.sql file" << std::endl;
        return false;
    }
    
    std::string sql((std::istreambuf_iterator<char>(sqlFile)),
                    std::istreambuf_iterator<char>());
    
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    
    return true;
}

bool StudentDatabase::executeSQL(const std::string& sql) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    
    return true;
}

int StudentDatabase::getLastInsertId() {
    return sqlite3_last_insert_rowid(db);
}

std::string StudentDatabase::getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(4) << (1900 + ltm->tm_year) << "-"
       << std::setw(2) << (1 + ltm->tm_mon) << "-"
       << std::setw(2) << ltm->tm_mday;
    return ss.str();
}

// Student operations
bool StudentDatabase::addStudent(const std::string& rollNumber, const std::string& name, 
                                const std::string& email, const std::string& phone, 
                                const std::string& address) {
    std::stringstream sql;
    sql << "INSERT INTO students (roll_number, name, email, phone, address) VALUES ('"
        << rollNumber << "', '" << name << "', '" << email << "', '" 
        << phone << "', '" << address << "');";
    
    return executeSQL(sql.str());
}

bool StudentDatabase::updateStudent(int studentId, const std::string& rollNumber, 
                                   const std::string& name, const std::string& email, 
                                   const std::string& phone, const std::string& address) {
    std::stringstream sql;
    sql << "UPDATE students SET roll_number='" << rollNumber << "', name='" << name
        << "', email='" << email << "', phone='" << phone << "', address='" << address
        << "' WHERE student_id=" << studentId << ";";
    
    return executeSQL(sql.str());
}

bool StudentDatabase::deleteStudent(int studentId) {
    std::stringstream sql;
    sql << "DELETE FROM students WHERE student_id=" << studentId << ";";
    return executeSQL(sql.str());
}

std::vector<Student> StudentDatabase::getAllStudents() {
    std::vector<Student> students;
    sqlite3_stmt* stmt;
    
    const char* sql = "SELECT * FROM students ORDER BY name;";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            Student student;
            student.student_id = sqlite3_column_int(stmt, 0);
            student.roll_number = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            student.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            student.email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            student.phone = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            student.address = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
            student.admission_date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
            students.push_back(student);
        }
    }
    
    sqlite3_finalize(stmt);
    return students;
}

Student StudentDatabase::getStudentById(int studentId) {
    Student student;
    sqlite3_stmt* stmt;
    
    std::stringstream sql;
    sql << "SELECT * FROM students WHERE student_id=" << studentId << ";";
    
    if (sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            student.student_id = sqlite3_column_int(stmt, 0);
            student.roll_number = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            student.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            student.email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            student.phone = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            student.address = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
            student.admission_date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
        }
    }
    
    sqlite3_finalize(stmt);
    return student;
}

Student StudentDatabase::getStudentByRollNumber(const std::string& rollNumber) {
    Student student;
    sqlite3_stmt* stmt;
    
    std::stringstream sql;
    sql << "SELECT * FROM students WHERE roll_number='" << rollNumber << "';";
    
    if (sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            student.student_id = sqlite3_column_int(stmt, 0);
            student.roll_number = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            student.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            student.email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            student.phone = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            student.address = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
            student.admission_date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
        }
    }
    
    sqlite3_finalize(stmt);
    return student;
}

// Course operations
bool StudentDatabase::addCourse(const std::string& courseCode, const std::string& courseName, 
                               int credits, const std::string& department) {
    std::stringstream sql;
    sql << "INSERT INTO courses (course_code, course_name, credits, department) VALUES ('"
        << courseCode << "', '" << courseName << "', " << credits << ", '" << department << "');";
    
    return executeSQL(sql.str());
}

std::vector<Course> StudentDatabase::getAllCourses() {
    std::vector<Course> courses;
    sqlite3_stmt* stmt;
    
    const char* sql = "SELECT * FROM courses ORDER BY course_name;";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            Course course;
            course.course_id = sqlite3_column_int(stmt, 0);
            course.course_code = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            course.course_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            course.credits = sqlite3_column_int(stmt, 3);
            course.department = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            courses.push_back(course);
        }
    }
    
    sqlite3_finalize(stmt);
    return courses;
}

// Subject operations
bool StudentDatabase::addSubject(const std::string& subjectName, int courseId, int semester, int maxMarks) {
    std::stringstream sql;
    sql << "INSERT INTO subjects (subject_name, course_id, semester, max_marks) VALUES ('"
        << subjectName << "', " << courseId << ", " << semester << ", " << maxMarks << ");";
    
    return executeSQL(sql.str());
}

std::vector<Subject> StudentDatabase::getAllSubjects() {
    std::vector<Subject> subjects;
    sqlite3_stmt* stmt;
    
    const char* sql = "SELECT s.*, c.course_name FROM subjects s "
                     "JOIN courses c ON s.course_id = c.course_id ORDER BY s.subject_name;";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            Subject subject;
            subject.subject_id = sqlite3_column_int(stmt, 0);
            subject.subject_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            subject.course_id = sqlite3_column_int(stmt, 2);
            subject.semester = sqlite3_column_int(stmt, 3);
            subject.max_marks = sqlite3_column_int(stmt, 4);
            subject.course_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
            subjects.push_back(subject);
        }
    }
    
    sqlite3_finalize(stmt);
    return subjects;
}

std::vector<Subject> StudentDatabase::getSubjectsByCourse(int courseId) {
    std::vector<Subject> subjects;
    sqlite3_stmt* stmt;
    
    std::stringstream sql;
    sql << "SELECT s.*, c.course_name FROM subjects s "
        << "JOIN courses c ON s.course_id = c.course_id "
        << "WHERE s.course_id = " << courseId << " ORDER BY s.subject_name;";
    
    if (sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            Subject subject;
            subject.subject_id = sqlite3_column_int(stmt, 0);
            subject.subject_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            subject.course_id = sqlite3_column_int(stmt, 2);
            subject.semester = sqlite3_column_int(stmt, 3);
            subject.max_marks = sqlite3_column_int(stmt, 4);
            subject.course_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
            subjects.push_back(subject);
        }
    }
    
    sqlite3_finalize(stmt);
    return subjects;
}

// Marks operations
bool StudentDatabase::addMark(int studentId, int subjectId, const std::string& examType, 
                             int marksObtained, int maxMarks, const std::string& examDate) {
    std::stringstream sql;
    sql << "INSERT OR REPLACE INTO marks (student_id, subject_id, exam_type, marks_obtained, max_marks, exam_date) "
        << "VALUES (" << studentId << ", " << subjectId << ", '" << examType << "', "
        << marksObtained << ", " << maxMarks << ", '" << examDate << "');";
    
    return executeSQL(sql.str());
}

bool StudentDatabase::updateMark(int markId, int marksObtained) {
    std::stringstream sql;
    sql << "UPDATE marks SET marks_obtained=" << marksObtained << " WHERE mark_id=" << markId << ";";
    
    return executeSQL(sql.str());
}

bool StudentDatabase::deleteMark(int markId) {
    std::stringstream sql;
    sql << "DELETE FROM marks WHERE mark_id=" << markId << ";";
    return executeSQL(sql.str());
}

std::vector<Mark> StudentDatabase::getAllMarks() {
    std::vector<Mark> marks;
    sqlite3_stmt* stmt;
    
    const char* sql = "SELECT * FROM student_results ORDER BY student_name, subject_name;";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            Mark mark;
            mark.student_id = sqlite3_column_int(stmt, 0);
            mark.roll_number = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            mark.student_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            mark.course_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            mark.subject_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            mark.semester = sqlite3_column_int(stmt, 5);
            mark.exam_type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
            mark.marks_obtained = sqlite3_column_int(stmt, 7);
            mark.max_marks = sqlite3_column_int(stmt, 8);
            mark.percentage = sqlite3_column_double(stmt, 9);
            mark.grade = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10));
            marks.push_back(mark);
        }
    }
    
    sqlite3_finalize(stmt);
    return marks;
}

std::vector<Mark> StudentDatabase::getMarksByStudent(int studentId) {
    std::vector<Mark> marks;
    sqlite3_stmt* stmt;
    
    std::stringstream sql;
    sql << "SELECT * FROM student_results WHERE student_id=" << studentId 
        << " ORDER BY subject_name, exam_type;";
    
    if (sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            Mark mark;
            mark.student_id = sqlite3_column_int(stmt, 0);
            mark.roll_number = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            mark.student_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            mark.course_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            mark.subject_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            mark.semester = sqlite3_column_int(stmt, 5);
            mark.exam_type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
            mark.marks_obtained = sqlite3_column_int(stmt, 7);
            mark.max_marks = sqlite3_column_int(stmt, 8);
            mark.percentage = sqlite3_column_double(stmt, 9);
            mark.grade = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10));
            marks.push_back(mark);
        }
    }
    
    sqlite3_finalize(stmt);
    return marks;
}

std::vector<Mark> StudentDatabase::getMarksBySubject(int subjectId) {
    std::vector<Mark> marks;
    sqlite3_stmt* stmt;
    
    std::stringstream sql;
    sql << "SELECT * FROM student_results WHERE subject_id=" << subjectId 
        << " ORDER BY student_name;";
    
    if (sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            Mark mark;
            mark.student_id = sqlite3_column_int(stmt, 0);
            mark.roll_number = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            mark.student_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            mark.course_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            mark.subject_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            mark.semester = sqlite3_column_int(stmt, 5);
            mark.exam_type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
            mark.marks_obtained = sqlite3_column_int(stmt, 7);
            mark.max_marks = sqlite3_column_int(stmt, 8);
            mark.percentage = sqlite3_column_double(stmt, 9);
            mark.grade = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10));
            marks.push_back(mark);
        }
    }
    
    sqlite3_finalize(stmt);
    return marks;
}

std::vector<Mark> StudentDatabase::getStudentResults(int studentId) {
    return getMarksByStudent(studentId);
}

// Report operations
void StudentDatabase::printStudentReport(int studentId) {
    Student student = getStudentById(studentId);
    if (student.student_id == 0) {
        std::cout << "Student not found!" << std::endl;
        return;
    }
    
    std::vector<Mark> marks = getStudentResults(studentId);
    
    std::cout << "\n=== STUDENT REPORT ===" << std::endl;
    std::cout << "Name: " << student.name << std::endl;
    std::cout << "Roll Number: " << student.roll_number << std::endl;
    std::cout << "Email: " << student.email << std::endl;
    std::cout << "Phone: " << student.phone << std::endl;
    std::cout << "Address: " << student.address << std::endl;
    std::cout << "Admission Date: " << student.admission_date << std::endl;
    std::cout << "\n=== MARKS ===" << std::endl;
    
    std::cout << std::left << std::setw(20) << "Subject" 
              << std::setw(10) << "Exam Type" 
              << std::setw(10) << "Marks" 
              << std::setw(10) << "Max Marks" 
              << std::setw(10) << "Percentage" 
              << std::setw(6) << "Grade" << std::endl;
    std::cout << std::string(66, '-') << std::endl;
    
    float totalPercentage = 0;
    int subjectCount = 0;
    
    for (const auto& mark : marks) {
        std::cout << std::left << std::setw(20) << mark.subject_name
                  << std::setw(10) << mark.exam_type
                  << std::setw(10) << mark.marks_obtained
                  << std::setw(10) << mark.max_marks
                  << std::setw(10) << std::fixed << std::setprecision(2) << mark.percentage
                  << std::setw(6) << mark.grade << std::endl;
        
        totalPercentage += mark.percentage;
        subjectCount++;
    }
    
    if (subjectCount > 0) {
        float avgPercentage = totalPercentage / subjectCount;
        std::string overallGrade;
        if (avgPercentage >= 90) overallGrade = "A+";
        else if (avgPercentage >= 80) overallGrade = "A";
        else if (avgPercentage >= 70) overallGrade = "B";
        else if (avgPercentage >= 60) overallGrade = "C";
        else if (avgPercentage >= 50) overallGrade = "D";
        else overallGrade = "F";
        
        std::cout << std::string(66, '-') << std::endl;
        std::cout << "Average Percentage: " << std::fixed << std::setprecision(2) << avgPercentage << "%" << std::endl;
        std::cout << "Overall Grade: " << overallGrade << std::endl;
    }
    
    std::cout << std::endl;
}

void StudentDatabase::printSubjectReport(int subjectId) {
    std::vector<Mark> marks = getMarksBySubject(subjectId);
    if (marks.empty()) {
        std::cout << "No marks found for this subject!" << std::endl;
        return;
    }
    
    std::cout << "\n=== SUBJECT REPORT ===" << std::endl;
    std::cout << "Subject: " << marks[0].subject_name << std::endl;
    std::cout << "Course: " << marks[0].course_name << std::endl;
    std::cout << "Semester: " << marks[0].semester << std::endl;
    std::cout << "\n=== STUDENT PERFORMANCE ===" << std::endl;
    
    std::cout << std::left << std::setw(15) << "Roll Number" 
              << std::setw(20) << "Student Name" 
              << std::setw(10) << "Exam Type" 
              << std::setw(10) << "Marks" 
              << std::setw(10) << "Percentage" 
              << std::setw(6) << "Grade" << std::endl;
    std::cout << std::string(71, '-') << std::endl;
    
    float totalPercentage = 0;
    int studentCount = 0;
    
    for (const auto& mark : marks) {
        std::cout << std::left << std::setw(15) << mark.roll_number
                  << std::setw(20) << mark.student_name
                  << std::setw(10) << mark.exam_type
                  << std::setw(10) << mark.marks_obtained
                  << std::setw(10) << std::fixed << std::setprecision(2) << mark.percentage
                  << std::setw(6) << mark.grade << std::endl;
        
        totalPercentage += mark.percentage;
        studentCount++;
    }
    
    if (studentCount > 0) {
        float avgPercentage = totalPercentage / studentCount;
        std::cout << std::string(71, '-') << std::endl;
        std::cout << "Class Average: " << std::fixed << std::setprecision(2) << avgPercentage << "%" << std::endl;
        std::cout << "Total Students: " << studentCount << std::endl;
    }
    
    std::cout << std::endl;
}

void StudentDatabase::printClassPerformance() {
    std::vector<Mark> marks = getAllMarks();
    if (marks.empty()) {
        std::cout << "No marks data available!" << std::endl;
        return;
    }
    
    std::cout << "\n=== CLASS PERFORMANCE REPORT ===" << std::endl;
    
    // Group by student
    std::map<int, std::vector<Mark>> studentMarks;
    for (const auto& mark : marks) {
        studentMarks[mark.student_id].push_back(mark);
    }
    
    std::cout << std::left << std::setw(15) << "Roll Number" 
              << std::setw(20) << "Student Name" 
              << std::setw(10) << "Subjects" 
              << std::setw(12) << "Avg Percentage" 
              << std::setw(6) << "Grade" << std::endl;
    std::cout << std::string(63, '-') << std::endl;
    
    for (const auto& pair : studentMarks) {
        float totalPercentage = 0;
        for (const auto& mark : pair.second) {
            totalPercentage += mark.percentage;
        }
        float avgPercentage = totalPercentage / pair.second.size();
        
        std::string overallGrade;
        if (avgPercentage >= 90) overallGrade = "A+";
        else if (avgPercentage >= 80) overallGrade = "A";
        else if (avgPercentage >= 70) overallGrade = "B";
        else if (avgPercentage >= 60) overallGrade = "C";
        else if (avgPercentage >= 50) overallGrade = "D";
        else overallGrade = "F";
        
        std::cout << std::left << std::setw(15) << pair.second[0].roll_number
                  << std::setw(20) << pair.second[0].student_name
                  << std::setw(10) << pair.second.size()
                  << std::setw(12) << std::fixed << std::setprecision(2) << avgPercentage
                  << std::setw(6) << overallGrade << std::endl;
    }
    
    std::cout << std::endl;
}

void StudentDatabase::printGradeDistribution() {
    std::vector<Mark> marks = getAllMarks();
    if (marks.empty()) {
        std::cout << "No marks data available!" << std::endl;
        return;
    }
    
    std::map<std::string, int> gradeCount;
    for (const auto& mark : marks) {
        gradeCount[mark.grade]++;
    }
    
    std::cout << "\n=== GRADE DISTRIBUTION ===" << std::endl;
    std::cout << std::left << std::setw(6) << "Grade" << std::setw(10) << "Count" << std::setw(15) << "Percentage" << std::endl;
    std::cout << std::string(31, '-') << std::endl;
    
    int total = marks.size();
    for (const auto& pair : gradeCount) {
        float percentage = (pair.second * 100.0) / total;
        std::cout << std::left << std::setw(6) << pair.first 
                  << std::setw(10) << pair.second 
                  << std::setw(14) << std::fixed << std::setprecision(1) << percentage << "%" << std::endl;
    }
    
    std::cout << std::string(31, '-') << std::endl;
    std::cout << "Total: " << total << " records" << std::endl;
    std::cout << std::endl;
}
