#include "TString.h"
#include "TROOT.h"
void generateEfficiencies( const TString& folderName = "")
{
    //TString algArray[6] = {"metcell","metmht","mettopocl","mettopoclps","mettopoclpuc","mettopoclem"};
    //TString algArray[6] = {"metl1","metcell","metmht","mettopocl","mettopoclps","mettopoclpuc"};
    //TString algArray[4] = {"metl1","metl1kf","metl1mht","metl1mhtkf"};
    
   /* 
    for ( std::size_t i = 0 ; i < sizeof(algArray) ; i++)
    {
    	for ( std::size_t j = i+1 ; j < sizeof(algArray) ; j++)
    	{
    	    gROOT->ProcessLine(".x threeEfficiencies.C(\"" + algArray[i] + "\",\"" + algArray[j]+"\")" );
    	}
    }
*/

//    gROOT->ProcessLine(".x threeEfficiencies.C(\"metl1\", \"metl1kf\")");
//    gROOT->ProcessLine(".x threeEfficiencies.C(\"metl1\", \"metl1mht\")");
//    gROOT->ProcessLine(".x threeEfficiencies.C(\"metl1\", \"metl1mhtkf\")");
    gROOT->ProcessLine(".x threeEfficiencies.C(\"metl1kf\", \"metl1mht\")");
    gROOT->ProcessLine(".x threeEfficiencies.C(\"metl1kf\", \"metl1mhtkf\")");
    gROOT->ProcessLine(".x threeEfficiencies.C(\"metl1mht\", \"metl1mhtkf\")");
}
