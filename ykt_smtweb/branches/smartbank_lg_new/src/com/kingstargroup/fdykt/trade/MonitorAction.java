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
		
		
		String deviceId = request.getParameter("deviceId");
		if (deviceId == null || "".equals(deviceId)) {
			request.setAttribute("msg", "�����ԱΪ������ע��һ���豸��");
			return mapping.findForward("returninfo");
		}
	
		long xpackhandle = 0;
		int drtpno = 1;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// ��̨drtp���ܺ�
		int bankmainfunction = KSConfiguration.getInstance().getPropertyAsInt("bankmainfunction", 9998);
		int func = KSConfiguration.getInstance().getPropertyAsInt("banktransferfunction", 900077);// ��̨ҵ���ܺ�
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 1);// Ĭ�����Դ���
	    int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		
		try {
			bcc = BccctlInit.getBccctlInstance();
	
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
				
				bcc.SetStringFieldByName(xpackhandle, 0, "sclose_emp"
						.getBytes(), "240108".getBytes());//���״���
			
				bcc.SetStringFieldByName(xpackhandle, 0, "sorder2"
						.getBytes(), deviceId.getBytes());//�豸��
				
				bcc.SetStringFieldByName(xpackhandle, 0, "scust_no".getBytes(),
						 "web".getBytes());/// ����Ա

				boolean bccret = false;
				while (--tries >= 0) {
					bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
							bankmainfunction, 3000, errcode, errmsg);
					if (bccret) {
						break;
					}
				}
				if (bccret) {
					logger.error("���������ɹ� ��" +RetCode[0] );
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					
					if (0 == RetCode[0]) {
						
						if (0 < RecordCount[0]) {
						    
						/*	byte[] key = new byte[16];
							bcc.GetStringFieldByName(xpackhandle, 0, "sstation0"
									.getBytes(), key, 16);*/
							
						//	DesUtil.getDesPassword("170800",key);
							
						//	System.out.println(DesUtil.getDesPassword("170800",key));
							/*ServletContext  app = request.getSession().getServletContext();
							app.setAttribute("pinkey",key);
							*/
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
					 logger.error("��������ʧ��");
				
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
