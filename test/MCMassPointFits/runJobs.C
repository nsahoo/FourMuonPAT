#include "myntupleAnaInclV.C"

void runJobs()
{

	TChain * chain = new TChain("mkcands/X_data",""); 
  	// TChain * chain = new TChain("X_data","");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_10_1_GPv.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_11_1_F5Z.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_12_1_GzA.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_13_1_zrp.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_14_1_WAJ.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_15_1_qhR.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_16_1_g2L.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_17_1_7Bk.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_18_1_di0.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_19_1_yAe.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_1_1_hod.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_20_1_0Wp.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_21_1_wvc.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_22_1_pSl.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_23_1_nUU.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_24_1_Y7o.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_25_1_c93.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_26_1_6Pl.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_27_1_fk7.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_28_1_jq5.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_29_1_vxi.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_2_1_IH1.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_30_1_AJX.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_31_1_E1z.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_32_1_Ji1.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_33_1_e9Q.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_34_1_O0U.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_35_1_Dic.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_36_1_YL4.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_37_1_Uro.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_38_1_x1z.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_39_1_lQ3.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_3_1_Tn1.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_40_1_pyu.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_41_1_4wm.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_42_1_eoH.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_43_1_uYy.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_44_1_Q4F.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_45_1_81u.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_46_1_wUL.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_47_1_Dex.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_48_1_taA.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_49_1_cwM.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_4_1_vhA.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_50_1_JL5.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_51_1_bhU.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_52_1_hCa.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_53_1_uuV.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_54_1_Isk.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_55_1_buZ.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_56_1_mmU.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_57_1_XsY.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_58_1_4js.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_59_1_q2f.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_5_1_ZTo.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_60_1_8JN.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_61_1_SWJ.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_62_1_yzw.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_63_1_GcL.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_64_1_MCG.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_6_1_CNv.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_7_1_ZZV.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_8_1_pZG.root");
	chain->Add("/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m50p0/Run2012OMC_ntuple_9_1_GCh.root");

	myntuple _myntuple(chain);  
  	//myntuple _myntuple;
	_myntuple.Loop();

}
