#include<stdio.h>	/*Include for standard input and output*/
#include<string.h>	/*Include for the functions of strings*/
#include<Windows.h>
#include<conio.h>	/*Include for the function getch()*/
#include<stdlib.h>	
#include<time.h>	/*Include for the initialization of the seed of function time()*/

typedef struct{
	char cName[41];
	char cAddress[51];
	char cTelenumber[16];
	char cAccount[11];
	char cPIN[7];
	int iBalance;
	int iRegister;
}Customer;	/*Define a structure type called "Customer"*/

void bankclerk(void);
char input_1char(void);
void create_bankclerk(void);
void delete(void);
void input_PIN(char *b);
void add(void);
void print(Customer *);
int input_account(char *a);
int input(char *a, int max);
int input_number(char *a, int max);
void edit(void);
void deposit(void);
void customer(void);
void manager(void);
void create_account(char *account);
int customer_login(char *account);
void update(Customer *a, FILE *p);

int order;

int main(){
	FILE *fp;
	if (order == 1) 
		mf();

	if ((fp = fopen("manager.txt", "r")) == NULL) {  /*Check whether the file is exist */
		fp = fopen("manager.txt", "w");              /*Creat a new txt-file named "nmanager"*/
		fclose(fp);                               /*Close the file*/
	}
	else 
		fclose(fp);

	if ((fp = fopen("bc.txt", "r")) == NULL) {  /*Check whether the file is exist */
		fp = fopen("bc.txt", "w");              /*Creat a new txt-file named "bc"*/
		fclose(fp);                               /*Close the file*/
	}
	else 
		fclose(fp);
	
	while (1){
		char cmd;
		system("cls");
		printf("==================                         ====================\n");
		printf("================== Bank Information system ====================\n");
		printf("==================                         ====================\n");
		printf("\n");
		printf("***********************   welcome!   **************************\n");
		printf("*                                                             *\n");
		printf("*                 (1)     Customer                            *\n");
		printf("*                 (2)     Bank clerk                          *\n");
		printf("*                 (3)     Manager                             *\n");
		printf("*                 (4)     Quit                                *\n");
		printf("*                                                             *\n");
		printf("***************************************************************\n");
		printf("\n\n");	/*Print the main menu*/
		cmd = input_1char();
		while (cmd < '1' || cmd > '4'){
			printf("Invalid input\n\n");
			cmd = input_1char();
		}	/*Choose the identity to login*/
		switch ((int)(cmd - '0')){
		case 1:
			customer();	/*Login as a customer*/
			break;
		case 2:
			bc();	/*Login as a bank clerk*/
			break;
		case 3:
			man();	/*Login as a manager*/
			break;
		default:
			system("cls");
			printf("\n == Quit successfully! ==\n\n");
			exit(0);	/*Quit the system*/
		}
	}
}

void manager(void){
	FILE *p;
	char cAccount[11];
	Customer tmp;
	if ((p = fopen("Customer.txt", "r")) == NULL) {  /*Check whether the file is exist */
		p = fopen("Customer.txt", "w");              /*If not, creat a new txt-file named user*/
		fclose(p);        /*Close the file*/
	}
	else
		fclose(p);

	p = fopen("Customer.txt", "r+b");	/*Open the databse of the customer*/
	if (p == NULL){
		printf("==Cannot access the database.==\nPlease restart the program.\n");
		exit(1);
	}
	system("cls");
	while (1){
		char cmd;
		printf("\n  == Press 1 to access account information\n\n");
		printf("  == Press 2 to access number of customers\n\n");
		printf("  == Press 3 to access number of accounts\n\n");
		printf("  == Press 4 to quit viewing banking statistics\n\n");	/*Print the menu*/
		cmd = input_1char();
		while (cmd < '1' || cmd > '5'){
			printf("Invalid input\n");
			cmd = input_1char();
		}	/*Make a choice including test for illegal input*/
		switch ((int)(cmd - '0')){
		case 1:{
				   int i;
				   system("cls");
				   printf("\nAccount number:");
				   i = input_number(cAccount, 10);
				   if (i == 1 || strlen(cAccount) != 10){
					   printf("\n =The account must have 10 digits= \n\n");
					   break;
				   }
				   if (check_account(cAccount, p) == 0){
					   printf("\n =The account does not exist=\n\n");
					   break;
				   }	/*Input the account number including test for the existance of the account*/
				   system("cls");
				   putchar('\n');
				   rewind(p);
				   while (fread(&tmp, sizeof(Customer), 1, p)){
					   if (strcmp(tmp.cAccount, cAccount) == 0)
						   break;
				   }	/*Read the account out of the file*/
				   print(&tmp);	/*Display the account information*/
		}
			break;
		case 2:
		{
				  int n;
				  int i, j;
				  int count1, count2;
				  char *name;
				  Customer *test;
				  Customer tmp;
				  fseek(p, 0L, SEEK_END);
				  n = ftell(p) / sizeof(Customer);
				  system("cls");
				  if (n == 0){
					  printf("\n==There is no customers.==\n");
					  break;
				  }	/*Find the total number of accounts*/
				  test = (Customer *)malloc(n*sizeof(Customer));
				  rewind(p);
				  i = 0;
				  while (fread(&test[i++], sizeof(Customer), 1, p));	/*Store all the structures*/
				  for (i = 0; i < n; i++)
				  {
					  for (j = i + 1; j < n; j++)
					  {
						  if (strcmp(test[j].cName, test[j + 1].cName)>0)
						  {
							  tmp = test[j];
							  test[j] = test[j + 1];
							  test[j + 1] = tmp;
						  }
					  }				/*Bubble sort*/
				  }
				  count2 = 0;
				  for (i = 0; i < n; i++){
					  count1 = 0;
					  for (j = i + 1; j < n; j++)	/*Compare the current structure with the structures behind it*/
					  {
						  if (strcmp(test[i].cName, test[j].cName) == 0)
							  count1++;
					  }
					  if (count1 == 0)	/*If there is no accounts with the same name, add the count number*/
						  count2++;
				  }
				  printf("\n  == Number of customers: %d\n", count2);	/*Display the total number of customers*/
		}
			break;
		case 3:
		{
				  int n;
				  fseek(p, 0L, SEEK_END);
				  n = ftell(p) / sizeof(Customer);
				  system("cls");
				  printf("\n  == Number of accounts: %d\n", n);	/*Display the total number of accounts*/
		}
			break;
		default:{
					fclose(p);
					order = 0;
					system("cls");
					return;
		}
		}
	}
}

