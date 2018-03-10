# include <iostream>
# include <cstdlib>
# include <ctime>
#include <cassert>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
using namespace std;

/**
* @Author: Darrian Johnson
* @email: dmj0018@auburn.edu
* 2-19-2018
* hw3.cpp
*
* Compiled using emacs and g++ compiler on Linux machine in Engineering lab via putty from Windows.
* (syllabus method).
*/

bool firstshot = true;
bool Aaron, Bob, Charlie = true;
const double AARON_AVG = 33;
const double BOB_AVG = 50;
const double NUM_DUELS = 10000;
const double PERCENT = 100; 

  //////////////////////
 //Function prototypes/
//////////////////////
/* Input: A_alive indicates whether Aaron is alive
 *         B_alive indicates whether Bob is alive
 *         C_alive indicates whether Charlie is alive
 *  Return: true if at least two are alive
 *          otherwise return false
 */
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive) {
       return A_alive && B_alive || A_alive && C_alive || B_alive && C_alive; 
   }

/*  strategy 1: Use call by reference
 *   Input: B_alive indicates whether Bob is alive or dead
 *         C_alive indicates whether Charlie is alive or dead
 *  Return: Change B_alive into false if Bob is killed.
 *         Change C_alive into false if Charlie is killed.
*/
void Aaron_shoots1(bool& B_alive, bool& C_alive) {
    double shoot;
    shoot = rand() % 100;
    if (shoot <= AARON_AVG) {
        if (C_alive) {
            C_alive = false;
            cout << "Charlie is dead.\n";
        } 
        else {
            B_alive = false;  
            cout  << "Bob is dead.\n";
        }
    }
        else {
            cout << "Aaron missed.\n";
        }
} 

/*  Call by reference
 *   Input: A_alive indicates whether Aaron is alive or dead
 *         C_alive indicates whether Charlie is alive or dead
 *  Return: Change A_alive into false if Aaron is killed.
 *         Change C_alive into false if Charlie is killed.
*/
void Bob_shoots(bool& A_alive, bool& C_alive) {
    double shoot;
    shoot = rand() % 100;
    if (shoot <= BOB_AVG) {
        if (C_alive) {
            C_alive = false;
            cout << "Charlie is dead.\n";
        }
        else {
            A_alive = false;
            cout << "Aaron is dead.\n";
        }
    }
    else {
        cout << "Bob missed.\n";
    }    
}

/*  Call by reference
 *   Input: A_alive indicates whether Aaron is alive or dead
 *         B_alive indicates whether Bob is alive or dead
 *  Return: Change A_alive into false if Aaron is killed.
 *         Change B_alive into false if Bob is killed.
*/
void Charlie_shoots(bool& A_alive, bool& B_alive) {
    if (B_alive) {
        B_alive = false;
        cout << "Bob is dead.\n";
    }
    else {
        A_alive = false;
        cout << "Aaron is dead.\n";
    }
}

/*  strategy 2: Use call by reference
 *   Input: B_alive indicates whether Bob is alive or dead
 *         C_alive indicates whether Charlie is alive or dead
 *  Return: Change B_alive into false if Bob is killed.
 *         Change C_alive into false if Charlie is killed.
*/
void Aaron_shoots2(bool& B_alive, bool& C_alive) {
    int shoot;
    if(firstshot) {
        firstshot = false;
        cout << "Both Bob and Charlie are alive.\n";
        return;
    }
    shoot = rand() % 100;
    if (shoot <= AARON_AVG) {
        if (C_alive) {
          C_alive = false;
          cout << "Charlie is dead.\n";
        } 
        else {
            B_alive = false; 
            cout << "Bob is dead.\n"; 
        }
    }
    else {
        cout << "Aaron missed.\n";
    }
}

/*
 *
 * Get character method for press any key
 *
 */
int mygetch(void);
void press_any_key(void);

int mygetch ( void ) 
{
  int ch;
  struct termios oldt, newt;
  
  tcgetattr ( STDIN_FILENO, &oldt );
  newt = oldt;
  newt.c_lflag &= ~( ICANON | ECHO );
  tcsetattr ( STDIN_FILENO, TCSANOW, &newt );
  ch = getchar();
  tcsetattr ( STDIN_FILENO, TCSANOW, &oldt );
  
  return ch;
} 

/*
 *
 * Press any key
 * 
 */
void press_any_key(void) {
  char ch;
  cout << "Press any key to continue...";
  ch = mygetch();
  if (ch == 0 || ch == 224) mygetch();
}
  

