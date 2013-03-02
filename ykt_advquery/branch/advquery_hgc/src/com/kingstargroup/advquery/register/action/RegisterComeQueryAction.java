package com.kingstargroup.advquery.register.action;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.beanutils.BeanUtils;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;

import com.kingstargroup.advquery.hibernate.util.RegisterUtil;
import com.kingstargroup.advquery.register.dto.Register;

public class RegisterComeQueryAction extends Action{
	
	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest req, 
			HttpServletResponse res) throws Exception {
		
		
  		  DynaActionForm dForm = (DynaActionForm)form;
		  Register  register = new Register();
		  //String term = req.getParameter("term");
		  BeanUtils.copyProperties(register,dForm);
		  String term  = register.getTerm();
		  if ("".equals(term)){
				req.setAttribute("errorcont",new String("学期为必选条件"));
				return mapping.findForward("errortest");
		  }
		  List registerComeList = RegisterUtil.getRegisterComeResult(register);
		/*  String beginDate = register.getBegindate();
		  String endDate=register.getEnddate();
		  SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
			 if("".equals(endDate)){
				 endDate =dateFormat.format(new Date());
			 }
	      req.setAttribute("beginDate",beginDate);
	      req.setAttribute("endDate",endDate);*/
		 
		  
		  
		  req.getSession().setAttribute("register",register);
		  req.setAttribute("registerComeList",registerComeList);
		  
		  return mapping.findForward("registercome.result");
		
		
	}

}
