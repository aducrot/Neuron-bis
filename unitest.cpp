#include <iostream>
#include <cmath>
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
  EXPECT_EQ(1,neurons[1].getPotential()+1);// to avoid provlem witht he zero value
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

  neurons[1].setConnexion(2);
  EXPECT_EQ(2,neurons[1].getConnection()[0]);
}

TEST (NeuronTest, Buffer)
{
  std::vector<Neuron> neurons;
  int neuron_sim(2);
  for (size_t i(0); i<neuron_sim; ++i)
  {
    Neuron n;
    neurons.push_back(n);
  }
  int value;
  neurons[1].setConnexion(2);
  neurons[1].setBuffer();
  neurons[2].getBuffer()[0];
  EXPECT_EQ(0.1,neurons[2].getBuffer()[0]);//there should be the value of J (0.1)
                                            //in the Buffer when the clock is at 0
}

int main(int argc,char**argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
