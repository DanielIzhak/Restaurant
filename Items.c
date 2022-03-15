#define _CRT_SECURE_NO_WARNINGS
#include "Items.h"

Items** Read_Items(Items** items)
{
	Numofitems = 0;
	FILE* file;
	file = fopen(FILE_NAME, "rt");
	if (file == NULL)
	{
		printf("There are no items in file\n");
		return NULL;
	}
	int Meal, serial;
	char tav;
	do
	{
		items[Numofitems] = (Items*)malloc(sizeof(Items));
		fscanf(file, "%d %s %s%lf %d %d/%d/%d", &items[Numofitems]->SerialNum, items[Numofitems]->NameofItem, items[Numofitems]->TypeOfItem, &items[Numofitems]->price, &Meal, &items[Numofitems]->EntranceDate.day, &items[Numofitems]->EntranceDate.month, &items[Numofitems]->EntranceDate.year);
		if (Meal == 0)
			items[Numofitems]->Meal = false;
		else
			items[Numofitems]->Meal = true;
		items = (Items*)realloc(items, sizeof(Items) * (Numofitems + 5));
		Numofitems++;
		tav = fgetc(file);
	} while ((tav = fgetc(file)) != EOF);
	fclose(file);
	return items;
}

void Add_New_Item(Items item)
{
	FILE* file = fopen(FILE_NAME, "a");
	if (file == NULL)
	{
		printf("Cant open file\n");
		return;
	}
	Write_Item(item);
	fclose(file);
	return;
}

void Write_Item(Items item)
{
	FILE* file = fopen(FILE_NAME, "a");
	fprintf(file, "\n");
	fprintf(file, "%d\n", item.SerialNum);
	fprintf(file, "%s\n", item.NameofItem);
	fprintf(file, "%s\n", item.TypeOfItem);
	fprintf(file, "%lf\n", item.price);
	fprintf(file, "%d\n", item.Meal);
	fprintf(file, "%d/%d/%d\n", item.EntranceDate.day, item.EntranceDate.month, item.EntranceDate.year);
	fclose(file);
}

void Find_Item(Items** items, Items* item)
{
	int flag = 0;
	int i = 0;
	for(i=0;i<Numofitems;i++)
	{
		if (items[i]->SerialNum == item->SerialNum)
		{
			items[i]->SerialNum = item->SerialNum;
			items[i]->NameofItem == item->NameofItem;
			items[i]->TypeOfItem == item->TypeOfItem;
			items[i]->price = item->price;
			items[i]->Meal == item->Meal;
			items[i]->EntranceDate = item->EntranceDate;
			flag++;
		}
	}
	if (flag)
	{
		FILE* file = fopen(FILE_NAME, "w");
		if (file == NULL)
		{
			printf("Cant find file\n");
			return NULL;
		}
		for (i = 0; i < Numofitems; i++)
		{
			Write_Item(*items[i]);
		}
		fclose(file);
		return;
	}
	else
	{
		printf("Item serialnum isn't valid to update");
		return;
	}	
}

void Delete_Item(Items** items, int Serialnum)
{
	int indexToDelete = -1, i;
	for (i = 0; i < Numofitems; i++)
	{
		if (items[i]->SerialNum == Serialnum)
		{
			indexToDelete = i;
			break;
		}	
	}
	if (indexToDelete == -1)
	{
		printf("Didn't find item to delete, serial doesn't match");
		return ;
	}
	for (i = indexToDelete; i < Numofitems - 1; i++)
	{
		items[i] = items[i + 1];
		items[i]->SerialNum--;
	}
	Numofitems -= 1;
	FILE* file = fopen(FILE_NAME, "w");
	if (file == NULL)
	{
		printf("Cant open file\n");
		return;
	}
	for (int i = 0; i < Numofitems; i++) 
		Write_Item(*items[i]);
	fclose(file);
}

void Print_Menu(Items** items,int number)
{
	for (int i = 0; i < number; i++) 
	{
		printf("Serialnum : %d\n", items[i]->SerialNum);
		printf("Product name: %s\n", items[i]->NameofItem);
		printf("Product type: %s\n", items[i]->TypeOfItem);
		printf("Product Price : %lf\n", items[i]->price);
		printf("Product is meal : %s\n", items[i]->Meal ? "true" : "false");
		printf("Product Entrance date: %d/%d/%d\n", items[i]->EntranceDate.day, items[i]->EntranceDate.month, items[i]->EntranceDate.year);
		printf("\n");
	}
}

void Free_Items(Items** items)
{
	for (int i = 0; i < Numofitems; i++) 
		free(items[i]);
	free(items);
}

void Search_By_Two_Types(Items** items)
{
	char Searchbytype[20];
	char Searchbyname[20];
	printf("please enter the type of the search: ");
	scanf("%s", Searchbytype);
	printf("please enter the name of the item to search: ");
	scanf("%s", Searchbyname);
	Items** Founditems = (Items*)malloc(sizeof(Items*));
	int index = 0;
	if (items == NULL) 
	{
		printf("Items list is empty");
		return;
	}
	for (int i = 0; i < Numofitems; i++)
	{
		if (strcmp(items[i]->TypeOfItem, Searchbytype) == 0 && strcmp(items[i]->NameofItem, Searchbyname) == 0) 
		{
			Founditems[index] = (Items*)malloc(sizeof(Items*));
			Founditems[index] = items[i];
			index++;
		}
	}
	Print_Menu(Founditems, index++);
}

