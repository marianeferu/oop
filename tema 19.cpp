#include <iostream>
#include<cstring>
using namespace std;

/*Se dau urmatoarele clase:
- Persoana(int id, char* nume)
- Abonat(char *nr_telefon) : Persoana
- Abonat_Skype(id_skype) : Abonat
- Abonat_Skype_Romania (adresa_mail) : Abonat_Skype
- Abonat_Skype_Extern(tara) : Abonat_Skype
Sa se construiasca clasa Agenda ce contina o lista de abonati si sa se
supraincarce operatorul [ ](indexare)care returneaza abonatul cu numele
precizat .



Clasele derivate trebuie sa contina constructori parametrizati (prin care sa se
evidentieze transmiterea parametrilor catre constructorul din clasa de baza)
si destructori.
 toate clase vor conține obligatoriu constructori de inițializare,
parametrizati și de copiere, destructor, iar operatorii „=”, „>>”, „<<”
să fie supraincarcati.
 ilustrarea conceptelor: upcasting, downcasting, functii virtuale (pure –
unde se considera mai natural)
 utilizarea variabilelor și functiilor statice
 citirea informațiilor complete a n obiecte, memorarea și afisarea
acestora
*/

class Persoana
{
protected:

    int id;
    char *nume;
    static int nr;

public:

    Persoana(int id_ul)
    {
        id=id_ul;
        nume=NULL;
        nr++;
    }

    Persoana(char *nume_pers)
    {
        nr++;
        nume=new char[strlen(nume_pers)+1];
        strcpy(nume,nume_pers);
        id=0;
    }

    Persoana(int id_ul, char *nume_pers)
    {
        nr++;
        id=id_ul;
        nume=new char[strlen(nume_pers)+1];
        strcpy(nume, nume_pers);
    }

    Persoana()
    {
        id=0;
        nume=NULL;
        nr++;
    }

    virtual ~Persoana()
    {
        nr--;
        cout<<"destruct_persoana"<<" ";
        delete [] nume;
    }

    Persoana ( const Persoana &p )
    {
        id=p.id;
        nume= new char [strlen(p.nume)+1];
        strcpy(nume,p.nume);
    }

    const Persoana & operator=(const Persoana &);
    friend istream & operator>>( istream &, Persoana &);
    friend ostream & operator<<( ostream &, Persoana &);
};

int Persoana::nr = 0;

const Persoana&  Persoana :: operator=(const Persoana &p)
{
    if(this!=&p)
    {
        id=p.id;
        nume= new char [strlen(p.nume)+1];
        strcpy(nume,p.nume);
    }
    return *this;
}

istream & operator>>(istream &in, Persoana &p)
{
    cout<<endl;
    cout<<"Dati id-ul"<<" ";
    in>>p.id;

    delete[] p.nume;
    p.nume = new char[256];
    cout<<"Introduceti nume ";
    in>>p.nume;

    return in;
}

ostream & operator<<(ostream &out, Persoana &p)
{
    out<<p.id<<" "<<p.nume;
    return out;
}

class Abonat: public Persoana
{
protected:

    char *nr_telefon;

public:

    Abonat(char *nr_tel_abonat,int id_ul,char *nume_pers): Persoana(id_ul,nume_pers)
    {
        nr_telefon= new char[strlen(nr_tel_abonat)+1];
        strcpy(nr_telefon,nr_tel_abonat);
    }

    Abonat () : Persoana ()
    {
        nr_telefon=NULL;
    }

    virtual ~Abonat()
    {
        cout << "destruct_abonat"<<" ";
        delete[] nr_telefon;
    }

    Abonat (const Abonat &a ): Persoana(a.id,a.nume)
    {
        nr_telefon= new char [strlen(a.nr_telefon)+1];
        strcpy(nr_telefon, a.nr_telefon);
    }

    const Abonat & operator=(const Abonat &);
    friend istream & operator>>(istream &, Abonat &);
    friend ostream & operator<<(ostream &, Abonat &);

};
const Abonat &  Abonat :: operator=(const Abonat &p)
{
    if(this!=&p)
    {
        id=p.id;
        nume= new char [strlen(p.nume)+1];
        strcpy(nume,p.nume);
        nr_telefon= new char [strlen(p.nr_telefon)+1];
        strcpy(nr_telefon, p.nr_telefon);
    }

    return *this;
}

istream & operator>>(istream &in, Abonat &p)
{
    cout<<"Dati abonatul ";
    in>>p.id;
    delete[] p.nume;
    p.nume = new char[256];
    cout<<"Introduceti nume ";
    in>>p.nume;

    delete[] p.nr_telefon;
    p.nr_telefon = new char[256];
    cout<<"Introduceti nr de tel ";
    in>>p.nr_telefon;
    return in;
}

ostream & operator<<(ostream &out, Abonat &p)
{
    out<<p.id<<" "<<p.nume;
    out<<p.nr_telefon;
    return out;
}

class Abonat_Skype : public Abonat
{
protected:

    char *id_skype;

public:

    Abonat_Skype(char *id_abonat_skype,char *nr_tel_abonat,int id_ul,char *nume_pers): Abonat(nr_tel_abonat, id_ul, nume_pers)
    {
        id_skype= new char[strlen(id_abonat_skype)+1];
        strcpy(id_skype,id_abonat_skype);
    }

    Abonat_Skype():Abonat()
    {
        id_skype=NULL;
    }

    virtual ~Abonat_Skype()
    {
        cout<<"destruct_abonat_Skype"<<" ";
        delete[] id_skype;
    }

    Abonat_Skype (const Abonat_Skype &a) :Abonat (a.nr_telefon, a.id, a.nume )
    {
        id_skype=new char [strlen(a.id_skype)+1];
        strcpy(id_skype,a.id_skype);
    }

    const Abonat_Skype & operator=(const Abonat_Skype &);
    friend istream & operator>>( istream &, Abonat_Skype &);
    friend ostream & operator<<( ostream &, Abonat_Skype &);

};

const Abonat_Skype &  Abonat_Skype :: operator=(const Abonat_Skype &p)
{
    if(this!=&p)
    {
        id=p.id;
        nume= new char [strlen(p.nume)+1];
        strcpy(nume,p.nume);
        nr_telefon= new char [strlen(p.nr_telefon)+1];
        strcpy(nr_telefon, p.nr_telefon);
        id_skype=new char [strlen(p.id_skype)+1];
        strcpy(id_skype,p.id_skype);
    }

    return *this;
}

istream & operator>>(istream &in, Abonat_Skype &p)
{
    cout<<"Dati abonatul"<<" ";
    in>>p.id;

    delete[] p.nume;
    p.nume = new char[256];
    cout<<"Introduceti nume";
    in>>p.nume;

    delete[] p.nr_telefon;
    p.nr_telefon = new char[256];
    cout<<"Introduceti nr tel";
    in>>p.nr_telefon;

    delete[] p.id_skype;
    p.id_skype = new char[256];
    cout<<"Id skype";
    in>>p.id_skype;
    return in;
}

ostream & operator<<(ostream &out, Abonat_Skype &p)
{
    out<<p.id<<" "<<p.nume;
    out<<p.nr_telefon;
    out<<p.id_skype;
    return out;
}

class Abonat_Skype_Romania: public Abonat_Skype
{
protected:

    char *adresa_mail;

public:

    Abonat_Skype_Romania(char *mail_ab_skype_ro,char *id_abonat_skype,char *nr_tel_abonat,int id_ul,char *nume_pers): Abonat_Skype(id_abonat_skype, nr_tel_abonat, id_ul, nume_pers)
    {
        adresa_mail=new char [strlen(mail_ab_skype_ro)+1];
        strcpy(adresa_mail, mail_ab_skype_ro);
    }

    Abonat_Skype_Romania()
    {
        adresa_mail=NULL;
    }
    ~Abonat_Skype_Romania()
    {
        cout<<"destruct_abonat_Skype_Romania"<<" ";
        delete[] adresa_mail;
    }
    Abonat_Skype_Romania(const Abonat_Skype_Romania &a): Abonat_Skype (a.id_skype,a.nr_telefon,a.id,a.nume)
    {
        adresa_mail=new char [strlen(a.adresa_mail)+1];
        strcpy(adresa_mail, a.adresa_mail);
    }

    const Abonat_Skype_Romania & operator=(const Abonat_Skype_Romania &);
    friend istream & operator>>( istream &, Abonat_Skype_Romania &);
    friend ostream & operator<<( ostream &, Abonat_Skype_Romania &);
};

const Abonat_Skype_Romania &  Abonat_Skype_Romania :: operator=(const Abonat_Skype_Romania &p)
{
    if(this!=&p)
    {
        id=p.id;
        nume= new char [strlen(p.nume)+1];
        strcpy(nume,p.nume);
        nr_telefon= new char [strlen(p.nr_telefon)+1];
        strcpy(nr_telefon, p.nr_telefon);
        id_skype=new char [strlen(p.id_skype)+1];
        strcpy(id_skype,p.id_skype);
        adresa_mail=new char [strlen(p.adresa_mail)+1];
        strcpy(adresa_mail, p.adresa_mail);
    }

    return *this;
}

istream & operator>>(istream &in, Abonat_Skype_Romania &p)
{
    cout<<"Dati abonatul"<<" ";
    in>>p.id;

    delete[] p.nume;
    p.nume = new char[256];
    cout<<"Introduceti nume";
    in>>p.nume;

    delete[] p.nr_telefon;
    p.nr_telefon = new char[256];
    cout<<"Introduceti nr tel ";
    in>>p.nr_telefon;

    delete[] p.id_skype;
    p.id_skype = new char[256];
    cout<<"Id skype ";
    in>>p.id_skype;

    delete[] p.adresa_mail;
    p.adresa_mail = new char[256];
    cout<<"Adresa mail ";
    in>>p.adresa_mail;
    return in;
}

ostream & operator<<(ostream &out, Abonat_Skype_Romania &p)
{
    out<<p.id<<" "<<p.nume;
    out<<p.nr_telefon;
    out<<p.id_skype;
    out<<p.adresa_mail;
    return out;
}

