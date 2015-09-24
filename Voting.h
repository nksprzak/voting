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
		int current_first;
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

/**
 *@param r an istream 
 *@param w an ostream
 */
void voting_solve(istream& r, ostream& w);

vector<Canidate> voting_read (istream& r, int& total_votes);

vector<int> process_votes(vector<Canidate>& c, int total_votes);

#endif