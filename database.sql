-- Student Marks Management System Database Schema
-- SQLite Database Structure

-- Create Students table
CREATE TABLE IF NOT EXISTS students (
    student_id INTEGER PRIMARY KEY AUTOINCREMENT,
    roll_number VARCHAR(20) UNIQUE NOT NULL,
    name VARCHAR(100) NOT NULL,
    email VARCHAR(100) UNIQUE,
    phone VARCHAR(20),
    address TEXT,
    admission_date DATE DEFAULT CURRENT_DATE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Create Courses table
CREATE TABLE IF NOT EXISTS courses (
    course_id INTEGER PRIMARY KEY AUTOINCREMENT,
    course_code VARCHAR(10) UNIQUE NOT NULL,
    course_name VARCHAR(100) NOT NULL,
    credits INTEGER NOT NULL DEFAULT 3,
    department VARCHAR(50),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Create Subjects table (linking courses to specific subjects/exams)
CREATE TABLE IF NOT EXISTS subjects (
    subject_id INTEGER PRIMARY KEY AUTOINCREMENT,
    subject_name VARCHAR(100) NOT NULL,
    course_id INTEGER NOT NULL,
    semester INTEGER NOT NULL,
    max_marks INTEGER NOT NULL DEFAULT 100,
    FOREIGN KEY (course_id) REFERENCES courses(course_id),
    UNIQUE(subject_name, course_id, semester)
);

-- Create Marks table
CREATE TABLE IF NOT EXISTS marks (
    mark_id INTEGER PRIMARY KEY AUTOINCREMENT,
    student_id INTEGER NOT NULL,
    subject_id INTEGER NOT NULL,
    exam_type VARCHAR(20) NOT NULL, -- 'Midterm', 'Final', 'Practical', 'Assignment'
    marks_obtained INTEGER NOT NULL,
    max_marks INTEGER NOT NULL,
    exam_date DATE DEFAULT CURRENT_DATE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (student_id) REFERENCES students(student_id),
    FOREIGN KEY (subject_id) REFERENCES subjects(subject_id),
    UNIQUE(student_id, subject_id, exam_type)
);

-- Create Results view for easy querying
CREATE VIEW IF NOT EXISTS student_results AS
SELECT 
    s.student_id,
    s.roll_number,
    s.name,
    c.course_name,
    sub.subject_name,
    sub.semester,
    m.exam_type,
    m.marks_obtained,
    m.max_marks,
    ROUND((m.marks_obtained * 100.0 / m.max_marks), 2) AS percentage,
    CASE 
        WHEN (m.marks_obtained * 100.0 / m.max_marks) >= 90 THEN 'A+'
        WHEN (m.marks_obtained * 100.0 / m.max_marks) >= 80 THEN 'A'
        WHEN (m.marks_obtained * 100.0 / m.max_marks) >= 70 THEN 'B'
        WHEN (m.marks_obtained * 100.0 / m.max_marks) >= 60 THEN 'C'
        WHEN (m.marks_obtained * 100.0 / m.max_marks) >= 50 THEN 'D'
        ELSE 'F'
    END AS grade
FROM students s
JOIN marks m ON s.student_id = m.student_id
JOIN subjects sub ON m.subject_id = sub.subject_id
JOIN courses c ON sub.course_id = c.course_id;

-- Insert sample data for testing
INSERT OR IGNORE INTO courses (course_code, course_name, credits, department) VALUES
('CS101', 'Computer Science', 4, 'Computer Science'),
('IT201', 'Information Technology', 4, 'Information Technology'),
('ME301', 'Mechanical Engineering', 4, 'Mechanical Engineering');

INSERT OR IGNORE INTO subjects (subject_name, course_id, semester, max_marks) VALUES
('Data Structures', 1, 1, 100),
('Algorithms', 1, 2, 100),
('Database Systems', 1, 3, 100),
('Web Development', 2, 1, 100),
('Network Security', 2, 2, 100),
('Thermodynamics', 3, 1, 100),
('Fluid Mechanics', 3, 2, 100);

INSERT OR IGNORE INTO students (roll_number, name, email, phone, address) VALUES
('CS001', 'Alice Johnson', 'alice@example.com', '1234567890', '123 Main St'),
('IT002', 'Bob Smith', 'bob@example.com', '0987654321', '456 Oak Ave'),
('ME003', 'Charlie Brown', 'charlie@example.com', '1122334455', '789 Pine Rd');

-- Insert sample marks
INSERT OR IGNORE INTO marks (student_id, subject_id, exam_type, marks_obtained, max_marks, exam_date) VALUES
(1, 1, 'Midterm', 85, 100, '2024-01-15'),
(1, 1, 'Final', 92, 100, '2024-05-20'),
(1, 2, 'Midterm', 78, 100, '2024-02-10'),
(2, 4, 'Midterm', 88, 100, '2024-01-20'),
(2, 4, 'Final', 95, 100, '2024-05-25'),
(3, 6, 'Midterm', 72, 100, '2024-01-25'),
(3, 6, 'Final', 81, 100, '2024-05-30');