void customer(void){
	int flag = 0;	/*Declare as a command control of the loop*/
	char cmd;	/*Store the choice*/
	Customer tmp;
	char cAccount[11];	/*Store the account number*/
	FILE *p;
	int a;	/*Store the return value of the function*/
	if (customer_login(cAccount) == 1)	/*Login process*/
		return;
	p = fopen("Customer.txt", "r+b");
	if (p == NULL){
		printf("\n=Failed to access the database.=\n\n");
		return;
	}	/*Open the file*/
	while (fread(&tmp, sizeof(Customer), 1, p)){
		if (strcmp(tmp.cAccount, cAccount) == 0)
			break;
	}		/*Find the login account*/
	fseek(p, -sizeof(Customer), SEEK_CUR);	/*Find the position of the account*/
	while (flag == 0){
		printf("---------------------------------------------\n");
		printf("\n== Press 1 to display current account balance\n\n");
		printf("== Press 2 to withdraw\n\n");
		printf("== Press 3 to register a deposit\n\n");
		printf("== Press 4 to display account information\n\n");
		printf("== Press 5 to log off\n\n");
		cmd = input_1char();
		while (cmd < '1' || cmd > '5'){
			printf("Invalid input\n");
			cmd = input_1char();
		}
		system("cls");
		switch ((int)(cmd - '0')){
		case 1:
		{
				  system("cls");
				  printf("\nCurrent account balance: %d\n\n", tmp.iBalance);	/*Print the balance*/
		}
			break;
		case 2:
		{
				  int iWithdraw;
				  char cWithdraw[6];
				  system("cls");
				  printf("\nWithdraw:");
				  a = input_number(cWithdraw, 5);	/*Test of the input*/
				  putchar('\n');
				  if (a == 1){
					  printf("Invalid input\n\n");
					  break;
				  }
				  iWithdraw = atoi(cWithdraw);	/*Convert the input string to an integer*/
				  if (iWithdraw < 0){
					  printf("Illegal activity\n\n");
					  break;
				  }
				  else if (iWithdraw > 10000){
					  printf("=You can withdraw 10,000 at a time=\n\n");
					  break;
				  }
				  else if (iWithdraw > tmp.iBalance){
					  printf("=Not enough money=\n\n");	/*Check whether the withdraw is illegal*/
					  break;
				  }
				  else
				  {
					  tmp.iBalance -= iWithdraw;
					  printf("= Withdraw successfully! =\n\n");
				  }
		}
			break;
		case 3:
		{
				  int iRegister;	/*Similar with the process of withdraw*/
				  char cRegister[6];
				  system("cls");
				  printf("\nRegister a deposit:");
				  a = input_number(cRegister, 5);
				  putchar('\n');
				  if (a == 1){
					  printf("Invalid input\n\n");
					  break;
				  }
				  iRegister = atoi(cRegister);
				  if (iRegister < 0){
					  printf("Illegal activity\n\n");
					  break;
				  }
				  else if (iRegister > 10000){
					  printf("=You can register 10,000 at a time=\n\n");
					  break;
				  }
				  else
				  {
					  printf("= Register successfully! =\n\n");
					  tmp.iRegister += iRegister;
				  }
		}
			break;
		case 4:
		{
				  system("cls");
				  print(&tmp);
		}
			break;
		default:
		{
				   fwrite(&tmp, sizeof(Customer), 1, p);	/*Write the strucutre to the file*/
				   fclose(p);
				   flag = 1;	/*To break the while loop*/
				   system("cls");
				   printf("\n== Log off successfully! ==\nPress any key to continue\n");
				   getch();
		}
			break;
		}
	}
}

int customer_login(char *account){
	FILE *p;
	char cAccount[11];	/*Store the input account*/
	char cPIN[7];	/*Store PIN*/
	Customer tmp;	/*Store the structure read from the file*/
	int a, b;	/*Store the return value*/
	char cmd;	/*Declarea as a command control*/
	p = fopen("Customer.txt", "rb");
	if (p == NULL){
		printf("\n=Failed to access the database.=\n\n");
		exit(1);
	}	/*Open the file for login*/
	a = 1;
	b = 1;	/*Initialization*/
	while ((a + b) != 0){
		a = 1;
		b = 1;
		system("cls");
		printf("\n-----------------Customer login--------------\n");
		printf("\nAccount number:");
		a = input_account(cAccount, 10);	/*Input the account number*/
		putchar('\n');
		if (a == 1){
			printf("\n=The account number must have 10 digits.=\n");
			printf("Continue to login?(y/n)\n\n");	/*Provide an option to quit the login process*/
			cmd = input_1char();
			while (cmd != 'y' && cmd != 'n'){
				printf("Invalid input\n");
				cmd = input_1char();
			}
			if (cmd == 'n')
			{
				fclose(p);	/*Quit the login process*/
				return 1;
			}
			else
				continue;
		}
		b = 1 - check_account(cAccount, p);	/*Check the existance of the account*/
		if (b == 1){
			printf("\n==The account dose not exist.==\n");
			printf("Continue to login?(y/n)\n\n");
			cmd = input_1char();
			while (cmd != 'y' && cmd != 'n'){
				printf("Invalid input\n");
				cmd = input_1char();
			}
			if (cmd == 'n')
			{
				fclose(p);	/*Quit the login process*/
				return 1;
			}
			else
				continue;
		}
	}
	system("cls");
	printf("\n-----------------Customer login--------------\n");
	printf("\nAccount number: %s\n", cAccount);	/*Update the interface*/
	rewind(p);
	while (fread(&tmp, sizeof(Customer), 1, p)){
		if (strcmp(tmp.cAccount, cAccount) == 0)
			break;
	}	/*Find the matched account*/
	input_PIN(cPIN);
	while (strcmp(cPIN, tmp.cPIN) != 0){	/*Find whether the PIN matches*/
		printf("=Wrong PIN.=\n");
		printf("Continue to input?(y/n)\n");	/*Provide an option to quit the login process*/
		cmd = input_1char();
		while (cmd != 'y' && cmd != 'n'){
			printf("Invalid input\n");
			cmd = input_1char();
		}
		if (cmd == 'n')
		{
			fclose(p);
			return 1;	/*Close the file and quit the login process*/
		}
		else
		{
			system("cls");
			printf("\n-----------------Customer login--------------\n");
			printf("\nAccount number: %s\n", cAccount);	/*Update the interface*/
			input_PIN(cPIN);
		}
	}
	strcpy(account, tmp.cAccount);	/*Copy the login account number*/
	fclose(p);
	printf("\n== Login successfully! ==\nPress any key to continue\n");
	getchar();
	system("cls");
	return 0;
}
/*The login process as a customer*/

