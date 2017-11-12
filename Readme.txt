Project Brunel:

The idea is to simulate a neuron cortex using inhibitory neurons and excitory neurons.
We also added a background noise in the simulation that generates random spikes.

In the calculation of the variables, we assume that nu_threshold is constant throughout the simulation.
Hence the only variable that changes are : the ration nu_ext/nu_threshold and the inhibitory current J_

To generate the various graphs, the program needs to be called 4 times using the various parameter, and
graph needs to be generated 4 times (once after each simulation) using jupyter notebook.

However, there is still a certain error. The simulation if generated for a smaller amount of time (100ms)
it provides what seems to be the correct graph (similar to the one of the Brunel paper). For the moment
the error still hasn't been found or corrected. 
