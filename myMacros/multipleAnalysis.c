int multipleAnalysis(){	
	TString METalgArray[6] = { "metl1","metcell","metmht","mettopocl","mettopoclps","mettopoclpuc" }
	TString alg;
	for (int i = 0; i < 6; i++)
	{
		std::cout << "Processing analysis for " << METalgArray[i] << std::endl;
		alg = METalgArray[i];
		gROOT->ProcessLine(".x doAnalysis.c(\"" + alg + "\")");
	}
	return(0);
}