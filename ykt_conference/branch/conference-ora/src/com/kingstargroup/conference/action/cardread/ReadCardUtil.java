package com.kingstargroup.conference.action.cardread;

public class ReadCardUtil {
	
	static { 

		System.loadLibrary("ReadCardUtil"); 

		} 
	
	public static int PortStat = 0 ;
	
	/**
		* File name: ReadCardUtil.java<br>
		* Description: 开串口<br>
		* Return: @return 0 打开成功<br>
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-1-18  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public native static int OpenSeriesPort(int port,int frequency);
	
	
	/**
		* File name: ReadCardUtil.java<br>
		* Description: 关闭串口<br>
		* Return: @return<br>
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-1-18  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public native static int CloseSeriesPort();
	 
	/**
		* File name: ReadCardUtil.java<br>
		* Description: 读卡<br>
		* Return: @return<br>
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-1-18  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public native static String ReadCardNO();
	
	/**
		* File name: ReadCardUtil.java<br>
		* Description: 鸣叫一次<br>
		* Return: <br>
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-1-18  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public native static int BeepOnce();
	
	/**
		* File name: ReadCardUtil.java<br>
		* Description: 鸣叫两次<br>
		* Return: <br>
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-1-18  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public native static int BeepTwice();
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.print(ReadCardNO());
	}


}
