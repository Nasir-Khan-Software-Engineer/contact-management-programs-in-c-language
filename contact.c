#include <windows.h>
#include <unistd.h>
#include<stdio.h>
#include <string.h>
#include<stdbool.h>
#include <stdlib.h>

bool isRunning = true;
void Menu();
void AddNewNumber();
void ShowAllContacts();
void SearchContact();
void EditContact();
void DeleteContact();
void DeleteAllContacts();
void ClearWindow();
void ShowNameWithSpace(char *Name[20]);
void ShowPhoneWithSpace(char *Phone[20]);
void ShowEmailWithSpace(char *Email[30]);
void ErrorAndRestart(char *error[100]);
bool AlreadyExists(char *GivenLine[30]);
void GoBackOrExit();
void UserGuideline();
void AboutUs();
void Exit();

int main(){
    int i;
    printf("\t\t");
    char AppStarting[100] = "Application is Starting....";
    for(i=0;i<strlen(AppStarting);i++){
        printf("%c",AppStarting[i]);
        Sleep(40);
    }
    system("cls");


    while(isRunning == true){
        Menu();
        char *str[100];
        char option;
        scanf("%s",&str);
        option = str[0];
        switch(option){
            case '0':
                Exit();
                break;
            case '1':
                AddNewContact();
                break;
            case '2':
                ShowAllContacts();
                break;
            case '3':
                SearchContact();
                break;
            case '4':
                EditContact();
                break;
            case '5':
                DeleteContact();
                break;
            case '6':
                DeleteAllContacts();
                break;
            case '7':
                system("cls");
                break;
            case 'I':
            case 'i':
                UserGuideline();
                break;
            case 'A':
            case 'a':
                AboutUs();
                break;
            default:
                ErrorAndRestart("Option not found!");
                break;
        }
    }
}

void Menu(){
    printf("\n\t **** My-Contact Management System ****\n");
    printf("\n\n\n\t\t\tMAIN MENU\n");
    printf("\t\t=====================\n");
    printf("\t\t[1] Add a new Contact\n");
    printf("\t\t[2] List all Contacts\n");
    printf("\t\t[3] Search for contact\n");
    printf("\t\t[4] Edit a Contact\n");
    printf("\t\t[5] Delete a Contact\n");
    printf("\t\t[6] Delete All Contact\n");
    printf("\t\t[7] Clear Window\n");
    printf("\t\t[i] User Guideline\n");
    printf("\t\t[a] About Us\n");
    printf("\t\t[0] Exit\n\t\t=================\n\t\t");
    printf("Enter the choice:");
}

void AddNewContact(){
    system("cls");
    printf("\n\t\t **** Add new Contact ****\n\n");
    char Name[20];
    char Phone[20];
    char Email[30];
    char NewContact[100];
    NewContact[0] = 0;
    printf("*Name should be unique and maximum 20 charters long.\n");
    printf("Enter The Name: ");
    scanf(" %[^\n]s",Name);
    if(strlen(Name) > 20){
        ErrorAndRestart("!!!!Name Length Error!!!");
    }
    if(AlreadyExists(Name) == 1){
        ErrorAndRestart("!!!!Name Already Exists!!!");
    }
    printf("\n*Phone should be unique and maximum 20 charters long.\n");
    printf("Enter The Phone Number: ");
    scanf("%s",Phone);
    if(strlen(Phone) > 20){
        ErrorAndRestart("!!!!Phone Length Error!!!!");
    }
    if(AlreadyExists(Phone) == 1){
        ErrorAndRestart("!!!!Phone Number Already Exists!!!");
    }
    printf("\n*Email should be unique and maximum 30 charters long.\n");
    printf("Enter The Email: ");
    scanf("%s",Email);
    if(strlen(Email) > 30){
        ErrorAndRestart("!!!!Email Length Error!!!!");
    }
    if(AlreadyExists(Email) == 1){
        ErrorAndRestart("!!!!Email Already Exists!!!");
    }
    strcat(NewContact,Name);
    strcat(NewContact,"\n");
    strcat(NewContact,Phone);
    strcat(NewContact,"\n");
    strcat(NewContact,Email);
    strcat(NewContact,"\n");

    FILE *allContactTxtFile = fopen("All-Contact.txt","a");
    fprintf(allContactTxtFile,NewContact);
    fclose(allContactTxtFile);
    printf("\nContact Added Successfully!\n");
    GoBackOrExit();
}

