package com.kingstargroup.conference.action.sign;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.common.ParamUtil;
import com.kingstargroup.conference.util.AttendeeUtil;
import com.kingstargroup.conference.util.GetDictionary;
import com.kingstargroup.conference.util.SignUtil;

/**
 * ���
 * @author hjw
 *
 */
public class LeaveAction extends Action{

	public ActionForward execute(
			ActionMapping mapping, 
			ActionForm from, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		String cmd = ParamUtil.getString(request,"cmd");
		int confid = ParamUtil.getInteger(request,"confid");
		if ("query".equals(cmd)){
			String custno = ParamUtil.getString(request,"custno");
			String custname = ParamUtil.getString(request,"custname");
			String deptcode = ParamUtil.getString(request,"deptcode");
			String duty = ParamUtil.getString(request,"duty");
			
			request.setAttribute("confid",new Integer(confid));
			request.setAttribute("custno",custno);
			request.setAttribute("custname",custname);
			request.setAttribute("duty",duty);
			request.setAttribute("deptcode",deptcode);
			request.setAttribute("result",AttendeeUtil.getCustListLeaveMap(confid,custno,custname,duty,deptcode));
			return mapping.findForward("leave");
			
		}else if ("sign".equals(cmd)){
			String custids = request.getParameter("custids");
			if(custids.lastIndexOf(",")==-1){
				request.setAttribute("tipinfo","���ʧ��:��ѡ��Ҫ��ٵ���Ա��");
				return mapping.findForward("error");
			}
			custids = custids.substring(0,custids.lastIndexOf(","));
			String[] custid = custids.split(",");

//			if (SignUtil.getSignedOrNot(confid,custid)){				
//				request.setAttribute("tipinfo",GetDictionary.getCustNameById(custid)+"�Ѿ�ǩ����");
//				return mapping.findForward("error");
//			}
			String reason = ParamUtil.getString(request,"reason");
			int ret = SignUtil.attendeeLeave(confid,custid,reason);
			if (ret==1){
				String custs ="";
				/*for(int i=0;i<custid.length;i++){
					custs+=GetDictionary.getCustNameById(Integer.parseInt(custid[i]))+" ";
				}*/
				request.setAttribute("tipinfo","��ٳɹ���");
				return mapping.findForward("succeed");
			}else if(ret ==2){
				request.setAttribute("tipinfo","��ѡ��Ա�Ѿ�ȫ����٣��������룡");
				return mapping.findForward("error");
			}else{
				request.setAttribute("tipinfo","���ʧ�ܣ�����ԭ��");
				return mapping.findForward("error");
			}
		}else if ("cleave".equals(cmd)){
			
			String custids = request.getParameter("custids");
			if(custids.lastIndexOf(",")==-1){
				request.setAttribute("tipinfo","����ʧ��:��ѡ��Ҫ��ٵ���Ա��");
				return mapping.findForward("error");
			}
			custids = custids.substring(0,custids.lastIndexOf(","));
			String[] custid = custids.split(",");
			
//			if (SignUtil.getSignedOrNot(confid,custid)){
//				request.setAttribute("tipinfo",GetDictionary.getCustNameById(custid)+"�Ѿ�ǩ����");
//				return mapping.findForward("error");
//			}
			int ret = SignUtil.attendeeCancleLeave(confid,custid);
			if (ret == 1){
				String custs ="";
				/*for(int i=0;i<custid.length;i++){
					custs+=GetDictionary.getCustNameById(Integer.parseInt(custid[i]))+" ";
				}*/
				request.setAttribute("tipinfo","���ٳɹ���");
				return mapping.findForward("succeed");
			}else if(ret ==2){
				request.setAttribute("tipinfo","��ѡ��Ա������٣��������٣�");
				return mapping.findForward("error");
			}else{
				request.setAttribute("tipinfo","����ʧ�ܣ�����ԭ��");
				return mapping.findForward("error");
			}
		}
		return null;
	}

}
