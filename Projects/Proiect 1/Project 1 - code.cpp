#include <iostream>
#include <cstring>

using namespace std;

// ---------- CONTRACT ----------

class Contract{
    string movie, name; // name reprezinta numele companiei sau numele actorului, in functie de caz
    int day, month, year;
    bool active;
    int duration; // in luni
    double price; 

public:
    Contract();
    Contract(int day, int month, int year, bool active, int duration, double price);
    Contract(string movie, string name, int day, int month, int year, bool active,
             int duration, double price);
    Contract(const Contract &contr);
    ~Contract();

    Contract &operator=(const Contract &contr);
    bool operator==(const Contract &contr);
    bool operator<(const Contract &contr);
    bool operator>(const Contract &contr);
    Contract operator+(Contract contr);
    Contract operator+=(int x);
    Contract operator+(int x);
    Contract operator-(Contract contr);
    Contract operator-=(int x);
    Contract operator-(int x);
    
    explicit operator float(){
        return (float)this->duration;
    }

    friend Contract operator+(int x, Contract contr);
    friend Contract operator-(int x, Contract contr);
    friend istream &operator>>(istream &in, Contract &c);
    friend ostream &operator<<(ostream &out, const Contract &c);
    const Contract &operator++(); //preincrementare

    static int getCount_id();

    void setMovie(string movie);
    void setName(string name);
    void setActive(bool active);
    void setDuration(int duration);
    void setPrice(double price);
    
    bool getActive();
    double getPrice();

    int avg();
};

// Constructori

// Fara parametri
Contract::Contract(){
    this->movie="-";
    this->name="-";
    this->day=0;
    this->month=0;
    this->year=0;
    this->active=false;
    this->duration=0;
    this->price=0;
}

// Cu parametri
Contract::Contract(int day, int month, int year, bool active, int duration, double price){
    this->movie="-";
    this->name="-";
    this->day=day;
    this->month=month;
    this->year=year;
    this->active=active;
    this->duration=duration;
    this->price=price;
    // Apelam functia auto_fill pentru celelalte variabile
}

// Cu toti parametrii
Contract::Contract(string movie, string name, int day, int month, 
                   int year, bool active, int duration, double price){
    this->movie=movie;
    this->name=name;
    this->day=day;
    this->month=month;
    this->year=year;
    this->active=active;
    this->duration=duration;
    this->price=price;
}

// Constructor de copiere
Contract::Contract(const Contract &contr){
    this->movie=contr.movie;
    this->name=contr.name;
    this->day=contr.day;
    this->month=contr.month;
    this->year=contr.year;
    this->active=contr.active;
    this->duration=contr.duration;
    this->price=contr.price;
}

//Destructor
Contract::~Contract(){
}

// Supraincarcarea operatorului =
Contract &Contract::operator=(const Contract &contr){
    if (this != &contr){
        this->movie=contr.movie;
        this->name=contr.name;
        this->day=contr.day;
        this->month=contr.month;
        this->year=contr.year;
        this->active=contr.active;
        this->duration=contr.duration;
        this->price=contr.price;
    }
    return *this;
}

// Supraincarcarea operatorului ==
bool Contract::operator==(const Contract &contr){
    if(this->movie==contr.movie && this->name==contr.name && this->day==contr.day
      && this->month==contr.month && this->year==contr.year && this->duration==contr.duration)
        return true;
    return false;
}

// Supraincarcarea operatorului <
bool Contract::operator<(const Contract &contr){
    if(this->price<contr.price)
        return true;
    return false;
}

// Supraincarcarea operatorului <
bool Contract::operator>(const Contract &contr){
    if(this->price>contr.price)
        return true;
    return false;
}

// Supraincarcare operator + (intre contracte)
Contract Contract::operator+(Contract contr){
    contr.movie=this->movie+"+"+contr.movie;
    contr.name=this->name+"+"+contr.name;
    contr.price=this->price+contr.price;
    return contr;
}

// Supraincarcare operator += 
Contract Contract::operator+=(int x){
    this->price+=x;
    return *this;
}

// Supraincarcare operator + (cu un int, la dreapta)
Contract Contract::operator+(int x){
    Contract aux(*this);
    aux.price=aux.price+x;
    return aux;
}

// Supraincarcare operator + (cu int, la stanga)
Contract operator+(int x, Contract contr){
    contr.price=contr.price+x;
    return contr;
}

// Supraincarcare operator - (intre contracte)
Contract Contract::operator-(Contract contr){
    contr.movie=this->movie+"-"+contr.movie;
    contr.name=this->name+"-"+contr.name;
    contr.price=this->price-contr.price;
    return contr;
}

// Supraincarcare operator -= 
Contract Contract::operator-=(int x){
    this->price-=x;
    return *this;
}

// Supraincarcare operator - (cu un int, la dreapta)
Contract Contract::operator-(int x){
    Contract aux(*this);
    aux.price=aux.price-x;
    return aux;
}

// Supraincarcare operator - (cu int, la stanga)
Contract operator-(int x, Contract contr){
    contr.price=contr.price-x;
    return contr;
}

// Supraincarcarea operatorului>>
istream &operator>>(istream &in, Contract &c){
    cout<<"\nDate:\nDay [no]: ";
    in>>c.day;
    cout<<"Month [no]: ";
    in>>c.month;
    cout<<"Year [no]: ";
    in>>c.year;
    cout<<"\nActive status: [yes/no]: ";
    char aux[4];
    in>>aux;
    if(strcmp(aux, "yes")==0)
        c.active=true;
    else
        c.active=false;
    cout<<"\nDuration [months]: ";
    in>>c.duration;
    cout<<"\nPrice [$]: ";
    in>>c.price;
    // pentru celelalte variabile apelam auto_fill
}

// Supraincarcarea operatorului<<
ostream &operator<<(ostream &out, const Contract &c){
    out<<"\n";
    for(int i=0; i<10; i++)
        out<<"-";
    out<<"Contract";
    for(int i=0; i<10; i++)
        out<<"-";
    out<<'\n';
    for(int i=0; i<strlen("Contract")+20; i++)
        out<<"-";
    out<<"\nMovie title: "<<c.movie;
    out<<"\nCompany/actor name: "<<c.name;
    out<<"\nContract date: ";
    if(c.day<10)
        out<<"0"<<c.day<<".";
    else
        out<<c.day<<".";
    if(c.month<10)
        out<<"0"<<c.month<<".";
    else
        out<<c.month<<"."; 
    out<<c.year<<"\n";
    out<<"Active: ";
    out<<(c.active ? "yes" : "no")<<"\n";
    out<<"Duration: "<<c.duration<<" months\n";
    out<<"Price: ";
    out<<c.price<<" $"<<"\n\n";

    return out;
}

