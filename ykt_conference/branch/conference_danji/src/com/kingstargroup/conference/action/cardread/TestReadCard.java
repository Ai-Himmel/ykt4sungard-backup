package com.kingstargroup.conference.action.cardread;

public class TestReadCard {

	/**
	 * File name: TestReadCard.java<br>
	 * Description: <br>
	 * Return: @param args<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      何林青    2007-1-18  <br>
	 * @author   何林青
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
