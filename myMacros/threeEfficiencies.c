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
Int_t nbins = 50;
Double_t metMin = 0.0;
Double_t metMax = 250.0;
Int_t passrndm, numPassMuon,passmuon,cleanCutsFlag,recalBrokeFlag;
Float_t algAMET,algBMET,metoffrecal,offrecal_met,offrecal_mex,offrecal_mey,offrecalmuon_mex,offrecalmuon_mey,acthresh,bcthresh;

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

std::cout << "Returned to threeEfficiencies.c" << std::endl;
std::cout << "algAThresh: " << algAThresh << std::endl;
std::cout << "algBThresh: " << algBThresh << std::endl;


//same frac individually, together keep 10^(-4) thresholds
gROOT->ProcessLine(".L sameFracGetCombinedFrac.c");
argc = ".x sameFracGetCombinedFrac.c(\"" + algA + "\",\"" + algB + "\")";
Float_t combinedFrac = gROOT->ProcessLine(argc);

std::cout << "Returned to threeEfficiencies.c" << std::endl;
std::cout << "CombinedFrac to keep: " << combinedFrac << std::endl;


argc = ".x determineThresh.c(\"" + algA + "\"," + combinedFrac + ")";
Float_t acthresh = (Float_t) gROOT->ProcessLine(argc);
argc = ".x determineThresh.c(\"" + algB + "\"," + combinedFrac + ")";
Float_t bcthresh = (Float_t) gROOT->ProcessLine(argc);

std::cout << "Threshold to keep 10^(-4) events for " << algA << ": " << algAThresh << std::endl;
std::cout << "Threshold to keep 10^(-4) events for " << algB << ": " << algBThresh << std::endl;
std::cout << "Thresholds to keep 10^(-4) events respectively for: " << algA << " and " << algB << ": " << acthresh << " and " << bcthresh
<<std::endl;

TString cstring = "TEfficiency using " + algA + " at thresh " + Form(" %.2f", acthresh) + " and " + algB +
" at thresh " + Form(" %.2f", bcthresh);
TString astring = algA + " TEfficiency at thresh of " + Form(" %.2f", algAThresh);
TString bstring = algB + " TEfficiency at thresh of " + Form(" %.2f", algBThresh);

TEfficiency* Ateff  = new TEfficiency(astring , "Efficiency", nbins, metMin, metMax);
TEfficiency* Bteff  = new TEfficiency(bstring , "Efficiency", nbins, metMin, metMax);
TEfficiency* Cteff  = new TEfficiency(cstring,  "Efficiency", nbins, metMin, metMax);


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
        Cteff->Fill(((algAMET > acthresh) && (algBMET > bcthresh) ), metnomu);
    }
}

TCanvas* c1 = new TCanvas("Efficiency Canvas", "Efficiency Canvas");
Ateff->Draw();
Ateff->SetLineColor(kBlue);
Bteff->Draw("same");
Bteff->SetLineColor(kGreen);
Cteff->Draw("same");
Cteff->SetLineColor(kRed);
TLegend *legend = new TLegend(.1,.7,.48,.9);
legend->AddEntry(Ateff, astring);
legend->AddEntry(Bteff, bstring);
legend->AddEntry(Cteff, cstring);
legend->Draw();

TString path = "./TEfficienciesPics/" + algA + "and" + algB + "efficiencies.pdf";

c1.Print(path);

return(0);



}
