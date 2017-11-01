#include "neuron.hpp"
#include <iostream>
#include <cmath>
#include <random>
#include <cassert>

//!<Constructeur et destructeur

Neuron::Neuron (): potential_(0), spikecount_(0),spikeTime_(0), taux_(20),tauxRefractory_(2), h_(0.1), Iext_(0),
							ref_time_(tauxRefractory_/h_), conductivity_(1), Res_(taux_/conductivity_),
							threshold_(20), isSpiking_(false),clock_(0),Delay_(15), Buffer_(Delay_+1,0.0), J_(0.1),
							isExcitory(false)
{}

Neuron::~Neuron()
{}

//!<Getteur et Setteur
int Neuron::getSpikecount() const
{
	return spikecount_;
}

vector <double> Neuron::getSpiketime() const
{
	return spikeTime_;
}

void Neuron::setSpikecount()
{
	spikecount_= spikecount_+1;
}

void Neuron::setSpikeTime(double t)
{
	spikeTime_.push_back(t);
}

bool Neuron::getisSpiking() const
{
	return isSpiking_;
}

void Neuron::setConnexion (int const neuron_index)
{
	connected_with_.push_back(neuron_index);
}

void Neuron::setBuffer()
{
	Buffer_[(clock_+Delay_)%Buffer_.size()]+=J_;
}

void Neuron::setBool()
{
	isExcitory=true;
}

vector<int> Neuron::getConnection() const
{
	return connected_with_;
}

void Neuron::setJ_()
{
	J_=-0.5;
}


//!<Methodes
void Neuron::give_spike(vector<Neuron>& neuron_sim)
{
	for (size_t i(0); i<connected_with_.size(); ++i)
	{
		neuron_sim[connected_with_[i]].setBuffer();
	}
}

void Neuron::update(double& simtime, vector<Neuron>& neuron_sim)
{
	double lambda(2); //!<poisson probability of receiving spike from the rest of the brain, can
										//!<be calculated using nu_ext*h = 2 ==> the average firing rate is 2 spikes per time step
	static random_device rd;
	static mt19937 gen(rd());
	assert(lambda>0);
	static poisson_distribution<> p(lambda);

	int background_(p(gen)); //!<intialise the background stimulation every time step

	if (ref_time_>0)
	{
		potential_=0;
		ref_time_-=1;
		isSpiking_=false;
	} else {

		assert(clock_%Buffer_.size()<Buffer_.size());
		assert(Buffer_.size()==(Delay_+1));
		assert(clock_%Buffer_.size()>=0);

		if(potential_>threshold_)
		{
			isSpiking_=true;
			give_spike(neuron_sim);
			setSpikecount();
			setSpikeTime(simtime);
			ref_time_= tauxRefractory_/h_;
			assert (ref_time_>0);
		} else {
			isSpiking_=false;
			potential_= (exp(-h_/taux_)*potential_)+Iext_*Res_*(1-exp(-h_/taux_))+
									Buffer_[clock_%Buffer_.size()]+ background_*0.1;
			Buffer_[clock_%Buffer_.size()]=0;
		}
	}
		clock_+=1;
}