void bankclerk(void){
	system("cls");
	int flag = 0;	/*Declare as a command control for the while loop*/
	while (flag == 0){
		char cmd;
		printf("\n---------------------------------------------------\n");
		printf("\n== Press 1 to add a new account\n\n");
		printf("== Press 2 to make a deposit to an account\n\n");
		printf("== Press 3 to edit an account\n\n");
		printf("== Press 4 to delete an account\n\n");
		printf("== Press 5 to log off\n\n");	/*Print the selections*/
		cmd = input_1char();
		while (cmd < '1' || cmd > '5'){
			printf("Invalid input\n");
			cmd = input_1char();
		}	/*Make a choice*/
		switch ((int)(cmd - '0')){
		case 1:
			add();	/*Call the function to add a new account*/
			break;
		case 2:
			deposit();	/*Call the function to make a deposit*/
			break;
		case 3:
			edit();		/*Call the function to edit an account*/
			break;
		case 4:
			delete();	/*Call the function to delete an account*/
			break;
		default:
		{
				   flag = 1;
				   system("cls");
				   printf("\n== Log off successfully! ==\n");
				   printf("\nPress any key to continue\n");
				   getchar();
		}
			break;
		}
	}
}

void deposit(void){
	FILE *p;
	int iDeposit;	/*Store the deposit money*/
	char cAccount[11];	/*Store the input account number*/
	char cmd;	/*Declare for command control*/
	p = fopen("Customer.txt", "r+b");
	if (p == NULL){
		printf("\nCannot access the database.\n\nPlease restart the program.\n\n");
		exit(1);
	}	/*Open the database to make a deposit*/
	system("cls");
	printf("\n----------------Make a deposit------------------\n\n");
	printf("=Do you want to view all the registers?(y/n)=\n\n");	/*Provide an option to output all the registers*/
	cmd = input_1char();
	while (cmd != 'y' && cmd != 'n'){
		printf("Invalid input\n");
		cmd = input_1char();
	}
	system("cls");
	if (cmd == 'y')
	{
		Customer tmp;
		int i = 0;
		rewind(p);	/*Ensure the file pointer is at the beginning of the file*/
		while (fread(&tmp, sizeof(Customer), 1, p)){	/*Each time read a structure from the file*/
			if (tmp.iRegister != 0)
			{
				printf("Account number: %s\n", tmp.cAccount);
				printf("Name: %s\n", tmp.cName);
				printf("Deposit registered: %d\n", tmp.iRegister);	/*Print all the accounts whose register is not 0*/
				i++;	/*Count the number of accounts whose register is not 0*/
				putchar('\n');
			}
		}
		if (i == 0)	/*i=0 means there is no registers*/
			printf("\nNo registers\n");
	}
	while (1){
		Customer test;	/*Declare to store the structures read from the file*/
		putchar('\n');
		printf("-----------------Choose the account----------------\n\n");
		printf("Account number:");
		if (input_number(cAccount, 10) == 1 || strlen(cAccount) != 10){	/*Input the account number to make a deposit*/
			printf("\n=The account number must have 10 digits=\n");
			fclose(p);
			return;
		}
		if (check_account(cAccount, p) == 0){	/*Use the function chech_account() to check the existance of the account*/
			printf("\n=The account does not exist=\n");
			fclose(p);
			return;
		}
		putchar('\n');
		rewind(p);
		while (fread(&test, sizeof(Customer), 1, p)){
			if (strcmp(test.cAccount, cAccount) == 0)
				break;
		}
		fseek(p, -sizeof(Customer), SEEK_CUR);		/*Find the position of the current account in the file*/
		while (1){
			int flag;	/*Declare to store the return value*/
			char cDeposit[6];	/*Declare for test*/
			printf("\nDeposit:");
			flag = input_number(cDeposit, 5);	/*Input the deposit money*/
			if (flag == 1){
				printf("\n=You can register maximum $10,000 at a time=\n");
				continue;
			}
			else
				iDeposit = atoi(cDeposit);	/*Convert the string to an integer*/
			if (iDeposit < 0){
				printf("\nInvalid activity\n");
				continue;
			}
			else if (iDeposit > 10000){
				printf("\n=You can register maximum $10,000 at a time=\n");	/*The limit of each deposit is 10,000*/
				continue;
			}
			else
			{
				system("cls");
				printf("\n== Register successfully! ==\n");
				break;
			}
		}
		test.iBalance += iDeposit;	/*Make a deposit to the account*/
		if (test.iRegister - iDeposit >= 0)
			test.iRegister -= iDeposit;	/*Reduce the registered money*/
		else
			test.iRegister = 0;	/*If the deposit money is larger than the registered money, registered money is set to 0*/
		fwrite(&test, sizeof(Customer), 1, p);	/*Rewrite the structure back to the file*/
		printf("=Do you want to continue your operation?(y/n)=\n\n");	/*Provide an option to output all the registers*/
		cmd = input_1char();
		while (cmd != 'y' && cmd != 'n'){
			printf("Invalid input\n");
			cmd = input_1char();
		}
		if (cmd == 'n')
			break;
		else
			system("cls");
	}
	fclose(p);
}
/*The process of making a deposit*/

