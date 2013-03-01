package com.kingstargroup.advquery.struts.actions;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstar.bcc.bccclt;
import com.kingstargroup.advquery.common.BccctlInit;
import com.kingstargroup.advquery.hibernate.util.CustomerUtil;


public class LostCardAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) throws Exception {
		 
			   
		        String custId = request.getParameter("custId");
		        
		        String state = CustomerUtil.getStateByCustId(custId);
		        if(state !=null ){
		        	if (state.substring(1, 2).equals("1")) {
		        		request.setAttribute("errorcont",new String("�˿��ѹ�ʧ�򱻶��ᣬ�����ٹ�ʧ"));
						return mapping.findForward("errortest");
					}
		        	
		        }
		        
			    long xpackhandle = 0;
				int drtpno = 0;
				int errcode[] = { 1 };
				byte errmsg[] = new byte[300];
				int branchno = 0;// ��̨drtp���ܺ�
				int mainfunction = 9000;
				int func = 847318;// ��̨ҵ���ܺ�
				int tries =3;
				int[] RetCode = new int[1];
				int[] RecordCount = new int[1];
				bccclt bcc = null;
			     
				
				bcc = BccctlInit.getBccctlInstance();
				xpackhandle = bcc.NewXpackHandle(BccctlInit.getCpack().getBytes());
			try{  
				if (0 != xpackhandle){
					bcc.SetRequestType(xpackhandle, func);
					bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
							Integer.parseInt(custId));// �ͻ���
					bcc.SetIntFieldByName(xpackhandle, 0, "lvol1".getBytes(),
							Integer.parseInt("0"));// ���׿���
					bcc.SetIntFieldByName(xpackhandle, 0, "lvol2".getBytes(),
							Integer.parseInt("0"));// ���׿���
				/*	bcc.SetStringFieldByName(xpackhandle, 0, "semp_pwd"
							.getBytes(), password.getBytes());//����
					bcc.SetStringFieldByName(xpackhandle, 0, "sstatus0"
							.getBytes(), "1".getBytes());//У������
                */					
					bcc.SetStringFieldByName(xpackhandle, 0, "scust_limit"
							.getBytes(), "web".getBytes());//����
					boolean bccret = false;
					
				
					while (--tries >= 0) {
						bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
								mainfunction, 2000, errcode, errmsg);
						if (bccret) {
							break;
						}
					}
					
					if (bccret) {
						bcc.GetRetCode(xpackhandle, RetCode);
						bcc.GetRecordCount(xpackhandle, RecordCount);
						if (0 == RetCode[0]) {
							request.setAttribute("errorcont",new String("�˿���ʧ�ɹ���"));
							return mapping.findForward("success");
						} else {
							// ʧ��
							if (0 < RecordCount[0]) {
								byte[] vsmess = new byte[300];
								bcc.GetStringFieldByName(xpackhandle, 0,
										"vsmess".getBytes(), vsmess, 300);
								int i;
								for (i = 0; i < vsmess.length; i++) {
									if (vsmess[i] == 0) {
										break;
									}
								}
								String vs_mess = new String(vsmess, 0, i);
								request.setAttribute("errorcont",vs_mess);
								return mapping.findForward("errortest");
							} else {
								
								request.setAttribute("errorcont","��̨����ʧ��");
								return mapping.findForward("errortest");
							}

						}

					}else{
						// ����ʧ��
						request.setAttribute("errorcont","��̨ͨ���쳣,����ʧ��");
						return mapping.findForward("errortest");
					
					}
					 
				}else{
					 request.setAttribute("errorcont",new String("�˹�����ʱ����ʹ��,cpack·������"));
					 return mapping.findForward("errortest");
				}
			
			}catch(UnsatisfiedLinkError e){
				
				_log.error(e.getMessage());
				request.setAttribute("errorcont","ϵͳ��ʼ���쳣���Ժ����ԣ�");
				return mapping.findForward("errortest");
			
			}catch(Exception e){
	
				_log.error(e.getMessage());
				request.setAttribute("errorcont","��ʧ��ʧ��!���Ժ����ԣ�");
				return mapping.findForward("errortest");
			
			} finally {
				if (xpackhandle != 0) {
					bcc.DeleteXpackHandle(xpackhandle);
				}
	      }
			
        }
	private static final Logger _log = Logger.getLogger(LostCardAction.class);
}