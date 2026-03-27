#include <iostream>
#include <cmath>
#include <graphics.h>
#include <winbgim.h>
#include <stack>
#include <cstring>

#include <cstdlib> // pentru rand() și srand()
#include <ctime>   // pentru time()

using namespace std;

void afiseazaMeniu();
void playerVSplayer();

int x = 600;
int y = 250;
int l = 300;

// Structura pentru piese
struct Piesa
{
    int x = 0;
    int y = 0;
    int size = 0;
    int player = 0;
    int calculator = 0;
};

Piesa piesa_selected; // variabila de tip struct pentru piesa selectata

// Matricea de 3x3 pentru tabla de joc
stack<Piesa> board[3][3]; // fiecare element din matrice este o stiva care contine variabile de tip struct

Piesa pieces[12]; // in afara tablei sunt 12 piese; 6 piese rosii si 6 piese albastre
int pieceCount = 0;

Piesa piecesComputer[6];
int pieceComputerCount = 0;

char player1[25] = "";
char player2[25] = "";

struct TextMessage // structura pentru mesajul de eroare
{
    char text[256] = "";
    int x = 0, y = 0;
    bool show = false;
};

TextMessage text_msg; // variabila de tip struct pentru mesajul de eroare

// FUNCTII

// rand() genereaza mereu un numar aleatoriu pe baza unui algoritm in functie de timp
// operatia  rand() % (y - x + 1) reduce numarul la intervalul [0; y-x] (de asta y > x)
// x + random aduaga valoarea lui x pentru a obtine un nr in intervalul [x; y]
int generareNumar(int x, int y) 
{
    if (x > y)
        swap(x, y);
    int random = rand() % (y - x + 1);
    return x + random;
}

// Functie pentru stergerea erorii precedente si afisarea erorii actuale
void afisareMesaj(char text[])
{
    if (text_msg.show == true) // daca exista un  mesaj anterior se sterge
    {
        setfillstyle(SOLID_FILL, BLACK);
        setcolor(BLACK);
        bar(text_msg.x, text_msg.y, text_msg.x + textwidth(text), text_msg.y + textheight(text));
    }
    text_msg.show = true;
    strcpy(text_msg.text, text);
    text_msg.x = 600 - textwidth(text_msg.text) / 2;
    text_msg.y = 425 - textheight(text_msg.text) / 2;
    setcolor(RED);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(text_msg.x, text_msg.y, text_msg.text);
}

// Functie pentru ascunderea mesajului de eroare (la urmatorul click)
void ascundereMesaj()
{
    if (text_msg.show == true)
    {
        setfillstyle(SOLID_FILL, BLACK);
        setcolor(BLACK);
        bar(text_msg.x, text_msg.y, text_msg.x + textwidth(text_msg.text), text_msg.y + textheight(text_msg.text));
        text_msg.show = false;
    }
}

// Functie pentru resetarea piesei selectate
void resetselected()
{
    piesa_selected.x = 0;
    piesa_selected.y = 0;
    piesa_selected.player = 0;
    piesa_selected.size = 0;
}

// Functie pentru adaugarea piesei pe tabla
void AdaugarePiesa(int rand, int coloana, int player, int size)
{
    Piesa piesa; // piesa este o variabila de tip struct ce memoreaza playerul si marimea piesei
    piesa.player = player;
    piesa.size = size;
    board[rand][coloana].push(piesa); // se memoreaza in stiva de pe pozitia [rand][coloana] piesa
}

// Verificam daca exista un castigator
int castig;
int inceput;
int player_castigator;

bool AvemCastigator()
{
    for (int i = 0; i < 3; i++)
        if (!board[i][0].empty() && !board[i][1].empty() && !board[i][2].empty())                                             // verificam ca stivele cu care lucram sa nu fie goale
            if (board[i][0].top().player == board[i][1].top().player && board[i][0].top().player == board[i][2].top().player) // verificam daca avem castigator pe linie
            {
                castig = 1;
                inceput = i;
                player_castigator = board[i][0].top().player;
                return true;
            }
    for (int j = 0; j < 3; j++)
        if (!board[0][j].empty() && !board[1][j].empty() && !board[2][j].empty())
            if (board[0][j].top().player == board[1][j].top().player && board[0][j].top().player == board[2][j].top().player) // verificam castigul pe coloana
            {
                castig = 2;
                inceput = j;
                player_castigator = board[0][j].top().player;
                return true;
            }
    if (!board[0][0].empty() && !board[1][1].empty() && !board[2][2].empty())
        if (board[0][0].top().player == board[1][1].top().player && board[0][0].top().player == board[2][2].top().player) // verificam castigul pe coloana principala
        {
            castig = 3;
            player_castigator = board[0][0].top().player;
            return true;
        }
    if (!board[0][2].empty() && !board[1][1].empty() && !board[2][0].empty())
        if (board[0][2].top().player == board[1][1].top().player && board[0][2].top().player == board[2][0].top().player) // verificam castigul pe diagonala secundara
        {
            castig = 4;
            player_castigator = board[0][2].top().player;
            return true;
        }
    return false;
}

// Functie pentru desenarea piesei in celula
void DeseneazaPiesa(int rand, int coloana, int player, int size)
{
    int X = 450 + coloana * (l / 3) + (l / 6);
    int Y = 100 + rand * (l / 3) + (l / 6);

    // randul si coloana pot fi numerotate 0, 1 sau 2
    // 450 si 100 repprezinta distantele pana la inceputul tablei
    // l/3 reprezinta latura unei celule;
    // coloana * (l / 3) - coordonata X a casetei (pt latura cea mai apropiata de centrul de axe xoy)
    // rand * (l / 3) - coordonata Y

    // l/6 are rolu de a pune elementele fix pe mijlocul casetei

    int raza = 10 * size;

    AdaugarePiesa(rand, coloana, player, size); // adaug piesa desenata si in stiva

    if (player == 1) // setez culoarea pentru piesele jucatorilor
    {
        setfillstyle(SOLID_FILL, RED);
        setcolor(RED);
    }
    else
    {
        setfillstyle(SOLID_FILL, BLUE);
        setcolor(BLUE);
    }

    fillellipse(X, Y, raza, raza);
}

