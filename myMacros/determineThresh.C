int determineThresh(TString& alg) {
	
	
	
	//ROOT data FileName
	TString fileName = "../myData/ZeroBias2016.13Runs.root";
	//create an array containing names of all algorithms so i can parse over them
	TString nameArray[6] = { "metl1","metcell","metmht","mettopocl","mettopoclps","mettopoclpuc" };



	//algorithm of interest name
	TString passed_hist_name = alg;
	TString passed_hist_title = alg;

	//Reference hist parameters 
	TString reference_hist_name = "metoffrecal";
	TString reference_hist_title = "METOFFRECAL";

	//Histogram parameters
	int nbins = 250;
	Double_t metMin = 0.0;
	Double_t metMax = 200.0;

	//Histogram Axis labels 
	TString xaxis = "MET [GeV]";
	TString yaxis = "Events";

	TString teff_name, teff_title;

	//Reference Hist Labels
	TString reference_hist_full_param = (reference_hist_title + " HIST;" + xaxis + ";" + yaxis);

	//Calculate Full Hist Params
	TString passed_hist_full_param1 = (passed_hist_title  + " HIST; " + xaxis + ";" + yaxis);
	

	//Open ROOT file 
	TFile * 2016Data = TFile::Open(fileName, "READ");


	//variables take on values of alg
	Float_t passed_hist_met, reference_hist_met;

	Int_t passrndm;

	//Get addresses of variables
	tree->SetBranchAddress(passed_hist_name, &passed_hist_met);
	tree->SetBranchAddress(reference_hist_name, &reference_hist_met);
	tree->SetBranchAddress("passrndm", &passrndm);


	//Initial TH1F object
	TH1F *cut = new TH1F(passed_hist_name, passed_hist_full_param1, nbins, metMin, metMax);
	TH1F *target = new TH1F("cumu", "cumu", nbins, metMin, metMax);




	//# of entries
	int nentries = tree->GetEntries();

	Float_t condition = nentries * (10 * * (-4));



	for (Long64_t k = 0; k < nentries; k++)
	{
		//get the first entry; after adding, get next entry
		tree->GetEntry(k);
		//maintain passrndm is true 
		if (passrndm == 1)
		{
			cut->Fill(passed_hist_met);
		}
	}

	//number of entries after applying passrndm
	nentries = cut->GetEntries();
Float_t thresh;

//define a range for the number of entries to be within 
Float_t epsilon = 100.0;

//generate the cumulative right tail sum hist
for (int t = nbins; t >= 0 ; t--)
{
	Float_t summ = 0;

	for (int i = t ; i <= nbins ; i++)
	{
		summ += cut->GetBinContent(i);
	}
	target->SetBinContent(t, summ );
}

Float_t condition = (10e-4);

Float_t keep = (10e-4) * nentries;

for (int t = nbins; t >=0 ; t--)
{
	//std::cout << "Number of entries in bin" << t << " " << target->GetBinContent(t) << std::endl;
	if (abs(target->GetBinContent(t) - (keep)) < epsilon)
	{
		thresh = target->GetBinCenter(t);
		std::cout << "Entered set thresh" << std::endl;
	}
}

std::cout << "number of entries in after passrndm flag : " << nentries << std::endl;
std::cout << "Number of entries to keep " << keep << std::endl;

//TH1* cumu = cut->GetCumulative();
//	target->Draw();



std::cout << "The threshold for " << passed_hist_name << " to keep " << keep << " events is: " <<  thresh << std::endl;
	return 0;
}
