#include "TString.h"
#include "TROOT.h"
Int_t Run_ThreeEff_Missing_ET_All_Algs( const TString& folderName = "")
{
    TString algArray[5] = {"metcell","metmht","mettopocl","mettopoclps","mettopoclpuc"};
    
    for ( std::size_t i = i+1 ; i < sizeof(algArray) ; i++)
    {
        gROOT->ProcessLine(".x Perform_Missing_ET_Efficiency_Analysis.C(\"" + algArray[i] + "\");");
    }

  return(0);

}
