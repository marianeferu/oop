#include <iostream>
#include<cstring>
#include<fstream>
#include<string>
#define N 50
using namespace std;

/*
Cerinte comune tuturor temelor:
1. tratarea exceptiilor
2. utilizarea conceptelor de Dynamic_Cast și Static_Cast
3. utilizarea sabloanelor
4. citirea informațiilor complete a n obiecte, memorarea și afisarea
acestora
Obs. Se pot considera și probleme din fișierul Tema2.docx,
adaptate la cerintele de mai sus.
 Cerinte generale aplicate fiecarei teme din acest fisier:
- să se identifice și să se implementeze ierarhia de clase;
- clasele sa conțină constructori, destructori, =, >>, <<;
- clasa de baza sa conțină funcție virtuala de afisare, rescrisa în
clasele derivate;
- clasele derivate trebuie sa contina cel puțin constructori parametrizati
și de copiere prin care sa se evidentieze transmiterea parametrilor
către constructorul din clasa de baza.

Tema 7. La realizarea unui film(nume,tip,durata), participa o mulțime de
persoane: un regizor, actori, personal tehnic etc. Dacă filmul este bun,
atunci el ruleaza într-un numar de cinematografe și realizeaza incasari
substantiale pe fiecare cinematogram în parte. Fiecare personal (cnp,
nume, nume_film) are prevăzut prin contract un procent din incasari, drept
urmare primește, pentru fiecare film la care participa, o anumita suma.
Actorii, dacă sunt personaje principale, primesc un bonus de 10% din
incasari, iar regizorul are prevăzut și o suma fixa, indiferent de calitatea
filmului produs.
Cerinta suplimentara:
- Sa se construiasca clasa template FirmaDistributie care sa conțină
informații despre filmele realizate într-un an. Clasa conțina numărul total
de persoane implicat incrementat automat), numărul de actori
(incrementat automat) și un vector de persoane alocat dinamic.
- Sa se construiasca o specializare a acestei clase pentru un tip de data
la alegere care sa conțină numărul actorilor care au fost distribuiti în
roluri principale.

*/

class Personal
{
    double salariu;
    string cnp;
    string nume;
    string film;

public:

    Personal(): salariu(0), cnp("Necunoscut"), nume("Necunoscut"), film("Necunoscut") {};
    Personal(double s, string c, string n, string f);

    Personal & operator=(const Personal &);

    friend istream & operator >>(istream &, Personal &);
    friend ostream & operator <<(ostream &, const Personal &);

    virtual void Afisare() {};

};

Personal :: Personal ( double s, string c, string n, string f)
{
    try
    {
        salariu = s;
        cnp = "Invalid, nu contine doar cifre";
        nume = n;
        film = f;

        char * aux = new char [c.size()+1];
        copy(c.begin(), c.end(), aux);
        aux[c.size()] = '\0';
        if(strspn(aux, "0123456789") != strlen(aux))
        {
            delete[] aux;
            throw 0;
        }

        cnp = c;
        delete[] aux;

    }
    catch (int x)
    {
        cout<<"CNP invalid"<<"\n";

    }
}

istream & operator >>(istream &in, Personal &ob)
{
    in>>ob.salariu;
    in>>ob.cnp;
    in>>ob.nume;
    in>>ob.film;
    return in;

}

ostream & operator <<(ostream &out, const Personal &ob)
{
    out<<"Salariu este: "<<ob.salariu<<"\n";
    out<<"Cnp_ul este: "<<ob.cnp<<"\n";
    out<<"Numele este: "<<ob.nume<<"\n";
    out<<"Filmul este: "<<ob.film<<"\n";
    return out;

}

Personal & Personal::operator = (const Personal &ob)
{
    if(this!=&ob)
    {
        salariu=ob.salariu;
        cnp=ob.cnp;
        nume=ob.nume;
        film=ob.film;

    }
    return *this;
}

class Filme
{
    string nume;
    string tip;
    int durata;
    int nr_pers;
    Personal **creditele_filmului;

public:

    Filme(): nume("Necunoscut"), tip("Necunoscut"), durata(0), nr_pers(5), creditele_filmului( new Personal *[nr_pers] )
    {
        for(int i = 0; i < nr_pers; ++i )
            creditele_filmului[i] = new Personal[nr_pers];
    }

    Filme( string n, string t, int d, int nr_p, Personal ** p) : nume(n), tip(t), durata(d), nr_pers(nr_p), creditele_filmului(p) {}

    Filme& operator= (const Filme&);

