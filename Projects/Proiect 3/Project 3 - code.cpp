#include <iostream>
#include <list>
#include <vector>
#include <set>
#include <map>
#include <iterator>

using namespace std;

//  Smart pointer
template <class T>
class SmartPtr {
    T* ptr; 
public:
    SmartPtr(){ ptr = NULL; }
    SmartPtr(T* p){ ptr = p; }
    ~SmartPtr(){ delete (ptr); }
 
    T& operator*(){ return *ptr; }
    T* operator->(){ return ptr; }
};

//  Clasa abstracta
class CitireAfisare{
public:
    virtual istream& Citire(istream&)=0;
    virtual ostream& Afisare(ostream&)const=0;
};

//  Clasa User
class User:public CitireAfisare{
    string name;
    int age;
    bool admin;
    const int id;
    static int countId;
public:
    User();
    User(string name, int age, bool admin);
    User(const User &u);
    ~User(){}

    User& operator=(const User &u);
    bool operator==(const User &u)const;
    bool operator<(const User &u)const;
    bool operator>(const User &u)const;

    virtual istream& Citire(istream&);
    virtual ostream& Afisare(ostream&)const;

    friend istream& operator>>(istream& in, User& u);
    friend ostream& operator<<(ostream& out, const User& u);

    void setCountId(int countId){
        this->countId=countId;
    }
    const int getId()const{
        return this->id;
    }
    static int getCountId(){
        return countId;
    }
    string getName()const{
        return this->name;
    }
    bool getAdmin()const{
        if(this->admin)
            return true;
        return false;
    }
};

//  Constructor fara parametri
User::User():id(++countId){
    this->name="-";
    this->age=0;
    this->admin=false;
}

//  Constructor cu toti parametri
User::User(string name, int age, bool admin):id(++countId){
    this->name=name;
    this->age=age;
    this->admin=admin;
}

//  Constructor de copiere
User::User(const User &u):id(u.id){
    this->name=u.name;
    this->age=u.age;
    this->admin=u.admin;
}

//  Operator =
User &User::operator=(const User &u){ 
    if(this!=&u){
        this->name=u.name;
        this->age=u.age;
        this->admin=u.admin;
    }
    return *this;
}

//  Operator ==
bool User::operator==(const User &u)const{
    if(this->name==u.name)
        return true;
    return false;
}

//  Operator <
bool User::operator<(const User &u)const{
    if(this->name<u.name)
        return true;
    return false;
}

//  Operator >
bool User::operator>(const User &u)const{
    if(this->name>u.name)
        return true;
    return false;
}

//  Citire
istream& User::Citire(istream& in){
    cout<<"User: ";
    in.get();
    getline(in, name);
    cout<<"Age: ";
    try{
        in>>age;
        if(age<=0)
            throw age;
    }
    catch(int age){
        cout<<"Introduceti o varsta pozitiva";
    }
    admin=false;
    return in;
}

//  Afisare
ostream& User::Afisare(ostream& out)const{
    cout<<endl;
    cout<<"User: "<<name<<endl;
    cout<<"Age: "<<age<<endl;
    cout<<"Admin: ";
    if(admin)
        cout<<"yes";
    else
        cout<<"no";
    cout<<endl;
    cout<<"ID: "<<id;
    return out;
}

//  Supraincarcare >>
istream& operator>>(istream& in, User& u){
    return u.Citire(in);
}

//  Supraincarcare <<
ostream& operator<<(ostream& out, const User& u){
    return u.Afisare(out);
}

//  Set
set<User> setUsers;

//  Static
int User::countId=0;

//  Clasa de baza
class App:public CitireAfisare{
protected:
    string title;
    string type;    // tipul se refera la aplicatii de fintes, jocuri rpg, romane etc
    int price;
    map<int, int> status;  
    //  key     valoare status
    //  id      0 -> pentru: necumparat/neinstalat 
    //          1 -> pentru: cumparat/instalat
    //          2 -> pentru: neupdatat
    vector<int> review; // folosim vector deoarece ne intereseaza sortarea si parcurgerea, inserarea se face doar la final (nu random) si nu se efectueaza stergeri.

