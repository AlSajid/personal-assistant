#include <stdio.h>      ///basic input-output functions
#include <time.h>       ///time & date related functions
#include <string.h>     ///string related functions
#include <conio.h>      ///for using getch() functions
#include <windows.h>    ///windows console related functions


///a function that returns current date
const char * date ()
{
    time_t now = time(NULL);                            ///time() with NULL parameter returns current date-time
    struct tm *date = localtime(&now);                  ///it contains date-time in a struct

    static char data[15];                               ///it contains date
    strftime(data, sizeof(data), "%d%m%Y", date);       ///formatting the date in a string
    return data;
}
struct date
{
    char name[100], date[4], month[4], year[6];
} add;

///a function to add a task
void addTask ()
{
    system("cls");
    printf("******************************\n");
    printf("***        Add Task        ***\n");
    printf("******************************\n");
    printf("\n\n");

    printf("\nWhat task do you want to add?\n");
    gets(add.name);                //read task name

    printf("\nWhen do you want to %s? [dd mm year]\n", add.name);
    scanf("%s", &add.date);
    scanf("%s", &add.month);
    scanf("%s", &add.year);                     //read task date

    //create file path
    char path[30];              //contains file path
    strcpy(path, "./tasks/");   //add directory name in file path
    strcat(path, add.date);        //add date in file path
    strcat(path, add.month);        //add month in file path
    strcat(path, add.year);        //add year in file path
    strcat(path, ".txt");       //add file extension in file path

    //add task in file
    FILE *addtask = fopen(path, "a");
    fprintf(addtask, "%s\n", add.name);
    fclose(addtask);

    printf("\nThe task has been added successfully\n");
    system("pause");
    return;
}

void updateTask ()
{
    system("cls");
    printf("******************************\n");
    printf("****      Update Task      ***\n");
    printf("******************************\n");
    printf("\n\n");

    char taskd[4], taskm[4], tasky[6];
    printf("\nDate of the Task? [dd mm year]\n");     //contains task date
    scanf("%s %s %s", &taskd, &taskm, &tasky);    //read task date

    //create file path
    char path[30];
    strcpy(path, "./tasks/");
    strcat(path, taskd);
    strcat(path, taskm);
    strcat(path, tasky);
    strcat(path, ".txt");

    char output[100];
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        printf("No task found in %s/%s/%s", taskd, taskm, tasky);
    }
    else
    {
        printf("\nIn %s/%s/2019, List of Your Task(s)\n", taskd, taskm, tasky);
        printf("************************************************************\n\n");

        int i = 0;
        while (fgets(output, sizeof(output), file) != NULL)
        {
            i++;
            printf("%d. %s", i, output);

        }
        fclose(file);

        int line;
        printf("\n\nWhich task Do You Want to Update?\n");
        scanf("%d", &line);
        getchar();

        char newtask[100];                                  // contains task name
        printf("\nWhat task do you want to add?\n");
        gets(newtask);                                      //read task name

        FILE *uptask = fopen("./tasks/tmp.txt", "a");
        FILE *file = fopen(path, "r");

        i=0;
        while (fgets(output, sizeof(output), file) != NULL)
        {
            i++;
            if (i == line)
                fprintf(uptask, "%s\n", newtask);
            else
                fprintf(uptask, "%s", output);


        }
        fclose(uptask);
        fclose(file);

        remove(path);
        int p = rename("./tasks/tmp.txt", path);

        if(p == 0)
            printf("\n%d no task has been updated successfully\n\n", line);
        else
            printf("\nError: Unable to update the task\n\n");

        system("pause");
    }
}

void cmpltTask ()
{

    system("cls");
    printf("\t\t\t******************************\n");
    printf("\t\t\t****     Complete Task     ***\n");
    printf("\t\t\t******************************\n");
    printf("\n\n");

    char taskd[4], taskm[4], tasky[6];
    printf("\nDate of the Task? [dd mm year]\n");     //contains task date
    scanf("%s %s %s", &taskd, &taskm, &tasky);    //read task date

    //create file path
    char path[30];
    strcpy(path, "./tasks/");
    strcat(path, taskd);
    strcat(path, taskm);
    strcat(path, tasky);
    strcat(path, ".txt");

    char output[100];
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        printf("No task found in %s/%s/%s", taskd, taskm, tasky);
    }
    else
    {
        printf("\nIn %s/%s/2019, List of Your Task(s)\n", taskd, taskm, tasky);
        printf("************************************************************\n\n");

        int i = 0;
        while (fgets(output, sizeof(output), file) != NULL)
        {
            i++;
            printf("%d. %s", i, output);

        }
        fclose(file);

        int line;
        printf("\n\nWhich task Do You Want to flag as completed?\n");
        scanf("%d", &line);
        getchar();

        FILE *uptask = fopen("./tasks/tmp.txt", "a");
        FILE *file = fopen(path, "r");
        FILE *cmplt = fopen("./tasks/completed.txt", "a");

        i=0;
        while (fgets(output, sizeof(output), file) != NULL)
        {
            i++;
            if (i == line)
                fprintf(cmplt, "%s", output);
            else
                fprintf(uptask, "%s", output);


        }
        fclose(uptask);
        fclose(file);
        fclose(cmplt);

        remove(path);
        int p = rename("./tasks/tmp.txt", path);

        if(p == 0)
            printf("\n%d no task has been flagged successfully\n\n", line);
        else
            printf("\nError: Unable to update the task\n\n");

        system("pause");
    }
}
void cancelTask ()
{
    system("cls");
    printf("\t\t\t******************************\n");
    printf("\t\t\t****      Cancel Task      ***\n");
    printf("\t\t\t******************************\n");
    printf("\n\n");


    char taskd[4], taskm[4], tasky[6];
    printf("\nDate of the Task? [dd mm year]\n");     //contains task date
    scanf("%s %s %s", &taskd, &taskm, &tasky);    //read task date

    //create file path
    char path[30];
    strcpy(path, "./tasks/");
    strcat(path, taskd);
    strcat(path, taskm);
    strcat(path, tasky);
    strcat(path, ".txt");

    char output[100];
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        printf("No task found in %s/%s/%s", taskd, taskm, tasky);
    }
    else
    {
        printf("\nIn %s/%s/2019, List of Your Task(s)\n", taskd, taskm, tasky);
        printf("************************************************************\n\n");

        int i = 0;
        while (fgets(output, sizeof(output), file) != NULL)
        {
            i++;
            printf("%d. %s", i, output);

        }
        fclose(file);

        int line;
        printf("\n\nWhich task Do You Want to cancel?\n");
        scanf("%d", &line);
        getchar();

        FILE *uptask = fopen("./tasks/tmp.txt", "a");
        FILE *file = fopen(path, "r");

        i=0;
        while (fgets(output, sizeof(output), file) != NULL)
        {
            i++;
            if (i != line)
                fprintf(uptask, "%s", output);


        }
        fclose(uptask);
        fclose(file);

        remove(path);
        int p = rename("./tasks/tmp.txt", path);

        if(p == 0)
            printf("\n%d no task has been canceled successfully\n\n", line);
        else
            printf("\nError: Unable to update the task\n\n");

        system("pause");
    }

}