void ShowAllContacts(){
    system("cls");
    printf("\n\t\t **** All Contacts ****\n\n");
    FILE* AllContactTextFile;
    int LineLength = 300;
    char Line[LineLength];

    printf("|====================|====================|==============================|\n");
    printf("|        Name        |    Phone Number    |          Email               |\n");
    printf("|====================|====================|==============================|\n");

    AllContactTextFile = fopen("All-Contact.txt", "r");
    int TotalContact = 0;
    int LineCount = 0;
    while(fgets(Line, LineLength, AllContactTextFile)) {
        LineCount++;
        if(LineCount==1){
            ShowNameWithSpace(Line);
        }else if(LineCount == 2){
           ShowPhoneWithSpace(Line);
        }else if(LineCount == 3){
            ShowEmailWithSpace(Line);
            LineCount=0;
            TotalContact++;
        }
    }
    printf("You Have Total %d Contacts.\n\n",TotalContact);
    fclose(AllContactTextFile);
    GoBackOrExit();
}

void ShowNameWithSpace(char *Name[20]){
    int i;
    char *FormatedName = NULL;
    FormatedName = strdup(Name);
    int FormatedNameLenght = strlen(FormatedName);

    printf("|");
    for(i=0;i<FormatedNameLenght-1;i++){
        printf("%c",FormatedName[i]);
    }

    for(i=0;i<=20-FormatedNameLenght;i++){
        printf(" ");
    }
}

void ShowPhoneWithSpace(char *Phone[20]){
    int i;
    char *FormatedPhone = NULL;
    FormatedPhone = strdup(Phone);
    int FormatedPhoneLength = strlen(FormatedPhone);

    printf("|");
    for(i=0;i<FormatedPhoneLength-1;i++){
        printf("%c",FormatedPhone[i]);
    }

    for(i=0;i<=20-FormatedPhoneLength;i++){
        printf(" ");
    }
}

void ShowEmailWithSpace(char *Email[30]){
    int i;
    char *FormatedEmai = NULL;
    FormatedEmai = strdup(Email);
    int FormatedEmailLength = strlen(FormatedEmai);

    printf("|");
    for(i=0;i<FormatedEmailLength-1;i++){
        printf("%c",FormatedEmai[i]); // printing email without last char(new line)
    }

    for(i=0;i<=30-FormatedEmailLength;i++){
        printf(" ");
    }
    printf("|\n");
    printf("|--------------------|--------------------|------------------------------|\n");
}

void SearchContact(){
    system("cls");
    printf("\n\t\t **** Search Contact ****\n\n");

    int FoundContact = 0;
    char Name[100];
    printf("*Name should be maximum 20 charters long.\n");
    printf("Enter The Name: ");
    scanf(" %[^\n]s",Name);
    if(strlen(Name) > 20){
        ErrorAndRestart("!!!!Name Length Error!!!");
    }
    strcat(Name,"\n");

    FILE* AllContactFile;
    int LineLength = 255;
    char Line[LineLength];
    AllContactFile = fopen("All-Contact.txt", "r");
    int LineCount = 0;
    while(fgets(Line, LineLength, AllContactFile)) {
       LineCount++;
        if(LineCount == 1 && strcmp(Name, Line) == 0){
            FoundContact = 1;
        }
        if(FoundContact > 0){
            if(LineCount==1){
                printf("\nContact information of %s",Name);
                printf("\nName: %s",Line);
            }else if(LineCount == 2){
                printf("Phone: %s",Line);
            }else if(LineCount == 3){
                printf("Email: %s\n",Line);
            }
        }
        if(LineCount == 3){
            LineCount=0;
        }
    }
    fclose(AllContactFile);
    if(FoundContact == 0){
        printf("\nSorry no contact found for %s\n",Name);
    }
    GoBackOrExit();
}