    friend istream & operator >> (istream &, Filme&);
    friend ostream & operator << (ostream &, const Filme &);

};

Filme& Filme::operator=(const Filme& ob)
{
    if(this != &ob)
    {
        nume = ob.nume;
        tip = ob.tip;
        durata = ob.durata;
        nr_pers = ob.nr_pers;
        for(int i = 0; i < nr_pers; ++i)
            creditele_filmului[i] = ob.creditele_filmului[i];
    }

    return *this;

}

ostream & operator << (ostream &out, const Filme &ob )
{
    out<<"Numele filmului este "<< ob.nume <<"\n";
    out<<"Tipul filmului este " << ob.tip<<"\n";
    out<<"Durata filmului este "<< ob.durata<<"\n";
    out<<"Numarul persoanelor este "<< ob.nr_pers<<"\n";
    out<<"Creditul este: \n";

    for(int i= 0; i< ob.nr_pers; i++)
        (ob.creditele_filmului[i]) -> Afisare();

    return out;
}

istream & operator >> (istream & in, Filme& ob)
{
    in >> ob.nume;
    in >> ob.tip;
    in >> ob.durata;
    in >> ob.nr_pers;

    for(int i = 0; i < ob.nr_pers; ++i)
        in >> *ob.creditele_filmului[i];

    return in;
}

class Regizor: public Personal
{
public:

    Regizor(): Personal() {}
    Regizor(double _salariu, string _cnp, string _nume, string _film) : Personal( _salariu, _cnp, _nume, _film ) {}

    Regizor& operator= (const Regizor&);
    friend istream & operator >> (istream &, Regizor&);
    friend ostream & operator << (ostream &, const Regizor&);

    void Afisare()
    {
        cout<<*this;
    }
};

Regizor& Regizor::operator= (const Regizor& ob)
{
    if(this != &ob)
    {
        Personal::operator=(ob);
    }

    return *this;
}

istream & operator >> (istream & in, Regizor& ob)
{
    in >> dynamic_cast<Personal&>(ob);

    return in;
}

ostream & operator << (ostream & out, const Regizor& ob)
{
    out << "Clasa Personal Regizor\n";
    out << dynamic_cast<const Personal& > (ob);

    return out;
}

class Tehnic: public Personal
{
public:

    Tehnic(): Personal() {}
    Tehnic(double _salariu, string _cnp, string _nume, string _film) : Personal ( _salariu, _cnp, _nume, _film ) {}

    Tehnic & operator = (const Tehnic &);
    friend istream & operator >> (istream &, Tehnic &);
    friend ostream & operator << (ostream &, const Tehnic &);

    void Afisare()
    {
        cout<<*this;
    }
};

Tehnic & Tehnic :: operator =( const Tehnic &ob)
{
    if (this!=&ob)
    {
       Personal::operator=(ob);

    }

    return *this;
}

istream & operator >> ( istream &in, Tehnic &ob)
{
    in>> static_cast< Personal& > (ob);

    return in;

}

ostream & operator << ( ostream &out, const Tehnic &ob)
{
    out<<"Clasa Personal Tehnic\n";
    out<<static_cast< const Personal& > (ob);

    return out;
}

class Actor_principal: public Personal
{
public:

    Actor_principal(): Personal() {}
    Actor_principal (double _salariu, string _cnp, string _nume, string _film) : Personal ( _salariu, _cnp, _nume, _film ) {}

    Actor_principal & operator = (const Actor_principal &);
    friend istream & operator >> (istream &, Actor_principal &);
    friend ostream & operator << (ostream &, const Actor_principal &);

    void Afisare()
    {
        cout<<*this;
    }
};

Actor_principal& Actor_principal :: operator =( const Actor_principal &ob)
{
    if (this!=&ob)
    {
        Personal::operator=(ob);
    }

    return *this;
}

istream & operator >> ( istream &in, Actor_principal &ob)
{
    in>> dynamic_cast< Personal& > (ob);

    return in;
}

ostream & operator << ( ostream &out, const Actor_principal &ob)
{
    out<<"Clasa Actor Principal\n";
    out<< dynamic_cast< const Personal& > (ob);

    return out;
}

class Actor_secundar: public Personal
{

public:

    Actor_secundar(): Personal() {}
    Actor_secundar (double _salariu, string _cnp, string _nume, string _film) : Personal ( _salariu, _cnp, _nume, _film ) {}

    Actor_secundar & operator = (const Actor_secundar &);
    friend istream & operator >> (istream &, Actor_secundar &);
    friend ostream & operator << (ostream &, const Actor_secundar &);

