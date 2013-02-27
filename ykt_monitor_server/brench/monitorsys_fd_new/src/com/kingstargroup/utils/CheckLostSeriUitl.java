package com.kingstargroup.utils;

import java.util.ArrayList;
import java.util.List;

/**<br>
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. <br>
 * File name: CheckLostSeriUitl.java<br>
 * Description: 循序查找缺失流水类
 * Modify History（或Change Log）:  <br>
 * 操作类型（创建、修改等）   操作日期     操作者    操作内容简述<br>
 * 创建  				 2005-10-21  何林青    循序查找缺失流水
 * <p>
 *
 * @author      何林青
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
		* Return: @param firstnum 大数
		* Return: @param secondnum 小数
		* Return: @return<br>
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-2-6  <br>
		* @author   何林青
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
