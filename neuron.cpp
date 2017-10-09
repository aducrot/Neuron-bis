#include "neuron.hpp"
#include <iostream>
#include <cmath>


/*Constructeur et destructeur*/

Neuron::Neuron (): potential_(0), spikecount_(0),spikeTime_(0), taux_(20),tauxRefractory_(2),
							conductivity_(1), Res_(taux_/conductivity_)
{}


Neuron::Neuron (Neuron const& other)
{
	potential_= other.potential_;
	spikecount_=other.spikecount_;
	spikeTime_=other.spikeTime_;
	taux_=other.taux_;
	tauxRefractory_ =other.tauxRefractory_;
	Res_=other.Res_;
	conductivity_=other.conductivity_;

}

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

void Neuron:: setRes(double r)
{
	Res_=r;
}

const double Neuron::getTaux()
{
	return taux_;
}

const double Neuron::getTauxRefractory()
{
	return tauxRefractory_;
}

//methodes

void Neuron::update(double const& Iext, double const& h, double const& threshold, double& simtime, double& n, ostream& out)
{
	if (n>0)
	{
		potential_=0;
		n-=1;
		out<<potential_<<endl;
		//simtime+=h;
	} else {
		potential_= (exp(-h/taux_)*potential_)+Iext*Res_*(1-exp(-h/taux_));
		if (potential_<threshold)
		{
			out<<potential_<<endl;
		}

		if (potential_> threshold)
		{
			spikecount_=spikecount_+1;
			setSpikeTime(simtime);
			potential_= 0;
			n= tauxRefractory_/h;
			out<<potential_<< endl;
		}
	}
}
