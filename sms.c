#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#include <windows.h>

#define MAX 100

struct Student {
    char name[100];
    char dept[50];
    int roll;
    float sgpa[12];
    float cgpa;
};

struct Attendance {
    int roll;
    int daysPresent;
    int totalDays;
};

struct Password {
    char pass[25];
};

struct Password pa;
FILE *fp, *tp;

void title();
void addStudent(FILE * fp);
void modifyStudent(FILE * fp);
void displayStudents(FILE * fp);
void individualView(FILE * fp);
void removeStudent(FILE * fp);
void changePassword();
void searchByName(FILE * fp);
void sortByCGPA(FILE * fp);
void addAttendance(FILE * fp);
void displayAttendance();
void displayMenu();
bool isValidRoll(int roll);
bool isUniqueRoll(int roll, FILE *fp);
bool isValidSGPA(float sgpa);
void encryptDecrypt(char *data);
FILE* openFile(char *fileName, char *mode);
void safeFileWrite(const char *filename, const void *data, size_t size);
void printChar(char ch, int n);

int main() {
	
    int option;
    char another;
    char pas[25];

    fp = openFile("students.txt", "ab+");
    tp = openFile("Password.txt", "r+b");
mains:
    SetConsoleTitle("Student Management System | DIU");
    fread(&pa, sizeof(pa), 1, tp);
    encryptDecrypt(pa.pass);  
    system("cls");
    title();
    printf("\n\n\t\t\tEnter Password: ");
    fgets(pas, 25, stdin);
    pas[strlen(pas) - 1] = '\0';

    if (strcmp(pas, pa.pass) == 0) {
        while (1) {
            displayMenu();
            scanf("%d", &option);
            switch (option) {
                case 1: addStudent(fp); break;
                case 2: modifyStudent(fp); break;
                case 3: displayStudents(fp); break;
                case 4: individualView(fp); break;
                case 5: removeStudent(fp); break;
                case 6: changePassword(); break;
                case 7: searchByName(fp); break;
                case 8: sortByCGPA(fp); break;
                case 9: addAttendance(fp); break;
                case 10: displayAttendance(); break;
                case 11: fclose(fp); fclose(tp); exit(0);
                default: printf("\nInvalid Option.\n"); break;
            }
        }
    } else {
        printf("\nIncorrect Password.\n");
        system("pause");
        goto mains;
//        return 1;
    }
}

void title() {
    system("cls");
    system("COLOR 03");
    printf("\n\t\t\t--------------------------------------------------");
    printf("\n\t\t\t\t\t  Student Management System");
    printf("\n\t\t\t--------------------------------------------------");
}

void displayMenu() {
    title();
    printf("\n\t");
    printChar('*', 64);
    printf("\n\n\t\t\t\t1. Add Student");
    printf("\n\n\t\t\t\t2. Modify Student");
    printf("\n\n\t\t\t\t3. Show All Students");
    printf("\n\n\t\t\t\t4. Individual View");
    printf("\n\n\t\t\t\t5. Remove Student");
    printf("\n\n\t\t\t\t6. Change Password");
    printf("\n\n\t\t\t\t7. Search Student by Name");
    printf("\n\n\t\t\t\t8. Sort Students by CGPA");
    printf("\n\n\t\t\t\t9. Add Attendance");
    printf("\n\n\t\t\t\t10. Display Attendance");
    printf("\n\n\t\t\t\t11. Logout\n\t");
    printChar('*', 64);
    printf("\n\n\t\t\t\tEnter Your Option :--> ");
}

bool isValidRoll(int roll) {
    return roll > 0;
}

bool isUniqueRoll(int roll, FILE *fp) {
    struct Student s;
    rewind(fp);
    while (fread(&s, sizeof(s), 1, fp) == 1) {
        if (s.roll == roll) {
            return false;
        }
    }
    return true;
}

bool isValidSGPA(float sgpa) {
    return sgpa >= 0.0 && sgpa <= 10.0;
}

void encryptDecrypt(char *data) {
    char key = 'K';
    int i;
    for ( i = 0; i < strlen(data); i++) {
        data[i] ^= key;
    }
}

FILE* openFile(char *fileName, char *mode) {
    FILE *fp = fopen(fileName, mode);
    if (fp == NULL) {
        printf("Error opening file: %s\n", fileName);
        exit(1);
    }
    return fp;
}

void safeFileWrite(const char *filename, const void *data, size_t size) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Error opening file for writing: %s\n", filename);
        return;
    }
    if (fwrite(data, size, 1, fp) != 1) {
        printf("Error writing to file: %s\n", filename);
    }
    fclose(fp);
}

void printChar(char ch, int n) {
	int i;
    for (i = 0; i < n; i++) {
        putchar(ch);
    }
    putchar('\n');
}

