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
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.action.user.ErrorCode;
import com.kingstargroup.commons.BaseAction;
import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.form.DeviceAccessList;
import com.kingstargroup.form.MapSetsTable;
import com.kingstargroup.utils.XMLGenerateUtil;

public class DeviceAccessAction  extends BaseAction {
	
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession httpSession = request.getSession();
		// todo≈–∂œ–≈œ¢
		if (httpSession.getAttribute("userLogin") != null) {
			request.setCharacterEncoding("GBK");
			String xmlOut = "";
			MessageResources msgResources = (MessageResources) this.getServlet()
					.getServletContext().getAttribute(Globals.MESSAGES_KEY);
			try {
				Session session = HibernateSessionFactory.currentSession();
				Query query = session.createQuery("select new com.kingstargroup.form.DeviceAccessList" +
						"(device.deviceid,device.devicename,device.devphyid,device.devtypecode,b.devphyid," +
						"device.status,device.ip,'0') from TDevice device,TDevice b " +
						"where device.fdeviceid = b.deviceid and device.status ='1' " +
						"and device.devtypecode<>'0010' and device.devtypecode<>'0020' " +
						"Order by device.devtypecode desc");
				List list = query.list();
				
				Query query1 = session.createQuery("from MapSetsTable");
				List list1 = query1.list();
				String fdevphyid_Str="";
				for(int j=0;j<list1.size();j++){
					MapSetsTable mapsetstable = (MapSetsTable)list1.get(j);
					fdevphyid_Str+=mapsetstable.getSetsid()+",";
				}
				if(!"".equals(fdevphyid_Str)){
					for(int i=0;i<list.size();i++){
						DeviceAccessList deviceacess = (DeviceAccessList)list.get(i);
						if(deviceacess.getDevphy999Id()!=null){
							if(fdevphyid_Str.indexOf(deviceacess.getDevphy999Id())!=-1){
								deviceacess.setOnmap("1");
							}
						}
					}
				}
				xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
						.valueOf(list.size()), list);
				XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

			} catch (Exception e) {
				e.printStackTrace();
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
