#include "TROOT.h"

Int_t generateL1Analysis()
{
    gROOT->ProcessLine("gROOT->Time();");
    gROOT->ProcessLine(".L examineL1.C;");

    gROOT->ProcessLine(".x examineL1.C(\"metcell\",\"mettopoclpuc\");");
    gROOT->ProcessLine(".x examineL1.C(\"metmht\",\"mettopoclps\");");
  return(0);

}
