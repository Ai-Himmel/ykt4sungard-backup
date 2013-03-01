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
 * ͳ�Ƹ���λ���࿨��ռ������
 * @author Administrator
 *
 */
public class QueryCardUseStatByConditionAction extends Action{

	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		//ͳ��ʱҪ����Ĳ���
		String departmentNo = request.getParameter("deptno");
		String code = "";
		//����ͼ��ʱҪ����Ĳ���
		String fillData = "dictCaption";
		String yData = "dictCaption";
		String xData = "cardNum";
		String dataType = "integer";
		
		// �Զ���ͼ����ʾҪ����Ĳ���
		// ��ʾ�Զ�����ɫ
		boolean showCustColor = true;
		// ��ʾ���������ֵ���ת����
		boolean showTextAxis ;
		// ��ʾBarͼ���ϵ�����
		boolean showLabel = false;
		// ��ʾ�Զ���ͼ������ɫ
		boolean showBackgroundColor = true;
		// ��ʾ������
		boolean showOutLine = true;
		// ��ʾ������
		boolean showGrid = true;
		HttpSession session = request.getSession();
		session.setAttribute("depttype",departmentNo);
		List result = new CardDAO().getCardUseStatByCondition(departmentNo,code);
		if (result.isEmpty()){
			request.setAttribute("errorcont",new String("û����Ҫ��ѯ�����ݣ�������ָ����ѯ������"));
			return mapping.findForward("errortest");			
		}
		showTextAxis = new ErrorInfo().showTextAxis(result);
		request.setAttribute("result",result);
		request.setAttribute("deptname",getDeptNameByCode(departmentNo));
		// �Զ���ͼ����ʾ
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
