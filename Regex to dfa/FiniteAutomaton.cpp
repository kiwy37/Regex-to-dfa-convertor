#include "FiniteAutomaton.h"
using namespace std;

struct comp {
	bool operator()(pair<int, set<int>> a, pair<int, set<int>> b) const
	{
		if (a.first > b.first)
			return true;
		return false;
	}
};

FiniteAutomaton FiniteAutomaton::LambdaToNonLambda(AFN_lambda l) {

	sigma = l.getSigma();
	stareFinala.push_back(0);
	int x = l.getStareInitiala();
	set<int> rezultat_lambda_inchidere_initiala;
	l.inCatePotAjungeCuLambda(x, rezultat_lambda_inchidere_initiala);
	Q.insert(Q.size());

	queue<pair<int, set<int>>> coada;
	int cont = 0;
	set<pair<int, set<int>>, comp> set_de_verificari;
	set_de_verificari.insert(make_pair(cont, rezultat_lambda_inchidere_initiala));
	coada.push(make_pair(cont, rezultat_lambda_inchidere_initiala));
	cont++;
	stareInitiala = 0;

	while (coada.size())
	{
		pair<int, set<int>> qAnalizat = coada.front();
		coada.pop();
		for (char c : sigma)
		{
			set<int> rez = l.aplicaSimbolPeMultime(qAnalizat.second, c);
			if (rez.size())
			{
				int t = set_de_verificari.size();
				int temp = cont + 1;
				int ok = 1;
				for (auto e : set_de_verificari)
				{
					if (e.second == rez)
					{
						ok = 0;
						break;
					}
				}

				if (ok == 1)
				{
					set_de_verificari.insert(make_pair(temp, rez));
					set<int> rez2 = l.lambdaInchidere(rez);
					set_de_verificari.insert(make_pair(cont, rez2));
					deltha[make_pair(qAnalizat.first, c)].push_back(cont);
					coada.push(make_pair(cont, rez2));
					cont++;
					stareFinala[0]=cont;
					Q.insert(Q.size());
				}
				else
				{
					for (auto e : set_de_verificari)
					{
						if (e.second == rez)
						{
							deltha[make_pair(qAnalizat.first, c)].push_back(e.first-1);
							stareFinala[0]=e.first - 1;
							break;
						}
					}
				}
			}
		}
	}


	return FiniteAutomaton();
}

void FiniteAutomaton::printAutomaton()
{
	std::cout << "Q:";
	for (int q : Q)
	{
		std::cout << q << " ";
	}
	std::cout << std::endl;
	std::cout << "Sigma:";
	for (char c : sigma)
	{
		std::cout << c << " ";
	}
	std::cout << std::endl;
	std::cout << "Stare initiala: ";
	std::cout << stareInitiala << " ";
	std::cout << std::endl;
	std::cout << "Stare finala:";
	for(auto i:stareFinala)
	std::cout << i << " ";
	std::cout << std::endl;

	for (auto it = deltha.begin(); it != deltha.end(); ++it)
	{
		std::cout << it->first.first << "," << it->first.second << "-";
		for(auto i:it->second)
		cout << i<<" ";
		std::cout << std::endl;
	}
}

bool FiniteAutomaton::VerifyAutomaton()
{
	if (Q.empty() || sigma.empty() || stareInitiala == ' ' || stareFinala.empty() || deltha.empty())
	{
		return 0;
	}
	char state = 0;
	std::unordered_set <char> visited;
	std::queue <char> queue;
	queue.push(stareInitiala);
	visited.insert(stareInitiala);
	while (!queue.empty())
	{
		char currentState = queue.front();
		for (const auto& input : sigma)
		{
			vector<int> futureStates = deltha[{ currentState, input }];
			for (const auto& futureState : futureStates)
			{
				if (visited.find(futureState) == visited.end())
				{
					visited.insert(futureState);
					queue.push(futureState);
				}
			}
		}
		queue.pop();
	}
	for (const auto& finalState : stareFinala)
	{
		if (visited.find(finalState) != visited.end())
			return 1;
	}
	return 0;
}

bool FiniteAutomaton::CheckWord(std::string cuv)
{
	std::set<char> lista;

	lista.insert(stareInitiala);
	for (int i = 0;i < cuv.size();i++)
	{
		std::set<char> aux;
		for (auto it = lista.begin(); it != lista.end(); it++)
		{
			std::pair<char, char> p = std::make_pair(*it, cuv[i]);
			it = lista.find(*it);
			for (int k = 0;k < deltha[p].size();k++)
				aux.insert(deltha[p][k]);
		}
		lista.clear();
		for (auto x = aux.begin(); x != aux.end(); x++)
			lista.insert(*x);
	}
	for (auto i : stareFinala)
	{
		auto pos = lista.find(i);
		if (pos != lista.end())
			return true;
	}
	return false;
}

bool FiniteAutomaton::IsDeterministic()
{
	for(auto i:Q)
		for (auto j : sigma)
		{
			std::pair<int, char> p = std::make_pair(i, j);
			if (deltha[p].size() > 1)
				return false;
		}
	return true;
}