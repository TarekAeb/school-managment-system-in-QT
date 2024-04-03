# Student Management System on QT

This is a Student Management System developed using Qt in C++ (OOP) language, designed to provide a user-friendly interface and experience.

## Project Description

This application is released under the GPL3 license. Please refer to the LICENSE file provided in the project folder for more details. The primary objective of this project is to create a platform that facilitates users, including administrators, teachers, and students.

- **Administrator Functions:**
  - Create users (teachers, students).
  - Create courses and schedule them.
  - Control the system, including adding/removing teachers, students, courses, etc.
  - Update administrator's information. The default administrator ID is "0000000001" with the password "admin".

- **Teacher Functions:**
  - Assign marks to students based on assigned modules.
  - Update their own password.
  - Access a personalized dashboard.

- **Student Functions:**
  - View personal information.
  - Change permitted information (e.g., password).
  - Limited access for security reasons.

## How to Run

1. When running the application for the first time, it will prompt you to choose a password for data storage.
2. Replace the automatically created 'assets' folder with the one located in the repository.
3. To access the system:
   - Use ID: 0000000001
   - Password: "admin"

## User Manual

### System Credentials:

- Name: Must contain two words, each with more than three characters.
- ID: Must contain 10 digits.
- Phone: Must contain 10 digits, starting with 0 as per Algerian credentials.
- Email: Must be the Ensia email.
- Date: Must be of the format YYYY-MM-DD

Ensure compliance with these criteria while using the system.
