{
    TChain* zb_chain = new TChain( "METTree" , "zb_chain" );
    TChain* jetm10_chain = new TChain( "METTree", "jetm10chain");
    zb_chain->Add("/home/joseph/ATLAS_Research/DATA/ZB/ZB_jburr_15thru17_with_missing_et_significance.root");
    jetm10_chain->Add("/home/joseph/ATLAS_Research/DATA/PhysicsMain/JETM10_15thru17_with_missing_et_significance.root");

    ComputeL1XE30toZBEfficiency* buildl1xe30Efficiencies = new ComputeL1XE30toZBEfficiency();
    CorrectL1XE30toZB* correctToZB = new CorrectL1XE30toZB();
    ComputeL1XE50toL1XE30Efficiency* createL1XE50Efficiencies = new ComputeL1XE50toL1XE30Efficiency();
    CorrectL1XE50toZB* CorrectL1XE50DataAllWay = new CorrectL1XE50toZB();

    std::cout << "Processing L1XE30toZBEfficiency..." << std::endl;
    zb_chain->Process( buildl1xe30Efficiencies );
    std::cout << "Processing CorrectL1XE30toZB..." << std::endl;
    jetm10_chain->Process( correctToZB );
    std::cout << "Processing L1XE50toL1XE30Efficiency..." << std::endl;
    jetm10_chain->Process( createL1XE50Efficiencies );
    std::cout << "Processing CorretL1XE50toZB..." << std::endl;
    jetm10_chain->Process( CorrectL1XE50DataAllWay );
}
