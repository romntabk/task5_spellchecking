#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <set>
#include <iomanip> // setw
#include <vector>

#include "dictionary.h"

using namespace std;

void lower(string& s);
string stripPunct(const string& s);
void checkSpelling(ifstream& in, Dictionary& dict);



// program arguments to run, example: main.exe ../../res/wordlist.txt ../../res/test.txt
int main(int argc, char* argv[]) {
	
	// Output usage message if improper command line args were given.
	if (argc != 3)
    {
		cerr << "Usage: " << argv[0] << " wordlist_filename input_file\n";
		return EXIT_FAILURE;
	}

	ifstream inf(argv[2]);
	if (! inf) 
    {
		cerr << "Could not open " << argv[2] << "\n";
		return EXIT_FAILURE;
	}
	
	// Read dictionary, but let user know what we are working on.
	cout << "Loading dictionary, this may take awhile...\n";

	Dictionary d(argv[1]);
    
	checkSpelling(inf, d);

	inf.close();
	system("pause");
	return EXIT_SUCCESS;
}

void checkSpelling(ifstream& in, Dictionary& dict) {

	int line_number = 0;

	while (in) 
    {
		line_number++;
		set<string> totest;
		string line;
		getline(in, line);

  	    stringstream ss (stringstream::in | stringstream::out);
		ss << line;
		
		string word;
		while (ss >> word) 
        {
			// TODO: Complete the spell check of each word
			lower(word);
			word = stripPunct(word);
			if (!dict.search(word))
			{
				vector<string> variants;
				//Transposing of adjacent letters
				for (size_t i = 0; i < word.length()-1; i++)
				{
					string testword = word;
					swap(testword[i], testword[i + 1]);
					if (dict.search(testword))
						variants.push_back(testword);
						//cout << " " << testword;
				}
				//Removal of each letter
				for (size_t i = 0; i < word.length(); i++)
				{
					string testword = word;
					testword.erase(i, 1);
					if (dict.search(testword))
						variants.push_back(testword);

//						cout << " " << testword;
				}
				//Replacement of each letter
				for (size_t i = 0; i < word.length(); i++)
				{
					string testword = word;
					for (char c = 'a'; c <= 'z'; c++)
					{
						if (c != word[i])
						{
							testword[i] = c;
							if (dict.search(testword))
								variants.push_back(testword);
							//cout << " " << testword;
						}
					}
				}
				//Inserting any letter at any position in a word
				for (size_t i = 0; i <= word.length(); i++)
				{
					for (char c = 'a'; c <= 'z'; c++)
					{
						string testword = word;
						testword=testword.insert(i,1, c);
						if (dict.search(testword))
							variants.push_back(testword);
							//cout << " " << testword;
					}
				}
				Dictionary uniq;
				cout << line_number << " " << word << ":";
				if (variants.size() == 0)
					cout << " -none-";
				else
				{
					for (size_t i = 0; i < variants.size(); i++)
					{
						if (!uniq.search(variants[i]))
						{
							cout << " " << variants[i];
							uniq.insert(variants[i]);
						}
					}
				}
				cout << endl;
			}
		}
	}
}

void lower(string& s) {

    // Ensures that a word is lowercase
	for (size_t i = 0; i < s.length(); i++)
    {
		s[i] = tolower(s[i]);
	}
}

string stripPunct(const string& s) {

	// Remove any single trailing
	// punctuation character from a word.  
	if (ispunct(s[s.length() - 1]) ) 
    {
		return s.substr (0, s.length() - 1);
	}
	else 
    {
		return s;
	}
}
