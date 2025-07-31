#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/auth.h"

User users[MAX_USERS];
int user_count = 0;

void load_users() {
	FILE *file = fopen("../data/youdone.csv", "r");
	if (!file) return;

	while (fscanf(file, "%49[^,],%49[^,],%d\n",
	              users[user_count].username,
	              users[user_count].password,
	              &users[user_count].role) == 3) {
		user_count++;
	}
	fclose(file);
}

void save_users() {
	FILE *file = fopen("../data/youdone.csv", "w");
	for (int i = 0; i < user_count; i++) {
		fprintf(file, "%s,%s,%d\n",
		        users[i].username,
		        users[i].password,
		        users[i].role);
	}
	fclose(file);
}

int login() {
	char username[USERNAME_LEN];
	char password[PASSWORD_LEN];

	printf("Username: ");
	fgets(username, USERNAME_LEN, stdin);
	username[strcspn(username, "\n")] = 0;

	printf("Password: ");
	fgets(password, PASSWORD_LEN, stdin);
	password[strcspn(password, "\n")] = 0;

	for (int i = 0; i < user_count; i++) {
		if (strcmp(username, users[i].username) == 0 &&
		        strcmp(password, users[i].password) == 0) {
			return users[i].role;
		}
	}
	printf("Login failed\n");
	return 0;
}

void register_user() {
	if (user_count >= MAX_USERS) {
		printf("Max users reached\n");
		return;
	}

	printf("Enter username: ");
	fgets(users[user_count].username, USERNAME_LEN, stdin);
	users[user_count].username[strcspn(users[user_count].username, "\n")] = 0;

	printf("Enter password: ");
	fgets(users[user_count].password, PASSWORD_LEN, stdin);
	users[user_count].password[strcspn(users[user_count].password, "\n")] = 0;

	printf("Role (1=customer, 2=agent, 3=admin): ");
	scanf("%d", &users[user_count].role);
	getchar();

	if (users[user_count].role == 3) {
		int code;
		printf("Enter admin code: ");
		scanf("%d", &code);
		if (code != 1234) {
			printf("Invalid admin code\n");
			return;
		}
	}

	user_count++;
	save_users();
	printf("Registration successful\n");
}