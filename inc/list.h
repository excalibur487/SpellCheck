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
	string word;
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

// Initializes node with given word and pointer to previous node
node *init_node(string word, node *prev);

// Prints text-based visualization of the list
void visualize(node *head);

// Returns the last node in list
node *last_node(node *head);

// Prints text-based visualization of the list in reverse order
void visualize_reverse(node *head);

// Frees the list
void free_list(node *head);

// Appends a node to the start of the list
node *add_node(string word, node *head);

// Returns reference to the node
node *search_node(string word, node *head);

// Returns head to list with node containing word removed
node *remove_node(string word, node *head);

// Removes the first node in list and returns reference to second node
node *remove_head(node *head);

#endif
