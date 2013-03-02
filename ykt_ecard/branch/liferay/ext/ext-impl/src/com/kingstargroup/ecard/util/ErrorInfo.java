/**
 * 
 */
package com.kingstargroup.ecard.util;

import java.util.List;

import javax.servlet.http.HttpServletRequest;

/**
 * ������ʾ��Ϣ
 * 
 * @author Administrator
 * 
 */
public class ErrorInfo {
	

	/**
	 * ��������������ʾ����
	 * 
	 * @param statType
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public static String getErrorTip(String statType, String beginDate, String endDate) {
		String errorTip = "";
		if (("bydate".equals(statType))||("byweek".equals(statType))) {
			if (("".equals(beginDate)) && ("".equals(endDate))) {
				errorTip = "��û��ѡ��ʼ���ںͽ������ڣ�����ѡ����Ҫ��ѯ�����ڷ�Χ��";
			} else if ("".equals(beginDate)) {
				errorTip = "��û��ѡ��ʼ���ڣ�����ѡ��ʼ���ڣ�";
			} else if ("".equals(endDate)) {
				errorTip = "��û��ѡ��������ڣ�����ѡ��������ڣ�";
			} else {
				errorTip = "��ѡ������ڷ�Χ��" + beginDate + "-" + endDate
						+ "û�����ݣ�������ָ����ѯ������";
			}
		} else if ("bymonth".equals(statType)) {
			if (("".equals(beginDate)) && ("".equals(endDate))) {
				errorTip = "��û��ѡ��ʼ�·ݺͽ����·ݣ�����ѡ����Ҫ��ѯ���·ݷ�Χ��";
			} else if ("".equals(beginDate)) {
				errorTip = "��û��ѡ��ʼ�·ݣ�����ѡ��ʼ�·ݣ�";
			} else if ("".equals(endDate)) {
				errorTip = "��û��ѡ������·ݣ�����ѡ������·ݣ�";
			} else {
				errorTip = "��ѡ����·ݷ�Χ��" + beginDate + "-" + endDate
						+ "û�����ݣ�������ָ����ѯ������";
			}

		}
		return errorTip;
	}

	/**
	 * ������ȡ�����������ж��Ƿ�ѣ���������б��������9������б��������б��
	 * 
	 * @param result
	 * @return
	 */
	public static boolean showTextAxis(List result) {
		/***********************************************************************
		 * if ((int)(result.size()/5)>1){ return true; }else{ return false; }
		 **********************************************************************/
		return ((int) (result.size() / 5) > 1) ? true : false;

	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ErrorInfo�ж����ڷ�Χ�����ڷ�Χ����28��ʱ���ܲ鿴��״ͼ�Ͷ�ջͼ��ֻ�ܲ鿴����ͼ��<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-5-10 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public static String DateRangeJudeg(
			String showType, 
			String statType,
			String beginDate, 
			String endDate, 
			HttpServletRequest request) {
		String errorTip ="";
		if ("bydate".equals(statType)) {
			if ((DateUtilExtend.diffDate(beginDate, endDate) > 30)&&(!"line".equals(showType))){
				errorTip = "���ڷ�Χ����30�죬����ʹ������ͼ�Ͷ�ջͼ�鿴����鿴����ͼ��";
				
			}
			return errorTip;
		} else if ("byweek".equals(statType)){
			if ((Integer.parseInt(DateUtilExtend.getWeek(endDate))
					- Integer.parseInt(DateUtilExtend.getWeek(beginDate)) > 30)
					&& (!"line".equals(showType))){
				errorTip = "��Χ����30���ܣ�����ʹ������ͼ�Ͷ�ջͼ�鿴����鿴����ͼ��";
			}
			return errorTip;
		} else if ("bymonth".equals(statType)) {
			if((DateUtil.getdiffMonth(beginDate,endDate)>30||DateUtil.getdiffMonth(beginDate,endDate)<0)&& (!"line".equals(showType))){
				errorTip = "��Χ����30���£�����ʹ������ͼ�Ͷ�ջͼ�鿴����鿴����ͼ��";
			}
			return errorTip;
		} else {
			return "��������";
		}
	}

}
