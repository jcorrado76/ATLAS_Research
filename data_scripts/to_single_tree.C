{
    // this macro takes in a directory of root trees and collapses them into a single tree
    TChain* mychain = new TChain("METTree");
    mychain->Add("../jburr_2019_04_24_JETM10/*.root");
    std::cout << "Number of trees loaded: " << mychain->GetNtrees() << std::endl;
    TString fname = "../jburr_2019_04_24_JETM10.root";
    mychain->Merge(fname);
    TFile* outfile = TFile::Open(fname, "READ");
    if (outfile->IsOpen()){
        std::cout << "New file successfully created" << std::endl;
    }else{
        std::cout << "Unable to open the merged file" << std::endl;
    }
    outfile->Close();
}
