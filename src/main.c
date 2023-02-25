#include <stdio.h>
#include "/home/siddarths/dev/c/spellcheck/inc/list.h"

int main()
{
    printf("Test\n");
    node *list = init_list("foo");

    list = add_node("bar", list);
    visualize(list);

    list = add_node("baz", list);
    visualize(list);

    list = add_node("broke", list);
    visualize(list);

    list = add_node("filter", list);
    visualize(list);

    list = add_node("foggy", list);
    visualize(list);

    //visualize_reverse(last_node(list));

    remove_node("foo", list);
    visualize(list);

    remove_node("bar", list);
    visualize(list);

    remove_node("foggy", list);
    visualize(list);

    free_list(list);
    return 0;
}
