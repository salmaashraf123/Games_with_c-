// File: A1_T1_S8_20231073.cpp
// Purpose: 1:Correcting Spaces and Letters , 4 : Finding Prime Numbers , 7 : Domino solving , 10 :Censorship Avoidance
// Author: Salma Ashraf Hassan
// Section: S8
// ID: 20231073
// TA: Unknown
// Date: 10 Oct 2024
//====================================================================================================
/*This program is divided into four programs
 *1-Correcting Spaces and Characters (program_1):
* This program reads sentences until a sentence ending with a period (.) is entered.
* It converts the first character of the sentence to uppercase and the other characters to lowercase.
* The program also replace multiple spaces to single space.Finally, it prints the corrected sentence.
* ===================================================================================================
* 2-Printing Prime Numbers (program_2):
* This program reads an integer from the user using safe input methods.
* It uses the Sieve of Eratosthenes algorithm to determine all prime numbers from 2 up to the entered number.
* All identified prime numbers are printed.
* =====================================================================================================
* 3-Domino Game (program_3):
* This program reads a specified number of domino pairs from the user.
* It validates the inputs and creates structure of type dominoT representing the domino sides.
* A recursive function is used to check if a sequence of dominoes can be formed.
* If a sequence can be formed, the program prints the order; if not, it notifies the user that forming a sequence is impossible.
* =============================================================================================================================
* 4-Changing Text to Avoid Censorship (program_4):
* This program reads a file name containing text (input_text.txt) and another file containing the lookup table (alter.txt).
* It opens the files, reads the contents, and replaces the specified words in the text with their alternatives from the lookup table.
* The modified text is saved in a new file (output_text.txt), and a message is displayed to the user that is completed of the process.
*=======================================================================================================================================
*/
#include <bits/stdc++.h>
using namespace std;
void program_1 ()
{
    vector<char>sentence;
    int ver = 1 ;
    cin.ignore();
    //read input lines until a period (.) is encountered at the end of a line
    cout << "Please enter your sentences\n";
    while(ver)
    {
        string b;
        getline(cin , b);
        // Add each character of the string to the vector
        for(int i = 0 ; i < b.size() ; i++)
        {
            sentence.push_back(b[i]);
        }
        // If the last character in the line is a period (.), stop reading
        if(b[b.size()-1] == '.')
        {
            ver = 0;
        }
        // Add a space after each line including the final line
        sentence.push_back(' ');
    }
    vector<char>result;
    // check if the first letter has been found
    bool found_first = false ;
    for(int i = 0 ; i < sentence.size(); i++)
    {
        // If we find the first alphabetic character and it's not capitalized
        if(isalpha(sentence[i]) && !found_first)
        {
            sentence[i] = toupper(sentence[i]);
            found_first = true;
        }
        // After the first letter is found, convert all other characters to lowercase
        else if(found_first)
        {
            sentence[i] = tolower(sentence[i]);
        }
        // convert multiple spaces to single space only
        if(sentence[i] == ' ' && sentence[i+1] == ' ' && i+1 != sentence.size())
        {
            continue;
        }
        // Add the character to the vector
        result.push_back(sentence[i]);
    }
    // If the last character in the vector is a space, remove it.
    if(result.back() == ' ')
    {
        result.pop_back();
    }
    // the final formatted sentence
    for(int i = 0 ; i < result.size() ; i++)
    {
        cout << result[i] ;
    }

}
void program_2 ()
{
    long long n;
    cout << "Enter a number: ";
    // Loop until a valid number is entered
    cin.ignore();
    while(true)
    {
        string s ;
        getline(cin , s);
        bool valid = true;
        for(char s2 : s)
        {
            // Check if the character is not a digit
            if(!isdigit(s2))
            {
                valid = false;
                break;
            }
        }
        if(valid)
        {
            // Convert the string to a long long integer
            n = stoll(s);
            break;
        }
        else{
            cout << "Invalid input, please enter a valid number : ";
        }
    }
    vector<bool>check(n+1 , true);
    check[0] = false;
    check[1] = false;
    // the Sieve of Eratosthenes algorithm
    for(long long i = 2 ; i <= n ; i++)
    {
        if(check[i])
        {
            for(long long j = i ; j <= n ; j++)
            {
                if(j % i == 0 && j != i)
                {
                    check[j] = false;
                }
            }
        }
    }
    //track if any prime numbers are found
    bool found_prime = false;
    // print all numbers prime form 2 to the number.
    for(long long i = 2 ; i <=  n ; i++)
    {
        if(check[i])
        {
            cout << i << " ";
            found_prime = true;
        }
    }
    // If no prime numbers were found
    if(!found_prime)
    {
        cout <<"There are no prime numbers." ;
    }
    cout << endl;
}
// represent a domino piece with two sides
struct dominoT{
    int leftDots;
    int rightDots;
};
// Recursive function to determine if a chain of dominos can be solved
bool FormsDominoChain (vector<dominoT>&before , vector<dominoT>&res , int initial, vector<bool>&use)
{
    // Base case , if all domino pieces have been used
    if(initial == before.size())
    {
        return true;
    }
    for(int i = 0 ; i <before.size() ; i++)
    {
        if(!use[i])
        {
            if(initial == 0 || res[initial-1].rightDots == before[i].leftDots)
            {
                res.push_back({before[i].leftDots , before[i].rightDots});
                use[i]=true;
                if( FormsDominoChain( before , res , initial+1 , use))
                {
                    return true;
                }
                // If not successful, remove the last domino added
                res.pop_back();
                use[i] = false;
            }
        }
    }
    return false; // Return false if no valid chain can be formed
}
void program_3()
{
    cout << "please enter number of domino pairs : ";
    string num;
    long long t;
    cin.ignore();
    // Loop to ensure valid input for number of domino pairs
    while(true)
    {
        getline(cin , num);
        try{
            t = stoll(num); // Convert input to long long
            if(t > 0)
            {
                break;
            }
        }
        catch(const invalid_argument &){}
        cout << "Invalid input, please enter a positive integer : ";
    }
    string input , pieces = "";
    cout << "enter pieces of domino : ";
    getline(cin , input);
    // Validate input for domino pairs
    for(int i = 0 ; i < input.size() ; i++)
    {
        if(!((input[i] <= '6' & input[i] >= '0') || input[i]== ' '))
        {
            cout << "Invalid input ,try again and please enter correct domino pairs" << endl;
            return ;
        }
    }
    // extract digits from input to form domino pairs
    for(int i = 0 ; i < input.size() ; i++)
    {
        if(isdigit(input[i]))
        {
            pieces+=input[i];
        }
    }
    // Check if the number of digits matches the number of domino pieces
    if(pieces.size() != (t*2))
    {
        cout << "Not enough domino pairs" << endl;
        return ;
    }
    vector<dominoT> prep1;
    vector<dominoT> prep2;
    vector<bool> checked(pieces.size() , false);
    for(int i = 0 ; i<pieces.size()-1 ; i += 2)
    {
        prep1.push_back({int(pieces[i]-'0'),int(pieces[i+1]-'0')});
    }
    // Check if a valid domino chain can be formed
    if(!FormsDominoChain(prep1 , prep2 , 0 , checked))
    {
        cout << "NO , we can not solve it" << endl;
    }
    else {
        cout << "YES , we can solve it . this is its order : " << endl;
        for(int i = 0 ; i < prep2.size() ; i++)
        {
            if(i != prep2.size()-1)
            {
                cout << prep2[i].leftDots << "|" << prep2[i].rightDots << " - " ;
            }
            else{
                cout << prep2[i].leftDots << "|" << prep2[i].rightDots << endl ;
            }
        }
    }
}
void program_4()
{
    locale::global(locale(""));
    string fl1 , tb1 ;
    cin.ignore();
    cout << "please enter your file name that is named (input_text.txt)";
    while(true)
    {
        getline(cin , fl1);
        if(fl1 != "input_text.txt" )
        {
            cout << "Invalid input , please enter correct file name (input_text.txt) : ";
        }
        else
        {
            break;
        }
    }
    cout << "please enter your lookup table file name that named (alter.txt)";
    while(true)
    {
        getline(cin , tb1);
        if(tb1 != "alter.txt")
        {
            cout << "Invalid input , please enter correct lookup table file name (alter.txt) : ";
        }
        else
        {
            break;
        }
    }
    wifstream file(fl1);
    file.imbue(locale(file.getloc(), new codecvt_utf8<wchar_t>));
    wifstream alter_file(tb1);
    alter_file.imbue(locale(file.getloc(), new codecvt_utf8<wchar_t>));
    map<wstring, wstring>table;
    wstring l;
    if (!file.is_open())
    {
        wcerr << L"Error opening input file\n";
        return ;
    }
    if(!alter_file.is_open())
    {
        wcerr << L"Error opening look up table files\n";
        return ;
    }
    while (getline(alter_file, l))
    {
        wistringstream lr(l);
        wstring l2, altr_u;
        lr >> l2;
        lr >> altr_u;
        table[l2] = altr_u;
    }
    wstring line_1, line_2;
    while (getline(file, line_1))
    {
        line_2 += line_1 + L"\n";
    }
    wstringstream res1;
    wistringstream block(line_2);
    wstring word1;
    while (block >> word1)
    {
        if (table.find(word1) != table.end())
        {
            res1 << table[word1] << L" ";
        }
        else {
            res1 << word1 << L" ";
        }
    }
    wofstream out_file("output_text.txt");
    out_file.imbue(locale(file.getloc(), new codecvt_utf8<wchar_t>));
    if (!out_file.is_open()) {
        wcerr << L"Error opening output file\n";
        return ;
    }
    wstring line;
    while (getline(res1, line)) {
        out_file << line << L" " ;
    }
    cout << "Done , to show the output please open output_text.txt file" << endl;
    out_file.close();
    file.close();
    alter_file.close();
}
int main() {
    cout << "Dear user, Welcome to my program ^_^ \n";
    cout << "1 : Correcting spaces and letters\n";
    cout << "2 : Print prime numbers form 2 to input_number\n";
    cout << "3 : Domino playing using recursion\n";
    cout << "4 : Alter message to avoid censorship\n";
    cout << "Please choose what you want to do from 1 to 4 : ";
    string choice;
    // choose which the program will be run
    while(true)
    {
        cin >> choice;
        if(choice == "1")
        {
            program_1();
            break;
        }
        else if (choice == "2")
        {
            program_2();
            break;
        }
        else if(choice == "3")
        {
            program_3();
            break;
        }
        else if(choice == "4")
        {
            program_4();
            break;
        }
        else
        {
            cout << "Invalid input , please choose a number from 1 to 4 : ";
        }
    }
}
