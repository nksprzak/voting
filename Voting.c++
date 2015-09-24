#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
#include <vector>

#include "Voting.h"

using namespace std;


vector<Canidate> voting_read (istream& r, int& total_votes)
{
	int num_of_cands, num_votes;
	vector<Canidate> canidates;
	string::size_type sz;
	string s;

	// Read the number of canidates in the election.
	getline(r,s);
	num_of_cands = stoi(s,&sz);
	num_votes = 0;
	// Iterate through lines with canidates and add them to the vector with basic info.
	for(int y = 0; y < num_of_cands; y++)
	{
		Canidate c1;
		getline(r,s);
		c1.name = s;
		c1.can_num = y;
		canidates.push_back(c1);
	}
	// Iterate through the votes until you hit a blank line indicating end of votes. 
	while(getline(r,s) && !s.empty())
	{
		Vote v1;
		vector<int> buf;
		int temp;
		stringstream in(s);
		// Using a while loop to process the vote string and pushing the preferences.
		while(in >> temp)
		{
			if(buf.empty()) 
			{
				v1.current_first = temp-1;
				canidates[temp-1].vote_total += 1;
			}
			   buf.push_back(temp);
		}
		num_votes++;
		v1.prefs = buf;
		canidates[v1.current_first].votes.push_back(v1);	
	}
	total_votes = num_votes;
	return canidates;
}

vector<int> process_votes(vector<Canidate>& c, int total_votes)
{
	vector<int> winners, losers;
	while(true)
	{
		losers.clear();
		int low = 100000;
		int high = 0;
		// Iterate through all the canidates to determine if someone has an outright win 
		// or to  determine losers(who have votes not ones with zero votes)
		for(vector<Canidate>::size_type x = 0; x != c.size(); x++)
		{
			if(!c[x].is_loser)
			{
				if(c[x].vote_total > (total_votes/2))
				{
					winners.push_back(x);
					return winners;
				}
				if(c[x].vote_total < low && c[x].vote_total != 0)
				{
					 low = c[x].vote_total;
					 losers.clear();
					 losers.push_back(x);
				}
				else if(c[x].vote_total == low) losers.push_back(x);
				if(c[x].vote_total > high) high = c[x].vote_total;
			}
		}
		// Catching the perfect tie case in which the low and high would equal
		if(high == low)
		{
			winners = losers;
			return winners;
		}
		// Set the losers bool flags to true so we don't have to check to see if they win later
		for(vector<Canidate>::size_type y = 0; y!=c.size(); y++)
		{
			if(c[y].vote_total == low || c[y].vote_total == 0) c[y].is_loser = true;
		}
		// Reassign the loser votes by iterating through each of their votes and assigning to their next
		// prefence, checking to see if that preference isn't also a loser.
		for(vector<Canidate>::size_type z = 0; z!=c.size(); z++)
		{
			if(c[z].is_loser && c[z].vote_total != 0)
			{
				for(vector<Vote>::size_type a = 0; a != c[z].votes.size(); a++)
				{
					int next = c[z].votes[a].index;
					int buf = c[z].votes[a].prefs[next++];
					while(c[buf-1].is_loser)
					{
						buf = c[z].votes[a].prefs[next++];
					}
					c[buf-1].vote_total += 1;
					Vote b = c[z].votes[a];
					c[buf-1].votes.push_back(b);
				}
				c[z].vote_total = 0;
			}
		}
	}
	return winners;
}
void voting_solve(istream& r, ostream& w)
{
	string s;
	int num_of_cands;
	vector<Canidate> canidates;
	int length;
	int num_votes = 0;
	string::size_type sz;
	// Get number of elections
	getline(r,s);
	length = stoi(s,&sz);
	// Go past the blank line
	getline(r,s);
	for(int x = 0; x < length; x++)
	{
		canidates = voting_read(r,num_votes);
		vector<int> winners = process_votes(canidates, num_votes);
		for(vector<int>::size_type i = 0; i != winners.size(); i++)
		{
			w << canidates[winners[i]].name << endl;
			if(i == winners.size()-1 && x != length-1) w << endl;
		}
		canidates.clear();
	}

}
