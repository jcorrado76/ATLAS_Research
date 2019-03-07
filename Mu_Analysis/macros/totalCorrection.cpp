{
    // initialize tchains
    TChain* zb_chain = new TChain( "METTree" , "zb_chain" );
    TChain* jetm10_chain = new TChain( "METTree", "jetm10chain");

    // if successfully get the jburr zb data
    if (zb_chain->Add("/home/joseph/ATLAS_Research/DATA/ZB/ZB_jburr_15thru17_with_missing_et_significance.root")){
        std::cout << "Processing L1XE30toZBEfficiency..." << std::endl;
        // create an analysis object to generate the l1xe30 efficiencies
        ComputeL1XE30toZBEfficiency* buildl1xe30Efficiencies = new ComputeL1XE30toZBEfficiency();
        zb_chain->Process( buildl1xe30Efficiencies);
    }
    else{
        std::cout << "ZB Jburr data file not found..." << std::endl;
        return 0;
    }
    // if successfully get the JETM10 data
    if (jetm10_chain->Add("/home/joseph/ATLAS_Research/DATA/PhysicsMain/JETM10_15thru17_with_missing_et_significance.root")){
        // create object to correct the l1xe30 data to zerobias 
        CorrectL1XE30toZB* correctToZB = new CorrectL1XE30toZB();
        // pass the l1xe30 efficiency curves to corrector
        correctToZB->Set_L1XE30_Efficiency_Fit_Objects(buildl1xe30Efficiencies->Get_L1XE30_Efficiency_Fit_Objects());
        jetm10_chain->Process( correctToZB );

        // create the l1xe50 to l1xe30 efficiency curves
        ComputeL1XE50toL1XE30Efficiency* createL1XE50Efficiencies = new ComputeL1XE50toL1XE30Efficiency();
        jetm10_chain->Process( createL1XE50Efficiencies );

        // pass all the efficiency curves to correct all the way 
        CorrectL1XE50toZB* CorrectL1XE50DataAllWay = new CorrectL1XE50toZB();
        CorrectL1XE50DataAllWay->Set_L1XE30_Efficiency_Fit_Objects(buildl1xe30Efficiencies->Get_L1XE30_Efficiency_Fit_Objects());
        CorrectL1XE50DataAllWay->Set_L1XE50_Efficiency_Fit_Objects(createL1XE50Efficiencies->Get_L1XE50_Efficiency_Fit_Objects());
        // then correct the l1xe50 data back to zerobias
        jetm10_chain->Process( CorrectL1XE50DataAllWay );
    }
    else{
        std::cout << "JETM10 Jburr data file not found..." << std::endl;
        return 0;
    }

    // TODO: write the full correction object to file

    // TODO: take all plotting and saving of stuff out of these selectors. 
    // save the final object to a root file out here in the macro
    // plot the things in a separate macro that loads the info
}