// Preincrementare
const Contract &Contract::operator++(){
    this->price=(price/duration)*(duration+1);
    this->duration++;
    return *this;
}

// Setteri
void Contract::setMovie(string movie){
    this->movie=movie;
}
void Contract::setName(string name){
    this->name=name;
}
void Contract::setActive(bool active){
    this->active=active;
}
void Contract::setDuration(int duration){
    this->duration=duration;
}
void Contract::setPrice(double price){
    this->price=price;
}

// Getteri
bool Contract::getActive(){
    return this->active;
}
double Contract::getPrice(){
    return this->price;
}

// Functionalitate: returneaza venitul mediu pe luna
int Contract::avg(){
    return this->price/this->duration;
}

// ---------- ACTOR ----------

class Actor{
    string name;
    char *gender;
    int *age;       // in ani
    int no_movies;
    float height;   // in cm
    string* movies;

    Contract* status;

public:
    Actor();
    Actor(string name, char *gender, int *age, float height,
          Contract* status);
    Actor(string name, char *gender, int *age,
          int no_movies, float height, string* movies, Contract* status);
    Actor(const Actor &act);
    ~Actor();

    Actor &operator=(const Actor &act);
    bool operator==(const Actor &act);
    bool operator<(const Actor &act);
    bool operator>(const Actor &act);
    Actor operator+(Actor act);
    Actor operator+=(int x);
    Actor operator+(int x);
    Actor operator-(Actor act);
    Actor operator-=(int x);
    Actor operator-(int x);
    string operator[](int index);

    explicit operator float(){
        return (float)*this->age;
    }

    friend Actor operator+(Actor act, Contract &contr);
    friend Actor operator+(Contract &contr, Actor act);
    friend Actor operator+(int x, Actor act);
    friend Actor operator-(int x, Actor act);
    friend istream &operator>>(istream &in, Actor &act);
    friend ostream &operator<<(ostream &out, const Actor &act);
    const Actor &operator++(); //preincrementare

    void setName(string name);
    void setGender(char * gender);
    void setAge(int *age);
    void setHeight(float height);
    void setMovies(string movies);

    string getName();
    const char* getGender();
    const int* getAge();
    float getHeight();
    int getNo_movies();
    Contract &getContract();
};

// Constructori

// Fara parametri
Actor::Actor(){
    this->name="-";
    this->gender=NULL;
    this->age=NULL;
    this->no_movies=1;
    this->height=0;
    this->movies=NULL;
    this->status=NULL;
}

// Cu parametri
Actor::Actor(string name, char *gender, int* age, float height,
             Contract* status){
    this->name=name;
    this->gender=new char[strlen(gender)+1];
    strcpy(this->gender, gender);
    this->age=new int(*age);
    this->no_movies=1;
    this->height=height; 
    this->movies=new string[this->no_movies];
    for(int i=0; i<this->no_movies; i++)
        this->movies[i]="-";
    this->status=new Contract(*status);
    
    // Apelam functia auto_fill pentru celelalte variabile
}

// Cu toti parametri
Actor::Actor(string name, char *gender,
             int *age, int no_movies, float height, string* movies, Contract* status){
    this->name=name;
    this->gender=new char[strlen(gender)+1];
    strcpy(this->gender, gender);
    this->age=new int[1];
    this->age[0]=age[0];
    this->no_movies=no_movies;
    this->height=height;
    this->movies=new string[this->no_movies];
    for(int i=0; i<this->no_movies; i++)
        this->movies[i]=movies[i];
    this->status=new Contract;
    this->status=status;
}

// Constructor de copiere
Actor::Actor(const Actor &act){
    this->name=act.name;
    this->gender=new char[strlen(act.gender)+1];
    strcpy(this->gender, act.gender);
    this->age=new int[1];
    this->age[0]=act.age[0];
    this->no_movies=act.no_movies;
    this->height=act.height;
    this->movies=new string[act.no_movies];
    for(int i=0; i<act.no_movies; i++)
        this->movies[i]=act.movies[i];
    this->status=new Contract;
    this->status=act.status;
}

// Destructor
Actor::~Actor(){
    if(this->gender!=NULL)
        delete[] this->gender;
    if(this->age!=NULL)
        delete[] this->age;
    if(this->movies!=NULL)
        delete[] this->movies;
    if(this->status!=NULL)
        delete[] this->status;
}

// Supraincarcarea operatorului =
Actor &Actor::operator=(const Actor &act){
    if(this!=&act){
        if(this->gender!=NULL)
            delete[] this->gender;
        if(this->age!=NULL)
            delete[] this->age;
        if(this->movies!=NULL)
            delete[] this->movies;
        if(this->status!=NULL)
            delete[] this->status;

        this->name=act.name;
        this->gender=new char[strlen(act.gender)+1];
        strcpy(this->gender, act.gender);
        this->age=new int[1];
        this->age[0]=act.age[0];
        this->no_movies=act.no_movies;
        this->height=act.height;
        this->movies=new string[act.no_movies];
        for(int i=0; i<act.no_movies; i++)
            this->movies[i]=act.movies[i];

        this->status=new Contract;
        this->status=act.status;
    }
    return *this;
}

// Supraincarcarea operatorului ==
bool Actor::operator==(const Actor &act){
    if(this->name==act.name && this->age==act.age && this->height==act.height)
        return true;
    return false;
}

// Supraincarcarea operatorului <
bool Actor::operator<(const Actor &act){ // folosim supraincarcarea lui operatorului< de la contract
    if(this->status<act.status)
        return true;
    return false;
}

// Supraincarcarea operatorului >
bool Actor::operator>(const Actor &act){ // folosim supraincarcarea lui operatorului< de la contract
    if(this->status>act.status)
        return true;
    return false;
}

// Supraincarcare operator + (intre actori)
Actor Actor::operator+(Actor act){
    act.name=this->name+"+"+act.name;
    *act.status=*this->status+*act.status;
    return act;
}

// Supraincarcare operator +=
Actor Actor::operator+=(int x){
    *this->status+=x;
    return *this;
}

