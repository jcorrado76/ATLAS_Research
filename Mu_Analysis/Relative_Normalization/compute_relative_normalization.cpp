

void compute_relative_normalization(){
    TString relative_normalization_directory_name = "relative_normalized_curves";

    TFile* mu_file = TFile::Open("../Root_Files/mu_analysis.root");

    if ( mu_analysis_file->GetDirectory("relative_normalized_curves"){
        TDirectory* relative_norm_dir = mu_analysis_file->GetDirectory( relative_normalization_directory_name );

        efficiency_dir->GetObject("metmu0thru10Efficiency",efficiencyObjectMu0thru10);
        efficiency_dir->GetObject("metmu10thru20Efficiency",efficiencyObjectMu10thru20);
        efficiency_dir->GetObject("metmu20thru30Efficiency",efficiencyObjectMu20thru30);
        efficiency_dir->GetObject("metmu30thru40Efficiency",efficiencyObjectMu30thru40);
        efficiency_dir->GetObject("metmu40thru50Efficiency",efficiencyObjectMu40thru50);
        efficiency_dir->GetObject("metmu50thru60Efficiency",efficiencyObjectMu50thru60);
        efficiency_dir->GetObject("metmu60thru70Efficiency",efficiencyObjectMu60thru70);

    }else{
        std::cout << "Relative normalization directory already exsits" << std::endl;
        TDirectory* relative_norm_dir = mu_analysis_file->mkdir( relative_normalization_directory_name );
        std::cout << "Successfully got the relative normalization directory" << std::endl;
}

