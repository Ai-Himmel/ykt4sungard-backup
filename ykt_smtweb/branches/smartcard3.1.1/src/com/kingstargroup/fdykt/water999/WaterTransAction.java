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

import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.dao.DB2SysParaDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.SysParaDTO;
import com.kingstargroup.fdykt.util.DateUtil;
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
		
		String cardphyid = request.getParameter("cardphyid");
		String money = request.getParameter("money");
		String cardBala = request.getParameter("cardBala");
		String waterBala = request.getParameter("waterBala");
		String txCnt = request.getParameter("txCnt");
		String txCnt1 = request.getParameter("txCnt1");
		String sphone3 = request.getParameter("sphone3");
		String saddr =request.getParameter("saddr");	
		String outCardAmount = request.getParameter("outCardAmount");
		String outCardAmount1 =request.getParameter("outCardAmount1");
		String sdate3 = request.getParameter("sdate3");
		String stime3 =request.getParameter("stime3");
		String ipServer = KSConfiguration.getInstance().getProperty("drtpip1",
		"172.0.0.1");
		String drtpPort = KSConfiguration.getInstance().getProperty(
				"drtpport1", "4000");
		String svrFunc = KSConfiguration.getInstance().getProperty(
				"mainfunction1", "6000");
		String price1="10";
		String price2="10";
		String price3="10";
		String validatedate = DateUtil.getNewDateTime(sdate3, 90, "yyyyMMdd");		
		
		HashMap datamap = new HashMap();
		datamap.put("OutCardAmount", outCardAmount);
		datamap.put("OutCardAmount1", outCardAmount1);
		datamap.put("cardphyid", cardphyid);
		datamap.put("txCnt", txCnt);
		datamap.put("txCnt1", txCnt1);
		datamap.put("amount", money);
		datamap.put("sphone3", sphone3);
		datamap.put("saddr", saddr);
		datamap.put("cardBala", cardBala);
		datamap.put("waterBala", waterBala);
		datamap.put("sdate3", sdate3);
		datamap.put("stime3", stime3);
		datamap.put("ipServer", ipServer);
		datamap.put("drtpPort", drtpPort);
		datamap.put("svrFunc", svrFunc);
		datamap.put("price1", price1);
		datamap.put("price2", price2);
		datamap.put("price3", price3);
		datamap.put("validatedate", validatedate);
		
		String xmlout = XMLGenerateUtil.XMLGenerate(
				"0000", "水控转账成功", datamap,null);
		XMLGenerateUtil.XMLSendOut(request, response,
				xmlout);
		return null;

	}
}
