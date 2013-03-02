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
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.util.RetMessageUtil;

public class UpdateCardInfoAction extends Action{
	
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = updateCard(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}
	
	private ActionForward updateCard(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		String deviceId = request.getAttribute("deviceId").toString();
		String cardno = request.getAttribute("cardno").toString(); 
		String pwd = request.getAttribute("pwd").toString();
		
		
		
		HttpSession session = request.getSession(true);
		ServletContext  app = request.getSession().getServletContext();
		
		if(app.getAttribute("pinkey")==null){
			return mapping.findForward("devicelogon");
		}	
	
	if (deviceId == null || "".equals(deviceId)) {
		request.setAttribute("msg", "�����ԱΪ������ע��һ���豸��");
		return mapping.findForward("returninfo");
	}
	
	DB2CardDAO carddao = new DB2CardDAO();
	
	String hexcardno = Integer.toHexString(Integer.parseInt(cardno))
			.toUpperCase();
	for (int i = hexcardno.length(); i < 8; i++) {
		hexcardno = "0" + hexcardno;//pad left
	}
	CardDTO card = new CardDTO();
	
	try {
		card = carddao.getCardInfoById(hexcardno);
	} catch (Exception e) {
		// TODO: handle exception
		//logger.error("����Ϣ��ȡʧ��"); 
		request.setAttribute("msg","����ʧ�ܣ�У԰�����Ų�����");
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

	try {
	
		bcc = BccctlInit.getBccctlInstance();
		xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance().getProperty("cpackfile", "/opt/cpack.dat").getBytes());
		if (0 != xpackhandle) {
			bcc.SetRequestType(xpackhandle, func);

			bcc.SetStringFieldByName(xpackhandle, 0, "sclose_emp"
					.getBytes(), "240105".getBytes());// ���״���

			bcc.SetStringFieldByName(xpackhandle, 0, "sname".getBytes(),
					deviceId.getBytes());// �豸��
			
			bcc.SetStringFieldByName(xpackhandle, 0, "semp_pwd".getBytes(),
					pwd.getBytes());//����
			
			bcc.SetStringFieldByName(xpackhandle, 0, "lvol0".getBytes(),
					card.getCardId().getBytes());// У԰������
			
			bcc.SetStringFieldByName(xpackhandle, 0, "scust_no".getBytes(),	"web".getBytes());/// ����Ա
			
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
					
						byte[] enddate = new byte[20];
						bcc.GetStringFieldByName(xpackhandle, 0, "sdate0"
								.getBytes(), enddate,20);//��ֹ����
						
						int i=0;
						for(;i<enddate.length;i++){
							if(0==enddate[i]){
								break;
							}
						}
						
					 
						
						int[] custtype = new int[1];
						bcc.GetIntFieldByName(xpackhandle, 0, "lvol1"
								.getBytes(), custtype);
						
						int[] feetype = new int[1];
						bcc.GetIntFieldByName(xpackhandle, 0, "lvol5"
								.getBytes(), feetype);//�շ����
						
						byte[] feename = new byte[30];
						bcc.GetStringFieldByName(xpackhandle, 0, "sbankname"
								.getBytes(), feename,30);//�շ��������
						
						int j=0;
						for(;j<feename.length;j++){
							if(0==feename[j]){
								break;
							}
						}
						
						
						byte[] name = new byte[50];
						bcc.GetStringFieldByName(xpackhandle, 0, "sname"
								.getBytes(), name,50);//����
						int k=0;
						for(;k<name.length;k++){
							if(0==name[k]){
								break;
							}
						}
						
						byte[] stuempno = new byte[20];
						bcc.GetStringFieldByName(xpackhandle, 0, "scust_limit"
								.getBytes(), stuempno,20);//ѧ����
						int m=0;
						for(;m<stuempno.length;m++){
							if(0==stuempno[m]){
								break;
							}
						}
						
						request.setAttribute("enddate",new String(enddate,0,i));
						request.setAttribute("stuempno",new String(stuempno,0,m));
						request.setAttribute("name",new String(name,0,k));
						request.setAttribute("feename",new String(feename,0,j));
						request.setAttribute("feetype",String.valueOf(feetype[0]));
						request.setAttribute("cardno",cardno);
						
						return mapping.findForward("success");
						
					}else{
						request.setAttribute("msg","�����ݷ��أ�ϵͳ�쳣"+RetCode[0]);
						return mapping.findForward("returninfo");
					
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
					request.setAttribute("msg",vs_mess+RetCode[0]);
					return mapping.findForward("returninfo");
				}

	           }
			}else{
             //����ʧ��
				request.setAttribute("msg","��̨ͨѶ��ʱ�����ã����Ժ�����!");
				return mapping.findForward("returninfo");
			}
		}
		request.setAttribute("msg","ϵͳ�����쳣�����Ժ�����,û��cpack��");
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
