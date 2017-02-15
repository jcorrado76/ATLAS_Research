{

  // use plain black on white colors
  Int_t icol=0;
  gStyle->SetFrameBorderMode(icol);
  gStyle->SetCanvasBorderMode(icol);
  gStyle->SetPadBorderMode(icol);
  gStyle->SetPadColor(icol);
  gStyle->SetCanvasColor(icol);
  gStyle->SetStatColor(icol);
  //gStyle->SetFillColor(icol);
  gStyle->SetFrameFillColor(icol);
  gStyle->SetHistFillColor(icol);

  gStyle->SetTitleFillColor(icol);

  //   // set the paper & margin sizes
  gStyle->SetPaperSize(20,26);
  //   gStyle->SetPadTopMargin(0.05);
  //   gStyle->SetPadRightMargin(0.05);
  //   gStyle->SetPadBottomMargin(0.16);
  //   gStyle->SetPadLeftMargin(0.12);

  gStyle->SetPadGridX(1);
  gStyle->SetPadGridY(1);

  // use large fonts
  //Int_t font=72;
  Int_t font=42;
  Double_t tsize=0.05;
  gStyle->SetTextFont(font);
  gStyle->SetTextSize(tsize);
  gStyle->SetLabelFont(font,"x");
  gStyle->SetLabelFont(font,"y");
  gStyle->SetLabelFont(font,"z");
  gStyle->SetTitleFont(font,"x");
  gStyle->SetTitleFont(font,"y");
  gStyle->SetTitleFont(font,"z");
  gStyle->SetLabelSize(0.9*tsize,"x");
  gStyle->SetLabelSize(0.9*tsize,"y");
  gStyle->SetLabelSize(0.9*tsize,"z");
  gStyle->SetTitleSize(0.9*tsize,"x");
  gStyle->SetTitleSize(0.9*tsize,"y");
  gStyle->SetTitleSize(0.9*tsize,"z");

  // use bold lines and markers
  gStyle->SetMarkerStyle(20);
  gStyle->SetMarkerSize(1.2);
  gStyle->SetHistLineWidth(2.);
  gStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

  // get rid of X error bars and y error bar caps
  //  gStyle->SetErrorX(0.001);

  // do not display any of the standard histogram decorations
  //  gStyle->SetOptTitle(0);
  //  gStyle->SetOptStat(1111);
  //  gStyle->SetOptStat(0);
  //  gStyle->SetOptFit(1111);
  //  gStyle->SetOptFit(0);

  // put tick marks on top and RHS of plots
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  ////////////////////////////////////////////////////////////

  // rainbow palette
  gStyle->SetPalette(1);

//   gStyle->SetOptStat(1111111);  // Set stat options
//   gStyle->SetStatY(0.9);  // Set y-position (fraction of pad size)
//   gStyle->SetStatX(0.9);  // Set x-position (fraction of pad size)
//   gStyle->SetStatW(0.4);  // Set width of stat-box (fraction of pad size)
//   gStyle->SetStatH(0.2);  // Set height of stat-box (fraction of pad size)

///////////////////////////////////////////////////////////////////////
  /* Colors:
     1 Black
     2 red
     3 light green
     4 blue
     5 yellow
     6 magenta
     7 cyan
     8 dark green
     9 dark blue
     10 clear
     11 grey
     12 black

     28 brown

     46 orange-red-brown
  */

  //default defs:
  //int nmetbins=75;
  Double_t metmin=0.0;
  //Double_t metmax=150.0;
  //DEFs for getting high thersholds:
  int nmetbins=200;
  Double_t metmax=400.0;

  //int nmetbins=60;
  //Double_t metmax=300.0;

  //int nmetbins=80;
  //Double_t metmax=400.0;


  int colorfeb = 1;
  int colorfebcalib = 2;
  int coloremcluster =4;
  int colortclcw = 8;
  int colorl1 = 11;
  int colorefcell = 6;
  int colortruth = 7;
  int colorlochadtopo = 28;
  int colorreffinal = 46;

    //set delbg to 0.0 in two places below to use full set of bunches
    //set delbg to 12.5 to use recommended bunch cuts.

    TString bg1("0.0");
    TString bg2("80.0");
    TString bg3("160.0");
    TString bg4("240.0");
    TString bg5("500.0");
    TString delbg("12.5");
    //TString delbg("0.0");
    //TString delbg("3.5");
    TString L1METcut("0.0");
    //TString L1METcut("40.0");
    //TString L1METcut("70.0");
    TString BG7CUT1("(BCID >"+bg1+"+"+delbg+" && BCID < "+bg2+")"); 
    TString BG7CUT2("(BCID >"+bg2+"+"+delbg+" && BCID < "+bg3+")");
    TString BG7CUT3("(BCID >"+bg3+"+"+delbg+" && BCID < "+bg4+")");
    TString BG7CUT4("(BCID >"+bg4+"+"+delbg+" && BCID < "+bg5+")");
    TString BG7CUT(BG7CUT1+" || "+BG7CUT2+" || "+BG7CUT3+" || "+BG7CUT4);
    TString BG7CUTANDL1CUT("("+BG7CUT1+" || "+BG7CUT2+" || "+BG7CUT3+" || "+BG7CUT4+") && (Trig_l2met_Cell/1000.>"+L1METcut+")");

    double bung1 = 0.0;
    double bung2 = 80.0;
    double bung3 = 160.0;
    double bung4 = 240.0;
    double bung5 = 500.0;
    double delbung = 12.5;
    //double delbung = 0.0;
    //double delbung = 3.5;
    //double l1metcut = 40.0;
    double l1metcut = 0.0;
    //double l1metcut = 70.0;

  //TFile *firsttest = TFile::Open("AnalysisSkeleton.14tevttbar54mu25ns.e1565_s1499_s1504_r4326_r4371.aan.root"); // 2 July 2013 top files
  //TFile *firsttest = TFile::Open("AnalysisSkeleton.14tevjetjet_JZ5.54mu25ns.e1712_s1499_s1504_r4326_r4371.aan.root"); // 5 July jetjet 5Z files
  //TFile *firsttest = TFile::Open("AnalysisSkeleton.14tevjetjet_JZ3.54mu25ns.e1712_s1499_s1504_r4326_r4371.aan.root"); // 5 July jetjet 3Z files

  //Below is ttbar 54 Collisons, 25 ns with FEB info included
  //TFile *firsttest = TFile::Open("AnalysisSkeleton.14tevttbar25nsmu54.6August2013.e1565_s1499_s1504_r4326_r4371.aan.root");

  //Below is minbias 54 Collisons, 25 ns with FEB info included.  Try plottong minbias vs minbias to see that all is OK
  //TFile *firsttest = TFile::Open("AnalysisSkeleton.14tevminbias.7Aug2013.25nsmu54.e1564_s1499_s1504_r4326_r4371.aan.root");

  //Below is 2 jet Z3 54 Collisons, 25 ns with FEB info included
  //TFile *firsttest = TFile::Open("AnalysisSkeleton.14tev2Z3jet.7Aug2013.25nsmu54.e1712_s1499_s1504_r4326_r4371.aan.root");

  //Below is 2 jet Z1 54 Collisons, 25 ns with FEB info included
  //TFile *firsttest = TFile::Open("AnalysisSkeleton.14tevjetjet_JZ1.15Aug2013.25nsmu54.e1712_s1499_s1504_r4326_r4371.root");

  //Below is Z-> tau tau Z1 54 Collisons, 25 ns with FEB info included
  //TFile *firsttest = TFile::Open("AnalysisSkeleton.14tevZmumu25nsmu54.e1836_s1499_s1504_r4326_r4371.aan.root");

  //Below is 1M W+ -> e nu events 25 ns mu =60 3 Marhc 2014
  //TFile *firsttest = TFile::Open("AnalysisSkeleton.14tevWplusenu25ns60mu500K.e1564_s1682_s1691_r4939_r4643.aan.root");

  //Below is 1M ttbar events 25 ns?  mu =60 6 March 2014
  //TFile *firsttest = TFile::Open("AnalysisSkeleton.14tevttbar25ns60mu1M.e2176_s1682_s1691_r4709_r4643.aan.root");

  //Below is 3/26/2014 1M ZH->nu nu b b events, mu=60 25ns no L1 zero suppression
  TFile *firsttest = TFile::Open("AnalysisSkeleton.14tevZHnunubb25ns60mu10M.e2103_s1682_s1691_r4939_r4643.aan.root");
  //Below is 3/26/2014 10M minbias, mu=60 25ns no L1 zero suppression
  //TFile *firsttest = TFile::Open("AnalysisSkeleton.14tevMinbais25ns60mu10M.e1133_s1717_s1691_r5286_r4643.aan.root");
  //Below is 8/12/14 1M Wplus mu nu imprved L1 and HLT zero suppression but only 1/2 the files
  //TFile *firsttest = TFile::Open("AnalysisSkeleton.14TevWplusmunu100files12August2014.e1564_s1682_s1691_r5634_r4643.aan.root");
  //Below is 8/12/14 1M Hznunu bb imprved L1 and HLT zero suppression but only 1/5 the files
  //TFile *firsttest = TFile::Open("AnalysisSkeleton.14TevHZnunubb10files12August2014.e2103_s1682_s1691_r5634_r4643.aan.root");
  //Below is 8/12/14 1M Hznunu bb improved L1 and HLT zero suppression
  TFile *firsttest = TFile::Open("AnalysisSkeleton.14TevHZnunubb1M12August2014.e2103_s1682_s1691_r5634_r4643.aan.root");

  //General definitions for efficiency:
  TTree *thistree = (TTree*)firsttest->Get("tree_AS");
  Double_t reffinal_met,l1_met,l2_met,ef_met_cell,ef_met_tclcw,ef_met_emcluster;
  Double_t l2febcalib_metx_presamplB, l2febcalib_metx_emb1,   l2febcalib_metx_emb2,     l2febcalib_metx_emb3, l2febcalib_metx_presamplE;
  Double_t l2febcalib_metx_eme1,      l2febcalib_metx_eme2,   l2febcalib_metx_eme3,     l2febcalib_metx_hec,  l2febcalib_metx_TileBar;
  Double_t l2febcalib_metx_TileExt,   l2febcalib_metx_FCalEM, l2febcalib_metx_FCalHad1, l2febcalib_metx_FCalHad2;
  Double_t l2febcalib_mety_presamplB, l2febcalib_mety_emb1,   l2febcalib_mety_emb2,     l2febcalib_mety_emb3, l2febcalib_mety_presamplE;
  Double_t l2febcalib_mety_eme1,      l2febcalib_mety_eme2,   l2febcalib_mety_eme3,     l2febcalib_mety_hec,  l2febcalib_mety_TileBar;
  Double_t l2febcalib_mety_TileExt,   l2febcalib_mety_FCalEM, l2febcalib_mety_FCalHad1, l2febcalib_mety_FCalHad2;
  
  Double_t olmetxrefele, olmetxrefgamma, olmetxreftau, olmetxrefjet, olmetxcellouteflow;
  Double_t olmetyrefele, olmetyrefgamma, olmetyreftau, olmetyrefjet, olmetycellouteflow;

  Double_t truthmetx, truthmety;

  Double_t lochadtopomet, lochadtoposet;

  Int_t tbcid;
  TBranch *b_RefFinal_met = new TBranch();
  TBranch *b_L1_met = new TBranch();
  TBranch *b_L2_met = new TBranch();
  TBranch *b_EF_met_cell = new TBranch();
  TBranch *b_EF_met_tclcw = new TBranch();
  TBranch *b_EF_met_emcluster = new TBranch();
  TBranch *b_tbcid = new TBranch();

  TBranch *b_L2febcalib_metx_presamplB = new TBranch();
  TBranch *b_L2febcalib_metx_emb1 = new TBranch();
  TBranch *b_L2febcalib_metx_emb2 = new TBranch();
  TBranch *b_L2febcalib_metx_emb3 = new TBranch();
  TBranch *b_L2febcalib_metx_presamplE = new TBranch();
  TBranch *b_L2febcalib_metx_eme1 = new TBranch();
  TBranch *b_L2febcalib_metx_eme2 = new TBranch();
  TBranch *b_L2febcalib_metx_eme3 = new TBranch();
  TBranch *b_L2febcalib_metx_hec = new TBranch();
  TBranch *b_L2febcalib_metx_TileBar = new TBranch();
  TBranch *b_L2febcalib_metx_TileExt = new TBranch();
  TBranch *b_L2febcalib_metx_FCalEM = new TBranch();
  TBranch *b_L2febcalib_metx_FCalHad1 = new TBranch();
  TBranch *b_L2febcalib_metx_FCalHad2 = new TBranch();

  TBranch *b_L2febcalib_mety_presamplB = new TBranch();
  TBranch *b_L2febcalib_mety_emb1 = new TBranch();
  TBranch *b_L2febcalib_mety_emb2 = new TBranch();
  TBranch *b_L2febcalib_mety_emb3 = new TBranch();
  TBranch *b_L2febcalib_mety_presamplE = new TBranch();
  TBranch *b_L2febcalib_mety_eme1 = new TBranch();
  TBranch *b_L2febcalib_mety_eme2 = new TBranch();
  TBranch *b_L2febcalib_mety_eme3 = new TBranch();
  TBranch *b_L2febcalib_mety_hec = new TBranch();
  TBranch *b_L2febcalib_mety_TileBar = new TBranch();
  TBranch *b_L2febcalib_mety_TileExt = new TBranch();
  TBranch *b_L2febcalib_mety_FCalEM = new TBranch();
  TBranch *b_L2febcalib_mety_FCalHad1 = new TBranch();
  TBranch *b_L2febcalib_mety_FCalHad2 = new TBranch();

  TBranch *b_olmetxrefele = new TBranch();
  TBranch *b_olmetxrefgamma = new TBranch();
  TBranch *b_olmetxreftau = new TBranch();
  TBranch *b_olmetxrefjet = new TBranch();
  TBranch *b_olmetxcellouteflow = new TBranch();
  TBranch *b_olmetyrefele = new TBranch();
  TBranch *b_olmetyrefgamma = new TBranch();
  TBranch *b_olmetyreftau = new TBranch();
  TBranch *b_olmetyrefjet = new TBranch();
  TBranch *b_olmetycellouteflow = new TBranch();

  TBranch *b_truthmetx = new TBranch();
  TBranch *b_truthmety = new TBranch();

  TBranch *b_lochadtopomet = new TBranch();
  TBranch *b_lochadtoposet = new TBranch();

  thistree->SetBranchAddress("Olmet_reffinal",&reffinal_met,&b_RefFinal_met);
  thistree->SetBranchAddress("Trig_l2met_Cell",&l1_met,&b_L1_met);
  thistree->SetBranchAddress("Trig_efmet_FEB",&l2_met,&b_L2_met);
  thistree->SetBranchAddress("Trig_efmet_Cell",&ef_met_cell,&b_EF_met_cell);
  thistree->SetBranchAddress("Trig_efmet_tclcw",&ef_met_tclcw,&b_EF_met_tclcw);
  thistree->SetBranchAddress("Trig_efmet_emcluster",&ef_met_emcluster,&b_EF_met_emcluster);
  thistree->SetBranchAddress("BCID",&tbcid,&b_tbcid);

  thistree->SetBranchAddress("Trig_efmetx_FEB_presamplB", &l2febcalib_metx_presamplB, &b_L2febcalib_metx_presamplB);
  thistree->SetBranchAddress("Trig_efmetx_FEB_emb1", &l2febcalib_metx_emb1, &b_L2febcalib_metx_emb1);
  thistree->SetBranchAddress("Trig_efmetx_FEB_emb2", &l2febcalib_metx_emb2, &b_L2febcalib_metx_emb2);
  thistree->SetBranchAddress("Trig_efmetx_FEB_emb3", &l2febcalib_metx_emb3, &b_L2febcalib_metx_emb3);
  thistree->SetBranchAddress("Trig_efmetx_FEB_presamplE", &l2febcalib_metx_presamplE, &b_L2febcalib_metx_presamplE);
  thistree->SetBranchAddress("Trig_efmetx_FEB_eme1", &l2febcalib_metx_eme1, &b_L2febcalib_metx_eme1);
  thistree->SetBranchAddress("Trig_efmetx_FEB_eme2", &l2febcalib_metx_eme2, &b_L2febcalib_metx_eme2);
  thistree->SetBranchAddress("Trig_efmetx_FEB_eme3", &l2febcalib_metx_eme3, &b_L2febcalib_metx_eme3);
  thistree->SetBranchAddress("Trig_efmetx_FEB_hec", &l2febcalib_metx_hec, &b_L2febcalib_metx_hec);
  thistree->SetBranchAddress("Trig_efmetx_FEB_TileBar", &l2febcalib_metx_TileBar, &b_L2febcalib_metx_TileBar);
  thistree->SetBranchAddress("Trig_efmetx_FEB_TileExt", &l2febcalib_metx_TileExt, &b_L2febcalib_metx_TileExt);
  thistree->SetBranchAddress("Trig_efmetx_FEB_FCalEM", &l2febcalib_metx_FCalEM, &b_L2febcalib_metx_FCalEM);
  thistree->SetBranchAddress("Trig_efmetx_FEB_FCalHad1", &l2febcalib_metx_FCalHad1, &b_L2febcalib_metx_FCalHad1);
  thistree->SetBranchAddress("Trig_efmetx_FEB_FCalHad2", &l2febcalib_metx_FCalHad2, &b_L2febcalib_metx_FCalHad2);

  thistree->SetBranchAddress("Trig_efmety_FEB_presamplB", &l2febcalib_mety_presamplB, &b_L2febcalib_mety_presamplB);
  thistree->SetBranchAddress("Trig_efmety_FEB_emb1", &l2febcalib_mety_emb1, &b_L2febcalib_mety_emb1);
  thistree->SetBranchAddress("Trig_efmety_FEB_emb2", &l2febcalib_mety_emb2, &b_L2febcalib_mety_emb2);
  thistree->SetBranchAddress("Trig_efmety_FEB_emb3", &l2febcalib_mety_emb3, &b_L2febcalib_mety_emb3);
  thistree->SetBranchAddress("Trig_efmety_FEB_presamplE", &l2febcalib_mety_presamplE, &b_L2febcalib_mety_presamplE);
  thistree->SetBranchAddress("Trig_efmety_FEB_eme1", &l2febcalib_mety_eme1, &b_L2febcalib_mety_eme1);
  thistree->SetBranchAddress("Trig_efmety_FEB_eme2", &l2febcalib_mety_eme2, &b_L2febcalib_mety_eme2);
  thistree->SetBranchAddress("Trig_efmety_FEB_eme3", &l2febcalib_mety_eme3, &b_L2febcalib_mety_eme3);
  thistree->SetBranchAddress("Trig_efmety_FEB_hec", &l2febcalib_mety_hec, &b_L2febcalib_mety_hec);
  thistree->SetBranchAddress("Trig_efmety_FEB_TileBar", &l2febcalib_mety_TileBar, &b_L2febcalib_mety_TileBar);
  thistree->SetBranchAddress("Trig_efmety_FEB_TileExt", &l2febcalib_mety_TileExt, &b_L2febcalib_mety_TileExt);
  thistree->SetBranchAddress("Trig_efmety_FEB_FCalEM", &l2febcalib_mety_FCalEM, &b_L2febcalib_mety_FCalEM);
  thistree->SetBranchAddress("Trig_efmety_FEB_FCalHad1", &l2febcalib_mety_FCalHad1, &b_L2febcalib_mety_FCalHad1);
  thistree->SetBranchAddress("Trig_efmety_FEB_FCalHad2", &l2febcalib_mety_FCalHad2, &b_L2febcalib_mety_FCalHad2);

  thistree->SetBranchAddress("Olmetx_refele", &olmetxrefele, &b_olmetxrefele);
  thistree->SetBranchAddress("Olmetx_refgamma", &olmetxrefgamma, &b_olmetxrefgamma);
  thistree->SetBranchAddress("Olmetx_reftau", &olmetxreftau, &b_olmetxreftau);
  thistree->SetBranchAddress("Olmetx_refjet", &olmetxrefjet, &b_olmetxrefjet);
  thistree->SetBranchAddress("Olmetx_cellouteflow", &olmetxcellouteflow, &b_olmetxcellouteflow);
  thistree->SetBranchAddress("Olmety_refele", &olmetyrefele, &b_olmetyrefele);
  thistree->SetBranchAddress("Olmety_refgamma", &olmetyrefgamma, &b_olmetyrefgamma);
  thistree->SetBranchAddress("Olmety_reftau", &olmetyreftau, &b_olmetyreftau);
  thistree->SetBranchAddress("Olmety_refjet", &olmetyrefjet, &b_olmetyrefjet);
  thistree->SetBranchAddress("Olmety_cellouteflow", &olmetycellouteflow, &b_olmetycellouteflow);

  thistree->SetBranchAddress("Truth_metx", &truthmetx, &b_truthmetx);
  thistree->SetBranchAddress("Truth_mety", &truthmety, &b_truthmety);

  thistree->SetBranchAddress("Olmet_calo_lochadtopo", &lochadtopomet, &b_lochadtopomet);
  thistree->SetBranchAddress("Olset_calo_lochadtopo", &lochadtoposet, &b_lochadtoposet);

  int nentries = thistree->GetEntries();
  bool pass;
  int nbins=30;
  Double_t reffinalmin=0.0;
  Double_t reffinalmax=300.0;

  TCanvas *L1_MATCHED_EFFICIENCY = new TCanvas("L1_MATCHED_EFFICIENCY","L1_MATCHED_EFFICIENCY");
    TEfficiency *EFF_L1_matched = new TEfficiency
                   //("EFF_L1_matched","L1_XE81 Efficiency;Truth MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
                   ("EFF_L1_matched","L1_XE81 Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
                   //("EFF_L1_matched","L1_XE81 Efficiency;LocHadTopo MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);

    for (int i=0; i<nentries; i++) 
	{
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (l1_met/1000.0>81.   && l1_met/1000.>l1metcut) {
          pass=true;
        } else {
          pass=false;
        }
        //RefFinal:
        //EFF_L1_matched->Fill(pass,reffinal_met/1000.0);
        //RefFinal Calorimeter only:
        EFF_L1_matched->Fill(pass,sqrt((olmetxrefele+olmetxrefgamma+olmetxreftau+olmetxrefjet+olmetxcellouteflow)*(olmetxrefele+olmetxrefgamma+\
			olmetxreftau+olmetxrefjet+olmetxcellouteflow)+(olmetyrefele+olmetyrefgamma+olmetyreftau+olmetyrefjet+olmetycellouteflow)*(olmetyrefele+\
				olmetyrefgamma+olmetyreftau+olmetyrefjet+olmetycellouteflow))/1000.);
       //Truth:
       //EFF_L1_matched->Fill(pass,sqrt(truthmetx*truthmetx+truthmety*truthmety)/1000.0);
       //LocHadTopo
       //EFF_L1_matched->Fill(pass,lochadtopomet/1000.0);
      } // end in correct bcid
    }
    EFF_L1_matched->SetMarkerStyle(20);
    EFF_L1_matched->SetMarkerSize(1.1);
    EFF_L1_matched->SetMarkerColor(colorl1);
    EFF_L1_matched->SetLineColor(colorl1);
    EFF_L1_matched->Draw();

  TCanvas *L2_FEB_MATCHED_EFFICIENCY = new TCanvas("L2_FEB_MATCHED_EFFICIENCY","L2_FEB_MATCHED_EFFICIENCY");
    TEfficiency *EFF_L2_feb_matched = new TEfficiency
                   //("EFF_L2_feb_matched","L2_xe82_feb Efficiency;Truth MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
                   ("EFF_L2_feb_matched","L2_xe82_feb Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
                   //("EFF_L2_feb_matched","L2_xe82_feb Efficiency;LocHadTopo MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (l2_met/1000.0>82.   && l1_met/1000.>l1metcut) {
          pass=true;
        } else {
          pass=false;
        }
        //RefFinal:
        //EFF_L2_feb_matched->Fill(pass,reffinal_met/1000.0);
        //RefFinal Calorimeter only:
        EFF_L2_feb_matched->Fill(pass,sqrt((olmetxrefele+olmetxrefgamma+olmetxreftau+olmetxrefjet+olmetxcellouteflow)*(olmetxrefele+olmetxrefgamma+olmetxreftau+olmetxrefjet+olmetxcellouteflow)+(olmetyrefele+olmetyrefgamma+olmetyreftau+olmetyrefjet+olmetycellouteflow)*(olmetyrefele+olmetyrefgamma+olmetyreftau+olmetyrefjet+olmetycellouteflow))/1000.);
       //Truth:
       //EFF_L2_feb_matched->Fill(pass,sqrt(truthmetx*truthmetx+truthmety*truthmety)/1000.0);
       //LocHadTopo
       //EFF_L2_feb_matched->Fill(pass,lochadtopomet/1000.0);
      } // end in correct bcid
    }
    EFF_L2_feb_matched->SetMarkerStyle(20);
    EFF_L2_feb_matched->SetMarkerSize(1.1);
    EFF_L2_feb_matched->SetMarkerColor(colorfeb);
    EFF_L2_feb_matched->SetLineColor(colorfeb);
    EFF_L2_feb_matched->Draw();
  
  TCanvas *L2_FEBCALIB_MATCHED_EFFICIENCY = new TCanvas("L2_FEBCALIB_MATCHED_EFFICIENCY","L2_FEBCALIB_MATCHED_EFFICIENCY");
    TEfficiency *EFF_L2_febcalib_matched = new TEfficiency
                   //("EFF_L2_febcalib_matched","L2_xe190_febcalib Efficiency;Truth MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
                   ("EFF_L2_febcalib_matched","L2_xe190_febcalib Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
                   //("EFF_L2_febcalib_matched","L2_xe190_febcalib Efficiency;LocHadTopo MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i); // one row in matrix
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        //Andrew's JetTauETmiss constants:
        //if (sqrt((1.80*l2febcalib_metx_presamplB+1.38*l2febcalib_metx_emb1+1.18*l2febcalib_metx_emb2+1.58*l2febcalib_metx_emb3+1.88*l2febcalib_metx_presamplE+1.57*l2febcalib_metx_eme1+1.68*l2febcalib_metx_eme2+2.67*l2febcalib_metx_eme3+1.51*l2febcalib_metx_hec+1.43*l2febcalib_metx_TileBar+1.53*l2febcalib_metx_TileExt+1.86*l2febcalib_metx_FCalEM+2.26*l2febcalib_metx_FCalHad1+3.06*l2febcalib_metx_FCalHad2)*(1.80*l2febcalib_metx_presamplB+1.38*l2febcalib_metx_emb1+1.18*l2febcalib_metx_emb2+1.58*l2febcalib_metx_emb3+1.88*l2febcalib_metx_presamplE+1.57*l2febcalib_metx_eme1+1.68*l2febcalib_metx_eme2+2.67*l2febcalib_metx_eme3+1.51*l2febcalib_metx_hec+1.43*l2febcalib_metx_TileBar+1.53*l2febcalib_metx_TileExt+1.86*l2febcalib_metx_FCalEM+2.26*l2febcalib_metx_FCalHad1+3.06*l2febcalib_metx_FCalHad2)+(1.80*l2febcalib_mety_presamplB+1.38*l2febcalib_mety_emb1+1.18*l2febcalib_mety_emb2+1.58*l2febcalib_mety_emb3+1.88*l2febcalib_mety_presamplE+1.57*l2febcalib_mety_eme1+1.68*l2febcalib_mety_eme2+2.67*l2febcalib_mety_eme3+1.51*l2febcalib_mety_hec+1.43*l2febcalib_mety_TileBar+1.53*l2febcalib_mety_TileExt+1.86*l2febcalib_mety_FCalEM+2.26*l2febcalib_mety_FCalHad1+3.06*l2febcalib_mety_FCalHad2)*(1.80*l2febcalib_mety_presamplB+1.38*l2febcalib_mety_emb1+1.18*l2febcalib_mety_emb2+1.58*l2febcalib_mety_emb3+1.88*l2febcalib_mety_presamplE+1.57*l2febcalib_mety_eme1+1.68*l2febcalib_mety_eme2+2.67*l2febcalib_mety_eme3+1.51*l2febcalib_mety_hec+1.43*l2febcalib_mety_TileBar+1.53*l2febcalib_mety_TileExt+1.86*l2febcalib_mety_FCalEM+2.26*l2febcalib_mety_FCalHad1+3.06*l2febcalib_mety_FCalHad2))/1000.0>190.  && l1_met/1000.>l1metcut) {
        //Andrew's minbias constants
        if (sqrt((2.36*l2febcalib_metx_presamplB+2.74*l2febcalib_metx_emb1+2.64*l2febcalib_metx_emb2+3.24*l2febcalib_metx_emb3+3.40*l2febcalib_metx_presamplE+2.18*l2febcalib_metx_eme1+2.78*l2febcalib_metx_eme2+4.08*l2febcalib_metx_eme3+1.73*l2febcalib_metx_hec+1.96*l2febcalib_metx_TileBar+0.36*l2febcalib_metx_TileExt+2.08*l2febcalib_metx_FCalEM+2.48*l2febcalib_metx_FCalHad1+2.88*l2febcalib_metx_FCalHad2)*(2.36*l2febcalib_metx_presamplB+2.74*l2febcalib_metx_emb1+2.64*l2febcalib_metx_emb2+3.24*l2febcalib_metx_emb3+3.40*l2febcalib_metx_presamplE+2.18*l2febcalib_metx_eme1+2.78*l2febcalib_metx_eme2+4.08*l2febcalib_metx_eme3+1.73*l2febcalib_metx_hec+1.96*l2febcalib_metx_TileBar+0.36*l2febcalib_metx_TileExt+2.08*l2febcalib_metx_FCalEM+2.48*l2febcalib_metx_FCalHad1+2.88*l2febcalib_metx_FCalHad2)+(2.36*l2febcalib_mety_presamplB+2.74*l2febcalib_mety_emb1+2.64*l2febcalib_mety_emb2+3.24*l2febcalib_mety_emb3+3.40*l2febcalib_mety_presamplE+2.18*l2febcalib_mety_eme1+2.78*l2febcalib_mety_eme2+4.08*l2febcalib_mety_eme3+1.73*l2febcalib_mety_hec+1.96*l2febcalib_mety_TileBar+0.36*l2febcalib_mety_TileExt+2.08*l2febcalib_mety_FCalEM+2.48*l2febcalib_mety_FCalHad1+2.88*l2febcalib_mety_FCalHad2)*(2.36*l2febcalib_mety_presamplB+2.74*l2febcalib_mety_emb1+2.64*l2febcalib_mety_emb2+3.24*l2febcalib_mety_emb3+3.40*l2febcalib_mety_presamplE+2.18*l2febcalib_mety_eme1+2.78*l2febcalib_mety_eme2+4.08*l2febcalib_mety_eme3+1.73*l2febcalib_mety_hec+1.96*l2febcalib_mety_TileBar+0.36*l2febcalib_mety_TileExt+2.08*l2febcalib_mety_FCalEM+2.48*l2febcalib_mety_FCalHad1+2.88*l2febcalib_mety_FCalHad2))/1000.0>190.  && l1_met/1000.>l1metcut) {
          pass=true;
        } else {
          pass=false;
        }
        //RefFinal:
        //EFF_L2_febcalib_matched->Fill(pass,reffinal_met/1000.0);
        //RefFinal Calorimeter only:
        EFF_L2_febcalib_matched->Fill(pass,sqrt((olmetxrefele+olmetxrefgamma+olmetxreftau+olmetxrefjet+olmetxcellouteflow)*(olmetxrefele+olmetxrefgamma+olmetxreftau+olmetxrefjet+olmetxcellouteflow)+(olmetyrefele+olmetyrefgamma+olmetyreftau+olmetyrefjet+olmetycellouteflow)*(olmetyrefele+olmetyrefgamma+olmetyreftau+olmetyrefjet+olmetycellouteflow))/1000.);
       //Truth:
       //EFF_L2_febcalib_matched->Fill(pass,sqrt(truthmetx*truthmetx+truthmety*truthmety)/1000.0);
       //LocHadTopo
       //EFF_L2_febcalib_matched->Fill(pass,lochadtopomet/1000.0);
      } // end in correct bcid
    }
    EFF_L2_febcalib_matched->SetMarkerStyle(20);
    EFF_L2_febcalib_matched->SetMarkerSize(1.1);
    EFF_L2_febcalib_matched->SetMarkerColor(colorfebcalib);
    EFF_L2_febcalib_matched->SetLineColor(colorfebcalib);
    EFF_L2_febcalib_matched->Draw();

  TCanvas *EF_TCLCW_MATCHED_EFFICIENCY = new TCanvas("EF_TCLCW_MATCHED_EFFICIENCY","EF_TCLCW_MATCHED_EFFICIENCY");
    TEfficiency *EFF_EF_tclcw_matched = new TEfficiency
                   //("EFF_EF_tclcw_matched","EF_xe196_tclcw Efficiency;Truth MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
                   ("EFF_EF_tclcw_matched","EF_xe196_tclcw Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
                   //("EFF_EF_tclcw_matched","EF_xe196_tclcw Efficiency;LocHadTopo MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_tclcw/1000.0>196.  && l1_met/1000.>l1metcut) {
          pass=true;
        } else {
          pass=false;
        }
        //RefFinal:
        //EFF_EF_tclcw_matched->Fill(pass,reffinal_met/1000.0);
        //RefFinal Calorimeter only:
        EFF_EF_tclcw_matched->Fill(pass,sqrt((olmetxrefele+olmetxrefgamma+olmetxreftau+olmetxrefjet+olmetxcellouteflow)*(olmetxrefele+olmetxrefgamma+olmetxreftau+olmetxrefjet+olmetxcellouteflow)+(olmetyrefele+olmetyrefgamma+olmetyreftau+olmetyrefjet+olmetycellouteflow)*(olmetyrefele+olmetyrefgamma+olmetyreftau+olmetyrefjet+olmetycellouteflow))/1000.);
       //Truth:
       //EFF_EF_tclcw_matched->Fill(pass,sqrt(truthmetx*truthmetx+truthmety*truthmety)/1000.0);
       //LocHadTopo
       //EFF_EF_tclcw_matched->Fill(pass,lochadtopomet/1000.0);
      } // end in correct bcid
    }
    EFF_EF_tclcw_matched->SetMarkerStyle(20);
    EFF_EF_tclcw_matched->SetMarkerSize(1.1);
    EFF_EF_tclcw_matched->SetMarkerColor(colortclcw);
    EFF_EF_tclcw_matched->SetLineColor(colortclcw);
    EFF_EF_tclcw_matched->Draw();

  TCanvas *EF_EMCLUSTER_MATCHED_EFFICIENCY = new TCanvas("EF_EMCLUSTER_MATCHED_EFFICIENCY","EF_EMCLUSTER_MATCHED_EFFICIENCY");
    TEfficiency *EFF_EF_emcluster_matched = new TEfficiency
                   //("EFF_EF_emcluster_matched","EF_xe120_emcluster Efficiency;Truth MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
                   ("EFF_EF_emcluster_matched","EF_xe120_emcluster Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
                   //("EFF_EF_emcluster_matched","EF_xe120_emcluster Efficiency;LocHadTopo MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_emcluster/1000.0>120.  && l1_met/1000.>l1metcut) {
          pass=true;
        } else {
          pass=false;
        }
        //RefFinal:
        //EFF_EF_emcluster_matched->Fill(pass,reffinal_met/1000.0);
        //RefFinal Calorimeter only:
        EFF_EF_emcluster_matched->Fill(pass,sqrt((olmetxrefele+olmetxrefgamma+olmetxreftau+olmetxrefjet+olmetxcellouteflow)*(olmetxrefele+olmetxrefgamma+olmetxreftau+olmetxrefjet+olmetxcellouteflow)+(olmetyrefele+olmetyrefgamma+olmetyreftau+olmetyrefjet+olmetycellouteflow)*(olmetyrefele+olmetyrefgamma+olmetyreftau+olmetyrefjet+olmetycellouteflow))/1000.);
       //Truth:
       //EFF_EF_emcluster_matched->Fill(pass,sqrt(truthmetx*truthmetx+truthmety*truthmety)/1000.0);
       //LocHadTopo
       //EFF_EF_emcluster_matched->Fill(pass,lochadtopomet/1000.0);
      } // end in correct bcid
    }
    EFF_EF_emcluster_matched->SetMarkerStyle(20);
    EFF_EF_emcluster_matched->SetMarkerSize(1.1);
    EFF_EF_emcluster_matched->SetMarkerColor(coloremcluster);
    EFF_EF_emcluster_matched->SetLineColor(coloremcluster);
    EFF_EF_emcluster_matched->Draw();

  TCanvas *EF_CELL_MATCHED_EFFICIENCY = new TCanvas("EF_CELL_MATCHED_EFFICIENCY","EF_CELL_MATCHED_EFFICIENCY");
    TEfficiency *EFF_EF_cell_matched = new TEfficiency
                   //("EFF_EF_cell_matched","EF_xe87_cell Efficiency;Truth MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
                   ("EFF_EF_cell_matched","EF_xe87_cell Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
                   //("EFF_EF_cell_matched","EF_xe87_cell Efficiency;LocHadTopo MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++)
	{
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_cell/1000.0>87.  && l1_met/1000.>l1metcut) {
          pass=true;
        } else {
          pass=false;
        }
        //RefFinal:
        //EFF_EF_cell_matched->Fill(pass,reffinal_met/1000.0);
        //RefFinal Calorimeter only:
        EFF_EF_cell_matched->Fill(pass,sqrt((olmetxrefele+olmetxrefgamma+olmetxreftau+olmetxrefjet+olmetxcellouteflow)*(olmetxrefele+olmetxrefgamma+olmetxreftau+olmetxrefjet+olmetxcellouteflow)+(olmetyrefele+olmetyrefgamma+olmetyreftau+olmetyrefjet+olmetycellouteflow)*(olmetyrefele+olmetyrefgamma+olmetyreftau+olmetyrefjet+olmetycellouteflow))/1000.);
       //Truth:
       //EFF_EF_cell_matched->Fill(pass,sqrt(truthmetx*truthmetx+truthmety*truthmety)/1000.0);
       //LocHadTopo
       //EFF_EF_cell_matched->Fill(pass,lochadtopomet/1000.0);
      } // end in correct bcid
    }
    EFF_EF_cell_matched->SetMarkerStyle(20);
    EFF_EF_cell_matched->SetMarkerSize(1.1);
    EFF_EF_cell_matched->SetMarkerColor(colorefcell);
    EFF_EF_cell_matched->SetLineColor(colorefcell);
    EFF_EF_cell_matched->Draw();

  TCanvas *OL_LOCHADTOPO_MATCHED_EFFICIENCY = new TCanvas("OL_LOCHADTOPO_MATCHED_EFFICIENCY","OL_LOCHADTOPO_MATCHED_EFFICIENCY");
    TEfficiency *EFF_OL_lochadtopo_matched = new TEfficiency
                   //("EFF_OL_lochadtopo_matched","LocHadTopo 192 GeV Efficiency;Truth MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
                   ("EFF_OL_lochadtopo_matched","LocHadTopo 192 GeV Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
                   //("EFF_OL_lochadtopo_matched","LocHadTopo 192 GeV Efficiency;LocHadTopo MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (lochadtopomet/1000.0>192.  && l1_met/1000.>l1metcut) {
          pass=true;
        } else {
          pass=false;
        }
        //RefFinal:
        //EFF_OL_lochadtopo_matched->Fill(pass,reffinal_met/1000.0);
        //RefFinal Calorimeter only:
        EFF_OL_lochadtopo_matched->Fill(pass,sqrt((olmetxrefele+olmetxrefgamma+olmetxreftau+olmetxrefjet+olmetxcellouteflow)*(olmetxrefele+olmetxrefgamma+olmetxreftau+olmetxrefjet+olmetxcellouteflow)+(olmetyrefele+olmetyrefgamma+olmetyreftau+olmetyrefjet+olmetycellouteflow)*(olmetyrefele+olmetyrefgamma+olmetyreftau+olmetyrefjet+olmetycellouteflow))/1000.);
       //Truth:
       //EFF_OL_lochadtopo_matched->Fill(pass,sqrt(truthmetx*truthmetx+truthmety*truthmety)/1000.0);
       //LocHadTopo
       //EFF_OL_lochadtopo_matched->Fill(pass,lochadtopomet/1000.0);
      } // end in correct bcid
    }
    EFF_OL_lochadtopo_matched->SetMarkerStyle(20);
    EFF_OL_lochadtopo_matched->SetMarkerSize(1.1);
    EFF_OL_lochadtopo_matched->SetMarkerColor(colorlochadtopo);
    EFF_OL_lochadtopo_matched->SetLineColor(colorlochadtopo);
    EFF_OL_lochadtopo_matched->Draw();

  TCanvas *OL_REFFINALCALOPARTS_MATCHED_EFFICIENCY = new TCanvas("OL_REFFINALCALOPARTS_MATCHED_EFFICIENCY","OL_REFFINALCALOPARTS_MATCHED_EFFICIENCY");
    TEfficiency *EFF_OL_reffinalcaloparts_matched = new TEfficiency
                   //("EFF_OL_reffinalcaloparts_matched","RefFinal Calo Parts 260 GeV Efficiency;Truth MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
                   ("EFF_OL_reffinalcaloparts_matched","RefFinal Calo Parts 260 GeV Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
                   //("EFF_OL_reffinalcaloparts_matched","RefFinal Calo Parts 260 GeV Efficiency;LocHadTopo MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        //RefFinal:
        //if(reffinal_met/1000.0>260. && l1_met/1000.>l1metcut) {
        //RefFinal calo parts:
        if (sqrt((olmetxrefele+olmetxrefgamma+olmetxreftau+olmetxrefjet+olmetxcellouteflow)*(olmetxrefele+olmetxrefgamma+olmetxreftau+olmetxrefjet+olmetxcellouteflow)+(olmetyrefele+olmetyrefgamma+olmetyreftau+olmetyrefjet+olmetycellouteflow)*(olmetyrefele+olmetyrefgamma+olmetyreftau+olmetyrefjet+olmetycellouteflow))/1000.>260.  && l1_met/1000.>l1metcut) {
        //RefFinlal calo parts without soft energy:
        //if (sqrt((olmetxrefele+olmetxrefgamma+olmetxreftau+olmetxrefjet)*(olmetxrefele+olmetxrefgamma+olmetxreftau+olmetxrefjet)+(olmetyrefele+olmetyrefgamma+olmetyreftau+olmetyrefjet)*(olmetyrefele+olmetyrefgamma+olmetyreftau+olmetyrefjet))/1000.>260.  && l1_met/1000.>l1metcut) {
          pass=true;
        } else {
          pass=false;
        }
        //RefFinal:
        //EFF_OL_reffinalcaloparts_matched->Fill(pass,reffinal_met/1000.0);
        //RefFinal Calorimeter only:
        EFF_OL_reffinalcaloparts_matched->Fill(pass,sqrt((olmetxrefele+olmetxrefgamma+olmetxreftau+olmetxrefjet+olmetxcellouteflow)*(olmetxrefele+olmetxrefgamma+olmetxreftau+olmetxrefjet+olmetxcellouteflow)+(olmetyrefele+olmetyrefgamma+olmetyreftau+olmetyrefjet+olmetycellouteflow)*(olmetyrefele+olmetyrefgamma+olmetyreftau+olmetyrefjet+olmetycellouteflow))/1000.);
       //Truth:
       //EFF_OL_reffinalcaloparts_matched->Fill(pass,sqrt(truthmetx*truthmetx+truthmety*truthmety)/1000.0);
       //LocHadTopo
       //EFF_OL_reffinalcaloparts_matched->Fill(pass,lochadtopomet/1000.0);
      } // end in correct bcid
    }
    EFF_OL_reffinalcaloparts_matched->SetMarkerStyle(20);
    EFF_OL_reffinalcaloparts_matched->SetMarkerSize(1.1);
    EFF_OL_reffinalcaloparts_matched->SetMarkerColor(colorreffinal);
    EFF_OL_reffinalcaloparts_matched->SetLineColor(colorreffinal);
    EFF_OL_reffinalcaloparts_matched->Draw();

  TCanvas *COMBINEDEFFICIENCY = new TCanvas("COMBINEDEFFICIENCY","COMBINEDEFFICIENCY");
    EFF_L2_feb_matched->Draw();
    EFF_L2_febcalib_matched->Draw("sameP");
    EFF_EF_tclcw_matched->Draw("sameP");
    EFF_EF_emcluster_matched->Draw("sameP");
    EFF_L1_matched->Draw("sameP");
    EFF_EF_cell_matched->Draw("sameP");
    EFF_OL_lochadtopo_matched->Draw("sameP");
    EFF_OL_reffinalcaloparts_matched->Draw("sameP");
    //EFF_L2_feb_82->SetName("EFF_L2_feb_82");
    //EFF_L2_febcalib_75->SetName("EFF_L2_febcalib_75");
    //EFF_EF_tclcw_104->SetName("EFF_EF_tclcw_104");
    //EFF_EF_emcluster_86->SetName("EFF_EF_emcluster_86");
    TLegend* lcombeff=new TLegend(0.1,0.7,0.4,0.9);
    lcombeff->AddEntry("EFF_L2_feb_matched","FEB 82 GeV","p");
    lcombeff->AddEntry("EFF_L2_febcalib_matched","FEB Had Calib 190 GeV","p");
    lcombeff->AddEntry("EFF_EF_tclcw_matched","tclcw 196 GeV","p");
    lcombeff->AddEntry("EFF_EF_emcluster_matched","EM cluster 120 GeV","p");
    lcombeff->AddEntry("EFF_L1_matched","L1 81 GeV","p");
    lcombeff->AddEntry("EFF_EF_cell_matched","EF Cell 87 GeV","p");
    lcombeff->AddEntry("EFF_OL_lochadtopo_matched","LocHadTopo 192 GeV","p");
    lcombeff->AddEntry("EFF_OL_reffinalcaloparts_matched","RefFinalCalo 260 GeV","p");
    lcombeff->Draw();

  TCanvas *L1MET = new TCanvas("L1MET","L1MET");
    TH1F* l1met = new TH1F("l1met"," L1 MET ",  nmetbins, metmin, metmax);
    l1met->SetLineColor(colorl1);
    l1met->GetXaxis()->SetTitle("L1 MET [GeV]");
    l1met->GetYaxis()->SetTitle("Number of Events");
    tree_AS->Draw("Trig_l2met_Cell/1000.>>l1met",BG7CUT);
    gPad->Update();
    TPaveStats *statboxmetl1 = (TPaveStats*)l1met->GetListOfFunctions()->FindObject("stats");
    l1met->GetListOfFunctions()->Remove(statboxmetl1);
    l1met->SetStats(0);
    statboxmetl1->SetTextColor(colorl1);
    statboxmetl1->SetY1NDC(0.1); //new y start position
    statboxmetl1->SetY2NDC(0.2); //new y end position
    statboxmetl1->Draw();

  TCanvas *L1METL1CUT = new TCanvas("L1METL1CUT","L1METL1CUT");
    TH1F* l1metl1cut = new TH1F("l1metl1cut"," L1 MET with L1 Cut",  nmetbins, metmin, metmax);
    l1metl1cut->SetLineColor(colorl1);
    l1metl1cut->GetXaxis()->SetTitle("L1 MET [GeV]");
    l1metl1cut->GetYaxis()->SetTitle("Number of Events");
    tree_AS->Draw("Trig_l2met_Cell/1000.>>l1metl1cut",BG7CUTANDL1CUT);
    gPad->Update();
    TPaveStats *statboxmetl1l1cut = (TPaveStats*)l1metl1cut->GetListOfFunctions()->FindObject("stats");
    l1metl1cut->GetListOfFunctions()->Remove(statboxmetl1l1cut);
    l1metl1cut->SetStats(0);
    statboxmetl1l1cut->SetTextColor(colorl1);
    statboxmetl1l1cut->SetY1NDC(0.1); //new y start position
    statboxmetl1l1cut->SetY2NDC(0.2); //new y end position
    statboxmetl1l1cut->Draw();

  TCanvas *L1METTHRESH = new TCanvas("L1METTHERSH","L1METTHRESH");
    TH1F* l1metthresh = new TH1F("l1metthresh","Fraction of events above Algorithm Threshold", nmetbins, metmin, metmax);
    l1metthresh->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    l1metthresh->GetYaxis()->SetTitle("Fraction of events above threshold");
    l1metthresh->SetLineColor(colorl1);
    Double_t* zvall1, sumitl1, ratiol1;
    sumitl1=l1metl1cut->GetBinContent(nmetbins+1);
    Double_t* totnuml1 = l1metl1cut->GetEntries();
    Double_t* totnuml1wol1cut = l1met->GetEntries();
    std::cout << "L1 threshold plot \n";
    double ttbarl1thresh[nmetbins];
    for (int j=nmetbins; j>0; j--) {
      zvall1=l1metl1cut->GetBinContent(j);
      sumitl1 += zvall1;
      //std::cout << "number of events in bin   " << j << "  content   " << zvall1 << "\n";
      ratiol1 = sumitl1/totnuml1wol1cut;
      l1metthresh->SetBinContent(j,ratiol1);
      std::cout << "L1 Signal bin " << j << "MET [GeV] " <<  float(metmin)+float((j-1)*(metmax-metmin))/float(nmetbins)    << "  fraction above threshold " << ratiol1 <<"\n";
      ttbarl1thresh[j-1]=ratiol1;
    }
    //zval=l1met->GetBinContent(0);
    //std::cout << "number of underflow events  " << zval << "\n";
    //zval=l1met->GetBinContent(31);
    //std::cout << "number of overflow events  " << zval << "\n";
    //zval=l1met->GetEntries();
    //std::cout << "number of entries = " << zval << "\n";
    l1metthresh->Draw();
    gPad->Update();
    TPaveStats *statboxl1 = (TPaveStats*)l1metthresh->GetListOfFunctions()->FindObject("stats");
    l1metthresh->GetListOfFunctions()->Remove(statboxl1);
    l1metthresh->SetStats(0);
    statboxl1->SetTextColor(colorl1);
    statboxl1->SetY1NDC(0.1); //new y start position
    statboxl1->SetY2NDC(0.2); //new y end position
    statboxl1->Draw();

  TCanvas *L2METFEB = new TCanvas("L2METFEB","L2METFEB");
    TH1F* l2metfeb = new TH1F("l2metfeb"," L2 FEB MET ",  nmetbins, metmin, metmax);
    l2metfeb->SetLineColor(colorfeb);
    l2metfeb->GetXaxis()->SetTitle("L2 MET [GeV]");
    l2metfeb->GetYaxis()->SetTitle("Number of Events");
    tree_AS->Draw("Trig_efmet_FEB/1000.>>l2metfeb",BG7CUT);
    gPad->Update();
    TPaveStats *statboxmetfeb = (TPaveStats*)l2metfeb->GetListOfFunctions()->FindObject("stats");
    l2metfeb->GetListOfFunctions()->Remove(statboxmetfeb);
    l2metfeb->SetStats(0);
    statboxmetfeb->SetTextColor(colorfeb);
    statboxmetfeb->SetY1NDC(0.3); //new y start position
    statboxmetfeb->SetY2NDC(0.4); //new y end position
    statboxmetfeb->Draw();

  TCanvas *L2METFEBL1CUT = new TCanvas("L2METFEBL1CUT","L2METFEBL1CUT");
    TH1F* l2metfebl1cut = new TH1F("l2metfebl1cut"," L2 FEB MET with L1 Cut",  nmetbins, metmin, metmax);
    l2metfebl1cut->SetLineColor(colorfeb);
    l2metfebl1cut->GetXaxis()->SetTitle("L2 MET [GeV]");
    l2metfebl1cut->GetYaxis()->SetTitle("Number of Events");
    tree_AS->Draw("Trig_efmet_FEB/1000.>>l2metfebl1cut",BG7CUTANDL1CUT);
    gPad->Update();
    TPaveStats *statboxmetfebl1cut = (TPaveStats*)l2metfebl1cut->GetListOfFunctions()->FindObject("stats");
    l2metfebl1cut->GetListOfFunctions()->Remove(statboxmetfebl1cut);
    l2metfebl1cut->SetStats(0);
    statboxmetfebl1cut->SetTextColor(colorfeb);
    statboxmetfebl1cut->SetY1NDC(0.3); //new y start position
    statboxmetfebl1cut->SetY2NDC(0.4); //new y end position
    statboxmetfebl1cut->Draw();

  TCanvas *L2METFEBTHRESH = new TCanvas("L2METFEBTHERSH","L2METFEBTHRESH");
    TH1F* l2metfebthresh = new TH1F("l2metfebthresh","Fraction of events above Algorithm Threshold", nmetbins, metmin, metmax);
    l2metfebthresh->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    l2metfebthresh->GetYaxis()->SetTitle("Fraction of events above threshold");
    l2metfebthresh->SetLineColor(colorfeb);
    Double_t* zvall2feb, sumitl2feb, ratiol2feb;
    sumitl2feb=l2metfebl1cut->GetBinContent(nmetbins+1);
    Double_t* totnuml2feb = l2metfebl1cut->GetEntries();
    Double_t* totnuml2febwol1cut = l2metfeb->GetEntries();
    std::cout << "L2 FEB threshold plot \n";
    double ttbarfebthresh[nmetbins];
    for (int j=nmetbins; j>0; j--) {
      zvall2feb=l2metfebl1cut->GetBinContent(j);
      sumitl2feb += zvall2feb;
      //std::cout << "number of events in bin   " << j << "  content   " << zval << "\n";
      ratiol2feb = sumitl2feb/totnuml2febwol1cut;
      l2metfebthresh->SetBinContent(j,ratiol2feb);
      std::cout << "L2 FEB Signal bin " << j << "MET [GeV] " <<  float(metmin)+float((j-1)*(metmax-metmin))/float(nmetbins)    << "  fraction above threshold " << ratiol2feb <<"\n";
      ttbarfebthresh[j-1]=ratiol2feb;
    }
    //zval=l1met->GetBinContent(0);
    //std::cout << "number of underflow events  " << zval << "\n";
    //zval=l1met->GetBinContent(31);
    //std::cout << "number of overflow events  " << zval << "\n";
    //zval=l1met->GetEntries();
    //std::cout << "number of entries = " << zval << "\n";
    l2metfebthresh->Draw();
    gPad->Update();
    TPaveStats *statboxfeb = (TPaveStats*)l2metfebthresh->GetListOfFunctions()->FindObject("stats");
    l2metfebthresh->GetListOfFunctions()->Remove(statboxfeb);
    l2metfebthresh->SetStats(0);
    statboxfeb->SetTextColor(colorfeb);
    statboxfeb->SetY1NDC(0.3); //new y start position
    statboxfeb->SetY2NDC(0.4); //new y end position
    statboxfeb->Draw();

  TCanvas *L2METFEBCALIB = new TCanvas("L2METFEBCALIB","L2METFEBCALIB");
    TH1F* l2metfebcalib = new TH1F("l2metfebcalib"," L2 FEB Hadron Calibrated MET ",  nmetbins, metmin, metmax);
    l2metfebcalib->SetLineColor(colorfebcalib);
    l2metfebcalib->GetXaxis()->SetTitle("L2 MET [GeV]");
    l2metfebcalib->GetYaxis()->SetTitle("Number of Events");
    //Andrew's JetTauETmiss constants:
    //tree_AS->Draw("sqrt((1.80*Trig_efmetx_FEB_presamplB+1.38*Trig_efmetx_FEB_emb1+1.18*Trig_efmetx_FEB_emb2+1.58*Trig_efmetx_FEB_emb3+1.88*Trig_efmetx_FEB_presamplE+1.57*Trig_efmetx_FEB_eme1+1.68*Trig_efmetx_FEB_eme2+2.67*Trig_efmetx_FEB_eme3+1.51*Trig_efmetx_FEB_hec+1.43*Trig_efmetx_FEB_TileBar+1.53*Trig_efmetx_FEB_TileExt+1.86*Trig_efmetx_FEB_FCalEM+2.26*Trig_efmetx_FEB_FCalHad1+3.06*Trig_efmetx_FEB_FCalHad2)*(1.80*Trig_efmetx_FEB_presamplB+1.38*Trig_efmetx_FEB_emb1+1.18*Trig_efmetx_FEB_emb2+1.58*Trig_efmetx_FEB_emb3+1.88*Trig_efmetx_FEB_presamplE+1.57*Trig_efmetx_FEB_eme1+1.68*Trig_efmetx_FEB_eme2+2.67*Trig_efmetx_FEB_eme3+1.51*Trig_efmetx_FEB_hec+1.43*Trig_efmetx_FEB_TileBar+1.53*Trig_efmetx_FEB_TileExt+1.86*Trig_efmetx_FEB_FCalEM+2.26*Trig_efmetx_FEB_FCalHad1+3.06*Trig_efmetx_FEB_FCalHad2)+(1.80*Trig_efmety_FEB_presamplB+1.38*Trig_efmety_FEB_emb1+1.18*Trig_efmety_FEB_emb2+1.58*Trig_efmety_FEB_emb3+1.88*Trig_efmety_FEB_presamplE+1.57*Trig_efmety_FEB_eme1+1.68*Trig_efmety_FEB_eme2+2.67*Trig_efmety_FEB_eme3+1.51*Trig_efmety_FEB_hec+1.43*Trig_efmety_FEB_TileBar+1.53*Trig_efmety_FEB_TileExt+1.86*Trig_efmety_FEB_FCalEM+2.26*Trig_efmety_FEB_FCalHad1+3.06*Trig_efmety_FEB_FCalHad2)*(1.80*Trig_efmety_FEB_presamplB+1.38*Trig_efmety_FEB_emb1+1.18*Trig_efmety_FEB_emb2+1.58*Trig_efmety_FEB_emb3+1.88*Trig_efmety_FEB_presamplE+1.57*Trig_efmety_FEB_eme1+1.68*Trig_efmety_FEB_eme2+2.67*Trig_efmety_FEB_eme3+1.51*Trig_efmety_FEB_hec+1.43*Trig_efmety_FEB_TileBar+1.53*Trig_efmety_FEB_TileExt+1.86*Trig_efmety_FEB_FCalEM+2.26*Trig_efmety_FEB_FCalHad1+3.06*Trig_efmety_FEB_FCalHad2))/1000.>>l2metfebcalib",BG7CUT);
    //Andrew's minbias constants:
    tree_AS->Draw("sqrt((2.36*Trig_efmetx_FEB_presamplB+2.74*Trig_efmetx_FEB_emb1+2.64*Trig_efmetx_FEB_emb2+3.24*Trig_efmetx_FEB_emb3+3.40*Trig_efmetx_FEB_presamplE+2.18*Trig_efmetx_FEB_eme1+2.78*Trig_efmetx_FEB_eme2+4.08*Trig_efmetx_FEB_eme3+1.73*Trig_efmetx_FEB_hec+1.96*Trig_efmetx_FEB_TileBar+0.36*Trig_efmetx_FEB_TileExt+2.08*Trig_efmetx_FEB_FCalEM+2.48*Trig_efmetx_FEB_FCalHad1+2.88*Trig_efmetx_FEB_FCalHad2)*(2.36*Trig_efmetx_FEB_presamplB+2.74*Trig_efmetx_FEB_emb1+2.64*Trig_efmetx_FEB_emb2+3.24*Trig_efmetx_FEB_emb3+3.40*Trig_efmetx_FEB_presamplE+2.18*Trig_efmetx_FEB_eme1+2.78*Trig_efmetx_FEB_eme2+4.08*Trig_efmetx_FEB_eme3+1.73*Trig_efmetx_FEB_hec+1.96*Trig_efmetx_FEB_TileBar+0.36*Trig_efmetx_FEB_TileExt+2.08*Trig_efmetx_FEB_FCalEM+2.48*Trig_efmetx_FEB_FCalHad1+2.88*Trig_efmetx_FEB_FCalHad2)+(2.36*Trig_efmety_FEB_presamplB+2.74*Trig_efmety_FEB_emb1+2.64*Trig_efmety_FEB_emb2+3.24*Trig_efmety_FEB_emb3+3.40*Trig_efmety_FEB_presamplE+2.18*Trig_efmety_FEB_eme1+2.78*Trig_efmety_FEB_eme2+4.08*Trig_efmety_FEB_eme3+1.73*Trig_efmety_FEB_hec+1.96*Trig_efmety_FEB_TileBar+0.36*Trig_efmety_FEB_TileExt+2.08*Trig_efmety_FEB_FCalEM+2.48*Trig_efmety_FEB_FCalHad1+2.88*Trig_efmety_FEB_FCalHad2)*(2.36*Trig_efmety_FEB_presamplB+2.74*Trig_efmety_FEB_emb1+2.64*Trig_efmety_FEB_emb2+3.24*Trig_efmety_FEB_emb3+3.40*Trig_efmety_FEB_presamplE+2.18*Trig_efmety_FEB_eme1+2.78*Trig_efmety_FEB_eme2+4.08*Trig_efmety_FEB_eme3+1.73*Trig_efmety_FEB_hec+1.96*Trig_efmety_FEB_TileBar+0.36*Trig_efmety_FEB_TileExt+2.08*Trig_efmety_FEB_FCalEM+2.48*Trig_efmety_FEB_FCalHad1+2.88*Trig_efmety_FEB_FCalHad2))/1000.>>l2metfebcalib",BG7CUT);

    gPad->Update();
    TPaveStats *statboxmetfebcalib = (TPaveStats*)l2metfebcalib->GetListOfFunctions()->FindObject("stats");
    l2metfebcalib->GetListOfFunctions()->Remove(statboxmetfebcalib);
    l2metfebcalib->SetStats(0);
    statboxmetfebcalib->SetTextColor(colorfebcalib);
    statboxmetfebcalib->SetY1NDC(0.2); //new y start position
    statboxmetfebcalib->SetY2NDC(0.3); //new y end position
    statboxmetfebcalib->Draw();

  TCanvas *L2METFEBCALIBL1CUT = new TCanvas("L2METFEBCALIBL1CUT","L2METFEBCALIBL1CUT");
    TH1F* l2metfebcalibl1cut = new TH1F("l2metfebcalibl1cut"," L2 FEB Hadron Calibrated MET with L1 Cut",  nmetbins, metmin, metmax);
    l2metfebcalibl1cut->SetLineColor(colorfebcalib);
    l2metfebcalibl1cut->GetXaxis()->SetTitle("L2 MET [GeV]");
    l2metfebcalibl1cut->GetYaxis()->SetTitle("Number of Events");
    //Andrew's JetTauETmiss constants:
    //tree_AS->Draw("sqrt((1.80*Trig_efmetx_FEB_presamplB+1.38*Trig_efmetx_FEB_emb1+1.18*Trig_efmetx_FEB_emb2+1.58*Trig_efmetx_FEB_emb3+1.88*Trig_efmetx_FEB_presamplE+1.57*Trig_efmetx_FEB_eme1+1.68*Trig_efmetx_FEB_eme2+2.67*Trig_efmetx_FEB_eme3+1.51*Trig_efmetx_FEB_hec+1.43*Trig_efmetx_FEB_TileBar+1.53*Trig_efmetx_FEB_TileExt+1.86*Trig_efmetx_FEB_FCalEM+2.26*Trig_efmetx_FEB_FCalHad1+3.06*Trig_efmetx_FEB_FCalHad2)*(1.80*Trig_efmetx_FEB_presamplB+1.38*Trig_efmetx_FEB_emb1+1.18*Trig_efmetx_FEB_emb2+1.58*Trig_efmetx_FEB_emb3+1.88*Trig_efmetx_FEB_presamplE+1.57*Trig_efmetx_FEB_eme1+1.68*Trig_efmetx_FEB_eme2+2.67*Trig_efmetx_FEB_eme3+1.51*Trig_efmetx_FEB_hec+1.43*Trig_efmetx_FEB_TileBar+1.53*Trig_efmetx_FEB_TileExt+1.86*Trig_efmetx_FEB_FCalEM+2.26*Trig_efmetx_FEB_FCalHad1+3.06*Trig_efmetx_FEB_FCalHad2)+(1.80*Trig_efmety_FEB_presamplB+1.38*Trig_efmety_FEB_emb1+1.18*Trig_efmety_FEB_emb2+1.58*Trig_efmety_FEB_emb3+1.88*Trig_efmety_FEB_presamplE+1.57*Trig_efmety_FEB_eme1+1.68*Trig_efmety_FEB_eme2+2.67*Trig_efmety_FEB_eme3+1.51*Trig_efmety_FEB_hec+1.43*Trig_efmety_FEB_TileBar+1.53*Trig_efmety_FEB_TileExt+1.86*Trig_efmety_FEB_FCalEM+2.26*Trig_efmety_FEB_FCalHad1+3.06*Trig_efmety_FEB_FCalHad2)*(1.80*Trig_efmety_FEB_presamplB+1.38*Trig_efmety_FEB_emb1+1.18*Trig_efmety_FEB_emb2+1.58*Trig_efmety_FEB_emb3+1.88*Trig_efmety_FEB_presamplE+1.57*Trig_efmety_FEB_eme1+1.68*Trig_efmety_FEB_eme2+2.67*Trig_efmety_FEB_eme3+1.51*Trig_efmety_FEB_hec+1.43*Trig_efmety_FEB_TileBar+1.53*Trig_efmety_FEB_TileExt+1.86*Trig_efmety_FEB_FCalEM+2.26*Trig_efmety_FEB_FCalHad1+3.06*Trig_efmety_FEB_FCalHad2))/1000.>>l2metfebcalibl1cut",BG7CUTANDL1CUT);
    //Andrew's minbias constants:
    tree_AS->Draw("sqrt((2.36*Trig_efmetx_FEB_presamplB+2.74*Trig_efmetx_FEB_emb1+2.64*Trig_efmetx_FEB_emb2+3.24*Trig_efmetx_FEB_emb3+3.40*Trig_efmetx_FEB_presamplE+2.18*Trig_efmetx_FEB_eme1+2.78*Trig_efmetx_FEB_eme2+4.08*Trig_efmetx_FEB_eme3+1.73*Trig_efmetx_FEB_hec+1.96*Trig_efmetx_FEB_TileBar+0.36*Trig_efmetx_FEB_TileExt+2.08*Trig_efmetx_FEB_FCalEM+2.48*Trig_efmetx_FEB_FCalHad1+2.88*Trig_efmetx_FEB_FCalHad2)*(2.36*Trig_efmetx_FEB_presamplB+2.74*Trig_efmetx_FEB_emb1+2.64*Trig_efmetx_FEB_emb2+3.24*Trig_efmetx_FEB_emb3+3.40*Trig_efmetx_FEB_presamplE+2.18*Trig_efmetx_FEB_eme1+2.78*Trig_efmetx_FEB_eme2+4.08*Trig_efmetx_FEB_eme3+1.73*Trig_efmetx_FEB_hec+1.96*Trig_efmetx_FEB_TileBar+0.36*Trig_efmetx_FEB_TileExt+2.08*Trig_efmetx_FEB_FCalEM+2.48*Trig_efmetx_FEB_FCalHad1+2.88*Trig_efmetx_FEB_FCalHad2)+(2.36*Trig_efmety_FEB_presamplB+2.74*Trig_efmety_FEB_emb1+2.64*Trig_efmety_FEB_emb2+3.24*Trig_efmety_FEB_emb3+3.40*Trig_efmety_FEB_presamplE+2.18*Trig_efmety_FEB_eme1+2.78*Trig_efmety_FEB_eme2+4.08*Trig_efmety_FEB_eme3+1.73*Trig_efmety_FEB_hec+1.96*Trig_efmety_FEB_TileBar+0.36*Trig_efmety_FEB_TileExt+2.08*Trig_efmety_FEB_FCalEM+2.48*Trig_efmety_FEB_FCalHad1+2.88*Trig_efmety_FEB_FCalHad2)*(2.36*Trig_efmety_FEB_presamplB+2.74*Trig_efmety_FEB_emb1+2.64*Trig_efmety_FEB_emb2+3.24*Trig_efmety_FEB_emb3+3.40*Trig_efmety_FEB_presamplE+2.18*Trig_efmety_FEB_eme1+2.78*Trig_efmety_FEB_eme2+4.08*Trig_efmety_FEB_eme3+1.73*Trig_efmety_FEB_hec+1.96*Trig_efmety_FEB_TileBar+0.36*Trig_efmety_FEB_TileExt+2.08*Trig_efmety_FEB_FCalEM+2.48*Trig_efmety_FEB_FCalHad1+2.88*Trig_efmety_FEB_FCalHad2))/1000.>>l2metfebcalibl1cut",BG7CUTANDL1CUT);

    gPad->Update();
    TPaveStats *statboxmetfebcalibl1cut = (TPaveStats*)l2metfebcalibl1cut->GetListOfFunctions()->FindObject("stats");
    l2metfebcalibl1cut->GetListOfFunctions()->Remove(statboxmetfebcalibl1cut);
    l2metfebcalibl1cut->SetStats(0);
    statboxmetfebcalibl1cut->SetTextColor(colorfebcalib);
    statboxmetfebcalibl1cut->SetY1NDC(0.2); //new y start position
    statboxmetfebcalibl1cut->SetY2NDC(0.3); //new y end position
    statboxmetfebcalibl1cut->Draw();

  TCanvas *L2METFEBCALIBTHRESH = new TCanvas("L2METFEBCALIBTHERSH","L2METFEBCALIBTHRESH");
    TH1F* l2metfebcalibthresh = new TH1F("l2metfebcalibthresh","Fraction of events above Algorithm Threshold", nmetbins, metmin, metmax);
    l2metfebcalibthresh->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    l2metfebcalibthresh->GetYaxis()->SetTitle("Fraction of events above threshold");
    l2metfebcalibthresh->SetLineColor(colorfebcalib);
    Double_t* zvall2febcalib, sumitl2febcalib, ratiol2febcalib;
    sumitl2febcalib=l2metfebcalibl1cut->GetBinContent(nmetbins+1);
    Double_t* totnuml2febcalib = l2metfebcalibl1cut->GetEntries();
    Double_t* totnuml2febcalibwol1cut = l2metfebcalib->GetEntries();
    std::cout << "L2 FEB had calibrated threshold plot \n";
    double ttbarfebcalibthresh[nmetbins];
    for (int j=nmetbins; j>0; j--) {
      zvall2febcalib=l2metfebcalibl1cut->GetBinContent(j);
      sumitl2febcalib += zvall2febcalib;
      //std::cout << "number of events in bin   " << j << "  content   " << zval << "\n";
      ratiol2febcalib = sumitl2febcalib/totnuml2febcalibwol1cut;
      l2metfebcalibthresh->SetBinContent(j,ratiol2febcalib);
      std::cout << "L2 FEB Had Calib Signal bin " << j << "MET [GeV] " <<  float(metmin)+float((j-1)*(metmax-metmin))/float(nmetbins)    << "  fraction above threshold " << ratiol2febcalib <<"\n";
      ttbarfebcalibthresh[j-1]=ratiol2febcalib;
    }
    //zval=l1met->GetBinContent(0);
    //std::cout << "number of underflow events  " << zval << "\n";
    //zval=l1met->GetBinContent(31);
    //std::cout << "number of overflow events  " << zval << "\n";
    //zval=l1met->GetEntries();
    //std::cout << "number of entries = " << zval << "\n";
    l2metfebcalibthresh->Draw();
    gPad->Update();
    TPaveStats *statboxfebcalib = (TPaveStats*)l2metfebcalibthresh->GetListOfFunctions()->FindObject("stats");
    l2metfebcalibthresh->GetListOfFunctions()->Remove(statboxfebcalib);
    l2metfebcalibthresh->SetStats(0);
    statboxfebcalib->SetTextColor(colorfebcalib);
    statboxfebcalib->SetY1NDC(0.2); //new y start position
    statboxfebcalib->SetY2NDC(0.3); //new y end position
    statboxfebcalib->Draw();

  TCanvas *EFMETTCLCW = new TCanvas("EFMETTCLCW","EFMETTCLCW");
    TH1F* efmettclcw = new TH1F("efmettclcw"," EF TCLCW MET ",  nmetbins, metmin, metmax);
    efmettclcw->SetLineColor(colortclcw);
    efmettclcw->GetXaxis()->SetTitle("EF MET [GeV]");
    efmettclcw->GetYaxis()->SetTitle("Number of Events");
    tree_AS->Draw("Trig_efmet_tclcw/1000.>>efmettclcw",BG7CUT);
    gPad->Update();
    TPaveStats *statboxmettclcw = (TPaveStats*)efmettclcw->GetListOfFunctions()->FindObject("stats");
    efmettclcw->GetListOfFunctions()->Remove(statboxmettclcw);
    efmettclcw->SetStats(0);
    statboxmettclcw->SetTextColor(colortclcw);
    statboxmettclcw->SetY1NDC(0.4); //new y start position
    statboxmettclcw->SetY2NDC(0.5); //new y end position
    statboxmettclcw->Draw();

  TCanvas *EFMETTCLCWL1CUT = new TCanvas("EFMETTCLCWL1CUT","EFMETTCLCWL1CUT");
    TH1F* efmettclcwl1cut = new TH1F("efmettclcwl1cut"," EF TCLCW MET with L1 Cut",  nmetbins, metmin, metmax);
    efmettclcwl1cut->SetLineColor(colortclcw);
    efmettclcwl1cut->GetXaxis()->SetTitle("EF MET [GeV]");
    efmettclcwl1cut->GetYaxis()->SetTitle("Number of Events");
    tree_AS->Draw("Trig_efmet_tclcw/1000.>>efmettclcwl1cut",BG7CUTANDL1CUT);
    gPad->Update();
    TPaveStats *statboxmettclcwl1cut = (TPaveStats*)efmettclcwl1cut->GetListOfFunctions()->FindObject("stats");
    efmettclcwl1cut->GetListOfFunctions()->Remove(statboxmettclcwl1cut);
    efmettclcwl1cut->SetStats(0);
    statboxmettclcwl1cut->SetTextColor(colortclcw);
    statboxmettclcwl1cut->SetY1NDC(0.4); //new y start position
    statboxmettclcwl1cut->SetY2NDC(0.5); //new y end position
    statboxmettclcwl1cut->Draw();

  TCanvas *EFMETTCLCWTHRESH = new TCanvas("EFMETTCLCWTHERSH","EFMETTCLCWTHRESH");
    TH1F* efmettclcwthresh = new TH1F("efmettclcwthresh","Fraction of events above Algorithm Threshold", nmetbins, metmin, metmax);
    efmettclcwthresh->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    efmettclcwthresh->GetYaxis()->SetTitle("Fraction of events above threshold");
    efmettclcwthresh->SetLineColor(colortclcw);
    Double_t* zvaleftclcw, sumiteftclcw, ratioeftclcw;
    sumiteftclcw=efmettclcwl1cut->GetBinContent(nmetbins+1);
    Double_t* totnumeftclcw = efmettclcwl1cut->GetEntries();
    Double_t* totnumeftclcwwol1cut = efmettclcw->GetEntries();
    std::cout << "EF tclcw threshold plot \n";
    double ttbartclcwthresh[nmetbins];
    for (int j=nmetbins; j>0; j--) {
      zvaleftclcw=efmettclcwl1cut->GetBinContent(j);
      sumiteftclcw += zvaleftclcw;
      //std::cout << "number of events in bin   " << j << "  content   " << zval << "\n";
      ratioeftclcw = sumiteftclcw/totnumeftclcwwol1cut;
      efmettclcwthresh->SetBinContent(j,ratioeftclcw);
      std::cout << "EF tclcw Signal bin " << j << "MET [GeV] " <<  float(metmin)+float((j-1)*(metmax-metmin))/float(nmetbins)    << "  fraction above threshold " << ratioeftclcw <<"\n";
      ttbartclcwthresh[j-1]=ratioeftclcw;
    }
    //zval=l1met->GetBinContent(0);
    //std::cout << "number of underflow events  " << zval << "\n";
    //zval=l1met->GetBinContent(31);
    //std::cout << "number of overflow events  " << zval << "\n";
    //zval=l1met->GetEntries(); 
    //std::cout << "number of entries = " << zval << "\n";
    efmettclcwthresh->Draw();
    gPad->Update();
    TPaveStats *statbox = (TPaveStats*)efmettclcwthresh->GetListOfFunctions()->FindObject("stats");
    efmettclcwthresh->GetListOfFunctions()->Remove(statbox);
    efmettclcwthresh->SetStats(0);
    statbox->SetTextColor(colortclcw);
    statbox->SetY1NDC(0.4); //new y start position
    statbox->SetY2NDC(0.5); //new y end position
    statbox->Draw();

  TCanvas *EFMETEMCLUSTER = new TCanvas("EFMETEMCLUSTER","EFMETEMCLUSTER");
    TH1F* efmetemcluster = new TH1F("efmetemcluster"," EF MET ",  nmetbins, metmin, metmax);
    efmetemcluster->SetLineColor(coloremcluster);
    efmetemcluster->GetXaxis()->SetTitle("EF MET [GeV]");
    efmetemcluster->GetYaxis()->SetTitle("Number of Events");
    tree_AS->Draw("Trig_efmet_emcluster/1000.>>efmetemcluster",BG7CUT);
    gPad->Update();
    TPaveStats *statboxmetemcluster = (TPaveStats*)efmetemcluster->GetListOfFunctions()->FindObject("stats");
    efmetemcluster->GetListOfFunctions()->Remove(statboxmetemcluster);
    efmetemcluster->SetStats(0);
    statboxmetemcluster->SetTextColor(coloremcluster);
    statboxmetemcluster->SetY1NDC(0.5); //new y start position
    statboxmetemcluster->SetY2NDC(0.6); //new y end position
    statboxmetemcluster->Draw();

  TCanvas *EFMETEMCLUSTERL1CUT = new TCanvas("EFMETEMCLUSTERL1CUT","EFMETEMCLUSTERL1CUT");
    TH1F* efmetemclusterl1cut = new TH1F("efmetemclusterl1cut"," EF MET with L1 Cut",  nmetbins, metmin, metmax);
    efmetemclusterl1cut->SetLineColor(coloremcluster);
    efmetemclusterl1cut->GetXaxis()->SetTitle("EF MET [GeV]");
    efmetemclusterl1cut->GetYaxis()->SetTitle("Number of Events");
    tree_AS->Draw("Trig_efmet_emcluster/1000.>>efmetemclusterl1cut",BG7CUTANDL1CUT);
    gPad->Update();
    TPaveStats *statboxmetemclusterl1cut = (TPaveStats*)efmetemclusterl1cut->GetListOfFunctions()->FindObject("stats");
    efmetemclusterl1cut->GetListOfFunctions()->Remove(statboxmetemclusterl1cut);
    efmetemclusterl1cut->SetStats(0);
    statboxmetemclusterl1cut->SetTextColor(coloremcluster);
    statboxmetemclusterl1cut->SetY1NDC(0.5); //new y start position
    statboxmetemclusterl1cut->SetY2NDC(0.6); //new y end position
    statboxmetemclusterl1cut->Draw();

  TCanvas *EFMETEMCLUSTERTHRESH = new TCanvas("EFMETEMCLUSTERTHERSH","EFMETEMCLUSTERTHRESH");
    TH1F* efmetemclusterthresh = new TH1F("efmetemclusterthresh","Fraction of events above Algorithm Threshold", nmetbins, metmin, metmax);
    efmetemclusterthresh->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    efmetemclusterthresh->GetYaxis()->SetTitle("Fraction of events above threshold");
    efmetemclusterthresh->SetLineColor(coloremcluster);
    Double_t* zvalefemcluster, sumitefemcluster, ratioefemcluster;
    sumitefemcluster=efmetemclusterl1cut->GetBinContent(nmetbins+1);
    Double_t* totnumefemcluster = efmetemclusterl1cut->GetEntries();
    Double_t* totnumefemclusterwol1cut = efmetemcluster->GetEntries();
    std::cout << "EF em cluster threshold plot \n";
    double ttbaremclusterthresh[nmetbins];
    for (int j=nmetbins; j>0; j--) {
      zvalefemcluster=efmetemclusterl1cut->GetBinContent(j);
      sumitefemcluster += zvalefemcluster;
      //std::cout << "number of events in bin   " << j << "  content   " << zval << "\n";
      ratioefemcluster = sumitefemcluster/totnumefemclusterwol1cut;
      efmetemclusterthresh->SetBinContent(j,ratioefemcluster);
      std::cout << "EF EM cluster Signal bin " << j << "MET [GeV] " <<  float(metmin)+float((j-1)*(metmax-metmin))/float(nmetbins)    << "  fraction above threshold " << ratioefemcluster <<"\n";

      ttbaremclusterthresh[j-1]=ratioefemcluster;
    }
    //zval=l1met->GetBinContent(0);
    //std::cout << "number of underflow events  " << zval << "\n";
    //zval=l1met->GetBinContent(31);
    //std::cout << "number of overflow events  " << zval << "\n";
    //zval=l1met->GetEntries();
    //std::cout << "number of entries = " << zval << "\n";
    efmetemclusterthresh->Draw();
    gPad->Update();
    TPaveStats *statboxemclusterthresh = (TPaveStats*)efmetemclusterthresh->GetListOfFunctions()->FindObject("stats");
    efmetemclusterthresh->GetListOfFunctions()->Remove(statboxemclusterthresh);
    efmetemclusterthresh->SetStats(0);
    statboxemclusterthresh->SetTextColor(coloremcluster);
    statboxemclusterthresh->SetY1NDC(0.5); //new y start position
    statboxemclusterthresh->SetY2NDC(0.6); //new y end position
    statboxemclusterthresh->Draw();

  TCanvas *EFMETCELL = new TCanvas("EFMETCELL","EFMETCELL");
    TH1F* efmetcell = new TH1F("efmetcell"," EF CELL MET ",  nmetbins, metmin, metmax);
    efmetcell->SetLineColor(colorefcell);
    efmetcell->GetXaxis()->SetTitle("EF MET [GeV]");
    efmetcell->GetYaxis()->SetTitle("Number of Events");
    tree_AS->Draw("Trig_efmet_Cell/1000.>>efmetcell",BG7CUT);
    gPad->Update();
    TPaveStats *statboxmetefcell = (TPaveStats*)efmetcell->GetListOfFunctions()->FindObject("stats");
    efmetcell->GetListOfFunctions()->Remove(statboxmetefcell);
    efmetcell->SetStats(0);
    statboxmetefcell->SetTextColor(colorefcell);
    statboxmetefcell->SetY1NDC(0.6); //new y start position
    statboxmetefcell->SetY2NDC(0.7); //new y end position
    statboxmetefcell->Draw();

  TCanvas *EFMETCELLL1CUT = new TCanvas("EFMETCELLL1CUT","EFMETCELLL1CUT");
    TH1F* efmetcelll1cut = new TH1F("efmetcelll1cut"," EF CELL MET with L1 Cut",  nmetbins, metmin, metmax);
    efmetcelll1cut->SetLineColor(colorefcell);
    efmetcelll1cut->GetXaxis()->SetTitle("EF MET [GeV]");
    efmetcelll1cut->GetYaxis()->SetTitle("Number of Events");
    tree_AS->Draw("Trig_efmet_Cell/1000.>>efmetcelll1cut",BG7CUTANDL1CUT);
    gPad->Update();
    TPaveStats *statboxmetefcelll1cut = (TPaveStats*)efmetcelll1cut->GetListOfFunctions()->FindObject("stats");
    efmetcelll1cut->GetListOfFunctions()->Remove(statboxmetefcelll1cut);
    efmetcelll1cut->SetStats(0);
    statboxmetefcelll1cut->SetTextColor(colorefcell);
    statboxmetefcelll1cut->SetY1NDC(0.6); //new y start position
    statboxmetefcelll1cut->SetY2NDC(0.7); //new y end position
    statboxmetefcelll1cut->Draw();

  TCanvas *EFMETCELLTHRESH = new TCanvas("EFMETCELLTHERSH","EFMETCELLTHRESH");
    TH1F* efmetcellthresh = new TH1F("efmetcellthresh","Fraction of events above Algorithm Threshold", nmetbins, metmin, metmax);
    efmetcellthresh->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    efmetcellthresh->GetYaxis()->SetTitle("Fraction of events above threshold");
    efmetcellthresh->SetLineColor(colorefcell);
    Double_t* zvalefcell, sumitefcell, ratioefcell;
    sumitefcell=efmetcelll1cut->GetBinContent(nmetbins+1);
    Double_t* totnumefcell = efmetcelll1cut->GetEntries();
    Double_t* totnumefcellwol1cut = efmetcell->GetEntries();
    std::cout << "EF cell threshold plot \n";
    double ttbarefcellthresh[nmetbins];
    for (int j=nmetbins; j>0; j--) {
      zvalefcell=efmetcelll1cut->GetBinContent(j);
      sumitefcell += zvalefcell;
      //std::cout << "number of events in bin   " << j << "  content   " << zval << "\n";
      ratioefcell = sumitefcell/totnumefcellwol1cut;
      efmetcellthresh->SetBinContent(j,ratioefcell);
      std::cout << "EF cell Signal bin " << j << "MET [GeV] " <<  float(metmin)+float((j-1)*(metmax-metmin))/float(nmetbins)    << "  fraction above threshold " << ratioefcell <<"\n";
      ttbarefcellthresh[j-1]=ratioefcell;
    }
    //zval=l1met->GetBinContent(0);
    //std::cout << "number of underflow events  " << zval << "\n";
    //zval=l1met->GetBinContent(31);
    //std::cout << "number of overflow events  " << zval << "\n";
    //zval=l1met->GetEntries();
    //std::cout << "number of entries = " << zval << "\n";
    efmetcellthresh->Draw();
    gPad->Update();
    TPaveStats *statboxefcellthresh = (TPaveStats*)efmetcellthresh->GetListOfFunctions()->FindObject("stats");
    efmetcellthresh->GetListOfFunctions()->Remove(statboxefcellthresh);
    efmetcellthresh->SetStats(0);
    statboxefcellthresh->SetTextColor(colorefcell);
    statboxefcellthresh->SetY1NDC(0.6); //new y start position
    statboxefcellthresh->SetY2NDC(0.7); //new y end position
    statboxefcellthresh->Draw();

  TCanvas *COMPTHRESHMANY  = new TCanvas("COMPTHRESHMANY","COMPTHRESHMANY");
    efmettclcwthresh->Draw();
    statboxemclusterthresh->Draw();
    //gPad->Update();
    //TPaveStats *statbox = (TPaveStats*)efmettclcwthresh->GetListOfFunctions()->FindObject("stats");
    //efmettclcwthresh->GetListOfFunctions()->Remove(statbox);
    //efmettclcwthresh->SetStats(0);
    //statbox->SetTextColor(2);
    //statbox->SetY1NDC(0.4); //new y start position
    //statbox->SetY2NDC(0.5); //new y end position
    statbox->Draw();
    efmetemclusterthresh->Draw("same");
    l2metfebthresh->Draw("same");
    statboxfeb->Draw();
    l2metfebcalibthresh->Draw("same");
    statboxfebcalib->Draw();
    l1metthresh->Draw("same");
    statboxl1->Draw();
    efmetcellthresh->Draw("same");
    statboxefcellthresh->Draw();

  //TFile *secondtest = TFile::Open("AnalysisSkeleton.minbias14tev54mu25ns.e1564_s1499_s1504_r4326_r4371.aan.root"); //1 July 2013 minbias files

  //Below is 2 jet Z3 54 Collisons, 25 ns with FEB info included
  //TFile *secondtest = TFile::Open("AnalysisSkeleton.14tev2Z3jet.7Aug2013.25nsmu54.e1712_s1499_s1504_r4326_r4371.aan.root");
  //Below is minbias 54 Collisons, 25 ns with FEB info included
  //TFile *secondtest = TFile::Open("AnalysisSkeleton.14tevminbias.7Aug2013.25nsmu54.e1564_s1499_s1504_r4326_r4371.aan.root");
  //Below is 2 jet Z1 54 Collisons, 25 ns with FEB info included
  //TFile *secondtest = TFile::Open("AnalysisSkeleton.14tevjetjet_JZ1.15Aug2013.25nsmu54.e1712_s1499_s1504_r4326_r4371.root");
  //Below is 3/26/2014 Minbias 10M events, mu=60, 25 ns, no L1 noise cuts
  //TFile *secondtest = TFile::Open("AnalysisSkeleton.14tevMinbais25ns60mu10M.e1133_s1717_s1691_r5286_r4643.aan.root");
  //Below is the 8/12/14 10M minbias file with L1 and HLT zero suppression
  TFile *secondtest = TFile::Open("AnalysisSkeleton.14TevMinbias12August2014.e1133_s1717_s1691_r5635_r4643.aan.root"); 

  TCanvas *MBL1MET = new TCanvas("MBL1MET","MBL1MET");
    TH1F* mbl1met = new TH1F("mbl1met"," minbias L1 MET ",  nmetbins, metmin, metmax);
    mbl1met->SetLineColor(colorl1);
    mbl1met->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    mbl1met->GetYaxis()->SetTitle("Number of Events");
    tree_AS->Draw("Trig_l2met_Cell/1000.>>mbl1met",BG7CUT);
    gPad->Update();
    TPaveStats *mbstatboxmetl1 = (TPaveStats*)mbl1met->GetListOfFunctions()->FindObject("stats");
    mbl1met->GetListOfFunctions()->Remove(mbstatboxmetl1);
    mbl1met->SetStats(0);
    mbstatboxmetl1->SetTextColor(colorl1);
    mbstatboxmetl1->SetY1NDC(0.1); //new y start position
    mbstatboxmetl1->SetY2NDC(0.2); //new y end position
    mbstatboxmetl1->Draw();

  TCanvas *MBL1METL1CUT = new TCanvas("MBL1METL1CUT","MBL1METL1CUT");
    TH1F* mbl1metl1cut = new TH1F("mbl1metl1cut"," minbias L1 MET with L1 Cut",  nmetbins, metmin, metmax);
    mbl1metl1cut->SetLineColor(colorl1);
    mbl1metl1cut->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    mbl1metl1cut->GetYaxis()->SetTitle("Number of Events");
    tree_AS->Draw("Trig_l2met_Cell/1000.>>mbl1metl1cut",BG7CUTANDL1CUT);
    gPad->Update();
    TPaveStats *mbstatboxmetl1l1cut = (TPaveStats*)mbl1metl1cut->GetListOfFunctions()->FindObject("stats");
    mbl1metl1cut->GetListOfFunctions()->Remove(mbstatboxmetl1l1cut);
    mbl1metl1cut->SetStats(0);
    mbstatboxmetl1l1cut->SetTextColor(colorl1);
    mbstatboxmetl1l1cut->SetY1NDC(0.1); //new y start position
    mbstatboxmetl1l1cut->SetY2NDC(0.2); //new y end position
    mbstatboxmetl1l1cut->Draw();

  TCanvas *MBL1METTHRESH = new TCanvas("MBL1METTHERSH","MBL1METTHRESH");
    TH1F* mbl1metthresh = new TH1F("mbl1metthresh","Fraction of minbias events above Algorithm Threshold", nmetbins, metmin, metmax);
    mbl1metthresh->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    mbl1metthresh->GetYaxis()->SetTitle("Fraction of events above threshold");
    mbl1metthresh->SetLineColor(colorl1);
    Double_t* mbzvall1, mbsumitl1, mbratiol1;
    mbsumitl1=mbl1metl1cut->GetBinContent(nmetbins+1);
    Double_t* mbtotnuml1 = mbl1metl1cut->GetEntries();
    Double_t* mbtotnuml1wol1cut = mbl1met->GetEntries();
    std::cout << "minbias L1 threshold plot \n";
    double mbttbarl1thresh[nmetbins];
    for (int j=nmetbins; j>0; j--) {
      mbzvall1=mbl1metl1cut->GetBinContent(j);
      mbsumitl1 += mbzvall1;
      //std::cout << "number of events in bin   " << j << "  content   " << mbzvall1 << "\n";
      mbratiol1 = mbsumitl1/mbtotnuml1wol1cut;
      mbl1metthresh->SetBinContent(j,mbratiol1);
      std::cout << "L1 Background bin " << j << "MET [GeV] " <<  float(metmin)+float((j-1)*(metmax-metmin))/float(nmetbins)    << "  fraction above threshold " << mbratiol1 <<"\n";
      mbttbarl1thresh[j-1]=mbratiol1;
    }
    //mbzval=mbl1met->GetBinContent(0);
    //std::cout << "number of underflow events  " << zval << "\n";
    //zval=l1met->GetBinContent(31);
    //std::cout << "number of overflow events  " << zval << "\n";
    //zval=l1met->GetEntries();
    //std::cout << "number of entries = " << zval << "\n";
    mbl1metthresh->Draw();
    gPad->Update();
    TPaveStats *mbstatboxl1 = (TPaveStats*)mbl1metthresh->GetListOfFunctions()->FindObject("stats");
    mbl1metthresh->GetListOfFunctions()->Remove(mbstatboxl1);
    mbl1metthresh->SetStats(0);
    mbstatboxl1->SetTextColor(colorl1);
    mbstatboxl1->SetY1NDC(0.1); //new y start position
    mbstatboxl1->SetY2NDC(0.2); //new y end position
    mbstatboxl1->Draw();

  TCanvas *MBL2METFEB = new TCanvas("MBL2METFEB","MBL2METFEB");
    TH1F* mbl2metfeb = new TH1F("mbl2metfeb"," minbias L2 FEB MET ",  nmetbins, metmin, metmax);
    mbl2metfeb->SetLineColor(colorfeb);
    mbl2metfeb->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    mbl2metfeb->GetYaxis()->SetTitle("Number of Events");
    tree_AS->Draw("Trig_efmet_FEB/1000.>>mbl2metfeb",BG7CUT);
    gPad->Update();
    TPaveStats *mbstatboxmetfeb = (TPaveStats*)mbl2metfeb->GetListOfFunctions()->FindObject("stats");
    mbl2metfeb->GetListOfFunctions()->Remove(mbstatboxmetfeb);
    mbl2metfeb->SetStats(0);
    mbstatboxmetfeb->SetTextColor(colorfeb);
    mbstatboxmetfeb->SetY1NDC(0.3); //new y start position
    mbstatboxmetfeb->SetY2NDC(0.4); //new y end position
    mbstatboxmetfeb->Draw();

  TCanvas *MBL2METFEBL1CUT = new TCanvas("MBL2METFEBL1CUT","MBL2METFEBL1CUT");
    TH1F* mbl2metfebl1cut = new TH1F("mbl2metfebl1cut"," minbias L2 FEB MET L1 Cut",  nmetbins, metmin, metmax);
    mbl2metfebl1cut->SetLineColor(colorfeb);
    mbl2metfebl1cut->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    mbl2metfebl1cut->GetYaxis()->SetTitle("Number of Events");
    tree_AS->Draw("Trig_efmet_FEB/1000.>>mbl2metfebl1cut",BG7CUTANDL1CUT);
    gPad->Update();
    TPaveStats *mbstatboxmetfebl1cut = (TPaveStats*)mbl2metfebl1cut->GetListOfFunctions()->FindObject("stats");
    mbl2metfebl1cut->GetListOfFunctions()->Remove(mbstatboxmetfebl1cut);
    mbl2metfebl1cut->SetStats(0);
    mbstatboxmetfebl1cut->SetTextColor(colorfeb);
    mbstatboxmetfebl1cut->SetY1NDC(0.3); //new y start position
    mbstatboxmetfebl1cut->SetY2NDC(0.4); //new y end position
    mbstatboxmetfebl1cut->Draw();

  TCanvas *MBL2METFEBTHRESH = new TCanvas("MBL2METFEBTHERSH","MBL2METFEBTHRESH");
    TH1F* mbl2metfebthresh = new TH1F("mbl2metfebthresh","Fraction of minbias events above Algorithm Threshold", nmetbins, metmin, metmax);
    mbl2metfebthresh->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    mbl2metfebthresh->GetYaxis()->SetTitle("Fraction of events above threshold");
    mbl2metfebthresh->SetLineColor(colorfeb);
    Double_t* mbzvall2feb, mbsumitl2feb, mbratiol2feb;
    mbsumitl2feb=mbl2metfebl1cut->GetBinContent(nmetbins+1);
    Double_t* mbtotnuml2feb = mbl2metfebl1cut->GetEntries();
    Double_t* mbtotnuml2febwol1cut = mbl2metfeb->GetEntries();
    std::cout << "minbias L2 FEB threshold plot \n";
    double mbttbarfebthresh[nmetbins];
    for (int j=nmetbins; j>0; j--) {
      mbzvall2feb=mbl2metfebl1cut->GetBinContent(j);
      mbsumitl2feb += mbzvall2feb;
      //std::cout << "number of events in bin   " << j << "  content   " << zval << "\n";
      mbratiol2feb = mbsumitl2feb/mbtotnuml2febwol1cut;
      mbl2metfebthresh->SetBinContent(j,mbratiol2feb);
      std::cout << "L2 FEB background bin " << j << "MET [GeV] " <<  float(metmin)+float((j-1)*(metmax-metmin))/float(nmetbins)    << "  fraction above threshold " << mbratiol2feb <<"\n";
      mbttbarfebthresh[j-1]=mbratiol2feb;
    }
    //zval=l1met->GetBinContent(0);
    //std::cout << "number of underflow events  " << zval << "\n";
    //zval=l1met->GetBinContent(31);
    //std::cout << "number of overflow events  " << zval << "\n";
    //zval=l1met->GetEntries();
    //std::cout << "number of entries = " << zval << "\n";
    mbl2metfebthresh->Draw();
    gPad->Update();
    TPaveStats *mbstatboxfeb = (TPaveStats*)mbl2metfebthresh->GetListOfFunctions()->FindObject("stats");
    mbl2metfebthresh->GetListOfFunctions()->Remove(mbstatboxfeb);
    mbl2metfebthresh->SetStats(0);
    mbstatboxfeb->SetTextColor(colorfeb);
    mbstatboxfeb->SetY1NDC(0.3); //new y start position
    mbstatboxfeb->SetY2NDC(0.4); //new y end position
    mbstatboxfeb->Draw();

  TCanvas *MBL2METFEBCALIB = new TCanvas("MBL2METFEBCALIB","MBL2METFEBCALIB");
    TH1F* mbl2metfebcalib = new TH1F("mbl2metfebcalib"," minbias L2 FEB Hadron Calibrated MET ",  nmetbins, metmin, metmax);
    mbl2metfebcalib->SetLineColor(colorfebcalib);
    mbl2metfebcalib->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    mbl2metfebcalib->GetYaxis()->SetTitle("Number of Events");
    //Andrew's JetTauETmiss constants:
    //tree_AS->Draw("sqrt((1.80*Trig_efmetx_FEB_presamplB+1.38*Trig_efmetx_FEB_emb1+1.18*Trig_efmetx_FEB_emb2+1.58*Trig_efmetx_FEB_emb3+1.88*Trig_efmetx_FEB_presamplE+1.57*Trig_efmetx_FEB_eme1+1.68*Trig_efmetx_FEB_eme2+2.67*Trig_efmetx_FEB_eme3+1.51*Trig_efmetx_FEB_hec+1.43*Trig_efmetx_FEB_TileBar+1.53*Trig_efmetx_FEB_TileExt+1.86*Trig_efmetx_FEB_FCalEM+2.26*Trig_efmetx_FEB_FCalHad1+3.06*Trig_efmetx_FEB_FCalHad2)*(1.80*Trig_efmetx_FEB_presamplB+1.38*Trig_efmetx_FEB_emb1+1.18*Trig_efmetx_FEB_emb2+1.58*Trig_efmetx_FEB_emb3+1.88*Trig_efmetx_FEB_presamplE+1.57*Trig_efmetx_FEB_eme1+1.68*Trig_efmetx_FEB_eme2+2.67*Trig_efmetx_FEB_eme3+1.51*Trig_efmetx_FEB_hec+1.43*Trig_efmetx_FEB_TileBar+1.53*Trig_efmetx_FEB_TileExt+1.86*Trig_efmetx_FEB_FCalEM+2.26*Trig_efmetx_FEB_FCalHad1+3.06*Trig_efmetx_FEB_FCalHad2)+(1.80*Trig_efmety_FEB_presamplB+1.38*Trig_efmety_FEB_emb1+1.18*Trig_efmety_FEB_emb2+1.58*Trig_efmety_FEB_emb3+1.88*Trig_efmety_FEB_presamplE+1.57*Trig_efmety_FEB_eme1+1.68*Trig_efmety_FEB_eme2+2.67*Trig_efmety_FEB_eme3+1.51*Trig_efmety_FEB_hec+1.43*Trig_efmety_FEB_TileBar+1.53*Trig_efmety_FEB_TileExt+1.86*Trig_efmety_FEB_FCalEM+2.26*Trig_efmety_FEB_FCalHad1+3.06*Trig_efmety_FEB_FCalHad2)*(1.80*Trig_efmety_FEB_presamplB+1.38*Trig_efmety_FEB_emb1+1.18*Trig_efmety_FEB_emb2+1.58*Trig_efmety_FEB_emb3+1.88*Trig_efmety_FEB_presamplE+1.57*Trig_efmety_FEB_eme1+1.68*Trig_efmety_FEB_eme2+2.67*Trig_efmety_FEB_eme3+1.51*Trig_efmety_FEB_hec+1.43*Trig_efmety_FEB_TileBar+1.53*Trig_efmety_FEB_TileExt+1.86*Trig_efmety_FEB_FCalEM+2.26*Trig_efmety_FEB_FCalHad1+3.06*Trig_efmety_FEB_FCalHad2))/1000.>>mbl2metfebcalib",BG7CUT);
    //Andrew's minbias constants:
    tree_AS->Draw("sqrt((2.36*Trig_efmetx_FEB_presamplB+2.74*Trig_efmetx_FEB_emb1+2.64*Trig_efmetx_FEB_emb2+3.24*Trig_efmetx_FEB_emb3+3.40*Trig_efmetx_FEB_presamplE+2.18*Trig_efmetx_FEB_eme1+2.78*Trig_efmetx_FEB_eme2+4.08*Trig_efmetx_FEB_eme3+1.73*Trig_efmetx_FEB_hec+1.96*Trig_efmetx_FEB_TileBar+0.36*Trig_efmetx_FEB_TileExt+2.08*Trig_efmetx_FEB_FCalEM+2.48*Trig_efmetx_FEB_FCalHad1+2.88*Trig_efmetx_FEB_FCalHad2)*(2.36*Trig_efmetx_FEB_presamplB+2.74*Trig_efmetx_FEB_emb1+2.64*Trig_efmetx_FEB_emb2+3.24*Trig_efmetx_FEB_emb3+3.40*Trig_efmetx_FEB_presamplE+2.18*Trig_efmetx_FEB_eme1+2.78*Trig_efmetx_FEB_eme2+4.08*Trig_efmetx_FEB_eme3+1.73*Trig_efmetx_FEB_hec+1.96*Trig_efmetx_FEB_TileBar+0.36*Trig_efmetx_FEB_TileExt+2.08*Trig_efmetx_FEB_FCalEM+2.48*Trig_efmetx_FEB_FCalHad1+2.88*Trig_efmetx_FEB_FCalHad2)+(2.36*Trig_efmety_FEB_presamplB+2.74*Trig_efmety_FEB_emb1+2.64*Trig_efmety_FEB_emb2+3.24*Trig_efmety_FEB_emb3+3.40*Trig_efmety_FEB_presamplE+2.18*Trig_efmety_FEB_eme1+2.78*Trig_efmety_FEB_eme2+4.08*Trig_efmety_FEB_eme3+1.73*Trig_efmety_FEB_hec+1.96*Trig_efmety_FEB_TileBar+0.36*Trig_efmety_FEB_TileExt+2.08*Trig_efmety_FEB_FCalEM+2.48*Trig_efmety_FEB_FCalHad1+2.88*Trig_efmety_FEB_FCalHad2)*(2.36*Trig_efmety_FEB_presamplB+2.74*Trig_efmety_FEB_emb1+2.64*Trig_efmety_FEB_emb2+3.24*Trig_efmety_FEB_emb3+3.40*Trig_efmety_FEB_presamplE+2.18*Trig_efmety_FEB_eme1+2.78*Trig_efmety_FEB_eme2+4.08*Trig_efmety_FEB_eme3+1.73*Trig_efmety_FEB_hec+1.96*Trig_efmety_FEB_TileBar+0.36*Trig_efmety_FEB_TileExt+2.08*Trig_efmety_FEB_FCalEM+2.48*Trig_efmety_FEB_FCalHad1+2.88*Trig_efmety_FEB_FCalHad2))/1000.>>mbl2metfebcalib",BG7CUT);
    gPad->Update();
    TPaveStats *mbstatboxmetfebcalib = (TPaveStats*)mbl2metfebcalib->GetListOfFunctions()->FindObject("stats");
    mbl2metfebcalib->GetListOfFunctions()->Remove(mbstatboxmetfebcalib);
    mbl2metfebcalib->SetStats(0);
    mbstatboxmetfebcalib->SetTextColor(colorfebcalib);
    mbstatboxmetfebcalib->SetY1NDC(0.2); //new y start position
    mbstatboxmetfebcalib->SetY2NDC(0.3); //new y end position
    mbstatboxmetfebcalib->Draw();

  TCanvas *MBL2METFEBCALIBL1CUT = new TCanvas("MBL2METFEBCALIBL1CUT","MBL2METFEBCALIBL1CUT");
    TH1F* mbl2metfebcalibl1cut = new TH1F("mbl2metfebcalibl1cut"," minbias L2 FEB Hadron Calibrated MET L1 Cut",  nmetbins, metmin, metmax);
    mbl2metfebcalibl1cut->SetLineColor(colorfebcalib);
    mbl2metfebcalibl1cut->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    mbl2metfebcalibl1cut->GetYaxis()->SetTitle("Number of Events");
    //Andrew's JetTauETmiss constants:
    //tree_AS->Draw("sqrt((1.80*Trig_efmetx_FEB_presamplB+1.38*Trig_efmetx_FEB_emb1+1.18*Trig_efmetx_FEB_emb2+1.58*Trig_efmetx_FEB_emb3+1.88*Trig_efmetx_FEB_presamplE+1.57*Trig_efmetx_FEB_eme1+1.68*Trig_efmetx_FEB_eme2+2.67*Trig_efmetx_FEB_eme3+1.51*Trig_efmetx_FEB_hec+1.43*Trig_efmetx_FEB_TileBar+1.53*Trig_efmetx_FEB_TileExt+1.86*Trig_efmetx_FEB_FCalEM+2.26*Trig_efmetx_FEB_FCalHad1+3.06*Trig_efmetx_FEB_FCalHad2)*(1.80*Trig_efmetx_FEB_presamplB+1.38*Trig_efmetx_FEB_emb1+1.18*Trig_efmetx_FEB_emb2+1.58*Trig_efmetx_FEB_emb3+1.88*Trig_efmetx_FEB_presamplE+1.57*Trig_efmetx_FEB_eme1+1.68*Trig_efmetx_FEB_eme2+2.67*Trig_efmetx_FEB_eme3+1.51*Trig_efmetx_FEB_hec+1.43*Trig_efmetx_FEB_TileBar+1.53*Trig_efmetx_FEB_TileExt+1.86*Trig_efmetx_FEB_FCalEM+2.26*Trig_efmetx_FEB_FCalHad1+3.06*Trig_efmetx_FEB_FCalHad2)+(1.80*Trig_efmety_FEB_presamplB+1.38*Trig_efmety_FEB_emb1+1.18*Trig_efmety_FEB_emb2+1.58*Trig_efmety_FEB_emb3+1.88*Trig_efmety_FEB_presamplE+1.57*Trig_efmety_FEB_eme1+1.68*Trig_efmety_FEB_eme2+2.67*Trig_efmety_FEB_eme3+1.51*Trig_efmety_FEB_hec+1.43*Trig_efmety_FEB_TileBar+1.53*Trig_efmety_FEB_TileExt+1.86*Trig_efmety_FEB_FCalEM+2.26*Trig_efmety_FEB_FCalHad1+3.06*Trig_efmety_FEB_FCalHad2)*(1.80*Trig_efmety_FEB_presamplB+1.38*Trig_efmety_FEB_emb1+1.18*Trig_efmety_FEB_emb2+1.58*Trig_efmety_FEB_emb3+1.88*Trig_efmety_FEB_presamplE+1.57*Trig_efmety_FEB_eme1+1.68*Trig_efmety_FEB_eme2+2.67*Trig_efmety_FEB_eme3+1.51*Trig_efmety_FEB_hec+1.43*Trig_efmety_FEB_TileBar+1.53*Trig_efmety_FEB_TileExt+1.86*Trig_efmety_FEB_FCalEM+2.26*Trig_efmety_FEB_FCalHad1+3.06*Trig_efmety_FEB_FCalHad2))/1000.>>mbl2metfebcalibl1cut",BG7CUTANDL1CUT);
    //Andrew's minbias constants:
    tree_AS->Draw("sqrt((2.36*Trig_efmetx_FEB_presamplB+2.74*Trig_efmetx_FEB_emb1+2.64*Trig_efmetx_FEB_emb2+3.24*Trig_efmetx_FEB_emb3+3.40*Trig_efmetx_FEB_presamplE+2.18*Trig_efmetx_FEB_eme1+2.78*Trig_efmetx_FEB_eme2+4.08*Trig_efmetx_FEB_eme3+1.73*Trig_efmetx_FEB_hec+1.96*Trig_efmetx_FEB_TileBar+0.36*Trig_efmetx_FEB_TileExt+2.08*Trig_efmetx_FEB_FCalEM+2.48*Trig_efmetx_FEB_FCalHad1+2.88*Trig_efmetx_FEB_FCalHad2)*(2.36*Trig_efmetx_FEB_presamplB+2.74*Trig_efmetx_FEB_emb1+2.64*Trig_efmetx_FEB_emb2+3.24*Trig_efmetx_FEB_emb3+3.40*Trig_efmetx_FEB_presamplE+2.18*Trig_efmetx_FEB_eme1+2.78*Trig_efmetx_FEB_eme2+4.08*Trig_efmetx_FEB_eme3+1.73*Trig_efmetx_FEB_hec+1.96*Trig_efmetx_FEB_TileBar+0.36*Trig_efmetx_FEB_TileExt+2.08*Trig_efmetx_FEB_FCalEM+2.48*Trig_efmetx_FEB_FCalHad1+2.88*Trig_efmetx_FEB_FCalHad2)+(2.36*Trig_efmety_FEB_presamplB+2.74*Trig_efmety_FEB_emb1+2.64*Trig_efmety_FEB_emb2+3.24*Trig_efmety_FEB_emb3+3.40*Trig_efmety_FEB_presamplE+2.18*Trig_efmety_FEB_eme1+2.78*Trig_efmety_FEB_eme2+4.08*Trig_efmety_FEB_eme3+1.73*Trig_efmety_FEB_hec+1.96*Trig_efmety_FEB_TileBar+0.36*Trig_efmety_FEB_TileExt+2.08*Trig_efmety_FEB_FCalEM+2.48*Trig_efmety_FEB_FCalHad1+2.88*Trig_efmety_FEB_FCalHad2)*(2.36*Trig_efmety_FEB_presamplB+2.74*Trig_efmety_FEB_emb1+2.64*Trig_efmety_FEB_emb2+3.24*Trig_efmety_FEB_emb3+3.40*Trig_efmety_FEB_presamplE+2.18*Trig_efmety_FEB_eme1+2.78*Trig_efmety_FEB_eme2+4.08*Trig_efmety_FEB_eme3+1.73*Trig_efmety_FEB_hec+1.96*Trig_efmety_FEB_TileBar+0.36*Trig_efmety_FEB_TileExt+2.08*Trig_efmety_FEB_FCalEM+2.48*Trig_efmety_FEB_FCalHad1+2.88*Trig_efmety_FEB_FCalHad2))/1000.>>mbl2metfebcalibl1cut",BG7CUTANDL1CUT);
    gPad->Update();
    TPaveStats *mbstatboxmetfebcalibl1cut = (TPaveStats*)mbl2metfebcalibl1cut->GetListOfFunctions()->FindObject("stats");
    mbl2metfebcalibl1cut->GetListOfFunctions()->Remove(mbstatboxmetfebcalibl1cut);
    mbl2metfebcalibl1cut->SetStats(0);
    mbstatboxmetfebcalibl1cut->SetTextColor(colorfebcalib);
    mbstatboxmetfebcalibl1cut->SetY1NDC(0.2); //new y start position
    mbstatboxmetfebcalibl1cut->SetY2NDC(0.3); //new y end position
    mbstatboxmetfebcalibl1cut->Draw();

  TCanvas *MBL2METFEBCALIBTHRESH = new TCanvas("MBL2METFEBCALIBTHERSH","MBL2METFEBCALIBTHRESH");
    TH1F* mbl2metfebcalibthresh = new TH1F("mbl2metfebcalibthresh","Fraction of minbias events above Algorithm Threshold", nmetbins, metmin, metmax);
    mbl2metfebcalibthresh->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    mbl2metfebcalibthresh->GetYaxis()->SetTitle("Fraction of events above threshold");
    mbl2metfebcalibthresh->SetLineColor(colorfebcalib);
    Double_t* mbzvall2febcalib, mbsumitl2febcalib, mbratiol2febcalib;
    mbsumitl2febcalib=mbl2metfebcalibl1cut->GetBinContent(nmetbins+1);
    Double_t* mbtotnuml2febcalib = mbl2metfebcalibl1cut->GetEntries();
    Double_t* mbtotnuml2febcalibwol1cut = mbl2metfebcalib->GetEntries();
    std::cout << "minbias L2 FEB had calibrated threshold plot \n";
    double mbttbarfebcalibthresh[nmetbins];
    for (int j=nmetbins; j>0; j--) {
      mbzvall2febcalib=mbl2metfebcalibl1cut->GetBinContent(j);
      mbsumitl2febcalib += mbzvall2febcalib;
      //std::cout << "number of events in bin   " << j << "  content   " << zval << "\n";
      mbratiol2febcalib = mbsumitl2febcalib/mbtotnuml2febcalibwol1cut;
      mbl2metfebcalibthresh->SetBinContent(j,mbratiol2febcalib);
      std::cout << "L2 FEB had calib background bin " << j << "MET [GeV] " <<  float(metmin)+float((j-1)*(metmax-metmin))/float(nmetbins)    << "  fraction above threshold " << mbratiol2febcalib <<"\n";
      mbttbarfebcalibthresh[j-1]=mbratiol2febcalib;
    }
    //zval=l1met->GetBinContent(0);
    //std::cout << "number of underflow events  " << zval << "\n";
    //zval=l1met->GetBinContent(31);
    //std::cout << "number of overflow events  " << zval << "\n";
    //zval=l1met->GetEntries();
    //std::cout << "number of entries = " << zval << "\n";
    mbl2metfebcalibthresh->Draw();
    gPad->Update();
    TPaveStats *mbstatboxfebcalib = (TPaveStats*)mbl2metfebcalibthresh->GetListOfFunctions()->FindObject("stats");
    mbl2metfebcalibthresh->GetListOfFunctions()->Remove(mbstatboxfebcalib);
    mbl2metfebcalibthresh->SetStats(0);
    mbstatboxfebcalib->SetTextColor(colorfebcalib);
    mbstatboxfebcalib->SetY1NDC(0.2); //new y start position
    mbstatboxfebcalib->SetY2NDC(0.3); //new y end position
    mbstatboxfebcalib->Draw();

  TCanvas *MBEFMETCELL = new TCanvas("MBEFMETCELL","MBEFMETCELL");
    TH1F* mbefmetcell = new TH1F("mbefmetcell"," Minbais EF CELL MET ",  nmetbins, metmin, metmax);
    mbefmetcell->SetLineColor(colorefcell);
    mbefmetcell->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    mbefmetcell->GetYaxis()->SetTitle("Number of Events");
    tree_AS->Draw("Trig_efmet_Cell/1000.>>mbefmetcell",BG7CUT);
    gPad->Update();
    TPaveStats *mbstatboxmetefcell = (TPaveStats*)mbefmetcell->GetListOfFunctions()->FindObject("stats");
    mbefmetcell->GetListOfFunctions()->Remove(mbstatboxmetefcell);
    mbefmetcell->SetStats(0);
    mbstatboxmetefcell->SetTextColor(colorefcell);
    mbstatboxmetefcell->SetY1NDC(0.6); //new y start position
    mbstatboxmetefcell->SetY2NDC(0.7); //new y end position
    mbstatboxmetefcell->Draw();

  TCanvas *MBEFMETCELLL1CUT = new TCanvas("MBEFMETCELLL1CUT","MBEFMETCELLL1CUT");
    TH1F* mbefmetcelll1cut = new TH1F("mbefmetcelll1cut"," Minbias EF CELL MET with L1 Cut",  nmetbins, metmin, metmax);
    mbefmetcelll1cut->SetLineColor(colorefcell);
    mbefmetcelll1cut->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    mbefmetcelll1cut->GetYaxis()->SetTitle("Number of Events");
    tree_AS->Draw("Trig_efmet_Cell/1000.>>mbefmetcelll1cut",BG7CUTANDL1CUT);
    gPad->Update();
    TPaveStats *mbstatboxmetefcelll1cut = (TPaveStats*)mbefmetcelll1cut->GetListOfFunctions()->FindObject("stats");
    mbefmetcelll1cut->GetListOfFunctions()->Remove(mbstatboxmetefcelll1cut);
    mbefmetcelll1cut->SetStats(0);
    mbstatboxmetefcelll1cut->SetTextColor(colorefcell);
    mbstatboxmetefcelll1cut->SetY1NDC(0.6); //new y start position
    mbstatboxmetefcelll1cut->SetY2NDC(0.7); //new y end position
    mbstatboxmetefcelll1cut->Draw();

  TCanvas *MBEFMETCELLTHRESH = new TCanvas("MBEFMETCELLTHERSH","MBEFMETCELLTHRESH");
    TH1F* mbefmetcellthresh = new TH1F("mbefmetcellthresh","Fraction of minbias events above Algorithm Threshold", nmetbins, metmin, metmax);
    mbefmetcellthresh->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    mbefmetcellthresh->GetYaxis()->SetTitle("Fraction of events above threshold");
    mbefmetcellthresh->SetLineColor(colorefcell);
    Double_t* mbzvalefcell, mbsumitefcell, mbratioefcell;
    mbsumitefcell=mbefmetcelll1cut->GetBinContent(nmetbins+1);
    Double_t* mbtotnumefcell = mbefmetcelll1cut->GetEntries();
    Double_t* mbtotnumefcellwol1cut = mbefmetcell->GetEntries();
    std::cout << "minbias EF cell threshold plot \n";
    double mbttbarefcellthresh[nmetbins];
    for (int j=nmetbins; j>0; j--) {
      mbzvalefcell=mbefmetcelll1cut->GetBinContent(j);
      mbsumitefcell += mbzvalefcell;
      //std::cout << "number of events in bin   " << j << "  content   " << zval << "\n";
      mbratioefcell = mbsumitefcell/mbtotnumefcellwol1cut;
      mbefmetcellthresh->SetBinContent(j,mbratioefcell);
      std::cout << "EF cell background bin " << j << "MET [GeV] " <<  float(metmin)+float((j-1)*(metmax-metmin))/float(nmetbins)    << "  fraction above threshold " << mbratioefcell <<"\n";
      mbttbarefcellthresh[j-1]=mbratioefcell;
    }
    //zval=l1met->GetBinContent(0);
    //std::cout << "number of underflow events  " << zval << "\n";
    //zval=l1met->GetBinContent(31);
    //std::cout << "number of overflow events  " << zval << "\n";
    //zval=l1met->GetEntries();
    //std::cout << "number of entries = " << zval << "\n";
    mbefmetcellthresh->Draw();
    gPad->Update();
    TPaveStats *mbstatboxefcellthresh = (TPaveStats*)mbefmetcellthresh->GetListOfFunctions()->FindObject("stats");
    mbefmetcellthresh->GetListOfFunctions()->Remove(mbstatboxefcellthresh);
    mbefmetcellthresh->SetStats(0);
    mbstatboxefcellthresh->SetTextColor(colorefcell);
    mbstatboxefcellthresh->SetY1NDC(0.6); //new y start position
    mbstatboxefcellthresh->SetY2NDC(0.7); //new y end position
    mbstatboxefcellthresh->Draw();

  TCanvas *MBEFMETTCLCW = new TCanvas("MBEFMETTCLCW","MBEFMETTCLCW");
    TH1F* mbefmettclcw = new TH1F("mbefmettclcw"," Minbias EF TCLCW MET ",  nmetbins, metmin, metmax);
    mbefmettclcw->SetLineColor(colortclcw);
    mbefmettclcw->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    mbefmettclcw->GetYaxis()->SetTitle("Number of Events");
    tree_AS->Draw("Trig_efmet_tclcw/1000.>>mbefmettclcw",BG7CUT);
    gPad->Update();
    TPaveStats *mbstatboxmettclcw = (TPaveStats*)mbefmettclcw->GetListOfFunctions()->FindObject("stats");
    mbefmettclcw->GetListOfFunctions()->Remove(mbstatboxmettclcw);
    mbefmettclcw->SetStats(0);
    mbstatboxmettclcw->SetTextColor(colortclcw);
    mbstatboxmettclcw->SetY1NDC(0.4); //new y start position
    mbstatboxmettclcw->SetY2NDC(0.5); //new y end position
    mbstatboxmettclcw->Draw();

  TCanvas *MBEFMETTCLCWL1CUT = new TCanvas("MBEFMETTCLCWL1CUT","MBEFMETTCLCWL1CUT");
    TH1F* mbefmettclcwl1cut = new TH1F("mbefmettclcwl1cut"," Minbias EF TCLCW MET L1 Cut",  nmetbins, metmin, metmax);
    mbefmettclcwl1cut->SetLineColor(colortclcw);
    mbefmettclcwl1cut->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    mbefmettclcwl1cut->GetYaxis()->SetTitle("Number of Events");
    tree_AS->Draw("Trig_efmet_tclcw/1000.>>mbefmettclcwl1cut",BG7CUTANDL1CUT);
    gPad->Update();
    TPaveStats *mbstatboxmettclcwl1cut = (TPaveStats*)mbefmettclcwl1cut->GetListOfFunctions()->FindObject("stats");
    mbefmettclcwl1cut->GetListOfFunctions()->Remove(mbstatboxmettclcwl1cut);
    mbefmettclcwl1cut->SetStats(0);
    mbstatboxmettclcwl1cut->SetTextColor(colortclcw);
    mbstatboxmettclcwl1cut->SetY1NDC(0.4); //new y start position
    mbstatboxmettclcwl1cut->SetY2NDC(0.5); //new y end position
    mbstatboxmettclcwl1cut->Draw();

  TCanvas *MBEFMETTCLCWTHRESH = new TCanvas("MBEFMETTCLCWTHERSH","MBEFMETTCLCWTHRESH");
    TH1F* mbefmettclcwthresh = new TH1F("mbefmettclcwthresh","Fraction of minbias events above Algorithm Threshold", nmetbins, metmin, metmax);
    mbefmettclcwthresh->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    mbefmettclcwthresh->GetYaxis()->SetTitle("Fraction of events above threshold");
    mbefmettclcwthresh->SetLineColor(colortclcw);
    Double_t* mbzvaleftclcw, mbsumiteftclcw, mbratioeftclcw;
    mbsumiteftclcw=mbefmettclcwl1cut->GetBinContent(nmetbins+1);
    Double_t* mbtotnumeftclcw = mbefmettclcwl1cut->GetEntries();
    Double_t* mbtotnumeftclcwwol1cut = mbefmettclcw->GetEntries();
    std::cout << "minbias EF tclcw threshold plot \n";
    double mbttbartclcwthresh[nmetbins];
    for (int j=nmetbins; j>0; j--) {
      mbzvaleftclcw=mbefmettclcwl1cut->GetBinContent(j);
      mbsumiteftclcw += mbzvaleftclcw;
      //std::cout << "number of events in bin   " << j << "  content   " << zval << "\n";
      mbratioeftclcw = mbsumiteftclcw/mbtotnumeftclcwwol1cut;
      mbefmettclcwthresh->SetBinContent(j,mbratioeftclcw);
      std::cout << "EF tclcw background bin " << j << "MET [GeV] " <<  float(metmin)+float((j-1)*(metmax-metmin))/float(nmetbins)    << "  fraction above threshold " << mbratioeftclcw <<"\n";
      mbttbartclcwthresh[j-1]=mbratioeftclcw;
    }
    //zval=l1met->GetBinContent(0);
    //std::cout << "number of underflow events  " << zval << "\n";
    //zval=l1met->GetBinContent(31);
    //std::cout << "number of overflow events  " << zval << "\n";
    //zval=l1met->GetEntries();
    //std::cout << "number of entries = " << zval << "\n";
    mbefmettclcwthresh->Draw();
    gPad->Update();
    TPaveStats *mbstatbox = (TPaveStats*)mbefmettclcwthresh->GetListOfFunctions()->FindObject("stats");
    mbefmettclcwthresh->GetListOfFunctions()->Remove(mbstatbox);
    mbefmettclcwthresh->SetStats(0);
    mbstatbox->SetTextColor(colortclcw);
    mbstatbox->SetY1NDC(0.4); //new y start position
    mbstatbox->SetY2NDC(0.5); //new y end position
    mbstatbox->Draw();

  TCanvas *MBEFMETEMCLUSTER = new TCanvas("MBEFMETEMCLUSTER","MBEFMETEMCLUSTER");
    TH1F* mbefmetemcluster = new TH1F("mbefmetemcluster"," Minbias EF MET ",  nmetbins, metmin, metmax);
    mbefmetemcluster->SetLineColor(coloremcluster);
    mbefmetemcluster->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    mbefmetemcluster->GetYaxis()->SetTitle("Number of Events");
    tree_AS->Draw("Trig_efmet_emcluster/1000.>>mbefmetemcluster",BG7CUT);
    gPad->Update();
    TPaveStats *mbstatboxmetemcluster = (TPaveStats*)mbefmetemcluster->GetListOfFunctions()->FindObject("stats");
    mbefmetemcluster->GetListOfFunctions()->Remove(mbstatboxmetemcluster);
    mbefmetemcluster->SetStats(0);
    mbstatboxmetemcluster->SetTextColor(coloremcluster);
    mbstatboxmetemcluster->SetY1NDC(0.5); //new y start position
    mbstatboxmetemcluster->SetY2NDC(0.6); //new y end position
    mbstatboxmetemcluster->Draw();

  TCanvas *MBEFMETEMCLUSTERL1CUT = new TCanvas("MBEFMETEMCLUSTERL1CUT","MBEFMETEMCLUSTERL1CUT");
    TH1F* mbefmetemclusterl1cut = new TH1F("mbefmetemclusterl1cut"," Minbias EF MET L1 Cut",  nmetbins, metmin, metmax);
    mbefmetemclusterl1cut->SetLineColor(coloremcluster);
    mbefmetemclusterl1cut->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    mbefmetemclusterl1cut->GetYaxis()->SetTitle("Number of Events");
    tree_AS->Draw("Trig_efmet_emcluster/1000.>>mbefmetemclusterl1cut",BG7CUTANDL1CUT);
    gPad->Update();
    TPaveStats *mbstatboxmetemclusterl1cut = (TPaveStats*)mbefmetemclusterl1cut->GetListOfFunctions()->FindObject("stats");
    mbefmetemclusterl1cut->GetListOfFunctions()->Remove(mbstatboxmetemclusterl1cut);
    mbefmetemclusterl1cut->SetStats(0);
    mbstatboxmetemclusterl1cut->SetTextColor(coloremcluster);
    mbstatboxmetemclusterl1cut->SetY1NDC(0.5); //new y start position
    mbstatboxmetemclusterl1cut->SetY2NDC(0.6); //new y end position
    mbstatboxmetemclusterl1cut->Draw();

  TCanvas *MBEFMETEMCLUSTERTHRESH = new TCanvas("MBEFMETEMCLUSTERTHERSH","MBEFMETEMCLUSTERTHRESH");
    TH1F* mbefmetemclusterthresh = new TH1F("mbefmetemclusterthresh","Fraction of minbias events above Algorithm Threshold", nmetbins, metmin, metmax);
    mbefmetemclusterthresh->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    mbefmetemclusterthresh->GetYaxis()->SetTitle("Fraction of events above threshold");
    mbefmetemclusterthresh->SetLineColor(coloremcluster);
    Double_t* mbzvalefemcluster, mbsumitefemcluster, mbratioefemcluster;
    mbsumitefemcluster=mbefmetemclusterl1cut->GetBinContent(nmetbins+1);
    Double_t* mbtotnumefemcluster = mbefmetemclusterl1cut->GetEntries();
    Double_t* mbtotnumefemclusterwol1cut = mbefmetemcluster->GetEntries();
    std::cout << "Minbias EF em cluster threshold plot \n";
    double mbttbaremclusterthresh[nmetbins];
    for (int j=nmetbins; j>0; j--) {
      mbzvalefemcluster=mbefmetemclusterl1cut->GetBinContent(j);
      mbsumitefemcluster += mbzvalefemcluster;
      //std::cout << "number of events in bin   " << j << "  content   " << zval << "\n";
      mbratioefemcluster = mbsumitefemcluster/mbtotnumefemclusterwol1cut;
      mbefmetemclusterthresh->SetBinContent(j,mbratioefemcluster);
      std::cout << "EF EM cluster background bin " << j << "MET [GeV] " <<  float(metmin)+float((j-1)*(metmax-metmin))/float(nmetbins)    << "  fraction above threshold " << mbratioefemcluster <<"\n";
      mbttbaremclusterthresh[j-1]=mbratioefemcluster;
    }
    //zval=l1met->GetBinContent(0);
    //std::cout << "number of underflow events  " << zval << "\n";
    //zval=l1met->GetBinContent(31);
    //std::cout << "number of overflow events  " << zval << "\n";
    //zval=l1met->GetEntries();
    //std::cout << "number of entries = " << zval << "\n";
    mbefmetemclusterthresh->Draw();
    gPad->Update();
    TPaveStats *mbstatboxemclusterthresh = (TPaveStats*)mbefmetemclusterthresh->GetListOfFunctions()->FindObject("stats");
    mbefmetemclusterthresh->GetListOfFunctions()->Remove(mbstatboxemclusterthresh);
    mbefmetemclusterthresh->SetStats(0);
    mbstatboxemclusterthresh->SetTextColor(coloremcluster);
    mbstatboxemclusterthresh->SetY1NDC(0.5); //new y start position
    mbstatboxemclusterthresh->SetY2NDC(0.6); //new y end position
    mbstatboxemclusterthresh->Draw();

  TCanvas *MBOLMETLOCHADTOPO = new TCanvas("MBOLMETLOCHADTOPO","MBOLMETLOCHADTOPO");
    TH1F* mbolmetlochadtopo = new TH1F("mbolmetlochadtopo"," Minbias LocHadTopo MET ",  nmetbins, metmin, metmax);
    mbolmetlochadtopo->SetLineColor(colorlochadtopo);
    mbolmetlochadtopo->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    mbolmetlochadtopo->GetYaxis()->SetTitle("Number of Events");
    tree_AS->Draw("Olmet_calo_lochadtopo/1000.>>mbolmetlochadtopo",BG7CUT);
    gPad->Update();
    TPaveStats *mbstatboxmetlochadtopo = (TPaveStats*)mbolmetlochadtopo->GetListOfFunctions()->FindObject("stats");
    mbolmetlochadtopo->GetListOfFunctions()->Remove(mbstatboxmetlochadtopo);
    mbolmetlochadtopo->SetStats(0);
    mbstatboxmetlochadtopo->SetTextColor(colorlochadtopo);
    mbstatboxmetlochadtopo->SetY1NDC(0.7); //new y start position
    mbstatboxmetlochadtopo->SetY2NDC(0.8); //new y end position
    mbstatboxmetlochadtopo->Draw();

  TCanvas *MBOLMETLOCHADTOPOL1CUT = new TCanvas("MBOLMETLOCHADTOPOL1CUT","MBOLMETLOCHADTOPOL1CUT");
    TH1F* mbolmetlochadtopol1cut = new TH1F("mbolmetlochadtopol1cut"," Minbias LocHadTopo MET L1 Cut",  nmetbins, metmin, metmax);
    mbolmetlochadtopol1cut->SetLineColor(colorlochadtopo);
    mbolmetlochadtopol1cut->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    mbolmetlochadtopol1cut->GetYaxis()->SetTitle("Number of Events");
    tree_AS->Draw("Olmet_calo_lochadtopo/1000.>>mbolmetlochadtopol1cut",BG7CUTANDL1CUT);
    gPad->Update();
    TPaveStats *mbstatboxmetlochadtopol1cut = (TPaveStats*)mbolmetlochadtopol1cut->GetListOfFunctions()->FindObject("stats");
    mbolmetlochadtopol1cut->GetListOfFunctions()->Remove(mbstatboxmetlochadtopol1cut);
    mbolmetlochadtopol1cut->SetStats(0);
    mbstatboxmetlochadtopol1cut->SetTextColor(colorlochadtopo);
    mbstatboxmetlochadtopol1cut->SetY1NDC(0.7); //new y start position
    mbstatboxmetlochadtopol1cut->SetY2NDC(0.8); //new y end position
    mbstatboxmetlochadtopol1cut->Draw();

  TCanvas *MBOLMETLOCHADTOPOTHRESH = new TCanvas("MBOLMETLOCHADTOPOTHRESH","MBOLMETLOCHADTOPOTHRESH");
    TH1F* mbolmetlochadtopothresh = new TH1F("mbolmetlochadtopothresh","Fraction of minbias events above Algorithm Threshold", nmetbins, metmin, metmax);
    mbolmetlochadtopothresh->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    mbolmetlochadtopothresh->GetYaxis()->SetTitle("Fraction of events above threshold");
    mbolmetlochadtopothresh->SetLineColor(colorlochadtopo);
    Double_t* mbzvaleflochadtopo, mbsumiteflochadtopo, mbratioeflochadtopo;
    mbsumiteflochadtopo=mbolmetlochadtopol1cut->GetBinContent(nmetbins+1);
    Double_t* mbtotnumeflochadtopo = mbolmetlochadtopol1cut->GetEntries();
    Double_t* mbtotnumeflochadtopowol1cut = mbolmetlochadtopo->GetEntries();
    std::cout << "Minbias OL LocHadTopo threshold plot \n";
    double mbttbarlochadtopothresh[nmetbins];
    for (int j=nmetbins; j>0; j--) {
      mbzvaleflochadtopo=mbolmetlochadtopol1cut->GetBinContent(j);
      mbsumiteflochadtopo += mbzvaleflochadtopo;
      //std::cout << "number of events in bin   " << j << "  content   " << zval << "\n";
      mbratioeflochadtopo = mbsumiteflochadtopo/mbtotnumeflochadtopowol1cut;
      mbolmetlochadtopothresh->SetBinContent(j,mbratioeflochadtopo);
      std::cout << "Ol LocHadTopo background bin " << j << "MET [GeV] " <<  float(metmin)+float((j-1)*(metmax-metmin))/float(nmetbins)    << "  fraction above threshold " << mbratioeflochadtopo <<"\n";
      mbttbarlochadtopothresh[j-1]=mbratioeflochadtopo;
    }
    //zval=l1met->GetBinContent(0);
    //std::cout << "number of underflow events  " << zval << "\n";
    //zval=l1met->GetBinContent(31);
    //std::cout << "number of overflow events  " << zval << "\n";
    //zval=l1met->GetEntries();
    //std::cout << "number of entries = " << zval << "\n";
    mbolmetlochadtopothresh->Draw();
    gPad->Update();
    TPaveStats *mbstatboxlochadtopothresh = (TPaveStats*)mbolmetlochadtopothresh->GetListOfFunctions()->FindObject("stats");
    mbolmetlochadtopothresh->GetListOfFunctions()->Remove(mbstatboxlochadtopothresh);
    mbolmetlochadtopothresh->SetStats(0);
    mbstatboxlochadtopothresh->SetTextColor(colorlochadtopo);
    mbstatboxlochadtopothresh->SetY1NDC(0.7); //new y start position
    mbstatboxlochadtopothresh->SetY2NDC(0.8); //new y end position
    mbstatboxlochadtopothresh->Draw();

  TCanvas *MBOLMETREFFINALCALOPARTS = new TCanvas("MBOLMETREFFINALCALOPARTS","MBOLMETREFFINALCALOPARTS");
    TH1F* mbolmetreffinalcaloparts = new TH1F("mbolmetreffinalcaloparts"," Minbias RefFinal Calo parts MET ",  nmetbins, metmin, metmax);
    mbolmetreffinalcaloparts->SetLineColor(colorreffinal);
    mbolmetreffinalcaloparts->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    mbolmetreffinalcaloparts->GetYaxis()->SetTitle("Number of Events");
    //RefFinal
    //tree_AS->Draw("Olmet_reffinal/1000.>>mbolmetreffinalcaloparts",BG7CUT);
    //RefFinal Calo parts only:
    tree_AS->Draw("sqrt((Olmetx_refele+Olmetx_refgamma+Olmetx_reftau+Olmetx_refjet+Olmetx_cellouteflow)*(Olmetx_refele+Olmetx_refgamma+Olmetx_reftau+Olmetx_refjet+Olmetx_cellouteflow)+(Olmety_refele+Olmety_refgamma+Olmety_reftau+Olmety_refjet+Olmety_cellouteflow)*(Olmety_refele+Olmety_refgamma+Olmety_reftau+Olmety_refjet+Olmety_cellouteflow))/1000.>>mbolmetreffinalcaloparts",BG7CUT);
    //RefFinal Calo parts only without soft term
    //tree_AS->Draw("sqrt((Olmetx_refele+Olmetx_refgamma+Olmetx_reftau+Olmetx_refjet)*(Olmetx_refele+Olmetx_refgamma+Olmetx_reftau+Olmetx_refjet)+(Olmety_refele+Olmety_refgamma+Olmety_reftau+Olmety_refjet)*(Olmety_refele+Olmety_refgamma+Olmety_reftau+Olmety_refjet))/1000.>>mbolmetreffinalcaloparts",BG7CUT);
    gPad->Update();
    TPaveStats *mbstatboxmetreffinalcaloparts = (TPaveStats*)mbolmetreffinalcaloparts->GetListOfFunctions()->FindObject("stats");
    mbolmetreffinalcaloparts->GetListOfFunctions()->Remove(mbstatboxmetreffinalcaloparts);
    mbolmetreffinalcaloparts->SetStats(0);
    mbstatboxmetreffinalcaloparts->SetTextColor(colorreffinal);
    mbstatboxmetreffinalcaloparts->SetY1NDC(0.8); //new y start position
    mbstatboxmetreffinalcaloparts->SetY2NDC(0.9); //new y end position
    mbstatboxmetreffinalcaloparts->Draw();

  TCanvas *MBOLMETREFFINALCALOPARTSL1CUT = new TCanvas("MBOLMETREFFINALCALOPARTSL1CUT","MBOLMETREFFINALCALOPARTSL1CUT");
    TH1F* mbolmetreffinalcalopartsl1cut = new TH1F("mbolmetreffinalcalopartsl1cut"," Minbias RefFinal Calo parts MET L1 Cut",  nmetbins, metmin, metmax);
    mbolmetreffinalcalopartsl1cut->SetLineColor(colorreffinal);
    mbolmetreffinalcalopartsl1cut->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    mbolmetreffinalcalopartsl1cut->GetYaxis()->SetTitle("Number of Events");
    //RefFinal
    //tree_AS->Draw("Olmet_reffinal/1000.>>mbolmetreffinalcalopartsl1cut",BG7CUTANDL1CUT);
    //RefFinal calo parts only:
    tree_AS->Draw("sqrt((Olmetx_refele+Olmetx_refgamma+Olmetx_reftau+Olmetx_refjet+Olmetx_cellouteflow)*(Olmetx_refele+Olmetx_refgamma+Olmetx_reftau+Olmetx_refjet+Olmetx_cellouteflow)+(Olmety_refele+Olmety_refgamma+Olmety_reftau+Olmety_refjet+Olmety_cellouteflow)*(Olmety_refele+Olmety_refgamma+Olmety_reftau+Olmety_refjet+Olmety_cellouteflow))/1000.>>mbolmetreffinalcalopartsl1cut",BG7CUTANDL1CUT);
    //RefFinal calo parts only without soft term:
    //tree_AS->Draw("sqrt((Olmetx_refele+Olmetx_refgamma+Olmetx_reftau+Olmetx_refjet)*(Olmetx_refele+Olmetx_refgamma+Olmetx_reftau+Olmetx_refjet)+(Olmety_refele+Olmety_refgamma+Olmety_reftau+Olmety_refjet)*(Olmety_refele+Olmety_refgamma+Olmety_reftau+Olmety_refjet))/1000.>>mbolmetreffinalcalopartsl1cut",BG7CUTANDL1CUT);
    gPad->Update();
    TPaveStats *mbstatboxmetreffinalcalopartsl1cut = (TPaveStats*)mbolmetreffinalcalopartsl1cut->GetListOfFunctions()->FindObject("stats");
    mbolmetreffinalcalopartsl1cut->GetListOfFunctions()->Remove(mbstatboxmetreffinalcalopartsl1cut);
    mbolmetreffinalcalopartsl1cut->SetStats(0);
    mbstatboxmetreffinalcalopartsl1cut->SetTextColor(colorreffinal);
    mbstatboxmetreffinalcalopartsl1cut->SetY1NDC(0.8); //new y start position
    mbstatboxmetreffinalcalopartsl1cut->SetY2NDC(0.9); //new y end position
    mbstatboxmetreffinalcalopartsl1cut->Draw();

  TCanvas *MBOLMETREFFINALCALOPARTSTHRESH = new TCanvas("MBOLMETREFFINALCALOPARTSTHRESH","MBOLMETREFFINALCALOPARTSTHRESH");
    TH1F* mbolmetreffinalcalopartsthresh = new TH1F("mbolmetreffinalcalopartsthresh","Fraction of minbias events above Algorithm Threshold", nmetbins, metmin, metmax);
    mbolmetreffinalcalopartsthresh->GetXaxis()->SetTitle("Algorithm MET [GeV]");
    mbolmetreffinalcalopartsthresh->GetYaxis()->SetTitle("Fraction of events above threshold");
    mbolmetreffinalcalopartsthresh->SetLineColor(colorreffinal);
    Double_t* mbzvalefreffinalcaloparts, mbsumitefreffinalcaloparts, mbratioefreffinalcaloparts;
    mbsumitefreffinalcaloparts=mbolmetreffinalcalopartsl1cut->GetBinContent(nmetbins+1);
    Double_t* mbtotnumefreffinalcaloparts = mbolmetreffinalcalopartsl1cut->GetEntries();
    Double_t* mbtotnumefreffinalcalopartswol1cut = mbolmetreffinalcaloparts->GetEntries();
    std::cout << "Minbias OL RefFinal Calo Parts threshold plot \n";
    double mbttbarreffinalcalopartsthresh[nmetbins];
    for (int j=nmetbins; j>0; j--) {
      mbzvalefreffinalcaloparts=mbolmetreffinalcalopartsl1cut->GetBinContent(j);
      mbsumitefreffinalcaloparts += mbzvalefreffinalcaloparts;
      //std::cout << "number of events in bin   " << j << "  content   " << zval << "\n";
      mbratioefreffinalcaloparts = mbsumitefreffinalcaloparts/mbtotnumefreffinalcalopartswol1cut;
      mbolmetreffinalcalopartsthresh->SetBinContent(j,mbratioefreffinalcaloparts);
      std::cout << "Ol RefFInal Calo Parts background bin " << j << "MET [GeV] " <<  float(metmin)+float((j-1)*(metmax-metmin))/float(nmetbins)    << "  fraction above threshold " << mbratioefreffinalcaloparts <<"\n";
      mbttbarreffinalcalopartsthresh[j-1]=mbratioefreffinalcaloparts;
    }
    //zval=l1met->GetBinContent(0);
    //std::cout << "number of underflow events  " << zval << "\n";
    //zval=l1met->GetBinContent(31);
    //std::cout << "number of overflow events  " << zval << "\n";
    //zval=l1met->GetEntries();
    //std::cout << "number of entries = " << zval << "\n";
    mbolmetreffinalcalopartsthresh->Draw();
    gPad->Update();
    TPaveStats *mbstatboxreffinalcalopartsthresh = (TPaveStats*)mbolmetreffinalcalopartsthresh->GetListOfFunctions()->FindObject("stats");
    mbolmetreffinalcalopartsthresh->GetListOfFunctions()->Remove(mbstatboxreffinalcalopartsthresh);
    mbolmetreffinalcalopartsthresh->SetStats(0);
    mbstatboxreffinalcalopartsthresh->SetTextColor(colorreffinal);
    mbstatboxreffinalcalopartsthresh->SetY1NDC(0.8); //new y start position
    mbstatboxreffinalcalopartsthresh->SetY2NDC(0.9); //new y end position
    mbstatboxreffinalcalopartsthresh->Draw();

  TCanvas *MBCOMPTHRESHMANY  = new TCanvas("MBCOMPTHRESHMANY","MBCOMPTHRESHMANY");
    mbefmettclcwthresh->Draw();
    //mbstatbox->Draw();
    mbefmetemclusterthresh->Draw("same");
    //mbstatboxemclusterthresh->Draw();
    mbl2metfebthresh->Draw("same");
    //mbstatboxfeb->Draw();
    mbl2metfebcalibthresh->Draw("same");
    //mbstatboxfebcalib->Draw();
    mbl1metthresh->Draw("same");
    //mbstatboxl1->Draw();
    mbefmetcellthresh->Draw("same");
    //mbstatboxefcellthresh->Draw();
    mbolmetlochadtopothresh->Draw("same");
    //mbstatboxlochadtopothresh->Draw();
    mbolmetreffinalcalopartsthresh->Draw("same");
    //mbstatboxreffinalcalopartsthresh->Draw();
    TLegend* lmbeff=new TLegend(0.1,0.7,0.4,0.9);
    lmbeff->AddEntry("mbl2metfebthresh","FEB","L");
    lmbeff->AddEntry("mbl2metfebcalibthresh","FEB Had Calib","L");
    lmbeff->AddEntry("mbefmettclcwthresh","tclcw","L");
    lmbeff->AddEntry("mbefmetemclusterthresh","EM cluster","L");
    lmbeff->AddEntry("mbl1metthresh","L1","L");
    lmbeff->AddEntry("mbefmetcellthresh","EF Cell","L");
    lmbeff->AddEntry("mbolmetlochadtopothresh","LocHadTopo","L");
    lmbeff->AddEntry("mbolmetreffinalcalopartsthresh","RefFinal","L");
    lmbeff->Draw();

  TCanvas *MBTRUTHMET = new TCanvas("MBTRUTHMET","MBTRUTHMET");
    TH1F* mbtruthmet = new TH1F("mbtruthmet"," Minbias Truth MET ",  nmetbins, metmin, metmax);
    mbtruthmet->SetLineColor(colortruth);
    mbtruthmet->GetXaxis()->SetTitle("Truth MET [GeV]");
    mbtruthmet->GetYaxis()->SetTitle("Number of Events");
    tree_AS->Draw("sqrt(Truth_metx*Truth_metx+Truth_mety*Truth_mety)/1000.>>mbtruthmet",BG7CUT);
    gPad->Update();
    TPaveStats *mbstatboxmettruth = (TPaveStats*)mbtruthmet->GetListOfFunctions()->FindObject("stats");
    mbtruthmet->GetListOfFunctions()->Remove(mbstatboxmettruth);
    mbtruthmet->SetStats(0);
    mbstatboxmettruth->SetTextColor(colortruth);
    mbstatboxmettruth->SetY1NDC(0.7); //new y start position
    mbstatboxmettruth->SetY2NDC(0.8); //new y end position
    mbstatboxmettruth->Draw();
    
  TCanvas *MBCOMPMET = new TCanvas("MBCOMPMET","MBCOMPMET");
    mbl2metfeb->Draw();
    //mbstatboxmetfeb->Draw();
    mbl2metfebcalib->Draw("same");
    //mbstatboxmetfebcalib->Draw();
    mbefmettclcw->Draw("same");
    //mbstatboxmettclcw->Draw();
    mbefmetemcluster->Draw("same");
    //mbstatboxmetemcluster->Draw();
    mbtruthmet->Draw("same");
    //mbstatboxmettruth->Draw();
    mbl1met->Draw("same");
    //mbstatboxmetl1->Draw();
    mbefmetcell->Draw("same");
    //mbstatboxmetcell->Draw();
    mbolmetlochadtopo->Draw("same");
    mbolmetreffinalcaloparts->Draw("same");
    TLegend* mbcomp=new TLegend(0.7,0.7,0.9,0.9);
    mbcomp->AddEntry("mbefmettclcw","tclcw","L");
    mbcomp->AddEntry("mbefmetemcluster","EM cluster","L");
    mbcomp->AddEntry("mbl2metfeb","FEB","L");
    mbcomp->AddEntry("mbl2metfebcalib","FEB Had Calib","L");
    mbcomp->AddEntry("mbl1met","L1","L");
    mbcomp->AddEntry("mbtruthmet","Truth","L");
    mbcomp->AddEntry("mbefmetcell","EF Cell","L");
    mbcomp->AddEntry("mbolmetlochadtopo","LocHadTopo","L");
    mbcomp->AddEntry("mbolmetreffinalcaloparts","RefFinal Calo Parts","L");
    mbcomp->Draw();

  TCanvas *SIGVSMBTCLCW = new  TCanvas("SIGVSMBTCLCW","SIGVSMBTCLCW");
    TGraph *tclcwgr = new TGraph(nmetbins,mbttbartclcwthresh,ttbartclcwthresh);
    tclcwgr->SetTitle("Efficiency versus rate");
    tclcwgr->SetMarkerColor(colortclcw);
    tclcwgr->SetMarkerSize(1.0);
    tclcwgr->SetMarkerStyle(20);
    //X-axis is BG
    tclcwgr->GetXaxis()->SetTitle("minbias fraction pass");
    //tclcwgr->GetXaxis()->SetTitle("2-jet Z3 fraction pass");
    //Y-axis is signal
    //tclcwgr->GetYaxis()->SetTitle("ttbar lept fraction pass");
    //tclcwgr->GetYaxis()->SetTitle("jetjet z3 fraction pass");
    tclcwgr->GetYaxis()->SetTitle("signal fraction pass");
    tclcwgr->Draw("AP");

    TGraph *efcellgr = new TGraph(nmetbins,mbttbarefcellthresh,ttbarefcellthresh);
    efcellgr->SetTitle("Efficiency versus rate");
    efcellgr->SetMarkerColor(colorefcell);
    efcellgr->SetMarkerSize(1.0);
    efcellgr->SetMarkerStyle(20);
    //X-axis is BG
    efcellgr->GetXaxis()->SetTitle("minbias fraction pass");
    //efcellgr->GetXaxis()->SetTitle("2-jet Z3 fraction pass");
    //Y-axis is signal
    //efcellgr->GetYaxis()->SetTitle("ttbar lept fraction pass");
    //efcellgr->GetYaxis()->SetTitle("jetjet z3 fraction pass");
    efcellgr->GetYaxis()->SetTitle("signal fraction pass");
    efcellgr->Draw("P");

    TGraph *emclustergr = new TGraph(nmetbins,mbttbaremclusterthresh,ttbaremclusterthresh);
    emclustergr->SetTitle("Efficiency versus rate");
    emclustergr->SetMarkerColor(coloremcluster);
    emclustergr->SetMarkerSize(1.0);
    emclustergr->SetMarkerStyle(20);
    //X-axis is BG
    emclustergr->GetXaxis()->SetTitle("minbias fraction pass");
    //emclustergr->GetXaxis()->SetTitle("2-jet Z3 fraction pass");
    //Y-axis is signal
    emclustergr->GetYaxis()->SetTitle("ttbar lept fraction pass");
    //emclustergr->GetYaxis()->SetTitle("jetjet Z3 fraction pass");
    emclustergr->Draw("P");

    TGraph *febgr = new TGraph(nmetbins,mbttbarfebthresh,ttbarfebthresh);
    febgr->SetTitle("Efficiency versus rate");
    febgr->SetMarkerColor(colorfeb);
    febgr->SetMarkerSize(1.0);
    febgr->SetMarkerStyle(20);
    //X-axis is BG
    febgr->GetXaxis()->SetTitle("minbias fraction pass");
    //febgr->GetXaxis()->SetTitle("2-jet Z3 fraction pass");
    //Y-axis is signal
    febgr->GetYaxis()->SetTitle("ttbar lept fraction pass");
    //febgr->GetYaxis()->SetTitle("jetjet z3 fraction pass");
    febgr->Draw("P");

    TGraph *febcalibgr = new TGraph(nmetbins,mbttbarfebcalibthresh,ttbarfebcalibthresh);
    febcalibgr->SetTitle("Efficiency versus rate");
    febcalibgr->SetMarkerColor(colorfebcalib);
    febcalibgr->SetMarkerSize(1.0);
    febcalibgr->SetMarkerStyle(20);
    //X-axis is BG
    febcalibgr->GetXaxis()->SetTitle("minbias fraction pass");
    //febcalibgr->GetXaxis()->SetTitle("2-jet Z3 fraction pass");
    //Y-axis is signal
    febcalibgr->GetYaxis()->SetTitle("ttbar lept fraction pass");
    //febcalibgr->GetYaxis()->SetTitle("jetjet z3 fraction pass");
    febcalibgr->Draw("P");

    TGraph *l1gr = new TGraph(nmetbins,mbttbarl1thresh,ttbarl1thresh);
    l1gr->SetTitle("Efficiency versus rate");
    l1gr->SetMarkerColor(colorl1);
    l1gr->SetMarkerSize(1.0);
    l1gr->SetMarkerStyle(20);
    //X-axis is BG
    l1gr->GetXaxis()->SetTitle("minbias fraction pass");
    //febcalibgr->GetXaxis()->SetTitle("2-jet Z3 fraction pass");
    //Y-axis is signal
    l1gr->GetYaxis()->SetTitle("ttbar lept fraction pass");
    //l1gr->GetYaxis()->SetTitle("jetjet z3 fraction pass");
    l1gr->Draw("P");

    tclcwgr->SetName("tclcwgr");
    emclustergr->SetName("emclustergr");
    febgr->SetName("febgr");
    febcalibgr->SetName("febcalibgr");
    l1gr->SetName("l1gr");
    efcellgr->SetName("efcellgr");

    TLegend* l=new TLegend(0.1,0.7,0.3,0.9);
    l->AddEntry("tclcwgr","tclcw","p");
    l->AddEntry("emclustergr","EM cluster","p");
    l->AddEntry("febgr","FEB","p");
    l->AddEntry("febcalibgr","FEB Had Calib","p");
    l->AddEntry("l1gr","L1","p");
    l->AddEntry("efcellgr","EF Cell","p");
    l->Draw();

}

  TCanvas *REFFINALMET = new TCanvas("REFFINALMET","REFFINALMET");
    TH1F* reffinalmet = new TH1F("reffinlamet"," RefFinal MET ",  nmetbins, metmin, metmax);
    reffinlamet->SetLineColor(2);
    reffinlamet->GetXaxis()->SetTitle("RefFinal MET [GeV]");
    reffinlamet->GetYaxis()->SetTitle("Number of Events");
    tree_AS->Draw("Olmet_reffinal/1000.>>reffinlamet");

  //put in next line not to do efficiency curves

  //General definitions for efficiency:
  TTree *thistree = (TTree*)firsttest->Get("tree_AS");
  Double_t reffinal_met,l1_met,l2_met,ef_met_cell,ef_met_tclcw;
  Int_t tbcid;
  TBranch *b_RefFinal_met = new TBranch();
  TBranch *b_L1_met = new TBranch();
  TBranch *b_L2_met = new TBranch();
  TBranch *b_EF_met_cell = new TBranch();
  TBranch *b_EF_met_tclcw = new TBranch();
  TBranch *b_tbcid = new TBranch();

  thistree->SetBranchAddress("Olmet_reffinal",&reffinal_met,&b_RefFinal_met);
  thistree->SetBranchAddress("Trig_l2met_Cell",&l1_met,&b_L1_met);
  thistree->SetBranchAddress("Trig_efmet_FEB",&l2_met,&b_L2_met);
  thistree->SetBranchAddress("Trig_efmet_Cell",&ef_met_cell,&b_EF_met_cell);
  thistree->SetBranchAddress("Trig_efmet_tclcw",&ef_met_tclcw,&b_EF_met_tclcw);
  thistree->SetBranchAddress("BCID",&tbcid,&b_tbcid);
  int nentries = thistree->GetEntries();
  bool pass;
  int nbins=30;
  Double_t reffinalmin=0.0;
  //Double_t reffinalmax=200.0;
  Double_t reffinalmax=300.0;
  
  TCanvas *L1METBG7test = new TCanvas("L1METBG7test","L1METBG7test");
    TH1F* l1metbg7test = new TH1F("l1metbg7test"," Level 1 MET Bunch Group 7", nmetbins, metmin, metmax );
    //TH1F* l1metbg7test = new TH1F("l1metbg7test"," Level 1 MET Bunch Group 7", 100., 0.0, 2.0e6 );
    l1metbg7test->SetLineColor(1);
    l1metbg7test->GetXaxis()->SetTitle("L1 MET Bunch Group 7 [GeV]");
    l1metbg7test->GetYaxis()->SetTitle("Number of Events");

    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        l1metbg7test->Fill(l1_met/1000.);
      }  
    }
    l1metbg7test->Draw();

  TCanvas *L1METCUMBG7test = new TCanvas("L1METCUMBG7test","L1METCUMBG7test");
    TH1F* l1metcumbg7test = new TH1F(*l1metbg7test);
    l1metcumbg7test->ComputeIntegral();
    Double_t* intl1metcumbg7test = l1metcumbg7test->GetIntegral();
    l1metcumbg7test->SetContent(intl1metcumbg7test);
    l1metcumbg7test->GetYaxis()->SetTitle("Cumulative count");
    l1metcumbg7test->Draw();

  TCanvas *L1METTHRESHBG7test = new TCanvas("L1METTHERSHBG7test","L1METTHRESHBG7test");
    TH1F* l1metthreshbg7test = new TH1F("l1metthreshbg7test","Fraction of bunch group 7 events above L1 Threshold", nmetbins, metmin, metmax);
    l1metthreshbg7test->GetXaxis()->SetTitle("L1 MET Bunch Group 7 [GeV]");
    l1metthreshbg7test->GetYaxis()->SetTitle("Fraction of events above threshold");
    Double_t* zvalbg7test, sumitbg7test, ratiobg7test;
    sumitbg7test=l1metbg7test->GetBinContent(nmetbins+1);
    Double_t* totnumbg7test = l1metbg7test->GetEntries();
    for (int jbg7test=nmetbins; jbg7test>0; jbg7test--) {
      zvalbg7test=l1metbg7test->GetBinContent(jbg7test);
      sumitbg7test += zvalbg7test;
      //std::cout << "number of events in bin   " << j << "  content   " << zval << "\n";
      ratiobg7test = sumitbg7test/totnumbg7test;
      l1metthreshbg7test->SetBinContent(jbg7test,ratiobg7test);
    }
    //zval=l1met->GetBinContent(0);
    //std::cout << "number of underflow events  " << zval << "\n";
    //zval=l1met->GetBinContent(31);
    //std::cout << "number of overflow events  " << zval << "\n";
    //zval=l1met->GetEntries();
    //std::cout << "number of entries = " << zval << "\n";
    l1metthreshbg7test->Draw();

  TCanvas *L1_10_EFFICIENCY = new TCanvas("L1_10_EFFICIENCY","L1_10_EFFICIENCY");
    TEfficiency *EFF_L1_10 = new TEfficiency
                   ("EFF_L1_10","L1_XE10 Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (l1_met/1000.0>10.) { 
          pass=true;
        } else {
          pass=false;
        }
        EFF_L1_10->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_L1_10->Draw();

  TCanvas *L1_20_EFFICIENCY = new TCanvas("L1_20_EFFICIENCY","L1_20_EFFICIENCY");
    TEfficiency *EFF_L1_20 = new TEfficiency
                   ("EFF_L1_20","L1_XE20 Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (l1_met/1000.0>20.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_L1_20->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_L1_20->Draw();

  TCanvas *L1_30_EFFICIENCY = new TCanvas("L1_30_EFFICIENCY","L1_30_EFFICIENCY");
    TEfficiency *EFF_L1_30 = new TEfficiency
                   ("EFF_L1_30","L1_XE30 Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (l1_met/1000.0>30.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_L1_30->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_L1_30->Draw();


  TCanvas *L1_40_EFFICIENCY = new TCanvas("L1_40_EFFICIENCY","L1_40_EFFICIENCY");
    TEfficiency *EFF_L1_40 = new TEfficiency
                   ("EFF_L1_40","L1_XE40 Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (l1_met/1000.0>40.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_L1_40->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_L1_40->Draw();

  TCanvas *L1_50_EFFICIENCY = new TCanvas("L1_50_EFFICIENCY","L1_50_EFFICIENCY");
    TEfficiency *EFF_L1_50 = new TEfficiency
                   ("EFF_L1_50","L1_XE50 Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (l1_met/1000.0>50.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_L1_50->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_L1_50->Draw();

  TCanvas *L1_60_EFFICIENCY = new TCanvas("L1_60_EFFICIENCY","L1_60_EFFICIENCY");
    TEfficiency *EFF_L1_60 = new TEfficiency
                   ("EFF_L1_60","L1_XE60 Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (l1_met/1000.0>60.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_L1_60->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_L1_60->Draw();

  TCanvas *L1_70_EFFICIENCY = new TCanvas("L1_70_EFFICIENCY","L1_70_EFFICIENCY");
    TEfficiency *EFF_L1_70 = new TEfficiency
                   ("EFF_L1_70","L1_XE70 Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (l1_met/1000.0>70.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_L1_70->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_L1_70->Draw();

  TCanvas *L1_80_EFFICIENCY = new TCanvas("L1_80_EFFICIENCY","L1_80_EFFICIENCY");
    TEfficiency *EFF_L1_80 = new TEfficiency
                   ("EFF_L1_80","L1_XE80 Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (l1_met/1000.0>80.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_L1_80->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_L1_80->Draw();

  TCanvas *L1_90_EFFICIENCY = new TCanvas("L1_90_EFFICIENCY","L1_90_EFFICIENCY");
    TEfficiency *EFF_L1_90 = new TEfficiency
                   ("EFF_L1_90","L1_XE90 Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (l1_met/1000.0>90.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_L1_90->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_L1_90->Draw();

  TCanvas *L2_10_EFFICIENCY = new TCanvas("L2_10_EFFICIENCY","L2_10_EFFICIENCY");
    TEfficiency *EFF_L2_10 = new TEfficiency
                   ("EFF_L2_10","L2_XE10 Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (l2_met/1000.0>10.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_L2_10->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_L2_10->Draw();

  TCanvas *L2_20_EFFICIENCY = new TCanvas("L2_20_EFFICIENCY","L2_20_EFFICIENCY");
    TEfficiency *EFF_L2_20 = new TEfficiency
                   ("EFF_L2_20","L2_XE20 Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (l2_met/1000.0>20.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_L2_20->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_L2_20->Draw();

  TCanvas *L2_30_EFFICIENCY = new TCanvas("L2_30_EFFICIENCY","L2_30_EFFICIENCY");
    TEfficiency *EFF_L2_30 = new TEfficiency
                   ("EFF_L2_30","L2_XE30 Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (l2_met/1000.0>30.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_L2_30->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_L2_30->Draw();

  TCanvas *L2_40_EFFICIENCY = new TCanvas("L2_40_EFFICIENCY","L2_40_EFFICIENCY");
    TEfficiency *EFF_L2_40 = new TEfficiency
                   ("EFF_L2_40","L2_XE40 Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (l2_met/1000.0>40.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_L2_40->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_L2_40->Draw();

  TCanvas *L2_50_EFFICIENCY = new TCanvas("L2_50_EFFICIENCY","L2_50_EFFICIENCY");
    TEfficiency *EFF_L2_50 = new TEfficiency
                   ("EFF_L2_50","L2_XE50 Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (l2_met/1000.0>50.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_L2_50->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_L2_50->Draw();

  TCanvas *L2_60_EFFICIENCY = new TCanvas("L2_60_EFFICIENCY","L2_60_EFFICIENCY");
    TEfficiency *EFF_L2_60 = new TEfficiency
                   ("EFF_L2_60","L2_XE60 Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (l2_met/1000.0>60.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_L2_60->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_L2_60->Draw();

  TCanvas *L2_70_EFFICIENCY = new TCanvas("L2_70_EFFICIENCY","L2_70_EFFICIENCY");
    TEfficiency *EFF_L2_70 = new TEfficiency
                   ("EFF_L2_70","L2_XE70 Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (l2_met/1000.0>70.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_L2_70->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_L2_70->Draw();

  TCanvas *L2_80_EFFICIENCY = new TCanvas("L2_80_EFFICIENCY","L2_80_EFFICIENCY");
    TEfficiency *EFF_L2_80 = new TEfficiency
                   ("EFF_L2_80","L2_XE80 Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (l2_met/1000.0>80.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_L2_80->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_L2_80->Draw();

  TCanvas *L2_90_EFFICIENCY = new TCanvas("L2_90_EFFICIENCY","L2_90_EFFICIENCY");
    TEfficiency *EFF_L2_90 = new TEfficiency
                   ("EFF_L2_90","L2_XE90 Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (l2_met/1000.0>90.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_L2_90->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_L2_90->Draw();

  TCanvas *L2_100_EFFICIENCY = new TCanvas("L2_100_EFFICIENCY","L2_100_EFFICIENCY");
    TEfficiency *EFF_L2_100 = new TEfficiency
                   ("EFF_L2_100","L2_XE100 Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (l2_met/1000.0>100.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_L2_100->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_L2_100->Draw();

  TCanvas *L2_110_EFFICIENCY = new TCanvas("L2_110_EFFICIENCY","L2_110_EFFICIENCY");
    TEfficiency *EFF_L2_110 = new TEfficiency
                   ("EFF_L2_110","L2_XE110 Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (l2_met/1000.0>110.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_L2_110->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_L2_110->Draw();

  TCanvas *L2_120_EFFICIENCY = new TCanvas("L2_120_EFFICIENCY","L2_120_EFFICIENCY");
    TEfficiency *EFF_L2_120 = new TEfficiency
                   ("EFF_L2_120","L2_XE120 Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (l2_met/1000.0>120.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_L2_120->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_L2_120->Draw();

  TCanvas *L2_130_EFFICIENCY = new TCanvas("L2_130_EFFICIENCY","L2_130_EFFICIENCY");
    TEfficiency *EFF_L2_130 = new TEfficiency
                   ("EFF_L2_130","L2_XE130 Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (l2_met/1000.0>130.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_L2_130->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_L2_130->Draw();

  TCanvas *EF_CELL_10_EFFICIENCY = new TCanvas("EF_CELL_10_EFFICIENCY","EF_CELL_10_EFFICIENCY");
    TEfficiency *EFF_EF_CELL_10 = new TEfficiency
                   ("EFF_EF_CELL_10","EF_XE10_CELL Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_cell/1000.0>10.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_CELL_10->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_CELL_10->Draw();

  TCanvas *EF_CELL_20_EFFICIENCY = new TCanvas("EF_CELL_20_EFFICIENCY","EF_CELL_20_EFFICIENCY");
    TEfficiency *EFF_EF_CELL_20 = new TEfficiency
                   ("EFF_EF_CELL_20","EF_XE20_CELL Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_cell/1000.0>20.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_CELL_20->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_CELL_20->Draw();

  TCanvas *EF_CELL_30_EFFICIENCY = new TCanvas("EF_CELL_30_EFFICIENCY","EF_CELL_30_EFFICIENCY");
    TEfficiency *EFF_EF_CELL_30 = new TEfficiency
                   ("EFF_EF_CELL_30","EF_XE30_CELL Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_cell/1000.0>30.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_CELL_30->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_CELL_30->Draw();

  TCanvas *EF_CELL_40_EFFICIENCY = new TCanvas("EF_CELL_40_EFFICIENCY","EF_CELL_40_EFFICIENCY");
    TEfficiency *EFF_EF_CELL_40 = new TEfficiency
                   ("EFF_EF_CELL_40","EF_XE40_CELL Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_cell/1000.0>40.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_CELL_40->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_CELL_40->Draw();

  TCanvas *EF_CELL_50_EFFICIENCY = new TCanvas("EF_CELL_50_EFFICIENCY","EF_CELL_50_EFFICIENCY");
    TEfficiency *EFF_EF_CELL_50 = new TEfficiency
                   ("EFF_EF_CELL_50","EF_XE50_CELL Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_cell/1000.0>50.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_CELL_50->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_CELL_50->Draw();

  TCanvas *EF_CELL_60_EFFICIENCY = new TCanvas("EF_CELL_60_EFFICIENCY","EF_CELL_60_EFFICIENCY");
    TEfficiency *EFF_EF_CELL_60 = new TEfficiency
                   ("EFF_EF_CELL_60","EF_XE60_CELL Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_cell/1000.0>60.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_CELL_60->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_CELL_60->Draw();

  TCanvas *EF_CELL_70_EFFICIENCY = new TCanvas("EF_CELL_70_EFFICIENCY","EF_CELL_70_EFFICIENCY");
    TEfficiency *EFF_EF_CELL_70 = new TEfficiency
                   ("EFF_EF_CELL_70","EF_XE70_CELL Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_cell/1000.0>70.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_CELL_70->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_CELL_70->Draw();

  TCanvas *EF_CELL_80_EFFICIENCY = new TCanvas("EF_CELL_80_EFFICIENCY","EF_CELL_80_EFFICIENCY");
    TEfficiency *EFF_EF_CELL_80 = new TEfficiency
                   ("EFF_EF_CELL_80","EF_XE80_CELL Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_cell/1000.0>80.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_CELL_80->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_CELL_80->Draw();

  TCanvas *EF_CELL_90_EFFICIENCY = new TCanvas("EF_CELL_90_EFFICIENCY","EF_CELL_90_EFFICIENCY");
    TEfficiency *EFF_EF_CELL_90 = new TEfficiency
                   ("EFF_EF_CELL_90","EF_XE90_CELL Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_cell/1000.0>90.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_CELL_90->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_CELL_90->Draw();

  TCanvas *EF_CELL_100_EFFICIENCY = new TCanvas("EF_CELL_100_EFFICIENCY","EF_CELL_100_EFFICIENCY");
    TEfficiency *EFF_EF_CELL_100 = new TEfficiency
                   ("EFF_EF_CELL_100","EF_XE100_CELL Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_cell/1000.0>100.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_CELL_100->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_CELL_100->Draw();

  TCanvas *EF_CELL_110_EFFICIENCY = new TCanvas("EF_CELL_110_EFFICIENCY","EF_CELL_110_EFFICIENCY");
    TEfficiency *EFF_EF_CELL_110 = new TEfficiency
                   ("EFF_EF_CELL_110","EF_XE110_CELL Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_cell/1000.0>110.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_CELL_110->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_CELL_110->Draw();

  TCanvas *EF_CELL_120_EFFICIENCY = new TCanvas("EF_CELL_120_EFFICIENCY","EF_CELL_120_EFFICIENCY");
    TEfficiency *EFF_EF_CELL_120 = new TEfficiency
                   ("EFF_EF_CELL_120","EF_XE120_CELL Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_cell/1000.0>120.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_CELL_120->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_CELL_120->Draw();

  TCanvas *EF_CELL_130_EFFICIENCY = new TCanvas("EF_CELL_130_EFFICIENCY","EF_CELL_130_EFFICIENCY");
    TEfficiency *EFF_EF_CELL_130 = new TEfficiency
                   ("EFF_EF_CELL_130","EF_XE130_CELL Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_cell/1000.0>130.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_CELL_130->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_CELL_130->Draw();

  TCanvas *EF_TCLCW_10_EFFICIENCY = new TCanvas("EF_TCLCW_10_EFFICIENCY","EF_TCLCW_10_EFFICIENCY");
    TEfficiency *EFF_EF_TCLCW_10 = new TEfficiency
                   ("EFF_EF_TCLCW_10","EF_XE10_TCLCW Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_tclcw/1000.0>10.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_TCLCW_10->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_TCLCW_10->Draw();

  TCanvas *EF_TCLCW_20_EFFICIENCY = new TCanvas("EF_TCLCW_20_EFFICIENCY","EF_TCLCW_20_EFFICIENCY");
    TEfficiency *EFF_EF_TCLCW_20 = new TEfficiency
                   ("EFF_EF_TCLCW_20","EF_XE20_TCLCW Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_tclcw/1000.0>20.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_TCLCW_20->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_TCLCW_20->Draw();

  TCanvas *EF_TCLCW_30_EFFICIENCY = new TCanvas("EF_TCLCW_30_EFFICIENCY","EF_TCLCW_30_EFFICIENCY");
    TEfficiency *EFF_EF_TCLCW_30 = new TEfficiency
                   ("EFF_EF_TCLCW_30","EF_XE30_TCLCW Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_tclcw/1000.0>30.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_TCLCW_30->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_TCLCW_30->Draw();

  TCanvas *EF_TCLCW_40_EFFICIENCY = new TCanvas("EF_TCLCW_40_EFFICIENCY","EF_TCLCW_40_EFFICIENCY");
    TEfficiency *EFF_EF_TCLCW_40 = new TEfficiency
                   ("EFF_EF_TCLCW_40","EF_XE40_TCLCW Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_tclcw/1000.0>40.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_TCLCW_40->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_TCLCW_40->Draw();

  TCanvas *EF_TCLCW_50_EFFICIENCY = new TCanvas("EF_TCLCW_50_EFFICIENCY","EF_TCLCW_50_EFFICIENCY");
    TEfficiency *EFF_EF_TCLCW_50 = new TEfficiency
                   ("EFF_EF_TCLCW_50","EF_XE50_TCLCW Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_tclcw/1000.0>50.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_TCLCW_50->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_TCLCW_50->Draw();

  TCanvas *EF_TCLCW_60_EFFICIENCY = new TCanvas("EF_TCLCW_60_EFFICIENCY","EF_TCLCW_60_EFFICIENCY");
    TEfficiency *EFF_EF_TCLCW_60 = new TEfficiency
                   ("EFF_EF_TCLCW_60","EF_XE60_TCLCW Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_tclcw/1000.0>60.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_TCLCW_60->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_TCLCW_60->Draw();

  TCanvas *EF_TCLCW_70_EFFICIENCY = new TCanvas("EF_TCLCW_70_EFFICIENCY","EF_TCLCW_70_EFFICIENCY");
    TEfficiency *EFF_EF_TCLCW_70 = new TEfficiency
                   ("EFF_EF_TCLCW_70","EF_XE70_TCLCW Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_tclcw/1000.0>70.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_TCLCW_70->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_TCLCW_70->Draw();

  TCanvas *EF_TCLCW_80_EFFICIENCY = new TCanvas("EF_TCLCW_80_EFFICIENCY","EF_TCLCW_80_EFFICIENCY");
    TEfficiency *EFF_EF_TCLCW_80 = new TEfficiency
                   ("EFF_EF_TCLCW_80","EF_XE80_TCLCW Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_tclcw/1000.0>80.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_TCLCW_80->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_TCLCW_80->Draw();

  TCanvas *EF_TCLCW_90_EFFICIENCY = new TCanvas("EF_TCLCW_90_EFFICIENCY","EF_TCLCW_90_EFFICIENCY");
    TEfficiency *EFF_EF_TCLCW_90 = new TEfficiency
                   ("EFF_EF_TCLCW_90","EF_XE90_TCLCW Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_tclcw/1000.0>90.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_TCLCW_90->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_TCLCW_90->Draw();

  TCanvas *EF_TCLCW_100_EFFICIENCY = new TCanvas("EF_TCLCW_100_EFFICIENCY","EF_TCLCW_100_EFFICIENCY");
    TEfficiency *EFF_EF_TCLCW_100 = new TEfficiency
                   ("EFF_EF_TCLCW_100","EF_XE100_TCLCW Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_tclcw/1000.0>100.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_TCLCW_100->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_TCLCW_100->Draw();

  TCanvas *EF_TCLCW_110_EFFICIENCY = new TCanvas("EF_TCLCW_110_EFFICIENCY","EF_TCLCW_110_EFFICIENCY");
    TEfficiency *EFF_EF_TCLCW_110 = new TEfficiency
                   ("EFF_EF_TCLCW_110","EF_XE110_TCLCW Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_tclcw/1000.0>110.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_TCLCW_110->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_TCLCW_110->Draw();

  TCanvas *EF_TCLCW_120_EFFICIENCY = new TCanvas("EF_TCLCW_120_EFFICIENCY","EF_TCLCW_120_EFFICIENCY");
    TEfficiency *EFF_EF_TCLCW_120 = new TEfficiency
                   ("EFF_EF_TCLCW_120","EF_XE120_TCLCW Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_tclcw/1000.0>120.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_TCLCW_120->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_TCLCW_120->Draw();

  TCanvas *EF_TCLCW_130_EFFICIENCY = new TCanvas("EF_TCLCW_130_EFFICIENCY","EF_TCLCW_130_EFFICIENCY");
    TEfficiency *EFF_EF_TCLCW_130 = new TEfficiency
                   ("EFF_EF_TCLCW_130","EF_XE130_TCLCW Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_tclcw/1000.0>130.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_TCLCW_130->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_TCLCW_130->Draw();

  TCanvas *EF_TCLCW_140_EFFICIENCY = new TCanvas("EF_TCLCW_140_EFFICIENCY","EF_TCLCW_140_EFFICIENCY");
    TEfficiency *EFF_EF_TCLCW_140 = new TEfficiency
                   ("EFF_EF_TCLCW_140","EF_XE140_TCLCW Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_tclcw/1000.0>140.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_TCLCW_140->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_TCLCW_140->Draw();

  TCanvas *EF_TCLCW_150_EFFICIENCY = new TCanvas("EF_TCLCW_150_EFFICIENCY","EF_TCLCW_150_EFFICIENCY");
    TEfficiency *EFF_EF_TCLCW_150 = new TEfficiency
                   ("EFF_EF_TCLCW_150","EF_XE150_TCLCW Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_tclcw/1000.0>150.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_TCLCW_150->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_TCLCW_150->Draw();

  TCanvas *EF_TCLCW_160_EFFICIENCY = new TCanvas("EF_TCLCW_160_EFFICIENCY","EF_TCLCW_160_EFFICIENCY");
    TEfficiency *EFF_EF_TCLCW_160 = new TEfficiency
                   ("EFF_EF_TCLCW_160","EF_XE160_TCLCW Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_tclcw/1000.0>160.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_TCLCW_160->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_TCLCW_160->Draw();

  TCanvas *EF_TCLCW_170_EFFICIENCY = new TCanvas("EF_TCLCW_170_EFFICIENCY","EF_TCLCW_170_EFFICIENCY");
    TEfficiency *EFF_EF_TCLCW_170 = new TEfficiency
                   ("EFF_EF_TCLCW_170","EF_XE170_TCLCW Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_tclcw/1000.0>170.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_TCLCW_170->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_TCLCW_170->Draw();

  TCanvas *EF_TCLCW_180_EFFICIENCY = new TCanvas("EF_TCLCW_180_EFFICIENCY","EF_TCLCW_180_EFFICIENCY");
    TEfficiency *EFF_EF_TCLCW_180 = new TEfficiency
                   ("EFF_EF_TCLCW_180","EF_XE180_TCLCW Efficiency;RefFinal MET [GeV];Efficiency",nbins,reffinalmin,reffinalmax);
    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if( (tbcid>bung1+delbung && tbcid< bung2) || (tbcid>bung2+delbung && tbcid< bung3) ||
          (tbcid>bung3+delbung && tbcid< bung4) || (tbcid>bung4+delbung && tbcid< bung5) ) {
        if (ef_met_tclcw/1000.0>180.) {
          pass=true;
        } else {
          pass=false;
        }
        EFF_EF_TCLCW_180->Fill(pass,reffinal_met/1000.0);
      } // end in correct bcid
    }
    EFF_EF_TCLCW_180->Draw();

  TCanvas *L1EFF = new TCanvas("L1EFF","L1EFF");
    EFF_L1_50->SetMarkerStyle(5);
    EFF_L1_50->SetMarkerColor(6);
    EFF_L1_50->SetLineColor(6);
    EFF_L1_50->Draw();
    EFF_L1_10->SetMarkerStyle(8);
    EFF_L1_10->SetMarkerSize(1.2);
    EFF_L1_10->SetMarkerColor(2);
    EFF_L1_10->SetLineColor(2);
    EFF_L1_10->Draw("same");
    EFF_L1_90->SetMarkerStyle(5);
    EFF_L1_90->SetMarkerColor(1);
    EFF_L1_90->SetLineColor(1);
    EFF_L1_90->Draw("same");
    EFF_L1_70->SetMarkerStyle(5);
    EFF_L1_70->SetMarkerColor(2);
    EFF_L1_70->SetLineColor(2);
    EFF_L1_70->Draw("same");
    //EFF_L1_50->SetMarkerStyle(5);
    //EFF_L1_50->SetMarkerColor(6);
    //EFF_L1_50->SetLineColor(6);
    //EFF_L1_50->Draw("same");
    EFF_L1_30->SetMarkerStyle(8);
    EFF_L1_30->SetMarkerSize(1.2);
    EFF_L1_30->SetMarkerColor(1);
    EFF_L1_30->SetLineColor(1);
    EFF_L1_30->Draw("same");
    //EFF_L1_10->SetMarkerStyle(8);
    //EFF_L1_10->SetMarkerSize(1.2);
    //EFF_L1_10->SetMarkerColor(2);
    //EFF_L1_10->SetLineColor(2);
    //EFF_L1_10->Draw("same");

  TCanvas *L2EFF = new TCanvas("L2EFF","L2EFF");
    EFF_L2_50->SetMarkerStyle(5);
    EFF_L2_50->SetMarkerColor(6);
    EFF_L2_50->SetLineColor(6);
    EFF_L2_50->Draw();
    EFF_L2_10->SetMarkerStyle(8);
    EFF_L2_10->SetMarkerSize(1.1);
    EFF_L2_10->SetMarkerColor(2);
    EFF_L2_10->SetLineColor(2);
    EFF_L2_10->Draw("same");
    EFF_L2_110->SetMarkerStyle(5);
    EFF_L2_110->SetMarkerSize(1.1);
    EFF_L2_110->SetMarkerColor(6);
    EFF_L2_110->SetLineColor(6);
    EFF_L2_110->Draw("same");
    EFF_L2_90->SetMarkerStyle(5);
    EFF_L2_90->SetMarkerColor(1);
    EFF_L2_90->SetLineColor(1);
    EFF_L2_90->Draw("same");
    EFF_L2_70->SetMarkerStyle(5);
    EFF_L2_70->SetMarkerColor(2);
    EFF_L2_70->SetLineColor(2);
    EFF_L2_70->Draw("same");
    //EFF_L2_50->SetMarkerStyle(5);
    //EFF_L2_50->SetMarkerColor(6);
    //EFF_L2_50->SetLineColor(6);
    //EFF_L2_50->Draw("same");
    EFF_L2_30->SetMarkerStyle(8);
    EFF_L2_30->SetMarkerSize(1.1);
    EFF_L2_30->SetMarkerColor(1);
    EFF_L2_30->SetLineColor(1);
    EFF_L2_30->Draw("same");
    //EFF_L2_10->SetMarkerStyle(8);
    //EFF_L2_10->SetMarkerSize(1.1);
    //EFF_L2_10->SetMarkerColor(2);
    //EFF_L2_10->SetLineColor(2);
    //EFF_L2_10->Draw("same");

  TCanvas *EFEFF = new TCanvas("EFEFF","EFEFF");
    EFF_EF_TCLCW_90->SetMarkerStyle(5);
    EFF_EF_TCLCW_90->SetMarkerColor(1);
    EFF_EF_TCLCW_90->SetLineColor(1);
    EFF_EF_TCLCW_90->Draw();
    EFF_EF_TCLCW_50->SetMarkerStyle(5);
    EFF_EF_TCLCW_50->SetMarkerColor(6);
    EFF_EF_TCLCW_50->SetLineColor(6);
    EFF_EF_TCLCW_50->Draw("same");
    EFF_EF_TCLCW_10->SetMarkerStyle(8);
    EFF_EF_TCLCW_10->SetMarkerSize(1.1);
    EFF_EF_TCLCW_10->SetMarkerColor(2);
    EFF_EF_TCLCW_10->SetLineColor(2);
    EFF_EF_TCLCW_10->Draw("same");
    EFF_EF_TCLCW_130->SetMarkerStyle(8);
    EFF_EF_TCLCW_130->SetMarkerSize(1.1);
    EFF_EF_TCLCW_130->SetMarkerColor(2);
    EFF_EF_TCLCW_130->SetLineColor(2);
    EFF_EF_TCLCW_130->Draw("same");
    EFF_EF_TCLCW_110->SetMarkerStyle(8);
    EFF_EF_TCLCW_110->SetMarkerSize(1.1);
    EFF_EF_TCLCW_110->SetMarkerColor(6);
    EFF_EF_TCLCW_110->SetLineColor(6);
    EFF_EF_TCLCW_110->Draw("same");
    //EFF_EF_TCLCW_90->SetMarkerStyle(5);
    //EFF_EF_TCLCW_90->SetMarkerColor(1);
    //EFF_EF_TCLCW_90->SetLineColor(1);
    //EFF_EF_TCLCW_90->Draw("same");
    EFF_EF_TCLCW_70->SetMarkerStyle(5);
    EFF_EF_TCLCW_70->SetMarkerColor(2);
    EFF_EF_TCLCW_70->SetLineColor(2);
    EFF_EF_TCLCW_70->Draw("same");
    //EFF_EF_TCLCW_50->SetMarkerStyle(5);
    //EFF_EF_TCLCW_50->SetMarkerColor(6);
    //EFF_EF_TCLCW_50->SetLineColor(6);
    //EFF_EF_TCLCW_50->Draw("same");
    EFF_EF_TCLCW_30->SetMarkerStyle(8);
    EFF_EF_TCLCW_30->SetMarkerSize(1.1);
    EFF_EF_TCLCW_30->SetMarkerColor(1);
    EFF_EF_TCLCW_30->SetLineColor(1);
    EFF_EF_TCLCW_30->Draw("same");
    //EFF_EF_TCLCW_10->SetMarkerStyle(8);
    //EFF_EF_TCLCW_10->SetMarkerSize(1.1);
    //EFF_EF_TCLCW_10->SetMarkerColor(2);
    //EFF_EF_TCLCW_10->SetLineColor(2);
    //EFF_EF_TCLCW_10->Draw("same");

}
