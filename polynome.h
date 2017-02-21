// PROJET REALISEE PAR QASSOU Mohamed et PETIT Maximilien
#ifndef POLYNOME_H_INCLUDED
#define POLYNOME_H_INCLUDED
#include <map>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>

template <typename T>
class Polynome;

template <typename T>
std::ostream& operator<<(std::ostream& os,  Polynome<T>& poly);

template <typename T>
class Polynome
{
private:
    std::map <int,T> mymap;

public:
    Polynome();
    Polynome(const Polynome<T>& poly);
    Polynome(std::vector<int>& coef);
    Polynome(std::map<int,T>& assoc);
    ~Polynome();

    void setMymap(int degre,T coef);

    std::string afficherPolynome();
    void derive(Polynome<T>& poly);
    void composition(Polynome<T>& poly);
    T eval(int x);
    static bool correcteur_syntaxique(std::string poly);

    friend std::ostream& operator<< <T>(std::ostream& os,  Polynome<T>& poly);
    T operator[](const T i){return mymap[i];} // surcharge de l'opérateur " [] "
    Polynome<T>& operator+=( Polynome<T>& poly);
    Polynome<T>& operator-=( Polynome<T>& poly);
    Polynome<T>& operator*=( Polynome<T>& poly);
    Polynome<T>& operator*=( int scalaire);
    Polynome<T>& operator=(std::string poly);

    Polynome<T> operator+( Polynome<T>& poly);
    Polynome<T> operator-( Polynome<T>& poly);
    Polynome<T> operator*( Polynome<T>& poly);
    Polynome<T> operator%( Polynome<T>& poly);
    Polynome<T> operator*( int scalaire);


};

/////  constructeur par defaut ////
template <typename T>
Polynome<T>::Polynome()
{
    mymap[0]=0;
}

/////  constructeur par copie ////
template <typename T>
Polynome<T>::Polynome(const Polynome<T>& poly)
{
    typename   std::map<int,T>::const_iterator it;
    for(it=poly.mymap.begin(); it!=poly.mymap.end(); it++)
    {
        mymap[(*it).first]=(*it).second;

    }
}

/////  CONSTRUCTEUR TABLEAU DE COEF ////
template <typename T>
Polynome<T>::Polynome(std::vector<int>& coef)
{
    for (int unsigned i = 0; i<coef.size(); i++)
    {
        mymap[i]=coef[i];
    }
}
/////  CONSTRUCTEUR TABLEAU associatif ////
template <typename T>
Polynome<T>::Polynome(std::map<int,T>& assoc)
{
    typename  std::map<int,T>::const_iterator it;
    for(it=assoc.begin(); it!=assoc.end(); it++)
    {
        this->mymap[(*it).first]=(*it).second;

    }

}

///// DESTRUCTEUR ////
template <typename T>
Polynome<T>::~Polynome()
{

}


/////  METHODE setMymap ////
template <typename T>
void Polynome<T>::setMymap( int degre,T coef)
{
    mymap[degre]=coef;
}

/////  SURCHARGE OPERATEUR "<<"  ////
template <typename T>
std::ostream& operator<<(std::ostream& os,  Polynome<T>& poly)
{
    os << poly.afficherPolynome();
    return os;
}
/////  SURCHARGE OPERATEUR +=  ////
template <typename T>
Polynome<T>&  Polynome<T>::operator+=( Polynome<T>& poly)
{
    typename   std::map<int,T>::const_iterator it_poly;
    typename   std::map<int,T>::const_iterator it;
    Polynome<T> copie;
    copie=*this;
    int drapeau=0;

    for(it_poly=poly.mymap.begin(); it_poly!=poly.mymap.end(); it_poly++)
    {

        for(it=mymap.begin(); it!=mymap.end(); it++)
        {

            if((*it).first==(*it_poly).first)
            {

                copie.mymap[(*it).first]= mymap[(*it).first]+ poly.mymap[(*it_poly).first];
                drapeau=1;
            }

        }


        if(drapeau==0)
        {
            copie.mymap[(*it_poly).first]=(*it_poly).second;
        }
        drapeau=0;
    }

    *this=copie;

    return *this;
}
/////  SURCHARGE OPERATEUR -=  ////
template <typename T>
Polynome<T>&  Polynome<T>::operator-=( Polynome<T>& poly)
{

    typename   std::map<int,T>::const_iterator it_poly;
    typename   std::map<int,T>::const_iterator it;
    Polynome<T> copie;
    copie=*this;
    int drapeau=0;

    for(it_poly=poly.mymap.begin(); it_poly!=poly.mymap.end(); it_poly++)
    {

        for(it=mymap.begin(); it!=mymap.end(); it++)
        {

            if((*it).first==(*it_poly).first)
            {

                copie.mymap[(*it).first]= mymap[(*it).first]-poly.mymap[(*it_poly).first];
                drapeau=1;

            }
        }

        if(drapeau==0)
        {
            copie.mymap[(*it_poly).first]=-(*it_poly).second;
        }
        drapeau=0;
    }

    *this=copie;

    return *this;
}
/////  SURCHARGE OPERATEUR *=  ////
template <typename T>
Polynome<T>&  Polynome<T>::operator*=( Polynome<T>& poly)
{

    typename   std::map<int,T>::const_iterator it_poly;
    typename   std::map<int,T>::const_iterator it;
    Polynome<T> copie,copie2;



    for(it_poly=poly.mymap.begin(); it_poly!=poly.mymap.end(); it_poly++)
    {
        copie.mymap.clear();
        for(it=mymap.begin(); it!=mymap.end(); it++)
        {

            copie.mymap[(*it).first+(*it_poly).first]= mymap[(*it).first]*poly.mymap[(*it_poly).first];

        }
        copie2+=copie;
    }
    *this=copie2;

    return *this;
}

