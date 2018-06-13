{

    TString fileName1 = "totalntuple2015.root";
    TString fileName2 = "totalntuple2016.root";
    TString fileName3 = "totalntuple2017.root";
    TString fileName4 = "totalJburrTuple.root";

    TFile* file2015 = TFile::Open(fileName1);
    TFile* file2016 = TFile::Open(fileName2);
    TFile* file2017 = TFile::Open(fileName3);
    TFile* totalJburrFile = TFile::Open(fileName4);


    TTree* tree2015 = (TTree*) file2015->Get("METTree");
    TTree* tree2016 = (TTree*) file2016->Get("METTree");
    TTree* tree2017 = (TTree*) file2017->Get("METTree");
    TTree* totalTree = (TTree*) totalJburrFile->Get("METTree");

    Int_t tree2015Nentries = tree2015->GetEntries();
    Int_t tree2016Nentries = tree2016->GetEntries();
    Int_t tree2017Nentries = tree2017->GetEntries();
    Int_t totalTreeNentries = totalTree->GetEntries();

    std::cout << "Number of entries in " << fileName1 << ": " << tree2015Nentries << std::endl;
    std::cout << "Number of entries in " << fileName2 << ": " << tree2016Nentries << std::endl;
    std::cout << "Number of entries in " << fileName3 << ": " << tree2017Nentries << std::endl;
    std::cout << "Number of entries in " << fileName4 << ": " << totalTreeNentries<< std::endl;

    Int_t sumOfEntries = tree2015Nentries + tree2016Nentries + tree2017Nentries;
    std::cout << "Total Tree Entries == Sum of Entries" << std::endl;
    std::cout << totalTreeNentries << " == " << sumOfEntries << std::endl;
}
