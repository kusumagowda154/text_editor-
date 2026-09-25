#include "main.h"


/* Move cursor UP */
void move_up(void)
{
    Dlist *node;

    if (cursorLine > 0)
    {
        cursorLine--;
    }

    node = get_node(cursorLine);

    if (node != NULL)
    {
        if (cursorChar > strlen(node->data))
        {
            cursorChar = strlen(node->data);
        }
    }
}


/* Move cursor DOWN */
void move_down(void)
{
    Dlist *node;

    if (get_node(cursorLine + 1) != NULL)
    {
        cursorLine++;
    }

    node = get_node(cursorLine);

    if (node != NULL)
    {
        if (cursorChar > strlen(node->data))
        {
            cursorChar = strlen(node->data);
        }
    }
}


/* Move cursor LEFT */
void move_left(void)
{
    if (cursorChar > 0)
    {
        cursorChar--;
    }
}


/* Move cursor RIGHT */
void move_right(void)
{
    Dlist *node;

    node = get_node(cursorLine);

    if (node != NULL)
    {
        if (cursorChar < strlen(node->data))
        {
            cursorChar++;
        }
    }
}


/* Insert text at cursor */
void insert_text(const char *text)
{
    Dlist *node;
    int currentLength;
    int insertLength;

    insertLength = strlen(text);

    /* Empty document */
    if (head == NULL)
    {
        append_node(text);
        cursorLine = 0;
        cursorChar = insertLength;

        return;
    }

    node = get_node(cursorLine);

    if (node == NULL)
    {
        return;
    }

    currentLength = strlen(node->data);

    if (currentLength + insertLength > MAX_LINE_LENGTH)
    {
        printf("Cannot insert. Maximum line length exceeded.\n");
        return;
    }

    /*
     * Move existing characters to the right.
     */
    memmove(node->data + cursorChar + insertLength,
            node->data + cursorChar,
            currentLength - cursorChar + 1);

    /*
     * Copy new text.
     */
    memcpy(node->data + cursorChar,
           text,
           insertLength);

    cursorChar += insertLength;
}


/* Delete character */
void delete_character(void)
{
    Dlist *node;
    int length;

    node = get_node(cursorLine);

    if (node == NULL)
    {
        return;
    }

    length = strlen(node->data);

    if (cursorChar >= length)
    {
        printf("No character to delete.\n");
        return;
    }

    memmove(node->data + cursorChar,
            node->data + cursorChar + 1,
            length - cursorChar);

    if (cursorChar > 0)
    {
        cursorChar--;
    }
}


/* Delete current line */
void delete_line(void)
{
    Dlist *node;

    node = get_node(cursorLine);

    if (node == NULL)
    {
        printf("No line to delete.\n");
        return;
    }

    /* Update previous node */
    if (node->pre != NULL)
    {
        node->pre->next = node->next;
    }
    else
    {
        head = node->next;
    }

    /* Update next node */
    if (node->next != NULL)
    {
        node->next->pre = node->pre;
    }
    else
    {
        tail = node->pre;
    }

    free(node);

    /*
     * If cursor was on the last line,
     * move it to the new last line.
     */
    if (head == NULL)
    {
        cursorLine = 0;
        cursorChar = 0;
    }
    else
    {
        if (get_node(cursorLine) == NULL)
        {
            cursorLine--;
        }

        if (cursorLine < 0)
        {
            cursorLine = 0;
        }

        node = get_node(cursorLine);

        if (node != NULL &&
            cursorChar > strlen(node->data))
        {
            cursorChar = strlen(node->data);
        }
    }
}