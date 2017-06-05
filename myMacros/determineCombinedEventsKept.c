Float_t determineCombinedEventsKept(TString& algA, Float_t threshA, TString& algB, Float_t threshB)
{
  std::cout << "Determining fraction of zero bias events kept when using combined algorithm of " << algA << " at: " << threshA << " and "
  << algB << " at: " << threshB << std::endl;
  TString fileName = "../myData/ZeroBias2016new.13Runs.root";
	TFile * 2016Data = TFile::Open(fileName, "READ");
	Int_t nbins = 400;
	Double_t metMin = 0.0;
	Double_t metMax = 500.0;
  Int_t nentries = tree->GetEntries();
  Float_t algAMET, algBMET;
  Int_t passrndm,cleanCutsFlag,recalBrokeFlag;

  tree->SetBranchAddress("passcleancuts", &cleanCutsFlag);
  tree->SetBranchAddress("recalbroke", &recalBrokeFlag);
  tree->SetBranchAddress("passrndm",&passrndm);
  tree->SetBranchAddress(algA,&algAMET);
  tree->SetBranchAddress(algB,&algBMET);

  Int_t counter,numRndm = 0;

  for (Int_t i  = 0 ; i < nentries ;i++)
  {
    tree->GetEntry(i);
    if (passrndm >0.1)
    {
      numRndm++;
    }
    if ((passrndm > 0.1) && (cleanCutsFlag > 0.1) && (recalBrokeFlag > 0.1) && (algAMET > threshA) && (algBMET > threshB))
    {
      counter++;
    }
  }

std::cout << "Combined alg kept: " << counter << " events" << std::endl;
Float_t frac = (Float_t) counter / (Float_t) numRndm;
std::cout << "Fraction of passrndm events: " << frac << std::endl;


return(frac);


}
