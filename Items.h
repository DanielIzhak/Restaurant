#ifndef _ITEM_
#define _ITEM_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FILE_NAME "itemlist.txt"
#define CUSTOMER_FILE_NAME "customer.txt"

typedef struct
{
	int year;
	int month;
	int day;
}Date;

typedef struct item
{
	int SerialNum;
	char NameofItem[50];
	char TypeOfItem[50];
	double price;
	bool Meal;
	Date EntranceDate;
}Items;

typedef struct customer
{
	char NameofCustomer[20];
	struct customer* next;
	char solditems[1000];
}Customer;

int Numofitems;
double profit;
int NumofCustomers;

Items** Read_Items(Items** items,char *);
void Add_New_Item(Items item);
void Write_Item(Items items);
void Find_Item(Items** items, Items* item);
void Delete_Item(Items** items, int ID);
void Print_Menu(Items** items); 
void Free_Items(Items** items);
void Search_By_Two_Types(Items** items);
void Search_By_One_Type(Items** items, char* Searchfield);
void Search_By_Price(Items* items, double price);
void Search_By_Date(Items* items, Date Date);
int compare_dates(Date date1, Date date2);
void Search_By_Bool(Items* items, int Meal);

Customer* Sell_item(Items* items, int numofproducts, Customer* customerlist);
void Add_Last_Purchase(Customer* customerlist, Customer* newcustomer);
void Print_Purchase_History_to_file(Customer* customerlist);
void Read_Customers_From_File(Customer* customerlist);
void Print_Purchase_History(Customer* customerlist);
void initializecustomer(Customer* customer);
void Free_Customers(Customer* customerlist);

#endif
