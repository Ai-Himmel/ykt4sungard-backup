package com.kingstargroup.advquery.unify.action;

//查询一个部门下所有人的消费总金额和平均金额
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
    	req.setAttribute("error","请求失败，没有接收到请求数据！");
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
     		req.setAttribute("error","请求数据格式不正确");
        	return mapping.findForward("error");
     	}
        
     	
    	String manIds = "";
    	String deptname="";//只能查一个部门信息
    	
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
     	 String specStatTip = deptname+"人均月消费金额(元)";
     	 req.setAttribute("specStatTip",specStatTip);
     	 req.setAttribute("json",json);
     	 req.setAttribute("dateRange",dateRange);
    	 req.setAttribute("result",list);
    	 req.setAttribute("ylabel","单位:元");
    	 req.setAttribute("json",json);
    	 
//    	绘制图形
 		// 定义柱形图显示时传入参数
 		String fillData = "avgFee";
 		String xData = "avgFee";
 		String yData = "avgFee";
 		String barDataType = "float";
// 	 自定义图表显示要传入的参数
		// 显示自定义颜色
		boolean showCustColor = true;
		// 显示横坐标文字的旋转方向
		boolean showTextAxis = false;
		// 显示Bar图标上的数字
		boolean showLabel = true;
		// 显示自定义图表背景颜色
		boolean showBackgroundColor = true;
		// 显示轮廓线
		boolean showOutLine = true;
		// 显示网格线
		boolean showGrid = true;
		
		//showTextAxis = new ErrorInfo().showTextAxis(list);
	
		
		
		req.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
				showTextAxis, showLabel, showBackgroundColor, showOutLine,showGrid).getChartPostProcessor());
		
		
		
        //创建各卡类别所占数量图形数据集
		req.setAttribute(
				"consAvgData",new DrawBarSingleMap(list, fillData, xData, yData,barDataType).getDatasetProducer());		
		
		//绘制图形显示结束
        
    	
		return mapping.findForward("avgtraderesult");
    	 
    	 }catch (JSONException e) {
    		 req.setAttribute("error","查询数据异常JSONException！");
             return mapping.findForward("error");
         }catch(Exception e){
        	 req.setAttribute("error","查询数据异常Exception！");
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
