#include <iostream>
using namespace std;

/**
* @Author: Darrian Johnson
* @email: dmj0018@auburn.edu
* 2-3-2018
* hw2.cpp
*
* Compiled using emacs and g++ compiler on Linux machine in Engineering lab via putty from Windows.
* (syllabus method).
*/

int main()
{
   double balance, yearRate, monthlyPay, rate, interest, principal;
   double total = 0.0;
   int month = 0;
	
   cout << "Loan Amount: ";
   cin >> balance;

   cout << "Interest Rate (% per year): ";
   cin >> yearRate;

   cout << "Monthly Payments: ";
   cin >> monthlyPay;

   cout.setf(ios::fixed); 
   cout.setf(ios::showpoint); 
   cout.precision(2);

   cout << "\n******************************************************";
   cout << "\n\t \tAmortization Table";
   cout << "\n******************************************************";
   cout << "\nMonth\tBalance\tPayment\tRate  Interest Principal" << endl;
   cout << "0\t$" << balance << " N/A\tN/A\tN/A\tN/A\n";
	
   rate = ((yearRate * 100) / 1200);
	
   while (balance > 0) {
      if (balance < monthlyPay) {
         interest = (balance * rate) / 100;
      	//cout<<rate<<endl;
         monthlyPay = balance * (1 + (rate/100));
         principal = balance;
         total += interest;
         balance = 0;
      }
      else {
         interest = (balance * rate) / 100;
         principal = monthlyPay - interest;
         total += interest;
         balance -= principal;	
      }
      if (principal < 0) {
         cout << "******************************************************\n";	
         return 0;
      }
   		
   	
      month++;
   			
      cout << month << "\t$" << balance << "\t$" << monthlyPay;
      cout << "\t" << rate << "\t$" << interest << "\t$" << principal << endl;
   }	
   cout << "******************************************************\n";
	

   cout << "\nIt takes " << month << " months to pay off the loan.\n";
   cout << "Total interest paid is: $" << total << endl;
   cout <<
     
      return 0;
}
