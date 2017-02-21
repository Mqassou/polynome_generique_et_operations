// PROJET REALISEE PAR QASSOU Mohamed et PETIT Maximilien
#include "polynome.h"

using namespace std;

int main()
{

// POLYNOME A TESTER //
Polynome<int> s;
Polynome<int> d;

s.setMymap(1,3);
s.setMymap(2,3);
s.setMymap(3,1);

d.setMymap(1,2);

// POLYNOME QUI INITIALISENT NOS POLYNOMES A LEURS VALEURS DE DEPART //
Polynome<int> s_ini(s);
Polynome<int> d_ini(d);

cout<<endl<<endl<<"============= Fonction s = "<<s<<endl;
cout<<"============= Fonction d = "<<d<<endl<<endl;

// // // // // // // // // // // // // // // //
s*=d;
cout<<"////SURCHARGE *= >>>>>  s*=d ////"<<endl<<"resultat : "<<s<<endl<<endl;
s=s_ini;

s=s*d;
cout<<"////SURCHARGE *  >>>>> s=s*d ////"<<endl<<"resultat : "<<s<<endl<<endl;
s=s_ini;

// // // // // // // // // // // // // // // //
cout<<"=================================="<<endl;

cout<<"////SURCHARGE [] >>>>> s[2] ////"<<endl<<"resultat : "<<s[2]<<endl<<endl;

cout<<"=================================="<<endl;
// // // // // // // // // // // // // // // //
cout<<"=================================="<<endl;

s+=d;
cout<<"///SURCHARGE +=  >>>>>  s+=d ////"<<endl<<"resultat : "<<s<<endl<<endl;
s=s_ini;

s=s+d;
cout<<"////SURCHARGE +  >>>>> s=s+d ////"<<endl<<"resultat : "<<s<<endl<<endl;
s=s_ini;

// // // // // // // // // // // // // // // //
cout<<"=================================="<<endl;

s-=d;
cout<<"////SURCHARGE -= >>>>> s-=d ////"<<endl<<"resultat : "<<s<<endl<<endl;
s=s_ini;

s=s-d;
cout<<"////SURCHARGE  - >>>>> s=s-d ////"<<endl<<"resultat : "<<s<<endl<<endl;
s=s_ini;

// // // // // // // // // // // // // // // //
cout<<"=================================="<<endl;


s*=3;
cout<<"////SURCHARGE  *= avec scalaire >>>>> s*=3 ////"<<endl<<"resultat : "<<s<<endl<<endl;
s=s_ini;

s=s*3;
cout<<"//// SURCHARGE * avec scalaire >>>>> s=s*3 ////"<<endl<<"resultat : "<<s<<endl<<endl;
s=s_ini;

// // // // // // // // // // // // // // // //
cout<<"=================================="<<endl;


s.derive(d);
cout<<"//// METHODE derive  >>>>> s.derive(d) ////"<<endl<<"Polynome initial : "<<s<<endl<<"Polynome derive : "<<d<<endl<<endl;
d=d_ini;


d.composition(s);
cout<<"////METHODE composition  >>>>> d.composition(s)  ////"<<endl<<"d(s)= "<<d<<endl<<endl;
d=d_ini;


cout<<"////METHODE eval >>>>> s.eval(3)  ////"<<endl<<endl;
s.eval(3);
s=s_ini;

vector<int> vect;
map<int,int> map1;
map1[2]=64;
map1[12]=6;
map1[2]=18;
map1[0]=22;
map1[4]=14;
map1[5]=2;

vect.push_back( 0 );
vect.push_back( 5 );
vect.push_back( 10 );
vect.push_back( 15 );
vect.push_back( 20 );

cout<<"=================================="<<endl;
cout<<"=================================="<<endl<<endl<<endl;

cout<<"//// Constructeur par copie  ////"<<endl;
Polynome<int> c(s);
cout<<c<<endl<<endl;

cout<<"//// Constructeur avec tableau de coefficient  ////"<<endl;
Polynome<int> v(vect);
cout<<v<<endl<<endl;

cout<<"//// Constructeur avec tableau associatif  ////"<<endl;
Polynome<int> m(map1);
cout<<m<<endl<<endl;


//////////////////////////////////////////////////////////////////
//////////////////////// PARTIE 2 : INTERPRETEUR /////////////////
//////////////////////////////////////////////////////////////////
cout<<"||||||||||||||||||||||||||||||||||||"<<endl;
cout<<"|||||||||||| INTERPRETEUR ||||||||||"<<endl;
cout<<"||||||||||||||||||||||||||||||||||||"<<endl<<endl;

Polynome<double> P;
Polynome<double> Q;
Polynome<double> R;
string polia;

cout<<"Veuillez entre le polynome P "<<endl;
cin>>polia;

bool erreur =Polynome<double>::correcteur_syntaxique(polia);
while(erreur)
{
cin>>polia;
erreur =Polynome<double>::correcteur_syntaxique(polia);
}

P=polia;
cout<<"P(x)="<<P<<endl;


cout<<"Veuillez entre le polynome R "<<endl;
cin>>polia;

erreur =Polynome<double>::correcteur_syntaxique(polia);
while(erreur)
{
cin>>polia;
erreur =Polynome<double>::correcteur_syntaxique(polia);
}

Q=polia;
cout<<"Q(x)="<<Q<<endl<<endl;

cout<<"////SURCHARGE % division euclidienne >>>>> Q%P ////"<<endl<<endl;
Q%P;

R=P+Q;
cout<<"R= P+Q"<<endl;
cout<<"R="<<R<<endl<<endl;

R=P-Q;
cout<<"R= P-Q"<<endl;
cout<<"R="<<R<<endl<<endl;

R=P*Q;
cout<<"R= P*Q"<<endl;
cout<<"R="<<R<<endl<<endl;

R=P*3;
cout<<"R= P*3"<<endl;
cout<<"R="<<R<<endl<<endl;




return 0;
}
