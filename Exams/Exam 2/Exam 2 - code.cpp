#include <iostream>
#include <list>
#include <map>
#include <set>
#include <iterator>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;


//  Clasa abstracta
class CitireAfisare{
public:
    virtual istream& Citire(istream&)=0;
    virtual ostream& Afisare(ostream&)const=0;
};

class Vaccin:public CitireAfisare{
    string nume;
    int pret;
    int temperatura;
    list<string> ingrediente;
public:
    Vaccin(){
        nume="-";
        pret=0;
        temperatura=0;
    }

    Vaccin(string nume, int pret, int temperatura, list<string> ingrediente){
        this->pret=pret;
        this->temperatura=temperatura;
        this->ingrediente=ingrediente;
    }

    Vaccin(const Vaccin &v){
        this->nume=v.nume;
        this->pret=v.pret;
        this->temperatura=v.temperatura;
        this->ingrediente=v.ingrediente;
    }

    ~Vaccin(){
        ingrediente.clear();
    }

    Vaccin& operator=(const Vaccin &v){
        if(this!=&v){
            ingrediente.clear();

            this->nume=v.nume;
            this->pret=v.pret;
            this->temperatura=v.temperatura;
            this->ingrediente=v.ingrediente;
        }
        return *this;
    }

    virtual istream& Citire(istream& in){
        cout<<"\nNume producator: ";
        in>>nume;
        cout<<"\nPret: ";
        in>>pret;
        cout<<"\nTemperatura: ";
        in>>temperatura;
        int n;
        cout<<"\nNumar de ingrediente: ";
        in>>n;
        string aux;
        cout<<"\nIntroduceti ingredientele:\n";
        for(int i=0; i<n; i++){
            cout<<i+1<<". ";
            in>>aux;
            ingrediente.push_back(aux);
            aux.clear();
        }
    }

    virtual ostream& Afisare(ostream& out)const{
        out<<"\nNume producator: "<<nume;
        out<<"\nPret: "<<pret;
        out<<"\nTemperatura: "<<temperatura;
        out<<"\nIngrediente:\n";
        for(auto iter=ingrediente.begin(); iter!=ingrediente.end(); iter++){
            out<<*iter<<endl;
        }
    }

    friend istream& operator>>(istream& in, Vaccin&  v){
        return v.Citire(in);
    }
    friend ostream& operator<<(ostream& out, const Vaccin& v){
        return v.Afisare(out);
    }

    virtual void schemaVaccinare(){}
    string getName(){
        return nume;
    }
    int getPret(){
        return pret;
    }
};
list<Vaccin*> lista;

class VaccinAntigripal:public Vaccin{
    bool recomandari;
    string tulpina;
public:
    VaccinAntigripal():Vaccin(){
        recomandari=false;
        tulpina="-";
    }

    VaccinAntigripal(string nume, int pret, int temperatura, list<string> ingrediente, bool recomandari, string tulpina):Vaccin(nume, pret, temperatura, ingrediente){
        this->recomandari=recomandari;
        this->tulpina=tulpina;
    }

    VaccinAntigripal(const VaccinAntigripal &v):Vaccin(v){
        this->recomandari=v.recomandari;
        this->tulpina=v.tulpina;
    }

    //~VaccinAntigripal():~Vaccin(){}

    VaccinAntigripal& operator=(const VaccinAntigripal &v){
        if(this!=&v){
            Vaccin::operator=(v);
            this->recomandari=v.recomandari;
            this->tulpina=v.tulpina;
        }
        return *this;
    }

    virtual istream& Citire(istream& in){
        Vaccin::Citire(in);
        cout<<"\nRespecta recomandarile? [yes/no]";
        string aux;
        in>>aux;
        if(aux=="yes")
            recomandari=true;
        else
            recomandari=false;
        cout<<"\nTulpina: ";
        in>>tulpina;
    }

    virtual ostream& Afisare(ostream& out)const{
        Vaccin::Afisare(out);
        if(recomandari)
            out<<"\nRespecta recomandarile";
        else
            out<<"\nNu respecta recomandarile";
        out<<"\nTulpina"<<tulpina;
    }

    friend istream& operator>>(istream& in, VaccinAntigripal&  v){
        return v.Citire(in);
    }
    friend ostream& operator<<(ostream& out, const VaccinAntigripal& v){
        return v.Afisare(out);
    }

