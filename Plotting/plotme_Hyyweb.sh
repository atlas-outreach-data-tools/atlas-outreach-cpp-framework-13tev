########################################
#
# General plotting script
#
########################################

# names of 12 analyses
analysisCollection=("WBosonAnalysis" "ZBosonAnalysis" "TTbarAnalysis" "SingleTopAnalysis" "WZDiBosonAnalysis" "ZZDiBosonAnalysis" "HWWAnalysis" "HZZAnalysis" "ZTauTauAnalysis" "HyyAnalysis" "SUSYAnalysis" "ZPrimeBoostedAnalysis")

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
)

# begin
echo 'WELCOME!! Which analysis you want to plot?'
choice=9

# check choices
if (( ($choice == 0) || ($choice == 1) || ($choice == 2) || ($choice == 3) ||($choice == 4) ||($choice == 5) ||($choice == 6) || ($choice == 7) || ($choice == 8) || ($choice == 9) ||($choice == 10) ||($choice == 11) )) ; then
    
  analysisName=${analysisCollection[${choice}]}
  echo "Will use ${outputpath[${choice}]} as the location of the ${analysisName} output!"
  option=0

  if (($option == 0)); then
    analysisPath=${outputpath[${choice}]}

    # run main command
    root -l -b << EOF
	.L Plotting.cxx+
    	Plotting *m=new Plotting();
	m->SetLumi(10064);
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
