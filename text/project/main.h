#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

typedef struct node
{
    char data[MAX_LINE_LENGTH + 1];

    struct node *pre;
    struct node *next;

} Dlist;


/* Global document pointers */
extern Dlist *head;
extern Dlist *tail;


/* Cursor position */
extern int cursorLine;
extern int cursorChar;


/* File operations */
int load_data(const char *filename);
int save_data(const char *filename);


/* Display */
void print_document(void);


/* Memory management */
void free_list(void);


/* Linked list operations */
void append_node(const char *text);
Dlist *get_node(int line);


/* Cursor operations */
void move_up(void);
void move_down(void);
void move_left(void);
void move_right(void);


/* Editing operations */
void insert_text(const char *text);
void delete_character(void);
void delete_line(void);


/* Menus */
void edit_menu(void);

#endif