/////  SURCHARGE OPERATEUR *=   PAR UN SCALAIRE ////
template <typename T>
Polynome<T>&  Polynome<T>::operator*=(int scalaire)
{

    typename   std::map<int,T>::const_iterator it;

    for(it=mymap.begin(); it!=mymap.end(); it++)
    {

        mymap[(*it).first]= mymap[(*it).first] *scalaire;

    }

    return *this;
}


/////  METHODE correcteur_syntaxique ////
template <typename T>
 bool Polynome<T>::correcteur_syntaxique(std::string poly)
 {
bool erreur=false;
char comparer='0';
int i=0,compteur=0, compteur2=0;
std::map <char,int> caractere;
std::map<char,int>::const_iterator it;
caractere['^']=0;
caractere['x']=0;
caractere['.']=0;
caractere['-']=0;
caractere['+']=0;
  try
    {
        for(i=0;i<poly.size();i++)
        {

            if(isdigit(poly[i]))
               {
                   compteur2++;

                if(i+1==poly.size() && compteur2==1)
                   {
                    throw std::string("ERREUR : Vous n'avez mis qu'un chiffre, precisez en ajoutant ^degre");
                   }
                }


            if(!isdigit(poly[i]))
               {
                   compteur++;
                   if(i+1==poly.size() && compteur==1)
                   {
                    throw std::string("ERREUR : Vous n'avez mis qu'un symbole, precisez en ajoutant coeffx^degre");
                   }

                   if(poly[i]=='x' && i==0)
                   {
                    throw std::string("ERREUR : Veuillez rajouter le coefficient devant x");
                   }

                    if(poly[i-1]!='x' && poly[i]=='^')
                        {
                        throw std::string("ERREUR : Vous ne pouvez pas ecrire deux symboles de suite autre que 'x^'");
                        }

                    if(poly[i]=='x' && poly[i+1]!='^')
                        {
                        throw std::string("ERREUR : Vous ne pouvez pas ecrire deux symboles de suite autre que 'x^'");
                        }

                   if(!isdigit(poly[i+1]) && i+1!=poly.size())
                   {
                    if(poly[i]!='x' && poly[i+1]!='^')
                        {
                        throw std::string("ERREUR : Vous ne pouvez pas ecrire deux symboles de suite autre que 'x^'");
                        }
                    if(poly[i]=='x' && poly[i+1]!='^')
                        {
                        throw std::string("ERREUR : Vous ne pouvez pas ecrire deux symboles de suite autre que 'x^'");
                        }
                   }



                    switch(poly[i])
                    {
                        case '^':caractere['^']+=1;
                                if(caractere['^']==2)
                                {
                                throw std::string("ERREUR : Vous ne pouvez pas ecrire '^^'");
                                }
                                 break;

                        case 'x':caractere['x']+=1;
                                if(caractere['x']==2)
                                {
                                throw std::string("ERREUR : Vous ne pouvez pas ecrire 'xx'");
                                }
                                 break;

                        case '.':caractere['.']+=1;
                                if(caractere['.']==2)
                                {
                                throw std::string("ERREUR : Vous ne pouvez pas ecrire '..'");
                                }
                                 break;

                        case '-':caractere['-']+=1;
                                if(caractere['-']==2)
                                {
                                throw std::string("ERREUR : Vous ne pouvez pas ecrire '--'");
                                }
                                 break;

                        case '+':caractere['+']+=1;
                                if(caractere['+']==2)
                                {
                                throw std::string("ERREUR : Vous ne pouvez pas ecrire '++'");
                                }
                                 break;
                        default:
                                 break;
                        }

                for(it=caractere.begin(); it!=caractere.end(); it++)
                    {
                        if(caractere['^']==1  && i+1==poly.size())
                           {
                            throw std::string("ERREUR : Vous devez mettre au moins une valeur pour le degre'");
                           }

                    }

               }
               else
               {
                for(it=caractere.begin(); it!=caractere.end(); it++)
                    {
                        caractere[(*it).first]=0;
                    }

               }





        }


       return erreur;
   }
   catch(std::string const& chaine)
   {
       std::cerr << chaine << std::endl;
       erreur=true;
       return erreur;
   }

 }