// Supraincarcare operator + (cu un int, la dreapta)
Actor Actor::operator+(int x){
    Actor aux(*this);
    *aux.status=*aux.status+x;
    return aux;
}

// Supraincarcam operator + (intre clasa actor si calsa companie)
Actor operator+(Actor act, Contract &contr){
    *act.status=*act.status+contr;
    return act;
}

// Supraincarcam operator + (intre clasa actor si calsa companie) comutativitate
Actor operator+(Contract &contr, Actor act){
    *act.status=*act.status+contr;
    return act;
}

// Supraincarcare operator + (cu int, la stanga)
Actor operator+(int x, Actor act){
    *act.status=*act.status+x;
    return act;
}

// Supraincarcare operator - (intre actori)
Actor Actor::operator-(Actor act){
    act.name=this->name+"-"+act.name;
    *act.status=*this->status-*act.status;
    return act;
}

// Supraincarcare operator -=
Actor Actor::operator-=(int x){
    *this->status-=x;
    return *this;
}

// Supraincarcare operator - (cu un int, la dreapta)
Actor Actor::operator-(int x){
    Actor aux(*this);
    *aux.status=*aux.status-x;
    return aux;
}

// Supraincarcare operator - (cu int, la stanga)
Actor operator-(int x, Actor act){
    *act.status=*act.status-x;
    return act;
}

// Supraincarcare operator []
string Actor::operator[](int index){
    if (0 <= index && index < this->no_movies)
        return this->movies[index];
    cout << "Index introdus gresit";   
}

// Supraincarcarea operatorului>>
istream &operator>>(istream &in, Actor &act){
    cout<<"\n   "<<"Actor\n";
    cout<<"\nFull name: [Name Surname] ";
    in.get();
    getline(in, act.name);
    char aux[100];
    cout<<"Sex: [M/F] ";
    in>>aux;
    if(act.gender!=NULL)
        delete[] act.gender;
    act.gender=new char[strlen(aux)+1];
    strcpy(act.gender, aux);
    cout<<"Age: ";
    if(act.age!=NULL) 
        delete[] act.age;
    act.age=new int[1];
    in>>act.age[0];
    cout<<"Height: ";
    in>>act.height;
    if(act.movies!=NULL)
        delete[] act.movies;
    act.movies=new string[1];
   
    cout<<"\n   ->Create contract: ";
    if (act.status!=NULL)
        delete[] act.status;
    act.status=new Contract[1];
    in>>act.status[0]; 
    // Apelam functia auto_fill pentru celelalte variabile
}

// Supraincarcarea operatorului<<
ostream &operator<<(ostream &out, const Actor &act){
    out<<"\n   "<<"Actor\n";
    out<<"---> "<<act.name<<"\n";
    out<<"Gender: "<<*act.gender<<"\n";
    out<<"Age: "<<*act.age<<" yo\n";
    out<<"Heigh: "<<act.height<<"cm\n\n";
    out<<"   Total moives: "<<act.no_movies<<"\n";
    for(int i=0; i<act.no_movies; i++)
        cout<<i+1<<". "<<act.movies[i]<<"\n";
    out<<"\n"<<*act.status;
    return out;
}

// Preincrementare
const Actor &Actor::operator++(){
    this->no_movies++;
    return *this;
}

//  Setteri
void Actor::setName(string name){
    this->name=name;
}
void Actor::setGender(char * gender){
    if(this->gender!=NULL)
        delete[] this->gender;
    this->gender=new char[strlen(gender)+1];
    this->gender=gender;
}
void Actor::setAge(int* age){
    if(this->age!=NULL)
        delete[] this->age;
    this->age=new int[1];
    this->age[0]=age[0];
}
void Actor::setHeight(float height){
    this->height=height;
}
void Actor::setMovies(string movies){
    string *aux;
    aux=new string[this->no_movies];
    for(int i=0; i<this->no_movies-1; i++)
        aux[i]=this->movies[i];
    delete[] this->movies;
    aux[this->no_movies-1]=movies;
    this->movies=new string[no_movies];
    for(int i=0; i<this->no_movies; i++)
        this->movies[i]=aux[i];
    delete[] aux;
}

//  Getteri
string Actor::getName(){
    return this->name;
}
const char *Actor::getGender(){
    return this->gender;
}
const int* Actor::getAge(){
    return this->age;
}
float Actor::getHeight(){
    return this->height;
}
int Actor::getNo_movies(){
    return this->no_movies;
}
Contract &Actor::getContract(){
    return this->status[0];
}

// ----------- COMPANY -----------

class Company{
    string name;
    int no_movies, no_contracts;
    string *movies;

    Contract* status;

public:
    Company();
    Company(string name, Contract* status);
    Company(string name, int no_movies, int no_contracts,
            string *movies, Contract* status);
    Company(const Company &comp);
    ~Company();

    Company &operator=(const Company &comp);
    bool operator==(const Company &comp);
    bool operator<(const Company &comp);
    Company operator+(Company comp);
    Company operator+=(int x);
    Company operator+(int x);
    Company operator-(Company comp);
    Company operator-=(int x);
    Company operator-(int x);
    string operator[](int index);

    explicit operator float(){
        return (float)this->no_movies;
    }

    friend Company operator+(int x, Company comp);
    friend Company operator-(int x, Company comp);
    friend istream &operator>>(istream &in, Company &comp);
    friend ostream &operator<<(ostream &out, Company &comp);
    const Company &operator++(); //preincrementare

    void setName(string name);
    void setNo_movies(int no_movies);
    void setNo_contracts(int no_cotnracts);
    void setMovies(string movies);

    string getName();
    int getNo_movies();
    Contract &getContract();
};

// Constructori

// Fara parametri
Company::Company(){
    this->name="-";
    this->no_movies=1;
    this->no_contracts=1;
    this->movies=NULL;
    this->status=NULL;
}

// Cu parametri
Company::Company(string name, Contract* status){
    this->no_movies=1;
    this->no_contracts=1;
    this->name=name;
    this->movies=new string[this->no_movies];
    for(int i=0; i<this->no_movies; i++)
        this->movies[i]="-";
    this->status=new Contract;
    this->status=status;
    // Apelam functia auto_fill pentru celelalte variabile
}

// Cu toti parametrii
Company::Company(string name, int no_movies, int no_contracts, 
                string *movies, Contract* status){
    this->name=name;
    this->no_movies=no_movies;
    this->no_contracts=no_contracts;
    this->movies=new string[this->no_movies];
    for(int i=0; i<this->no_movies; i++)
        this->movies[i]=movies[i];
    this->status=new Contract;
    this->status=status;
}

