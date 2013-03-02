package com.kingstargroup.conference.action.cardread;

public class ReadCardUtil {
	
	static { 

		System.loadLibrary("ReadCardUtil"); 

		} 
	
	public static int PortStat = 0 ;
	
	/**
		* File name: ReadCardUtil.java<br>
		* Description: ������<br>
		* Return: @return 0 �򿪳ɹ�<br>
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-1-18  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public native static int OpenSeriesPort(int port,int frequency);
	
	
	/**
		* File name: ReadCardUtil.java<br>
		* Description: �رմ���<br>
		* Return: @return<br>
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-1-18  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public native static int CloseSeriesPort();
	 
	/**
		* File name: ReadCardUtil.java<br>
		* Description: ����<br>
		* Return: @return<br>
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-1-18  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public native static String ReadCardNO();
	
	/**
		* File name: ReadCardUtil.java<br>
		* Description: ����һ��<br>
		* Return: <br>
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-1-18  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public native static int BeepOnce();
	
	/**
		* File name: ReadCardUtil.java<br>
		* Description: ��������<br>
		* Return: <br>
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-1-18  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public native static int BeepTwice();
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.print(ReadCardNO());
	}


}
