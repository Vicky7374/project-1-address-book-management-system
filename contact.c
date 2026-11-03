#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#define RESET   "\033[0m"
#include <stdio_ext.h>

void printHeader() {
    printf(CYAN BOLD "\n=========================================\n" RESET);
    printf(MAGENTA BOLD "        📖 ADDRESS BOOK MANAGER 📖       \n" RESET);
    printf(CYAN BOLD "=========================================\n" RESET);
}
void listContacts(AddressBook *addressBook) 
{
    
    //bubble sort.
    
    for(int i=0;i<addressBook->contactCount-1;i++)
    {
        for(int j=0;j<addressBook->contactCount-1-i;j++)
        {  
            if(strcasecmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0)
            {
                Contact temp=addressBook->contacts[j];
                addressBook->contacts[j]=addressBook->contacts[j+1];
                addressBook->contacts[j+1]=temp;

                // char temp_str[50];
                // strcpy(temp_str,addressBook->contacts[j].name);
                // strcpy(addressBook->contacts[j].name,addressBook->contacts[j+1].name);
                // strcpy(addressBook->contacts[j+1].name,temp_str);

                // strcpy(temp_str,addressBook->contacts[j].phone);
                // strcpy(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone);
                // strcpy(addressBook->contacts[j+1].phone,temp_str);

                // strcpy(temp_str,addressBook->contacts[j].email);
                // strcpy(addressBook->contacts[j].email,addressBook->contacts[j+1].email);
                // strcpy(addressBook->contacts[j+1].email,temp_str);
            }
        }
    }

// Top border of the table
printf("+--------+----------------------+-----------------+--------------------------------+\n");


printf("| " BOLD CYAN "%-6s" RESET " | " BOLD CYAN "%-20s" RESET " | " BOLD CYAN "%-15s" RESET " | " BOLD CYAN "%-30s" RESET " |\n", 
       "S.No.", "Name", "Phone No.", "Email");

// Middle separator
printf("+--------+----------------------+-----------------+--------------------------------+\n");


for (int i = 0; i < addressBook->contactCount; i++)
{
    printf("| " MAGENTA "%-6d" RESET " | %-20s | " YELLOW "%-15s" RESET " | " BLUE "%-30s" RESET " |\n",
           i + 1, 
           addressBook->contacts[i].name,
           addressBook->contacts[i].phone,
           addressBook->contacts[i].email);
}

// Bottom border of the table
printf("+--------+----------------------+-----------------+--------------------------------+\n");

    printf(YELLOW "\nPress [ENTER] to return to the main menu..." RESET);
    __fpurge(stdin);// here it will eat previous enter
    getchar();      // it will wait for enter
    

    printf(CLEARSCR""STOPCLEARSCR);// clearing srceen after doing above work.

    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    
    
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program or terminate the program successfully
}

int validate_name(char *str)
{
   for(int i=0;str[i];i++)
   {
        if(!(str[i]>='a'&&str[i]<='z' || str[i]>='A'&&str[i]<='Z'|| str[i]=='.' || str[i]==' '))
        {
             printf("\nInvalid Name...try again...");
             printf("\nName should contain alphabet,dot and spaces only \n");
             return 0;
        }
    }
   return 1;
}
int validate_number(char *str,AddressBook *addressBook)
{
    if(strlen(str)!=10)
    {
        printf("\nNumber should contain 10 digit...try again...\n");
        return 0;
    }

   
        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(strcmp(addressBook->contacts[i].phone,str)==0)//here i am cheking phone number already exist or not...
            {
                printf("\nphone number already found\nEnter new number...");
                return 0;
            }
        }                        
        
    
    
    
   for(int i=0;str[i];i++)
   {
     if(!(str[i]>='0'&&str[i]<='9'))
     {
        printf("\nInvalid Number...try again..");
        printf("\nNumber should contain only digit.");
        return 0;
     }
   }
   return 1;
}

