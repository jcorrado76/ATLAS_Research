Int_t determineMuonFractionKept(TString& algA, Float_t threshA, TString& algB, Float_t threshB)
{
  std::cout << "Determining how many zero bias events kept when using combined algorithm of " << algA << " at: " << threshA << " and "
  << algB << " at: " << threshB << std::endl;
  TString fileName = "../myData/ExpressMuons2016newanalysis.11runs.root";
	TFile * 2016Data = TFile::Open(fileName, "READ");
	Int_t nbins = 60;
	Double_t metMin = 0.0;
	Double_t metMax = 500.0;
  Int_t numRndm = 0;
  Int_t nentries = tree->GetEntries();
  Float_t algAMET, algBMET;
  Int_t passmuonFlag;

  tree->SetBranchAddress("passmu24med",&passmuonFlag);
  tree->SetBranchAddress(algA,&algAMET);
  tree->SetBranchAddress(algB,&algBMET);

  Int_t counter =0;


  for (Int_t i  = 0 ; i < nentries ;i++)
  {
    tree->GetEntry(i);
    if (passmuonFlag > 0.1 )
    {
      numbMuon++;
      if (algAMET > threshA && algBMET > threshB)
      {
        counter++;
      }
    }
  }

Float_t frac = counter / numbMuon;

std::cout << "Combined alg kept: " << counter << " events" << std::endl;
std::cout << "Fraction Kept: " << frac << std::endl;
}
