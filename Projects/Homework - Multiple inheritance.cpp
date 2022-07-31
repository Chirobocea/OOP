#include <iostream>

using namespace std;

class CitireAfisare{
public:
    virtual istream& Citire(istream&)=0;
    virtual ostream& Afisare(ostream&)const=0;
};


//  ---Persoana---
class Persoana:public CitireAfisare{
private:
    string nume, cnp;
public:
    Persoana();
    Persoana(string nume, string cnp);
    Persoana(const Persoana& p);
    Persoana& operator=(const Persoana& p);
    ~Persoana(){}

    virtual istream& Citire(istream&);
    virtual ostream& Afisare(ostream&)const;

    friend istream& operator>>(istream& in, Persoana& p);
    friend ostream& operator>>(ostream& out, const Persoana& p);

    string getNume(){return this->nume;}
    string getCnp(){return this->cnp;}
};

Persoana::Persoana(){
    this->nume="-";
    this->cnp="-";
}

Persoana::Persoana(string nume, string cnp){
    this->nume=nume;
    this->cnp=cnp;
}

Persoana::Persoana(const Persoana& p){
    this->nume=p.nume;
    this->cnp=p.cnp;
}

Persoana& Persoana::operator=(const Persoana& p){
    if(this!=&p){
        this->nume=p.nume;
        this->cnp=p.cnp;
    }
    return *this;
}

istream& Persoana::Citire(istream& in){
    cout<<"Nume: ";
    in>>this->nume;
    cout<<"CNP: ";
    in>>this->cnp;
    return in;
}

ostream& Persoana::Afisare(ostream& out)const{
    out<<"Nume: "<<this->nume<<"\n";
    out<<"CNP: "<<this->cnp<<"\n";
    return out;
}

istream& operator>>(istream& in, Persoana& p){
    return p.Citire(in);
}

ostream& operator<<(ostream& out, const Persoana& p){
    return p.Afisare(out);
}

//  ---Angajat---
class Angajat:virtual public Persoana{
protected:
    string functie;
public:
    Angajat();
    Angajat(string functie);
    Angajat(string nume, string cnp, string functie);
    Angajat(const Angajat& a);
    Angajat& operator=(const Angajat& a);
    ~Angajat(){}

    istream& Citire(istream&);
    ostream& Afisare(ostream&)const;

    friend istream& operator>>(istream& in, Angajat& a);
    friend ostream& operator>>(ostream& out, const Angajat& a);\

    string getFunctie(){return this->functie;}
};

Angajat::Angajat():Persoana(){
    this->functie="-";
}

Angajat::Angajat(string functie):Persoana(){
    this->functie=functie;
}

Angajat::Angajat(string nume, string cnp, string functie):Persoana(nume, cnp){
    this->functie=functie;
}

Angajat::Angajat(const Angajat& a):Persoana(a){
    this->functie=a.functie;
}

Angajat& Angajat::operator=(const Angajat& a){
    if(this!=&a){
        Persoana::operator=(a);
        this->functie=a.functie;
    }
    return *this;
}

istream& Angajat::Citire(istream& in){
    Persoana::Citire(in);
    cout<<"Functie: ";
    in>>this->functie;
    return in;
}

ostream& Angajat::Afisare(ostream& out)const{
    Persoana::Afisare(out);
    out<<"Functie: "<<this->functie<<"\n";
    return out;
}

istream& operator>>(istream& in, Angajat& a){
    return a.Citire(in);
}

ostream& operator<<(ostream& out, const Angajat& a){
    return a.Afisare(out);
}

//  ---Student---
class Student:virtual public Persoana{
protected:
    string facultate;
public:
    Student();
    Student(string facultate);
    Student(string nume, string cnp, string facultate);
    Student(const Student& s);
    Student& operator=(const Student& s);
    ~Student(){}

    istream& Citire(istream&);
    ostream& Afisare(ostream&)const;

    friend istream& operator>>(istream& in, Student& s);
    friend ostream& operator>>(ostream& out, const Student& s);

    string getFacultate(){return this->facultate;}
};

Student::Student():Persoana(){
    this->facultate="-";
}

Student::Student(string facultate):Persoana(){
    this->facultate=facultate;
}

Student::Student(string nume, string cnp, string facultate):Persoana(nume, cnp){
    this->facultate=facultate;
}

