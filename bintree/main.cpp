#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

void kiir(vector<string> vektor);
void kiir2(vector<int> vektor);

    struct Elem
    {
        int adat;
        Elem* bal;
        Elem* jobb;
    };

    Elem* Level_Letrehoz(int ertek)
    {
        Elem* uj = new Elem;
        uj->adat = ertek;
        uj->bal = uj->jobb = NULL;
        return uj;
    }

    Elem* gyoker = Level_Letrehoz(2);
    Elem* kov_elem = gyoker;

    Elem* Level_Hozzaad(int ertek, Elem* &act_elem)
    {
        if(act_elem->bal == NULL && ertek == 0)    {act_elem->bal=Level_Letrehoz(ertek);return kov_elem=gyoker;}
        else if(act_elem->jobb == NULL && ertek == 1)    {act_elem->jobb=Level_Letrehoz(ertek);return kov_elem=gyoker;}
        else if(act_elem->bal != NULL && ertek == 0 )  {return kov_elem=act_elem->bal;}
        else if(act_elem->jobb != NULL && ertek == 1)    {return kov_elem=act_elem->jobb;}
    }

    int Elemszam(Elem* &act_elem)
    {
        int elemszam=1;
        if(act_elem->bal != NULL)   {elemszam+=Elemszam(act_elem->bal);}
        if(act_elem->jobb != NULL)       {elemszam+=Elemszam(act_elem->jobb);}
        return elemszam;
    }

    int Magassag(Elem* &act_elem)
    {
        if (act_elem == NULL) return 0;
        else
        {
            int bal = Magassag(act_elem->bal);
            int jobb = Magassag(act_elem->jobb);
            if (bal > jobb)
            return bal + 1;
            else    return jobb + 1;
        }
    }

    int osszeg;
    int Osszeg(Elem* &act_elem)
    {
        if(act_elem-> bal != NULL)      Osszeg(act_elem->bal);
        if(act_elem->jobb != NULL)      {osszeg++; Osszeg(act_elem->jobb);}
        return osszeg ;
    }

    int agak_szama;
    int Agak_szama(Elem* &act_elem)
    {
        if(act_elem->bal != NULL)   Agak_szama(act_elem->bal);
        if(act_elem->jobb != NULL)  Agak_szama(act_elem->jobb);
        if(act_elem->bal == NULL && act_elem->jobb == NULL)     agak_szama++;
        return agak_szama;
    }

    vector<int> preorder;
    vector<int> Preorder(Elem* &act_elem, vector<int> &vektor)
    {
            vektor.push_back(act_elem->adat);
            if(act_elem->bal != NULL)         Preorder(act_elem->bal,vektor);
            if(act_elem->jobb != NULL)        Preorder(act_elem->jobb,vektor);
            return vektor;
    }

    bool agak_kiir=false;
    float agak_hossza_szum;
    vector<int> agak_hosszai;
    void Ag_Kiir ( Elem* &act_elem, vector<int> ag, int ag_hossz);
    void Ag(Elem* &act_elem)
    {
        vector<int> ag;
        Ag_Kiir(act_elem, ag, 0);
    }

     void Ag_Kiir (Elem* &act_elem, vector<int> ag, int ag_hossz)
    {
        ag.push_back(act_elem->adat);
        if(act_elem->bal == NULL && act_elem->jobb == NULL)
        {
            if(agak_kiir == true)
            {
                for(int i =1; i<ag.size(); i++)
                {cout<<ag.at(i);}
                cout<<endl;
            }
            agak_hossza_szum += (ag.size()-1);
            agak_hosszai.push_back(ag.size()-1);
        }
        else
        {
            if(act_elem->bal !=NULL) {ag_hossz++; Ag_Kiir(act_elem->bal, ag, ag_hossz);}
            if(act_elem->jobb !=NULL) {ag_hossz++; Ag_Kiir(act_elem->jobb, ag, ag_hossz);}
        }
    }

