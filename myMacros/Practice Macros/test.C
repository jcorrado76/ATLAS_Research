
Int_t test()
{
gROOT->ProcessLine(".L generateEfficiencies.C");
gROOT->ProcessLine(".L print7Efficiencies.C");
gROOT->ProcessLine(".x generateEfficiencies.C()");
gROOT->ProcessLine(".x print7Efficiencies.C()");
return(0);
}
