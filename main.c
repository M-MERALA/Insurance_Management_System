#include <stdio.h>
#include <stdlib.h>
#include "../include/auth.h"
#include "../include/policies.h"
#include "../include/claims.h"
#include "../include/reporting.h"

int main() {
    int logged_in = 0;
    int user_role = 0; // 0=not logged, 1=customer, 2=agent, 3=admin
    
    while (1) {
        printf("\nInsurance Management System\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Policy Management\n");
        printf("4. Claims Processing\n");
        printf("5. Customer Management\n");
        printf("6. Reporting\n");
        printf("7. Exit\n");
        printf("Choice: ");
        
        int choice;
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1: register_user(); break;
            case 2: user_role = login(); logged_in = user_role > 0; break;
            case 3: if (logged_in) policy_menu(); break;
            case 4: if (logged_in) claims_menu(user_role); break;
            case 5: if (logged_in && user_role == 3) customer_menu(); break;
            case 6: if (logged_in && user_role == 3) reporting_menu(); break;
            case 7: exit(0);
            default: printf("Invalid choice\n");
        }
    }
    return 0;
}