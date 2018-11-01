#include "CorrectL1XE30toZB.h"
void compute_l1xe30_efficiency(){
{
    std::cout << "Correcting l1xe30 distributions to zerobias" << std::endl;
    TChain* mychain = new TChain( "METTree" , "mychain" );
    mychain->Add("~/DATA/PhysicsMain/JburrJETM10*");
    mychain->Process("CorrectL1XE30toZB.C++g");
}

