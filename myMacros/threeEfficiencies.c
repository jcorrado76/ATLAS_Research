Int_t threeEfficiencies(TString& algA , TString& algB)
{
  /*
  Makes TEFFICIENCY Plots ONCE
  TEFFICIENCY ALG A AT 10^(-4)
  TEFFICIENCY ALG b AT 10^(-4)
  TEFFICIENCY ALG c AT 10^(-4)
  */

TString fileName = "ExpressMuons2016newanalysis.11runs.root";
Float_t frac = (Float_t) 10.0**(-4.0);
TString path = "../myData/"+fileName;
TFile * muonFile = TFile::Open(path, "READ");
TTree* myTree = NULL;
muonFile->GetObject("tree",myTree);

std::cout << "Data being used to compute algorithm efficiency: " << path << std::endl;
Int_t nentries = myTree->GetEntries();
Int_t nbins = 60;
Double_t metMin = 0.0;
Double_t metMax = 500.0;
Int_t passrndm, numPassMuon,passmuon,cleanCutsFlag,recalBrokeFlag;
Float_t algAMET,algBMET,metoffrecal,offrecal_met,offrecal_mex,offrecal_mey,offrecalmuon_mex,offrecalmuon_mey;

myTree->SetBranchAddress(algA,&algAMET);
myTree->SetBranchAddress(algB,&algBMET);
myTree->SetBranchAddress("passmu24med", &passmuon); // get first pass moun flag
myTree->SetBranchAddress("passcleancuts", &cleanCutsFlag); // get cleancuts flag
myTree->SetBranchAddress("recalbroke", &recalBrokeFlag); // get recalbroke flag
myTree->SetBranchAddress("metoffrecal", &offrecal_met);
myTree->SetBranchAddress("mexoffrecal", &offrecal_mex);
myTree->SetBranchAddress("meyoffrecal", &offrecal_mey);
myTree->SetBranchAddress("mexoffrecalmuon", &offrecalmuon_mex);
myTree->SetBranchAddress("meyoffrecalmuon", &offrecalmuon_mey);

gROOT->ProcessLine(".L determineThresh.c");
TString argc;
argc = ".x determineThresh.c(\"" + algA + "\")";
Float_t algAThresh = (Float_t) gROOT->ProcessLine(argc);
argc = ".x determineThresh.c(\"" + algB + "\")";
Float_t algBThresh = (Float_t) gROOT->ProcessLine(argc);

std::cout << "Threshold to keep 10^(-4) events for " << algA << ": " << algAThresh << std::endl;
std::cout << "Threshold to keep 10^(-4) events for " << algB << ": " << algBThresh << std::endl;

TString cstring = "TEfficiency using " + algA + " at thresh " + Form(" %.2f", algAThresh) + " and " + algB +
" at thresh " + Form(" %.2f", algBThresh);
TString astring = algA + " TEfficiency at thresh of " + Form(" %.2f", algAThresh);
TString bstring = algB + " TEfficiency at thresh of " + Form(" %.2f", algBThresh);

TEfficiency* Ateff  = new TEfficiency(astring , astring, nbins, metMin, metMax);
TEfficiency* Bteff  = new TEfficiency(bstring , bstring, nbins, metMin, metMax);
TEfficiency* Cteff  = new TEfficiency(cstring, cstring, nbins, metMin, metMax);


for (Int_t j = 0 ; j < nentries ; j++)
{
    myTree->GetEntry(j);
    //CLEANCUTS AND RECALBROKE
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