void EditContact(){
    system("cls");
    printf("\n\t\t **** Edit Contact ****\n\n");

    int LineCount = 0;
    int FoundContact = 0;
    int SkipLines = 0;
    char GivenName[100];
    char NewName[100];
    char NewPhone[20];
    char NewEmail[100];
    char NewFullContact[300];
    NewFullContact[0] = 0;
    printf("*Name should be maximum 20 charters long.\n");
    printf("Enter The Name which one you want to edit: ");
    scanf(" %[^\n]s",GivenName);
    if(strlen(GivenName) > 20){
        ErrorAndRestart("!!!!Name Length Error!!!");
    }

    strcat(GivenName,"\n");

    FILE* OurExistingFile;
    FILE* NewTempFile;
    int LineLength = 255;
    char Line[LineLength];
    OurExistingFile = fopen("All-Contact.txt", "r");
    NewTempFile = fopen("temp-file.txt", "w");
    while(fgets(Line, LineLength, OurExistingFile)) {
        LineCount++;

        if(LineCount == 1 && strcmp(GivenName, Line) == 0){
            // we found the contact
            FoundContact = 1;
            SkipLines = 3;
        }

        if(SkipLines > 0){
            if(LineCount == 1){
                printf("\n*New Name should be unique and maximum 20 charters long.\n");
                printf("Old Name is: %s",Line);
                printf("New Name(0 for skip): ");
                scanf(" %[^\n]s",NewName);
                if(strcmp(NewName, "0") == 0){
                    strcat(NewFullContact,Line);
                }else{
                    if(strlen(NewName) > 20){
                        ErrorAndRestart("!!!!Name Length Error!!!");
                    }
                    if(AlreadyExists(NewName) == 1){
                        ErrorAndRestart("!!!!Name Already Exists!!!");
                    }
                    strcat(NewFullContact,NewName);
                    strcat(NewFullContact,"\n");
                }
                SkipLines = 2;
            }else if(LineCount == 2){
                printf("\n*New Phone should be unique and maximum 20 charters long.\n");
                printf("Old Phone is: %s",Line);
                printf("New Phone(0 for skip): ");
                scanf("%s",NewPhone);
                if(strcmp(NewPhone, "0") == 0){
                    strcat(NewFullContact,Line);
                }else{
                    if(strlen(NewPhone) > 20){
                        ErrorAndRestart("!!!!Phone Length Error!!!");
                    }
                    if(AlreadyExists(NewPhone) == 1){
                        ErrorAndRestart("!!!!Phone Already Exists!!!");
                    }
                    strcat(NewFullContact,NewPhone);
                    strcat(NewFullContact,"\n");
                }
                SkipLines = 1;
            }else if(LineCount == 3){
                printf("\n*New Email should be unique and maximum 30 charters long.\n");
                printf("Old Email is: %s",Line);
                printf("New Email(0 for skip): ");
                scanf("%s",NewEmail);

                if(strcmp(NewEmail, "0") == 0){
                    strcat(NewFullContact,Line);
                }else{
                    if(strlen(NewEmail) > 30){
                        ErrorAndRestart("!!!!Email Length Error!!!");
                    }
                    if(AlreadyExists(NewEmail) == 1){
                        ErrorAndRestart("!!!!Email Already Exists!!!");
                    }
                    strcat(NewFullContact,NewEmail);
                    strcat(NewFullContact,"\n");
                }
                SkipLines = 0;
                fprintf(NewTempFile,NewFullContact);
            }
        }else{
            fprintf(NewTempFile,Line);
        }

        if(LineCount == 3){
            LineCount = 0;
        }
    }
    fclose(NewTempFile);
    fclose(OurExistingFile);

    if(FoundContact == 0){
        printf("Contact Not Found!\n");
        remove("temp-file.txt");
    }else{
        printf("\nContact Updated Successfully!\n\n");
        remove("All-Contact.txt");
        rename("temp-file.txt", "All-Contact.txt");
    }
    GoBackOrExit();
}

void DeleteContact(){

    system("cls");
    printf("\n\t\t **** Delete Contact ****\n\n");

    int lineCount = 0;
    int FoundTheContact = 0;
    int SkipLines = 0;
    char GivenName[100];
    printf("\n*Name should be maximum 20 charters long.\n");
    printf("Enter The Name which one you want to delete: ");
    scanf(" %[^\n]s",GivenName);
    if(strlen(GivenName) > 20){
        ErrorAndRestart("!!!!Name Length Error!!!");
    }
    strcat(GivenName,"\n");

    FILE* OurExistingFile;
    FILE* NewTempFile;
    int LineLenght = 300;
    char line[LineLenght];
    OurExistingFile = fopen("All-Contact.txt", "r");
    NewTempFile = fopen("temp-file.txt", "w");
    while(fgets(line, LineLenght, OurExistingFile)) {
        lineCount++;

        if(lineCount == 1 && strcmp(GivenName, line) == 0){
            // we found the contact
            FoundTheContact = 1;
            SkipLines = 3;
        }

        if(SkipLines > 0){
            SkipLines--;
        }else{
            fprintf(NewTempFile,line);
        }

        if(lineCount == 3){
            lineCount = 0;
        }
    }
    fclose(NewTempFile);
    fclose(OurExistingFile);

    if(FoundTheContact == 0){
        printf("\nContact Not Found!\n\n");
        remove("temp-file.txt");
    }else{
        printf("\nContact Deleted Successfully!\n\n");
        remove("All-Contact.txt");
        rename("temp-file.txt", "All-Contact.txt");
    }
    GoBackOrExit();
}

