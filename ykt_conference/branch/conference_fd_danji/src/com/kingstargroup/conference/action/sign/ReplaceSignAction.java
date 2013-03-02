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
 * ���ǩ��
 * @author hjw
 *
 */
public class ReplaceSignAction extends Action{

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
			request.setAttribute("result",AttendeeUtil.getCustListReplaceMap(confid,custno,custname,duty,deptcode));
			request.setAttribute("custno",custno);
			request.setAttribute("custname",custname);
			request.setAttribute("duty",duty);
			request.setAttribute("deptcode",deptcode);
			request.setAttribute("confid",new Integer(confid));
			return mapping.findForward("replace");
			
		}else if ("sign".equals(cmd)){
			int custid = ParamUtil.getInteger(request,"custid");
			String repid = ParamUtil.getString(request,"repid");
			String repname = ParamUtil.getString(request,"repname");
			String repdept = ParamUtil.getString(request,"repdept");
			String repduty = ParamUtil.getString(request,"repduty");
			String repcomments = ParamUtil.getString(request,"repcomments");
	//		String signtime = ParamUtil.getString(request,"signtime");
			String signtime = DateUtilExtend.getNowTime();
			if (custid==0){
				request.setAttribute("tipinfo","��ǩʧ��:��ѡ��Ҫ��ǩ��Ա����");
				return mapping.findForward("error");
			}
			if (SignUtil.getSignedOrNot(confid,custid)){
				request.setAttribute("tipinfo","�������Ա�Ѿ�ǩ����");
				return mapping.findForward("error");
			}
			if(signtime.compareTo(SignUtil.getEndTimeByConid(confid))>0){
	            	request.setAttribute("tipinfo","�ѵ��������ʱ�䣬����ǩ��");
					return mapping.findForward("error");
	            }
			if (SignUtil.attendeeReplace(confid,custid,repid,repname,repdept,repduty,repcomments,signtime)){
				request.setAttribute("tipinfo",GetDictionary.getCustNameById(custid)+"��ǩ�ɹ���");
				return mapping.findForward("succeed");
			}else{
				request.setAttribute("tipinfo","��ǩʧ�ܣ�����ԭ��");
				return mapping.findForward("error");
			}
		}else if ("unsign".equals(cmd)){
			int custid = ParamUtil.getInteger(request,"custid");

			if (custid==0){
				request.setAttribute("tipinfo","ȡ����ǩʧ��:��ѡ��Ҫȡ����ǩ��Ա����");
				return mapping.findForward("error");
			}
			if (SignUtil.attendeeUnReplace(confid,custid)){
				request.setAttribute("tipinfo",GetDictionary.getCustNameById(custid)+"ȡ����ǩ�ɹ���");
				return mapping.findForward("succeed");
			}else{
				request.setAttribute("tipinfo","ȡ����ǩʧ�ܣ�����ԭ��");
				return mapping.findForward("error");
			}
		}
		return null;
	}

}
