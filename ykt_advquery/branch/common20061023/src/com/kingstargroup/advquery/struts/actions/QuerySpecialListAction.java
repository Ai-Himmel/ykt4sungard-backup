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
import com.kingstargroup.advquery.common.DateUtilExtend;
import com.kingstargroup.advquery.common.ErrorInfo;
import com.kingstargroup.advquery.tradeserial.TradeSerialDAO;

/**
 * ���̻�Ӫҵ���ͳ��
 * 
 * @author Administrator
 * 
 */
public class QuerySpecialListAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		// ��ʼ����
		String beginDate = request.getParameter("begindate");
		// ��������
		String endDate = request.getParameter("enddate");
		// ���ڲ���Ϊ��
		if (("".equals(beginDate)) || ("".equals(endDate))) {
			request.setAttribute("errorcont", new ErrorInfo().getErrorTip(
					"bydate", beginDate, endDate));
			return mapping.findForward("errortest");
		}
		// ������Ϊ��
		if ("".endsWith(request.getParameter("enum"))
				|| ("".equals(request.getParameter("bnum")))
				|| ("".equals(request.getParameter("efee")))
				|| ("".equals(request.getParameter("bfee")))) {
			request.setAttribute("errorcont", new String(
					"ƽ�����ѱ������ֵ����Сֵ��ƽ�����ѽ�����ֵ����Сֵ������Ϊ�գ������룡"));
			return mapping.findForward("errortest");
		}
		int eNum = Integer.parseInt(request.getParameter("enum"));
		int bNum = Integer.parseInt(request.getParameter("bnum"));
		float eFee = Float.parseFloat(request.getParameter("efee"));
		float bFee = Float.parseFloat(request.getParameter("bfee"));
		HttpSession session = request.getSession();
		session.setAttribute("enum", Integer.valueOf(String.valueOf(eNum)));
		session.setAttribute("bnum", Integer.valueOf(String.valueOf(bNum)));
		session.setAttribute("efee", Float.valueOf(String.valueOf(eFee)));
		session.setAttribute("bfee", Float.valueOf(String.valueOf(bFee)));
		session.setAttribute("begindate27d",beginDate);
		session.setAttribute("enddate27d",endDate);
		beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
		endDate = DateUtil.reFormatTime(request.getParameter("enddate"));
		if (bFee>eFee){
			request.setAttribute("errorcont", new String("��С���ܴ���������"));
			return mapping.findForward("errortest");			
		}
		if (bNum>eNum){
			request.setAttribute("errorcont", new String("��С�������ܴ�������������"));
			return mapping.findForward("errortest");			
		}
		int datenum = (int)DateUtilExtend.diffDate(beginDate,endDate);
		List result = new TradeSerialDAO().getSpecialList(datenum,beginDate,endDate,bNum,eNum,bFee,eFee);
		if (null==result){
			request.setAttribute("errorcont", new ErrorInfo().getErrorTip(
					"bydate", beginDate, endDate));
			return mapping.findForward("errortest");			
		}
		String dateRange = ":"+beginDate+"-"+endDate+"(��"+datenum+"��)";
		request.setAttribute("daterange",dateRange);
		request.setAttribute("result",result);
		return mapping.findForward("speciallist_queryresult");
	}
}
