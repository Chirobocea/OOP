/*
Nume: Chirobocea Mihail Bogdan
Grupa: 212
Tutore laborant: Tiberiu Maxim
Compilator: Visual Studio Code
*/

#include <iostream>
#include <list>

using namespace std;

class CitireAfisare{
public:
    virtual istream& Citire(istream&)=0;
    virtual ostream& Afisare(ostream&)const=0;
};

class Date:public CitireAfisare{
    int day, month, year;
public:
    Date(){
        day=0;
        month=0;
        year=0;
    }

    Date(int day, int month, int year){
        this->day=day;
        this->month=month;
        this->year=year;
    }

    Date(const Date &d){
        this->day=d.day;
        this->month=d.month;
        this->year=d.year;
    }

    ~Date(){}

    Date &operator=(const Date &d){ 
        if(this!=&d){
            this->day=d.day;
            this->month=d.month;
            this->year=d.year;
        }
        return *this;
    }

    int operator-(Date d){
        //nu am avut timp sa implementez diferenta dintre date;
        return d.day;
    }

    //  Citire
    istream& Citire(istream& in){
        cout<<"\nZi: ";
        in>>day;
        cout<<"\nLuna: ";
        in>>month;
        cout<<"\nAn: ";
        in>>year;
        return in;
    }

    //  Afisare
    ostream& Afisare(ostream& out)const{
        cout<<day<<"."<<month<<"."<<year<<endl;
        return out;
    }

    //  Supraincarcare >>
    friend istream& operator>>(istream& in, Date& d){
        return d.Citire(in);
    }

    //  Supraincarcare <<
    friend ostream& operator<<(ostream& out, const Date& d){
        return d.Afisare(out);
    }
};

class Pers:public CitireAfisare{
    string name;
    int age;
    string nationality;
    Date dateStart, dateEnd;
    int pret;
    const int id;
    static int countId;

public:
    Pers():id(++countId){
        name="-";
        age=0;
        nationality="-";
        pret=0;
    }

    Pers(string name, int age, string nationality, Date dateStart, Date dateEnd, int pret):id(++countId){
        this->name=name;
        this->age=age;
        this->nationality=nationality;
        this->dateStart=dateStart;
        this->dateEnd=dateEnd;
        this->pret=pret;
    }

    Pers(const Pers &p):id(p.id){
        this->name=p.name;
        this->age=p.age;
        this->nationality=p.nationality;
        this->dateStart=p.dateStart;
        this->dateEnd=p.dateEnd;
        this->pret=p.pret;
    }

    ~Pers(){}

    Pers &operator=(const Pers &p){ 
        if(this!=&p){
            this->name=p.name;
            this->age=p.age;
            this->nationality=p.nationality;
            this->dateStart=p.dateStart;
            this->dateEnd=p.dateEnd;
            this->pret=p.pret;
        }
        return *this;
    }

    //  Citire
    istream& Citire(istream& in){
        cout<<"\nNume: ";
        in.get();
        getline(in, name);
        cout<<"\nVarsta";
        in>>age;
        Date aux1, aux2;
        cout<<"\nData de inceput: ";
        in>>aux1;
        cout<<"\nDate de final: ";
        in>>aux2;
        dateStart=aux1;
        dateEnd=aux2;
        return in;
    }

    //  Afisare
    ostream& Afisare(ostream& out)const{
        out<<"\nNume: ";
        out<<name;
        out<<"\nVarsta";
        out<<age;
        out<<"\nData de inceput: ";
        out<<dateStart;
        out<<"\nDate de final: ";
        out<<dateEnd;    
        return out;
    }

    //  Supraincarcare >>
    friend istream& operator>>(istream& in, Pers& p){
        return p.Citire(in);
    }

    //  Supraincarcare <<
    friend ostream& operator<<(ostream& out, const Pers& p){
        return p.Afisare(out);
    }
};
//  Static
int Pers::countId=0;

class Event:public CitireAfisare{
    string name;
    Date date;
    int hour;
    int nrMaxParticipants;
    string type;
    list<Pers> listPers;
public:
    Event(){
        name="-";
        hour=0;
        nrMaxParticipants=0;
        type="-";
    }

    Event(string name, Date date, int hour, int nrMaxParticipants, string type, list<Pers> listPers){
        this->name=name;
        this->date=date;
        this->hour=hour;
        this->nrMaxParticipants=nrMaxParticipants;
        this->type=type;
        this->listPers=listPers;
    }

    Event(const Event &e){
        this->name=e.name;
        this->date=e.date;
        this->hour=e.hour;
        this->nrMaxParticipants=e.nrMaxParticipants;
        this->type=e.type;
        this->listPers=e.listPers;
    }

    ~Event(){
        listPers.clear();
    }

    Event &operator=(const Event &e){ 
        if(this!=&e){
            this->name=e.name;
            this->date=e.date;
            this->hour=e.hour;
            this->nrMaxParticipants=e.nrMaxParticipants;
            this->type=e.type;
            this->listPers=e.listPers;
        }
        return *this;
    }

    void operator+(Pers aux){
        listPers.push_back(aux);
    }

