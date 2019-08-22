analysisCollection=("HZZAnalysis" "HWWAnalysis" "TTbarAnalysis" "WBosonAnalysis" "WZDiBosonAnalysis" "ZBosonAnalysis" "ZZDiBosonAnalysis" "ZTauTauAnalysis")
outputpath=("./Analysis/HZZAnalysis/Output_HZZAnalysis" \
"../Analysis/HWWAnalysis/Output_HWWAnalysis" \
"../Analysis/TTbarAnalysis/Output_TTbarAnalysis" \
"../Analysis/WBosonAnalysis/Output_WBosonAnalysis" \
"../Analysis/WZDiBosonAnalysis/Output_WZDiBosonAnalysis" \
"../Analysis/ZBosonAnalysis/Output_ZBosonAnalysis" \
"../Analysis/ZZDiBosonAnalysis/Output_ZZDiBosonAnalysis" \
"../Analysis/ZTauTauAnalysis/Output_ZTauTauAnalysis"
)

echo 'WELCOME!! Which analysis you want to plot?'
echo 'Input your option now (and click <ENTER>):'
echo '0 = HZZAnalysis'
echo '1 = HWWAnalysis'
echo '2 = TTbarAnalysis'
echo '3 = WBosonAnalysis'
echo '4 = WZDiBosonAnalysis'
echo '5 = ZBosonAnalysis'
echo '6 = ZZDiBosonAnalysis'
echo '7 = ZTauTauAnalysis'

read choice

if ((( $choice == 0) || ($choice == 1) || ($choice == 2) || ($choice == 3) || ($choice == 4) ||($choice == 5) ||($choice == 6) ||($choice == 7)   )) ; then
echo 'Choose your option about the analysis output path!' 
echo "If the location corresponds to ${outputpath[${choice}]}: type 0"
echo 'If you have a custom location path: type 1'
read option

  if (($option == 0)); then
    analysisName=${analysisCollection[${choice}]}
    analysisPath=${outputpath[${choice}]}

    root -l -b << EOF
	.L Plotting.cxx+
    	Plotting *m=new Plotting();
    	m->SetOption("$analysisName");
    	m->SetInputLocation("$analysisPath")
    	m->run()
    	.q
EOF

  elif (($option == 1)); then
    echo "Please enter your analysis output path:"
    read analysisPath

    root -l -b << EOF
    	.L Plotting.cxx+
    	Plotting *m=new Plotting();
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


