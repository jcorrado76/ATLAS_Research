#define Print_7_Efficiencies_Selector_cxx

#include "Print_7_Efficiencies_Selector.h"
#include <TH2.h>
#include <TStyle.h>

void Print_7_Efficiencies_Selector::Begin(TTree * /*tree*/)
{

   TString option = GetOption();
}

void Print_7_Efficiencies_Selector::SlaveBegin(TTree * /*tree*/)
{

   TString option = GetOption();
    //individuals
    cellTeff  = new TEfficiency("metcell" , "Efficiency", nbins, metMin, metMax);
    mhtTeff  = new TEfficiency("metmht", "Efficiency", nbins, metMin, metMax);
    topoclpucTeff  = new TEfficiency("mettopocl",  "Efficiency", nbins, metMin, metMax);

    ///combined algs
    cellmhtTeff  = new TEfficiency("cellmhtcombined" , "Efficiency", nbins, metMin, metMax);
    mhttopoclpucTeff  = new TEfficiency("mhttopoclpuccombined" , "Efficiency", nbins, metMin, metMax);


   fOutput->Add(cellTeff);
   fOutput->Add(mhtTeff);
   fOutput->Add(topoclpucTeff);
   fOutput->Add(cellmhtTeff);
   fOutput->Add(mhttopoclpucTeff);


}

Bool_t Print_7_Efficiencies_Selector::Process(Long64_t entry)
{

   fReader.SetEntry(entry);

    metnomu = Compute_MetNoMu();



   if ( PassTransverseMassCut() && Is_Clean() && Is_Muon() && *actint > actintCut )
   {


    cellTeff->Fill( ( *metcell > cellThresh) &&  ( *metl1 > metl1thresh) &&
                        ( *actint > actintCut), metnomu);

    mhtTeff->Fill( ( *metmht > mhtThresh) && ( *metl1 > metl1thresh) &&
                        ( *actint > actintCut), metnomu);

    topoclpucTeff->Fill( ( *mettopoclpuc > topoclpucThresh) &&  ( *metl1 > metl1thresh) &&
                        ( *actint > actintCut),  metnomu);

    cellmhtTeff->Fill( ( *metcell > cellCombinedThresh) && 
            ( *metmht > mhtCombinedThresh)&& 
            ( *metl1 > metl1thresh) &&
                        ( *actint > actintCut), metnomu );

    mhttopoclpucTeff->Fill( ( ( *metmht > mhtCombined2Thresh) && 
                ( *mettopoclpuc > topoclpucCombinedThresh) && 
                ( *metl1 > metl1thresh))&&
                        ( *actint > actintCut) , metnomu);
   }

   return kTRUE;
}

void Print_7_Efficiencies_Selector::SlaveTerminate()
{

}

void Print_7_Efficiencies_Selector::Terminate()
{
    TCanvas* Efficiency_Canvas = new TCanvas("myCanv", "Efficiency Canvas");
    Efficiency_Canvas->RangeAxis(0,0,500,1.0);

    cellTeff->SetLineColor(kBlue);
    mhtTeff->SetLineColor(kRed);
    topoclpucTeff->SetLineColor(kGreen);
    cellmhtTeff->SetLineColor(kBlack);
    mhttopoclpucTeff->SetLineColor(kTeal);


    const TString canvName = "Efficiency Best Combination vs Best Individual;Offline Recalibrated MET w/o Muon term [GeV];Efficiency";

    cellTeff->SetTitle(canvName);

    cellTeff->Draw();
    mhtTeff->Draw("same");
    topoclpucTeff->Draw("same");
    cellmhtTeff->Draw("same");
    mhttopoclpucTeff->Draw("same");


    TLegend *legend = new TLegend(0.57,0.15,0.9, 0.4 ,"","NDC");
    legend->AddEntry(cellTeff, "metcell");
    legend->AddEntry(mhtTeff, "metmht");
    legend->AddEntry(topoclpucTeff, "mettopoclpuc");
    legend->AddEntry(cellmhtTeff, "cell and mht");
    legend->AddEntry(mhttopoclpucTeff, "mht and topoclpuc");
    legend->Draw();

    Efficiency_Canvas->Draw();



/*
    TString folderPath = "./pictures/BestCombinationefficiencies.tiff";
    TString bestCombinationRootFileName = "./pictures/EfficiencyBestCombination.root";
    TFile rootFile(bestCombinationRootFileName,"CREATE");

    if ( !( rootFile.IsOpen() ) )
        {
            TString suffix = "";
            std::cout << "Unable to open file" << std::endl;
            std::cout << "Enter run number: ";
            std::cin >> suffix;
            suffix = "(" + suffix + ")";
            bestCombinationRootFileName.Insert( (bestCombinationRootFileName.Length()-5),suffix);
            rootFile.Open( bestCombinationRootFileName ,"RECREATE");
            folderPath.Insert( (folderPath.Length()-5),suffix);
        }

    std::cout << "Root file successfully opened" << std::endl;

    Efficiency_Canvas->Write();
    cellTeff->Write();
    mhtTeff->Write();
    topoclpucTeff->Write();
    cellmhtTeff->Write();
    mhttopoclpucTeff->Write();


    Efficiency_Canvas->Print(folderPath);
*/
}
