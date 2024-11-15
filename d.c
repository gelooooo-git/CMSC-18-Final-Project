#include <stdio.h>
#include <string.h>

#define MAX_MEMBER_COUNT 200
#define NAME_LENGTH 100
#define MEMBERS_FILE "members_list.txt"
#define FUNDS_FILE "total_funds.txt"
#define FUNDS_HISTORY "funds_history.txt"

// Arrays
char members[MAX_MEMBER_COUNT][NAME_LENGTH];
int active[MAX_MEMBER_COUNT]; 
int member_count = 0;
int total_funds = 0;

// Members Section
void addMember() {
    if (member_count >= MAX_MEMBER_COUNT) {
        printf("Organization is currently full! Remove any inactive member if necessary.\n");
        return;
    }

    printf("Enter the name of the member: ");
    getchar(); // to clear newline from input buffer
    fgets(members[member_count], NAME_LENGTH, stdin);

    members[member_count][strcspn(members[member_count], "\n")] = 0;
    active[member_count] = 1;  // Set the member as active
    member_count++;

    printf("%s has been added to the org!\n", members[member_count - 1]);

    char decision;
    printf("Would you like to add another member? (y/n): ");
    scanf(" %c", &decision);  
    if (decision == 'y' || decision == 'Y') {
        addMember();   
    }
}

void showMembers() {
    printf("\nList of Current Org Members as of 2024:\n");
    int count = 0;

    for (int i = 0; i < member_count; i++) {
        if (active[i]) {
            printf("%d. %s\n", count + 1, members[i]);
            count++;
        }
    }

    if (count == 0) {
        printf("No members :(.\n");
    }
}

void removeMember() {
    char name[NAME_LENGTH];
    printf("Enter the name of the member to remove: ");
    getchar();
    fgets(name, NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0;

    int member_check = 0;
    
    for (int i = 0; i < member_count; i++) {
        if (active[i] && strcmp(members[i], name) == 0) {
            active[i] = 0; 
            printf("%s has been removed from the org!\n", name);
            member_check = 1;
            break;
        }
    }

    if (!member_check) {
        printf("%s is not found in the current member list.\n", name);
    }

    char decision;
    printf("Would you like to remove another member? (y/n): ");
    scanf(" %c", &decision); 
    if (decision == 'y' || decision == 'Y') {
        removeMember(); 
    }
}

void saveMembers() {
    FILE *file = fopen(MEMBERS_FILE, "w");
    if (file == NULL) {
        printf("Error saving members to file.\n");
        return;
    }

    for (int i = 0; i < member_count; i++) {
        if (active[i]) {
            fprintf(file, "%s\n", members[i]);
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

    while (fgets(members[member_count], NAME_LENGTH, file)) {
        members[member_count][strcspn(members[member_count], "\n")] = 0; 
        active[member_count] = 1;  
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
        printf("No total funds file found, resetting funsd.\n");
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

    printf("Enter the amount spent: ");
    scanf("%d", &expense);

    printf("Enter the reason for the expense: ");
    getchar();
    fgets(reason, sizeof(reason), stdin);

    reason[strcspn(reason, "\n")] = 0; 
    total_funds -= expense;
    printf("%d deducted successfully for '%s'!\n", expense, reason);

    saveFunds();
    fundsHistory("Expenses", expense, reason);

    char decision;
    printf("Would you like to audit more expenses? (y/n): ");
    scanf(" %c", &decision);  
    if (decision == 'y' || decision == 'Y') {
        expenses();   
    }
}

void fundsLog() {
    FILE *file = fopen(FUNDS_HISTORY, "r");
    char line[256];
    printf("\nFunds History:\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

void collections(){
    int contribution;
    char reason[256];

    printf("Enter the amount to be added: ");
    scanf("%d", &contribution);
    getchar(); 
    printf("Enter the reason for the contribution: ");
    fgets(reason, sizeof(reason), stdin);
    reason[strcspn(reason, "\n")] = 0; 

    total_funds += contribution;
    printf("Contribution of PHP %d added successfully for '%s'!\n", contribution, reason);

    saveFunds();
    fundsHistory("Contribution", contribution, reason);

    char decision;
    printf("Would you like to audit more collections? (y/n): ");
    scanf(" %c", &decision);  
    if (decision == 'y' || decision == 'Y') {
        collections();   
    }    
}

void overrideFunds() {
    int new_total_funds;

    printf("Enter the new total funds amount: PHP ");
    scanf("%d", &new_total_funds);

    total_funds = new_total_funds;
    printf("Total funds overridden to %d PHP!\n", new_total_funds);

    saveFunds();
    fundsHistory("Override", new_total_funds, "Funds override");
}

int main() {
    int choice;
    
    loadMembers();
    loadFunds();

    start:
    while (1) {
        printf("\nGROUP10TYPESHI - ORGANIZATION MANAGEMENT SYSTEM\n");
        printf("1. Manage Organization Members\n");
        printf("2. Post Announcements/Schedule Meetings\n");
        printf("3. Manage Funds\n");
        printf("4. Exit\n");
        printf("What do you want to do? ");
        scanf("%d", &choice);

        switch (choice) {

            case 1: 
                while (1) {
                    printf("\nMANAGE ORGANIZATION MEMBERS\n");
                    printf("1. Add Member\n");
                    printf("2. Show Members\n");
                    printf("3. Remove Member\n");
                    printf("4. Exit\n");
                    printf("What do you want to do? ");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            addMember();
                            saveMembers();
                            break;
                        case 2:
                            showMembers();
                            break;
                        case 3:
                            removeMember();
                            saveMembers();
                            break;
                        case 4:
                            printf("Returning to main interface.\n");
                            goto start;  // Break out of the main loop and return to the main menu
                        default:
                            printf("Invalid choice! Choose among the options.\n");
                    }
                }
                break; 
            case 2:
                printf("Under construction pa bai :(\n");
                break;
            case 3:
                while (1){
                    printf("\nMANAGE FUNDS\n");
                    printf("Current Total Funds: %d PHP\n", total_funds);
                    printf("1. Expenses\n");
                    printf("2. Collections\n");
                    printf("3. Check Funds Log\n");
                    printf("4. Override Current Total Funds\n");
                    printf("5. Exit\n");
                    printf("What do you want to do? ");
                    scanf("%d", &choice);
                    switch (choice) {
                        case 1:
                            expenses();
                            break;
                        case 2:
                            collections();
                            break;
                        case 3:
                            fundsLog();
                            break;
                        case 4:
                            overrideFunds();
                            break;
                        case 5:
                            printf("Returning to main interface.\n");
                            goto start;
                        default:
                            printf("Invalid choice! Choose among the options.\n");
                    }
                }
                break;
            case 4:
                printf("\nClosing Program. Thank you!\n");
                return 0;
            default:
                printf("Invalid choice! Choose among the options.\n");
        }
    }
    return 0;
}
