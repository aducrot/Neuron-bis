#include "neuron.hpp"
#include <iostream>
#include <cmath>
#include <random>

/*Constructeur et destructeur*/

Neuron::Neuron (): potential_(0), spikecount_(0),spikeTime_(0), taux_(20),tauxRefractory_(2), h_(0.1), Iext_(0),
							ref_time_(tauxRefractory_/h_), conductivity_(1), Res_(taux_/conductivity_),
							threshold_(20), isSpiking_(false),clock_(0),Delay_(15), Buffer_(Delay_+1,0), J_(0.1)
							//,connected_with_(0)
{}

Neuron::~Neuron()
{}

//Getteur et Setteur
const double Neuron::getPotential()
{
	return potential_;
}

const int Neuron::getSpikecount()
{
	return spikecount_;
}

vector <double> Neuron::getSpiketime()
{
	return spikeTime_;
}

const double Neuron:: getRes()
{
	return Res_;
}

const double Neuron::getConductivity()
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
	clock_=t; // use the value of n??
}

void Neuron::setIsSpiking(bool answer)
{
	isSpiking_=answer;
}

const double Neuron::getTaux()
{
	return taux_;
}

const double Neuron::getTauxRefractory()
{
	return tauxRefractory_;
}

const bool Neuron::getisSpiking()
{
	return isSpiking_;
}

const int Neuron::getClock()
{
	return clock_;
}

void Neuron::setConnexion (vector <Neuron>const& connexion_matrix)
{
	connected_with_=connexion_matrix;
}

void Neuron::setBuffer()
{
	Buffer_[(clock_+Delay_)%Buffer_.size()]+=1;
}

//methodes
void Neuron::give_spike()
{
	if (isSpiking_)
	{
		for (int i(0); i<connected_with_.size(); ++i)
		{
			connected_with_[i].setBuffer();
		}
	}
}

void Neuron::update(double& simtime)
{
	double lambda(0.005);
	random_device rd;
	mt19937 gen(rd());
	poisson_distribution<> p(lambda);

	double background_ (static_cast<double> (p(gen))); //intialise the background stimulation every time tep

	if (ref_time_>=0)
	{
		potential_=0;
		ref_time_-=1;
		isSpiking_=false; // a verifier.... essayer true si ca marche pas...
	} else {
		potential_= (exp(-h_/taux_)*potential_)+Iext_*Res_*(1-exp(-h_/taux_))+Buffer_[clock_]*J_+background_;
		Buffer_[clock_]=0;
		spikecount_+=1;
		setSpikeTime(simtime);
		ref_time_= tauxRefractory_/h_;

		if(potential_>threshold_)
		{
			isSpiking_=true;
			give_spike();
		} else {
			isSpiking_=false;
		}
	}
		clock_+=1;
}
