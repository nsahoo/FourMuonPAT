#include "myntupleAnaInclV.C"

void runJobs()
{
	TChain * chain = new TChain("mkcands/X_data","");
	// TChain * chain = new TChain("X_data","");

	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_1.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_10.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_11.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_12.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_13.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_14.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_15.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_16.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_17.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_18.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_19.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_2.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_20.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_21.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_22.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_23.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_24.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_25.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_26.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_27.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_28.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_29.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_3.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_30.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_31.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_32.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_33.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_34.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_35.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_36.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_37.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_38.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_39.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_4.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_40.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_41.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_42.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_43.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_44.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_45.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_46.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_47.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_48.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_49.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_5.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_50.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_51.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_52.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_53.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_54.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_55.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_56.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_57.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_58.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_59.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_6.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_60.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_61.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_62.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_63.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_64.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_65.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_66.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_67.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_68.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_69.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_7.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_70.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_71.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_72.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_73.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_74.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_75.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_76.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_77.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_78.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_79.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_8.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5_doMC/Run2012OMC_ntuple_9.root");


	myntuple _myntuple(chain);
	_myntuple.Loop();
	
}
