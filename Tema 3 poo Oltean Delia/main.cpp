#include <iostream>
#include <cstring>
#include <vector>
#include <list>

using namespace std;

class Exceptie: public exception
{
    virtual const char* what() const throw()
    {
        return "Tara nu a fost introdusa cu litera mare.\n"
               "Reintroduceti: \n";
    }
} exceptia_mea;

class Persoana
{
protected:
    string nume;
    int ID;
    double pret_abonament;

public:
    Persoana();
    Persoana(string nume, int ID, double pret_abonament);
    Persoana(const Persoana& p);
    Persoana& operator=(const Persoana& p);
    ~Persoana();
    friend istream &operator>>(istream &in, Persoana &p);
    friend ostream &operator<<(ostream &out, const Persoana &p);

    int getid()
    {
        return this->ID;
    };
};
Persoana :: Persoana()
{
    nume = "necunoscuta";
    ID = 0;
    pret_abonament = 0;
}

Persoana :: Persoana(string nume, int ID, double pret_abonament)
{
this->nume = nume;
this->ID = ID;
this->pret_abonament = pret_abonament;
}

Persoana :: Persoana(const Persoana& p)
{
    this->nume = p.nume;
    this->ID = p.ID;
    this->pret_abonament = p.pret_abonament;
}

Persoana& Persoana :: operator=(const Persoana& p)
{
    if(this != &p)
    {
        this->nume = p.nume;
        this->ID = p.ID;
        this->pret_abonament = p.pret_abonament;
    }

    return *this;
}
Persoana :: ~Persoana()
{}

auto verificare=[](int a) // functie lambda
{
    return a<0;
};
void eroare(float a) // doua erori tratate
{
    if(verificare(a))
        throw 11;
    if((int)a != a)
        throw 12.34;
}

istream &operator>>(istream &in, Persoana &p)
{
    cout<<"Persoana este: ";
    in>>p.nume;
    int k = 1;
    while(k==1)
    {
        cout<<"IDul Persoanei este: ";
        float x;
        in>>x;
        try
        {
            eroare(x);
            p.ID = (int)x;
            k = 0;
        }

        catch(int)
        {
            cout<<"Valoarea introdusa este negativa, iar IDul poate fi doar pozitiv.\n"
                  "Reintroduceti:\n";
        }

        catch(double)
        {
            cout<<"ID-ul este un numar intreg si a fost introdus un float.\n"
                  "Reintroduceti: \n";
        }

    }
    cout<<"Pretul abonamentului este: ";
    in>>p.pret_abonament;

    return in;
}

ostream &operator<<(ostream &out, const Persoana &p)
{
    out<<"Persoana este: "<<p.nume<<endl;
    out<<"IDul Persoanei este: "<<p.ID<<endl;
    out<<"Pretul abonamentului este: "<<p.pret_abonament<<endl;

    return out;
}


class Abonat : public Persoana
{
protected:
    string nr_telefon;
public:
    Abonat();
    Abonat(string nume, int ID, double pret_abonament, string nr_telefon);
    Abonat(const Abonat& f);
    Abonat& operator=(const Abonat& f);
    ~Abonat();
    friend istream &operator>>(istream &in, Abonat &f);
    friend ostream &operator<<(ostream &out, const Abonat &f);

};

Abonat :: Abonat():Persoana()
{
    nr_telefon = "necunoscut";
}

Abonat :: Abonat(string nume, int ID, double pret_abonament, string nr_telefon):Persoana(nume, ID, pret_abonament)
{
this->nr_telefon = nr_telefon;
}

Abonat :: Abonat(const Abonat& f):Persoana(f)
{
    this->nr_telefon = f.nr_telefon;
}

Abonat& Abonat :: operator=(const Abonat& f)
{
    if(this != &f)
    {
        Persoana ::operator=(f);
        this->nr_telefon = f.nr_telefon;
    }

    return *this;
}

Abonat :: ~Abonat()
{}

void eroare2(string a)
{
    for (int i = 0; i < a.size(); i++)
        if(a[i] <= '0' && a[i] >= '9')
            throw 2.3;
}

