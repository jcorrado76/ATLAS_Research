#define CorrectingDistributions_cxx
#include "CorrectingDistributions.h"

void CorrectingDistributions::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
}

void CorrectingDistributions::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();

}

Bool_t CorrectingDistributions::Process(Long64_t entry)
{
   fReader.SetEntry(entry);

   if ( passedL1ZB()  && isGoodRun() ){
       if ( inMuRange( 0.0 , 10.0) ){
           MET_Correctedmu0thru10->Fill(*MET_Data, );
       }
       if ( inMuRange( 10.0, 20.0) ){
           MET_Correctedmu10thru20->Fill(*MET_Data,);
       }
       if ( inMuRange( 20.0 , 30.0) ){
           MET_Correctedmu20thru30->Fill(*MET_Data,);
       }
       if ( inMuRange( 30.0, 40.0) ){
           MET_Correctedmu30thru40->Fill(*MET_Data,);
       }
       if ( inMuRange( 40.0 , 50.0 ) ){
           MET_Correctedmu40thru50->Fill(*MET_Data,);
       }
       if ( inMuRange( 50.0 , 60.0 ) ){
           MET_Correctedmu50thru60->Fill(*MET_Data,);
       }
       if ( inMuRange( 60.0 , 70.0 ) ){
           MET_Correctedmu60thru70->Fill(*MET_Data,);
       }
   }

   return kTRUE;
}
Double CorrectingDistributions::ComputeWeight(TF1* fitFunc )
{

}
void CorrectingDistributions::SlaveTerminate(){}
void CorrectingDistributions::Terminate(){}
Bool_t PlotMETDistsVersMu::isGoodRun(){//{{{
    return (*RunNumber != 330203 && *RunNumber != 331975 && *RunNumber != 334487);
}

Bool_t PlotMETDistsVersMu::passedL1ZB(){//{{{
    return (*HLT_noalg_zb_L1ZB_passed);
}
Bool_t PlotMETDistsVersMu::inMuRange( Float_t a , Float_t b ){ //{{{
    return ( *InTimePileup > a && *InTimePileup < b );
} //}}}
