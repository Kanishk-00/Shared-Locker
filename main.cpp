/*
Name:              Kanishk Chugh
Roll No.:          2004215
Branch:            Mathematics and Computing (MnC)
Course:            CS222 Algorithm Design Lab03 Assignment
File:              main.cpp
*/

/*Including the header files*/
#include "bits/stdc++.h"
/*Including the use module*/
#include "use.h"
/*Including the configure module*/
#include "configure.h"

using namespace std;

/*Main Begins*/

signed main()
{
    int preference;
    while (preference != 3)
    {
        cout << "\n*--------------------------------------Menu Displayed--------------------------------------*\n";
        cout << "Mention your preference(1/2/3)" << endl
             << "1. CONFIGURE" << endl
             << "2. USE" << endl
             << "3. EXIT" << endl;
        cin >> preference;

        /*If the user chose preference as 1 then we'll redirect the user towards the configure module as per the question*/
        if (preference == 1)
        {
            /*Call to configure_content function inside the configure module*/
            configure_content();
        }

        /*If the user chose preference as 2 then we'll redirect the user towards the use module as per the question*/
        else if (preference == 2)
        {
            /*Call to configure_content function inside the use module*/
            use_content();
        }

        /*If the user chose preference as 3 then we'll simply break out and terminate the program as per the question*/

        else if (preference == 3)
        {

            /*Terminating the program*/
            exit(0);
        }

        /*If the user's preference is anything other than 1/2/3 then the following error message is displayed*/
        else
            cout << "\n Oops! The entered choice is not correct.Select between 1/2/3 preference" << endl;
    }
    return 0;

    /*Main Ends*/
}