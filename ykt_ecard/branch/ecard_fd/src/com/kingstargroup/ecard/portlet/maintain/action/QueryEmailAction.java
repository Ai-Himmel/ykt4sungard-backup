package com.kingstargroup.ecard.portlet.maintain.action;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.hibernate.util.WebDictionaryUtil;
import com.kingstargroup.ecard.hibernate.web.WebDictionary;
import com.liferay.portal.struts.PortletAction;

public class QueryEmailAction extends PortletAction {
	public ActionForward execute(ActionMapping mapping, ActionForm form,
		HttpServletRequest req, HttpServletResponse res) throws Exception {
		
		WebDictionary  webservice= WebDictionaryUtil.getDictionary("003","01");
		String service="";
		if(webservice!=null){
			service=webservice.getDicCaption();
		}
		
		WebDictionary  websendEmail= WebDictionaryUtil.getDictionary("004","01");
		String sendEmail="";
		if(websendEmail!=null){
			sendEmail=websendEmail.getDicCaption();
		}
		
		WebDictionary  webusername= WebDictionaryUtil.getDictionary("005","01");
		String username="";
		if(webusername!=null){
			username=webusername.getDicCaption();
		}
		
		WebDictionary  webpassword= WebDictionaryUtil.getDictionary("006","01");
		String password ="";
		if(webpassword!=null){
			password=webpassword.getDicCaption();
		}
		
		WebDictionary  webtitle = WebDictionaryUtil.getDictionary("007","01");
		String title ="";
		if(webtitle!=null){
			title=webtitle.getDicCaption();
		}
		
		List     list  = WebDictionaryUtil.getDictionaryByDicNo("008");
		
		
		WebDictionary  WebemailReport = WebDictionaryUtil.getDictionary("010", "0");
		String mailreport = "";
		if(WebemailReport!=null){
			mailreport=WebemailReport.getDicCaption();
		}
		
		WebDictionary  WebBeginDate = WebDictionaryUtil.getDictionary("011", "0");
		String beginDate ="";
		if(WebBeginDate!=null){
			beginDate = WebBeginDate.getDicCaption();
		}
		
		WebDictionary  WebSecondtimes  =  WebDictionaryUtil.getDictionary("012", "0");
		String secondtimes="";
		if(WebSecondtimes!=null){
			secondtimes = WebSecondtimes.getDicCaption();
		}
		
		
		req.setAttribute("emailReport",mailreport);
		req.setAttribute("beginDate",beginDate);
		req.setAttribute("secondtimes",secondtimes);
		req.setAttribute("service", service);
		req.setAttribute("sendEmail", sendEmail);
		req.setAttribute("username", username);
		req.setAttribute("password", password);
		req.setAttribute("title", title);
		req.setAttribute("list", list);
	
	 return  mapping.findForward("portlet.maintain.editemail");
  }

}
