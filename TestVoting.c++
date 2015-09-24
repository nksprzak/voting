#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"

#include "Voting.h"

using namespace std;


TEST(VotingFixture, read_1)
{
	istringstream s("1\nJoe\n1");
	int num = 1;
	vector<Canidate> c = voting_read(s,num);
	ASSERT_EQ("Joe",c[0].name);
}

TEST(VotingFixture, read_2)
{
	istringstream s("2\nJoe\nBob\n1 2\n2 1");
	int num = 2;
	vector<Canidate> c = voting_read(s,num);
	ASSERT_EQ("Joe",c[0].name);
	ASSERT_EQ("Bob",c[1].name);
}

TEST(VotingFixture, read_3)
{
	istringstream s("3\nJoe\nBob\nSusie\n1 2\n2 1");
	int num = 3;
	vector<Canidate> c = voting_read(s,num);
	ASSERT_EQ("Joe",c[0].name);
	ASSERT_EQ("Bob",c[1].name);
	ASSERT_EQ("Susie",c[2].name);
}



TEST(VotingFixture, process_1)
{
	istringstream s("3\nJoe\nBob\nSusie\n1 2 3\n");
	int num = 3;
	int votes = 1;
	vector<Canidate> c = voting_read(s,num);
	vector<int> win = process_votes(c,votes);
	ASSERT_EQ(0,win[0]);
}


TEST(VotingFixture, process_2)
{
	istringstream s("2\nJoe\nBob\n1 2\n2 1\n");
	int num = 2;
	int votes = 2;
	vector<Canidate> c = voting_read(s,num);
	vector<int> win = process_votes(c,votes);
	ASSERT_EQ(0,win[0]);
	ASSERT_EQ(1,win[1]);
}



TEST(VotingFixture, process_3)
{
	istringstream s("3\nJoe\nBob\nSusie\n1 2 3\n2 1 3\n1 3 2\n2 3 1\n3 1 2\n");
	int num = 3;
	int votes = 5;
	vector<Canidate> c = voting_read(s,num);
	vector<int> win = process_votes(c,votes);
	ASSERT_EQ(0,win[0]);
}


TEST(VotingFixture, solve_1)
{
	istringstream r("1\n\n2\nJoe\nBob\n1 2\n");
	ostringstream w;
	voting_solve(r,w);
	ASSERT_EQ("Joe\n",w.str());
}

TEST(VotingFixture, solve_2)
{
	istringstream r("2\n\n2\nJoe\nBob\n1 2\n\n1\nBob\n1\n");
	ostringstream w;
	voting_solve(r,w);
	ASSERT_EQ("Joe\n\nBob\n",w.str());
}

TEST(VotingFixture, solve_3)
{
	istringstream r("1\n\n3\nJoe\nBob\nSusie\n1 2 3\n2 1 3\n1 3 2\n2 3 1\n3 1 2\n");
	ostringstream w;
	voting_solve(r,w);
	ASSERT_EQ("Joe\n",w.str());
}





