#include <stdio.h>
#include <string.h>

/*
Name: Mahmoud Obied
Student ID : 1251151
lecture section : 7
lab section : 14L
*/

struct Student
{
    int studentID;
    char name[50];
    int age;
    double gpa;
};

struct Student students[100];
int studentCount = 0;

void initializeStudentRecords();
void displayMainMenu();
void addStudent();
void removeStudent();
void searchStudent();
void displayAllStudents();
void saveStudentRecords();

int main()
{
    int choice;
    initializeStudentRecords();

    do
    {
        displayMainMenu();
        printf("Enter your operation : ");
        int checkBuffer = scanf("%d", &choice);

        while (checkBuffer != 1)
        {
            char buffer;
            do
            {
                scanf("%c", &buffer);
            } while (buffer != '\n');
            printf("\n\n");
            displayMainMenu();
            printf("\nYou Have Entered characters, not integers. Please try valid operation (1-5): ");
            checkBuffer = scanf("%d", &choice);
        }

        while (choice > 5 || choice < 1)
        {
            printf("\n\n");
            displayMainMenu();
            printf("\nInvalid Operation\nPlease Select valid Choice : ");
            checkBuffer = scanf("%d", &choice);
            while (checkBuffer != 1)
            {
                char buffer;
                do
                {
                    scanf("%c", &buffer);
                } while (buffer != '\n');
                printf("\n\n");
                displayMainMenu();
                printf("\nYou Have Entered characters, not integers. Please try valid operation (1-5): ");
                checkBuffer = scanf("%d", &choice);
            }
        }

        printf("\n===================================\n\n\n\n");
        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            removeStudent();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            displayAllStudents();
            break;
        }
    } while (choice != 5);

    saveStudentRecords(); // استدعاء دالة الحفظ عند الخروج
    return 0;
}

void initializeStudentRecords()
{
    FILE *fptr = fopen("students.bin", "rb");
    if (fptr == NULL)
    {
        printf("No existing records found. Starting with empty system.\n");
        printf("===================================\n\n\n");
        return;
    }

    studentCount = fread(students, sizeof(struct Student), 100, fptr);

    printf("%d student record(s) loaded from students.bin.\n", studentCount);
    printf("===================================\n\n\n");
    fclose(fptr); // إغلاق الملف دائماً بعد الانتهاء
}

void displayMainMenu()
{
    printf("==== STUDENT RECORD MANAGEMENT SYSTEM ====\n");
    printf("Please Select an Operation(1-5)\n");
    printf("1- Add New Student \n");
    printf("2- Remove Student \n");
    printf("3- Search for Student\n");
    printf("4- Display All Students\n");
    printf("5- Exit\n");
}

