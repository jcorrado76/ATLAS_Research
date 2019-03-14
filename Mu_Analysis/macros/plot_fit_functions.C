
{
    TFile *mu_analysis_file = TFile::Open("mu_analysis.root", "READ");
    
    TObjArray* l1xe30_efficiency_fit_objects = 0;
    mu_analysis_file->GetObject( "l1xe30_efficiency_fit_objects" , l1xe30_efficiency_fit_objects );

    TF1* currentFitFunction = 0;

    TCanvas* fitfunctioncanvas = new TCanvas();
    TLegend* fitfunctionlegend = new TLegend();
    l = new TList();
    for ( int i = 0 ; i < l1xe30_efficiency_fit_objects->GetLast() ; i++ ){
        currentFitFunction = (TF1*)l1xe30_efficiency_fit_objects->At(i);
        if ( i == 0 ){
            currentFitFunction->Draw();
        }else{
            currentFitFunction->Draw("SAME");
        }
        fitfunctionlegend->AddEntry( currentFitFunction );
    }
    fitfunctionlegend->Draw("SAME");
}
