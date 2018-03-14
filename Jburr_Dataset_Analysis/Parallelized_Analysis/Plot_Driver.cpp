{
    gROOT->Reset();
    TString mincer_zbpath= "$DATA/ZeroBiasL1KF2016R307195R311481.51Runs.root";
    TString jburr_zbpath = "$work/../Jburr_Dataset_Analysis/data/totalntuple16.root";

    if ( gSystem->AccessPathName( mincer_zbpath ) ){
         
        TFile* mincer_file = TFile::Open( mincer_zbpath );

    }
    else{
        std::cout << "Could not access filename " << std::endl;
        std::cout << "Filename:\n" << mincer_zbpath << std::endl;
    }

    if ( gSystem->AccessPathName( jburr_zbpath ) ){
         
        TFile* jburr_file = TFile::Open( jburr_zbpath );

    }
    else{
        std::cout << "Could not access filename " << std::endl;
        std::cout << "Filename:\n" << jburr_zbpath << std::endl;
    }

    TTree* mincertree = (TTree*)mincer_file->Get("tree");
    TTree* jburrtree= (TTree*)jburr_file->Get("METTree");


    Jburr_Selector* jburr_analysis = new Jburr_Selector();
    Mincer_Selector* mincer_analysis = new Mincer_Selector();




    TChain* mincerchain = new TChain( "tree" , "Mincer_Chain" );
    mincerchain->Add( mincer_zbpath );
    TChain* jburrchain = new TChain( "METTree" , "Jburr_Chain" );
    jburr_chain->Add( jburr_zbpath );
    TProof* proof = TProof::Open("");
    mychain->SetProof();
    proof->SetParameter("PROOF_UseTreeCache" , (Int_t)0);
    mychain->Process("ZB_Eff_Selector.C+");













}
