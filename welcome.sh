#!/bin/bash
#######################################################
#                                                     # 
# Welcome to ATLAS 13 TeV Open Data C++ framework !!! #
#                                                     #   
#######################################################

echo 'Welcome to ATLAS 13 TeV Open Data C++ framework!!!'
echo 'Input your option now'
echo '1 = create all output directories (do it at the very beginning just once)'
echo '0 = remove all output directories (in case you want to clean and begin from zero)'
read choice

# names of 12 analyses
analysisCollection=("WBosonAnalysis" "ZBosonAnalysis" "TTbarAnalysis" "SingleTopAnalysis" "WZDiBosonAnalysis" "ZZDiBosonAnalysis" "HWWAnalysis" "HZZAnalysis" "ZTauTauAnalysis" "HyyAnalysis" "SUSYAnalysis" "ZPrimeBoostedAnalysis")

# creating the output directory for the Analyses codes
if (( $choice == 1 )) ; then
  for i in {0..11} ; do
    analysisName=${analysisCollection[$i]}
    echo "Creating the directory: Analysis/${analysisName}/Output_${analysisName}"
    mkdir Analysis/${analysisName}/Output_${analysisName}
  done

  echo "Creating the directory for the Plotting code: Plotting/histograms"
  mkdir Plotting/histograms

# removing everything within directories
elif  (( $choice == 0 )) ; then
  for i in {0..11} ; do
    analysisName=${analysisCollection[$i]}
    echo "Removing the directory: Analysis/${analysisName}/Output_${analysisName}"
    rm -rf Analysis/${analysisName}/Output_${analysisName}
  done

  echo "Removing the directory for the Plotting code: Plotting/histograms"
  rm -rf Plotting/histograms

else
     echo "Invalid choice!"
fi

########################




