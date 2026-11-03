#include <stdio.h>
#include "contact.h"
//#include <stdio_ext.h>   // this header file for fpurge function



int main() 
{
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book 
    printf(CLEARSCR STOPCLEARSCR);// clearing screen text
    printHeader();
    do 
    {

        printf("\n");
        printf(MAGENTA BOLD "  ------MAIN MENU-------\n" RESET);
        printf(YELLOW "  [1] " RESET "Create new contact\n");
        printf(YELLOW "  [2] " RESET "Search contact\n");
        printf(YELLOW "  [3] " RESET "Edit contact\n");
        printf(YELLOW "  [4] " RESET "Delete contact\n");
        printf(YELLOW "  [5] " RESET "List all contacts\n");
        printf(YELLOW "  [6] " RESET GREEN "Save and Exit\n" RESET);       
        printf(YELLOW "  [7] " RESET RED "Exit without saving\n" RESET);
        printf(CYAN "-----------------------------------------\n" RESET);
        printf(BOLD "Enter your choice (1-7): " RESET);
        
        //__fpurge(stdin); 
        
        // Checking  if scanf successfully read an integer
        if (scanf("%d", &choice) != 1) {
            choice = -1; // Assigning invalid choice if user types a letter
        }
        
        printf("\n"); // Adding spacing before executing the function

        switch (choice) 
        {
            case 1:
                printf(CLEARSCR""STOPCLEARSCR);// clearing screen text
                printf(GREEN BOLD ">>> CREATING NEW CONTACT <<<\n\n" RESET);
                createContact(&addressBook);
                break;
            case 2:
                printf(CLEARSCR" "STOPCLEARSCR);// clearing screen text
                printf(CYAN BOLD ">>> SEARCHING CONTACT <<<\n\n" RESET);
                searchContact(&addressBook);
                break;
            case 3:
                printf(CLEARSCR" "STOPCLEARSCR);// clearing screen text
                printf(YELLOW BOLD ">>> EDITING CONTACT <<<\n\n" RESET);
                editContact(&addressBook);
                break;
            case 4:
                printf(CLEARSCR" "STOPCLEARSCR);// clearing screen text
                printf(RED BOLD ">>> DELETING CONTACT <<<\n\n" RESET);
                deleteContact(&addressBook);
                break;
            case 5: 
                printf(CLEARSCR" "STOPCLEARSCR);// clearing screen text         
                printf(MAGENTA BOLD ">>> LISTING ALL CONTACTS <<<\n\n" RESET);
                listContacts(&addressBook);
                break;
            case 6:
                printf(GREEN BOLD "💾 Saving changes to file...\nExiting Address Book.\n" RESET);
                saveContactsToFile(&addressBook);
                break;
            case 7:
                printf(RED BOLD "Exiting without saving changes...\n" RESET);
                break;
            default:
                printf(CLEARSCR" "STOPCLEARSCR);// clearing screen text
                printf(RED "⚠️ Invalid choice! Please enter a number between 1 and 7.\n" RESET);
        }
        


    } while (choice != 6 && choice != 7);
    
    return 0;
}
