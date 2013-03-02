package com.kingstargroup.fdykt.cfgfee;

import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstar.itemconfig.Configitem;
import com.kingstar.itemconfig.ItemConfigDocument;
import com.kingstar.itemconfig.ItemConfigDocument.ItemConfig;
import com.kingstargroup.fdykt.ConfigItemInit;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;

/**
 * <p>Title:Test</p>
 * <p>Description: </p>
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Company: kingstargroup</p>
 * @author
 * @version 1.0
 */

public class CfgfeeBusinessAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(CfgfeeBusinessAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		KSDaoSessionFactory.createSession();
		ActionForward forward = checklogin(mapping, request);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			logger.error("提交事务失败");
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward checklogin(ActionMapping mapping, HttpServletRequest request) {
		
		//找出配置
		ItemConfigDocument itemconfigdocument = ConfigItemInit.getInstance();
		if(itemconfigdocument!=null){
			ItemConfig itemconfig = itemconfigdocument.getItemConfig();
			Configitem cfgitemArr[] = itemconfig.getItemArray();
//			for(int i=0;i<cfgitemArr.length;i++){
//				Configitem cfgitem = cfgitemArr[i];
//				cfgitem.getStartTime()
//			}
			request.setAttribute("cfgitemArr", cfgitemArr);
			
		}	
		
		return (mapping.findForward("success"));
	}
}
