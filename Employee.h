#define _CRT_SECURE_NO_WARNINGS
#ifndef __EMPLOYEES__
#define __EMPLOYEES__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "EmployeesList.txt"

typedef struct employee
{
	char Fullname[30];
	char Username[30];
	char Password[30];
	int level;
	struct employee *next;
}Employee;

Employee* Read_Employees(Employee* employees);
Employee* Add_Employee(Employee* employees, Employee* newemployee);
void Add_New_Employee(Employee* emplyees);
void Write_Employee(Employee* employee,FILE* file);
void Find_Employee(Employee* employees, Employee* employee);
void Delete_Employee(Employee* employees, char* fullName);
void Create_Admin_User();
void Print_Employees(Employee* employees); 
void Update_Employees_File(Employee* employees);
void Free_Employees(Employee* employees);
int Login_Level_Employee(Employee* employees,char* Username, char* Password);

#endif