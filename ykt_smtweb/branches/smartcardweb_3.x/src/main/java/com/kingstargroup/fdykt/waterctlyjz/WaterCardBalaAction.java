package com.kingstargroup.fdykt.waterctlyjz;

import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionError;
import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.Util;
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.DB2TradeSerialDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.dto.CustomerDTO;
import com.kingstargroup.fdykt.dto.TTifSubsidyDTO;

/**
 * <p>Title:Test</p>
 * <p>Description: </p>
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Company: kingstargroup</p>
 * @author
 * @version 1.0
 */

public class WaterCardBalaAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		String bala = request.getParameter("bala");
		String sslrsb_waterBala = request.getParameter("sslrsb_waterBala");
		String ksfxyf_waterBala = request.getParameter("ksfxyf_waterBala");

		request.setAttribute("bala", bala);
		request.setAttribute("sslrsb_waterBala", sslrsb_waterBala);
		request.setAttribute("ksfxyf_waterBala", ksfxyf_waterBala);
		return mapping.findForward("success");
	}
}
