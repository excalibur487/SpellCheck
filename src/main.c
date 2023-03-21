#include <stdio.h>
#include "/home/siddarths/dev/c/SpellCheck/inc/list.h"

int main()
{
    char command;
    scanf("%c", &command);

    node *head;

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
        char *string;
        printf("Enter a string: ");
        scanf("%s", string);
        if (head != NULL)
        {
            free_list(head);
        }
        head = init_list(string);
        break;
    case 'A':
        char *string;
        printf("Enter a string: ");
        scanf("%s", string);
        if (head == NULL)
        {
            head = init_list(string);
        }
    default:
        break;
    }

    return 0;
}
