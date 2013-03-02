package com.kingstargroup.fdykt.trade;

import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionError;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessages;

import com.kingstargroup.fdykt.KSConstant;
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.dto.SysParaDTO;
import com.kingstargroup.fdykt.util.XMLGenerateUtil;

public class GetDeadlineDateAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(GetDeadlineDateAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = doGetPara(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			logger.error(e.getMessage());
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doGetPara(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		DB2CardDAO carddao = new DB2CardDAO();
		try {

			String cardno = request.getParameter("cardno");
			String hexcardno = Integer.toHexString(Integer.parseInt(cardno))
					.toUpperCase();
			for (int i = hexcardno.length(); i < 8; i++) {
				hexcardno = "0" + hexcardno;// pad left
			}

			String xmlout ="";
			try {
				xmlout = carddao.getCardDeadlineDateById(hexcardno);

			} catch (Exception e) {
				// TODO: handle exception
				logger.error("卡信息读取失败");
				System.out.println("卡信息读取失败");
			}
			
			
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		} catch (Exception e) {
			// TODO Auto-generated catch block
			logger.error(e.getMessage());
			e.printStackTrace();
			String xmlout = "";
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}

	}
}