    void Afisare()
    {
        cout<<*this;
    }
};

Actor_secundar& Actor_secundar :: operator =( const Actor_secundar &ob)
{
    if (this!=&ob)
    {
        Personal::operator=(ob);
    }

    return *this;
}

istream & operator >> ( istream &in, Actor_secundar &ob)
{
    in>> dynamic_cast< Personal& > (ob);

    return in;
}

ostream & operator << ( ostream &out, const Actor_secundar &ob)
{
    out<<"Clasa Actor Secundar\n";
    out<< dynamic_cast< const Personal& > (ob);

    return out;
}

template <class T1, class T2>
class FirmaDistributie
{

    T1 numarActori;
    T2 ** Personaje;

public:

    FirmaDistributie() : numarActori(0), Personaje(new T2* [N])
    {
        for(int i = 0; i < N; ++i)
            Personaje[i] = new T2 [N];
    }

    FirmaDistributie(T1 _numarActori, T2** _Personaje) : numarActori(_numarActori), Personaje(_Personaje) {}

    FirmaDistributie<T1, T2>& operator= (const FirmaDistributie<T1, T2>&);

    template<class Y1, class Y2>
    friend istream & operator >> (istream &, FirmaDistributie<Y1, Y2>& );
    template<class Y1, class Y2>
    friend ostream & operator << (ostream &, const FirmaDistributie<Y1, Y2>& );
};

template <class T1, class T2>
FirmaDistributie<T1, T2>& FirmaDistributie<T1, T2>::operator= (const FirmaDistributie <T1, T2> & ob)
{
    if(this != &ob)
    {
        numarActori = ob.numarActori;
        for(int i = 0; i < ob.numarActori; ++i)
            Personaje[i] = ob.Personaje[i];
    }

    return *this;
}

template < class Y1, class Y2>
istream & operator >> (istream & in, FirmaDistributie<Y1, Y2>& ob)
{
    in >> ob.numarActori;
    for(int i = 0; i < ob.numarActori; ++i)
        in >> (*ob.Personaje[i]);

    return in;
}

template < class Y1, class Y2>
ostream & operator << (ostream & out, const FirmaDistributie<Y1, Y2>& ob)
{
    out<<"Clasa FirmaDistributie Neparametrizata\n";
    out<<"Numarul de actori este: "<<ob.numarActori<<'\n';
    for(int i = 0; i < ob.numarActori; ++i)
        (*ob.Personaje[i]).Afisare();

    return out;
}

template <>
class FirmaDistributie<int, Actor_principal>
{
    int Contor;
    Actor_principal **Actori;

public:

    FirmaDistributie() : Contor(0), Actori(new Actor_principal* [N])
    {
        for(int i = 0; i < N; ++i)
            Actori[i] = new Actor_principal [N];
    }

    FirmaDistributie(int _Contor, Actor_principal** _Actori) : Contor(_Contor), Actori(_Actori) {}

    void Afiseaza()
    {
        cout<<"Numarul de Actori din Clasa Specializata este: "<< Contor <<'\n';
        cout<<"Clasa Firma Distributie Specializata\n";
        for(int i = 0; i < Contor; ++i)
            Actori[i] -> Afisare();
    }
};

int main()
{
    ifstream fin ("document.txt");

    Personal **P;
    P = new Personal* [4];

    double salariu;
    string CNP, Nume, Film;
    int X;

    for(int i = 0; i < 4; ++i)
    {
        fin >> X;
        fin >> salariu >> CNP >> Nume >> Film;
        switch(X)
        {
        case 1:

            P[i] = new Actor_principal(salariu, CNP, Nume, Film);
            break;

        case 2:

            P[i] = new Actor_secundar(salariu, CNP, Nume, Film);
            break;

        case 3:

            P[i] = new Regizor(salariu, CNP, Nume, Film);
            break;

        case 4:

            P[i] = new Tehnic(salariu, CNP, Nume, Film);
            break;

        }
    }

    for(int i = 0; i < 4; ++i)
        (*P[i]).Afisare();     //cout<<*P[i];

    cout<<'\n';
    Filme M("Romanticii", "Romantic", 120, 4, P);

    FirmaDistributie<int, Personal> Firma(4, P);

    Actor_principal *Actori[2];
    Actori[0] = new Actor_principal(124.5, "124234", "Bogy", "Horror");
    Actori[1] = new Actor_principal(124.5, "124234", "Dana", "Horror");

    FirmaDistributie<int, Actor_principal> Distributie(2, Actori);
    Distributie.Afiseaza();
}
