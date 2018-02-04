{

    TString zb_path = "$(DATA)/ZeroBiasL1KF2016R307195R311481.51Runs.root";    

    if (!gSystem->AccessPathName( zb_path ) ){
        std::cout << "could not open root file" << std::endl;
    }

    std::cout << "File accessed successfully" << std::endl;

    TFile* zb_file      = TFile::Open( zb_path , "READ");
    TTree* zb_tree      = (TTree*)zb_file->Get("tree");

}

