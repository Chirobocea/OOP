#include <iostream>
#include <list>
#include <iterator>
#include <cstring>
#include <string>
#include <typeinfo>

using namespace std;


class CitireAfisare{
public:
    virtual istream& Citire(istream&)=0;
    virtual ostream& Afisare(ostream&)const=0;
};

class Jucarii:public CitireAfisare{
    string nume;
    int volum;
    string tip;
public:
    Jucarii(){
        nume="-";
        volum=0;
        tip="-";
    }
    Jucarii(string nume, int volum, string tip){
        this->nume=nume;
        this->volum=volum;
        this->tip=tip;
    }
    Jucarii(const Jucarii& j){
        nume=j.nume;
        volum=j.volum;
        tip=j.tip;
    }
    ~Jucarii(){}
    Jucarii& operator=(const Jucarii& j){
        if(this!=&j){
            nume=j.nume;
            volum=j.volum;
            tip=j.tip;
        }
        return *this;
    }
    virtual istream& Citire(istream& in){
        cout<<"\nNume jucarie: ";
        in>>nume;
        cout<<"Volum ambalaj: ";
        in>>volum;
        cout<<"Tipul jucariei: ";
        in>>tip;
        return in;
    }
    virtual ostream& Afisare(ostream& out)const{
        out<<"\nNume jucarie: "<<nume;
        out<<"\nVolum ambalaj: "<<volum;
        out<<"\nTipul jucarie: "<<tip;
        return out;
    }
    friend istream& operator>>(istream& in, Jucarii& j){
        return j.Citire(in);
    }
    friend ostream& operator<<(ostream& out, Jucarii& j){
        return j.Afisare(out);
    }
};

class JucariiClasice:public Jucarii{
    string material;
    string culoare;
public:
    JucariiClasice():Jucarii(){
        material="-";
        culoare="-";
    }
    JucariiClasice(string nume, int volum, string tip, string material, string culoare):Jucarii(nume, volum, tip){
        this->material=material;
        this->culoare=culoare;
    }
    JucariiClasice(const JucariiClasice& j):Jucarii(j){
        material=j.material;
        culoare=j.culoare;
    }
    ~JucariiClasice(){}
    JucariiClasice& operator=(const JucariiClasice& j){
        if(this!=&j){
            material=j.material;
            culoare=j.culoare;
        }
        return *this;
    }
    virtual istream& Citire(istream& in){
        Jucarii::Citire(in);
        cout<<"Material: ";
        in>>material;
        cout<<"Culoare: ";
        in>>culoare;
        return in;
    }
    virtual ostream& Afisare(ostream& out)const{
        Jucarii::Afisare(out);
        out<<"\nMaterial: "<<material;
        out<<"\nCuloare: "<<culoare;
        return out;
    }
    friend istream& operator>>(istream& in, JucariiClasice& j){
        return j.Citire(in);
    }
    friend ostream& operator<<(ostream& out, JucariiClasice& j){
        return j.Afisare(out);
    }
};

class JucariiEducative:public Jucarii{
    string abilitate;
public:
    JucariiEducative():Jucarii(){
        abilitate="-";
    }
    JucariiEducative(string nume, int volum, string tip, string abilitate):Jucarii(nume, volum, tip){
        this->abilitate=abilitate;
    }
    JucariiEducative(const JucariiEducative& j):Jucarii(j){
        abilitate=j.abilitate;
    }
    ~JucariiEducative(){}
    JucariiEducative& operator=(const JucariiEducative& j){
        if(this!=&j){
            abilitate=j.abilitate;
        }
        return *this;
    }
    virtual istream& Citire(istream& in){
        Jucarii::Citire(in);
        cout<<"Abilitate dezvoltata: ";
        in>>abilitate;
        return in;
    }
    virtual ostream& Afisare(ostream& out)const{
        Jucarii::Afisare(out);
        out<<"\nAbilitate dezvoltata: "<<abilitate;
        return out;
    }
    friend istream& operator>>(istream& in, JucariiEducative& j){
        return j.Citire(in);
    }
    friend ostream& operator<<(ostream& out, JucariiEducative& j){
        return j.Afisare(out);
    }
};

class JucariiElectronice:public Jucarii{
    int nrBaterii;
public:
    JucariiElectronice():Jucarii(){
        nrBaterii=0;
    }
    JucariiElectronice(string nume, int volum, string tip, int nrBaterii):Jucarii(nume, volum, tip){
        this->nrBaterii=nrBaterii;
    }
    JucariiElectronice(const JucariiElectronice& j):Jucarii(j){
        nrBaterii=j.nrBaterii;
    }
    ~JucariiElectronice(){}
    JucariiElectronice& operator=(const JucariiElectronice& j){
        if(this!=&j){
            nrBaterii=j.nrBaterii;
        }
        return *this;
    }
    virtual istream& Citire(istream& in){
        Jucarii::Citire(in);
        cout<<"Numar baterii: ";
        in>>nrBaterii;
        return in;
    }
    virtual ostream& Afisare(ostream& out)const{
        Jucarii::Afisare(out);
        out<<"\nNumar baterii: "<<nrBaterii;
        return out;
    }
    friend istream& operator>>(istream& in, JucariiElectronice& j){
        return j.Citire(in);
    }
    friend ostream& operator<<(ostream& out, JucariiElectronice& j){
        return j.Afisare(out);
    }
};

