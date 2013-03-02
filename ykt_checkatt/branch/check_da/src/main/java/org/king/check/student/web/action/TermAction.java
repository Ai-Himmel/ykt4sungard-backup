package org.king.check.student.web.action;

import java.util.ArrayList;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.commons.beanutils.BeanUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.king.check.domain.TTerm;
import org.king.check.service.TermService;
import org.king.check.util.DateUtilExtend;
import org.king.framework.web.action.BaseAction;
 
public class TermAction extends BaseAction {
	
	private static final Log log = LogFactory.getLog(TermAction.class);
	
	private TermService termService;
	
	public void setTermService(TermService termService) {
		this.termService = termService;
	}
	
	public ActionForward search(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		  List  termList = new ArrayList();
		  DynaActionForm   dform =(DynaActionForm)form; 
		  String termName =request.getParameter("termname");
		  termList = termService.findTerm(termName);
		  request.setAttribute("termList", termList);
		  return mapping.findForward("termSearch");	
	}
	
	public ActionForward addTerm_init(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		
		  
		  return mapping.findForward("termAdd");	
		  
	}
	
	
	
	public ActionForward update_step1(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		  DynaActionForm  dform = (DynaActionForm)form;
		  String termId = request.getParameter("termId");
		  TTerm termItem = termService.getTerm(termId);
		  BeanUtils.copyProperties(dform, termItem); 
		  request.setAttribute("termId", termId);
		  return  mapping.findForward("termEdit");
	}
	
	
	public ActionForward saveTerm(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		  String createDate = DateUtilExtend.getNowDate2();
		  HttpSession session = request.getSession();
		  String  accountId = (String)session.getAttribute("account");
		  DynaActionForm   dform =(DynaActionForm)form; 
		  TTerm term = new TTerm();
		  BeanUtils.copyProperties(term,dform); 
		  term.setCreateDate(createDate);
		  term.setCreateTime(DateUtilExtend.getNowTime());
		  term.setCreator(accountId);
		  term.setEnable("1");
		  termService.saveTerm(term);
		  
		  return  search(mapping,form,request,response);
	}
	
	public ActionForward updateTerm(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		  String termId = request.getParameter("termId");
		  DynaActionForm   dform =(DynaActionForm)form;
		  TTerm term = termService.getTerm(termId);
		  BeanUtils.copyProperties(term,dform);
		  termService.updateTerm(term);
		  
		  return search(mapping,form,request,response);
		  
	}
	public ActionForward deleteTerm(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		
		    String[] termIds = request.getParameterValues("itemlist");
		    for(int i=0;i<termIds.length;i++){
		    	  termService.delteTerm(termIds[i]);
		    }
		  
		  return search(mapping,form,request,response);
		  
	}
	
	

}
