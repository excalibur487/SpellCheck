// Define doubly linked list for strings
#ifndef LIST_H
#define LIST_H

#define MAX_LENGTH 50

/**
 * @brief Defing string type
 *
 */
typedef char *string;

/**
 * @brief Define node for a doubly linked list
 *
 */
typedef struct node
{
	/**
	 * @brief Word data
	 *
	 */
	char word[MAX_LENGTH + 1];
	/**
	 * @brief Pointer to next node in list
	 *
	 */
	struct node *next;
	/**
	 * @brief Pointer to previous node in list
	 *
	 */
	struct node *prev;
} node;

/**
 * @brief Dynamically allocates memory for a copy of the word passed in
 *
 * @param word The word to be copied
 * @return string The reference to the copied word
 */
string read_word(string word);

/**
 * @brief Initializes a list with the given word
 *
 * @param word The word to initialize list with
 * @return node* Reference to the head of the list
 */
node *init_list(string word);

/**
 * @brief Initializes node with given word and pointer to previous node
 *
 * @param word Word to initialize node with
 * @param prev Reference to previous node
 * @return node* Reference to newly created node
 */
node *init_node(string word, node *prev);

/**
 * @brief Prints text-based visualization of the list
 *
 * @param head Reference to the head of the list
 */
void visualize(node *head);

/**
 * @brief Returns the last node in list
 *
 * @param head Reference to the head of the list
 * @return node* Reference to the last node in list
 */
node *last_node(node *head);

/**
 * @brief Prints text-based visualization of the list in reverse order
 *
 * @param head Reference to the head of the list
 */
void visualize_reverse(node *head);

/**
 * @brief Frees heap usage of the list
 *
 * @param head Reference to the head of the list
 */
void free_list(node *head);

/**
 * @brief Appends a node to the start of the list
 *
 * @param word Node data
 * @param head Reference to the head of the list
 * @return node* Reference to the new head of the list
 */
node *add_node(string word, node *head);

// Returns reference to the node
/**
 * @brief Searches for word in list
 *
 * @param word Word to search list for
 * @param head Reference to the head of the list
 * @return node* Reference to the node with word, if found
 */
node *search_node(string word, node *head);

/**
 * @brief Searches for word in list
 *
 * @param myword Word to search list for
 * @param head Reference to the head of the list
 * @return true If found
 * @return false If not found in list
 */
bool found(const char *myword, node *head);

/**
 * @brief Returns head to list with node containing word removed
 *
 * @param word Word to be removed from list
 * @param head Reference to the head of the list
 * @return node* Reference to removed node
 */
node *remove_node(string word, node *head);

/**
 * @brief Removes the head of a list
 *
 * @param head Reference to the head of the list
 * @return node* Reference to second node
 */
node *remove_head(node *head);

#endif
