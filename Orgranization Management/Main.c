// prio: options for each positions, transfer positions
// minor: potential bugs, specific max values

//Members functions: Profile, Messages, See Announcements, About Organization, 
//President and Vice-President Functions: All
//Secretary: Member Access, Announcements, Edit About Oganization
//Treasurer: Funds Access
//Auditor: Funds Access


// ask for name part,

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <ctype.h>

#define MAX_INFO_LENGTH 100
#define MAX_MEMBERS 20
#define MAX_ABOUT_LENGTH 2000
#define MAX_ANNOUNCEMENTS 100
#define MAX_ANNOUNCEMENT_LENGTH 256
#define MAX_MESSAGES 100
#define MAX_MESSAGE_LENGTH 1000
#define MAX_FUNDS 100
#define MAX_PASSWORD_TRIES 4

#define ACCOUNT_DELIMITER "="
#define MESSAGE_DELIMITER_1 "|"
#define MESSAGE_DELIMITER_2 "^"
#define MESSAGE_DELIMITER_3 "`"
#define END_CHARACTER '~'

#define MEMBERS_FILE "c-files/accounts.txt"
#define MESSAGES_FILE "c-files/message.txt"
#define PENDING_FILE "c-files/pending-accounts.txt"
#define ABOUT_FILE "c-files/about.txt"
#define ANNOUNCEMENTS_FILE "c-files/announcements.txt"
#define FUNDS_FILE "c-files/funds.txt"

typedef struct {
    char sender[MAX_INFO_LENGTH];
    char message[MAX_INFO_LENGTH];
} Inbox;

typedef struct {
    char name[MAX_INFO_LENGTH];
    char password[MAX_INFO_LENGTH];
    char studentNumber[MAX_INFO_LENGTH];
    char position[MAX_INFO_LENGTH];
    char program[MAX_INFO_LENGTH];
    char year[MAX_INFO_LENGTH];
    char birthday[MAX_INFO_LENGTH];
    Inbox inbox[MAX_MESSAGES];
} Member;

Member member[MAX_MEMBERS];
Member pendingAccount[MAX_MEMBERS];
int membersCount;
int currentUser;
int pendingCount;

char orgAbout[MAX_ABOUT_LENGTH] = "";

char announcements[MAX_ANNOUNCEMENTS][MAX_MESSAGE_LENGTH];
int announcementsCount;

typedef struct {
    char category[MAX_INFO_LENGTH];
    int amount;
    char purpose[MAX_INFO_LENGTH];
} Funds;

Funds fund[MAX_FUNDS];
int fundsCount;
int fundsTotal = 0;

// char ListPostedAnnouncements[MAX_ANNOUNCEMENTS][MAX_ANNOUNCEMENT_LENGTH];
// int announcement_counter = 0;

int sortAlphabetically();
// char *inputPassword();

// Function prototypes
void loadMembers();
void saveMembers();
void loadMessages();
void saveMessages();
void loadPending();
void savePending();
void loadAbout();
void saveAbout();
void loadAnnouncements();
void saveAnnouncements();
void loadFunds();
void saveFunds();

bool login();
void signUp();

void presidentOptions();
void memberOptions();

void profileOptions();
void viewProfile(int index);
void editInformation();
void changePassword();

void messageOptions();
void showInbox();
void sendMessage();

void organizationOptions();
void organizationAbout();

void announcementsOptions();
void showAnnouncements();
void postAnnouncements();
void removeAnnouncements();

void editMembersOptions();
void showMembers();
void pendingRequests();
void membersDelete();
void showPositions();
void editPositions(char position[]);
void transferPosition(char position[]);
void removeMember(Member array[], int *size, int index);

void fundsOptions();
void fundsHistory();
void addFunds();
void addExpense();
void deleteExpense();
void overrideFunds();

// main function
int main() {
    loadMembers();
    loadPending();
    loadMessages();
    loadAbout();
    loadAnnouncements();
    loadFunds();

    int choice;
    bool isLogin = false;

    do {
        printf("\n[ORGANIZATION MANAGEMENT]\n");
        printf("[1] Sign Up\n");
        printf("[2] Login\n");
        printf("[3] Exit\n");
        printf(">> ");
        scanf("%d", &choice);
        system("cls");
        switch (choice) {
            case 1: signUp(); break;
            case 2:
                isLogin = login();
                if (isLogin) {
                    if (!strcmp(member[currentUser].position, "President")) {
                        presidentOptions();
                    } else {
                        memberOptions();
                    }
                }
                break;
            case 3: printf("\nThank you for using the program.\n"); break;
            default: printf("\nInvalid option!\n");
        }
    } while (choice != 3);

    return 0;
}


// for sorting
int sortAlphabetically(const void *a, const void *b) {
    const Member *personA = (const Member *)a;
    const Member *personB = (const Member *)b;
    return strcmp(personA->name, personB->name);
}


// load/save stuff
void loadMembers() {
    FILE *membersFile = fopen(MEMBERS_FILE, "r");
    membersCount = 0;

    if (!membersFile) {
        printf("\nThere was an error opening files.\n");
        exit(0);
    }

    char currentLine[MAX_INFO_LENGTH];
    for (int i = 0; fgets(currentLine, MAX_INFO_LENGTH, membersFile); i++) {
        currentLine[strcspn(currentLine, "\n")] = '\0';
        char *fileUsername = strtok(currentLine, ACCOUNT_DELIMITER);
        char *filePassword = strtok(NULL, ACCOUNT_DELIMITER);
        char *fileStudentNumber = strtok(NULL, ACCOUNT_DELIMITER);
        char *filePosition = strtok(NULL, ACCOUNT_DELIMITER);
        char *fileProgram = strtok(NULL, ACCOUNT_DELIMITER);
        char *fileYear = strtok(NULL, ACCOUNT_DELIMITER);
        char *fileBirthday = strtok(NULL, ACCOUNT_DELIMITER);
        strcpy(member[i].name, fileUsername);
        strcpy(member[i].password, filePassword);
        strcpy(member[i].studentNumber, fileStudentNumber);
        strcpy(member[i].position, filePosition);
        strcpy(member[i].program, fileProgram);
        strcpy(member[i].year, fileYear);
        strcpy(member[i].birthday, fileBirthday);
        membersCount++;
    }

    qsort(member, membersCount, sizeof(Member), sortAlphabetically);
    
    fclose(membersFile);
}

