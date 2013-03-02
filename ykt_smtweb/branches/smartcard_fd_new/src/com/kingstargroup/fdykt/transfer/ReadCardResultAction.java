package com.kingstargroup.fdykt.transfer;

import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.DB2CustomerDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.dto.CustomerDTO;
import com.kingstargroup.fdykt.logon.LogonAction;

public class ReadCardResultAction  extends Action {
	
	private static final Logger logger = Logger.getLogger(LogonAction.class);
	
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = readcard(mapping, form, request);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}
	
	
	public ActionForward readcard(ActionMapping mapping, ActionForm form,
			HttpServletRequest request) {

		KSDaoSessionFactory.createSession();
		
		try {
			DB2CardDAO carddao = new DB2CardDAO();
			DB2CustomerDAO custDao = new DB2CustomerDAO();
			String cardno = request.getParameter("cardno");
			//String bala = request.getParameter("bala");
			KSDaoSessionFactory.commit();
			
		    request.getSession().setAttribute("card_no_first",cardno);
		    //request.getSession().setAttribute("bala",bala);//��
		    String hexcardno = Integer.toHexString(Integer.parseInt(cardno))
			.toUpperCase();
	        for (int i = hexcardno.length(); i < 8; i++) {
		       hexcardno = "0" + hexcardno;//pad left
	        }
	        //CardDTO  card = carddao.getCardInfoById(hexcardno);
	        CardDTO card = carddao.getCardState(hexcardno);
			String stateId = card.getStateId();
			if("1100".equals(stateId)){
				request.setAttribute("msg","���ѹ�ʧ����ת�ˣ��뵽һ��ͨ�������Ĵ���");
				return mapping.findForward("failure");
			}else if("1010".equals(stateId)) {
				request.setAttribute("msg","���Ѷ��᲻��ת�ˣ��뵽һ��ͨ�������Ĵ���");
				return mapping.findForward("failure");
			}
	        CustomerDTO customer = custDao.getCustomerByCustId(card.getCosumerId());
	        request.getSession().setAttribute("customer",customer);
	       
			return (mapping.findForward("success"));
			
		} catch (SQLException e) {
			logger.error("�ύ����ʧ��");
			e.printStackTrace();
			request.setAttribute("msg","�޷���ȡ���ţ�ϵͳ�쳣���Ժ�����");
			return mapping.findForward("failure");
		}catch(Exception e){
			logger.error("�ύ����ʧ��");
			e.printStackTrace();
			request.setAttribute("msg","�޷���ȡ���ţ�ϵͳ�쳣���Ժ�����");
			return mapping.findForward("failure");
			
		}
		
	}

}
