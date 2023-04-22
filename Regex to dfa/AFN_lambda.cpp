#include "AFN_lambda.h"
std::set<int> AFN_lambda::getQ()
{
    return Q;
}
std::set<char> AFN_lambda::getSigma()
{
    return sigma;
}
std::unordered_map<std::pair<int, char>, std::set<int>, hashiforlambda> AFN_lambda::getDeltha()
{
    return deltha;
}
int AFN_lambda::getStareInitiala()
{
    return stareInitiala;
}
int AFN_lambda::getStareFinala()
{
    return stareFinala;
}
//lambda este reprezentat de caracterul #
AFN_lambda AFN_lambda::sau(AFN_lambda l1, AFN_lambda l2, int contor)
{
    {
        //operatia de |
        AFN_lambda aux;
        aux.stareInitiala = contor;
        aux.stareFinala = contor + 1;
        aux.Q.insert(contor);
        aux.Q.insert(contor + 1);
        aux.Q.insert(l1.Q.begin(), l1.Q.end());
        aux.Q.insert(l2.Q.begin(), l2.Q.end());
        aux.sigma = l1.sigma;
        aux.sigma.insert(l2.sigma.begin(), l2.sigma.end());
        aux.deltha = l1.deltha;
        aux.deltha.insert(l2.deltha.begin(), l2.deltha.end());
        {std::set<int>intermediar;
        intermediar.insert(l1.stareInitiala);
        intermediar.insert(l2.stareInitiala);
        aux.deltha.insert({ std::make_pair(contor, '#'),intermediar }); }
        {std::set<int>intermediar;
        intermediar.insert(contor + 1);
        aux.deltha.insert({ std::make_pair(l1.stareFinala,'#'),intermediar });
        aux.deltha.insert({ std::make_pair(l2.stareFinala,'#'),intermediar }); }
        return aux;
    }
}

int precedenta(char t)
{
    if (t == '(')
        return 0;
    if (t == '|')
        return 1;
    if (t == '.')
        return 2;
    if (t == '*')
        return 3;
}

std::vector<char> AFN_lambda::formapoloneza(std::string sir)
{
    std::vector<char>pl;
    std::stack<char>op;
    for (int i = 0; i < sir.length(); i++)
    {
        char E = sir[i];
        if (E == ' ');
        else {
            if (isalpha(E))
            {
                pl.push_back(E);
            }
            else
            {
                if (E == '(')
                    op.push('(');
                else
                {
                    if (E == ')')
                    {
                        while (!op.empty() && op.top() != '(')
                        {
                            pl.push_back(op.top());
                            op.pop();
                        }
                        op.pop();
                    }
                    else
                    {
                        while (!op.empty() && precedenta(E) <= precedenta(op.top()))
                        {
                            pl.push_back(op.top());
                            op.pop();
                        }
                        op.push(E);
                    }
                }
            }
        }
    }
    while (!op.empty())
    {
        pl.push_back(op.top());
        op.pop();

    }
    return pl;
}

bool verificareoperatori(char t)
{
    if (t == '.' || t == '*' || t == '|')
        return true;
    return false;
}

bool AFN_lambda::verificareerori(std::string sir) //posibil neexhaustiv
{
    std::stack<char>paranteze;
    for (int i = 0; i < sir.length(); i++)
    {
        if (!verificareoperatori(sir[i]) && !verificareoperatori(sir[i + 1]) && isalpha(sir[i]) && isalpha(sir[i + 1]))
            return false;
        if (verificareoperatori(sir[i]) && verificareoperatori(sir[i + 1]) && sir[i] != '*')
            return false;
        if (!isalpha(sir[i]) && !verificareoperatori(sir[i]) && sir[i] != '(' && sir[i] != ')' && sir[i] != ' ')
            return false;
        if ((sir[i] == '.' || sir[i] == '|') && !isalpha(sir[i - 1]) && !isalpha(sir[i + 1]))
            return false;
        if (sir[i] == '(')
        {
            paranteze.push(sir[i]);
            if (i != 0 && isalpha(sir[i - 1]))
                return false;
        }
        if (sir[i] == ')')
        {
            if (i != sir.length() - 1 && isalpha(sir[i + 1]))
                return false;
            if (paranteze.empty() || paranteze.top() != '(')
                return false;
            else paranteze.pop();
        }
    }
    if (!paranteze.empty())
        return false;
    return true;
}

AFN_lambda AFN_lambda::concatenare(AFN_lambda l1, AFN_lambda l2)
{
    {
        //operatia de .
        AFN_lambda aux;
        aux.stareInitiala = l1.stareInitiala;
        aux.stareFinala = l2.stareFinala;
        aux.Q = l1.Q;
        aux.Q.insert(l2.Q.begin(), l2.Q.end());
        aux.Q.erase(aux.Q.find(l2.stareInitiala));
        aux.sigma = l1.sigma;
        aux.sigma.insert(l2.sigma.begin(), l2.sigma.end());
        aux.deltha = l1.deltha;
        std::unordered_map < std::pair<int, char>, std::set<int>, hashiforlambda>::iterator it;
        for (it = l2.deltha.begin(); it != l2.deltha.end(); it++)
        {
            if (it->first.first == l2.stareInitiala)
            {
                aux.deltha.insert({ std::make_pair(l1.stareFinala,it->first.second),it->second }); //starea initiala a automatului 2 este substituita de starea finala a automatului 1
            }
            else aux.deltha.insert({ *it });
        }

        return aux;
    }
}

