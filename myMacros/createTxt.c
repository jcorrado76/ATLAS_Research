Int_t createTxt()
{
  #include<iostream>
  #include<fstream>
  TString fileName = "../myData/ExpressMuons2016newanalysis.11runs.root";
	TFile * 2016Data = TFile::Open(fileName, "READ");

  Int_t nbins = 60;
	Double_t metMin = 0.0;
	Double_t metMax = 500.0;
	TString xlabel = "MET [GeV]";
	TString ylabel = "Events";

	Int_t nentries = tree->GetEntries();

  ofstream myFile;

  myFile.open("./tails/metl1Tail.txt");

  int passrndm, passmuon;
  float metl1,metcell,metmht,mettopocl,mettopoclps,mettopoclpuc;

  tree->SetBranchAddress("passrndm",&passrndm);
  tree->SetBranchAddress("passmu24med", &passmuon); // get first pass moun flag
	tree->SetBranchAddress("metl1", &metl1); // get cleancuts flag
	tree->SetBranchAddress("metcell", &metcell); // get recalbroke flag
	tree->SetBranchAddress("metmht", &metmht);
	tree->SetBranchAddress("mettopocl", &mettopocl);
	tree->SetBranchAddress("mettopoclps", &mettopoclps);
	tree->SetBranchAddress("mettopoclpuc", &mettopoclpuc);



/*
  myFile <<"entry," <<"passrndm," << "passmuon," <<   "metl1," << "metcell," << "metmht," << "mettopocl," << "mettopoclps,"
   << "mettopoclpuc\n";

   for (int i = 0; i< nentries; i++)
   {
     tree->GetEntry(i);
     myFile <<i<<',' <<passrndm <<',' << passmuon<< ',' <<   metl1<<',' << metcell<<',' << metmht<<',' << mettopocl<<','
     << mettopoclps << ','  << mettopoclpuc << '\n';
   }
*/


  myFile << "entry," <<"metl1 \n";
  for (int k = 0; k < nentries;k++)
  {
    tree->GetEntry(k);
    if (passrndm > 0.1)
    {
      myFile << k << ',' << metl1 << '\n';
    }
  }
  myFile.close();


  TH2F* corrHist = new TH2F("corrHist","corrHist",nbins, metMin, metMax, nbins, metMin, metMax);
  for (int j = 0; j < nentries ; j++)
  {
    if (passrndm > 0.1)
    {
      corrHist->Fill(metl1,metcell);
    }
  }
  corrHist->Draw();
  //corrHist->GetCorrelationFactor();
  //std::cout << "Correlation factor between metl1 and metcell bulk: " << GetCorrelationFactor << std::endl;


}
