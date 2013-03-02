package com.kingstargroup.fdykt.trade;

import java.sql.SQLException;
import java.util.ArrayList;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.dao.DB2CustomerDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.TCardphytypeDTO;

public class LossQueryAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(LossQueryAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = mapping.findForward("failure");
		try {
			forward = doLossQuery(mapping, request);
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doLossQuery(ActionMapping mapping,
			HttpServletRequest request) {
		DB2CustomerDAO custdao = new DB2CustomerDAO();

		ArrayList<TCardphytypeDTO> list = custdao.getAvailCardPhytype();
		request.setAttribute("cardphytypeList", list);
			
		return mapping.findForward("logon");
	}
}
