#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Login.h"

void User_Registeration()
{
	User MTD;
	FILE* Log = fopen("Login.txt", "w");
	printf("Enter first name:");
	scanf("%s", MTD.FirstName);
	printf("Enter last number:");
	scanf("%s", MTD.LastName);
	printf("Enter Username:");
	scanf("%s", MTD.Username);
	printf("Enter password:");
	//scanf("%d", MTD, MTD.Password);
	fwrite(&MTD, 1, sizeof(MTD), Log);
	fclose(Log);

	printf("\n press any key to continue");
	getch();
	system("cls");
	User_Login();
}

void User_Login()
{
	char username[20], password[20];
	User MTD;
	FILE* Log;
	Log = fopen("Login.txt", "r");
	printf("UserID:");
	scanf("%s", &username);
	printf("password:");
	scanf("%s", &password);

	while (fread(&MTD, 1, sizeof(MTD), Log))
	{
		if ((strcmp(username, MTD.Username) == 0) && strcmp(password, MTD.Password == 0))
		{
			printf("Login Successfully\n");
		}
		else {
			printf("Incorrect details, Please try again\n");
		}
	}
	fclose(Log);
}




