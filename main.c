#include <stdio.h>
#include <string.h>
/*
Name:Mahmoud Obied
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
{ // Declare the variables that we will put the information in
    int choice;
    initializeStudentRecords(); // call this function to print "Student records loaded successfully."
    do
    {
        displayMainMenu(); // call display menu
        printf("Enter your operation : ");
        int checkBuffer = scanf("%d", &choice); // if checkBuffer =0 then we will enter the loop beacuse the scanf hasn't read the input

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
            /* just make sure that the operation is invalid in the main menu list
            if it's not invalid the program will continue reasking for new value till it find a valid input*/
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
    } while (choice != 5); // the loop will break when the user enter the number 5

    saveStudentRecords(); // call saveStudentRecords Function to print that the operation is ends then close the program
    return 0;
}

void initializeStudentRecords()
{
    FILE *fptr = fopen("students.bin", "rb"); // Open The Binary File
    if (fptr == NULL)                         // If The File Is Empty We Will Print This
    {
        printf("No existing records found. Starting with empty system.\n");
        printf("===================================\n\n\n");
        return;
    }
    studentCount = fread(students, sizeof(struct Student), 100, fptr); // Take All The Data From The File
    fclose(fptr);                                                      // Close The File
    if (studentCount == 0)
    {
        printf("The System Is Empty.\nLets Start From The Start\n");
        printf("===================================\n\n\n");
        return;
    }
    printf("Student records loaded successfully.\n");
    printf("===================================\n\n\n");
}

void displayMainMenu()
{
    // a Function To Print The Choices To the user
    printf("==== STUDENT RECORD MANAGEMENT SYSTEM ====\n");
    printf("Please Select an Operation(1-5)\n");
    printf("1- Add New Student \n");
    printf("2- Remove Student \n");
    printf("3- Search for Student\n");
    printf("4- Display All Students\n");
    printf("5- Exit\n");
}

