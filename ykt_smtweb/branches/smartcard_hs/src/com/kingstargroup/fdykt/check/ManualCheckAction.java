package com.kingstargroup.fdykt.check;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessage;
import org.apache.struts.action.ActionMessages;

import com.kingstargroup.fdykt.Util;
import com.kingstargroup.fdykt.dao.DB2CustomerDAO;
import com.kingstargroup.fdykt.dao.DB2DeviceDAO;
import com.kingstargroup.fdykt.dao.DB2TradeCodeDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CustomerDTO;
import com.kingstargroup.fdykt.util.DateUtil;

/**
 * <p>Title:Test</p>
 * <p>Description: </p>
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Company: kingstargroup</p>
 * @author
 * @version 1.0
 */

public class ManualCheckAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(ManualCheckAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		KSDaoSessionFactory.createSession();
		ActionForward forward = check(mapping, request);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			logger.error("�ύ����ʧ��");
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward check(ActionMapping mapping, HttpServletRequest request) {
		
		    String stuempno = request.getParameter("stuempno");
		    String password = request.getParameter("password");
		    DB2CustomerDAO customerdao = new DB2CustomerDAO();
		    String name="";
		    String phyId="";
		    int    cardId=0;
		    ActionMessages messages   =    new   ActionMessages();


		    try {
		      if (stuempno.equals("") || password.equals("")) {
		    	  
		    	  request.setAttribute("msg","������ѧ���ź�����");
		           return mapping.findForward("failure");    		
							        
		      }
		
		      String ciphered=Util.DESEnc(password);
		      String sql="select * from ykt_cur.t_cif_customer cus " +
		                 "join  ykt_cur.T_PIF_Card card on cus.Cut_id=card.Cosumer_id " +
		                 "where cus.StuEmp_no='" + stuempno +"'"
		                 +" and card.password='" + ciphered +"'"
		                 +" and card.STATE_ID<>'2000'";
		       ArrayList customers = customerdao.CheckCustomer(sql);
		       if (customers==null || customers.size() == 0) {
		    	   request.setAttribute("msg","ѧ���Ż��������");
		           return mapping.findForward("failure");
		       }else {
		    	   
		         HttpSession session = request.getSession(true);
		         name= ((CustomerDTO) customers.get(0)).getCut_name();
		         cardId = ((CustomerDTO) customers.get(0)).getCardId();
		         phyId = ((CustomerDTO) customers.get(0)).getPhyId();
		        // session.setAttribute("name",name);
		                              
		         int cutid = ((CustomerDTO) customers.get(0)).getCut_id();
		         
		         if(!customerdao.getCheckManBycutId(cutid)){
		        	 
		        	 request.setAttribute("msg","�ǿ�����Ա�������ֹ�����");
					 
					 return mapping.findForward("failure");
		         }
		         
		     	List manualList = customerdao.getManualCheckList(cutid,DateUtil.getNow("yyyyMMdd"));
		     	if(manualList!=null){
				int manualSize = manualList.size();
				if (manualSize>0){
					Map manualMap = (Map)manualList.get(0);
					if (("2".equals(manualMap.get("IFOFFICE"))&& manualSize>=2)||
							("1".equals(manualMap.get("IFOFFICE"))&& manualSize>=8)){
						 request.setAttribute("msg","��������Աÿ���ֹ����ڼ�¼���ܴ���2����������Աÿ���ֹ����ڼ�¼���ܴ���8��");
						 return mapping.findForward("failure");
					}
				 }
		     	}
				 if(customerdao.insertCheck(cutid,cardId,phyId)){
				    request.setAttribute("msg",name+":�ֹ����ڳɹ�");
				 }else{
					 request.setAttribute("msg",name+":�ֹ�����ʧ�ܣ����ݿ��쳣"); 
					 return mapping.findForward("failure");
				 }
		         return mapping.findForward("success");
		     }
		} catch (Exception e) {
			 messages.add("", new ActionMessage("���ڳ����쳣�����Ժ�����"));
			 this.saveMessages(request, messages);  
			 return mapping.findForward("failure");
			
		}
	}
}
