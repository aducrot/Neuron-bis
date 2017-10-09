#include "neuron.cpp"
//#include <random>

using namespace std;

int main()
{
	double t_stop (1000);
	double h (0.1);
	double simtime (0);
	double Iext;
	//auto Iext=unifrom_int_distribution<> (0,400);
	cout<< "what is the intensity of the current Iext? the value should be between 0 and 400 pA."<< endl; //gestion d'erreur a ajouter
	cin>> Iext;
	double threshold (20);

	Neuron N_1;
	double n;
	n=(N_1.getTauxRefractory()/h);
    ofstream out;
    out.open("potential.txt");

    if (out.fail())
    {
        cout<<"Erreur, the file was not opened"<<endl;
    } else {

      while (simtime<t_stop)
        {
            N_1.update(Iext,h,threshold,simtime,n,out);
            simtime +=h;
        }

        cout << "the neuron spiked :"<<N_1.getSpikecount()<<" times"<< endl;
    }

	out.close();

	return 0;
}