void addStudent()
{
    // add a student for the data in the program
    if (studentCount >= 100)
    {
        printf("System is full! Cannot add more students.\n");
        printf("===================================\n\n\n");
        return;
    }
    printf("==== ADD NEW STUDNET ====");
    printf("\nPlease Enter Student ID (1000-9999) : ");
    int checkBuffer = scanf("%d", &students[studentCount].studentID); // if checkBuffer =0 then we will enter the loop beacuse the scanf hasn't read the input

    while (checkBuffer != 1)
    {
        char buffer;
        do
        {
            scanf("%c", &buffer);
        } while (buffer != '\n');

        printf("\nYou Have Entered characters, not integers. Please try ID (1000-9999): ");

        checkBuffer = scanf("%d", &students[studentCount].studentID);
    }

    while (students[studentCount].studentID > 9999 || students[studentCount].studentID < 1000)
    { // check if the id is 4 digits
        printf("\nPlease reEnter the  Student ID  And make sure it's a valid input (1000-9999) : ");
        checkBuffer = scanf("%d", &students[studentCount].studentID); // if checkBuffer =0 then we will enter the loop beacuse the scanf hasn't read the input

        while (checkBuffer != 1)
        {
            char buffer;
            do
            {
                scanf("%c", &buffer);
            } while (buffer != '\n');

            printf("\nYou Have Entered characters, not integers. Please try ID (1000-9999): ");

            checkBuffer = scanf("%d", &students[studentCount].studentID);
        }
    }
    for (int j = 0; j < studentCount; j++)
    {
        if (students[studentCount].studentID == students[j].studentID)
        { // check if the ID used before this time
            printf("\nStudent ID is already in use Please reEnter new one (1000-9999): ");
            checkBuffer = scanf("%d", &students[studentCount].studentID); // if checkBuffer =0 then we will enter the loop beacuse the scanf hasn't read the input
            while (checkBuffer != 1)
            {
                char buffer;
                do
                {
                    scanf("%c", &buffer);
                } while (buffer != '\n');

                printf("\nYou Have Entered characters, not integers. Please try again: ");

                checkBuffer = scanf("%d", &students[studentCount].studentID);
            }
            while (students[studentCount].studentID > 9999 || students[studentCount].studentID < 1000)
            { // make sure that the new entered number is 4-digits
                printf("\nPlease reEnter the  Student ID  And make sure it's a valid input(1000-9999) : ");
                checkBuffer = scanf("%d", &students[studentCount].studentID); // if checkBuffer = 0 then we will enter the loop beacuse the scanf hasn't read the input

                while (checkBuffer != 1)
                {
                    char buffer;
                    do
                    {
                        scanf("%c", &buffer);
                    } while (buffer != '\n');

                    printf("\nYou Have Entered characters, not integers. Please try numbers (1000-9999) : ");

                    checkBuffer = scanf("%d", &students[studentCount].studentID);
                }
            }
            j = -1; // because of the j++ in the end of the loop so this return j to 0 to check the new entered number if it's used before this time or not
        }
    }
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
        scanf(" %c", &students[studentCount].name[0]); // to make sure that the first character is a letter
        if ((students[studentCount].name[0] < 'A' || students[studentCount].name[0] > 'Z') && (students[studentCount].name[0] < 'a' || students[studentCount].name[0] > 'z'))
        {
            printf("\nplease Enter letters not numbers :");
            do
            {
                scanf("%c", &cleanBuffer);
            } while (cleanBuffer != '\n'); // get the buffer out so we don't get \n in the buffer and break the loops
        }
        else
        {
            for (int i = 1; i < 50; i++)
            { // we do this loop because if we used scanf("%s",name); it will stop after the spaces in the name
                if (i == 49)
                { // if we see i ==50 and the loop doesn't break then the name is longer than 50 we will ask to enter it again
                    checkNumbers = 0;
                    printf("\nError: The name is too long! Maximum 50 characters. Please try again: ");
                    do
                    {
                        scanf("%c", &cleanBuffer);
                    } while (cleanBuffer != '\n'); // delete the buffer
                    break;
                }
                scanf("%c", &students[studentCount].name[i]);
                if ((students[studentCount].name[i] >= 'A' && students[studentCount].name[i] <= 'Z') || (students[studentCount].name[i] >= 'a' && students[studentCount].name[i] <= 'z') || students[studentCount].name[i] == ' ' || students[studentCount].name[i] == '\n')
                { // make sure the user enter letters not any thing else
                    checkNumbers++;
                }
                else // check if there is any thing else with the letters
                {
                    checkNumbers = 0;
                    printf("\nPlease Enter just letters : ");
                    do
                    {
                        scanf("%c", &cleanBuffer);
                    } while (cleanBuffer != '\n'); // delete the buffer
                    break;
                }
                if (students[studentCount].name[i] == '\n')
                { // if the test character = \n "Enter" we will put it \0 and break the loop and go to enter the age
                    students[studentCount].name[i] = '\0';
                    break;
                }
            }
        }
    } while (checkNumbers == 0);
    printf("\nPlease Enter Student Age (6-50) : ");
    checkBuffer = scanf("%d", &students[studentCount].age); // if checkBuffer =0 then we will enter the loop beacuse the scanf hasn't read the input
    while (checkBuffer != 1)
    {
        char buffer;
        do
        {
            scanf("%c", &buffer);
        } while (buffer != '\n');

        printf("\nYou Have Entered characters, not integers. Please try ages (6-50) : ");

        checkBuffer = scanf("%d", &students[studentCount].age);
    }
    while (students[studentCount].age > 50 || students[studentCount].age < 6)
    {
        // if the age bigger than 50 or smaller than 6 the program will keep asking for a right age number between them
        printf("\nPlease reEnter Student Age it should be between (6-50) : ");
        checkBuffer = scanf("%d", &students[studentCount].age); // if checkBuffer =0 then we will enter the loop beacuse the scanf hasn't read the input
        while (checkBuffer != 1)
        {
            char buffer;
            do
            {
                scanf("%c", &buffer);
            } while (buffer != '\n');

            printf("\nYou Have Entered characters, not integers. Please try ages (6-50) : ");

            checkBuffer = scanf("%d", &students[studentCount].age);
        }
    }
    printf("\nPlease Enter Student GPA (0.00-4.00) : ");
    checkBuffer = scanf("%lf", &students[studentCount].gpa); // if checkBuffer =0 then we will enter the loop beacuse the scanf hasn't read the input
    while (checkBuffer != 1)
    {
        char buffer;
        do
        {
            scanf("%c", &buffer);
        } while (buffer != '\n');

        printf("\nYou Have Entered characters, not GPA. Please try numbers (0.00-4.00) : ");

        checkBuffer = scanf("%lf", &students[studentCount].gpa);
    }
    while (students[studentCount].gpa > 4 || students[studentCount].gpa < 0)
    {
        // if the GPA bigger than 4 or smaller than 0 the program will keep asking for a right GPA number between them
        printf("\nPlease reEnter Student GPA (0.00-4.00): ");
        checkBuffer = scanf("%lf", &students[studentCount].gpa); // if checkBuffer =0 then we will enter the loop beacuse the scanf hasn't read the input
        while (checkBuffer != 1)
        {
            char buffer;
            do
            {
                scanf("%c", &buffer);
            } while (buffer != '\n');

            printf("\nYou Have Entered characters, not GPA. Please try numbers (0.00-4.00) : ");

            checkBuffer = scanf("%lf", &students[studentCount].gpa);
        }
    }
    studentCount++; // increase the number of students in the program
    printf("\nStudent added successfully\n");
    printf("===================================\n\n\n");
}

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
    checkBuffer = scanf("%d", &ID); // if checkBuffer =0 then we will enter the loop beacuse the scanf hasn't read the input
    while (checkBuffer != 1)
    {
        char buffer;
        do
        {
            scanf("%c", &buffer);
        } while (buffer != '\n');

        printf("\nYou Have Entered characters, not integers. Please try ID (1000-9999): ");
        checkBuffer = scanf("%d", &ID);
    }
    while (ID > 9999 || ID < 1000)
    {
        // check if the ID is 4-digit because human may miss numbers
        printf("Please reEnter Student ID (1000-9999) : \n");
        checkBuffer = scanf("%d", &ID); // if checkBuffer =0 then we will enter the loop beacuse the scanf hasn't read the input
        while (checkBuffer != 1)
        {
            char buffer;
            do
            {
                scanf("%c", &buffer);
            } while (buffer != '\n');

            printf("\nYou Have Entered characters, not integers. Please try ID (1000-9999): ");

            checkBuffer = scanf("%d", &ID);
        }
    }
    for (int i = 0; i < studentCount; i++)
    {
        if (ID == students[i].studentID)
        {
            printf("\nAre You Sure You want to remove the information of this ID = %d \n", ID); // make sure the user want to remove this ID not another one
            printf("If You Are Sure Enter 1 if You Don't Want To Remove it enter 0 : ");
            int test;
            checkBuffer = scanf("%d", &test); // if checkBuffer =0 then we will enter the loop beacuse the scanf hasn't read the input
            while (checkBuffer != 1)
            {
                char buffer;
                do
                {
                    scanf("%c", &buffer);
                } while (buffer != '\n');

                printf("\nYou Have Entered characters, not integers. Please try ID (1000-9999): ");

                checkBuffer = scanf("%d", &ID);
            }
            while (test != 1 && test != 0)
            { // make sure the input is 1 or 0
                printf("\nplease Enter 1 to remove this ID : %d or 0 to not remove it : ", ID);
                scanf("%d", &test);
            }
            if (test == 0)
            {
                // if the input is 0 so it will close this function and get back to the main menu
                printf("\nNo Student Deleted");
                printf("\n===================================\n\n\n");
                return;
            }
            int j = i;
            while (j < (studentCount)-1)
            {
                // move the next information backward one step so it's going to be next to the before one in the memory
                students[j] = students[j + 1];
                j++;
            }
            studentCount = studentCount - 1;
            printf("\nStudent removed successfully\n");
            printf("===================================\n\n\n");
            return;
        }
    }
    // if we don't found the student we will print this
    printf("\nThere's no student with this ID\n");
    printf("===================================\n\n\n");
}