    float avgReview()const{
        float sum;
        int k=0;
        for(auto iter=review.begin(); iter!=review.end(); iter++){
            sum+=*iter; k++;
        }
        sum=sum/k;
        return sum;
    }

    virtual void sendReview(){
        cout<<"\nCe nota acordati aplicatiei? [1->5]\n";
        float aux;
        cin>>aux;
        cout<<endl;
        review.push_back((int)aux);
    }
public:
    App();
    App(string title, string type, int price);
    App(string title, string type, int price, map<int,int> status, vector<int> review);
    App(const App &a);
    ~App(){
        status.clear();
        review.clear();
    }
    
    App& operator=(const App &a);
    bool operator<=(const App &a);
    bool operator>=(const App &a);

    void pairForMap(int id);

    virtual void update();
    virtual void action(int id);

    virtual istream& Citire(istream&);
    virtual ostream& Afisare(ostream&)const;

    virtual void Afisare(User user);

    friend istream& operator>>(istream& in, App& a);
    friend ostream& operator>>(ostream& out, const App& a);

    void setTitle(string title){this->title = title;}
    void setType(string type){this->type = type;}
    //void setStatus(string status){this->status = status;}
    void setPrice(int price){this->price= price;}

    //string getStatus(){return this->status;}
    string getTitle(){return this->title;}
    int getPrice(){return this->price;}
};

// Declarare lista de aplicatii
list<SmartPtr<App>> lista; // folosim lista pentru ca are performante mai bune in stergerea random de elemente (Delete din CRUD)

//-----------------------------------------------------------------------------

//  Constructor fara parametri
App::App(){
    this->title = "-";
    this->type = "-";
    this->price = 0;
    for(auto iter=setUsers.begin(); iter!=setUsers.end(); iter++){
        status.insert( { iter->getId(), 0 } );
    }
}

//  Constructor cu parametri
App::App(string title, string type, int price){
    this->title = title;
    this->type = type;
    this->price = price;
}

//  Constructor cu toti parametri
App::App(string title, string type, int price, map<int,int> status, vector<int> review){
    this->title = title;
    this->type = type;
    this->price = price;
    this->status = status;
    this->review = review;
}

//  Constructor de copiere
App::App(const App &a){
    this->title = a.title;
    this->type = a.type;
    this->price = a.price;
    this->status = a.status;
    this->review = a.review;
}

//  Supraincarcare =
App& App::operator=(const App &a){
    if(this!=&a){
        status.clear();
        review.clear();
        
        this->title = a.title;
        this->type = a.type;
        this->price = a.price;
        this->status = a.status;
        this->review = a.review;
    }
    return *this;
}

//  Supraincarcare <=
bool App::operator<=(const App &a){
    if(this->price<=a.price)
        return true;
    return false;
}

//  Supraincarcare >=
bool App::operator>=(const App &a){
    if(this->price>=a.price)
        return true;
    return false;
}

//  Initializam map-ul pentru noul user creat
void App::pairForMap(int id){
    status.insert({id, 0});
}

//  Update
void App::update(){
    int comanda;
    cout<<"\nCe doriti sa modificati?";
    cout<<"\n1. Titlul";
    cout<<"\n2. Tipul";
    cout<<"\n3. Pretul";
    cout<<endl;

    do{
        cin>>comanda;
        switch(comanda){
            case 1:{
                string title;
                cout<<"\nTitlu: ";
                cin>>title;
                this->title=title;
                break;
            }
            case 2:{
                string type;
                cout<<"\nTipul: ";
                cin>>type;
                this->type= type;
                break;
            }
            case 3:{
                int price;
                cout<<"\nPretul: ";
                cin>>price;
                this->price= price;
                break;
            }
        }
    }while(comanda!=1 && comanda!=2 && comanda!=3);

    for(auto iter=status.begin(); iter!=status.end(); iter++){
        //cout<<endl<<iter->first<<" "<<iter->second<<endl;
        if(iter->second == 1) //daca aplicatia este instalata se transforma in neupdatata
            iter->second=2;
        //cout<<endl<<iter->first<<" "<<iter->second<<endl;
    }

}

