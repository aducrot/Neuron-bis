#include "neuron.hpp"
#include <iostream>
#include <cmath>

/*Constructeur et destructeur*/

Neuron::Neuron (): potential_(0), spikecount_(0),spikeTime_(0), taux_(20),tauxRefractory_(2), h_(0.1),
							ref_time_(tauxRefractory_/h_), conductivity_(1), Res_(taux_/conductivity_),
							threshold_(20), isSpiking_(false),clock_(0),Delay_(15), SumSpike_(Delay_,0), J_(0.1)
							//,connected_with_(0)
{}


Neuron::Neuron (Neuron const& other) // a modifier avec le reste des new values
{
	potential_= other.potential_;
	spikecount_=other.spikecount_;
	spikeTime_=other.spikeTime_;
	taux_=other.taux_;
	tauxRefractory_ =other.tauxRefractory_;
	Res_=other.Res_;
	conductivity_=other.conductivity_;
	isSpiking_=other.isSpiking_;
	clock_=other.clock_;
	Delay_=other.Delay_;
	SumSpike_=other.SumSpike_;
	J_=other.J_;

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

//methodes

void Neuron::isSpiking_check(double const& Iext, double const& simtime)
{
	potential_= (exp(-h_/taux_)*potential_)+Iext*Res_*(1-exp(-h_/taux_));
	if (potential_> threshold_)
	{
		isSpiking_=true;
		spikecount_=spikecount_+1;
		setSpikeTime(simtime);
		potential_= 0;
		ref_time_= tauxRefractory_/h_;
	} else {
		isSpiking_=false;
	}

}

void Neuron::update(double const& Iext, double& simtime, bool ispiking)
{
	if (ispiking==true)
	{
		SumSpike_[0]+=1;
	}

	for (int i(Delay_-1); i>=1 ; --i)
	{
		SumSpike_[i]= SumSpike_[i-1];
	}

	SumSpike_[0]=0;

	if (ref_time_>0)
	{
		isSpiking_=true;
		potential_=0;
		ref_time_-=1;
	} else if (ispiking==true)
		{
			if (clock_>=Delay_) // if never spiked ans is already greater then delay
			{
				int x=SumSpike_[Delay_-1];// takes last value in table
				potential_= (exp(-h_/taux_)*potential_)+Iext*Res_*(1-exp(-h_/taux_)) + x*J_;
				SumSpike_[Delay_-1]=0;
				clock_=0;

				if (potential_>threshold_)
				{
					isSpiking_=true;
					spikecount_=spikecount_+1;
					setSpikeTime(simtime);
					potential_= 0;
					ref_time_= tauxRefractory_/h_;
				}
			} else { isSpiking_check(Iext,simtime); }
		} else { isSpiking_check(Iext,simtime); }

		clock_+=1;
}
