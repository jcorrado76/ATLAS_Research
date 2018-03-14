{
    std::cout << "JBurr_Dataset_Analysis_Env" << std::endl;

    TString include_path = gSystem->GetIncludePath();

    if (!include_path.Contains("-I$jburr/include")){
            gSystem->AddIncludePath("-I$jburr/include");
            }


    if (gSystem->CompileMacro("src/GenerateTableDifferences.cpp",
                          "k-",
                          "libTableDiff",
                          "lib") ==0) {return false;}

    if (gSystem->CompileMacro("src/Plot2016Data.cpp",
                          "k-",
                          "libPlot2016Data",
                          "lib") ==0) {return false;}
    if (gSystem->CompileMacro("src/FindingPassrndm.cpp",
                          "k-",
                          "libFindingPassrndm",
                          "lib") ==0) {return false;}
    if (gSystem->CompileMacro("src/CompareRunNumbers.cpp",
                          "k-",
                          "libCompareRunNumbers",
                          "lib") ==0) {return false;}
}
