#ifndef STUDENT_DATABASE_H
#define STUDENT_DATABASE_H

#include <sqlite3.h>
#include <string>
#include <vector>
#include <iostream>

struct Student {
    int student_id;
    std::string roll_number;
    std::string name;
    std::string email;
    std::string phone;
    std::string address;
    std::string admission_date;
};

struct Course {
    int course_id;
    std::string course_code;
    std::string course_name;
    int credits;
    std::string department;
};

struct Subject {
    int subject_id;
    std::string subject_name;
    int course_id;
    int semester;
    int max_marks;
    std::string course_name;
};

struct Mark {
    int mark_id;
    int student_id;
    int subject_id;
    std::string exam_type;
    int marks_obtained;
    int max_marks;
    std::string exam_date;
    std::string student_name;
    std::string subject_name;
    float percentage;
    std::string grade;
};

class StudentDatabase {
private:
    sqlite3* db;
    std::string dbName;
    
public:
    StudentDatabase(const std::string& filename = "student_marks.db");
    ~StudentDatabase();
    
    bool openDatabase();
    bool closeDatabase();
    bool initializeDatabase();
    
    // Student operations
    bool addStudent(const std::string& rollNumber, const std::string& name, 
                   const std::string& email, const std::string& phone, 
                   const std::string& address);
    bool updateStudent(int studentId, const std::string& rollNumber, 
                      const std::string& name, const std::string& email, 
                      const std::string& phone, const std::string& address);
    bool deleteStudent(int studentId);
    std::vector<Student> getAllStudents();
    Student getStudentById(int studentId);
    Student getStudentByRollNumber(const std::string& rollNumber);
    
    // Course operations
    bool addCourse(const std::string& courseCode, const std::string& courseName, 
                  int credits, const std::string& department);
    std::vector<Course> getAllCourses();
    
    // Subject operations
    bool addSubject(const std::string& subjectName, int courseId, int semester, int maxMarks);
    std::vector<Subject> getAllSubjects();
    std::vector<Subject> getSubjectsByCourse(int courseId);
    
    // Marks operations
    bool addMark(int studentId, int subjectId, const std::string& examType, 
                int marksObtained, int maxMarks, const std::string& examDate);
    bool updateMark(int markId, int marksObtained);
    bool deleteMark(int markId);
    std::vector<Mark> getAllMarks();
    std::vector<Mark> getMarksByStudent(int studentId);
    std::vector<Mark> getMarksBySubject(int subjectId);
    std::vector<Mark> getStudentResults(int studentId);
    
    // Report operations
    void printStudentReport(int studentId);
    void printSubjectReport(int subjectId);
    void printClassPerformance();
    void printGradeDistribution();
    
    // Utility functions
    bool executeSQL(const std::string& sql);
    int getLastInsertId();
    std::string getCurrentDate();
};

#endif // STUDENT_DATABASE_H
