/**
   Autor : Sandru Marius-Constantin
   Descriere :          Program care simuleaza un AFN dat pe un cuvant primit. Citeste
                        AFN-ul din "automat.txt" si cuvantul de la tastatura si afiseaza
                        la ecran daca cuvantul este acceptat de automat sau nu.

                        "automat.txt" are formatul urmator:
                                Q
                                F q1 q2 ... qf
                                T
                                stare_plecare1 stare_sosire1 nr_litere1 litera1 ...
                                stare_plecare2 stare_sosire2 nr_litere2 litera2 ...
                                :
                                :
                        Here,   Q -> Nr. de stari (starile sunt numere intre 0 ... Q-1). 0 e starea de start
                                F -> Nr. de stari finale, urmat de F stari (0 <= qi <= N-1)
                                T -> Nr. de tranzitii, urmat de T linii
                                stare_plecarei -> Starea din care pleaca ( 0 <= stare_plecarei <= Q-1)
                                stare_sosirei -> Starea in care se duce ( 0 <= stare_sosirei <= Q-1)
                                nr_literei -> Numarul de litere cu care se poate duce din stare_plecare in stare_sosire
                                literai -> litera alfabetului prin care se va duce din stare_plecare in stare_sosire



    Creez un vector in care reprezint prin 0 starile ce nu sunt finale si 1 cele finale
    Creez o matrice tridimensionala cu Q linii (starile de plecare) si Q coloane (starile in care intra)
    La intersectie am o alta dimensiune (adancimea), in care voi avea fiecare litera prin care se poate face tranzitia sau numai 0 daca nu se poate face

    Functia de testare e una recursiva care ia ca parametrii matricea, vectorul, nr. de stari, starea in care am ajuns si cuvantul pe care-l testam
    La fiecare apel voi merge in alta stare si voi merge pe urmatoare litera din cuvant
    Voi cauta in a treia dimeniune daca pot continua in urmatoarea stare, folosind strchr
    Folosesc o variabila statica pentru a nota daca intr-una dintre recursii cuvantul a fost validat
 */


#include <iostream>
#include <cstring>
#include <fstream>
#define LUNGIME_MAXIMA 100
#define NUMAR_STARI 10
#define NUMAR_LITERE 20

using namespace std;

ifstream f("automat.txt");

int testeazaCuvantul(int stare_curenta, int nr_stari, char matrice_[NUMAR_STARI][NUMAR_STARI][NUMAR_LITERE], int *finale, char *cuvant)
{
    static int raspuns = 0;                                           ///este nevoie ca macar in una dintre apeluri sa se indeplineasca conditile de mai jos

    if(strlen(cuvant) == 0 && finale[stare_curenta] == 1)             ///daca ajunge la finalu cuvantului si suntem intr-o stare finala
        raspuns = 1;
    else                                                              ///cautam pentru starea curenta o alta in care se se duca pe baza literei la care ne aflam
        for(int i = 0; i < nr_stari; i++)
            if(strlen(cuvant) != 0 && strchr(matrice_[stare_curenta][i], cuvant[0]))
                testeazaCuvantul(i, nr_stari, matrice_, finale, cuvant+1);

///ca sa vedem daca ne putem duce in alta stare, cautam daca litera cuvantului se gaseste in cea de-a treia dimensiune
///daca nu am ajuns la finalull cuvantului si si ne putem duce in alta stare, ne ducem in starea respectiva si "taiem" litera curenta a cuvantului
///daca se termina for-ul fara a se face vreo operatie, inseamna ca am terminat cuvantul, dar nu intr-o stare finala sau ne-am blocat intr-o stare


    return raspuns;
}

int main()
{
    int numarStari, numarFinale, numarTranzitii;
    int finale[NUMAR_STARI] = {0};                                     ///un vector in care 1 pentru stari finale si 0 pentru restul
    char matrice_AFN[NUMAR_STARI][NUMAR_STARI][NUMAR_LITERE] = {0};    ///primul indice e starea din care pleaca, cel de-al doilea in care se duce
                                                                       ///la intersectie e o alta dimensiune, un sir cu literele prin care putem trece dintr-o stare in alta
    f >> numarStari >> numarFinale;

    for(int i = 0; i < numarFinale; i++)                               ///citesc starea si setez pozitia cu 1
        {
            int stare;
            f>>stare;
            finale[stare] = 1;
        }

    f >> numarTranzitii;

    for(int i = 0; i < numarTranzitii; i++)                            ///tranzitile sunt de tipul stare din care pleaca, in care pleaca si
        {                                                              ///si prin ce litera
            int din_stare, in_stare, nr_litere;
            char litera_alfabet;
            f >> din_stare >> in_stare >> nr_litere;

         for(int j = 0; j < nr_litere; j++){
            f >> litera_alfabet;
            matrice_AFN[din_stare][in_stare][j] = litera_alfabet;
         }
        }

    char *cuvant = NULL;
    cuvant = new char [LUNGIME_MAXIMA];
    cout << "Testeaza-ti cuvantul: ";

    cin.get(cuvant, LUNGIME_MAXIMA);
    cin.get();

    ///testez daca cuvantul citit de la tastatura este vid si pozitia de start este una finala
    if(strlen(cuvant) == 0)
         if(finale[0] == 1)
         {
             cout<<"Cuvantul este vid si este acceptat =)";
             return 0;
         }
    else
         {
            cout<<"Cuvantul este vid si este respins =))";
            return 0;
         }

    if(testeazaCuvantul(0, numarStari, matrice_AFN, finale, cuvant))
        cout << "Cuvantul este acceptat :* ";
    else
        cout << "Cuvantul este respins :( ";

    delete [] cuvant;

    return 0;
}
