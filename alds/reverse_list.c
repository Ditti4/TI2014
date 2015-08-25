#include <stdio.h>
#include <stdlib.h>

typedef struct __list_entry list_entry;

struct __list_entry {
    int id;
    list_entry *next;
};

list_entry *anchor = NULL;

/*
 * This function will set a new anchor (which will hopefully be the old last item of the list)
 * and reverse the list.
 */

void reverse_list() {
    // TODO
    list_entry *prev_entry = NULL;
    list_entry *current_entry = anchor;
    list_entry *next_entry = anchor->next;
    while(current_entry) {
        next_entry = current_entry->next;
        current_entry->next = prev_entry;
        prev_entry = current_entry;
        current_entry = next_entry;
    }
    anchor = prev_entry;
}

/*
 * This function will add an element to the end of the list
 */

void add_element(int id) {
    list_entry *new_entry = malloc(sizeof(list_entry));
    if(!new_entry) {
        return;
    }
    new_entry->id = id;
    new_entry->next = NULL;
    if(!anchor) {
        anchor = new_entry;
        return;
    }
    list_entry *current_entry = anchor;
    while(current_entry->next) {
        current_entry = current_entry->next;
    }
    current_entry->next = new_entry;
}

void print_list() {
   list_entry *current_entry = anchor;
   while(current_entry) {
       printf("%d\n", current_entry->id);
       current_entry = current_entry->next;
   }
}

int main(int argc, char **argv) {
    add_element(1);
    add_element(2);
    add_element(3);
    print_list();
    printf("Reversing list …\n");
    reverse_list();
    print_list();
    return 0;
}
