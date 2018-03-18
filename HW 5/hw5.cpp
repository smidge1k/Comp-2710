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
 * Coded from github account (smidge1k) and contributions were made in the form of comments from github user (kareithdyce).
 * Compiled using syllabus method - Shelby Computer Lab via remote access through putty using emacs g++ compiler.
 *
 */


/**
 * Comment this line to enable production version of code!
 **/
//#define UNIT_TESTING

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
    int count;
    triviaNode *head, *root;
    triviaList()
     {
      count = 0;
      head = NULL;
      root = NULL;
    }
  };	

/**
 * initializes the Trivia questions via hard code.
 **/
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

/**
 * this function asks the player a question 
 * */
int askQuestion(triviaList tL, int i, int &bonus) {
    triviaNode *q = tL.head;

 //parameter checking 

    if (i < 1) { // checks if the number of trivia questions is equal to zero
        cout << "\nWarning - The number of trivia to be asked must equal to or be larger than 1.";
        return 1;
    }
    if (i > tL.count) { //checks if the number of trivia questions exceeds the number of questions in the list
        cout << "\nWarning - There are only " << tL.count << " trivia in the list";
        i = tL.count;
        
    }
    string ans;
    bonus = 0;

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

/**
 *  this function prompts the user to create their own question, answer, and point value
 **/
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

/**
 * function test the asking a user a question function works properly
 **/
void test_askQuestion()
{
	// Initialize test fixtures
	triviaList tL;
    int bonus;
	
	// Setup Trivia list
	initializeList(tL);

	cout << "\nFunction to test: int askQuestion(triviaList& tL, int i, int &bonus)\n";

	// Case 1
	cout << "Unit Test Case 1: Ask no questions. The program should give a warning message.\n";
	
    // Run assertions 
	assert(1 == askQuestion(tL, 0, bonus));
	cout << "\nCase 1 passed...\n";
	
	// Case 2.1
	cout << "\nUnit Test Case 2.1: Ask 1 question in the linked list. The tester enters the correct answer.\n";

	// Run assertions
	assert(0 == askQuestion(tL, 1, bonus));
	assert(100 == bonus);
	cout << "Case 2.1 passed...\n";

	// Case 2.2
	cout << "\nUnit Test Case 2.2: Ask 1 question in the linked list. The tester enters an incorrect answer.\n";
	
	// Run assertions
	assert(0 == askQuestion(tL, 1, bonus));
	assert(0 == bonus);
	cout << "Case 2.2 passed...\n";

	// Case 3.1
	cout << "\nUnit Test Case 3.1: Ask all of the questions in the linked list. The tester enters the correct answers.\n";

	// Run assertions
	assert(0 == askQuestion(tL, 3, bonus));
	// cover all possible scores
	assert(170 == bonus);
	cout << "Case 3.1 passed...\n";

    // Case 3.2
	cout << "\nUnit Test Case 3.2: Ask all of the questions in the linked list. The tester enters the incorrect answers.\n";

	// Run assertions
	assert(0 == askQuestion(tL, 3, bonus));
	// cover all possible scores
	assert(0 == bonus);
	cout << "Case 3.2 passed...\n";

	// Case 4
	cout << "\nUnit Test Case 4: Attempt to ask 5 questions in the linked list. Program should give a warning message.\n";

	// Run assertions
    assert (0 == askQuestion(tL, 5, bonus));
	cout << "Case 4 passed...\n";
}

#ifdef UNIT_TESTING
	void test_askQuestion(void);
#endif

// main function
 int main() {
   //insert unit testing code
     #ifdef UNIT_TESTING
	cout << "*** This is a debugging version ***\n";
	test_askQuestion();
	cout << "\n*** End of the debugging version ***\n";

 //insert production code   
    #else
     cout << "*** Welcome to Darrian's trivia quiz ***" << endl;
    triviaList game;
    int bonus;
    initializeList(game);
    addTrivia(game);
    
    cout << "\n..." << endl;
    
    askQuestion(game, game.count, bonus);
    
    cout << "\n..." << endl;    

    cout << "\n*** Thank you for playing the trivia quiz game. Goodbye! ***" << endl;
    
    #endif
    return 0;
 }
