// thing to do next time, organization info, funds, options for each positions, announcements, edit members, promote members, 

// ask for name part,

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <ctype.h>

#define NAME_LENGTH 100
#define MAX_MEMBERS 20
#define MAX_ANNOUNCEMENTS 100
#define PASSWORD_TRIES 4
#define MESSAGE_LENGTH 1000
#define MESSAGE_COUNT 100
#define ABOUT_LENGTH 2000
#define DELIMITER "="
#define END_CHARACTER '~'

#define MEMBERS_FILE "c-files/accounts.txt"
#define MESSAGES_FILE "c-files/message.txt"
#define PENDING_FILE "c-files/pending-accounts.txt"
#define ABOUT_FILE "c-files/about.txt"
#define ANNOUNCEMENTS_FILE "c-files/announcements.txt"

typedef struct {
    char sender[NAME_LENGTH];
    char message[NAME_LENGTH];
} Inbox;

typedef struct {
    char username[NAME_LENGTH];
    char password[NAME_LENGTH];
    Inbox inbox[MESSAGE_COUNT];
    char studentNumber[NAME_LENGTH];
    char position[NAME_LENGTH];
    char program[NAME_LENGTH];
    char year[NAME_LENGTH];
    char birthday[NAME_LENGTH];
} Member;

Member member[MAX_MEMBERS];
Member pendingAccount[MAX_MEMBERS];
int membersCount;
int currentUser;
int pendingCount;

char orgAbout[ABOUT_LENGTH] = "";

typedef struct {
    int amount;
    char purpose[NAME_LENGTH];
} Funds;

char announcements[MAX_ANNOUNCEMENTS][MESSAGE_LENGTH];
int announcementsCount;

int sortAlphabetically();
char *inputPassword();

void loadMembers();
void saveMembers();
void loadMessages();
void saveMessages();
void loadPending();
void savePending();
void loadAbout();
void saveAbout();

bool login();
void signUp();

void adminOptions();
void organizationOptions();
void organizationAbout();
void membersOptions();
void pendingRequests();
void deleteMember(Member array[], int *size, int index);

void membersDelete();
void showPositions();
void editPositions(char position[]);
void transferPosition(char position[]);

void mainOptions();
void showMembers();

void profileOptions();
void viewProfile(int index);
void editInformation();
void changePassword();

void messageOptions();
void showInbox();
void sendMessage();

int main() {
    loadMembers();
    loadPending();
    loadMessages();
    loadAbout();

    int choice;
    bool isLogin = false;

    do {
        printf("[1] Sign Up\n");
        printf("[2] Login\n");
        printf("[3] Show Accounts\n");
        printf("[4] Exit\n");
        printf(">> ");
        scanf("%d", &choice);
        system("cls");
        switch (choice) {
            case 1: signUp(); break;
            case 2:
                isLogin = login();
                if (isLogin) {
                    if (!strcmp(member[currentUser].position, "President")) {
                        adminOptions();
                    } else {
                        mainOptions();
                    }
                }
                break;
            case 3: showMembers(); break;
            case 4: printf("\nThank you for using the program.\n"); break;
            default: printf("\nInvalid option!\n");
        }
    } while (choice != 4);

    return 0;
}

int sortAlphabetically(const void *a, const void *b) {
    const Member *personA = (const Member *)a;
    const Member *personB = (const Member *)b;
    return strcmp(personA->username, personB->username);
}

