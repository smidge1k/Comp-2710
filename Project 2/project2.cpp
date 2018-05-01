# include <iostream>
# include <string>
# include <vector>
# include <array>
# include <ostream>
# include <fstream>
using namespace std;

/**
 * Darrian Johnson
 * Comp 2710
 * Project2.cpp
 * 4-30-18
 *
 *
 */

class user;
class menu; 
class admin;
class account;
class client;

int const DATABASE_SIZE = 100;

class user {
    private:

    string name, password;

    public:
        friend class admin;
    user() { 
        name = "";
        password = "";

        int verification = 0;
        
    }

    //setters
    void setUsername(string nameIn) {
        name = nameIn;
    }
    void setPassword(string passwordIn) {
        password = passwordIn;
    }
    void setVerification(int verificationIn) {
        verification = verificationIn;
    }
    //getters
    string getUsername() {
        return name;
    }
   string getPassword() {
       return password;
   }
   int getVerification() {
       return verification;
   }
    void changePassword(user, vector <user>&);
    void addClient(string, string, int, string, int, vector <client>);

    int verification = 0;
};

void user::changePassword(user currentUser, vector <user>& dataBase) {
    string passwordIn;
    do {
        cout << "New Password: ";
        cin >> passwordIn;
        if (passwordIn == currentUser.getPassword()) {
            cout<< "Error - Your new password must be different from the old one.\n";
        }
    }while (passwordIn == currentUser.getPassword());
    currentUser.setPassword(passwordIn);
    for(int i = 0; i < DATABASE_SIZE; i++) {
        if(dataBase[i].getUsername() == currentUser.getUsername()) {
            dataBase[i] = currentUser;
            break;
        }
    }
}

class menu {
    private:

    public:

    friend class user;

    menu(){

    };

    void showMain() {
        cout << "\t===========================================================\n";
        cout << "\t|\tWelcome to the Auburn Branch of Tiger Bank!\t  |\n";
        cout << "\t===========================================================\n";
        cout << "1) Login\n";
        cout << "2) Quit\n";
    }
    void userMenu() {
        cout << "\t===========================================================\n";
        cout << "\t|\t\tTeller Terminal System - Branch Staff\t\t|\n";
        cout << "\t===========================================================\n";
        cout << "1) Client and Account Management\n";
        cout << "2) Change Password\n";
        cout << "3) Exit\n";
        cout << "Please choose an option: ";

    }
     
    bool authenticate(string nameIn, string passwordIn, vector <user> dataBase) {
        bool valid = false;
        for (int i = 0; i < DATABASE_SIZE; i++) {
            if(dataBase[i].getUsername() == nameIn && dataBase[i].getPassword() == passwordIn) {
                valid = true;
                break;
            }
            else {
                valid = false;
            }
        }
        return valid;
    }
    
    void showLogin() {
        cout << "\t===========================================================\n";
        cout << "\t|\t Login to Access the Teller Terminal System\t  |\n";
        cout << "\t===========================================================\n";
    }
   
    void adminMenu() {
        cout << "\t===========================================================\n";
        cout << "\t|\tTeller Terminal System - System Administration\t  |\n";
        cout << "\t===========================================================\n";
        cout << "1) Client and Account Management\n";
        cout << "2) Add a branch staff member\n";
        cout << "3) Delete a branch staff member\n";
        cout << "4) Display branch staff\n";
        cout << "5) Change password\n";
        cout << "6) Exit\n";
        cout << "Please choose an option: ";
    }
    void showManage() {
        cout << "\t===========================================================\n";
        cout << "\t|  Teller Terminal System - Client and Account Management |\n";
        cout << "\t===========================================================\n";
        cout << "1) Add a client\n";
        cout << "2) Add an account\n";
        cout << "3) Edit Client Information\n";
        cout << "4) Manage an account\n";
        cout << "5) Save Client and Account Information\n";
        cout << "6) Exit\n";
        cout << "Please choose an option: ";
    }
    user returnClient(string, string, vector <user>);
};


