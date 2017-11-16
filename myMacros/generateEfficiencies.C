#include "TString.h"
#include "TROOT.h"

//TODO: write some file handling code that generates a folder within TEfficienciesPics and time stamps it to keep everything
//organized


Int_t generateEfficiencies( const TString& folderName = "")
{
    //TString algArray[6] = {"metcell","metmht","mettopocl","mettopoclps","mettopoclpuc","mettopoclem"};
    //TString algArray[6] = {"metl1","metcell","metmht","mettopocl","mettopoclps","mettopoclpuc"};
    TString algArray[4] = {"metl1","metl1kf","metl1mht","metl1mhtkf"};
    
    
    for (Int_t i = 0 ; i < sizeof(algArray) ; i++)
    {
    	for (Int_t j = i+1 ; j < sizeof(algArray) ; j++)
    	{
    	    gROOT->ProcessLine(".x threeEfficiencies.C(\"" + algArray[i] + "\",\"" + algArray[j] );
    	}
    }

  return(0);

}