/////  METHODE afficherPolynome ////
template <typename T>
std::string Polynome<T>::afficherPolynome()
{
    typename   std::map<int,T>::const_iterator it;
    std::stringstream degre,coef;
    std::string resultat;
    int drapeau=0;
    for(it=mymap.begin(); it!=mymap.end(); it++)
    {
        coef.str("");
        degre.str("");
        if((*it).second!=0)
        {
            if((*it).second<0)
            {
                coef<<(*it).second;
                degre<<(*it).first;
                if((*it).first==0)
                {
                    resultat=resultat+coef.str();
                }
                else
                {
                    resultat=resultat+coef.str()+"x^"+degre.str();
                }
            }
            else if((*it).second>=0 && drapeau==1)
            {
                coef<<(*it).second;
                degre<<(*it).first;

                if((*it).first==0)
                {
                    resultat=resultat+coef.str();
                }
                else
                {
                    resultat=resultat+coef.str()+"x^"+degre.str();
                }
                drapeau=0;
            }
            else if(drapeau==0)
            {
                coef<<(*it).second;
                degre<<(*it).first;
                if((*it).first==0)
                {
                    resultat=resultat+coef.str();
                }
                else
                {
                    resultat=resultat+"+"+coef.str()+"x^"+degre.str();
                }
            }
        }
        else
        {
            drapeau=1;
        }
    }
    return resultat;

}

/////  METHODE derive ////
template <typename T>
void Polynome<T>::derive(Polynome<T>& poly)
{

    typename   std::map<int,T>::const_iterator it;
    for(it=mymap.begin(); it!=mymap.end(); it++)
    {

        poly.mymap[(*it).first-1]=((*it).second)*((*it).first);

        // std::cout<<polyDerive<<std::endl;
    }

}

/////  METHODE composition ////
template <typename T>
void Polynome<T>::composition(Polynome<T>& poly)
{
    Polynome<T> copie,copie2;

    typename   std::map<int,T>::const_iterator it;
    typename   std::map<int,T>::const_iterator it_poly;
    int i=0;
    for(it=mymap.begin(); it!=mymap.end(); it++)
    {

        for(it_poly=poly.mymap.begin(); it_poly!=poly.mymap.end(); it_poly++)
        {
            copie.mymap.clear();
            copie=poly;
            if((*it).second!=0)
            {
                if((*it).first==1)
                {
                    copie*=(*it).second;
                }
                else if((*it).first>1)
                {
                    for(i=1; i<(*it).first; i++)
                    {
                        copie*=poly;
                    }
                    copie*=(*it).second;
                }
            }
            else
            {
                copie*=0;
            }
        }
        copie2+=copie;
    }
    *this=copie2;

}

// EVAL
template <typename T>
T Polynome<T>::eval(int x)
{
    T resultat = 0;
    typename   std::map<int,T>::const_iterator it;
    for(it=mymap.begin(); it!=mymap.end(); it++)
    {
        resultat += pow(x,(*it).first)*mymap[(*it).first];
    }
    std::cout << "Le resultat du polynome pour la valeur " << x << " est " << resultat <<std::endl;
    return resultat;
}





// SURCHARGE OPERATEUR +
template <typename T>
Polynome<T> Polynome<T>::operator+( Polynome<T>& poly)
{
    typename   std::map<int,T>::const_iterator it_poly;
    typename   std::map<int,T>::const_iterator it;
    Polynome<T> somme;

    for(it_poly=poly.mymap.begin(); it_poly!=poly.mymap.end(); it_poly++)
    {

        for(it=mymap.begin(); it!=mymap.end(); it++)
        {
            if((*it).first==(*it_poly).first)
            {
                somme.mymap[(*it).first] = mymap[(*it).first] + poly.mymap[(*it_poly).first];
            }
            else if (((*it).first==0) && ((*it_poly).first!=0))
            {
                somme.mymap[(*it_poly).first] = poly.mymap[(*it_poly).first];
            }
            else if (((*it).first!=0) && ((*it_poly).first==0))
            {
                somme.mymap[(*it).first] = mymap[(*it).first];
            }
        }
    }
    return somme;
}