// 2. دالة إضافة طالب جديد باستخدام الـ Struct
void addStudent()
{
    if (studentCount >= 100)
    {
        printf("System is full! Cannot add more students.\n");
        printf("===================================\n\n\n");
        return;
    }

    printf("==== ADD NEW STUDENT ====");
    printf("\nPlease Enter Student ID (1000-9999) : ");
    int tempID;
    int checkBuffer = scanf("%d", &tempID);

    while (checkBuffer != 1 || tempID > 9999 || tempID < 1000)
    {
        if (checkBuffer != 1)
        {
            char buffer;
            do
            {
                scanf("%c", &buffer);
            } while (buffer != '\n');
        }
        printf("\nInvalid ID. Please enter a valid 4-digit ID (1000-9999): ");
        checkBuffer = scanf("%d", &tempID);
    }

    // التحقق من أن الرقم الجامعي غير مكرر داخل المصفوفة
    for (int j = 0; j < studentCount; j++)
    {
        if (tempID == students[j].studentID)
        {
            printf("\nStudent ID is already in use. Operation aborted.\n");
            printf("===================================\n\n\n");
            return;
        }
    }

    // إسناد المعرّف الفريد بعد نجاح التحقق
    students[studentCount].studentID = tempID;

    char cleanBuffer;
    do
    {
        scanf("%c", &cleanBuffer);
    } while (cleanBuffer != '\n');

    printf("\nPlease Enter Student Name : ");
    int checkNumbers;
    do
    {
        checkNumbers = 0;
        scanf(" %c", &students[studentCount].name[0]);
        if ((students[studentCount].name[0] < 'A' || students[studentCount].name[0] > 'Z') && (students[studentCount].name[0] < 'a' || students[studentCount].name[0] > 'z'))
        {
            printf("\nPlease Enter letters not numbers: ");
            do
            {
                scanf("%c", &cleanBuffer);
            } while (cleanBuffer != '\n');
        }
        else
        {
            for (int i = 1; i < 50; i++)
            {
                if (i == 49)
                {
                    checkNumbers = 0;
                    printf("\nError: The name is too long! Maximum 50 characters. Please try again: ");
                    do
                    {
                        scanf("%c", &cleanBuffer);
                    } while (cleanBuffer != '\n');
                    break;
                }
                scanf("%c", &students[studentCount].name[i]);
                if ((students[studentCount].name[i] >= 'A' && students[studentCount].name[i] <= 'Z') || (students[studentCount].name[i] >= 'a' && students[studentCount].name[i] <= 'z') || students[studentCount].name[i] == ' ' || students[studentCount].name[i] == '\n')
                {
                    checkNumbers++;
                }
                else
                {
                    checkNumbers = 0;
                    printf("\nPlease Enter just letters: ");
                    do
                    {
                        scanf("%c", &cleanBuffer);
                    } while (cleanBuffer != '\n');
                    break;
                }
                if (students[studentCount].name[i] == '\n')
                {
                    students[studentCount].name[i] = '\0';
                    break;
                }
            }
        }
    } while (checkNumbers == 0);

    // إدخال العمر والتحقق منه
    printf("\nPlease Enter Student Age (6-50) : ");
    checkBuffer = scanf("%d", &students[studentCount].age);
    while (checkBuffer != 1 || students[studentCount].age > 50 || students[studentCount].age < 6)
    {
        if (checkBuffer != 1)
        {
            char buffer;
            do
            {
                scanf("%c", &buffer);
            } while (buffer != '\n');
        }
        printf("\nInvalid Age. Please try again (6-50): ");
        checkBuffer = scanf("%d", &students[studentCount].age);
    }

    // إدخال المعدل التراكمي والتحقق منه
    printf("\nPlease Enter Student GPA (0.00-4.00) : ");
    checkBuffer = scanf("%lf", &students[studentCount].gpa);
    while (checkBuffer != 1 || students[studentCount].gpa > 4.0 || students[studentCount].gpa < 0.0)
    {
        if (checkBuffer != 1)
        {
            char buffer;
            do
            {
                scanf("%c", &buffer);
            } while (buffer != '\n');
        }
        printf("\nInvalid GPA. Please try again (0.00-4.00): ");
        checkBuffer = scanf("%lf", &students[studentCount].gpa);
    }

    studentCount++; // زيادة عدد الطلاب الفعليين بالمنظومة
    printf("\nStudent added successfully\n");
    printf("===================================\n\n\n");
}

// 3. دالة حذف طالب باستخدام الـ Struct
void removeStudent()
{
    printf("==== REMOVE STUDENT PAGE ====\n");
    if (studentCount == 0)
    {
        printf("There's No Students In The System \n");
        printf("===================================\n\n\n");
        return;
    }

    printf("Please Enter Student ID (1000-9999) : ");
    int ID, checkBuffer;
    checkBuffer = scanf("%d", &ID);
    while (checkBuffer != 1 || ID > 9999 || ID < 1000)
    {
        if (checkBuffer != 1)
        {
            char buffer;
            do
            {
                scanf("%c", &buffer);
            } while (buffer != '\n');
        }
        printf("\nInvalid ID. Please enter a valid ID (1000-9999): ");
        checkBuffer = scanf("%d", &ID);
    }

    for (int i = 0; i < studentCount; i++)
    {
        if (ID == students[i].studentID)
        {
            printf("\nAre You Sure You want to remove the information of this ID = %d \n", ID);
            printf("If You Are Sure Enter 1 if You Don't Want To Remove it enter 0 : ");
            int test;
            checkBuffer = scanf("%d", &test);
            while (checkBuffer != 1 || (test != 1 && test != 0))
            {
                if (checkBuffer != 1)
                {
                    char buffer;
                    do
                    {
                        scanf("%c", &buffer);
                    } while (buffer != '\n');
                }
                printf("\nPlease Enter 1 to remove this ID : %d or 0 to cancel: ", ID);
                checkBuffer = scanf("%d", &test);
            }

            if (test == 0)
            {
                printf("\nNo Student Deleted");
                printf("\n===================================\n\n\n");
                return;
            }

            // إزاحة باقي عناصر الـ struct بالذاكرة خطوة للخلف لملء الفراغ
            for (int j = i; j < studentCount - 1; j++)
            {
                students[j] = students[j + 1];
            }
            studentCount--;
            printf("\nStudent removed successfully\n");
            printf("===================================\n\n\n");
            return;
        }
    }
    printf("\nThere's no student with this ID\n");
    printf("===================================\n\n\n");
}

