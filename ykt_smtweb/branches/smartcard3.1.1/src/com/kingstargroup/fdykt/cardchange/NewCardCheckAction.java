package com.kingstargroup.fdykt.cardchange;

import java.io.UnsupportedEncodingException;
import java.sql.SQLException;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.dao.DB2CustomerDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.NewCardInfoDTO;
import com.kingstargroup.fdykt.dto.PursetypeDTO;

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
		long pursetype1 = 0;
		long pursetype2 = 0;
		long pursetype3 = 0;
		String pursetypename1="";
		String pursetypename2="";
		String pursetypename3="";
		DB2CustomerDAO custdao = new DB2CustomerDAO();
		NewCardInfoDTO newcardinfodto = custdao.getNewCardInfo(showcardno);
		if (newcardinfodto != null) {
			if (newcardinfodto.getStatus()==4) {
				return (mapping.findForward("done"));
			}else{
				List enablepursetypeList =  custdao.getEnablePursetype();
				for(int i=0;i<enablepursetypeList.size();i++){
					PursetypeDTO pursetype = (PursetypeDTO)enablepursetypeList.get(i);
					if(i==0){
						pursetype1 = pursetype.getPursetype();
						pursetypename1 = pursetype.getPursetypename();
					}
					if(i==1){
						pursetype2 = pursetype.getPursetype();
						pursetypename2 = pursetype.getPursetypename();
					}
					if(i==2){
						pursetype3 = pursetype.getPursetype();
						pursetypename3 = pursetype.getPursetypename();
					}
				}
				request.setAttribute("newcardinfodto", newcardinfodto);
				request.setAttribute("newcardphyid", newcardphyid);
				request.setAttribute("pursetype1", String.valueOf(pursetype1));
				request.setAttribute("pursetypename1", String.valueOf(pursetypename1));
				request.setAttribute("pursetype2", String.valueOf(pursetype2));
				request.setAttribute("pursetypename2", String.valueOf(pursetypename2));
				request.setAttribute("pursetype3", String.valueOf(pursetype3));
				request.setAttribute("pursetypename3", String.valueOf(pursetypename3));
				return (mapping.findForward("success"));
			}
		} else {
			return (mapping.findForward("failure"));
		}
	}
}
