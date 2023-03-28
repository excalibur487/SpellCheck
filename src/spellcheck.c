#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>

#include "/home/siddarths/dev/c/SpellCheck/inc/list.h"
#include "/home/siddarths/dev/c/SpellCheck/inc/table.h"

#define DICTIONARY "/home/siddarths/dev/c/SpellCheck/test/test-files/large.txt"

/**
 * @brief Hash Table
 *
 */
node *table[BUCKETS];

int words = 0;

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int hashcode = 0;
    int length = strlen(word);

    for (int i = 0; i < length; i++)
    {
        //weighted sum of all letters, i capped to 4 because of memory limitations
        if (((toupper(word[i]) - 'A') > 0) && (i < 4))
        {
            hashcode += (toupper(word[i]) - 'A') * (int)pow(26.0, i);
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

bool populate(const char *dictionary)
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
                table[hashcode] = add_node(word, table[hashcode]);
                words++;
                index = 0;
            }
        }

        else if (isdigit(c))
        {
            while (fread(&c, sizeof(char), 1, dict) && isalnum(c))
                ;

            hashcode = hash(word);
            table[hashcode] = add_node(word, table[hashcode]);
            //visualize(table[hashcode]);
            words++;
            index = 0;
        }

        else if (index > 0)
        {
            word[index] = '\0';

            hashcode = hash(word);
            table[hashcode] = add_node(word, table[hashcode]);
            //visualize(table[hashcode]);
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

bool check(char *word)
{
    unsigned int hashcode = hash(word);

    return search_node(word, table[hashcode]);
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
        free_list(table[i]);
    }

    if (listcounter == BUCKETS)
    {
        return false;
    }

    return true;
}

int main(int argc, char *argv[])
{
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./speller [DICTIONARY] text\n");
        return 1;
    }

    // Determine dictionary to use
    char *dictionary = (argc == 3) ? argv[1] : DICTIONARY;

    bool loaded = populate(dictionary);

    // Exit if dictionary not loaded
    if (!loaded)
    {
        printf("Could not load %s.\n", dictionary);
        return 1;
    }

    char *text = (argc == 3) ? argv[2] : argv[1];
    FILE *file = fopen(text, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", text);
        free_dict();
        return 1;
    }

    printf("\nMISSPELLED WORDS\n\n");

    // Prepare to spell-check
    int index = 0, misspellings = 0, words = 0;
    char word[MAX_LENGTH + 1];

    // Spell-check each word in text
    char c;
    while (fread(&c, sizeof(char), 1, file))
    {
        // Allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // Append character to word
            word[index] = c;
            index++;

            // Ignore alphabetical strings too long to be words
            if (index > MAX_LENGTH)
            {
                // Consume remainder of alphabetical string
                while (fread(&c, sizeof(char), 1, file) && isalpha(c));

                // Prepare for new word
                index = 0;
            }
        }

        // Ignore words with numbers (like MS Word can)
        else if (isdigit(c))
        {
            // Consume remainder of alphanumeric string
            while (fread(&c, sizeof(char), 1, file) && isalnum(c));

            // Prepare for new word
            index = 0;
        }

        // We must have found a whole word
        else if (index > 0)
        {
            // Terminate current word
            word[index] = '\0';

            // Update counter
            words++;

            bool misspelled = !check(word);

            // Print word if misspelled
            if (misspelled)
            {
                printf("%s\n", word);
                misspellings++;
            }

            // Prepare for next word
            index = 0;
        }
    }

    // Check whether there was an error
    if (ferror(file))
    {
        fclose(file);
        printf("Error reading %s.\n", text);
        free_dict();
        return 1;
    }

    // Close text
    fclose(file);

    unsigned int n = size();
    printf("Words in dictionary: %u\n", n);

    bool unloaded = free_dict();

    // Abort if dictionary not unloaded
    if (!unloaded)
    {
        printf("Could not unload %s.\n", dictionary);
        return 1;
    }

    return 0;
}