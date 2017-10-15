#include "neuron.hpp"
#include <iostream>
#include <cmath>

/*Constructeur et destructeur*/

Neuron::Neuron (): potential_(0), spikecount_(0),spikeTime_(0), taux_(20),tauxRefractory_(2),
							conductivity_(1), Res_(taux_/conductivity_), isSpiking_(false),clock_(0),Delay_(15),
							SumSpike_(Delay_,0), J_(0.1)
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

void Neuron::update(double const& Iext, double const& h, double const& threshold,
										double& simtime, double& n, ostream& out, bool ispiking)
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

	if (n>0)
	{
		isSpiking_=true;
		potential_=0;
		n-=1;
		out<<potential_<<endl;

	} else if (ispiking==true)
		{
			if (clock_>=Delay_)
			{
				int x=SumSpike_[Delay_-1];// takes last value in table
				potential_= (exp(-h/taux_)*potential_)+Iext*Res_*(1-exp(-h/taux_)) + x*J_;
				SumSpike_[Delay_-1]=0;
				clock_=0;

				if (potential_>threshold)
				{
					isSpiking_=true;
					spikecount_=spikecount_+1;
					setSpikeTime(simtime);
					potential_= 0;
					n= tauxRefractory_/h;
					out<<potential_<< endl;
				}
			} else
			{
				potential_= (exp(-h/taux_)*potential_)+Iext*Res_*(1-exp(-h/taux_));
				if (potential_<threshold)
				{
					isSpiking_=false;
					out<<potential_<<endl;
				}

				if (potential_> threshold)
				{
					isSpiking_=true;
					spikecount_=spikecount_+1;
					setSpikeTime(simtime);
					potential_= 0;
					n= tauxRefractory_/h;
					out<<potential_<< endl;
				}
			}
		} else {
			potential_= (exp(-h/taux_)*potential_)+Iext*Res_*(1-exp(-h/taux_));
			if (potential_<threshold)
			{
				isSpiking_=false;
				out<<potential_<<endl;
			}

			if (potential_> threshold)
			{
				isSpiking_=true;
				spikecount_=spikecount_+1;
				setSpikeTime(simtime);
				potential_= 0;
				n= tauxRefractory_/h;
				out<<potential_<< endl;
			}
		}
		clock_+=1;
}
