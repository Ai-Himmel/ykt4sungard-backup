package com.kingstargroup.conference.action.cardread;

public class TestReadCard {

	/**
	 * File name: TestReadCard.java<br>
	 * Description: <br>
	 * Return: @param args<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ������    2007-1-18  <br>
	 * @author   ������
	 * @version 
	 * @since 1.0
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		int a = ReadCardUtil.OpenSeriesPort(100,19200);
		System.out.println(a);
		System.out.println(ReadCardUtil.ReadCardNO());
//		System.out.print(ReadCardUtil.ReadCardNO());
		int b = ReadCardUtil.CloseSeriesPort();
		System.out.println(b);
		b = ReadCardUtil.CloseSeriesPort();
		System.out.println(b);
//		if(a==0){
//			System.out.print(ReadCardUtil.ReadCardNO());
//			ReadCardUtil.BeepTwice();
//			ReadCardUtil.BeepTwice();
//			ReadCardUtil.CloseSeriesPort();
//		}else{		
//			System.out.print("fail....."+a);
//			
//		}
		
		
	}

}
