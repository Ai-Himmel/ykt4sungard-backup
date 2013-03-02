package com.kingstargroup.advquery.struts.actions;

import java.util.Iterator;
import java.util.List;
import com.kingstargroup.advquery.hibernate.dao.AccountDAO;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.advquery.common.DateUtil;
import com.kingstargroup.advquery.customer.TCifCustomer;
import com.kingstargroup.advquery.hibernate.dao.GetQueryConListDAO;
import com.kingstargroup.advquery.hibernate.util.AccountUtil;

public class QueryAccountDetailByCustIdAction extends Action{

	public ActionForward execute(
			ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		String custno = request.getParameter("empno");
		String stuempno = request.getParameter("stuempno");
		String beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
		String endDate = DateUtil.reFormatTime(request.getParameter("enddate"));
		HttpSession session = request.getSession();
		session.setAttribute("custid",custno);
		session.setAttribute("stuempno",stuempno);
		String dateRange = beginDate+"-"+endDate;
		
		if ("".equals(custno)&&"".equals(stuempno)){
			request.setAttribute("errorcont",new String("请输入要查询的客户号或学工号！"));
			return mapping.findForward("errortest");
		}
		if(!"".equals(stuempno)){
	          String 	temp_custId =   getCustId(stuempno);
	          if((!"".equals(custno))&&!temp_custId.equals(custno)){
	        	  request.setAttribute("errorcont",new String("客户不存在，请重新输入！"));
					return mapping.findForward("errortest");
	          }else{
	        	  custno = temp_custId;
	          }
			}
		/*if (("".equals(getCustName(custno))) || null==(getCustName(custno))) {
			request.setAttribute("errorcont",new String("客户号："+custno+"不存在，请重新输入！"));
			return mapping.findForward("errortest");			
		}*/
		
		
		
		
		List detail = AccountUtil.getOneAccountDetail(custno,beginDate,endDate);
		if (null==detail){
			request.setAttribute("errorcont","没有你要查询的数据，请重新指定查询条件！");
			return mapping.findForward("errortest");			
		}
		request.setAttribute("title",getCustName(custno)+":["+dateRange+"]消费情况明细");
		request.setAttribute("result",detail);
		return mapping.findForward("oneaccountstatdetail_queryresult");
	}
	private String getCustName(String custId){
		String custName = "";
		List list = new GetQueryConListDAO().getCustNameByID(custId);
		Iterator iter = list.iterator();
		while (iter.hasNext()){
			TCifCustomer row = (TCifCustomer)iter.next();
			custName = row.getCutName().toString();
		}
		return custName;
	}
	private String getCustId(String stuempNo){
		String custId ="";
		custId =  AccountUtil.getCustIdBystuempNo(stuempNo);
	    return custId;
	}

}
