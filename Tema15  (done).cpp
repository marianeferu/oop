#include<iostream>
using namespace std;

/* Cerinte comune  implementare in C++ folosind clase
 ATENTIE: functiile pe care le-am numit mai jos metode (fie ca sunt
supraincarcari de operatori, fie altfel de functii), pot fi implementate ca functii
prieten in loc de metode ale claselor respective, daca se considera ca aceasta alegere
este mai naturala;
 supraincarcarea operatorilor << si >> pentru iesiri si intrari de obiecte,
dupa indicatiile de mai jos, astfel incat sa fie permise (si ilustrate in program):
 sa existe o metoda publica prin care se realizeaza citirea informațiilor
complete a n obiecte, memorarea și afisarea acestora.

 Clasa ”ABC”- arbori binari de cautare, in reprezentare inlantuita.
Se considera Class Nod{ int info; Nod* st, dr;}
- constructori de inițializare și parametrizati pentru clasa Nod;
- destructor pentru clasa Nod;
Clasa ”ABC” are:
- membru privat de tip „Nod*” reprezentând rădăcina arborelui;
- metode publice pentru inserarea unui element, care sa supraincarce operatorul
+, care va fi aplicat intre un numar reprezentand elementul nou introdus si un arbore;
- supraincarcarea operatorului >>, prin inserari succesive;
- supraincarcarea operatorului <<, care sa afiseze arborele în toate cele 3
metode (preordine, inordine, postordine;
- metoda publica pentru stergerea unui element;
- metoda publica pentru determinarea inaltimii arborelui;
- metoda publica pentru afisarea listei frunzelor

*/


class nod
{
    int info;
    nod* st;
    nod* dr;
    friend class ABC;
    friend void SRD(ostream &out, nod* x);
    friend void RSD(ostream &out, nod* x);
    friend void SDR(ostream &out, nod* x);

public:
    nod()
    {
        info=0;
        this->dr=NULL;
        this->st=NULL;
    }
    nod(int x)
    {
        info=x;
        st=NULL;
        dr=NULL;
    }
    ~nod()
    {
        st=NULL;
        dr= NULL;
        cout<<"d"<<" ";
    }
};

class ABC
{
private: //friend class nod;
    nod* rad;

public:
    ABC()
    {
        rad = NULL;
    }

    ~ABC()
    {
        rad = makeEmpty(rad);
    }

    void insereaza(int x)
    {
        rad = insereaza(x, rad);
    }

    void sterge(int x)
    {
        rad = sterge(x, rad);
    }

    void afisare()
    {
        afisareFrunze(rad);
    }

    nod* makeEmpty(nod* x);
    nod* insereaza(int i, nod* x);
    nod* gmin(nod* x);
    nod* gmax(nod *x);
    nod* sterge(int i, nod* x);

    int inaltime(nod* arb,int h);

    int inaltime()
    {

        return inaltime(rad, 0);
    }

    void afisareFrunze(nod *p);

    ABC &operator+(const int &x);
    friend ostream &operator<<(ostream &,const ABC &);

};

nod* ABC::makeEmpty(nod* x)
{
    if(x == NULL)
        return NULL;
    {
        makeEmpty(x->st);
        makeEmpty(x->dr);
        delete x;
    }
    return NULL;
}

nod* ABC::insereaza(int i, nod* x)
{
    if(x == NULL)
    {
        x = new nod;
        x->info = i;
        x->st = x->dr = NULL;
    }
    else if(i < x->info)
        x->st = insereaza(i, x->st);
    else if(i > x->info)
        x->dr = insereaza(i, x->dr);
    return x;
}

nod* ABC::gmin(nod* x)
{
    if(x == NULL)
        return NULL;
    else if(x->st == NULL)
        return x;
    else
        return gmin(x->st);
}

nod* ABC::gmax(nod *x)
{
    if(x == NULL)
        return NULL;
    else if(x->dr == NULL)
        return x;
    else
        return gmax(x->dr);
}
nod* ABC::sterge(int i, nod* x)
{
    nod* aux;
    if(x == NULL)
        //return NULL;
        cout<<endl<<"Nodul pe care vreti sa il stergeti este inexistent"<<endl;
    else if(i < x->info)
        x->st = sterge(i, x->st);
    else if(i > x->info)
        x->dr = sterge(i, x->dr);
    else if(x->st && x->dr)
    {
        aux = gmin(x->dr);
        x->info = aux->info;
        x->dr = sterge(x->info, x->dr);
    }
    else
    {
        aux = x;
        if(x->st == NULL)
            x = x->dr;
        else if(x->dr == NULL)
            x = x->st;
        delete aux;
    }

    return x;
}

