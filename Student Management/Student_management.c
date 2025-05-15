#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100

// Structure to store student details
struct Student {
    int rollNo;
    char name[50];
    float marks;
};

// Function to save students to a binary file
void saveToFile(struct Student students[], int count) {
    FILE *file = fopen("students.dat", "wb");  // Open file for writing in binary mode
    if (file == NULL) {
        printf("Error opening file for saving!\n");
        return;
    }
    fwrite(&count, sizeof(int), 1, file);  // Write the number of students
    fwrite(students, sizeof(struct Student), count, file);  // Write all student records
    fclose(file);  // Close the file
    printf("Data saved successfully!\n");
}

// Function to load students from the binary file
void loadFromFile(struct Student students[], int *count) {
    FILE *file = fopen("students.dat", "rb");  // Open file for reading in binary mode
    if (file == NULL) {
        printf("No existing data found. Starting fresh.\n");
        return;
    }
    fread(count, sizeof(int), 1, file);  // Read the number of students
    fread(students, sizeof(struct Student), *count, file);  // Read all student records
    fclose(file);  // Close the file
    printf("Data loaded successfully!\n");
}

// Function to add a student
void addStudent(struct Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Student limit reached!\n");
        return;
    }

    char temp[20];  // Temporary string to store roll number as string

    // Take input for roll number as string to validate
    printf("Enter Roll Number: ");
    scanf("%s", temp);  // Read as string
    if (sscanf(temp, "%d", &students[*count].rollNo) != 1) {
        printf("Invalid roll number! Please enter numeric value.\n");
        while (getchar() != '\n');  // Clear input buffer
        return;
    }

    // Clear input buffer before reading name
    while (getchar() != '\n');

    // Read name including spaces
    printf("Enter Name: ");
    fgets(students[*count].name, sizeof(students[*count].name), stdin);
    students[*count].name[strcspn(students[*count].name, "\n")] = '\0'; // Remove newline

    // Read marks
    printf("Enter Marks: ");
    if (scanf("%f", &students[*count].marks) != 1) {
        printf("Invalid marks input!\n");
        while (getchar() != '\n');  // Clear buffer
        return;
    }

    (*count)++;  // Increase count

    // Save student data
    saveToFile(students, *count);

    printf("Student added and saved successfully!\n");
}

// Function to display all students
void displayStudents(struct Student students[], int count) {
    if (count == 0) {
        printf("No students to display!\n");
        return;
    }

    printf("\nStudent Records:\n");
    printf("Roll No\tName\t\tMarks\n");
    printf("---------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t\t%.2f\n", students[i].rollNo, students[i].name, students[i].marks);
    }
}

// Function to search for a student by roll number
void searchStudent(struct Student students[], int count) {
    int rollNo;
    printf("Enter Roll Number to search: ");
    scanf("%d", &rollNo);

    for (int i = 0; i < count; i++) {
        if (students[i].rollNo == rollNo) {
            printf("Student Found:\n");
            printf("Roll No: %d\n", students[i].rollNo);
            printf("Name: %s\n", students[i].name);
            printf("Marks: %.2f\n", students[i].marks);
            return;
        }
    }
    printf("Student with Roll No %d not found!\n", rollNo);
}

// Main function
int main() {
    struct Student students[MAX_STUDENTS];  // Array to store student records
    int count = 0;  // Number of students
    int choice;

    // Load students from file at startup
    loadFromFile(students, &count);

    while (1) {
        // Display menu
        printf("\nStudent Management System\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Process choice
        switch (choice) {
            case 1:
                addStudent(students, &count);
                break;
            case 2:
                displayStudents(students, count);
                break;
            case 3:
                searchStudent(students, count);
                break;
            case 4:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}
