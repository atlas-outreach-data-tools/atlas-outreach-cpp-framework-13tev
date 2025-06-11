#!/bin/bash
########################################
#
# General plotting script
#
########################################

# names of 4 available analyses
analysisCollection=("HWWAnalysis" "ZTauTauAnalysis" "TTbarAnalysis" "TTbarDilepAnalysis")

# location of their outputs
outputpath=("../Analysis/HWWAnalysis/Output_HWWAnalysis" \
"../Analysis/ZTauTauAnalysis/Output_ZTauTauAnalysis" \
"../Analysis/TTbarAnalysis/Output_TTbarAnalysis" \
"../Analysis/TTbarDilepAnalysis/Output_TTbarDilepAnalysis"
)

# begin
echo 'WELCOME!! Which analysis you want to plot?'
echo 'Input your option now (and click <ENTER>):'
echo '0 = HWWAnalysis'
echo '1 = ZTauTauAnalysis'
echo '2 = TTbarAnalysis'
echo '3 = TTbarDilepAnalysis'

read choice

# check choices
if [ $choice -ge 0 -a $choice -le 3 ]; then
  analysisName=${analysisCollection[${choice}]}
  echo "Now, choose the location of the ${analysisName} output!"
  echo "If the location corresponds to ${outputpath[${choice}]}: type 0"
  echo 'If you have a custom location path: type 1'
  read option

  if (($option == 0)); then
    analysisPath=${outputpath[${choice}]}

    # run main command
    root -l -b << EOF
	.L Plotting.cxx+
    	Plotting *m=new Plotting();
	m->SetLumi(36000);
	m->SetOption("$analysisName");
    	m->SetInputLocation("$analysisPath")
    	m->run()
    	.q
EOF

  elif (($option == 1)); then
    echo "Please enter your analysis output path (and click <ENTER>):"
    read analysisPath

    root -l -b << EOF
    	.L Plotting.cxx+
    	Plotting *m=new Plotting();
	m->SetLumi(36000);
    	m->SetOption("$analysisName");
    	m->SetInputLocation("$analysisPath")
    	m->run()
    	.q
EOF

  else
    echo "Invalid option!"
  fi


else
     echo "Analysis choice not found!!"
fi
########################################
