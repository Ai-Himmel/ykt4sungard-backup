

/*************************************************************************
	module		:[‚c‚q‚`‚l”j‰óŽžó‘Ô‚ð•ÛŽ‚·‚é]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	ProtoType	:[void MEM_EscapeData(void){}]
	date		:[1998/05/08]
	author		:[–ØŒ³  C]
*************************************************************************/
void MEM_EscapeData (struct MEM_StoreData_t *StoreP,						/* Œ´e‚Ì’~Ïî•ñ‚ðŽw’è‚µ‚Ü‚· */
					 struct MEM_ExecData_t	*ExecP)						/* ’~Ï’†‚Ìƒf[ƒ^‚ðŠi”[‚·‚éƒGƒŠƒA‚ðŽw’è‚µ‚Ü‚· */
{

	CMN_DisableInterrupt();
	
	/* ƒƒ‚ƒŠŠÇ—‚ÅŽg—p‚µ‚Ä‚¢‚é‘åˆæ•Ï”‚Ì‘Ò”ð */
	BKUP_TopEmptyBlock = 				MEM_TopEmptyBlock;
	BKUP_EndBlock = 					MEM_EndBlock;
	BKUP_TotalStoreBlockCounter = 		MEM_TotalStoreBlockCounter;
	BKUP_TotalAvailableStoreBlkCnt = 	MEM_TotalAvailableStoreBlkCnt;
	BKUP_AvailableMaxFATArea = 			MEM_AvailableMaxFATArea;
	BKUP_DMAEndStatus = 				MEM_DMAEndStatus;
	BKUP_BlockCounterEndStatus = 		MEM_BlockCounterEndStatus;
	BKUP_ScanFlag = 					MEM_ScanFlag;

	/* ’~Ïî•ñƒf[ƒ^‚Ì‘Ò”ð */
	BKUP_StoreData.No = 		StoreP->No;
	BKUP_StoreData.Page = 		StoreP->Page;
	BKUP_StoreData.Item = 		StoreP->Item;
	BKUP_StoreData.Code = 		StoreP->Code;
	BKUP_StoreData.Mode = 		StoreP->Mode;
	BKUP_StoreData.Size = 		StoreP->Size;
	BKUP_StoreData.Area = 		StoreP->Area;
	BKUP_StoreData.Cassette = 	StoreP->Cassette;
	BKUP_StoreData.BoxNumber = 	StoreP->BoxNumber;
	BKUP_StoreData.Dummy = 		StoreP->Dummy;

	BKUP_ExecData.IndexNo1 = 	ExecP->IndexNo1;
	BKUP_ExecData.IndexNo2 = 	ExecP->IndexNo2;
	BKUP_ExecData.ExecBlockNo = ExecP->ExecBlockNo;
	BKUP_ExecData.NextBlockNo = ExecP->NextBlockNo;

	CMN_EnableInterrupt();

}

