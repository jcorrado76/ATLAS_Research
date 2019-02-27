{
    //ComputeL1XE30toZBEfficiency* myAnalysis = (ComputeL1XE30toZBEfficiency*)TSelector::GetSelector("ComputeL1XE30toZBEfficiency.C");
    ComputeL1XE30toZBEfficiency* myAnalysis = new ComputeL1XE30toZBEfficiency();
    TChain* mychain = new TChain( "METTree" , "mychain" );
    mychain->Add("/home/joseph/ATLAS_Research/DATA/ZB/ZB_jburr_15thru17_with_missing_et_significance.root");
    mychain->Process(myAnalysis);
}

