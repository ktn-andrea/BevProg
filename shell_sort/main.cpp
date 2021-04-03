//c++11
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void kiir(vector<int> vektor)
{
    cout<<endl;
    for(int i =0; i< vektor.size(); i++)
    {
        cout<< vektor.at(i) << " ";
        if( i %10 ==0 && i>0 )
        {
            cout<< endl;
        }
    }
    cout<<endl;
}

vector<int> rendez(vector<int> &vektor)
{
    vector<int> LK{100,30,8,3,1};
    for(int k=0; k<LK.size(); k++)
    {
        int lepeskoz= LK.at(k);
        for(int eltolas =0; eltolas<lepeskoz; eltolas++)
        {
            int i= lepeskoz+eltolas;
            while(i < vektor.size())
            {
                int kulcs = vektor.at(i);
                int j = i-lepeskoz;
                while(j>= 0 && vektor.at(j) > kulcs)
                {
                    vektor.at(j+lepeskoz) = vektor.at(j);
                    j=j-lepeskoz;
                }
                vektor.at(j+lepeskoz) = kulcs;
                i=i+lepeskoz;
            }
        }
    }
    return vektor;
}


int main(int argc, char** argv)
{
	fstream myfile(argv[1], ios_base::in);
	vector<int> vektor;
	int tmpvalt;
   	while (myfile >> tmpvalt)
   	{
        vektor.push_back(tmpvalt);
	}

  	vector<int> Vektor;

    int a;
    while(cin>>a)
    {
        Vektor.push_back(a);
    }

    cout<< "Input adatok: ";
    kiir(Vektor);

    rendez(Vektor);

    cout<< "Rendezett adatok: ";
    kiir(Vektor);

    return 0;
}

