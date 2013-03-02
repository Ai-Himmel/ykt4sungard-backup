package com.kingstargroup.conference.action.sign;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.common.ParamUtil;
import com.kingstargroup.conference.util.SignUtil;

/**
 * ���
 * @author hjw
 *
 */
public class SignPreviewAction extends Action{

	public ActionForward execute(
			ActionMapping mapping, 
			ActionForm from, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		if (null==request.getParameter("confid")){
			request.setAttribute("tipinfo","û��ҪԤ���Ļ��飡");
			return mapping.findForward("error");
		}
		int confid=ParamUtil.getInteger(request,"confid");
		String selectType = ParamUtil.getString(request,"selecttype");
		String attendeesign = ParamUtil.getString(request,"attendeesign");
		if ("totle".equals(selectType)){
			if ("prev".equals(attendeesign)){
				request.setAttribute("conference",SignUtil.getConfInfoById(confid));
				//��Ӧ������
				request.setAttribute("totleattendee",new Integer(SignUtil.getConfTotleAttendeeByCofid(confid)));
				//ʵ������
				request.setAttribute("signednum",new Integer(SignUtil.getSignedNumByCofid(confid)));
				//�������
				request.setAttribute("leavenum",new Integer(SignUtil.getLeaveNumByConfid(confid).size()));
				request.setAttribute("leavelist",SignUtil.getLeaveNumByConfid(confid));
				//���ǩ������
				request.setAttribute("replacenum",new Integer(SignUtil.getReplaceNumByConfid(confid).size()));
				request.setAttribute("replacelist",SignUtil.getReplaceNumByConfid(confid));
				//����ǩ������
				request.setAttribute("csignednum",new Integer(SignUtil.getSignedNumByConfid(confid).size()));
				request.setAttribute("csignedlist",SignUtil.getSignedNumByConfid(confid));
				//δ������
				request.setAttribute("unsignnum",new Integer(SignUtil.getUnSignNumByConfid(confid).size()));
				request.setAttribute("unsignlist",SignUtil.getUnSignNumByConfid(confid));
				
				HttpSession session = request.getSession();
				session.setAttribute("confid",new Integer(confid));

				return mapping.findForward("preview");
				
			}else if ("sign".equals(attendeesign)){
				request.setAttribute("resultinfo",SignUtil.getSignedNumByConfid(confid));
				request.setAttribute("pretip","ǩ�����Ԥ������ǩ����Ա�б�");
				return mapping.findForward("previewinfo");
			}else if ("unsign".equals(attendeesign)){
				request.setAttribute("resultinfo",SignUtil.getUnSignNumByConfid(confid));
				request.setAttribute("pretip","ǩ�����Ԥ����δǩ����Ա�б�");
				return mapping.findForward("previewinfo");
			}else if ("leave".equals(attendeesign)){
				request.setAttribute("resultinfo",SignUtil.getLeaveNumByConfid(confid));
				request.setAttribute("pretip","ǩ�����Ԥ���������Ա�б�");
				return mapping.findForward("previewinfo");
			}else if ("replace".equals(attendeesign)){
				request.setAttribute("resultinfo",SignUtil.getReplaceNumByConfid(confid));
				request.setAttribute("pretip","ǩ�����Ԥ�������ǩ����Ա�б�");
				return mapping.findForward("previewinfo");
			}
			
		}else if ("delegray".equals(selectType)){
			request.setAttribute("delegraylist",SignUtil.getDelegrayListByConfid(confid));
			request.setAttribute("pretip","ǩ�����Ԥ���������ų�ϯ���ͳ��");
			return mapping.findForward("delegray");
		}
		return null;
	}

}
