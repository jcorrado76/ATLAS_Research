{
    std::cout << "Parallelized_JBurr_Dataset_Analysis_Env" << std::endl;

    TString include_path = gSystem->GetIncludePath();

    if (!include_path.Contains("-I$jburr/Parallelized_Analysis/include")){
            gSystem->AddIncludePath("-I$jburr/Parallelized_Analysis/include");
            }


    if (gSystem->CompileMacro("src/Jburr_Selector.C",
                          "k-",
                          "libJburrSelector",
                          "lib") ==0) {return false;}

    if (gSystem->CompileMacro("src/Mincer_Selector.C",
                          "k-",
                          "libMincerSelector",
                          "lib") ==0) {return false;}

    gSystem->Load("lib/libMincerSelector.so");
    gSystem->Load("lib/libJburrSelector.so");


    if (gSystem->CompileMacro("src/Plot_Driver.cpp",
                          "k-",
                          "libPlotDriver",
                          "lib") ==0) {return false;}
}