void DoarDeseneazaPiesa(int rand, int coloana, int player, int size) // la fel ca functia DeseneazaPiesa doar ca nu mai adaug piesa in stiva
{
    int X = 450 + coloana * (l / 3) + (l / 6);
    int Y = 100 + rand * (l / 3) + (l / 6);

    int raza = 10 * size;

    if (player == 1) // setez culoarea pentru piesele jucatorilor
    {
        setfillstyle(SOLID_FILL, RED);
        setcolor(RED);
    }
    else
    {
        setfillstyle(SOLID_FILL, BLUE);
        setcolor(BLUE);
    }
    fillellipse(X, Y, raza, raza);
}

// Identificarea celulei in functie de coordonatele mouseului
void getCell(int mouseX, int mouseY, int &rand, int &coloana) // daca nu avem "&" nu afiseaza
{
    // mai intai se scade din coordonatele mose-ului 450 si 100 (coordonatele de inceput ale tablei)
    // dupa se imparte la l/3 pentru ca l/3 reprezinta dimensiunile casetei ( inaltime si latime )
    // exemplu: mouseX = 550: (550 - 450) / 100 = 1 (coloana)
    /*
       450            550            650
    -------------------------------*--------------
    100|    (0,0)     |    (0,1)     |    (0,2)     |
    -------------------------------*--------------
    200|    (1,0)     |    (1,1)     |    (1,2)     |
    -------------------------------*-------------
    300|    (2,0)     |    (2,1)     |    (2,2)     |
    ------------------------------------------------
    */
    coloana = (mouseX - 450) / (l / 3);
    rand = (mouseY - 100) / (l / 3);
}

// Functie pentru a afla centrul piesei in functie de randul si coloana pe care se afla
void getXYFromCell(int rand, int coloana, int &x, int &y)
{
    x = 450 + coloana * (l / 3) + (l / 6);
    y = 100 + rand * (l / 3) + (l / 6);
}

// Functie pentru adaugarea pieselor in afara tablei
void AddPiesa(int x, int y, int player, int size)
{

    Piesa piesa;
    piesa.player = player;
    piesa.size = size;
    piesa.x = x;
    piesa.y = y;
    pieces[pieceCount] = piesa; // adaugam piesa in vectorul pentru piesele din afara tablei
    int raza = 10 * size;
    if (player == 1)
    {
        setfillstyle(SOLID_FILL, RED);
        setcolor(RED);
    }
    else
    {
        setfillstyle(SOLID_FILL, BLUE);
        setcolor(BLUE);
    }
    fillellipse(x, y, raza, raza);

    pieceCount++; // pregatim pozitia pentru urmatoarea piesa memorata in vectorul de piese din afara tablei
}

//Functie pentru desenarea pieselor computerului in afara tablei
void AddPiesaComputer(int x, int y, int size)
{

    Piesa piesa;
    piesa.size = size;
    piesa.x = x;
    piesa.y = y;
    piecesComputer[pieceComputerCount] = piesa;
    int raza = 10 * size;
    setfillstyle(SOLID_FILL, BLUE);
    setcolor(BLUE);
    fillellipse(x, y, raza, raza);

    pieceComputerCount++;
}

int curent_player = 0;

//Fucntie pentru generarea playerului care face prima mutare
void setPlayer(char player1[], char player2[]) 
{
    if (curent_player == 0)
    {
        curent_player = generareNumar(1, 2);
        if (curent_player == 1)
        {
            setcolor(GREEN);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            outtextxy(225 - textwidth(player1) / 2, 50 - textheight(player1) / 2, player1);

            setcolor(WHITE);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            outtextxy(975 - textwidth(player2) / 2, 50 - textheight(player2) / 2, player2);
        }
        else
        {
            setcolor(WHITE);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            outtextxy(225 - textwidth(player1) / 2, 50 - textheight(player1) / 2, player1);

            setcolor(GREEN);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            outtextxy(975 - textwidth(player2) / 2, 50 - textheight(player1) / 2, player2);
        }
    }
}

//Functie pentru alternarea playerului care face mutarea
void changePlayer(char player1[], char player2[])
{
    if (curent_player == 0)
    {
        setPlayer(player1, player2);
    }
    else
    {

        if (curent_player == 1)
            curent_player = 2;
        else
            curent_player = 1;
        // GRAFICA
        if (curent_player == 1)
        {
            setcolor(GREEN);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            outtextxy(225 - textwidth(player1) / 2, 50 - textheight(player1) / 2, player1);

            setcolor(WHITE);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            outtextxy(975 - textwidth(player2) / 2, 50 - textheight(player2) / 2, player2);
        }
        else
        {
            setcolor(WHITE);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            outtextxy(225 - textwidth(player1) / 2, 50 - textheight(player1) / 2, player1);

            setcolor(GREEN);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            outtextxy(975 - textwidth(player2) / 2, 50 - textheight(player1) / 2, player2);
        }
    }
}

