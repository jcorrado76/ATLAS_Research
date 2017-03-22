int doAnalysis(TString& alg) 
{
	//This macro will call plot a cut and determine threshold in order to determine the zero bias thresholds and apply
	//them to muon events to see how many muon events are kept, 
	//determines thresh from zero bias

	std::cout << "Entering determineThresh.C" << std::endl;
	TString threshCommand = ".x determineThresh.c(\"" + alg + "\")";
	Float_t thresh = gROOT->ProcessLine(threshCommand);
	TString threshVal = Form("%f", thresh);
	std::cout << "Thresh value: " << threshVal << std::endl;


	std::cout << "Entering plotACut.C" << std::endl;
	TString cutCommand = ".x plotACut.c(\"" + alg + "\"," + threshVal + ",\"muon\")";
	gROOT->ProcessLine(cutCommand);
}