// Constructor de copiere
Company::Company(const Company &comp){ 
    this->name=comp.name;
    this->no_movies=comp.no_movies;
    this->no_contracts=comp.no_contracts;
    this->movies=new string[comp.no_movies];
    for(int i=0; i<comp.no_movies; i++)
        this->movies[i]=comp.movies[i];
    this->status=new Contract; 
    this->status=comp.status;
}

// Destructor
Company::~Company(){
    if(this->movies!=NULL)
        delete[] this->movies;
    if(this->status!=NULL)
        delete[] this->status;
}

// Supraincarcarea operatorului=
Company &Company::operator=(const Company &comp){
    if(this!=&comp){
        if(this->movies!=NULL)
            delete[] this->movies;
        if(this->status!=NULL)
            delete[] this->status;

        this->name=comp.name;
        this->no_movies=comp.no_movies;
        this->no_contracts=comp.no_contracts;
        this->movies=new string[comp.no_movies];
        for(int i=0; i<comp.no_movies; i++)
            this->movies[i]=comp.movies[i];
        this->status=new Contract;
        this->status=comp.status;
    }
    return *this; 
}

// Supraincarcarea operatorului ==
bool Company::operator==(const Company &comp){
    if(this->name==comp.name)
        return true;
    return false;
}

// Supraincarcarea operatorului <
bool Company::operator<(const Company &comp){
    if(this->status<comp.status)
        return true;
    return false;
}

// Supraincarcare operator + (intre companii)
Company Company::operator+(Company comp){
    comp.name=this->name+"+"+comp.name;
    *comp.status=*this->status+*comp.status;
    return comp;
}

// Supraincarcare operator +=
Company Company::operator+=(int x){
    *this->status+=x;
    return *this;
}

// Supraincarcare operator + (cu un int, la dreapta)
Company Company::operator+(int x){
    Company aux(*this);
    *aux.status=*aux.status+x;
    return aux;
}

// Supraincarcare operator + (cu int, la stanga)
Company operator+(int x, Company comp){
    *comp.status=*comp.status+x;
    return comp;
}

// Supraincarcare operator - (intre companii)
Company Company::operator-(Company comp){
    comp.name=this->name+"-"+comp.name;
    *comp.status=*this->status-*comp.status;
    return comp;
}

// Supraincarcare operator -=
Company Company::operator-=(int x){
    *this->status-=x;
    return *this;
}

// Supraincarcare operator - (cu un int, la dreapta)
Company Company::operator-(int x){
    Company aux(*this);
    *aux.status=*aux.status-x;
    return aux;
}

// Supraincarcare operator + (cu int, la stanga)
Company operator-(int x, Company comp){
    *comp.status=*comp.status-x;
    return comp;
}

// Supraincarcare operator []
string Company::operator[](int index){
    if (0 <= index && index < this->no_movies)
        return this->movies[index];
    cout << "Index introdus gresit";   
}

// Supraincarcarea operatorului>>
istream &operator>>(istream &in, Company &comp){
    cout<<"\n   "<<"Company\n";
    cout<<"\nName: ";
    in>>comp.name;
    comp.no_movies=1;
    comp.no_contracts=1; 
    if(comp.movies!=NULL)
        delete[] comp.movies;
    comp.movies=new string[1];

    cout<<"\n   ->Create contract: ";
    if (comp.status!=NULL)
        delete[] comp.status;
    comp.status=new Contract[1];
    in>>comp.status[0];
    // Apelam functia auto_fill pentru celelalte variabile
}

// Supraincarcarea operatorului<<
ostream &operator<<(ostream &out, Company &comp){
    out<<"\n   "<<"Company\n";
    out<<"---> "<<comp.name<<"\n";
    out<<"No contracts: "<<comp.no_contracts<<"\n";
    out<<"No movies: "<<comp.no_movies<<"\n";
    for(int i=0; i<comp.no_movies; i++)
        out<<i+1<<". "<<comp.movies[i]<<"\n";
    out<<"\n"<<*comp.status;
    return out;
}

// Preincrementare
const Company &Company::operator++(){
    this->no_movies++;
    this->no_contracts++;
    return *this;
}

//  Setteri
void Company::setName(string name){
    this->name=name;
}
void Company::setNo_movies(int no_movies){
    this->no_movies=no_movies;
}
void Company::setNo_contracts(int no_cotnracts){
    this->no_contracts=no_contracts;
}
void Company::setMovies(string movies){
    string *aux;
    aux=new string[this->no_movies];
    for(int i=0; i<this->no_movies-1; i++)
        aux[i]=this->movies[i];
    delete[] this->movies;
    aux[this->no_movies-1]=movies;
    this->movies=new string[no_movies];
    for(int i=0; i<this->no_movies; i++)
        this->movies[i]=aux[i];
    delete[] aux;
}

//  Getter
string Company:: getName(){
    return this->name;
}
int Company::getNo_movies(){
    return this->no_movies;
} 
Contract &Company::getContract(){
    return this->status[0];
}

// ----------- MOVIES ----------

class Movie{
    string title;
    string description;
    string* type;
    bool seen;
    int no_views, no_actors, no_companies;
    double money_earned;

    Actor* a;
    Company* c; 

    const int movie_id;
    static int count_id, view_price; 

public:
    Movie();
    Movie(string title, string description, string* type, 
          int no_actors, int no_companies, Actor* a, Company* c);
    Movie(string title, string description, string* type, bool seen,
          int no_views, int no_actors, int n_companies, double money_earned,
          Actor* a, Company* c);
    Movie(const Movie &mov);
    ~Movie();

    Movie &operator=(const Movie &mov);
    bool operator==(const Movie &mov);
    bool operator<(const Movie &mov);
    const Movie &operator++(); //preincrementare
    Movie operator+(Movie mov);
    Movie operator+=(int x);
    Movie operator+(int x);
    Movie operator-(Movie mov);
    Movie operator-=(int x);
    Movie operator-(int x);
    string operator[](int index);

    explicit operator float(){
        return (float)this->no_views;
    }

    friend Movie operator+(int x, Movie mov);
    friend Movie operator-(int x, Movie mov);
    friend istream &operator>>(istream &in, Movie &mov);
    friend ostream &operator<<(ostream &out, Movie &mov);

