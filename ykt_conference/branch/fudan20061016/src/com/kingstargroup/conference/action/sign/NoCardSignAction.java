package com.kingstargroup.conference.action.sign;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.common.DateUtilExtend;
import com.kingstargroup.conference.common.ParamUtil;
import com.kingstargroup.conference.util.AttendeeUtil;
import com.kingstargroup.conference.util.GetDictionary;
import com.kingstargroup.conference.util.SignUtil;

/**
 * �޿�ǩ��
 * @author hjw
 *
 */
public class NoCardSignAction extends Action{

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
			String dlgtcode = ParamUtil.getString(request, "dlgtcode");
			String duty = ParamUtil.getString(request,"duty");
			request.setAttribute("result",AttendeeUtil.getCustListMapSPE(confid,custno,custname,duty,deptcode,dlgtcode));
			request.setAttribute("custno",custno);
			request.setAttribute("custname",custname);
			request.setAttribute("duty",duty);
			request.setAttribute("deptcode",deptcode);
			request.setAttribute("dlgtcode",dlgtcode);
			request.setAttribute("confid",new Integer(confid));
			return mapping.findForward("nocardsign");
			
		}else if ("sign".equals(cmd)){
	//		String[] custid = request.getParameterValues("custid");
			String custids = request.getParameter("custids");
			if(custids.lastIndexOf(",")==-1){
				request.setAttribute("tipinfo","ǩ��ʧ��:��ѡ��Ҫǩ���������Ա��");
				return mapping.findForward("error");
			}
			custids = custids.substring(0,custids.lastIndexOf(","));
			String[] custid = custids.split(",");
	//		String signtime = ParamUtil.getString(request,"signtime");
			String signtime = DateUtilExtend.getNowTime();

//			for(int i=0;i<custid.length;i++){
//				if (SignUtil.getSignedOrNot(confid,Integer.parseInt(custid[i]))){
//					request.setAttribute("tipinfo","�������Ա "+custid[i]+" �Ѿ�ǩ����");
//					return mapping.findForward("error");
//				}
//			}
			String custs ="";
			int ret = SignUtil.attendeeNoCardSign(confid,custid,signtime);
			if (ret ==1){				
				for(int i=0;i<custid.length;i++){
					custs+=GetDictionary.getCustNameById(Integer.parseInt(custid[i]))+" ";
				}
				request.setAttribute("tipinfo",custs+"ǩ���ɹ���");
				return mapping.findForward("succeed");
			}else if(ret ==2){
				request.setAttribute("tipinfo","��ѡ��Ա��ȫ��ǩ����������ǩ��");
				return mapping.findForward("error");
			}else{
				request.setAttribute("tipinfo","ǩ��ʧ�ܣ�����ԭ��");
				return mapping.findForward("error");
			}
		}else if ("unsign".equals(cmd)){
			String custids = request.getParameter("custids");
			if(custids.lastIndexOf(",")==-1){
				request.setAttribute("tipinfo","ǩ��ʧ��:��ѡ��Ҫȡ��ǩ���������Ա��");
				return mapping.findForward("error");
			}
			custids = custids.substring(0,custids.lastIndexOf(","));
			String[] custid = custids.split(",");
			String signtime = DateUtilExtend.getNowTime();
			String custs ="";
			int ret = SignUtil.attendeeNoCardUnSign(confid,custid,signtime);
			if (ret == 1){
				
				for(int i=0;i<custid.length;i++){
					custs+=GetDictionary.getCustNameById(Integer.parseInt(custid[i]))+" ";
				}
				request.setAttribute("tipinfo",custs+"ȡ��ǩ���ɹ���");
				return mapping.findForward("succeed");
			}else if(ret ==2){
				request.setAttribute("tipinfo","��ѡ��Աȫδǩ��������ȡ����");
				return mapping.findForward("error");				
			}else{
				request.setAttribute("tipinfo","ȡ��ǩ��ʧ�ܣ�����ԭ��");
				return mapping.findForward("error");
			}
		}
		return null;
	}

}
