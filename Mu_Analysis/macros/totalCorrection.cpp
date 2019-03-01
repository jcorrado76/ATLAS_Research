{
    TChain* zb_chain = new TChain( "METTree" , "zb_chain" );
    TChain* jetm10_chain = new TChain( "METTree", "jetm10chain");

    if (zb_chain->Add("/home/joseph/ATLAS_Research/DATA/ZB/ZB_jburr_15thru17_with_missing_et_significance.root")){
        std::cout << "Processing L1XE30toZBEfficiency..." << std::endl;
        ComputeL1XE30toZBEfficiency buildl1xe30Efficiencies = ComputeL1XE30toZBEfficiency();
        zb_chain->Process( buildl1xe30Efficiencies );
    }
    else{
        std::cout << "ZB Jburr data file not found..." << std::endl;
        return 0;
    }
    if (jetm10_chain->Add("/home/joseph/ATLAS_Research/DATA/PhysicsMain/JETM10_15thru17_with_missing_et_significance.root")){
        CorrectL1XE30toZB correctToZB( buildl1xe30Efficiencies );
        std::cout << "Processing CorrectL1XE30toZB..." << std::endl;
        jetm10_chain->Process( correctToZB );

        ComputeL1XE50toL1XE30Efficiency createL1XE50Efficiencies = ComputeL1XE50toL1XE30Efficiency();
        CorrectL1XE50toZB CorrectL1XE50DataAllWay = CorrectL1XE50toZB();
        std::cout << "Processing L1XE50toL1XE30Efficiency..." << std::endl;
        jetm10_chain->Process( createL1XE50Efficiencies );
        std::cout << "Processing CorretL1XE50toZB..." << std::endl;
        jetm10_chain->Process( CorrectL1XE50DataAllWay );
    }
    else{
        std::cout << "JETM10 Jburr data file not found..." << std::endl;
        return 0;
    }

    // TODO: take all plotting and saving of stuff out of these selectors. 
    // save the final object to a root file out here in the macro
    // plot the things in a separate macro that loads the info
}