// SURCHARGE OPERATEUR -
template <typename T>
Polynome<T> Polynome<T>::operator-( Polynome<T>& poly)
{
    typename   std::map<int,T>::const_iterator it_poly;
    typename   std::map<int,T>::const_iterator it;
    Polynome<T> soustraction;

    for(it_poly=poly.mymap.begin(); it_poly!=poly.mymap.end(); it_poly++)
    {

        for(it=mymap.begin(); it!=mymap.end(); it++)
        {
            if((*it).first==(*it_poly).first)
                soustraction.mymap[(*it).first] = mymap[(*it).first] - poly.mymap[(*it_poly).first];
            else if (((*it).first==0) && ((*it_poly).first!=0))
            {
                soustraction.mymap[(*it_poly).first] = - poly.mymap[(*it_poly).first];
            }
            else if (((*it).first!=0) && ((*it_poly).first==0))
            {
                soustraction.mymap[(*it).first] = mymap[(*it).first];
            }
        }
    }
    return soustraction;
}


// SURCHARGE OPERATEUR *
template <typename T>
Polynome<T> Polynome<T>::operator*( Polynome<T>& poly)
{
    typename   std::map<int,T>::const_iterator it_poly;
    typename   std::map<int,T>::const_iterator it;
    Polynome<T> resultat;
    Polynome<T> produit;

    for(it_poly=poly.mymap.begin(); it_poly!=poly.mymap.end(); it_poly++)
    {
        resultat.mymap.clear();
        for(it=mymap.begin(); it!=mymap.end(); it++)
        {
            resultat.mymap[(*it).first+(*it_poly).first] = mymap[(*it).first] * poly.mymap[(*it_poly).first];
        }
        produit+=resultat;
    }
    return produit;
}


//////// SURCHARGE OPERATEUR % DIVISION EUCLIDIENNE //////
template <typename T>
Polynome<T> Polynome<T>::operator%( Polynome<T>& diviseur)
{

int fin=0,compare_degre=0, coef_max_reste=0,coef_max_diviseur=0,valeur_max_diviseur = 0;
    Polynome<T> dividende=*this;
    Polynome<T> produit;
    Polynome<T> copie_produit;
    Polynome<T> resultat;
    Polynome<T> soustraire;
    int reste=0;
    int test = 0;
    typename   std::map<int,T>::const_iterator it;

    try{
    for(it=diviseur.mymap.begin(); it!=diviseur.mymap.end(); it++)
    {
      if((*it).first>compare_degre)
      {
          compare_degre=(*it).first;
          coef_max_diviseur=(*it).first;
          valeur_max_diviseur=(*it).second;
      }
    }
    if(valeur_max_diviseur == 0){
           throw std::string("Impossible de diviser par 0 !");
          }
    else{
    compare_degre=0;
    while(!fin)
    {
        compare_degre=0;
        reste=0;
             for(it=dividende.mymap.begin(); it!=dividende.mymap.end(); it++)
                {
                  if((*it).first>compare_degre && dividende.mymap[(*it).first]!=0)
                  {
                      compare_degre=(*it).first;
                      coef_max_reste=(*it).first;
                  }
                  if(dividende.mymap[(*it).first]!=0)
                  {
                      reste=1;
                  }
                }

                if(coef_max_reste<coef_max_diviseur || reste==0)
                {
                    fin=1;
                      std::cout<<"Dividende : "<<*this<<"| diviseur :"<<diviseur<<std::endl<<std::endl;
                      if(reste==0)
                      {
                        std::cout<<"Reste : 0 "<<"| quotient :"<<copie_produit<<std::endl<<std::endl;
                      }
                      else
                        {
                        std::cout<<"Reste : "<<dividende<<"| quotient :"<<copie_produit<<std::endl<<std::endl;
                        }


                    resultat=(copie_produit*diviseur);
                    resultat+=dividende;
                    return resultat;
                }

                produit.mymap[coef_max_reste-coef_max_diviseur]=dividende.mymap[coef_max_reste]/diviseur.mymap[coef_max_diviseur];
                copie_produit+=produit;
                soustraire=produit*diviseur;
                dividende-=soustraire;
                produit.mymap.clear();
    }
    }

    return resultat;
    }
    catch(std::string const& message)
    {
       std::cerr << message << std::endl;
    }
}


