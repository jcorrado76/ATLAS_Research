#define ComputeL1XE30toZBEfficiency_cxx
#include "ComputeL1XE30toZBEfficiency.h"
ClassImp(ComputeL1XE30toZBEfficiency);
void ComputeL1XE30toZBEfficiency::Begin(TTree *){TString option = GetOption();}
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
               for ( int j = 0 ; j < Number_Mu_Bins ; j++ ){
                   Met_Distributions_By_Mu_Bin[j]->Fill(*MET_Data , *HLT_noalg_zb_L1ZB_prescale);
                   L1XE30_Efficiency_Objects[j]->Fill(*L1_MET > L1XE , *MET_Data);
               }
           }
       }
   }
   return kTRUE;
}//}}}
void ComputeL1XE30toZBEfficiency::Terminate() //{{{
{
    // Generate fit functions {{{
   for ( int i = 0; i < Number_Mu_Bins ; i++ ){
       L1XE30_Efficiency_Fit_Objects[i] = generateFitFunction( L1XE30_Efficiency_Objects[i] );
   }
   //}}}
    // Write MET Histograms, Efficiency Objects and Efficiency Fits to File {{{
    std::cout << "Writing the met distributions to zb_met_distributions" << std::endl;
    TFile* Mu_Analysis_File = TFile::Open("run_files/mu_analysis.root", "RECREATE");
    TDirectory* zb_met_distributions = Mu_Analysis_File->mkdir("zb_met_distributions");
    TDirectory* efficiency_curves = Mu_Analysis_File->mkdir("l1xe30_efficiency_curves");
    TDirectory* L1XE30_Efficiency_Fit_Objects_Dir = Mu_Analysis_File->mkdir("l1xe30_efficiency_fits");

    for ( int  i = 0 ; i < Number_Mu_Bins ; i++ ){
        Name.Form("zb_met_dist_mubin%d" , i );
        zb_met_distributions->WriteObject(Met_Distributions_By_Mu_Bin[i], Name);
        Name.Form("l1xe30_efficiency_object%d" , i );
        efficiency_curves->WriteObject(L1XE30_Efficiency_Objects[i], Name);
        Name.Form("l1xe30_efficiency_fit%d" , i );
        L1XE30_Efficiency_Fit_Objects_Dir->WriteObject(L1XE30_Efficiency_Fit_Objects[i], Name);
    }
    Mu_Analysis_File->Close();//}}}
}//}}}
void ComputeL1XE30toZBEfficiency::SlaveBegin(TTree*){TString option = GetOption();}
void ComputeL1XE30toZBEfficiency::SlaveTerminate(){}
void ComputeL1XE30toZBEfficiency::Init(TTree *tree){fReader.SetTree(tree);}
