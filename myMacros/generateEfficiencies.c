Int_t generateEfficiencies()
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
      argc = ".x threeEfficiencies.c(\"" + algArray[i] + "\",\"" + algArray[j] + "\")";
      gROOT->ProcessLine(argc);
    }
  }

  return(0);

}
