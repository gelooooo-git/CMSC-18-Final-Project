#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <unistd.h>

#define PASSWORD "admin123"
#define MAX_MEMBER_COUNT 200
#define NAME_LENGTH 100
#define ROLE_COUNT 7
#define MEMBERS_FILE "members_list.txt"
#define OFFICERS_FILE "officers_list.txt"
#define FUNDS_FILE "total_funds.txt"
#define FUNDS_HISTORY "funds_history.txt"
#define MAX_ANNOUNCEMENTS 50
#define MAX_ANNOUNCEMENT_LENGTH 256
#define ROLE_COUNT 7

// Arrays
//char members[MAX_MEMBER_COUNT][NAME_LENGTH];
int active[MAX_MEMBER_COUNT]; 
int member_count = 0;
char roles[ROLE_COUNT][NAME_LENGTH] = {"President", "Vice President", "Secretary", "Treasurer", "Auditor", "Event Coordinator", "Public Relations and Communications"};
char officer_names[ROLE_COUNT][NAME_LENGTH] = {"Vacant", "Vacant", "Vacant", "Vacant", "Vacant", "Vacant", "Vacant"};
int total_funds = 0;
char ListPostedAnnouncements[MAX_ANNOUNCEMENTS][MAX_ANNOUNCEMENT_LENGTH];
int announcement_counter = 0;

//function prototypes
void adminPassword();
void addMember();
void showMembers();
void removeMember();
void saveMembers();
void loadMembers();
void listOfficers();
void replaceOfficer();
void saveOfficers();
void loadOfficers();
void loadFunds();
void saveFunds();
void fundsHistory(const char *action, int amount, const char *reason);
void expenses();
void fundsLog();
void collections();
void overrideFunds();
void postAnnouncement();
void createDraftAnnouncement();
void postedAnnouncements();

struct orgMember { 
    char surname[50];
    char firstname[50];
    char midInitials[5]; 
    int year; // 1-6 hanggang 6 yrs lnf diba tau asdjaskd
    int age;
    int active; // 1 for active and 0 for inactive
};

struct orgMember members[MAX_MEMBER_COUNT];

