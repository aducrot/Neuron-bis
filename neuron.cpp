#include "neuron.hpp"
#include <iostream>
#include <cmath>
#include <random>
#include <cassert>

//!<Constructeur et destructeur

Neuron::Neuron (): potential_(0), spikecount_(0),spikeTime_(0), taux_(20),tauxRefractory_(2), h_(0.1), Iext_(0),
							ref_time_(tauxRefractory_/h_), conductivity_(1), Res_(taux_/conductivity_),
							threshold_(20), isSpiking_(false),clock_(0),Delay_(15), Buffer_(Delay_+1,0.0), J_(0.1),connected_with_(0)
{}

Neuron::~Neuron()
{}

//!<Getteur et Setteur
double Neuron::getPotential() const
{
	return potential_;
}

int Neuron::getSpikecount() const
{
	return spikecount_;
}

vector <double> Neuron::getSpiketime() const
{
	return spikeTime_;
}

double Neuron:: getRes() const
{
	return Res_;
}

double Neuron::getConductivity() const
{
	return conductivity_;
}

void Neuron::setPotential(double p)
{
	potential_=p;
}

void Neuron::setSpikecount()
{
	spikecount_= spikecount_+1;
}

void Neuron::setSpikeTime(double t)
{
	spikeTime_.push_back(t);
}

void Neuron::setConductivity(double c)
{
	conductivity_=c;
}

void Neuron::setRes(double r)
{
	Res_=r;
}

void Neuron::setClock(double t)
{
	clock_=t;
}

void Neuron::setIsSpiking(bool answer)
{
	isSpiking_=answer;
}

double Neuron::getTaux() const
{
	return taux_;
}

double Neuron::getTauxRefractory() const
{
	return tauxRefractory_;
}

bool Neuron::getisSpiking() const
{
	return isSpiking_;
}

int Neuron::getClock() const
{
	return clock_;
}

void Neuron::setConnexion (vector <int>const& connexion_matrix)
{
	connected_with_=connexion_matrix;
}

void Neuron::setBuffer()
{
	Buffer_[(clock_+Delay_)%Buffer_.size()]+=1;
}

//!<Methodes
void Neuron::give_spike(vector<Neuron>& neuron_sim)
{
	if (isSpiking_)
	{
		for (int i(0); i<connected_with_.size(); ++i)
		{
			neuron_sim[connected_with_[i]].setBuffer();
		}
	}
}

void Neuron::update(double& simtime, vector<Neuron>& neuron_sim)
{
	double lambda(2); //!<poisson probability of receiving spike from the rest of the brain, can
										//!<be calculated using vext/vth = 2 ==> the average firing rate is 2 spikes per time step
	random_device rd;
	mt19937 gen(rd());
	poisson_distribution<> p(lambda);

	double background_(static_cast<double> (p(gen))); //!<intialise the background stimulation every time step

	if (ref_time_>=0)
	{
		potential_=0;
		ref_time_-=1;
		isSpiking_=true; // a verifier.... essayer true si ca marche pas...
	} else {
		assert(clock_%Buffer_.size()<Buffer_.size());
		potential_= (exp(-h_/taux_)*potential_)+Iext_*Res_*(1-exp(-h_/taux_))+(Buffer_[clock_%Buffer_.size()]+background_)*J_;
		Buffer_[clock_%Buffer_.size()]=0;
		setSpikecount();
		setSpikeTime(simtime);
		ref_time_= tauxRefractory_/h_;

		if(potential_>threshold_)
		{
			isSpiking_=true;
			give_spike(neuron_sim);
		} else {
			isSpiking_=false;
		}
	}
		clock_+=1;
}
