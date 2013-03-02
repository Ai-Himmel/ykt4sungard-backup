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

import com.kingstargroup.advquery.cewolf.CustomerDrawChart;
import com.kingstargroup.advquery.cewolf.DrawBarConfTypeMap;
import com.kingstargroup.advquery.common.DateUtil;
import com.kingstargroup.advquery.common.ErrorInfo;
import com.kingstargroup.advquery.common.GetListResultStat;
import com.kingstargroup.advquery.common.GetProperty;
import com.kingstargroup.advquery.photo.PhotoDAO;
/**
 * 拍照情况统计
 * @author Administrator
 *
 */
public class QueryPhotoStatAction extends Action{

	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		String cutType = request.getParameter("emptype");
		//金额单位
		int dataUnit = 0;
		//Ｙ轴提示信息
		String yLabel = "";
		//开始日期
		String beginDate = request.getParameter("begindate");
		//结束日期
		String endDate = request.getParameter("enddate");
		String dateRange = "";
		String statTypeShow = "";
		List result = null;
		String statType = request.getParameter("statType");
		if (("".equals(beginDate))||("".equals(endDate))){
			request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
			return mapping.findForward("errortest");			
		}
		HttpSession session = request.getSession();
		session.setAttribute("cuttype",cutType);
		if ("bydate".equals(statType)){
			beginDate = DateUtil.reFormatTimeOther(request.getParameter("begindate"));
			endDate = DateUtil.reFormatTimeOther(request.getParameter("enddate"));	
 			session.setAttribute("begindate51d",request.getParameter("begindate"));
			session.setAttribute("enddate51d",request.getParameter("enddate"));
			session.setAttribute("querytype51","0");
			statTypeShow = GetProperty.getProperties("title.date",this.servlet.getServletContext());
		}else if ("bymonth".equals(statType)){
			beginDate = DateUtil.getMonthOther(request.getParameter("begindate"));
			endDate = DateUtil.getMonthOther(request.getParameter("enddate"));	
 			session.setAttribute("begindate51m",request.getParameter("begindate"));
			session.setAttribute("enddate51m",request.getParameter("enddate"));
			session.setAttribute("querytype51","1");
			statTypeShow = GetProperty.getProperties("title.month",this.servlet.getServletContext());
		}
		dateRange = ':'+beginDate+'-'+endDate;
		
		//生成图表要传入的参数
		String accType[] = {"拍照情况统计"};
		String xData = "photo_date";
		String showColumn = "photonum";
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
		if ("all".equals(cutType)){
			result = new PhotoDAO().getphotoNumAll(beginDate,endDate,statType);
			request.setAttribute("cuttype","所有人");
		}else{
			result = new PhotoDAO().getphotoNumByType(cutType,beginDate,endDate,statType);
			request.setAttribute("cuttype",cutType);
		}
		
		if (result.isEmpty()){
			request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
			return mapping.findForward("errortest");			
		}
		showTextAxis = new ErrorInfo().showTextAxis(result);
		request.setAttribute("daterange",dateRange);
		
		yLabel = new GetListResultStat().getYLabelManNum(result,"photonum",dataType);
		dataUnit = new GetListResultStat().getUnitValue(result,"photonum",dataType);
		request.setAttribute("result",result);
		request.setAttribute("ylabel",yLabel);
		request.setAttribute("stattypeshow",statTypeShow);
		request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
				showTextAxis, showLabel, showBackgroundColor, showOutLine,showGrid)
				.getChartPostProcessor());
		
		request.setAttribute("photoChart",
				new DrawBarConfTypeMap(result,accType,xData,dataType,showColumn,dataUnit).getDataProducer());
		return mapping.findForward("photo_queryresult");
	}

}
