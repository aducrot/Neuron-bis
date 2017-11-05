#include <iostream>
#include "neuron.hpp"
#include "gtest/gtest.h"

TEST (NeuronTest, MembranePotentialStartValue )
{
  std::vector<Neuron> neurons;
  int neuron_sim(1);
  for (size_t i(0); i<neuron_sim; ++i)
  {
    Neuron n;
    neurons.push_back(n);
  }
  EXPECT_EQ(1,neurons[1].getPotential()+1);// to avoid problems with the zero value
}

TEST (NeuronTest, connection)
{
  std::vector<Neuron> neurons;
  int neuron_sim(2);
  for (size_t i(0); i<neuron_sim; ++i)
  {
    Neuron n;
    neurons.push_back(n);
  }

  neurons[0].setConnexion(2);
  EXPECT_EQ(2,neurons[0].getConnection()[0]);
}

TEST (NeuronTest, Buffer)
{
  std::vector<Neuron> neurons;
  int neuron_sim(1);
  for (size_t i(0); i<neuron_sim; ++i)
  {
    Neuron n;
    neurons.push_back(n);
  }

  neurons[0].setBuffer();
  EXPECT_EQ(0.1, neurons[0].getBuffer()[15]); //there should be the value of J (0.1)
}

TEST (NeuronTest, GiveSpike)
{
  std::vector<Neuron> neurons;
  int neuron_sim(2);
  for (size_t i(0); i<neuron_sim; ++i)
  {
    Neuron n;
    neurons.push_back(n);
  }
  neurons[0].setConnexion(1);
  neurons[0].give_spike(neurons);
  EXPECT_EQ(0.1,neurons[1].getBuffer()[15]);

}

int main(int argc,char**argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
