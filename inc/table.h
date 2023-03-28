// Define hash table for strings
#ifndef TABLE_H
#define TABLE_H

#define BUCKETS 777777

#include "/home/siddarths/dev/c/SpellCheck/inc/list.h"

/**
 * @brief Hash Table
 *
 */
node *table[BUCKETS];

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
 * @brief Unloads dictionary from memory, returning true if successful, else false
 * 
 * @return true 
 * @return false 
 */
bool free_dict(void);

#endif