user menu::returnClient(string nameIn, string passwordIn, vector <user> dataBase) {
    user fetch;
    for(int i = 0; i < DATABASE_SIZE; i++) {
        if(dataBase[i].getUsername() == nameIn && dataBase[i].getPassword() == passwordIn) {
            fetch.setVerification(dataBase[i].getVerification());
            fetch.setPassword(dataBase[i].getPassword());
            fetch.setUsername(dataBase[i].getUsername());
            break;
        }
    }
    return fetch;
}

class admin {
    private:

    string name, password;
    int verification;

    public:

    admin(){
        string name = "";
        string password = "";

        int verification = 0;
    };
    //getters
    string getAdminName(string) {
        return name;
    }
    string getAdminPassword(string) {
        return password;
    }
    int getVerification() {
        return verification;
    }
    //setters
    void setAdminName(string nameIn) {
        name = nameIn;
    }
    void setAdminPassword(string passwordIn) {
        password = passwordIn;
    }
    void setVerification(int verificationIn) {
        verification = verificationIn;
    }


    void addNewUser(vector <user>& dataBase) {
        user nUser;
        string nameIn, passwordIn;
        int verificationIn;

        cout << "Username: ";
        cin >> nameIn;
        nUser.setUsername(nameIn);
        cout << "Password: ";
        cin >> passwordIn;
        nUser.setPassword(passwordIn);
        cout << "Role (1 - Admnistrator; 2 - Branch Staff): ";
        cin >> verificationIn;
        nUser.setVerification(verificationIn);
        for(int i = 0; i < DATABASE_SIZE; i++) {
            if(dataBase[i].getVerification() == 0) {
                dataBase[i] = nUser;
                if(nUser.getVerification() == 1) {
                    cout << "Username: " << nameIn << "\tRole: System Administrator\n";
                }
                else{
                    cout << "Username: " << nameIn << "\tRole: Branch Staff\n";
                }
                break;
            }
            else if(i == DATABASE_SIZE - 1 && dataBase[i].getVerification() != 0) {
                cout << "We apologize. The database appears to be full\n";
                break;
            }
        }
        
    }

    void deleteUser(vector <user>& dataBase) {
        user emptyUser;
        string nameIn;
        int option;

       cout << "Delete a user - Username: ";
       cin >> nameIn;
       cout << "3) Confirm\n";
       cout << "4) Cancel\n";
       cout << "Please choose an option: ";
       cin >> option;
       switch(option){
           case 3:
            for(int i = 0; i < DATABASE_SIZE; i++){
                if(dataBase[i].getUsername() == nameIn) {
                    dataBase[i] = emptyUser;
                    cout << "User " << nameIn << " was deleted.\n";
                    break;
                }
                else if(i == DATABASE_SIZE - 1) {
                    cout << "Error - User was not found in the system.\n";
                }
            }
            
            break;
        case 4:
            break;
       }
    }

    void displayBranch(vector <user> dataBase) {
        int counter = 0;
        for(int i = 0; i < DATABASE_SIZE; i++) {
            if(dataBase[i].getVerification() != 0) {
                if(dataBase[i].getVerification() == 1 || dataBase[i].getVerification() == 2) {
                  counter++;
                }
            }
        }
        cout << "There are " << counter << " users in the system at the moment.\n";
        for(int i = 0; i < DATABASE_SIZE; i++) {
            if(dataBase[i].getVerification() != 0) {
                if(dataBase[i].getVerification() == 1) {
                    cout << "Username: " << dataBase[i].getUsername() << " Role: Administrator\n";
                }
                else if(dataBase[i].getVerification() == 2) {
                    cout << "Username: " << dataBase[i].getUsername() << "Role: Branch Staff\n";
                }
            }
        }
    }
    

    void changePassword(user currentUser, vector <user>& dataBase) {
        string passwordIn;

        do{
            cout << "New Password: ";
            cin >> passwordIn;
            if(passwordIn == currentUser.getPassword()) {
                cout << "Error - Your new password must be different from the old one.\n";
            }
        }while(passwordIn == currentUser.getPassword());
        currentUser.setPassword(passwordIn);
        for(int i = 0; i < DATABASE_SIZE; i++) {
            if(dataBase[i].getUsername() == currentUser.getUsername()) {
                dataBase[i] = currentUser;
                break;
            }
        }
    }
};