void addStudent(FILE * fp) {
    title();
    char another = 'y';
    struct Student s;
    int i;
    float cgpa;
    fseek(fp, 0, SEEK_END);
    while (another == 'y' || another == 'Y') {
        printf("\n\n\t\tEnter Full Name of Student: ");
        fflush(stdin);
        fgets(s.name, 100, stdin);
        s.name[strlen(s.name) - 1] = '\0';
        printf("\n\n\t\tEnter Department Name: ");
        fflush(stdin);
        fgets(s.dept, 50, stdin);
        s.dept[strlen(s.dept) - 1] = '\0';
        do {
            printf("\n\n\t\tEnter Roll number: ");
            scanf("%d", &s.roll);
            if (!isValidRoll(s.roll) || !isUniqueRoll(s.roll, fp)) {
                printf("\nInvalid or duplicate roll number. Please enter a positive unique number.\n");
            }
        } while (!isValidRoll(s.roll) || !isUniqueRoll(s.roll, fp));
        printf("\n\n\tEnter SGPA for 12 semesters\n");
        for (i = 0, cgpa = 0; i < 12; i++) {
            do {
                printf("\tSemester %d: ", i + 1);
                scanf("%f", &s.sgpa[i]);
                if (!isValidSGPA(s.sgpa[i])) {
                    printf("\nInvalid SGPA. Please enter a value between 0 and 10.\n");
                }
            } while (!isValidSGPA(s.sgpa[i]));
            cgpa += s.sgpa[i];
        }
        cgpa /= 12.0;
        s.cgpa = cgpa;
        fwrite(&s, sizeof(s), 1, fp);
        printf("\n\n\t\tAdd another student? (Y/N)? ");
        fflush(stdin);
        another = getchar();
    }
}

void modifyStudent(FILE * fp) {
    title();
    struct Student s;
    int roll, flag = 0, siz = sizeof(s) , i;
    FILE *ft = openFile("temp.txt", "wb");
    float cgpa;
    printf("\n\n\tEnter Roll Number of Student to Modify: ");
    scanf("%d", &roll);
    rewind(fp);
    while ((fread(&s, siz, 1, fp)) == 1) {
        if (s.roll == roll) {
            flag = 1;
        }
        else {
            fwrite(&s, siz, 1, ft);
        }
    }
    fclose(fp);
    if (flag == 0) {
        printf("\n\n\tStudent Not Found\n");
        fclose(ft);
        remove("temp.txt");
    } else {
        //fseek(fp, -siz, SEEK_CUR);
        printf("\n\n\tEnter Full Name of Student: ");
        fflush(stdin);
        fgets(s.name, 100, stdin);
        s.name[strlen(s.name) - 1] = '\0';
        printf("\n\n\tEnter Department Name: ");
        fflush(stdin);
        fgets(s.dept, 50, stdin);
        s.dept[strlen(s.dept) - 1] = '\0';
        printf("\n\n\tEnter SGPA for 12 semesters\n");
        for (i = 0, cgpa = 0; i < 12; i++) {
            do {
                printf("\tSemester %d: ", i + 1);
                scanf("%f", &s.sgpa[i]);
                if (!isValidSGPA(s.sgpa[i])) {
                    printf("\nInvalid SGPA. Please enter a value between 0 and 10.\n");
                }
            } while (!isValidSGPA(s.sgpa[i]));
            cgpa += s.sgpa[i];
        }
        cgpa /= 12.0;
        s.cgpa = cgpa;
        fwrite(&s, sizeof(s), 1, ft);
        printf("\n\n\tStudent Record Updated Successfully.\n");
        fclose(ft);
        remove("students.txt");
        rename("temp.txt", "students.txt");
        fp = openFile("students.txt", "ab+");

    }
    system("pause");
}

void displayStudents(FILE * fp) {
    title();
    struct Student s;
    int i, siz = sizeof(s);
    rewind(fp);
    while ((fread(&s, siz, 1, fp)) == 1) {
        printf("\n\n\tStudent Name: %s", s.name);
        printf("\n\tDepartment: %s", s.dept);
        printf("\n\tRoll Number: %d", s.roll);
        printf("\n\tCGPA: %.2f", s.cgpa);
        printf("\n\n\tSGPA for 12 semesters:\n");
        for (i = 0; i < 12; i++) {
            printf("\tSemester %d: %.2f\n", i + 1, s.sgpa[i]);
        }
        printChar('-', 65);
    }
    system("pause");
}

void individualView(FILE * fp) {
    title();
    struct Student s;
    int roll, flag = 0, siz = sizeof(s), i;
    printf("\n\n\tEnter Roll Number: ");
    scanf("%d", &roll);
    rewind(fp);
    while ((fread(&s, siz, 1, fp)) == 1) {
        if (s.roll == roll) {
            flag = 1;
            break;
        }
    }
    if (flag == 0) {
        printf("\n\n\tStudent Not Found\n");
    } else {
        printf("\n\n\tStudent Name: %s", s.name);
        printf("\n\tDepartment: %s", s.dept);
        printf("\n\tRoll Number: %d", s.roll);
        printf("\n\tCGPA: %.2f", s.cgpa);
        printf("\n\n\tSGPA for 12 semesters:\n");
        for ( i = 0; i < 12; i++) {
            printf("\tSemester %d: %.2f\n", i + 1, s.sgpa[i]);
        }
        printChar('-', 65);
    }
    system("pause");
}

