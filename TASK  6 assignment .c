#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int studentID;
    char fullName[100];
    char batch[20];           
    char membership[10];       
    char regDate[20];         
    char dob[20];              
    char interest[10];        
} Student;

Student *db = NULL;
int count = 0, capacity = 0;

void loadDatabase(const char *filename);
void saveDatabase(const char *filename);
void addStudent(Student s, const char *filename);
void updateStudent(int id);
void deleteStudent(int id);
void displayAll();
int exists(int id);
void batchReport(const char *batchName);

void loadDatabase(const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) return;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    count = size / sizeof(Student);
    capacity = count + 10;

    db = malloc(capacity * sizeof(Student));
    fread(db, sizeof(Student), count, f);
    fclose(f);
}

void saveDatabase(const char *filename) {
    FILE *f = fopen(filename, "wb");
    if (!f) { printf("File write error!\n"); return; }
    fwrite(db, sizeof(Student), count, f);
    fclose(f);
}

int exists(int id) {
    for (int i = 0; i < count; i++)
        if (db[i].studentID == id) return 1;
    return 0;
}

void addStudent(Student s, const char *filename) {
    if (exists(s.studentID)) {
        printf("Error: Student ID already exists!\n");
        return;
    }

    if (count == capacity) {
        capacity += 10;
        db = realloc(db, capacity * sizeof(Student));
    }

    db[count++] = s;
    saveDatabase(filename);
    printf("Student added successfully.\n");
}

void updateStudent(int id) {
    for (int i = 0; i < count; i++) {
        if (db[i].studentID == id) {
            printf("Enter new Batch: ");
            scanf("%s", db[i].batch);

            printf("Enter new Membership (IEEE/ACM): ");
            scanf("%s", db[i].membership);

            saveDatabase("members.dat");
            printf("Record updated.\n");
            return;
        }
    }
    printf("Student not found!\n");
}

void deleteStudent(int id) {
    int found = -1;

    for (int i = 0; i < count; i++)
        if (db[i].studentID == id) found = i;

    if (found == -1) {
        printf("Record not found!\n");
        return;
    }

    for (int i = found; i < count - 1; i++)
        db[i] = db[i + 1];

    count--;
    saveDatabase("members.dat");
    printf("Record deleted.\n");
}

// ------------ Display All ---------------------
void displayAll() {
    printf("\n---- All Students ----\n");
    for (int i = 0; i < count; i++) {
        printf("%d | %s | %s | %s | %s | %s | %s\n",
               db[i].studentID, db[i].fullName, db[i].batch,
               db[i].membership, db[i].regDate,
               db[i].dob, db[i].interest);
    }
}

void batchReport(const char *batchName) {
    printf("\n---- %s Students ----\n", batchName);
    for (int i = 0; i < count; i++)
        if (strcmp(db[i].batch, batchName) == 0)
            printf("%d | %s | %s\n", db[i].studentID,
                   db[i].fullName, db[i].membership);
}

int main() {
    loadDatabase("members.dat");

    int choice;
    while (1) {
        printf("\n1.Add Student\n2.Update Student\n3.Delete Student\n4.View All\n5.Batch Report\n6.Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            Student s;
            printf("Enter ID: ");              scanf("%d", &s.studentID);
            printf("Full Name: ");             getchar(); fgets(s.fullName, 100, stdin);
            s.fullName[strcspn(s.fullName, "\n")] = 0;
            printf("Batch: ");                 scanf("%s", s.batch);
            printf("Membership: ");            scanf("%s", s.membership);
            printf("Reg Date: ");              scanf("%s", s.regDate);
            printf("DOB: ");                   scanf("%s", s.dob);
            printf("Interest: ");              scanf("%s", s.interest);

            addStudent(s, "members.dat");
        }
        else if (choice == 2) {
            int id;
            printf("Enter Student ID: ");
            scanf("%d", &id);
            updateStudent(id);
        }
        else if (choice == 3) {
            int id;
            printf("Enter Student ID: ");
            scanf("%d", &id);
            deleteStudent(id);
        }
        else if (choice == 4) {
            displayAll();
        }
        else if (choice == 5) {
            char b[20];
            printf("Enter Batch for report: ");
            scanf("%s", b);
            batchReport(b);
        }
        else if (choice == 6) {
            saveDatabase("members.dat");
            printf("Saved. Exiting...\n");
            break;
        }
    }

    free(db);
    return 0;
}

