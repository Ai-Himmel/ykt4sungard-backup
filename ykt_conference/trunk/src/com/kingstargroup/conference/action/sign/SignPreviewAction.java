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
 * 请假
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
			request.setAttribute("tipinfo","没有要预览的会议！");
			return mapping.findForward("error");
		}
		int confid=ParamUtil.getInteger(request,"confid");
		String selectType = ParamUtil.getString(request,"selecttype");
		String attendeesign = ParamUtil.getString(request,"attendeesign");
		if ("totle".equals(selectType)){
			if ("prev".equals(attendeesign)){
				request.setAttribute("conference",SignUtil.getConfInfoById(confid));
				//总应到人数
				request.setAttribute("totleattendee",new Integer(SignUtil.getConfTotleAttendeeByCofid(confid)));
				//实到人数
				request.setAttribute("signednum",new Integer(SignUtil.getSignedNumByCofid(confid)));
				//请假人数
				request.setAttribute("leavenum",new Integer(SignUtil.getLeaveNumByConfid(confid).size()));
				request.setAttribute("leavelist",SignUtil.getLeaveNumByConfid(confid));
				//替代签到人数
				request.setAttribute("replacenum",new Integer(SignUtil.getReplaceNumByConfid(confid).size()));
				request.setAttribute("replacelist",SignUtil.getReplaceNumByConfid(confid));
				//正常签到人数
				request.setAttribute("csignednum",new Integer(SignUtil.getSignedNumByConfid(confid).size()));
				request.setAttribute("csignedlist",SignUtil.getSignedNumByConfid(confid));
				//未到人数
				request.setAttribute("unsignnum",new Integer(SignUtil.getUnSignNumByConfid(confid).size()));
				request.setAttribute("unsignlist",SignUtil.getUnSignNumByConfid(confid));
				
				HttpSession session = request.getSession();
				session.setAttribute("confid",new Integer(confid));

				return mapping.findForward("preview");
				
			}else if ("sign".equals(attendeesign)){
				request.setAttribute("resultinfo",SignUtil.getSignedNumByConfid(confid));
				request.setAttribute("pretip","签到情况预览－已签到人员列表");
				return mapping.findForward("previewinfo");
			}else if ("unsign".equals(attendeesign)){
				request.setAttribute("resultinfo",SignUtil.getUnSignNumByConfid(confid));
				request.setAttribute("pretip","签到情况预览－未签到人员列表");
				return mapping.findForward("previewinfo");
			}else if ("leave".equals(attendeesign)){
				request.setAttribute("resultinfo",SignUtil.getLeaveNumByConfid(confid));
				request.setAttribute("pretip","签到情况预览－请假人员列表");
				return mapping.findForward("previewinfo");
			}else if ("replace".equals(attendeesign)){
				request.setAttribute("resultinfo",SignUtil.getReplaceNumByConfid(confid));
				request.setAttribute("pretip","签到情况预览－替代签到人员列表");
				return mapping.findForward("previewinfo");
			}
			
		}else if ("delegray".equals(selectType)){
			request.setAttribute("delegraylist",SignUtil.getDelegrayListByConfid(confid));
			request.setAttribute("pretip","签到情况预览－代表团出席情况统计");
			return mapping.findForward("delegray");
		}
		return null;
	}

}
