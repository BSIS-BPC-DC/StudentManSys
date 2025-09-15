#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 50
#define MAX_GRADES 5

typedef struct Student {
    char name[NAME_LEN];
    int grades[MAX_GRADES];
    int grade_count;
    struct Student* next;
} Student;

Student* create_student(const char* name, int grades[], int grade_count) {
    Student* new_student = (Student*)malloc(sizeof(Student));
    if (!new_student) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    strncpy(new_student->name, name, NAME_LEN - 1);
    new_student->name[NAME_LEN - 1] = '\0';

    int i;
    for (i = 0; i < grade_count && i < MAX_GRADES; i++) {
        new_student->grades[i] = grades[i];
    }

    new_student->grade_count = grade_count;
    new_student->next = NULL;
    return new_student;
}

void add_student(Student** head, Student* new_student) {
    if (*head == NULL) {
        *head = new_student;
    } else {
        Student* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_student;
    }
}


void display_students(Student* head) {
    if (!head) {
        printf("No students to display.\n");
        return;
    }

    Student* current = head;
    while (current != NULL) {
        int sum = 0;
        int i;
        printf("\nName: %s\nGrades: ", current->name);
        for (i = 0; i < current->grade_count; i++) {
            printf("%d ", current->grades[i]);
            sum += current->grades[i];
        }
        printf("\nAverage: %.2f\n", (current->grade_count > 0) ? ((float)sum / current->grade_count) : 0);
        current = current->next;
    }
}

void search_student(Student* head, const char* name) {
    Student* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            int i;
            printf("\nStudent Found: %s\nGrades: ", current->name);
            for (i = 0; i < current->grade_count; i++) {
                printf("%d ", current->grades[i]);
            }
            printf("\n");
            return;
        }
        current = current->next;
    }
    printf("Student '%s' not found.\n", name);
}


void delete_student(Student** head, const char* name) {
    Student* current = *head;
    Student* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Student '%s' deleted.\n", name);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Student '%s' not found for deletion.\n", name);
}

void free_all(Student* head) {
    Student* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Student* student_list = NULL;
    int choice;

    while (1) {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        if (choice == 1) {
            char name[NAME_LEN];
            int grades[MAX_GRADES];
            int grade_count;
            int i;

            printf("Enter student name: ");
            fgets(name, NAME_LEN, stdin);
            name[strcspn(name, "\n")] = '\0';

            printf("Enter number of grades (max %d): ", MAX_GRADES);
            scanf("%d", &grade_count);
            if (grade_count > MAX_GRADES) grade_count = MAX_GRADES;

            printf("Enter %d grades: ", grade_count);
            for (i = 0; i < grade_count; i++) {
                scanf("%d", &grades[i]);
            }

            add_student(&student_list, create_student(name, grades, grade_count));

        } else if (choice == 2) {
            display_students(student_list);
        } else if (choice == 3) {
            char name[NAME_LEN];
            printf("Enter name to search: ");
            fgets(name, NAME_LEN, stdin);
            name[strcspn(name, "\n")] = '\0';
            search_student(student_list, name);
        } else if (choice == 4) {
            char name[NAME_LEN];
            printf("Enter name to delete: ");
            fgets(name, NAME_LEN, stdin);
            name[strcspn(name, "\n")] = '\0';
            delete_student(&student_list, name);
        } else if (choice == 5) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }

    free_all(student_list);
    return 0;
}
