#include "BankingInfo.h"

bool account_read = false;
bool trans_read = false;

void welcome(void)
{
	/*
	Designed to welcome the user.

	@param void: None
	@return void: None
	*/
	printf("Welcome!!!\n\nThis Bank Reconciliation Program is the Final Project for CIS 1057 for the\n");
	printf("Spring 2016 Semester. This program is designed to read both the account information\n");
	printf("and transaction information from the text files account.txt and trans.txt, and update\n");
	printf("banking information according to both the account and the transaction information.");
	printf("\n\n");
}

void menu(void)
{
	/*
	Designed to display the manual.

	@param void: None
	@return void: None
	*/
	printf("1-Read and sort account and transaction files\n");
	printf("2-Reconcile accounts\n");
	printf("3-Find account by ID-Binary Search-List Transactions\n");
	printf("4-Find account by owner-Selection Search-List Transactions\n");
	printf("5-Print account summary report\n");
	printf("6-Print account detail report\n");
	printf("7-Print all accounts\n");
	printf("8-Print all transactions\n");
	printf("9-Save account and transactions to file\n");
	printf("0-Exit\n");
	printf("Enter a choice: ");
}

void PrintDate(Date d, char s[])
{
	/*
	Designed to print the date.

	@param d: Date variable to be printed.
	@param s[]: Char array that carries Date.
	@return void: None
	*/
	sprintf(s, "%d/%d/%d", d.month, d.day, d.year);
}

int CompareDates(Date a, Date b)
{
	/*
	Designed to compare the different dates and return the result as an int.

	@param a: Date variable that returns negative if greater.
	@param b: Date variable that returns positive if greater.
	@return int: Results from comparison.
	*/
	if (a.year < b.year)
	{
		return 1;
	}
	else if (a.year > b.year)
	{
		return -1;
	}
	else if (a.month < b.month)
	{
		return 1;
	}
	else if (a.month > b.month)
	{
		return -1;
	}
	else if (a.day < b.day)
	{
		return 1;
	}
	else if (a.day > b.day)
	{
		return -1;
	}
	else
		return 0;
}

double round_dbl(double d, int i)
{
	/*
	Designed to round the double passed in the double. Obtained from Free Stuff in Project description.

	@param d: Double variable to be rounded.
	@param i: Int variable that manages multiplication and division by powers.
	@return double: Rounded double
	*/

	// Multiply d by 10^(i+1) and cast as int
	int n = (int)(d * pow(10, i + 1));

	// Add 5 - will round up if last digit > 5
	n += 5;

	// Remove least significant digit
	n /= 10;

	// Cast n as double into d
	d = (double)n;

	// Divide d by 10^i
	d /= pow(10, i);

	// return d rounded to i digits

	return d;

}

//Account
void account_tag(void)
{
	/*
	Designed to identify the presented data within AccountArray.

	@param void: None
	@param void: None
	*/
	printf("ID\tOwner\t\tBalance\n");
	printf("--\t-----\t\t-------\n");
}
void trans_tag(void)
{
	/*
	Designed to identify the presented data within TransactionArray.

	@param void: None
	@param void: None
	*/
	printf("TID\tID\tDate\t\tType\tBalance\n");
	printf("---\t--\t----------\t-\t------\n");
}

