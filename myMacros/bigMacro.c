Int_t bigMacro()
{
  gROOT->ProcessLine(".L generateEfficiencies.c");
  argc = ".x threeEfficiencies.c(30,1e-4)";
  gROOT->ProcessLine(argc);
  gROOT->ProcssLine("gROOT->Reset()");

  argc = ".x threeEfficiencies.c(40,1e-4)";
  gROOT->ProcessLine(argc);
  gROOT->ProcssLine("gROOT->Reset()");

  argc = ".x threeEfficiencies.c(40,5e-5)";
  gROOT->ProcessLine(argc);
  gROOT->ProcssLine("gROOT->Reset()");

  argc = ".x threeEfficiencies.c(30,5e-5)";
  gROOT->ProcessLine(argc);

  return(0);
}
