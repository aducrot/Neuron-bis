#ifndef NEURON_H
#define NEURON_H
using namespace std;
#include <vector>
#include <fstream>

class Neuron
{
	private:
	double potential_; // V(t)
	double h_;
//	double current_; // I(t)
	int spikecount_; // conteur qui garde en memoir le nombre de spike qui ont ete genere
	vector <double> spikeTime_; // tableau qui conserve le temps auquel le spike a eu lieu
	double taux_; // temps caracteristique taux=Resistance*C
	double tauxRefractory_; //refractory time (le neuron n'est pas stimule)
	double conductivity_;
	double Res_;
	int clock_; // neuron internal clock to keep track of time- number of h steps
	bool isSpiking_; // to know if the neuron has spiked.
	int Delay_; // the number of h needed to get the delay time
	vector <int> SumSpike_; // take the number of spikes that happened in 1 h step
	double J_;
	double threshold_;
	double ref_time_;
	//vector<Neuron> connected_with_;

	public:
	//constructeur et destructeur
	Neuron ();
	//Neuron (double p, double i);
	Neuron (Neuron const& other);
	~Neuron ();

	//getteurs et setteurs
	const double getPotential();
	//const double getCurrent();
	const int getSpikecount();
	vector <double> getSpiketime();
	const double getTaux();
	const double getTauxRefractory();
	const double getRes();
	const double getConductivity();
	const int getClock();
	const bool getisSpiking();

	void setPotential(double p);
	//void setCurrent(double i);
	void setSpikecount ();
	void setSpikeTime(double t);
	void setRes(double r);
	void setConductivity(double c);
	void setIsSpiking(bool answer);
	void setClock(double t);
	//vector <Neuron> connected();
	void isSpiking_check(double const& Iext, double const& simtime);

	// methodes
	void update(double const& Iext, double& simtime, bool ispiking);

};

#endif
