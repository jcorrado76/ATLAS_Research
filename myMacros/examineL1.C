#include "TROOT.h"
#include <iostream>
void examineL1()
{
    gDirectory->cd("../myMacros");
    gROOT->ProcessLine(".L threeEfficiencies.C;");
    TString algArray[6] = {"mettopoclem","metcell","metmht","mettopocl","mettopoclps","mettopoclpuc"};
    std::cout << "Starting the stack..." << std::endl;
    gROOT->ProcessLine(".x threeEfficiencies.C(\"metcell\",\"mettopoclpuc\",0);");
    gROOT->ProcessLine(".x threeEfficiencies.C(\"metcell\",\"mettopoclpuc\",5);");
    gROOT->ProcessLine(".x threeEfficiencies.C(\"metcell\",\"mettopoclpuc\",10);");
    gROOT->ProcessLine(".x threeEfficiencies.C(\"metcell\",\"mettopoclpuc\",15);");
    gROOT->ProcessLine(".x threeEfficiencies.C(\"metcell\",\"mettopoclpuc\",20);");
    gROOT->ProcessLine(".x threeEfficiencies.C(\"metcell\",\"mettopoclpuc\",25);");
    gROOT->ProcessLine(".x threeEfficiencies.C(\"metcell\",\"mettopoclpuc\",30);");
    gROOT->ProcessLine(".x threeEfficiencies.C(\"metcell\",\"mettopoclpuc\",35);");
    gROOT->ProcessLine(".x threeEfficiencies.C(\"metcell\",\"mettopoclpuc\",40);");
    std::cout << "Finished." << std::endl;
}
