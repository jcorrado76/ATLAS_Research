Int_t generateEfficiencies(Float_t metl1Thresh = 30.0, Float_t frac = 1e-4,TString& zeroBiasfileName = "ZeroBias2016R307195R311481Runs56.root",TString& muonFilename = "PhysicsMain2016.Muons.R3073065R311481Runs9.root")
{
  /*
   This program should just call threeefficiencies.c for all of the 15 combinations of algorithms
  */
  gROOT->ProcessLine(".L threeEfficiencies.c");
  TString algArray[6] = {"mettopoclem","metcell","metmht","mettopocl","mettopoclps","mettopoclpuc"};
//  TString algArray[6] = {"metl1","metcell","metmht","mettopocl","mettopoclps","mettopoclpuc"};
  TString argc;
  for (Int_t i = 0 ; i < 6 ; i++)
  {
    for (Int_t j = i+1 ; j < 6 ; j++)
    {
      argc = ".x threeEfficiencies.c(\"" + algArray[i] + "\",\"" + algArray[j] + "\"," + Form("%.7f",metl1thresh) + "," + Form("%.7f",frac) + ",\""+zeroBiasfileName+"\",\""+muonFilename+"\")";
      gROOT->ProcessLine(argc);
    }
  }

  return(0);

}
