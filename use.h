/*
Name:              Kanishk Chugh
Roll No.:          2004215
Branch:            Mathematics and Computing (MnC)
Course:            CS222 Algorithm Design Lab03 Assignment
File:              use.h (USE Module)
*/

/*
Descriptions:-

user_keys_array[i] is given array of remainders u(i)'s

prod is product of all given numbers
            prod = prime_number_array[0] * prime_number_array[1] * ... * prime_number_array[k-1]

pp[i] is product of all divided by num[i]
            pp[i] = prod / prime_number_array[i]

MultiplicativeInverseUnderModuloM[i] = Modular Multiplicative Inverse of
            pp[i] with respect to prime_number_array[i]
*/

#include <bits/stdc++.h>
using namespace std;

/* Function which Returns modulo inverse of a with respect to m using extended Euclid Algorithm. Multiplicative-inverse-under-modulo-m/ */
long long MultiplicativeInverseUnderModuloM(long long a, long long m)
{
    long long m0 = m, t, quotient;
    long long x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    /*Applying the Extended Euclid Algorithm*/
    while (a > 1)
    {
        quotient = a / m;
        t = m;
        /*Applying the same algorithm as Extended Euclid ALgorithm, the
        implementation is based on Chinese Remainder Theorem*/
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - quotient * x0;
        x1 = t;
    }
    /*To make x1 as postive*/
    if (x1 < 0)
        x1 += m0;

    return x1;
}

/*----------------------------------------------------------------------------------------------------------------------*/
/*

k is size of primes[] and user_keys[].
Returns the smallest number L such that: (access_key)
L % primes[0] = user_keys[0],
L % primes[1] = user_keys[1],
 ..................
L % primes[k-2] = user_keys[k-1]

*/

/*Applying Chinese Remainder Theorem*/

/*
The Formula used for Chinese Remainder Theorem:

(access_key)     L =  ( ∑ (user_keys[i]*pp[i]*MultiplicativeInverseUnderModuloM[i]) ) % prod
   Where 0 <= i <= n-1

user_keys[i] is given array of remainders

prod is product of all given numbers
prod = primes[0] * primes[1] * ... * primes[k-1]

pp[i] is product of all divided by primes[i]
pp[i] = prod / primes[i]

*/

/*----------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------USE MODULE--------------------------------------------------------*/

void use_content()
{
    /*Locker ID is of the form LNN where NN is a two digit number*/
    /*locker ID declaration as a string*/
    string locker_id;
    /*Taking Input of the Locker Id*/
    cout << "Please, Enter the Locker Id" << endl;
    cin >> locker_id;

    string flag = "";
    /*ifstream: Stream class to read from files*/
    /*we can use our file streams the same way we are already used to use cin and cout,
    with the only difference that we have to associate these streams with physical files.*/

    ifstream config_input;
    /*opening the configure.txt and reading the data*/
    config_input.open("configure.txt");
    /*Checker for checking that the Locker ID is matching or not with the one given by the user and the
    one in configure.txt*/
    long long LockerIdMatch = 0;

    /*In this loop;
    The pointer config_input will go through the lines of configure.txt line by line and will check
    the first 3 characters of every line and try to see if it matches with the locker_id entered by the user */

    /*Whenever the pointer hits a '\n, it will change it's line*/
    while (getline(config_input, flag, '\n'))
    {
        /*Inserting the empty flag with data and checking the first 3 char of (0,1,2) of a particular row and checking it with
        the locker_id entered by the user*/

        /*If found the we'll simply make our checker LockerIdMatch to 1 indicating that the locker_id is found
        in the configure.txt file and then simply break out of the loop*/
        if (flag.substr(0, 3) == locker_id)
        {
            cout << " The Locker ID is found in the configure.txt file" << endl;
            LockerIdMatch = 1;
            break;
        }
    }

    /*If the checker remains as 0, this means the locker_id is not found in the configure.txt file */
    if (LockerIdMatch == 0)
    {
        cout << "\nCan't find the Locker ID entered, not found in configure.txt\n";
        /*Closing the file pointer*/
        config_input.close();
        return;
    }

    /*Closing the file pointer*/
    config_input.close();
    string num_at_moment = "";

    /*A stringstream associates a string object with a stream allowing you to read from the string as if it were a stream (like cin)*/
    /*Copying will starting from the 4th char as the first 3 characters would be for locker_id */

    stringstream ss(flag.substr(4));
    /*Untill the stream hits the '\t' char it will traverse through the row */

    getline(ss, num_at_moment, '\t');
    /*The first time it hits a tab, then we know we got the number of primes as per the sequence given in the question*/
    /*Hence we convert that stored string into integer to use further in loops using stoi*/
    long long num_of_primes = stoi(num_at_moment);

    /*Declaration of the prime numbers array*/
    long long prime_number_array[num_of_primes];

    for (long long i = 0; i < num_of_primes; i++)
    {
        /*Again, whenever a '\t' is hitted, then we'll get different primes in a row
        and similarly storing them with indexes in primes array after converting the string into integer*/
        getline(ss, num_at_moment, '\t');
        prime_number_array[i] = stoi(num_at_moment);
    }

    /*Declaration of the user keys array*/
    long long user_keys_array[num_of_primes];

    /*Taking the input from the user for the user keys(this we have to remember first exactly with sequence)*/
    for (long long i = 0; i < num_of_primes; i++)
    {
        cout << "Please, Enter the User Key: " << (i + 1) << endl;
        cin >> user_keys_array[i];
    }

    /*Applying Chinese Remainder Theorem*/

    /*intialize product as 1*/
    long long prod = 1;

    /*calculating the product*/
    for (long long i = 0; i < num_of_primes; i++)
    {
        prod *= prime_number_array[i];
    }

    /*Declaration of the result*/
    long long result = 0;

    /*Applying the above given formula for Chinese Reminder Theorem*/
    for (long long i = 0; i < num_of_primes; i++)
    {
        long long pp = prod / prime_number_array[i];
        long long res_helper = MultiplicativeInverseUnderModuloM(pp, prime_number_array[i]);
        long long ans = user_keys_array[i] * res_helper * pp;
        result += ans;
    }

    /*The access key which we've regenerated using Chinese Reminder Theorem*/
    long long access_key = result % prod;
    cout << "\nThe Key Generated (L) back using Chinese Remainder Theorem is:\n";
    cout << access_key << endl;
    return;
}