AFN_lambda AFN_lambda::stelare(AFN_lambda l, int contor)
{
    {
        //operatia de *
        AFN_lambda aux;
        aux.stareInitiala = contor;
        aux.stareFinala = contor + 1;
        aux.Q = l.Q;
        aux.Q.insert(contor);
        aux.Q.insert(contor + 1);
        aux.sigma = l.sigma;
        aux.deltha = l.deltha;
        {
            std::set<int>intermediar;
            intermediar.insert(contor + 1);
            intermediar.insert(l.stareInitiala);
            aux.deltha.insert({ std::make_pair(contor,'#'),intermediar });
            aux.deltha.insert({ std::make_pair(l.stareFinala,'#'),intermediar });
        }
        return aux;
    }
}

void AFN_lambda::inCatePotAjungeCuLambda(int start, std::set<int>& valori_sosire)
{
    std::set<int> s = deltha[std::make_pair(start, '#')];
    for (int i : s)
        valori_sosire.insert(i);

    for (int i : s)
        inCatePotAjungeCuLambda(i, valori_sosire);
    valori_sosire.insert(start);
}

std::set<int> AFN_lambda::aplicaSimbolPeMultime(std::set<int> multime, char c)
{
    std::set<int> s,aux;
    for (auto x : multime)
    {
        aux = deltha[std::make_pair(x, c)];
        for (auto y : aux)
            s.insert(y);
        aux.clear();
    }
    return s;
}

std::set<int> AFN_lambda::lambdaInchidere(std::set<int> x)
{
    std::set<int> result,ret;
    for (int i : x)
    {
        result.clear();
        inCatePotAjungeCuLambda(i, result);
        for (int r : result)
        {
            ret.insert(r);
        }
    }
    return ret;
}

//std::set<int> AFN_lambda::aplicareDeltha(std::set<int> s, char c)
//{
//    for (int x : s)
//    {
//
//    }
//    return set<int>();
//}

void AFN_lambda::evaluareexpresie(std::vector<char> pl)
{
    {
        std::stack<AFN_lambda>numar;
        int contor = 0;
        int i = 0;
        while (i < pl.size())
        {
            if (i != pl.size() - 1 && isalpha(pl[i]))
            {

                AFN_lambda val; //transformare in automat in functie de valorile contorului
                val.stareInitiala = contor;
                val.stareFinala = contor + 1;
                val.Q.insert(contor);
                val.Q.insert(contor + 1);
                val.sigma.insert(pl[i]);
                std::set<int>aux;
                aux.insert(contor + 1);
                val.deltha.insert({ std::make_pair(contor, pl[i]), aux });
                numar.push(val);
                contor += 2;

            }
            else
            {
                AFN_lambda rez;
                switch (pl[i])
                {
                case '|':
                {AFN_lambda x = numar.top();
                numar.pop();
                AFN_lambda y = numar.top();
                numar.pop();
                rez = sau(x, y, contor);
                contor += 2;
                break;
                }
                case '.':
                { AFN_lambda x = numar.top();
                numar.pop();
                AFN_lambda y = numar.top();
                numar.pop();
                rez = concatenare(y, x);
                break; }
                case '*': {
                    AFN_lambda x = numar.top();
                    numar.pop();
                    rez = stelare(x, contor);
                    contor += 2;
                    break; }


                }
                numar.push(rez);

            }
            i++;
        }

        *this = numar.top(); //initializarea obiectului curent cu rezultatul transformarii
    }
}

void AFN_lambda::printAutomaton()
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
    std::cout << "Stare finale:";
    std::cout << stareFinala << " ";
    std::cout << std::endl;

    for (auto it = deltha.begin(); it != deltha.end(); ++it)
    {
        std::cout << it->first.first << "," << it->first.second << "-";
        for (int j : it->second)
        {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}

void AFN_lambda::readAutomaton()
{
    std::ifstream f;
    f.open("automat.txt");
    if (f.is_open())
    {
        std::string linie;
        char aux;
        getline(f, linie);
        aux = std::stoi(linie);
        stareInitiala = aux;

        getline(f, linie);
        aux = std::stoi(linie);
        stareFinala = aux;

        getline(f, linie);
        for (int i = 0;i < linie.size();i++)
            if (linie[i] != ' ')
            {
                sigma.insert(linie[i]);
            }

        for (int i = stareInitiala;i <= stareFinala;i++)
            Q.insert(i);

        int n;
        f >> n;
        f.get();
        for (int i = 0;i < n;i++)
        {
            int qiu;
            char pornire;
            getline(f, linie);
            int j = 0;
            std::string aux = "";
            while (linie[j] != ',')
            {
                j++;
            }
            qiu = stoi(linie.substr(0, j));
            j++;
            pornire = linie[j];
            j++;
            j++;
            std::set<int> v;
            int s = j;
            while (j < linie.size())
            {
                while (linie[j] != ',' && j < linie.size())
                    j++;
                v.insert(stoi(linie.substr(s, j)));
                j++;
                s = j;
            }
            deltha[std::make_pair(qiu, pornire)] = v;
        }
        f.close();
    }
    else
        std::cout << "Nu s-a putut deschide fisierul";
}
