#ifndef PROJECTCHERRY

	#include <stdio.h>
	#include <math.h>
	#include <stdlib.h>
	#include <string.h>
	#include <stdbool.h>

	#define LENGTH 10
	#define OVERDRAFT_CHARGE 35
	#define INTEREST_RATE 12

	typedef struct DateInfo
	{
		int day;
		int month;
		int year;
	}Date;

	typedef struct AccountData
	{
		int id;
		char owner[15];
		double balance;
	}Account;

	typedef struct AccountInfo
	{
		Account array[50];
		int length;
		int count;
	}AccountArray;

	typedef struct TransactionData
	{
		Date d;
		int account;
		char date[11];
		int id;
		char type;
		double amount;
	}Transactions;

	typedef struct TransactionInfo
	{
		Transactions array[50];
		int length;
		int count;
	}TransactionArray;

	// Declared Prototypes
	// Part 2
	void welcome();
	void menu();
	void PrintDate(Date d, char s[]);
	int CompareDates(Date a, Date b);
	double round_dbl(double d, int i);

	// Part 3
	void print_account(Account acct);
	void print_account_array(AccountArray aa);
	void insert_account(AccountArray *acctArr, int id, char owner[], double balance);
	void read_accounts(char file_name[], AccountArray *acctArr);
	void swap_accounts(AccountArray *acctArr, int i, int j);
	void sort_accounts(AccountArray *acctArr);
	int search_account_id(AccountArray acctArr, int id);
	int search_account_owner(AccountArray acctArr, char owner[]);
	void save_accounts(AccountArray acctArr, char fileName[]);
	// Part 4
	void print_transaction(Transactions trans);
	int compare_transactions(Transactions a, Transactions b);
	void print_transaction_array(TransactionArray transArr);
	void insert_transaction(TransactionArray *transArr, int id, int account, char date[], char type, double amount);
	void read_transactions(char file_name[], TransactionArray *transArr);
	void swap_transactions(TransactionArray *transArr, int i, int j);
	void sort_transactions(TransactionArray *transArr);
	int find_first_transaction(TransactionArray transArr, int acctNo);
	void sort_transactions_id(TransactionArray *transArr);
	void save_transactions(TransactionArray transArr, char fileName[]);
	// Part 5
	void reconcile(AccountArray *acctArr, TransactionArray *transArr);
	void print_account_id(AccountArray acctArr, TransactionArray transArr, int acctNo);
	void print_account_owner(AccountArray acctArr, TransactionArray transArr, char owner[]);
	void print_account_transactions(AccountArray acctArr, TransactionArray transArr, int acctIdx);
	void print_summary_report(AccountArray acctArr, TransactionArray transArr);
	void print_detail_report(AccountArray acctArr, TransactionArray transArr);
	#define PROJECTCHERRY
#endif
