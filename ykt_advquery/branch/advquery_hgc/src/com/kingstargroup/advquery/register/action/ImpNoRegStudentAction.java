package com.kingstargroup.advquery.register.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.advquery.hibernate.util.RegisterUtil;

public class ImpNoRegStudentAction extends Action {
	
	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest req, 
			HttpServletResponse res) throws Exception {
		
		  String termName = req.getParameter("termName");
		  boolean flag =  RegisterUtil.ImpNoRegStudent(termName);
		  if(flag==false){
			  req.setAttribute("errorcont","ѧ����Ϣ����ʧ�ܣ���ϵϵͳ����Ա��");
			  return mapping.findForward("errortest");
		  }
		  //req.setAttribute("termName",termName);
		  req.setAttribute("errorcont","ѧ����Ϣ����ɹ�");
		  //req.setAttribute("flag",Boolean.valueOf(flag));
		  return mapping.findForward("errortest");
	}

}
