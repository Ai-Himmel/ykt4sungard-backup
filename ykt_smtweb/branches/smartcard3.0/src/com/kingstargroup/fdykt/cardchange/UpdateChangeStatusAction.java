package com.kingstargroup.fdykt.cardchange;

import java.io.UnsupportedEncodingException;
import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.dao.DB2ChangeCardDAO;
import com.kingstargroup.fdykt.dao.DB2CustomerDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.NewCardInfoDTO;

public class UpdateChangeStatusAction extends Action {
	/**
	 * Logger for this class
	 */

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = doShowpacket(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doShowpacket(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		String stage = request.getParameter("stage");
		String showcardno = request.getParameter("showcardno");
		String error = request.getParameter("error");
		DB2ChangeCardDAO changecarddao = new DB2ChangeCardDAO();
		try {
			changecarddao.updateChangeCardStatus(stage, showcardno);
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		if ("2".equals(stage)) {
			return mapping.findForward("oldcardwriteerror");
		}else if ("3".equals(stage)) {
			if("1".equals(error)){
				return mapping.findForward("newcardwriteerror");
			}else if("2".equals(error)){
				return mapping.findForward("newcardwriteerror2");
			}else if("3".equals(error)){
				return mapping.findForward("newcardwriteerror3");
			}else{
				return mapping.findForward("newcardwriteerror");
			}
		}else{
			return mapping.findForward("oldcardwriteerror");
		}
	}
}