//  Action
void App::action(int id){
    string comanda;
    auto iter=status.find(id);
    switch (iter->second)
    {
        case 0:{
            cout<<"\nDoriti sa instalati aceasta aplicatie? [yes/no]\n";
            cin>>comanda;
            if(comanda=="yes"){
                iter->second=1;
                if(this->price)
                    cout<<"Costa: "<<this->price<<endl;
                sendReview();
            }
            break;
        }
        case 1:{
            cout<<"\nDoriti sa dezinstalati aceasta aplicatie? [yes/no]\n";
            cin>>comanda;
            if(comanda=="yes")
                iter->second=0;
            break;
        }
        case 2:{
            cout<<"\nDoriti sa updatati aceasta aplicatie? [yes/no]\n";
            cin>>comanda;
            if(comanda=="yes")
                iter->second=1;
                break;
        }   
    }
}

//  Citire
istream& App::Citire(istream& in){
    cout<<"Title: ";
    in.get();
    getline(in, title);
    cout<<"Type: ";
    getline(in, type);
    cout<<"Price: ";
    in>>price;
    return in;
}

//  Afisare
ostream& App::Afisare(ostream& out)const{
    out<<"Title: "<<this->title<<"\n";
    out<<"Type: "<<this->type<<"\n";
    if(price==0)
        out<<"free\n";
    else
        out<<"Price: "<<this->price<<"\n";
    //float rating=avgReview();
    out<<"Reting: "<<avgReview()<<endl;
    return out;
}

//
void App::Afisare(User user){
    cout<<"Title: "<<this->title<<"\n";
    cout<<"Type: "<<this->type<<"\n";
    if(user.getAdmin()==false){
        auto iter=status.find(user.getId());
        switch (iter->second)
        {
            case 0:{
                cout<<"Neinstalat\n";
                cout<<"Price: "<<this->price<<endl;
                break;
            }
            case 1:{
                cout<<"Instalat\n";
                break;
            }
            case 2:{
                cout<<"Neupdatat\n";
                break;
            }
        }
    }
    cout<<"Rating: "<<avgReview()<<endl;
}

//  Supraincarcare >>
istream& operator>>(istream& in, App& a){
    return a.Citire(in);
}

//  Supraincarcare <<
ostream& operator<<(ostream& out, const App& a){
    return a.Afisare(out);
}

//-----------------------------------------------------------------------------

//  Derivata 1 - baza
class Game:public App{
    string mode;    // mode precizeaza daca jocul este pvp sau nu
public:
    Game();
    Game(string title, string type, int price, string mode);
    Game(string title, string type, int price, string mode, map<int,int> status, vector<int> review);
    Game(const Game& g);

    Game& operator=(const Game& g);

    void update();

    virtual istream& Citire(istream&);
    virtual ostream& Afisare(ostream&)const;

    friend istream& operator>>(istream& in, Game& g);
    friend ostream& operator>>(ostream& out, const Game& g);

    void setMode(string mode){this->mode = mode;}
};

//-----------------------------------------------------------------------------

//  Constructor fara parametri
Game::Game():App(){
    this->mode = "-";
}

//  Constructor cu parametri
Game::Game(string title, string type, int price, string mode):App(title, type, price){
    this->mode = mode;
}

//  Constructor cu toti parametri
Game::Game(string title, string type, int price, string mode, map<int,int> status, vector<int> review):App(title, type, price, status, review){
    this->mode = mode;
}

//  Constructor de copiere
Game::Game(const Game& g):App(g){
    this->mode = g.mode;
}

//  Supraincarcare =
Game& Game::operator=(const Game& g){
    if(this!=&g){
        App::operator=(g);
        this->mode = g.mode;
    }
    return *this;
}

