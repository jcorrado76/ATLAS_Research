Float_t determineCombinedEventsKept(TString& algA, Float_t threshA, TString& algB, Float_t threshB, Float_t metl1thresh = 30.0,TString& fileName = "ZeroBias2016new.13Runs.root")
{
  gROOT->ProcessLine("gROOT->Reset();");
  std::cout << "Determining fraction of zero bias events kept when using combined algorithm of " << algA << " at: " << threshA << " and "
  << algB << " at: " << threshB << std::endl;

  TString path = "../myData/"+fileName;
	TFile * 2016Data = TFile::Open(path, "READ");
	Int_t nbins = 400;
	Double_t metMin = 0.0;
	Double_t metMax = 500.0;
  Int_t nentries = tree->GetEntries();
  Float_t algAMET, algBMET,metl1;
  Int_t passrndm;


  tree->SetBranchAddress("passrndm",&passrndm);
  tree->SetBranchAddress(algA,&algAMET);
  tree->SetBranchAddress(algB,&algBMET);
  tree->SetBranchAddress("metl1",&metl1);

  Int_t counter,numRndm = 0;

  for (Int_t i  = 0 ; i < nentries ;i++)
  {
    tree->GetEntry(i);
    if (passrndm >0.1)
    {
      numRndm++;
    }
    if ((passrndm > 0.1) && (algAMET > threshA) && (algBMET > threshB) && (metl1 > metl1thresh))
    {
      counter++;
    }
  }

std::cout << "Combined alg kept: " << counter << " events" << std::endl;
Float_t frac = (Float_t) counter / (Float_t) numRndm;
std::cout << "Fraction of passrndm events: " << frac << std::endl;


return(counter);


}
