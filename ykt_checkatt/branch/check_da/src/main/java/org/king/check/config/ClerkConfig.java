package org.king.check.config;

public class ClerkConfig {
	public  final static int  isSeat=1;//坐班
	public final static int isNoSeat=2;//不坐班
	public final static int isExtra=1;//加班
	public final static int isNoExtra=0;//不加班
	public final static String isNoIrregularRest="0";//不是特殊休息
	public final static String isIrregularRest="1";//是特殊休息
	
	//hanjiwei add it 20061009
	public final static int ISOFFICE = 1;//坐班
	public final static int ISNOTOFFICE = 2;//不坐班
	public final static String ISOFFICE_NAME = "坐班";
	public final static String ISNOTOFFICE_NAME = "不坐班";

	//规定的上班时间和下班时间
	public final static String WORKONTIME = "080000";
	public final static String WORKOFFTIME = "173000";
		
}
