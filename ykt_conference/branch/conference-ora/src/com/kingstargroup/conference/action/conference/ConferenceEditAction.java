package com.kingstargroup.conference.action.conference;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.common.DateUtilExtend;
import com.kingstargroup.conference.common.GetterUtil;
import com.kingstargroup.conference.util.ConferenceUtil;

public class ConferenceEditAction extends Action{

	public ActionForward execute(
			ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		String username = GetterUtil.get((String) request.getSession().getAttribute("username"), "");
		Integer confId = new Integer(request.getParameter("conid"));
		String confName = request.getParameter("conname");
		String open = request.getParameter("open");
		String roomId = request.getParameter("assembly");
		String typeName = request.getParameter("type");
		String signTime = request.getParameter("signtime");
		String beginDate = request.getParameter("begindate");
		String beginTime = request.getParameter("begintime");
		String endDate = request.getParameter("begindate");
		String endTime = request.getParameter("endtime");
		String compere = request.getParameter("compere");
		String orgId = request.getParameter("org");
		String ifSerecy = "1";
		String explan = request.getParameter("explan");
		String comments = request.getParameter("comments");
		String nowdate = DateUtilExtend.getNowDate2();
		if (DateUtilExtend.diffDate(beginDate,nowdate)>0){
			request.setAttribute("tipinfo","会议开始日期不能小于今天！");
			return mapping.findForward("error");
		}
		if (DateUtilExtend.timeDiff2(signTime,beginTime)<=0){
			request.setAttribute("tipinfo","签到时间不能小于会议开始时间，请重新设置！");
			return mapping.findForward("error");
		}
		if (DateUtilExtend.timeDiff2(signTime,endTime)<=0){
			request.setAttribute("tipinfo","签到时间不能小于会议结束时间，请重新设置！");
			return mapping.findForward("error");
		}
		if (DateUtilExtend.timeDiff2(beginTime,endTime)<=0){
			request.setAttribute("tipinfo","开始时间不能大于结束时间，请重新设置！");
			return mapping.findForward("error");
		}
		if ((DateUtilExtend.timeDiff2(beginTime,"1200")>=0)
				&&(DateUtilExtend.timeDiff2("1200",endTime)>=0)){
			request.setAttribute("tipinfo","时间段设置不能跨上下午，请作为两个会议处理！");
			return mapping.findForward("error");
		}
		try {
			if (ConferenceUtil.editConference(
												confId,
												confName,
												open,
												roomId,
												typeName,
												signTime,
												beginDate,
												beginTime,
												endDate,
												endTime,
												compere,
												orgId,
												ifSerecy,
												explan,
												comments)){
				request.setAttribute("result",ConferenceUtil.getAllConference(username));
				return mapping.findForward("defconflist");
			}
		} catch (Exception e) {
			request.setAttribute("tipinfo","修改会议失败："+e.toString());
			return mapping.findForward("error");
		}
		return null;
	}

}
