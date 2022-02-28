#include "Invest.h"

void Invest::Hello() {
    try {
        double initial;
        double dep;
        double annInt;
        int years;

        cout << "           The Power of Investing" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "  Enter values you would like to test.... \n" << endl;

        cout << "  Intial Investment Amount: " << endl;
        while (!(cin >> initial)) //catches non-numerical input
        {
            // Explain error
            cout << "ERROR: a number must be entered: ";
            // Clear input stream
            cin.clear();
            // Discard previous input
            cin.ignore(123, '\n');
        }

        cout << "  Monthly Deposit: " << endl;
        while (!(cin >> dep))
        {
            cout << "ERROR: a number must be entered: ";
            cin.clear();
            cin.ignore(123, '\n');
        }

        cout << "  Annual Interest: " << endl;
        while (!(cin >> annInt))
        {
            cout << "ERROR: a number must be entered: ";
            cin.clear();
            cin.ignore(123, '\n');
        }

        cout << "  Number of Years: " << endl;
        while (!(cin >> years))
        {
            cout << "ERROR: a number must be entered: ";
            cin.clear();
            cin.ignore(123, '\n');
        }

        //calculate and print
        SetUserInput(initial, dep, annInt, years);
        CurrBalWDep();
        SetUserInput(initial, dep, annInt, years);
        CurrBalNoDep();
        Print();
    }
    catch(...){ //just in case ;)
        cout << "Woops! Something went very wrong." << endl;
        return;
    }
}

void Invest::SetUserInput(double t_initial, double t_dep, double t_annInt, int t_years) {
	//store user input in private variables
    m_investAmt = t_initial;
	m_deposit = t_dep;
	m_compInt = t_annInt;
	m_numYears = t_years;
}


void Invest::CurrBalNoDep() {
    int month = 0;
    int year = 0;
    double earnedInt = 0;

    for (int i = 0; i < (m_numYears * 12); ++i) {//iterate through number of months
                                              //according to user years input 
        month += 1; //increment months
        double interest = (m_investAmt * ((m_compInt / 100) / 12)); //calculate interest
        double closeBal = m_investAmt + interest; //calculate closing balance
        earnedInt += interest; //increment earned interest
        m_investAmt = closeBal; //overwrite investAmt for next loop

        if (month % 12 == 0) //writes current stats to vector every 12 months
        {
            year += 1; //increment years

            ostringstream strYear, strCloseBal, strEarnedInt; //create stream buffers
            strCloseBal.precision(2); //set to two decimal places
            strEarnedInt.precision(2);
            strYear << year; //enter int or double into buffer
            strCloseBal << fixed << closeBal;
            strEarnedInt << fixed << earnedInt;
            //convert int and double to string within new string
            string fillVector = ("   " + strYear.str() + "         $" + strCloseBal.str() + "           $" + strEarnedInt.str());
            //send string to vector
            noDeposit.push_back(fillVector);

        }
    }
}


void Invest::CurrBalWDep() {
    int month = 0;
    int year = 0;
    double earnedInt = 0;
    //same as CurrBalNoDep except includes deposit
    for (int i = 0; i <(m_numYears * 12); ++i){
        month += 1;
        double interest = ((m_investAmt + m_deposit) * ((m_compInt/100)/12));
        double closeBal = m_investAmt + m_deposit + interest;
        earnedInt += interest;
        m_investAmt = closeBal;

        if (month % 12 == 0)
        {
            year += 1;

            ostringstream strYear, strCloseBal, strEarnedInt;
            strCloseBal.precision(2);
            strEarnedInt.precision(2);
            strYear << year;
            strCloseBal << fixed << closeBal;
            strEarnedInt << fixed << earnedInt;

            string fillVector = ( "   " + strYear.str() + "         $" + strCloseBal.str() + "           $" + strEarnedInt.str());
            //sends calculations with deposit to different vector
            yesDeposit.push_back(fillVector);

        }
    }
}

void Invest::Print() {
    unsigned int i;
   
    cout << "\033[2J\033[1;1H"; //clear screen
    cout << "        Balance and Interest With a Monthly Deposit" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "  Year     Year End Balance     Year End Earned Interest" << endl;
    cout << "..........................................................." << endl;
    //prints vector with deposit calculations
    for (i = 0; i < yesDeposit.size(); ++i) {

        cout << yesDeposit.at(i) << endl;
    }

    cout << "\n \n \n";

    cout << "       Balance and Interest Without a Monthly Deposit" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "  Year     Year End Balance     Year End Earned Interest" << endl;
    cout << "..........................................................." << endl;
    //prints vector with no deposit in calculations
    for (i = 0; i < noDeposit.size(); ++i) {

        cout << noDeposit.at(i) << endl;
    }
    EndScreen();
}

void Invest::EndScreen() {
    string input;

    cout << " \n \n \n";
    cout << "If you would like to test different values, type YES" << endl;
    cout << "If you would like to leave the program, type EXIT" << endl;
    cin >> input;
    if (input == "YES" || input == "yes") { //restart program
        cout << "\033[2J\033[1;1H";
        Hello();
    }
    else if (input == "EXIT" || input == "exit") { //exit hello() to main() and end program
        return;
    }
    else { //catch for input not == YES or EXIT
        cout << "Invalid Entry." << endl;
        cin.clear();
        EndScreen();
    }
}