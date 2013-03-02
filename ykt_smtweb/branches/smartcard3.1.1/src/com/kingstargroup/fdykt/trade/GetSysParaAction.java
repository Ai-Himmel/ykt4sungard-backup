package com.kingstargroup.fdykt.trade;

import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.KSConstant;
import com.kingstargroup.fdykt.dao.DB2SysParaDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.SysParaDTO;
import com.kingstargroup.fdykt.util.XMLGenerateUtil;

public class GetSysParaAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(GetSysParaAction.class);

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
		DB2SysParaDAO sysParadao = new DB2SysParaDAO();
		try {
			String key = request.getParameter("key");
			if(null!=key&&"kingstar".equals(key)){
				SysParaDTO sysPara = sysParadao.getSysPara(KSConstant.DICT_MAINKEY);
				String xmlout = sysPara.getParaval();
				XMLGenerateUtil.XMLSendOut(request, response, xmlout);
				return null;
			}else{
				String xmlout = "";
				XMLGenerateUtil.XMLSendOut(request, response, xmlout);
				return null;
			}
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
