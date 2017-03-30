{
	#include <vector>
	#include <stdexcept>
	#include <iostream>
	#include <fstream>

	/*
	Select events from tail of MET (greater than 121 GeV).
	Make a histogram of the corresponding sqrt SET energies.
	For bins of this histogram with nonzero amount of events, record bin number in nonZeroSETBins.
	Make an array of pointers to a histogram for each bin of SET in nonZeroSETBins
	For each pointer, create the histogram for corresponding bin of SET.
	For each histogram, fill with values of MET if 
	
	
	*/



	//set parameters for creating new files 
	int singleFile = 1;
	TString singleFileName = "Single_File";
	TString fileExt = ".pdf";
	TString targetDirectory("../pictures/");

	//open data 
	TFile * 2015 = TFile::Open("../myData/ZeroBias2015.p2634.PeriodJ.root");

	//get location in tree for set ans met 
	Float_t setalg;
	TBranch *b_setalg = new TBranch();
	tree->SetBranchAddress("settopoclps", &setalg, &b_setalg);

	Float_t metalg;
	TBranch *b_metalg = new TBranch();
	tree->SetBranchAddress("mettopoclps", &metalg, &b_metalg);

	//MET value to designate tail 
	int tail = 121;

	//==================================================================================================================================================//
	//Initialize scatter plot of alg met vs. sqrt alg set ***NOTE: CHANGE RANGE FOR SIGNAL EVENTS***	
	TH1F *algset = new TH1F("algset", "sqrt of Algorithm SET", 100, 0., 100.);
	TH1F *algmet = new TH1F("algmet", "Algorith MET", 200, 0., 200.);

	//if the MET energy is in the tail of MET, fill SET hist with sqrt SET
	Long64_t nentries = tree->GetEntries();
	for (int i = 0; i < nentries; i++)
	{
		tree->GetEntry(i);
		// Only pass the events that are in the specified tail of the algorithm
		if (metalg > tail)
		{
			//fill hist with sqrt set
			algset->Fill(sqrt(setalg));
		}
	}

	//Get the bin content of each bin of sq.rt(SET)
	//If the bin content is nonzero, save the number of that bin in the binnum array
	int binNum[100];
	int numbNonZeroBinsSET = 0;
	Float_t metAlgBins;
	vector<Double_t> nonZeroSETBins;
	for (int j = 0; j < 100; j++)
	{
		//get amount of entries in jth in of set 
		Double_t numbSETEntries = algset->GetBinContent(j);
		//if the jth SET bin has nonzero number of entries, populate the nonZeroSETBins array with the bin number of that bin of SET
		if (numbSETEntries > 0.0)
		{
			//array of bin numbers of SET with greater than zero entries 
			binNum[j] = algset->GetBin(j);
			numbNonZeroBinsSET++;
			nonZeroSETBins.push_back(binNum[j]);
		}
	}
	
	//each MET hist in array is for one bin of SET
	TH1F *metHistArray[numbNonZeroBinsSET];
	char *histname = new char;
	metAlgBins = 300.;
	float xmin = 0., xmax = 300.;

	//lets make each of the histograms corresponding to a bin of SET 
	for (int l = 1; l < numbNonZeroBinsSET; l++)
	{
		//send name-number of hist to histname 
		sprintf(histname, "histo%d", l);
		//create each histogram in SEThistarray for each bin of SET
		metHistArray[l] = new TH1F(histname, "", metAlgBins, xmin, xmax);
		//populate the lth hist with all values of metalg if lth bin number is less than sqrt set and sqrt set less than lth bin number plus one 
		for (int i = 0; i < nentries; i++)
		{
			// Parse through the tree again, and fill each MET histogram only with events in their respective sqrt(set) bins
			//why is comparison between th lth bin number with greater than zero entries, and the sqrt of the SET energy recorded?
			tree->GetEntry(i);
			if (nonZeroSETBins[l] < sqrt(setalg) && sqrt(setalg) < nonZeroSETBins[l] + 1)
			{
				metHistArray[l]->Fill(metalg);
			}
			//you have to compare the energy of SET to the energies that bound the lth bin of methistarray for each bin of SET
		}
	}

	


	//initialize rayleigh TF1
	TF1 *raydist = new TF1("raydist", "[0]*(1/[1])*(x/[1])*exp(-.5*(x/[1])*(x/[1]))");
	raydist->SetParameters(0, 100000.);
	raydist->SetParameters(1, 1.);
	raydist->SetParLimits(0, 0.1, 10000000.);
	raydist->SetParLimits(1, 0.1, 10000000.);

	//initialize canvas
	TCanvas myCanv("c1");
	//initialize canvas 
	char *canvname = new char;

	try {
		//check to make sure directory exists 
		/*
		if ([CONDITION])
		{
			throw std::runtime_error("Directory does not exist");
		}*/
		//WILL GENERATE MANY FILES
		if (!singleFile) 
		{
			for (int m = 1; m < numNonZeroBinsSET; m++)
			{
				//send new canvas names to canvname
				sprintf(canvname, "canv%d", m);
				//create new canvas for each SET hist 
				mycanv[m] = new TCanvas(canvname, "");
				//fit rayleigh to each SET hist 
				myhist[m]->Fit("raydist", "L");
				//before you write, check to make sure a file doesn't already exist
				ifstream file(Form(targetDirectory + "%s" + fileExt, myhist[m]->GetName()));
				if (file)
				{
					throw std::runtime_error("File with name already exists");
				}
				file.close();
				//now write to file for each SET hist 
				mycanv[m]->Print(Form(targetDirectory + "%s" + fileExt , myhist[m]->GetName()));
			}

		}
		//WILL GENERATE ONE FILE
		else
		{

			//open file; suppress printing 
			TString fullPath(targetDirectory + singleFileName + fileExt);

			ifstream file(fullPath);
			if (file)
			{
				throw std::runtime_error("File with name already exists");
			}

			file.close();

			myCanv->Print(fullPath + "[");
			for (int m = 1; m < numNonZeroBinsSET; m++)
			{
				//generate canvas name each iteration
				sprintf(canvname, "canv%d", m);
				//reassign canvas to new name
				myCanv = new TCanvas(canvname, "");
				//put the fit onto the new canvas
				myhist[m]->Fit("raydist", "L");
				//write the new canvas to file 
				myCanv->Print(fullPath);
			}
			//close the file ;suppress printing
			myCanv->Print(fullPath + "]");
		}
	}
		catch (std::exception &err)
		{
			std::cout << err.what() << std::endl;
		}
		return 0;
}