#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <sys/resource.h>
#include <sys/time.h>

#include "/Users/siddarthshinde/dev/projects/SpellCheck/inc/list.h"
#include "/Users/siddarthshinde/dev/projects/SpellCheck/inc/table.h"

#define DICTIONARY "/Users/siddarthshinde/dev/projects/SpellCheck/test/test-files/large.txt"

#undef calculate
#undef getrusage

// Prototype
double calculate(const struct rusage *b, const struct rusage *a);

/**
 * @brief Hash Table
 *
 */
node *table[BUCKETS];

int words = 0;

// Hashes word to a number
unsigned int hash(const char *word)
{
    int hashcode = 0;
    int length = strlen(word);

    for (int i = 0; i < length; i++)
    {
        // weighted sum of all letters, i capped to 4 because of memory limitations
        if (((toupper(word[i]) - 'A') > 0) && (i < 4))
        {
            int mul = 26;
            for (int j = 0; j < i - 1; j++)
                mul *= 26;
            hashcode += (toupper(word[i]) - 'A') * mul;
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
            // visualize(table[hashcode]);
            words++;
            index = 0;
        }

        else if (index > 0)
        {
            word[index] = '\0';

            hashcode = hash(word);
            table[hashcode] = add_node(word, table[hashcode]);
            // visualize(table[hashcode]);
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
    int hashcode = hash(word);

    return found(word, table[hashcode]);
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

    // Structures for timing data
    struct rusage before, after;

    // Benchmarks
    double time_load = 0.0, time_check = 0.0, time_size = 0.0, time_unload = 0.0;

    // Determine dictionary to use
    char *dictionary = (argc == 3) ? argv[1] : DICTIONARY;

    // Load dictionary
    getrusage(RUSAGE_SELF, &before);
    bool loaded = populate(dictionary);
    getrusage(RUSAGE_SELF, &after);

    // Exit if dictionary not loaded
    if (!loaded)
    {
        printf("Could not load %s.\n", dictionary);
        return 1;
    }

    // Calculate time to load dictionary
    time_load = calculate(&before, &after);

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
                while (fread(&c, sizeof(char), 1, file) && isalpha(c))
                    ;

                // Prepare for new word
                index = 0;
            }
        }

        // Ignore words with numbers (like MS Word can)
        else if (isdigit(c))
        {
            // Consume remainder of alphanumeric string
            while (fread(&c, sizeof(char), 1, file) && isalnum(c))
                ;

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

            // Check word's spelling
            getrusage(RUSAGE_SELF, &before);
            bool misspelled = !check(word);
            getrusage(RUSAGE_SELF, &after);

            // Update benchmark
            time_check += calculate(&before, &after);

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

    // Determine dictionary's size
    getrusage(RUSAGE_SELF, &before);
    unsigned int n = size();
    getrusage(RUSAGE_SELF, &after);

    // Calculate time to determine dictionary's size
    time_size = calculate(&before, &after);

    // Unload dictionary
    getrusage(RUSAGE_SELF, &before);
    bool unloaded = free_dict();
    getrusage(RUSAGE_SELF, &after);

    printf("\nWORDS MISSPELLED:     %d\n", misspellings);
    printf("WORDS IN DICTIONARY:  %d\n", n);
    printf("WORDS IN TEXT:        %d\n", words);

    // Abort if dictionary not unloaded
    if (!unloaded)
    {
        printf("Could not unload %s.\n", dictionary);
        return 1;
    }
    // Calculate time to unload dictionary
    time_unload = calculate(&before, &after);

    printf("TIME IN load:         %.2f\n", time_load);
    printf("TIME IN check:        %.2f\n", time_check);
    printf("TIME IN size:         %.2f\n", time_size);
    printf("TIME IN unload:       %.2f\n", time_unload);
    printf("TIME IN TOTAL:        %.2f\n\n",
           time_load + time_check + time_size + time_unload);
    return 0;
}

// Returns number of seconds between b and a
double calculate(const struct rusage *b, const struct rusage *a)
{
    if (b == NULL || a == NULL)
    {
        return 0.0;
    }
    else
    {
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                  (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                 ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                  (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec))) /
                1000000.0);
    }
}
