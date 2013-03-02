package com.kingstargroup.ecard.portlet.advquery.action;

import java.util.Iterator;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.hibernate.card.TDept;
import com.kingstargroup.ecard.portlet.advquery.cewolf.CustomerDrawChart;
import com.kingstargroup.ecard.portlet.advquery.cewolf.DrawBarSingleMap;
import com.kingstargroup.ecard.portlet.advquery.service.AdvqueryServiceUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.kingstargroup.ecard.util.ErrorInfo;
import com.liferay.util.servlet.SessionErrors;

public class CardUseByDeptAction extends Action{
	
	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		//统计时要传入的参数
		String deptcode = request.getParameter("deptcode");
		String code = "";
		//绘制图形时要传入的参数
		String fillData = "cardtypename";
		String yData = "cardtypename";
		String xData = "cardnum";
		String dataType = "integer";
		
		// 自定义图表显示要传入的参数
		// 显示自定义颜色
		boolean showCustColor = true;
		// 显示横坐标文字的旋转方向
		boolean showTextAxis ;
		// 显示Bar图标上的数字
		boolean showLabel = false;
		// 显示自定义图表背景颜色
		boolean showBackgroundColor = true;
		// 显示轮廓线
		boolean showOutLine = true;
		// 显示网格线
		boolean showGrid = true;
			
		List result = AdvqueryServiceUtil.getCardUseByDept(deptcode);
		
		List deptList = AdvqueryServiceUtil.getDeptList();
		request.setAttribute("deptList", deptList);
		
		if (result==null || result.isEmpty()){
			SessionErrors.add(request, EcardConstants.CARDUSEBYDEPT_ERROR_EXIST,"没有你要查询的数据，请重新指定查询条件！");
			return mapping.findForward("errortest");			
		}
		showTextAxis =  ErrorInfo.showTextAxis(result);
		request.setAttribute("result",result);
		request.setAttribute("deptname", getDeptNameByCode(deptcode));
		// 自定义图形显示
		request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
				showTextAxis, showLabel, showBackgroundColor, showOutLine,showGrid)
				.getChartPostProcessor());
		
		request.setAttribute("cardUseStatByDept",
				new DrawBarSingleMap(result,fillData,yData,xData,dataType).getDatasetProducer());
		
		return mapping.findForward("cardusebydept_queryresult");
	}
	private String getDeptNameByCode(String deptCode) {
		String deptN = "";
		List deptName = AdvqueryServiceUtil.getDeptName(deptCode);
		if (deptName != null) {
			Iterator iter = deptName.iterator();
			while (iter.hasNext()) {
				TDept row = (TDept) iter.next();
				deptN = row.getDeptname();
			}
		}
		return deptN;
	}

}
