#include <windows.h>
#include <unistd.h>
#include<stdio.h>
#include <string.h>
#include<stdbool.h>
#include <stdlib.h>

bool isRunning = true;
void Menu();
void AddNewNumber();
void ShowAllNumber();
void SearchNumber();
void EditNumber();
void DeleteNumber();
void DeleteAllNumber();
void ClearWindow();
void showNameWithSpace(char *name[20]);
void showPhoneWithSpace(char *phone[20]);
void showEmailWithSpace(char *email[20]);
void ErrorAndRestart(char *error[100]);
bool AlreadyExists(char *GivenLine[30]);
void GoBackOrExit();
void Exit();

int main(){
    int i;
    printf("\t\t");
    char AppStarting[100] = "Application is Starting....";
    for(i=0;i<strlen(AppStarting);i++){
        printf("%c",AppStarting[i]);
        Sleep(50);
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
                AddNewNumber();
                break;
            case '2':
                ShowAllNumber();
                break;
            case '3':
                SearchNumber();
                break;
            case '4':
                EditNumber();
                break;
            case '5':
                DeleteNumber();
                break;
            case '6':
                DeleteAllNumber();
                break;
            case '7':
                system("cls");
                break;
            default:
                ErrorAndRestart("Option not found!");
                break;
        }
    }
}
// all function
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
    printf("\t\t[0] Exit\n\t\t=================\n\t\t");
    printf("Enter the choice:");
}

void AddNewNumber(){
    char name[20];
    char phone[20];
    char email[30];
    char NewContact[100];
    NewContact[0] = 0;
    printf("Enter The Name: ");
    scanf(" %[^\n]s",name);
    if(strlen(name) > 20){
        ErrorAndRestart("!!!!Name Length Error!!!");
    }
    if(AlreadyExists(name) == 1){
        ErrorAndRestart("!!!!Name Already Exists!!!");
    }
    printf("Enter The Phone Number: ");
    scanf("%s",phone);
    if(strlen(phone) > 20){
        ErrorAndRestart("!!!!Phone Length Error!!!!");
    }
    if(AlreadyExists(phone) == 1){
        ErrorAndRestart("!!!!Phone Number Already Exists!!!");
    }
    printf("Enter The Email: ");
    scanf("%s",email);
    if(strlen(email) > 30){
        ErrorAndRestart("!!!!Email Length Error!!!!");
    }
    if(AlreadyExists(email) == 1){
        ErrorAndRestart("!!!!Email Already Exists!!!");
    }
    strcat(NewContact,name);
    strcat(NewContact,"\n");
    strcat(NewContact,phone);
    strcat(NewContact,"\n");
    strcat(NewContact,email);
    strcat(NewContact,"\n");

    FILE *allContactTxtFile = fopen("All-Contact.txt","a");
    fprintf(allContactTxtFile,NewContact);
    fclose(allContactTxtFile);
    printf("Number Added Successfully!\n");
    GoBackOrExit();
}

void ShowAllNumber(){
    FILE* AllContactTextFile;
    int LineLength = 300;
    char line[LineLength];

    system("cls");
    printf("All Contacts:\n");

    printf("|====================|====================|==============================|\n");
    printf("|        Name        |    Phone Number    |          Email               |\n");
    printf("|====================|====================|==============================|\n");

    AllContactTextFile = fopen("All-Contact.txt", "r");
    int TotalContact = 0;
    int LineCount = 0;
    while(fgets(line, LineLength, AllContactTextFile)) {
        LineCount++;
        if(LineCount==1){
            showNameWithSpace(line);
        }else if(LineCount == 2){
           showPhoneWithSpace(line);
        }else if(LineCount == 3){
            showEmailWithSpace(line);
            LineCount=0;
            TotalContact++;
        }
    }
    printf("You Have Total %d Contacts\n",TotalContact);
    fclose(AllContactTextFile);
    GoBackOrExit();
}

void showNameWithSpace(char *name[20]){
    int i;
    char *name2 = NULL;
    name2 = strdup(name);
    int nameLength = strlen(name2);

    printf("|");
    for(i=0;i<nameLength-1;i++){
        printf("%c",name2[i]);
    }

    for(i=0;i<=20-nameLength;i++){
        printf(" ");
    }
}

void showPhoneWithSpace(char *phone[20]){
    int i;
    char *phone2 = NULL;
    phone2 = strdup(phone);
    int phoneLength = strlen(phone2);

    printf("|");
    for(i=0;i<phoneLength-1;i++){
        printf("%c",phone2[i]);
    }

    for(i=0;i<=20-phoneLength;i++){
        printf(" ");
    }
}

void showEmailWithSpace(char *email[30]){
    int i;
    char *emai2 = NULL;
    emai2 = strdup(email);
    int emailLength = strlen(emai2);

    printf("|");
    for(i=0;i<emailLength-1;i++){
        printf("%c",emai2[i]); // printing email without last char(new line)
    }

    for(i=0;i<=30-emailLength;i++){
        printf(" ");
    }
    printf("|\n");
    printf("|--------------------|--------------------|------------------------------|\n");
}

