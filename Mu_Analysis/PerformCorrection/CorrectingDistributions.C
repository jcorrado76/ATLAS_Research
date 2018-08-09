#define CorrectingDistributions_cxx
#include "CorrectingDistributions.h"

void CorrectingDistributions::Begin(TTree * /*tree*/)
{
   TString option = GetOption();

    // GET EFFICIENCY OBJECTS FROM FILE 
    TFile* EfficiencyObjectFile = TFile::Open("../Root_Files/EfficiencyObjects.root");
    std::cout << "Getting fits from file" << std::endl;
    efficiencyObjectMu0thru10 = (TEfficiency*)EfficiencyObjectFile->Get("metmu0thru10Efficiency");
    efficiencyObjectMu10thru20 = (TEfficiency*)EfficiencyObjectFile->Get("metmu10thru20Efficiency");
    efficiencyObjectMu20thru30 = (TEfficiency*)EfficiencyObjectFile->Get("metmu20thru30Efficiency");
    efficiencyObjectMu30thru40 = (TEfficiency*)EfficiencyObjectFile->Get("metmu30thru40Efficiency");
    efficiencyObjectMu40thru50 = (TEfficiency*)EfficiencyObjectFile->Get("metmu40thru50Efficiency");
    efficiencyObjectMu50thru60 = (TEfficiency*)EfficiencyObjectFile->Get("metmu50thru60Efficiency");
    efficiencyObjectMu60thru70 = (TEfficiency*)EfficiencyObjectFile->Get("metmu60thru70Efficiency");
    std::cout << "Name of first efficiency object: " << efficiencyObjectMu0thru10->GetName() << std::endl;
    std::cout << "Name of last efficiency object: " << efficiencyObjectMu60thru70->GetName() << std::endl;

	// GET FIT FUNCTIONS ATTACHED TO THE EFFICIENCY OBJECTS
	 EfficiencyFitMuBin1 = (TF1*)(efficiencyObjectMu0thru10->GetListOfFunctions())->At(0);
	 EfficiencyFitMuBin2 = (TF1*)(efficiencyObjectMu10thru20->GetListOfFunctions())->At(0);
	 EfficiencyFitMuBin3 = (TF1*)(efficiencyObjectMu20thru30->GetListOfFunctions())->At(0);
	 EfficiencyFitMuBin4 = (TF1*)(efficiencyObjectMu30thru40->GetListOfFunctions())->At(0);
	 EfficiencyFitMuBin5 = (TF1*)(efficiencyObjectMu40thru50->GetListOfFunctions())->At(0);
	 EfficiencyFitMuBin6 = (TF1*)(efficiencyObjectMu50thru60->GetListOfFunctions())->At(0);
	 EfficiencyFitMuBin7 = (TF1*)(efficiencyObjectMu60thru70->GetListOfFunctions())->At(0);

	// INITIALIZE THE NEW CORRECTED DISTRIBUTIONS
    std::cout << "Initializing histograms to contain the corrected data" << std::endl;
    MET_Correctedmu0thru10 = new TH1F("correctedmetmu0thru10","Corrected Data for actint between 0 and 10", nbins , gevLow , gevHigh );
    MET_Correctedmu10thru20 = new TH1F("correctedmetmu10thru20","Corrected Data for actint between 10 and 20", nbins , gevLow , gevHigh );
    MET_Correctedmu20thru30 = new TH1F("correctedmetmu20thru30","Corrected Data for actint between 20 and 30", nbins , gevLow , gevHigh );
    MET_Correctedmu30thru40 = new TH1F("correctedmetmu30thru40","Corrected Data for actint between 30 to 40", nbins , gevLow , gevHigh );
    MET_Correctedmu40thru50 = new TH1F("correctedmetmu40thru50","Corrected Data for actint between 40 to 50", nbins , gevLow , gevHigh );
    MET_Correctedmu50thru60 = new TH1F("correctedmetmu50thru60","Corrected Data for actint between 50 and 60", nbins , gevLow , gevHigh );
    MET_Correctedmu60thru70 = new TH1F("correctedmetmu60thru70","Corrected Data for actint between 60 and 70", nbins , gevLow , gevHigh );

    EfficiencyObjectFile->Close();

    std::cout << "Closed the efficiency object file" << std::endl;
}

void CorrectingDistributions::SlaveBegin(TTree * /*tree*/)//{{{
{
   TString option = GetOption();
}//}}}

