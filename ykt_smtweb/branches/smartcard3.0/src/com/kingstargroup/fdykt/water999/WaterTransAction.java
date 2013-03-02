package com.kingstargroup.fdykt.water999;

import java.sql.SQLException;
import java.util.HashMap;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.util.XMLGenerateUtil;

public class WaterTransAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(WaterTransAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = dotrans(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward dotrans(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		String cardId = request.getParameter("cardId");
		String money = request.getParameter("money");
		String cardBala = request.getParameter("cardBala");
		String waterBala = request.getParameter("waterBala");
		String txCnt = request.getParameter("txCnt");
		String txCnt1 = request.getParameter("txCnt1");
		String tradecode = request.getParameter("tradecode");
		String sphone3 = request.getParameter("sphone3");
		String saddr =request.getParameter("saddr");	
		String packetno = request.getParameter("packetno");	
		String outCardAmount = request.getParameter("outCardAmount");
		String outCardAmount1 =request.getParameter("outCardAmount1");
		HashMap datamap = new HashMap();
		datamap.put("OutCardAmount", outCardAmount);
		datamap.put("OutCardAmount1", outCardAmount1);
		datamap.put("CardId", cardId);
		datamap.put("txCnt", txCnt);
		datamap.put("txCnt1", txCnt1);
		datamap.put("Amount", money);
		datamap.put("tradecode", tradecode);
		datamap.put("sphone3", sphone3);
		datamap.put("saddr", saddr);
		datamap.put("packetno", packetno);
		datamap.put("cardBala", cardBala);
		datamap.put("waterBala", waterBala);
		
		String xmlout = XMLGenerateUtil.XMLGenerate(
				"0000", "水控转账成功", datamap,null);
		XMLGenerateUtil.XMLSendOut(request, response,
				xmlout);
		return null;

	}
}