    void setCount_id(int count_id);
    void setTitle(string title);
    void setDescription(string description);
    void setType(string type, int i);
    void setNo_views(int no_views);
    void setSeen(bool seen);
    void setNo_actors(int no_actors);
    void setNo_companies(int no_companies);
    void setMoney_earned(double money_earned);

    int getMovie_id();
    static int getCount_id();
    string getTitle();
    string getDescription();
    const string* getType() const;
    int getNo_views();
    int getNo_companies();
    int getNo_actors();
    int getView_price();

    Actor &getActor(int i);
    Company &getCompany(int i);

    void show(int const space);
    int avg_company();
    int avg_actor();
};

// Constructori

// Fara parametri
Movie::Movie():movie_id(++count_id){
    this->title="-";
    this->description="-";
    this->type=new string[3]; 
    for(int i=0; i<3; i++)
        this->type[i]="-";
    this->seen=false;
    this->no_views=0;
    this->no_actors=0;
    this->no_companies=0;
    this->money_earned=0;
    this->a=NULL;
    this->c=NULL;
}

// Cu parametrii
Movie::Movie(string title, string description, string* type, int no_actors, 
            int no_companies, Actor* a, Company* c):movie_id(++count_id){
    this->title=title;
    this->description=description;
    this->type=new string[3]; 
    for(int i=0; i<3; i++)
        this->type[i]=type[i];
    this->seen=false;
    this->no_actors=no_actors;
    this->no_companies=no_companies;
    this->no_views=0;
    this->money_earned=0;
    this->a=new Actor[this->no_actors]; 
    for(int i=0; i<this->no_actors; i++)
        this->a[i]=a[i];

    this->c=new Company[this->no_companies];
    for(int i=0; i<this->no_companies; i++)
        this->c[i]=c[i];
}

// Cu toti parametrii
Movie::Movie(string title, string description, string* type, bool seen, 
            int no_views, int no_actors, int no_companies, double money_earned,
            Actor* a, Company* c):movie_id(++count_id){
    this->title=title;
    this->description=description;
    this->type=new string[3]; 
    for(int i=0; i<3; i++)
        this->type[i]=type[i];
    this->seen=seen;
    this->no_views=no_views;
    this->no_actors=no_actors;
    this->no_companies=no_companies;
    this->money_earned=money_earned;

    this->a=new Actor[this->no_actors]; 
    for(int i=0; i<this->no_actors; i++)
        this->a[i]=a[i];
    this->c=new Company[this->no_companies]; 
    for(int i=0; i<this->no_companies; i++)
        this->c[i]=c[i];
}

// Constructor de copiere
Movie::Movie(const Movie &mov):movie_id(mov.count_id){ // id-ul este ok asa?
    // cred ca trebuia mov.id
    this->title=mov.title;
    this->description=mov.description;
    this->type=new string[3];
    for(int i=0; i<3; i++)
        this->type[i]=mov.type[i];
    this->seen=mov.seen;
    this->no_views=mov.no_views;
    this->no_actors=mov.no_actors;
    this->no_companies=mov.no_companies;
    this->money_earned=mov.money_earned;

    this->a=new Actor[mov.no_actors];
    for(int i=0; i<mov.no_actors; i++)
        this->a[i]=mov.a[i];
    this->c=new Company[mov.no_companies];
    for(int i=0; i<mov.no_companies; i++)
        this->c[i]=mov.c[i];
}

// Destructor
Movie::~Movie(){
    if(this->type!=NULL)
        delete[] this->type;
    if(this->a!=NULL)
        delete[] this->a;
    if(this->c!=NULL)
        delete[] this->c;
}

// Supraincarcarea operatorului=
Movie &Movie::operator=(const Movie &mov){
    if(this!=&mov){
        if(this->type!=NULL)
            delete[] this->type;
        if(this->a!=NULL)
            delete[] this->a;
        if(this->c!=NULL)
            delete[] this->c;

        this->title=mov.title;
        this->description=mov.description;
        this->type=new string[3];
        for(int i=0; i<3; i++)
            this->type[i]=mov.type[i];
        this->seen=mov.seen;
        this->no_views=mov.no_views;
        this->no_actors=mov.no_actors;
        this->no_companies=mov.no_companies;
        this->money_earned=mov.money_earned;

        this->c=new Company[mov.no_companies];
        for(int i=0; i<mov.no_companies; i++)
            this->c[i]=mov.c[i];   
        
        this->a=new Actor[mov.no_actors];
        for(int i=0; i<mov.no_actors; i++)
            this->a[i]=mov.a[i];
    }
    return *this; 
}

// Supraincarcarea operatorului ==
bool Movie::operator==(const Movie &mov){
    if(this->title==mov.title && this->no_actors==mov.no_actors
       && this->no_companies==mov.no_companies)
        return true;
    return false;
}

// Supraincarcarea operatorului <
bool Movie::operator<(const Movie &mov){
    if(this->money_earned<mov.money_earned)
        return true;
    return false;
}

// Supraincarcare operator + (intre filme)
Movie Movie::operator+(Movie mov){
    mov.title=this->title+"+"+mov.title;
    mov.money_earned=this->money_earned+money_earned;
    return mov;
}

// Supraincarcare operator +=
Movie Movie::operator+=(int x){
    this->money_earned+=x;
    return *this;
}

// Supraincarcare operator + (cu un int, la dreapta)
Movie Movie::operator+(int x){
    Movie aux(*this);
    aux.money_earned=aux.money_earned+x;
    return aux;
}

// Supraincarcare operator + (cu int, la stanga)
Movie operator+(int x, Movie mov){
    mov.money_earned=mov.money_earned+x;
    return mov;
}

// Supraincarcare operator - (intre filme)
Movie Movie::operator-(Movie mov){
    mov.title=this->title+"-"+mov.title;
    mov.money_earned=this->money_earned-money_earned;
    return mov;
}

// Supraincarcare operator -=
Movie Movie::operator-=(int x){
    this->money_earned-=x;
    return *this;
}

// Supraincarcare operator - (cu un int, la dreapta)
Movie Movie::operator-(int x){
    Movie aux(*this);
    aux.money_earned=aux.money_earned-x;
    return aux;
}

// Supraincarcare operator - (cu int, la stanga)
Movie operator-(int x, Movie mov){
    mov.money_earned=mov.money_earned-x;
    return mov;
}

// Supraincarcare operator []
string Movie::operator[](int index){
    if (0 <= index && index < 3)
        return this->type[index];
    cout << "Index introdus gresit";   
}

