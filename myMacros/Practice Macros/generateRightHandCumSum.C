#include "TString.h"
#include "TROOT.h"

Int_t generateRightHandCumSum()
{
    gROOT->ProcessLine("gROOT->Time();");
    gROOT->ProcessLine(".L computeRightHandIntegral.C");
    TString algArray[6] = {"mettopoclem","metcell","metmht","mettopocl","mettopoclps","mettopoclpuc"};
    //TString algArray[6] = {"metl1","metcell","metmht","mettopocl","mettopoclps","mettopoclpuc"};
    for (Int_t i = 0 ; i < 6 ; i++)
    {
    	for (Int_t j = i+1 ; j < 6 ; j++)
    	{
    	    gROOT->ProcessLine(".x computeRightHandIntegral.C(\"" + algArray[i] + "\")");
        }
    }

  return(0);

}
