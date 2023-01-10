#include <stdio.h>
#include <string.h>
#include <dirent.h>

void displayDescription();
int getTasksNumber(int *tasksNumber);
int displayList(int tasksNumber);

int main()
{
    int tasksNumber;

    // displayDescription();

    getTasksNumber(&tasksNumber);

    printf("\n");
    printf("You have %d tasks to do:\n", tasksNumber);
    printf("\n");

    displayList(tasksNumber);

    return 0;
}

void displayDescription()
{
    printf("Hi! This is a terminal prototype of Just One List app.\n\n");
    printf("The idea behind Just One List is to have (so insightful, I know) just ONE list - 'To do', instead of 'work', 'school', 'development', 'shopping', etc.\n\n");
    printf("The purpose is to work and complete only the task at the top of the list. This way, you don't get distracted by less prioritized tasks.\n");
}

int getTasksNumber(int *tasksNumber)
{
    int filesCounter = 0;
    DIR *dir;
    struct dirent *entry;

    dir = opendir("./tasks");
    if (dir == NULL)
    {
        printf("Error in getTasksNumber(): Cannot open directory");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_REG)
        {
            filesCounter++;
        }
    }

    closedir(dir);

    *tasksNumber = filesCounter;

    return 0;
}

int displayList(int tasksNumber)
{
    FILE *file;
    char taskContent[100];

    for (int i = 1; i <= tasksNumber; i++)
    {
        char pathToFile[100] = "./tasks/task_";
        char strNumber[3];

        snprintf(strNumber, sizeof(strNumber), "%d", i);
        strcat(pathToFile, strNumber);
        strcat(pathToFile, ".txt");

        file = fopen(pathToFile, "r");

        if (file == NULL)
        {
            printf("Error in displayList(): Cannot open file");
            return 1;
        }

        while (fgets(taskContent, 100, file) != NULL)
        {
            printf("    ");

            printf("☐ ");

            if(i == 1) {
                printf("\033[42m");
            }
            printf("%s", taskContent);

            if(i == 1) {
                printf("\033[0m");
            }
        }

        fclose(file);

        printf("\n");
        printf("\n");
    }
    return 0;
}