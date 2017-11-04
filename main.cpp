#include "neuron.hpp"
#include <iostream>
#include <cassert>
#include <random>

using namespace std;

void random_connection(vector <Neuron>& neuron_sim, int const CE, int const CI,
												int const nb_exc, int const nb_inh);//!< method that will generate random connections.
												//!<The values generated will correspond to the neurons index and will be stored in
												//!< the neuron's attribut connected_with_.

int main()
{
	double g;
	double eta;
	double t_stop (100);//!< total simulation time
	double h (0.1);//!< time step
	double simtime (0);//!< Simulation time
	int number_Neuron_sim;//!<numbers of neurons in the simulation
	cout << "how many neurons must be generated?" << endl;
	cin >> number_Neuron_sim;
	cout << "what is the value of nu_ext/nu_threshold ?"<<endl;
	cin >> eta;
	cout<< "what is the weight of the inhibitory neuorns (g)?" <<endl;
	cin >> g;

	assert (g>=0);
	assert (eta>=0);

	double nb_exc = 0.8*number_Neuron_sim;
	double nb_inh = 0.2*number_Neuron_sim;

	int const Excitory_neuron_nb (static_cast<int>(nb_exc));//!< number of Excitory neurons in the simulation
	int const Inhibitory_neuron_nb (static_cast<int>(nb_inh));//!< number of Inhibitory neurons in the simulation


	double CE_temp = 0.1*Excitory_neuron_nb;
	double CI_temp =0.1*Inhibitory_neuron_nb;

	int const CE (static_cast<int>(CE_temp));//!< number of excitory connections per neuron
	int const CI (static_cast<int>(CI_temp));//!< number of inhibitory connections per neuron

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
			n.setBool();//!< the neurons are by default inhibitory
			n.setEta_(eta);
			Neurons.push_back(n);
		}

		for (int j(0); j< Inhibitory_neuron_nb; ++j)
		{
			Neuron n;
			n.setJ_(g);//!< the J by default was Je(excitory =0.1)
			n.setEta_(eta);
			Neurons.push_back(n);
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

void random_connection(vector <Neuron>& neuron_sim, int const CE, int const CI,
												int const nb_exc, int const nb_inh)
{
	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<int> distr(0,nb_exc-1);//!<the range is as large as
																					//!<the number of excitory neurons.
																					//!<it corresponds to the indeces of excitory
																					//!<neurons in the vector Neuron_sim

	random_device rd2;
	mt19937 eng2(rd2());
	uniform_int_distribution<int> distr2(nb_exc+1,nb_exc+nb_inh-1);//!<the range is as large as
																					//!<the number of inhibitory neurons.
																					//!<it corresponds to the indeces of
																					//!<inhibitory neurons in the vector Neuron_sim

	for (size_t i(0); i< neuron_sim.size(); ++i)
	{
		//!< uses index associated with neuron
		for (int j(0); j< CE; ++j)
		{
			neuron_sim[i].setConnexion(distr(eng));
		}

		for (int k(0); k<CI; ++k)
		{
			neuron_sim[i].setConnexion(distr2(eng2)); //!< sets the attribut connected_with_
		}
	}
}
