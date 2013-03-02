package com.kingstargroup.fdykt.trade;

import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.dao.DB2DeviceDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;

public class GetGroupAction extends Action{
	
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		
		ActionForward forward = getGroup(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();   
		}
		return forward;
	}
	private  ActionForward getGroup(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		try{
			System.out.println("------GetGroupAction-------");
		String deviceId = request.getParameter("deviceId");
		System.out.println("------GetGroupAction-------");
		DB2DeviceDAO dao = new DB2DeviceDAO();
		String  group = dao.getGroupbyDeviceId(deviceId);
		System.out.println("------group-------"+group);
		request.setAttribute("group", group);
		return mapping.findForward("dsdj");
		}catch(Exception e){
			e.printStackTrace();
			request.setAttribute("msg", "设备注册信息错误,暂时无法使用");
			return mapping.findForward("returninfo");
		}finally{
			
		}
		
	}

}
