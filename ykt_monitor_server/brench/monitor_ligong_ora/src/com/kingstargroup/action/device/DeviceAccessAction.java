package com.kingstargroup.action.device;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.Globals;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.util.MessageResources;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.Transaction;

import com.kingstargroup.action.user.ErrorCode;
import com.kingstargroup.commons.BaseAction;
import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.utils.XMLGenerateUtil;

public class DeviceAccessAction  extends BaseAction {
	
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession httpSession = request.getSession();
		// todo≈–∂œ–≈œ¢
		if (httpSession.getAttribute("userLogin") != null) {
			request.setCharacterEncoding("GBK");
			Transaction tx = null;
			String xmlOut = "";
			MessageResources msgResources = (MessageResources) this.getServlet()
					.getServletContext().getAttribute(Globals.MESSAGES_KEY);
			try {

				Session session = HibernateSessionFactory.currentSession();

				tx = session.beginTransaction();
				Query query = session.createQuery("select new com.kingstargroup.form.DeviceAccessList" +
						"(device.deviceId,device.deviceName,device.devphy999Id,device.devtype,b.devphy999Id," +
						"device.stateId,device.comadd) from TPifDevice  device,TPifDevice  b " +
						"where device.fdevId = b.deviceId and device.stateId <> 5 " +
						"Order by device.devtype desc");
				
				List list = query.list();
				tx.commit();
				xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
						.valueOf(list.size()), list);
				XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

			} catch (HibernateException e) {
				if (tx != null) {
					tx.rollback();
				}
				// server is busy!
				xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SERVER_IS_BUSY,
						msgResources.getMessage("server.state.SERVER_IS_BUSY"),
						null);
				XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

			} finally {
				HibernateSessionFactory.closeSession();
			}
		}
		return null;
	}

}