    virtual void schemaVaccinare(){
        cout<<"\nSe administrează la adulți o doză de 0.5 ml, iar la copii și adolescenți o doză de 0.3 ml, repetându-se din 2 în 2 ani";
    }
};

class VaccinAntihepatic:public Vaccin{
    string tip;
    string administrare;
public:
    VaccinAntihepatic():Vaccin(){
        tip="-";
        administrare="-";
    }

    VaccinAntihepatic(string nume, int pret, int temperatura, list<string> ingrediente, string tip, string administrare):Vaccin(nume, pret, temperatura, ingrediente){
        this->tip=tip;
        this->administrare=administrare;
    }

    VaccinAntihepatic(const VaccinAntihepatic &v):Vaccin(v){
        this->tip=v.tip;
        this->administrare=v.administrare;
    }

    //~VaccinHepatita():~Vaccin(){}

    VaccinAntihepatic& operator=(const VaccinAntihepatic &v){
        if(this!=&v){
            Vaccin::operator=(v);
            this->tip=v.tip;
            this->administrare=v.administrare;
        }
        return *this;
    }

    virtual istream& Citire(istream& in){
        Vaccin::Citire(in);
        cout<<"\nTipul: ";
        in>>tip;
        cout<<"\nMod de administrare: ";
        in>>administrare;
    }

    virtual ostream& Afisare(ostream& out)const{
        Vaccin::Afisare(out);
        out<<"\nTipul: "<<tip;
        out<<"\nMod de administrare: "<<administrare;
    }

    friend istream& operator>>(istream& in, VaccinAntihepatic&  v){
        return v.Citire(in);
    }
    friend ostream& operator<<(ostream& out, const VaccinAntihepatic& v){
        return v.Afisare(out);
    }

    virtual void schemaVaccinare(){
        cout<<"\nAntihepatită A și B, la copii cu vârstă mai mică de 1 an se adminstrează 2 injectări la un interval de o lună, a treia injectare după 6 luni de la prima administrare, la adulți conform schemei de imunizare recomandată de medic"<<endl<<"Antihepatită C doar la recomandarea medicului";
    }
};

class VaccinAntiSarsCov2:public Vaccin{
    list<string> reactiiAdverse;
    int eficienta;
    list<string> medicamenteContraindicate;
public:
    VaccinAntiSarsCov2():Vaccin(){
        eficienta=0;
    }

    VaccinAntiSarsCov2(string nume, int pret, int temperatura, list<string> ingrediente, list<string> reactiiAdverse, int eficienta, list<string> medicamenteContraindicate):Vaccin(nume, pret, temperatura, ingrediente){
        this->reactiiAdverse=reactiiAdverse;
        this->eficienta=eficienta;
        this->medicamenteContraindicate=medicamenteContraindicate;
    }

    VaccinAntiSarsCov2(const VaccinAntiSarsCov2 &v):Vaccin(v){
        this->reactiiAdverse=v.reactiiAdverse;
        this->eficienta=v.eficienta;
        this->medicamenteContraindicate=v.medicamenteContraindicate;
    }

    //~VaccinAntigripal():~Vaccin(){}

    VaccinAntiSarsCov2& operator=(const VaccinAntiSarsCov2 &v){
        if(this!=&v){
            Vaccin::operator=(v);

            reactiiAdverse.clear();
            medicamenteContraindicate.clear();

            this->reactiiAdverse=v.reactiiAdverse;
            this->eficienta=v.eficienta;
            this->medicamenteContraindicate=v.medicamenteContraindicate;
        }
        return *this;
    }

    virtual istream& Citire(istream& in){
        Vaccin::Citire(in);
        cout<<"\nNumar de reactii adverse: ";
        int n; in>>n;
        string aux;
        for(int i=0; i<n; i++){
            cout<<i+1<<". ";
            in>>aux;
            reactiiAdverse.push_back(aux);
            aux.clear();
        }
        cout<<"\nEficienta: ";
        in>>eficienta;
        cout<<"\nNumar medicamente contraindicate pe o perioada de 6 luni: ";
        in>>n;
        for(int i=0; i<n; i++){
            cout<<i+1<<". ";
            in>>aux;
            medicamenteContraindicate.push_back(aux);
            aux.clear();
        }
    }