class account {
    private:

    string clientName, accountType;
    int accountNum, balance;

    public:

    account(){
        string clientName = "";
        string accountType = "";
        int accountNum = 0;
        int balance = 0;

        int verification = 0;
    };
    
    //setters
    void setAccountName(string nameIn) {
        clientName = nameIn;
    }
    void setAccountType(string typeIn) {
        accountType = typeIn;
    }
    void setBalance(int balanceIn) {
        balance = balanceIn;
    }
    void setAccountNum(int numIn) {
        accountNum = numIn;
    }
    void setVerification(int verificationIn) {
        verification = verificationIn;
    }
    //getters
    string getAccountName() {
        return clientName;
    }
    string getAccountType() {
        return accountType;
    }
    int getBalance() {
        return balance;
    }
    int getAccountNum() {
        return accountNum;
    }
    int getVerification() {
        return verification;
    }
    void deposit(int depositIn) {
        balance += depositIn;
    }
    void withdraw(int withdrawIn) {
        if(withdrawIn > balance) {
            cout << "Insufficient funds. Cannot withdraw. ";
        }
        else {
            balance -= withdrawIn;
        }
    }
    
    int verification = 0;
};

class client{
    private:

    string name;
    string password, address, employer;
    int ssn, income;

    public:


    client(){
       string name = "";
       string address = "";
       string employer = ""; 
       int ssn = 0;
       int income = 0;

       int verification = 0;
      
    };
    account clientAccount;
    friend class account;
//getters
    string getClientName() {
        return name;
    } 
    string getAddress() {
        return address;
    }
    int getSSN() {
        return ssn;
    }
    string getEmployer() {
        return employer;
    }
    int getIncome() {
        return income;
    }
    int getVerification() {
        return verification;
    }
    //setters
    void setClientName(string nameIn) {
        name = nameIn;
    }
    void setAddress(string addressIn) {
        address = addressIn;
    }
    void setSSN(int ssnIn) {
        ssn = ssnIn;
    }
    void setEmployer(string employerIn) {
        employer = employerIn;
    }
    void setIncome(int incomeIn) {
        income = incomeIn;
    }
    void setVerification(int verificationIn) {
        verification = verificationIn;
    }
    
    int verification = 0;
};

void addClient(vector <client>& clientDatabase) {
    
    string nameIn, addressIn, employerIn;
    int ssnIn, incomeIn;

    cout << "A new client will be added: \n";
    client newClient;
    cout << "Client name: ";
    cin >> nameIn; 
    newClient.setClientName(nameIn);
    cout << "Address: ";
    cin >> addressIn;
    cout << "Social Security Number: ";
    cin >> ssnIn;
    newClient.setSSN(ssnIn);
    cout << "Employer: ";
    cin >> employerIn;
    newClient.setEmployer(employerIn);
    cout << "Annual Income: ";
    cin >> incomeIn;
    newClient.setIncome(incomeIn);
    for(int i = 0; i < DATABASE_SIZE; i++) {
        if(clientDatabase[i].getVerification() == 0) {
            newClient.setVerification(1);
            clientDatabase[i] = newClient;
            cout << "A new client was added!\n";
            break;
        }
       else if(i == DATABASE_SIZE - 1 && clientDatabase[i].getVerification() != 0) {
           "We apologize. The database appears to be full\n";
           break;
       } 
    }
}

