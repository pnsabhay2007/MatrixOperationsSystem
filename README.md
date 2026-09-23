# Matrix Operations System

A C++ application that performs core matrix computations — addition, subtraction, multiplication, transpose, determinant, adjoint, inverse, and rank — built with proper Object-Oriented Programming principles and delivered through an interactive web interface.

Built as a Cornerstone Project for the OOP (C++) course at Aditya University.

---

## Features

- **Full matrix operation suite**: addition, subtraction, multiplication, transpose, determinant, adjoint, inverse, and rank
- **Web interface**: enter matrices and view results directly in the browser — no console needed
- **Interactive console demo**: menu-driven terminal program for demonstrating each module individually
- **Exception handling**: gracefully catches dimension mismatches and singular matrices instead of crashing
- **Clean architecture**: the C++ computation engine is completely decoupled from the web layer

---

## Tech Stack

| Layer | Technology |
|---|---|
| Core Engine | C++17 |
| Web Server | [cpp-httplib](https://github.com/yhirose/cpp-httplib) |
| Frontend | HTML, CSS, JavaScript |
| Compiler | MinGW-w64 (g++) |

---

## Project Structure

```
MatrixOperationsSystem/
├── src/
│   ├── Matrix.h            # Matrix class declaration
│   ├── Matrix.cpp           # Matrix class implementation
│   ├── server.cpp            # C++ web server (bridges engine to browser)
│   ├── console_demo.cpp       # Interactive terminal demo, menu-driven
│   ├── test_console.cpp        # Standalone console test
│   └── httplib.h                # Third-party HTTP server library
└── web/
    ├── index.html         # Landing page
    ├── app.html            # Matrix operations tool
    ├── style.css            # Styling
    ├── script.js             # Frontend logic (talks to the C++ server)
    └── rain.js                # Landing page animation
```

---

## Getting Started

### Prerequisites
- A C++ compiler supporting C++17 (e.g., MinGW-w64 / g++)

### Build & Run the Web App

```bash
cd src
g++ -std=c++17 -O2 -pthread Matrix.cpp server.cpp -o server.exe -lws2_32
.\server.exe
```

Then open `http://localhost:8080` in your browser.

### Build & Run the Console Demo

```bash
cd src
g++ -std=c++17 -O2 Matrix.cpp console_demo.cpp -o console_demo.exe
.\console_demo.exe
```

---

## Architecture

```
Browser (HTML/CSS/JS)
        |  JSON over HTTP (fetch)
        v
C++ Web Server (cpp-httplib)
        |  direct function calls
        v
Matrix Engine (pure C++ classes)
```

The Matrix engine has zero knowledge of the web layer — it can be (and is) tested entirely on the console, independent of the server.

---

## OOP Concepts Demonstrated

- **Encapsulation** — private matrix data, accessed only through safe public methods
- **Operator Overloading** — `A + B`, `A - B`, `A * B` work directly on Matrix objects
- **Constructors** — size-based and values-based construction
- **Exception Handling** — `std::invalid_argument` and `std::runtime_error` for invalid operations
- **Abstraction** — complex algorithms (cofactor expansion, row reduction) hidden behind simple method calls

---

## Team

| Name | Roll No. | Branch |
|---|---|---|
| P. Namrath Sai Abhay | 25B11CS687 | CSE |
| V. Rajeev | 25B11CSA12 | CSE |
| K. Sri Koushik | 25B11DS221 | DS |
| N. Mokshith Abhinav | 25B11DS388 | DS |

**Guided by:** Kalyani Mam, Assistant Professor (AIML)

---

## License

This project was developed for academic purposes as part of the Cornerstone Project curriculum at Aditya University.
