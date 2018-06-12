{
    TProof::Open("");
    TChain* mychain = new TChain( "METTree" , "Jburr_CELL_MET_Dists_versus_Mu" );
    mychain->Add("../data/totalntuple2015.root");
    mychain->SetProof();
    mychain->Process("PlotMETDistsVersMu.C++");
}
