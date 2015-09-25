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

/**
 *@param r an istream 
 *@param total an int
 *@return canidate vector filled in with votes
 * Reads in selected input to process for one election.
 * Runs in for loop from first line length to get every election.
 */

vector<Canidate> voting_read (istream& r, int& total_votes);

/**
 *@param c an canidate vector 
 *@param total an int
 * Determines the winner by figuring if anyone has more than half votes
 * or if there is a perfect tie. If not reassigns losers votes. 
 */

vector<int> process_votes(vector<Canidate>& c, int total_votes);

#endif