void edit(void){
	int cmd = 0;
	int flag = 0;	/*Declare for command control*/
	FILE *fptr;
	char c[11];
	fptr = fopen("Customer.txt", "r+b");
	if (fptr == NULL){
		printf("\n==Cannot access the database.==\n\nPlease restart the program.\n\n");
		exit(1);
	}	/*Open the databse for editing*/
	system("cls");
	printf("\n----------------Edit an account------------------\n\n");
	printf("Input the account number:");
	flag = input_number(c, 10);
	if (flag == 1 || strlen(c) != 10){
		system("cls");
		printf("\n=The account must have 10 digits.=\n");
		return;
	}	/*Input an account number*/
	cmd = check_account(c, fptr);
	if (cmd == 0){
		system("cls");
		printf("\n=Cannot find the account.=\n");	/*Print the warning*/
		fclose(fptr);
		return;
	}
	system("cls");
	cmd = 1;
	while (cmd){
		Customer tmp, test;
		rewind(fptr);
		while (fread(&tmp, sizeof(Customer), 1, fptr)){
			if (strcmp(tmp.cAccount, c) == 0)
				break;
		}
		print(&tmp);
		printf("\n");
		printf("==Choose which part to edit==\n\n");
		printf("      (1)--------Name\n\n");
		printf("      (2)--------Address\n\n");
		printf("      (3)--------Telephone number\n\n");
		printf("      (4)--------PIN\n\n");
		printf("      (5)--------Quit\n\n");
		cmd = input_1char();
		while (cmd < '1' || cmd > '5'){
			printf("Invalid input\n");
			cmd = input_1char();
		}	/*Make a choice including test for illegal input*/
		system("cls");
		print(&tmp);
		putchar('\n');
		switch ((int)(cmd - '0')){
		case 1:{
				   printf("Name:");
				   flag = input(tmp.cName, 40);	/*Change the name*/
				   if (flag == 1)
				   {
					   system("cls");
					   printf("\nInvalid input\n");	/*If the input is invalid, return to the selection interface*/
					   break;
				   }
				   putchar('\n');
				   update(&tmp, fptr);
		}
			break;
		case 2:{
				   printf("Address:");
				   flag = input(tmp.cAddress, 50);	/*Change the address*/
				   if (flag == 1)
				   {
					   system("cls");
					   printf("\nInvalid input\n");
					   break;
				   }
				   putchar('\n');
				   update(&tmp, fptr);
		}
			break;
		case 3:{
				   printf("Telephone number:");
				   flag = input_number(tmp.cTelenumber, 15);	/*Change the telephone number*/
				   if (flag == 1)
				   {
					   system("cls");
					   printf("\nInvalid input\n");
					   break;
				   }
				   putchar('\n');
				   update(&tmp, fptr);
		}
			break;
		case 4:{
				   char PIN1[7];
				   char PIN2[7];
				   input_PIN(PIN1);
				   printf("\n\n=Please input again for check=\n");	/*Change the PIN and input twice for check*/
				   input_PIN(PIN2);
				   if (strcmp(PIN1, PIN2) != 0)
				   {
					   system("cls");
					   printf("\n=The PINs are not the same.=\n");	/*If they are not the same, back to the selection interface*/
					   break;
				   }
				   else
					   strcpy(tmp.cPIN, PIN1);
				   update(&tmp, fptr);
		}
			break;
		default:
			cmd = 0;	/*Quit editing the account*/
			break;
		}
	}
	fclose(fptr);
	system("cls");
}
/*The process of editing an existing account*/

void update(Customer *a, FILE *p){
	Customer tmp;
	rewind(p);	/*Ensure that the file pointer is at the beginning of the file*/
	while (fread(&tmp, sizeof(Customer), 1, p)){
		if (strcmp(tmp.cAccount, a->cAccount) == 0)
			break;
	}
	fseek(p, -sizeof(Customer), SEEK_CUR);	/*Find the position of the current account*/
	fwrite(a, sizeof(Customer), 1, p);	/*Update the structure information*/
}

void delete(void){
	int n, i, j, cmd;	/*Declare for command control*/
	char cAccount_test[11];	/*Declare a test account number string*/
	FILE *f1, *f2;	/*Pointing to two files*/
	Customer test;
	f1 = fopen("Customer.txt", "rb");
	if (f1 == NULL){
		printf("\n==Cannot access the database.==\n\nPlease restart the program.\n\n");
		exit(1);
	}	/*Open the file and Check the existance of the database*/
	system("cls");
	printf("\n----------------Delete an account------------------\n\n");
	printf("Account number:");
	cmd = input_number(cAccount_test, 10);	/*Input an account number*/
	putchar('\n');
	if (cmd == 1 || strlen(cAccount_test) != 10)
	{
		printf("Illegal input.\n\n");
		fclose(f1);
		return;
	}
	if (check_account(cAccount_test, f1) == 0)
	{
		printf("=The account does not exist.=\n\n");
		fclose(f1);
		return;
	}	/*Check the existance of the account*/
	f2 = fopen("New.txt", "wb");	/*Create a new for updating*/
	if (f2 == NULL){
		printf("=Delete failed.=\n press any key to continue");
		exit(1);
	}
	rewind(f1);
	while (fread(&test, sizeof(Customer), 1, f1)){	/*Each time read one structure from the file*/
		if (strcmp(test.cAccount, cAccount_test) != 0)	/*Compare the account number of the structure with the input account number */
			fwrite(&test, sizeof(Customer), 1, f2);	/*If they are not the same, write the structure into the new file*/
	}
	fclose(f2);
	fclose(f1);
	remove("Customer.txt");	/*Delete the previous file*/
	rename("New.txt", "Customer.txt");	/*Rename the new file*/
	printf("\n== Delete successfully! ==\n\nPress any key to continue\n");
	getchar();
}
/*The process of deleting an existing account*/

