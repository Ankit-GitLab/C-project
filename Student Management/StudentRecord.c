#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100

// Structure to store student details
struct Student {
    int rollNo;
    char name[50];
    float marks;
};

// Function to save students to a file
void saveToFile(struct Student students[], int count) {
    FILE *file = fopen("students.dat", "wb");
    if (file == NULL) {
        printf("Error opening file for saving!\n");
        return;
    }
    fwrite(&count, sizeof(int), 1, file); // Save the count of students
    fwrite(students, sizeof(struct Student), count, file); // Save the student array
    fclose(file);
    printf("Data saved successfully!\n");
}

// Function to load students from a file
void loadFromFile(struct Student students[], int *count) {
    FILE *file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("No existing data found. Starting fresh.\n");
        return;
    }
    fread(count, sizeof(int), 1, file); // Load the count of students
    fread(students, sizeof(struct Student), *count, file); // Load the student array
    fclose(file);
    printf("Data loaded successfully!\n");
}

// Function to add a student
void addStudent(struct Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Student limit reached!\n");
        return;
    }

    printf("Enter Roll Number: ");
    scanf("%d", &students[*count].rollNo);
    printf("Enter Name: ");
    scanf(" %[^\n]", students[*count].name); // To read string with spaces
    printf("Enter Marks: ");
    scanf("%f", &students[*count].marks);

    (*count)++;
    printf("Student added successfully!\n");
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

int main() {
    struct Student students[MAX_STUDENTS];
    int count = 0;
    int choice;

    // Load data from file at the start
    loadFromFile(students, &count);

    while (1) {
        printf("\nStudent Management System\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

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
                saveToFile(students, count);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}