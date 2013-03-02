package com.kingstargroup.advquery.unify;

import java.io.BufferedReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import com.kingstargroup.advquery.hibernate.util.TradeUtil;


//查询个人消费余额

public class OutBalanceQryAction extends Action{
	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest req, 
			HttpServletResponse res) throws Exception {
		
		 /* String json = readJSONString(req);
		    
		    if(json==null ||"".equals(json)){
		    	json = req.getAttribute("json")==null?"":req.getAttribute("json").toString();
		    }
		    
		    if("".equals(json)){
		    	req.setAttribute("error","请求失败，没有接收到请求数据！");
		    	return mapping.findForward("error");
		    }
	        
		     JSONObject jsonObject = null;  
	       
	        try{
	        jsonObject = new JSONObject(json);
	        
        //	String begindate =    jsonObject.getString("begindate");
        //	String enddate = jsonObject.getString("enddate"); 	
        	JSONArray arr = jsonObject.getJSONArray("persons");
        	
        	String manIds = "";
        	String deptname="";//只能同时查一个部门的信息
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
        	 List list = TradeUtil.getOutBalance(arrlist,manIds);
        	
        	 req.setAttribute("json",json);
        	 req.setAttribute("result",list);
	        
        	 return mapping.findForward("tradeoutbalance");
        	 }catch (JSONException e) {
        		 req.setAttribute("error","查询数据异常JSONException！");
                 return mapping.findForward("error");
             }catch(Exception e){
            	 req.setAttribute("error","查询数据异常Exception！");
            	 return mapping.findForward("error");
           }*/
		return null;
     }
	
	  
	

	
	 private String readJSONString(HttpServletRequest request){
	        StringBuffer json = new StringBuffer();
	        String line = null;
	        try {
	            BufferedReader reader = request.getReader();
	            while((line = reader.readLine()) != null) {
	                json.append(line);
	            }
	        }
	        catch(Exception e) {
	            System.out.println(e.toString());
	        }
	        return json.toString();
	    }
}