void add(void){
	Customer *new;
	char PIN1[7];
	char PIN2[7];	/*Declare two strings for checking the PIN*/
	FILE *fptr;
	new = (Customer *)malloc(sizeof(Customer));	/*Declare a new structure*/
	if (new == NULL)
	{
		printf("==Memory allocation failed.==\n\nPlease restart the program.\n\n");
		exit(1);
	}
	fptr = fopen("Customer.txt", "a+b");	/*Open the file to add at the end*/
	if (fptr == NULL){
		printf("\n==Cannot access the database.==\n\nPlease restart the program.\n\n");
		exit(1);
	}
	system("cls");
	printf("\n----------------Add a new account------------------\n\n");
	printf("Name:");
	while (input(new->cName, 40) == 1){
		printf("\n=The name must have no more than 20 characters=\n\n");
		printf("Name:");
	}	/*Input the name*/
	system("cls");
	printf("\n----------------Add a new account------------------\n\n");
	printf("Name:%s\n\n", new->cName);
	printf("Address:");	/*Update the interface*/
	while (input(new->cAddress, 50) == 1){
		printf("\nIllegal input.Please input again.\n\n");
		printf("Address:");
	}	/*Input the address*/
	system("cls");
	printf("\n----------------Add a new account------------------\n\n");
	printf("Name:%s\n\n", new->cName);
	printf("Address:%s\n\n", new->cAddress);
	printf("Telephone number:");	/*Update the interface*/
	while (input_number(new->cTelenumber, 15) == 1){
		printf("\nIllegal input.Please input again.\n\n");
		printf("Telephone number:");
	}	/*Input the telephone number*/
	system("cls");
	printf("\n----------------Add a new account------------------\n\n");
	printf("Name:%s\n\n", new->cName);
	printf("Address:%s\n\n", new->cAddress);
	printf("Telephone number:%s\n\n", new->cTelenumber);	/*Update the interface*/
	input_PIN(PIN1);	/*Input the PIN for the first time*/
	system("cls");
	printf("\n----------------Add a new account------------------\n\n");
	printf("Name:%s\n\n", new->cName);
	printf("Address:%s\n\n", new->cAddress);
	printf("Telephone number:%s\n\n", new->cTelenumber);
	printf("PIN:******");
	printf("\n\n=Please input again for check=\n\n");	/*Update the interface*/
	input_PIN(PIN2);	/*Input the PIN for the second time*/
	while (strcmp(PIN1, PIN2) != 0){
		system("cls");
		printf("\n----------------Add a new account------------------\n\n");
		printf("Name:%s\n\n", new->cName);
		printf("Address:%s\n\n", new->cAddress);
		printf("Telephone number:%s\n\n", new->cTelenumber);	/*Update the interface*/
		printf("=The PINs are not the same=\n=Please reset the PIN=\n\n");	/*Print warning*/
		input_PIN(PIN1);
		system("cls");
		printf("\n----------------Add a new account------------------\n\n");
		printf("Name:%s\n\n", new->cName);
		printf("Address:%s\n\n", new->cAddress);
		printf("Telephone number:%s\n\n", new->cTelenumber);
		printf("PIN:******\n\n");
		printf("=Please input again for check=\n\n");	/*Update the interface*/
		input_PIN(PIN2);	/*Check again*/
	}
	strcpy(new->cPIN, PIN1);
	create_account(new->cAccount);	/*Generate an account number*/
	new->iBalance = 0;
	new->iRegister = 0;	/*Initialize the account information*/
	system("cls");
	printf("\n------------------Account information---------------\n");
	print(new);
	fwrite(new, sizeof(Customer), 1, fptr);	/*Write the structure into the file*/
	fclose(fptr);
	free(new);
	printf("\n== Account built successfully! ==\n\nPress any key to continue\n");
	getch();
	system("cls");
}
/*The process of adding a new account*/

int input_account(char *a){
	char cTest[11];		/*Declare a test string*/
	int cmd;	/*Declare as a command control*/
	cmd = input_number(cTest, 10);	/*Input an account*/
	if (cmd == 1 || strlen(cTest) != 10)
		return 1;	/*Only accept accounts with 10 digits*/
	else
	{
		strcpy(a, cTest);	/*Copy the test string to the formal string*/
		return 0;
	}
}
/*Return 1 means the input is invalid. Return 2 means the input is valid*/

char input_1char(void){
	char c1, c2;	/*Declare two characters for the test of valid input*/
	while (1){
		printf("Your choice:");
		c1 = getchar();
		if (c1 == 10){	/*If the first input is the "Enter key", the input is not valid*/
			printf("Invalid input!\n\n");
			continue;	/*Input again*/
		}
		scanf("%c", &c2);
		fflush(stdin);		/*Clean the keyboard buffer*/
		if (c2 != 10)	/*If the second input is not the "Enter key", the input is not valid*/
			printf("Invalid input!\n\n");
		else
			break;	/*End the input and return value*/
	}
	return c1;
}
/*return a single character*/

void create_account(char *account){
	int i;
	int a;
	FILE *fptr;
	fptr = fopen("Customer.txt", "rb");
	while (1){
		char cTest[11];
		srand(time(0));		/*Initialize for rand()*/
		for (i = 0; i < 10; i++)
		{
			a = rand() % 10;
			cTest[i] = a + 48;
		}
		cTest[10] = '\0';	/*Obtain a random account number with 10 digits*/
		if (check_account(cTest, fptr) == 0)	/*Check whether the account has been occupied*/
		{
			strcpy(account, cTest);
			break;
		}
	}
	fclose(fptr);
}
/*Obtain a random account number with 10 digits and store it in string b */

void print(Customer *a){
	printf("\nAccount number: %s\n", a->cAccount);
	printf("\nName: %s\n", a->cName);
	printf("\nAddress: %s\n", a->cAddress);
	printf("\nTelephone number: %s\n", a->cTelenumber);
	printf("\nAccount balance: %d\n", a->iBalance);
	printf("\nRegistered deposit: %d\n", a->iRegister);
}

