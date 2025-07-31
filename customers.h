#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/claims.h"

Claim claims[MAX_CLAIMS];
int claim_count = 0;

void load_claims() {
    FILE *file = fopen("../data/claims.csv", "r");
    if (!file) return;
    
    int status;
    while (fscanf(file, "%d,%d,%19[^,],%199[^,],%d,%f\n", 
           &claims[claim_count].id,
           &claims[claim_count].policy_id,
           claims[claim_count].date,
           claims[claim_count].description,
           &status,
           &claims[claim_count].amount) == 6) {
        claims[claim_count].status = (ClaimStatus)status;
        claim_count++;
    }
    fclose(file);
}

void save_claims() {
    FILE *file = fopen("../data/claims.csv", "w");
    for (int i = 0; i < claim_count; i++) {
        fprintf(file, "%d,%d,%s,%s,%d,%.2f\n", 
                claims[i].id,
                claims[i].policy_id,
                claims[i].date,
                claims[i].description,
                claims[i].status,
                claims[i].amount);
    }
    fclose(file);
}

void create_claim() {
    if (claim_count >= MAX_CLAIMS) {
        printf("Max claims reached\n");
        return;
    }
    
    claims[claim_count].id = claim_count + 1;
    
    printf("Policy ID: ");
    scanf("%d", &claims[claim_count].policy_id);
    getchar();
    
    printf("Date (YYYY-MM-DD): ");
    fgets(claims[claim_count].date, 20, stdin);
    claims[claim_count].date[strcspn(claims[claim_count].date, "\n")] = 0;
    
    printf("Description: ");
    fgets(claims[claim_count].description, 200, stdin);
    claims[claim_count].description[strcspn(claims[claim_count].description, "\n")] = 0;
    
    printf("Amount: ");
    scanf("%f", &claims[claim_count].amount);
    
    claims[claim_count].status = INITIATED;
    
    claim_count++;
    save_claims();
    printf("Claim created successfully\n");
}

void review_claim() {
    int id, new_status;
    printf("Enter claim ID to review: ");
    scanf("%d", &id);
    
    for (int i = 0; i < claim_count; i++) {
        if (claims[i].id == id) {
            printf("Current status: %d\n", claims[i].status);
            printf("New status (1=Under Review, 2=Approved, 3=Rejected): ");
            scanf("%d", &new_status);
            
            if (new_status >= 1 && new_status <= 3) {
                claims[i].status = (ClaimStatus)new_status;
                save_claims();
                printf("Claim status updated\n");
            } else {
                printf("Invalid status\n");
            }
            return;
        }
    }
    printf("Claim not found\n");
}

void list_claims() {
    printf("\nID\tPolicy\tDate\t\tStatus\tAmount\tDescription\n");
    for (int i = 0; i < claim_count; i++) {
        printf("%d\t%d\t%s\t%d\t%.2f\t%s\n",
               claims[i].id,
               claims[i].policy_id,
               claims[i].date,
               claims[i].status,
               claims[i].amount,
               claims[i].description);
    }
}

void claims_menu(int user_role) {
    int choice;
    do {
        printf("\nClaims Management\n");
        printf("1. Create Claim\n");
        if (user_role >= 2) printf("2. Review Claim\n");
        printf("3. List Claims\n");
        printf("4. Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1: create_claim(); break;
            case 2: if (user_role >= 2) review_claim(); break;
            case 3: list_claims(); break;
            case 4: return;
            default: printf("Invalid choice\n");
        }
    } while (1);
}