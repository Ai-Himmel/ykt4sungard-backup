package com.kingstargroup.conference.action.conference;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.util.ConferenceUtil;

public class ConferenceQueryAction extends Action{

	public ActionForward execute(
			ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		String confName = request.getParameter("conname");
		String confRoom = request.getParameter("confroom");
		String confType = request.getParameter("type");
		String beginDate = request.getParameter("begindate");
		String endDate = "";
		String compere = "";
		String confDept = "";
		if (null==confName){
			request.setAttribute("tipinfo","没有你要查找的会议记录，请重新指定查询条件！");
			return mapping.findForward("error");
		}
		try {
			List result = ConferenceUtil.getConfListByQuery
										(confName,confType,confRoom,confDept,beginDate,endDate,compere);
			if (null == result){
				request.setAttribute("tipinfo","没有你要查找的会议记录，请重新指定查询条件！");
				return mapping.findForward("error");
			}
			request.setAttribute("result",result);
			return mapping.findForward("defconflist");
			
		} catch (Exception e) {
			e.printStackTrace();
			return mapping.findForward("error");
		}
	}

}
