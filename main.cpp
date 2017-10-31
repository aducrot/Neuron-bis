#include "neuron.hpp"
#include <iostream>
#include <cassert>
#include <random>

using namespace std;

void random_connection(vector <Neuron>& neuron_sim, int const CE, int const CI, int const nb_exc, int const nb_inh);

int main()
{
	double t_stop (1000);
	double h (0.1);
	double simtime (0);
	int number_Neuron_sim;
	cout << "how many neurons must be generated?" << endl;
	cin >> number_Neuron_sim;

	double nb_exc = 0.8*number_Neuron_sim;
	double nb_inh = 0.2*number_Neuron_sim;

	int const Excitory_neuron_nb (static_cast<int>(nb_exc));
	int const Inhibitory_neuron_nb (static_cast<int>(nb_inh));


	double CE_temp = 0.1*Excitory_neuron_nb;
	double CI_temp =0.1*Inhibitory_neuron_nb;

	int const CE (static_cast<int>(CE_temp));
	int const CI (static_cast<int>(CI_temp));

	ofstream out;
	out.open("spiketime.txt");

	if(out.fail())
	{
		cout<< "the file failed to open correctly"<<endl;
	} else{

		vector< Neuron > Neurons; //!< vector of all neurons in simulation
		//!< initialisation of the neurons in the simulation: exhibitory and inhibitory
		for (int i(0); i< Excitory_neuron_nb; ++i)
		{
			Neuron n;
			n.setBool();
			Neurons.push_back(n);
			//cout << "Excitory_neuron neuron" << i+1<< endl;
		}

		for (int j(0); j< Inhibitory_neuron_nb; ++j)
		{
			Neuron n;
			Neurons.push_back(n);
			//cout << "Inhibitory_ neuron" << j+1<< endl;
		}

		cout<< "the neuron simulation vector has been generated"<<endl;

		//<! making the connections between the neurons
		random_connection(Neurons,CE,CI,Excitory_neuron_nb,Inhibitory_neuron_nb);

		cout<< "the connections have been made"<<endl;

		while (simtime<t_stop)
		{
			for (size_t i(0); i<Neurons.size(); ++i)
			{
				Neurons[i].update(simtime,Neurons);
			}
			simtime+=h;
		}

		for (size_t i(0); i< Neurons.size(); ++i)
		{
			for(auto time: Neurons[i].getSpiketime())
			{
				out << time << '\t' <<i<< '\n';
			}
		}
		cout<< "end of program"<<endl;
	}

out.close();
return 0;

}

void random_connection(vector <Neuron>& neuron_sim, int const CE, int const CI, int const nb_exc, int const nb_inh)
{

	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<int> distr(0,nb_exc-1);

	random_device rd2;
	mt19937 eng2(rd2());
	uniform_int_distribution<int> distr2(nb_exc+1,nb_exc+nb_inh-1);

 cout << "neuorn sim sizee: "<< neuron_sim.size()<<endl;
 cout << "CE" << CE <<endl;
 cout << "CI" << CI << endl;

	for (size_t i(0); i< neuron_sim.size(); ++i)
	{
		//!< uses index associated with neuron
		for (int j(0); j< CE; ++j)
		{
			neuron_sim[i].setConnexion(distr(eng));
		}

		for (int k(0); k<CI; ++k)
		{
			neuron_sim[i].setConnexion(distr2(eng2));
		}
		//neuron_sim[i].setConnexion(connexion_matrix);
	}
}