int main() {
    int choice;
    char input[50]; 
    int attempts = 3;

    loadMembers();
    loadOfficers();
    loadFunds();
    
    do {
        login:
        system("cls");
        printf("Welcome to ORGanized! a C-based Organization Management System\n");
        printf("    [1] Login as Admin\n");
        printf("    [2] Login as Member\n");
        printf("    [3] Close program\n");
        printf("What is your position? ");
        scanf("%d", &choice);
        system("cls");

        switch (choice) {
            case 1: // admin options
                printf("Please enter the password to proceed:\n");
                getchar();
                while (attempts > 0) { 
                    printf("Password: ");
                    fgets(input, sizeof(input), stdin); 
                    input[strcspn(input, "\n")] = 0;    

                    if (strcmp(input, PASSWORD) == 0) { 
                        printf("\nAccess granted! Welcome, admin!\n");
                        printf("Logging in as Administrator...");
                        sleep(2);
                        system("cls");
                        start:
                        do {
                            printf("Welcome to ORGanized! Currently logged in as Administrator\n");
                            printf("    [1] Manage Organization Members and Officers\n");
                            printf("    [2] Post Announcements/Schedule Meetings\n");
                            printf("    [3] Manage Funds\n");
                            printf("    [4] Log Out\n");
                            printf("What do you want to do? ");
                            scanf("%d", &choice);
                            system("cls");

                            switch (choice) {
                                case 1:
                                    printf("Loading...");
                                    sleep(2);
                                    system("cls");
                                    do {
                                        printf("MANAGE ORGANIZATION MEMBERS AND OFFICERS\n");
                                        printf("    [1] Add Member\n");
                                        printf("    [2] Show Members List\n");
                                        printf("    [3] Remove Member\n");
                                        printf("    [4] Show Officers List\n");
                                        printf("    [5] Replace Officers\n");
                                        printf("    [6] Return to Main Menu\n");
                                        printf("What do you want to do? ");
                                        scanf("%d", &choice);
                                        system("cls");

                                        switch (choice) {
                                            case 1: // add members
                                                printf("Loading...");
                                                sleep(2);
                                                system("cls");
                                                addMember();
                                                saveMembers();
                                                system("cls");
                                                break;
                                            case 2: // show list of members
                                                printf("Loading...");
                                                sleep(2);
                                                system("cls");
                                                showMembers();
                                                system("cls");
                                                break;
                                            case 3: // remove members from org
                                                printf("Loading...");
                                                sleep(2);
                                                system("cls");
                                                removeMember();
                                                saveMembers();
                                                system("cls");
                                                break;
                                            case 4: // show list of officers
                                                printf("Loading...");
                                                sleep(2);
                                                system("cls");
                                                listOfficers();
                                                system("cls");
                                                break;                                    
                                            case 5: // replace officer
                                                printf("Loading...");
                                                sleep(2);
                                                system("cls");
                                                replaceOfficer();
                                                saveOfficers();
                                                system("cls");
                                                break;
                                            case 6:
                                                printf("Returning to main interface...\n");
                                                sleep(2);
                                                break;  // Break out of the main loop and return to the main menu
                                            default:
                                                printf("Invalid choice! Choose among the options.\n");
                                        }
                                    } while (choice != 6);
                                    break;
                                case 2:
                                    printf("Loading...");
                                    sleep(2);
                                    system("cls");
                                    do {
                                        printf("ANNOUNCEMENTS AND MEETINGS\n");
                                        printf("    [1] Post an announcememt\n");
                                        printf("    [2] Create a draft\n");
                                        printf("    [3] See posted announcements\n");
                                        printf("    [4] Return to Main Menu\n");
                                        printf("Choose: ");
                                        scanf("%d", &choice);
                                        system("cls");

                                        switch (choice) {
                                            case 1:
                                                printf("Loading...");
                                                sleep(2);
                                                system("cls");
                                                postAnnouncement();
                                                system("cls");
                                                break;
                                            case 2:
                                                printf("Loading...");
                                                sleep(2);
                                                system("cls");
                                                createDraftAnnouncement();
                                                system("cls");
                                                break;
                                            case 3:
                                                printf("Loading...");
                                                sleep(2);
                                                system("cls");
                                                postedAnnouncements();
                                                system("cls");
                                                break;
                                            case 4:
                                                printf("Returning to Main Menu...\n");
                                                sleep(2);
                                                break;
                                            default:
                                                printf("Invalid choice! Choose among the options.\n");
                                        }
                                    } while (choice != 4);
                                    choice = -1;
                                    break;
                                case 3:
                                    printf("Loading...");
                                        sleep(2);
                                        system("cls");
                                    do {
                                        printf("FUND MANAGEMENT\n");
                                        printf("Current Total Funds: %d PHP\n", total_funds);
                                        printf("    [1] Expenses\n");
                                        printf("    [2] Collections\n");
                                        printf("    [3] Check Funds Log\n");
                                        printf("    [4] Override Current Total Funds\n");
                                        printf("    [5] Return to main interface\n");
                                        printf("Choose: ");
                                        scanf("%d", &choice);
                                        system("cls");
                                        switch (choice) {
                                            case 1:
                                                printf("Loading...");
                                                sleep(2);
                                                system("cls");
                                                expenses();
                                                system("cls");
                                                break;
                                            case 2:
                                                printf("Loading...");
                                                sleep(2);
                                                system("cls");
                                                collections();
                                                system("cls");
                                                break;
                                            case 3:
                                                printf("Loading...");
                                                sleep(2);
                                                system("cls");
                                                fundsLog();
                                                system("cls");
                                                break;
                                            case 4:
                                                printf("Loading...");
                                                sleep(2);
                                                system("cls");
                                                overrideFunds();
                                                system("cls");
                                                break;
                                            case 5:
                                                printf("Returning to main interface...\n");
                                                sleep(2);
                                                system("cls");
                                                break;
                                            default:
                                                printf("Invalid choice! Choose among the options.\n");
                                        }
                                    } while (choice != 5);
                                    break;
                                case 4:
                                    printf("\nLogging Out...\n");
                                    sleep(2);
                                    break;
                                default:
                                    printf("Invalid choice! Choose among the options.\n");
                            }
                        } while (choice != 4);
                        break;
                    } else {
                        attempts--;
                        printf("\nIncorrect password. You only have %d attempt/s remaining before the program returns to the main interface.\n", attempts);
                    }
                    
                    if (attempts <= 0) {
                        printf("\nAttempt limit reached. Returning to main interface...\n");
                        sleep(2);
                        attempts = 3;
                        break;
                    }
                }
                break;
            case 2: // member options
                printf("Logging in as Member...");
                sleep(2);
                system("cls");
                do {
                    printf("Welcome to ORGanized! Currently logged in as Member\n");
                    printf("    [1] Announcments\n");
                    printf("    [2] Show Members\n");
                    printf("    [3] Messages\n");
                    printf("    [4] Log Out\n");
                    printf("What do you want to do? ");
                    scanf("%d", &choice);
                    system("cls");

                    switch (choice) {
                        case 1:
                            printf("Loading...");
                            sleep(2);
                            system("cls");
                            postedAnnouncements();
                            printf("\nEnter to continue...\n");
                            getchar();
                            getchar();
                            sleep(2);
                            system("cls");
                            break;
                        case 2:
                            printf("Loading...");
                            sleep(2);
                            system("cls");
                            showMembers();
                            system("cls");
                            break;
                        case 3:
                            printf("Loading...");
                            sleep(2);
                            system("cls");
                            do {
                                printf("\nMessages\n");
                                printf("    [1] Inbox\n");
                                printf("    [2] Send message\n");
                                printf("    [3] Return to main interface \n");
                                printf("Choose: ");
                                scanf("%d", &choice);
                                system("cls");

                                switch (choice) {
                                    case 1:
                                        printf("Loading...");
                                        sleep(2);
                                        system("cls");
                                        //checkInbox();
                                        printf("\nInbox\n");
                                        printf("\nEnter to continue...\n");
                                        getchar();
                                        getchar();
                                        sleep(2);
                                        system("cls");
                                        break;
                                    case 2:
                                        printf("Loading...");
                                        sleep(2);
                                        system("cls");
                                        //sendMessage();
                                        printf("\nSend Messages\n");
                                        printf("\nEnter to continue...\n");
                                        getchar();
                                        getchar();
                                        sleep(2);
                                        system("cls");
                                        break;
                                    case 3:
                                        printf("\nReturning...\n");
                                        sleep(2);
                                        break;
                                    default:
                                        printf("\nInvalid option!\n");
                                        getchar();
                                        getchar();
                                        system("cls");
                                }
                            } while (choice != 3);
                            break;
                        case 4:
                            printf("\nLogging Out...\n");
                            sleep(2);
                            break;
                        default:
                            printf("\nInvalid option!\n");
                            getchar();
                            getchar();
                            system("cls");
                    }
                } while (choice != 4);
                break;
            case 3:
                printf("Thank you for using our program. Remember to keep it ORGanized!...\n");
                sleep(2);
                return 0;
            default:
                printf("\nInvalid option!\n");
                getchar();
                getchar();
                system("cls");
                break;
        }
    } while (choice != 3);
    
    
    return 0;
}


