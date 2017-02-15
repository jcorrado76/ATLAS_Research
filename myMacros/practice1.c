{
		auto counter = new TH1F("count_rate", "Count Rate;N_{Counts};#occurencies", 100, -0.5, 15.5);
		auto averageCount = 3.6f;
		TRandom3 randomGenerator;
		for (int imeas = 0; imeas < 400; imeas++)
		{
			counter->Fill(randomGenerator.Poisson(averageCount));
		}
		auto c = new TCanvas();
		counter->Draw();

		auto c_norm = new TCanvas();
		counter->DrawNormalized();


		cout << "Moments of Distribution:\n"
			 << " - Mean = " << cnt_r_h->GetMean() << " +- "
			 << cnt_r_h->GetMeanError() << "\n"
			 << " - Std Dev = " << cnt_r_h->GetStdDev() << " +- "
			 << cnt_r_h->GetStdDevError() << "\n"
			 << " - Skewness = " << cnt_r_h->GetSkewness() << "\n"
			 << " - Kurtosis = " << cnt_r_h->GetKurtosis() << "\n";





}
