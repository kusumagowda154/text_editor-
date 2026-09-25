#include "main.h"


void delete_menu(void)
{
    int choice;

    while (1)
    {
        printf("\n");
        printf("===== DELETE MENU =====\n");
        printf("1. Delete character\n");
        printf("2. Delete current line\n");
        printf("3. Cancel\n");
        printf("Enter option: ");

        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
            case 1:
                delete_character();
                printf("Character deleted.\n");
                break;

            case 2:
                delete_line();
                printf("Current line deleted.\n");
                break;

            case 3:
                return;

            default:
                printf("Invalid option.\n");
        }

        print_document();
    }
}


void edit_menu(void)
{
    int choice;
    char text[MAX_LINE_LENGTH + 1];

    while (1)
    {
        print_document();

        printf("\n===== EDIT MENU =====\n");
        printf("1. Move up\n");
        printf("2. Move down\n");
        printf("3. Move left\n");
        printf("4. Move right\n");
        printf("5. Insert data\n");
        printf("6. Delete data\n");
        printf("7. Exit editing\n");

        printf("Enter option: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
            case 1:
                move_up();
                break;

            case 2:
                move_down();
                break;

            case 3:
                move_left();
                break;

            case 4:
                move_right();
                break;

            case 5:

                printf("Enter text to insert: ");

                fgets(text, sizeof(text), stdin);

                text[strcspn(text, "\n")] = '\0';

                insert_text(text);

                printf("Document updated successfully.\n");

                break;

            case 6:

                delete_menu();

                break;

            case 7:

                return;

            default:

                printf("Invalid option.\n");
        }
    }
}


int main(void)
{
    int choice;

    printf("\n");
    printf("====================================\n");
    printf("        C TEXT EDITOR\n");
    printf("====================================\n");

    if (!load_data("data.txt"))
    {
        printf("Starting with an empty document.\n");
    }

    while (1)
    {
        print_document();

        printf("\n===== MAIN MENU =====\n");
        printf("1. Edit document\n");
        printf("2. Exit\n");

        printf("Enter option: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
            case 1:

                edit_menu();

                break;

            case 2:

                if (save_data("data.txt"))
                {
                    printf("Document saved successfully to data.txt.\n");
                }

                free_list();

                printf("Memory released. Goodbye.\n");

                return 0;

            default:

                printf("Invalid option.\n");
        }
    }
}