// Members Section
void addMember() {
    // if (member_count >= MAX_MEMBER_COUNT) {
    //     printf("Organization is currently full! Remove any inactive member if necessary.\n");
    //     return;
    // }

    // printf("Enter the name of the member to add: ");
    // getchar(); // to clear newline from input buffer
    // fgets(members[member_count], NAME_LENGTH, stdin);

    // members[member_count][strcspn(members[member_count], "\n")] = 0;
    // active[member_count] = 1;  // Set the member as active
    // member_count++;

    // printf("%s has been added to the org!\n", members[member_count - 1]);

    // char decision;
    // while (1) { 
    //     printf("\nWould you like to add another member? (y/n): ");
    //     scanf(" %c", &decision);  

    //     decision = tolower(decision);
    //     if (decision == 'y') {
    //         system("cls"); 
    //         addMember(); 
    //         break;
    //     } else if (decision == 'n') {
    //         printf("Returning...");
    //         sleep(2); 
    //         system("cls"); 
    //         break;
    //     } else {
    //         printf("Invalid input! Please enter 'y' for yes or 'n' for no ONLY.\n");
    //     }
    // }
     if (member_count >= MAX_MEMBER_COUNT) {
        printf("Organization is currently full! Remove any inactive member if necessary.\n");
        return;
    }

    struct orgMember newMember;

    // lastnaem
    printf("Enter the member's surname: ");
    getchar(); 
    fgets(newMember.surname, sizeof(newMember.surname), stdin);
    newMember.surname[strcspn(newMember.surname, "\n")] = '\0';

    // firstname
    printf("Enter the member's first name: ");
    fgets(newMember.firstname, sizeof(newMember.firstname), stdin);
    newMember.firstname[strcspn(newMember.firstname, "\n")] = '\0';

    // MI
    printf("Enter the member's middle initials (if any, or leave blank): ");
    fgets(newMember.midInitials, sizeof(newMember.midInitials), stdin);
    newMember.midInitials[strcspn(newMember.midInitials, "\n")] = '\0';

    //uearlvl
    printf("Enter the member's year level (1-6): ");
    while (scanf("%d", &newMember.year) != 1 || newMember.year < 1 || newMember.year > 6) {
        printf("Invalid input! Please enter a number between 1 and 6: ");
        while (getchar() != '\n'); // Clear invalid input
    }

    //age
    printf("Enter the member's age: ");
    while (scanf("%d", &newMember.age) != 1 || newMember.age <= 0) {
        printf("Invalid age! Please enter a positive number: ");
        while (getchar() != '\n');
    }

    newMember.active = 1;  // activememberstatus

    members[member_count++] = newMember;
    printf("%s %s has been added to the organization!\n", newMember.firstname, newMember.surname);

    // prompt if user wants to add another memeber
    char decision;
    while (1) {
        printf("\nWould you like to add another member? (y/n): ");
        scanf(" %c", &decision);

        decision = tolower(decision);
        if (decision == 'y') {
            system("cls");
            addMember(); 
            break;
        } else if (decision == 'n') {
            printf("Returning...\n");
            sleep(2);
            system("cls");
            break;
        } else {
            printf("Invalid input! Please enter 'y' for yes or 'n' for no ONLY.\n");
        }
    }
    saveMembers();
}

