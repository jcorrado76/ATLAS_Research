# Muon Analysis

Given the physics main stream (2015-2017) data jonathan burr generated:
user.jburr:user.jburr.201\d.JETM10
Select events passing HLTnoalgL1XE (30 for this case). triggers

This project will take the distributions of MET, in particular for CELL, and
correct the distribution by multiplying the frequency counts of each MET bin by the
prescale for that event divided by the efficiency at that value of MET.

Correct the L1XE30 data from Physics main. Divide by the efficiency and multiply
by the pre-scale. Physics main here is the JburrJETM10

Plot those distributions on top of the appropriately normalized zerobias
distributions (perhaps accounting for the prescale, although mincer said it was
funny; just try normalizing and see what happens). 

This macro will fill histograms of the zerobias MET data, as well as create the
efficiency of L1 XE 30.

This is the first stage of the corrections. The efficiency objects created from
this macro are used to correct the L1XE30 data back to the zerobias data

It writes the non-normalized MET distributions to file, as well as the
efficiency objects, and the efficiency fits
