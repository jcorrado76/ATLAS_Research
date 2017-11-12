#include "TMath.h"
#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TEfficiency.h"
#include "TLegend.h"
#include <iostream>
#include <fstream>
#include "TCanvas.h"
#include "TSystem.h"
#include "TF1.h"
#include "TString.h"
#include "TROOT.h"

Int_t wAnalysisFull()
{
/*
this program calls WAnalysis for all four pairs of algorithms that do better combined to compare
using W cut for those combinations
*/
    gROOT->ProcessLine(".L WAnalysis.C");
    gROOT->ProcessLine(".x WAnalysis.C(\"metcell\",\"metmht\");");
    gROOT->ProcessLine(".x WAnalysis.C(\"metcell\",\"mettopocl\");");
    gROOT->ProcessLine(".x WAnalysis.C(\"metcell\",\"mettopoclps\");");
    gROOT->ProcessLine(".x WAnalysis.C(\"metmht\",\"mettopoclpuc\");");


  return(0);

}
