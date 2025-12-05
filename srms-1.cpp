#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring> // Required for string operations

using namespace std;

// ==========================================
// 1. Student Class Definition
// ==========================================
class Student {
private:
    // --- Identity ---
    char reg_no[20];        // Primary Key
    char name[50];
    
    // --- Personal Info ---
    char dob[15];
    char gender[10];
    char father_name[50];   //  Father Name
    char mother_name[50];  // Mother Name
    char email[50];
    char phone[15];

    // --- Academic Info ---
    char program[20];
    char section[10];
    int semester;
    float cgpa;

    // --- Extra Curricular ---
    char clubs[100];

public:
    // --- Function to Get Data from User ---
    void get_data() {
        cout << "\n=== Enter Student Details ===" << endl;
        
        // Clear input buffer to prevent skipping
        cin.ignore(0); 

        cout << "Enter Registration No : ";
        cin.getline(reg_no, 20);
        
        cout << "Enter Student Name    : ";
        cin.getline(name, 50);

        cout << "Enter Date of Birth   : ";
        cin.getline(dob, 15);

        cout << "Enter Gender          : ";
        cin.getline(gender, 10);

        cout << "Enter Program         : ";
        cin.getline(program, 20);
        
        cout << "Enter Section         : ";
        cin.getline(section, 10);

        cout << "Enter Semester (Int)  : ";
        cin >> semester;
        
        cout << "Enter CGPA (Float)    : ";
        cin >> cgpa;
        
        // CRITICAL: Consume the 'newline' character left by cin >>
        cin.ignore(); 

        cout << "Enter Phone Number    : ";
        cin.getline(phone, 15);

        cout << "Enter Email ID        : ";
        cin.getline(email, 50);

        // INPUTS 
        cout << "Enter Father's Name   : ";
        cin.getline(father_name, 50);

        cout << "Enter Mother's Name   : ";
        cin.getline(mother_name, 50);
        // ----------------------

        cout << "Enter Clubs           : ";
        cin.getline(clubs, 100);
        
        cout << endl;
    }

    // --- Function to Show Detailed View (Search) ---
    void show_detailed_data() const {
        cout << "\n------- Student Detailed Profile -------" << endl;
        cout << "Reg No      : " << reg_no << endl;
        cout << "Name        : " << name << endl;
        cout << "----------------------------------------" << endl;
        cout << "Program     : " << program << endl;
        cout << "Semester    : " << semester <<endl;
        cout << " | Section: " << section << endl;
        cout << "CGPA        : " << cgpa << endl;
        cout << "----------------------------------------" << endl;
        cout << "DOB         : " << dob << " (" << gender << ")" << endl;
        cout << "Father Name : " << father_name << endl;
        cout << "Mother Name : " << mother_name << endl;
        cout << "Phone       : " << phone << endl;
        cout << "Email       : " << email << endl;
        cout << "Clubs       : " << clubs << endl;
        cout << "----------------------------------------" << endl;
    }

    // --- Function to Show Row View (Table) ---
    void show_tabular_data() const {
        cout << left << setw(15) << reg_no
             << left << setw(20) << name
             << left << setw(10) << program
             << left << setw(5)  << semester
             << left << setw(8)  << fixed << setprecision(2) << cgpa 
             << left << setw(15) << phone << endl;
    }

    // --- Getter for ID ---
    const char* get_reg_no() const {
        return reg_no;
    }
};

// ==========================================
// 2. Function Prototypes
// ==========================================
void write_student();
void display_all();
void search_student(char* id);
void modify_student(char* id);
void delete_student(char* id);
void display_menu();

// ==========================================
// 3. Main Function
// ==========================================
int main() {
    display_menu();
    return 0;
}

// ==========================================
// 4. Function Implementations
// ==========================================

