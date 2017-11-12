#include "mincerMacros.h"

Float_t computeMetNoMu( const Float_t mexoffrecal , const Float_t meyoffrecal , const Float_t mexoffrecalmuon , const Float_t meyoffrecalmuon )
{
    Float_t metnomu = sqrt(((mexoffrecal - mexoffrecalmuon) * (mexoffrecal - mexoffrecalmuon)) +
    ((meyoffrecal - meyoffrecalmuon)*(meyoffrecal - meyoffrecalmuon))); //compute metnomu
    return (metnomu);
}


Bool_t passTransverseMassCut( const Float_t metoffrecal , const Float_t mexoffrecal  , const Float_t meyoffrecal ,
                              const Float_t metoffrecalmuon , const Float_t mexoffrecalmuon , const Float_t meyoffrecalmuon )
{
    Float_t wLowerbnd = 40.0;
    Float_t wUpperbnd = 100.0;
    Float_t wValue = sqrt( 2.0 * metoffrecal * metoffrecalmuon * ( 1 + ( ( mexoffrecal * mexoffrecalmuon + meyoffrecal * meyoffrecalmuon ) /
                           ( metoffrecal * metoffrecalmuon ) ) ) );
    return( (( wValue >= wLowerbnd ) && ( wValue <= wUpperbnd )) );
}

Float_t computeThresh(const TH1F* target, const Float_t numberEventsToKeep)
{
    Int_t nbin = 0;
    //target is a right hand cumulative sum histogram
    target->GetBinWithContent( numberEventsToKeep , nbin , 5 , -1 , 20000 ); //if firstx<=0{firstx=1}; if lastx<firstx{lastx=fXaxis.GetNbinsX()};
    Float_t thresh = (target->GetXaxis())->GetBinCenter(nbin);
    return(thresh);
}


Float_t determineZeroBiasThresh( const TString& algName, Int_t & numPass , const Float_t frac ,
    const TString& threshFileName)
{
    //this function determines thresh to keep proper trigger rate for process 2 on algs A and B
    //these thresholds are used on both passnoalg and muon data
    userInfo* parameters = new userInfo();
    parameters->Print();
    const Float_t metL1Thresh = parameters->getMetL1Thresh();
    const Float_t actintCut = parameters->getActintCut();

    //get passnoalg tree
    const TString threshFilePath = "../myData/" + threshFileName;
	TFile *threshFileHandle = TFile::Open(threshFilePath, "READ");
	TTree *threshTree = (TTree*)(threshFileHandle->Get("tree"));
    const Int_t passnoAlgNentries = threshTree->GetEntries();
    Float_t passnoalg_actint = 0;

    //display inputs
    std::cout << "DETERMINETHRESH.C" << std::endl;
    std::cout << "using passnoalg datafile: " << threshFileName << std::endl;
    std::cout << "alg: " << algName << std::endl;
    std::cout << "using L1 thresh: " << metL1Thresh << std::endl;
    std::cout << "fraction of events to keep: " << frac << std::endl;
    std::cout << "passnoalg nentries: " << passnoAlgNentries << std::endl;

    //intialize parameters
    //numberEventsToKeep CHANGES BASED ON THE ACTINT CUT
    //TODO: maybe recompute this number based on actint cut every time. not sure
    const Int_t numberEventsToKeep = 1108;
	const Int_t nbins = parameters->getNbins();
	const Double_t metMin = parameters->getMetMin();
	const Double_t metMax = parameters->getMetMax();
	Float_t metl1, algMET;
    Int_t numberEventsKept = 0;
    Int_t passnoalgL1XE10 , passnoalgL1XE30 , passnoalgL1XE40 , passnoalgL1XE45;
    TH1F *indeterminateHist = new TH1F(algName, algName, nbins, metMin, metMax);

    //set branch address for zerobias branches
	threshTree->SetBranchAddress(algName,&algMET);
	threshTree->SetBranchAddress("metl1",&metl1);
    threshTree->SetBranchAddress("passnoalgL1XE10",&passnoalgL1XE10);
    threshTree->SetBranchAddress("passnoalgL1XE30",&passnoalgL1XE30);
    threshTree->SetBranchAddress("passnoalgL1XE40",&passnoalgL1XE40);
    threshTree->SetBranchAddress("passnoalgL1XE45",&passnoalgL1XE45);
    threshTree->SetBranchAddress("actint",&passnoalg_actint);

    for (Int_t k = 0; k < passnoAlgNentries; k++)
	{
		threshTree->GetEntry(k);
		if ( ( metl1 > metL1Thresh ) && ( passnoalg_actint > actintCut ) &&
            ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 || passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5 ) )
		{
			indeterminateHist->Fill(algMET);
		}
    }

    //compute the threshold to keep appropriate fraction
    TH1F *indeterminatetarget = (TH1F*) indeterminateHist->GetCumulative(kFALSE);
	Float_t indeterminateThresh = computeThresh(indeterminatetarget, numberEventsToKeep);
	std::cout << algName << "threshold: " << indeterminateThresh << std::endl;
	std::cout << "target number events to keep: " << numberEventsToKeep << std::endl;

    //determine number of events kept at determined threshold (gives idea of error due to binning)
	for (Int_t l = 0 ; l < passnoAlgNentries ; l++)
	{
		threshTree->GetEntry(l);
		if ( (algMET > indeterminateThresh) && (metl1 > metL1Thresh) && ( passnoalg_actint > actintCut ) &&
           ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 || passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5 ) )
		{
			numberEventsKept++;
		}
	}
    std::cout << "number of events kept at threshold: " << numberEventsKept << std::endl;
    threshFileHandle->Close();
    numPass = numberEventsKept;
	return(indeterminateThresh);
}