    virtual ostream& Afisare(ostream& out)const{
        Vaccin::Afisare(out);
        out<<"\nReactii adverse: ";
        for(auto iter=reactiiAdverse.begin(); iter!=reactiiAdverse.end(); iter++)
            out<<*iter<<endl;
        out<<"\nEficienta: "<<eficienta;
        out<<"\nMedicamente contraindicate pe o perioada de 6 luni: ";
        for(auto iter=medicamenteContraindicate.begin(); iter!=medicamenteContraindicate.end(); iter++)
            out<<*iter<<endl;
    }

    friend istream& operator>>(istream& in, VaccinAntiSarsCov2&  v){
        return v.Citire(in);
    }
    friend ostream& operator<<(ostream& out, const VaccinAntiSarsCov2& v){
        return v.Afisare(out);
    }

    virtual void schemaVaccinare(){
        cout<<"\n Sars-Cov2 se administrează persoanelor cu vârstă de peste 16 ani, 2 doze la o perioadă de 21 zile";
    }
};

class Comanda{
    const int id;
    static int countId;
    string data;
    bool anotimp;
    string nume;
    map <int, int> listaVac;
    /*  key         
        1=antigipal     =pret 10
        2=antihepatic   =pret 11
        3=antisarscov2  =pret 12

        valoare=cantitate de vaccinuri
    */
public:
    Comanda():id(++countId){
        data="-";
        nume="-";
        anotimp=false;
    }

    Comanda(string data, string nume, map<int,int> listaVac):id(++countId){
        this->data=data;
        this->nume=nume;
        this->listaVac=listaVac;
        anotimp=false;
    }

    Comanda(const Comanda& c):id(c.id){
        this->data=c.data;
        this->nume=c.nume;
        this->listaVac=c.listaVac;
        this->anotimp=c.anotimp;
    }

    ~Comanda(){
        listaVac.clear();
    }

    Comanda& operator=(const Comanda& c){
        if(this!=&c){
            listaVac.clear();

            this->data=c.data;
            this->nume=c.nume;
            this->listaVac=c.listaVac;
            this->anotimp=c.anotimp;
        }
        return *this;
    }

    friend istream& operator>>(istream& in, Comanda &c){
        string zi, luna, an;
        int k, nr, doze;
        cout<<"\nNume: ";
        in>>c.nume;
        cout<<"\nData";
        cout<<"\nZi: ";     in>>zi;
        cout<<"\nLuna: ";   in>>luna;
        cout<<"\nAn: ";     in>>an;
        c.data=zi+"."+luna+"."+an;
        int aux;
        stringstream s(luna);
        s>>aux;
        if(aux>=6 && aux<=8)
            c.anotimp=true;
        
        do{
            k=1;
            cout<<"\nSelectati vaccinul pe cre doriti sa il comandati:\n";
            for(auto iter=lista.begin(); iter!=lista.end(); iter++){
                cout<<k<<". "<<**iter<<endl;
                k++;
            }
            cout<<"0. STOP"<<endl;
            cin>>nr;
            if(nr==0)
                break;
            cout<<"\nCate doze doriti?";
            cin>>doze;
            c.listaVac.insert({nr, doze});
        }while(true);

        return in;
    }

    friend ostream& operator<<(ostream& out, const Comanda& c){
        out<<"\nNume: "<<c.nume;
        out<<"\nData: "<<c.data;
        out<<"\nID comanda: "<<c.id;

        return out;
    }

    int valoareComanda(){
        int sum=0;
        int nr1, nr2, pret;
        auto iterVac=lista.begin();
        for(auto iter=listaVac.begin(); iter!=listaVac.end(); iter++){
            nr1=iter->first;
            advance(iterVac, nr1-1);
            nr2=iter->second;
            pret=(*iterVac)->getPret();
            cout<<"ceva";
            sum=(pret*nr2)+sum;
            cout<<"ceva2";
        }
        
        return sum;
    }

    string getData(){
        return data;
    }
};
list<Comanda*> comenzi;
int Comanda::countId=0;


class MeniuSingleton{

    static MeniuSingleton *object;
    //  Constructor
    MeniuSingleton(){}
    
    //  COMANDA     1
    template <class Ttype>
    void create(Ttype t){
        Vaccin* aux;
        aux=new Ttype();
        cin>>*aux;
        lista.push_back(aux);
    }

