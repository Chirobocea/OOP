/* Chirobocea Mihail-Bogdan 212

Visual Studio Code 1.63.2 with GCC compiler 11.2.0

Szmeteanca Eduard */ 

#include <iostream>
#include <memory>
#include <list>
#include <iterator>
#include <typeinfo>

using namespace std;

// Structura clasei de citire si afisare a fost luata din laborator, deoarece este general valabila
class CitireAfisare{
public:
    virtual istream& Citire(istream&)=0;
    virtual ostream& Afisare(ostream&)const=0;
};

class PachetClasic:public CitireAfisare{
    int nrMese;
    bool singur;
    list<string> alergeni;
public:
    PachetClasic();
    virtual ~PachetClasic(){};

    virtual istream& Citire(istream&);
    virtual ostream& Afisare(ostream&)const;

    friend istream& operator>>(istream& in, PachetClasic& p);
    friend ostream& operator>>(ostream& out, const PachetClasic& p);

    bool getSingur(){
        if(singur)
            return true;
        return false;
    }
};

PachetClasic::PachetClasic(){
    nrMese=0;
    singur=false;
}

istream& PachetClasic::Citire(istream& in){
    cout<<"\nNumar de mese: ";
    in>>nrMese;
    cout<<"\nDoriti sa stea singur: [y/n] ";
    string aux;
    in>>aux;
    if(aux=="y")
        singur=true;
    else
        singur=false;
    cout<<"\nCati alergeni doriti sa introduceti? ";
    int n;
    in>>n;
    for(int i=0; i<n; i++){
        in>>aux;
        alergeni.push_back(aux);
    }
    return in;
}

ostream& PachetClasic::Afisare(ostream& out)const{
    out<<"\nNumar de mese: "<<nrMese;
    out<<"\nAnimalul ";
    if(singur)
        out<<"va sta singur";
    else
        out<<"nu va sta singur";
    out<<"\nLista de alergeni este: ";
    for(auto &iter:alergeni)
        out<<endl<<iter;
    return out;
}

istream& operator>>(istream& in, PachetClasic& p){
    return p.Citire(in);
}

ostream& operator<<(ostream& out, const PachetClasic& p){
    return p.Afisare(out);
}

class PachetSportiv:virtual public PachetClasic{
protected:
    int nrPlimbari;
public:
    PachetSportiv():PachetClasic(){
        nrPlimbari=0;
    }
    ~PachetSportiv(){}

    virtual istream& Citire(istream&);
    virtual ostream& Afisare(ostream&)const;

    friend istream& operator>>(istream& in, PachetSportiv& p);
    friend ostream& operator>>(ostream& out, const PachetSportiv& p);

    int getNrPlimbari(){
        return nrPlimbari;
    }
};

istream& PachetSportiv::Citire(istream& in){
    PachetClasic::Citire(in);
    cout<<"\nNumar plimbari: ";
    in>>nrPlimbari;
    return in;
}

ostream& PachetSportiv::Afisare(ostream& out)const{
    PachetClasic::Afisare(out);
    out<<"\nNumar de plimbari: "<<nrPlimbari;
    return out;
}

istream& operator>>(istream& in, PachetSportiv& p){
    return p.Citire(in);
}

ostream& operator<<(ostream& out, const PachetSportiv& p){
    return p.Afisare(out);
}

class PachetConfort:virtual public PachetClasic{
protected:
    list<string> activitati;
public:
    PachetConfort():PachetClasic(){}
    ~PachetConfort(){}

    virtual istream& Citire(istream&);
    virtual ostream& Afisare(ostream&)const;

    friend istream& operator>>(istream& in, PachetConfort& s);
    friend ostream& operator>>(ostream& out, const PachetConfort& s);
};

istream& PachetConfort::Citire(istream& in){
    PachetClasic::Citire(in);
    cout<<"\nCate activitati doriti sa adaugati? ";
    int n;
    do{
        in>>n;
    }while(n<=2 && n>0);
    string aux;
    for(int i=0; i<n; i++){
        activitati.push_back(aux);
    }
    return in;
}

ostream& PachetConfort::Afisare(ostream& out)const{
    PachetClasic::Afisare(out);
    out<<"\nActivitatile alese sunt: ";
    for(auto &iter:activitati)
        out<<endl<<iter;
    return out;
}

istream& operator>>(istream& in, PachetConfort& p){
    return p.Citire(in);
}

ostream& operator<<(ostream& out, const PachetConfort& p){
    return p.Afisare(out);
}


class PachetVip:public PachetSportiv, public PachetConfort{
    string ora;
    int durata;
public:
    PachetVip():PachetSportiv(){
        ora="-";
        durata=0;
    }
    ~PachetVip(){}

    virtual istream& Citire(istream&);
    virtual ostream& Afisare(ostream&)const;

