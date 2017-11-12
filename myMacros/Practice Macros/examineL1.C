#include "TROOT.h"
#include <iostream>
void examineL1( const TString& firstAlg = "metcell", const TString& secondAlg = "mettopoclpuc")
{
    std::cout << "Processing L1 analysis for: " << firstAlg << " and " << secondAlg << std::endl;
    gDirectory->cd("../myMacros");
    gROOT->ProcessLine(".L threeEfficiencies.C;");
    gROOT->ProcessLine(".x threeEfficiencies.C(\"" + firstAlg + "\",\"" + secondAlg + "\",0);");
    gROOT->ProcessLine(".x threeEfficiencies.C(\"" + firstAlg + "\",\"" + secondAlg + "\",5);");
    gROOT->ProcessLine(".x threeEfficiencies.C(\"" + firstAlg + "\",\"" + secondAlg + "\",10);");
    gROOT->ProcessLine(".x threeEfficiencies.C(\"" + firstAlg + "\",\"" + secondAlg + "\",15);");
    gROOT->ProcessLine(".x threeEfficiencies.C(\"" + firstAlg + "\",\"" + secondAlg + "\",20);");
    gROOT->ProcessLine(".x threeEfficiencies.C(\"" + firstAlg + "\",\"" + secondAlg + "\",25);");
    gROOT->ProcessLine(".x threeEfficiencies.C(\"" + firstAlg + "\",\"" + secondAlg + "\",30);");
    gROOT->ProcessLine(".x threeEfficiencies.C(\"" + firstAlg + "\",\"" + secondAlg + "\",35);");
    gROOT->ProcessLine(".x threeEfficiencies.C(\"" + firstAlg + "\",\"" + secondAlg + "\",40);");
    std::cout << "Finished." << std::endl;
}
