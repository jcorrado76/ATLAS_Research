#define ComputeL1XE30toZBEfficiency_cxx
#include "ComputeL1XE30toZBEfficiency.h"
ClassImp(ComputeL1XE30toZBEfficiency);
void ComputeL1XE30toZBEfficiency::Begin(TTree *) // {{{
{
   TString option = GetOption();
   // fill Mu_Values
   for (int i = 0 ; i < Number_Mu_Bins + 1; i++){
       Mu_Values[i] = i * 10.;
   }
   Int_t n;
   Float_t muLow;
   Float_t muHigh;
   TString Name;
   TString Title;
   TString EfficiencyName;
   TString EfficiencyTitle;
   std::cout << "Creating the proper met distribution, l1xe30 efficiency and l1xe30 efficiency fit objects" << std::endl;
   for (int i = 0 ; i < Number_Mu_Bins ; i++){
       muLow = Mu_Values[i];
       muHigh = Mu_Values[i+1];
       Name.Form("metmu%.0fthru%.0f" , muLow , muHigh );
       EfficiencyName.Form("metmu%.0fthru%.0fEfficiency", muLow , muHigh );
       Title.Form("ZeroBias MET Distribution for %s With Actint Between %.0f and %.0f" ,Alg_Name.Data(), muLow , muHigh );
       EfficiencyTitle.Form("Efficiency of L1XE 30 As a Function of %s for Actint Between %.0f and %.0f", Alg_Name.Data() , muLow , muHigh );

       Met_Distributions_By_Mu_Bin[i] = new TH1F( Name , Title , met_dist_nbins , gevLow , gevHigh );
       L1XE30_Efficiency_Objects[i] = new TEfficiency( EfficiencyName , EfficiencyTitle , efficiency_nbins , gevLow , gevHigh );
       L1XE30_Efficiency_Fit_Objects[i] = new TF1();
   }
} // }}}
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
                   L1XE30_Efficiency_Objects[j]->Fill(*L1_MET > XE , *MET_Data);
               }
           }
       }
   }
   return kTRUE;
}//}}}
void ComputeL1XE30toZBEfficiency::Terminate() //{{{
{
    std::cout << "Setting the plotting characteristics of the l1xe30 efficiency objects, fits and the met distributions" << std::endl;
   for ( int i = 0; i < Number_Mu_Bins ; i++ ){
       L1XE30_Efficiency_Objects[i]->SetLineColor( Colors[i] );
       L1XE30_Efficiency_Objects[i]->SetMarkerStyle( Colors[i] );
       L1XE30_Efficiency_Fit_Objects[i] = generateFitFunction( L1XE30_Efficiency_Objects[i] );
       L1XE30_Efficiency_Fit_Objects[i]->SetLineColor( Colors[i] );
       Met_Distributions_By_Mu_Bin[i]->SetLineColor( Colors[i] );
   }
    // WRITE TO FILE {{{
    std::cout << "Writing the met distributions to zb_met_distributions" << std::endl;
    TFile* Mu_Analysis_File = TFile::Open("mu_analysis.root", "RECREATE");
    TDirectory* zb_met_distributions = Mu_Analysis_File->mkdir("zb_met_distributions");
    zb_met_distributions->cd();
    for ( int  i = 0 ; i < Number_Mu_Bins ; i++ ){
        Met_Distributions_By_Mu_Bin[i]->Write();
    }

    std::cout << "Writing the l1xe30 efficiency curves to l1xe30_efficiency_curves" << std::endl;
    TDirectory* efficiency_curves = Mu_Analysis_File->mkdir("l1xe30_efficiency_curves");
    efficiency_curves->cd();
    for ( int  i = 0 ; i < Number_Mu_Bins ; i++ ){
        L1XE30_Efficiency_Objects[i]->Write();
    }

    std::cout << "Writing the l1xe30 efficiency curve objects to l1xe30_efficiency_curves" << std::endl;
    TDirectory* L1XE30_Efficiency_Fit_Objects_Dir = Mu_Analysis_File->mkdir("l1xe30_efficiency_fits");
    L1XE30_Efficiency_Fit_Objects_Dir->cd();
    for ( int  i = 0 ; i < Number_Mu_Bins ; i++ ){
        L1XE30_Efficiency_Fit_Objects[i]->Write();
    }

    Mu_Analysis_File->Close();//}}}
}//}}}
void ComputeL1XE30toZBEfficiency::SlaveBegin(TTree * /*tree*/) // {{{
{
   TString option = GetOption();
} // }}}
void ComputeL1XE30toZBEfficiency::SlaveTerminate(){}
void ComputeL1XE30toZBEfficiency::Init(TTree *tree) //{{{
{
   fReader.SetTree(tree);
} //}}}
Bool_t ComputeL1XE30toZBEfficiency::Notify() //{{{
{
   return kTRUE;
} //}}}
Bool_t ComputeL1XE30toZBEfficiency::isGoodRun(){ //{{{
    return (*RunNumber != 330203 && *RunNumber != 331975 && *RunNumber != 334487);
} // }}}
Bool_t ComputeL1XE30toZBEfficiency::isHLT_zb_L1ZB(){ //{{{
    return (*HLT_noalg_zb_L1ZB_passed);
} //}}}
Bool_t ComputeL1XE30toZBEfficiency::isHLT_zb_L1XE30(){ //{{{
    return (*HLT_noalg_L1XE30_passed);
} //}}}
Bool_t ComputeL1XE30toZBEfficiency::inMuRange( Float_t a , Float_t b ){ //{{{
    return ( *InTimePileup > a && *InTimePileup < b );
} //}}}
Double_t ComputeL1XE30toZBEfficiency::fitFunction(Double_t *x , Double_t *par ){//{{{
    Float_t xx = x[0];
    Double_t l1cut = 30.0;
    Double_t fitval = (1./2.)*(1.+TMath::Erf((par[0]*x[0]+par[1]-l1cut)/(par[2]*TMath::Sqrt(2.))));
    return fitval;
}//}}}
TF1* ComputeL1XE30toZBEfficiency::generateFitFunction(TEfficiency* teff_obj, float gevMax, float initial_slope, float initial_intercept, float initial_sigma ){//{{{
    TF1 *fitErrorFunction = new TF1("fitFunction",fitFunction,0.0,gevMax,3);
    fitErrorFunction->SetParameter(0, initial_slope);
    fitErrorFunction->SetParameter(1, initial_intercept);
    fitErrorFunction->SetParameter(2, initial_sigma);
    //initializing parameters reasonably is important because it is a maximum likelihood fit
    fitErrorFunction->SetParNames("Slope","Translation","Sigma");
    //"R" tells the fit function from BinomialEfficiency::Fit to use the range of the TF1 as the fitting range
    teff_obj->Fit( fitErrorFunction  , "R+");

    std::cout << "Value of fit for a: " << fitErrorFunction->GetParameter(0) << std::endl;
    std::cout << "Value of error on a: " << fitErrorFunction->GetParError(0) << std::endl;
    std::cout << "Value of fit for b: " << fitErrorFunction->GetParameter(1) << std::endl;
    std::cout << "Value of error on b: " << fitErrorFunction->GetParError(1) << std::endl;
    std::cout << "Value of fit for sigma: " << fitErrorFunction->GetParameter(2) << std::endl;
    std::cout << "Value of error on sigma: " << fitErrorFunction->GetParError(2) << std::endl;
    return fitErrorFunction;
}//}}}
