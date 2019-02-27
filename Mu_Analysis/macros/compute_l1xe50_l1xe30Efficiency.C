{
    ComputeL1XE50toL1XE30Efficiency* myAnalysis = new ComputeL1XE50toL1XE30Efficiency();
    TChain* mychain = new TChain( "METTree" , "mychain" );
    mychain->Add("/home/joseph/ATLAS_Research/DATA/PhysicsMain/JETM10_15thru17_with_missing_et_significance.root");
    mychain->Process(myAnalysis);
}