int input(char *a, int max){
	char c;
	int i = 0; /*Declare a integer representing the number of the input characters*/
	int count = 0;	/*Declare as the number of characters and digits in the string*/
	int j;	/*Declare for the use of for loop*/
	char *p;
	p = (char *)malloc(max + 1);	/*Declare a dynamic array*/
	while ((c = getch()) != 13)	/*getch() store the input from the keyboard without displaying on the screen*/
	{							/*When the user dose not press the Enter key, the input continues*/
		if (c == '\b')
		{
			if (i > 0 && i < max + 1)	/*When the input is within the limit, the operation works*/
			{
				printf("\b \b"); /*When the user press the Backspace, change the display on the screen looks as if the last characters is deleted*/
				i--;	/*Move the count number backward*/
				*(p + i) = NULL;	/*Remove the last element*/
			}
			else if (i > max)
			{
				printf("\b \b");	/*When the number of input characters exceeds the limit, no operation will be conducted for the array*/
				i--;	/*Still move the count number backward*/
			}
		}
		if (c > 31 && c < 127)
		{
			printf("%c", c);	/*Print the input results on the screen*/
			if (i < max){
				*(p + i) = c;	/*Store the input valid characters*/
				*(p + i + 1) = '\0';
			}
			i++;	/*Increase the input count number*/
		}
	}
	if (i == 0)
		return 1;
	for (j = 0; j<strlen(p); j++)
	{
		if (isalnum(p[j]) || p[j] == 32)
			count++;
	}
	if (count != strlen(p))		/*Check whether the string consists only characters and digits*/
		return 1;
	if (i > max)
		return 1;	/*i>max means the input exceeds the limit*/
	else
	{
		strcpy(a, p);	/*The input is valid and copy the test string to the formal string*/
		return 0;
	}
}
/*Return 1 means exceeding the limit or empty. Return 0 means within the limit*/

void input_PIN(char *b){	/*Similar with the procedure of function int input()*/
	while (1){
		char c;
		int i = 0;
		int j;
		int count = 0;
		printf("PIN:");
		while ((c = getch()) != 13)
		{
			if (c == '\b')
			{
				if (i > 0 && i < 7)
				{
					printf("\b \b");
					i--;
					b[i] = NULL;
				}
				else if (i > 6)
				{
					printf("\b \b");
					i--;
				}
			}
			else
			{
				printf("*"); /*The only difference is that the display on the screen is replaced by '*' as it's password*/
				if (i < 6){
					b[i] = c;
					b[i + 1] = '\0';
				}
				i++;
			}
		}
		if (i != 6){	/*Only accept 6 digits*/
			printf("\n=The PIN must have 6 digits=\nPlease input again\n");
			continue;
		}
		for (j = 0; j < strlen(b); j++)
		{
			if (isdigit(b[j]))	/*Check whether the inputs are all digits*/
				count++;
		}
		if (count != 6)
		{
			printf("\n=The PIN must have 6 digits=\nPlease input again\n");
			continue;
		}
		break;
	}
	fflush(stdin);	/*Clean the key buffer*/
	putchar('\n');
}
/*Only store a PIN with 6 digits into string b*/ /*Perfect*/

int input_number(char *number, int max){
	char *a;
	a = (char *)malloc((max + 1)*sizeof(char));	/*Declare a dynamic array*/
	int i, cmd;
	int count = 0;
	cmd = input(a, max);	/*Store a string within the limit*/
	if (cmd == 1)	/*Return 1 means the input is invalid*/
		return 1;
	for (i = 0; i < strlen(a); i++){
		if (isdigit(a[i]))	/*Check whether each element is a digit*/
			count++;
	}
	if (count != strlen(a))
		return 1;
	else
	{
		strcpy(number, a);
		return 0;	/*Store it into the string passed into the function*/
	}
}
/*Return 1 means exceeding the limit or empty. Return 0 means within the limit*/

int check_account(char *a, FILE *p){
	int cmd = 0;	/*Declare for the return value*/
	Customer test;	/*Declare a test structure for comparison*/
	rewind(p);	/*Ensure the file pointer is at the beginning of the file*/
	while (fread(&test, sizeof(Customer), 1, p))	/*Each time read one structure from the file for test*/
	{
		if (strcmp(a, test.cAccount) == 0)	/*Compare the input username with the test username read from the file*/
		{
			cmd = 1;	/*If they are the same, stop reading structures from the file*/
			break;		/*Break the loop and then return a value*/
		}
	}
	return cmd;
}
/*Check the exsitance of the input account. Return 1 means the account exist, return 0 means the account does not exist*/

Another source code "4_2" is shown below.
#include<stdio.h>
#include<string.h>
#include<Windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

typedef struct user{
	char name[21];
	char code[21];
}s;

s tu,cp;
FILE *fp;
char check;
int order;

int varip(char *p){           /*check whether the length of passward meet the requirements*/
	int len;
	len = strlen(p);
	if (len<6 || len>12)
	{
		return 0;
	}
	else
		return 1;
}

int varin(char *p)            /*check whether the length of user name meet the requirements*/
{
	int ln;
	ln = strlen(p);
	if (ln>16 || ln<4)
	{
		return 0;
	}
	else
		return 1;
}

void pw(char *p)                   /*Change the characters entered into '*'  */
{
	unsigned char c;                /*declare the varible c with positive value*/
	int i = 0;
	while ((c = getch()) != '\r')   /*check whther entered charater is the enter key*/
	{
		if (i<12 && isprint(c))     /*check the length of password and whether it can be printed */
		{
			p[i++] = c;
			putchar('*');
		}
		else if (i>0 && c == '\b')  /*Censored function*/
		{
			--i;
			putchar('\b');
			putchar(' ');
			putchar('\b');
		}
	}
	putchar('\n');
	p[i] = '\0';
}

