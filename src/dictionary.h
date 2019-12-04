#ifndef  _DICTIONARY_H_ 
#define  _DICTIONARY_H_

#include  <iostream>
#include  <fstream>
#include  <vector>
#include  <list>
#include  <algorithm>
#include  <string>
#include  <stdlib.h>

#include  "hashset.h"
#include  "hashset.cpp"

using namespace std;

class hash_function
{
public:

    unsigned int operator()( const string& s )  const {
        //http://rsdn.org/forum/alg/360746.all
		int hash = 0;
		int i = 0;
		for(size_t i=0;i<s.length();i++)
			hash = (hash << 5) + hash + s[i];
		return hash;
        
    }
};

class equality
{
public:
    equality() {}
    bool  operator()( const string& A, const string& B )  const 
    {
        return  (A == B);
    }
};

class Dictionary: public HashSet<string, hash_function, equality> {

    // Complete definition
public:
	Dictionary(string filename);
	Dictionary() {}
};
#endif // _DICTIONARY_H_
