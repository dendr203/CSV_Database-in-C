#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void addrow(char **text, char **command, int rows)
{
    char *token;
    int pomoc = rows - 1;
    int velikost = 0;

    token = strtok(*command, " ");
    token = strtok(NULL, "\n");

    velikost = strlen(token);
    text[pomoc] = (char *)malloc(sizeof(char) * velikost + 1);
    strcpy(text[pomoc], token);

    printf("Radek byl pridan\n");
}

void addcol(char **text, char **command, int rows)
{
    char *token;
    int velikost = 0;
    int pomoc = rows - 2;

    token = strtok(*command, " ");
    token = strtok(NULL, " ");

    velikost = strlen(text[0]) + strlen(token) + 2;
    char *radek = (char *)malloc(sizeof(char) * velikost);
    strcpy(radek, text[0]);
    strcat(radek, ",");
    strcat(radek, token);

    text[0] = (char *)realloc(text[0], sizeof(char) * velikost);
    strcpy(text[0], radek);
    token = strtok(NULL, ",");

    for (int i = 1; i < rows; i++)
    {
        velikost = strlen(text[i]) + strlen(token) + 2;
        radek = (char *)realloc(radek, sizeof(char) * velikost);
        strcpy(radek, text[i]);
        strcat(radek, ",");
        strcat(radek, token);

        text[i] = (char *)realloc(text[i], sizeof(char) * velikost);
        strcpy(text[i], radek);
        if (i == pomoc)
        {
            token = strtok(NULL, "\n");
        }
        else
        {
            token = strtok(NULL, ",");
        }
    }

    printf("Sloupec byl pridan\n");

    free(radek);
}

bool test_stats(char **command, int *rows, int *cols)
{
    char *token;
    char *help = (char *)malloc(sizeof(char) * (strlen(*command) + 1));
    strcpy(help, *command);

    if (strstr(help, "addrow"))
    {
        token = strtok(help, " ");
        token = strtok(NULL, ",");
        int sloupce_compare = 0;
        while (token != NULL)
        {
            sloupce_compare++;
            token = strtok(NULL, ",");
        }

        free(help);
        if (sloupce_compare != *cols)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else if (strstr(help, "addcol"))
    {
        token = strtok(help, " ");
        int radky_compare = 0;
        token = strtok(NULL, " ");
        radky_compare++;
        token = strtok(NULL, ",");

        while (token != NULL)
        {
            radky_compare++;
            token = strtok(NULL, ",");
        }

        free(help);
        if (radky_compare == *rows)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool existuje(char **text, char **command, int rows, int cols)
{
    char *token;
    char *help = (char *)malloc(sizeof(char) * (strlen(*command) + 1));
    strcpy(help, *command);
    token = strtok(help, " ");
    token = strtok(NULL, "\n");
    if (token == NULL)
    {
        return false;
    }
    

    char *radek = (char *)malloc(sizeof(char) * (strlen(text[0]) + 1));
    strcpy(radek, text[0]);

    if (strstr(radek, token))
    {
        free(help);
        free(radek);
        return true;
    }
    else
    {
        free(help);
        free(radek);
        return false;
    }
}

void average(char **text, char **command, int rows, int cols)
{
    char *token;
    char *token_r;
    int sloupec = 0;
    float vypocet = 0;
    token = strtok(*command, " ");
    token = strtok(NULL, "\n");
    

    char *radek = (char *)malloc(sizeof(char) * (strlen(text[0]) + 1));
    strcpy(radek, text[0]);
    token_r = strtok(radek, ",");

    while (token_r != NULL)
    {
        if (strcmp(token_r, token) == 0)
        {
            break;
        }
        sloupec++;
        token_r = strtok(NULL, ",");
    }

    for (int i = 1; i < rows; i++)
    {
        radek = (char *)realloc(radek, sizeof(char) * (strlen(text[i]) + 1));
        strcpy(radek, text[i]);

        token = strtok(radek, ",");
        for (int j = sloupec; j > 0; j--)
        {
            token = strtok(NULL, ",");
        }

        if (atof(token))
        {
            vypocet += atof(token);
        }
    }
    vypocet = vypocet / (rows - 1);

    printf("Prumer sloupce: %0.1f\n", vypocet);

    free(radek);
}

void max(char **text, char **command, int rows, int cols)
{
    char *token;
    char *token_r;
    int sloupec = 0;
    float max = 0;
    float pomoc = 0;

    token = strtok(*command, " ");
    token = strtok(NULL, "\n");

    char *radek = (char *)malloc(sizeof(char) * (strlen(text[0]) + 1));
    strcpy(radek, text[0]);
    token_r = strtok(radek, ",");

    while (token_r != NULL)
    {
        if (strcmp(token_r, token) == 0)
        {
            break;
        }
        sloupec++;
        token_r = strtok(NULL, ",");
    }

    for (int i = 1; i < rows; i++)
    {
        radek = (char *)realloc(radek, sizeof(char) * (strlen(text[i]) + 1));
        strcpy(radek, text[i]);

        token = strtok(radek, ",");
        for (int j = sloupec; j > 0; j--)
        {
            token = strtok(NULL, ",");
        }

        if (atof(token))
        {
            pomoc = atof(token);
            if (pomoc > max)
            {
                max = pomoc;
            }
        }
    }

    printf("Maximum sloupce: %0.1f\n", max);

    free(radek);
}

void min(char **text, char **command, int rows, int cols)
{
    char *token;
    char *token_r;
    int sloupec = 0;
    float min = __INT_FAST32_MAX__;
    float pomoc = 0;

    token = strtok(*command, " ");
    token = strtok(NULL, "\n");

    char *radek = (char *)malloc(sizeof(char) * (strlen(text[0]) + 1));
    strcpy(radek, text[0]);
    token_r = strtok(radek, ",");

    while (token_r != NULL)
    {
        if (strcmp(token_r, token) == 0)
        {
            break;
        }
        sloupec++;
        token_r = strtok(NULL, ",");
    }

    for (int i = 1; i < rows; i++)
    {
        radek = (char *)realloc(radek, sizeof(char) * (strlen(text[i]) + 1));
        strcpy(radek, text[i]);

        token = strtok(radek, ",");
        for (int j = sloupec; j > 0; j--)
        {
            token = strtok(NULL, ",");
        }

        if (atof(token))
        {
            pomoc = atof(token);
            if (min > pomoc)
            {
                min = pomoc;
            }
        }
        else
        {
            
        }
    }

    if (min == __INT_FAST32_MAX__)
    {
        min = 0;
    }
    

    printf("Minimum sloupce: %0.1f\n", min);

    free(radek);
}

void sum(char **text, char **command, int rows, int cols)
{
    char *token;
    char *token_r;
    int sloupec = 0;
    float sum = 0;

    token = strtok(*command, " ");
    token = strtok(NULL, "\n");

    char *radek = (char *)malloc(sizeof(char) * (strlen(text[0]) + 1));
    strcpy(radek, text[0]);
    token_r = strtok(radek, ",");

    while (token_r != NULL)
    {
        if (strcmp(token_r, token) == 0)
        {
            break;
        }
        sloupec++;
        token_r = strtok(NULL, ",");
    }

    for (int i = 1; i < rows; i++)
    {
        radek = (char *)realloc(radek, sizeof(char) * (strlen(text[i]) + 1));
        strcpy(radek, text[i]);

        token = strtok(radek, ",");
        for (int j = sloupec; j > 0; j--)
        {
            token = strtok(NULL, ",");
        }

        if (atof(token))
        {
            sum += atof(token);
        }
    }

    printf("Sum sloupce: %0.1f\n", sum);

    free(radek);
}