Bool_t CorrectingDistributions::Process(Long64_t entry)
{
   fReader.SetLocalEntry(entry);

   std::cout << "Hello world" << std::endl;
   std::cout << *InTimePileup << std::endl;
   // just make sure this is the correct flag L1XE30
   // still need to compute new error and pass it to this fill function somehow 

   // if the entry is passnoalg L1XE30, and it one of the good runs
   if ( isPassnoAlgL1XE30() && isGoodRun() ){
       std::cout << "Entered first layer of logic" << std::endl;
       if ( inMuRange( 0.0 , 10.0) ){
           std::cout << "is in mu range" << std::endl;
           MET_Correctedmu0thru10->Fill(*cell_met, ComputeWeight(EfficiencyFitMuBin1));
           std::cout << "Was able to reference cell met and use compute weight on the efficiency fit mu bin 1" << std::endl;
       }
       if ( inMuRange( 10.0, 20.0) ){
           MET_Correctedmu10thru20->Fill(*cell_met,ComputeWeight( EfficiencyFitMuBin2));
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

    // normalize to 1 
    MET_Correctedmu0thru10->SetNormFactor(1.);
    MET_Correctedmu10thru20->SetNormFactor(1.);
    MET_Correctedmu20thru30->SetNormFactor(1.);
    MET_Correctedmu30thru40->SetNormFactor(1.);
    MET_Correctedmu40thru50->SetNormFactor(1.);
    MET_Correctedmu50thru60->SetNormFactor(1.);
    MET_Correctedmu60thru70->SetNormFactor(1.);


    TCanvas* correctedCanvas = new TCanvas("correctedCanvas","Canvas with corrected data");
    MET_Correctedmu0thru10->SetLineColor(2);
    MET_Correctedmu10thru20->SetLineColor(3);
    MET_Correctedmu20thru30->SetLineColor(4);
    MET_Correctedmu30thru40->SetLineColor(44);
    MET_Correctedmu40thru50->SetLineColor(6);
    MET_Correctedmu50thru60->SetLineColor(7);
    MET_Correctedmu60thru70->SetLineColor(8);
    MET_Correctedmu0thru10->Draw();
    MET_Correctedmu10thru20->Draw("SAME");
    MET_Correctedmu20thru30->Draw("SAME");
    MET_Correctedmu30thru40->Draw("SAME");
    MET_Correctedmu40thru50->Draw("SAME");
    MET_Correctedmu50thru60->Draw("SAME");
    MET_Correctedmu60thru70->Draw("SAME");
	TLegend* correctedLegend = new TLegend();
	correctedLegend->AddEntry(MET_Correctedmu0thru10);
	correctedLegend->AddEntry(MET_Correctedmu10thru20);
	correctedLegend->AddEntry(MET_Correctedmu20thru30);
	correctedLegend->AddEntry(MET_Correctedmu30thru40);
	correctedLegend->AddEntry(MET_Correctedmu40thru50);
	correctedLegend->AddEntry(MET_Correctedmu50thru60);
	correctedLegend->AddEntry(MET_Correctedmu60thru70);
	correctedCanvas->Draw("SAME");

	// GET ZEROBIAS DISTRIBUTIONS FROM FILE 
    TFile* zb_MET_File = TFile::Open("../Root_Files/ZB_MET_Distributions.root");
    TH1F* zbMETMuBin0thru10 = (TH1F*)zb_MET_File->Get("metmu0thru10");
    TH1F* zbMETMuBin10thru20 = (TH1F*)zb_MET_File->Get("metmu10thru20");
    TH1F* zbMETMuBin20thru30 = (TH1F*)zb_MET_File->Get("metmu20thru30");
    TH1F* zbMETMuBin30thru40 = (TH1F*)zb_MET_File->Get("metmu30thru40");
    TH1F* zbMETMuBin40thru50 = (TH1F*)zb_MET_File->Get("metmu40thru50");
    TH1F* zbMETMuBin50thru60 = (TH1F*)zb_MET_File->Get("metmu50thru60");
    TH1F* zbMETMuBin60thru70 = (TH1F*)zb_MET_File->Get("metmu60thru70");
	std::cout << "Name of the first zb cell met distribution object: " << zbMETMuBin0thru10->GetName() << std::endl;
	std::cout << "Name of the last zb Cell met distribution object: " << zbMETMuBin10thru20->GetName() << std::endl;

	// PLOT ZERO BIAS DISTRIBUTIONS
	TCanvas* zb_MET_Canvas = new TCanvas("zbCanvas","Canvas with zerobias data");
    zbMETMuBin0thru10->SetLineColor(2);
    zbMETMuBin10thru20->SetLineColor(3);
    zbMETMuBin20thru30->SetLineColor(4);
    zbMETMuBin30thru40->SetLineColor(44);
    zbMETMuBin40thru50->SetLineColor(6);
    zbMETMuBin50thru60->SetLineColor(7);
    zbMETMuBin60thru70->SetLineColor(8);
    zbMETMuBin0thru10->Draw();
    zbMETMuBin10thru20->Draw("SAME");
    zbMETMuBin20thru30->Draw("SAME");
    zbMETMuBin30thru40->Draw("SAME");
    zbMETMuBin40thru50->Draw("SAME");
    zbMETMuBin50thru60->Draw("SAME");
    zbMETMuBin60thru70->Draw("SAME");
	zb_MET_Canvas->Draw();

    zb_MET_File->Close();
/*
    std::cout << "Starting to draw canvases" << std::endl;
    TCanvas* canvMuBin1 = new TCanvas("c1","Canvas for Mu Bin 0 to 10");
    zbMETMuBin0thru10->Draw();
    MET_Correctedmu0thru10->Draw("SAME");
    TLegend* legend1 = new TLegend();
    legend1->AddEntry(MET_Correctedmu0thru10);
    legend1->AddEntry(zbMETMuBin0thru10);
    legend1->Draw("SAME");


    TCanvas* canvMuBin2 = new TCanvas("c2","Canvas for Mu Bin 10 to 20");
    zbMETMuBin10thru20->Draw();
    MET_Correctedmu10thru20->Draw("SAME");
    TLegend* legend2 = new TLegend();
    legend2->AddEntry(MET_Correctedmu10thru20);
    legend2->AddEntry(zbMETMuBin10thru20);
    legend2->Draw("SAME");

    TCanvas* canvMuBin3 = new TCanvas("c3","Canvas for Mu Bin 20 to 30");
    MET_Correctedmu20thru30->Draw();
    zbMETMuBin20thru30->Draw("SAME");
    TLegend* legend3 = new TLegend();
    legend3->AddEntry(MET_Correctedmu20thru30);
    legend3->AddEntry(zbMETMuBin20thru30);
    legend3->Draw("SAME");

    TCanvas* canvMuBin4 = new TCanvas("c4","Canvas for Mu Bin 30 to 40");
    MET_Correctedmu30thru40->Draw();
    zbMETMuBin30thru40->Draw("SAME");
    TLegend* legend4 = new TLegend();
    legend4->AddEntry(MET_Correctedmu30thru40);
    legend4->AddEntry(zbMETMuBin30thru40);
    legend4->Draw("SAME");

    TCanvas* canvMuBin5 = new TCanvas("c5","Canvas for Mu Bin 40 to 50");
    zbMETMuBin40thru50->Draw();
    MET_Correctedmu40thru50->Draw("SAME");
    TLegend* legend5 = new TLegend();
    legend5->AddEntry(MET_Correctedmu40thru50);
    legend5->AddEntry(zbMETMuBin40thru50);
    legend5->Draw("SAME");

    TCanvas* canvMuBin6 = new TCanvas("c6","Canvas for Mu Bin 50 to 60");
    MET_Correctedmu50thru60->Draw();
    zbMETMuBin50thru60->Draw("SAME");
    TLegend* legend6 = new TLegend();
    legend6->AddEntry(MET_Correctedmu50thru60);
    legend6->AddEntry(zbMETMuBin50thru60);
    legend6->Draw("SAME");

    TCanvas* canvMuBin7 = new TCanvas("c7","Canvas for Mu Bin 60 to 70");
    MET_Correctedmu60thru70->Draw();
    zbMETMuBin60thru70->Draw("SAME");
    TLegend* legend7 = new TLegend();
    legend7->AddEntry(MET_Correctedmu60thru70);
    legend7->AddEntry(zbMETMuBin60thru70);
    legend7->Draw("SAME");


*/   
    /*
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
    */
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
    try{
        std::cout << "Trying to de-reference in time pileup" << std::endl;
        *InTimePileup;
    }
    catch (int n){
        std::cout << "Could not de-reference InTimePileup" << std::endl;
    }

    return ( *InTimePileup > a && *InTimePileup < b );
} //}}}
Bool_t CorrectingDistributions::isPassnoAlgL1XE30(){ // {{{
    return (*HLT_noalg_L1XE30_passed);
} // }}}
