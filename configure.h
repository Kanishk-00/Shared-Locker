/*
Name:              Kanishk Chugh
Roll No.:          2004215
Branch:            Mathematics and Computing (MnC)
Course:            CS222 Algorithm Design Lab03 Assignment
File:              configure.h (CONFIGURE Module)
*/

#include "bits/stdc++.h"
using namespace std;

/*-----------------------------------------------------------------------------------------------------------------------*/

/*Function to add a new locker entry into configure.txt file*/
void AddNewLockerEntry()
{
    /*Declaration of the locker_id as a string*/
    string locker_id;
    /*Declaration of the number of users*/
    int num_of_users;
    /*Declaration of the configure module access key (L)*/
    int configure_access_key;
    string flag = "";

    /*Taking the input of locker_id, number of users and access key from the user*/
    cout << "Please, Enter the Locker Id: " << endl;
    cin >> locker_id;
    cout << "Please, Enter the Number of Users: " << endl;
    cin >> num_of_users;
    cout << "Please, Enter the 10 digit Locker Key L: " << endl;
    cin >> configure_access_key;

    /*ifstream: Stream class to read from files*/
    /*we can use our file streams the same way we are already used to use cin and cout,
    with the only difference that we have to associate these streams with physical files.*/

    ifstream configure_input;
    /*Opening the configure.txt and reading the data from configure.txt*/
    configure_input.open("configure.txt");

    /*In this loop;-
       The pointer configure_input will read and go through the lines of configure.txt line by line and will check
       the first 3 characters of every line and try to see if it matches with the locker_id entered by the user */

    /*Whenever the pointer hits a '\n, it will change it's line, hence the deliminator is '\n' character*/
    while (getline(configure_input, flag, '\n'))
    {
        if (flag.substr(0, 3) == locker_id)
        {
            cout << "The Locker Id entered is already present in configure.txt file. Can't add the entry with duplicate locker_id: " << endl;
            return;
        }
    }
    /*Closing the file pointer*/
    configure_input.close();

    /*Declaration of the prime numbers array of length number of users*/
    int prime_numbers_array[num_of_users];
    /*Declaration of the user keys array of length number of users*/
    int user_keys_array[num_of_users];
    /*Intializing the counter for number of users*/
    int CounterOfNumberOfUser = 0;
    /*Declaring the KthRoot of L (the access key) which will help us to find the primes such that the product of
    all the primes should exceed L(the access key)*/
    int KthRoot;
    /*helper = 1/k*/
    float helper_kth_root_power = (1.0 / num_of_users);
    /*KthRoot = (L)^(1/k)*/
    KthRoot = pow(configure_access_key, helper_kth_root_power);
    /*Taking the input of prime numbers stored in another file named StorePrimeNumbers.txt*/
    /*In this file the prime numbers from 1-2000 are stored */
    ifstream prime_file("StorePrimeNumbers.txt");
    /*Reading from StorePrimeNumbers.txt file using prime_file pointer */
    string string_num_at_moment = "";
    /*This will give the current number at which the prime_file pointer is at that moment while reading*/
    int NumberAtMoment;

    /*This Loop will read the numbers as string with ',' as the deliminator and will get compared with the KthRoot*/
    while (getline(prime_file, string_num_at_moment, ','))
    {
        /*This will convert the curent number read as string into an integer value*/
        NumberAtMoment = stoi(string_num_at_moment);
        /*When the number we got at that moment is greater than the KthRoot of the L this means if we'll product all
        the number after this number which we've got, then it surely ensure that the total product would be greater than L*/
        if (NumberAtMoment > KthRoot)
        {
            /*Storing the numbers got into out primes array*/
            prime_numbers_array[CounterOfNumberOfUser] = NumberAtMoment;
            /*Incrementing the Counter of Number of users*/
            CounterOfNumberOfUser++;
            /*When the CounterofNumbers of users becomes k, then we break out of the loop and prime array is formed*/
            if (CounterOfNumberOfUser == num_of_users)
            {
                break;
            }
        }
    }

    /*Closing the prime_file pointer*/
    prime_file.close();

    /*This will calculate the user keys for different prime numbers as L%p(i)*/
    cout << endl
         << "The User Keys which we got are as follows:" << endl;
    for (int i = 0; i < num_of_users; i++)
    {
        user_keys_array[i] = configure_access_key % prime_numbers_array[i];
    }

    /*This Loop will display the user keys for different prime numbers as L%p(i)*/
    /*As per given in the question, the user keys must be of 4 length hence I've used "%04d" which will help in fulfilling that*/
    for (int i = 0; i < num_of_users; i++)
    {
        printf("%04d", user_keys_array[i]);
        cout << endl;
    }
    /*Declaring another pointer for a file which will write in configure.txt*/
    ofstream configure_output;

    /*ios::app
    All output operations are performed at the end of the file, appending the content to the current content of the file.*/
    configure_output.open("configure.txt", ios::app);
    configure_output << locker_id << '\t' << num_of_users << '\t';
    for (int i = 0; i < num_of_users; i++)
    {
        configure_output << prime_numbers_array[i] << '\t';
    }
    configure_output << endl;

    /*Closing the file pointer*/
    configure_output.close();
    return;
}

