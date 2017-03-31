int multipleAnalysis(){	
	TString METalgArray[6] = { "metl1","metcell","metmht","mettopocl","mettopoclps","mettopoclpuc" }
	TString alg;
	gROOT->ProcessLine(".L doAnalysis.C");
	for (int i = 0; i < 6; i++)
	{
		std::cout << "Processing analysis for " << METalgArray[i] << std::endl;
		alg = METalgArray[i];
		gROOT->ProcessLine(".x doAnalysis.c(\"" + alg + "\")");
		std::cout << "\n\n" << std::endl;
	}
	return(0);
}	