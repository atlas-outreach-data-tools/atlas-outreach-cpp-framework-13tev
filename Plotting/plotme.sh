#!/bin/bash
########################################
#
# General plotting script
#
########################################

# names of 12 analyses
analysisCollection=("WBosonAnalysis" "ZBosonAnalysis" "TTbarAnalysis" "SingleTopAnalysis" "WZDiBosonAnalysis" "ZZDiBosonAnalysis" "HWWAnalysis" "HZZAnalysis" "ZTauTauAnalysis" "HyyAnalysis" "SUSYAnalysis" "ZPrimeBoostedAnalysis" "TTbarDilepAnalysis")

# location of their outputs
outputpath=("../Analysis/WBosonAnalysis/Output_WBosonAnalysis" \
"../Analysis/ZBosonAnalysis/Output_ZBosonAnalysis" \
"../Analysis/TTbarAnalysis/Output_TTbarAnalysis" \
"../Analysis/SingleTopAnalysis/Output_SingleTopAnalysis" \
"../Analysis/WZDiBosonAnalysis/Output_WZDiBosonAnalysis" \
"../Analysis/ZZDiBosonAnalysis/Output_ZZDiBosonAnalysis" \
"../Analysis/HWWAnalysis/Output_HWWAnalysis" \
"../Analysis/HZZAnalysis/Output_HZZAnalysis" \
"../Analysis/ZTauTauAnalysis/Output_ZTauTauAnalysis" \
"../Analysis/HyyAnalysis/Output_HyyAnalysis" \
"../Analysis/SUSYAnalysis/Output_SUSYAnalysis" \
"../Analysis/ZPrimeBoostedAnalysis/Output_ZPrimeBoostedAnalysis"
"../Analysis/TTbarDilepAnalysis/Output_TTbarDilepAnalysis"
)

# begin
echo 'WELCOME!! Which analysis you want to plot?'
echo 'Input your option now (and click <ENTER>):'
echo '0 = WBosonAnalysis'
echo '1 = ZBosonAnalysis'
echo '2 = TTbarAnalysis'
echo '3 = SingleTopAnalysis'
echo '4 = WZDiBosonAnalysis'
echo '5 = ZZDiBosonAnalysis'
echo '6 = HWWAnalysis'
echo '7 = HZZAnalysis'
echo '8 = ZTauTauAnalysis'
echo '9 = HyyAnalysis'
echo '10 = SUSYAnalysis'
echo '11 = ZPrimeBoostedAnalysis'
echo '12 = TTbarDilepAnalysis'

read choice

# check choices
if [ $choice -ge 0 -a $choice -le 12 ]; then
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