    void createVaccin(){
        int comanda;
        cout<<"\nCe tip de vaccin doriti sa creati? ;";
        cout<<"\n1. Antigripal";
        cout<<"\n2. Antihepatic";
        cout<<"\n3. Antisars-cov2";
        do{
            cin>>comanda;   cout<<endl;
            switch (comanda)
            {
                case 1:{
                    VaccinAntigripal type;
                    create(type);
                    break;
                }
                case 2:{
                    VaccinAntihepatic type;
                    create(type);
                    break;
                }
                case 3:{
                    VaccinAntiSarsCov2 type;
                    create(type);
                    break;
                }
            }
        }while(comanda!=1 && comanda!=2 && comanda!=3);
    }
    //  ------------1

    //  COMANDA     2   
    void afisareVaccin(){
        for(auto iter=lista.begin(); iter!=lista.end(); iter++){
            cout<<**iter;
        }
    }
    //  ------------2

    //   COMANDA    3
    void producatori(){
        cout<<"Numele producatorilor pentru toate vaccinurile sunt: \n";
        set<string> nume;
        for(auto iter=lista.begin(); iter!=lista.end(); iter++){
            nume.insert((*iter)->getName());
        }
        for(auto iter=nume.begin(); iter!=nume.end(); iter++){
            cout<<*iter<<endl;
        }
        nume.clear();
    }
    //  ------------3

    //  COMANDA     4
    void addComanda(){
        Comanda* aux;
        aux=new Comanda;
        cin>>*aux;
        // De adaugat exceptii pentru comenzi cu pret prea mic
        comenzi.push_back(aux);
    }
    //  ------------4

    //  COMANDA     5
    void afisareComenzi(){
        for(auto iter=comenzi.begin(); iter!=comenzi.end(); iter++)
            cout<<**iter<<endl;
    }
    //  ------------5

    //  COMANDA     6
    string citireData(){
        string data;
        string zi, luna, an;
        cout<<"\nIntroduceti data ";
        cout<<"\nZi: ";     cin>>zi;
        cout<<"\nLuna: ";   cin>>luna;
        cout<<"\nAn: ";     cin>>an;
        data=zi+"."+luna+"."+an;
        return data;
    }

    void valoareComanda(){
        string data=citireData();
        int sum=0;  
        for(auto iter=comenzi.begin(); iter!=comenzi.end(); iter++){
            if(data==(*iter)->getData()){
                sum+=(*iter)->valoareComanda();
            }
        }
        cout<<"\nValoarea comenzilor din data de "<<data<<" este de: "<<sum<<endl;
    }
    //  ------------6
    
    //  COMANDA     7
    void afisareSchemaVaccinare(){
        cout<<"\nSelectati un tip de vaccin";
        cout<<"\n1. Antigripal\n2. Antivocid\n3. Antihepatic";
        int comanda;
        do{
            cin>>comanda;
            switch (comanda)
            {
                case 1:{
                    VaccinAntigripal aux;
                    aux.schemaVaccinare();
                    break;
                } 
                case 2:{
                    VaccinAntiSarsCov2 aux;
                    aux.schemaVaccinare();
                    break;
                }
                case 3:{
                    VaccinAntihepatic aux;
                    aux.schemaVaccinare();
                    break;
                }
            }
            
        }while(comanda!=1 && comanda!=2 && comanda!=3);

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
            cout<<"\n   1. Adaugarea unui vaccin nou";
            cout<<"\n   2. Afisarea tuturor vaccinurilor pe care le detine";
            cout<<"\n   3. Numele producatorilor pentru toate vaccinurile";
            cout<<"\n   4. Adaugarea unei comenzi";
            cout<<"\n   5. Afisarea tuturor comenzilor ";
            cout<<"\n   6. Valorea comenzilor dintr-o anumita zi";
            cout<<"\n   7. Afisarea schemei de vaccinare pentru un anumit tip de vaccin";
            cout<<"\n   8. Exportul comenzilor intr-un fisier .txt";
            cout<<"\n   0. STOP";
            cout<<endl;
            cin>>comanda;
            switch (comanda)
            {
                case 1:{
                    createVaccin();
                    break;
                }
                case 2:{
                    afisareVaccin();
                    break;
                }
                case 3:{
                    producatori();
                    break;
                }
                case 4:{
                    addComanda();
                    break;
                }
                case 5:{
                    afisareComenzi();
                    break;
                }
                case 6:{
                    valoareComanda();
                    break;
                }
                case 7:{
                    afisareSchemaVaccinare();
                    break;
                }
                case 0:{
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