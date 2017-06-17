#include "TROOT.h"

Int_t bigMacro()
{
    gROOT->ProcessLine("gSystem->cd(\"../myMacros/\"");
    gROOT->ProcessLine(".L ../myMacros/generateEfficiencies.C+");
    TString algArray[6] = {"mettopoclem","metcell","metmht","mettopocl","mettopoclps","mettopoclpuc"};
    
    gROOT->ProcessLine("generateEfficiencies(30,1e-4,\"L130frac1e-4NewestMuonData\"");
    gROOT->ProcessLine("generateEfficiencies(40,1e-4,\"L140frac1e-4NewestMuonData\"");
    gROOT->ProcessLine("generateEfficiencies(40,5e-5,\"L140frac5e-5NewestMuonData\"");
    gROOT->ProcessLine("generateEfficiencies(30,5e-5,\"L130frac5e-5NewestMuonData\"");
 

    for (int i = 0 ; i < 6; i++)
    {
	gROOT->ProcessLine("threeEfficiencies(\" " + algArray[i] +"\" ,\"" +  algArray[i]+ "\" , 30 , 1e-4 , \"controlGroup\" , \"ZeroBias2016R307195R311481Runs56.root\", \"PhysicsMain2016.Muons.noalgL1XE45R3073065R311481Runs9B.root\"" );
    }

    return(0);
}
