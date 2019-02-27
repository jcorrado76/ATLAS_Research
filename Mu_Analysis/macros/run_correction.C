{
    std::cout << "Starting to run correcting distributions" << std::endl;
    CorrectL1XE50toZB* dol1xe50correction = new CorrectL1XE50toZB();
    TChain* mychain = new TChain( "METTree" , "mychain" );
    mychain->Add("/home/joseph/ATLAS_Research/DATA/PhysicsMain/JETM10_15thru17_with_missing_et_significance");
    mychain->Process(dol1xe50correction);
}