    //  Citire
    istream& Citire(istream& in){
        cout<<"\nNume: ";
        in.get();
        getline(in, name);
        Date aux1;
        cout<<"\nData de inceput: ";
        in>>aux1;
        date=aux1;
        cout<<"\nOra: ";
        in>>hour;
        cout<<"\nNumar maxim de participanti: ";
        in>>nrMaxParticipants;
        cout<<"\nTipul evenimentului: ";
        in>>type;
        return in;
    }

    //  Afisare
    ostream& Afisare(ostream& out)const{
        cout<<"\nNume: ";
        out<<name;
        out<<"\nData de inceput: ";
        out<<date;
        out<<"\nOra: ";
        out<<hour;
        out<<"\nNumar maxim de participanti: ";
        out<<nrMaxParticipants;
        out<<"\nTipul evenimentului: ";
        out<<type;
        for(auto iter=listPers.begin(); iter!=listPers.end(); iter++)
            out<<*iter;
        return out;
    }

    //  Supraincarcare >>
    friend istream& operator>>(istream& in, Event& e){
        return e.Citire(in);
    }

    //  Supraincarcare <<
    friend ostream& operator<<(ostream& out, const Event& e){
        return e.Afisare(out);
    }
};

class Pavilion:public CitireAfisare{
    string country;
    int zona;
    const int id;
    static int countId;
    list<Event> events;
public:

    Pavilion():id(++countId){
        country="-";
        zona=0;
    }

    Pavilion(string country, int zona, list<Event> events):id(++countId){
        this->country=country;
        this->zona=zona;
        this->events=events;
    }

    Pavilion(const Pavilion &p):id(p.id){
        this->country=p.country;
        this->zona=p.zona;
        this->events=p.events;
    }

    ~Pavilion(){
        events.clear();
    }

    Pavilion &operator=(const Pavilion &p){ 
        if(this!=&p){
            this->country=p.country;
            this->zona=p.zona;
            this->events=p.events;
        }
        return *this;
    }

    void addEvent(int k, Pers aux){
        auto iter=events.begin();
        advance(iter, k);
        (*iter)+aux;
    }

    int selectEvent(){
        int k=1;
        int select;
        for(auto iter=events.begin(); iter!=events.end(); iter++){
            cout<<k<<"."<<*iter<<endl;
            k++;
        }
        cout<<"\nSelectati un eveniment: ";
        cin>>select;
        return select;
    }

    void operator+(Event aux){
        events.push_back(aux);
    }

    //  Citire
    istream& Citire(istream& in){
        cout<<"\nTara gazda: ";
        in.get();
        getline(in, country);
        cout<<"\nZona: ";
        in>>zona;
        Event aux;
        in>>aux;
        events.push_back(aux);
        return in;
    }

    //  Afisare
    ostream& Afisare(ostream& out)const{
        cout<<"\nTara gazda: ";
        out<<country;
        cout<<"\nZona: ";
        out<<zona;
        for(auto iter=events.begin(); iter!=events.end(); iter++)
            out<<*iter;
        return out;
    }

    //  Supraincarcare >>
    friend istream& operator>>(istream& in, Pavilion& p){
        return p.Citire(in);
    }

    //  Supraincarcare <<
    friend ostream& operator<<(ostream& out, const Pavilion& p){
        return p.Afisare(out);
    }

};

list<Pavilion> listaPavilioane;
//  Static
int Pavilion::countId=0;


class MeniuSingleton{

    static MeniuSingleton *object;
    //  Constructor
    MeniuSingleton(){}

    void showPavilioane(){
        for(auto iter=listaPavilioane.begin(); iter!=listaPavilioane.end(); iter++)
            cout<<*iter;
    }

    void createPavilion(){
        Pavilion aux;
        cin>>aux;
        listaPavilioane.push_back(aux);
    }

    void addEvent(){
        int k;
        cout<<"\nSelectati un pavilion: ";
        showPavilioane();
        cin>>k; k--;
        cout<<"\nSe adauga evenimentul: ";
        Event aux;
        auto iter=listaPavilioane.begin();
        advance(iter, k);
        (*iter)+aux;
        cin>>aux;

    }

    void buyTicket(){
        Pers aux;
        int k1, k2;
        cout<<"\nSelectati un pavilion: ";
        showPavilioane();
        cin>>k1; k1--;
        auto iterPav=listaPavilioane.begin();
        advance(iterPav, k1);
        k2=iterPav->selectEvent();  k2--;
        cin>>aux;
        iterPav->addEvent(k2, aux);
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
            cout<<"\n   1. Creati pavilion";
            cout<<"\n   2. Adaugati eveniment";
            cout<<"\n   3. Cumpara bilet";
            cout<<"\n   0. STOP";
            cout<<endl;
            cin>>comanda;
            switch (comanda)
            {
                case 1:{
                    createPavilion();
                    break;
                }
                case 2:{
                    addEvent();
                    break;
                }
                case 3:{
                    buyTicket();
                }
                case 0:{
                    run=false;
                    break;
                }
            }
        }while( (comanda!=1 && comanda!=2 && comanda!=3 && comanda!=0) || run==true);
    }

};

// Static
MeniuSingleton *MeniuSingleton::object=0;

int main(){

    MeniuSingleton *myMenu = myMenu->getInstance();
    myMenu->meniu();

    listaPavilioane.clear();

    return 0;
}