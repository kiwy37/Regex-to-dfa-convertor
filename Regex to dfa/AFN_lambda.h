#pragma once
#include<unordered_map>
#include<string>
#include<stack>
#include<set>
#include<iostream>
#include<fstream>

struct hashiforlambda
{
    size_t operator()(const std::pair<int, char>& pair) const
    {
        return pair.first * 12378 + pair.second * 3984;
    }
};

class AFN_lambda
{
private:
    std::set<int> Q;
    std::set<char> sigma;
    std::unordered_map<std::pair<int, char>, std::set<int>, hashiforlambda> deltha;
    int stareInitiala;
    int stareFinala;

    AFN_lambda sau(AFN_lambda l1, AFN_lambda l2, int contor);
    AFN_lambda concatenare(AFN_lambda l1, AFN_lambda l2);
    AFN_lambda stelare(AFN_lambda l, int contor);


public:
    std::set<int> lambdaInchidere(std::set<int> x);
    std::set<int> aplicareDeltha(std::set<int> s, char c);
    void printAutomaton();
    void readAutomaton();
    void inCatePotAjungeCuLambda(int start, std::set<int>& valori_sosire);
    std::set<int> aplicaSimbolPeMultime(std::set<int> multime, char c);
    void evaluareexpresie(std::vector<char>pl); //pentru apelarea acestei functii, trebuie intai construita forma poloneza prin intermediul functiei din main
    std::vector<char> formapoloneza(std::string sir);
    bool verificareerori(std::string sir);

    std::set<int> getQ();
    std::set<char> getSigma();
    std::unordered_map<std::pair<int, char>, std::set<int>, hashiforlambda> getDeltha();
    int getStareInitiala();
    int getStareFinala();
};
