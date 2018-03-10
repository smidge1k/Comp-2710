# include <fstream>
# include <iostream>
# include <cstdlib> //for exit()
# include <string>
# include <cassert>
# include <stdio.h>
# include <termios.h>
# include <unistd.h>
# include <ctype.h>
using namespace std; 

/**
 * Author: Darrian Johnson
 * email: dmj0018@auburn.edu
 * 2-25-18
 * 
 * hw4.cpp
 * Compiled using emacs and g++ compiler on Linux machine in Engineering lab via Putty from Windows.
 * (Syllabus Method)
 */

//maximum size of arrays.
const int MAX_SIZE = 100;

//functions to be called.
int readFile(int inputArray[], ifstream& instream);
int sort(int inputArray1[], int inputArray1_size, int inputArray2[], int inputArray2_size, int outputArray[]);
void writefile(int outputArray[], int outputArray_size, string name);

int readfile(int inputArray[], ifstream& instream) {
  if (instream.fail()) {
        cout << "Input file opening failed." << endl;
        return -1;
    }
    int i = 0;
    instream >> inputArray[i];
    while (! instream.eof()) {
        //cout << inputArray[i] << endl;
        i++;
        instream >> inputArray[i];
    }
    return i;
}
// sorts both arrays into the final order
int sort(int inputArray1[], int inputArray1_size, int inputArray2[], int inputArray2_size, int outputArray[]) {
     int i = 0;
     int j = 0;
     int k = 0;
     int n = 0;
 while (i < inputArray1_size && j < inputArray2_size) {
         if (inputArray1[i] <= inputArray2[j]) {
             outputArray[k] = inputArray1[i];
             i++;
         }
         else {
             outputArray[k] = inputArray2[j];
             j++;
         }
         k++;
     }
     if ( i < inputArray1_size ) {
         for ( n = i; n < inputArray1_size; n++) {
             outputArray[k] = inputArray1[n];
             k++;
         }
     }
     else {
        for ( n = j; n < inputArray2_size; n++) {
             outputArray[k] = inputArray2[n];
             k++;
        }
     }
     return k;
}
// writes sorted file to new outputt
void writefile(int outputArray[], int outputArray_size, string name) {
    ofstream output;
    output.open(name.c_str());
    for (int i = 0; i < outputArray_size; i++) {
        output << outputArray[i] << "\n";
    }
    output.close();
}
//Get character method for press any key
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
//Press any key
void press_any_key(void) {
  char ch;
  cout << "Press any key to continue...";
  ch = mygetch();
  if (ch == 0 || ch == 224) mygetch();
}
//tests if file inputs are read/found
void test_readfile(void) {
    int test[MAX_SIZE];

    cout << "*** Unit Test Cases ***\n";
    cout << "Unit Test Case 1: readfile(int inputArray[], ifstream& instream)\n";
    cout << "\tCase 1.1: a text file that can be found (input0.txt)\n";

    ifstream input;
    input.open("input0.txt");
    int a = readfile(test, input);
    assert((0 <= a));
    cout << "\tCase 1.1 passed.\n";
    input.close();
    cout << "\tCase 1.2: a text file that can be found (input3.txt)\n";
    string z = "input3.txt";
    input.open(z.c_str());
    int b = readfile(test, input);
    assert(0 <= b);
    cout << "\tCase 1.2 passed.\n";
    input.close();
    cout << "\tCase 1.3: file with a large ammount of inputs (input4.txt)\n";
    input.open("input4.txt");
    int c = readfile(test, input);
    assert(100 == c);
    cout << "\tCase 1.3 passed.\n\n";
    input.close();
    press_any_key(); //Press Any Key To Continue
    cout << endl;

}
//tests if read files are sorted
void test_sort(void) {
    int s1[10];
    int s2[] = {0, 1, 2, 6};
    int s3[] = {20, 15,12, 3, 8, 7};
    int s4[] = {7,6,5, 4, 3, 2, -1};
    int s6[MAX_SIZE];
    for (int l = 0; l < MAX_SIZE; l++) {
        s6[l] = rand() % 100;
    }
    int s5[MAX_SIZE];
    cout << "Unit Test Case 2: sort(int inputArray1[], int inputArray1_size, ";
    cout << "int inputArray2[], int inputArray2_size, int outputArray[]) \n";
    cout << "\tCase 2.1: sorting with an empty array and a filled one(s1, 0, s2, 4, s5)\n";
    assert(4 == sort(s1, 0, s2, 4, s5));
    cout << "\tCase 2.1 passed.\n";
    cout << "\tCase 2.2: sorting with a unsorted array and reverse order array(s3, 5, s4, 5, s5)\n";
    assert(11 == sort(s3, 6, s4, 5, s5));
    cout << "\tCase 2.2 passed.\n";
    cout << "\tCase 2.3: sorting with a large unsorted array (s4, 5, s6, 99, s5)\n";
    assert(106 == sort(s4, 7, s6, 99, s5));
    cout << "\tCase 2.3 passed.\n\n";
    press_any_key(); //Press Any Key To Continue
    cout << endl;
}
// main fuction
int main() {
    int arraySize1 = 0;
    int arraySize2 = 0;
    int A1[MAX_SIZE];
    int A2[MAX_SIZE];

    int oa[MAX_SIZE];

    string file1, file2, ofile;
    test_readfile();
    test_sort();


    cout << "*** Welcome to Darrian's sorting program ***\n";
    cout << "Enter the first input file name: ";
    cin >> file1;
    ifstream input1;
    input1.open(file1.c_str());
    arraySize1 = readfile(A1, input1);
    if (arraySize1 < 0) {
        exit(1);
    }
    cout << "\nThe list of " << arraySize1 << " numbers in file ";
    cout << file1 << " is: \n";
    for (int i = 0; i < arraySize1; i++) {
        cout << A1[i] << "\n";

    }
    input1.close();
    cout << "\nEnter the second input file name: ";
    cin >> file2;
    ifstream input2;
    input2.open(file2.c_str());
    arraySize2 = readfile(A2, input2);
    if (arraySize2 < 0) {
        exit(1);
    }
    cout << "\nThe list of " << arraySize2 << " numbers in file ";
    cout << file2 << " is: \n";
    for (int j = 0; j < arraySize2; j++) {
        cout << A2[j] << "\n";
    }
    input2.close();
    int outSize = sort(A1, arraySize1, A2, arraySize2, oa);
    cout << "\nThe sorted list of " << outSize << " numbers is: ";
    for (int k = 0; k < outSize; k++) {
        cout << oa[k] << " ";
    }
    cout << "\nEnter the output file name: ";
    cin >> ofile;
    writefile(oa, outSize, ofile);
    cout << "\n*** Please check the new file - " << ofile << " ***\n";
    cout << "*** Goodbye. ***" << endl;



    input1.close();
    input2.close();
    return 0;
}

