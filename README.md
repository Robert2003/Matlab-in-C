Copyright Damian Mihai-Robert 312CAb 2022-2023

```
    In problema trebuie sa facem operatii pe matrice. Cum nu cunoastem numarul
de matrice si nici dimensiunile acestora, vom utiliza matrice alocate dinamic,
ale caror pointeri vor fi stocati intr-un vector, de asemenea alocat dinamic.
    Toate calculele vor fi facute modulo 10007, iar daca rezultatul este
negativ, atunci se va adauga un 10007 la rezultat.
```

```
Am folosit programarea defensiva pe unde s-a putut. Am avut 2 probleme cu
checkerul:
    1.  Daca aveam o conditie care verifica daca malloc, calloc sau realloc nu
      intorc NULL, dealocam tot si dadeam exit(-1), dar checkerul imi dadea
      eroare -11, desi nu se intra deloc pe ramura else. Daca stergeam conditia,
      aveam aceeasi eroare -11, dar in schimb, daca dadeam ctrl+z (undo) pana in
      momentul in care nu aveam conditia de defensiva, luam maxim, apoi puneam
      din nou conditia de defensiva, identica si luam maxim, nu mai dadea -11.
    2.  Daca dadeam ./check si opream fortat checkerul cu ctrl+c, la alte
      incercari de a testa, imi afisa in .out-uri cu cateva sute sau chiar mii de
      linii in plus. Dar nu doar atat, pentru ca de fiecare data cand rulam
      checkerul, afisa numere diferite, dar si numar de linii diferit. Am un
      coleg de grupa care mi-am zis ca el a rulat checkerul si doar a dat ctrl+f5
      (dica mute) si nu i-au mai dat testele pana la alta rulare.
```

## Task 1 - Încărcarea în memorie a unei matrice - L
```   
    Matricea va fi tinuta in vectorul v, alocat dinamic, pe pozitia last_index.
Daca last_index, este -1, inseamna ca nu exista o matrice in memorie si memoria
trebuie alocata. Daca nu este -1, atunci exista deja o matrice si memoria
trebuie doar realocata. Este acoperit si cazul in care nu se poate aloca sau
realoca memorie. Dimensiunile matricei adaugate se vor stoca in vectorul de tip
struct: dimensions, in acelasi mod in care se adauga o matrice in colectie.
Atat vectorul de matrice, cat si cel de dimensiuni sunt utilizate ca o coada.
```

## Task 2 - Determinarea dimensiunilor unei matrice - D
```
    Se citeste un index, iar daca este valid, se vor afisa dimensiunile
matricei stocate pe acel index. Cum in vectorul de dimensiuni sunt toate
dimensiunile matricelor, doar se va afisa continutul lui de la acel index.
```

## Task 3 - Afisarea unei matrice - P
```
    In acelasi mod, daca indexul este valid se afla dimensiunile matricei de pe
acel index, se parcurge matricea din colectie si se afiseaza continutul.
```

## Task 4 - Redimensionarea unei matrice - C
```
    Se citeste un index, un numar de linii si un vector de linii, apoi un numar
de coloane si un vector de coloane. Se foloseste o matrice auxiliara pentru a
constui matricea obtinuta doar din elementele care se afla la intersectia
liniilor si a coloanelor din cei 2 vectori. Dupa ce am contruit mauxiliara,
eliberez memoria matricei pe care voiam sa o redimensionez si v[index] primeste
pointer spre zona de memorie unde se afla matricea nou-constuita.
```

## Task 5 - Înmultirea a două matrice - M
```
    Se citesc 2 indici si daca inmultirea este posibila, matricea auxiliara c
primeste pointer spre zona de memorie a rezultatului inmultirii, rezultat
returnat de o functie de tip int**.
```

## Task 6 - Sortarea matricelor - O
```
    Se construieste un vector, tot alocat dinamic, in care pe pozitia i va fi
suma elementelor matricei de pe pozitia i in colectie. apoi se aplica selection
sort pe vectorul de sume, dar in acelasi timp se interschimba si pointerii
matricelor din v, dar si pointerii elementelor din structul de dimentiuni.
```

## Task 7 - Transpunerea unei matrice - T
```
    Se primeste un index pentru care se doreste transpunerea. Se construieste
matricea auxiliara transpusa, adica toate elementele de pe linii se trec pe
coloane. Se dezaloca memoria matricei vechi, iar colectia de matrice pe acel
index primeste pointer catre zona de memorie unde este transpusa.
```

## Task 8 - Ridicarea unei matrice la o putere in timp logaritmic - R
```
    Algoritmul de ridicare al unui numar la o putere in timp logaritmic pentru
numere, numit si algoritmul lui al-Kashi, se poate extinde si la matrice. Se
considera matricea helper, care este In, matricea unitate initial. Cat timp
exponentul este diferit de 0, daca este impar, se inmulteste helper cu v[index]
unde index este indexul matricei pe care o vrem ridicata la putere, iar
rezultatul este stocat in helper. Se inmulteste apoi v[index] cu v[index], iar
exponentul se injumatateste.
    Practic algoritmul transforma pe (a * a * ... * a), inmultit de n ori in:
        1) (a^2) * (a^2) * ... * (a^2), daca n este par;
        2) a * (a^2) * (a^2) * ... * (a^2), daca n este impar;
    Restrans, a^n =
        1) ((a^2))^(n/2), daca n este par;
        2) a * ((a^2))^(n/2), daca n este impar;
    Rezultatul insa este obtinut in matricea helper, deci trebuie eliberata
memoria matricei v[index], care apoi primeste pointer spre helper.
```

## Task 9 - Eliberarea memoriei unei matrice - F
```
    Se elibereaza memoria pentru matricea de la indexul dat, dupa care se
parcurge toata colectia de matrice incepand de la index pana la last_index - 1
si se deplaseaza stanga toti pointerii spre matrice. La final, se realoca
memoria lui v cu 1 in minus, astfel matricea a fost eliminata cu succes.
```

## Task 10 - Eliberarea tuturor resurselor - Q
```
    In continuare tot ce va fi eliberat, va fi verificat sa fie diferit de NULL
Desi functia free() poate sa primeasca un pointer NULL, checkerului nu ii place
Se parcurge tot vectorul de matrice si se elibereaza fiecare matrice in parte.
Apoi se elibereaza si vectorul de matrice, cat si vectorul de dimensiuni.
```

## Task 11 - Alte situatii
```
    Daca nu se citeste un caracter corespunzator taskurilor exemplificate mai
sus, se va afisa mesajul: Unrecognized command.
```
