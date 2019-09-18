echo 'Welcome to ATLAS Open Data C++ framework'
echo 'Input your option now'
echo '1 = creates all output directories (recommended to do at the very beginning once)'
echo '0 = removes everything within those directories (in case you want to clean all outputs)'
read choice

if (( $choice == 1 )) ; then
  echo 'Creating the needed empty output directories in Analysis/NNAnalysis/** and in Plotting/histograms'
  mkdir Analysis/HZZAnalysis/Output_HZZAnalysis
  mkdir Analysis/HyyAnalysis/Output_HyyAnalysis
  mkdir Analysis/TTbarAnalysis/Output_TTbarAnalysis
  mkdir Analysis/WBosonAnalysis/Output_WBosonAnalysis
  mkdir Analysis/WZDiBosonAnalysis/Output_WZDiBosonAnalysis
  mkdir Analysis/ZBosonAnalysis/Output_ZBosonAnalysis
  mkdir Analysis/ZZDiBosonAnalysis/Output_ZZDiBosonAnalysis
  mkdir Plotting/histograms
elif  (( $choice == 0 )) ; then
  echo 'Removing everything within directories Analysis/NNAnalysis/Output_NNAnalysis/* and in Plotting/histograms/*'
  rm Analysis/HZZAnalysis/Output_HZZAnalysis/*
  rm Analysis/HyyAnalysis/Output_HyyAnalysis/*
  rm Analysis/TTbarAnalysis/Output_TTbarAnalysis/*
  rm Analysis/WBosonAnalysis/Output_WBosonAnalysis/*
  rm Analysis/WZDiBosonAnalysis/Output_WZDiBosonAnalysis/*
  rm Analysis/ZBosonAnalysis/Output_ZBosonAnalysis/*
  rm Analysis/ZZDiBosonAnalysis/Output_ZZDiBosonAnalysis/*
  rm Plotting/histograms/*
else
     echo "Invalid choice!"
fi





