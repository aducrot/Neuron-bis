#include <iostream>
#include "neuron.hpp"
#include "gtest/gtest.h"

TEST (NeuronTest, membranePotential )
{
  std::vector<Neuron> neurons;
  int neuron_sim(1);
  for (size_t i(0); i<neuron_sim; ++i)
  {
    Neuron n;
    neurons.push_back(n);
  }
  n.update(1,neurons);
  EXPECT_EQ(n.getPotential()>20);
}
