/**
 * 
 */
package com.kingstargroup.advquery.struts.actions;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.advquery.common.DateUtil;
import com.kingstargroup.advquery.common.ErrorInfo;
import com.kingstargroup.advquery.tradeserial.TradeSerialDAO;

/**
 * 门禁信息统计分析
 * 
 * @author Administrator
 * 
 */
public class EntranceGuardAnalyseAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String groupedlist = request.getParameter("groupedlist");
		// 开始日期
		String beginDate = request.getParameter("begindate").toString();
		// 结束日期
		String endDate = request.getParameter("enddate").toString();
		// 日期不能为空
		if (("".equals(beginDate)) || ("".equals(endDate))) {
			request.setAttribute("errorcont", new ErrorInfo().getErrorTip(
					"bydate", beginDate, endDate));
			return mapping.findForward("errortest");
		}
		
		String deptNo = nullToString(request.getParameter("deptNo"));
		String specNo = nullToString(request.getParameter("specNo"));
		String classNo = nullToString(request.getParameter("classNo"));
		int custType = Integer.parseInt(nullToString(request.getParameter("custType")));
		int cardType = Integer.parseInt(nullToString(request.getParameter("cardType")));
		String devUse = nullToString(request.getParameter("devUse"));
		String bStuempNo = nullToString(request.getParameter("bStuempNo"));
		String eStuempNo = nullToString(request.getParameter("eStuempNo"));
		
		
		HttpSession session = request.getSession();
		session.setAttribute("bdate71",String.valueOf(beginDate));
		session.setAttribute("edate71",String.valueOf(endDate));
		session.setAttribute("deptNo",String.valueOf(deptNo));
		session.setAttribute("specNo",String.valueOf(specNo));
		session.setAttribute("classNo",String.valueOf(classNo));
		session.setAttribute("custType",String.valueOf(custType));
		session.setAttribute("devUse",String.valueOf(devUse));
		session.setAttribute("eStuempNo",String.valueOf(eStuempNo));
		session.setAttribute("bStuempNo",String.valueOf(bStuempNo));
		session.setAttribute("eStuempNo",String.valueOf(eStuempNo));
		session.setAttribute("egroupedlist",String.valueOf(groupedlist));
		
		
		beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
		endDate = DateUtil.reFormatTime(request.getParameter("enddate"));
		
		List resultList = new TradeSerialDAO().entranceAnalyse(beginDate,endDate,deptNo,specNo,classNo,custType,
				cardType,devUse,bStuempNo,eStuempNo,groupedlist);
		if (null==resultList){
			request.setAttribute("errorcont", new ErrorInfo().getErrorTip(
					"bydate", beginDate, endDate));
			return mapping.findForward("errortest");
		}
		request.setAttribute("resultList",resultList);
		request.setAttribute("egroupedlist",String.valueOf(groupedlist));
		request.setAttribute("specStatTip","认证信息统计分析(最后一条为合计值)");
		return mapping.findForward("entranceanalyse_queryresult");
		/*
		//绘制图形
		// 定义柱形图显示时传入参数
		String fillData = "amavg";
		String xData = "amavg";
		String yData = "num";
		String barDataType = "integer";
		// 自定义图表显示要传入的参数
		// 显示自定义颜色
		boolean showCustColor = true;
		// 显示横坐标文字的旋转方向
		boolean showTextAxis = false;
		// 显示Bar图标上的数字
		boolean showLabel = true;
		// 显示自定义图表背景颜色
		boolean showBackgroundColor = true;
		// 显示轮廓线
		boolean showOutLine = false;
		// 显示网格线
		boolean showGrid = true;
		
		request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
				showTextAxis, showLabel, showBackgroundColor, showOutLine,showGrid)
				.getChartPostProcessor());

		// 创建各卡类别所占数量图形数据集
		request.setAttribute(
				"consAvgData",
				new DrawBarSingleMap(result3, fillData, xData, yData,barDataType)
						.getDatasetProducer());				
		//绘制图形显示结束
		 * 
		 */
	}
	/*
	private String mealTrans(String in){
		if ("bk".equals(in.trim())){
			return "早餐";
		}else if ("lun".equals(in.trim())){
			return "午餐";
		}else if ("sup".equals(in.trim())){
			return "晚餐";
		}else{
			return "全天";
		}
	}
	*/
	private String nullToString(Object o){
		if (o==null){
			return "";
		}else{
			return o.toString();
		}
	}
	
	/*
	private String nullToInt(Object o){
		if (o==null){
			return "0";
		}else{
			return o.toString();
		}
	}
	*/
}