int validate_email(char *str,AddressBook *addressBook)
{
    int count=0;
    int len=strlen(str);   
        if(len<6)
        {
            printf("\nlength should be greater then six");
            return 0;
        }
        for(int i=0;i<addressBook->contactCount;i++) 
        {
            if(strcmp(addressBook->contacts[i].email,str)==0)// here i am checking email already exist or not..
            {
                count=1;
                printf("\nEmail already exist...\nEnter new email...");
            }
        }
        if(count)// returning zero if email already found...
        return 0;
   
    if(str[0]>='0'&&str[0]<='9' || str[0]=='@' || str[0]=='.')
    {
        printf("First charcter can't be digit,'@'and dot ,try again...");
        return 0;
    }
    
      

    if(!(str[len-1]=='m'&&str[len-2]=='o'&&str[len-3]=='c'&&str[len-4]=='.'&&str[len-5]!='@'))// .com checking in last
    {
        printf("\nOne character before .com '@' should not be there and .com at last is compulsory...try again..");
        return 0;
    }

    int count_=0;
    for(int i=0;str[i];i++)
    {
        if(str[i]=='@')
         count_++;
    }
    if(count_!=1)
    return 0;
   for(int i=0;str[i];i++)
   {
     if(!(str[i]>='0'&&str[i]<='9' || str[i]>='a'&&str[i]<='z'||str[i]=='m'||str[i]=='o'||str[i]=='c'||str[i]=='.'||str[i]=='@'))
     {
        printf("\nInvalid Email..try again");
        printf("\nEmail should not contain other then @,dot,digit and lower case alphabet..");
        return 0;
     }
   }
   return 1;
}

void createContact(AddressBook *addressBook)
{
	if(addressBook->contactCount==MAX_CONTACTS)
    {
        printf(RED"\nMaximum contact limit reached..."RESET);
        return;
    }
    printf(CYAN BOLD"\n------------------ENTRY INSTRUCTIONS ---------------------\n" RESET);
    printf("Name   : Letters, dots, and spaces only"GREEN"(Example: Vicky Kashyap)\n"RESET);
    printf("Number : Exactly 10 digits only"GREEN" (Example: 9876543211)\n"RESET);
    printf("Email  : Must contain '@' and '.com'"GREEN"(Example: vickycontact@gmail.com)\n"RESET);
    printf(CYAN BOLD"-----------------------------------------------------------\n\n" RESET);
    
    char str1[20];
    char str2[50];
    char str3[50];
    int res,len,count=0;

// Name

    do{
        printf("Enter the name : ");
        scanf(" %[^\n]",str1);

        res = validate_name(str1);
        count++;
        if(count==5)// here i am checking condition if within five attempts user enter wrong formate name then
        {                                               //then cortrol automatically back to main menu.
            printf("\nfailed....you reached your limit...😐\n");
            return;
        }

    }while(res == 0);
    count=0;
   
// phone number

    do{
        printf("\nEnter the Phone Number : ");
        scanf(" %[^\n]",str2);
        
        res = validate_number(str2,addressBook);
        count++;
        if(count==5)// here i am checking condition if within five attempts user enter wrong formate number then
        {                                               //then cortrol automatically back to main menu.
            printf("\nfailed....you reached your limit...😐\n");
            return;
        }

    }while(res == 0);
    count=0;
// email

    do{
        printf("\nEnter the Email id : ");
        scanf(" %[^\n]",str3);
        
        res = validate_email(str3,addressBook);
        count++;
        if(count==5)// here i am checking condition if within five attempts user enter wrong formate email id then
        {                                 //then cortrol automatically back to main menu.
            printf("\nfailed....you reached your limit...😐\n");
            return;
        }

    }while(res == 0);
    count=0;

    strcpy(addressBook->contacts[addressBook->contactCount].name, str1);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, str2);
    strcpy(addressBook->contacts[addressBook->contactCount].email, str3);

    addressBook->contactCount++;

    printf("\nContact Created Succussfully...😊\n");
    __fpurge(stdin);// here it will eat enter
    printf(YELLOW "\nPress [ENTER] to return to the main menu..." RESET);
    getchar(); // it will wait for enter 

    printf(CLEARSCR""STOPCLEARSCR);// clearing srceen after doing above work.

    
    
}
int search_by_number(AddressBook *addressBook)
{

    printf("\nEnter the phone no.: ");
    char str[20];
    scanf(" %[^\n]",str);
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].phone,str)==0)
        {
            printf("%s",str);
            return i;
        }
    }
    printf("Number Not found...");
    return -1;
}
int search_by_name(AddressBook *addressBook)
{
    int count=0,index;
    printf("Enter the name: ");
    char str[20];
    scanf(" %[^\n]",str);
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcasecmp(addressBook->contacts[i].name,str)==0)
        {
            printf("\n%s",str);
            count++;
            index=i;
        }
    }
    if(count>1)
    {
        printf("\nMultiple name found....");
        return search_by_number(addressBook);
    }
    else if(count==1)
    return index;
    else
    {
        printf("Name not found...");
        return -1;
    }
   
}