void showMembers() {
    printf("CURRENT ORG MEMBERS\n\n");

    // // temp array to store active members
    // char sorted_members[MAX_MEMBER_COUNT][NAME_LENGTH];
    // int sorted_count = 0;

    // for (int i = 0; i < member_count; i++) {
    //     if (active[i]) {
    //         strcpy(sorted_members[sorted_count], members[i]); // Copy active members
    //         sorted_count++;
    //     }
    // }

    // // sort the member list in alphabetical order (A-Z)
    // for (int i = 0; i < sorted_count - 1; i++) {
    //     for (int j = i + 1; j < sorted_count; j++) {
    //         if (strcmp(sorted_members[i], sorted_members[j]) > 0) {
    //             // Swap
    //             char temp[NAME_LENGTH];
    //             strcpy(temp, sorted_members[i]);
    //             strcpy(sorted_members[i], sorted_members[j]);
    //             strcpy(sorted_members[j], temp);
    //         }
    //     }
    // }

    // // print the updated member list
    // if (sorted_count > 0) {
    //     for (int i = 0; i < sorted_count; i++) {
    //         printf("%d. %s\n", i + 1, sorted_members[i]);
    //     }
    // } else {
    //     printf("No members :(.\n");
    // }

    char sorted_members[MAX_MEMBER_COUNT][NAME_LENGTH];
    int sorted_count = 0;

    for (int i = 0; i < member_count; i++) {
        if (members[i].active) {
            snprintf(sorted_members[sorted_count], NAME_LENGTH, "%s %s", members[i].firstname, members[i].surname);
            sorted_count++;
        }
    }

    for (int i = 0; i < sorted_count - 1; i++) {
        for (int j = i + 1; j < sorted_count; j++) {
            if (strcmp(sorted_members[i], sorted_members[j]) > 0) {
                char temp[NAME_LENGTH];
                strcpy(temp, sorted_members[i]);
                strcpy(sorted_members[i], sorted_members[j]);
                strcpy(sorted_members[j], temp);
            }
        }
    }

    // Print the updated member list
    if (sorted_count > 0) {
        for (int i = 0; i < sorted_count; i++) {
            printf("%d. %s\n", i + 1, sorted_members[i]);
        }
    } else {
        printf("No active members :(\n");
    }



    // Pause before returning
    printf("\nPress Enter to continue...");
    getchar(); // Clear any leftover newline
    getchar(); // Wait for Enter
    printf("Returning...");
    sleep(2); 
    system("cls"); 
    // OLD MEMBERS LIST (not sorted alphabetically, keeping incase I mess smth up)
    // printf("CURRENT ORG MEMBERS\n\n");
    // int count = 0;

    // for (int i = 0; i < member_count; i++) {
    //     if (active[i]) {
    //         printf("%d. %s\n", count + 1, members[i]);
    //         count++;
    //     }
    // }

    // if (count == 0) {
    //     printf("No members :(.\n");
    // }

    // printf("\nEnter to continue...");
    // getchar();
    // getchar();
}

