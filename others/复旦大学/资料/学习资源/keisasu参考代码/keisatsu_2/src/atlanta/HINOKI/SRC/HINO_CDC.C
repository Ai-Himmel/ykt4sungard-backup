/*************************************************************************
	module		:[エンコードタスク]
	function	:[
		1.イメージバッファからＲＬバッファにデータを転送する。（イメージ->ＲＬ変換）
		2.エンコードを行う。
		3.上記の処理を１ページ行い、最終ラインをエンコード終了すると、ＲＴＣをセットする。
	]
	return		:[]
	common		:[]
	condition	:[
		子タスク：	ImageToRlConvertTask()	<Small>
					EncodeExecuteTask()		<Small>
	]
	comment		:[]
	machine		:[V53]
	language	:[CH38(V.2.0B)]
	keyword		:[SCDC]
	ProtoType	:[void SCDC_EncodeTask(void){}]
	date		:[1998/09/30]
	author		:[木元  修]
*************************************************************************/
void SCDC_Encodetask(void)
{
	/* 内部変数宣言 */
	MESSAGE_t	*MessageControl;
	MESSAGE_t	EncodeTaskMessage;
	UWORD Item;
	UWORD Message;
	UBYTE	wait_convert;
	UBYTE	wait_encode;
	UBYTE	convert_p;
	UBYTE	encode_p;
	UBYTE	buffer_p[3];

	EncodeTaskMessage.Item = FROM_SCD_ENCODE;
	wait_convert = FALSE;
	wait_encode = TRUE;
	convert_p = 0;
	encode_p = 0;
	buffer_p[0] = FREE;
	buffer_p[1] = FREE;
	buffer_p[2] = FREE;

	/* イメージをＲＬに変換するタスク生成 */
	cre_tsk( &tskno_SCDC_ImageToRlConvertTask, TSK_SCD_IMAGETORLCONVERTTASK, 0 );

	/* ＲＬを符号に変換（エンコード）するタスク生成 */
	cre_tsk( &tskno_SCDC_EncodeExecuteTask, TSK_SCD_ENCODEEXECUTETASK, 0 );
	
	/* 読み取り処理からのエンコードスタート待ち */
	do {
		rcv_msg(mbxno.SCD_EncodeTask, &MessageControl); /** タスクからメッセージ受信 */
	} while (!(MessageControl->Item == FROM_SCANNER));

	/* ImageToRLConvertTaskに1ライン処理実行を起動 */
	buffer_p[convert_p] = CONVERT;
	EnocodeTaskMessage.Message = CONVERT_START;
	snd_msg(mbxno.SCDC_EncodeExeTask, &EnocdeTaskMessage);

	while(1) {
		/* メッセージ待ち */
		rcv_msg(mbxno.SCD_EncodeTask, &MessageControl); /** タスクからメッセージ受信 */
		Item = MessageControl->Item;
		Message = MessageControl->Message;

		/* メッセージ処理 */
		switch(Item) {
		case FROM_CONVERT:	/* ImageToRlConvertTaskより */
			buffer_p[convert_p] = DATA_SET;

			if (wait_encode == TRUE) {
				/* エンコード処理起動 */
				wait_encode = FALSE;
				buffer_p[encode_p] = ENCODE;
				EnocodeTaskMessage.Message = ENCODE_START;
				snd_msg(mbxno.SCDC_EncodeExeTask, &EnocdeTaskMessage);
			}

			convet_p ++;
			if (convert_p == BUF_LINE_MAX) {
				convert_p = 0;
			}
			/* ＲＬバッファに開きが無い？ */
			if (buffer_p[convert_p] == FREE) {
				/* 次のラインの処理起動 */
				wait_convert = FALSE;
				buffer_p[convert_p] = CONVERT;
				EnocodeTaskMessage.Message = ENCODE_START;
				snd_msg(mbxno.SCDC_EncodeExeTask, &EnocdeTaskMessage);
			}
			else {
				/* あくのを待つ */
				wait_convert = TRUE;
			}
			break;
		case FROM_ENCODE:	/* EncodeExecuteTaskより */
			buffer_p[encode_p] = REFERENCE_LINE;
			if (encode_p != 0) {
				buffer_p[(encode_p - 1)] = FREE;
			}
			else {
				buffer_p[(BUF_LINE_MAX - 1)] = FREE;
			}

			if (encode_method == MH) {
				buffer_p[encode_p] = FREE;
			}

			encode_p ++;
			if (encode_p == BUF_LINE_MAX) {
				encode_p = 0;
			}

			/* 全データエンコード終了していれば、ＲＴＣ書き込み */

			/* ＲＬデータが貼り終わっていない？ */
			if (buffer_p[encode_p] == DATA_SET) {
				/* エンコード処理起動 */
				wait_encode = FALSE;
				buffer_p[encode_p] = ENCODE;
				EnocodeTaskMessage.Message = ENCODE_START;
				snd_msg(mbxno.SCDC_EncodeExeTask, &EnocdeTaskMessage);
			}
			else {
				/* 貼られるのを待つ */
				wait_encode = TRUE;
			}
			break;
		case FROM_SCANNER:	/* 読み取り処理から */
			/* 停止キーが押された？ */
			break;
		default:
			/* ここへ来ることはありえないはず!! */
			break;
		}
	}
}


/*************************************************************************
	module		:[イメージをＲＬに変換]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[CH38(V.2.0B)]
	keyword		:[SCDC]
	ProtoType	:[void SCDC_ImageToRlConvertTask(void){}]
	date		:[1998/09/30]
	author		:[木元  修]
*************************************************************************/
void SCDC_ImageToRlConvertTask(void)
{
}


/*************************************************************************
	module		:[1ラインエンコード]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[CH38(V.2.0B)]
	keyword		:[SCDC]
	ProtoType	:[void SCDC_EncodeExecutetask{}]
	date		:[1998/09/30]
	author		:[木元  修]
*************************************************************************/
void SCDC_EncodeExecutetask(void)
{
}


