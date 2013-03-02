package com.kingstargroup.advquery.door.action;

import java.util.Iterator;
import java.util.List;

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
import com.kingstargroup.advquery.hibernate.util.CustomerUtil;
import com.kingstargroup.advquery.hibernate.util.DoorUtil;

public class QueryUserDoorAction extends Action{
	
	public ActionForward execute(
			ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		HttpSession session = request.getSession();
		//String manId = request.getSession().getAttribute("username").toString();//���֤
		String beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
		String endDate = DateUtil.reFormatTime(request.getParameter("enddate"));
		String dateRange = beginDate+"-"+endDate;
		String custno =request.getParameter("custId");
		/*TCifCustomer customer =	CustomerUtil.getCustomerByStuempno(name);
		if(customer !=null ){
			custno = String.valueOf(customer.getCutId());
		}*/
		
		
		String name = session.getAttribute("name").toString();
		
		if (custno ==null ||"".equals(custno)){
			request.setAttribute("errorcont",new String(name+"û����Ӧ�Ŀͻ���,����һ��ͨѧ���ŵ�¼��"));
			return mapping.findForward("errortest");
		}
		
		
		session.setAttribute("custid",custno);
		
	
		List detail = DoorUtil.getDoorDetailByCust(custno,beginDate,endDate);
		if (null==detail){
			request.setAttribute("errorcont","û����Ҫ��ѯ�����ݣ�������ָ����ѯ������");
			return mapping.findForward("errortest");			
		}
		request.setAttribute("title",name+":["+dateRange+"]�Ž������ϸ");
		request.setAttribute("result",detail);
		return mapping.findForward("doordetail_queryresult");
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

}