// SURCHARGE OPERATEUR * SCALAIRE
template <typename T>
Polynome<T> Polynome<T>::operator*( int scalaire)
{
    typename   std::map<int,T>::const_iterator it;
    Polynome<T> produit;

    for(it=mymap.begin(); it!=mymap.end(); it++)
    {
        {
            produit.mymap[(*it).first] = mymap[(*it).first] * scalaire;
        }
    }
    return produit;
}

//// SURCHARGE OPERATEUR =  pour l'interpréteur ////
template <typename T>
Polynome<T>& Polynome<T>::operator=(std::string poly)
{
    // poly.size() nombre exacte de caractere
    //nos variables
    int unsigned i=0,j=0, taille_map;
    char comparer, signe='-';
    int drapeau=0, drapeau_fin=0,degre=0,result;
    double multiplieur;
    std::map <int,double> tab_entier;
    std::map <int,double> tab_decimal;
    std::map <int,double> tab_degre;
    typename std::map<int,T>::const_iterator it;
    std::string lecture;
    Polynome<T> poly_lecture;
    //fin variables


    for(i=0; i<poly.size()+1; i++)
    {
        comparer=poly[i];
        if(comparer==signe)
            {
                signe='1';
            }
        if(comparer=='.')
        {
            drapeau=1;
            taille_map=tab_entier.size();
            multiplieur=1;

            for(j=1; j<taille_map; j++)
            {
                multiplieur*=10;
            }

            for(it=tab_entier.begin(); it!=tab_entier.end(); it++)
            {
                poly_lecture.mymap[0]+=(multiplieur*(*it).second);
                multiplieur*=0.1;
            }
        }
        else
        {
            if(isdigit(poly[i]) && drapeau==0 && drapeau_fin==0)
            {
                lecture=poly[i];
                std::stringstream ss(lecture);
                ss >> result ;
                if(signe=='1')
                    {
                    tab_entier[i]=result*-1;
                    }
                else
                    {
                        tab_entier[i]=result;
                    }
            }
        }

        if(comparer=='x')
        {
            if(drapeau==1)
            {
                multiplieur=0.1;
                taille_map=tab_decimal.size();

                for(it=tab_decimal.begin(); it!=tab_decimal.end(); it++)
                {
                    poly_lecture.mymap[0]+=(multiplieur*(*it).second);
                    multiplieur*=0.1;

                }
            }
            else
                {
                    taille_map=tab_entier.size();
                    multiplieur=1;

                    for(j=1; j<taille_map; j++)
                    {
                        multiplieur*=10;

                    }

                    for(it=tab_entier.begin(); it!=tab_entier.end(); it++)
                    {
                        poly_lecture.mymap[0]+=(multiplieur*(*it).second);
                        multiplieur*=0.1;
                    }
                }
        }
        else
        {
            if(isdigit(poly[i]) && drapeau==1 && drapeau_fin==0)
            {
                lecture=poly[i];
                std::stringstream ss(lecture);
                ss >> result ;

                  if(signe=='1')
                    {
                    tab_decimal[i]=result*-1;
                    }
                else
                    {
                      tab_decimal[i]=result;
                    }
            }

        }

        if(comparer=='^')
        {
            drapeau_fin=1;

        }
        else
        {
            if(isdigit(poly[i]) && drapeau_fin==1)
            {
                lecture=poly[i];
                std::stringstream ss(lecture);
                ss >> result ;
                tab_degre[i]=result;
            }

            else if(!isdigit(poly[i]) && drapeau_fin==1  )
            {
                taille_map=tab_degre.size();
                multiplieur=1;

                for(j=1; j<taille_map; j++)
                {
                    multiplieur*=10;

                }
                degre=0;
                for(it=tab_degre.begin(); it!=tab_degre.end(); it++)
                {
                    degre+=(multiplieur*(*it).second);
                    multiplieur*=0.1;
                }
                poly_lecture.mymap[degre]=poly_lecture.mymap[0];
                if(degre!=0)
                {
                 poly_lecture.mymap[0]=0;
                }

                drapeau=0;
                drapeau_fin=0;
                tab_entier.clear();
                tab_decimal.clear();
                tab_degre.clear();
                if(comparer=='-')
                {
                    signe='1';
                }
                else
                {
                    signe='-';
                }

            }
        }
    }
    *this=poly_lecture;
    return *this;

}





#endif // POLYNOME_H_INCLUDED
