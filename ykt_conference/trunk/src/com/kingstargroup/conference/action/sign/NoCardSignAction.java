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
			String duty = ParamUtil.getString(request,"duty");
			request.setAttribute("result",AttendeeUtil.getCustListMap(confid,custno,custname,duty,deptcode));
			request.setAttribute("custno",custno);
			request.setAttribute("custname",custname);
			request.setAttribute("duty",duty);
			request.setAttribute("deptcode",deptcode);
			request.setAttribute("confid",new Integer(confid));
			return mapping.findForward("nocardsign");
			
		}else if ("sign".equals(cmd)){
			int custid = ParamUtil.getInteger(request,"custid");
			String signtime = ParamUtil.getString(request,"signtime");
			if (custid==0){
				request.setAttribute("tipinfo","ǩ��ʧ��:��ѡ��Ҫǩ���������Ա��");
				return mapping.findForward("error");
			}
			if (SignUtil.getSignedOrNot(confid,custid)){
				request.setAttribute("tipinfo","�������Ա�Ѿ�ǩ����");
				return mapping.findForward("error");
			}
			if (SignUtil.attendeeNoCardSign(confid,custid,signtime)){
				request.setAttribute("tipinfo",GetDictionary.getCustNameById(custid)+"ǩ���ɹ���");
				return mapping.findForward("succeed");
			}else{
				request.setAttribute("tipinfo","ǩ��ʧ�ܣ�����ԭ��");
				return mapping.findForward("error");
			}
		}
		return null;
	}

}
