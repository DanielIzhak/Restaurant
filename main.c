#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <time.h>
#include<stdlib.h>
#include<string.h>
#include"Employee.h"
#include"Items.h"
#include"Log.h"
#include<conio.h>




#define MENU_LEVEL_1 "\n1: Print purchase history \n2: Print items \n3: sell items \n4: Search by one type \n5: Search by two types \n6: Search by price \n7: Search by meal \n8: Search by date \n9: Add new item\n"
#define MENU_LEVEL_2 "10: Update item \n11: Delete item\n"
#define MENU_LEVEL_3 "12: Add employee \n13: Update employee \n14: delete employee\n15: Print all employees\n"
#define EXIT_MENU "0: Exit\n press number from the menu"


Employee Get_Into_system()
{
	Employee employee = { NULL };
	printf("enter user name:  ");
	scanf("%s", &employee.Username);
	printf("enter password :  ");
	scanf("%s", &employee.Password);
	printf("enter level ");
	scanf("%d", &employee.level);
	printf("enter full name:  ");
	scanf("%s", &employee.Fullname);
	return employee;
}

Items Addnewitem(int serial)
{
	Items newitem = { ++serial,"","",0,0,0 };
	int Meal;
	printf("enter 1 if you want a meal 0 if not:");
	scanf_s("%d", &Meal);
	if (Meal == 0)
		newitem.Meal = false;
	else
		newitem.Meal = true;
	printf("enter the type of item :  ");
	scanf("%s", newitem.TypeOfItem);
	printf("enter the item's name:  ");
	scanf("%s", newitem.NameofItem);
	printf("enter price for order:  ");
	scanf("%lf", &newitem.price);
	printf("enter date in this format day/month/year:  ");
	scanf_s("%d/%d/%d", &newitem.EntranceDate.day, &newitem.EntranceDate.month, &newitem.EntranceDate.year);
	return newitem;
}

void search_with_one_type(Items** items) 
{
	char Onetypesearch[20];
	printf("Please enter your search field  ");
	scanf("%s", Onetypesearch);
	Search_By_One_Type(items, Onetypesearch);
}

void SearchByDate(Items** items) 
{
	Date  search_Date = { 0,0,0 };
	printf("enter date day/month/year:  ");
	scanf_s("%d/%d/%d", &search_Date.day, &search_Date.month, &search_Date.year);
	Search_By_Date(items, search_Date);	
}

void searchByPrice(Items** items)
{
	double price;
	printf("Please enter price  ");
	scanf("%lf", &price);
	Search_By_Price(items, price);
}

void Searchifmeal(Items* items)
{
	int meal;
	printf("please enter 0 for false & 1 for true  ");
	scanf("%d", &meal);
	Search_By_Bool(items, meal);
}

Customer* Sellitem(Items** items,Customer* customerlist)
{
	int numofproducts;
	printf("Enter the number of products you want to buy\n");
	scanf("%d", &numofproducts);
	if (numofproducts > 3 && numofproducts < 1)
	{
		printf("You cant buy more then 3 products at once\n");
		scanf("%d", &numofproducts);
	}
	Sell_item(items, numofproducts, customerlist);
	return customerlist;
}

void showMenu(char* MenuByLevel, Employee* employees, Items** items,Customer* customerlist)
{
	int NumForMenu;
	Items item;
	Employee employee;
	int serial;
	char fullname[30];
	do {
		printf(MenuByLevel);
		printf("Press number of function from our menu, 0 to quit menu\n ");
		scanf_s("%d", &NumForMenu);
		switch (NumForMenu)
		{
		case 1:
			Print_Purchase_History(customerlist);
			Write_Log("Print purchase history");
			break;
		case 2:
			Print_Menu(items, Numofitems);
			Write_Log("Print items\n");
			break;
		case 3:
			customerlist = Sellitem(items, customerlist);
			Print_Purchase_History_to_file(customerlist);
			Write_Log("Sell item\n");
			break;
		case 4:
			search_with_one_type(items);
			Write_Log("Search by one type\n");
			break;
		case 5:
			Search_By_Two_Types(items);
			Write_Log("Search by two types\n");
			break;
		case 6:
			searchByPrice(items);
			Write_Log("Search by price\n");
			break;
		case 7:
			Searchifmeal(items);
			Write_Log("Search by meal or not\n");
			break;
		case 8:
			SearchByDate(items);
			Write_Log("Search by enter date\n");
			break;
		case 9:
			item = Addnewitem(Numofitems);
			Write_Item(item);
			Free_Items(items);
			items = (Items**)malloc(sizeof(Items*));
			if (items == NULL) {
				return NULL;
			}
			items = Read_Items(items,FILE_NAME);
			Write_Log("Add new item \n");
			break;
		case 10:
			serial = 0;
			printf("enter serial to update: ");
			scanf_s("%d", &serial);
			item = Addnewitem(--serial);
			Find_Item(items, &item);
			Write_Log("Update item\n");
			break;
		case 11:
			serial = 0;
			printf("enter serial to delete: ");
			scanf_s("%d", &serial);
			Delete_Item(items, serial);
			Write_Log("Delete item\n");
			break;
		case 12:
			employee = Get_Into_system();
			Add_New_Employee(&employee);
			employees = (Employee*)malloc(sizeof(Employee*));
			if (employees == NULL) 
			{
				return NULL;
			}
			employees = Read_Employees(employees);
			Write_Log("Add employee\n");
			break;
		case 13:
			employee = Get_Into_system();
			Update_Employee(employees,employee);
			Write_Log("Update employee\n");
			break;
		case 14:
			printf("enter full name employee To delete:  ");
			scanf_s("%s", &fullname);
			Delete_Employee(employees, fullname);
			Write_Log("Delete employee\n");
			break;
		case 15:
			Print_Employees(employees);
			Write_Log("Print employees\n");
			break;
		default:
			Free_Employees(employees);
			Free_Customers(customerlist);
			Free_Items(items);
		}
	} while (NumForMenu != 0);

	
	return;
}

