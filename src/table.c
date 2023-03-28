#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>

#include "/home/siddarths/dev/c/SpellCheck/inc/list.h"
#include "/home/siddarths/dev/c/SpellCheck/inc/table.h"

int words = 0;

unsigned int hash(const char *word)
{
    unsigned int hashcode = 0;
    int length = strlen(word);

    for (int i = 0; i < length; i++)
    {
        // weighted sum of all letters, i capped to 4 because of memory limitations
        if (((toupper(word[i]) - 'A') > 0))
        {
            hashcode += (toupper(word[i]) - 'A') * 26.0 * (int)pow(26.0, i - 1);
        }
        else
        {
            if (((toupper(word[i]) - 'A') > 0))
            {
                hashcode += (toupper(word[i]) - 'A') * i;
            }
        }
    }

    return hashcode;
}

bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    char word[MAX_LENGTH + 1];
    char c;

    int index = 0;
    words = 0;

    int hashcode;

    while (fread(&c, sizeof(char), 1, dict))
    {
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            word[index] = c;
            index++;

            if (index > MAX_LENGTH)
            {
                while (fread(&c, sizeof(char), 1, dict) && isalpha(c))
                    ;

                hashcode = hash(word);
                table[hashcode] = insert(word, table[hashcode]);
                words++;
                index = 0;
            }
        }

        else if (isdigit(c))
        {
            while (fread(&c, sizeof(char), 1, dict) && isalnum(c))
                ;

            hashcode = hash(word);
            table[hashcode] = insert(word, table[hashcode]);
            words++;
            index = 0;
        }

        else if (index > 0)
        {
            word[index] = '\0';

            hashcode = hash(word);
            table[hashcode] = insert(word, table[hashcode]);
            words++;
            index = 0;
        }
    }

    if (ferror(dict))
    {
        fclose(dict);
        return false;
    }

    fclose(dict);
    return true;
}

unsigned int size(void)
{
    return words;
}

bool free_dict(void)
{
    int listcounter = 0;

    for (int i = 0; i < BUCKETS; i++)
    {
        if (table[i] == NULL)
        {
            listcounter++;
            continue;
        }
        destroy(table[i]);
    }

    if (listcounter == BUCKETS)
    {
        return false;
    }

    return true;
}