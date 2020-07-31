/**
CIS 1057 Final Project
ProjectCherry.c
Purpose: Manages Bank Accounts and Transactions

@author Tyrel Cherry
@version 1.1 08/25/2018
*/

#define _CRT_SECURE_NO_WARNINGS
#include "BankingInfo.h"

int main(void)
{
	/**
	Main function of ProjectCherry.c

	@param None: void
	@return None: void
	*/
	char request = '\0';
	int id;
	char name[15];
	AccountArray aa;
	TransactionArray ta;
	aa.count = 0;
	ta.count = 0;

	welcome();
	while (request != '0')
	{
		menu();
		scanf(" %c", &request);
		switch (request)
		{
		case '1':
			//Accounts
			printf("\nContents of accounts.txt\n\n");
			read_accounts("accounts.txt", &aa);
			print_account_array(aa);
			printf("\nSORTED...\n\n");
			sort_accounts(&aa);
			print_account_array(aa);
			//Transactions
			printf("\nContents of trans.txt\n\n");
			read_transactions("trans.txt", &ta);
			print_transaction_array(ta);
			printf("\n SORTED...\n\n");
			sort_transactions(&ta);
			print_transaction_array(ta);
			break;
		case '2':
			read_accounts("accounts.txt", &aa);
			read_transactions("trans.txt", &ta);
			reconcile(&aa, &ta);
			printf("Reconciled!\n");
			break;
		case '3':
			read_accounts("accounts.txt", &aa);
			sort_accounts(&aa);
			printf("Which ID are you looking for? \n");
			scanf("%d", &id);
			search_account_id(aa, id);
			read_transactions("trans.txt", &ta);
			find_first_transaction(ta, id);
			break;
		case '4':
			read_accounts("accounts.txt", &aa);
			sort_accounts(&aa);
			printf("Whose ID are you looking for? \n");
			scanf("%s", &name);
			search_account_owner(aa, name);
			printf("Input the first integer you see\n");
			scanf("%d", &id);
			read_transactions("trans.txt", &ta);
			find_first_transaction(ta, id);
			break;
		case '5':
			read_accounts("accounts.txt", &aa);
			read_transactions("trans.txt", &ta);
			print_summary_report(aa, ta);
			break;
		case '6':
			read_accounts("accounts.txt", &aa);
			read_transactions("trans.txt", &ta);
			print_detail_report(aa, ta);
			break;
		case '7':
			read_accounts("accounts.txt", &aa);
			print_account_array(aa);
			break;
		case '8':
			read_transactions("trans.txt", &ta);
			print_transaction_array(ta);
			break;
		case '9':
			read_accounts("accounts.txt", &aa);
			read_transactions("trans.txt", &ta);
			save_accounts(aa, "accounts.txt");
			break;
		}
	}
	return 0;
}


