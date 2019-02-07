#include "TString.h"
#include "TROOT.h"

//TODO: write some file handling code that generates a folder within TEfficienciesPics and time stamps it to keep everything
//organized


Int_t generateEfficiencies( const TString& folderName = "")
{
    TString algArray[7] = {"metl1","metcell","metmht","mettopocl","mettopoclps","mettopoclpuc","mettopoclem"};
    
    for ( std::size_t i = 0 ; i < sizeof(algArray) ; i++)
    {
    	for ( std::size_t j = i+1 ; j < sizeof(algArray) ; j++)
    	{
    	    gROOT->ProcessLine(".x threeEfficiencies.C(\"" + algArray[i] + "\",\"missing_et_significance\")" );
    	}
    }

  return(0);

}
