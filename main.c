#include <stdio.h>
#include <stdlib.h>
#define MAX_EMPLOYEES 100
struct Employee {
    int id;
    char name[50];
    char position[50];
    int salary;
};
struct Employee employees[MAX_EMPLOYEES];
int num_employees = 0;
void show_menu() {
    printf("\nEmployee Management Menu:\n");
    printf("1. Show all employees\n");
    printf("2. Enter a new employee\n");
    printf("3. Delete an employee by index\n");
    printf("4. Save to CSV file\n");
    printf("5. Exit\n");
}
void show_all_employees() {
    printf("\nList of all employees:\n");
    for (int i = 0; i < num_employees; i++) {
        printf("%d. %s (%s) - Salary: %d\n", employees[i].id, employees[i].name, employees[i].position, employees[i].salary);
    }
}
void enter_new_employee() {
    if (num_employees >= MAX_EMPLOYEES) {
        printf("Error: Cannot add more employees. Maximum number of employees reached.\n");
        return;
    }
    printf("\nEnter a new employee:\n");
    while (1) {
        printf("ID: ");
        if (scanf("%d", &employees[num_employees].id) == 1) {
            break;
        } else {
            printf("Error: Invalid input for ID. Please enter an integer.\n");
            while (getchar() != '\n');
        }
    }
    printf("Name: ");
    scanf("%49s", employees[num_employees].name);
    printf("Position: ");
    scanf("%49s", employees[num_employees].position);
    while (1) {
        printf("Salary: ");
        if (scanf("%d", &employees[num_employees].salary) == 1) {
            break;
        } else {
            printf("Error: Invalid input for salary. Please enter an integer.\n");
            while (getchar() != '\n');
        }
    }
    num_employees++;
}
void delete_employee_by_index() {
    int index;
    printf("Enter the index of the employee to delete: ");
    scanf("%d", &index);
    if (index < 0 || index >= num_employees) {
        printf("Error: Invalid index.\n");
        return;
    }
    for (int i = index; i < num_employees - 1; i++) {
        employees[i] = employees[i + 1];
    }
    num_employees--;
}
void save_to_csv() {
    FILE *fp = fopen("employees.csv", "w");
    if (fp == NULL) {
        printf("Error: Cannot open file for writing.\n");
        return;
    }
    fprintf(fp, "ID,Name,Position,Salary\n");
    for (int i = 0; i < num_employees; i++) {
        fprintf(fp, "%d,%s,%s,%d\n", employees[i].id, employees[i].name, employees[i].position, employees[i].salary);
    }
    fclose(fp);
    printf("Employee data saved to employees.csv\n");
}
void read_csv(const char* filename, struct Employee employees[], int max_employees) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Cannot open file for reading.\n");
        return;
    }
    char line[256];
    int row = 0;
    num_employees = 0;
    while (fgets(line, sizeof(line), fp) != NULL && row < max_employees) {
        sscanf(line, "%d,%[^,],%[^,],%d\n",
               &employees[row].id,
               employees[row].name,
               employees[row].position,
               &employees[row].salary);
        row++;
    }
    fclose(fp);
    num_employees = row;
}
int main() {
    read_csv("employees.csv", employees, MAX_EMPLOYEES);
    int choice;
    if (num_employees > 0) {
        for (int i = 0; i < num_employees - 1; i++) {
            employees[i] = employees[i + 1];
        }
        num_employees--;
    }
    while (1) {
        show_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                show_all_employees();
                break;
            case 2:
                enter_new_employee();
                break;
            case 3:
                delete_employee_by_index();
                break;
            case 4:
                save_to_csv();
                break;
            case 5:
                exit(0);
            default:
                printf("Error: Invalid choice.\n");
        }
    }
    return 0;
}