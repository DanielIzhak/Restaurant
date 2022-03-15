typedef struct user
{
	char FirstName[20];
	char LastName[20];
	char Username[20];
	char Password[20];
	int level;
}User;

void User_Registeration();
void User_Login();