//  Update
void Game::update(){
    int comanda;
    cout<<"\nCe doriti sa modificati?";
    cout<<"\n1. Titlul";
    cout<<"\n2. Tipul";
    cout<<"\n3. Pretul";
    cout<<"\n4. Modul";
    cout<<endl;

    do{
        cin>>comanda;
        switch(comanda){
            case 1:{
                string title;
                cout<<"\nTitlu: ";
                cin>>title;
                this->title=title;
                break;
            }
            case 2:{
                string type;
                cout<<"\nTipul: ";
                cin>>type;
                this->type= type;
                break;
            }
            case 3:{
                int price;
                cout<<"\nPret: ";
                cin>>price;
                this->price= price;
                break;
            }
            case 4:{
                int comandaMode;
                do{
                    cout<<"Mode: ";
                    cout<<"\n1. Pvp";
                    cout<<"\n2. Cpu";
                    cout<<endl;
                    cin>>comandaMode;
                    switch(comandaMode){
                        case 1:{
                            this->mode="Pvp";
                            break;
                        }
                        case 2:{
                            this->mode="Cpu";
                            break;
                        }
                    }
                }while(comandaMode!=1 && comandaMode!=2);
                break;
            }
        }
    }while(comanda!=1 && comanda!=2 && comanda!=3 && comanda!=4);

    for(auto iter=status.begin(); iter!=status.end(); ++iter){
        iter->second=0;
    }
    
}

//  Citire
istream& Game::Citire(istream& in){
    App::Citire(in);
    int comanda;
    do{
        cout<<"Mode: ";
        cout<<"\n1. Pvp";
        cout<<"\n2. Cpu";
        cout<<endl;
        cin>>comanda;
        switch(comanda){
            case 1:{
                this->mode="Pvp";
                break;
            }
            case 2:{
                this->mode="Cpu";
                break;
            }
        }
    }while(comanda!=1 && comanda!=2);
    return in;
}

//  Afisare
ostream& Game::Afisare(ostream& out)const{
    App::Afisare(out);
    out<<"Mode: "<<this->mode<<"\n";
    return out;
}

//  Supraincarcare >>
istream& operator>>(istream& in, Game& g){
    return g.Citire(in);
}

//  Supraincarcare <<
ostream& operator<<(ostream& out, const Game& g){
    return g.Afisare(out);
}

//-----------------------------------------------------------------------------

//  Derivata 1 - baza
class Book:public App{
    string author;
    virtual void sendReview(){
        cout<<"\nCe nota acordati cartii? [1->5]\n";
        float aux;
        cin>>aux;
        cout<<endl;
        review.push_back((int)aux);
    }
public:
    Book();
    Book(string title, string type, int price, string author);
    Book(string title, string type, int price, string author, map<int,int> status, vector<int> review);
    Book(const Book& b);

    Book& operator=(const Book& b);

    virtual void action(int id);
    virtual void Afisare(User user);

    virtual istream& Citire(istream&);
    virtual ostream& Afisare(ostream&)const;

    friend istream& operator>>(istream& in, Game& g);
    friend ostream& operator>>(ostream& out, const Game& g);  
};

//-----------------------------------------------------------------------------

//  Constructor fara parametri
Book::Book():App(){
    this->author = "-";
}

//  Constructor cu parametri
Book::Book(string title, string type, int price, string author):App(title, type, price){
    this->author = author;
}

//  Constructor cu toti parametri
Book::Book(string title, string type, int price, string author, map<int,int> status, vector<int> review):App(title, type, price, status, review){
    this->author = author;
}

//  Constructor de copiere
Book::Book(const Book& b):App(b){
    this->author = b.author;
}

//  Supraincarcare =
Book& Book::operator=(const Book& b){
    if(this!=&b){
        App::operator=(b);
        this->author = b.author;
    }
    return *this;
}

//  Action
void Book::action(int id){
    string comanda;
    auto iter=status.find(id);
    if(iter->second==0){
        cout<<"\nDoriti sa cumparati aceasta carte? [yes/no]\n";
        cin>>comanda;
        if(comanda=="yes"){
            iter->second=1;
            if(this->price)
                cout<<"Costa: "<<this->price;
        }
    }
    else
        cout<<"\nNu exista actiune disponibila pentru aceasta aplicatie";
}

