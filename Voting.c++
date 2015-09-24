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

	getline(r,s);
	num_of_cands = stoi(s,&sz);
	num_votes = 0;
	for(int y = 0; y < num_of_cands; y++)
	{
		Canidate c1;
		getline(r,s);
		c1.name = s;
		c1.can_num = y;
		canidates.push_back(c1);
	}
	while(getline(r,s) && !s.empty())
	{
		Vote v1;
		vector<int> buf;
		int temp;
		stringstream in(s);
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
	}

}
