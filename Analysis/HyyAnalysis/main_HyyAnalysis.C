//////////////////////////////////////////////////////////////////////////////////////////
// Creates a TChain to be used by the Analysis.C class
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"

void main_HyyAnalysis(int proof = 0, int option = 0)
{
    /* The URL to the CERN Open Data portal repository */
    // TString path = "root://eospublic.cern.ch//eos/opendata/atlas/rucio/opendata/";
    TString path = "atlas_data/";

    //***************************************************************************************************//
    // adding chains of all MC and data samples
    // option==0 will run all one by one
    // Currently 5 options for MC (2,3,4,5,6) and 1 for data (1) which can be run in parallel
    //***************************************************************************************************//

    TString skim = "GamGam";
    TString prefix = path + "ODEO_FEB2025_v0_" + skim + "_";

    if (option == 1 || option == 0)
    {

        // data15
        TChain *chain_data = new TChain("analysis");
        chain_data->AddFile(prefix + "data15_periodD." + skim + ".root");
        chain_data->AddFile(prefix + "data15_periodE." + skim + ".root");
        chain_data->AddFile(prefix + "data15_periodF." + skim + ".root");
        chain_data->AddFile(prefix + "data15_periodG." + skim + ".root");
        chain_data->AddFile(prefix + "data15_periodH." + skim + ".root");
        chain_data->AddFile(prefix + "data15_periodJ." + skim + ".root");

        // data16
        chain_data->AddFile(prefix + "data16_periodA." + skim + ".root");
        chain_data->AddFile(prefix + "data16_periodB." + skim + ".root");
        chain_data->AddFile(prefix + "data16_periodC." + skim + ".root");
        chain_data->AddFile(prefix + "data16_periodD." + skim + ".root");
        chain_data->AddFile(prefix + "data16_periodE." + skim + ".root");
        chain_data->AddFile(prefix + "data16_periodF." + skim + ".root");
        chain_data->AddFile(prefix + "data16_periodG." + skim + ".root");
        chain_data->AddFile(prefix + "data16_periodI." + skim + ".root");
        chain_data->AddFile(prefix + "data16_periodK." + skim + ".root");
        chain_data->AddFile(prefix + "data16_periodL." + skim + ".root");

        chain_data->Process("HyyAnalysis.C+", "data");
    } // option 1

    if (option == 2 || option == 0)
    {

        // Higgs MC, ggH production
        TChain *chain_ggH125_PowhegPythia = new TChain("analysis");
        chain_ggH125_PowhegPythia->AddFile(prefix + "mc_343981.PowhegPythia8EvtGen_NNLOPS_nnlo_30_ggH125_gamgam." + skim + ".root");
        chain_ggH125_PowhegPythia->Process("HyyAnalysis.C+", "PowhegPythia8EvtGen_NNLOPS_nnlo_30_ggH125_gamgam");

        TChain *chain_ggH125_PhH7EG = new TChain("analysis");
        chain_ggH125_PhH7EG->AddFile(prefix + "mc_346797.PhH7EG_H7UE_NNLOPS_nnlo_30_ggH125_gamgam." + skim + ".root");
        chain_ggH125_PhH7EG->Process("HyyAnalysis.C+", "PhH7EG_H7UE_NNLOPS_nnlo_30_ggH125_gamgam");

        // VBF Higgs production
        TChain *chain_VBFH125 = new TChain("analysis");
        chain_VBFH125->AddFile(prefix + "mc_346214.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_gamgam." + skim + ".root");
        chain_VBFH125->Process("HyyAnalysis.C+", "PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_gamgam");

        // WH production
        TChain *chain_WmH125 = new TChain("analysis");
        chain_WmH125->AddFile(prefix + "mc_345317.PowhegPythia8EvtGen_NNPDF30_AZNLO_WmH125J_Hyy_Wincl_MINLO." + skim + ".root");
        chain_WmH125->Process("HyyAnalysis.C+", "PowhegPythia8EvtGen_NNPDF30_AZNLO_WmH125J_Hyy_Wincl_MINLO");

        TChain *chain_WpH125 = new TChain("analysis");
        chain_WpH125->AddFile(prefix + "mc_345318.PowhegPythia8EvtGen_NNPDF30_AZNLO_WpH125J_Hyy_Wincl_MINLO." + skim + ".root");
        chain_WpH125->Process("HyyAnalysis.C+", "PowhegPythia8EvtGen_NNPDF30_AZNLO_WpH125J_Hyy_Wincl_MINLO");

        // ZH production
        TChain *chain_ZH125 = new TChain("analysis");
        chain_ZH125->AddFile(prefix + "mc_345319.PowhegPythia8EvtGen_NNPDF30_AZNLO_ZH125J_Hyy_Zincl_MINLO." + skim + ".root");
        chain_ZH125->Process("HyyAnalysis.C+", "PowhegPythia8EvtGen_NNPDF30_AZNLO_ZH125J_Hyy_Zincl_MINLO");

        // ttH production
        TChain *chain_ttH125_PowhegPythia = new TChain("analysis");
        chain_ttH125_PowhegPythia->AddFile(prefix + "mc_346525.PowhegPythia8EvtGen_A14NNPDF23_NNPDF30ME_ttH125_gamgam." + skim + ".root");
        chain_ttH125_PowhegPythia->Process("HyyAnalysis.C+", "PowhegPythia8EvtGen_A14NNPDF23_NNPDF30ME_ttH125_gamgam");

        TChain *chain_ttH125_PowhegHerwig = new TChain("analysis");
        chain_ttH125_PowhegHerwig->AddFile(prefix + "mc_346526.PowhegHerwig7EvtGen_H7UE_NNPDF30ME_ttH125_gamgam." + skim + ".root");
        chain_ttH125_PowhegHerwig->Process("HyyAnalysis.C+", "PowhegHerwig7EvtGen_H7UE_NNPDF30ME_ttH125_gamgam");

        TChain *chain_ttH125_aMcAtNloHerwig = new TChain("analysis");
        chain_ttH125_aMcAtNloHerwig->AddFile(prefix + "mc_346601.aMcAtNloHerwig7EvtGen_MEN30NLO_ttH125_gamgam." + skim + ".root");
        chain_ttH125_aMcAtNloHerwig->Process("HyyAnalysis.C+", "aMcAtNloHerwig7EvtGen_MEN30NLO_ttH125_gamgam");
    }
    // option 2
}