// Funcția pentru detectarea piesei dim afara tablei și afișarea detaliilor
void checkOutsideBoard(int mouseX, int mouseY)
{

    // in esenta functia asta verifica PENTRU FIECARE PIESA daca click-ul a fost dat in interiorul ei

    /*
                *  (mouseX, mouseY)

    |
    |      /|
    |     / |
    |    /  | dy
    |   /   |
    |  /    |
    | /     |
    |/|
    (0,0)    dx
    (pieces[i].x, pieces[i].y)

    deci o piesa are 3 propietati geometrice X Y si raza
    cand se da click undeva pentru fiecare piesa am un mouseX si un mouseY
    din mouseX si din mouseY scad x si y-ul piesei si obtin distanta dintre click si centrul piesei pe ambele coordonate, dar doar cu astea 2 nu pot verifica daca s-a dat click pe piesa motiv pentru care calculez ipotenuza lor (distanta totala)
    pentru a cacula distanta totala folosesc teorema lui pitagora iar distanta trebuie sa fie mai mica sau egala decat raza piesei respective, daca e mai mare continui cautarea

    exemplu : daca am o piesa cu coordonatele X: 0, Y:0 cu raza 10 si dau click X:3 Y:4
    aflu dX = 3-0 =3
    aflu dY = 4-0 = 4
    aflu distanta 3,4,5 nr pitagoreice => distanta este 5
    distanta <= raza deci am dat click in interiprul piesei


    */
    for (int i = 0; i < pieceCount; i++) // ne uitam la fiecare piesa din vectorul de piese din afara tablei
    {
        int dx = mouseX - pieces[i].x;
        int dy = mouseY - pieces[i].y;
        int ipotenuza = sqrt(dx * dx + dy * dy); // TEOREMA LUI PITAGORA (AFLU IPOTENUZA)
        int raza = 10 * pieces[i].size;

        if (ipotenuza <= raza) // verificam daca s-a dat click in interiorul piesei
        {
            if(pieces[i].player != curent_player) 
            {
                char eroarerand[] = "eroare : piesa selectata nu iti apartine";
                afisareMesaj(eroarerand);
                break;
            }
            piesa_selected.player = pieces[i].player;
            piesa_selected.size = pieces[i].size;

            // stergem piesa din afara tablei
            setfillstyle(SOLID_FILL, BLACK);
            setcolor(BLACK);
            fillellipse(pieces[i].x, pieces[i].y, raza, raza);
            // sterge piesa din vector
            for (int j = i; j < pieceCount - 1; j++)
            {
                pieces[j] = pieces[j + 1];
            }
            pieceCount--;
            break;
        }
    }
}

// Functie pentru a verifica daca celula este goala
bool esteGoala(int rand, int coloana)
{
    return board[rand][coloana].empty();
}

// Functie pentru a verifica daca putem pune piesa selectata in celula aleasa
int VerificarePunerePiesa(int rand, int coloana, int size)
{
    if (board[rand][coloana].empty())
        return 1; // daca celula este goala putem pune piesa indiferent de marimea ei
    if (board[rand][coloana].top().size == 3)
        return 0; // daca ultima piesa pusa in celula aleasa este de dimensiune mare, nu mai putem adauga nicio piesa
    if (board[rand][coloana].top().size < piesa_selected.size)
        return 1; // daca ultima piesa pusa in celula aleasa are dimensiunea mai mica decat piesa aleasa, atunci putem pune piesa aleasa in celula respectiva
}

bool VerificarePunereInAcelasiLoc(int rand, int coloana)
{
    int mouseX = mousex(), mouseY = mousey();
    getXYFromCell(rand, coloana, x, y);
    if (piesa_selected.x == x && piesa_selected.y == y)
        return true;
    else
        return false;
}

void intrebareBack ()
{
    initwindow (1000, 500);

    setbkcolor(CYAN); //fundal albastru deschis
    cleardevice();

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);

    char intrebare[] = "Esti sigur ca vrei sa parasesti jocul?";
    outtextxy((1000 - textwidth(intrebare)) / 2, 100, intrebare);

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);

    char raspuns_1[] = "DA";
    outtextxy((1000 - textwidth(raspuns_1)) / 2, 200, raspuns_1);

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);

    char raspuns_2[] = "NU";
    outtextxy((1000 - textwidth(raspuns_2)) / 2, 300, raspuns_2);

    while (true)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            int mouseX = mousex();
            int mouseY = mousey();
            clearmouseclick(WM_LBUTTONDOWN);

            if (mouseX >= (1000 - textwidth(raspuns_1)) / 2 && mouseX <= (1000 + textwidth(raspuns_1)) / 2 && mouseY >= 200 && mouseY <= 250) //suntem in cazul in care dam click pe "DA"
            {
                closegraph();
                afiseazaMeniu();
            }
            else if (mouseX >= (1000 - textwidth(raspuns_2)) / 2 && mouseX <= (1000 + textwidth(raspuns_2)) / 2 && mouseY >= 300 && mouseY <= 350) //suntem in cazul in care dam click pe "NU"
            {
                closegraph();
                playerVSplayer();
            }
        }
    }
}

