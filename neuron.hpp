#ifndef NEURON_H
#define NEURON_H
using namespace std;
#include <vector>
#include <fstream>

class Neuron
{
	private:
	double potential_; //!< membrane potential of the neuron
	double h_; //!< time step of simulation in ms
	double Iext_; //!< external current- used when their is no backdroung stimulation
	int spikecount_; //!< count keeper of the numbers of spike generated by the neuron
	vector <double> spikeTime_; //!< vector that keeps track of the spike timees of the neurons in ms
	double taux_; //!< temps caracteristique taux=Resistance*C
	double tauxRefractory_; //!< refractory time in ms
	double conductivity_; //!< mebrane conductivity
	double Res_; //!< membrane resistance
	int clock_; //!< neuron internal clock to keep track of time- number of h steps
	bool isSpiking_; //!< boolean test to know if the neuron has spiked.
	int Delay_; //!< Delay time initialised in contructor in number of time steps
	vector <int> Buffer_; //!< keeps track of the number of spikes received at each time step
	double J_; //!< the potential increase of the mebran whne it receives a spike (including from rest of the brain)
	double threshold_;//!< membrane potential above which the neuron spikes
	double ref_time_;//!< refractory time in time steps
	vector <int> connected_with_;//!< neurons that are connected with it using their index
	bool isExcitory;

	public:
	//!<constructor and destructor
	Neuron ();
	~Neuron ();

	//!< Getteurs et Setteurs
	double getPotential() const;
	int getSpikecount() const;
	vector <double> getSpiketime() const;
	double getTaux() const;
	double getTauxRefractory() const;
	double getRes() const;
	double getConductivity() const;
	int getClock() const;
	bool getisSpiking() const;
	vector<int> getConnection() const;

	void setPotential(double p);
	void setSpikecount ();
	void setSpikeTime(double t);
	void setRes(double r);
	void setConductivity(double c);
	void setIsSpiking(bool answer);
	void setClock(double t);
	void setConnexion (int const neuron_index);
	void setBuffer();
	void setBool();


	//!< Methodes
	void update(double& simtime,vector<Neuron>& neuron_sim);
	void give_spike(vector<Neuron>& neuron_sim);//!< puts spike in the buffer of the neurons connected with it

};

#endif
