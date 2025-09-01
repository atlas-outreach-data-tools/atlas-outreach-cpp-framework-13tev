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

# names of 4 analyses
analysisCollection="HWWAnalysis ZTauTauAnalysis TTbarAnalysis TTbarDilepAnalysis HTauTauAnalysis"

# creating the output directory for the Analyses codes
if (( $choice == 1 )) ; then
    for anAnalysis in $analysisCollection; do
	echo "Creating the directory: Analysis/${anAnalysis}/Output_${anAnalysis}"
	mkdir Analysis/${anAnalysis}/Output_${anAnalysis}
    done

    echo "Creating the directory for the Plotting code: Plotting/histograms"
    mkdir Plotting/histograms

# removing everything within directories
elif  (( $choice == 0 )) ; then
    for anAnalysis in $analysisCollection; do
	echo "Removing the directory: Analysis/${anAnalysis}/Output_${anAnalysis}"
	rm -rf Analysis/${anAnalysis}/Output_${anAnalysis}
    done

    echo "Removing the directory for the Plotting code: Plotting/histograms"
    rm -rf Plotting/histograms

else
     echo "Invalid choice!"
fi

########################
