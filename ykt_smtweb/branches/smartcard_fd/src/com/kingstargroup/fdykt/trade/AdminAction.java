package com.kingstargroup.fdykt.trade;

import java.sql.SQLException;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.dao.DB2DeviceDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;

public class AdminAction extends Action{
	
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = admin(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}
	
	private ActionForward admin(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		   try{
			   HttpSession session = request.getSession();
			   int  page = 1;
			   DB2DeviceDAO    deviceDao = new DB2DeviceDAO();
			   int  count =  deviceDao.DeviceCount();
			   List   list =   deviceDao.DeviceList(page);
			   session.setAttribute("count",new Integer(count));
			   session.setAttribute("list",list);
			   session.setAttribute("page",new Integer(page));
			   return mapping.findForward("success");
		   }catch (Exception e) {
				return (mapping.findForward("failure"));
		  }
		
		
	}

}
