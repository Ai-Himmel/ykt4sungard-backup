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
//接收查询数据
public class ReceiveMsgAction extends Action{
	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest req, 
			HttpServletResponse res) throws Exception {

	
    String json = req.getParameter("json")==null?"":req.getParameter("json").toString();
    String pama = req.getParameter("pama")==null?"":req.getParameter("pama").toString();
    
    if(pama==null ||"".equals(pama)){
    	req.setAttribute("errorcont","缺少参数pama");
    	return mapping.findForward("error");
    }
    
    if(json==null ||"".equals(json)){
    	json = req.getAttribute("json")==null?"":req.getAttribute("json").toString();
    }
    
    if("".equals(json)){
    	req.setAttribute("errorcont","请求失败，没有接收到请求数据！");
    	return mapping.findForward("error");
    }
    
    JSONObject jsonObject = null;  
	
	 try{
	    
		jsonObject = new JSONObject(json);
	        
     	String begindate =    jsonObject.getString("begindate");
     	       
     	       
     	String enddate = jsonObject.getString("enddate"); 	
     	      
     	JSONArray arr = jsonObject.getJSONArray("persons");
     	if(arr.length()==0){
     		req.setAttribute("errorcont","请求数据格式不正确");
        	return mapping.findForward("error");
     	}
     	
    	String manIds = "";
    	String deptname="";//只能查一个部门信息
    	//查询部门平均消费金额
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
    	 
    	} else if("outBalanceQry".equals(pama)){//查询个人消费金额
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
    	 req.setAttribute("errorcont","请求失败，请联系系统管理员，pama");
    	 return mapping.findForward("error");
	 }catch (JSONException e) {
		 req.setAttribute("errorcont","查询数据异常JSONException！");
         return mapping.findForward("error");
     }catch(Exception e){
    	 req.setAttribute("errorcont","查询数据异常Exception！");
    	 return mapping.findForward("error");
     }
	}
}
