package com.kingstargroup.fdykt.cityhotspot;

import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.util.BdUtil;

public class CityHotspotCheckAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = docheck(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward docheck(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		String cardno = request.getParameter("cardno");
		String TransAmount = request.getParameter("TransAmount");
		String SerialNo = request.getParameter("SerialNo");
		String OutCardAmount = request.getParameter("OutCardAmount");
		String pwd = request.getParameter("pwd");
		String cxCnt = request.getParameter("cxCnt");
		
		String writecardmoney = String.valueOf(BdUtil.YuantoFen(OutCardAmount));
		
		request.setAttribute("writecardmoney",writecardmoney);
		request.setAttribute("pwd",pwd);
		request.setAttribute("cardno", cardno);
		request.setAttribute("TransAmount", TransAmount);
		request.setAttribute("SerialNo", SerialNo);
		request.setAttribute("OutCardAmount", OutCardAmount);	
		request.setAttribute("cxCnt", cxCnt);	
		
		return mapping.findForward("success");
						
	}
}