void saveMembers() {
    FILE *membersFile = fopen(MEMBERS_FILE, "w");

    if (!membersFile) {
        printf("\nThere was an error opening files.\n");
        exit(0);
    }
    
    qsort(member, membersCount, sizeof(Member), sortAlphabetically);

    for (int i = 0; i < membersCount; i++) {
        fprintf(membersFile, "%s%s%s%s%s%s%s%s%s%s%s%s%s\n", member[i].name, ACCOUNT_DELIMITER, member[i].password, ACCOUNT_DELIMITER, member[i].studentNumber, ACCOUNT_DELIMITER, member[i].position, ACCOUNT_DELIMITER, member[i].program, ACCOUNT_DELIMITER, member[i].year, ACCOUNT_DELIMITER, member[i].birthday);
    }

    fclose(membersFile);
}

void loadPending() {
    FILE *pendingFile = fopen(PENDING_FILE, "r");
    pendingCount = 0;

    if (!pendingFile) {
        printf("\nThere was an error opening files.\n");
        exit(0);
    }

    char currentLine[MAX_INFO_LENGTH];
    for (int i = 0; fgets(currentLine, MAX_INFO_LENGTH, pendingFile); i++) {
        currentLine[strcspn(currentLine, "\n")] = '\0';
        char *fileUsername = strtok(currentLine, ACCOUNT_DELIMITER);
        char *filePassword = strtok(NULL, ACCOUNT_DELIMITER);
        char *fileStudentNumber = strtok(NULL, ACCOUNT_DELIMITER);
        char *filePosition = strtok(NULL, ACCOUNT_DELIMITER);
        char *fileProgram = strtok(NULL, ACCOUNT_DELIMITER);
        char *fileYear = strtok(NULL, ACCOUNT_DELIMITER);
        char *fileBirthday = strtok(NULL, ACCOUNT_DELIMITER);
        strcpy(pendingAccount[i].name, fileUsername);
        strcpy(pendingAccount[i].password, filePassword);
        strcpy(pendingAccount[i].studentNumber, fileStudentNumber);
        strcpy(pendingAccount[i].position, filePosition);
        strcpy(pendingAccount[i].program, fileProgram);
        strcpy(pendingAccount[i].year, fileYear);
        strcpy(pendingAccount[i].birthday, fileBirthday);
        pendingCount++;
    }

    qsort(pendingAccount, pendingCount, sizeof(Member), sortAlphabetically);
    
    fclose(pendingFile);
}

void savePending() {
    FILE *pendingFile = fopen(PENDING_FILE, "w");

    if (!pendingFile) {
        printf("\nThere was an error opening files.\n");
        exit(0);
    }
    
    qsort(pendingAccount, pendingCount, sizeof(Member), sortAlphabetically);

    for (int i = 0; i < pendingCount; i++) {
        fprintf(pendingFile, "%s%s%s%s%s%s%s%s%s%s%s%s%s\n", pendingAccount[i].name, ACCOUNT_DELIMITER, pendingAccount[i].password, ACCOUNT_DELIMITER, pendingAccount[i].studentNumber, ACCOUNT_DELIMITER, pendingAccount[i].position, ACCOUNT_DELIMITER, pendingAccount[i].program, ACCOUNT_DELIMITER, pendingAccount[i].year, ACCOUNT_DELIMITER, pendingAccount[i].birthday);
    }

    fclose(pendingFile);
}

void loadAbout() {
    FILE *aboutFile = fopen(ABOUT_FILE, "r");

    if (!aboutFile) {
        printf("\nThere was an error opening files.\n");
        exit(0);
    }

    char currentLine[MAX_MESSAGE_LENGTH];
    for (int i = 0; fgets(currentLine, MAX_MESSAGE_LENGTH, aboutFile); i++) {
        strcat(orgAbout, currentLine);
    }
    
    fclose(aboutFile);
}

void saveAbout() {
    FILE *aboutFile = fopen(ABOUT_FILE, "w");

    if (!aboutFile) {
        printf("\nThere was an error opening files.\n");
        exit(0);
    }

    fprintf(aboutFile, "%s", orgAbout);
    
    fclose(aboutFile);
}

void loadMessages() {
    FILE *messagesFile = fopen("c-files/message.txt", "r");

    if (!messagesFile) {
        printf("\nThere was an error opening files.\n");
        exit(0);
    }

    char currentLine[MAX_MESSAGE_LENGTH];
    for (int i = 0; fgets(currentLine, MAX_MESSAGE_LENGTH, messagesFile); i++) {
        currentLine[strcspn(currentLine, "\n")] = '\0';
        char *fileUsername = strtok(currentLine, MESSAGE_DELIMITER_1);

        char *fileSender;
        char *fileMessage;

        for (int j = 0; (fileSender = strtok(NULL, MESSAGE_DELIMITER_3)) && (fileMessage = strtok(NULL, MESSAGE_DELIMITER_2)); j++) {
            strcpy(member[i].inbox[j].sender, fileSender);
            strcpy(member[i].inbox[j].message, fileMessage);
        }
    }
    
    fclose(messagesFile);
}

void saveMessages() {
    FILE *messagesFile = fopen(MESSAGES_FILE, "w");

    if (!messagesFile) {
        printf("\nThere was an error opening files.\n");
        exit(0);
    }
    
    for (int i = 0; i < membersCount; i++) {
        fprintf(messagesFile, "%s%s", member[i].name, MESSAGE_DELIMITER_1);

        for (int j = 0; j < MAX_MESSAGES; j++) {
            if (!strlen(member[i].inbox[j].sender)||!strlen(member[i].inbox[j].message)) continue;
            fprintf(messagesFile, "%s%s%s%s", member[i].inbox[j].sender, MESSAGE_DELIMITER_3, member[i].inbox[j].message, MESSAGE_DELIMITER_2);
        }
        fprintf(messagesFile, "\n");
    } 

    fclose(messagesFile);
}