void man(){
	system("cls");
	order = 0;
	char temp[21];               /*Declare a variable to store the second user code*/

	if ((fp = fopen("manager.txt", "r+")) == NULL) {   /*Open the file with 'r' mode and check whether it is successful*/
		printf("Failed to open the file!\n");
		exit(1);
	}
	
	fread(&cp, sizeof(struct user), 1, fp);
	if (strlen(cp.name) == 0){
		char *tname = "admin";
		strcpy(cp.name, tname);
		char *tcode = "123456";
		strcpy(cp.code, tcode);
		fwrite(&cp, sizeof(struct user), 1, fp);
	}
	printf("\n-----------------Manager login--------------\n");
	printf("\nManager name:");

	gets(tu.name);

	if (varin(tu.name) == 0) {                     /*Check the entered name whether it is illegal*/
		printf("\n=The Manager name is illegal! Please input again!=\n");
		printf("(Press enter to return.)\n");
		fclose(fp);
		getchar();                                 /*Pause the program*/
		rewind(stdin);                             /*Empty the buffer area*/
		man();
	}

	while (1)                                  /*find the user name from the file and check whether it is exist*/
	{
		if (strcmp(tu.name, cp.name) == 0) {   /*if the entered user name is same as one of the name in the file*/
			break;
		}
		else {
			if (!feof(fp))
				fread(&cp, sizeof(struct user), 1, fp);
			else {
				printf("\n=The Manager name does not exit!=");
				printf("\nPress 1 to login again.\nPress 2 to return to main menu.\n");
				fclose(fp);
				while (1) {                     /*Select to return to which function with illegal check*/
					printf("\n");
					check = input_1char();
					switch ((int)(check - '0'))
					{
					case 1: man(); break;
					case 2: system("cls"); main(); break;
					default:printf("\n=Input Error! Please input again!=");
					}
				}
			}
		}
	}

	printf("\nManager password:");
	pw(tu.code);                              /*input the user name */
	rewind(stdin);

	while (varip(tu.code) == 0) {               /*check the entered user name whether it is illegal*/
		printf("\n=The password is illegal!Please input again!=");
		printf("\n=Please enter the code:");
		pw(tu.code);
	}

	/*Compare the entered user code with recorded code in the file*/
	if (strcmp(tu.code, cp.code) == 0)           /*if the codes were agree*/
	{
		fclose(fp);
		printf("\n== Login successfully! ==\npress any key to continue");
		order = 1;
		getchar();                               /*Pause the program*/
		rewind(stdin);
		system("cls");
		main();                                  
	}
	else {                                       /*if the user codes were not the same*/
		printf("\n==Login failed!The password is not correct.==");
		printf("\nPress 1 to re-login. \nPress 2 to return to main menu.\n");
		fclose(fp);
		while (1) {                              /*Determain which function to return with illegal check*/
			printf("\n");
			check = input_1char();
			switch ((int)(check - '0'))
			{
			case 1: man(); break;
			case 2: system("cls"); main(); break;
			default:printf("\n=Input Error! Please input again!=");
			}
		}
	}
}

void manreg(){
		system("cls");
		char temp[20];               /*Declare a variable to store the second user code*/


		if ((fp = fopen("manager.txt", "r")) == NULL) {   /*Open the file with 'r' mode and check whether it is successful*/
			printf("=Fail to open the file!=\n");
			exit(1);
		}

		printf("\nManager account(length between 4 and 16):");

		fread(&cp, sizeof(struct user), 1, fp);        /*Read a struct from the file into the struct named cp*/

		gets(tu.name);                                 /*Store the user name from the keyboard into the name of struct tu*/

		if (varin(tu.name) == 0) {                     /*Check the entered name whether it is illegal*/
			printf("\nThe Manager account is illegal! Please input again!");
			printf("\n(Press enter to return.)");
			fclose(fp);
			getchar();                                 /*Pause the program*/
			rewind(stdin);                             /*Empty the buffer area*/
			manreg();
		}

		while (1)                                      /*Check whether the entered user name is exist in the file*/
		{
			if (strcmp(tu.name, cp.name) == 0)
			{
				printf("\n==The Manager account has been occupied!==");
				printf("\nPress 1 to to register again.\nPress 2 to return to main menu.\n");
				fclose(fp);
				while (1) {                            /*Determain which function to return with illegal check*/
					printf("\n");
					check = input_1char();
					switch ((int)(check - '0'))
					{
					case 1: manreg(); break;
					case 2: system("cls"); main(); break;
					default:printf("\n=Input Error! Please input again!=");
					}
				}
			}
			else {
				if (!feof(fp)) {
					fread(&cp, sizeof(struct user), 1, fp); /*Read a struct from the file into the struct named cp*/
				}
				else
					break;
			}
		}

		printf("\nManager password(length between 6 and 12):");
		pw(tu.code);                                    /*Store the user code into the struct tu*/
		rewind(stdin);

		while (varip(tu.code) == 0) {                    /*Check whether the code is illegal*/
			printf("\n=The Manager password is illegal!Please input again!=");
			printf("\nPlease enter the password:");
			pw(tu.code);
			rewind(stdin);
		}

		printf("\nPlease confirm the password:");         /*Reinput the user code to ensure */
		pw(temp);
		rewind(stdin);

		if (strcmp(tu.code, temp) != 0) {               /*Check whether the two passwords are the same*/

			fclose(fp);
			printf("\n==Two passwords does not agree!==");
			printf("\nPress 1 to to register again.\nPress 2 to return to main menu.");
			while (1) {                                 /*If the codes were not the same, determain which function to return*/
				printf("\nYour Choice:");
				check = input_1char();
				switch ((int)(check - '0'))
				{
				case 1: manreg();  break;
				case 2: system("cls"); main(); break;
				default:printf("\n=Input Error! Please input again!=");
				}
			}
		}

		fclose(fp);

		if ((fp = fopen("manager.txt", "a")) == NULL) {   /*Open the file with 'a' mode and check whether it is successful*/
			printf("==Fail to open the file!==\n");
			exit(1);
		}

		fwrite(&tu, sizeof(struct user), 1, fp);       /*Write the successfully registered uaer into the file*/
		printf("\n== Register successfully! ==\npress any key to continue\n");
		fclose(fp);
		getchar();                                     /*Pause the program*/
		rewind(stdin);
		system("cls");
		main();
}