// 4. دالة البحث عن طالب باستخدام الـ Struct
void searchStudent()
{
    printf("==== SEARCH FOR STUDENT PAGE ====\n");
    if (studentCount == 0)
    {
        printf("There's No Student's In The System\n");
        printf("===================================\n\n\n");
        return;
    }

    printf("\nPlease Enter Student ID (1000-9999) : ");
    int ID, checkBuffer;
    checkBuffer = scanf("%d", &ID);
    while (checkBuffer != 1 || ID > 9999 || ID < 1000)
    {
        if (checkBuffer != 1)
        {
            char buffer;
            do
            {
                scanf("%c", &buffer);
            } while (buffer != '\n');
        }
        printf("\nInvalid ID. Please enter a valid ID (1000-9999): ");
        checkBuffer = scanf("%d", &ID);
    }

    printf("\n");
    for (int i = 0; i < studentCount; i++)
    {
        if (ID == students[i].studentID)
        {
            printf("Student Name : %s\n", students[i].name);
            printf("Student Age : %02d\n", students[i].age);
            printf("Student GPA : %.2f\n", students[i].gpa);
            printf("===================================\n\n\n");
            return;
        }
    }
    printf("There's no student with this ID\n");
    printf("===================================\n\n\n");
}

// 5. دالة عرض جميع الطلاب وتنسيق الجدول
void displayAllStudents()
{
    printf("==== ALL THE STUDENTS MENU ====\n");
    if (studentCount != 0)
    {
        int length = strlen(students[0].name);
        for (int i = 1; i < studentCount; i++)
        {
            if (length < strlen(students[i].name))
            {
                length = strlen(students[i].name);
            }
        }
        length = length + 3;
        printf("ID     ");
        printf("Name");
        for (int i = 0; i < length - 4; i++)
        {
            printf(" ");
        }
        printf("Age   ");
        printf("GPA\n");

        double sumGpa = 0;
        for (int i = 0; i < studentCount; i++)
        {
            printf("%d   ", students[i].studentID);
            printf("%s", students[i].name);

            int temp = strlen(students[i].name);
            for (int j = 0; j < length - temp; j++)
            {
                printf(" ");
            }

            if (students[i].age > 9)
            {
                printf("%d    ", students[i].age);
            }
            else
            {
                printf(" %d    ", students[i].age);
            }
            printf("%.2f\n", students[i].gpa);

            sumGpa = sumGpa + students[i].gpa;
        }

        printf("The Total Number Of Students : %d \n", studentCount);
        printf("Students average GPA : %.2f\n", sumGpa / studentCount);
        printf("===================================\n\n\n");
    }
    else
    {
        printf("No students in the system \n");
        printf("===================================\n\n\n");
    }
}

// 6. دالة حفظ السجلات داخل ملف ثنائي عند الخروج (المرحلة الثانية)
void saveStudentRecords()
{
    FILE *fptr = fopen("students.bin", "wb"); // فتح الملف للكتابة الثنائية (سيمسح القديم وينشئ جديد)
    if (fptr == NULL)
    {
        printf("Error: Could not save records.\n");
        return;
    }

    // كتابة جميع سجلات الطلاب المخزنة حالياً دفعة واحدة بالـ Binary Format
    size_t written = fwrite(students, sizeof(struct Student), studentCount, fptr);

    if (written == (size_t)studentCount)
    {
        printf("%d student record(s) saved to students.bin.\n", studentCount);
    }
    else
    {
        printf("Error: Failed to write all records to file.\n");
    }

    printf("===================================\n\n\n");
    fclose(fptr); // إغلاق الملف لحماية البيانات
}