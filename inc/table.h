// Define hash table for strings
#ifndef TABLE_H
#define TABLE_H

#define BUCKETS 777777

#include "/Users/siddarthshinde/dev/projects/SpellCheck/inc/list.h"

/**
 * @brief Custom hash function
 *
 * @param word Word to be hashed
 * @return unsigned int The hash code for the word
 * @author Siddarth Shinde
 */
unsigned int hash(const char *word);

/**
 * @brief Populates hash table with words in dictionary
 *
 * @param dictionary Name of the file containing dictionary words
 * @return true If the table was succesfully populated
 * @return false If table could not be populated
 */
bool populate(const char *dictionary);

/**
 * @brief Returns number of words in dictionary if loaded, else 0 if not yet loaded
 *
 * @return unsigned int Number of words in dictionary if loaded
 */
unsigned int size(void);

/**
 * @brief Checks the spelling of a word by searching for it in the dictionary
 *
 * @param word Word to check spelling of
 * @return true If spelled correctly
 * @return false If misspelled
 */
bool check(char *word);

/**
 * @brief Unloads dictionary from memory, returning true if successful, else false
 *
 * @return true If dictionary was successfully freed
 * @return false If error was encountered while freeing dictionary
 */
bool free_dict(void);

#endif
