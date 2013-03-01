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

import com.kingstargroup.advquery.common.DateUtil;
import com.kingstargroup.advquery.hibernate.util.InterfaceInfoUtil;
import com.kingstargroup.advquery.hibernate.util.TradeUtil;

public class QueryCardBalanceAction extends Action{
	
	
	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		
		try{
		  String  ticketIdOfUser =  request.getParameter("ticketIdOfUser");
		  
		 // ticketIdOfUser="00fe9b82-90f3-45a9-bf27-3112bc3d6aeb";
		  
		  String  ticketIdOfDept = request.getParameter("ticketIdOfDept");
		  
		//  tickedIdOfDept="aa555c18-6c9f-44dd-8f1a-2e27c4b53fe5";
		  
		  if("".equals(ticketIdOfUser)&&"".equals(ticketIdOfDept)){
			  request.setAttribute("errorcont",new String("请选择人员或部门信息！"));
			  return mapping.findForward("errortest");
		  }
       
        
		  List list = new ArrayList();
		  
		  //直接选人
		  if(ticketIdOfUser!=null && !"".equals(ticketIdOfUser)){
			  
			  List<User> users  = InterfaceInfoUtil.getSelectedUsersByTicketID(ticketIdOfUser);
			  
			  String manIds = InterfaceInfoUtil.getManIdByUsers(users);
			  
			  List  list1 = TradeUtil.getCardBalance(users,manIds,true,false);
			 
			 list.addAll(list1);
		  }else if(ticketIdOfDept !=null && !"".equals(ticketIdOfDept)){
			  
			  List users =  InterfaceInfoUtil.getSelectedUsersByDeptTicketID(ticketIdOfDept);
			  
			  String manIds  = InterfaceInfoUtil.getManIdsByGuIds(users);
			  
			  List   list2 = TradeUtil.getCardBalance(users, manIds,false,true);
			  
			  list.addAll(list2);
		  } 
		   
		request.setAttribute("title","个人卡余额信息查询结果");
		request.setAttribute("result",list);
      
  	    return mapping.findForward("cardbalance_queryresult");
  	
        }catch(Exception e){
        	request.setAttribute("error","查询数据异常！");
      	 return mapping.findForward("error");
     }
		
	}

}