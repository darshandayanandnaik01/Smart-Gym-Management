#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store member details
struct Member {
    int id;
    char name[50];
    char gender;
    char dob[15];
    char membershipType[20];
    int attendance;
    double caloriesBurnt;
};

// Function prototypes
void registerMember(struct Member *members, int *totalMembers);
void displayMemberDetails(struct Member *members, int totalMembers);
void markAttendance(struct Member *members, int totalMembers);
void updateCaloriesBurnt(struct Member *members, int totalMembers);
int authenticateStaff();

int main() {
    struct Member members[100];  // Assuming a maximum of 100 members
    int totalMembers = 0;
    int choice;

    while (1) {
        printf("\nSmart Gym Management System\n");
        printf("1. Register Member\n");
        printf("2. Display Member Details\n");
        printf("3. Mark Attendance\n");
        printf("4. Update Calories Burnt\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerMember(members, &totalMembers);
                break;
            case 2:
                displayMemberDetails(members, totalMembers);
                break;
            case 3:
                markAttendance(members, totalMembers);
                break;
            case 4:
                updateCaloriesBurnt(members, totalMembers);
                break;
            case 5:
                printf("Exiting program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Function to register a new member
void registerMember(struct Member *members, int *totalMembers) {
    if (authenticateStaff()) {
        printf("\nEnter Member Details:\n");
        members[*totalMembers].id = *totalMembers + 1;  // Incremental member ID
        printf("Name: ");
        scanf("%s", members[*totalMembers].name);
        printf("Gender (M/F): ");
        scanf(" %c", &members[*totalMembers].gender);
        printf("Date of Birth (DD/MM/YYYY): ");
        scanf("%s", members[*totalMembers].dob);

        // Allow staff to choose membership type
        printf("Choose Membership Type:\n");
        printf("1. Gold\n");
        printf("2. Silver\n");
        int membershipChoice;
        scanf("%d", &membershipChoice);

        switch (membershipChoice) {
            case 1:
                strcpy(members[*totalMembers].membershipType, "Gold");
                break;
            case 2:
                strcpy(members[*totalMembers].membershipType, "Silver");
                break;
            default:
                printf("Invalid choice. Setting default to Silver membership.\n");
                strcpy(members[*totalMembers].membershipType, "Silver");
        }

        // Initialize attendance and calories burnt to zero
        members[*totalMembers].attendance = 0;
        members[*totalMembers].caloriesBurnt = 0.0;

        (*totalMembers)++;
        printf("Member successfully registered!\n");
    } else {
        printf("Authentication failed. Only staff members can register new members.\n");
    }
}

// Function to display member details
void displayMemberDetails(struct Member *members, int totalMembers) {
    if (authenticateStaff()) {
        printf("\nMember Details:\n");
        for (int i = 0; i < totalMembers; i++) {
            printf("ID: %d\n", members[i].id);
            printf("Name: %s\n", members[i].name);
            printf("Gender: %c\n", members[i].gender);
            printf("Date of Birth: %s\n", members[i].dob);
            printf("Membership Type: %s\n", members[i].membershipType);
            printf("Attendance: %d\n", members[i].attendance);
            printf("Calories Burnt: %.2lf\n", members[i].caloriesBurnt);
            printf("----------------------\n");
        }
    } else {
        printf("Authentication failed. Only staff members can access member details.\n");
    }
}

// Function to mark member attendance
void markAttendance(struct Member *members, int totalMembers) {
    if (authenticateStaff()) {
        int memberId;
        printf("Enter Member ID for Attendance: ");
        scanf("%d", &memberId);

        for (int i = 0; i < totalMembers; i++) {
            if (members[i].id == memberId) {
                members[i].attendance++;
                printf("Attendance marked for %s.\n", members[i].name);
                return;
            }
        }

        printf("Member not found with ID %d.\n", memberId);
    } else {
        printf("Authentication failed. Only staff members can mark attendance.\n");
    }
}

// Function to update member calories burnt
void updateCaloriesBurnt(struct Member *members, int totalMembers) {
    if (authenticateStaff()) {
        int memberId;
        double calories;
        printf("Enter Member ID for Calories Update: ");
        scanf("%d", &memberId);

        for (int i = 0; i < totalMembers; i++) {
            if (members[i].id == memberId) {
                printf("Enter Calories Burnt: ");
                scanf("%lf", &calories);
                members[i].caloriesBurnt += calories;
                printf("Calories updated for %s.\n", members[i].name);
                return;
            }
        }

        printf("Member not found with ID %d.\n", memberId);
    } else {
        printf("Authentication failed. Only staff members can update calories burnt.\n");
    }
}

// Function to authenticate staff members
int authenticateStaff() {
    int password;
    printf("Enter Staff Password: ");
    scanf("%d", &password);

    // Simple password check
    if (password == 1234) {
        return 1; // Authentication successful
    } else {
        return 0; // Authentication failed
    }
}