void removeMember() {
    //char name[NAME_LENGTH];
    // printf("Enter the name of the member to remove: ");
    // getchar();
    // fgets(name, NAME_LENGTH, stdin);
    // name[strcspn(name, "\n")] = 0;

    // int member_check = 0;
    
    // for (int i = 0; i < member_count; i++) {
    //     if (active[i] && strcmp(members[i], name) == 0) {
    //         active[i] = 0; 
    //         printf("%s has been removed from the org!\n", name);
    //         member_check = 1;
    //         break;
    //     }
    // }

    // if (!member_check) {
    //     printf("%s is not found in the current member list.\n", name);
    // }

    // char decision;
    // while (1) { 
    //     printf("\nWould you like to remove another member? (y/n): ");
    //     scanf(" %c", &decision);  

    //     decision = tolower(decision);
    //     if (decision == 'y') {
    //         system("cls"); 
    //         removeMember(); 
    //         break;
    //     } else if (decision == 'n') {
    //         printf("Returning...");
    //         sleep(2); 
    //         system("cls"); 
    //         break;
    //     } else {
    //         printf("Invalid input! Please enter 'y' for yes or 'n' for no ONLY.\n");
    //     }
    // }
    printf("CURRENT ACTIVE MEMBERS\n\n");

    // list of active members with numbers, murag katong show list ra
    int active_count = 0;
    for (int i = 0; i < member_count; i++) {
        if (members[i].active) {
            printf("%d. %s %s\n", active_count + 1, members[i].firstname, members[i].surname);
            active_count++;
        }
    }

    if (active_count == 0) {
        printf("No active members to remove.\n");
        return;
    }

    int member_to_remove;
    printf("\nEnter the number of the member to remove: ");
    scanf("%d", &member_to_remove);

    if (member_to_remove < 1 || member_to_remove > active_count) {
        printf("Invalid number! Please enter a valid number from the list.\n");
        return;
    }

    int index = -1;
    active_count = 0;
    for (int i = 0; i < member_count; i++) {
        if (members[i].active) {
            active_count++;
            if (active_count == member_to_remove) {
                index = i;
                break;
            }
        }
    }

    if (index != -1) {
        members[index].active = 0;
        printf("%s %s has been removed from the org!\n", members[index].firstname, members[index].surname);
    }

    char decision;
    while (1) {
        printf("\nWould you like to remove another member? (y/n): ");
        scanf(" %c", &decision);

        decision = tolower(decision);
        if (decision == 'y') {
            system("cls");
            removeMember(); // Recursively call removeMember to remove another member
            break;
        } else if (decision == 'n') {
            printf("Returning...\n");
            sleep(2);
            system("cls");
            break;
        } else {
            printf("Invalid input! Please enter 'y' for yes or 'n' for no ONLY.\n");
        }
    }
    saveMembers();
}

// void saveMembers() {
//     FILE *file = fopen(MEMBERS_FILE, "w");
//     if (file == NULL) {
//         printf("Error saving members to file.\n");
//         return;
//     }

//     for (int i = 0; i < member_count; i++) {
//         if (active[i]) {
//             fprintf(file, "%s\n", members[i]);
//         }
//     }

//     fclose(file);
// }

// void loadMembers() {
//     FILE *file = fopen(MEMBERS_FILE, "r");
//     if (file == NULL) {
//         printf("No members file found.\n");
//         return;
//     }

//     while (fgets(members[member_count], NAME_LENGTH, file)) {
//         members[member_count][strcspn(members[member_count], "\n")] = 0; 
//         active[member_count] = 1;  
//         member_count++;
//     }

//     fclose(file);
// }

