

void compute_relative_normalization(){
    TString relative_normalization_directory_name = "relative_normalized_curves";
    // TH1 OBJECTS DO NOT BELONG TO TFILE SCOPE. THEY WILL STAY
    TH1::AddDirectory(false);

    TFile* mu_analysis_file = TFile::Open("../Root_Files/mu_analysis.root");

    Float_t metlow = 0.0;
    Float_t methigh = 300.0;
    Int_t nbins = 100;

    TH1F* metdistmubin1 = new TH1F("h1","mubin1", nbins ,metlow,methigh);
    TH1F* metdistmubin2 = new TH1F("h2","mubin2", nbins, metlow, methigh);
    TH1F* metdistmubin3 = new TH1F("h3","mubin3", nbins, metlow, methigh);
    TH1F* metdistmubin4 = new TH1F("h4","mubin4", nbins, metlow, methigh);
    TH1F* metdistmubin5 = new TH1F("h5","mubin5", nbins, metlow, methigh);
    TH1F* metdistmubin6 = new TH1F("h6","mubin6", nbins, metlow, methigh);
    TH1F* metdistmubin7 = new TH1F("h7","mubin7", nbins, metlow, methigh);

    TH1F* correctedmetdistmubin1 = new TH1F("correctedh1","correctedmubin1", nbins, metlow, methigh);
    TH1F* correctedmetdistmubin2 = new TH1F("correctedh2","correctedmubin2", nbins, metlow, methigh);
    TH1F* correctedmetdistmubin3 = new TH1F("correctedh3","correctedmubin3", nbins, metlow, methigh);
    TH1F* correctedmetdistmubin4 = new TH1F("correctedh4","correctedmubin4", nbins, metlow, methigh);
    TH1F* correctedmetdistmubin5 = new TH1F("correctedh5","correctedmubin5", nbins, metlow, methigh);
    TH1F* correctedmetdistmubin6 = new TH1F("correctedh6","correctedmubin6", nbins, metlow, methigh);
    TH1F* correctedmetdistmubin7 = new TH1F("correctedh7","correctedmubin7", nbins, metlow, methigh);

    // open the zerobias distribution directory 
    TDirectory* zb_dir = mu_analysis_file->GetDirectory( "zb_met" );
    // read the met distributions from file 
    zb_dir->GetObject("metmu0thru10",metdistmubin1);
    zb_dir->GetObject("metmu10thru20",metdistmubin2);
    zb_dir->GetObject("metmu20thru30",metdistmubin3);
    zb_dir->GetObject("metmu30thru40",metdistmubin4);
    zb_dir->GetObject("metmu40thru50",metdistmubin5);
    zb_dir->GetObject("metmu50thru60",metdistmubin6);
    zb_dir->GetObject("metmu60thru70",metdistmubin7);

    // open the corrected dist zb directory
    TDirectory* zb_corrected_dir = mu_analysis_file->GetDirectory( "corrected_met" );
    // read the corrected met distributions from file 
    zb_corrected_dir->GetObject("correctedmetmu0thru10",correctedmetdistmubin1);
    zb_corrected_dir->GetObject("correctedmetmu10thru20",correctedmetdistmubin2);
    zb_corrected_dir->GetObject("correctedmetmu20thru30",correctedmetdistmubin3);
    zb_corrected_dir->GetObject("correctedmetmu30thru40",correctedmetdistmubin4);
    zb_corrected_dir->GetObject("correctedmetmu40thru50",correctedmetdistmubin5);
    zb_corrected_dir->GetObject("correctedmetmu50thru60",correctedmetdistmubin6);
    zb_corrected_dir->GetObject("correctedmetmu60thru70",correctedmetdistmubin7);

    // if relative normalization directory already exists
    if ( mu_analysis_file->cd( relative_normalization_directory_name )){
        // get the relative normalization directory 
        TDirectory* relative_norm_dir = mu_analysis_file->GetDirectory( relative_normalization_directory_name );

    }else{
        // else if the directory doesn't already exist 
        std::cout << "Relative normalization directory does not already exsit" << std::endl;
        // make a new one 
        TDirectory* relative_norm_dir = mu_analysis_file->mkdir( relative_normalization_directory_name );
        std::cout << "Successfully created the relative normalization directory" << std::endl;
    }


    // pick a value of MET to use to normalize the distributions to 
    Float_t thresh = 100.0;
    Int_t thresh_bin = metdistmubin1->GetBin( thresh );

    Int_t initial_bin_content = metdistmubin1->GetBinContent( thresh_bin );
    Int_t initial_bin_content_corrected = correctedmetdistmubin1->GetBinContent( thresh_bin );

    correctedmetdistmubin1->Scale( initial_bin_content / initial_bin_content_corrected );

    correctedmetdistmubin1->Draw();
    metdistmubin1->Draw("SAME");

}