class Skype_Extern: public Abonat_Skype
{
protected :

    char *tara;

public:

    Skype_Extern(char *tara_skype_ext,char *id_abonat_skype,char *nr_tel_abonat,int id_ul,char *nume_pers)
    {
        tara= new char [strlen(tara_skype_ext)+1];
        strcpy(tara, tara_skype_ext);
    }
    Skype_Extern()
    {
        tara=NULL;
    }
    ~Skype_Extern()
    {
        delete[] tara;
    }
    Skype_Extern (const Skype_Extern &a) : Abonat_Skype (a.id_skype,a.nr_telefon,a.id,a.nume)
    {
        tara= new char [strlen(a.tara)+1];
        strcpy(tara,a.tara);

    }

    const Skype_Extern & operator=(const Skype_Extern &);
    friend istream & operator>>( istream &, Skype_Extern &);
    friend ostream & operator<<( ostream &, Skype_Extern &);

};


const Skype_Extern &  Skype_Extern :: operator=(const Skype_Extern &p)
{
    if(this!=&p)
    {
        id=p.id;
        nume= new char [strlen(p.nume)+1];
        strcpy(nume,p.nume);
        nr_telefon= new char [strlen(p.nr_telefon)+1];
        strcpy(nr_telefon, p.nr_telefon);
        id_skype=new char [strlen(p.id_skype)+1];
        strcpy(id_skype,p.id_skype);
        tara= new char [strlen(p.tara)+1];
        strcpy(tara,p.tara);
    }

    return *this;
}

istream & operator>>(istream &in, Skype_Extern &p)
{
    cout<<"Dati abonatul ";
    in>>p.id;
    delete[] p.nume;
    p.nume = new char[256];
    cout<<"Introduceti nume ";
    in>>p.nume;

    delete[] p.nr_telefon;
    p.nr_telefon = new char[256];
    cout<<"Introduceti nr de tel ";
    in>>p.nr_telefon;

    delete[] p.id_skype;
    p.id_skype = new char[256];
    cout<<"id skype ";
    in>>p.id_skype;

    delete[] p.tara;
    p.tara = new char[256];
    cout<<"Introduceti tara ";
    in>>p.tara;
    return in;
}

ostream & operator<<(ostream &out, Skype_Extern &p)
{
    out<<p.id<<" "<<p.nume;
    out<<p.nr_telefon;
    out<<p.id_skype;
    out<<p.tara;
    return out;
}

class Agenda
{
    Abonat* lista_abonati;
    int nr_abonati;

public:

    Agenda()
    {
        lista_abonati=NULL;
        nr_abonati=0;
    }
    Agenda( int n)
    {
        lista_abonati=new Abonat[n], nr_abonati=n;
    }
    ~Agenda()
    {
        delete [] lista_abonati;
    }

    Agenda (const Agenda &ag)
    {
        lista_abonati= new Abonat [ag.nr_abonati];
        nr_abonati= ag.nr_abonati;
        for(int i=0; i<nr_abonati; i++)
            lista_abonati[i]=ag.lista_abonati[i];
    }

    const Agenda & operator=(const Agenda &);
    friend istream & operator>>( istream &, Agenda &);
    friend ostream & operator<<( ostream &, Agenda &);

    Abonat & operator [] (int index)
    {
        return  lista_abonati[index];
    }

    const Abonat & operator [](int index) const
    {
        return lista_abonati[index];   //nu te lasa sa faci atribuire,ci doar sa extragi elem
    }
};

const Agenda & Agenda :: operator=(const Agenda &ag)
{
    if(this!=&ag)
    {
        lista_abonati= new Abonat [ag.nr_abonati];
        nr_abonati= ag.nr_abonati;
        for(int i=0; i<nr_abonati; i++)
            lista_abonati[i]=ag.lista_abonati[i];
    }
    return *this;
}

istream & operator>>(istream &in, Agenda &ag)
{
    for(int i=0; i<ag.nr_abonati; i++)
        in>>ag.lista_abonati[i];

    return in;
}

ostream &operator<<(ostream &out, Agenda &ag)
{
    for(int i=0; i<ag.nr_abonati; i++)
        out<<ag.lista_abonati[i];

    return out;
}

void meniu()
{
    cout<<"1. Abonat Skype Extern"<<endl;
    cout<<"2. Abonat skype Romania"<<endl;
    cout<<" Introduceti tipul de abonat skype "<<endl;
}

int main()
{
    int n;
    cout<<"Introduceti nr de abonati ";
    cin>>n;

    Agenda ag (n);

    for(int i=0; i<=n-1; i++)
    {
        meniu();
        int optiune;
        cin>>optiune;

        Skype_Extern ab_ext;
        Abonat_Skype_Romania ab_ro;

        switch(optiune)
        {
        case 1:

            cin>>ab_ext;
            ag[i]=ab_ext;
            break;

        case 2:

            cin>>ab_ro;
            ag[i]=ab_ro;
            break;
        }
    }

    for(int i=0; i<n; i++)
        cout<<ag[i];
}