void SearchNumber(){
    int result;
    char name[100];

    printf("Enter The Name: ");
    scanf(" %[^\n]s",name);
    if(strlen(name) > 20){
        ErrorAndRestart("!!!!Name Length Error!!!");
    }
    strcat(name,"\n");

    FILE* AllContactFile;
    int LineLength = 255;
    char Line[LineLength];
    AllContactFile = fopen("All-Contact.txt", "r");
    int LineCount = 0;
    int TotalContact = 0;
    while(fgets(Line, LineLength, AllContactFile)) {
       LineCount++;
        if(LineCount == 1){
            result = strcmp(name, Line);
        }
        if(result == 0){

            if(LineCount==1){
                printf("Name: %s",Line);
            }else if(LineCount == 2){
                printf("Phone: %s",Line);
            }else if(LineCount == 3){
                printf("Email: %s",Line);
                printf("--------------------------\n");
                LineCount=0;
                TotalContact++;
            }
        }
    }
    fclose(AllContactFile);
    printf("Total %d Contacts Found!\n",TotalContact);
}

void EditNumber(){

    int lineCount = 0;
    int foundAndWrite = 0;
    int skipLines = 0;
    char GivenName[100];
    char NewName[100];
    char NewPhone[20];
    char NewEmail[100];
    char NewFullContact[300];
    NewFullContact[0] = 0;

    printf("Enter The Name which one you want to edit: ");
    scanf(" %[^\n]s",GivenName);
    if(strlen(GivenName) > 20){
        ErrorAndRestart("!!!!Name Length Error!!!");
    }

    strcat(GivenName,"\n");

    FILE* OurExistingFile;
    FILE* newTempFile;
    int bufferLength = 255;
    char line[bufferLength];
    OurExistingFile = fopen("All-Contact.txt", "r");
    newTempFile = fopen("temp-file.txt", "w");
    while(fgets(line, bufferLength, OurExistingFile)) {
        lineCount++;

        if(lineCount == 1 && strcmp(GivenName, line) == 0){
            // we found the contact
            foundAndWrite = 1;
            skipLines = 3;
        }

        if(skipLines > 0){
            if(lineCount == 1){
                printf("Name(0 for skip): ");
                scanf(" %[^\n]s",NewName);
                if(strcmp(NewName, "0") == 0){
                    strcat(NewFullContact,line);
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
                skipLines = 2;
            }else if(lineCount == 2){
                printf("Phone(0 for skip): ");
                scanf("%s",NewPhone);
                if(strcmp(NewPhone, "0") == 0){
                    strcat(NewFullContact,line);
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
                skipLines = 1;
            }else if(lineCount == 3){
                printf("Email(0 for skip): ");
                scanf("%s",NewEmail);

                if(strcmp(NewEmail, "0") == 0){
                    strcat(NewFullContact,line);
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
                skipLines = 0;
                lineCount = 0;
                fprintf(newTempFile,NewFullContact);
            }
        }else{
            fprintf(newTempFile,line);
        }
    }
    fclose(newTempFile);
    fclose(OurExistingFile);

    if(foundAndWrite == 0){
        printf("Contact Not Found!\n");
        remove("temp-file.txt");
    }else{
        printf("Contact Update Success\n");
        remove("All-Contact.txt");
        rename("temp-file.txt", "All-Contact.txt");
    }
    GoBackOrExit();
}

void DeleteNumber(){
    int lineCount = 0;
    int foundTheContact = 0;
    int skipLines = 0;
    char GivenName[100];

    printf("Enter The Name which one you want to delete: ");
    scanf(" %[^\n]s",GivenName);
    if(strlen(GivenName) > 20){
        ErrorAndRestart("!!!!Name Length Error!!!");
    }
    strcat(GivenName,"\n");

    FILE* OurExistingFile;
    FILE* newTempFile;
    int LineLenght = 300;
    char line[LineLenght];
    OurExistingFile = fopen("All-Contact.txt", "r");
    newTempFile = fopen("temp-file.txt", "w");
    while(fgets(line, LineLenght, OurExistingFile)) {
        lineCount++;

        if(lineCount == 1 && strcmp(GivenName, line) == 0){
            // we found the contact
            foundTheContact = 1;
            skipLines = 3;
        }

        if(skipLines > 0){
            if(lineCount == 1){
                // skipping the name
                skipLines = 2;
            }else if(lineCount == 2){
                // skipping the phone
                skipLines = 1;
            }else if(lineCount == 3){
                // skipping the email
                skipLines = 0;
                lineCount = 0;
            }
        }else{
            fprintf(newTempFile,line);
        }
    }
    fclose(newTempFile);
    fclose(OurExistingFile);

    if(foundTheContact == 0){
        printf("Contact Not Found!\n");
        remove("temp-file.txt");
    }else{
        printf("Contact Delete Success\n");
        remove("All-Contact.txt");
        rename("temp-file.txt", "All-Contact.txt");
    }
    GoBackOrExit();
}

void DeleteAllNumber(){
    char option;
    getchar();
    printf("Are you sure want to delete all the contacts? (Y,N)?: ");
    scanf("%c",&option);
    if(option=='Y' || option=='y'){
        int i;
        remove("All-Contact.txt");
        FILE *allContactTxtFile = fopen("All-Contact.txt","a");
        fclose(allContactTxtFile);

        system("cls");
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

void Exit(){
    getchar();
    printf("Are You Sure Want to Exit? (Y,N): ");
    char YesOrNO;
    scanf("%c",&YesOrNO);
    if(YesOrNO == 'Y' || YesOrNO == 'y'){
        system("cls");
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
        system("cls");
        isRunning = true;
    }
}




