Int_t threeEfficiencies(TString& algA , TString& algB)
{
  /*
  Makes TEFFICIENCY Plots ONCE
  TEFFICIENCY ALG A AT 10^(-4)
  TEFFICIENCY ALG b AT 10^(-4)
  TEFFICIENCY ALG c AT 10^(-4)
  */

Float_t frac = (Float_t) 10.0**(-4.0);
TString fileName = "../myData/ZeroBias2016new.13Runs.root";
TFile * 2016Data = TFile::Open(fileName, "READ");
Int_t nentries = tree->GetEntries();
Int_t nbins = 60;
Double_t metMin = 0.0;
Double_t metMax = 500.0;
Int_t passrndm, numRndm,passmuon;
Float_t algAMET,algBMET,metoffrecal;

tree->SetBranchAddress(algA,&algAMET);
tree->SetBranchAddress(algB,&algBMET);
tree->SetBranchAddress("passrndm",&passrndm);
tree->SetBranchAddress("metoffrecal",&metoffrecal);

TH1F* algAHist     = new TH1F("Algorithm A Histogram" , "Algorithm A Histogram" , nbins, metMin, metMax);
TH1F* algACumuHist = new TH1F("AcumuHist", "AcumuHist" , nbins, metMin, metMax);
TH1F* algBHist     = new TH1F("Algorithm B Histogram" , "Algorithm B Histogram" , nbins, metMin, metMax);
TH1F* algBCumuHist = new TH1F("BcumuHist", "BcumuHist" , nbins, metMin, metMax);

TEfficiency* Ateff  = new TEfficiency("ATEfficiency", "ATEfficiency", nbins, metMin, metMax);
TEfficiency* Bteff  = new TEfficiency("BTEfficiency", "BTEfficiency", nbins, metMin, metMax);
TEfficiency* Cteff  = new TEfficiency("CTEfficiency", "CTEfficiency", nbins, metMin, metMax);


for (Int_t i = 0 ; i < nentries ; i++)
{
  tree->GetEntry(i);
  if (passrndm > 0.1)
  {
    numRndm++;
    algAHist->Fill(algAMET);
    algBHist->Fill(algBMET);
  }
}

Float_t numbToKeep = numRndm * frac;

//determine threshold for 10^(-4) events
for (Int_t t = nbins; t >= 0; t--)
{
  Float_t summ2 = 0;

  for (Int_t i = t; i <= nbins; i++)
  {
    summ2 += algAHist->GetBinContent(i);
  }
  algACumuHist->SetBinContent(t, summ2);
}
for (Int_t t = nbins; t >= 0; t--)
{
  if ((abs(algACumuHist->GetBinContent(t) - (numbToKeep) > 0) != (abs(algACumuHist->GetBinContent(t + 1) - (numbToKeep)) > 0)))
  {
    Float_t algAThresh = algACumuHist->GetBinCenter(t);
  }
}

//determine other threshold for 10^(-4) events
for (Int_t t = nbins; t >= 0; t--)
{
  Float_t summ3 = 0;

  for (Int_t i = t; i <= nbins; i++)
  {
    summ3 += algBHist->GetBinContent(i);
  }
  algBCumuHist->SetBinContent(t, summ3);
}
for (Int_t t = nbins; t >= 0; t--)
{
  if ((abs(algBCumuHist->GetBinContent(t) - (numbToKeep) > 0) != (abs(algBCumuHist->GetBinContent(t + 1) - (numbToKeep)) > 0)))
  {
    Float_t algBThresh = algBCumuHist->GetBinCenter(t);
  }
}

std::cout << "Threshold to keep 10^(-4) events for " << algA << ": " << algAThresh << std::endl;
std::cout << "Threshold to keep 10^(-4) events for " << algB << ": " << algBThresh << std::endl;

for (Int_t j = 0 ; j < nentries ; j++)
{
    tree->GetEntry(j);
    if (passrndm > 0.1)
    {
        Ateff->Fill(algAMET > algAThresh, metoffrecal);
        Bteff->Fill(algBMET > algBThresh, metoffrecal);
        Cteff->Fill(((algAMET > algAThresh) && (algBMET > algBThresh) ), metoffrecal);
    }
}

TCanvas* c1 = new TCanvas("Efficiency Canvas", "Efficiency Canvas");
c1->Divide(3);
c1->cd(1);
Ateff->Draw();

c1->cd(2);
Bteff->Draw();

c1->cd(3);
Cteff->Draw();

TString path = "./TEfficienciesPics/" + algA + "and" + algB + "efficiencies.pdf";

c1.Print(path);

return(0);

}
