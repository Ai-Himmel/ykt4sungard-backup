package com.kingstargroup.advquery.unify.action;

import java.util.List;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import com.kingstargroup.advquery.hibernate.util.TradeUtil;

//��ѯ�����������

public class OutBalanceQryAction extends Action{
	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest req, 
			HttpServletResponse res) throws Exception {
		
		   
	     /*  
	        try{
	  
	        	String manIds = req.getSession().getAttribute("manIds").toString();
	        	//String begindate = req.getSession().getAttribute("begindate").toString();
	        	//String enddate = req.getSession().getAttribute("enddate").toString();
	        	List arrlist = (List)req.getSession().getAttribute("arrlist");
        	
        	    List list = TradeUtil.getOutBalance(arrlist,manIds);
        	    
        	    req.setAttribute("title","���˿������Ϣ��ѯ���(Ԫ)");
        	    req.setAttribute("result",list);
	        
        	    return mapping.findForward("tradeoutbalance");
        	
              }catch(Exception e){
            	 req.setAttribute("error","��ѯ�����쳣Exception��");
            	 return mapping.findForward("error");
           }*/
		return null;
     }
}