void nextTask ()
{
    system("cls");
    printf("\t\t\t******************************\n");
    printf("\t\t\t****  Check Upcoming Task  ***\n");
    printf("\t\t\t******************************\n");
    printf("\n\n");

    char path[30];
    strcpy(path, "./tasks/");
    strcat(path, date());
    strcat(path, ".txt");

    char output[1000];
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        printf("\n\nNo Upcoming Task Found\n\n");
    }
    else
    {
        printf("\n\nList of Your Upcoming Task(s):\n");
        printf("************************************************************\n\n");
        int i = 0;

        while (fgets(output, sizeof(output), file) != NULL)
        {
            i++;
            printf("%d. %s", i, output);
        }
    }
    fclose(file);

    system("pause");
}

void checkTask ()
{
    system("cls");
    printf("******************************\n");
    printf("*   Tasks of Specific Date   *\n");
    printf("******************************\n");
    printf("\n\n");

    char taskd[4], taskm[4], tasky[6];
    printf("\nDate of the Task? [dd mm year]\n");     //contains task date
    scanf("%s %s %s", &taskd, &taskm, &tasky);    //read task date

    //create file path
    char path[30];
    strcpy(path, "./tasks/");

    strcat(path, taskd);
    strcat(path, taskm);
    strcat(path, tasky);
    strcat(path, ".txt");

    char output[1000];
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        printf("\nNo task found in %s/%s/%s\n\n", taskd, taskm, tasky);
    }
    else
    {
        printf("\nIn %s/%s/%s, List of Your Task(s):\n", taskd, taskm, tasky);
        printf("************************************************************\n\n");

        int i = 0;

        while (fgets(output, sizeof(output), file) != NULL)
        {
            i++;
            printf("%d. %s", i, output);
        }
        printf("\n\n");
    }
    fclose(file);

    system("pause");
    return;
}

void checkDone ()
{
    system("cls");
    printf("******************************\n");
    printf("****    Completed  Task    ***\n");
    printf("******************************\n");
    printf("\n\n");

    char path[30];
    strcpy(path, "./tasks/");
    strcat(path, "completed");
    strcat(path, ".txt");

    char output[1000];
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        printf("\n\nNo Completed Task Found\n\n");
    }
    else
    {
        printf("\nList of Your Completed Task(s):\n");
        printf("************************************************************\n\n");
        int i = 0;

        while (fgets(output, sizeof(output), file) != NULL)
        {
            i++;
            printf("%d. %s", i, output);
        }
        printf("\n\n");
    }
    fclose(file);
    system("pause");
}

void bye ()
{
    char ans[5];
    printf("\nDo you really want to exit?\n");
    scanf ("%[^\n]%*c", ans);
    if(strcmp(ans, "Yes") == 0 || strcmp(ans, "yes") == 0 || strcmp(ans, "sure") == 0)
    {
        system("cls");
        exit (1);
    }


}

void home ()
{
    printf("**************************************************\n");
    printf("******                                      ******\n");
    printf("****            Personal  Assistant            ***\n");
    printf("******                                      ******\n");
    printf("**************************************************\n");

    printf("\n\n\n");
    printf("1. Add task\n");
    printf("2. Update task\n");
    printf("3. Complete task\n");
    printf("4. Cancel task\n");
    printf("5. Upcoming task\n");
    printf("6. Check tasks of specific date\n");
    printf("7. Check completed task\n");
    printf("8. Exit\n");
    printf("\n");

    printf("Enter your choice: ");
    int ans;                //contains the choice from user
    scanf("%d", &ans);       //read the choice from user
    getchar();

    switch (ans)
    {
    case 1:
        addTask();
        break;
    case 2:
        updateTask ();
        break;
    case 3:
        cmpltTask ();
        break;
    case 4:
        cancelTask();
        break;
    case 5:
        nextTask();
        break;
    case 6:
        checkTask();
        break;
    case 7:
        checkDone();
        break;
    case 8:
        bye();
        break;

    }
    system("cls");
    home();

    return;
}

int main ()
{
    home ();
    return 0;
}

