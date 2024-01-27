#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int signup, signin, id, ex = 1, e = 1, courseCount = 0, list = 0;
char username[100];
char password[100];
char course[100][7] = {
    "CSE001", "CSE002", "CSE005", "CSE006", "CSE008",
    "CSE009", "CSE011", "CSE013", "CSE014", "CSE016",
    "CSE017", "CSE019", "CSE120", "CSE121", "CSE022",
    "CSE024", "CSE025", "CSE026", "CSE032", "CSE033",
    "CSE134", "CSE037", "CSE039", "CSE041", "CSE042",
    "CSE044", "CSE145", "CSE047", "CSE049", "CSE050",
    "CSE051", "CSE053", "CSE054", "CSE055", "CSE158",
    "CSE059", "CSE160", "CSE061", "CSE063", "CSE064",
    "CSE065", "CSE066", "CSE068", "CSE069", "CSE071",
    "CSE072", "CSE073", "CSE076", "CSE077", "CSE081",
    "CSE082", "CSE084", "CSE185", "CSE087", "CSE088",
    "CSE089", "CSE091", "CSE092", "CSE093", "CSE196",
    "CSE199"
};

struct User
{
    char username[100];
    int id;
    char password[100];
    char repassword[100];
};

struct Course
{
    char coursecode[100];
    char coursetitle[100];
    int credit;
    int priority;
    char facultycode[4];
};

void registration();
void login();
void coursemanagement();
void listedcourse();
void insertcourse();
void deletecourse();
void replacecourse();
void requestcourse();

void printBanner()
{
    printf("*********************************************\n");
    printf("***** Academic Course Management System *****\n");
    printf("*********************************************\n\n");
}

void printLoginBanner()
{
    printf("\n\n");
    printf("                    Login                   \n");
    printf("-------------------------------------------\n");
}

void printRegistrationBanner()
{
    printf("\n\n");
    printf("                Registration                \n");
    printf("-------------------------------------------\n");
}

void courseHeader()
{
    printf("\n\n");
    printf("             Course Advising               \n");
    printf("-------------------------------------------\n");
}

int main()
{
    int choice1;

    while (ex)
    {
        e = 1;
        printBanner();

        printf("  0 Exit    1 Sign In    2 Sign Up\n");
        printf("Enter the option to continue: ");
        scanf("%d", &choice1);

        if (choice1 == 0 || choice1 == 1 || choice1 == 2)
        {
            switch (choice1)
            {
            case 0:
                system("cls");
                printBanner();
                printf("Your courses have been successfully saved in the following format (Your Information) \"namepassword.txt\" file!\n\n");
                printf("Please click X to close the compiler\n");
                ex = 0;
                break;

            case 1:
                login();
                if (signin)
                {
                    system("cls");
                    printf("\n\nWelcome, %s!\n", username);
                    printf("\nID: %d\n", id);
                    coursemanagement();
                }
                else
                {
                    system("cls");
                    printf("\n\nIncorrect password or invalid username. Failed to log in!\n\n");
                }
                break;

            case 2:
                registration();
                if (signup)
                {
                    system("cls");
                    printf("\n\nRegistration successful!\n");
                    printf("\nYour information has been saved in the Users.txt file.\n\n");
                }
                else
                {
                    system("cls");
                    printf("\n\nPassword did not match or invalid username. Unsuccessful registration!\n\n");
                }
                break;
            }
        }
        else
        {
            printf("\nInvalid option! Please enter 0 to exit, 1, or 2 to continue.\n\n");
        }

        if (ex == 0)
        {
            return 0;
        }
    }

    return 0;
}

void registration()
{
    int flag = 0;
    struct User Student;
    fflush(stdin);

    printRegistrationBanner();

    printf("Enter your Username (Only alphabets or numbers): ");
    gets(Student.username);
    printf("Enter your ID: ");
    scanf("%d", &Student.id);
    printf("Enter Password: ");
    fflush(stdin);
    gets(Student.password);
    printf("Confirm Password: ");
    fflush(stdin);
    gets(Student.repassword);

    for (int i = 0; Student.username[i] != '\0'; i++)
    {
        if (!isalnum(Student.username[i]))
        {
            flag = 1;
            break;
        }
    }

    if (strcmp(Student.password, Student.repassword) == 0 && flag == 0)
    {
        signup = 1;
        FILE *fp = fopen("Users.txt", "a");
        if (fp == NULL)
        {
            printf("\nFailed to create or open file!\n");
        }
        else
        {
            fprintf(fp, "%s\t%d\t%s\n", Student.username, Student.id, Student.password);
            fclose(fp);
        }
    }
    else
    {
        signup = 0;
    }
}

