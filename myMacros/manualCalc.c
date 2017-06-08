Int_t manualCalc()
{
  gROOT->ProcessLine(".L threeEfficiencies.c");
  TString argc = ".x threeEfficiencies.c(\"metcell\",\"metmht\")";
  gROOT->ProcessLine(argc);
  gROOT->ProcessLine("gROOT->Reset()");

  argc = ".x threeEfficiencies.c(\"mettopocl\",\"mettopoclpuc\")";
  gROOT->ProcessLine(argc);
  gROOT->ProcessLine("gROOT->Reset()");

  argc = ".x threeEfficiencies.c(\"metmht\",\"mettopoclpuc\")";
  gROOT->ProcessLine(argc);
  gROOT->ProcessLine("gROOT->Reset()");

  argc = ".x threeEfficiencies.c(\"metmht\",\"mettopocl\")";
  gROOT->ProcessLine(argc);
  gROOT->ProcessLine("gROOT->Reset()");


  argc = ".x threeEfficiencies.c(\"metmht\",\"mettopoclps\")";
  gROOT->ProcessLine(argc);
  gROOT->ProcessLine("gROOT->Reset()");

  return(0);
}