class Copii{
    const int id;
    static int countId;
    string nume, prenume, adresa;
    int varsta, nrFapteBune;
    bool cuminte;
    list<Jucarii*> listaJucarii;
public:
    Copii():id(++countId){
        nume = "-";
        prenume = "-";
        adresa = "-";
        varsta = 0;
        nrFapteBune = 0;
        cuminte = false;
    }
    Copii(string nume, string prenume, string adresa, int varsta, int nrFapteBune, bool cuminte, list<Jucarii*> listaJucarii):id(++countId){
        this->nume=nume;
        this->prenume=prenume;
        this->adresa=adresa;
        this->varsta=varsta;
        this->nrFapteBune=nrFapteBune;
        this->cuminte=cuminte;
        this->listaJucarii=listaJucarii;
    }
    Copii(const Copii& c):id(c.id){
        nume=c.nume;
        prenume=c.prenume;
        adresa=c.adresa;
        varsta=c.varsta;
        nrFapteBune=c.nrFapteBune;
        cuminte=c.cuminte;
        listaJucarii=c.listaJucarii;
    }
    ~Copii(){
        listaJucarii.clear();
    }
    Copii& operator=(const Copii& c){
        if(this!=&c){
            nume=c.nume;
            prenume=c.prenume;
            adresa=c.adresa;
            varsta=c.varsta;
            nrFapteBune=c.nrFapteBune;
            cuminte=c.cuminte;
            listaJucarii=c.listaJucarii;
        }
        return *this;
    }
    bool operator<=(const Copii& c){
        if(varsta<=c.varsta)
            return true;
        return false;
    }
    void operator+(int n){
        nrFapteBune+=n;
        Jucarii *aux;
        for(int i=0; i<n; i++){
            aux=new Jucarii;
            cin>>*aux;
            listaJucarii.push_back(aux);
        }
    }
    friend istream& operator>>(istream& in, Copii& c){
        cout<<"\nNume: ";
        in>>c.nume;
        cout<<"Prenume: ";
        in>>c.prenume;
        cout<<"Adresa: ";
        in.get();
        getline(in, c.adresa);
        cout<<"Varsta: ";
        in>>c.varsta;
        cout<<"Numar de fapte bune: ";
        in>>c.nrFapteBune;
        int comanda;
        for(int i=0; i<c.nrFapteBune; i++){
            cout<<"\nCe tip de jucarie doriti sa creati? "; 
            cout<<"\n1. Clasica";
            cout<<"\n2. Eduvativa";
            cout<<"\n3. Electronica";
            cout<<endl;
            cin>>comanda;
            Jucarii* aux;
            switch(comanda){
                case 1:{
                    aux = new JucariiClasice;
                    cin>>*aux;
                    c.listaJucarii.push_back(aux);
                    break; 
                }
                case 2:{
                    aux = new JucariiEducative;
                    cin>>*aux;
                    c.listaJucarii.push_back(aux);
                    break; 
                }
                case 3:{
                    aux = new JucariiElectronice;
                    cin>>*aux;
                    c.listaJucarii.push_back(aux);
                    break;
                }
            }
        }
        return in;
    }
    friend ostream& operator<<(ostream& out, Copii& c){
        out<<"\nID: "<<c.id;
        out<<"\nNume: "<<c.nume;
        out<<"\nPrenume: "<<c.prenume;
        out<<"\nAdresa: "<<c.adresa;
        out<<"\nVarsta: "<<c.varsta;
        out<<"\nNumar de fapte bune: "<<c.nrFapteBune;
        int k=1;
        for(auto iter=c.listaJucarii.begin(); iter!=c.listaJucarii.end(); iter++){
            out<<k<<". "<<endl; k++;
            out<<**iter;
        }
        return out;
    }

    int getId(){
        return id;
    }
    string getNume()const{
        return nume;
    }
    int getNrFapteBune()const{
        return nrFapteBune;
    }

    void raportJucarii(int& sum, int& tip1, int& tip2, int& tip3){
        for(auto iter=listaJucarii.begin(); iter!=listaJucarii.end(); iter++){
            if(typeid(**iter)==typeid(JucariiClasice))
                tip1++;
            if(typeid(**iter)==typeid(JucariiEducative))
                tip2++;
            if(typeid(**iter)==typeid(JucariiElectronice))
                tip3++;
        }
        sum+=tip1+tip2+tip3;
    }
    template<class Ttype>
    void addJucarie(Ttype j){
        listaJucarii.push_back(&j);
    }
};
int Copii::countId=0;

class MeniuSingleton{

