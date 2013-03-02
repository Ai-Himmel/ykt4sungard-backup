package org.king.check.web.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.king.check.domain.WebDictionary;
import org.king.check.domain.WebDictionaryKey;
import org.king.check.service.LeaveInfoService;
import org.king.framework.web.action.BaseAction;

public class EditEmailAction 
	extends BaseAction {
		private LeaveInfoService leaveInfoService;
		
		public void setLeaveInfoService(LeaveInfoService leaveInfoService) {
			this.leaveInfoService = leaveInfoService;
		}
		public ActionForward editEmail(ActionMapping mapping,
				ActionForm form, HttpServletRequest request,
				HttpServletResponse response) throws Exception {
			
		     String address = request.getParameter("address");
		     String email = request.getParameter("email");
		     String username = request.getParameter("username");
		     String password = request.getParameter("password");
		     String title = request.getParameter("title");
		     
		     WebDictionary dic1 = new WebDictionary();
		     WebDictionaryKey key1 = new WebDictionaryKey("001","01");
		     dic1.setId(key1);
		     dic1.setDicCaption(address);
		     dic1.setDicName("邮件服务器");
		     if(leaveInfoService.QueryEmail("001")==null){
		    	leaveInfoService.saveEmail(dic1);
		     }else{
		        leaveInfoService.updateEmail(dic1);
             }
		     
		     WebDictionary dic2 = new WebDictionary();
		     WebDictionaryKey key2 = new WebDictionaryKey("002","02");
		     dic2.setId(key2);
		     dic2.setDicCaption(email);
		     dic2.setDicName("发件箱");
		     if(leaveInfoService.QueryEmail("002")==null){
		    	 leaveInfoService.saveEmail(dic2);
		     }else{
		    	 leaveInfoService.updateEmail(dic2);
		     }
		     
		     WebDictionary dic3 = new WebDictionary();
		     WebDictionaryKey key3 = new WebDictionaryKey("003","03");
		     dic3.setId(key3);
		     dic3.setDicCaption(username);
		     dic3.setDicName("用户名");
		     if(leaveInfoService.QueryEmail("003")==null){
		         leaveInfoService.saveEmail(dic3);
		     }else{
		    	 leaveInfoService.updateEmail(dic3);
		     }
		     
		     
		     WebDictionary dic4 = new WebDictionary();
		     WebDictionaryKey key4 = new WebDictionaryKey("004","04");
		     dic4.setId(key4);
		     dic4.setDicCaption(password);
		     dic4.setDicName("密码");
		     if(leaveInfoService.QueryEmail("004")==null || leaveInfoService.QueryEmail("004").isEmpty()){
		    	 leaveInfoService.saveEmail(dic4);
		     }else{
		         leaveInfoService.updateEmail(dic4);
		     }
		     
		     WebDictionary dic5 = new WebDictionary();
		     WebDictionaryKey key5 = new WebDictionaryKey("005","05");
		     dic5.setId(key5);
		     dic5.setDicCaption(title);
		     dic5.setDicName("标题");
		     if(leaveInfoService.QueryEmail("005")==null || leaveInfoService.QueryEmail("005").isEmpty()){
		       leaveInfoService.saveEmail(dic5);
		     }else{
		       leaveInfoService.updateEmail(dic5);
		     }
		    
		     
		     return mapping.findForward("success");
		}
		

}
