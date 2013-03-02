package com.kingstargroup.fdykt.trade;

import java.sql.SQLException;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstar.bcc.bccclt;
import com.kingstargroup.fdykt.BccctlInit;
import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.util.BdUtil;
import com.kingstargroup.fdykt.util.RetMessageUtil;

public class FeeBalanceAction extends Action{
	
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = feebalance(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();   
		}
		return forward;
	}
	
	private  ActionForward feebalance(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		HttpSession session = request.getSession(true);
		String deviceId = request.getParameter("deviceId");
		//System.out.println("deviceId----------"+deviceId);
		String card_bala = request.getParameter("cardBala");
		//System.out.println("card_bala----------"+card_bala);
		String pwd = request.getParameter("password");
		//System.out.println("pwd----------"+pwd);
		String cxCnt = request.getParameter("cxCnt");
		//System.out.println("cxCnt----------"+cxCnt);
		String cardId = session.getAttribute("cardId").toString();
		//System.out.println("cardId----------"+cardId);
		String cardno = request.getParameter("cardno");
		//System.out.println("cardno----------"+cardno);
		
		double cardBala = Double.parseDouble(card_bala);
		cardBala = cardBala/100; 
		
	
		ServletContext  app = request.getSession().getServletContext();
		
		if(app.getAttribute("pinkey")==null){
			return mapping.findForward("devicelogon");
		}	
	
	
	if (deviceId == null || "".equals(deviceId)) {
		request.setAttribute("msg", "�����ԱΪ������ע��һ���豸��");
		return mapping.findForward("returninfo");
	}
	
	long xpackhandle = 0;
	int drtpno = 1;// ��2��drtp
	int errcode[] = { 1 };
	byte errmsg[] = new byte[300];
	int branchno = 0;// ��̨drtp���ܺ�
	int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
			"bankmainfunction", 9998);
	int func = KSConfiguration.getInstance().getPropertyAsInt(
			"banktransferfunction", 900077);// ��̨ҵ���ܺ�
	int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 1);
	int[] RetCode = new int[1];
	int[] RecordCount = new int[1];
	bccclt bcc = null;
	try{
		bcc = BccctlInit.getBccctlInstance();
		// System.out.print("---bcc over----");
		xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance().getProperty("cpackfile", "/opt/cpack.dat").getBytes());
		if (0 != xpackhandle) {
			bcc.SetRequestType(xpackhandle, func);
			bcc.SetStringFieldByName(xpackhandle, 0, "sclose_emp"
					.getBytes(), "240116".getBytes());// ���״���
			
			
			bcc.SetDoubleFieldByName(xpackhandle, 0,"damt0".getBytes(),cardBala);
			
			bcc.SetIntFieldByName(xpackhandle, 0, "sserial0".getBytes(),
					Integer.parseInt(cardId));// ����
			
			bcc.SetStringFieldByName(xpackhandle, 0, "sorder2".getBytes(),
					deviceId.getBytes());// �豸��
			
			bcc.SetStringFieldByName(xpackhandle, 0, "semp_pwd".getBytes(),
					pwd.getBytes());//����
			
			bcc.SetIntFieldByName(xpackhandle, 0, "lvol3".getBytes(),
					Integer.parseInt(cxCnt));// ���״���
			
			bcc.SetStringFieldByName(xpackhandle, 0, "scust_no".getBytes(),"web".getBytes());/// ����Ա
			
			boolean bccret = false;
			while (--tries >= 0) {
				bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
						mainfunction, 60000, errcode, errmsg);
				if (bccret) {
					break;
				}
			}
			if (bccret) {
				bcc.GetRetCode(xpackhandle, RetCode);
				bcc.GetRecordCount(xpackhandle, RecordCount);
				
				if (0 == RetCode[0]) {
					if (0 < RecordCount[0]) {
						double[] OutCardAmount = new double[1];
						bcc.GetDoubleFieldByName(xpackhandle, 0, "damt0"
								.getBytes(), OutCardAmount);//�뿨ֵ
						
						int writecard = BdUtil.YuantoFen(OutCardAmount[0]);
						//System.out.println("showmoney-----"+String.valueOf(OutCardAmount[0]));
						//System.out.println("writecardmoney-----"+String.valueOf(writecard));
						request.setAttribute("cardno",cardno);
						request.setAttribute("showmoney",String.valueOf(OutCardAmount[0]));
						request.setAttribute("writecardmoney",String.valueOf(writecard));
						request.setAttribute("cxCnt",String.valueOf(cxCnt));
						return mapping.findForward("success");
					}
				}else{
					String vs_mess = "";
					RetMessageUtil retmsg = new RetMessageUtil();
					vs_mess = retmsg.getMsg(RetCode[0]);
						// ʧ��
						if (0 < RecordCount[0]) {
							request.setAttribute("msg",vs_mess+RetCode[0]);
							return mapping.findForward("returninfo");
						} else {
							request.setAttribute("msg", "��������ʧ��,�����ݷ���,���Ժ�����");
							return mapping.findForward("returninfo");
						}
			        }
				}else{
					  //����ʧ��
					request.setAttribute("msg","��̨ͨѶ��ʱ�����ã����Ժ�����!");
					return mapping.findForward("returninfo");
				}
			}else{
				request.setAttribute("msg","ϵͳ�����쳣,��ʱ������,δ�ҵ�cpack�ļ�!");
				return mapping.findForward("returninfo");
			}
		request.setAttribute("msg","ϵͳ�����쳣�����Ժ����ԣ�");
		return mapping.findForward("returninfo");

	}catch (UnsatisfiedLinkError e) {
		
		request.setAttribute("msg","ϵͳ��ʼ���쳣�����Ժ����ԣ�");
		return mapping.findForward("returninfo");
	}catch(Exception e){
		request.setAttribute("msg","ϵͳ�����쳣�����Ժ����ԣ�");
		return mapping.findForward("returninfo");
	} finally {
		if (xpackhandle != 0) {
			bcc.DeleteXpackHandle(xpackhandle);
		}
	}	
  }
}