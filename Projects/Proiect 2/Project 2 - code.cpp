#include <iostream>
#include <list>
#include <iterator>
#include <typeinfo>

using namespace std;

//  Smart pointer class
/*
template <class T>
class SmartPtr {
    T* ptr;
public:

    explicit SmartPtr(T* p = NULL) { ptr = p; }
    ~SmartPtr() { delete (ptr); }
 
    T& operator*() { return *ptr; } 
    T* operator->() { return ptr; }
};
*/

//  Clasa abstracta
class CitireAfisare{
public:
    virtual istream& Citire(istream&)=0;
    virtual ostream& Afisare(ostream&)const=0;
};

//  Clasa de baza
class App:public CitireAfisare{
protected:
    string title;
    string type;    // tipul se refera la aplicatii de fintes, jocuri rpg, romane etc
    string status;  // status poate fi: "instalata", "update disponibil", "dezinstaleaza" etc
    int price; 
public:
    App();
    App(string title, string type, int price);
    App(string title, string type, string status, int price);
    App(const App &a);
    ~App(){}
    
    App& operator=(const App &a);
    bool operator<=(const App &a);
    bool operator>=(const App &a);

    virtual void update();

    virtual istream& Citire(istream&);
    virtual ostream& Afisare(ostream&)const;

    friend istream& operator>>(istream& in, App& a);
    friend ostream& operator>>(ostream& out, const App& a);

    void setTitle(string title){this->title = title;}
    void setType(string type){this->type = type;}
    void setStatus(string status){this->status = status;}
    void setPrice(int price){this->price= price;}

    string getStatus(){return this->status;}
    string getTitle(){return this->title;}
};

// Declarare lista de aplicatii
list<App*> lista;

//-----------------------------------------------------------------------------

//  Constructor fara parametri
App::App(){
    this->title = "-";
    this->status = "-";
    this->type = "-";
    this->price = 0;
}

//  Constructor cu parametri
App::App(string title, string type, int price){
    this->title = title;
    this->type = type;
    this->status = "-";
    this->price = price;
}

//  Constructor cu toti parametri
App::App(string title, string type, string status, int price){
    this->title = title;
    this->type = type;
    this->status = status;
    this->price = price;
}

//  Constructor de copiere
App::App(const App &a){
    this->title = a.title;
    this->status = a.status;
    this->type = a.type;
    this->price = a.price;
}

