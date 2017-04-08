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
  //int nmetbins=80;
  Double_t metmin=0.0;
  //Double_t metmax=400.0;
  int nmetbins=100;
  Double_t metmax=500.0;

  int colorefcell75 = 1;
  int colorefcell80 = 2;
  int colormht110 =4;
  int colortclcw = 11;
  int colorl1 = 8;
  int coloroffrecal = 6;
  int coloroffrecalnomu = 8;
  int colorlochadtopo = 28;
  int colorreffinal = 46;

  double l1metcut = 50.0;
  //double l1metcut = 0.0;

  //TFile *firsttest = TFile::Open("test/data16_13TeV.root");
  //TFile *firsttest = TFile::Open("ExpressMuons2016.12runs.root");
  //TFile *firsttest = TFile::Open("ExpressMuons2016.m1620.Run304178.root");
  //TFile *firsttest = TFile::Open("ExpressMuons2016.m1620.Run304337.root");
  TFile *firsttest = TFile::Open("ExpressMuons2016newanalysis.11runs.root");

  //General definitions for efficiency:
  TTree *thistree = (TTree*)firsttest->Get("tree");
  Float_t l1_met,l2_met_feb,ef_met_cell,ef_met_tclcw,ef_met_emcluster, ef_met_mht;
  Float_t offrecal_met, offrecal_mex, offrecal_mey, offrecalmuon_mex, offrecalmuon_mey;
  Int_t tflag_mu24med, tflag_cleancuts, tflag_recalbroke;

  Int_t tbcid;
  TBranch *b_L1_met = new TBranch();
  TBranch *b_L2_met_feb = new TBranch();
  TBranch *b_EF_met_cell = new TBranch();
  TBranch *b_EF_met_tclcw = new TBranch();
  TBranch *b_EF_met_emcluster = new TBranch();
  TBranch *b_EF_met_mht = new TBranch();
  TBranch *b_OffRecal_met = new TBranch();
  TBranch *b_OffRecal_mex = new TBranch();
  TBranch *b_OffRecal_mey = new TBranch();
  TBranch *b_OffRecalMuon_mex = new TBranch();
  TBranch *b_OffRecalMuon_mey = new TBranch(); 

  TBranch *b_TFLAG_mu24med = new TBranch();
  TBranch *b_TFLAG_cleancuts = new TBranch();
  TBranch *b_TFLAG_recalbroke = new TBranch();

  TBranch *b_tbcid = new TBranch();


  thistree->SetBranchAddress("metl1",&l1_met,&b_L1_met);
  thistree->SetBranchAddress("metl2feb",&l2_met_feb,&b_L2_met_feb);
  thistree->SetBranchAddress("metcell",&ef_met_cell,&b_EF_met_cell);
  thistree->SetBranchAddress("mettopocl",&ef_met_tclcw,&b_EF_met_tclcw);
  thistree->SetBranchAddress("mettopoclem",&ef_met_emcluster,&b_EF_met_emcluster);
  thistree->SetBranchAddress("metmht",&ef_met_mht,&b_EF_met_mht);
  thistree->SetBranchAddress("metoffrecal",&offrecal_met,&b_OffRecal_met);
  thistree->SetBranchAddress("mexoffrecal",&offrecal_mex,&b_OffRecal_mex);
  thistree->SetBranchAddress("meyoffrecal",&offrecal_mey,&b_OffRecal_mey);
  thistree->SetBranchAddress("mexoffrecalmuon",&offrecalmuon_mex,&b_OffRecalMuon_mex);
  thistree->SetBranchAddress("meyoffrecalmuon",&offrecalmuon_mey,&b_OffRecalMuon_mey);

  thistree->SetBranchAddress("passmu24med", &tflag_mu24med, &b_TFLAG_mu24med);
  thistree->SetBranchAddress("passcleancuts", &tflag_cleancuts, &b_TFLAG_cleancuts);
  thistree->SetBranchAddress("recalbroke", &tflag_recalbroke, &b_TFLAG_recalbroke);

  int nentries = thistree->GetEntries();
  bool pass;
  //int nbins=80;
  int nbins=60;
  Double_t reffinalmin=0.0;
  //Double_t reffinalmax=400.0;
  Double_t reffinalmax=300.0;

  //int nbins=70;
  //Double_t reffinalmax=700.0;


  TCanvas *L1_EFFICIENCY50 = new TCanvas("L1_EFFICIENCY50","L1_EFFICIENCY50");
    TEfficiency *L1_efficiency50 = new TEfficiency
                   ("L1_efficiency50","Algorithm Efficiency;Offline Recal MET No Muons [GeV];Efficiency",nbins,reffinalmin,reffinalmax);

    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if(tflag_mu24med>0.1 && tflag_cleancuts>0.1 && tflag_recalbroke<0.1) {
        if (l1_met>l1metcut) {
          pass=true;
        } else {
          pass=false;
        }
        //Offline recalibrated MET:
        //EFF_CELL_matched75->Fill(pass,offrecal_met);
        //Offline recalibrated MET Calorimeter only:
        L1_efficiency50->Fill(pass,sqrt( ( (offrecal_mex-offrecalmuon_mex)*(offrecal_mex-offrecalmuon_mex) ) +
                                            ( (offrecal_mey-offrecalmuon_mey)*(offrecal_mey-offrecalmuon_mey) ) ));

      }
    }
    L1_efficiency50->SetMarkerStyle(20);
    L1_efficiency50->SetMarkerSize(1.1);
    L1_efficiency50->SetMarkerColor(colorl1);
    L1_efficiency50->SetLineColor(colorl1);
    L1_efficiency50->Draw();

  TCanvas *CELL_MATCHED_EFFICIENCY75 = new TCanvas("CELL_MATCHED_EFFICIENCY75","CELL_MATCHED_EFFICIENCY75");
    TEfficiency *EFF_CELL_matched75 = new TEfficiency
                   ("EFF_CELL_matched75","Algorithm Efficiency;Offline Recal MET No Muons [GeV];Efficiency",nbins,reffinalmin,reffinalmax);

    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if(tflag_mu24med>0.1 && tflag_cleancuts>0.1 && tflag_recalbroke<0.1) {
        if (l1_met>l1metcut && ef_met_cell>75.) {
          pass=true;
        } else {
          pass=false;
        }
        //Offline recalibrated MET:
        //EFF_CELL_matched75->Fill(pass,offrecal_met);
        //Offline recalibrated MET Calorimeter only:
        EFF_CELL_matched75->Fill(pass,sqrt( ( (offrecal_mex-offrecalmuon_mex)*(offrecal_mex-offrecalmuon_mex) ) +
                                            ( (offrecal_mey-offrecalmuon_mey)*(offrecal_mey-offrecalmuon_mey) ) ));

      }
    }
    EFF_CELL_matched75->SetMarkerStyle(20);
    EFF_CELL_matched75->SetMarkerSize(1.1);
    EFF_CELL_matched75->SetMarkerColor(colorefcell75);
    EFF_CELL_matched75->SetLineColor(colorefcell75);
    EFF_CELL_matched75->Draw();
  
  TCanvas *CELL_MATCHED_EFFICIENCY80 = new TCanvas("CELL_MATCHED_EFFICIENCY80","CELL_MATCHED_EFFICIENCY80");
    TEfficiency *EFF_CELL_matched80 = new TEfficiency
                   ("EFF_CELL_matched80","Algorithm Efficiency;Offline Recal MET No Muons [GeV];Efficiency",nbins,reffinalmin,reffinalmax);

    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if(tflag_mu24med>0.1 && tflag_cleancuts>0.1 && tflag_recalbroke<0.1) {
        if (l1_met>l1metcut && ef_met_cell>80.) {
          pass=true;
        } else {
          pass=false;
        }
        //Offline recalibrated MET:
        //EFF_CELL_matched80->Fill(pass,offrecal_met);
        //Offline recalibrated MET Calorimeter only:
        EFF_CELL_matched80->Fill(pass,sqrt(((offrecal_mex-offrecalmuon_mex)*(offrecal_mex-offrecalmuon_mex))+((offrecal_mey-offrecalmuon_mey)*(offrecal_mey-offrecalmuon_mey))) );
      }
    }
    EFF_CELL_matched80->SetMarkerStyle(20);
    EFF_CELL_matched80->SetMarkerSize(1.1);
    EFF_CELL_matched80->SetMarkerColor(colorefcell80);
    EFF_CELL_matched80->SetLineColor(colorefcell80);
    EFF_CELL_matched80->Draw();

  TCanvas *MHT_MATCHED_EFFICIENCY110 = new TCanvas("MHT_MATCHED_EFFICIENCY110","MET_MATCHED_EFFICIENCY110");
    TEfficiency *EFF_MHT_matched110 = new TEfficiency
                   ("EFF_MHT_matched110","Algorithm Efficiency;Offline Recal MET No Muons [GeV];Efficiency",nbins,reffinalmin,reffinalmax);

    for (int i=0; i<nentries; i++) {
      thistree->GetEntry(i);
      if(tflag_mu24med>0.1 && tflag_cleancuts>0.1 && tflag_recalbroke<0.1) {
        if (l1_met>l1metcut && ef_met_mht>110.) {
          pass=true;
        } else {
          pass=false;
        }
        //Offline recalibrated MET:
        //EFF_MHT_matched110->Fill(pass,offrecal_met);
        //Offline recalibrated MET Calorimeter only:
        EFF_MHT_matched110->Fill(pass,sqrt(((offrecal_mex-offrecalmuon_mex)*(offrecal_mex-offrecalmuon_mex))+((offrecal_mey-offrecalmuon_mey)*(offrecal_mey-offrecalmuon_mey))) );
      }
    }
    EFF_MHT_matched110->SetMarkerStyle(20);
    EFF_MHT_matched110->SetMarkerSize(1.1);
    EFF_MHT_matched110->SetMarkerColor(colormht110);
    EFF_MHT_matched110->SetLineColor(colormht110);
    EFF_MHT_matched110->Draw();

  TCanvas *COMBINEDEFFICIENCY = new TCanvas("COMBINEDEFFICIENCY","COMBINEDEFFICIENCY");
    EFF_CELL_matched75->Draw();
    EFF_CELL_matched80->Draw("sameP");
    EFF_MHT_matched110->Draw("sameP");
    L1_efficiency50->Draw("sameP");
    TLegend* lcombeff=new TLegend(0.1,0.7,0.4,0.9);
    lcombeff->AddEntry("L1_efficiency50","L1 50 GeV","p");
    lcombeff->AddEntry("EFF_CELL_matched75","Cell 75 GeV","p");
    lcombeff->AddEntry("EFF_CELL_matched80","Cell 80 GeV","p");
    lcombeff->AddEntry("EFF_MHT_matched110","MHT 110 GeV","p");
    lcombeff->Draw();

  TCanvas *OFFRECALMET = new TCanvas("OFFRECALMET","OFFRECALMET");
    TH1F* offrecalmet = new TH1F("offrecalmet"," Offline Recalibrated MET ",  nmetbins, metmin, metmax);
    offrecalmet->SetLineColor(coloroffrecal);
    offrecalmet->GetXaxis()->SetTitle("Offline Recal. MET [GeV]");
    offrecalmet->GetYaxis()->SetTitle("Number of Events");
    tree->Draw("metoffrecal>>offrecalmet","passmu24med>0.1 && recalbroke<0.1 &&passcleancuts>0.5");
    gPad->Update();
    TPaveStats *statboxmetoffrecal = (TPaveStats*)offrecalmet->GetListOfFunctions()->FindObject("stats");
    offrecalmet->GetListOfFunctions()->Remove(statboxmetoffrecal);
    offrecalmet->SetStats(0);
    statboxmetoffrecal->SetTextColor(coloroffrecal);
    statboxmetoffrecal->SetY1NDC(0.5); //new y start position
    statboxmetoffrecal->SetY2NDC(0.7); //new y end position
    statboxmetoffrecal->Draw();

  TCanvas *OFFRECALNOMUMET = new TCanvas("OFFRECALNOMUMET","OFFRECALNOMUMET");
    TH1F* offrecalmetnomu = new TH1F("offrecalmetnomu"," Offline Recalibrated MET without Muons",  nmetbins, metmin, metmax);
    offrecalmetnomu->SetLineColor(coloroffrecalnomu);
    offrecalmetnomu->GetXaxis()->SetTitle("Offline Recal. MET no Muons [GeV]");
    offrecalmetnomu->GetYaxis()->SetTitle("Number of Events");
    tree->Draw("sqrt(((mexoffrecal-mexoffrecalmuon)*(mexoffrecal-mexoffrecalmuon))+((meyoffrecal-meyoffrecalmuon)*(meyoffrecal-meyoffrecalmuon)))>>offrecalmetnomu","passmu24med>0.1 && recalbroke<0.1 &&passcleancuts>0.5");
    gPad->Update();
    TPaveStats *statboxmetoffrecalnomu = (TPaveStats*)offrecalmetnomu->GetListOfFunctions()->FindObject("stats");
    offrecalmetnomu->GetListOfFunctions()->Remove(statboxmetoffrecalnomu);
    offrecalmetnomu->SetStats(0);
    statboxmetoffrecalnomu->SetTextColor(coloroffrecalnomu);
    statboxmetoffrecalnomu->SetY1NDC(0.7); //new y start position
    statboxmetoffrecalnomu->SetY2NDC(0.9); //new y end position
    statboxmetoffrecalnomu->Draw();

  TCanvas *COMBINEDOFFNOMUOFF = new TCanvas("COMBINEDOFFNOMUOFF","COMBINEDOFFNOMUOFF");
    offrecalmet->Draw();
    statboxmetoffrecal->Draw("same");    
    offrecalmetnomu->Draw("same");
    statboxmetoffrecalnomu->Draw("same");
    TLegend* lcombdiff=new TLegend(0.6,0.7,0.9,0.9);
    lcombdiff->AddEntry("offrecalmet","Off Recal ","l");
    lcombdiff->AddEntry("offrecalmetnomu","Off Recal No Muons","l");
    lcombdiff->Draw();

  TCanvas *OFFRECALNOMUMETDIFFCELL = new TCanvas("OFFRECALNOMUMETDIFFCELL","OFFRECALNOMUMETDIFFCELL");
    TH1F* offrecalnomumetdiffcell = new TH1F("offrecalnomumetdiffcell"," Algorithm MET minus Offline Recalibrated MET without Muons",  80, -200., 200.);
    offrecalnomumetdiffcell->SetLineColor(colorefcell75);
    offrecalnomumetdiffcell->GetXaxis()->SetTitle("Algorithm MET minus Offline Recal. MET no Muons [GeV]");
    offrecalnomumetdiffcell->GetYaxis()->SetTitle("Number of Events");
    tree->Draw("metcell-sqrt(((mexoffrecal-mexoffrecalmuon)*(mexoffrecal-mexoffrecalmuon))+((meyoffrecal-meyoffrecalmuon)*(meyoffrecal-meyoffrecalmuon)))>>offrecalnomumetdiffcell","passmu24med>0.1 && recalbroke<0.1 &&passcleancuts>0.5");
    gPad->Update();
    TPaveStats *statboxoffrecalnomumetdiffcell = (TPaveStats*)offrecalnomumetdiffcell->GetListOfFunctions()->FindObject("stats");
    offrecalnomumetdiffcell->GetListOfFunctions()->Remove(statboxoffrecalnomumetdiffcell);
    offrecalnomumetdiffcell->SetStats(0);
    statboxoffrecalnomumetdiffcell->SetTextColor(colorefcell75);
    statboxoffrecalnomumetdiffcell->SetX1NDC(0.7); //new x start position
    statboxoffrecalnomumetdiffcell->SetX2NDC(0.9); //new x end position
    statboxoffrecalnomumetdiffcell->SetY1NDC(0.5); //new y start position
    statboxoffrecalnomumetdiffcell->SetY2NDC(0.7); //new y end position
    statboxoffrecalnomumetdiffcell->Draw();

  TCanvas *OFFRECALNOMUMETDIFFMHT = new TCanvas("OFFRECALNOMUMETDIFFMHT","OFFRECALNOMUMETDIFFMHT");
    TH1F* offrecalnomumetdiffmht = new TH1F("offrecalnomumetdiffmht"," Algorithm MET minus Offline Recalibrated MET without Muons",  80, -200., 200.);
    offrecalnomumetdiffmht->SetLineColor(colormht110);
    offrecalnomumetdiffmht->GetXaxis()->SetTitle("Agorithm MET minus Offline Recal. MET no Muons [GeV]");
    offrecalnomumetdiffmht->GetYaxis()->SetTitle("Number of Events");
    tree->Draw("metmht-sqrt(((mexoffrecal-mexoffrecalmuon)*(mexoffrecal-mexoffrecalmuon))+((meyoffrecal-meyoffrecalmuon)*(meyoffrecal-meyoffrecalmuon)))>>offrecalnomumetdiffmht","passmu24med>0.1 && recalbroke<0.1 &&passcleancuts>0.5");
    gPad->Update();
    TPaveStats *statboxoffrecalnomumetdiffmht = (TPaveStats*)offrecalnomumetdiffmht->GetListOfFunctions()->FindObject("stats");
    offrecalnomumetdiffmht->GetListOfFunctions()->Remove(statboxoffrecalnomumetdiffmht);
    offrecalnomumetdiffmht->SetStats(0);
    statboxoffrecalnomumetdiffmht->SetTextColor(colormht110);
    statboxoffrecalnomumetdiffmht->SetX1NDC(0.7); //new x start position
    statboxoffrecalnomumetdiffmht->SetX2NDC(0.9); //new x end position
    statboxoffrecalnomumetdiffmht->SetY1NDC(0.3); //new y start position
    statboxoffrecalnomumetdiffmht->SetY2NDC(0.5); //new y end position
    statboxoffrecalnomumetdiffmht->Draw();

  TCanvas *COMBINEDDIFF = new TCanvas("COMBINEDDIFF","COMBINEDDIFF");
    //offrecalnomumetdiffcell->Draw();
    offrecalnomumetdiffmht->Draw();
    offrecalnomumetdiffcell->Draw("same");
    statboxoffrecalnomumetdiffcell->Draw();
    statboxoffrecalnomumetdiffmht->Draw();
    TLegend* lcombdiff=new TLegend(0.6,0.7,0.9,0.9);
    lcombdiff->AddEntry("offrecalnomumetdiffcell","Cell minus Off Recal ","l");
    lcombdiff->AddEntry("offrecalnomumetdiffmht","MHT minus Off Recal ","l");
    lcombdiff->Draw();

  /*
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
    */

  /*
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
  */

}

