#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hlavicka.h"


int main(int argc, char **argv)
{
    int counter = 0;
    char *cesta_in;
    char *cesta_out;
    char *buffer;
    long lSize;
    char *command;

    parametry_check(&cesta_in, &cesta_out, argc, argv);

    FILE *input = fopen(cesta_in, "r");
    if (input == NULL)
    {
        printf("Chyba pri otevreni vstupu\n");
        destroy_in_out(&cesta_in, &cesta_out);
        return 1;
    }

    FILE *output = fopen(cesta_out, "w");
    if (output == NULL)
    {
        printf("Chyba pri otevreni vystupu\n");
        destroy_in_out(&cesta_in, &cesta_out);
        return 1;
    }

    fseek(input, 0L, SEEK_END);
    lSize = ftell(input);
    rewind(input);

    buffer = calloc(1, lSize + 1);
    if (!buffer)
        fclose(input), fputs("memory alloc fails", stderr), exit(1);

    if (1 != fread(buffer, lSize, 1, input))
        fclose(input), free(buffer), fputs("entire read fails", stderr), exit(1);

    fclose(input);

    int cols = 0;
    int rows = 0;

    stats(&buffer, &rows, &cols);
    printf("Soubor: %s, sloupce: %d, radky: %d\n", cesta_in, cols, rows);

    char **text = (char **)malloc(rows * (sizeof(char *)));

    create(text, &buffer, rows);
    free(buffer);

    do
    {
        printf("Zadejte prikaz: ");
        fgets(command, 255, stdin);

        if (strstr(command, "addrow"))
        {
            rows++;
            if (test_stats(&command, &rows, &cols))
            {

                text = (char **)realloc(text, rows * (sizeof(char *)));
                addrow(text, &command, rows);
            }
            else
            {
                rows--;
                printf("Zadano malo/hodne sloupcu!!!\n");
            }
        }
        else if (strstr(command, "addcol"))
        {
            cols++;
            if (test_stats(&command, &rows, &cols))
            {
                addcol(text, &command, rows);
            }
            else
            {
                cols--;
                printf("Zadano malo/hodne sloupcu na radky, nebo jste nepojmenoval radek!!!\n");
            }
        }
        else if (strstr(command, "average"))
        {
            if (existuje(text, &command, rows, cols))
            {
                average(text, &command, rows, cols);
            }
            else
            {
                printf("Zadany sloupec se nenasel\n");
            }
        }
        else if (strstr(command, "max"))
        {
            if (existuje(text, &command, rows, cols))
            {
                max(text, &command, rows, cols);
            }
            else
            {
                printf("Zadany sloupec se nenasel\n");
            }
        }
        else if (strstr(command, "min"))
        {
            if (existuje(text, &command, rows, cols))
            {
                min(text, &command, rows, cols);
            }
            else
            {
                printf("Zadany sloupec se nenasel\n");
            }
        }
        else if (strstr(command, "sum"))
        {
            if (existuje(text, &command, rows, cols))
            {
                sum(text, &command, rows, cols);
            }
            else
            {
                printf("Zadany sloupec se nenasel\n");
            }
        }
        else if (strstr(command, "exit") == 0)
        {
            printf("Zadany prikaz se nenasel!!!\n");
        }

    } while ((strcmp(command, "exit\n")) != 0);

    printf("Ukladam databazi do souboru %s.\n", cesta_out);

    for (int i = 0; i < rows; i++)
    {
        fwrite(text[i], sizeof(char), strlen(text[i]), output);
        if (i != (rows - 1))
        {
            fwrite("\n", sizeof(char), 1, output);
        }
    }
    fclose(output);
    destroy_in_out(&cesta_in, &cesta_out);
    destroy_arr(text, rows);
    return 0;
}