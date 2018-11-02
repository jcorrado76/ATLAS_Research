Given the physics main stream data jonathan burr generated:
user.jburr:user.jburr.2017.JETM10
to select events passing HLTnoalgL1XE (30 for this case). triggers

This project will take the distributions of MET, in particular for CELL, and
correct the distribution by weighting the fills to the histogram by the
prescale divided by the efficiency at that value of MET.




Correct the L1XE30 data from Physics main. Divide by the efficiency and multiply
by the pre-scale. Physics main here is the JburrJETM10

Do it with the red efficiency fits, and try with the blue average. 

Create the distributions for cell met for the L1XE30 by dividing at event level.
you can func->eval in denominator 

Plot those distributions on top of the appropriately normalized zerobias
dsitributions (perhaps accounting for the prescale, although mincer said it was
funny; just try normalizing and see what happens). 


