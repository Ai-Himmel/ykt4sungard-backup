package com.kingstargroup.advquery.struts.actions;



import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.datacontract.schemas._2004._07.saff.User;
import com.kingstargroup.advquery.common.DateUtil;
import com.kingstargroup.advquery.common.DateUtilExtend;
import com.kingstargroup.advquery.hibernate.util.InterfaceInfoUtil;
import com.kingstargroup.advquery.hibernate.util.TradeUtil;

public class QueryMoreTradeDetailAction extends Action{

	public ActionForward execute(
			ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		
		String  ticketIdOfUser =  request.getParameter("ticketIdOfUser");
		
		 if("".equals(ticketIdOfUser)){
			  request.setAttribute("errorcont",new String("请选择人员信息！"));
			  return mapping.findForward("errortest"); 
		 }
		
		  String begindate = request.getParameter("begindate");
		  request.setAttribute("begindate", begindate);
		  String enddate =request.getParameter("enddate");
		  request.setAttribute("enddate", enddate);
		  long diffdays = DateUtilExtend.diffDate(begindate,enddate); 
		  /*if(diffdays>100){  
			  request.setAttribute("errorcont",new String("日期范围大于3个月,影响系统性能,请减少日期范围！"));
			  return mapping.findForward("errortest");
			  
		  } */
		  begindate = DateUtil.reFormatTime(begindate); 
		  enddate = DateUtil.reFormatTime(enddate);
		  String dateRange = begindate+"-"+enddate;
		  List<User> users  = InterfaceInfoUtil.getSelectedUsersByTicketID(ticketIdOfUser);
		  String manIds = InterfaceInfoUtil.getManIdByUsers(users);
		
	 	List detail = TradeUtil.getMoreAccountDetail(manIds,begindate,enddate);
	 	
		if (null==detail){
			request.setAttribute("errorcont","没有你要查询的数据，请重新指定查询条件！");
			return mapping.findForward("errortest");			
		}
		request.setAttribute("title","客户["+dateRange+"]帐户交易明细");
		request.setAttribute("result",detail);
		return mapping.findForward("moretradedetail_queryresult");
	}

}