int search_by_email(AddressBook *addressBook)
{
     int count=0;
    printf("Enter the email id: ");
    char str[30];
    scanf(" %[^\n]",str);
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].email,str)==0)
        {
            printf("%s",str);
            return i;
        }
    }
    printf("Email Not found...");
    return -1;
}
void searchContact(AddressBook *addressBook) 
{
    int choice=0,index;
    do{
    printf("\nSearch by:\n");
    printf("1.Name :\n");
    printf("2.number :\n");
    printf("3.Email :\n");
    printf("4.Exit :\n");
    printf("Enter your choice: ");
    __fpurge(stdin);
    scanf("%d",&choice);
        switch(choice)
        {
            case 1:index=search_by_name(addressBook);
                    if(index>=0)
                    printf("\nFound at index %d",index);
                    break; 
            case 2:index=search_by_number(addressBook);
                    if(index>=0)
                    printf("\nFound at index %d",index);
                    break; 
            case 3:index=search_by_email(addressBook);
                    if(index>=0)
                    printf("\nFound at index %d",index);
                    break; 
            case 4:printf("\nExiting....from search menu....");
                   printf(CLEARSCR""STOPCLEARSCR);
                   break; 
            default:
                    printf("Invalid input");
                    break;
        }
    }while(choice!=4);
}
void Edit_function(int index,AddressBook* addressBook)
{
    int choice=0;
    char str1[30];
    char str2[20];
    char str3[30];
    do{
    printf("\nSelect Field to Edit: ");
    printf("\n1.Name");
    printf("\n2.Phone");
    printf("\n3.email");
    printf("\n4.Exit");
    printf("\nEnter your choice: ");
    __fpurge(stdin);
    scanf("%d",&choice);
        switch(choice)
        {
            case 1: 
                    printf("Enter the new name: ");
                    scanf(" %[^\n]",str1);
                    if(validate_name(str1))
                    {
                        strcpy(addressBook->contacts[index].name,str1);
                        printf("Name Updated Successfully...😊\n");
                        return;
                    }
                    choice=0;// reseting choice value so that if user enter any garbage value
                             // it should not take automatically previous choice value
                    
                    break;
            
            case 2: 
                    printf("Enter the new number:");
                    scanf(" %[^\n]",str2);
                    if(validate_number(str2,addressBook))
                    {
                        strcpy(addressBook->contacts[index].phone,str2);
                        printf("Number Updated Successfully...😊\n");
                        return;
                    }
                    choice=0;
                    break;
            case 3: 
                    printf("Enter the new email:");
                    scanf(" %[^\n]",str3);
                    if(validate_email(str3,addressBook))
                    {
                        strcpy(addressBook->contacts[index].email,str3);
                        printf("Email Updated Successfully...😊\n");
                        return;
                    }
                    choice=0;
                    break;
            case 4: 
                    printf("Exiting....");
                    break;
            default:
                    printf("\nInvalid input");
                    break;
        }
    }while(choice!=4);
    
}
void editContact(AddressBook *addressBook)
{
	int choice=0,index=-1;
    do{
    printf("\nSearch for edit:\n");
    printf("1.Name :\n");
    printf("2.number :\n");
    printf("3.Email :\n");
    printf("4.Exit :\n");
    printf("Enter your choice: ");
    __fpurge(stdin);
    scanf("%d",&choice);
        switch(choice)
        {
            case 1: index=search_by_name(addressBook);
                    if(index!=-1)
                    Edit_function(index,addressBook);
                    choice=0; // reseting choice value
                    break; 
            case 2: index=search_by_number(addressBook);
                    if(index!=-1)
                    Edit_function(index,addressBook);
                    choice=0;
                    break; 
            case 3: index=search_by_email(addressBook);
                    if(index!=-1)
                    Edit_function(index,addressBook);
                    choice=0;
                    break; 
            case 4: printf("\nExiting....from search menu....");
                    printf(CLEARSCR""STOPCLEARSCR);// clr scr so when it back to main menu screen look clear
                    index=-1;
                    break; 
            default:
                    printf("Invalid input try again...");
                    break;
        }
       

       

    }while(choice!=4);
    
}

