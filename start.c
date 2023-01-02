#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parametry_check(char **cesta_in, char **cesta_out, int argc, char **argv)
{
    int check = 0;
    int check_in = 0;
    int check_out = 0;

    for (int i = 0; i < argc; i++)
    {

        if ((strcmp(argv[i], "--input")) == 0)
        {
            check_in++;
        }
        else if ((strcmp(argv[i], "--output")) == 0)
        {
            check_out++;
        }
    }

    if ((check_in > 1) || (check_out > 1))
    {
        printf("Mnoho zadanych parametru!!!\n");
        exit(1);
    }

    for (int i = 0; i < argc; i++)
    {
        if ((strcmp(argv[i], "--input")) == 0)
        {
            *cesta_in = (char *)malloc(sizeof(char) * strlen(argv[i + 1]) + 1);
            strcpy(*cesta_in, argv[i + 1]);
            check++;
        }
        else if ((strcmp(argv[i], "--output")) == 0)
        {
            *cesta_out = (char *)malloc(sizeof(char) * strlen(argv[i + 1]) + 1);
            strcpy(*cesta_out, argv[i + 1]);
            check++;
        }
    }
    if ((check < 2) || (check > 2))
    {
        printf("Spatne zadane parametry!!!\n");
        exit(1);
    }
}

void stats(char **buffer, int *rows, int *cols)
{
    char *token1;
    char *token2;

    char *text = (char *)malloc((strlen(*buffer) * (sizeof(char)) + 1));
    strcpy(text, *buffer);
    token1 = strtok(text, "\n");

    while (token1 != NULL)
    {
        *rows = *rows + 1;
        token1 = strtok(NULL, "\n");
    }

    token1 = strtok(text, "\n");
    token2 = strtok(token1, ",");

    while (token2 != NULL)
    {
        *cols = *cols + 1;
        token2 = strtok(NULL, ",");
    }
    free(text);
}

void create(char **text, char **buffer, int rows)
{
    char *token;
    char *help = (char *)malloc((strlen(*buffer) * (sizeof(char)) + 1));

    strcpy(help, *buffer);
    token = strtok(help, "\n");
    for (int i = 0; i < rows; i++)
    {
        text[i] = (char *)malloc(strlen(token) * sizeof(char) + 1);
        strcpy(text[i], token);
        token = strtok(NULL, "\n");
    }
    free(help);
}