void DeleteAllContacts(){
    system("cls");
    printf("\n\t\t **** Delete All The Contacts ****\n\n");

    char Option;
    getchar();
    printf("Are you sure want to delete all the contacts? (Y,N)?: ");
    scanf("%c",&Option);
    if(Option=='Y' || Option=='y'){
        int i;
        remove("All-Contact.txt");
        FILE *AllContactTxtFile = fopen("All-Contact.txt","a");
        fclose(AllContactTxtFile);

        char Deleting[100] = "Deleting....";
        for(i=0;i<strlen(Deleting);i++){
            printf("%c",Deleting[i]);
            Sleep(70);
        }
        printf("\nSuccessfully Deleted All Contacts!\n\n");

    }
    GoBackOrExit();
}

bool AlreadyExists(char *GivenLine[30]){
    char *ThisLine[35];
    ThisLine[0] = 0;
    strcat(ThisLine,GivenLine);
    strcat(ThisLine,"\n");

    FILE* AllContactFile;
    int LineLength = 300;
    char Line[LineLength];
    AllContactFile = fopen("All-Contact.txt", "r");
    int LineCount = 0;
    int TotalContact = 0;
    int Found = 0;
    while(fgets(Line, LineLength, AllContactFile)) {
       LineCount++;
        if(LineCount == 1 && strcmp(ThisLine, Line) == 0){
            Found = 1;
        }
        if(LineCount == 3){
            LineCount = 0;
        }
    }
    fclose(AllContactFile);
    if(Found == 1){
        return true;
    }else{
        return false;
    }
}

void ErrorAndRestart(char *error[100]){
    printf("%s\n",error);
    int i = 0;
    printf("Restarting the program: ");
    for(i=0;i<10;i++){
        printf(".");
        Sleep(500);
    }
    system("cls");
    main();
}

void GoBackOrExit(){
    char option;
    getchar();
    printf("Go Back(b)? or Exit(0)?");
    scanf("%c",&option);
    if(option=='0'){
        Exit();
    }else{
        system("cls");
    }
}

void UserGuideline(){
    system("cls");
    printf("\n\t\t **** My-Contact Management System ****\n");
    printf("\n\n\n\t\t\tUser Guideline\n");
    printf("\t\t===============================\n");
    printf("\t\t[>] This Program is created using C Language.\n");
    printf("\t\t[>] Contact information will store in a text file.\n");
    printf("\t\t[>] You will found the text file in the same folder.\n");
    printf("\t\t[>] Text fill create automatically.\n");
    printf("\t\t[>] Name, Phone and email should be unique.\n");
    printf("\t\t[>] Maximum length of name is 20 characters.\n");
    printf("\t\t[>] Maximum length of phone is 20 characters.\n");
    printf("\t\t[>] Maximum length of email is 30 characters.\n");
    printf("\t\t===============================\n\t\t");

    GoBackOrExit();
}

void AboutUs(){
    system("cls");
    printf("\n\t\t **** My-Contact Management System ****\n");
    printf("\n\n\n\t\t\tAbout US\n");
    printf("\t\t======================\n");
    printf("\t\t[i] This program is managed by CodeCartBD.com and InsideTheDiv.com\n");
    printf("\t\t[i] CodeCartBD is a programing related platform from where you can\n");
    printf("\t\t[>] learn computer programming or related technology in Bangla Language.\n");
    printf("\t\t[i] InsideTheDiv is a programing related platform where you will\n");
    printf("\t\t[>] found programing related problem's solution with source code.\n");
    printf("\t\t======================\n\t\t");
    GoBackOrExit();
}

void Exit(){
    getchar();
    printf("Are You Sure Want to Exit? (Y,N): ");
    char YesOrNO;
    scanf("%c",&YesOrNO);
    if(YesOrNO == 'Y' || YesOrNO == 'y'){
        system("cls");
        printf("Visit www.CodeCartBd.com for more.\n");
        printf("Visit www.insideTheDiv.com for more.\n");

        char ThankYou[100] = "=====Thank You=====\n";
        char SeeYouSoon[100] = "=====See You Soon=====\n";
        int i=0;
        for(i=0;i<strlen(ThankYou);i++){
            printf("%c",ThankYou[i]);
            Sleep(100);
        }
        for(i=0;i<strlen(SeeYouSoon);i++){
            printf("%c",SeeYouSoon[i]);
            Sleep(100);
        }
        isRunning =  false;
    }else{
         isRunning = true;
    }
}