void login()
{
    struct User Student;
    fflush(stdin);

    printLoginBanner();

    printf("Enter your Username: ");
    gets(Student.username);
    printf("Enter Password: ");
    fflush(stdin);
    gets(Student.password);

    FILE *q = fopen("Users.txt", "r");
    signin = 0;

    while (fscanf(q, "%s %d %s", username, &id, password) == 3)
    {
        if (strcmp(username, Student.username) == 0 && strcmp(password, Student.password) == 0)
        {
            strcpy(username, Student.username);
            strcpy(password, Student.password);
            Student.id = id;
            signin = 1;
        }
    }
    strcpy(username, Student.username);
    strcpy(password, Student.password);
    id = Student.id;

    fclose(q);
}

void coursemanagement()
{
    int choice2;
    struct Course c1;

    while (e)
    {
        courseHeader();

        printf("\nAvailable courses are:\n");
        for (int i = 0; i < 100; i++)
        {
            printf("%s ", course[i]);
            if ((i + 1) % 10 == 0)
                printf("\n");
        }
        printf("  0 Return to main menu\n  1 View listed courses\n  2 Insert new course\n  3 Delete an existing course\n  4 Replace with an existing course\n  5 Request for an unavailable course \n");
        printf("Enter the option to continue: ");
        scanf("%d", &choice2);

        if (choice2 == 0 || choice2 == 1 || choice2 == 2 || choice2 == 3 || choice2 == 4 || choice2 == 5)
        {
            switch (choice2)
            {
            case 0:
                system("cls");
                printf("\nReturned to landing page \n\n\n");
                e = 0;
                break;
            case 1:
                listedcourse();
                break;
            case 2:
                insertcourse();
                break;
            case 3:
                deletecourse();
                break;
            case 4:
                replacecourse();
                break;
            case 5:
                requestcourse();
                break;
            }
        }
        else
        {
            printf("\nInvalid option! Please enter 1 to 5 continue operations or 0 to main menu.\n\n");
        }
    }
}

void listedcourse()
{
    FILE *fp;
    char fileName[15];
    strcpy(fileName, username);
    strcat(fileName, password);
    strcat(fileName, ".txt");
    fp = fopen(fileName, "r");

    if (fp == NULL)
    {
        system("cls");
        printf("No courses listed for the user.\n");
    }
    else
    {
        system("cls");
        printf("\nAdvised Courses:\n");
        char line[256];
        while (fgets(line, sizeof(line), fp))
        {
            printf("%s", line);
            list = 1;
        }
        if (list == 0)
        {
            printf("\nYour course list is empty\n");
        }
        fclose(fp);
    }
}

void insertcourse()
{
    listedcourse();
    FILE *fp;
    char fileName[15];
    strcpy(fileName, username);
    strcat(fileName, password);
    strcat(fileName, ".txt");
    fp = fopen(fileName, "a");
    if (fp == NULL)
    {
        printf("\nFailed to open file for course insertion.\n");
    }
    else
    {
        struct Course newCourse;

        if (courseCount < 10)
        {
            printf("Enter Course Code: ");
            fflush(stdin);
            scanf("%s", newCourse.coursecode);
            printf("Enter Course Title: ");
            fflush(stdin);
            scanf("%s", newCourse.coursetitle);
            printf("Enter Course Credit: ");
            fflush(stdin);
            scanf("%d", &newCourse.credit);
            printf("Enter Course Priority: ");
            fflush(stdin);
            scanf("%d", &newCourse.priority);
            printf("Enter Faculty Code: ");
            fflush(stdin);
            scanf("%s", newCourse.facultycode);
            courseCount++;
            fprintf(fp, "%s\t%s\t%d\t%d\t%s\n", newCourse.coursecode, newCourse.coursetitle, newCourse.credit, newCourse.priority, newCourse.facultycode);
            system("cls");
            printf("\nCourse inserted successfully. Total course taken %d\n", courseCount);
        }
        else
        {
            system("cls");
            printf("\nCourse limit reached. Cannot insert more courses.\n");
        }

        fclose(fp);
    }
}