void addAccount(vector <client>& clientDatabase, vector <account>& accountDatabase) {
    string clName, acctType;
    int accountNum, balance;

    cout << "Choose a client: ";
    cin >> clName;
    for(int i = 0; i < DATABASE_SIZE; i++) {
        if(clientDatabase[i].getClientName() == clName) {
            cout << "A new account will be created for " << clientDatabase[i].getClientName() << "...\n";
            account newAccount;

            newAccount.setVerification(1);
            cout << "Account Number: ";
            cin >> accountNum;
            newAccount.setAccountNum(accountNum);

            cout << "Account Type: ";
            cin >> acctType;
            newAccount.setAccountType(acctType);

            cout << "Balance: ";
            cin >> balance;
            newAccount.setBalance(balance);

            newAccount.setAccountName(clientDatabase[i].getClientName());
            for(int j = 0; j < DATABASE_SIZE; j++) {
                if(accountDatabase[j].getVerification() == 0) {
                    accountDatabase[j] = newAccount;
                    cout << "A new account was created for " << accountDatabase[i].getAccountName() << " \n";
                    break;
                }
                else if(i == DATABASE_SIZE -1 && accountDatabase[i].getVerification() == 0) {
                    "We apologize. The database appears to br full\n";
                    break;
                }
            }
            break;
        }
        else if(i == DATABASE_SIZE - 1) {
            cout << "Error - The client is not in the system.\n";
        }
    }
}

void editClient(vector <client>& clientDatabase) {
    string clName, newAddress, newEmployer;
    int newSSN, newIncome;
    bool edit = true;

    int decision = 0;

    cout << "Choose a client: ";
    cin >> clName;

    for(int i = 0; i < DATABASE_SIZE; i++) {
        if(clientDatabase[i].getClientName() == clName) {
            cout << "Display " << clientDatabase[i].getClientName() << "'s information: \n";
            cout << "Address: " << clientDatabase[i].getAddress() << "\n";
            cout << "Social Security Number: " << clientDatabase[i].getSSN() << "\n";
            cout << "Employer: " << clientDatabase[i].getEmployer() << "\n";
            cout << "Annual Income: " << clientDatabase[i].getIncome() << "\n";
            cout << "Client " << clientDatabase[i].getClientName() << "'s information will be updated...\n";
            cout << "1) Confirm\n";
            cout << "2) Cancel\n";
            cin >> decision;
            switch(decision) {
                case 1:
                    cout << "Address: ";
                    cin >> newAddress;
                    clientDatabase[i].setAddress(newAddress);

                    cout << "Social Security Number: ";
                    cin >> newSSN;
                    clientDatabase[i].setSSN(newSSN);

                    cout << "Employer: ";
                    cin >> newEmployer;
                    clientDatabase[i].setEmployer(newEmployer);

                    cout << "Annual Income: ";
                    cin >> newIncome;
                    clientDatabase[i].setIncome(newIncome);

                    cout << "Client " << clientDatabase[i].getClientName() << "'s information was updated.\n";
                    break;
                case 2:
                    break;
            }
            break;
        }
        else if(i == DATABASE_SIZE - 1) {
            cout << "Error - Accont " << clientDatabase[i].getClientName() << " is not in the system.\n";
        }
    }
}

void manageAccount(vector <account>& accountDatabase) {
    int decision, accountNum, deposit, withdraw;
    bool active = true;

    cout << "Which account will be managed? ";
    cin >> accountNum;

    for(int i = 0; i < DATABASE_SIZE; i++) {
        if(accountDatabase[i].getAccountNum() == accountNum) {
            do{
                cout << "Manage account " << accountDatabase[i].getAccountNum() << " for " << accountDatabase[i].getAccountName() << "...\n";
                cout << "1) Deposit\n";
                cout << "2) Withdraw\n";
                cout << "3) Cancel\n";
                cout << "Please choose an option: ";
                cin >> decision;
                switch(decision) {
                    case 1:
                        cout << "Deposit Amount: ";
                        cin >> deposit;
                        accountDatabase[i].deposit(deposit);
                        cout << "Balance of account " << accountDatabase[i].getAccountNum() << " is: " << accountDatabase[i].getBalance() << "\n";
                        break;  
                    case 2:
                        cout << "Withdraw Amount: ";
                        cin >> withdraw;
                        accountDatabase[i].withdraw(withdraw);
                        cout << "Balance of account " << accountDatabase[i].getAccountNum() << " is: " << accountDatabase[i].getBalance() << "\n";
                        break;
                    case 3:
                        active = false;
                        break;
                }
            }while(active == true);
            break;
        }
        else if(i == DATABASE_SIZE - 1) {
            cout << "Error - Account " << accountNum << " is not in the system.\n";
        }
    }
}

