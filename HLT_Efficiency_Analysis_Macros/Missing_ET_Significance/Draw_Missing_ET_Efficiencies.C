#define Draw_Missing_ET_Efficiencies_cxx
#include "Draw_Missing_ET_Efficiencies.h"
#include <TH2.h>
#include <TStyle.h>

void Draw_Missing_ET_Efficiencies::Begin(TTree *){TString option = GetOption();}
void Draw_Missing_ET_Efficiencies::SlaveBegin(TTree *){TString option = GetOption();}
Bool_t Draw_Missing_ET_Efficiencies::Process(Long64_t entry)
{
   fReader.SetEntry(entry);
   return kTRUE;
}
void Draw_Missing_ET_Efficiencies::SlaveTerminate(){}
void Draw_Missing_ET_Efficiencies::Terminate()
{
}
