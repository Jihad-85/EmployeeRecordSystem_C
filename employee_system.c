#include <stdio.h>
#include <string.h>

const int MAX_EMP = 100;
const int MAX_NAME_LEN = 50;
const int MAX_POSi = 50;

//Structure Definition
typedef struct {
    int id;
    char name[50];
    char position[50];
    double salary;
} Employee;


Employee records[100];
int employee_count = 0;

//Function
void display_menu();
void add_employee();
void display_all();
void search_employee();
void update_employee();
void delete_employee();

void add_employee() {
    if (employee_count >= MAX_EMP) {
        printf("\n[Error] Maximum employee capacity reached.\n");
        return;
    }

    Employee new_emp;

    printf("\n--- Add New Employee ---\n");

    if (employee_count > 0) {
        new_emp.id = records[employee_count - 1].id + 1;
    } else {
        new_emp.id = 1001;
    }
    printf("Generated Employee ID: %d\n", new_emp.id);

    printf("Enter Name (No spaces): ");
    scanf("%s", new_emp.name);

    printf("Enter Position (No spaces): ");
    scanf("%s", new_emp.position);

    printf("Enter Salary: $");
    scanf("%lf", &new_emp.salary);


    records[employee_count] = new_emp;
    employee_count++;

    printf("\n[SUCCESS] Employee %s (ID: %d) added.\n", new_emp.name, new_emp.id);
}


void display_all() {
    printf("\n--- All Employee Records (%d) ---\n", employee_count);
    if (employee_count == 0) {
        printf("No records found.\n");
        return;
    }

    printf("+------+--------------------+--------------------+-----------+\n");
    printf("| ID   | Name               | Position           | Salary    |\n");
    printf("+------+--------------------+--------------------+-----------+\n");

    for (int i = 0; i < employee_count; i++) {
        printf("| %-4d | %-18s | %-18s | $%-8.2lf |\n",
               records[i].id,
               records[i].name,
               records[i].position,
               records[i].salary);
    }
    printf("+------+--------------------+--------------------+-----------+\n");
}


void search_employee() {
    int choice;
    printf("\n--- Search Employee ---\n");
    printf("Search by:\n1. ID\n2. Name (Exact Match)\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int search_id;
        printf("Enter Employee ID to search: ");
        scanf("%d", &search_id);

        printf("\nSearch Results:\n");
        int found = 0;
        for (int i = 0; i < employee_count; i++) {
            if (records[i].id == search_id) {
                printf("ID: %d, Name: %s, Position: %s, Salary: $%.2lf\n",
                       records[i].id, records[i].name, records[i].position, records[i].salary);
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("Employee with ID %d not found.\n", search_id);
        }

    } else if (choice == 2) {
        char search_name[MAX_NAME_LEN];
        printf("Enter EXACT Name to search (No spaces): ");
        scanf("%s", search_name);

        printf("\nSearch Results:\n");
        int found = 0;
        for (int i = 0; i < employee_count; i++) {
            // Use simple string comparison (strcmp)
            if (strcmp(records[i].name, search_name) == 0) {
                printf("ID: %d, Name: %s, Position: %s, Salary: $%.2lf\n",
                       records[i].id, records[i].name, records[i].position, records[i].salary);
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("Employee with name '%s' not found.\n", search_name);
        }
    } else {
        printf("[Error] Invalid choice.\n");
    }
}


void update_employee() {
    int search_id;
    printf("\n--- Update Employee Details ---\n");
    printf("Enter Employee ID to update: ");
    scanf("%d", &search_id);

    int index = -1;
    for (int i = 0; i < employee_count; i++) {
        if (records[i].id == search_id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("[Error] Employee with ID %d not found.\n", search_id);
        return;
    }

    printf("\nUpdating Employee: ID %d, Name: %s\n", records[index].id, records[index].name);

    printf("Enter NEW Name (No spaces) (Current: %s): ", records[index].name);
    scanf("%s", records[index].name);

    printf("Enter NEW Position (No spaces) (Current: %s): ", records[index].position);
    scanf("%s", records[index].position);

    printf("Enter NEW Salary (Current: $%.2lf): $", records[index].salary);
    scanf("%lf", &records[index].salary);

    printf("\n[SUCCESS] Employee ID %d details updated successfully.\n", search_id);
}


void delete_employee() {
    int search_id;
    printf("\n--- Delete Employee Record ---\n");
    printf("Enter Employee ID to delete: ");
    scanf("%d", &search_id);

    int index_to_delete = -1;


    for (int i = 0; i < employee_count; i++) {
        if (records[i].id == search_id) {
            index_to_delete = i;
            break;
        }
    }

    if (index_to_delete == -1) {
        printf("[Error] Employee with ID %d not found. Deletion failed.\n", search_id);
        return;
    }


    for (int i = index_to_delete; i < employee_count - 1; i++) {
        records[i] = records[i + 1];
    }


    employee_count--;

    printf("\n[SUCCESS] Employee ID %d successfully deleted.\n", search_id);
}


void display_menu() {
    printf("\n============================================\n");
    printf("       EMPLOYEE RECORD SYSTEM MENU          \n");
    printf("============================================\n");
    printf("1. Add New Employee\n");
    printf("2. Display All Records\n");
    printf("3. Search Employee (by ID or Name)\n");
    printf("4. Update Employee Details\n");
    printf("5. Delete Employee\n");
    printf("0. Exit\n");
    printf("--------------------------------------------\n");
    printf("Enter your choice: ");
}

//Main Program
int main() {
    int choice;

    do {
        display_menu();

        if (scanf("%d", &choice) != 1) {
            printf("\n[Error] Invalid input. Please enter a number.\n");
            choice = -1;
        }

        switch (choice) {
            case 1:
                add_employee();
                break;
            case 2:
                display_all();
                break;
            case 3:
                search_employee();
                break;
            case 4:
                update_employee();
                break;
            case 5:
                delete_employee();
                break;

            case 0:
                printf("\nExiting system.\n");
                break;
            default:
                if (choice != -1) {
                    printf("\n[Error] Invalid choice. Please try again.\n");
                }
                break;
        }
    } while (choice != 0);

    return 0;
}
