#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_SIZE 20

typedef struct
{
    char name[MAX_NAME];
    char roll_number[MAX_SIZE];
    char course[MAX_NAME];
    char total_amt[MAX_SIZE];
    char paid_amt[MAX_SIZE];
    char balance_amt[MAX_SIZE];
} stud;

stud students[MAX_SIZE];
int total_students;

void select_course();
void initialize_file();
void add_data();
void update_data();
void load_data();
void display_data();

int main()
{

    FILE *filepointer;
    filepointer = fopen("feeData.csv", "r");

    if (filepointer == NULL)
    {
        perror("\nCould not open data file for reading or writing\n");
        return 0;
    }

    int option;

    printf("\n******FEE MANAGEMENT SYSTEM******");
    printf("\n1. ADD FEE DATA STUDENT");
    printf("\n2. UPDATE FEE DATA OF A STUDENT");
    printf("\n3. DISPLAY FEE DATA OF A STUDENT");
    printf("\n4. NEW DATA SHEET");
    printf("\n5. EXIT");

    do
    {
        printf("\n\nEnter the option(MAIN MENU): ");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            add_data();
            break;
        case 2:
            update_data();
            break;
        case 3:
            display_data();
            break;
        case 4:
            initialize_file();
            break;
        default:
            printf("\nEnter the valid option");
        }
    } while (option != 5);
    return 0;
}

void initialize_file()
{
    FILE *filepointer;
    filepointer = fopen("feeData.csv", "w");

    fprintf(filepointer, "Name, Roll Number, Course, Total Fees, Paid Amount, Balance Amount\n");
    fclose(filepointer);
}

void add_data()
{
    int n;
    FILE *filepointer = fopen("feeData.csv", "a");
    printf("\nNumber of Students To be added: ");
    scanf("%d", &n);
    total_students += n;
    for (int i = 0; i < n; i++)
    {
        printf("\n========STUDENT %d DETAILS========", i + 1);
        fflush(stdin);
        printf("\nName of student: ");
        gets(students[i].name);
        printf("Roll number: ");
        scanf("%s", &students[i].roll_number);
        select_course(&students[i]);
        printf("Amount paid: ");
        scanf("%s", &students[i].paid_amt);
        int balance_amt = atoi(students[i].total_amt) - atoi(students[i].paid_amt);
        itoa(balance_amt, students[i].balance_amt, 10);
        fprintf(filepointer, "%s,%s,%s,%s,%s,%s\n", students[i].name, students[i].roll_number, students[i].course, students[i].total_amt, students[i].paid_amt, students[i].balance_amt);
        printf("Fee Data of %s is successfully added.\n", students[i].name);
    }
    fclose(filepointer);
}

void select_course(stud *s1)
{
    int option;

    printf("\nSelect the course: ");
    printf("\n1. Computer Science ($2700)");
    printf("\n2. Electronics and Communication ($2300)");
    printf("\n3. Information Technology ($1900)\n");
    printf("\nEnter the option: ");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        strcpy(s1->course, "Computer Science");
        strcpy(s1->total_amt, "2700");
        strcpy(s1->balance_amt, "2700");
        break;
    case 2:
        strcpy(s1->course, "Electronics and Communication");
        strcpy(s1->total_amt, "2300");
        strcpy(s1->balance_amt, "2300");
        break;
    case 3:
        strcpy(s1->course, "Information Technology");
        strcpy(s1->total_amt, "1900");
        strcpy(s1->balance_amt, "1900");
        break;
    }
}

void update_data()
{
    char r_num[10];
    int fees, bal, amt, flag = 0;
    printf("\nEnter the roll number: ");
    scanf("%s", &r_num);
    load_data();
    printf("\nEnter the amount to be paid: ");
    scanf("%d", &fees);
    for (int i = 0; i < total_students; i++)
    {
        if (!strcmp(students[i].roll_number, r_num))
        {
            printf("\nFound Student");
            amt = atoi(students[i].paid_amt) + fees;
            itoa(amt, students[i].paid_amt, 10);
            bal = atoi(students[i].balance_amt) - fees;
            if (bal < 0)
                bal = 0;
            itoa(bal, students[i].balance_amt, 10);
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        printf("\nStudent record not found");
        return;
    }
    FILE *fp = fopen("feeData.csv", "w");
    fprintf(fp, "Name, Roll Number, Course, Total Fees, Paid Amount, Balance Amount\n");
    for (int i = 0; i < total_students; i++)
    {
        fprintf(fp, "%s,%s,%s,%s,%s,%s\n", students[i].name, students[i].roll_number, students[i].course, students[i].total_amt, students[i].paid_amt, students[i].balance_amt);
    }
    fclose(fp);
}

void load_data()
{
    FILE *fp = fopen("feeData.csv", "r");
    if (!fp)
    {
        puts("FILE NOT FOUND");
        return;
    }

    char buff[100];
    int row_count = 0;
    int field_count = 0;

    total_students = 0;
    while (fgets(buff, 100, fp))
    {
        field_count = 0;
        row_count++;
        if (row_count == 1)
            continue;
        char *field = strtok(buff, ",");
        while (field)
        {
            if (field_count == 0)
                strcpy(students[total_students].name, field);
            if (field_count == 1)
                strcpy(students[total_students].roll_number, field);
            if (field_count == 2)
                strcpy(students[total_students].course, field);
            if (field_count == 3)
                strcpy(students[total_students].total_amt, field);
            if (field_count == 4)
                strcpy(students[total_students].paid_amt, field);
            if (field_count == 5)
                strcpy(students[total_students].balance_amt, field);

            field = strtok(NULL, ",");
            field_count++;
        }
        total_students++;
    }
    fclose(fp);
}
void display_data()
{
    int option;
    load_data();
    char r_num[10];
    printf("\n1. Display data of particular student");
    printf("\n2. Display data of all students");
    printf("\nEnter the option: ");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        printf("\nEnter the roll number: ");
        scanf("%s", &r_num);
        for (int i = 0; i < total_students; i++)
        {
            if (!strcmp(students[i].roll_number, r_num))
            {
                printf("\nName: %s\nRoll Number: %s\nCourse: %s\nTotal amount: %s\nPaid Amount: %s\nBalance Amount: %s\n", students[i].name, students[i].roll_number, students[i].course, students[i].total_amt, students[i].paid_amt, students[i].balance_amt);
            }
        }
        break;

    case 2:
        printf("\n Fee data of all students");
        for (int i = 0; i < total_students; i++)
        {
            printf("\nName: %s\nRoll Number: %s\nCourse: %s\nTotal amount: %s\nPaid Amount: %s\nBalance Amount: %s\n", students[i].name, students[i].roll_number, students[i].course, students[i].total_amt, students[i].paid_amt, students[i].balance_amt);
        }
    }
}