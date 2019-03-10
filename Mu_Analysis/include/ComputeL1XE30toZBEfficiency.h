#ifndef ComputeL1XE30toZBEfficiency_h
#define ComputeL1XE30toZBEfficiency_h
#include "Jburr_Template_Selector.h"
class ComputeL1XE30toZBEfficiency : public Jburr_Template_Selector {
public :
   ComputeL1XE30toZBEfficiency(){
       for (int i = 0 ; i < Number_Mu_Bins; i++){
           Name.Form("hlt_zb_l1zb_met_dist_mubin%d" , i );
           Title.Form("HLT ZB L1ZB MET Distribution for %s for Actint bin %d" , Alg_Name.Data(), i);
           TH1F* tmpHist = new TH1F( Name , Title , met_dist_nbins , gevLow , gevHigh );
           HLT_ZB_L1ZB_MET_Distributions_by_Mubin->Add( tmpHist );
           ((TH1F*)HLT_ZB_L1ZB_MET_Distributions_by_Mubin->At(i))->SetLineColor( Colors[i] );

           EfficiencyName.Form("metL1XE30EfficiencyMubin%d", i);
           EfficiencyTitle.Form("Efficiency of L1XE 30 As a Function of %s for Actint bin %d", Alg_Name.Data() , i);
           TEfficiency* tmpEff = new TEfficiency( EfficiencyName , EfficiencyTitle , efficiency_nbins , gevLow , gevHigh );
           L1XE30_Efficiency_Objects->Add( tmpEff );
           TF1* tmpTF = new TF1();
           L1XE30_Efficiency_Fit_Objects->Add( tmpTF );

           ((TEfficiency*)L1XE30_Efficiency_Objects->At(i))->SetLineColor( Colors[i] );
           ((TEfficiency*)L1XE30_Efficiency_Objects->At(i))->SetMarkerStyle( Colors[i] );
           ((TF1*)L1XE30_Efficiency_Fit_Objects->At(i))->SetLineColor( Colors[i] );
       }
   }
   ~ComputeL1XE30toZBEfficiency() { };
   Bool_t  Process(Long64_t entry);
   void    Terminate();
   ClassDef(ComputeL1XE30toZBEfficiency,0);

   float L1XE = 30.0;
};
#endif 
