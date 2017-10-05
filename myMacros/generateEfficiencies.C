#include "TString.h"
#include "TROOT.h"



//TODO: write some file handling code that generates a folder within TEfficienciesPics and time stamps it to keep everything
//organized
Int_t generateEfficiencies(const Float_t frac = 0.00590,
        const TString& folderName = "",
        const TString& zeroBiasFileName = "PhysicsMain.All.noalgXEtriggers.2016.f731f758._m1659m1710.48Runs.root",
        const TString& muonFilename = "PhysicsMain.L1KFmuontriggers.2016.f731f758_m1659m1710.Run309759.48Runs.root")
{
    /*
    This program should just call threeefficiencies.c for all of the 15 combinations of algorithms
    */
    gROOT->ProcessLine(".L threeEfficiencies.C");
    TString algArray[6] = {"metcell","metmht","mettopocl","mettopoclps","mettopoclpuc","mettopoclem"};
    //TString algArray[6] = {"metl1","metcell","metmht","mettopocl","mettopoclps","mettopoclpuc"};
    for (Int_t i = 0 ; i < 6 ; i++)
    {
	for (Int_t j = i+1 ; j < 6 ; j++)
	{
	    gROOT->ProcessLine(".x threeEfficiencies.C(\"" + algArray[i] + "\",\"" + algArray[j] + "\"," +
        Form("%.7f",frac) + ",\""+ folderName + "\",\"" +zeroBiasFileName+"\",\""+muonFilename+"\")");
	}
    }

  return(0);

}
