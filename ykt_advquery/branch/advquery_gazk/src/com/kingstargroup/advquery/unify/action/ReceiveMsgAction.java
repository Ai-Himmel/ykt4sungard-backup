package com.kingstargroup.advquery.unify.action;


import java.util.ArrayList;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;    


import com.kingstargroup.advquery.unify.UnifyObject;
//���ղ�ѯ����
public class ReceiveMsgAction extends Action{
	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest req, 
			HttpServletResponse res) throws Exception {

	
    String json = req.getParameter("json")==null?"":req.getParameter("json").toString();
    String pama = req.getParameter("pama")==null?"":req.getParameter("pama").toString();
    
    if(pama==null ||"".equals(pama)){
    	req.setAttribute("errorcont","ȱ�ٲ���pama");
    	return mapping.findForward("error");
    }
    
    if(json==null ||"".equals(json)){
    	json = req.getAttribute("json")==null?"":req.getAttribute("json").toString();
    }
    
    if("".equals(json)){
    	req.setAttribute("errorcont","����ʧ�ܣ�û�н��յ��������ݣ�");
    	return mapping.findForward("error");
    }
    
    JSONObject jsonObject = null;  
	
	 try{
	    
		jsonObject = new JSONObject(json);
	        
     	String begindate =    jsonObject.getString("begindate");
     	       
     	       
     	String enddate = jsonObject.getString("enddate"); 	
     	      
     	JSONArray arr = jsonObject.getJSONArray("persons");
     	if(arr.length()==0){
     		req.setAttribute("errorcont","�������ݸ�ʽ����ȷ");
        	return mapping.findForward("error");
     	}
     	
    	String manIds = "";
    	String deptname="";//ֻ�ܲ�һ��������Ϣ
    	//��ѯ����ƽ�����ѽ��
    	if("avgTradeQry".equals(pama)){
    		begindate = begindate.substring(0,6);
    		enddate = enddate.substring(0,6);
    	 for(int i=0;i<arr.length();i++){
    		 		 
    		// String deptId = arr.getJSONObject(i).getString("deptId");
    		 deptname= arr.getJSONObject(i).getString("deptname");
    		 String manId = arr.getJSONObject(i).getString("manId");		 
    		 manIds ="'"+manId+"',"+manIds;
    		 
    	 }
    	 manIds = manIds.substring(0,manIds.lastIndexOf(","));
    	 int count= arr.length();
    	 req.getSession().setAttribute("manIds",manIds);
    	 req.getSession().setAttribute("count",new Integer(count));
    	 req.getSession().setAttribute("begindate",begindate);
    	 req.getSession().setAttribute("enddate",enddate);
    	 req.getSession().setAttribute("deptname",deptname);
    	 
    	 return  mapping.findForward("avgtrade_qry");
    	 
    	} else if("outBalanceQry".equals(pama)){//��ѯ�������ѽ��
    		List arrlist = new ArrayList();
       	     for(int i=0;i<arr.length();i++){
       		 		 
       		 String deptId = arr.getJSONObject(i).getString("deptId");
       		 deptname= arr.getJSONObject(i).getString("deptname");
       		 String manId = arr.getJSONObject(i).getString("manId");	
       		 
       		 UnifyObject uo = new UnifyObject();
       		 uo.setDeptId(deptId);
       		 uo.setDeptName(deptname);
       		 uo.setManId(manId);
       		 arrlist.add(uo);
       		 
       		 manIds ="'"+manId+"',"+manIds;
       		 
       	 }
       	 manIds = manIds.substring(0,manIds.lastIndexOf(","));
       	 req.getSession().setAttribute("arrlist",arrlist);
       	 req.getSession().setAttribute("manIds",manIds);
       	 req.getSession().setAttribute("begindate",begindate);
    	 req.getSession().setAttribute("enddate",enddate);
    	 
	     return mapping.findForward("outbalance_qry");   
    	}
    	 req.setAttribute("errorcont","����ʧ�ܣ�����ϵϵͳ����Ա��pama");
    	 return mapping.findForward("error");
	 }catch (JSONException e) {
		 req.setAttribute("errorcont","��ѯ�����쳣JSONException��");
         return mapping.findForward("error");
     }catch(Exception e){
    	 req.setAttribute("errorcont","��ѯ�����쳣Exception��");
    	 return mapping.findForward("error");
     }
	}
}
