#define CorrectingDistributions_cxx
#include "CorrectingDistributions.h"

void CorrectingDistributions::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
    TFile* myfile = TFile::Open("../fitEfficiencies/EfficiencyFits.root");
    std::cout << "Getting fits from file" << std::endl;
     EfficiencyFitMuBin1 = (TF1*)myfile->Get("metmu0thru10Fit");
    std::cout << "First efficiency object name: " << MET_Algmu0thru10Efficiency->GetName() << std::endl;
     EfficiencyFitMuBin2 =(TF1*)myfile->Get("metmu10thru20Fit");
     EfficiencyFitMuBin3 = (TF1*)myfile->Get("metmu20thru30Fit");
     EfficiencyFitMuBin4 = (TF1*)myfile->Get("metmu30thru40Fit");
     EfficiencyFitMuBin5 = (TF1*)myfile->Get("metmu40thru50Fit");
     EfficiencyFitMuBin6 = (TF1*)myfile->Get("metmu50thru60Fit");
     EfficiencyFitMuBin7 = (TF1*)myfile->Get("metmu60thru70Fit");
    std::cout << "Successfully got fit objects from file" << std::endl;
}

void CorrectingDistributions::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();

}

Bool_t CorrectingDistributions::Process(Long64_t entry)
{
   fReader.SetEntry(entry);

   if ( isPassnoAlgL1XE30() && isGoodRun() ){
       if ( inMuRange( 0.0 , 10.0) ){
           MET_Correctedmu0thru10->Fill(*MET_Data, ComputeWeight(EfficiencyFitMuBin1));
       }
       if ( inMuRange( 10.0, 20.0) ){
           MET_Correctedmu10thru20->Fill(*MET_Data,ComputeWeight(EfficiencyFitMuBin2));
       }
       if ( inMuRange( 20.0 , 30.0) ){
           MET_Correctedmu20thru30->Fill(*MET_Data,ComputeWeight(EfficiencyFitMuBin3));
       }
       if ( inMuRange( 30.0, 40.0) ){
           MET_Correctedmu30thru40->Fill(*MET_Data,ComputeWeight(EfficiencyFitMuBin4));
       }
       if ( inMuRange( 40.0 , 50.0 ) ){
           MET_Correctedmu40thru50->Fill(*MET_Data,ComputeWeight(EfficiencyFitMuBin5));
       }
       if ( inMuRange( 50.0 , 60.0 ) ){
           MET_Correctedmu50thru60->Fill(*MET_Data,ComputeWeight(EfficiencyFitMuBin6));
       }
       if ( inMuRange( 60.0 , 70.0 ) ){
           MET_Correctedmu60thru70->Fill(*MET_Data,ComputeWeight(EfficiencyFitMuBin7));
       }
   }

   return kTRUE;
}
Double_t CorrectingDistributions::ComputeWeight(TF1* fitFunc)
{
    Float_t numerator = *HLT_noalg_L1XE30_prescale;
    Double_t denominator = fitFunc->Eval( *cell_met ); 
    return numerator / denominator; 
}
void CorrectingDistributions::SlaveTerminate(){}
void CorrectingDistributions::Terminate(){}
void CorrectingDistributions::Init(TTree *tree){fReader.SetTree(tree);}
Bool_t CorrectingDistributions::Notify(){return kTRUE;}
Bool_t PlotMETDistsVersMu::isGoodRun(){//{{{
    return (*RunNumber != 330203 && *RunNumber != 331975 && *RunNumber != 334487);
}

Bool_t PlotMETDistsVersMu::passedL1ZB(){//{{{
    return (*HLT_noalg_zb_L1ZB_passed);
}
Bool_t PlotMETDistsVersMu::inMuRange( Float_t a , Float_t b ){ //{{{
    return ( *InTimePileup > a && *InTimePileup < b );
} //}}}
Bool_t L1XEefficiencySelector::isPassnoAlgL1XE30(){ // {{{
    return (*HLT_noalg_L1XE30_passed);
} // }}}
