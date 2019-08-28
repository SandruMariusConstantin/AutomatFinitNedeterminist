# AutomatFinitNedeterminist
AFN

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
 