void bcreg(){
	system("cls");
	char temp[20];               /*Declare a variable to store the second user code*/


	if ((fp = fopen("bc.txt", "r")) == NULL) {   /*Open the file with 'r' mode and check whether it is successful*/
		printf("==Failed to open the file!==\n");
		exit(1);
	}

	printf("\nBank clerk account(length between 4 and 16):");

	fread(&cp, sizeof(struct user), 1, fp);        /*Read a struct from the file into the struct named cp*/

	gets(tu.name);                                 /*Store the user name from the keyboard into the name of struct tu*/

	if (varin(tu.name) == 0) {                     /*Check the entered name whether it is illegal*/
		printf("\n=The account is illegal! Please input again!=");
		printf("\n(Press enter to return.)");
		fclose(fp);
		getchar();                                 /*Pause the program*/
		rewind(stdin);                             /*Empty the buffer area*/
		bcreg();
	}

	while (1)                                      /*Check whether the entered user name is exist in the file*/
	{
		if (strcmp(tu.name, cp.name) == 0)
		{
			printf("\n== The account is exist! ==");
			printf("\nPress 1 to to reregister.\n Press 2 to return to main interface.\n");
			fclose(fp);
			while (1) {                            /*Determain which function to return with illegal check*/
				printf("\nYour Choice(Press enter to determain):");
				check = input_1char();
				switch ((int)(check - '0'))
				{
				case 1: bcreg(); break;
				case 2: system("cls"); main(); break;
				default:printf("\nInput Error! Please reinput!");
				}
			}
		}
		else {
			if (!feof(fp)) {
				fread(&cp, sizeof(struct user), 1, fp); /*Read a struct from the file into the struct named cp*/
			}
			else
				break;
		}
	}

	printf("\nBank clerk password(length between 6 and 12):");
	pw(tu.code);                                    /*Store the user code into the struct tu*/
	rewind(stdin);

	while (varip(tu.code) == 0) {                    /*Check whether the code is illegal*/
		printf("\n=The password is illegal!Please reenter!=");
		printf("\nPlease enter the password:");
		pw(tu.code);
		rewind(stdin);
	}

	printf("\nPlease confirm the password:");         /*Reinput the user code to ensure */
	pw(temp);
	rewind(stdin);

	if (strcmp(tu.code, temp) != 0) {               /*Check whether the two passwords are the same*/

		fclose(fp);
		printf("\n== Two passwords does not agree! ==");
		printf("\nPress 1 to register again. \nPress 2 to return to main interface.");
		while (1) {                                 /*If the codes were not the same, determain which function to return*/
			printf("\nYour Choice:");
			check = input_1char();
			switch ((int)(check - '0'))
			{
			case 1: bcreg();  break;
			case 2: system("cls"); main(); break;
			default:printf("\n=Input Error! Please reinput!=");
			}
		}
	}
	fclose(fp);

	if ((fp = fopen("bc.txt", "a")) == NULL) {   /*Open the file with 'a' mode and check whether it is successful*/
		printf("==Fail to open the file!==\n");
		exit(1);
	}

	fwrite(&tu, sizeof(struct user), 1, fp);       /*Write the successfully registered uaer into the file*/
	printf("\n== Registered Success! ==\npress any key to continue!\n");
	fclose(fp);
	getchar();                                     /*Pause the program*/
	rewind(stdin);
	system("cls");
	main();
}

void mf(){
	while (1) {                              /*Determain which function to return with illegal check*/
		printf("\n1.Banking Activities \n\n2.Register a New Manager Account.  \n\n3.Register a New Bank Clerk Account \n\n4.Log Off\n");
		putchar('\n');
		check = input_1char();
		switch ((int)(check - '0'))
		{
		case 1: manager(); break;
		case 2: manreg(); break;
		case 3: bcreg(); break;
		case 4: printf("\n\n== Log off successfully! ==\n(Press any key to return)\n"); getchar(); system("cls"); order = 0; main(); break;
		default:printf("\n=Input Error! Please input again!=");
		}
	}
}

void bc(){
	system("cls");     /*clear the screen*/

	if ((fp = fopen("bc.txt", "r")) == NULL) {   /*Open the file through 'r' mode and check whether it is successful*/
		printf("==Failed to open the file!==\n");
		exit(1);
	}

	fread(&cp, sizeof(struct user), 1, fp);        /*Read a struct from the file into the struct named cp*//*\t*/
	rewind(stdin);
	printf("\nBank clerk account:");
	gets(tu.name);                                /*get the user name from keyboard including space*/

	if (varin(tu.name) == 0) {                    /*check the illegal input of the uaer name*/
		printf("\n=The account is illegal!Please input again!=");
		printf("\n(Press enter to return.)");
		fclose(fp);
		getchar();                                 /*Pause the program*/
		rewind(stdin);
		bc();
	}


	while (1)                                  /*find the user name from the file and check whether it is exist*/
	{
		if (strcmp(tu.name, cp.name) == 0) {   /*if the entered user name is same as one of the name in the file*/
			break;
		}
		else {
			if (!feof(fp))
				fread(&cp, sizeof(struct user), 1, fp);
			else {
				printf("\n== The account does not exit! ==");
				printf("\nPress 1 to login again. \nPress 2 to return to main menu.\n");
				fclose(fp);
				while (1) {                     /*Select to return to which function with illegal check*/
					putchar('\n');
					check = input_1char();
					switch ((int)(check - '0'))
					{
					case 1: bc(); break;
					case 2: system("cls"); main(); break;
					default:printf("\n=Input Error! Please input again!=");
					}
				}
			}
		}
	}

	printf("\nBank clerk password:");
	pw(tu.code);                              /*input the user name */
	rewind(stdin);

	while (varip(tu.code) == 0) {               /*check the entered user name whether it is illegal*/
		printf("\n=The password is illegal!Please input again!=");
		printf("\nPlease enter the password:");
		pw(tu.code);
	}

	/*Compare the entered user code with recorded code in the file*/
	if (strcmp(tu.code, cp.code) == 0)           /*if the codes were agree*/
	{
		fclose(fp);
		printf("\n== Login successfully! ==\nPress any key to continue.");
		getchar();                               /*Pause the program*/
		rewind(stdin);
		system("cls");
		bankclerk();                             /*Start the game if register successfully*/
	}
	else {                                       /*if the user codes were not the same*/
		printf("\n=Login failed!The password is not correct.=");
		printf("\nPress 1 to login again. \nPress 2 to return to main menu.\n");
		fclose(fp);
		while (1) {                              /*Determain which function to return with illegal check*/
			putchar('\n');
			check = input_1char();
			switch ((int)(check - '0'))
			{
			case 1: bc(); break;
			case 2: system("cls"); main(); break;
			default:printf("\n=Input Error! Please input again!=\n");
			}
		}
	}
}

