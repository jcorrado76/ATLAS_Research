#define CorrectingDistributions_cxx
#include "CorrectingDistributions.h"

void CorrectingDistributions::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
    TFile* EfficiencyObjectFile = TFile::Open("../Root_Files/EfficiencyObjects.root");
    std::cout << "Getting fits from file" << std::endl;


    /* you have to pull the tefficiency objects from file here, and then get the fit function associated with them, by
     * using TEfficiency->GetFunctions("Name"). Then you can use the TF1's you got to evaluate the weight at event level
     * You have to write a function to store the MET distributions for the zerobias data, so you can read them in
     * during the plotting process. You need to plot the zerobias distributions on the same plot as the corrected
     * PhysicsMain distributions. We want to compare the corrected PhysicsMain to the zerobias 
     */
    TEfficiency* efficiencyObjectMu0thru10 = (TEfficiency*)EfficiencyObjectFile->Get("metmu0thru10Efficiency");
    TEfficiency* efficiencyObjectMu10thru20 = (TEfficiency*)EfficiencyObjectFile->Get("metmu10thru20Efficiency");
    TEfficiency* efficiencyObjectMu20thru30 = (TEfficiency*)EfficiencyObjectFile->Get("metmu20thru30Efficiency");
    TEfficiency* efficiencyObjectMu30thru40 = (TEfficiency*)EfficiencyObjectFile->Get("metmu30thru40Efficiency");
    TEfficiency* efficiencyObjectMu40thru50 = (TEfficiency*)EfficiencyObjectFile->Get("metmu40thru50Efficiency");
    TEfficiency* efficiencyObjectMu50thru60 = (TEfficiency*)EfficiencyObjectFile->Get("metmu50thru60Efficiency");
    TEfficiency* efficiencyObjectMu60thru70 = (TEfficiency*)EfficiencyObjectFile->Get("metmu60thru70Efficiency");

    EfficiencyObjectFile->Close();

     EfficiencyFitMuBin1 = (TF1*)(efficiencyObjectMu0thru10->GetListOfFunctions())->At(0);
     EfficiencyFitMuBin2 = (TF1*)(efficiencyObjectMu10thru20->GetListOfFunctions())->At(0);
     EfficiencyFitMuBin3 = (TF1*)(efficiencyObjectMu20thru30->GetListOfFunctions())->At(0);
     EfficiencyFitMuBin4 = (TF1*)(efficiencyObjectMu30thru40->GetListOfFunctions())->At(0);
     EfficiencyFitMuBin5 = (TF1*)(efficiencyObjectMu40thru50->GetListOfFunctions())->At(0);
     EfficiencyFitMuBin6 = (TF1*)(efficiencyObjectMu50thru60->GetListOfFunctions())->At(0);
     EfficiencyFitMuBin7 = (TF1*)(efficiencyObjectMu60thru70->GetListOfFunctions())->At(0);

    std::cout << "Successfully got fit objects from file" << std::endl;
    std::cout << "Name of first fit: " << EfficiencyFitMuBin1->GetName() << std::endl;
    MET_Correctedmu0thru10 = new TH1F("correctedmetmu0thru10","MET Data for actint between 0 and 10", nbins , gevLow , gevHigh );
    MET_Correctedmu10thru20 = new TH1F("correctedmetmu10thru20","MET Data for actint between 10 and 20", nbins , gevLow , gevHigh );
    MET_Correctedmu20thru30 = new TH1F("correctedmetmu20thru30","MET Data for actint between 20 and 30", nbins , gevLow , gevHigh );
    MET_Correctedmu30thru40 = new TH1F("correctedmetmu30thru40","MET Data for actint between 30 and 40", nbins , gevLow , gevHigh );
    MET_Correctedmu40thru50 = new TH1F("correctedmetmu40thru50","MET Data for actint between 40 and 50", nbins , gevLow , gevHigh );
    MET_Correctedmu50thru60 = new TH1F("correctedmetmu50thru60","MET Data for actint between 50 and 60", nbins , gevLow , gevHigh );
    MET_Correctedmu60thru70 = new TH1F("correctedmetmu60thru70","MET Data for actint between 60 and 70", nbins , gevLow , gevHigh );
}

void CorrectingDistributions::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();
}