istream &operator>>(istream &in, Abonat &f)
{

    in >> (Persoana& )f;
    int k = 1;
    while(k==1)
    {
        cout<<"Numarul de telefon este: ";
        in>>f.nr_telefon;
        try
        {
            eroare2(f.nr_telefon);
            k = 0;
        }
        catch(double)
        {
            cout<<"Numarul de telefon nu exista, formatul acesteuia fiind gresit.\n"
                  "Reintroduceti:\n";
        }
    }

    return in;
}

ostream &operator<<(ostream &out, const Abonat &f)
{
    out<<(Persoana&) f;
    out<<"Numarul de telefon este: "<<f.nr_telefon<<endl;
    return out;
}

class Abonat_Skype_Romania: public Abonat
{
protected:
    string adresa_de_mail;
    int cnp;
public:
    Abonat_Skype_Romania();
    Abonat_Skype_Romania(string nume, int ID, double pret_abonament, string nr_telefon, string adresa_de_mail, int cnp);
    Abonat_Skype_Romania(const Abonat_Skype_Romania &t);
    Abonat_Skype_Romania& operator =(const Abonat_Skype_Romania &t);
    ~Abonat_Skype_Romania();
    friend istream &operator>>(istream &in, Abonat_Skype_Romania &t);
    friend ostream &operator<<(ostream &out, const Abonat_Skype_Romania &t);
    

    int getcnp()
    {
        return this->cnp;
    }

    bool verifcnp(int cnp)
    {
        if(this->cnp >= cnp)
            return true;
        else
            return false;
    }
};

Abonat_Skype_Romania :: Abonat_Skype_Romania():Abonat()
{
    this->adresa_de_mail = "necunoscut";
    this->cnp = 0;
   
}

Abonat_Skype_Romania :: Abonat_Skype_Romania(string nume, int ID, double pret_abonament, string nr_telefon, string adresa_de_mail, int cnp):Abonat(nume, ID, pret_abonament, nr_telefon)
{
this->adresa_de_mail = adresa_de_mail;
this->cnp = cnp;
}

Abonat_Skype_Romania :: Abonat_Skype_Romania(const Abonat_Skype_Romania &t):Abonat(t)
{
    this->adresa_de_mail = t.adresa_de_mail;
    this->cnp = t.cnp;
}

Abonat_Skype_Romania& Abonat_Skype_Romania ::  operator =(const Abonat_Skype_Romania &t)
{
    if(this != &t)
    {
        Abonat :: operator=(t);
        this->adresa_de_mail = t.adresa_de_mail;
        this->cnp = t.cnp;
    }
    return *this;
}

Abonat_Skype_Romania :: ~Abonat_Skype_Romania()
{}


void eroare3(int a)
{
    if(a < 0 || a > 1 )
        throw 1;
}

istream &operator>>(istream &in, Abonat_Skype_Romania &t)
{
    in>>(Abonat&)t;
    cout<<"Adresa de mail a abonatului din Romania este: ";
    in>>t.adresa_de_mail;
    cout<<"CNPul este: ";
    in>>t.cnp;
    return in;
}

ostream &operator<<(ostream &out, const Abonat_Skype_Romania &t)
{
    out<<(Abonat&) t;
    cout<<"Adresa de mail a abonatului din Romania este: "<<t.adresa_de_mail<<endl;
    cout<<"CNP ul abonatului din Romania este de: "<<t.cnp<<endl;
}

class Abonat_Skype_Extern: public Abonat
{
protected:
    string tara;
    int cnpE;

public:
    Abonat_Skype_Extern();
    Abonat_Skype_Extern(string nume, int ID, double pret_abonament, string nr_telefon, string tara, int cnpE);
    Abonat_Skype_Extern(const Abonat_Skype_Extern &l);
    ~Abonat_Skype_Extern();
    Abonat_Skype_Extern& operator=(const Abonat_Skype_Extern &l);
    friend istream& operator>>(istream &in, Abonat_Skype_Extern &l);
    friend ostream& operator<<(ostream &out, const Abonat_Skype_Extern &l);
    
    int getcnpE()
    {
        return this->cnpE;
    }

    bool verifcnpE(int cnp)
    {
        if(this->cnpE >= cnp)
            return true;
        else
            return false;
    }

};

Abonat_Skype_Extern :: Abonat_Skype_Extern():Abonat()
{
    this->tara = "necunoscuta";
    this->cnpE = 0;
}

Abonat_Skype_Extern :: Abonat_Skype_Extern(string nume, int ID, double pret_abonament, string nr_telefon,  string tara, int cnpE):Abonat(nume, ID, pret_abonament, nr_telefon)
{
this->tara = tara;
this->cnpE = cnpE;
}