void deletecourse()
{
    char delet[7];
    listedcourse();
    printf("Enter Course Code to delete: ");
    fflush(stdin);
    scanf("%s", delet);

    FILE *fp, *temp;
    char fileName[15];
    strcpy(fileName, username);
    strcat(fileName, password);
    strcat(fileName, ".txt");

    fp = fopen(fileName, "r");
    temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL)
    {
        printf("\nFailed to open files for course deletion.\n");
    }
    else
    {
        int found = 0;
        struct Course courseToDelete;

        while (fscanf(fp, "%s %s %d %d %s", courseToDelete.coursecode, courseToDelete.coursetitle, &courseToDelete.credit, &courseToDelete.priority, courseToDelete.facultycode) == 5)
        {
            if (strcmp(courseToDelete.coursecode, delet) == 0)
            {
                found = 1;
            }
            else
            {
                fprintf(temp, "%s\t%s\t%d\t%d\t%s\n", courseToDelete.coursecode, courseToDelete.coursetitle, courseToDelete.credit, courseToDelete.priority, courseToDelete.facultycode);
            }
        }

        fclose(fp);
        fclose(temp);

        if (found)
        {
            remove(fileName);
            rename("temp.txt", fileName);
            system("cls");
            printf("\nCourse deleted successfully.\n");
        }
        else
        {
            remove("temp.txt");
            system("cls");
            printf("\nCourse not found.\n");
        }
    }
}

void replacecourse()
{
    char replace[7];
    listedcourse();
    printf("Enter Course Code to replace: ");
    fflush(stdin);
    scanf("%s", replace);

    FILE *fp, *temp;
    char fileName[15];
    strcpy(fileName, username);
    strcat(fileName, password);
    strcat(fileName, ".txt");

    fp = fopen(fileName, "r");
    temp = fopen("temp.txt", "w");

    if (list == 0)
    {
        printf("\nYour courselist is empty. Please insert a course.\n");
        insertcourse();
    }
    else
    {
        if (fp == NULL || temp == NULL)
        {
            printf("\nFailed to open files for course replacement.\n");
        }
        else
        {
            int found = 0;
            struct Course newCourse;
            struct Course courseToReplace;

            while (fscanf(fp, "%s %s %d %d %s", courseToReplace.coursecode, courseToReplace.coursetitle, &courseToReplace.credit, &courseToReplace.priority, courseToReplace.facultycode) == 5)
            {
                if (strcmp(courseToReplace.coursecode, replace) == 0)
                {
                    found = 1;
                    printf("\nEnter new Course Code: ");
                    fflush(stdin);
                    scanf("%s", newCourse.coursecode);
                    printf("Enter new Course Title: ");
                    fflush(stdin);
                    scanf("%s", newCourse.coursetitle);
                    printf("Enter new Course Credit: ");
                    scanf("%d", &newCourse.credit);
                    printf("Enter new Course Priority: ");
                    scanf("%d", &newCourse.priority);
                    printf("Enter new Faculty Code: ");
                    fflush(stdin);
                    scanf("%s", newCourse.facultycode);

                    fprintf(temp, "%s\t%s\t%d\t%d\t%s\n", newCourse.coursecode, newCourse.coursetitle, newCourse.credit, newCourse.priority, newCourse.facultycode);
                }
                else
                {
                    fprintf(temp, "%s\t%s\t%d\t%d\t%s\n", courseToReplace.coursecode, courseToReplace.coursetitle, courseToReplace.credit, courseToReplace.priority, courseToReplace.facultycode);
                }
            }

            fclose(fp);
            fclose(temp);

            if (found)
            {
                remove(fileName);
                rename("temp.txt", fileName);
                system("cls");
                printf("\nCourse replaced successfully.\n");
            }
            else
            {
                remove("temp.txt");
                system("cls");
                printf("\nCourse not found.\n");
            }
        }
    }
}

void requestcourse()
{
    char requestedCourse[7];
    printf("Enter the Course Code to request: ");
    scanf("%s", requestedCourse);

    int courseAvailable = 0;

    for (int i = 0; i < 100; i++)
    {
        if (strcmp(requestedCourse, course[i]) == 0)
        {
            courseAvailable = 1;
            break;
        }
    }

    if (courseAvailable)
    {
        system("cls");
        printf("\nThe course %s is available!\n", requestedCourse);
    }
    else
    {
        system("cls");
        if (requestedCourse[0] == 'C' && requestedCourse[1] == 'S' && requestedCourse[2] == 'E')
            printf("\nThe course %s is requested!\n", requestedCourse);
        else
            printf("Invalid name");
    }
}