    list<Copii> listaCopii;

    static MeniuSingleton *object;

    MeniuSingleton(){}

    void showCopii(){
        int k=1;
        for(auto iter=listaCopii.begin(); iter!=listaCopii.end(); iter++){
            cout<<k<<"."<<*iter;    k++;
        }
    }

//  COMANDA 7
void raport(){
    int sum=0, tip1=0, tip2=0, tip3=0;
    for(auto iter=listaCopii.begin(); iter!=listaCopii.end(); iter++){
        iter->raportJucarii(sum, tip1, tip2, tip3);
    }
    cout<<"\nSunt "<<sum<<" jucarii in total, dintre care "<<tip1<<" sunt clasice "<<tip2<<" sunt educative "<<tip3<<" sunt electice";
}

//  COMANDA 6
void cresteNrFapteBune(){
    int id, n;
    cout<<"\nIntroduceti ID-ul copilului: ";
    cin>>id;
    for(auto iter=listaCopii.begin(); iter!=listaCopii.end(); iter++){
        if(iter->getId()==id){
            cout<<"\nCate fapte bune doriti sa adaugati? ";
            cin>>n;
            *iter+n;
            break;
        }
    }
}

//  COMANDA 5
void sortNrFapteBune(){
    listaCopii.sort([](Copii a, Copii b){ // avem nevoie de o astfel de declarare deoarece folosim pointeri
        if(a.getNrFapteBune()<=b.getNrFapteBune())
            return true;
        return false;
    });// lambda functie
    showCopii();
}

//  COMANDA 4
void sortVarsta(){
    listaCopii.sort([](Copii a, Copii b){ // avem nevoie de o astfel de declarare deoarece folosim pointeri
        if(a<=b)
            return true;
        return false;
    });// lambda functie
    showCopii();
}

//  COMANDA 3
    void search(){
        string nume;
        cout<<"\nIntroduceti numele: ";
        cin>>nume;

        for(auto iter=listaCopii.begin(); iter!=listaCopii.end(); iter++){
            if(iter->getNume()==nume)
                cout<<*iter;
        }
    }

//  COMANDA 2
    template <class Ttype>
    void create(Ttype t, Copii &c){
        cin>>t;
        c.addJucarie(t);
    }

    void createJucarii(){
        int select, comanda;
        showCopii();
        cout<<"\nSelectati copilul la care vreti sa adaugati jucarii: ";    cin>>select;
        auto iter=listaCopii.begin();
        advance(iter, select-1);
        cout<<"\nCe tip de jucarie doriti sa creati? "; 
        cout<<"\n1. Clasica";
        cout<<"\n2. Eduvativa";
        cout<<"\n3. Electronica";
        cout<<endl;
        cin>>comanda;
        switch(comanda){
            case 1:{
                JucariiClasice type;
                create(type, *iter);
                break; 
            }
            case 2:{
                JucariiEducative type;
                create(type, *iter);
                break; 
            }
            case 3:{
                JucariiElectronice type;
                create(type, *iter);
                break;
            }
        }
        
    }

//  COMANDA 1
    void createCopil(){
        Copii aux;
        cin>>aux;
        listaCopii.push_back(aux);
    }

public:
    static MeniuSingleton *getInstance(){
        if (object==NULL)
            object=new MeniuSingleton();
        return object;
    }

    //----------------------------------------------------------------MENIU------------------------------------------------------------------

    void meniu(){
        int comanda;
        bool run=true;

        do{
            cout<<"\n   1. Cititi un copil";
            cout<<"\n   2. Adaugati jucarii";
            cout<<"\n   3. Cautati un copil dupa nume";
            cout<<"\n   4. Sortati copii dupa varsta";
            cout<<"\n   5. Sortati copii dupa nr de fapte bune";
            cout<<"\n   6. Creste numarul de fapte bune al unui copil";
            cout<<"\n   7. Afisarea schemei de vaccinare pentru un anumit tip de vaccin";
            cout<<"\n   0. STOP";
            cout<<endl;
            cin>>comanda;
            switch (comanda)
            {
                case 1:{
                    createCopil();
                    break;
                }
                case 2:{
                    createJucarii();
                    break;
                }
                case 3:{
                    search();
                    break;
                }
                case 4:{
                    sortVarsta();
                    break;
                }
                case 5:{
                    sortNrFapteBune();
                    break;
                }
                case 6:{
                    cresteNrFapteBune();
                    break;
                }
                case 7:{
                    raport();
                    break;
                }
                case 0:{
                    listaCopii.clear();
                    run=false;
                    break;
                }
            }
        }while( (comanda!=1 && comanda!=2 && comanda!=3 && comanda!=4 && comanda!=5 && comanda!=6 && comanda!=7 && comanda!=0) || run==true);
    }

};

MeniuSingleton *MeniuSingleton::object=0;

int main(){

    MeniuSingleton *myMenu = myMenu->getInstance();
    myMenu->meniu();
    
    return 0;
}