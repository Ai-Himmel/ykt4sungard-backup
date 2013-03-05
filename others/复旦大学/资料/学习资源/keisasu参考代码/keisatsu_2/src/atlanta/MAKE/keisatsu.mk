#------------------------------------------------------------------------
#	警察FAX   大機能モジュール(LNK)結合、全体メイクファイル
#	1996/11/09		By M.Kotnai
#------------------------------------------------------------------------
#
#-----------------------------------------------------------------------------
#	ｺﾏﾝﾄﾞ名を定義
#-----------------------------------------------------------------------------
LNK			= lnk /subcommand=\src\atlanta\make\keisatsu.sub
#
#-----------------------------------------------------------------------------
#	オブジェクトディレクトリを定義
#-----------------------------------------------------------------------------
OBJECT		= \src\atlanta\$(MODEL)\work\$(COUNTRY)
#
#-----------------------------------------------------------------------------
#	大機能ﾓｼﾞｭｰﾙのﾘﾝｸを定義
#-----------------------------------------------------------------------------
#
$(OBJECT)\keisatsu.lnk:	  \src\atlanta\make\keisatsu.SUB	\
			$(OBJECT)\data.lnk			\
			$(OBJECT)\shdata2.lnk		\
			$(OBJECT)\table.lnk			\
			$(OBJECT)\shtable2.lnk		\
			$(OBJECT)\lstword.lnk		\
			$(OBJECT)\oprword.lnk		\
			$(OBJECT)\ini2.lnk			\
			$(OBJECT)\int2.lnk			\
			$(OBJECT)\mon2.lnk			\
			$(OBJECT)\man.lnk			\
			$(OBJECT)\dma.lnk			\
			$(OBJECT)\cmn.lnk			\
			$(OBJECT)\mem.lnk			\
			$(OBJECT)\cdc.lnk			\
			$(OBJECT)\scd2.lnk			\
			$(OBJECT)\fcm.lnk			\
			$(OBJECT)\fcm_comp.lnk		\
			$(OBJECT)\fcm_v34.lnk		\
			$(OBJECT)\opr.lnk			\
			$(OBJECT)\lst.lnk			\
#			$(OBJECT)\pat.lnk			\
#			$(OBJECT)\scn.lnk			\
#			$(OBJECT)\idp.lnk			\
			$(OBJECT)\ncu.lnk			\
			$(OBJECT)\print.lnk			\
			$(OBJECT)\mdm.lnk			\
			$(OBJECT)\s1.lnk			\
			$(OBJECT)\atd.lnk			\
#			$(OBJECT)\dpr.lnk			\
#			$(OBJECT)\rot.lnk			\
			$(OBJECT)\multi.lnk			\
#			$(OBJECT)\cl1.lnk			\
			$(OBJECT)\flash.lnk			\
			$(OBJECT)\iu_data.lnk			\
			$(OBJECT)\scn_hino.lnk			\
			$(OBJECT)\nd.lnk			\
			\src\memsw\sh\msw.lnk
		$(LNK)
