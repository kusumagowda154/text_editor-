#include "main.h"

Dlist *head = NULL;
Dlist *tail = NULL;

int cursorLine = 0;
int cursorChar = 0;


/* Create and append a new node */
void append_node(const char *text)
{
    Dlist *newNode;

    newNode = (Dlist *)malloc(sizeof(Dlist));

    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    strcpy(newNode->data, text);

    newNode->pre = NULL;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        newNode->pre = tail;
        tail->next = newNode;
        tail = newNode;
    }
}


/* Load file into linked list */
int load_data(const char *filename)
{
    FILE *fp;
    char buffer[MAX_LINE_LENGTH + 2];

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Unable to open %s\n", filename);
        return 0;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        buffer[strcspn(buffer, "\n")] = '\0';

        append_node(buffer);
    }

    fclose(fp);

    return 1;
}


/* Get node corresponding to line number */
Dlist *get_node(int line)
{
    Dlist *temp;
    int i;

    temp = head;

    for (i = 0; i < line && temp != NULL; i++)
    {
        temp = temp->next;
    }

    return temp;
}


/* Display document */
void print_document(void)
{
    Dlist *temp;
    int line = 0;

    printf("\n====================================\n");
    printf("          C TEXT EDITOR\n");
    printf("====================================\n");

    temp = head;

    if (temp == NULL)
    {
        printf("(Empty document)\n");
        return;
    }

    while (temp != NULL)
    {
        printf("%3d | %s", line + 1, temp->data);

        if (line == cursorLine)
        {
            printf("  <-- cursor line");
        }

        printf("\n");

        temp = temp->next;
        line++;
    }

    printf("====================================\n");
    printf("Cursor: Line %d, Character %d\n",
           cursorLine + 1,
           cursorChar);
}


/* Save linked list into file */
int save_data(const char *filename)
{
    FILE *fp;
    Dlist *temp;

    fp = fopen(filename, "w");

    if (fp == NULL)
    {
        printf("Unable to save file.\n");
        return 0;
    }

    temp = head;

    while (temp != NULL)
    {
        fprintf(fp, "%s\n", temp->data);
        temp = temp->next;
    }

    fclose(fp);

    return 1;
}


/* Free complete linked list */
void free_list(void)
{
    Dlist *temp;

    while (head != NULL)
    {
        temp = head;

        head = head->next;

        free(temp);
    }

    tail = NULL;
}