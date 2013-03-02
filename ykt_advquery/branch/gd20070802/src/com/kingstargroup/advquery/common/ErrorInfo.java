/**
 * 
 */
package com.kingstargroup.advquery.common;

import java.util.List;

import javax.servlet.http.HttpServletRequest;

/**
 * 出错提示信息
 * 
 * @author Administrator
 * 
 */
public class ErrorInfo {
	String errorTip = "";

	/**
	 * 根据输入条件显示错误
	 * 
	 * @param statType
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public String getErrorTip(String statType, String beginDate, String endDate) {
		if (("bydate".equals(statType))||("byweek".equals(statType))) {
			if (("".equals(beginDate)) && ("".equals(endDate))) {
				errorTip = "你没有选择开始日期和结束日期，请先选择你要查询的日期范围！";
			} else if ("".equals(beginDate)) {
				errorTip = "你没有选择开始日期，请先选择开始日期！";
			} else if ("".equals(endDate)) {
				errorTip = "你没有选择结束日期，请先选择结束日期！";
			} else {
				errorTip = "你选择的日期范围：" + beginDate + "-" + endDate
						+ "没有数据，请重新指定查询条件！";
			}

		} else if ("bymonth".equals(statType)) {
			if (("".equals(beginDate)) && ("".equals(endDate))) {
				errorTip = "你没有选择开始月份和结束月份，请先选择你要查询的月份范围！";
			} else if ("".equals(beginDate)) {
				errorTip = "你没有选择开始月份，请先选择开始月份！";
			} else if ("".equals(endDate)) {
				errorTip = "你没有选择结束月份，请先选择结束月份！";
			} else {
				errorTip = "你选择的月份范围：" + beginDate + "-" + endDate
						+ "没有数据，请重新指定查询条件！";
			}

		}
		return errorTip;
	}

	/**
	 * 根据提取数据量多少判断是否把Ｘ轴数据倾斜（若大于9条则倾斜，否则不倾斜）
	 * 
	 * @param result
	 * @return
	 */
	public boolean showTextAxis(List result) {
		/***********************************************************************
		 * if ((int)(result.size()/5)>1){ return true; }else{ return false; }
		 **********************************************************************/
		return ((int) (result.size() / 5) > 1) ? true : false;

	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ErrorInfo判断日期范围，日期范围大于28天时不能查看柱状图和堆栈图，只能查看曲线图形<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-5-10 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public boolean DateRangeJudeg(
			String showType, 
			String statType,
			String beginDate, 
			String endDate, 
			HttpServletRequest request) {
		if ("bydate".equals(statType)) {
			if ((DateUtilExtend.diffDate(beginDate, endDate) > 30)&&(!"line".equals(showType))){
				request.setAttribute("errorcont","日期范围大于30天，不能使用柱形图和堆栈图查看，请查看曲线图！");
				return true;
			}else{
				return false;
			}
		} else if ("byweek".equals(statType)){
			if ((Integer.parseInt(DateUtilExtend.getWeek(endDate))
					- Integer.parseInt(DateUtilExtend.getWeek(beginDate)) > 30)
					&& (!"line".equals(showType))){
				request.setAttribute("errorcont", "范围大于30个周，不能使用柱形图和堆栈图查看，请查看曲线图！");
				return true;
			}else{
				return false;
			}
		} else if ("bymonth1".equals(statType)) {
			if ((Integer.parseInt(DateUtil.getMonth(endDate))
					- Integer.parseInt(DateUtil.getMonth(beginDate)) > 30)
					&& (!"line".equals(showType))){
				request.setAttribute("errorcont", "范围大于30个月，不能使用柱形图和堆栈图查看，请查看曲线图！");
				return true;
			}else{
				return false;
			}
		} else {
			return false;
		}
	}

}
