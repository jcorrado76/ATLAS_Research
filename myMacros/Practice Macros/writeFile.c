void writeFile()
{
  TString fileName = "dataFile.txt";
  std::cout << "FileName" << fileName << std::endl;

  ofstream logFile;
  logFile.open(fileName,'w');

  TString algA = "metcell";
  TString algB = "metmht";

  Float_t inputArray[4] = {1,2,3,4};
  Float_t outputArray[4] = {1,2,3,4};
  Float_t numEventsArray[4] = {1,2,3,4};
  Float_t thresholdAarray[4] = {1,2,3,4};
  Float_t thresholdBarray[4] = {1,2,3,4};

  Float_t x1 = 0.0001;
  Float_t x3 = 0.005;
  Float_t firstGuess = (x1+x3)/2.0;
  Float_t f1 = 1;
  Float_t firstOutput = 2;
  Float_t f3 = 3;
  Float_t counter1 = 1;
  Float_t initialNumbEvents = 2;
  Float_t counter3 = 3;
  Float_t algAMETx1thresh =1;
  Float_t algBMETx1thresh =1;
  Float_t algAMETx2thresh=2;
  Float_t algBMETx2thresh=2;
  Float_t algAMETx3thresh=3;
  Float_t algBMETx3thresh=3;
  int j=2;

  logFile << "Algorithms: " << algA << "\t" << algB << "\r\n";

  logFile << "Bisection Information: " << "\r\n";
  logFile << "Iteration Number : " << "\tIndividual Fraction: \t" << "Combined Fraction Kept: \t" << "Number Events Kept: \t" <<
  "Threshold for " + algA + '\t' << "Threshold for " + algB +'\t' << "\r\n";
  logFile << "x1\t\t\t" << x1 << "\t\t\t" << f1 << "\t\t\t\t" << counter1 << "\t\t\t" <<
  algAMETx1thresh << "\t\t\t" << algBMETx1thresh << "\r\n";
  logFile << "x2\t\t\t" << firstGuess << "\t\t\t" << firstOutput << "\t\t\t\t" << initialNumbEvents << "\t\t\t" <<
  algAMETx2thresh << "\t\t\t" << algBMETx2thresh <<"\r\n";
  logFile << "x3\t\t\t" << inputArray[2] << "\t\t\t" << f3 << "\t\t\t\t" << counter3 << "\t\t\t" <<
  algAMETx3thresh << "\t\t\t" << algBMETx3thresh <<"\r\n";
  for (int m = 1; m < j+1 ; m++)
  {
    logFile << Form("I%d",m) << "\t\t\t" << Form("%.7f",inputArray[m+2]) << "\t\t" << Form("%.7f",outputArray[m+2])
    << "\t\t\t" << Form("%.7f",numEventsArray[m+2]) << "\t\t" << Form("%.7f",thresholdAarray[m+2]) << "\t\t" <<
    Form("%.7f",thresholdBarray[m+2]) << "\r\n";
  }
  logFile << (gROOT->ProcessLine("gROOT->Time()")); 


  logFile.close();


}
