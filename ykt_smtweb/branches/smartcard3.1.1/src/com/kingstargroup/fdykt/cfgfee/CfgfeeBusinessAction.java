package com.kingstargroup.fdykt.cfgfee;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstar.itemconfig.Configitem;
import com.kingstar.itemconfig.ItemConfigDocument;
import com.kingstar.itemconfig.ItemConfigDocument.ItemConfig;
import com.kingstargroup.fdykt.ConfigItemInit;

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

		//’“≥ˆ≈‰÷√
		ItemConfigDocument itemconfigdocument = ConfigItemInit.getInstance();
		if(itemconfigdocument!=null){
			ItemConfig itemconfig = itemconfigdocument.getItemConfig();
			Configitem cfgitemArr[] = itemconfig.getItemArray();
			request.setAttribute("cfgitemArr", cfgitemArr);
			
		}	
		
		return (mapping.findForward("success"));
	}

}