void display_menu() {
    int choice;
    char id_input[20];
    
    do {
        cout << "\n\n|=========== UNIVERSITY MANAGEMENT SYSTEM ===========|" << endl;
        cout << "  1. Add New Student                                  " << endl;
        cout << "  2. Display All Records (Table View)                 " << endl;
        cout << "  3. Search Student (Full Details)                    " << endl;
        cout << "  4. Modify Student Record                            " << endl;
        cout << "  5. Delete Student Record                            " << endl;
        cout << "  6. Exit                                             " << endl;
        cout << "======================================================" << endl;
        cout << "\nEnter your choice (1-6): ";
        
        if (!(cin >> choice)) { 
            cin.clear(); 
            cin.ignore(10000, '\n'); 
            choice = 0; 
        }
        cin.ignore(); // Consume the enter key

        switch (choice) {
            case 1: write_student(); break;
            case 2: display_all(); break;
            case 3:
                cout << "\nEnter Registration No to search: ";
                cin.getline(id_input, 20);
                search_student(id_input);
                break;
            case 4:
                cout << "\nEnter Registration No to modify: ";
                cin.getline(id_input, 20);
                modify_student(id_input);
                break;
            case 5:
                cout << "\nEnter Registration No to delete: ";
                cin.getline(id_input, 20);
                delete_student(id_input);
                break;
            case 6: cout << "\nExiting System. Goodbye!" << endl; break;
            default: cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);
}

void write_student() {
    Student st, temp;
    
    // 1. Get user input
    st.get_data();

    // 2. Check for Duplicate Registration Number
    ifstream inFile("university_db_v2.dat", ios::binary);
    bool duplicate = false;

    if (inFile) {
        while (inFile.read(reinterpret_cast<char*>(&temp), sizeof(Student))) {
            if (strcmp(temp.get_reg_no(), st.get_reg_no()) == 0) {
                duplicate = true;
                break;
            }
        }
        inFile.close();
    }

    // 3. Save or Reject
    if (duplicate) {
        cout << "\n A student with Registration No " << st.get_reg_no() << " already exists!" << endl;
    } else {
        ofstream outFile("university_db_v2.dat", ios::binary | ios::app); 
        outFile.write(reinterpret_cast<const char *>(&st), sizeof(Student));
        outFile.close();
        cout << "\n Student record added successfully!" << endl;
    }
}

void display_all() {
    Student st;
    ifstream inFile("university_db_v2.dat", ios::binary);

    if (!inFile) {
        cout << "\nNo records found (File does not exist yet)." << endl;
        return;
    }

    cout << "\n=========================================== STUDENT RECORDS TABLE ===========================================" << endl;
    cout << left << setw(15) << "Reg No"
         << left << setw(20) << "Name"
         << left << setw(10) << "Program"
         << left << setw(5)  << "Sem"
         << left << setw(8)  << "CGPA"
         << left << setw(15) << "Phone" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------" << endl;

    while (inFile.read(reinterpret_cast<char *>(&st), sizeof(Student))) {
        st.show_tabular_data();
    }
    inFile.close();
}

void search_student(char* id) {
    Student st;
    ifstream inFile("university_db_v2.dat", ios::binary);
    bool found = false;

    if (!inFile) { cout << "\nNo records found." << endl; return; }
    
    while (inFile.read(reinterpret_cast<char *>(&st), sizeof(Student))) {
        if (strcmp(st.get_reg_no(), id) == 0) {
            st.show_detailed_data();
            found = true;
            break;
        }
    }
    inFile.close();
    if (!found) cout << "\n No student found with Reg No: " << id << endl;
}

void modify_student(char* id) {
    Student st;
    fstream file("university_db_v2.dat", ios::binary | ios::in | ios::out);
    bool found = false;

    if (!file) { cout << "\nNo records found." << endl; return; }

    while (!file.eof()) {
        long pos = file.tellg(); 
        if (file.read(reinterpret_cast<char *>(&st), sizeof(Student))) {
            if (strcmp(st.get_reg_no(), id) == 0) {
                cout << "\n Enter New Details for " << id << ":" << endl;
                st.get_data(); 
                
                file.seekp(pos); 
                file.write(reinterpret_cast<char *>(&st), sizeof(Student));
                
                cout << "\n Record Updated!" << endl;
                found = true;
                break;
            }
        }
    }
    file.close();
    if (!found) cout << "\n No student found with Reg No: " << id << endl;
}

void delete_student(char* id) {
    Student st;
    ifstream inFile("university_db_v2.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary); 

    if (!inFile) { cout << "\nNo records found." << endl; return; }

    bool found = false;
    while (inFile.read(reinterpret_cast<char *>(&st), sizeof(Student))) {
        if (strcmp(st.get_reg_no(), id) != 0) {
            outFile.write(reinterpret_cast<char *>(&st), sizeof(Student));
        } else {
            found = true; 
        }
    }

    inFile.close();
    outFile.close();

    remove("university_db_v2.dat"); 
    rename("temp.dat", "university_db_v2.dat"); 

    if (found) cout << "\n Record Deleted!" << endl;
    else cout << "\n No student found with Reg No: " << id << endl;
}
