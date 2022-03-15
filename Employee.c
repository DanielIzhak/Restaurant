#define _CRT_SECURE_NO_WARNINGS
#include "Employee.h"

Employee* Read_Employees(Employee* employees)
{
	FILE* file = fopen(FILE_NAME, "r");
	if (file == NULL)
	{
		printf("The employee doesn't exist, creating a new employee\n");
		Create_Admin_User();
		file = fopen(FILE_NAME, "rt");
		fscanf(file, "%s\n%s\n%d\n%s\n", employees->Username, employees->Password, &(employees->level), employees->Fullname);
		fclose(file);
		employees->next = NULL;
		return;
	}
	Employee* temp = (Employee*)malloc(sizeof(Employee));
	char tav[20];
	while (!feof(file))
	{
		fscanf(file, "%s\n%s\n%d\n%s\n", temp->Username, temp->Password, &(temp->level), temp->Fullname);
		temp->next = NULL;
		employees = Add_Employee(employees, temp);
	} 
	fclose(file);
	return employees;
}

Employee* Add_Employee(Employee* employees,Employee* newemployee)
{
	if (strcmp(newemployee->Fullname, "SystemManager") == 0)
	{
		*employees = *newemployee;
		return employees;
	}
	else
	{
		Employee* temp = employees;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newemployee;
		return employees;
	}
}

void Create_Admin_User()
{
	FILE* file = fopen(FILE_NAME, "wt");
	char* systemManager = "SystemManager";
	fprintf(file, "%s\n%s\n%d\n%s\n", "admin", "admin", 3, systemManager);
	fclose(file);
}

void Add_New_Employee(Employee* employee)
{
	FILE* file = fopen(FILE_NAME, "a");
	if (file == NULL)
	{
		printf("Cant open file\n");
		return NULL;
	}
	Write_Employee(employee,file);
	fclose(file);
}

void Write_Employee(Employee* employee,FILE* file)
{
	fprintf(file, "%s\n", employee->Username);
	fprintf(file, "%s\n", employee->Password);
	fprintf(file, "%d\n", employee->level);
	fprintf(file, "%s\n", employee->Fullname);
}

void Update_Employee(Employee* employees, Employee *employee) 
{
	int found = 0;
	Employee* temp = employees;
	Employee* prev = temp;
	while(temp != NULL)
	{
		if (strcmp(temp->Fullname, employee->Fullname) == 0) 
		{
			employee->next = temp->next;
			prev->next = employee;
			free(temp);
			found++;
			break;
		}
		prev = temp;
		temp = temp->next;
	}
	if (found)
	{
		printf("The employee has been updated successfully!");
		Update_Employees_File(employees);
	}
	else
		printf("Invalid employee to update");
	return;
}

void Delete_Employee(Employee* employees, char* fullname)
{
	int found = 0;
	Employee* temp = employees;
	Employee* prev = temp;
	while (temp != NULL)
	{
		if (strcmp(temp->Fullname, fullname) == 0)
		{
			prev->next = temp->next;
			//free(temp);
			found++;
			break;
		}
		prev = temp;
		temp = temp->next;
	}
	Update_Employees_File(employees);
	if (found)
		printf("The employee has been updated successfully!");
	else
		printf("Invalid employee to update");
	return;
}

void Update_Employees_File(Employee* employees)
{
	FILE* file = fopen(FILE_NAME, "wt");
	Employee* temp = employees;
	if (file == NULL)
	{
		printf("File can't be opened\n");
		return NULL;
	}
	while (temp != NULL)
	{
		Write_Employee(temp,file);
		temp = temp->next;
	}

	fclose(file);
}

void Print_Employees(Employee* employees)
{
	while(employees != NULL)
	{
		printf("Username:%s\n Password:%s\n level:%d\n FullName:%s\n",
			employees->Username, employees->Password, employees->level, employees->Fullname);
		employees = employees->next;
	}
} 

void Free_Employees(Employee* employees)
{
	Employee* temp;
	while (employees != NULL)
	{
		temp = employees;
		employees = employees->next;
		free(temp);
	}
}

int Login_Level_Employee(Employee* employees, char* Username, char* Password)
{
	while(employees != NULL)
	{
		if (strcmp(employees->Username, Username) == 0 && strcmp(employees->Password, Password) == 0)
				return employees->level;
		employees = employees->next;
	}
	printf("Can't Login, Username or Password is incorrect\n");
	return 0;
}