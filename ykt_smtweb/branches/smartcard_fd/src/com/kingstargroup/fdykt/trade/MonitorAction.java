package com.kingstargroup.fdykt.trade;

import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstar.bcc.bccclt;
import com.kingstargroup.fdykt.BccctlInit;
import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;


public class MonitorAction  extends Action{
	
	
	private static final Logger logger = Logger.getLogger(MonitorAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = Monitor(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}
	
	private ActionForward Monitor(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		String deviceId = request.getParameter("device");
		
		if (deviceId != null || !"".equals(deviceId)) {
			int begin = deviceId.indexOf("=")+1;
			deviceId = deviceId.substring(begin,deviceId.length());
		}else{
			return mapping.findForward("index");
		}
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// ��̨drtp���ܺ�
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt("mainfunction", 9000);
		int func = KSConfiguration.getInstance().getPropertyAsInt("logicfunc_sidy", 847315);// ��̨ҵ���ܺ�
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 1);// Ĭ�����Դ���
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			bcc = BccctlInit.getBccctlInstance();
			bcc.XPackInit(1);			
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance().getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
				
				bcc.SetStringFieldByName(xpackhandle, 0, "sclose_emp"
						.getBytes(), "deviceId".getBytes());

				boolean bccret = false;
				while (--tries >= 0) {
					bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
							mainfunction, 3000, errcode, errmsg);
					if (bccret) {
						break;
					}
				}
				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {
						    
						
							byte[] outcardmoney = new byte[11];
							bcc.GetStringFieldByName(xpackhandle, 0, "sserial1"
									.getBytes(), outcardmoney, 11);
							
							
							logger.info("�豸����");
						
							return mapping.findForward("index");
						} else {
						
							return  mapping.findForward("index");
						}

					} else {
						// ʧ��
						if (0 < RecordCount[0]) {

							
							return  mapping.findForward("index");
						} else {
						
							return  mapping.findForward("index");
						}

					}

				} else {
					// ����ʧ��

					int i;
					for (i = 0; i < errmsg.length; i++) {
						if (errmsg[i] == 0) {
							break;
						}
					}
					String msg = new String(errmsg, 0, i);
					
					logger.error("connect:errcode=" + errcode[0] + "msg=" + msg);
				
					 return  mapping.findForward("index");
				}
			}
			
			return mapping.findForward("index");
		
		} catch (Exception e) {
			// TODO: handle exception
		
			return  mapping.findForward("index");
		}catch(UnsatisfiedLinkError e){
			
			return null;
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
			
		}		
	  }
}