// Supraincarcarea operatorului>>
istream &operator>>(istream &in, Movie &mov){
    cout<<"\nTitle: ";
    in.get();
    getline(in, mov.title); // sa faci sa citesti tota linia
    if(mov.type!=NULL)
        delete[] mov.type;
    mov.type=new string[3];
    cout<<"\nType: \n";
    for(int i=0; i<3; i++){
        cout<<i+1<<". ";
        in>>mov.type[i];
    }
    cout<<"\nDescription: \n";
    in.get();
    getline(in, mov.description);
    cout<<"\nNo companies working with this movie: ";
    in>>mov.no_companies;
    if(mov.c!=NULL)
        delete[] mov.c;
    mov.c=new Company[mov.no_companies];
    for(int i=0; i<mov.no_companies; i++){
        cout<<"\n   ~About companie no: "<<i+1<<"\n"; 
        in>>mov.c[i];
    }

    cout<<"\nNo actors playing in this movie: ";
    in>>mov.no_actors;
    if(mov.a!=NULL)
        delete[] mov.a;
    mov.a=new Actor[mov.no_actors];
    for(int i=0; i<mov.no_actors; i++){
        cout<<"\n   ~About actor no: "<<i+1<<"\n"; 
        in>>mov.a[i];
    }
}

// Supraincarcarea operatorului<<
ostream &operator<<(ostream &out, Movie &mov){
    out<<"\n   "<<"Movie\n";
    out<<"---> "<<mov.title<<"\n";
    out<<"Type: ";
    for(int i=0; i<3; i++){
        out<<"\n"<<i+1<<". "<<mov.type[i];
    }
    out<<"\nDescription: \n"<<mov.description<<"\n";
    out<<"Seen: ";
    out<<(mov.seen ? "yes" : "no")<<"\n";
    out<<"No views: "<<mov.no_views<<"\n\n";

    out<<*mov.c;

    out<<*mov.a;

    out<<"\nMoney earned: "<<mov.money_earned<<"$\n\n";

    return out;
}

// Functionalitate - film: updateaza numarul de vizualizari, suma de bani castigate si daca a fost vazut sau nu filmul
// Preincrementare
const Movie &Movie::operator++(){
    this->seen=true;
    this->no_views++;
    this->money_earned=this->no_views*view_price;
    return *this;
}

//  Setteri
void Movie::setCount_id(int count_id){
    this->count_id=count_id;
}
void Movie::setTitle(string title) {
    this->title=title;
}
void Movie::setDescription(string description) {
 	this->description=description;
}
void Movie::setType(string type, int i) {    
    this->type[i]=type[i];
}   
void Movie::setNo_views(int no_views) {
    this->no_views=no_views;
}   
void Movie::setSeen(bool seen) {
	this->seen=seen;
} 
void Movie::setNo_actors(int no_actors) {
    this->no_actors=no_actors;
}    
void Movie::setNo_companies(int no_companies) {
   	this->no_companies=no_companies;
}
void Movie::setMoney_earned(double money_earned) {
    this->money_earned=money_earned;
}

//  Getteri
int Movie::getMovie_id(){
    return this->movie_id;
}
int Movie::getCount_id(){
    return Movie::count_id;
}
string Movie::getTitle(){
	return this->title;
}
string Movie::getDescription() {
	return this->description;
}
int Movie::getNo_views(){
    return no_views;
}
const string* Movie::getType() const {
	return this->type;
}
int Movie::getNo_companies(){
    return this->no_companies;
}
int Movie::getNo_actors(){
    return this->no_actors;
}
Actor &Movie::getActor(int i){
    return this->a[i];
}
Company &Movie::getCompany(int i){
    return this->c[i];
}
int Movie::getView_price(){
    return view_price;
}

//  Show
void Movie::show(int const space){
    cout<<movie_id<<". "<<title;    for(int i=0; i<space-(title.length())-strlen("1. "); i++) cout<<" ";
    cout<<type[0]<<", "<<type[1]<<", "<<type[2]; 
    for(int j=0; j<12+space-(type[0].length()+type[1].length()+type[2].length()-strlen(", , ")); j++) cout<<" ";
    // dc +12? inca nu stiu, dar se aliniaza corect asa
    if(seen){
        cout<<"Yes";   for(int i=0; i<space-strlen("Yes"); i++) cout<<" "; 
    }
    else{
        cout<<"No";   for(int i=0; i<space-strlen("No"); i++) cout<<" ";         
    }
    cout<<no_views;
    cout<<endl;
}

// Functionalitate - companii: calculeaza valoarea medie a contractelor companiilor de la un film
int Movie::avg_company(){
    int n=0;
    for(int i=0; i<this->no_companies; i++)
        n+=this->c[i].getContract().getPrice();
    n/=this->no_companies;
    return n;
}

// Functionalitate - actori: calculeaza valoarea medie a contractelor actorilor dintr un film
int Movie::avg_actor(){
    int n=0;
    for(int i=0; i<this->no_actors; i++)
        n+=this->a[i].getContract().getPrice();
    n/=this->no_actors;
    return n;
}

// Static
int Movie::count_id=0;
int Movie::view_price=2;

// Vector de filme
Movie *n_movie;

// Functia afiseaza un tabel cu datele filmelor
void movie_table(){
    int n=Movie::getCount_id(); // n retine exact cate filme sunt in biblioteca
    int const space=20;
    cout<<endl;
    cout<<"    Title";  for(int i=0; i<space-strlen("    Title"); i++) cout<<" ";
    cout<<"    Type";   for(int i=0; i<space-strlen("    Type"); i++) cout<<" ";
    for(int i=0; i<space; i++) cout<<" ";
    cout<<"Seen";   for(int i=0; i<space-strlen("Seen"); i++) cout<<" ";
    cout<<"No views";
    cout<<endl;
    for(int i=0; i<n; i++){
        n_movie[i].show(space);
    }
}

// delete_movie nu functioneaza
void delete_movie(int i){

    movie_table();
}

void Delete(){
    int i;
    movie_table();
    cout<<"\n-> Selectati numarul filmului pe care doriti sa il stergeti: ";
    cin>>i; 
    delete_movie(i);
}