void removeStudent(FILE * fp) {
    title();
    struct Student s;
    int roll, flag = 0, siz = sizeof(s);
    FILE *ft = openFile("temp.txt", "wb");
    printf("\n\n\tEnter Roll Number of Student to Remove: ");
    scanf("%d", &roll);
    rewind(fp);
    while ((fread(&s, siz, 1, fp)) == 1) {
        if (s.roll == roll) {
            flag = 1;
        } else {
            fwrite(&s, siz, 1, ft);
        }
    }
    fclose(fp);
    fclose(ft);
    remove("students.txt");
    rename("temp.txt", "students.txt");
    fp = openFile("students.txt", "ab+");
    if (flag == 0) {
        printf("\n\n\tStudent Not Found\n");
    } else {
        printf("\n\n\tStudent Record Deleted Successfully.\n");
    }
    system("pause");
}

void changePassword() {
    char c;
    printf("\nEnter new password: ");
    fflush(stdin);
    fgets(pa.pass, 25, stdin);
    pa.pass[strlen(pa.pass) - 1] = '\0';
    encryptDecrypt(pa.pass);  // Encrypt password
    printf("\nSave password (y/n): ");
    fflush(stdin);
    scanf("%c", &c);
    if (c == 'y' || c == 'Y') {
        safeFileWrite("Password.txt", &pa, sizeof(pa));
        printf("\n\tPassword Saved\n");
    } else {
        printf("Password not saved.\n");
    }
    printf("Press any key to continue >>>");
    getch();
}

void searchByName(FILE * fp) {
    title();
    struct Student s;
    char name[100];
    int flag = 0, siz = sizeof(s) , i;
    printf("\n\n\tEnter Name of Student to Search: ");
    fflush(stdin);
    fgets(name, 100, stdin);
    name[strlen(name) - 1] = '\0';
    rewind(fp);
    while ((fread(&s, siz, 1, fp)) == 1) {
        if (strcmp(s.name, name) == 0) {
            flag = 1;
            printf("\n\n\tStudent Name: %s", s.name);
            printf("\n\tDepartment: %s", s.dept);
            printf("\n\tRoll Number: %d", s.roll);
            printf("\n\tCGPA: %.2f", s.cgpa);
            printf("\n\n\tSGPA for 12 semesters:\n");
            for ( i = 0; i < 12; i++) {
                printf("\tSemester %d: %.2f\n", i + 1, s.sgpa[i]);
            }
            printChar('-', 65);
        }
    }
    if (flag == 0) {
        printf("\n\n\tStudent Not Found\n");
    }
    system("pause");
}

void sortByCGPA(FILE * fp) {
    title();
    struct Student s[MAX], temp;
    int i, j, count = 0, siz = sizeof(s[0]);
    rewind(fp);
    while ((fread(&s[count], siz, 1, fp)) == 1) {
        count++;
    }
    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            if (s[i].cgpa < s[j].cgpa) {
                temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }
    for (i = 0; i < count; i++) {
        printf("\n\n\tStudent Name: %s", s[i].name);
        printf("\n\tDepartment: %s", s[i].dept);
        printf("\n\tRoll Number: %d", s[i].roll);
        printf("\n\tCGPA: %.2f", s[i].cgpa);
        printf("\n\n\tSGPA for 12 semesters:\n");
        for (j = 0; j < 12; j++) {
            printf("\tSemester %d: %.2f\n", j + 1, s[i].sgpa[j]);
        }
        printChar('-', 65);
    }
    system("pause");
}

void addAttendance(FILE *fp) {
    title();
    struct Attendance a;
    struct Student s;
    int flag = 0, siz = sizeof(struct Student);

    printf("\n\n\tEnter Roll Number: ");
    scanf("%d", &a.roll);

    rewind(fp);
    while (fread(&s, siz, 1, fp) == 1) {
        if (s.roll == a.roll) {
            flag = 1;
            break;
        }
    }

    if (flag == 1) {
        printf("\n\n\tEnter Total Days: ");
        scanf("%d", &a.totalDays);
        printf("\n\n\tEnter Days Present: ");
        scanf("%d", &a.daysPresent);

        FILE *afp = fopen("attendance.txt", "ab+");
        if (afp == NULL) {
            printf("\nError opening file.\n");
            return;
        }
        fwrite(&a, sizeof(a), 1, afp);
        fclose(afp);

        printf("\nAttendance record added successfully.\n");
    } else {
        printf("\nStudent not found.\n");
    }
    system("pause");
}

void displayAttendance() {
    title();
    struct Attendance a; 
    FILE *afp = fopen("attendance.txt", "rb");

    if (afp == NULL) {
        printf("\nError opening file.\n");
        return;
    }

    printf("\n\n\tAttendance Records:\n");
    printChar('-', 65);
    while (fread(&a, sizeof(a), 1, afp) == 1) {
        printf("\n\n\tRoll Number: %d", a.roll);
        printf("\n\tDays Present: %d", a.daysPresent);
        printf("\n\tTotal Days: %d\n", a.totalDays);
        printChar('-', 65);
    }
    fclose(afp);
    system("pause");
}