//  Citire
istream& Book::Citire(istream& in){
    App::Citire(in);
    cout<<"Author: ";
    in.get();
    getline(in, author);
    return in;
}

//  Afisare
ostream& Book::Afisare(ostream& out)const{
    App::Afisare(out);
    out<<"Author: "<<this->author<<"\n";
    return out;
}

//
void Book::Afisare(User user){
    cout<<"Title: "<<this->title<<"\n";
    cout<<"Type: "<<this->type<<"\n";
    if(user.getAdmin()==false){
        auto iter=status.find(user.getId());
        switch (iter->second)
        {
            case 0:{
                cout<<"Necumparat\n";
                cout<<"Price: "<<this->price<<endl;
                break;
            }
            case 1:{
                cout<<"Cumparat\n";
                break;
            }
        }
    }
}

//  Supraincarcare >>
istream& operator>>(istream& in, Book& b){
    return b.Citire(in);
}

//  Supraincarcare <<
ostream& operator<<(ostream& out, const Book& b){
    return b.Afisare(out);
}

//-----------------------------------------------------------------------------

//  Derivata 2 - Book - baza
class Ebook:public Book{
    int noPages;
public:
    Ebook();
    Ebook(string title, string type, int price, string author, int noPages);
    Ebook(string title, string type, int price, string author, int noPages, map<int,int> status, vector<int> review);
    Ebook(const Ebook& e);

    Ebook& operator=(const Ebook& e);

    void update();

    virtual istream& Citire(istream&);
    virtual ostream& Afisare(ostream&)const;

    friend istream& operator>>(istream& in, Ebook& e);
    friend ostream& operator>>(ostream& out, const Ebook& e);

    void setNoPages(int noPages){this->noPages = noPages;} 
};

//-----------------------------------------------------------------------------

//  Constructor fara parametri
Ebook::Ebook():Book(){
    this->noPages = 0;
}

//  Cosntructor cu parametri
Ebook::Ebook(string title, string type, int price, string author, int noPages):Book(title, type, price, author){
    this->noPages = noPages;
}

//  Constructor cu toti parametri
Ebook::Ebook(string title, string type, int price, string author, int noPages, map<int,int> status, vector<int> review):Book(title, type, price, author, status, review){
    this->noPages = noPages;
}

//  Constructor de copiere
Ebook::Ebook(const Ebook& e):Book(e){
    this->noPages = e.noPages;
}

//  Supraincarcare =
Ebook& Ebook::operator=(const Ebook& e){
    if(this!=&e){
        Book::operator=(e);
        this->noPages = e.noPages;
    }
    return *this;
}

//  Update
void Ebook::update(){
    int comanda;
    cout<<"\nCe doriti sa modificati?";
    cout<<"\n1. Titlul";
    cout<<"\n2. Tipul";
    cout<<"\n3. Pretul";
    cout<<"\n4. Numar pagini";
    cout<<endl;

    do{
        cin>>comanda;
        switch(comanda){
            case 1:{
                string title;
                cout<<"\nTitlu: ";
                cin>>title;
                this->title=title;
                break;
            }
            case 2:{
                string type;
                cout<<"\nTipul: ";
                cin>>type;
                this->type= type;
                break;
            }
            case 3:{
                int price;
                cout<<"\nPretul: ";
                cin>>price;
                this->price= price;
                break;
            }
            case 4:{
                int noPages;
                cout<<"\nNumar pagini: ";
                cin>>noPages;
                this->noPages= noPages;
                break;
            }
        }
    }while(comanda!=1 && comanda!=2 && comanda!=3 && comanda!=4);

    for(auto iter=status.begin(); iter!=status.end(); ++iter){
        iter->second=0;
    }

}

//  Citire
istream& Ebook::Citire(istream& in){
    Book::Citire(in);
    cout<<"No pages: ";
    in>>noPages;
    return in;
}

//  Afisare
ostream& Ebook::Afisare(ostream& out)const{
    Book::Afisare(out);
    out<<"No pages: "<<this->noPages<<"\n";
    return out;
}

