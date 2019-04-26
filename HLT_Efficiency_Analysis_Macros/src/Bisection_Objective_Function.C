#define Bisection_Objective_Function_cxx
#include "Bisection_Objective_Function.h"
#include <TH2.h>
#include <TStyle.h>

void Bisection_Objective_Function::Begin(TTree * )
{
    TString option = GetOption();
    TH1F *algACumulativeDistribution = (TH1F*) algAHist->GetCumulative(kFALSE);
    TH1F *algBCumulativeDistribution = (TH1F*) algBHist->GetCumulative(kFALSE);
    algAThreshold = computeThresh( algACumulativeDistribution , NumberEventsToKeep );
    algBThreshold = computeThresh( algBCumulativeDistribution , NumberEventsToKeep );
}

void Bisection_Objective_Function::SlaveBegin(TTree * )
{
   TString option = GetOption();
}

Bool_t Bisection_Objective_Function::Process(Long64_t entry)
{
    fReader.SetEntry(entry);
    if ( IsPassnoAlgOrRndm() && PassL1() && PassActint() )
    {
        zerobias_events++;
        if (AlgA* > algAThreshold && AlgB* > algBThreshold)
        {
            events_kept++;
        }
    }
   return kTRUE;
}

void Bisection_Objective_Function::SlaveTerminate(){}
void Bisection_Objective_Function::Terminate()
{
    std::cout << "Number of events kept when " << AlgAName << " > " << AlgAThreshold << " and " << 
        AlgBName << " > " << AlgBThreshold << ": " << NumberEventsKept << std::endl;
}

Bool_t Bisection_Objective_Function::IsPassnoAlgOrRndm(){ return ( *passrndm > RndmCut || *passnoalgL1XE10 > RndmCut || *passnoalgL1XE30 > RndmCut || *passnoalgL1XE40 > RndmCut || *passnoalgL1XE45 > RndmCut  );}
Bool_t Bisection_Objective_Function::IsClean(){ return *passcleancuts > 0.1 && *recalbroke < 0.1; }
Bool_t Bisection_Objective_Function::PassActint(){ return (*actint) > ActintCut; }
Bool_t Bisection_Objective_Function::AlgAPass(){ return *AlgA > AlgAThreshold; }
Bool_t Bisection_Objective_Function::AlgBPass(){ return *AlgB > AlgBThreshold; }
Bool_t Bisection_Objective_Function::PassL1(){ return *metl1 > MetL1Threshold; }
