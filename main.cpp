#include "neuron.cpp"
//#include <random>

using namespace std;

int main()
{
	double t_stop (1000);
	double h (0.1);
	double simtime (0);
	double Iext1;
	double Iext2;
	//auto Iext=unifrom_int_distribution<> (0,400);
	cout<< "what is the intensity of the current Iext for the 1st neuron? the value should be between 0 and 400 pA."<< endl;
	//gestion d'erreur a ajouter
	cin>> Iext1;
	cout<< "what is the intensity of the current Iext for the 1st neuron? the value should be between 0 and 400 pA."<< endl;
	//gestion d'erreur a ajouter
	cin>> Iext2;
	//double threshold (20);

	Neuron N_1;
	Neuron N_2;
	double n;
	n=(N_1.getTauxRefractory()/h);
  ofstream out1;
	ofstream out2;
  out1.open("potential1.txt");
	out2.open("potential2.txt");
	bool hh (true);

    if (out1.fail())
    {
        cout<<"Erreur, the file was not opened"<<endl;
    } else if (out2.fail())
		{
			cout<<"Erreur, the file was not opened"<<endl;
		} else {

      while (simtime<t_stop)
        {
            N_1.update(Iext1,simtime,N_2.getisSpiking());
						out1<<N_1.getPotential()<<endl;
						cout<< "N1 spiking status:" << N_1.getisSpiking()<<endl;
						N_2.update(Iext2,simtime,N_1.getisSpiking());
						out2<<N_2.getPotential()<<endl;
						cout<< "N2 spiking status:" << N_2.getisSpiking()<<endl;
          	simtime +=h;
        }

        cout << "the neuron 1 spiked :"<<N_1.getSpikecount()<<" times"<< endl;
				cout<< "the neuron 2 spiked :"<<N_2.getSpikecount()<<" times"<<endl;
    }

	out1.close();
	out2.close();

	return 0;
}
