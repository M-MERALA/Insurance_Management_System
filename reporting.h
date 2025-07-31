#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/customers.h"

Customer customers[MAX_CUSTOMERS];
int customer_count = 0;

void load_customers() {
    FILE *file = fopen("../data/customers.csv", "r");
    if (!file) return;
    
    while (fscanf(file, "%d,%49[^,],%49[^,],%19[^\n]\n", 
           &customers[customer_count].id,
           customers[customer_count].name,
           customers[customer_count].email,
           customers[customer_count].phone) == 4) {
        customer_count++;
    }
    fclose(file);
}

void save_customers() {
    FILE *file = fopen("../data/customers.csv", "w");
    for (int i = 0; i < customer_count; i++) {
        fprintf(file, "%d,%s,%s,%s\n", 
                customers[i].id,
                customers[i].name,
                customers[i].email,
                customers[i].phone);
    }
    fclose(file);
}

void add_customer() {
    if (customer_count >= MAX_CUSTOMERS) {
        printf("Max customers reached\n");
        return;
    }
    
    customers[customer_count].id = customer_count + 1;
    
    printf("Name: ");
    fgets(customers[customer_count].name, 50, stdin);
    customers[customer_count].name[strcspn(customers[customer_count].name, "\n")] = 0;
    
    printf("Email: ");
    fgets(customers[customer_count].email, 50, stdin);
    customers[customer_count].email[strcspn(customers[customer_count].email, "\n")] = 0;
    
    printf("Phone: ");
    fgets(customers[customer_count].phone, 20, stdin);
    customers[customer_count].phone[strcspn(customers[customer_count].phone, "\n")] = 0;
    
    customer_count++;
    save_customers();
    printf("Customer added successfully\n");
}

void list_customers() {
    printf("\nID\tName\tEmail\tPhone\n");
    for (int i = 0; i < customer_count; i++) {
        printf("%d\t%s\t%s\t%s\n",
               customers[i].id,
               customers[i].name,
               customers[i].email,
               customers[i].phone);
    }
}

void customer_menu() {
    int choice;
    do {
        printf("\nCustomer Management\n");
        printf("1. Add Customer\n");
        printf("2. List Customers\n");
        printf("3. Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1: add_customer(); break;
            case 2: list_customers(); break;
            case 3: return;
            default: printf("Invalid choice\n");
        }
    } while (1);
}