//  Supraincarcare >>
istream& operator>>(istream& in, Ebook& e){
    return e.Citire(in);
}

//  Supraincarcare <<
ostream& operator<<(ostream& out, const Ebook& e){
    return e.Afisare(out);
}

//-----------------------------------------------------------------------------

//  Derivata 2 - Book - baza
class AudioBook:public Book{
    int duration;
public:
    AudioBook();
    AudioBook(string title, string type, int price, string author, int duration);
    AudioBook(string title, string type, int price, string author, int duration, map<int,int> status, vector<int> review);
    AudioBook(const AudioBook& a);

    AudioBook& operator=(const AudioBook& a);

    void update();

    virtual istream& Citire(istream&);
    virtual ostream& Afisare(ostream&)const;

    friend istream& operator>>(istream& in, AudioBook& a);
    friend ostream& operator>>(ostream& out, const AudioBook& a);   

    void setDuration(int duration){this->duration = duration;} 
};

//-----------------------------------------------------------------------------

//  Constructor fara parametri
AudioBook::AudioBook():Book(){
    this->duration = 0;
}

//  Cosntructor cu parametri
AudioBook::AudioBook(string title, string type, int price, string author, int duration):Book(title, type, price, author){
    this->duration = duration;
}

//  Constructor cu toti parametri
AudioBook::AudioBook(string title, string type, int price, string author, int duration, map<int,int> status, vector<int> review):Book(title, type, price, author, status, review){
    this->duration = duration;
}

//  Constructor de copiere
AudioBook::AudioBook(const AudioBook& a):Book(a){
    this->duration = a.duration;
}

//  Supraincarcare =
AudioBook& AudioBook::operator=(const AudioBook& a){
    if(this!=&a){
        Book::operator=(a);
        this->duration = a.duration;
    }
    return *this;
}

//  Update
void AudioBook::update(){
    int comanda;
    cout<<"\nCe doriti sa modificati?";
    cout<<"\n1. Titlul";
    cout<<"\n2. Tipul";
    cout<<"\n3. Pretul";
    cout<<"\n4. Durata";
    cout<<endl;

    do{
        cin>>comanda;
        switch(comanda){
            case 1:{
                string title;
                cout<<"\nTitlu: ";
                cin>>title;
                this->title=title;
                break;
            }
            case 2:{
                string type;
                cout<<"\nTipul: ";
                cin>>type;
                this->type= type;
                break;
            }
            case 3:{
                int price;
                cout<<"\nPretul: ";
                cin>>price;
                this->price= price;
                break;
            }
            case 4:{
                int duration;
                cout<<"\nDurata: ";
                cin>>duration;
                this->duration= duration;
                break;
            }
        }
    }while(comanda!=1 && comanda!=2 && comanda!=3 && comanda!=4);

    for(auto iter=status.begin(); iter!=status.end(); ++iter){
        iter->second=0;
    }

}

//  Citire
istream& AudioBook::Citire(istream& in){
    Book::Citire(in);
    cout<<"Duration: ";
    in>>duration;
    return in;
}

//  Afisare
ostream& AudioBook::Afisare(ostream& out)const{
    Book::Afisare(out);
    out<<"Duration: "<<this->duration<<"\n";
    return out;
}

//  Supraincarcare >>
istream& operator>>(istream& in, AudioBook& a){
    return a.Citire(in);
}

//  Supraincarcare <<
ostream& operator<<(ostream& out, const AudioBook& a){
    return a.Afisare(out);
}

//-----------------------------------------------------------------------------


class MeniuSingleton{

    static MeniuSingleton *object;
    //  Constructor
    MeniuSingleton(){}

    //----------------------------------------------------------------CREATE-ADMIN----------------------------------------------------------------
    
    template <class Ttype>
    void create(Ttype t){
        App* aux;
        aux=new Ttype();
        cin>>*aux;
        lista.push_back(aux);
    }