//Partea de player vs player
void playerVSplayer()
{
    srand(time(0));

    initwindow(1200, 500);

    //Desenam sageata pentru back (in coltul din stanga-sus)
    setfillstyle(SOLID_FILL, BLUE);
    setcolor(BLUE);
    
    bar (75, 30, 110, 50);

    line (40, 40, 75, 20);
    line (75, 20, 75, 60);
    line (40, 40, 75, 60);

    floodfill(57, 40, BLUE); //punem culoarea albastru in interiorul triunghiului desenat mai sus

    // Desenam tabla de joc
    setcolor (WHITE);
    line(450 + (l / 3), 100, 450 + (l / 3), 400);
    line(600 + (l / 6), 100, 600 + (l / 6), 400);
    line(450, 250 - (l / 6), 600 + (l / 3) + (l / 6), 250 - (l / 6));
    line(450, 250 + (l / 6), 600 + (l / 3) + (l / 6), 250 + (l / 6));


    // aici intra in cazul currentPlayer = 0 deci se face random pentru primu
    changePlayer(player1, player2);

    char Castigator1[] = "Castigator : player 1 ~ Felicitari!";
    char Castigator2[] = "Castigator : player 2 ~ Felicitari~";

    // Adaugam in afara tablei pieselei playerului 1 (piesele rosii)
    setfillstyle(SOLID_FILL, RED);
    setcolor(RED);
    AddPiesa(100 + (l / 6), 100 + (l / 6), 1, 1);
    AddPiesa(250 + (l / 6), 100 + (l / 6), 1, 1);
    AddPiesa(100 + (l / 6), 200 + (l / 6), 1, 2);
    AddPiesa(250 + (l / 6), 200 + (l / 6), 1, 2);
    AddPiesa(100 + (l / 6), 300 + (l / 6), 1, 3);
    AddPiesa(250 + (l / 6), 300 + (l / 6), 1, 3);

    // Adaugam in afara tablei piesele playerlui 2 (piesele albastre)
    setfillstyle(SOLID_FILL, BLUE);
    setcolor(BLUE);
    AddPiesa(850 + (l / 6), 100 + (l / 6), 2, 1);
    AddPiesa(1000 + (l / 6), 100 + (l / 6), 2, 1);
    AddPiesa(850 + (l / 6), 200 + (l / 6), 2, 2);
    AddPiesa(1000 + (l / 6), 200 + (l / 6), 2, 2);
    AddPiesa(850 + (l / 6), 300 + (l / 6), 2, 3);
    AddPiesa(1000 + (l / 6), 300 + (l / 6), 2, 3);

    while (!AvemCastigator())
    {

        if (ismouseclick(WM_LBUTTONDOWN)) // daca s-a dat click
        {
            int localPlayer = 0;

            int mouseX = mousex(); // se memoreaza coodonata x a mouseului
            int mouseY = mousey(); // se memoreaza coordonata y a mouseului
            clearmouseclick(WM_LBUTTONDOWN);

            if ((mouseX >= 75 && mouseX <= 110 && mouseY >= 30 && mouseY <= 40) || (mouseX <= 75 && mouseX >= 40 && mouseY >= 20 && mouseY <= 60)) //in cazul in care dam click pe sageata
            {
                closegraph();
                intrebareBack();
            }

            int rand, coloana;
            getCell(mouseX, mouseY, rand, coloana); // identificam celula selectata

            ascundereMesaj();

            if (rand >= 0 && rand < 3 && coloana >= 0 && coloana < 3) // verificam daca s-a dat click in interiorul tablei
            {
                if (piesa_selected.player == 0 && !esteGoala(rand, coloana)) // in cazul in care nu avem deja o piesa selectata si celula nu este goala
                {
                    if(board[rand][coloana].top().player != curent_player)
                    {
                        char eroarerand[] = "eroare : piesa selectata nu iti apartine";
                        afisareMesaj(eroarerand);
                        continue;
                    }
                    piesa_selected.player = board[rand][coloana].top().player;
                    piesa_selected.size = board[rand][coloana].top().size;

                    int x, y;
                    getXYFromCell(rand, coloana, x, y);

                    piesa_selected.x = x;
                    piesa_selected.y = y;

                    setfillstyle(SOLID_FILL, BLACK);
                    setcolor(BLACK);
                    fillellipse(x, y, 30, 30); // stergem ultima piesa vizual

                    board[rand][coloana].pop(); // sterg ultima piesa din stiva

                    if (!esteGoala(rand, coloana)) // desenez ultima piesa din stiva
                    {
                        DoarDeseneazaPiesa(rand, coloana, board[rand][coloana].top().player, board[rand][coloana].top().size);
                    }
                }
                else 
                    if(piesa_selected.player != 0) // in cazul in care avem o piesa selectata
                        if (VerificarePunerePiesa(rand, coloana, piesa_selected.size)) // verificam daca mai putem adauga piese in celula
                        {
                            if (VerificarePunereInAcelasiLoc(rand, coloana) == true)
                            {
                                char eroarepozitie[] = "eroare : nu se poate plasa piesa in aceeasi celula";
                                afisareMesaj(eroarepozitie);
                            }
                            else
                            {
                                DeseneazaPiesa(rand, coloana, piesa_selected.player, piesa_selected.size); // adaugam piesa
                                changePlayer(player1, player2);
                                resetselected();
                            }
                        }
                        else // daca nu putem adauga piesa, afisam eroarea
                        {
                            char eroare[] = "eroare : nu se poate plasa piesa - piesa existenta in celula nu este mai mica";
                            afisareMesaj(eroare);
                        }
            }
            else 
                if (piesa_selected.player == 0)
                    checkOutsideBoard(mouseX, mouseY); // se verifica mereu (daca s-a dat click in exetriorul tablei, identificam piesa din afara tablei care s-a selectat)
            if (AvemCastigator())
            {
                setfillstyle(SOLID_FILL, WHITE);
                setcolor(WHITE);
                if (castig == 1)
                {
                    line(450, (inceput + 1) * (l / 3) + (l / 6), 450 + (l / 6) + (l / 3), (inceput + 1) * (l / 3) + (l / 6));
                    line(450 + (l / 6) + (l / 3), (inceput + 1) * (l / 3) + (l / 6), 750, (inceput + 1) * (l / 3) + (l / 6));
                }
                if (castig == 2)
                {
                    line(450 + inceput * (l / 3) + (l / 6), 100, 450 + inceput * (l / 3) + (l / 6), 250);
                    line(450 + inceput * (l / 3) + (l / 6), 250, 450 + inceput * (l / 3) + (l / 6), 400);
                }
                if (castig == 3)
                {
                    line(450, 100, 600, 250);
                    line(600, 250, 750, 400);
                }
                if (castig == 4)
                {
                    line(750, 100, 600, 250);
                    line(600, 250, 450, 400);
                }

                if (player_castigator == 1)
                {
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
                    setcolor(GREEN);
                    outtextxy(600 - textwidth(Castigator1) / 2, 75 - textheight(Castigator1) / 2, Castigator1);
                }
                else
                {
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
                    setcolor(GREEN);
                    outtextxy(600 - textwidth(Castigator2) / 2, 75 - textheight(Castigator2) / 2, Castigator2);
                }
            }
        }
    }
    while (AvemCastigator()) //putem iesi din joc si dupa ce avem un castigator, apasand pe sageata de back
    {
        if (ismouseclick(WM_LBUTTONDOWN)) // daca s-a dat click
        {
            int mouseX = mousex(); // se memoreaza coodonata x a mouseului
            int mouseY = mousey(); // se memoreaza coordonata y a mouseului
            clearmouseclick(WM_LBUTTONDOWN);

            if ((mouseX >= 75 && mouseX <= 110 && mouseY >= 30 && mouseY <= 40) || (mouseX <= 75 && mouseX >= 40 && mouseY >= 20 && mouseY <= 60)) //in cazul in care dam click pe sageata
            {
                closegraph();
                afiseazaMeniu();
            }
        }
    }
    getch();
    closegraph();
}