void delete_function(int index,AddressBook* addressBook)
{
    for(int i=index;i<addressBook->contactCount;i++)
    {
        addressBook->contacts[i]=addressBook->contacts[i+1];
    }
    addressBook->contactCount--;
}
void deleteContact(AddressBook *addressBook)
{
	 int choice=0,index;
     char yes_no;
    do{
    printf("\nSearch for delete:\n");
    printf("1.Name :\n");
    printf("2.number :\n");
    printf("3.Email :\n");
    printf("4.Delete all contacts :\n");
    printf("5.Exit :\n");
    printf("Enter your choice: ");
    __fpurge(stdin);
    scanf("%d",&choice);
        switch(choice)
        {
            case 1:index=search_by_name(addressBook);
                    if(index>=0)
                    {
                        printf("\nAre you sure you want to delete(Y/N): ");
                        scanf(" %c",&yes_no);
                        if(yes_no=='Y'||yes_no=='y')
                        {
                            delete_function(index,addressBook);
                            printf("\nName Deleted Successfully...😊");
                        }
                        else
                        break;
                        
                    }
                    else
                    printf("Name not found...");
                    break; 
            case 2:index=search_by_number(addressBook);
                    if(index>=0)
                    {
                        printf("\nAre you sure you want to delete(Y/N): ");
                        scanf(" %c",&yes_no);
                        if(yes_no=='Y'||yes_no=='y')
                        {
                            delete_function(index,addressBook);
                            printf("\nNumber Deleted Successfully...😊");
                        }
                        else
                        break;
                    }
                    else
                    printf("Number not found...");
                    break; 
            case 3:index=search_by_email(addressBook);
                    if(index>=0)
                    {
                        printf("\nAre you sure you want to delete(Y/N): ");
                        scanf(" %c",&yes_no);
                        if(yes_no=='Y'||yes_no=='y')
                        {
                            delete_function(index,addressBook);
                            printf("\nEmail Deleted Successfully...😊");
                        }
                        else
                        break;
                    }
                    else
                    printf("Email not found");
                    break; 
            case 4:
                   printf("\nAre you sure you want to delete(Y/N): ");
                   scanf(" %c",&yes_no);
                   if(yes_no=='Y'||yes_no=='y')
                    {
                        addressBook->contactCount=0;
                        printf("\nAll Contact Deleted Successfully...😊");
                    }
                    else
                    break;
                   
            case 5:printf("\nExiting....from delete menu....");
                   printf(CLEARSCR""STOPCLEARSCR);
                   break; 
            default:
                    printf("Invalid input");
                    break;
        }
    }while(choice!=5);
   
}
