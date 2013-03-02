package com.kingstargroup.conference.action.synchronize;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionError;
import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.validator.DynaValidatorForm;

import com.kingstargroup.conference.util.SynchronizeUtil;

public class DataSynchAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		DynaValidatorForm dyform = (DynaValidatorForm) form;	
		
		String databaseIP = "";
		String port = "";
		String dbname = "";
		String dbusername = "";
		String dbpassword = "";
		String username = dyform.get("username").toString();
//		String password = request.getParameter("password");
		String config = dyform.get("dbconfigure").toString();
		String[] conference = (String[])dyform.get("conference");
		String configs = "";
		String[] confs = config.split("&");
		databaseIP = confs[0];
		port = confs[1];
		dbname = confs[2];
		dbusername =confs[3];
		dbpassword =confs[4];
		ActionErrors messages = new ActionErrors();
		try {
			if (null == conference) {
				SynchronizeUtil synutil = new SynchronizeUtil();
				List confList = synutil.getConferenceList(databaseIP,
						port, dbname, dbusername, dbpassword,username);
				messages.add("meet", new ActionError(
						"datasynchronize.meetselect"));
				saveErrors(request, messages);
				request.setAttribute("dbconfigure", config);
				request.setAttribute("confList", confList);
				return mapping.findForward("datasynch");
			}  else {				
				for(int i=0;i<conference.length;i++){
					configs += conference[i]+",";
				}
				SynchronizeUtil synutil = new SynchronizeUtil();
				if (synutil.synchData(databaseIP, port, dbname,
						dbusername, dbpassword,username,configs.substring(0, configs.lastIndexOf(",")))) {
					request.setAttribute("tipinfo", "同步数据成功！");
					return mapping.findForward("success");
				} else {
					List confList = synutil.getConferenceList(
							databaseIP, port, dbname, dbusername, dbpassword,username);
					messages.add("errorinfo", new ActionError(
							"datasynchronize.synerror"));
					saveErrors(request, messages);
					request.setAttribute("dbconfigure", config);
					request.setAttribute("confList", confList);
					return mapping.findForward("datasynch");
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		messages.add("errorinfo", new ActionError(
				"datasynchronize.exceptionoccur"));
		saveErrors(request, messages);
		return mapping.findForward("datasynch");
	}

}