void searchStudent()
{
    printf("==== SEARCH FOR STUDENT PAGE ====\n");
    if (studentCount == 0)
    { // if there's no students in the system we will return this
        printf("There's No Student's In The System\n");
        printf("===================================\n\n\n");
        return;
    }
    printf("\nPlease Enter Student ID (1000-9999) : ");
    int ID, checkBuffer;
    checkBuffer = scanf("%d", &ID); // if checkBuffer = 0 then we will enter the loop beacuse the scanf hasn't read the input
    while (checkBuffer != 1)
    {
        char buffer;
        do
        {
            scanf("%c", &buffer);
        } while (buffer != '\n');

        printf("\nYou Have Entered characters, not integers. Please try ID (1000-9999): ");

        checkBuffer = scanf("%d", &ID);
    }
    while (ID > 9999 || ID < 1000)
    {
        // make sure the ID is invalid ID because people can miss again..
        printf("\nPlease reEnter Student ID (1000-9999) : ");
        checkBuffer = scanf("%d", &ID); // if checkBuffer =0 then we will enter the loop beacuse the scanf hasn't read the input
        while (checkBuffer != 1)
        {
            char buffer;
            do
            {
                scanf("%c", &buffer);
            } while (buffer != '\n');

            printf("\nYou Have Entered characters, not integers. Please try ID (1000-9999): ");

            checkBuffer = scanf("%d", &ID);
        }
    }
    printf("\n");
    for (int i = 0; i < (studentCount); i++)
    {
        // print the information of the student if we find him and if we do return will break the function
        if (ID == students[i].studentID)
        {
            printf("Student Name : %s\n", students[i].name);
            printf("Student Age : %.2d\n", students[i].age);
            printf("Student GPA : %.2f\n", students[i].gpa);
            printf("===================================\n\n\n");
            return;
        }
    }
    // if we don't found the ID of the student we will reach this area and print that we don't find it
    printf("There's no student with this ID\n");
    printf("===================================\n\n\n");
}