Student::Student(const Student& s):Persoana(s){
    this->facultate=s.facultate;
}

Student& Student::operator=(const Student& s){
    if(this!=&s){
        Persoana::operator=(s);
        this->facultate=s.facultate;
    }
    return *this;
}

istream& Student::Citire(istream& in){
    Persoana::Citire(in);
    cout<<"Facultate: ";
    in>>this->facultate;
    return in;
}

ostream& Student::Afisare(ostream& out)const{
    Persoana::Afisare(out);
    out<<"Facultate: "<<this->facultate<<"\n";
    return out;
}

istream& operator>>(istream& in, Student& s){
    return s.Citire(in);
}

ostream& operator<<(ostream& out, const Student& s){
    return s.Afisare(out);
}

//  ---AngajatStudent---
class AngajatStudent:public Angajat, public Student{
private:
    bool practica;
public:
    AngajatStudent();
    AngajatStudent(string facultate, string functie, bool practica);
    AngajatStudent(string nume, string cnp, string facultate, string functie, bool practica);
    AngajatStudent(const AngajatStudent& as);
    AngajatStudent& operator=(const AngajatStudent& as);
    ~AngajatStudent(){}

    istream& Citire(istream&);
    ostream& Afisare(ostream&)const;

    friend istream& operator>>(istream& in, AngajatStudent& as);
    friend ostream& operator>>(ostream& out, const AngajatStudent& as);

    bool getPractica(){return this->practica;}

};

AngajatStudent::AngajatStudent():Angajat(), Student(){
    this->practica=false;
}

AngajatStudent::AngajatStudent(string facultate, string functie, bool practica):Angajat(functie), Student(facultate){
    this->practica=practica;
}

AngajatStudent::AngajatStudent(const AngajatStudent& as):Angajat(as), Student(as){
    this->practica=as.practica;
}

AngajatStudent& AngajatStudent::operator=(const AngajatStudent& as){
    if(this!=&as){
        Angajat::operator=(as);
        Student::operator=(as);
        this->practica=as.practica;
    }
    return *this;
}

istream& AngajatStudent::Citire(istream& in){
    Persoana::Citire(in);
    cout<<"Facultate: ";
    in>>this->facultate;
    cout<<"Functie: ";
    in>>this->functie;
    cout<<"Practica [yes/no]: ";
    string aux;
    in>>aux;
    if(aux=="yes")
        this->practica=true;
    else
        this->practica=false;
    return in;
}

ostream& AngajatStudent::Afisare(ostream& out)const{
    Persoana::Afisare(out);
    out<<"Functie: "<<this->functie<<"\n"; 
    out<<"Facultate: "<<this->facultate<<"\n";
    out<<"Practica: ";
    if(this->practica)
        out<<"yes\n";
    else
        out<<"no\n";
    return out;
}

istream& operator>>(istream& in, AngajatStudent& as){
    return as.Citire(in);
}

ostream& operator>>(ostream& out, const AngajatStudent& as){
    return as.Afisare(out);
}


int main(){
    Persoana* listaPersoane[100];
    int i=0;
    int k=1;

    while(k==1){
        cout<<"\n 1. Pentru a adauga o Persoana ";
        cout<<"\n 2. Pentru a adauga un Student ";
        cout<<"\n 3. Pentru a adauga un Angajat ";
        cout<<"\n 4. Pentru a adauga un Stundent Angajat ";
        cout<<"\n 5. Pentru a afisa persoanele ";
        cout<<"\n 6. Stop ";
        cout<<endl;

        int comanda;
        cin>>comanda;
        
        switch(comanda){
            case 1:{
                listaPersoane[i]=new Persoana();
                cin>>*listaPersoane[i];
                i++;
                break;
            }
            case 2:{
                listaPersoane[i]=new Student();
                cin>>*listaPersoane[i];
                i++;
                break;
            }
            case 3:{
                listaPersoane[i]=new Angajat();
                cin>>*listaPersoane[i];
                i++;
                break;
            }
            case 4:{
                listaPersoane[i]=new AngajatStudent();
                cin>>*listaPersoane[i];
                i++;
                break;
            }
            case 5:{
                for(int j=0; j<i;j++)
                    cout<<*listaPersoane[j]<<endl;
                break;
            }
            case 6:{
                k=0;
                break;
            }
        }

    }

    return 0;       
}