    friend istream& operator>>(istream& in, PachetVip& p);
    friend ostream& operator>>(ostream& out, const PachetVip& p);
};

istream& PachetVip::Citire(istream& in){
    PachetSportiv::Citire(in);
    cout<<"\nOra: ";
    in>>ora;
    cout<<"\nDurata plimbarii: ";
    in>>durata;
    cout<<"\nCate activitati doriti sa adaugati? ";
    int n;    
    in>>n;
    string aux;
    for(int i=0; i<n; i++){
        activitati.push_back(aux);
    }
    return in;
}

ostream& PachetVip::Afisare(ostream& out)const{
    PachetSportiv::Afisare(out);
    out<<"\nOra: "<<ora;
    out<<"\nDurata plimbarii: "<<durata;
    out<<"\nNumar de plimbari: "<<nrPlimbari;
    return out;
}

istream& operator>>(istream& in, PachetVip& p){
    return p.Citire(in);
}

ostream& operator<<(ostream& out, const PachetVip& p){
    return p.Afisare(out);
}


//  CLASA CLIENT

class Client{
    string nume;
    string nrTel;
    string adresa;
    string cnp;
public:
    Client();
    Client(string nume,string nrTel, string adresa, string cnp);
    Client(const Client& c);
    ~Client(){}

    Client &operator=(const Client& c);

    friend istream &operator>>(istream &in, Client& c);
    friend ostream &operator<<(ostream &out, Client& c);
};

Client::Client(){
    nume="-";
    nrTel="-";
    adresa="-";
    cnp="-";
}

Client::Client(string nume, string nrTel, string adresa, string cnp){
    this->nume=nume;
    this->nrTel=nrTel;
    this->adresa=adresa;
    this->cnp=cnp;
}

Client::Client(const Client& c){
    this->nume=c.nume;
    this->nrTel=c.nrTel;
    this->adresa=c.adresa;
    this->cnp=c.cnp;
}

Client &Client::operator=(const Client& c){
    if(this!=&c){
        this->nume=c.nume;
        this->nrTel=c.nrTel;
        this->adresa=c.adresa;
        this->cnp=c.cnp;
    }
    return *this;
}

istream &operator>>(istream &in, Client& c){
    cout<<"\nNume: ";
    in>>c.nume;
    cout<<"\nNumara telefon: ";
    in>>c.nrTel;
    cout<<"\nAdresa: ";
    in>>c.adresa;
    cout<<"\nCnp: ";
    in>>c.cnp;
    return in;
}

ostream &operator<<(ostream &out, Client& c){
    out<<"\nNume: "<<c.nume;
    out<<"\nNumar telefon: "<<c.nrTel;
    out<<"\nAdresa: "<<c.adresa;
    out<<"\nCnp: "<<c.cnp;
    return out;
}

//  CLASA ANIMAL

class Animal{
    string nume;
    int varsta;
    string rasa;
    const int id;
    static int countId;
public:
    Animal();
    Animal(string nume, int varsta, string rasa);
    Animal(const Animal& a);
    ~Animal(){}

    Animal &operator=(const Animal& a);

    friend istream &operator>>(istream &in, Animal& a);
    friend ostream &operator<<(ostream &out, Animal& a);

    const int getId()const{
        return id;
    }
};

Animal::Animal():id(++countId){
    nume="-";
    varsta=0;
    rasa="-";
}

Animal::Animal(string nume, int varsta, string rasa):id(++countId){
    this->nume=nume;
    this->varsta=varsta;
    this->rasa=rasa;
}

Animal::Animal(const Animal& a):id(a.id){
    this->nume=a.nume;
    this->varsta=a.varsta;
    this->rasa=a.rasa;
}

Animal &Animal::operator=(const Animal& a){
    if(this!=&a){
        this->nume=a.nume;
        this->varsta=a.varsta;
        this->rasa=a.rasa;
    }
    return *this;
}

istream &operator>>(istream &in, Animal& a){
    cout<<"\nNume: ";
    in>>a.nume;
    cout<<"\nVarsta: ";
    in>>a.varsta;
    cout<<"\nRasa: ";
    in>>a.rasa;
    return in;
}

ostream &operator<<(ostream &out, Animal& a){
    out<<"\nNume: "<<a.nume;
    out<<"\nVarsta "<<a.varsta;
    out<<"\nRasa: "<<a.rasa;
    out<<"\nCod: "<<a.id;
    return out;
}

int Animal::countId=0;


//  CLASA FORMULAR
class Formular{
    string dataStart;
    string dataEnd;
    int numarZile; //nu am avut timp sa implementez o functie care sa calculeze acest lucru pe baza celorlalte date
    PachetClasic* pachetAles;
    Client client;
    Animal animal;
    int pret;
    int id;
public:
    Formular(){
        dataStart="-";
        dataEnd="-";
        pret=0;
    }
    ~Formular(){
        delete pachetAles;
    }

