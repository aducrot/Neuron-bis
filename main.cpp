#include "neuron.hpp"
#include <iostream>
#include <cassert>
#include <random>

using namespace std;

void random_connection(vector<Neuron> neuron_sim, int const CE, int const CI, int const nb_exc, int const nb_inh);

int main()
{
	double t_stop (1000);
	double h (0.1);
	double simtime (0);
	int number_Neuron_sim;
	cout << "how many neurons must be generated?" << endl;
	cin >> number_Neuron_sim;
	int const Excitory_neuron_nb (0.8*number_Neuron_sim);
	int const Inhibitory_neuron_nb (0.2*number_Neuron_sim);
	int const CE (0.1*Excitory_neuron_nb);
	int const CI (0.1*Inhibitory_neuron_nb);

	vector< Neuron > Neurons (number_Neuron_sim); //! vector of all neurons in simulation

	//! initialisation of the neurons in the simulation: exhibitory and inhibitory
	for (int i(0); i< Excitory_neuron_nb; ++i)
	{
		Neuron n;
		Neurons.push_back(n);
	}

	for (int j(0); j< Inhibitory_neuron_nb; ++j)
	{
		Neuron n;
		Neurons.push_back(n);
	}
	cout<< "the neuron simulation tableau has been generated"<<endl;

	//! making the connections between the neurons
	random_connection(Neurons,CE,CI,Excitory_neuron_nb,Inhibitory_neuron_nb);
	cout<< "the connections have been made"<<endl;

	while (simtime<t_stop)
	{
		for (int i(0); i<Neurons.size(); i++)
		{
			Neurons[i].update(simtime);
		}
		simtime+=h;
	}
	cout<< "end of program"<<endl;
	return 0;
}

void random_connection(vector <Neuron> neuron_sim, int const CE, int const CI, int const nb_exc, int const nb_inh)
{
	for (int i(0); i< neuron_sim.size(); ++i)
	{
		vector <Neuron> connexion_matrix (CE+CI);
		for (int j(0); j< CE; j++)
		{
			random_device rd;
			mt19937 eng(rd());
			uniform_int_distribution<int> distr(0,nb_exc);
			connexion_matrix.push_back(neuron_sim[distr(eng)]);
			neuron_sim[j].setConnexion(connexion_matrix);
		}
		for (int k(0); k<CI; k++)
		{
			random_device rd;
			mt19937 eng(rd());
			uniform_int_distribution<int> distr(nb_exc+1,nb_exc+nb_inh);
			connexion_matrix.push_back(neuron_sim[distr(eng)]);
			neuron_sim[k].setConnexion(connexion_matrix);
		}
	}

}
