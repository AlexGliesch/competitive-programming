#include <iostream>
#include <string>
#include <vector>

using namespace std;


bool is_vowel(char x)
{
    switch(x)
        {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                return true;
                break;
        }
    return false;
}

int main()
{
    string line;
    cin >> line;
    int n_vowels = 0;
    bool starts_with_vowel = ((line[0] == 'a') or (line[0] == 'e') or (line[0] == 'i') or (line[0] == 'o') or (line[0] == 'u'));
    for (char c: line)
    {
        switch(c)
        {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                n_vowels++;
                break;
        }
    }
    if (n_vowels == 0)
        cout << 1 << endl;
    else if(n_vowels == 1 and (not starts_with_vowel))
        cout << 0 << endl;
    else if(n_vowels % 2 == 1)
    {
        int find_me = (n_vowels + 1) / 2;
        int vowel_idx = -1;
        for (int i = 0; i < line.size(); ++i)
        {
            if (is_vowel(line[i]))
            {
                find_me--;
                if (find_me == 0)
                {
                    vowel_idx = i;
                    break;
                }
            }
        }
        int n_cons = 0;
        for (int i = vowel_idx + 1; not is_vowel(line[i]) and i < line.size(); ++i)
        {
            n_cons++;
        }
        cout << n_cons + 1 << endl;
    }
    else
    {
        int find_me = (n_vowels / 2) + 1;
        int vowel_idx = -1;
        for (int i = 0; i < line.size(); ++i)
        {
            if (is_vowel(line[i]))
            {
                find_me--;
                if (find_me == 0)
                {
                    vowel_idx = i;
                    break;
                }
            }
        }
        int n_cons = 0;
        for (int i = vowel_idx - 1; i >= 0 and not is_vowel(line[i]); --i)
        {
            n_cons++;
        } 
        cout << n_cons + 1 << endl;       
    }
}
