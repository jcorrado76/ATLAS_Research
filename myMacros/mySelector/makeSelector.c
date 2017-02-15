{
	// create template class for Selector to run on a tree
	//////////////////////////////////////////////////////
	//
	TString fileName = "../../myData/ZeroBias2016.13Runs.root";
	// open root file containing the Tree
	TFile f(fileName);
	// create TTree object from it
	TTree t*; 
	f.GetObject("metl1", t);
	// this generates the files MySelector.h and MySelector.C
	t->MakeSelector("MySelector");
}