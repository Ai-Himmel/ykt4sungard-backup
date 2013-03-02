package com.kingstargroup.conference.action.synchronize;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.httpclient.HttpClient;
import org.apache.commons.httpclient.HttpStatus;
import org.apache.commons.httpclient.methods.GetMethod;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionError;
import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.validator.DynaValidatorForm;

import com.kingstargroup.conference.common.SimpleEncoding;
import com.kingstargroup.conference.util.SynchronizeUtil;

public class DataConfigureAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		DynaValidatorForm dyform = (DynaValidatorForm) form;	   
		String url = request.getParameter("url");
		String username = dyform.get("username").toString();
		String password = dyform.get("password").toString();
		String flag = request.getParameter("flag");
		ActionErrors messages = new ActionErrors();
		try {
			if (null != flag && !"".equals(flag)) {
				if (null == url || "".equals(url)) {
					messages.add("conferenceurl", new ActionError(
							"dbconfigure.urlnoempty"));
					saveErrors(request, messages);
					return mapping.findForward("dbconf");
				}
				
				if (null == username || "".equals(username)) {
					messages.add("username", new ActionError(
							"dbconfigure.usernamenoempty"));
					saveErrors(request, messages);
					return mapping.findForward("dbconf");
				}
				if (null == password || "".equals(password)) {
					messages.add("password", new ActionError(
							"dbconfigure.passwordnoempty"));
					saveErrors(request, messages);
					return mapping.findForward("dbconf");
				}
				
				if(url.endsWith("/")){
					url+="DatabaseConfigure.do";
				}else{
					url+="/DatabaseConfigure.do";
				}
				
				HttpClient client = new HttpClient();
				GetMethod method = new GetMethod(url);
				int state = client.executeMethod(method);
				String config = "";
				String databaseIP = "";
				String port ="";
				String dbname ="";
				String dbusername="";
				String dbpassword="";
				if(HttpStatus.SC_OK==state){
					String body = method.getResponseBodyAsString();
					config = new String(SimpleEncoding.decode(SimpleEncoding.hex2byte(body),"kingstar".getBytes()));
					String[] confs = config.split("&");
					databaseIP = confs[0];
					port = confs[1];
					dbname = confs[2];
					dbusername =confs[3];
					dbpassword =confs[4];
					SynchronizeUtil synutil = new SynchronizeUtil();
					if (synutil.Chekdatabase(databaseIP, port, dbname,
							dbusername, dbpassword)) {
						//用户名密码验证
						if(synutil.checkuser(databaseIP, port, dbname, dbusername, dbpassword, username, password)){
						List confList = synutil.getConferenceList(
								databaseIP, port, dbname, dbusername, dbpassword,username);
						dyform.set("dbconfigure", config);
						request.setAttribute("confList", confList);
						return mapping.findForward("datasynch");
						}else{
							messages.add("errorinfo", new ActionError("dbconfigure.userorpwderror"));
							saveErrors(request, messages);
							return mapping.findForward("dbconf");
						}
					}
				}else{
					//服务器有问题
					messages.add("errorinfo", new ActionError("dbconfigure.urlerror"));
					saveErrors(request, messages);
					return mapping.findForward("dbconf");
					
				}		
				
			}else{
				return mapping.findForward("dbconf");
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		messages.add("errorinfo", new ActionError("dbconfigure.connecterror"));
		saveErrors(request, messages);
		return mapping.findForward("dbconf");
	}

}
