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
import com.kingstargroup.advquery.hibernate.util.TicketUtil;
import com.kingstargroup.advquery.util.ParamUtil;

public class QueryTicketFillDetailAction extends Action{

	public ActionForward execute( 
			ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		String deptNo = ParamUtil.getString(request,"depno");
		String ticketNo = ParamUtil.getString(request,"billno");
		int fillType = ParamUtil.getInteger(request,"tickettype");
		String stuempno = ParamUtil.getString(request,"stuempno");
		String beginDate = DateUtil.reFormatTime(ParamUtil.getString(request,"begindate"));
		String endDate = DateUtil.reFormatTime(ParamUtil.getString(request,"enddate"));
		int custType = ParamUtil.getInteger(request,"custtype");
		HttpSession session = request.getSession();
		session.setAttribute("deptcode",deptNo);
		session.setAttribute("filltype",new Integer(fillType));
		session.setAttribute("cuttype",new Integer(custType));
		List result = TicketUtil.getTicketFillDetail(deptNo,ticketNo,fillType,stuempno,beginDate,endDate,custType); 
		if (result.isEmpty()){
			request.setAttribute("errorcont","没有你要查询的数据，请重新指定查询条件！");
			return mapping.findForward("errortest");			
		}
		request.setAttribute("result",result);
		return mapping.findForward("ticket_queryresult");
	}

}
