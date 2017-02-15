{
	//2016Data is the fileHandle to "zerobias..."
	TFile * 2016data = TFile::Open("ZeroBias2016.13Runs.root");
	//pucalg is the histogram pointer; histogram initialization
	TH1F* pucalg = new TH1F("pucalg", "MET Topocl PUC", 100, 0., 100.);
	//canvas is the blank figure
	TCanvas *METPUC = new TCanvas("METPUC", "METPUC");
	//sends info from 
	tree->Draw("mettopoclpuc>>pucalg");
}