#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int amt, i;
    char c;
    int hash[26] = {0};

    scanf("%d", &amt);

    if (amt == 1 || amt > 26)
    {
        printf("I'm the god of Knuckles!\n");
    }
    else
    {
        for (i = 0; i < amt; i++)
        {
            scanf("%c", &c);
            hash[c - 'a']++;
        }

        int find = 0;
        for (i = 0; i < 26; i++)
        {
            if (hash[i] > 1)
                find++;
        }

        if (find == 0)
            printf("Different makes perfect\n");
        else
            printf("I'm the god of Knuckles!\n");
    }

    return 0;
}