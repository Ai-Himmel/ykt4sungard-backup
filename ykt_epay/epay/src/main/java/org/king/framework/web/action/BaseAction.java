package org.king.framework.web.action;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.actions.DispatchAction;
import org.king.utils.DateUtil;
import org.springframework.jdbc.core.JdbcTemplate;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

public class BaseAction extends DispatchAction {
	private JdbcTemplate jdbcTemplate;
	
    public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}
    
    public boolean savalog(String accno,String action,String message,HttpServletRequest request){
    	try{
	    	String sql = "insert into t_epay_acc_log(accno,OPERTIME,IP,ACTION,MESSAGE,id) values('"+accno+"','"+ DateUtil.getNow()+"','"
	    	+request.getRemoteAddr()+"','"+action+"','"+message+"',hibernate_sequence.nextval)";
	    	jdbcTemplate.execute(sql);
	    	return true;
    	}catch(Exception e){
    		e.printStackTrace();
    		return false;
    	}
    	
    }
	protected final void removeAttribute(ActionMapping mapping, HttpServletRequest request) {
        if (mapping.getAttribute() != null)
            if ("request".equals(mapping.getScope()))
                request.removeAttribute(mapping.getAttribute());
            else
                request.getSession().removeAttribute(mapping.getAttribute());
    }

    protected void removeFormBean(ActionMapping mapping, HttpServletRequest request) {
        if (mapping.getAttribute() != null)
            if ("request".equals(mapping.getScope())) {
                request.removeAttribute(mapping.getAttribute());
            } else {
                HttpSession session = request.getSession();
                session.removeAttribute(mapping.getAttribute());
            }
    }

    protected void updateFormBean(ActionMapping mapping, HttpServletRequest request, ActionForm form) {
        if (mapping.getAttribute() != null)
            if ("request".equals(mapping.getScope())) {
                request.setAttribute(mapping.getAttribute(), form);
            } else {
                HttpSession session = request.getSession();
                session.setAttribute(mapping.getAttribute(), form);
            }
    }
}