//Functie pentru introducerea numelor jucatorilor
void introduNume(char inc[], char name[], int LungimeMax)
{
    cleardevice(); //reseteaza fereastra

    setbkcolor(CYAN); //fundal albastru deschis
    cleardevice();

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3); 
    outtextxy((800 - textwidth(inc)) / 2, 200, inc); 

    int x = 800;
    int y = 300;
    char ch;
    int i = 0; //dimensiunea numelui introdus de la tastatura

    while ((ch = getch()) != 13) //getch () preia caracterul introdus de la tastatura
    { 
        // 13 este codul ASCII pentru ENTER deci se executa cat timp nu se apasa ENTER
        if (ch == 8 && i > 0) // daca i = 0 nu avem ce sa stergem
        { 
            // 8 e codul pentru BACKSPACE pentru ca trebuie sa poti sterge ultimu caracter
            i--; // se sterge ultimu caracter
            name[i] = '\0';
            
            cleardevice(); 
            outtextxy((800 - textwidth(inc)) / 2, 200, inc); // se reafiseaza textul "Introdu...."
            int text_width = textwidth(name);
            x = (800 - text_width) / 2;
            outtextxy(x, y, name); // afisam pe ecran numele introdus de la tastatura
        }
        else if (i < LungimeMax - 1 && ch != 8)
        {
            // se adauga caracterul ch si textul isi da update in grafica 
            
            name[i] = ch;
            name[i + 1] = '\0';
            cleardevice(); //se scrie in continuarea ultimului caracter afisat; nu se suprascrie
            outtextxy((800 - textwidth(inc)) / 2, 200, inc);
            int text_width = textwidth(name);
            x = (800 - text_width) / 2;
            outtextxy(x, y, name);
            
            i ++;
        }
    }
   // name[0]=name[0]-32;
}

//Partea de introducere a numelor jucatorilor
void meniuIntroducereNume()
{
    initwindow(800, 600);
    
    char textinc1[] = "Introduceti numele jucatorului 1";
    char textinc2[] = "Introduceti numele jucatorului 2";

    introduNume(textinc1, player1, 24); 
    introduNume(textinc2, player2, 24); 

    closegraph(); // se inchide fereastra unde introduci numele
    playerVSplayer(); // se deschide fereastra de joc pentru player vs player
}

//Partea cu regulile de joc
void meniuReguli ()
{
    initwindow (1350, 600);

    //setam culoare de fundal
    setbkcolor(CYAN);
    
    cleardevice();

    //Desenam sageata pentru back (in coltul din stanga-sus)
    setfillstyle(SOLID_FILL, BLUE);
    setcolor(BLUE);
    
    bar (75, 30, 110, 50);

    line (40, 40, 75, 20);
    line (75, 20, 75, 60);
    line (40, 40, 75, 60);

    floodfill(57, 40, BLUE); //punem culoarea albastru in interiorul triunghiului desenat mai sus

    setcolor(WHITE); //setez culoarea pentru scris

    char intrebare[] = "Cum se joaca acest joc?";
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy (25, 80, intrebare);

    char reguli1[] = "Pe rand, jucatorii pot fie sa puna o noua piesa pe tabla de joc, fie sa mute una dintre piesele ";
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy (15, 100, reguli1);

    char reguli2[] = "lor care se afla deja pe tabla intr-un spatiu liber, fie sa acopere orice piesa mai mica cu una ";
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy (1, 120, reguli2);

    char reguli3[] = "mai mare care este deja in joc.";
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy (1, 140, reguli3);

    char obiectiv[] = "Obiectivul jocului :";
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy (25, 180, obiectiv);

    char afisare_obiectiv[] = "Fii primul jucator care aranjeaza 3 piese in linie!";
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy (15, 200, afisare_obiectiv);

    char reguli_1[] = "Pe rand, jucatorii pot :";
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy (25, 240, reguli_1);

    char reguli_2[] = "-fie sa puna o noua piesa pe tabla de joc;";
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy (1, 260, reguli_2);

    char reguli_3[]= "-fie sa mute una dintre piesele lor care se afla deja pe tabla intr-un spatiu liber";
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy (1, 280, reguli_3);

    char reguli_4[] = "-fie sa acopere orice piesa mai mica aflata deja pe tabla de joc cu una mai mare";
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy (1, 300, reguli_4);

    char modalitate_castig[] = "Castigarea jocului :";
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy (25, 340, modalitate_castig);

    char castig1[] = "Primul jucator care aranjeaza 3 piese in linie castiga jocul. Piesele care formeaza o linie nu";
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy (15, 360, castig1);

    char castig2[] = "trebuie sa fie de aceeasi marime si pot fi aliniate vertical, orizontal sau pe diagonala.";
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy (1, 380, castig2);

    char important[] = "! Important !";
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy (25, 420, important);

    char afisare_important1[] = "Odata ce ai atins o piesa care se afla pe tabla de joc, trebuie sa o muti, iar daca atingi o";
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy (15, 440, afisare_important1);

    char afisare_important2[] = "piesa din exteriorul tablei trebuie sa o adaugi in tabla de joc.";
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy (1, 460, afisare_important2);

    while (true)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            int mouseX = mousex();
            int mouseY = mousey();
            clearmouseclick(WM_LBUTTONDOWN);

            if ((mouseX >= 75 && mouseX <= 110 && mouseY >= 30 && mouseY <= 40) || (mouseX <= 75 && mouseX >= 40 && mouseY >= 20 && mouseY <= 60)) //suntem in cazul in care dam click pe sageata
            {
                closegraph();
                afiseazaMeniu();
            }
        }
    }
}

