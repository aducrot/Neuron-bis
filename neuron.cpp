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
/**
@return int spikecount_
*/
int Neuron::getSpikecount() const
{
	return spikecount_;
}

/**
@return vector spikeTime_
*/
vector <double> Neuron::getSpiketime() const
{
	return spikeTime_;
}

void Neuron::setSpikecount()  //!< sets the spike count of the neuron
{
	spikecount_= spikecount_+1;
}

/**
@param double time
places spike time in the attribut spikeTime_
*/
void Neuron::setSpikeTime(double t)//!< sets the time of the spike in the vector spikeTime_
{
	spikeTime_.push_back(t);
}

/**
@return bool isSpiking_
*/
bool Neuron::getisSpiking() const
{
	return isSpiking_;
}
\/**
@param int const neuron_index
sets the connected_with_ vector
*/
void Neuron::setConnexion (int const neuron_index) //!< sets the connected_with_ vector
{
	connected_with_.push_back(neuron_index);
}

void Neuron::setBuffer() //!< sets the Buffer_ of the target neuron at the correct place
{
	Buffer_[(clock_+Delay_)%Buffer_.size()]+=J_;
}

void Neuron::setBool() //!< sets boolean isExcitory to true for Excitory neurons
{
	isExcitory=true;
}

/**
@return vector connected_with_
*/
vector<int> Neuron::getConnection() const
{
	return connected_with_;
}

void Neuron::setJ_() //!< sets the J_ value for inhibitory neurons (J=-0.5)
{
	J_=-0.5;
}


//!<Methodes
/**
@param vector<Neuron>& neuron_sim
puts spike in the buffer of the neurons connected with it
*/
void Neuron::give_spike(vector<Neuron>& neuron_sim)
{
	for (size_t i(0); i<connected_with_.size(); ++i)
	{
		neuron_sim[connected_with_[i]].setBuffer();
	}
}

/**
@param double& simtime, vector<Neuron>& neuron_sim;
update the potential of the neuron depending on if its in refractory time or not.
It also sets the buffer of the target neurons if it has spiked
*/
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
