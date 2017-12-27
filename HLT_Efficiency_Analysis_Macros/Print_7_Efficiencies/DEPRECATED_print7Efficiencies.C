#include"mincerMacros.h"

Int_t print7Efficiencies(const TString& muonFileName = "PhysicsMain.L1KFmuontriggers.2016.f731f758_m1659m1710.Run309759.48Runs.root")
{
    /* makes a plot with all 7 efficiency curves*/
    /* This plot compares the 4 combined algorithms that do better when used together, and plots them
    on the same canvas as the algorithms CERN currently uses
    4 that do better: (metcell, metmht) , (metcell , mettopocl) , (mettcell , mettopoclps) , (metmht , mettopoclpuc)
    3 individually: metmht ; metcell ; mettopoclpuc
    */

    Bool_t passTransverseMassCut( const Float_t , const Float_t ,const Float_t ,const Float_t ,const Float_t ,const Float_t);




    //parameters
    Int_t nbins = 300;
    Float_t metMin = 0.0;
    Float_t metMax = 300.0;
    Float_t metl1thresh = 50.0;
    Float_t actintCut = 35.0;

    //individual thresholds
    Float_t cellThresh = 94.88;
    Float_t mhtThresh = 144.38;
    Float_t topoclpucThresh = 121.62;

    //combined pairs of threhsolds
    Float_t cellCombinedThresh = 81.12;
    Float_t mhtCombinedThresh = 116.62;

    Float_t mhtCombined2Thresh = 123.62;
    Float_t topoclpucCombinedThresh = 106.38;

    //individuals
    TEfficiency* cellTeff  = new TEfficiency("metcell" , "Efficiency", nbins, metMin, metMax);
    TEfficiency* mhtTeff  = new TEfficiency("metmht", "Efficiency", nbins, metMin, metMax);
    TEfficiency* topoclpucTeff  = new TEfficiency("mettopocl",  "Efficiency", nbins, metMin, metMax);

    ///combined algs
    TEfficiency* cellmhtTeff  = new TEfficiency("cellmhtcombined" , "Efficiency", nbins, metMin, metMax);
    TEfficiency* mhttopoclpucTeff  = new TEfficiency("mhttopoclpuccombined" , "Efficiency", nbins, metMin, metMax);

    //initialize branch variables

    ///open muon tree
    TString muonFilePath = "../myData/"+muonFileName;
    TFile * muonFile = TFile::Open(muonFilePath, "READ");
    TTree* myMuonTree = (TTree*)muonFile->Get("tree");
    Int_t muonNentries = myMuonTree->GetEntries();


    Float_t metcell,metmht,metl1,mettopocl,mettopoclps,mettopoclpuc,metoffrecal,mexoffrecal,
    meyoffrecal,metoffrecalmuon,mexoffrecalmuon,meyoffrecalmuon,actint;
    Int_t passmuon,passmuvarmed,cleanCutsFlag,recalBrokeFlag;

    //assign branch variables to locations
    myMuonTree->SetBranchAddress("metcell",&metcell);
    myMuonTree->SetBranchAddress("metmht",&metmht);
    myMuonTree->SetBranchAddress("metl1",&metl1);
    myMuonTree->SetBranchAddress("mettopocl",&mettopocl);
    myMuonTree->SetBranchAddress("mettopoclps",&mettopoclps);
    myMuonTree->SetBranchAddress("mettopoclpuc",&mettopoclpuc);

    myMuonTree->SetBranchAddress("passmu26med", &passmuon);
    myMuonTree->SetBranchAddress("passmu26varmed", &passmuvarmed);
    myMuonTree->SetBranchAddress("passcleancuts", &cleanCutsFlag);
    myMuonTree->SetBranchAddress("recalbroke", &recalBrokeFlag);
    myMuonTree->SetBranchAddress("metoffrecal", &metoffrecal);
    myMuonTree->SetBranchAddress("mexoffrecal", &mexoffrecal);
    myMuonTree->SetBranchAddress("meyoffrecal", &meyoffrecal);
    myMuonTree->SetBranchAddress("metoffrecalmuon", &metoffrecalmuon);
    myMuonTree->SetBranchAddress("mexoffrecalmuon", &mexoffrecalmuon);
    myMuonTree->SetBranchAddress("meyoffrecalmuon", &meyoffrecalmuon);
    myMuonTree->SetBranchAddress("actint", &actint);

    Bool_t isMuon,isClean;

    for (Int_t l = 0 ; l < muonNentries ; l++)
    {
        myMuonTree->GetEntry(l);

        isMuon = (passmuvarmed > 0.1 || passmuon > 0.1);
        isClean = (cleanCutsFlag > 0.1) && (recalBrokeFlag < 0.1);
        {
            if (isMuon && isClean && actint > actintCut )
            {
                if ( passTransverseMassCut(metoffrecal,mexoffrecal,meyoffrecal,metoffrecalmuon,mexoffrecalmuon,meyoffrecalmuon) )
                {
        	        Float_t metnomu = computeMetNoMu(  mexoffrecal , meyoffrecal , mexoffrecalmuon , meyoffrecalmuon );
                    
               //metcell         
                    cellTeff->Fill( (metcell > cellThresh) && 
                                      (metl1 > metl1thresh)&&
                                        (actint > actintCut), metnomu);
//memht
                    mhtTeff->Fill( (metmht > mhtThresh) && 
                            (metl1 > metl1thresh)&&
                            (actint > actintCut), metnomu);
//mettopoclpuc
                    topoclpucTeff->Fill( (mettopoclpuc > topoclpucThresh) && 
                            (metl1 > metl1thresh)&&
                            (actint > actintCut),  metnomu);
//metcell && metmht
                    cellmhtTeff->Fill( (metcell > cellCombinedThresh) && 
                            (metmht > mhtCombinedThresh)&& 
                            (metl1 > metl1thresh)&&
                            (actint > actintCut), metnomu );
//metmht && mettopoclpuc 
                    mhttopoclpucTeff->Fill( ( (metmht > mhtCombined2Thresh) && 
                                (mettopoclpuc > topoclpucCombinedThresh) && 
                                (metl1 > metl1thresh)&&
                                (actint > actintCut)), metnomu);
           
                }
            }
        }
    }

    std::cout << "Number of events that passed all cuts, except for the cut on the alg itself (includes L1, etc.) ";

    TCanvas* efficiencyCanvas = new TCanvas("myCanv", "Efficiency Canvas");
    efficiencyCanvas->RangeAxis(0,0,500,1.0);

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

    efficiencyCanvas->Write();
    cellTeff->Write();
    mhtTeff->Write();
    topoclpucTeff->Write();
    cellmhtTeff->Write();
    mhttopoclpucTeff->Write();


    efficiencyCanvas->Print(folderPath);
    return(0);
}
