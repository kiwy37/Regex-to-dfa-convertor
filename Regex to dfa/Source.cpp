#include <iostream>
#include <vector>
#include <algorithm>
#include "AFN_lambda.h"
#include "FiniteAutomaton.h"

int main()
{
    std::ifstream f("expresieRegulata.txt");  
    std::string aux;
    f >> aux;
    f.close();
    AFN_lambda l;
    if (l.verificareerori(aux))
    {
        FiniteAutomaton a;
        l.evaluareexpresie(l.formapoloneza(aux));
        a.LambdaToNonLambda(l);
        std::string cuvant;
		int op = 9;
        do {
            std::cout << "Meniu \n 1. Pentru afisarea automatului obtinut prin transformarea expresiei, tastati 1\n 2. Pentru afisarea expresiei regulate citite, tastati 2 \n 3. Pentru verificarea unui cuvant in automat, tastati 3\n 4. Pentru a iesi, tastati 4\n";

            std::cin >> op;
            system("CLS");
            switch(op)
            {
            case 1:
                std::cout << "Meniu \n 1. Pentru afisarea automatului obtinut prin transformarea expresiei, tastati 1\n 2. Pentru afisarea expresiei regulate citite, tastati 2 \n 3. Pentru verificarea unui cuvant in automat, tastati 3\n 4. Pentru a iesi, tastati 4\n";
                a.printAutomaton();
                system("pause");
                system("cls");
                break;

            case 2:
                std::cout << "Meniu \n 1. Pentru afisarea automatului obtinut prin transformarea expresiei, tastati 1\n 2. Pentru afisarea expresiei regulate citite, tastati 2 \n 3. Pentru verificarea unui cuvant in automat, tastati 3\n 4. Pentru a iesi, tastati 4\n";
                std::cout << aux << std::endl;
                system("pause");
                system("cls");
                break;

            case 3:
                std::cout << "Meniu \n 1. Pentru afisarea automatului obtinut prin transformarea expresiei, tastati 1\n 2. Pentru afisarea expresiei regulate citite, tastati 2 \n 3. Pentru verificarea unui cuvant in automat, tastati 3\n 4. Pentru a iesi, tastati 4\n";
                std::cout << "Introduceti cuvantul pe care doriti sa-l verificati:";
                std::cin >> cuvant;
                if (a.CheckWord(cuvant))
                    std::cout << "Cuvantul este acceptat!!!\n";
                else std::cout << "Cuvantul nu este acceptat\n";
                system("pause");
                system("cls");
                break;

            case 4:
                op = 0;
                std::cout << "La revedere!";
                break;
            }
		} while (op);
    }
    else std::cout << "Expresia regulata transmisa nu este valida!!!\n";
}