#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/siddarths/dev/c/SpellCheck/inc/list.h"

string read_word(string word) {
	string read = malloc(sizeof(word));
	strcpy(read, word);
	return read;
}

node* init_list(string word) {
	node *new = malloc(sizeof(node));
	new->word = read_word(word);
	new->next = NULL;
	new->prev = NULL;
	return new;
}

node* init_node(string word, node *prev) {
	node *new = malloc(sizeof(node));
	new->word = read_word(word);
	new->next = NULL;
	new->prev = prev;
	return new;
}

void visualize(node *head) {
	if (head == NULL) {
		printf("NULL\n");
	        return;
	}
	printf("%s --> ", head->word);
	visualize(head->next);
}

node* last_node(node *head) {
	node *tmp;
	for (tmp = head; tmp->next != NULL; tmp = tmp->next);
	return tmp;
}

void visualize_reverse(node *last_node) {
	if (last_node == NULL) {
		printf("NULL\n");
	        return;
	}
	printf("%s --> ", last_node->word);
	visualize_reverse(last_node->prev);
}

void free_list(node *head) {
	if (head == NULL) {
		return;
	}
	free_list(head->next);
	free(head->word);
	free(head);
}

node* add_node(string word, node *head) {
	if (word == NULL || head == NULL) {
		return NULL;
	}
	node* new = init_list(word);
	head->prev = new;
	new->next = head;
	return new;
}

node* search_node(string word, node *head) {
	if (head->next == NULL) {
		if (strcmp(word, head->word) == 0) {
			return head;
		} else {
			return NULL;
		}
	}
	if (strcmp(word, head->word) == 0) {
		return head;
	}
	return search_node(word, head->next);
}

node* remove_node(string word, node *head) {
	node *remove = search_node(word, head);
	if (remove == NULL) {
		return head;
	}
	if (remove->prev == NULL) {
		return remove_head(head);
	} else {
		remove->prev->next = remove->next;
	}
	if (remove->next == NULL) {
		free(remove);
		return head;
	} else {
		remove->next->prev = remove->prev;
	}
	free(remove);
	return head;
}

node* remove_head(node *head) {
	node *tmp = head->next;
	free(head);
	return tmp;
}