Float_t determineMuonEventsKeptCombined( const TString& algA, const Float_t threshA,
                                         const TString& algB, Float_t threshB,
                                         const TString& muonFileName)
{

    //this function determines process2 for muon events on combined alg


    //TODO: proof lite this
    const Float_t metL1Thresh = 50.0;
    //display algs and thresholds
    std::cout << "Determining fraction of muon events kept when using combined algorithm of " << algA << " at: " << threshA << ", "
    << algB << " at: " << threshB << " and metl1 at: " << metL1Thresh << std::endl;

    //get muon tree
    TString muonFilePath = "../myData/"+muonFileName;
    TFile * muonFile = TFile::Open(muonFilePath, "READ");
    TTree* muonTree = (TTree*)muonFile->Get("tree");
    Int_t muonNentries = muonTree->GetEntries();

    //initialize variables
    Float_t algAMET, algBMET,metl1, wValue;
    Int_t passmuon,passmuvarmed,recalBrokeFlag,cleanCutsFlag;
    Float_t metoffrecal,metoffrecalmuon,mexoffrecal,meyoffrecal,mexoffrecalmuon,meyoffrecalmuon,metrefmuon,mexrefmuon,meyrefmuon;
    Int_t numbPassedEvents = 0;
    Int_t numberMuonEvents = 0;


    muonTree->SetBranchAddress("passmu26med",&passmuon);
    muonTree->SetBranchAddress("passmu26varmed",&passmuvarmed);
    muonTree->SetBranchAddress("recalbroke",&recalBrokeFlag);
    muonTree->SetBranchAddress("passcleancuts",&cleanCutsFlag);
    muonTree->SetBranchAddress(algA,&algAMET);
    muonTree->SetBranchAddress("metl1",&metl1);
    muonTree->SetBranchAddress("metoffrecal", &metoffrecal);
    muonTree->SetBranchAddress("mexoffrecal", &mexoffrecal);
    muonTree->SetBranchAddress("meyoffrecal", &meyoffrecal);
    muonTree->SetBranchAddress("metoffrecalmuon", &metoffrecalmuon);
    muonTree->SetBranchAddress("mexoffrecalmuon", &mexoffrecalmuon);
    muonTree->SetBranchAddress("meyoffrecalmuon", &meyoffrecalmuon);
    muonTree->SetBranchAddress("metrefmuon", &metrefmuon);
    muonTree->SetBranchAddress("mexrefmuon", &mexrefmuon);
    muonTree->SetBranchAddress("meyrefmuon", &meyrefmuon);

    if ( algA != algB ) {//algs not the same, initialize second alg
         muonTree->SetBranchAddress( algB , &algBMET );
     }
    else {//algs are the same; set B to pass always
        threshB = threshA; algBMET = 0;
    }

    for (Int_t i  = 0 ; i < muonNentries ;i++)
      {
        muonTree->GetEntry(i);

        if (
               ((passmuon > 0.5) || (passmuvarmed > 0.5)) &&
               (cleanCutsFlag > 0.1 && recalBrokeFlag < 0.1) &&
               (passTransverseMassCut(metoffrecal ,mexoffrecal , meyoffrecal , metoffrecalmuon , mexoffrecalmuon , meyoffrecalmuon ))
           )
            {
              numberMuonEvents++;
            }
                if (((algAMET > threshA) && (algBMET > threshB) && (metl1 > metL1Thresh)))
                {
                    numbPassedEvents++;
                }
      }


    std::cout << "Number of muon events kept: " << numbPassedEvents << std::endl;
    Float_t frac = (Float_t) numbPassedEvents / (Float_t) numberMuonEvents;
    std::cout << "Fraction of muon events kept: " << frac << std::endl;

    muonFile->Close();


    return(numbPassedEvents);
}
