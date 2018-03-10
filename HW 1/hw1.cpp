#include <iostream>
using namespace std;

/**
* @Author: Darrian Johnson
* @email: dmj0018@auburn.edu
* 1-20-2018
* hw1.cpp
* 
* Compiled using emacs and g++ compilier on Linux machine in Engineering Lab via Putty from Windows 
* (syllabus method).
*/


int main()
{
   const double MY_FRAC = 0.001;
   double mousesweet;
   double mouseweight;
   double humanweight;
   double humansweet;
   double sodapop;

   cout << "What is the amount of artificial sweetener needed to kill a mouse: \n";
   cin >> mousesweet;

   cout << "\nWhat is the weight of the mouse: ";
   cin >> mouseweight;

   cout << "\nWhat is the weight of the dieter: ";
   cin >> humanweight;

   humansweet = (mousesweet / mouseweight) * humanweight;
   sodapop = (humansweet / MY_FRAC);

   cout << "\nYou can drink " << sodapop << " diet soda without dying as a result." << endl;
   
   system("pause");
   return 0;
}
