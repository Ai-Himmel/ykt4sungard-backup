package org.king.security.web.action;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessage;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.action.DynaActionForm;
import org.king.common.Constant;
import org.king.common.displaytag.DBPaginatedList;
import org.king.common.displaytag.decorator.DecoratorFactory;
import org.king.common.displaytag.decorator.StateDecorator;
import org.king.framework.exception.BusinessException;
import org.king.framework.web.action.BaseAction;
import org.king.security.service.AccManageService;
import org.king.utils.PaginationUtil;

public class AccManageAction extends BaseAction {
	
	private AccManageService accManageService;
	
	public void setAccManageService(AccManageService accManageService) {
		this.accManageService = accManageService;
	}
	
	public ActionForward toupdateview(ActionMapping mapping, ActionForm form, 
			HttpServletRequest request, HttpServletResponse response) {
		HttpSession session = request.getSession(false);
        if (session == null) {
            session = request.getSession(true);
        }
        request.setAttribute("acctype", session.getAttribute("acctype"));
		return mapping.findForward("toupdateview");
	}
	public ActionForward changePwd(ActionMapping mapping, ActionForm form, 
			HttpServletRequest request, HttpServletResponse response) {
		HttpSession session = request.getSession(false);
        if (session == null) {
            session = request.getSession(true);
        }
        String accno = (String)session.getAttribute("accno");
        ActionMessages errors = new ActionMessages(); 
        String oldpwd = request.getParameter("oldpwd");
        String pwd = request.getParameter("newpwd");
        String pwdtype = request.getParameter("pwdtype");
        //判断密码是否为空
        if(pwd==null||pwd.equals("")){
        	 errors.add("newpwd", new ActionMessage("errors.required"));
             saveErrors(request, errors);
             return mapping.findForward("pwdupdatefaile");
        }
        //判断密码类型是否为空
        if(pwdtype==null||pwdtype.equals("")){
        	errors.add("pwdtype", new ActionMessage("errors.required"));
            saveErrors(request, errors);
            return mapping.findForward("pwdupdatefaile");
        }
        //判断是否与老密码相等
        if(oldpwd!=null&&accManageService.checkoldpwd(accno, oldpwd, pwdtype,session.getAttribute("acctype").toString())){
        	errors.add("oldpwd", new ActionMessage("error.oldpwderror"));
            saveErrors(request, errors);
            return mapping.findForward("pwdupdatefaile");
        }
        //2、修改密码
        try {
			if(accManageService.changepwd(accno, pwd, pwdtype,session.getAttribute("acctype").toString())){
				super.savalog(accno, Constant.EPAY_ACC_LOG_UPDATEPWD, "修改成功", request);
				errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage("errors.handlesuccess"));
	            saveErrors(request, errors);
			}
			return mapping.findForward("pwdupdatesuccess");
		} catch (BusinessException e) {
			e.printStackTrace();
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage("errors.handlefaile"));
            saveErrors(request, errors);
            super.savalog(accno, Constant.EPAY_ACC_LOG_UPDATEPWD, "修改失败", request);
			return mapping.findForward("pwdupdatefaile");
		}
	}
	public ActionForward setstoppay(ActionMapping mapping, ActionForm form, 
			HttpServletRequest request, HttpServletResponse response) throws IOException {
			String flag = request.getParameter("flag");
			HttpSession session = request.getSession(false);
	        if (session == null) {
	            session = request.getSession(true);
	        }
	        response.setContentType("text/html; charset=UTF-8");
			PrintWriter out = response.getWriter();
	        String accno = (String)session.getAttribute("accno");
			if(flag!=null&&accno!=null&&accManageService.setStopPay(flag, accno)){
				super.savalog(accno, "1".equals(flag)?"1":"2", "操作成功", request);
				out.print("1");
			}else{
				out.print("2");
			}
		return null;
	}
	public ActionForward listepay(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        //query condition
		HttpSession session = request.getSession(false);
        if (session == null) {
            session = request.getSession(true);
        }
        
        String accno = (String)session.getAttribute("accno");
		String starttime = (String) ((DynaActionForm) form).get("starttime");
        String endtime = (String) ((DynaActionForm) form).get("endtime");
        Object[] conditions = new Object[]{accno,starttime,endtime};
        DBPaginatedList page = new DBPaginatedList();
        PaginationUtil.pageInfoPopulate("row", request, page);
        accManageService.getPayRecordList(page, conditions);
        request.setAttribute("payRecord", page);
        return mapping.findForward("listepay");
    }
	
	
	public ActionForward listnetacc(ActionMapping mapping, ActionForm form, 
			HttpServletRequest request, HttpServletResponse response) throws Exception {
		  //query condition
		HttpSession session = request.getSession(false);
        if (session == null) {
            session = request.getSession(true);
        }
        
        StateDecorator accStatusDecorator = DecoratorFactory.getAccStatusDecorator();
        StateDecorator stopPayFlagDecorator = DecoratorFactory.getStopPayFlagDecorator();
        List cardphytypes = accManageService.getAvailCardPhytype();
        
        String stoppayflag = (String) ((DynaActionForm) form).get("stoppayflag");
        String status = (String) ((DynaActionForm) form).get("status");
        Object[] conditions = new Object[]{stoppayflag,status};
        DBPaginatedList page = new DBPaginatedList();
        PaginationUtil.pageInfoPopulate("row", request, page);
        accManageService.getNetaccList(page, conditions);
        
        request.setAttribute("accStatusDecorator", accStatusDecorator);
        request.setAttribute("stopPayFlagDecorator", stopPayFlagDecorator);
        request.setAttribute("cardphytypes", cardphytypes);
        request.setAttribute("netaccList", page);
        return mapping.findForward("listnetacc");
        
	}
	
	public ActionForward setstatus (ActionMapping mapping, ActionForm form, 
			HttpServletRequest request, HttpServletResponse response) throws Exception {
		String accnos = request.getParameter("accnos");
		String cardphytype = request.getParameter("cardphytype");
		String islockacc = request.getParameter("islockacc");
		String isfrozencard = request.getParameter("isfrozencard");
		
		Boolean ss = Boolean.valueOf(islockacc);
		
		return mapping.findForward("listnetacc");
		}
}
