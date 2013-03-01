package com.kingstargroup.advquery.register.action;

import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.advquery.customer.TCifCustomer;
import com.kingstargroup.advquery.hibernate.dao.GetQueryConListDAO;
import com.kingstargroup.advquery.hibernate.util.RegisterUtil;

public class RegisterInfoAction extends Action {
	
	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest req, 
			HttpServletResponse res) throws Exception {
		String cmd = req.getParameter("cmd");
		String regId = req.getParameter("regId");
		String custId = req.getParameter("custId"); 
		Map regMap = new HashMap();
		//regMap.clear();
	
		 if("update".equals(cmd)){
		  String comments = req.getParameter("comments");
		  boolean flag = RegisterUtil.updateResisterInfo(regId,custId,comments);
		  req.setAttribute("flag",new Boolean(flag));
		  }
		  regMap =(Map)RegisterUtil.getResisterInfo(regId,custId);
		  regMap.put("cutName",getCustName(custId));
		  req.setAttribute("regMap",regMap);
		return mapping.findForward("register.comments");
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