void Search_By_One_Type(Items** items, char* Searchfield)
{
	Items** Founditems = (Items*)malloc(sizeof(Items*));
	int index = 0;
	if (items == NULL)
	{
		printf("Items list is empty");
		return;
	}
	for (int i = 0; i < Numofitems; i++)
	{
		if (strcmp(items[i]->TypeOfItem, Searchfield) == 0 || strcmp(items[i]->NameofItem, Searchfield) == 0 )
		{
			Founditems[index] = (Items*)malloc(sizeof(Items*));
			Founditems[index] = items[i];
			index++;
		}
	}
	Print_Menu(Founditems, index++);
}

void Search_By_Price(Items** items, double price)
{
	Items** Founditems = (Items*)malloc(sizeof(Items*));
	int index = 0;
	if (items == NULL)
	{
		printf("Items list is empty");
		return;
	}
	for (int i = 0; i < Numofitems; i++)
	{
		if (price - (items[i]->price) >= 0)
		{
			Founditems[index] = (Items*)malloc(sizeof(Items*));
			Founditems[index] = items[i];
			index++;
		}
	}
	Print_Menu(Founditems, index++);
}

void Search_By_Date(Items** items, Date Date)
{
	Items** Founditems = (Items*)malloc(sizeof(Items*));
	int index = 0;
	if (items == NULL)
	{
		printf("Items list is empty");
		return;
	}
	for (int i = 0; i < Numofitems; i++)
	{
		if (compare_dates(items[i]->EntranceDate,Date) != -1)
		{
			Founditems[index] = (Items*)malloc(sizeof(Items*));
			Founditems[index] = items[i];
			index++;
		}
	}
	Print_Menu(Founditems, index++);
}

int compare_dates(Date date1, Date date2)
{
	if (date1.year < date2.year)
		return -1;

	else if (date1.year > date2.year)
		return 1;

	if (date1.year == date2.year)
	{
		if (date1.month < date2.month)
			return -1;
		else if (date1.month > date2.month)
			return 1;
		else if (date1.day < date2.day)
			return -1;
		else if (date1.day > date2.day)
			return 1;
		else
			return 0;
	}
}

void Search_By_Bool(Items** items, int Meal)
{
	Items** Founditems = (Items*)malloc(sizeof(Items*));
	int index = 0;
	if (items == NULL)
	{
		printf("Items list is empty");
		return;
	}
	bool isMeal;
	if (Meal)
		isMeal = true;
	else
		isMeal = false;
	for (int i = 0; i < Numofitems; i++)
	{
		if (Meal == items[i]->Meal)
		{
			Founditems[index] = (Items*)malloc(sizeof(Items*));
			Founditems[index] = items[i];
			index++;
		}
	}
	Print_Menu(Founditems, index++);
}

Customer* Sell_item(Items** items, int numofproducts, Customer* customerlist)
{
	NumofCustomers++;
	Customer* customer = (Customer*)malloc(sizeof(Customer));
	initializecustomer(customer);
	int serial, i;
	printf("Please enter your name:  ");
	scanf("%s", &customer->NameofCustomer);
	for (i = 0; i < numofproducts; i++)
	{
		printf("please enter the serialnum you want to buy  ");
		scanf("%d", &serial);
		if (serial > Numofitems || serial < 0)
		{
			printf("invalid serial, please try enter another serialnum  ");
			scanf("%d", &serial);
		}
		strcat(customer->solditems, items[serial-1]->NameofItem);
		strcat(customer->solditems, ".");
		profit += items[serial-1]->price;
	}
	Add_Last_Purchase(customerlist, customer);
	return customerlist;
}

void Add_Last_Purchase(Customer* customerlist, Customer* newcustomer)
{
	if (NumofCustomers == 1)
	{
		*customerlist = *newcustomer;
		return;
	}
	Customer* temp = customerlist;
	while (temp != NULL)
	{
		if (strcmp(temp->NameofCustomer, newcustomer->NameofCustomer) == 0)
		{
			strcat(temp->solditems,newcustomer->solditems);
			return;
		}
		temp = temp->next;
	}
	temp = customerlist;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = newcustomer;
	return;
}

void Print_Purchase_History_to_file(Customer* customerlist)
{
	if (NumofCustomers == 0)
	{
		printf("There are no customers\n");
		return;
	}
	FILE* file = fopen(CUSTOMER_FILE_NAME, "wt");
	while (customerlist != NULL)
	{
		fprintf(file, "%s\n%s\n", &customerlist->NameofCustomer, &customerlist->solditems);
		customerlist = customerlist->next;
	}
	fclose(file);
	return;
}

void Read_Customers_From_File(Customer* customerlist) 
{
	FILE* file = fopen(CUSTOMER_FILE_NAME, "r");
	if (file == NULL)
	{
		printf("File cant be opened\n");
		return;
	}
	Customer* newcustomer = (Customer*)malloc(sizeof(Customer));
	initializecustomer(newcustomer);
	while (!feof(file))
	{
		fscanf(file, "%s\n%s\n", newcustomer->NameofCustomer, newcustomer->solditems);
		NumofCustomers++;
		Add_Last_Purchase(customerlist, newcustomer);
	} 
	fclose(file);
	return;
}

void Print_Purchase_History(Customer* customerlist)
{
	if (NumofCustomers == 0)
	{
		printf("There are no customers at the moment\n");
		return;
	}
	FILE* file = fopen(CUSTOMER_FILE_NAME, "r");
	while (customerlist != NULL)
	{
		printf("%s\n%s\n", &customerlist->NameofCustomer, &customerlist->solditems);
		customerlist = customerlist->next;
	}
	fclose(file);
	return;
}

void initializecustomer(Customer* customer)
{
	customer->next = NULL;
	strcpy(customer->solditems, "Items-bought-on-visit:");
	return;
}
void Free_Customers(Customer* customerlist)
{
	Customer* temp;
	while (customerlist != NULL)
	{
		temp = customerlist;
		customerlist = customerlist->next;
		free(temp);
	}
}