//Functie pentru introducerea numelor jucatorului (pentru partea de player vs computer)
void introduNume2(char inc[], char name[], int LungimeMax)
{
    setbkcolor(CYAN);
    cleardevice();
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    outtextxy((800 - textwidth(inc)) / 2, 200, inc);

    int x = 800;
    int y = 300;
    char ch;
    int i = 0;

    while ((ch = getch()) != 13)
    {
        if (ch == 8 && i > 0)
        {
            i --;
            name[i] = '\0';
            cleardevice();
            outtextxy((800 - textwidth(inc)) / 2, 200, inc);
            int text_width = textwidth(name);
            x = (800 - text_width) / 2;
            outtextxy(x, y, name);
        }
        else if (i < LungimeMax - 1 && ch != 8)
        {
            name[i] = ch;
            //if(i==0)
                //name[0]=ch-32;
            name[i + 1] = '\0';
            cleardevice();
            outtextxy((800 - textwidth(inc)) / 2, 200, inc);
            int text_width = textwidth(name);
            x = (800 - text_width) / 2;
            outtextxy(x, y, name);
            i++;
        }
    }
   // name[0]=name[0]-32;
}

//Functie pentru alegerea unei dimensiuni random (pentru piesele computerului)
int getRandomSizeFromPiecesComputer()
{
    int sizes[6]; //tablou in care memoram dimensiunea pieselor computerului din exteriorul tablei 
    int k = 0;
    for (int i = 0; i < pieceComputerCount; i++) //adaug in tablou marimile pieselor
    {
        sizes[k] = piecesComputer[i].size;
        k ++;
    }
    if (k == 0) // daca nu avem nicio piesa in exteriorul tablei 
    {
        return -1; 
    }
    int randomIndex = generareNumar(0, k-1); //se alege o pozitie random din tablou 
    return sizes[randomIndex]; //se returneaza elementul (marimea) de pe pozitia generata
}

//Functie pentru mutarile computerului
void mutareComputer() 
{
    bool validMove = false; 
    int rand, coloana, size; 
    
    if (pieceComputerCount > 0) // daca  are piese disponibile in afara tablei
    { 
        for (int incercare = 0; incercare < pieceComputerCount * 9; incercare++) // pentru a evita o bucla infinita (numarul maxim de incercari random pe care le poate face calculatorul este egal cu numarul de piese * 9)
        {  
            rand = generareNumar(0, 2);
            coloana = generareNumar(0, 2);
            size = getRandomSizeFromPiecesComputer();

            if (size == -1) //daca nu mai avem piese in exteriorul tablei
            {
                break; 
            }

            if (VerificarePunerePiesa(rand, coloana, size)) 
            { 
                if (esteGoala(rand, coloana) || board[rand][coloana].top().size < 3) 
                {      
                    DeseneazaPiesa(rand, coloana, 2, size);

                    for (int i = 0; i < pieceComputerCount; i++) 
                    {
                        if (piecesComputer[i].size == size) 
                        {
                            int x = piecesComputer[i].x;
                            int y = piecesComputer[i].y;
                            int raza = 10 * piecesComputer[i].size;
                            
                            setfillstyle(SOLID_FILL, BLACK); //stergem piesa din exteriorul tablei vizual
                            setcolor(BLACK);
                            fillellipse(x, y, raza, raza);
                            
                            for (int j = i; j < pieceComputerCount - 1; j++) 
                            {
                                piecesComputer[j] = piecesComputer[j + 1]; //stergem piesa din tabloul cu piesele computerului
                            }

                            pieceComputerCount --;
                            break;
                        }
                    }
                    validMove = true; 
                    break;
                }
            }
        }
    }

    if (!validMove) //daca nu mai poate adauga piese pe tabla, computerul va incerca sa mute piesele existente deja in tabla de joc
    { 
        // incearca pentru fiecare combinatie de rand si de coloana posibila sa mute piesa de pe acel rand si coloana
        for(int r = 0; r < 3 && !validMove; r++) 
        {
            for(int c = 0; c < 3 && !validMove; c++) 
            {
                if (!esteGoala(r, c) && board[r][c].top().player == 2) 
                {
                    Piesa piesa = board[r][c].top(); //memorez piesa din randul si coloana aleasa
                    board[r][c].pop(); // se sterge din stiva
                    
                    setfillstyle(SOLID_FILL, BLACK);
                    setcolor(BLACK);

                    int oldX, oldY;
                    getXYFromCell(r, c, oldX, oldY); // in functie de rand si coloana aflu X si Y
                    fillellipse(oldX, oldY, 10 * piesa.size, 10 * piesa.size); // se sterge vizual

                    // caut random caseta in care pot pune piesa 
                    int newRand, newColoana;
                    while (!validMove) 
                    {
                        newRand = generareNumar(0, 2);
                        newColoana = generareNumar(0, 2);

                        // nu pot pune piesa in acelasi loc
                        if (newRand != r || newColoana != c) 
                        { 
                            if (VerificarePunerePiesa(newRand, newColoana, piesa.size)) 
                            {
                                DeseneazaPiesa(newRand, newColoana, 2, piesa.size); // desenez piesa pe tabla
                                if (!esteGoala(r, c)) 
                                {
                                    // desenez piesa care era sub piesa selectata
                                    DoarDeseneazaPiesa(r, c, board[r][c].top().player, board[r][c].top().size);
                                }
                                validMove = true;
                            }
                        }
                    }
                }
            }
        }
    }
}