void print_account(Account acct)
{
	/*
	Designed to print the information of one account.

	@param acct: Account variable to be printed.
	@return void: None
	*/
	printf("%d\t%s\t%1.2lf\n", acct.id, acct.owner, acct.balance);
}
void print_account_array(AccountArray aa)
{
	/*
	Designed to print the information of the entire AccountArray

	@param aa: AccountArray variable to be printed.
	@return void: None
	*/
	for (int i = 0; i < aa.count; i++)
	{
		print_account(aa.array[i]);
	}
}
void insert_account(AccountArray *acctArr, int id, char owner[], double balance)
{
	/*
	Designed to take the parameters and insert them into an AccountArray

	@param *acctArr: Pointer to AccountArray passed
	@param id: Int variable to be passed into *acctArr
	@param owner[]: Char array to be passed into *acctArr
	@param balance: Double variable to be passed into *acctArr
	@return void: None
	*/
	strcpy((*acctArr).array[(*acctArr).count].owner, owner);
	(*acctArr).array[(*acctArr).count].id = id;
	(*acctArr).array[(*acctArr).count].balance = balance;
	(*acctArr).count++;
}
void read_accounts(char file_name[], AccountArray *acctArr)
{
	/*
	Designed to read the contents of accounts.txt and store them into an AccountArray if the file
	has yet to be read.

	@param file_name[]: Char array that contains path of file to be opened
	@param *acctArr: Pointer to AccountArray designed to contain the contents of accounts.txt
	*/
	char a[200];
	char owner[15];
	int id;
	double balance;

	account_tag();

	if (account_read == false)
	{
		FILE *in_file = fopen(file_name, "r");
		if (in_file != NULL)
		{
			while (fgets(a, 200, in_file) != NULL)
			{
				a[strlen(a) - 1] = '\0';
				id = atoi(strtok(a, ","));
				strcpy(owner, strtok(NULL, ","));
				balance = atof(strtok(NULL, ","));
				insert_account(acctArr, id, owner, balance);
			}
			fclose(in_file);
		}
		else
		{
			printf("Error: file not found.\n");
		}
		account_read = true;
	}
	else
	{
		printf("");
	}

}
void swap_accounts(AccountArray *acctArr, int i, int j)
{
	/*
	Designed to swap the account information between one account and another account

	@param *acctArr: Pointer to AccountArray with account information
	@param i: Int variable that represents an account
	@param j: Int variable that represents an account
	@return void: None
	*/
	Account hold;

	hold.id = (*acctArr).array[j].id;
	strcpy(hold.owner, (*acctArr).array[j].owner);
	hold.balance = (*acctArr).array[j].balance;

	(*acctArr).array[j].id = (*acctArr).array[i].id;
	strcpy((*acctArr).array[j].owner, (*acctArr).array[i].owner);
	(*acctArr).array[j].balance = (*acctArr).array[i].balance;

	(*acctArr).array[i].id = hold.id;
	strcpy((*acctArr).array[i].owner, hold.owner);
	(*acctArr).array[i].balance = hold.balance;
}
void sort_accounts(AccountArray *acctArr)
{
	/*
	Designed to sort the account information by account ID.

	@param *acctArr: Pointer to AccountArray with account information
	@return void: None
	*/
	printf("ID\tOwner\t\tBalance\n");
	printf("--\t-----\t\t-------\n");
	for (int i = 0; i < LENGTH - 1; i++)
	{
		for (int j = LENGTH - 1; j > i; j--)
		{
			if ((*acctArr).array[j].id < (*acctArr).array[i].id)
			{
				swap_accounts(acctArr, i, j);
			}
		}
	}
}
int search_account_id(AccountArray acctArr, int id)
{
	/*
	Designed to find the requested ID

	@param acctArr: AccountArray with Account Information
	@param id: Int variable requested
	@return int: Result of ID search
	*/

	int begin = 0;
	int end = acctArr.count - 1;
	int mid;
	printf("id = %d\n", id);

	while (begin <= end)
	{
		mid = (end + begin) / 2;
		if (id < acctArr.array[mid].id)
		{
			end = mid - 1;
		}
		else if (id > acctArr.array[mid].id)
		{
			begin = mid + 1;
		}
		else if (id == acctArr.array[mid].id)
		{
			print_account(acctArr.array[mid]);
			return 0;
		}
	}
	printf("The id you want is not here");
	return -1;
}
int search_account_owner(AccountArray acctArr, char owner[])
{
	/*
	Designed to return the ID of the requested owner[]

	@param acctArr: AccountArray which contains the Account Information
	@param owner[]: Char array which contains name of requested owner
	@return int: ID of owner if present.
	*/
	int i;
	for (i = 0; i < acctArr.count; i++)
	{
		if (strcmp(acctArr.array[i].owner, owner) == 0)
		{
			print_account(acctArr.array[i]);
		}
	}
	return i;
	return -1;
}
void save_accounts(AccountArray acctArr, char fileName[])
{
	/*
	Designed to store the adjusted accounted information

	@param acctArr: AccountArray for information to be stored into file
	@param fileName[]: Char array to contain the path of the file.
	@return void: None
	*/
	printf("\n %s \n", fileName);
	FILE *out_file = fopen(fileName, "w");
	if (out_file != NULL)
	{
		for (int i = 0; i<acctArr.count; i++)
			fprintf(out_file, "%d, %s, %1.2lf \n",
				acctArr.array[i].id, acctArr.array[i].owner, acctArr.array[i].balance);
		fclose(out_file);
	}
}
//Transactions
void print_transaction(Transactions Trans)
{
	/*
	Designed to print the information of one transaction.

	@param Trans: Transaction variable to be printed.
	@return void: None
	*/
	printf("%d\t%d\t%s\t%c\t%1.2lf\n", Trans.id, Trans.account, Trans.date, Trans.type, Trans.amount);
}
void print_transaction_array(TransactionArray transArr)
{
	/*
	Designed to print the information of the entire TransactionArray

	@param transArr: TransactionArray variable to be printed.
	@return void: None
	*/
	for (int i = 0; i<transArr.count; i++)
	{
		print_transaction(transArr.array[i]);
	}
}
int compare_transactions(Transactions a, Transactions b)
{
	/*
	Designed to compare the different transactions and return the result as an int.

	@param a: Transaction variable that returns negative if greater.
	@param b: Transaction variable that returns positive if greater.
	@return int: Results from comparison.
	*/
	if (a.id < b.id)
	{
		return -1;
	}
	else if (a.id < b.id)
	{
		return 1;
	}
	else
	{
		CompareDates(a.d, b.d);
	}
}
void insert_transaction(TransactionArray *transArr, int id, int account, char date[], char type, double amount)
{
	/*
	Designed to take the parameters and insert them into a TransactionsArray

	@param *transArr: Pointer to TransactionsArray passed
	@param id: Int variable to be passed into *transArr
	@param account: Int to be passed into *transArr
	@param date[]: Char array to be passed into *transArr
	@param type: Char variable to be passed into *transArr
	@param amount: Double variable to be passed into *transArr
	@return void: None
	*/
	strcpy((*transArr).array[(*transArr).count].date, date);
	(*transArr).array[(*transArr).count].id = id;
	(*transArr).array[(*transArr).count].d.month = atoi(strtok(date, "/"));
	(*transArr).array[(*transArr).count].d.day = atoi(strtok(NULL, "/"));
	(*transArr).array[(*transArr).count].d.year = atoi(strtok(NULL, "/"));
	(*transArr).array[(*transArr).count].account = account;
	(*transArr).array[(*transArr).count].type = type;
	(*transArr).array[(*transArr).count].amount = amount;
	(*transArr).count++;
}
void read_transactions(char file_name[], TransactionArray *transArr)
{
	/*
	Designed to read the contents of accounts.txt and store them into a TransactionsArray if the file
	has yet to be read.

	@param file_name[]: Char array that contains path of file to be opened
	@param *transArr: Pointer to TransactionsArray designed to contain the contents of trans.txt
	*/

	char a[200];
	char date[10];
	char type[2];
	int account;
	int id;
	double amount;

	int month;
	int day;
	int year;

	trans_tag();

	if (trans_read == false)
	{
		FILE *in_file = fopen(file_name, "r");
		if (in_file != NULL)
		{
			while (fgets(a, 200, in_file) != NULL)
			{
				a[strlen(a) - 1] = '\0';
				id = atoi(strtok(a, ","));
				account = atoi(strtok(NULL, ","));
				strcpy(date, strtok(NULL, ","));
				strcpy(type, strtok(NULL, ","));
				amount = atof(strtok(NULL, ","));
				insert_transaction(transArr, id, account, date, type[0], amount);
			}
			fclose(in_file);
		}
		else
		{
			printf("Error: file not found.\n");
		}
		trans_read = true;
	}
	else
	{
		printf("");
	}
}
void swap_transactions(TransactionArray *transArr, int i, int j)
{
	/*
	Designed to swap the transaction information between one account and another account

	@param *acctArr: Pointer to TransactionArray with transaction information
	@param i: Int variable that represents a transaction
	@param j: Int variable that represents a transaction
	@return void: None
	*/
	Transactions hold;

	hold.id = (*transArr).array[j].id;
	hold.account = (*transArr).array[j].account;
	strcpy(hold.date, (*transArr).array[j].date);
	hold.type = (*transArr).array[j].type;
	hold.amount = (*transArr).array[j].amount;


	(*transArr).array[j].id = (*transArr).array[i].id;
	(*transArr).array[j].account = (*transArr).array[i].account;
	strcpy((*transArr).array[j].date, (*transArr).array[i].date);
	(*transArr).array[j].type = (*transArr).array[i].type;
	(*transArr).array[j].amount = (*transArr).array[i].amount;

	(*transArr).array[i].id = hold.id;
	(*transArr).array[i].account = hold.account;
	strcpy((*transArr).array[i].date, hold.date);
	(*transArr).array[i].type = hold.type;
	(*transArr).array[i].amount = hold.amount;
}
void sort_transactions(TransactionArray *transArr)
{
	/*
	Designed to sort the transaction information by account ID.

	@param *transArr: Pointer to AccountArray with transaction information
	@return void: None
	*/
	int i, j;

	printf("TID\tID\tDate\t\tType\tBalance\n");
	printf("---\t--\t----------\t-\t------\n");

	for (i = 0; i < LENGTH - 1; i++)
	{
		for (j = LENGTH - 1; j > i; j--)
		{
			if ((*transArr).array[j].account < (*transArr).array[i].account)
			{
				swap_transactions(transArr, i, j);
			}
		}
	}
}
int find_first_transaction(TransactionArray transArr, int acctNo)
{
	/*
	Designed to return the ID of the requested transaction of account number

	@param transArr: TransactionArray which contains the Transaction Information
	@param acctNo: Int array which contains name of requested owner
	@return int: ID of owner if present.
	*/
	int i;
	for (i = 0; i < transArr.count; i++)
	{
		if (transArr.array[i].account == acctNo)
		{
			print_transaction(transArr.array[i]);
		}
	}
	return i;
	return -1;
}
void sort_transactions_id(TransactionArray *transArr)
{
	/*
	Designed to sort the transaction information by account ID.

	@param *transArr: Pointer to TransactionArray with transaction information
	@return void: None
	*/
	for (int i = -1; i < LENGTH - 1; i++)
	{
		for (int j = LENGTH; j > i; j--)
		{
			if ((*transArr).array[j].id < (*transArr).array[j - 1].id)
			{
				swap_transactions(transArr, j, j);
			}
		}
	}
}
void save_transactions(TransactionArray transArr, char fileName[])
{
	/*
	Designed to store the adjusted transaction information

	@param transArr: TransactionArray for information to be stored into file
	@param fileName[]: Char array to contain the path of the file.
	@return void: None
	*/
	printf("\n %s \n", fileName);
	FILE *out_file = fopen(fileName, "w");
	int i;
	if (out_file != NULL)
	{
		for (i = 0; i < transArr.count; i++)
		{
			fprintf(out_file, "%d, %d, %s, %d, %lf \n",
				transArr.array[i].id, transArr.array[i].account, transArr.array[i].date, transArr.array[i].type, transArr.array[i].amount);
		}
		fclose(out_file);
	}
}
//Accounts and Transactions
void reconcile(AccountArray *acctArr, TransactionArray *transArr)
{
	/*
	Designed to update the information based off both the Account and Transaction Information

	@param *acctArr: Pointer to AccountArray where Account Information is stored
	@param *transArr: Pointer to TransactionArray where Transaction Information is stored
	@return void: None

	*/
	// Indices for acctArr and transArr, and counter
	int acctIdx = 0, transIdx = 0, count = 0;
	double balance = 0.0;	// Running balance for an account
	double interest = 0.0;	// Interest calculated for an account
	char date[20];			// To get date from user
	char date2[20];			// To copy date and insert into transArr because strtok damages strings

							// Get today's date from user
	printf("Enter date (m/d/yyyy): ");
	scanf("%s", date);

	// acctIdx starts at 0 and ends at count-1
	while (acctIdx < (*acctArr).count)
	{
		// Get balance from account
		balance = (*acctArr).array[acctIdx].balance;
		// Process transactions for this account
		while ((*acctArr).array[acctIdx].id == (*transArr).array[transIdx].account)
		{
			// Process a deposit
			if ((*transArr).array[transIdx].type == 'd')
				balance += (*transArr).array[transIdx].amount;
			// Process a withdrawl
			else if ((*transArr).array[transIdx].type == 'w')
				balance -= (*transArr).array[transIdx].amount;
			// If account has an overdraft - charge fee
			if (balance < 0.0)
			{
				// Make a copy of today's date
				strcpy(date2, date);
				// Insert overdraft fee into transactions
				insert_transaction(transArr, (*transArr).count + 1, (*acctArr).array[acctIdx].id,
					date2, 'o', OVERDRAFT_CHARGE);
				// Deduct overdraft from balance
				balance -= OVERDRAFT_CHARGE;
			}
			// Go to next transaction
			transIdx++;
			// Record that an account update has occurred
			count++;
			// If last transaction in array has been processed - break loop
			if (transIdx >= (*transArr).count)
				break;
		}
		// If an update occurred for this account
		if (count > 0)
		{
			// If balance is > zero - pay interest to account
			if (balance > 0.0)
			{
				// Calc interest
				interest = round_dbl(balance*(INTEREST_RATE / 12.0), 2);
				// Make a copy of today's date
				strcpy(date2, date);
				// Insert interest payment into transactions
				insert_transaction(transArr, (*transArr).count + 1,
					(*acctArr).array[acctIdx].id, date2, 'i', interest);
				// Update balance in account
				(*acctArr).array[acctIdx].balance = round_dbl(balance + interest, 2);
			}
			// No updates
			else
				// Update balance in account
				(*acctArr).array[acctIdx].balance = round_dbl(balance, 2);
		}
		// Go to next account
		acctIdx++;
		// Reset count of updates for account to zero
		count = 0;
	}
	// Sort transactions by account and date
	sort_transactions(transArr);
}
void print_account_owner(AccountArray acctArr, TransactionArray transArr, char owner[])
{
	/*
	Designed to print the account of the requested owner

	@param acctArr: AccountArray that contains the Account Information
	@param transArr: TransactionArray that contains the Transaction Information
	@param owner[]: Char array which contains the name of the owner
	@return void: None
	*/
	int i;
	for (i = 0; i<acctArr.count; i++)
		if (strcmp(acctArr.array[i].owner, owner) == 0)
			print_account(acctArr.array[i]);
	print_transaction(transArr.array[i]);

	printf("No such account");
}
void print_account_id(AccountArray acctArr, TransactionArray transArr, int acctNo)
{
	/*
	Designed to print the account of the requested ID

	@param acctArr: AccountArray that contains the Account Information
	@param transArr: TransactionArray that contains the Transaction Information
	@param acctNo: Char array which contains the name of the owner
	@return void: None
	*/
	int begin = 0;
	int end = acctArr.count - 1;
	int mid;
	printf("id = %d\n", acctNo);

	while (begin <= end)
	{
		mid = (end + begin) / 2;
		if (acctNo < acctArr.array[mid].id)
		{
			end = mid - 1;
		}
		else if (acctNo > acctArr.array[mid].id)
		{
			begin = mid + 1;
		}
		else if (acctNo == acctArr.array[mid].id)
		{
			print_account(acctArr.array[mid]);
			print_transaction(transArr.array[mid]);
		}

	}
	printf("The id you want is not here");
}
void print_account_transactions(AccountArray acctArr, TransactionArray transArr, int acctIdx)
{
	/*
	Designed to print information regarding both transactions and accounts

	@param acctArr: AccountArray with Account Information
	@param transArr: TransactionArray with Transaction Information
	@param acctIdx: Int variable with first index of transaction
	@return void: None
	*/
	char date[20];
	print_account(acctArr.array[acctIdx]);
	int transIdx = find_first_transaction(transArr, acctArr.array[acctIdx].id);
	if (transIdx >= 0)
	{
		printf("ID    Date    Type    Amount\n");
		while (transArr.array[transIdx].account == acctArr.array[acctIdx].id)
		{
			PrintDate(transArr.array[transIdx].d, date);
			printf("  %4d %15s %c %10.2f\n", transArr.array[transIdx].id, date, transArr.array[transIdx].type, transArr.array[transIdx].amount);
			transIdx++;
			if (transIdx >= transArr.count)
			{
				break;
			}
		}
	}
	else
		printf("No transactions found.\n");
}
void print_summary_report(AccountArray acctArr, TransactionArray transArr)
{
	/*
	Designed to print a full summary report of the given accounts.

	@param acctArr: AccountArray containing Account Information
	@param transArr: TransactionArray containing Transaction Information
	@return void: None
	*/
	int acctIdx = 0;
	// Print header
	printf("Account Summary Report\n");
	printf("    ID                Owner     Balance\n");
	// Loop tp print account
	for (acctIdx = 0; acctIdx<acctArr.count; acctIdx++)
	{
		printf("%6d %20s %10.2f\n",
			acctArr.array[acctIdx].id,
			acctArr.array[acctIdx].owner,
			acctArr.array[acctIdx].balance);
	}
}
void print_detail_report(AccountArray acctArr, TransactionArray transArr)
{
	/*
	Designed to print a detailed report regarding Accounts and Transactions

	@param acctArr: AccountArray which contains Account Information
	@param transArr: TransactionArray which contains Transaction Information
	*/
	int acctIdx = 0;
	printf("Account Detail Report\n");
	// Loop to print account
	for (acctIdx = 0; acctIdx<acctArr.count; acctIdx++)
	{
		print_account_transactions(acctArr, transArr, acctIdx);
		printf("\n");
	}
}

