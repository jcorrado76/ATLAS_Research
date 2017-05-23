Int_t threeEfficiencies(TString& algA , TString& algB)
{
  /*
  Makes TEFFICIENCY Plots ONCE
  TEFFICIENCY ALG A AT 10^(-4)
  TEFFICIENCY ALG b AT 10^(-4)
  TEFFICIENCY ALG c AT 10^(-4)
  */

Float_t frac = (Float_t) 10.0**(-4.0);
TString fileName = "../myData/ExpressMuons2016newanalysis.11runs.root";
TFile * 2016Data = TFile::Open(fileName, "READ");
std::cout << "Data being used to compute algorithm efficiency: " << fileName << std::endl;
Int_t nentries = tree->GetEntries();
Int_t nbins = 60;
Double_t metMin = 0.0;
Double_t metMax = 500.0;
Int_t passrndm, numPassMuon,passmuon,cleanCutsFlag,recalBrokeFlag;
Float_t algAMET,algBMET,metoffrecal,offrecal_met,offrecal_mex,offrecal_mey,offrecalmuon_mex,offrecalmuon_mey;

tree->SetBranchAddress(algA,&algAMET);
tree->SetBranchAddress(algB,&algBMET);
tree->SetBranchAddress("passmu24med", &passmuon); // get first pass moun flag
tree->SetBranchAddress("passcleancuts", &cleanCutsFlag); // get cleancuts flag
tree->SetBranchAddress("recalbroke", &recalBrokeFlag); // get recalbroke flag
tree->SetBranchAddress("metoffrecal", &offrecal_met);
tree->SetBranchAddress("mexoffrecal", &offrecal_mex);
tree->SetBranchAddress("meyoffrecal", &offrecal_mey);
tree->SetBranchAddress("mexoffrecalmuon", &offrecalmuon_mex);
tree->SetBranchAddress("meyoffrecalmuon", &offrecalmuon_mey);

gROOT->ProcessLine(".L determineThresh.c");
TString argc;
argc = ".x determineThresh.c(\"" + algA + "\")";
Float_t algAThresh = gROOT->ProcessLine(argc);
argc = ".x determineThresh.c(\"" + algB + "\")";
Float_t algBThresh = gROOT->ProcessLine(argc);

std::cout << "Threshold to keep 10^(-4) events for " << algA << ": " << algAThresh << std::endl;
std::cout << "Threshold to keep 10^(-4) events for " << algB << ": " << algBThresh << std::endl;

TEfficiency* Ateff  = new TEfficiency(algA + " TEfficiency at thresh of " + Form(" %.2f", algAThresh) , algA + " TEfficiency", nbins, metMin, metMax);
TEfficiency* Bteff  = new TEfficiency(algB + " TEfficiency at thresh of " + Form(" %.2f", algBThresh) , algB + " TEfficiency", nbins, metMin, metMax);
TEfficiency* Cteff  = new TEfficiency("TEfficiency using " + algA + " at thresh " + Form(" %.2f", algAThresh) + " and " + algB +
" at thresh " + Form(" %.2f", algBThresh), "CTEfficiency", nbins, metMin, metMax);


for (Int_t j = 0 ; j < nentries ; j++)
{
    tree->GetEntry(j);
    if (passmuon > 0.1 && cleanCutsFlag > 0.1 && recalBrokeFlag < 0.1)
    {
        Float_t metnomu = sqrt(((offrecal_mex - offrecalmuon_mex) * (offrecal_mex - offrecalmuon_mex)) +
        ((offrecal_mey - offrecalmuon_mey)*(offrecal_mey - offrecalmuon_mey))); //compute metnomu
        Ateff->Fill(algAMET > algAThresh, metnomu);
        Bteff->Fill(algBMET > algBThresh, metnomu);
        Cteff->Fill(((algAMET > algAThresh) && (algBMET > algBThresh) ), metnomu);
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
