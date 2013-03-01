/**
 * 
 */
package com.kingstargroup.advquery.struts.actions;

import java.util.Iterator;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.advquery.card.CardDAO;
import com.kingstargroup.advquery.cewolf.CustomerDrawChart;
import com.kingstargroup.advquery.cewolf.DrawBarSingleMap;
import com.kingstargroup.advquery.common.ErrorInfo;
import com.kingstargroup.advquery.dept.TCifDept;
import com.kingstargroup.advquery.hibernate.dao.GetQueryConListDAO;
/**
 * 统计各单位各类卡所占的数量
 * @author Administrator
 *
 */
public class QueryCardUseStatByConditionAction extends Action{

	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		//统计时要传入的参数
		String departmentNo = request.getParameter("deptno");
		String code = "";
		//绘制图形时要传入的参数
		String fillData = "dictCaption";
		String yData = "dictCaption";
		String xData = "cardNum";
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
		HttpSession session = request.getSession();
		session.setAttribute("depttype",departmentNo);
		List result = new CardDAO().getCardUseStatByCondition(departmentNo,code);
		if (result.isEmpty()){
			request.setAttribute("errorcont",new String("没有你要查询的数据，请重新指定查询条件！"));
			return mapping.findForward("errortest");			
		}
		showTextAxis = new ErrorInfo().showTextAxis(result);
		request.setAttribute("result",result);
		request.setAttribute("deptname",getDeptNameByCode(departmentNo));
		// 自定义图形显示
		request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
				showTextAxis, showLabel, showBackgroundColor, showOutLine,showGrid)
				.getChartPostProcessor());
		
		request.setAttribute("cardUseStatByConditionBarChart",
				new DrawBarSingleMap(result,fillData,yData,xData,dataType).getDatasetProducer());
		
		return mapping.findForward("cardusestatbycondition_queryresult");
	}
	private String getDeptNameByCode(String deptCode){
		String deptN = "";
		List deptName = new GetQueryConListDAO().getDeptName(deptCode);
		Iterator iter = deptName.iterator();
		while (iter.hasNext()){
			TCifDept row = (TCifDept)iter.next(); 
			deptN = row.getDeptName();
		}
		return deptN;
	}

}