/* Implementation of the test driver for at_least_two_alive() */
void test_at_least_two_alive(void) {
cout << "Unit Testing 1: Function – at_least_two_alive()\n";
cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
assert(true == at_least_two_alive(true, true, true));
cout << "\tCase passed ...\n";
cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
assert(true == at_least_two_alive(false, true, true));
 cout << "\tCase passed ...\n";
cout << "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
assert(true == at_least_two_alive(true, false, true));
 cout << "\tCase passed ...\n";
cout << "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
assert(true == at_least_two_alive(true, true, false));
 cout <<"\tCase passed ...\n";
cout << "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
assert(false == at_least_two_alive(false, false, true));
 cout << "\tCase passed ...\n";
cout << "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
assert(false == at_least_two_alive(false, true, false));
 cout << "\tCase passed ...\n";
cout << "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
assert(false == at_least_two_alive(true, false, false));
 cout << "\tCase passed ...\n";
cout << "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
assert(false == at_least_two_alive(false, false, false));
cout << "\tCase passed ...\n";
}

/* Implementation of the test driver for Aaron_shoots1() */
void test_Aaron_shoots1() {
cout << "\nUnit Testing 2: Function Aaraon_shoots1(Bob_Alive, Charlie_alive)\n";
 cout << "\tCase 1: Bob alive, Charlie alive\n";
Bob = true;
Charlie = true;
cout << "\t\tAaron is shooting at Charlie\n\t\t";
Aaron_shoots1(Bob, Charlie);
 cout << "\n\tCase 2: Bob dead, Charlie alive\n";
Bob = false;
Charlie = true;
cout << "\t\tAaron is shooting at Bob\n\t\t";
Aaron_shoots1(Bob, Charlie);
 cout << "\n\tCase 3: Bob alive, Charlie alive\n";
Bob = true;
Charlie = true;
cout << "\t\tAaron is shooting at Bob\n\t\t";
Aaron_shoots1(Bob, Charlie);
} 

/* Implementation of the test driver for Bob_shoots() */
void test_Bob_shoots() {
cout << "\nUnit Testing 3: Function Bob_shoots(Aaron_Alive, Charlie_alive)\n";
 cout << "\tCase 1: Aaron alive, Charlie alive\n";
Aaron = true;
Charlie = true;
cout << "\t\tBob is shooting at Charlie\n\t\t";
Bob_shoots(Aaron, Charlie);
 cout << "\n\tCase 2: Aaron dead, Charlie alive\n";
Aaron = false;
Charlie = true;
cout << "\t\tBob is shooting at Charlie\n\t\t";
Bob_shoots(Bob, Charlie);
 cout << "\n\tCase 3: Aaron alive, Charlie dead\n";
Aaron = true;
Charlie = false;
cout << "\t\tBob is shooting at Aaron\n\t\t";
Bob_shoots(Bob, Charlie);
} 

/* Implementation of the test driver for Charlie_shoots() */
void test_Charlie_shoots() {
cout << "\nUnit Testing 4: Function Charlie_shoots(Aaron_Alive, Bob_alive)\n";
 cout << "\tCase 1: Aaron alive, Bob alive\n";
Aaron = true;
Bob = true;
cout << "\t\tCharlie is shooting at Bob\n\t\t";
Charlie_shoots(Aaron, Bob);
 cout << "\n\tCase 2: Aaron dead, Bob alive\n";
Aaron = false;
Bob = true;
cout << "\t\tCharlie is shooting at Bob\n\t\t";
Charlie_shoots(Aaron, Bob);
 cout << "\n\tCase 3: Aaron alive, Bob dead\n";
Aaron = true;
Bob = false;
cout << "\t\tCharlie is shooting at Aaron\n\t\t";
Charlie_shoots(Aaron, Bob);
}

/* Implementation of the test driver for Aaron_shoots2() */
void test_Aaron_shoots2() {
cout << "\nUnit Testing 5: Function Aaraon_shoots2(Bob_Alive, Charlie_alive)\n";
 cout << "\tCase 1: Bob alive, Charlie alive\n";
Bob = true;
Charlie = true;
cout << "\t\tAaron intentionally misses his first shot\n\t\t";
Aaron_shoots2(Bob, Charlie);
 cout << "\n\tCase 2: Bob dead, Charlie alive\n";
Bob = false;
Charlie = true;
cout << "\t\tAaron is shooting at Charlie\n\t\t";
Aaron_shoots2(Bob, Charlie);
 cout << "\n\tCase 3: Bob alive, Charlie dead\n";
Bob = true;
Charlie = false;
cout << "\t\tAaron is shooting at Bob\n\t\t";
Aaron_shoots2(Bob, Charlie);
} 

