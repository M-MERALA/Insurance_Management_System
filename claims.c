#ifndef CLAIMS_H
#define CLAIMS_H

#define MAX_CLAIMS 100

typedef enum {
    INITIATED,
    UNDER_REVIEW,
    APPROVED,
    REJECTED
} ClaimStatus;

typedef struct {
    int id;
    int policy_id;
    char date[20];
    char description[200];
    ClaimStatus status;
    float amount;
} Claim;

void claims_menu(int user_role);
void create_claim();
void review_claim();
void list_claims();

#endif