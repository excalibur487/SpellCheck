#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "/home/siddarths/dev/c/SpellCheck/inc/list.h"

int main()
{
    char command;

    node *head = NULL;
    char word[MAX_LENGTH];
    char buffer[100];

    while (true)
    {
        printf("Command: ");
        scanf(" %c", &command);
        switch (command)
        {
        case 'Q':
            if (head != NULL)
            {
                free_list(head);
            }
            exit(0);
            break;
        case 'I':
            printf("Enter a string: ");
            //buffer[strcspn(buffer, "\n")] = 0;
            scanf("%s", word);
            if (head != NULL)
            {
                free_list(head);
            }
            head = init_list(word);
            visualize(head);
            break;
        case 'A':
            printf("Enter a string: ");
            //buffer[strcspn(buffer, "\n")] = 0;
            scanf("%s", word);
            if (head == NULL)
            {
                head = init_list(word);
                break;
            }
            head = add_node(word, head);
            break;
        case 'R':
            printf("String to remove: ");
            //buffer[strcspn(buffer, "\n")] = 0;
            scanf("%s", word);
            head = remove_node(word, head);
            break;
        case 'V':
            visualize(head);
            break;
        case 'B':
            visualize_reverse(head);
            break;
        default:
            break;
        }
    }

    return 0;
}