    void createByAdmin(){
        int comanda;

        do{
            cout<<"\nCe doriti sa creati?";
            cout<<"\n1. App";
            cout<<"\n2. Game";
            cout<<"\n3. Ebook";
            cout<<"\n4. Audio Book";
            cout<<endl;
            
            cin>>comanda;
            cout<<endl;
            switch(comanda){
                case 1:{
                    App type;
                    create(type);
                    break;
                }
                case 2:{
                    Game type;
                    create(type);
                    break;
                }
                case 3:{
                    Ebook type;
                    create(type);
                    break;
                }
                case 4:{
                    AudioBook type;
                    create(type);
                    break;
                }
            }
        }while(comanda!=1 && comanda!=2 && comanda!=3 && comanda!=4);

    }

    //----------------------------------------------------------------READ-USER-------------------------------------------------------------------

    void sortListaAlplhabetical(){
        int comanda;
        do{
            cout<<"\nAlegeti ordinea:";
            cout<<"\n1. Crescator";
            cout<<"\n2. Descrescator";
            cout<<endl;
            cin>>comanda;
            switch(comanda){
                case 1:{
                    lista.sort([](SmartPtr<App> a, SmartPtr<App> b){ // avem nevoie de o astfel de declarare deoarece folosim pointeri
                        if(a->getTitle()<=b->getTitle())
                            return true;
                        return false;
                    });// lambda functie
                    break;
                }
                case 2:{
                    lista.sort([](SmartPtr<App> a, SmartPtr<App> b){ // avem nevoie de o astfel de declarare deoarece folosim pointeri
                        if(a->getTitle()>=b->getTitle())
                            return true;
                        return false;
                    });// lambda functie
                    break;
                }
            }
        }while(comanda!=1 && comanda!=2);
        cout<<endl;
    }

    void sortListaPrice(){
        int comanda;
        do{
            cout<<"\nAlegeti ordinea:";
            cout<<"\n1. Crescator";
            cout<<"\n2. Descrescator";
            cout<<endl;
            cin>>comanda;
            switch(comanda){
                case 1:{
                    lista.sort([](SmartPtr<App> a, SmartPtr<App> b){ // avem nevoie de o astfel de declarare deoarece folosim pointeri
                        if(*a<=*b)
                            return true;
                        return false;
                    });// lambda functie
                    break;
                }
                case 2:{
                    lista.sort([](SmartPtr<App> a, SmartPtr<App> b){ // avem nevoie de o astfel de declarare deoarece folosim pointeri
                        if(*a>=*b)
                            return true;
                        return false;
                    });// lambda functie
                    break;
                }
            }
        }while(comanda!=1 && comanda!=2);
        cout<<endl;
    }

    void sortLista(){
        int comanda;
        do{
            cout<<"\nAlege tipul de sortare:";
            cout<<"\n1. Alfabetic";
            cout<<"\n2. Pret";
            cout<<endl;
            cin>>comanda;
            switch(comanda){
                case 1:{
                    sortListaAlplhabetical();
                    break;
                }
                case 2:{
                    sortListaPrice();
                    break;
                }
            }
        }while(comanda!=1 && comanda!=2);
    }

    void select(User user){
        auto iter=lista.begin();
        int k;
        string comanda;
        cout<<"\nSelectati o aplicatie: [0 for break] ";
        cout<<endl;
        cin>>k; k--;
        if(k>=0){
            advance(iter, k);
            (*iter)->action(user.getId());
        }
    }

    void readByUser(User user){
        int k=1; // numerotam aplicatiile
        for(auto iter=lista.begin(); iter!=lista.end(); iter++){
            cout<<k++<<".\n";
            (*iter)->Afisare(user);
            cout<<endl;
        }// afiseaza elementele din lista
    }

    //----------------------------------------------------------------READ-ADMIN-------------------------------------------------------------------

    void readByAdmin(){
        int k=1; // numerotam aplicatiile
        for(auto iter=lista.begin(); iter!=lista.end(); iter++){
            cout<<k++<<".\n"<<**iter<<endl;
        }// afiseaza elementele din lista
    }

