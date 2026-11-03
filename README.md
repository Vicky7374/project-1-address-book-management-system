# 📖 Address Book Management System in C

**Developed by:** Vicky Kumar  
**ID:** 26018_442  
**Language:** C Programming

## 📌 Project Overview

The Address Book Management System is a menu-driven console application developed using the C programming language. It helps users manage contact information, including names, phone numbers, and email addresses.

The application supports creating, searching, editing, deleting, displaying, sorting, and saving contacts using file handling.

## ✨ Features

- **Create Contact:** Add a new contact with name, phone number, and email.
- **Search Contact:** Find contacts using name, phone number, or email.
- **Edit Contact:** Update existing contact information.
- **Delete Contact:** Delete a specific contact or all contacts.
- **List Contacts:** Display all contacts in a formatted table.
- **Sort Contacts:** Arrange contacts alphabetically by name using Bubble Sort.
- **File Storage:** Save contacts in a text file and retrieve them when the application starts.
- **Input Validation:** Validate names, phone numbers, and email addresses.

## 🛠️ Technologies and Concepts Used

- C Programming Language
- Structures and `typedef`
- Arrays and Pointers
- Functions and Modular Programming
- String Handling
- File Handling (`fopen`, `fprintf`, `fscanf`, `fclose`)
- Bubble Sort Algorithm
- Input Validation

## 📂 Project Structure

```text
Address-Book-Management-System/
│
├── main.c
├── contact.c
├── contact.h
├── file.c
├── file.h
├── contacts.txt
└── README.md
```
## 💾 File Handling

The project uses a text file named `contacts.txt` to maintain contact records.

- `saveContactsToFile()` writes the contact count and contact details into the file.
- `loadContactsFromFile()` retrieves previously saved contact records when the application starts.

## 📚 Challenges Faced

During development, I faced challenges in:

- Managing multiple contacts using an array of structures.
- Understanding how `typedef` works with structures.
- Writing and retrieving contact records using file handling.
- Sorting complete structure records without losing associated information.
- Implementing email and phone number validation.
- Handling input buffer issues while using input functions.

## 🎓 Learning Outcomes

This project helped me gain practical experience in:

- Applying structures and pointers in real-world applications.
- Understanding file storage and data retrieval.
- Implementing sorting and searching logic.
- Developing modular programs using functions.
- Handling user input and validating data.
- Improving logical thinking and problem-solving skills.

## 👨‍💻 Author

**Vicky Kumar**  
**ID:** 26018_442

---

*My first C programming project and an important step in my journey towards Embedded Systems and Firmware Development.*
