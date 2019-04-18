#ifndef ComputeL1XE50toL1XE30Efficiency_h
#define ComputeL1XE50toL1XE30Efficiency_h

#include "Jburr_Template_Selector.h"

class ComputeL1XE50toL1XE30Efficiency : public Jburr_Template_Selector {
public :
   ComputeL1XE50toL1XE30Efficiency(){ 
       for (int i = 0 ; i < Number_Mu_Bins; i++){
           Name.Form("hlt_zb_l1xe30_met_dist_mubin%d" , i );
           Title.Form("HLT ZB L1XE30 MET Distribution for %s for Actint bin %d" , Alg_Name.Data(), i);
           TH1D* tmpHist = new TH1D( Name , Title , met_dist_nbins , gevLow , gevHigh );
           tmpHist->SetLineColor( Colors[i] );
           HLT_ZB_L1XE30_MET_Distributions_by_Mubin->Add( tmpHist );

           Name.Form("hlt_zb_l1xe50_met_dist_mubin%d" , i );
           Title.Form("HLT ZB L1XE50 MET Distribution for %s for Actint bin %d" , Alg_Name.Data(), i);
           TH1D* tmpHist = new TH1D( Name , Title , met_dist_nbins , gevLow , gevHigh );
           tmpHist->SetLineColor( Colors[i] );
           HLT_ZB_L1XE50_MET_Distributions_by_Mubin->Add( tmpHist );

           EfficiencyName.Form("metL1XE50EfficiencyMubin%d", i);           
           EfficiencyTitle.Form("Efficiency of L1XE 50 As a Function of %s for %d < #mu < %d;CELL MET [GeV];#epsilon", Alg_Name.Data() , i*10,(i+1)*10);
           TEfficiency* tmpEff = new TEfficiency( EfficiencyName , EfficiencyTitle , efficiency_nbins , gevLow , gevHigh );
           tmpEff->SetLineColor( Colors[i] );
           L1XE50_Efficiency_Objects->Add( tmpEff );
       }
   }
   ~ComputeL1XE50toL1XE30Efficiency() { }
   Bool_t  Process(Long64_t entry);
   void    Terminate();
   ClassDef(ComputeL1XE50toL1XE30Efficiency,0);


   float L1XE = 50.0;
};

#endif