    bool operator<(const Formular& f){
        if(this->pret<f.pret)
            return true;
        return false;
    }    

    void calculPret(){
        pret=100*numarZile;
        if(pachetAles->getSingur())
            pret=pret+30*numarZile;
        /*
        if(typeid(*pachetAles)==typeid(PachetSportiv)){
            pret=pret+30*(pachetAles->getNrPlimbari());
        }*/ //nu functioneaza
    }

    friend istream &operator>>(istream &in, Formular& f);
    friend ostream &operator<<(ostream &out, Formular& f);

    
};

istream &operator>>(istream &in, Formular& f){
    cout<<"\nIntroduceti data de inceput: ";
    in>>f.dataStart;
    cout<<"\nItroducetid data de final: ";
    in>>f.dataEnd;
    cout<<"\nCate zile stati? ";
    in>>f.numarZile;
    cout<<"\nCe pachet doriti? "; 
    cout<<"\n1. Clasica";
    cout<<"\n2. Sport";
    cout<<"\n3. Confort";
    cout<<"\n4. Vip";
    cout<<endl;
    int comanda;
    in>>comanda;
    switch(comanda){
        case 1:{
            f.pachetAles=new PachetClasic;
            in>>*(f.pachetAles);
            break; 
        }
        case 2:{
            f.pachetAles=new PachetSportiv;
            in>>*(f.pachetAles);
            break; 
        }
        case 3:{
            f.pachetAles=new PachetConfort;
            in>>*(f.pachetAles);
                break;
            }
        case 4:{
            f.pachetAles=new PachetVip;
            in>>*(f.pachetAles);
        }
    }
    in>>f.client;
    in>>f.animal;
    f.id=f.animal.getId();
    return in;
}

ostream &operator<<(ostream &out, Formular& f){
    out<<"\nData de inceput: "<<f.dataStart;
    out<<"\nData de final: "<<f.dataEnd;
    out<<*(f.pachetAles);
    out<<f.client;
    out<<f.animal;
    out<<"\nCod unic: "<<f.id;
    return out;
}

// Structura clasei singleton este luata din laboartor, deoarece este general valabila
class MeniuSingleton{

    static MeniuSingleton *object;
    list<Formular> listaFormulare;

    MeniuSingleton()=default;
    MeniuSingleton(const MeniuSingleton& o)=delete;
    MeniuSingleton& operator=(const MeniuSingleton& o)=delete;

    void adaugare();
    void afisare();
    void sortare();
public:
    static MeniuSingleton *getInstance();
    void meniu();
    void deleteInstance();

};
MeniuSingleton* MeniuSingleton::object=nullptr;

void MeniuSingleton::sortare(){
    listaFormulare.sort();
}

void MeniuSingleton::afisare(){
    for(auto &iter:listaFormulare)
        cout<<endl<<iter;
}

void MeniuSingleton::adaugare(){
    Formular aux;
    cin>>aux;
    aux.calculPret();
    listaFormulare.push_back(aux);
}

// Structura functiei meniu este luata din proiectul 3, deoarece do-while-ul si switch-ul sunt general valabile pentru un meniu
void MeniuSingleton::meniu(){
        int comanda;
        bool run=true;

        do{
            cout<<"\n   1. Adaugarea unuiformular nou";
            cout<<"\n   2. Afisarea tuturor formularelor cu detalii  despre data de început a cazarii, codul si pretul";
            cout<<"\n   3. Selectarea unui formular prin care se poate opta intre a afisa detalii despre oferta, animal sau client";
            cout<<"\n   4. Afisarea tuturor formularelor ordonate crescator in functie de pret dintr-o anumita zi";
            cout<<"\n   0. STOP";
            cout<<endl;
            cin>>comanda;
            switch (comanda)
            {
                case 1:{
                    adaugare();
                    break;
                }
                case 2:{
                    afisare();
                    break;
                }
                case 3:{
                    
                    break;
                }
                case 4:{
                    sortare();
                    break;
                }
                case 0:{
                    listaFormulare.clear();
                    run=false;
                    break;
                }
            }
        }while( (comanda!=1 && comanda!=2 && comanda!=3 && comanda!=4 && comanda!=0) || run==true);
}

MeniuSingleton* MeniuSingleton::getInstance(){
    if(object==nullptr){
        object=new MeniuSingleton();
    }
    return object;
}

void MeniuSingleton::deleteInstance(){
    if(object!=nullptr)
        delete object;
}

int main(){

    MeniuSingleton *myMenu = myMenu->getInstance();
    myMenu->meniu();
    myMenu->deleteInstance();

    return 0;
}
