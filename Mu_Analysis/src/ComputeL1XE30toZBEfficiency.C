#define ComputeL1XE30toZBEfficiency_cxx
#include "ComputeL1XE30toZBEfficiency.h"
ClassImp(ComputeL1XE30toZBEfficiency);
Bool_t ComputeL1XE30toZBEfficiency::Process(Long64_t entry)//{{{
{
   fReader.SetLocalEntry(entry);
   // if the event has passed HLT_noalg_zb_L1ZB_passed, and is not one of the bad run numbers
   if ( isHLT_zb_L1ZB()  && isGoodRun() ){
       Float_t muLow, muHigh;
       for ( int i = 0; i < Number_Mu_Bins ; i++ ){
           muLow = Mu_Values[ i ];
           muHigh = Mu_Values[ i + 1 ];
           if ( inMuRange( muLow , muHigh ) ){
               HLT_ZB_L1ZB_MET_Distributions_by_Mubin.at(i)->Fill(*cell_met , *HLT_noalg_zb_L1ZB_prescale);
               L1XE30_Efficiency_Objects.at(i)->Fill(*L1_met > L1XE , *cell_met);
           }
       }
   }
   return kTRUE;
}//}}}
void ComputeL1XE30toZBEfficiency::Terminate() //{{{
{
    // create the fit function for the l1xe30 efficiencies
    for ( int i = 0; i < Number_Mu_Bins ; i++ ){
    L1XE30_Efficiency_Fit_Objects[i] = generateFitFunction( L1XE30_Efficiency_Objects[i] );
    }
    // writing to file doesn't need to happen in here anymore
    //
    //TFile* Mu_Analysis_File = TFile::Open("run_files/mu_analysis.root", "RECREATE");
    //TDirectory* zb_met_distributions = Mu_Analysis_File->mkdir("hlt_zb_l1zb_met_distributions");
    //TDirectory* efficiency_curves = Mu_Analysis_File->mkdir("l1xe30_efficiency_curves");
    //TDirectory* L1XE30_Efficiency_Fit_Objects_Dir = Mu_Analysis_File->mkdir("l1xe30_efficiency_fits");

    //for ( int  i = 0 ; i < Number_Mu_Bins ; i++ ){
        //Name.Form("hlt_zb_l1zb_met_dist_mubin%d" , i );
        //zb_met_distributions->WriteObject(HLT_ZB_L1ZB_MET_Distributions_by_Mubin[i], Name);
        //Name.Form("l1xe30_efficiency_object%d" , i );
        //efficiency_curves->WriteObject(L1XE30_Efficiency_Objects[i], Name);
        //Name.Form("l1xe30_efficiency_fit%d" , i );
        //L1XE30_Efficiency_Fit_Objects_Dir->WriteObject(L1XE30_Efficiency_Fit_Objects[i], Name);
    //}
    //Mu_Analysis_File->Close();
}//}}}
