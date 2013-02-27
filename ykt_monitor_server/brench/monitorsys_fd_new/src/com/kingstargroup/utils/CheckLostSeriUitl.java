package com.kingstargroup.utils;

import java.util.ArrayList;
import java.util.List;

/**<br>
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. <br>
 * File name: CheckLostSeriUitl.java<br>
 * Description: ѭ�����ȱʧ��ˮ��
 * Modify History����Change Log��:  <br>
 * �������ͣ��������޸ĵȣ�   ��������     ������    �������ݼ���<br>
 * ����  				 2005-10-21  ������    ѭ�����ȱʧ��ˮ
 * <p>
 *
 * @author      ������
 * @version     1.0
 * @since       1.0
 */
public class CheckLostSeriUitl {

	public static List sequenceCheckLostSerial(List list){
		List returnSerialNo = new ArrayList();
		int[] tempSerialNo = null;
		if (list!=null){
			Object [] tmpAry = list.toArray();
			tempSerialNo = new int[tmpAry.length];
			for(int i = 0;i < tmpAry.length;i++)
			{
				tempSerialNo[i] = Integer.parseInt(tmpAry[i].toString());
			}
			int index = 0;
			for(int i= 0; i<(list.size()-1); i++){
				int checkFlag =tempSerialNo[i]-tempSerialNo[i+1];
				if(1!=checkFlag){
					for(int j=1; j<checkFlag; j++){
						returnSerialNo.add(index,Integer.valueOf(String.valueOf(tempSerialNo[i]-j)));
						index++;
					}
				}
			}
		}

		return returnSerialNo;
	}
	
	/**
		* File name: CheckLostSeriUitl.java<br>
		* Description: <br>
		* Return: @param firstnum ����
		* Return: @param secondnum С��
		* Return: @return<br>
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-2-6  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public static List numberLostSerial(int firstnum,int secondnum){
		List returnSerialNo = new ArrayList();
		int temp = firstnum-1;
		int index=0;
		while(temp>secondnum){
			returnSerialNo.add(index,Integer.valueOf(String.valueOf(temp)));
			temp--;
			index++;
		}
		return returnSerialNo;
	}
}
