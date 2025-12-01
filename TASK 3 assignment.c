#include <stdio.h>
#include <string.h>

struct Employee {
    int id;
    char name[50];
    char designation[50];
    float salary;
};

void displayEmployees(struct Employee e[], int n) {
    printf("\n---------------------------------------------\n");
    printf(" ID\tName\t\tDesignation\tSalary\n");
    printf("---------------------------------------------\n");

    for(int i = 0; i < n; i++) {
        printf(" %d\t%-10s\t%-10s\t%.2f\n",
               e[i].id, e[i].name, e[i].designation, e[i].salary);
    }
    printf("---------------------------------------------\n");
}
void findHighestSalary(struct Employee e[], int n) {
    int index = 0;

    for(int i = 1; i < n; i++) {
        if(e[i].salary > e[index].salary)
            index = i;
    }

    printf("\nEmployee with Highest Salary:\n");
    printf("ID: %d\n", e[index].id);
    printf("Name: %s\n", e[index].name);
    printf("Designation: %s\n", e[index].designation);
    printf("Salary: %.2f\n", e[index].salary);
}

void searchEmployee(struct Employee e[], int n) {
    int choice;
    printf("\nSearch Employee:\n1. By ID\n2. By Name\nEnter choice: ");
    scanf("%d", &choice);

    if(choice == 1) {
        int id;
        printf("Enter Employee ID: ");
        scanf("%d", &id);

        for(int i = 0; i < n; i++) {
            if(e[i].id == id) {
                printf("\nRecord Found:\n");
                printf("ID: %d\n", e[i].id);
                printf("Name: %s\n", e[i].name);
                printf("Designation: %s\n", e[i].designation);
                printf("Salary: %.2f\n", e[i].salary);
                return;
            }
        }
        printf("No employee found with ID %d.\n", id);
    }

    else if(choice == 2) {
        char name[50];
        printf("Enter Employee Name: ");
        scanf("%s", name);

        for(int i = 0; i < n; i++) {
            if(strcmp(e[i].name, name) == 0) {
                printf("\nRecord Found:\n");
                printf("ID: %d\n", e[i].id);
                printf("Name: %s\n", e[i].name);
                printf("Designation: %s\n", e[i].designation);
                printf("Salary: %.2f\n", e[i].salary);
                return;
            }
        }
        printf("No employee found with name %s.\n", name);
    }

    else {
        printf("Invalid choice!\n");
    }
}

int main() {
    int n;
    printf("Enter number of employees: ");
    scanf("%d", &n);

    struct Employee emp[n];

    for(int i = 0; i < n; i++) {
        printf("\nEnter details of Employee %d:\n", i + 1);
        printf("ID: ");
        scanf("%d", &emp[i].id);
        printf("Name: ");
        scanf("%s", emp[i].name);
        printf("Designation: ");
        scanf("%s", emp[i].designation);
        printf("Salary: ");
        scanf("%f", &emp[i].salary);
    }

    displayEmployees(emp, n);

    findHighestSalary(emp, n);

    searchEmployee(emp, n);

    return 0;
}

