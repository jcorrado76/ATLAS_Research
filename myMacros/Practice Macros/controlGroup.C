#include "TString.h"
#include "TROOT.h"

Int_t controlGroup(Float_t metl1Thresh = 30.0, const Float_t frac = 1e-4, const TString& folderName = "controlGroup", const TString& zeroBiasFileName = "ZeroBias2016R307195R311481Runs56.root", const TString& muonFilename = "PhysicsMain2016.Muons.noalgL1XE45R3073065R311481Runs9B.root")
{
    /* 
    This program computes the efficiencies of using the same algorithm combined with itself. Because using the same algorithm twice shouldn't add any new information to the efficiency, we should see that the three efficiency curves lie on the same line as a check to make sure threeEfficiencies.C does what it should be doing. 
    */
    
    gROOT->ProcessLine(".L threeEfficiencies.C");
    TString algArray[6] = {"mettopoclem","metcell","metmht","mettopocl","mettopoclps","mettopoclpuc"};
    for (Int_t i = 0 ; i < 6 ; i++)
    {
	gROOT->ProcessLine(".x threeEfficiencies.C(\"" + algArray[i] + "\",\"" + algArray[i] + "\"," + Form("%.7f",metl1Thresh) + "," + Form("%.7f",frac) + ",\""+zeroBiasFileName+"\",\""+muonFilename+"\")");
    }
  return(0);

}