void loadMembers() {
    FILE *membersFile = fopen(MEMBERS_FILE, "r");
    membersCount = 0;

    if (!membersFile) {
        printf("\nThere was an error opening files.\n");
        exit(0);
    }

    char currentLine[NAME_LENGTH];
    for (int i = 0; fgets(currentLine, NAME_LENGTH, membersFile); i++) {
        currentLine[strcspn(currentLine, "\n")] = '\0';
        char *fileUsername = strtok(currentLine, DELIMITER);
        char *filePassword = strtok(NULL, DELIMITER);
        char *fileStudentNumber = strtok(NULL, DELIMITER);
        char *filePosition = strtok(NULL, DELIMITER);
        char *fileProgram = strtok(NULL, DELIMITER);
        char *fileYear = strtok(NULL, DELIMITER);
        char *fileBirthday = strtok(NULL, DELIMITER);
        strcpy(member[i].username, fileUsername);
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
        fprintf(membersFile, "%s%s%s%s%s%s%s%s%s%s%s%s%s\n", member[i].username, DELIMITER, member[i].password, DELIMITER, member[i].studentNumber, DELIMITER, member[i].position, DELIMITER, member[i].program, DELIMITER, member[i].year, DELIMITER, member[i].birthday);
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

    char currentLine[NAME_LENGTH];
    for (int i = 0; fgets(currentLine, NAME_LENGTH, pendingFile); i++) {
        currentLine[strcspn(currentLine, "\n")] = '\0';
        char *fileUsername = strtok(currentLine, DELIMITER);
        char *filePassword = strtok(NULL, DELIMITER);
        char *fileStudentNumber = strtok(NULL, DELIMITER);
        char *filePosition = strtok(NULL, DELIMITER);
        char *fileProgram = strtok(NULL, DELIMITER);
        char *fileYear = strtok(NULL, DELIMITER);
        char *fileBirthday = strtok(NULL, DELIMITER);
        strcpy(pendingAccount[i].username, fileUsername);
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
        fprintf(pendingFile, "%s%s%s%s%s%s%s%s%s%s%s%s%s\n", pendingAccount[i].username, DELIMITER, pendingAccount[i].password, DELIMITER, pendingAccount[i].studentNumber, DELIMITER, pendingAccount[i].position, DELIMITER, pendingAccount[i].program, DELIMITER, pendingAccount[i].year, DELIMITER, pendingAccount[i].birthday);
    }

    fclose(pendingFile);
}

void loadAbout() {
    FILE *aboutFile = fopen(ABOUT_FILE, "r");

    if (!aboutFile) {
        printf("\nThere was an error opening files.\n");
        exit(0);
    }

    char currentLine[MESSAGE_LENGTH];
    for (int i = 0; fgets(currentLine, MESSAGE_LENGTH, aboutFile); i++) {
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

    char currentLine[MESSAGE_LENGTH];
    for (int i = 0; fgets(currentLine, MESSAGE_LENGTH, messagesFile); i++) {
        currentLine[strcspn(currentLine, "\n")] = '\0';
        char *fileUsername = strtok(currentLine, "|");

        char *fileSender;
        char *fileMessage;

        for (int j = 0; (fileSender = strtok(NULL, "`")) && (fileMessage = strtok(NULL, "^")); j++) {
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
        fprintf(messagesFile, "%s|", member[i].username);

        for (int j = 0; j < MESSAGE_COUNT; j++) {
            if (!strlen(member[i].inbox[j].sender)||!strlen(member[i].inbox[j].message)) continue;
            fprintf(messagesFile, "%s`%s^", member[i].inbox[j].sender, member[i].inbox[j].message);
        }
        fprintf(messagesFile, "\n");
    }

    fclose(messagesFile);
}

void loadAnnouncements() {
    FILE *announcementsFile = fopen(ABOUT_FILE, "r");

    if (!announcementsFile) {
        printf("\nThere was an error opening files.\n");
        exit(0);
    }

    announcementsCount = 0;

    while (fgets(announcements[announcementsCount], MESSAGE_LENGTH, announcementsFile)) {
        announcements[announcementsCount][strcspn(announcements[announcementsCount], "\n")] = '\0';
        announcementsCount++;
    }

    fclose(announcementsFile);
}

void saveAnnouncements() {
    FILE *announcementsFile = fopen(ABOUT_FILE, "w");

    if (!announcementsFile) {
        printf("\nThere was an error opening files.\n");
        exit(0);
    }

    for (int i = 0; i < announcementsCount; i++) {
        fprintf(announcementsFile, "%s\n", announcements[i]);
    }
    
    fclose(announcementsFile);
}


void signUp() {
    char username[NAME_LENGTH];
    char password[NAME_LENGTH];
    char studentNumber[NAME_LENGTH];
    char program[NAME_LENGTH];
    char year[NAME_LENGTH];
    char birthday[NAME_LENGTH];

    bool isTaken;

    getchar();
    do {
        isTaken = false;
        printf("Enter username: ");
        fgets(username, NAME_LENGTH, stdin);
        username[strcspn(username, "\n")] = '\0';
        for (int i = 0; i < pendingCount; i++) {
            if (!strcmp(pendingAccount[i].username, username)) {
                printf("\nUsername is already taken.\n");
                isTaken = true;
                printf("\nPress Enter to continue...");
                getchar();
                system("cls");
            }
        }
        for (int i = 0; i < membersCount; i++) {
            if (!strcmp(member[i].username, username)) {
                printf("\nUsername is already taken.\n");
                isTaken = true;
                printf("\nPress Enter to continue...");
                getchar();
                system("cls");
            }
        }
    } while (isTaken);

    do {
        if (strstr(password, DELIMITER)){
            printf("\nPassword should not contain '%s'\n", DELIMITER);
        }
        printf("Enter password: ");
        fgets(password, NAME_LENGTH, stdin);
        password[strlen(password)-1] = '\0';
    } while (strstr(password, DELIMITER));
    
    printf("Enter your student number: ");
    fgets(studentNumber, NAME_LENGTH, stdin);
    studentNumber[strcspn(studentNumber, "\n")] = '\0';

    printf("Enter your program: ");
    fgets(program, NAME_LENGTH, stdin);
    program[strcspn(program, "\n")] = '\0';

    printf("Enter your year: ");
    fgets(year, NAME_LENGTH, stdin);
    year[strcspn(year, "\n")] = '\0';

    printf("Enter your birthday: ");
    fgets(birthday, NAME_LENGTH, stdin);
    birthday[strcspn(birthday, "\n")] = '\0';

    strcpy(pendingAccount[pendingCount].username, username);
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
    bool isLogin = false;
    bool isFound;
    char username[NAME_LENGTH];
    char password[NAME_LENGTH];

    getchar();
    for (int i = PASSWORD_TRIES - 1; i >= 0; i--) {
        isFound = false;
        printf("Enter username: ");
        fgets(username, NAME_LENGTH, stdin);
        username[strlen(username)-1] = '\0';

        printf("Enter password: ");
        fgets(password, NAME_LENGTH, stdin);
        password[strlen(password)-1] = '\0';

        for (int j = 0; j < membersCount; j++) {
            if (!strcmp(member[j].username, username)) {
                if (!strcmp(member[j].password, password)) {
                    isLogin = true;
                    currentUser = j;
                } else {
                    isFound = true;
                }
                break;
            }
        }

        if (isLogin) {
            break;
        } else if (isFound) {
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
    return isLogin;
}


void mainOptions() {
    int choice;
    printf("\nWelcome!\n");
    do {
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

void adminOptions() {
    int choice;
    printf("\nWelcome!\n");
    do {
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
                membersOptions();
                break;
            case 3:
                // announcementOption();
                break;
            case 4:
                // fundsOption();
                break;
            case 5:
                system("cls");
            default:
                printf("\nInvalid option!\n");
        }
    } while (choice != 5);
}

void organizationAbout() {
    int choice;
    char input[ABOUT_LENGTH];
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
                    if (index < ABOUT_LENGTH - 1) {
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

void membersOptions() {
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
        printf("[%d]: %s\n", i+1, member[i].username);
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
            printf("[%d]: %s\n", i+1, pendingAccount[i].username);
        }
        printf("\n>> ");
        scanf("%d", &choice);
        index = choice - 1;
        system("cls");

        printf("\nUsername: %s\n", pendingAccount[index].username);
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
                strcpy(member[membersCount].username, pendingAccount[index].username);
                strcpy(member[membersCount].password, pendingAccount[index].password);
                strcpy(member[membersCount].studentNumber, pendingAccount[index].studentNumber);
                strcpy(member[membersCount].position, "Member");
                strcpy(member[membersCount].program, pendingAccount[index].program);
                strcpy(member[membersCount].year, pendingAccount[index].year);
                strcpy(member[membersCount].birthday, pendingAccount[index].birthday);
                printf("\n%s has been added successfully\n", pendingAccount[index].username);
                membersCount++;
                deleteMember(pendingAccount, &pendingCount, index);
                savePending();
                saveMembers();
                break;         
            case 2:
                deleteMember(pendingAccount, &pendingCount, index);
                printf("\n%s has been deleted successfully\n", pendingAccount[index].username);
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
            printf("[%d]: %s\n", i+1, member[i].username);
        }
        printf("\n>> ");
        scanf("%d", &choice);
        index = choice - 1;
        system("cls");

        printf("\nUsername: %s\n", member[index].username);
        printf("Program: %s\n", member[index].program);
        printf("Year: %s\n", member[index].year);
        printf("Birthday: %s\n", member[index].birthday);

        printf("\n[1] Delete member\n");
        printf("[2] Return\n");
        printf(">> ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                deleteMember(member, &membersCount, index);
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
            printf(" %s\n", member[i].username);
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
        if (member[i].username == member[currentUser].username) {
            continue;
        } else {
            index++;
            printf("[%d]: %s\n", index, member[i].username);
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

void deleteMember(Member array[], int *size, int index) {
    for (int i = index; i < *size - 1; i++) {
        array[i] = array[i + 1];
    }

    strcpy(array[*size - 1].username, "\0");
    strcpy(array[*size - 1].password, "\0");
    strcpy(array[*size - 1].studentNumber, "\0");
    strcpy(array[*size - 1].position, "\0");
    strcpy(array[*size - 1].program, "\0");
    strcpy(array[*size - 1].year, "\0");
    strcpy(array[*size - 1].birthday, "\0");

    (*size)--;
    saveMembers();
}


void profileOptions() {
    int choice;
    do {
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
    printf("\nUsername: %s\n", member[index].username);
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
    char newUsername[NAME_LENGTH];
    char newProgram[NAME_LENGTH];
    char newYear[NAME_LENGTH];
    char newBirthday[NAME_LENGTH];
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
                    printf("Enter your new username: ");
                    fgets(newUsername, NAME_LENGTH, stdin);
                    newUsername[strcspn(newUsername, "\n")] = '\0';
                    for (int i = 0; i < membersCount; i++) {
                        if (!strcmp(member[currentUser].username, newUsername)) {
                            printf("\nUsername is already taken.\n");
                            isTaken = true;
                            printf("\nPress Enter to continue...");
                            getchar();
                            system("cls");
                        }
                    }
                } while (isTaken);
                strcpy(member[currentUser].username, newUsername);
                printf("\nYour name has been changed successfully...");
                getchar();
                system("cls");
                break;
            case 2:
                getchar();
                printf("Enter your new program: ");
                fgets(newProgram, NAME_LENGTH, stdin);
                newProgram[strcspn(newProgram, "\n")] = '\0';
                strcpy(member[currentUser].program, newProgram);
                printf("\nYour program has been changed successfully...");
                getchar();
                system("cls");
                break;
            case 3:
                getchar();
                printf("Enter your new year: ");
                fgets(newYear, NAME_LENGTH, stdin);
                newYear[strcspn(newYear, "\n")] = '\0';
                strcpy(member[currentUser].year, newYear);
                printf("\nYour year has been changed successfully...");
                getchar();
                system("cls");
                break;
            case 4:
                getchar();
                printf("Enter your new birthday: ");
                fgets(newBirthday, NAME_LENGTH, stdin);
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
    char oldPassword[NAME_LENGTH];
    char newPassword[NAME_LENGTH];

    getchar();
    printf("Enter your current password: ");
    fgets(oldPassword, NAME_LENGTH, stdin);
    oldPassword[strlen(oldPassword)-1] = '\0';

    if (!strcmp(oldPassword, member[currentUser].password)) {
        do {
            if (strstr(newPassword, DELIMITER)){
                printf("\nPassword should not contain '%s'\n", DELIMITER);
            }
            printf("Enter your new password: ");
            fgets(newPassword, NAME_LENGTH, stdin);
            newPassword[strlen(newPassword)-1] = '\0';
        } while (strstr(newPassword, DELIMITER));

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
    for (; messageCount < MESSAGE_COUNT && strlen(member[currentUser].inbox[messageCount].sender); messageCount++){}
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
    char message[MESSAGE_LENGTH];
    int index = 0;

    printf("\n[MEMBERS]\n");
    for (int i = 0; i < membersCount; i++) {
        if (member[i].username == member[currentUser].username) {
            continue;
        } else {
            index++;
            printf("[%d]: %s\n", index, member[i].username);
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
    for (; messageCount < MESSAGE_COUNT && strlen(member[choice-1].inbox[messageCount].sender); messageCount++)
    if (MESSAGE_COUNT == messageCount) {
        printf("This person's inbox is full!"); 
        return;
    }

    getchar();
    printf("\nWrite the message: \n");
    printf(">> ");
    fgets(message, MESSAGE_LENGTH, stdin);
    message[strcspn(message, "\n")] = '\0';

    strcpy(member[choice-1].inbox[messageCount].sender, member[currentUser].username);
    strcpy(member[choice-1].inbox[messageCount].message, message);
    saveMessages();

    printf("\nMessage sent!\n");
    printf("\nPress Enter to continue...");
    getchar();
    system("cls");
}

// void enterPassword(Member *member) {
//     char input;
//     int i = 0;

//     printf("Enter your password (press Enter to finish): ");

//     while (1) {
//         input = getch();

//         if (input == '\r') { 
//             break;
//         } else if (input == '\b') {
//             if (i > 0) {
//                 printf("\b \b");
//                 i--;
//             }
//         } else {
//             if (i < sizeof(member->password) - 1) {
//                 member->password[i++] = input;
//                 printf("*");
//             }
//         }
//     }

//     member->password[i] = '\0';
//     printf("\n");
// }

// char *inputPassword() {
//     char password[NAME_LENGTH];
//     int index = 0;
//     char input;

//     while (1) {
//         input = getch(); 

//         if (input == '\r') { 
//             break;
//         } else if (input == '\b') {
//             if (index > 0) {
//                 printf("\b \b");
//                 index--;
//             }
//         } else {
//             if (index < NAME_LENGTH) {
//                 password[index++] = input;
//                 printf("*");
//             }
//         }
//     }

//     password[index] = '\0';
//     printf("\n");

//     return password;
// }
