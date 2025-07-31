#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#define MAX_CUSTOMERS 100

typedef struct {
    int id;
    char name[50];
    char email[50];
    char phone[20];
} Customer;

void customer_menu();
void add_customer();
void list_customers();

#endif