/////////////////
//Main Function//
/////////////////
int main() {
    int awins = 0, bwins = 0, cwins = 0;
    srand(time(0)); 
    
    cout << "*** Welcome to Darrian's Duel Simulator ***\n";
    test_at_least_two_alive();
     press_any_key(); //Press Any Key To Continue
     cout << endl;
    test_Aaron_shoots1();
     press_any_key(); //Press Any Key To Continue
     cout << endl;
    test_Bob_shoots();
     press_any_key(); //Press Any Key To Continue
     cout << endl;
    test_Charlie_shoots();
     press_any_key(); //Press Any Key To Continue
     cout << endl;
    test_Aaron_shoots2();
     press_any_key(); //Press Any Key To Continue
     cout << endl;
  
    cout << "\nReady to test strategy 1 (run 10000 times):\n";
        press_any_key(); //Press Any Key To Continue
       
    for (int i = 0; i < NUM_DUELS; i++) {
        while (at_least_two_alive(Aaron, Bob, Charlie)) {
            if (Aaron) {
                Aaron_shoots1(Bob, Charlie);
            }
            if (Bob) {
                Bob_shoots(Aaron, Charlie);
            }
            if (Charlie) {
                Charlie_shoots(Aaron, Bob);  
             } 
        } 
         if (Aaron) {
                awins++;
            }
         if (Bob) {
                bwins++;
            } 
         if (Charlie) {
            cwins++;
        }
        Aaron = true;
        Bob = true;
        Charlie = true;
    }
     cout << "\nAaron won " << awins << " / 10000 duels or " << (awins / NUM_DUELS) * PERCENT << "%";
     cout << "\nBob won " << bwins << " / 10000 duels or " << (bwins / NUM_DUELS) * PERCENT << "%";
     cout << "\nCharlie won " << cwins << " / 10000 duels or " << (cwins / NUM_DUELS) * PERCENT << "%" << endl;
    
     cout << "\nReady to test strategy 2 (run 10000 times):\n";
     press_any_key();

     double awins2, bwins2, cwins2 = 0;

     for (int j = 0; j < NUM_DUELS; j++) {
       while (at_least_two_alive(Aaron, Bob, Charlie)) {
            if (Aaron) {
                Aaron_shoots2(Bob, Charlie);
            }
            if (Bob) {
                Bob_shoots(Aaron, Charlie);
            }
            if (Charlie) {
                Charlie_shoots(Aaron, Bob);  
             } 
        }
         if (Aaron) {
                awins2++;
                
            }
         if (Bob) {
                bwins2++;
            } 
         if (Charlie) {
            cwins2++;
        }
        Aaron = true;
        Bob = true;
        Charlie = true;
}        
    cout << "\nAaron won " << awins2 << " / 10000 duels or " << (awins2 / NUM_DUELS) * PERCENT << "%\n";
    cout << "Bob won " << bwins2 << " / 10000 duels or " << (bwins2 / NUM_DUELS) * PERCENT << "%\n";
    cout << "Charlie won " << cwins2 << " / 10000 duels or " << (cwins2 / NUM_DUELS) * PERCENT << "%" << endl;

    if (awins > awins2) {
        cout << "\nStrategy 1 is better than strategy 2.";
    }
    if (awins2 > awins) {
        cout << "\nStrategy 2 is better than strategy 1.";
    }
return 0;
}
/*⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠃⠙⠉⠙⠷⢻⣴⣤⡀ 
⠀⠀⠀⠀⠀⠀⡀⠄⠀⠠⢄⡀⠀⠀⠀⠀⠈⠺⣻⣢ 
⠀⠀⠀⠀⠀⡎⠀⢀⡄⠀⠀⠈⠆⠀⠀⠀⠀⠀⠘⠗⠆ 
⠀⠀⠀⠀⢀⠇⠀⠀⠀⠀⠀⢀⠖⠉⠀⠀⠉⠑⢢ 
⢀⠤⠤⢌⡮⣐⠤⠤⡤⠔⢹⠀⠀⠀⠴⠀⠀⠀⡇ 
⡜⡐⠈⠉⠗⣌⠀⢠⠊⢀⠄⠈⠢⣀⠀⠀⠀⣀⠜ 
⢃⢇⠀⠀⠀⠒⡓⡪⣈⣀⣀⠀⠑⠠⠉⠉⠉ 
⠈⢊⢖⡄⡀⠀⠀⠁⢉⣒⣑⠊⠛⠒⠤⡰⡀ 
⠀⠀⠁⠓⠫⢥⢲⡀⡈⠙⢿⣷⣆⠀⠀⡁⡇ 
⠀⠀⠀⠀⠀⠈⠐⠋⠬⠎⠿⠿⠤⢐⠕⠁ 
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠈⠉
LOOK MORTY,I TURNED MYSELF INTO A C++ FILE...
I'M C++ RIIIIIIIIIICCCCCCKKKKKK!
*/