{
    TFile* mu_analysis_file = TFile::Open("mu_analysis.root", "READ");
    TObjArray* l1xe30_efficiency_fit_objects = 0;
    TObjArray* l1xe50_efficiency_fit_objects = 0;

    mu_analysis_file->GetObject("l1xe30_efficiency_fit_objects", l1xe30_efficiency_fit_objects);
    mu_analysis_file->GetObject("l1xe50_efficiency_fit_objects", l1xe50_efficiency_fit_objects);
    mu_analysis_file->Close();

    std::ofstream myfile;
    myfile.open("fit_pars_table.tex");
    myfile << "\\begin{table}[ht]\n";
    myfile << "\\caption{Fit Parameter Table}\n";
    myfile << "\\centering\n";
    myfile << "\\begin{tabular}{|c|c|c|c|c|}\n";
    myfile << "\\hline\\hline\n";
    myfile << "a & b & $\\sigma$ & L1XE & $\\mu$ bin\\\\ \n";
    myfile << "\\hline\n";

    TF1* l1xe30_efficiency_fit;
    TF1* l1xe50_efficiency_fit;
    for (int i = 0; i <= l1xe30_efficiency_fit_objects->GetLast(); i++){
        l1xe30_efficiency_fit = ((TF1*)(l1xe30_efficiency_fit_objects->At(i)));
        l1xe50_efficiency_fit = ((TF1*)(l1xe50_efficiency_fit_objects->At(i)));
        myfile << l1xe30_efficiency_fit->GetParameter(0) << " & " << l1xe30_efficiency_fit->GetParameter(1) << " & " << l1xe30_efficiency_fit->GetParameter(2) << " & " << "30" << " & " << i << "\\\\ \n";
        myfile << l1xe50_efficiency_fit->GetParameter(0) << " & " << l1xe50_efficiency_fit->GetParameter(1) << " & " << l1xe50_efficiency_fit->GetParameter(2) << " & " << "50" << " & " << i << "\\\\ \n";
    }
    myfile << "\\hline\n";
    myfile << "\\end{tabular}\n";
    myfile << "\\end{table}\n";
    myfile.close();
}
