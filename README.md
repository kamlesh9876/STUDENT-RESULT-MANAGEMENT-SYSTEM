# 📘 Student Result Management System
A C++ Console Application for Managing Student Records & Academic Results

---

## 🚀 Overview

The **Student Result Management System** is a simple yet powerful C++ console-based application that helps manage student records, marks, and results.  
It demonstrates:

- File handling  
- Data structures  
- Modular C++ design  
- CMake-based compilation  
- Beginner-friendly architecture  

Perfect for **students**, **beginners**, **mini-projects**, and **academic submissions**.

---

## ✨ Features

- ➕ Add new student  
- 🔍 Search student  
- ✏️ Update student info  
- 🗑️ Delete student  
- 📄 Display all students  
- 🧮 Auto calculation of total & percentage  
- 💾 SQL schema included (optional)  
- 🧱 Modular and clean C++ source files  
- 🖥️ Works on Windows, Linux, macOS  

---

## 🛠️ Tech Stack

- **C++17**
- **CMake**
- **File Handling**
- **SQL (Optional schema)**

---

## 📂 Project Structure

```
STUDENT-RESULT-MANAGEMENT-SYSTEM/
│
├── main.cpp
├── simple_main.cpp
├── StudentDatabase.cpp
├── StudentDatabase.h
├── database.sql
├── CMakeLists.txt
├── build.bat
├── run.bat
└── README.md
```

---

## ⚙️ How to Build & Run

### 🔹 Linux / macOS / WSL

```bash
git clone https://github.com/kamlesh9876/STUDENT-RESULT-MANAGEMENT-SYSTEM
cd STUDENT-RESULT-MANAGEMENT-SYSTEM

mkdir build
cd build
cmake ..
cmake --build .

./srms_simple   # or the generated executable
```

---

### 🔹 Windows

#### Option 1 — Visual Studio (Recommended)
- Open project folder in Visual Studio  
- It auto-detects `CMakeLists.txt`  
- Build → Run

#### Option 2 — Using `.bat` files
```
build.bat
run.bat
```

---

## 🧪 Sample Console Output

```
===== STUDENT RESULT MANAGEMENT SYSTEM =====
1. Add Student
2. Display All Students
3. Search Student
4. Delete Student
5. Update Student
0. Exit
Enter your choice:
```

---

## 🗄️ Database Schema (Optional)

```sql
CREATE TABLE students (
    roll_no INT PRIMARY KEY,
    name VARCHAR(100),
    mark1 INT,
    mark2 INT,
    mark3 INT
);
```

---

## 🧩 Future Enhancements

- Add CSV/JSON data storage  
- Integrate SQLite  
- GUI (Qt / Flutter / Web UI)  
- Export reports as PDF  
- Authentication system  
- Result analytics (graphs)  
- Add unit tests  

---

## 🤝 Contributing

Contributions, issues, and feature requests are welcome!  
Feel free to fork this repository and submit PRs.

---

## 📜 License

Licensed under the **MIT License**.

---

## 👨‍💻 Author

**Kamlesh Pawar**  
Developer • C++ • MERN • Android  
GitHub: [kamlesh9876](https://github.com/kamlesh9876)