void edit(int i){
    int no;
    string title, type, description;
    i--;    // trecem in sistemul de numerotare care incepe de la 0
    do{
        cout<<"\nCe doriti sa editati la acest film?\n1. Titlul\n2. Type 1\n3. Type 2\n4. Type 3\n5. Description\n0. Am terminat de editat\nNo:";
        cin>>no;
        if(no==1){
            cout<<"\nIntroduceti noul titlu: ";
            cin.get();
            getline(cin, title);
            n_movie[i].setTitle(title);
        }
        if(no==2){
            cout<<"\nIntroduceti noul gen: ";
            cin.get();
            getline(cin, type);
            n_movie[i].setType(type, 0);
        }
        if(no==2){
            cout<<"\nIntroduceti noul gen: ";
            cin.get();
            getline(cin, type);
            n_movie[i].setType(type, 1);
        }
        if(no==2){
            cout<<"\nIntroduceti noul gen: ";
            cin.get();
            getline(cin, type);
            n_movie[i].setType(type, 2);
        }
        if(no==5){
            cout<<"\nIntroduceti noua descriere: ";
            cin.get();
            getline(cin, description);
            n_movie[i].setDescription(description);
        }
        cout<<"\nS-a actualizat filmul:\n";
        n_movie[i].show(20); 
    }while(no!=0);

}

void Update(){
    int i;
    movie_table();
    cout<<"\n-> Selectati numarul filmului pe care doriti sa il editati: ";
    cin>>i; edit(i);
}

void open_movie(Movie &mov){
    int i, j;
    cout<<mov;
    do{
        cout<<"Doriti sa aflati:\n1. Valoarea medie a contractelor companiilor\n2. Valoarea medie a contractelor actorilor\n";
        cout<<"3. Venitul lunar al unei companii\n4. Venitul lunar al unui actor\n0. Back\n";
        cin>>i;
        if(i==1){
            cout<<"\nValoarea medie a contractelor comapniilor din filmul "<<mov.getTitle()<<" este: "<<mov.avg_company()<<"$";
        }
        if(i==2){
            cout<<"\nValoarea medie a contractelor actorilor din filmul "<<mov.getTitle()<<" este: "<<mov.avg_actor()<<"$";
        }
        if(i==3){
            cout<<"\nAlegeti numarul companiei dorite: ";
            cin>>j;
            cout<<"\nCompania "<<mov.getCompany(j-1).getName()<<" are un venit lunar de: "<<mov.getCompany(j-1).getContract().avg()<<"$";
        }
        if(i==4){
            cout<<"\nAlegeti numarul actorului dorit: ";
            cin>>j;
            cout<<"\nActorul "<<mov.getActor(j-1).getName()<<" are un venit lunar de: "<<mov.getActor(j-1).getContract().avg()<<"$";
        }
        cout<<endl<<endl;
    }while(i!=0);

}

void play_movie(Movie &mov){
    int n=mov.getTitle().length();
    int mid=(strlen("-  ")*16/2);
    int dif=n/2;
    int ok=0;
    for(int i=0; i<9; i++){
        for(int j=0; j<16; j++){
            if(i==4){
                for(int k=0; k<mid-dif; k++)
                    cout<<" ";
                    cout<<mov.getTitle();
                    break;
                }
            cout<<"-  ";
        }
        cout<<endl;
    }
    ++mov;
}

void Read(){
    int n=Movie::getCount_id(); // n retine exact cate filme sunt in biblioteca
    int choise_movie, choise_action;
    movie_table();

    do{
        cout<<"\n-> Selectati numarul filmului: ";
        cin>>choise_movie;
    }while(choise_movie<1 || choise_movie>n);
    choise_movie--; // scadem 1 ca sa folosim contorul de vectori

    do{
        cout<<"\n   Selectati o optiune:\n1. Open movie details\n2. Play movie\n0. Back\n";
        cin>>choise_action;
        if(choise_action==1){
            open_movie(n_movie[choise_movie]);
        }
        if(choise_action==2){ // afisam titlul in mijlocul unui 'ecran' de 16:9 format din "-  "
            play_movie(n_movie[choise_movie]);
        }
    }while(choise_action!=1 && choise_action!=2 && choise_action!=0);

}

// Functia auto_fill este facuta sa completeze automat datele companiei, a actorilor si contractele
// aceasta se asigura si sa nu existe dubluri
// insa din pacate, nu este functionala inca:
// folosim functia mai slaba aufo_fill_constr (care nu verifica si clonele)
/*
void auto_fill(Movie &mov){
    int n=Movie::getCount_id();       // referinta ca sa modificam si id-ul
    n--;    // scadem cu 1 ca sa obtinem nr ultimului film (id-ul incepe de la 1, dar numeroatarea in vector incepe de la 0)
    int no_companies=mov.getNo_companies();   // numarul de companii care lucreaza cu ultimul film citit
    int no_actors=mov.getNo_actors();         // numarul de actori care lucreaza cu ultimul film citit
    int clona=0;

    for(int i=0; i<n; i++){ 
        if(mov==n_movie[i]){
            //delete_movie(i);
            cout<<"ERROR: Acest film exista deja! \n Vreti sa folositi functia [edit] pentru acest film?";
            edit(n);
            break; // dupa ce am gasit un film clona, nu mai cautam
        }
    }
    for(int k=0; k<no_companies; k++){ // parcurgem fiecare companie din ultimul film citit
        clona=0;
        if(k>=1) // noi am initializat numarul de companii cu 1, nu incrementam daca filmul are doar o companie, e deja numarul potrivit
            ++mov.getCompany(no_companies-k-1);
        for(int i=0; i<n; i++){ // parcurgem fiecare film
            for(int j=0; j<n_movie[i].getNo_companies(); j++){ // parcurgem fiecare companie din film
                if(mov.getCompany(no_companies-k-1)==n_movie[i].getCompany(j)){ // verificam daca compania exista deja
                    // in preincrementarea companiei crestem numarul de filme si nr de contracte cu 1
                    if(n>=1){
                        ++mov.getCompany(no_companies-k-1);
                        ++n_movie[i].getCompany(j);
                    }
                    mov.getCompany(no_companies-k-1).setMovies(mov.getTitle());   // adaugam titlul filmului in lista cu filme a companiei
                    n_movie[i].getCompany(j).setMovies(mov.getTitle());         // adaugam titlul filmului in lista cu filme a companiei
                    clona=1;
                }
            }
        }
        mov.getCompany(no_companies-k-1).setMovies(mov.getTitle());   // adaugam titlul filmului in lista cu filme a companiei
        // nu este nevoie sa crestem nr de filme, a fost initializat oricum cu 1
        mov.getCompany(no_companies-k-1).getContract().setMovie(mov.getTitle());  // afaugam titlul fimului in contract
        mov.getCompany(no_companies-k-1).getContract().setName(mov.getCompany(no_companies-k).getName());   // adaugam numele firmei in contract
    }

    for(int k=0; k<no_actors; k++){ // parcurgem fiecare companie din ultimul film citit
        clona=0;
        if(k>=1) // noi am initializat numarul de companii cu 1, nu incrementam daca filmul are doar o companie, e deja numarul potrivit
            ++mov.getActor(no_actors-k-1);
        for(int i=0; i<n; i++){ // parcurgem fiecare film
            for(int j=0; j<n_movie[i].getNo_actors(); j++){ // parcurgem fiecare actor din film
                if(mov.getActor(no_actors-k-1)==n_movie[i].getActor(j)){ // verificam daca actorul exista deja
                    // in preincrementarea actorului crestem numarul de filme si nr de contracte cu 1
                    ++mov.getActor(no_actors-k-1);
                    ++n_movie[i].getActor(j);
                    mov.getActor(no_actors-k-1).setMovies(mov.getTitle());   // adaugam titlul filmului in lista cu filme a actorului
                    n_movie[i].getActor(j).setMovies(mov.getTitle());         // adaugam titlul filmului in lista cu filme a actorului
                    clona=1;
                    //break;
                }
            }
            if(clona){
                //break;
            }
        }
        mov.getActor(no_actors-k-1).setMovies(mov.getTitle());   // adaugam titlul filmului in lista cu filme a actorului
        // nu este nevoie sa crestem nr de filme, a fost initializat oricum cu 1
        mov.getActor(no_actors-k-1).getContract().setMovie(mov.getTitle());  // afaugam titlul fimului in contract
        mov.getActor(no_actors-k-1).getContract().setName(mov.getActor(no_actors-k-1).getName()); // adaugam numele actorului in contrat
    }

}
*/