//  Supraincarcare =
App& App::operator=(const App &a){
    if(this!=&a){
        this->title = a.title;
        this->status = a.status;
        this->type = a.type;
        this->price = a.price;
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

    this->status="Neupdatat";

}

//  Citire
istream& App::Citire(istream& in){
    cout<<"Title: ";
    in.get();
    getline(in, title);
    cout<<"Type: ";
    //cin.get();
    getline(in, type);
    this->status = "-";
    cout<<"Price: ";
    in>>price;
    return in;
}

//  Afisare
ostream& App::Afisare(ostream& out)const{
    out<<"Title: "<<this->title<<"\n";
    out<<"Type: "<<this->type<<"\n";
    out<<"Status: "<<this->status<<"\n";
    if(price==0)
        out<<"free\n";
    else
        out<<"Price: "<<this->price<<"\n";
    return out;
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
    Game(string title, string type, string status, int price, string mode);
    Game(const Game& g);
    ~Game(){}

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
Game::Game(string title, string type, string status, int price, string mode):App(title, type, status, price){
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

    this->status="Neupdatat";
    
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
public:
    Book();
    Book(string title, string type, int price, string author);
    Book(string title, string type, string status, int price, string author);
    Book(const Book& b);
    ~Book(){}

    Book& operator=(const Book& b);

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
Book::Book(string title, string type, string status, int price, string author):App(title, type, status, price){
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
    Ebook(string title, string type, string status, int price, string author, int noPages);
    Ebook(const Ebook& e);
    ~Ebook(){}

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
Ebook::Ebook(string title, string type, string status, int price, string author, int noPages):Book(title, type, status, price, author){
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
    AudioBook(string title, string type, string status, int price, string author, int duration);
    AudioBook(const AudioBook& a);
    ~AudioBook(){}

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
AudioBook::AudioBook(string title, string type, string status, int price, string author, int duration):Book(title, type, status, price, author){
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

//----------------------------------------------------------------CREATE----------------------------------------------------------------

void createApp(){
    App* aux;
    aux = new App();
    cin>>*aux;
    aux->setStatus("Neinstalat");
    lista.push_back(aux);
}

void createGame(){
    //App* aux;
    Game *aux;
    aux = new Game();
    //cin>>static_cast<Game&>(*aux);
    cin>>*aux;
    aux->setStatus("Neinstalat");
    lista.push_back(aux);
}

void createEbook(){
    //App* aux;
    Ebook *aux;
    aux = new Ebook();
    //cin>>static_cast<Ebook&>(*aux);
    cin>>*aux;
    aux->setStatus("Necumparat");
    lista.push_back(aux);
}

void createAudiobook(){
    //App* aux;
    AudioBook *aux;
    aux = new AudioBook();
    //cin>>static_cast<AudioBook&>(*aux);
    cin>>*aux;
    aux->setStatus("Necumparat");
    lista.push_back(aux);
}

void createBook(){
    int comanda;

    do{
        cout<<"\nCe doriti sa creati?";
        cout<<"\n1. Ebook";
        cout<<"\n2. Audio Book";
        cout<<endl;

        cin>>comanda;
        switch(comanda){
            case 1:{
                createEbook();
                break;
            }
            case 2:{
                createAudiobook();
                break;
            }
        }

    }while(comanda!=1 && comanda!=2);

}

void createCrud(){
    int comanda;

    do{
        cout<<"\nCe doriti sa creati?";
        cout<<"\n1. App";
        cout<<"\n2. Game";
        cout<<"\n3. Book";
        cout<<endl;
        
        cin>>comanda;
        cout<<endl;
        switch(comanda){
            case 1:{
                createApp();
                break;
            }
            case 2:{
                createGame();
                break;
            }
            case 3:{
                createBook();
                break;
            }
        }
    }while(comanda!=1 && comanda!=2 && comanda!=3);

}

//----------------------------------------------------------------READ-------------------------------------------------------------------

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
                lista.sort([](App* a, App* b){ // avem nevoie de o astfel de declarare deoarece folosim pointeri
                    if(a->getTitle()<=b->getTitle())
                        return true;
                    return false;
                });// lambda functie
                break;
            }
            case 2:{
                lista.sort([](App* a, App* b){ // avem nevoie de o astfel de declarare deoarece folosim pointeri
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
                lista.sort([](App* a, App* b){ // avem nevoie de o astfel de declarare deoarece folosim pointeri
                    if(*a<=*b)
                        return true;
                    return false;
                });// lambda functie
                break;
            }
            case 2:{
                lista.sort([](App* a, App* b){ // avem nevoie de o astfel de declarare deoarece folosim pointeri
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

void showLista(){
    int k=1; // numerotam aplicatiile
    for(auto iter=lista.begin(); iter!=lista.end(); iter++){
        cout<<k++<<".\n"<<**iter<<endl;
    }// afiseaza elementele din lista
}

void action(){
    list<App*>::iterator iter=lista.begin();
    int k;
    string comanda;
    cout<<"\nSelectati o aplicatie: [0 for break] ";
    cout<<endl;
    cin>>k; k--;
    if(k>=0){
        
        advance(iter, k);
    //    cout<<**iter;// afiseaza aplciatia selectata

        if(typeid(**iter)==typeid(Ebook) || typeid(**iter)==typeid(AudioBook)){

            if( (*iter)->getStatus()=="Necumparat" ){
                cout<<"\nDoriti sa cumparati aceasta carte? [yes/no]";
                cout<<endl;
                cin>>comanda;
                if(comanda=="yes")
                    (*iter)->setStatus("Cumparat");
            }
            else
                cout<<"\nNu exista actiune disponibila pentru aceasta aplicatie";

        }
        else{

            if( (*iter)->getStatus()=="Neinstalat"){
                cout<<"\nDoriti sa instalati aceasta aplicatie? [yes/no]";
                cout<<endl;
                cin>>comanda;
                if(comanda=="yes")
                    (*iter)->setStatus("Instalat");
            }
            else if( (*iter)->getStatus()=="Neupdatat"){
                cout<<"\nDoriti sa updatati aceasta aplicatie? [yes/no]";
                cout<<endl;
                cin>>comanda;
                if(comanda=="yes")
                    (*iter)->setStatus("Instalat");       
            }
            else{
                cout<<"\nDoriti sa dezinstalati aceasta aplicatie? [yes/no]";
                cout<<endl;
                cin>>comanda;
                if(comanda=="yes")
                    (*iter)->setStatus("Neinstalat");
            }
            
        }
        cout<<endl;

    }
}

void readCrud(){
    cout<<endl;
    
    sortLista();
    showLista();
    
    action();
}

//----------------------------------------------------------------UPDATE-----------------------------------------------------------------

void updateCrud(){
    list<App*>::iterator iter=lista.begin();
    int k;

    cout<<endl;
    showLista();

    cout<<"\nSelectati o aplicatie: [0 for break] ";
    cout<<endl;
    cin>>k; k--;
    advance(iter, k);

    (*iter)->update();

}

//----------------------------------------------------------------DELETE-----------------------------------------------------------------

void deleteCrud(){
    list<App*>::iterator iter=lista.begin();
    int k;
    cout<<endl;
    showLista();
    cout<<"\nSelectati aplicatia pe care doriti sa o stergeti: ";
    cout<<endl;
    cin>>k; k--;
    advance(iter, k);
    lista.erase(iter);

}

//----------------------------------------------------------------MENIU------------------------------------------------------------------

void meniu(){

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
                createCrud();
                break;
            }
            case 2:{
                readCrud();
                break;
            }
            case 3:{
                updateCrud();
                break;
            }
            case 4:{
                deleteCrud();
                break;
            }
            case 0:{
                run=false;
                break;
            }
        }

    }while( (comanda!=1 && comanda!=2 && comanda!=3 && comanda!=4 && comanda!=0) || run==true );

}

//---------------------------------------------------------------------------------------------------------------------------------------

int main(){
    meniu();
    return 0;
}