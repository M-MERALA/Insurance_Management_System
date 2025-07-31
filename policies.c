#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/policies.h"

Policy policies[MAX_POLICIES];
int policy_count = 0;

void load_policies() {
    FILE *file = fopen("../data/policies.csv", "r");
    if (!file) return;
    
    while (fscanf(file, "%d,%49[^,],%19[^,],%19[^,],%f,%d\n", 
           &policies[policy_count].id,
           policies[policy_count].type,
           policies[policy_count].start_date,
           policies[policy_count].end_date,
           &policies[policy_count].premium,
           &policies[policy_count].customer_id) == 6) {
        policy_count++;
    }
    fclose(file);
}

void save_policies() {
    FILE *file = fopen("../data/policies.csv", "w");
    for (int i = 0; i < policy_count; i++) {
        fprintf(file, "%d,%s,%s,%s,%.2f,%d\n", 
                policies[i].id,
                policies[i].type,
                policies[i].start_date,
                policies[i].end_date,
                policies[i].premium,
                policies[i].customer_id);
    }
    fclose(file);
}

void create_policy() {
    if (policy_count >= MAX_POLICIES) {
        printf("Max policies reached\n");
        return;
    }
    
    policies[policy_count].id = policy_count + 1;
    
    printf("Policy type: ");
    fgets(policies[policy_count].type, 50, stdin);
    policies[policy_count].type[strcspn(policies[policy_count].type, "\n")] = 0;
    
    printf("Start date (YYYY-MM-DD): ");
    fgets(policies[policy_count].start_date, 20, stdin);
    policies[policy_count].start_date[strcspn(policies[policy_count].start_date, "\n")] = 0;
    
    printf("End date (YYYY-MM-DD): ");
    fgets(policies[policy_count].end_date, 20, stdin);
    policies[policy_count].end_date[strcspn(policies[policy_count].end_date, "\n")] = 0;
    
    printf("Monthly premium: ");
    scanf("%f", &policies[policy_count].premium);
    
    printf("Customer ID: ");
    scanf("%d", &policies[policy_count].customer_id);
    
    policy_count++;
    save_policies();
    printf("Policy created successfully\n");
}

void list_policies() {
    printf("\nID\tType\tStart Date\tEnd Date\tPremium\tCustomer\n");
    for (int i = 0; i < policy_count; i++) {
        printf("%d\t%s\t%s\t%s\t%.2f\t%d\n",
               policies[i].id,
               policies[i].type,
               policies[i].start_date,
               policies[i].end_date,
               policies[i].premium,
               policies[i].customer_id);
    }
}

void policy_menu() {
    int choice;
    do {
        printf("\nPolicy Management\n");
        printf("1. Create Policy\n");
        printf("2. List Policies\n");
        printf("3. Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1: create_policy(); break;
            case 2: list_policies(); break;
            case 3: return;
            default: printf("Invalid choice\n");
        }
    } while (1);
}