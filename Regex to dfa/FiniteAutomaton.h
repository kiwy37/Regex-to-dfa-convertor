#pragma once
#include<unordered_map>
#include<unordered_set>
#include<fstream>
#include<queue>
#include<stack>
#include<iostream>
#include<string>
#include<set>
#include"AFN_lambda.h"

struct hashi
{
	size_t operator()(const std::pair<int, char>& pair) const
	{
		return pair.first * 12378 + pair.second * 3984;
	}
};

class FiniteAutomaton
{
public:
	FiniteAutomaton LambdaToNonLambda(AFN_lambda l);
	bool VerifyAutomaton();
	void printAutomaton();
	bool CheckWord(std::string cuv);
	bool IsDeterministic();

private:
	std::set<int> Q;
	std::set<char> sigma;
	std::unordered_map<std::pair<int, char>, std::vector<int>, hashi> deltha;
	int stareInitiala;
	std::vector<int> stareFinala;
};