    //----------------------------------------------------------------UPDATE-ADMIN-----------------------------------------------------------------

    void updateByAdmin(){
        auto iter=lista.begin();
        int k;

        cout<<endl;
        readByAdmin();

        cout<<"\nSelectati o aplicatie: [0 for break] ";
        cout<<endl;
        cin>>k; k--;
        advance(iter, k);

        (*iter)->update();

    }

    //----------------------------------------------------------------DELETE-ADMIN-----------------------------------------------------------------

    void deleteByAdmin(){
        auto iter=lista.begin();
        int k;
        string comanda;
        cout<<endl;
        readByAdmin();

        cout<<"\nSelectati aplicatia pe care doriti sa o stergeti: ";
        cout<<endl;
        cin>>k; k--;
        advance(iter, k);

        lista.erase(iter);

    }

    //----------------------------------------------------------------MENIU-USER------------------------------------------------------------------

    void meniuUser(User user){
        int comanda;
        bool run=true;

        do{
            cout<<endl;
            readByUser(user);
            cout<<"\n 1. Sortati lista";
            cout<<"\n 2. Selectati o aplicatie";
            cout<<"\n 0. Break";
            cout<<endl;

            cin>>comanda;
                
            switch(comanda){
                case 1:{
                    sortLista();
                    break;
                }
                case 2:{
                    select(user);
                    break;
                }
                case 0:{
                    run=false;
                    break;
                }
            }

        }while( (comanda!=1 && comanda!=2 && comanda!=0) || run==true );
   
    }

    //----------------------------------------------------------------MENIU-ADMIN------------------------------------------------------------------

    void meniuAdmin(User admin){
        int comanda;
        bool run=true;
        do{
            cout<<"\n 1. Create";
            cout<<"\n 2. Read";
            cout<<"\n 3. Update";
            cout<<"\n 4. Delete";
            cout<<"\n 0. Break";
            cout<<endl;

            cin>>comanda;
                
            switch(comanda){
                case 1:{
                    createByAdmin();
                    break;
                }
                case 2:{
                    readByAdmin();
                    break;
                }
                case 3:{
                    updateByAdmin();
                    break;
                }
                case 4:{
                    deleteByAdmin();
                    break;
                }
                case 0:{
                    run=false;
                    break;
                }
            }

        }while( (comanda!=1 && comanda!=2 && comanda!=3 && comanda!=4 && comanda!=0) || run==true );
   
    }

    void logIn(){
        string aux;
        cout<<"\nUser: ";
        cin.get();
        getline(cin, aux);
        for(auto iter=setUsers.begin(); iter!=setUsers.end(); iter++){
            if(aux == (iter->getName()) ){
                if(iter->getAdmin()){
                    meniuAdmin(*iter);
                    break;
                }
                else{
                    meniuUser(*iter);
                    break;
                }
            }
        }
        
    }

    void signIn(){
        User aux;
        cin>>aux;
        setUsers.insert(aux);

        for(auto iter=lista.begin(); iter!=lista.end(); iter++)
            (*iter)->pairForMap(aux.getId());
        //  pentru fiecare user nou setam toate aplicatiile si cartile ca fiind necumparate/neinstalate

        meniuUser(aux);
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
            cout<<"\n   1. Log in";
            cout<<"\n   2. Sing in";
            cout<<"\n   0. STOP";
            cout<<endl;
            cin>>comanda;
            switch (comanda)
            {
                case 1:{
                    logIn();
                    break;
                }
                case 2:{
                    signIn();
                    break;
                }
                case 0:{
                    run=false;
                    break;
                }
            }
        }while( (comanda!=1 && comanda!=2 && comanda!=0) || run==true);
    }

};

//---------------------------------------------------------------------------------------------------------------------------------------

// Static
MeniuSingleton *MeniuSingleton::object=0;



int main(){

    // Declarare admini
    User admin1("admin", 20, true);
    setUsers.insert(admin1);


    MeniuSingleton *myMenu = myMenu->getInstance();
    myMenu->meniu();
    
    setUsers.clear();
    lista.clear();
    
    return 0;
}