void playerVScomputer()
{

    srand(time(0));

    initwindow(1200, 500);

    //Desenam sageata pt back
    setfillstyle(SOLID_FILL, BLUE);
    setcolor(BLUE);
    
    bar (75, 30, 110, 50);

    line (40, 40, 75, 20);
    line (75, 20, 75, 60);
    line (40, 40, 75, 60);

    floodfill(57, 40, BLUE); //punem culoarea albastru in interiorul triunghiului desenat mai sus
    
    setcolor (WHITE);
    line(450 + (l / 3), 100, 450 + (l / 3), 400);
    line(600 + (l / 6), 100, 600 + (l / 6), 400);
    line(450, 250 - (l / 6), 600 + (l / 3) + (l / 6), 250 - (l / 6));
    line(450, 250 + (l / 6), 600 + (l / 3) + (l / 6), 250 + (l / 6));

    
    changePlayer(player1, player2);

    char Castigator1[] = "Castigator : player 1 ~ Felicitari!";
    char CastigatorComputer[] = "Ne pare rau, ai pierdut!";
    
    setfillstyle(SOLID_FILL, RED);
    setcolor(RED);
    AddPiesa(100 + (l / 6), 100 + (l / 6), 1, 1);
    AddPiesa(250 + (l / 6), 100 + (l / 6), 1, 1);
    AddPiesa(100 + (l / 6), 200 + (l / 6), 1, 2);
    AddPiesa(250 + (l / 6), 200 + (l / 6), 1, 2);
    AddPiesa(100 + (l / 6), 300 + (l / 6), 1, 3);
    AddPiesa(250 + (l / 6), 300 + (l / 6), 1, 3);

    setfillstyle(SOLID_FILL, BLUE);
    setcolor(BLUE);

    AddPiesaComputer(850 + (l / 6), 100 + (l / 6), 1);
    AddPiesaComputer(1000 + (l / 6), 100 + (l / 6), 1);
    AddPiesaComputer(850 + (l / 6), 200 + (l / 6), 2);
    AddPiesaComputer(1000 + (l / 6), 200 + (l / 6), 2);
    AddPiesaComputer(850 + (l / 6), 300 + (l / 6), 3);
    AddPiesaComputer(1000 + (l / 6), 300 + (l / 6), 3);


    while (!AvemCastigator())
    {

        if (curent_player == 1)
        {
            
            if (ismouseclick(WM_LBUTTONDOWN)) //daca s-a dat click
            {
                int mouseX = mousex();
                int mouseY = mousey();
                clearmouseclick(WM_LBUTTONDOWN);
                
                if ((mouseX >= 75 && mouseX <= 110 && mouseY >= 30 && mouseY <= 40) || (mouseX <= 75 && mouseX >= 40 && mouseY >= 20 && mouseY <= 60)) //in cazul in care dam click pe sageata
                {
                    closegraph(); //se inchide fereastra cu jocul
                    intrebareBack(); //se deschide fereastra cu intrebarea
                }

                int rand, coloana;
                getCell(mouseX, mouseY, rand, coloana);

                ascundereMesaj();

                if (rand >= 0 && rand < 3 && coloana >= 0 && coloana < 3)
                {
                    if (piesa_selected.player == 0 && !esteGoala(rand, coloana))
                    {
                        if(board[rand][coloana].top().player != curent_player)
                        {
                            char eroarerand[] = "eroare : piesa selectata nu iti apartine";
                            afisareMesaj(eroarerand);
                            continue;
                        }
                        piesa_selected.player = board[rand][coloana].top().player;
                        piesa_selected.size = board[rand][coloana].top().size;

                        int x, y;
                        getXYFromCell(rand, coloana, x, y);

                        piesa_selected.x = x;
                        piesa_selected.y = y;

                        setfillstyle(SOLID_FILL, BLACK);
                        setcolor(BLACK);
                        fillellipse(x, y, 30, 30);

                        board[rand][coloana].pop();

                        if (!esteGoala(rand, coloana))
                        {
                            DoarDeseneazaPiesa(rand, coloana, board[rand][coloana].top().player, board[rand][coloana].top().size);
                        }
                    }
                    else if (piesa_selected.player != 0)
                    {
                        if (VerificarePunerePiesa(rand, coloana, piesa_selected.size))
                        {
                            if (VerificarePunereInAcelasiLoc(rand, coloana) == true)
                            {
                                char eroarepozitie[] = "eroare : nu se poate plasa piesa in aceeasi celula";
                                afisareMesaj(eroarepozitie);
                            }
                            else
                            {
                                DeseneazaPiesa(rand, coloana, piesa_selected.player, piesa_selected.size);
                                changePlayer(player1, player2);
                                resetselected();
                            }
                        }
                        else
                        {
                            char eroare[] = "eroare : nu se poate plasa piesa - piesa existenta in celula este mai mare";
                            afisareMesaj(eroare);
                        }
                    }
                }
                else if (piesa_selected.player == 0)
                {
                    checkOutsideBoard(mouseX, mouseY);
                }
            }
        }
        else
        {

            mutareComputer();
            changePlayer(player1, player2);
        }

        if (AvemCastigator())
        {
            setfillstyle(SOLID_FILL, WHITE);
            setcolor(WHITE);
            if (castig == 1)
            {
                line(450, (inceput + 1) * (l / 3) + (l / 6), 450 + (l / 6) + (l / 3), (inceput + 1) * (l / 3) + (l / 6));
                line(450 + (l / 6) + (l / 3), (inceput + 1) * (l / 3) + (l / 6), 750, (inceput + 1) * (l / 3) + (l / 6));
            }
            if (castig == 2)
            {
                line(450 + inceput * (l / 3) + (l / 6), 100, 450 + inceput * (l / 3) + (l / 6), 250);
                line(450 + inceput * (l / 3) + (l / 6), 250, 450 + inceput * (l / 3) + (l / 6), 400);
            }
            if (castig == 3)
            {
                line(450, 100, 600, 250);
                line(600, 250, 750, 400);
            }
            if (castig == 4)
            {
                line(750, 100, 600, 250);
                line(600, 250, 450, 400);
            }

            if (player_castigator == 1)
            {
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
                setcolor(GREEN);
                outtextxy(600 - textwidth(Castigator1) / 2, 75 - textheight(Castigator1) / 2, Castigator1);
            }
            else
            {
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
                setcolor(RED);
                outtextxy(600 - textwidth(CastigatorComputer) / 2, 75 - textheight(CastigatorComputer) / 2, CastigatorComputer);
            }
        }
    }
    while (true)//daca apasa pe sageata, se inchide fereastra cu jocul si se deschide fereastra cu meniul
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            int mouseX = mousex();
            int mouseY = mousey();
            clearmouseclick(WM_LBUTTONDOWN);

            if ((mouseX >= 75 && mouseX <= 110 && mouseY >= 30 && mouseY <= 40) || (mouseX <= 75 && mouseX >= 40 && mouseY >= 20 && mouseY <= 60)) //suntem in cazul in care dam click pe sageata
            {
                closegraph();
                afiseazaMeniu();
            }
        }
    }

    getch();
    closegraph();
}

