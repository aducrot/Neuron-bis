#ifndef NEURON_H
#define NEURON_H
using namespace std;
#include <vector>
#include <fstream>

class Neuron
{
	private:
	double potential_; // V(t)
//	double current_; // I(t)
	int spikecount_; // conteur qui garde en memoir le nombre de spike qui ont ete genere
	vector <double> spikeTime_; // tableau qui conserve le temps auquel le spike a eu lieu
	double taux_; // temps caracteristique taux=Resistance*C
	double tauxRefractory_; //refractory time (le neuron n'est pas stimule)
	double conductivity_;
	double Res_;

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

	void setPotential(double p);
	//void setCurrent(double i);
	void setSpikecount ();
	void setSpikeTime(double t);
	void setRes(double r);
	void setConductivity(double c);

	// methodes
	void update(double const& Iext, double const& h, double const& threshold, double& simtime, double& n, ostream& out);

};

#endif