void saveMembers() {
    FILE *file = fopen(MEMBERS_FILE, "w");
    if (file == NULL) {
        printf("Error saving members to file.\n");
        return;
    }

    for (int i = 0; i < member_count; i++) {
        if (members[i].active) {
            // Save each field of the member to the file
            fprintf(file, "%s\n", members[i].surname);
            fprintf(file, "%s\n", members[i].firstname);
            fprintf(file, "%s\n", members[i].midInitials);
            fprintf(file, "%d\n", members[i].year);
            fprintf(file, "%d\n", members[i].age);
            fprintf(file, "%d\n", members[i].active);
        }
    }

    fclose(file);
}

void loadMembers() {
    FILE *file = fopen(MEMBERS_FILE, "r");
    if (file == NULL) {
        printf("No members file found.\n");
        return;
    }

    while (fscanf(file, "%49s %49s %4s %d %d %d\n", 
            members[member_count].surname, 
            members[member_count].firstname, 
            members[member_count].midInitials, 
            &members[member_count].year, 
            &members[member_count].age, 
            &members[member_count].active) == 6) {
        
        member_count++;
    }

    fclose(file);
}


// Funds Section
void loadFunds() {
    FILE *file = fopen(FUNDS_FILE, "r");
    if (file != NULL) {
        fscanf(file, "%d", &total_funds);
        fclose(file);
    } else {
        printf("No total funds file found, resetting funds.\n");
        total_funds = 0;
    }
}

void saveFunds() {
    FILE *file = fopen(FUNDS_FILE, "w");
    if (file != NULL) {
        fprintf(file, "%d", total_funds);
        fclose(file);
    } else {
        printf("Error saving total funds.\n");
    }
}

void fundsHistory(const char *action, int amount, const char *reason) {
    FILE *file = fopen(FUNDS_HISTORY, "a");
    if (file != NULL) {
        fprintf(file, "[%s] PHP %d - %s\n", action, amount, reason);
        fclose(file);
    } else {
        printf("Error opening funds history file for writing.\n");
    }
}

void expenses() {
    int expense;
    char reason[256];

    printf("\nEnter the amount spent: ");
    scanf("%d", &expense);

    printf("\nEnter the reason for the expense: ");
    getchar();
    fgets(reason, sizeof(reason), stdin);

    reason[strcspn(reason, "\n")] = 0; 
    total_funds -= expense;
    printf("\n%d deducted successfully for '%s'!\n", expense, reason);

    saveFunds();
    fundsHistory("Expenses", expense, reason);

    char decision;
    while (1) { 
        printf("\nWould you like to add another member? (y/n): ");
        scanf(" %c", &decision);  

        decision = tolower(decision);
        if (decision == 'y') {
            system("cls"); 
            expenses(); 
            break;
        } else if (decision == 'n') {
            printf("Returning...");
            sleep(2); 
            system("cls"); 
            break;
        } else {
            printf("Invalid input! Please enter 'y' for yes or 'n' for no ONLY.\n");
        }
    }
}

