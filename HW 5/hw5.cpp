# include <iostream>
# include <cstring>
# include <assert.h>
# include <cstdlib>
using namespace std;

/**
 * Darrian Johnson 
 * COMP 2710 
 * 03-11-2018
 * hw5.cpp
 *
 *
 */


// Comment this line to enable production version of code!
#define UNIT_TESTING

/**
 * creates a trivia node structure containing information about a single trivia question
 * and a pointer pointing to the other TriviaNode.
 **/
struct triviaNode {
    string question,answer;
    int points;
    triviaNode *next;
};


class triviaList
  {
     public:
     int count = 0;
    triviaNode *head, *root;
    trivialist()
    {
      head = NULL;
      root = NULL;
    }
  };	

//initializes the Trivia questions via hard code.
void initializeList(triviaList &tL) {
    triviaNode *q1 = new triviaNode;
    triviaNode *q2 = new triviaNode;
    triviaNode *q3 = new triviaNode;

//Trivia Question 1
    q1 -> question = "How long was the shortest war on record? (Hint: how many minutes)";
    q1 -> answer = "38";
    q1 -> points = 100;
    q1 -> next = q2;

//Trivia Question 2
    q2 -> question = "What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)";
    q2 -> answer = "Bank of Italy";
    q2 -> points = 50;
    q2 -> next = q3;

//Trivia Question 3
    q3 -> question = "What is the best-selling video game of all time? (Hint: Minecraft or Tetris)";
    q3 -> answer = "Tetris";
    q3 -> points = 20;
    q3 -> next = NULL;     

    tL.head = q1;
    tL.root = q3;
    tL.count += 3;
}

//this function asks the player a question 
int askQuestion(triviaList tL, int i) {
    triviaNode *q = tL.head;

 //parameter checking 

    if (i == 0) { // checks if the number of trivia questions is equal to zero
        cout << "\nWarning - The number of trivia to be asked must equal to or be larger than 1.";
        return 0;
    }
    if (i > tL.count) { //checks if the number of trivia questions exceeds the number of questions in the list
        cout << "\nWarning - There are only " << tL.count << " trivia in the list";
        i = tL.count;
        
    }
    string ans;
    int bonus = 0;

    for (int j = 0; j < i; j++) {
        cout << "\nQuestion: " << q -> question << "\nAnswer: ";
        getline(cin, ans);

        if (q -> answer == ans) {
            cout << "Your answer is correct. You receive " << q -> points << " points.";
            bonus += q -> points; //adds points to total point value   
        }    
        else {
            cout << "Your answer is wrong. The correct answer is: " << q -> answer;
        }
        cout << "\nYour Total Points: " << bonus << endl; 
        q = q -> next;
    }
    return 0; 
}


// this function prompts the user to create their own question, answer, and point value
void addTrivia(triviaList &tL){
    string response;
 do {
    tL.count++; //increases the count of questions
    triviaNode *temp = new triviaNode;
    //prompts the user to enter a question
    cout << "Enter a question: ";
    getline(cin, temp -> question);
    //prompts the user to create an answer to their question
    cout << "Enter an answer: ";
    getline(cin, temp -> answer);
    //the user creates a point value to be awarded to the player
    cout << "Enter award points: ";
    cin >> temp -> points;
   //prompts the user to continue
    cout << "Continue? (Yes/No): ";
    getline(cin.ignore(), response);
    
    //adds new trivia to list
        tL.root -> next = temp;
        tL.root = temp;
        
 }
   while (response.find("No") != string :: npos);
}


void test_initializeList()
{
	// Initialize test fixtures
	triviaList tL;


    triviaNode *q1 = new triviaNode;
    //triviaNode *q2 = new triviaNode;
    //triviaNode *q3 = new triviaNode;


	cout << "\nFunction to test: void hardCodedTriviaList(triviaList& tL)\n";
	cout << "\tUnit Test Case 1: Check if initialization of 3 trivia questions works properly\n";
	initializeList(tL);

    tL.head = new triviaNode;
	assert(tL.count == 3);
	// assertions for first question
	assert(tL.head -> question == "How long was the shortest war on record? (Hint: how many minutes?)");
	//assert( -> answer == "38");
	//assert(q1 -> points == 100);
	// assertions for second question
	//assert(q1 -> next -> question == "What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany?)");
	//assert(q1 -> next -> answer == "Bank of Italy");
	//assert(q1 -> next -> points == 50);
	// assertions for third question
	//assert(q1 -> next -> next -> question == "What is the best-selling video game of all time? (Hint: Minecraft or Tetris)");
	//assert(q1 -> next -> next -> answer == "Tetris");
	//assert(q1 -> next -> next -> points == 20);
	//assert(q1 -> next -> next -> next == NULL);

	cout << "\tCase 1 passed...\n";

     tL.head = q1;
    //tL.root = q3;
  
}

#ifdef UNIT_TESTING
   void test_initializeList(void);
	//void test_addTrivia(void);
	//void test_askQuestion(void);
#endif

// main function
 int main() {
   //insert unit testing code
     #ifdef UNIT_TESTING
	cout << "*** This is a debugging version ***\n";
	test_initializeList();
	//test_addNewQuestion();
	//test_askUserQuestion();
	cout << "\n*** End of the debugging version ***\n";

 //insert production code   
    #else
     cout << "*** Welcome to Darrian's trivia quiz ***" << endl;
    triviaList game;
    initializeList(game);
    addTrivia(game);
    
    cout << "\n..." << endl;
    
    askQuestion(game, game.count);
    
    cout << "\n..." << endl;    

    cout << "\n*** Thank you for playing the trivia quiz game. Goodbye! ***" << endl;
    
    #endif
    return 0;
 }
