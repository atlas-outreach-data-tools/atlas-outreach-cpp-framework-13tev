#######################################################
#                                                     # 
# Welcome to ATLAS 13 TeV Open Data C++ framework !!! #
#                                                     #   
#######################################################

choice=1

# names of 12 analyses
analysisCollection=("WBosonAnalysis" "ZBosonAnalysis" "TTbarAnalysis" "SingleTopAnalysis" "WZDiBosonAnalysis" "ZZDiBosonAnalysis" "HWWAnalysis" "HZZAnalysis" "ZTauTauAnalysis" "HyyAnalysis" "SUSYAnalysis" "ZPrimeBoostedAnalysis")

# creating the output directory for the Analyses codes
if (( $choice == 1 )) ; then
  for i in {0..11} ; do
    analysisName=${analysisCollection[$i]}
    mkdir Analysis/${analysisName}/Output_${analysisName}
  done

  mkdir Plotting/histograms