/*---------------------------------------------------------------------------------------------------------------------*/

/*Function to delete a locker entry from configure.txt file if present in it*/

void DeleteALockerEntry()
{
    /*Declaration of the locker_id as a string*/
    string locker_id;
    /*This empty string will help us read the contents from the configure.txt file*/
    string flag = "";
    /*Taking the input of locker_id, number of users and access key from the user*/
    cout << "Please, Enter the locker_id: " << endl;
    cin >> locker_id;

    /*ifstream: Stream class to read from files*/
    /*we can use our file streams the same way we are already used to use cin and cout,
    with the only difference that we have to associate these streams with physical files.*/

    ifstream delete_input;

    /*ofstream: Stream class to write on files*/
    ofstream delete_output;

    /*opening the configure.txt file to read data from it*/
    delete_input.open("configure.txt");
    /*If the file is empty then can't be opened*/
    if (!delete_input)
    {
        cout << "Oops! File Can't be found" << endl;
        return;
    }

    /*This is the checker which will give us the result of whether the entry entered by the user is found configure.txt*/
    int EntryFindChecker = 0;

    /*Opening a sample.txt file
    sample.txt:-
    This file will store all the entry data except the entry data of the locker_id entered by the user if found in configure.txt*/
    delete_output.open("sample.txt");

    /*Reading the content from configure.txt*/
    while (getline(delete_input, flag, '\n'))
    {

        /*Inserting the empty flag with data and checking the first 3 char of (0,1,2) of a particular row and checking it with
            the locker_id entered by the user*/

        /*If found the entry, then we'll intialise the deletion*/
        if (flag.substr(0, 3) == locker_id)
        {
            cout << "Locker Id entered is found, intialising the deletion of the entry" << endl;
            /*updating the entryfindchecker to 1 when the entry is found*/
            EntryFindChecker = 1;
        }

        /*otherwise, when the entry of locker_id doesn't matches the entered locker_id,
         then we'll simply write that data into another file named sample.txt, so it's like deleting only*/
        else
        {
            delete_output << flag << endl;
        }
    }

    /*Closing the file pointers*/
    delete_input.close();
    delete_output.close();

    /*if the entryfindchecker remains as 0 even after coming out of the while loop, then the entry is not found*/
    if (EntryFindChecker == 0)
    {
        cout << "Sorry, The Locker Id Entered by the user can't be found." << endl;
        return;
    }

    /*Afterwards we'll simply deleting the configure.txt and renaming the sample.txt(containg the updated data of configure.txt
    after deletion process) to configure.txt*/
    remove("configure.txt");
    rename("sample.txt", "configure.txt");

    return;
}

/*-------------------------------------------------CONFIGURE MODULE-------------------------------------------------*/

void configure_content()
{
    /*declaring the preference variable for the user*/
    int preference;
    cout << "\n*--------------------------------Configure Module Menu Displayed--------------------------------*\n";
    while (preference != 3)
    {
        cout << endl
             << "Mention your preference (1/2/3):-" << endl
             << "1. Add a New Locker Entry" << endl
             << "2. Delete a Locker Entry" << endl
             << "3. Return" << endl;

        /*Taking in the preference*/
        cin >> preference;

        /*When the preference given by the user is 1 then calling our add a new locker entry function*/
        if (preference == 1)
        {
            AddNewLockerEntry();
        }
        /*When the preference given by the user is 2 then calling our deletion of a locker entry function*/
        else if (preference == 2)
        {
            DeleteALockerEntry();
        }
        /*When the preference given by the user is 3 then returning out of the loop*/
        else if (preference == 3)
        {
            return;
        }
        /*When the preference given by the user is something else than 1,2,3 then displaying the error message*/
        else
            cout << "Oops! The Entered preference is not correct. Please check it once again!" << endl;
    }
}