void fundsLog() {
    FILE *file = fopen(FUNDS_HISTORY, "r");
    char line[256];
    printf("\nFunds History:\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    printf("\nEnter to continue...");
    getchar();
    getchar();
    fclose(file);
}

void collections(){
    int contribution;
    char reason[256];

    printf("\nEnter the amount to be added: ");
    scanf("%d", &contribution);
    getchar(); 
    printf("\nEnter the reason for the contribution: ");
    fgets(reason, sizeof(reason), stdin);
    reason[strcspn(reason, "\n")] = 0; 

    total_funds += contribution;
    printf("\nContribution of PHP %d added successfully for '%s'!\n", contribution, reason);

    saveFunds();
    fundsHistory("Contribution", contribution, reason);

    char decision;
    while (1) { 
        printf("\nWould you like to add another member? (y/n): ");
        scanf(" %c", &decision);  

        decision = tolower(decision);
        if (decision == 'y') {
            system("cls"); 
            collections(); 
            break;
        } else if (decision == 'n') {
            printf("Returning...");
            sleep(2); 
            system("cls"); 
            break;
        } else {
            printf("Invalid input! Please enter 'y' for yes or 'n' for no ONLY.\n");
        }
    }
}

void overrideFunds() {
    int new_total_funds;

    printf("\nEnter the new total funds amount: PHP ");
    scanf("%d", &new_total_funds);

    total_funds = new_total_funds;
    printf("\nTotal funds overridden to %d PHP!\n", new_total_funds);

    saveFunds();
    fundsHistory("Override", new_total_funds, "Funds override");
}



//Announcements Section
void postAnnouncement() {
    printf("What's on your mind?\n");
    getchar();
    fgets(ListPostedAnnouncements[announcement_counter], MAX_ANNOUNCEMENT_LENGTH, stdin);
    announcement_counter++;

    printf("Announcement Posted!");

    printf("\n\nEnter to continue...");
    getchar();
    printf("Returning...");
    sleep(2);
    system("cls");
}

void createDraftAnnouncement() {
    printf("Under construction :(");

    printf("\nEnter to continue...");
    getchar();
    getchar();
}

void postedAnnouncements() {
    // printf("\nAnnouncements:\n");
    // for(int i = 0; i < announcement_counter; i++) {
    //     printf("%d. %s\n", i + 1, ListPostedAnnouncements[i]);
    // }

    FILE *announcements;
    char ch[100];

    announcements = fopen("announcements.txt", "r");
    if(announcements == NULL) {
        printf("Error in opening file.\n");
        printf("Enter to continue...");
        getchar();
        return;
    }

    printf("\nAnnouncements:\n");
    while(fgets(ch, sizeof(ch), announcements) != NULL) {
        printf("%s", ch);
    }
    
    fclose(announcements);

    printf("\nEnter to continue...");
    getchar();
    printf("Returning...");
    sleep(2);
    system("cls");
}

void listOfficers() {
    printf("CURRENT ORG OFFICERS\n\n");
    for (int i = 0; i < ROLE_COUNT; i++) {
        printf("%s: %s\n", roles[i], officer_names[i]);
    }

    printf("\n\nEnter to continue...");
    getchar();
    getchar();
    printf("Returning...");
    sleep(2);
    system("cls");
}

void replaceOfficer() {
    int choice;
    char new_name[NAME_LENGTH];

    printf("\nSelect the role to replace based on their number:\n");
    for (int i = 0; i < ROLE_COUNT; i++) {
        printf("%d. %s\n", i + 1, roles[i]);
    }
    printf("\nEnter your choice (1-%d): ", ROLE_COUNT);
    scanf("%d", &choice);

    // if statement to check if role is valid
    if (choice < 1 || choice > ROLE_COUNT) {
        printf("Invalid choice! Please select a valid/existing role.\n");
        return;
    }

    // replace name of current officer of the specific role chosen
    getchar();
    printf("Enter the new name for %s: ", roles[choice - 1]);
    fgets(new_name, NAME_LENGTH, stdin);

    new_name[strcspn(new_name, "\n")] = 0;

    strcpy(officer_names[choice - 1], new_name);
    printf("%s has been assigned to the role of %s!\n", new_name, roles[choice - 1]);

    char decision;
    while (1) { 
        printf("\nWould you like to assign another member to a role? (y/n): ");
        scanf(" %c", &decision);  

        decision = tolower(decision);
        if (decision == 'y') {
            system("cls"); 
            replaceOfficer(); 
            break;
        } else if (decision == 'n') {
            printf("Returning...");
            sleep(2); 
            system("cls"); 
            break;
        } else {
            printf("Invalid input! Please enter 'y' for yes or 'n' for no ONLY.\n");
        }
    }
}

void loadOfficers() {
    FILE *file = fopen(OFFICERS_FILE, "r");
    if (file == NULL) {
        printf("Officers file empty.\n");
        return;
    }

    for (int i = 0; i < ROLE_COUNT; i++) {
        if (fgets(officer_names[i], NAME_LENGTH, file) != NULL) {
            officer_names[i][strcspn(officer_names[i], "\n")] = 0; 
        }
    }

    fclose(file);
}

void saveOfficers() {
    FILE *file = fopen(OFFICERS_FILE, "w");
    if (file == NULL) {
        printf("Error saving officer information!\n");
        return;
    }

    for (int i = 0; i < ROLE_COUNT; i++) {
        fprintf(file, "%s\n", officer_names[i]);
    }

    fclose(file);
    printf("Officer's name has been saved!\n");
}
