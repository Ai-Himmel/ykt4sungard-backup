package com.kingstargroup.fdykt.cardchange;

import java.io.UnsupportedEncodingException;
import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.dao.DB2CustomerDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.NewCardInfoDTO;

public class NewCardCheckAction extends Action {
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

		String showcardno = request.getParameter("showcardno");
		String newcardphyid = request.getParameter("newcardphyid");
		DB2CustomerDAO custdao = new DB2CustomerDAO();
		NewCardInfoDTO newcardinfodto = custdao.getNewCardInfo(showcardno);
		if (newcardinfodto != null) {
			if (newcardinfodto.getStatus()==4) {
				return (mapping.findForward("done"));
			}else{
				request.setAttribute("newcardinfodto", newcardinfodto);
				request.setAttribute("newcardphyid", newcardphyid);
				return (mapping.findForward("success"));
			}
		} else {
			return (mapping.findForward("failure"));
		}
	}
}