void meniuIntroducereNume2()
{
    initwindow(800, 600);

    char textinc1[] = "Introdu numele jucatorului:";

    introduNume2(textinc1, player1, 24);
    strcpy(player2, "Computer");

    closegraph();
    playerVScomputer();
}

//Partea de meniu
void afiseazaMeniu()
{
    initwindow(800, 600);
    readimagefile("imagegg.bmp", 0, 0, 800, 600);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);

    char titlu[] = "Gobblet Gobblers";
    outtextxy((800 - textwidth(titlu)) / 2, 50, titlu);

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);

    char optiune1[] = "Player vs Player";
    char optiune2[] = "Player vs Computer";
    char optiune3[] = "Reguli de joc";
    char optiune4[] = "Iesire";
    outtextxy((800 - textwidth(optiune1)) / 2, 200, optiune1);
    outtextxy((800 - textwidth(optiune2)) / 2, 300, optiune2);
    outtextxy((800 - textwidth(optiune3)) / 2, 400, optiune3);
    outtextxy((800 - textwidth(optiune4)) / 2, 500, optiune4);

    while (true)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            int mouseX = mousex();
            int mouseY = mousey();
            clearmouseclick(WM_LBUTTONDOWN);

            if (mouseX >= (800 - textwidth(optiune1)) / 2 && mouseX <= (800 + textwidth(optiune1)) / 2 && mouseY >= 200 && mouseY <= 250) //suntem in cazul in care facem click pe "Player vs Player"
            {
                closegraph(); //se inchide meniul de optiuni
                meniuIntroducereNume(); //se deschide fereastra pt introducerea numelor jucatorilor
            }
            else if (mouseX >= (800 - textwidth(optiune2)) / 2 && mouseX <= (800 + textwidth(optiune2)) / 2 && mouseY >= 300 && mouseY <= 350) //suntem in cazul in care dam click pe "Player vs Computer"
            {
                closegraph(); //se inchide meniul de optiuni
                meniuIntroducereNume2(); //se deschide fereastra pt introducerea numelui jucatorului
                return;
            }
            else if (mouseX >= (800 - textwidth(optiune3)) / 2 && mouseX <= (800 + textwidth(optiune3)) / 2 && mouseY >= 400 && mouseY <= 450) //suntem in cazul in care facem click pe "Reguli de joc"
            {
                closegraph(); //se inchide meniul de optiuni
                meniuReguli(); //se deschide fereastra unde se afla regulile de joc
            }
            else if (mouseX >= (800 - textwidth(optiune4)) / 2 && mouseX <= (800 + textwidth(optiune4)) / 2 && mouseY >= 500 && mouseY <= 550) // suntem in cazul in care facem click pe "Iesire"
            {
                closegraph(); //se inchide meniul de optiuni
                exit; //se inchide fereastra de tot
                return;
            }
        }
    }
}

int main()
{
    afiseazaMeniu();
    return 0;
}

