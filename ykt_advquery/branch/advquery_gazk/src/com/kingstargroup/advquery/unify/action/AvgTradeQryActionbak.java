package com.kingstargroup.advquery.unify.action;

//��ѯһ�������������˵������ܽ���ƽ�����
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

import com.kingstargroup.advquery.cewolf.CustomerDrawChart;
import com.kingstargroup.advquery.cewolf.DrawBarSingleMap;
import com.kingstargroup.advquery.hibernate.util.TradeUtil;


public class AvgTradeQryActionbak extends Action{
	
	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest req, 
			HttpServletResponse res) throws Exception {
	

    //String json = readJSONString(req);
    
  /*  String json = req.getParameter("json");
    
    
    if(json==null ||"".equals(json)){
    	json = req.getAttribute("json")==null?"":req.getAttribute("json").toString();
    }
    
    if("".equals(json)){
    	req.setAttribute("error","����ʧ�ܣ�û�н��յ��������ݣ�");
    	return mapping.findForward("error");
    }
    
    JSONObject jsonObject = null;  
	
	 try{
	        jsonObject = new JSONObject(json);
	        
     	String begindate =    jsonObject.getString("begindate");
     	       begindate = begindate.substring(0,6);
     	       
     	String enddate = jsonObject.getString("enddate"); 	
     	       enddate = enddate.substring(0,6);
     	JSONArray arr = jsonObject.getJSONArray("persons");
     	if(arr.length()==0){
     		req.setAttribute("error","�������ݸ�ʽ����ȷ");
        	return mapping.findForward("error");
     	}
        
     	
    	String manIds = "";
    	String deptname="";//ֻ�ܲ�һ��������Ϣ
    	
    	 for(int i=0;i<arr.length();i++){
    		 		 
    		// String deptId = arr.getJSONObject(i).getString("deptId");
    		 deptname= arr.getJSONObject(i).getString("deptname");
    		 String manId = arr.getJSONObject(i).getString("manId");	
    		 
    		 manIds ="'"+manId+"',"+manIds;
    		 
    	 }
    	 manIds = manIds.substring(0,manIds.lastIndexOf(","));
    	 int count= arr.length();
     	 List list  = TradeUtil.getavgTrade(manIds, begindate, enddate, deptname); 
     	 
     	 String dateRange = ":"+begindate+"-"+enddate;
     	 String specStatTip = deptname+"�˾������ѽ��(Ԫ)";
     	 req.setAttribute("specStatTip",specStatTip);
     	 req.setAttribute("json",json);
     	 req.setAttribute("dateRange",dateRange);
    	 req.setAttribute("result",list);
    	 req.setAttribute("ylabel","��λ:Ԫ");
    	 req.setAttribute("json",json);
    	 
//    	����ͼ��
 		// ��������ͼ��ʾʱ�������
 		String fillData = "avgFee";
 		String xData = "avgFee";
 		String yData = "avgFee";
 		String barDataType = "float";
// 	 �Զ���ͼ����ʾҪ����Ĳ���
		// ��ʾ�Զ�����ɫ
		boolean showCustColor = true;
		// ��ʾ���������ֵ���ת����
		boolean showTextAxis = false;
		// ��ʾBarͼ���ϵ�����
		boolean showLabel = true;
		// ��ʾ�Զ���ͼ������ɫ
		boolean showBackgroundColor = true;
		// ��ʾ������
		boolean showOutLine = true;
		// ��ʾ������
		boolean showGrid = true;
		
		//showTextAxis = new ErrorInfo().showTextAxis(list);
	
		
		
		req.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
				showTextAxis, showLabel, showBackgroundColor, showOutLine,showGrid).getChartPostProcessor());
		
		
		
        //�������������ռ����ͼ�����ݼ�
		req.setAttribute(
				"consAvgData",new DrawBarSingleMap(list, fillData, xData, yData,barDataType).getDatasetProducer());		
		
		//����ͼ����ʾ����
        
    	
		return mapping.findForward("avgtraderesult");
    	 
    	 }catch (JSONException e) {
    		 req.setAttribute("error","��ѯ�����쳣JSONException��");
             return mapping.findForward("error");
         }catch(Exception e){
        	 req.setAttribute("error","��ѯ�����쳣Exception��");
        	 return mapping.findForward("error");
       }*/
		return  null;
}
    
	

	/* private String readJSONString(HttpServletRequest request){
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
	    }*/
}
