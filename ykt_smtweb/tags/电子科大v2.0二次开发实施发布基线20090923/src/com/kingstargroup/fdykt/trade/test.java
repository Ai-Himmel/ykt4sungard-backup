package com.kingstargroup.fdykt.trade;

public class test {

	/**
	 * Method name: main<br>
	 * Description: <br>
	 * Return: void<br>
	 * Args: @param args
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ������    Jun 3, 2008  <br>
	 * @author   ������
	 * @version 
	 * @since 1.0
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String sbankacc = "0000-1002";
		if(sbankacc.indexOf("-")!=-1){
			sbankacc = sbankacc.substring(sbankacc.indexOf("-"));
		}
		String sb_1_str = Float.toString(Float.parseFloat(sbankacc)/100);
		System.out.println(sb_1_str);
	}

}