void auto_fill_constr(Movie &mov){

    int no_companies=mov.getNo_companies();   // numarul de companii care lucreaza cu ultimul film citit
    int no_actors=mov.getNo_actors();         // numarul de actori care lucreaza cu ultimul film citit
    
    for(int i=0; i<no_companies; i++){
        // in preincrementarea companiei crestem numarul de filme si nr de contracte cu 1
        if(i>=1) // noi am initializat numarul de companii cu 1, nu incrementam daca filmul are doar o companie, e deja numarul potrivit
            ++mov.getCompany(no_companies-i-1);
        mov.getCompany(no_companies-i-1).setMovies(mov.getTitle());   // adaugam titlul filmului in lista cu filme a companiei
        mov.getCompany(no_companies-i-1).getContract().setMovie(mov.getTitle());  // afaugam titlul fimului in contract
        mov.getCompany(no_companies-i-1).getContract().setName(mov.getCompany(no_companies-i-1).getName());   // adaugam numele firmei in contract
    }
    
    for(int i=0; i<no_actors; i++){
        // in preincrementarea companiei crestem numarul de filme si nr de contracte cu 1
        if(i>=1) // noi am initializat numarul de companii cu 1, nu incrementam daca filmul are doar o companie, e deja numarul potrivit
            ++mov.getActor(no_actors-i-1);
        mov.getActor(no_actors-i-1).setMovies(mov.getTitle());   // adaugam titlul filmului in lista cu filme a companiei
        mov.getActor(no_actors-i-1).getContract().setMovie(mov.getTitle());  // afaugam titlul fimului in contract
        mov.getActor(no_actors-i-1).getContract().setName(mov.getActor(no_actors-i-1).getName());   // adaugam numele firmei in contract
    }

}

void Create(){
    /*
    int n=Movie::getCount_id(); // n retine exact cate filme sunt in biblioteca
    cout<<"\nn="<<n<<endl;
    Movie *aux;
    aux=new Movie[n+1]; // lasam loc si pt filmul care urmeaza sa fie citit
    for(int i=0; i<n; i++){
        aux[i]=n_movie[i];
    }
    if(n_movie!=NULL){
        delete[] n_movie;
    }
    cout<<"\n     Se creaza filmul\n";
    cin>>aux[n];
    aux[n].setCount_id(0);
    n_movie=new Movie[n+1]; 
    for(int i=0; i<n+1; i++)
        n_movie[i]=aux[i]; 
    delete[] aux;   
    //auto_fill(n_movie[n]);
    */

    cin>>n_movie[2]; 
    n_movie[2].setCount_id(Movie::getCount_id()+1);
    auto_fill_constr(n_movie[2]);
}

// Meniu
void Meniu(){
    int casenr;
    do{
        cout<<"\n     Selectati comanda dorita:\n1. Create\n2. Read\n3. Update\n4. Delete\n0. STOP\n Nr: ";
        cin>>casenr;
        if(casenr==1)
            Create();
        if(casenr==2)
            Read();
        if(casenr==3)
            Update();
        if(casenr==4)
            Delete();
    }while (casenr!=0);
}

int main(){
    int age;
    n_movie=new Movie[3];

    n_movie[0].setCount_id(0);
    Contract c_comp1_mov1(26, 7, 2019, true, 6, double(21000));
    Contract c_act1_mov1(14, 11, 2020, true, 8, double(4000));
    Company comp1_mov1("MARVEL", &c_comp1_mov1);
    age=52;
    Actor act1_mov1("Robert Downey Jr.", "M", &age, 1.74, &c_act1_mov1);
    string type1[3]={"Actiune", "Aventura", "Comedie"};
    Movie m1("Avengers", "Un film bun", type1, 1, 1, &act1_mov1, &comp1_mov1);
    n_movie[0]=m1;
    Contract c_comp1_mov2(2, 3, 2009, false, 12, double(7000));
    Contract c_act1_mov2(21, 12, 2021, true, 24, double(9200));
    Company comp1_mov2("DC", &c_comp1_mov2);
    age=40;
    Actor act1_mov2("Margot Robbie", "F", &age, 1.72, &c_act1_mov2);
    string type2[3]={"Aventura", "Actiune", "Drama"};
    Movie m2("Batman", "Alt film bun", type2, 1, 1, &act1_mov2, &comp1_mov2);
    n_movie[1]=m2;
    auto_fill_constr(n_movie[0]);
    auto_fill_constr(n_movie[1]);

    Meniu();

    return 0;
    
}