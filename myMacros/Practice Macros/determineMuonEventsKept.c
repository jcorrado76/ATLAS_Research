Int_t determineMuonEventsKept(TString& algA, Float_t threshA, TString& algB, Float_t threshB)
{
  std::cout << "Determining how many muon events kept when using combined algorithm of " << algA << " at: " << threshA << " and "
  << algB << " at: " << threshB << std::endl;
  TString fileName = "../myData/ExpressMuons2016newanalysis.11runs.root";
	TFile * 2016Data = TFile::Open(fileName, "READ");
	Int_t nbins = 50;
	Double_t metMin = 0.0;
	Double_t metMax = 250.0;
  Int_t numbMuon = 0;
  Int_t nentries = tree->GetEntries();
  Float_t algAMET, algBMET,metoffrecal,offrecal_met,offrecal_mex,offrecal_mey,offrecalmuon_mex,offrecalmuon_mey;
  Int_t passmuonFlag,cleanCutsFlag,recalBrokeFlag;

  std::cout << "nentries: " << nentries << std::endl;



  tree->SetBranchAddress("passmu24med",&passmuonFlag);
  tree->SetBranchAddress("passcleancuts", &cleanCutsFlag);
  tree->SetBranchAddress("recalbroke", &recalBrokeFlag);
  tree->SetBranchAddress("metoffrecal", &offrecal_met);
  tree->SetBranchAddress("mexoffrecal", &offrecal_mex);
  tree->SetBranchAddress("meyoffrecal", &offrecal_mey);
  tree->SetBranchAddress("mexoffrecalmuon", &offrecalmuon_mex);
  tree->SetBranchAddress("meyoffrecalmuon", &offrecalmuon_mey);
  tree->SetBranchAddress(algA,&algAMET);
  tree->SetBranchAddress(algB,&algBMET);

  TString cstring = "TEfficiency using " + algA + " at thresh " + Form(" %.2f", threshA) + " and " + algB +
  " at thresh " + Form(" %.2f", threshB);
  TEfficiency* Cteff  = new TEfficiency(cstring,  "Efficiency", nbins, metMin,metMax);



  Int_t counter = 0;
  for (Int_t i  = 0 ; i < nentries ;i++)
  {
    tree->GetEntry(i);
    if (passmuonFlag > 0.1 && (cleanCutsFlag > 0.1) && (recalBrokeFlag < 0.1))
    {
      Float_t metnomu = sqrt(((offrecal_mex - offrecalmuon_mex) * (offrecal_mex - offrecalmuon_mex)) +
      ((offrecal_mey - offrecalmuon_mey)*(offrecal_mey - offrecalmuon_mey))); //compute metnomu
      Cteff->Fill(((algAMET > threshA) && (algBMET > threshB) ), metnomu);
      numbMuon++;
      if (algAMET > threshA && algBMET > threshB)
      {
        counter++;
      }
    }
  }

Float_t frac = (Float_t) counter / (Float_t) numbMuon;
std::cout << "numbMuon: " << numbMuon << std::endl;
std::cout << "Combined alg kept: " << counter << " events" << std::endl;
std::cout << "Fraction Kept: " << frac << std::endl;
}
