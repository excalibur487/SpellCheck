// Define doubly linked list for strings
#ifndef LIST_H
#define LIST_H

// Define string type
typedef char* string;

// Define node for a doubly linked list
typedef struct node {
	string word;
	struct node *next;
	struct node *prev;
} node;

// Initializes list with given word
node* init_list(string word);

// Initializes node with given word and pointer to previous node
node* init_node(string word, node *prev);

// Prints text-based visualization of the list
void visualize(node *head);

// Returns the last node in list
node* last_node(node *head);

// Prints text-based visualization of the list in reverse order
void visualize_reverse(node *head);

// Frees the list
void free_list(node *head);

// Appends a node to the start of the list
node* add_node(string word, node *head);

// Returns reference to the node 
node* search_node(string word, node *head);

// Returns head to list with node containing word removed
node* remove_node(string word, node *head);

// Removes the first node in list and returns reference to second node
node* remove_head(node *head);
	
#endif