Bool_t CorrectingDistributions::Process(Long64_t entry)
{
   fReader.SetLocalEntry(entry);

   // just make sure this is the correct flag L1XE30
   // still need to compute new error and pass it to this fill function somehow 

   if ( isPassnoAlgL1XE30() && isGoodRun() ){
       if ( inMuRange( 0.0 , 10.0) ){
           MET_Correctedmu0thru10->Fill(*cell_met, ComputeWeight(EfficiencyFitMuBin1));
       }
       if ( inMuRange( 10.0, 20.0) ){
           MET_Correctedmu10thru20->Fill(*cell_met,ComputeWeight(EfficiencyFitMuBin2));
       }
       if ( inMuRange( 20.0 , 30.0) ){
           MET_Correctedmu20thru30->Fill(*cell_met,ComputeWeight(EfficiencyFitMuBin3));
       }
       if ( inMuRange( 30.0, 40.0) ){
           MET_Correctedmu30thru40->Fill(*cell_met,ComputeWeight(EfficiencyFitMuBin4));
       }
       if ( inMuRange( 40.0 , 50.0 ) ){
           MET_Correctedmu40thru50->Fill(*cell_met,ComputeWeight(EfficiencyFitMuBin5));
       }
       if ( inMuRange( 50.0 , 60.0 ) ){
           MET_Correctedmu50thru60->Fill(*cell_met,ComputeWeight(EfficiencyFitMuBin6));
       }
       if ( inMuRange( 60.0 , 70.0 ) ){
           MET_Correctedmu60thru70->Fill(*cell_met,ComputeWeight(EfficiencyFitMuBin7));
       }
   }

   return kTRUE;
}
Double_t CorrectingDistributions::ComputeWeight(TF1* fitFunc)//{{{
{
    Float_t numerator = *HLT_noalg_L1XE30_prescale;
    Double_t denominator = fitFunc->Eval( *cell_met ); 
    return numerator / denominator; 
}//}}}
void CorrectingDistributions::SlaveTerminate(){}
void CorrectingDistributions::Terminate(){
    // color the histograms so we can see difference 
    MET_Correctedmu0thru10->SetLineColor(1);
    MET_Correctedmu10thru20->SetLineColor(2);
    MET_Correctedmu20thru30->SetLineColor(3);
    MET_Correctedmu30thru40->SetLineColor(4);
    MET_Correctedmu40thru50->SetLineColor(5);
    MET_Correctedmu50thru60->SetLineColor(6);
    MET_Correctedmu60thru70->SetLineColor(7);

    // normalize to 1 
    MET_Correctedmu0thru10->SetNormFactor(1.);
    MET_Correctedmu10thru20->SetNormFactor(1.);
    MET_Correctedmu20thru30->SetNormFactor(1.);
    MET_Correctedmu30thru40->SetNormFactor(1.);
    MET_Correctedmu40thru50->SetNormFactor(1.);
    MET_Correctedmu50thru60->SetNormFactor(1.);
    MET_Correctedmu60thru70->SetNormFactor(1.);

    MET_Correctedmu0thru10->Draw();
    MET_Correctedmu10thru20->Draw();
    MET_Correctedmu20thru30->Draw();
    MET_Correctedmu30thru40->Draw();
    MET_Correctedmu40thru50->Draw();
    MET_Correctedmu50thru60->Draw();
    MET_Correctedmu60thru70->Draw();
    
    mycanv->SetTitle("MET Slices in Mu");
    gPad->SetLogy();
    TLegend* legend = new TLegend();
    legend->AddEntry(MET_Correctedmu0thru10);
    legend->AddEntry(MET_Correctedmu10thru20);
    legend->AddEntry(MET_Correctedmu20thru30);
    legend->AddEntry(MET_Correctedmu30thru40);
    legend->AddEntry(MET_Correctedmu40thru50);
    legend->AddEntry(MET_Correctedmu50thru60);
    legend->AddEntry(MET_Correctedmu60thru70);
    legend->Draw("SAME");
    gStyle->SetOptStat(0);
}
void CorrectingDistributions::Init(TTree *tree){fReader.SetTree(tree);}
Bool_t CorrectingDistributions::Notify(){return kTRUE;}
Bool_t CorrectingDistributions::isGoodRun(){//{{{
    return (*RunNumber != 330203 && *RunNumber != 331975 && *RunNumber != 334487);
}//}}}
Bool_t CorrectingDistributions::passedL1ZB(){//{{{
    return (*HLT_noalg_zb_L1ZB_passed);
}//}}}
Bool_t CorrectingDistributions::inMuRange( Float_t a , Float_t b ){ //{{{
    return ( *InTimePileup > a && *InTimePileup < b );
} //}}}
Bool_t CorrectingDistributions::isPassnoAlgL1XE30(){ // {{{
    return (*HLT_noalg_L1XE30_passed);
} // }}}
