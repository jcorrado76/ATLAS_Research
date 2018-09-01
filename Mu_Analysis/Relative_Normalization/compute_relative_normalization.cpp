

void compute_relative_normalization(){
    TString relative_normalization_directory_name = "relative_normalized_curves";

    TFile* mu_file = TFile::Open("../Root_Files/mu_analysis.root");


    TH1F* metdistmubin1 = new TH1F("h1","mubin1");
    TH1F* metdistmubin2 = new TH1F("h2","mubin2");
    TH1F* metdistmubin3 = new TH1F("h3","mubin3");
    TH1F* metdistmubin4 = new TH1F("h4","mubin4");
    TH1F* metdistmubin5 = new TH1F("h5","mubin5");
    TH1F* metdistmubin6 = new TH1F("h6","mubin6");
    TH1F* metdistmubin7 = new TH1F("h7","mubin7");

    if ( mu_analysis_file->GetDirectory( relative_normalization_directory_name ){
        TDirectory* relative_norm_dir = mu_analysis_file->GetDirectory( relative_normalization_directory_name );

        relative_norm_dir->GetObject("",metdistmubin1);
        relative_norm_dir->GetObject("",metdistmubin2);
        relative_norm_dir->GetObject("",metdistmubin3);
        relative_norm_dir->GetObject("",metdistmubin4);
        relative_norm_dir->GetObject("",metdistmubin5);
        relative_norm_dir->GetObject("",metdistmubin6);
        relative_norm_dir->GetObject("",metdistmubin7);

    }else{
        std::cout << "Relative normalization directory already exsits" << std::endl;
        TDirectory* relative_norm_dir = mu_analysis_file->mkdir( relative_normalization_directory_name );
        std::cout << "Successfully got the relative normalization directory" << std::endl;
    }