void loadAnnouncements() {
    FILE *announcementsFile = fopen(ANNOUNCEMENTS_FILE, "r");

    if (!announcementsFile) {
        printf("\nThere was an error opening files.\n");
        exit(0);
    }

    announcementsCount = 0;

    while (fgets(announcements[announcementsCount], MAX_ANNOUNCEMENT_LENGTH, announcementsFile)) {
        announcements[announcementsCount][strcspn(announcements[announcementsCount], "\n")] = '\0';
        announcementsCount++;
    }

    fclose(announcementsFile);
}

void saveAnnouncements() {
    FILE *announcementsFile = fopen(ANNOUNCEMENTS_FILE, "w");

    if (!announcementsFile) {
        printf("\nThere was an error opening files.\n");
        exit(0);
    }

    for (int i = 0; i < announcementsCount; i++) {
        fprintf(announcementsFile, "%s\n", announcements[i]);
    }
    
    fclose(announcementsFile);
}

void loadFunds() {
    FILE *fundsFile = fopen(FUNDS_FILE, "r");

    if (!fundsFile) {
        printf("\nThere was an error opening files.\n");
        exit(0);
    }

    fundsCount = 0;

    char currentLine[MAX_INFO_LENGTH];

    fgets(currentLine, MAX_INFO_LENGTH, fundsFile);
    currentLine[strcspn(currentLine, "\n")] = '\0';
    fundsTotal = atof(currentLine);

    while (fgets(currentLine, MAX_INFO_LENGTH, fundsFile)) {
        currentLine[strcspn(currentLine, "\n")] = '\0';
        char *category = strtok(currentLine, ACCOUNT_DELIMITER);
        char *amount = strtok(NULL, ACCOUNT_DELIMITER);
        char *purpose = strtok(NULL, ACCOUNT_DELIMITER);

        strcpy(fund[fundsCount].category, category);
        fund[fundsCount].amount = atof(amount);
        strcpy(fund[fundsCount].purpose, purpose);
        fundsCount++;
    }
    
    fclose(fundsFile);
}

void saveFunds() {
    FILE *fundsFile = fopen(FUNDS_FILE, "w");

    if (!fundsFile) {
        printf("\nThere was an error opening files.\n");
        exit(0);
    }

    fprintf(fundsFile, "%d\n", fundsTotal);

    for (int i = 0; i < fundsCount; i++) {
        fprintf(fundsFile, "%s%s%d%s%s\n", fund[i].category, ACCOUNT_DELIMITER, fund[i].amount, ACCOUNT_DELIMITER, fund[i].purpose);
    }
    
    fclose(fundsFile);
}