Abonat_Skype_Extern :: Abonat_Skype_Extern(const Abonat_Skype_Extern &l):Abonat(l)
{
    this->tara = l.tara;
    this->cnpE = l.cnpE;
}

Abonat_Skype_Extern& Abonat_Skype_Extern :: operator=(const Abonat_Skype_Extern &l)
{
    if(this != &l)
    {
        Abonat ::operator=(l);
        this->tara = l.tara;
        this->cnpE = l.cnpE;
    }

    return *this;
}

Abonat_Skype_Extern :: ~Abonat_Skype_Extern()
{}

istream &operator >>(istream &in, Abonat_Skype_Extern &l)
{
    in>>(Abonat&) l;
    cout<<"Tara de provenienta a abonatului este: ";
    in>>l.tara;
    cout<<"CNP ul abonatului extern este: ";
    in>>l.cnpE;
    return in;
}

ostream &operator <<(ostream &out, const Abonat_Skype_Extern &l)
{
    out<<(Abonat&) l;
    cout<<"Tara de provenienta a abonatului este: "<<l.tara<<endl;
    cout<<"CNP ul abonatului extern este: "<<l.cnpE<<endl;
}

template < class T, int lungime> class lista
{
private:
    T *vec;
public:
    lista(T arr[])
    {
        this->vec = new T[lungime];
        for(int i=0; i<lungime; i++)
            vec[i] = arr[i];
    }
    void print()
    {
        for (int i = 0; i < lungime; i++)
            cout << vec[i]<<" ";
        cout << endl;
    }

};

class Meniu
{
private:
    static Meniu* instance;
public:
    static Meniu* getInstance()
    {
        if (instance == NULL) {
            instance = new Meniu;
        }
        return instance;
    }

    Abonat_Skype_Romania *t = new Abonat_Skype_Romania[1];
    Abonat_Skype_Extern *l = new Abonat_Skype_Extern[1];
    vector<Persoana*>lista_persoane;
    void afis()
    {
        cout<<"Apasati urmatoarele taste pt diferite comenzi: \n"
              "0 - iesire din program \n"
              "1 - adaugarea unui Abonat Skype din Romania \n"
              "2 - adaugarea unui Abonat Skype Extern \n"
              "3 - afisare \n"
              "4 - afisare prin clasa template\n";
    }
    

    void comanda1()
    {
        cin >> t[0];
        lista<Abonat_Skype_Romania, 1> ob(t);
        lista_persoane.push_back(t);
    }

    void comanda2()
    {
        cin >> l[0];
        lista<Abonat_Skype_Extern, 1> ob(l);
        lista_persoane.push_back(l);

    }

    void comanda3(list<Abonat_Skype_Romania> tt, list<Abonat_Skype_Extern> ll)
    {
        tt.push_back(t[0]);
        ll.push_back(l[0]);
        list<Abonat_Skype_Romania>::iterator it;
        for (it = tt.begin(); it != tt.end(); it++)
            cout << '\n' << *it;
        cout<<endl;

        list<Abonat_Skype_Extern>::iterator i;
        for (i = ll.begin(); i != ll.end(); i++)
            cout << '\n' << *i;
        cout<<endl;
    }

    void comanda4()
    {
        lista<Abonat_Skype_Extern, 1> ob(l);
        lista<Abonat_Skype_Romania,1>obb(t);
        ob.print();
        cout<<endl;
        obb.print();
    }




    void deleteInstanta()
    {
        if(instance != NULL)
            delete instance;
        instance = nullptr;
    }

};
Meniu* Meniu:: instance = nullptr;

int main()
{

    list<Abonat_Skype_Romania> tt;
    list<Abonat_Skype_Extern> ll;

    Meniu *m;
    m = Meniu::getInstance();

    int k = 1;
    while(k)
    {
        m->afis();
        int x;
        cin>>x;

        if(x == 0)
            k = 0;

        if(x == 1)
        {
            m->comanda1();
        }

        if(x == 2)
        {
            m->comanda2();
        }

        if(x == 3)
        {
            m->comanda3(tt,ll);
        }

        if(x == 4)
        {
            m->comanda4();
        }
    }
    m->deleteInstanta();

    return 0;
}
