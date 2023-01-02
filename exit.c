#include <stdlib.h>

void destroy_arr(char **text, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(text[i]);
    }

    free(text);
}

void destroy_in_out(char **cesta_in, char **cesta_out)
{
    free(*cesta_in);
    free(*cesta_out);
}