int main(void)
{
	printf("\033[1;32m");//green
	printf_s(" \n\n ");
	printf_s("                        System opening time:\n ");
	time_t s, val = 1;
	struct tm* current_time;

	// time in seconds
	s = time(NULL);

	// to get current time
	current_time = localtime(&s);

	// print time in minutes,
	// hours and seconds
	printf("                               %02d:%02d:%02d",
		current_time->tm_hour,
		current_time->tm_min,
		current_time->tm_sec);

	printf("\033[1;36m");//cyan
	printf_s(" \n\n\n                    %c  COPYRIGHT TO MDT COMPANY  %c \n\n\n", 2, 2);
	printf("\033[1;33m");//yellow
	printf_s("          &&&&    &&&&         &&&&&&&&     &&&&&&&&&&&&        \n");
	printf_s("        &&& &&&  &&& &&&       &&&    &&        &&&             \n");
	printf_s("       &&&  &&&  &&&  &&&      &&&    &&        &&&           \n");
	printf_s("       &&&    &&&&    &&&      &&&   &&&        &&&          \n");
	printf_s("       &&&    &&&&    &&&      &&&&&&&          &&&          \n\n\n\n\n");

	int norow, col, row, sps;
	printf_s("\033[1;37m");
	printf_s("HELLO , from 1 to 10 rate your day %c : ",2);
	scanf_s("%d", &norow);
	printf("\033[1;33m");//yellow
	for (row = 1; row <= norow; row++)
	{
		for (sps = 1; sps <= (norow - row); sps++)
			printf(" ");

		for (col = 1; col <= (2 * row) - 1; col++)
			printf("%c", 2);
		printf("\n");
	}
	printf("\n");
	printf_s("\033[1;37m");//white

	Employee* employees = (Employee*)malloc(sizeof(Employee));
	Items** items = (Items**)malloc(sizeof(Items));
	Customer* customerlist = (Customer*)malloc(sizeof(Customer));

	employees = Read_Employees(employees);
	items = Read_Items(items,"itemlist.txt");
	initializecustomer(customerlist);
	Read_Customers_From_File(customerlist);

	int Loginfailurecounter = 0, level = 0;
	char Username[20], Password[20];

	while (Loginfailurecounter < 3) 
	{
		printf("Enter your username:\n");
		scanf("%s", &Username);
		printf("Enter your passsword:\n");
		scanf("%s", &Password);

		level = Login_Level_Employee(employees, Username, Password);
		if (level == 0) 
		{
			Loginfailurecounter++;
		}
		else 
		{
			Loginfailurecounter = 0;
			break;
		}
		if (Loginfailurecounter == 3) 
		{
			printf("You have reached maximum attempts of login. please try again later\n");
			return NULL;
		}
	}
	char level2[300];
	strcpy(level2, MENU_LEVEL_1);
	strcat(level2, MENU_LEVEL_2);
	char level3[500];
	strcpy(level3, level2);
	strcat(level3, MENU_LEVEL_3);
	switch (level)
	{
	case 1:
		showMenu(MENU_LEVEL_1, employees, items,customerlist);
		break;
	case 2:
		showMenu(level2, employees, items,customerlist);
		break;
	case 3:
		showMenu(level3, employees, items,customerlist);
		break;
	default:
		return NULL;
	}

	printf("Total profit made today is %lf\n", profit);
	printf("Good Bye !!!\n");
}
