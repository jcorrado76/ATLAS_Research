#include "TROOT.h"

void generatePlots()
{
    gROOT->ProcessLine(".L examineL1.C;");
    gROOT->ProcessLine(".L threeEfficiencies.C;");
    gROOT->ProcessLine(".L generateEfficiencies.C;");

//    gROOT->ProcessLine(".x threeEfficiencies.C(\"metcell\",\"mettopoclps\",0);");
    gROOT->ProcessLine(".x threeEfficiencies.C(\"mettopocl\",\"mettopoclpuc\",0);");
    gROOT->ProcessLine(".x generateEfficiencies.C(0);");
    gROOT->ProcessLine(".x threeEfficiencies.C(\"metmht\",\"mettopoclps\",0);");
    gROOT->ProcessLine(".x examineL1.C(\"metcell\",\"mettopoclpuc\");");
    gROOT->ProcessLine(".x examineL1.C(\"metmht\",\"mettopoclps\");");
//    gROOT->ProcessLine(".x threeEfficiencies.C(\"" + firstAlg + "\",\"" + secondAlg + "\",0);");
}