void saveAccount(account accountRead) {
    ofstream outfile;

    outfile.open("account_info.txt");
    outfile << "Account name: " << accountRead.getAccountName() << endl;
    outfile << "Balance: " << accountRead.getBalance() << endl;
    outfile << "Account Type: " << accountRead.getAccountType() << endl;
    outfile << "Account Number: " << accountRead.getAccountNum() << endl;
    outfile.close();
    
    cout << "Account information has been saved in the account_info file." << endl;
}

void saveClient(client clientRead) {
    ofstream outfile;

    outfile.open("client_info.txt");
    outfile << "Client name: " << clientRead.getClientName() << endl;
    outfile << "Address: " << clientRead.getAddress() << endl;
    outfile << "Employer: " << clientRead.getEmployer() << endl;
    outfile << "Annual Income: " << clientRead.getIncome() << endl;
    outfile << "Social Security Number: " << clientRead.getSSN() << endl;
    outfile.close();
    
    cout << "Account information has been saved in the client_info file." << endl;
}

void systemTerminate(vector <user> data) {
    ofstream outfile;
    outfile.open("faculty_members.txt");
    for(int i = 0; i <= DATABASE_SIZE; i++){
        outfile << data[i].getUsername()<<endl;
        outfile<<  data[i].getPassword()<<endl; 
        if(data[i].getVerification() != 0) {
            if(data[i].getVerification() == 1) {
                outfile <<1<<endl;
            }
            else if(data[i].getVerification() == 2) {
                outfile <<2<<endl;
            }
        }
    
    }
    outfile.close();
}

 int main() {
     menu m;
     admin aD;
     user currUser; //current user
     user adUser; //admin user
     vector <user> dataBase(DATABASE_SIZE);
     vector <client> clientDatabase(DATABASE_SIZE);
     vector <account> accountDatabase(DATABASE_SIZE);
     adUser.setUsername("admin");
     adUser.setPassword("0000");
     adUser.setVerification(1);
     dataBase[0] = adUser;

     string name, password;
     int option;
     char a;

     bool valid = true;
     bool valid1 = true;
     bool valid2 = true;
     bool valid3 = true;
     bool valid4 = true;

     do {
         valid = true;
         m.showMain();

         cout << "\tPlease choose an option: ";
         cin >> option;

         switch(option) {
             case 1:
                m.showLogin();
                for(int chance = 0; chance < 3; chance++) {
                    cout << "Username: ";
                    cin >> name;

                    cout << "Password: ";
                    cin >> password;

                    if(!m.authenticate(name, password, dataBase)) {
                        cout << "The username or password you entered is incorrect. Please try again...\n";
                    }
                    else {
                        currUser.setUsername(m.returnClient(name, password, dataBase).getUsername());
                        currUser.setPassword(m.returnClient(name, password, dataBase).getPassword());
                        currUser.setVerification(m.returnClient(name, password, dataBase).getVerification());

                        if(currUser.getVerification() == 1) {
                            do {
                                int option2;
                                
                                m.adminMenu();
                                cin >> option2;

                                switch(option2) {
                                    case 1:
                                        do {
                                            int option3 = 0;

                                            m.showManage();
                                            cin >> option3;

                                            switch(option3) {
                                                case 1:
                                                    addClient(clientDatabase);
                                                    cout << "Press any key to continue...\n";
                                                    cin.ignore().get();
                                                    valid3 = true;
                                                    break;
                                                case 2:
                                                    addAccount(clientDatabase, accountDatabase);
                                                    cout << "Press any key to continue...\n";
                                                    cin.ignore().get();
                                                    valid3 = true;
                                                    break;
                                                case 3:
                                                    editClient(clientDatabase);
                                                    cout << "Press any key to continue...\n";
                                                    cin.ignore().get();
                                                    valid3 = true;
                                                    break;
                                                case 4:
                                                    manageAccount(accountDatabase);
                                                    valid3 = true;
                                                    break;
                                                case 5:
                                                    for(int i = 0; i < DATABASE_SIZE; i++) {
                                                        if(clientDatabase[i].getVerification() == 1) {
                                                            saveClient(clientDatabase[i]);
                                                        }
                                                    }
                                                    for(int i = 0; i < DATABASE_SIZE; i++) {
                                                        if(accountDatabase[i].getVerification() == 1){
                                                            saveAccount(accountDatabase[i]);
                                                        }
                                                    }
                                                    cout << "Press any key to continue...\n";
                                                    cin.ignore().get();
                                                    valid3 = true;
                                                    break;
                                                case 6:
                                                    valid3 = false;
                                                    break;
                                                default:
                                                    break;
                                            }
                                    }while(valid3);
                                    valid1 = true;
                                    break;
                                case 2:
                                    aD.addNewUser(dataBase);
                                    cout << "Press any key to continue...\n";
                                    cin.ignore().get();
                                    valid1 = true;
                                    break;
                                case 3:
                                    aD.deleteUser(dataBase);
                                    cout << "Press any key to continue...\n";
                                    cin.ignore().get();
                                    valid1 = true;
                                    break;
                                case 4:
                                    aD.displayBranch(dataBase);
                                    cout << "Press any key to continue...\n";
                                    cin.ignore().get();
                                    valid1 = true;
                                    break;
                                case 5:
                                    aD.changePassword(currUser, dataBase);
                                    cout << "Press any key to continue...\n";
                                    cin.ignore().get();
                                    valid1 = true;
                                    break;
                                case 6:
                                    valid1 = false;
                                    break;
                                default:
                                    break;
                                }
                            }while(valid1);
                            break;
                        }
                        else if(currUser.getVerification() == 2) {
                            do{
                                int option;

                                m.userMenu();
                                cin >> option;

                                switch(option) {
                                    case 1:
                                        do {
                                            m.showManage();
                                            int option2 = 0;
                                            cin >> option2;

                                            switch(option2) {
                                                case 1:
                                                    addClient(clientDatabase);
                                                    cout << "Press any key to continue...\n";
                                                    cin.ignore().get();
                                                    valid4 = true;
                                                    break;
                                                case 2:
                                                    addAccount(clientDatabase, accountDatabase);
                                                    cout << "Press any key to continue...\n";
                                                    cin.ignore().get();
                                                    valid4 = true;
                                                    break;
                                                case 3:
                                                    editClient(clientDatabase);
                                                    cout << "Press any key to continue...\n";
                                                    cin.ignore().get();
                                                    valid4 = true;
                                                    break;
                                                case 4:
                                                    manageAccount(accountDatabase);
                                                    valid4 = true;
                                                    break;
                                                case 5:
                                                    for(int i = 0; i < DATABASE_SIZE; i++) {
                                                        if(clientDatabase[i].getVerification() == 1) {
                                                            saveClient(clientDatabase[i]);
                                                        }
                                                    }
                                                    for(int i = 0; i < DATABASE_SIZE; i++) {
                                                        if(accountDatabase[i].getVerification() ==1) {
                                                            saveAccount(accountDatabase[i]);
                                                        }
                                                    }
                                                    cout << "Press any key to continue...\n";
                                                    cin.ignore().get();
                                                    valid4 = true;
                                                    break;
                                                case 6:
                                                    valid4 = false;
                                                default:
                                                    break;
                                            }
                                        }while(valid4);
                                        
                                        valid2 = true;
                                        break;
                                    case 2:
                                        currUser.changePassword(currUser, dataBase);
                                        cout << "Press any key to continue...\n";
                                        cin.ignore().get();
                                        valid2 = true;
                                        break;
                                    case 3:
                                        valid2 = false;
                                        break;
                                    default:
                                        break;
                                }
                            }while(valid2);
                        }
                        break;
                    }
                }
                valid = true;
                break;
            case 2:
                systemTerminate(dataBase);
                cout << "Press any key to continue...\n";
                cin.ignore().get();
                valid = false;
                break;
            default:
                break;
         }
     }while(valid);
     return 0;
 }