// Sign up/ login
void signUp() {
    char name[MAX_INFO_LENGTH];
    char password[MAX_INFO_LENGTH];
    char studentNumber[MAX_INFO_LENGTH];
    char program[MAX_INFO_LENGTH];
    char year[MAX_INFO_LENGTH];
    char birthday[MAX_INFO_LENGTH];

    bool isTaken;

    getchar();
    do {
        isTaken = false;
        printf("Enter your student number: ");
        fgets(studentNumber, MAX_INFO_LENGTH, stdin);
        studentNumber[strcspn(studentNumber, "\n")] = '\0';
        for (int i = 0; i < pendingCount; i++) {
            if (!strcmp(pendingAccount[i].studentNumber, studentNumber)) {
                printf("\nStudent number is already in pending.\n");
                isTaken = true;
                printf("\nPress Enter to continue...");
                getchar();
                system("cls");
            }
        }
        for (int i = 0; i < membersCount; i++) {
            if (!strcmp(member[i].studentNumber, studentNumber)) {
                printf("\nStudent number is already taken.\n");
                isTaken = true;
                printf("\nPress Enter to continue...");
                getchar();
                system("cls");
            }
        }
    } while (isTaken);
    
    do {
        if (strstr(password, ACCOUNT_DELIMITER)){
            printf("\nPassword should not contain '%s'\n", ACCOUNT_DELIMITER);
        }
        printf("Enter password: ");
        fgets(password, MAX_INFO_LENGTH, stdin);
        password[strlen(password)-1] = '\0';
    } while (strstr(password, ACCOUNT_DELIMITER));

    printf("Enter name: ");
    fgets(name, MAX_INFO_LENGTH, stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Enter your program: ");
    fgets(program, MAX_INFO_LENGTH, stdin);
    program[strcspn(program, "\n")] = '\0';

    printf("Enter your year: ");
    fgets(year, MAX_INFO_LENGTH, stdin);
    year[strcspn(year, "\n")] = '\0';

    printf("Enter your birthday: ");
    fgets(birthday, MAX_INFO_LENGTH, stdin);
    birthday[strcspn(birthday, "\n")] = '\0';

    strcpy(pendingAccount[pendingCount].name, name);
    strcpy(pendingAccount[pendingCount].password, password);
    strcpy(pendingAccount[pendingCount].studentNumber, studentNumber);
    strcpy(pendingAccount[pendingCount].position, "Pending");
    strcpy(pendingAccount[pendingCount].program, program);
    strcpy(pendingAccount[pendingCount].year, year);
    strcpy(pendingAccount[pendingCount].birthday, birthday);
    pendingCount++;

    printf("\nYour account is successfully created\n");
    printf("\nPress Enter to continue...");
    getchar();
    system("cls");
    
    savePending();
}

bool login() {
    bool isFound;
    char studentNumber[MAX_INFO_LENGTH];
    char password[MAX_INFO_LENGTH];

    getchar();
    for (int i = MAX_PASSWORD_TRIES - 1; i >= 0; i--) {
        isFound = false;
        printf("Enter student number: ");
        fgets(studentNumber, MAX_INFO_LENGTH, stdin);
        studentNumber[strlen(studentNumber)-1] = '\0';

        printf("Enter password: ");
        fgets(password, MAX_INFO_LENGTH, stdin);
        password[strlen(password)-1] = '\0';

        for (int j = 0; j < membersCount; j++) {
            if (!strcmp(member[j].studentNumber, studentNumber)) {
                if (!strcmp(member[j].password, password)) {
                    currentUser = j;
                    system("cls");
                    return true;
                } else {
                    isFound = true;
                }
                break;
            }
        }

        if (isFound) {
            printf("\nWrong password!\n");
        } else {
            printf("\nNo accounts found!\n");
        }

        if (i) {
            printf("\nYou have %d tries left\n", i);
        } else {
            printf("\nYou have no more tries\n");
        }

        printf("\nPress Enter to continue...");
        getchar();
        system("cls");
    }
    
    system("cls");
    return false;
}


// Options for each positions
void presidentOptions() {
    int choice;
    printf("\nWelcome!\n");
    do {
        printf("\nCurrent user: %s\n", member[currentUser].name);
        printf("[1] Profile\n");
        printf("[2] Organization Info\n");
        printf("[3] Messages\n");
        printf("[4] Log out\n");
        printf(">> ");
        scanf("%d", &choice);
        system("cls");
        switch (choice) {
            case 1:
                profileOptions();
                break;
            case 2:
                organizationOptions();
                break;
            case 3:
                messageOptions();
                break;
            case 4:
                printf("\nLogged out\n");
                printf("\nPress Enter to continue...");
                getchar();
                getchar();
                system("cls");
                break;
            default:
                printf("\nInvalid option!\n");
        }
    } while (choice != 4);
}

void memberOptions() {
    int choice;
    printf("\nWelcome!\n");
    do {
        printf("\nCurrent user: %s\n", member[currentUser].name);
        printf("[1] Profile\n");
        printf("[2] Change Password\n");
        printf("[3] Messages\n");
        printf("[4] Log out\n");
        printf(">> ");
        scanf("%d", &choice);
        system("cls");
        switch (choice) {
            case 1:
                profileOptions();
                break;
            case 2:
                changePassword();
                break;
            case 3:
                messageOptions();
                break;
            case 4:
                printf("\nLogged out\n");
                printf("\nPress Enter to continue...");
                getchar();
                getchar();
                system("cls");
                break;
            default:
                printf("\nInvalid option!\n");
        }
    } while (choice != 4);
}


// DEFAULT OPTIONS

// Profile Options
void profileOptions() {
    int choice;
    do {
        printf("\n[PROFILE]\n");
        printf("[1] View Profile\n");
        printf("[2] Edit Information\n");
        printf("[3] Change Password\n");
        printf("[4] Return to main menu\n");
        printf(">> ");
        scanf("%d", &choice);
        system("cls");
        switch (choice) {
            case 1:
                viewProfile(currentUser);
                break;
            case 2:
                editInformation();
                break;
            case 3:
                changePassword();
                break;
            case 4:
                system("cls");
                break;
            default:
                printf("\nInvalid option!\n");
        }
    } while (choice != 4);
}

void viewProfile(int index) {
    printf("\nUsername: %s\n", member[index].name);
    printf("Position: %s\n", member[index].position);
    printf("Program: %s\n", member[index].program);
    printf("Year: %s\n", member[index].year);
    printf("Birthday: %s\n", member[index].birthday);
    
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
    system("cls");
}

void editInformation() {
    int choice;
    bool isTaken;
    char newUsername[MAX_INFO_LENGTH];
    char newProgram[MAX_INFO_LENGTH];
    char newYear[MAX_INFO_LENGTH];
    char newBirthday[MAX_INFO_LENGTH];
    do {
        printf("\n[EDIT INFORMATION]\n");
        printf("[1] Name\n");
        printf("[2] Program\n");
        printf("[3] Year\n");
        printf("[4] Birthday\n");
        printf("[5] Return\n");
        printf(">> ");
        scanf("%d", &choice);
        system("cls");
        switch (choice) {
            case 1:
                do {
                    getchar();
                    isTaken = false;
                    printf("Enter your new name: ");
                    fgets(newUsername, MAX_INFO_LENGTH, stdin);
                    newUsername[strcspn(newUsername, "\n")] = '\0';
                    for (int i = 0; i < membersCount; i++) {
                        if (!strcmp(member[currentUser].name, newUsername)) {
                            printf("\nUsername is already taken.\n");
                            isTaken = true;
                            printf("\nPress Enter to continue...");
                            getchar();
                            system("cls");
                        }
                    }
                } while (isTaken);
                strcpy(member[currentUser].name, newUsername);
                printf("\nYour name has been changed successfully...");
                getchar();
                system("cls");
                break;
            case 2:
                getchar();
                printf("Enter your new program: ");
                fgets(newProgram, MAX_INFO_LENGTH, stdin);
                newProgram[strcspn(newProgram, "\n")] = '\0';
                strcpy(member[currentUser].program, newProgram);
                printf("\nYour program has been changed successfully...");
                getchar();
                system("cls");
                break;
            case 3:
                getchar();
                printf("Enter your new year: ");
                fgets(newYear, MAX_INFO_LENGTH, stdin);
                newYear[strcspn(newYear, "\n")] = '\0';
                strcpy(member[currentUser].year, newYear);
                printf("\nYour year has been changed successfully...");
                getchar();
                system("cls");
                break;
            case 4:
                getchar();
                printf("Enter your new birthday: ");
                fgets(newBirthday, MAX_INFO_LENGTH, stdin);
                newBirthday[strcspn(newBirthday, "\n")] = '\0';
                strcpy(member[currentUser].birthday, newBirthday);
                printf("\nYour birthday has been changed successfully...");
                getchar();
                system("cls");
                break;
            case 5:
                break;
            default:
                printf("\nInvalid option!\n");
        }
    } while (choice != 5);
}

void changePassword() {
    char oldPassword[MAX_INFO_LENGTH];
    char newPassword[MAX_INFO_LENGTH];

    getchar();
    printf("Enter your current password: ");
    fgets(oldPassword, MAX_INFO_LENGTH, stdin);
    oldPassword[strlen(oldPassword)-1] = '\0';

    if (!strcmp(oldPassword, member[currentUser].password)) {
        do {
            if (strstr(newPassword, ACCOUNT_DELIMITER)){
                printf("\nPassword should not contain '%s'\n", ACCOUNT_DELIMITER);
            }
            printf("Enter your new password: ");
            fgets(newPassword, MAX_INFO_LENGTH, stdin);
            newPassword[strlen(newPassword)-1] = '\0';
        } while (strstr(newPassword, ACCOUNT_DELIMITER));

        strcpy(member[currentUser].password, newPassword);
        printf("\nPassword change was successful!\n");
        saveMembers();
    } else {
        printf("\nIncorrect Password!\n");
    }
    printf("\nPress Enter to continue...");
    getchar();
    system("cls");
}

// Messaging Options
void messageOptions() {
    int choice;
    do {
        printf("\n[MESSAGES]\n");
        printf("[1] Inbox\n");
        printf("[2] Send Message\n");
        printf("[3] Back to main menu\n");
        printf(">> ");
        scanf("%d", &choice);
        system("cls");

        switch (choice) {
            case 1:
                showInbox();
                break;
            case 2:
                sendMessage();
                break;
            case 3:
                break;
            default:
                printf("\nInvalid option!\n");
        }
    } while (choice != 3);
}

void showInbox() {
    int messageCount = 0;
    printf("\n[INBOX]\n");
    for (; messageCount < MAX_MESSAGES && strlen(member[currentUser].inbox[messageCount].sender); messageCount++){}
    for (int i = 0; i < messageCount; i++) {
        printf("\n%s: %s\n", member[currentUser].inbox[i].sender, member[currentUser].inbox[i].message);
    }
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
    system("cls");
}

void sendMessage() {
    int choice;
    char message[MAX_MESSAGE_LENGTH];
    int index = 0;

    printf("\n[MEMBERS]\n");
    for (int i = 0; i < membersCount; i++) {
        if (member[i].name == member[currentUser].name) {
            continue;
        } else {
            index++;
            printf("[%d]: %s\n", index, member[i].name);
        }
    }

    printf("\nSend to: \n");
    printf(">> ");

    if (scanf("%d", &choice) && choice < 0 || choice > membersCount) {
        printf("\nInvalid option!\n");
        printf("\nPress Enter to continue...");
        getchar();
        getchar();
        system("cls");
        return;
    }

    if (choice > currentUser) {
        choice++;
    }

    int messageCount = 0;
    for (; messageCount < MAX_MESSAGES && strlen(member[choice-1].inbox[messageCount].sender); messageCount++)
    if (MAX_MESSAGES == messageCount) {
        printf("This person's inbox is full!"); 
        return;
    }

    getchar();
    printf("\nWrite the message: \n");
    printf(">> ");
    fgets(message, MAX_MESSAGE_LENGTH, stdin);
    message[strcspn(message, "\n")] = '\0';

    strcpy(member[choice-1].inbox[messageCount].sender, member[currentUser].name);
    strcpy(member[choice-1].inbox[messageCount].message, message);
    saveMessages();

    printf("\nMessage sent!\n");
    printf("\nPress Enter to continue...");
    getchar();
    system("cls");
}


// OFFICER OPTIONS

// Main options for editing the organization
void organizationOptions() {
    int choice;
    do {
        printf("\n[ORGANIZATION OPTIONS]\n");
        printf("[1] Organization About\n");
        printf("[2] Members\n");
        printf("[3] Announcements\n");
        printf("[4] Funds\n");
        printf("[5] Return\n");
        printf(">> ");
        scanf("%d", &choice);
        system("cls");
        switch (choice) {
            case 1:
                organizationAbout();
                break;
            case 2:
                editMembersOptions();
                break;
            case 3:
                announcementsOptions();
                break;
            case 4:
                fundsOptions();
                break;
            case 5:
                system("cls");
                break;
            default:
                printf("\nInvalid option!\n");
        }
    } while (choice != 5);
}


// About the organization
void organizationAbout() {
    int choice;
    char input[MAX_ABOUT_LENGTH];
    int index;
    char ch;
    do {
        printf("%s", orgAbout);

        printf("\n\n[1] Change About\n");
        printf("[2] Return\n");
        printf(">> ");
        scanf("%d", &choice);
        system("cls");
        switch (choice) {
            case 1: 
                index = 0;
                printf("Start typing (press '~' then 'Enter' to stop):\n");
                while (1) {
                    ch = getchar();
                    if (ch == END_CHARACTER) {
                        break;
                    }
                    if (index < MAX_ABOUT_LENGTH - 1) {
                        input[index++] = ch;
                    } else {
                        printf("Input reached maximum length. Stopping.\n");
                        break;
                    }
                }
                input[index] = '\0';

                strcpy(orgAbout, input);
                saveAbout();
                printf("\nSaved successfully!\n");
                printf("\nPress enter to continue");
                getchar();
                getchar();
                break;
            case 2:
                break;
            default:
                printf("\nInvalid option!\n");
        }
        system("cls");
    } while (choice != 2);
}


// Announcements Options
void announcementsOptions() {
    int choice;
    do {
        printf("[1] Show Announcement\n");
        printf("[2] Post Announcement\n");
        printf("[3] Remove Announcement\n");
        printf("[4] Return\n");
        printf(">> ");
        scanf("%d", &choice);
        system("cls");
        switch (choice) {
            case 1:
                showAnnouncements();
                break;
            case 2:
                postAnnouncements();
                break;
            case 3:
                removeAnnouncements();
                break;
            case 4:
                break;
            default:
                printf("\nInvalid option!\n");
        }
    } while (choice != 4);
}

void showAnnouncements() {
    bool isNoAnnouncements = true;
    for (int i = 0; i < announcementsCount; i++) {
        printf("\n[%d] %s\n", i+1, announcements[i]);
        isNoAnnouncements = false;
    }

    if (isNoAnnouncements) printf("\nThere are no annoucements currently\n");

    printf("\nPress Enter to continue...");
    getchar();
    getchar();
    system("cls");
}

void postAnnouncements() {
    printf("\nPost Announcement\n");
    printf(">> ");
    getchar();
    fgets(announcements[announcementsCount], MAX_ANNOUNCEMENT_LENGTH, stdin);
    announcements[announcementsCount][strcspn(announcements[announcementsCount], "\n")] = '\0';
    announcementsCount++;

    saveAnnouncements();
    printf("\nMessage successfully announced\n");
    printf("\nPress Enter to continue...");
    getchar();
    system("cls");
}

void removeAnnouncements() {
    bool isNoAnnouncements = true;
    int index;
    int choice;

    for (int i = 0; i < announcementsCount; i++) {
        printf("\n[%d] %s\n", i+1, announcements[i]);
        isNoAnnouncements = false;
    }

    if (isNoAnnouncements) {
        printf("\nThere are no annoucements currently\n");
        return;
        printf("\nPress Enter to continue...");
        getchar();
        getchar();
        system("cls");
    }


    printf("\nRemove announcement:\n");
    printf(">> ");
    scanf("%d", &choice);

    index = choice - 1;

    for (int i = index; i < announcementsCount - 1; i++) {
        strcpy(announcements[i], announcements[i + 1]);
    }

    strcpy(announcements[announcementsCount - 1], "\0");

    announcementsCount--;
    saveAnnouncements();
    printf("\nAnnouncement has been successfully removed\n");
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
    system("cls");
}


// Options for editing members 
void editMembersOptions() {
    int choice;
    do {
        printf("[MEMBER OPTIONS]\n");
        printf("[1] Show members\n");
        printf("[2] Pending requests\n");
        printf("[3] Delete members\n");
        printf("[4] Edit positions\n");
        printf("[5] Return\n");
        printf(">> ");
        scanf("%d", &choice);
        system("cls");
        switch (choice) {
            case 1:
                showMembers();
                break;
            case 2:
                pendingRequests();
                break;
            case 3:
                membersDelete();
                break;
            case 4:
                showPositions();
                break;
            case 5:
                system("cls");
                break;
            default:
                printf("\nInvalid option!\n");
        }
    } while (choice != 5);
}

void showMembers() {
    for (int i = 0; i < membersCount; i++) {
        printf("[%d]: %s\n", i+1, member[i].name);
    }
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
    system("cls");
}

void pendingRequests() {
    int choice;
    int index;
    if (pendingCount == 0) {
        printf("\nThere are no pending requests\n");
        printf("\nPress Enter to continue...");
        getchar();
        getchar();
        system("cls");
        return;
    }
    do {
        for (int i = 0; i < pendingCount; i++) {
            printf("[%d]: %s\n", i+1, pendingAccount[i].name);
        }
        printf("\n>> ");
        scanf("%d", &choice);
        index = choice - 1;
        system("cls");

        printf("\nUsername: %s\n", pendingAccount[index].name);
        printf("Program: %s\n", pendingAccount[index].program);
        printf("Year: %s\n", pendingAccount[index].year);
        printf("Birthday: %s\n", pendingAccount[index].birthday);

        printf("\n[1] Add to members\n");
        printf("[2] Delete request\n");
        printf("[3] Return\n");
        printf(">> ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                strcpy(member[membersCount].name, pendingAccount[index].name);
                strcpy(member[membersCount].password, pendingAccount[index].password);
                strcpy(member[membersCount].studentNumber, pendingAccount[index].studentNumber);
                strcpy(member[membersCount].position, "Member");
                strcpy(member[membersCount].program, pendingAccount[index].program);
                strcpy(member[membersCount].year, pendingAccount[index].year);
                strcpy(member[membersCount].birthday, pendingAccount[index].birthday);
                printf("\n%s has been added successfully\n", pendingAccount[index].name);
                membersCount++;
                removeMember(pendingAccount, &pendingCount, index);
                savePending();
                saveMembers();
                break;         
            case 2:
                removeMember(pendingAccount, &pendingCount, index);
                printf("\n%s has been deleted successfully\n", pendingAccount[index].name);
                savePending();
                break;
            case 3:
                system("cls");
                break;
            default:
                printf("Invalid option!");
        }
    } while (choice == 3);
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
    system("cls");
}

void membersDelete() {
    int choice;
    int index;
    do {
        for (int i = 0; i < membersCount; i++) {
            printf("[%d]: %s\n", i+1, member[i].name);
        }
        printf("\n>> ");
        scanf("%d", &choice);
        index = choice - 1;
        system("cls");

        printf("\nUsername: %s\n", member[index].name);
        printf("Program: %s\n", member[index].program);
        printf("Year: %s\n", member[index].year);
        printf("Birthday: %s\n", member[index].birthday);

        printf("\n[1] Delete member\n");
        printf("[2] Return\n");
        printf(">> ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                removeMember(member, &membersCount, index);
                break;         
            case 2:
                system("cls");
                break;                
            default:
                printf("Invalid option!");
        }
    } while (choice == 3);
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
    system("cls");
}

void showPositions() {
    int choice;
    printf("\n[1] President\n");
    printf("[2] Vice-President\n");
    printf("[3] Secretary\n");
    printf("[4] Treasurer\n");
    printf("[5] Auditor\n");
    printf("[6] Event Coordinator\n");
    printf("[7] Other\n");
    printf(">> ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            editPositions("President"); break;
        case 2:
            editPositions("Vice-President"); break;
        case 3:
            editPositions("Secretary"); break;
        case 4:
            editPositions("Treasurer"); break;
        case 5:
            editPositions("Auditor"); break;
        case 6:
            editPositions("Event Coordinator"); break;
        case 7:
            editPositions("Other"); break;
        case 8:
            break;
        default:
            printf("\nInvalid Option!\n");
            
    }

}

void editPositions(char position[]) {
    system("cls");
    int choice;
    bool isVacant = true;
    int i;
    
    for (i = 0; i < membersCount; i++) {
        if (!strcmp(position, member[i].position)) {
            printf("\n%s: ", position);
            printf(" %s\n", member[i].name);
            isVacant = false;
            break;
        }
    }

    if (isVacant || !strcmp(position, "President")) {
        if (isVacant) printf("\nThis position is currently vacant\n");
        printf("\n[1] Transfer position\n");
        printf("[2] Return\n");
        printf(">> ");
        scanf("%d", &choice);
        system("cls");
        switch (choice) {
            case 1: 
                if (!strcmp(position, "President") && strcmp(member[currentUser].position, "President")) {
                    printf("\nYou don't have the rights to tranfer this position to a member.\n");
                    printf("\nPress Enter to continue...");
                    getchar();
                    getchar();
                    system("cls"); 
                    break;
                }
                if (!strcmp(position, "Vice-President") && (strcmp(member[currentUser].position, "President") || strcmp(member[currentUser].position, "Vice-President"))) {
                    printf("\nYou don't have the rights to tranfer this position to a member.\n");
                    printf("\nPress Enter to continue...");
                    getchar();
                    getchar();
                    system("cls"); 
                    break;
                }
                transferPosition(position);
                break;
            case 2: system("cls"); break;
            default: 
                printf("Invalid Option...");
                getchar();
                getchar();
                system("cls");
        }
    } else {
        do {
            printf("\n[1] Transfer position\n");
            printf("[2] Remove position\n");
            printf("[3] Return\n");
            printf(">> ");
            scanf("%d", &choice);
            system("cls");
            switch (choice) {
                case 1: 
                    if (!strcmp(position, "President") && strcmp(member[currentUser].position, "President")) {
                        printf("\nYou don't have the rights to tranfer this officer's position.\n");
                        printf("\nPress Enter to continue...");
                        getchar();
                        getchar();
                        system("cls"); 
                        break;
                    }
                    if (!strcmp(position, "Vice-President") && (strcmp(member[currentUser].position, "President") || strcmp(member[currentUser].position, "Vice-President"))) {
                        printf("\nYou don't have the rights to tranfer this officer's position.\n");
                        printf("\nPress Enter to continue...");
                        getchar();
                        getchar();
                        system("cls"); 
                        break;
                    }
                    transferPosition(position);
                    break;
                case 2: 
                    if (!strcmp(position, "Vice-President") && (strcmp(member[currentUser].position, "President") || strcmp(member[currentUser].position, "Vice-President"))) {
                        printf("\nYou don't have the rights to remove this officer's position.\n");
                        printf("\nPress Enter to continue...");
                        getchar();
                        getchar();
                        system("cls"); 
                        break;
                    }
                    strcpy(member[i].position, "Member");

                    saveMembers();
                    printf("\nPosition has been successfully removed\n");
                    printf("\nPress Enter to continue...");
                    getchar();
                    getchar();
                    system("cls"); 
                    break;
                case 3: system("cls"); break;
                default: 
                    printf("Invalid Option...");
                    getchar();
                    getchar();
                    system("cls");
            }
        } while (choice != 3);
    }
    
}

void transferPosition(char position[]) {
    system("cls");
    int index = 0;
    int choice;

    printf("\n[MEMBERS]\n");
    for (int i = 0; i < membersCount; i++) {
        if (member[i].name == member[currentUser].name) {
            continue;
        } else {
            index++;
            printf("[%d]: %s\n", index, member[i].name);
        }
    }

    printf("\nTransfer to: \n");
    printf(">> ");

    if (scanf("%d", &choice) && choice < 0 || choice > membersCount) {
        printf("\nInvalid option!\n");
        printf("\nPress Enter to continue...");
        getchar();
        getchar();
        system("cls");
        return;
    }

    if (choice > currentUser) {
        choice++;
    }

    for (int i = 0; i < membersCount; i++) {
        if (!strcmp(position, member[i].position)) strcpy(member[i].position, "Member");
    }
    strcpy(member[choice-1].position, position);

    saveMembers();
    printf("\nPosition has been transfered successfully\n");
    getchar();
    getchar();
    system("cls");
}

void removeMember(Member array[], int *size, int index) {
    for (int i = index; i < *size - 1; i++) {
        array[i] = array[i + 1];
    }

    (*size)--;
    saveMembers();
}


// Options for funds
void fundsOptions() {
    int choice;
    do {
        printf("\n[FUNDS]\n");
        printf("[1] Show Funds History\n");
        printf("[2] Add Funds\n");
        printf("[3] Add Expenses\n");
        printf("[4] Delete Fund History\n");
        printf("[5] Override Funds\n");
        printf("[6] Return\n");
        printf(">> ");
        scanf("%d", &choice);
        system("cls");
        switch (choice) {
            case 1:
                fundsHistory();
                break;
            case 2:
                addFunds();
                break;
            case 3:
                addExpense();
                break;
            case 4:
                deleteExpense();
                break;
            case 5:
                overrideFunds();
                break;
            case 6:
                system("cls");
                break;
            default:
                printf("\nInvalid option!\n");
        }
    } while (choice != 6);
}

void fundsHistory() {
    printf("\nCurrent Funds: P%d\n", fundsTotal);


    if (fundsCount) {
        for (int i = 0; i < fundsCount; i++) {
            if (!strcmp(fund[i].category, "Funding")) {
                printf("\n%d. [%s]\nAmount: +P%d\nPurpose: %s\n", i+1, fund[i].category, fund[i].amount, fund[i].purpose);
            } else if (!strcmp(fund[i].category, "Expense")) {
                printf("\n%d. [%s]\nAmount: -P%d\nPurpose: %s\n", i+1, fund[i].category, fund[i].amount, fund[i].purpose);
            } else {
                printf("\n%d. [%s]\nAmount: P%d\nPurpose: %s\n", i+1, fund[i].category, fund[i].amount, fund[i].purpose);
            }
        }
    } else {
        printf("\nFunds history is currently empty\n");
    }
    
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
    system("cls");
}

void addFunds() {
    char purpose[MAX_INFO_LENGTH];

    printf("\nCurrent Funds: P%d\n", fundsTotal);

    strcpy(fund[fundsCount].category, "Funding");

    printf("\nEnter amount: ");
    scanf("%d", &fund[fundsCount].amount);
    fundsTotal += fund[fundsCount].amount;

    getchar();
    printf("Enter purpose: ");
    fgets(purpose, MAX_INFO_LENGTH, stdin);
    purpose[strcspn(purpose, "\n")] = '\0';    

    strcpy(fund[fundsCount].purpose, purpose);
    
    fundsCount++;

    saveFunds();
    printf("\nFunds has been added successfully\n");
    printf("\nPress Enter to continue...");
    getchar();
    system("cls");
}

void addExpense() {
    char purpose[MAX_INFO_LENGTH];

    printf("\nCurrent Funds: P%d\n", fundsTotal);

    strcpy(fund[fundsCount].category, "Expense");

    printf("\nEnter amount: ");
    scanf("%d", &fund[fundsCount].amount);
    fundsTotal -= fund[fundsCount].amount;

    if (fundsTotal < 0) {
        printf("\nInsufficient funds!\n");
        fundsTotal += fund[fundsCount].amount;
        printf("\nPress Enter to continue...");
        getchar();
        getchar();
        system("cls");
        return;
    }

    getchar();
    printf("Enter purpose: ");
    fgets(purpose, MAX_INFO_LENGTH, stdin);
    purpose[strcspn(purpose, "\n")] = '\0';    

    strcpy(fund[fundsCount].purpose, purpose);
    
    fundsCount++;

    saveFunds();
    printf("\nExpenses has been added successfully\n");
    printf("\nPress Enter to continue...");
    getchar();
    system("cls");
}

void deleteExpense() {
    int choice;
    printf("\nCurrent Funds: P%d\n", fundsTotal);
    if (fundsCount) {
        for (int i = 0; i < fundsCount; i++) {
            if (!strcmp(fund[i].category, "Funding")) {
                printf("\n%d. [%s]\nAmount: +P%d\nPurpose: %s\n", i+1, fund[i].category, fund[i].amount, fund[i].purpose);
            } else if (!strcmp(fund[i].category, "Expense")) {
                printf("\n%d. [%s]\nAmount: -P%d\nPurpose: %s\n", i+1, fund[i].category, fund[i].amount, fund[i].purpose);
            } else {
                printf("\n%d. [%s]\nAmount: P%d\nPurpose: %s\n", i+1, fund[i].category, fund[i].amount, fund[i].purpose);
            }
        }
    } else {
        printf("\nFunds history is currently empty\n");
        printf("\nPress Enter to continue...");
        getchar();
        getchar();
        system("cls");
        return;
    }

    printf("\nDelete expense:\n");
    printf(">> ");
    scanf("%d", &choice);


    for (int i = choice - 1; i < fundsCount - 1; i++) {
        fund[i] = fund[i + 1];
    }

    fundsCount--;
    saveFunds();

    printf("\nFund has been removed successfully\n");
    
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
    system("cls");
}

void overrideFunds() {
    char purpose[MAX_INFO_LENGTH];

    printf("\nCurrent Funds: P%d\n", fundsTotal);

    strcpy(fund[fundsCount].category, "Override");

    printf("\nEnter total amount: ");
    scanf("%d", &fundsTotal);
    fund[fundsCount].amount = fundsTotal;

    getchar();
    printf("Enter purpose: ");
    fgets(purpose, MAX_INFO_LENGTH, stdin);
    purpose[strcspn(purpose, "\n")] = '\0';    

    strcpy(fund[fundsCount].purpose, purpose);
    
    fundsCount++;

    saveFunds();
    printf("\nFunds has been overrided successfully\n");
    printf("\nPress Enter to continue...");
    getchar();
    system("cls");
}

//Announcements Section
// void postAnnouncement() {
//     printf("What's on your mind?\n");
//     getchar();
//     fgets(ListPostedAnnouncements[announcement_counter], MAX_ANNOUNCEMENT_LENGTH, stdin);
//     printf("Announcement Posted!");

//     FILE *post_announcement;
//     char ch[100];
//     int announcement_num = 1;

//     post_announcement = fopen("announcements.txt", "a+");
//     if(post_announcement == NULL) {
//         printf("Unable to open file.");
//         printf("Enter to continue...");
//         getchar();
//         return;
//     }

//     while (fgets(ch, sizeof(ch), post_announcement) != NULL) {
//         announcement_num++;
//     }

//     fprintf(post_announcement, "%d. %s", announcement_num, ListPostedAnnouncements[announcement_counter]);
//     fclose(post_announcement);
//     announcement_counter++;

//     printf("\n\nEnter to continue...");
//     getchar();
//     system("cls");
//     printf("Returning...");
//     // sleep(2);
//     system("cls");
// }

// void postedAnnouncements() {
//     FILE *announcements;
//     char ch[100];

//     announcements = fopen("announcements.txt", "r");
//     if(announcements == NULL) {
//         printf("Error in opening file.\n");
//         printf("Enter to continue...");
//         getchar();
//         return;
//     }

//     printf("Announcements:\n");
//     while(fgets(ch, sizeof(ch), announcements) != NULL) {
//         printf("%s", ch);
//     }
//     fclose(announcements);

//     printf("\n\nEnter to continue...");
//     getchar();
//     getchar();
//     system("cls");
//     printf("\nReturning...");
//     // sleep(2);
//     system("cls");
// }