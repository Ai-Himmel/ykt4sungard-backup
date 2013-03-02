package com.kingstargroup.conference.action.nocardimp;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.common.DateUtilExtend;
import com.kingstargroup.conference.util.AttendeeUtil;
import com.kingstargroup.conference.util.GetDictionary;
import com.kingstargroup.conference.util.SignUtil;

public class NoCardNoInfoAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String cmd = request.getParameter("cmd");
		String  confid = request.getParameter("confid");
		String  custname = request.getParameter("custname");
		if("query".equals(cmd)){
		try {
			if(confid==null){
				 request.setAttribute("tipinfo",NoCardConstant.SELECTCONF);
				 return mapping.findForward("error");
			}
			 List result = AttendeeUtil.findNocardNoInfoByName(confid,custname);
			 request.setAttribute("custname",custname);
			 request.setAttribute("confid",new Integer(confid));
			 request.setAttribute("result", result);
			return mapping.findForward("nocardnoinfo");
		    }
			catch(Exception e){
				request.setAttribute("tipinfo",NoCardConstant.EXCEPTION);
				return mapping.findForward("error");
			}
		}else if("sign".equals(cmd)){
			String custids = request.getParameter("custids");
			if(custids.lastIndexOf(",")==-1){
				request.setAttribute("tipinfo","ǩ��ʧ��:��ѡ��Ҫǩ���������Ա��");
				return mapping.findForward("error");
			}
			custids = custids.substring(0,custids.lastIndexOf(","));
			String[] custid = custids.split(",");
			String signtime = DateUtilExtend.getNowTime();
			int ret = SignUtil.attendeeNoCardSign(Integer.parseInt(confid),custid,signtime);
			if (ret ==1){
				request.setAttribute("tipinfo","ǩ���ɹ���");
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
			int ret = SignUtil.attendeeNoCardUnSign(Integer.parseInt(confid),custid,signtime);
			if (ret == 1){
				request.setAttribute("tipinfo","ȡ��ǩ���ɹ���");
				return mapping.findForward("succeed");
			}else if(ret ==2){
				request.setAttribute("tipinfo","��ѡ��Աȫδǩ��������ȡ����");
				return mapping.findForward("error");				
			}else{
				request.setAttribute("tipinfo","ȡ��ǩ��ʧ�ܣ�����ԭ��");
				return mapping.findForward("error");
			}
		}
		return mapping.getInputForward();
	}
}