void displayAllStudents()
{
    printf("==== ALL THE STUDENTS MENU ====\n");
    if (studentCount != 0)
    {
        int length = strlen(students[0].name);
        // We do this just to make the table aligned by getting the tallest name and do 3 spaces after it
        for (int i = 1; i < (studentCount); i++)
        {
            if (length < strlen(students[i].name))
            {
                length = strlen(students[i].name);
            }
        }
        if (length < 4)
        {
            length = 4;
        }
        length = length + 3;
        printf("ID     ");
        printf("Name");
        // here we print spaces depends on the tallest name in the list so the table get aligned
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

            int temp = strlen(students[i].name); // here again we print spaces depends on the tallest name in the list so the table get aligned
            for (int j = 0; j < length - temp; j++)
            {
                printf(" ");
            }

            if (students[i].age > 9)
            { // we print 4 spaces for the 2 digit age  and 3 spaces after the one digit and one before it so it's going to be good aligned table
                printf("%d    ", students[i].age);
            }
            else
            {
                printf(" %d    ", students[i].age);
            }
            printf("%.2f\n", students[i].gpa);

            sumGpa = sumGpa + students[i].gpa;
            // we sum the GPAs so we can divide it on the number of students when we get out the loop and get the AVG
        }

        printf("The Total Number Of Students : %d \n", studentCount);   // print the Number of the students
        printf("Students average GPA : %.2f\n", sumGpa / studentCount); // print the AVG
        printf("===================================\n\n\n");
    }
    else if (studentCount == 0)
    {
        printf("No students in the system \n");
        printf("===================================\n\n\n");
    }
}

void saveStudentRecords()
{                                                                 // print this to let the user know that the program ended here
    FILE *fptr = fopen("students.bin", "wb");                     // Open The File
    fwrite(students, sizeof(struct Student), studentCount, fptr); // Save The Student Records
    fclose(fptr);                                                 // Close The File
    printf("%d student record(s) saved to file.\n", studentCount);
    printf("===================================\n\n\n");
}