int main(int argc, char** argv)
{
    //FAJL BEOLVASASA
    fstream myfile(argv[1], ios_base::in);
	vector<int> vektor;
	int tmpvalt;
   	while (myfile >> tmpvalt)
   	{
        vektor.push_back(tmpvalt);
	}
    vector<string> fajl_elemei;
    string a;
    while(cin>>a)
    {
        fajl_elemei.push_back(a);
    }
  /*  cout<< "A fajl tartalma: ";
    kiir(fajl_elemei);*/

    //BEOLVASOTT ELEMEK ELTÁROLÁSA
    vector<int> beolvasott_elemek;
    for(int i=0; i<fajl_elemei.size(); i++)
    {
        string act_elem = fajl_elemei.at(i);
        for(int j=0; j<act_elem.length(); j++)
        {
            if(act_elem.at(j) == '0')
            {
                beolvasott_elemek.push_back(0);
            }
            else if(act_elem.at(j) == '1')
            {
                beolvasott_elemek.push_back(1);
            }
        }
    }

    //BEOLVASOTT ELEMEK KIIRASA
    if(beolvasott_elemek.size() <= 1000)
    {
        cout<< "A  beolvasott adatok: ";
        kiir2(beolvasott_elemek);
    }
    else
    {
        cout<<"A beolvasott adatok szama meghaladja az ezret."<<'('<< beolvasott_elemek.size()<<')'<<endl;
    }

    //FA LETREHOZASA
    for(int i=0; i<beolvasott_elemek.size(); i++)
    {
        Level_Hozzaad(beolvasott_elemek.at(i),kov_elem);
    }

    //FA ELEMSZAMA
    cout<< "Fa elemszama: "<<Elemszam(gyoker)<<endl;

    //FA MAGASSAGA
    cout<<"Fa magassaga: "<<Magassag(gyoker)<<endl;

    //FA ELEMEINEK ATLAGA
    float atlag = (float)Osszeg(gyoker) / (float)(Elemszam(gyoker)-1);
    cout<<"Fa elemeinek atlaga: "<<atlag<<endl;

    //FA AGAINAK SZAMA
    float ag_db = (float)Agak_szama(gyoker);
    cout<<"Fa againak szama: "<< ag_db <<endl;

    //FA ELEMEI PREORDER
    if(beolvasott_elemek.size() <= 1000)
    {
        preorder=Preorder(gyoker, preorder);
        cout<< "Fa elemei preorder: " << endl;
        for(int i=1; i<preorder.size(); i++)
        {
            cout<< preorder.at(i);
            if(i%20 == 0 && i !=0)  cout<<endl;
        } cout<<endl;
    }

    //FA AGAI
    if(agak_szama <= 50)
    {
        agak_kiir = true;
        cout<<"A fa agai: "<<endl;
        Ag(gyoker);
    }
    else
    {
        agak_kiir = false;
        cout<< "A fa againak szama meghaladja az 50-et."<< '('<< agak_szama<<')'<< endl;
        Ag(gyoker);
    }

    //FA AGAINAK ATLAGOS HOSSZA
    float agak_atlagos_hossza= agak_hossza_szum / ag_db;
    cout<< "Fa againak atlagos hossza: "<<agak_atlagos_hossza<<endl;

    //FA AGAINAK SZORASA
    float szoras_szum;
    for(int i=0; i<agak_hosszai.size(); i++)
    {
        szoras_szum += pow(agak_hosszai.at(i)-agak_atlagos_hossza,2);
    }
    cout<<"Agak hosszanak szorasa(tapasztalati szoras): "<< pow(szoras_szum/ag_db,0.5)<<endl;
    cout<<"Agak hosszanak szorasa(korrigalt tapasztalati szoras): "<< pow(szoras_szum/(ag_db-1),0.5)<<endl;

    return 0;
}


void kiir(vector<string> vektor)
{
    cout<<endl;
    for(int i=0; i< vektor.size(); i++)
    {
        cout<< vektor.at(i) << " ";
        if( i%19 ==0 && i>0 )
        {
            cout<< endl;
        }
    }
    cout<<endl;
}

void kiir2(vector<int> vektor)
{
    cout<<endl;
    for(int i=0; i<vektor.size(); i++)
    {
        cout<< vektor.at(i);
        if( i%19 ==0 && i>0 )
        {
            cout<< endl;
        }
    }
    cout<<endl;
}
