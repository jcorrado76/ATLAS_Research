{
    // initialize tchains
    TChain* zb_chain = new TChain( "METTree" , "zb_chain" );
    TChain* jetm10_chain = new TChain( "METTree", "jetm10chain");

    ComputeL1XE30toZBEfficiency* computeL1XE30toZBEfficiency = new ComputeL1XE30toZBEfficiency();
    CorrectL1XE30toZB* correctL1XE30ToZB = new CorrectL1XE30toZB();
    ComputeL1XE50toL1XE30Efficiency* computeL1XE50toL1XE30Efficiency = new ComputeL1XE50toL1XE30Efficiency();
    CorrectL1XE50toZB* CorrectL1XE50DataAllWay = new CorrectL1XE50toZB();

    // if successfully get the jburr zb data
    if (zb_chain->Add("/home/joseph/ATLAS_Research/DATA/ZB/ZB_jburr_15thru17_with_missing_et_significance.root")){
        zb_chain->Process( computeL1XE30toZBEfficiency );
    }
    else{
        std::cout << "ZB Jburr data file not found..." << std::endl;
        return 0;
    }
    // if successfully get the JETM10 data
    if (jetm10_chain->Add("/home/joseph/ATLAS_Research/DATA/PhysicsMain/JETM10_15thru17_with_missing_et_significance.root")){
        correctL1XE30ToZB->Set_L1XE30_Efficiency_Fit_Objects((TObjArray*)computeL1XE30toZBEfficiency->Get_L1XE30_Efficiency_Fit_Objects());
        correctL1XE30ToZB->Set_HLT_ZB_L1ZB_MET_Distributions_by_Mubin((TObjArray*)computeL1XE30toZBEfficiency->Get_HLT_ZB_L1ZB_MET_Distributions_by_Mubin());
        jetm10_chain->Process( correctL1XE30ToZB );

        // create the l1xe50 to l1xe30 efficiency curves
        jetm10_chain->Process( computeL1XE50toL1XE30Efficiency );

        // need zb l1 zb met dist for normalization
        CorrectL1XE50DataAllWay->Set_HLT_ZB_L1ZB_MET_Distributions_by_Mubin((TObjArray*)computeL1XE30toZBEfficiency->Get_HLT_ZB_L1ZB_MET_Distributions_by_Mubin());
        CorrectL1XE50DataAllWay->Set_HLT_ZB_L1XE30_MET_Distributions_by_Mubin((TObjArray*)computeL1XE50toL1XE30Efficiency->Get_HLT_ZB_L1XE30_MET_Distributions_by_Mubin());
        CorrectL1XE50DataAllWay->Set_L1XE30_Efficiency_Fit_Objects((TObjArray*)computeL1XE30toZBEfficiency->Get_L1XE30_Efficiency_Fit_Objects());
        CorrectL1XE50DataAllWay->Set_L1XE50_Efficiency_Fit_Objects((TObjArray*)computeL1XE50toL1XE30Efficiency->Get_L1XE50_Efficiency_Fit_Objects());
        CorrectL1XE50DataAllWay->Set_L1XE30_Efficiency_Objects((TObjArray*)computeL1XE30toZBEfficiency->Get_L1XE30_Efficiency_Objects());
        CorrectL1XE50DataAllWay->Set_L1XE50_Efficiency_Objects((TObjArray*)computeL1XE50toL1XE30Efficiency->Get_L1XE50_Efficiency_Objects());
        CorrectL1XE50DataAllWay->Set_HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution((TObjArray*)correctL1XE30ToZB->Get_HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution());
        // then correct the l1xe50 data back to zerobias
        jetm10_chain->Process( CorrectL1XE50DataAllWay );
    }
    else{
        std::cout << "JETM10 Jburr data file not found..." << std::endl;
        return 0;
    }

    TString filename("mu_analysis.root");
    CorrectL1XE50DataAllWay->Write( filename );

    // TODO: take all plotting and saving of stuff out of these selectors. 
    // plot the things in a separate macro that loads the object
}
