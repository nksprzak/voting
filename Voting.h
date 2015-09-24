#ifndef Voting_h
#define Voting_h


#include <iostream> // istream, ostream
#include <string>   // string
#include <utility>  // pair
#include <vector>

using namespace std;

class Vote
{
	public:
		vector<int> prefs;
		int index = 0;
};

class Canidate
{
	public:
		string name;
		int vote_total = 0;
		int can_num;
		vector<Vote> votes;
		bool is_loser = false;
};



void voting_solve(istream& r, ostream& w);

#endif