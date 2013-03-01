package com.kingstargroup.advquery.struts.actions;


import java.util.ArrayList;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.datacontract.schemas._2004._07.saff.User;

import com.kingstargroup.advquery.common.DateUtilExtend;
import com.kingstargroup.advquery.hibernate.util.InterfaceInfoUtil;
import com.kingstargroup.advquery.hibernate.util.TradeUtil;

public class QueryTradeSerialTotalAction extends Action{
	
	public ActionForward execute(
			ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		 
		  String  ticketIdOfUser =  request.getParameter("ticketIdOfUser");
		 // System.out.println("-------ticketIdOfUser--------"+ticketIdOfUser);
		 //ticketIdOfUser="00fe9b82-90f3-45a9-bf27-3112bc3d6aeb";
		 
		 // ticketIdOfUser = "bc18ff81-f4bf-481c-9de7-10d3fef01664";
		  
		  String  ticketIdOfDept = request.getParameter("ticketIdOfDept");
		 //  System.out.println("-------tickedIdOfDept--------"+ticketIdOfDept);
		  
		 //  tickedIdOfDept="aa555c18-6c9f-44dd-8f1a-2e27c4b53fe5";
		  
		  if("".equals(ticketIdOfUser)&&"".equals(ticketIdOfDept)){
			  request.setAttribute("errorcont",new String("请选择人员或部门信息！"));
			  return mapping.findForward("errortest");
		  }
		 
		  
       
		  List totallist = new ArrayList();
		  
		  String begindate = request.getParameter("begindate");
		  request.setAttribute("begindate", begindate);
		  String enddate =request.getParameter("enddate");
		  request.setAttribute("enddate", enddate);
		/*  long diffdays = DateUtilExtend.diffDate(begindate,enddate); 
		  if(diffdays>100){  
			  request.setAttribute("errorcont",new String("日期范围大于3个月,影响系统性能,请减少日期范围！"));
			  return mapping.findForward("errortest");
			  
		  } */
		  
		  
		  String dateRange = begindate+"-"+enddate;
		 // System.out.println("-------dateRange--------"+dateRange);
		 //直接选人
		  if(ticketIdOfUser!=null && !"".equals(ticketIdOfUser)){
			//  System.out.println("----users--begin--");
			  List<User> users  = InterfaceInfoUtil.getSelectedUsersByTicketID(ticketIdOfUser);
			//  System.out.println("----users----"+users.size());
			  String manIds = InterfaceInfoUtil.getManIdByUsers(users);
			//  System.out.println("-----manIds---"+manIds);
			  List  list1 = TradeUtil.getTradeTotal(users,manIds,begindate,enddate,true,false);
			//  System.out.println("----list1----"+list1.size());
			  totallist.addAll(list1);
		  }else if(ticketIdOfDept !=null && !"".equals(ticketIdOfDept)){
			  
			  List users =  InterfaceInfoUtil.getSelectedUsersByDeptTicketID(ticketIdOfDept);
			  
			  String manIds  = InterfaceInfoUtil.getManIdsByGuIds(users);
			  
			  List   list2 = new ArrayList();
				  
			  list2 = TradeUtil.getTradeTotal(users, manIds,begindate,enddate,false,true);
			  
			  totallist.addAll(list2);
		  } 
		 
		  
		  
		  
          // 绘制图形
  		// 定义柱形图显示时传入参数
  		/*String fillData = "avgFee";
  		String xData = "opeDate";
  		String yData = "avgFee";
  		String barDataType = "float";
  	   
          //自定义图表显示要传入的参数
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
  		
  	
  		request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
  				showTextAxis, showLabel, showBackgroundColor, showOutLine,showGrid).getChartPostProcessor());
  		
  		
  		
         //创建各卡类别所占数量图形数据集
  		request.setAttribute(
  				"consAvgData",new DrawBarSingleMap(list, fillData, xData, yData,barDataType).getDatasetProducer());		
  		
  		//绘制图形显示结束
  		
      	String specStatTip = dateRange+"人均消费金额(元)";
      	 
      	request.setAttribute("specStatTip",specStatTip);
      	request.setAttribute("dateRange",dateRange);
      	request.setAttribute("result",list);
      	request.setAttribute("ylabel","单位:元");*/
		  String specStatTip = dateRange+"个人消费金额(元)";
	      	 
	      	request.setAttribute("specStatTip",specStatTip);  
        request.setAttribute("result", totallist);
  	
           return  mapping.findForward("tradetotal_queryresult");
	}
	
	
	/*private  int  diffmonth(String begindate,String enddate){
		try{
		SimpleDateFormat   format   =   new   SimpleDateFormat("yyyyMM");   
		Date bdate = format.parse(begindate);
		Date edate =format.parse(enddate);
		 Calendar  bCal  =   Calendar.getInstance();   
		 Calendar  eCal   =   Calendar.getInstance();   
		 bCal.setTime(bdate);  
		 eCal.setTime(edate);
		 if(bCal.after(eCal)){   
			 return -1   ;
	     }   
		 int   year1   =   bCal.get(Calendar.YEAR);   
		 int   year2   =   eCal.get(Calendar.YEAR);         
		 int   month1   =   bCal.get(Calendar.MONTH);   
		 int   month2   =   eCal.get(Calendar.MONTH);   
		 return  (year2   -   year1)*12 -  (month1   -   month2);   
			}catch(Exception e){
				return -100;
			}
	}*/
}