int ABC::inaltime(nod* arb,int h)
{
    h++;

    if(arb->dr==NULL && arb->st==NULL)
        return h;
    else
    {
        if(arb->dr!=NULL && arb->st!=NULL)
            return max(inaltime(arb->dr,h),inaltime(arb->dr,h));
        else if(arb->dr==NULL)
            return inaltime(arb->st,h);
        else
            return inaltime(arb->dr,h);
    }
}

void ABC::afisareFrunze(nod *p)
{
    if(p != NULL)
    {
        afisareFrunze(p->st);
        if(p->st == NULL && p->dr == NULL)
            cout << p->info << " ";

        afisareFrunze(p->dr);
    }
}

ABC &ABC::operator+(const int &x)
{
    this->insereaza(x);
    return *this;
}

void SRD(ostream &out, nod* x)
{
    if(x == NULL)
        return;
    SRD(out, x->st);
    out << x->info<< " ";
    SRD(out, x->dr);
}

void RSD(ostream &out, nod *x)
{
    if(x!=NULL)
    {
        out<<x->info<<" ";
        RSD(out, x->st);
        RSD(out, x->dr);
    }
}
void SDR(ostream &out, nod *x)
{
    if(x!=NULL)
    {
        SDR(out, x->st);
        SDR(out, x->dr);
        out<<x->info<<" ";
    }
}

ostream &operator<<(ostream &out,const ABC &obj)
{
    out << '\n';
    out << "PREORDINE:";
    RSD(out, obj.rad);
    out << '\n';
    out << "INORDINE:";
    SRD(out, obj.rad);
    out << '\n';
    out << "POSTORDINE:";
    SDR(out, obj.rad);
    out << '\n';
    return out;
}

istream &operator>>(istream &in, ABC &arb)
{
    int nr_noduri;
    cout << endl <<"Numarul de noduri este: ";
    in>>nr_noduri;
    if (nr_noduri< 0)
        cout<<"Numarul de noduri trebuie sa fie pozitiv!";
    else
    {
        for(int i=0; i<nr_noduri; i++)
        {
            int val;
            cout<<endl<<"Elementul "<< i + 1 <<" este: ";
            in>>val;
            arb=arb+val;
        }
        return in;
    }
}

void meniu()
{
    cout<<"\n 1.INSERARI MULTIPLE";
    cout<<"\n 2.STERGERE NOD DE LA TASTATURA";
    cout<<"\n 3.AFISARE ARBORE";
    cout<<"\n 4.INALTIME ARBORE";
    cout<<"\n 5.FRUNZE";
    cout<<"\n 0.TERMINARE";
    cout<<endl;
}

void functie()
{
    cout<<"n = ";
    int n, x;
    cin>>n;
    ABC *t =new ABC[n];

    for(int i=0; i<n; ++i)
    {
        char optiune=' ';
        meniu();
        while (optiune != '0')
        {
            cout << endl;
            cout << "\n Optiunea dorita este:";
            cin >> optiune;
            if (((optiune >= '0') && (optiune <= '5')) || (optiune == 'n'))
            {
                switch (optiune)
                {
                case '1':
                    char op;
                    cout << "\n Inserari multiple:";
                    cin >> t[i];
                    break;

                case '2':
                    cout << "\n Nodul care se va sterge:";
                    cin >> x;
                    t[i].sterge(x);
                    break;

                case '3':
                    cout << "\n Arborele este:";
                    cout << t[i] << '\n';
                    break;

                case '4':
                    cout << "\n Inaltimea arborelui este:";
                    cout << t[i].inaltime();
                    break;

                case '5':
                    t[i].afisare();
                    break;

                case '0':
                    break;
                }
            }
            else cout<<endl<<"\n Optiunea nu exista in meniu!"<<endl;
        }
    }
    for(int i = 0; i < n; ++i)
        cout << t[i] <<endl;


    delete[] t;
}
int main()
{
    functie();
}
