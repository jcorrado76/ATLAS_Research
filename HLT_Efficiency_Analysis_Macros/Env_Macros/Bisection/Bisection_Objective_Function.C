#define Bisection_Objective_Function_cxx
#include "Bisection_Objective_Function.h"
#include <TH2.h>
#include <TStyle.h>

void Bisection_Objective_Function::Begin(TTree * )
{
   TString option = GetOption();
}

void Bisection_Objective_Function::SlaveBegin(TTree * )
{
   TString option = GetOption();
}

Bool_t Bisection_Objective_Function::Process(Long64_t entry)
{
   fReader.SetEntry(entry);
   if ( AlgAPass() && AlgBPass() && PassL1() && PassActint() && IsPassnoAlgOrRndm() && IsClean() ){
       NumberEventsKept++;
   }
   return kTRUE;
}

void Bisection_Objective_Function::SlaveTerminate()
{
}

void Bisection_Objective_Function::Terminate()
{
}
