#include <stdio.h>
#include <string.h>

#define MAX_MEMBER_COUNT 200
#define NAME_LENGTH 100

// Arrays to keep track of members
char members[MAX_MEMBER_COUNT][NAME_LENGTH];
int active[MAX_MEMBER_COUNT]; 
int member_count = 0;

// Adding members
void addMember() {
    if (member_count >= MAX_MEMBER_COUNT) {
        printf("Organization is currently full! Remove any inactive member if necessary.\n");
        return;
    }

    printf("Enter the name of the member: ");
    getchar();
    fgets(members[member_count], NAME_LENGTH, stdin);

    members[member_count][strcspn(members[member_count], "\n")] = 0;
    active[member_count] = 1; 
    member_count++;

    printf("%s has been added to the org!\n", members[member_count - 1]);

    char decision;
    printf("Would you like to add another member? (y/n): ");
    scanf(" %c", &decision);  
    if (decision == 'y' || decision == 'Y') {
        addMember();   
    }
}

// Show current mebers
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

// Remove members
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

// minus expenses to current total funds
void expenses() {

}

int main() {
    int choice;

    //For announcement
    int pick_announce;
    int max_announcement = 100;
    char announcement_lenght = 500;
    char announcement[announcement_lenght];
    int event_date, event_time;
    char event_name, event_venue;
    int total_funds;

    while (1) {
        printf("\nGROUP10TYPESHI - ORGANIZATION MANAGEMENT SYSTEM\n");
        printf("1. Manage Organization Members\n");
        printf("2. Post Announcements/Schedule Meetings\n");
        printf("3. Update Org Requirements\n");
        printf("4. Manage funds\n");
        printf("5. Exit\n");
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
                                break;
                            case 2:
                                showMembers();
                                break;
                            case 3:
                                removeMember();
                                break;
                            case 4:
                                printf("Returning to main interface.\n");
                                break;
                            default:
                                printf("Invalid choice! Choose among the options.\n");
                        } 
                        if (choice == 4) break;
                    }
                    break;
                case 2:
                    printf("What's on your mind?\n");
                    printf("1. Post Announcement");
                    printf("2. Schedule Event");
                    printf("3. Schedule Meeting");
                    scanf("%d", &pick_announce);

                    switch(pick_announce) {
                        case 1:
                            printf("Post an announcement.");
                            printf("What do you want to say?");
                            getchar();
                            fgets(announcement, announcement_lenght, stdin);

                            size_t len = strlen(announcement);
                            if (len > 0 && announcement[len - 1] == '\n')
                            {
                                announcement[len - 1] = '\0';
                            }

                            printf("Announcement posted:\n");
                            printf("%s\n", announcement);
                            break;
                        case 2:
                            printf("Schedule an Event.");
                            printf("Event Name: ");
                            scanf("%s", &event_name);
                            printf("Date: ");
                            scanf("%d", &event_date);
                            printf("Time: ");
                            scanf("%d", &event_time);
                            printf("Venue: ");
                            scanf("%s", &event_venue);
                            
                            break;
                        case 3:
                            break;

                        default:
                            break;
                    }
                    break;
                case 3:
                    printf("Under construction pa bai:(\n");
                    break;
                case 4:
                        printf("\nMANAGE FUNDS\n");
                        printf("1. Current Total Funds\n");
                        printf("2. Expenses\n");
                        printf("3. Revenue\n");
                        printf("4. Override Current Total Funds");
                        printf("5. Exit\n");
                        scanf("%d", &choice);
                        switch (choice) {
                            case 1:
                                printf("Total Funds: %d", total_funds);
                                break;
                            case 2:
                                showMembers();
                                break;
                            case 3:
                                removeMember();
                                break;
                            case 4:
                                printf("Returning to main interface.\n");
                                break;
                            default:
                                printf("Invalid choice! Choose among the options.\n");
                        } 
                        if (choice == 5) break;                       
                    break;
                case 5:
                    printf("")
                default:
                    printf("Invalid choice! Choose among the options.\n");
                }
        }
    return 0;
}
