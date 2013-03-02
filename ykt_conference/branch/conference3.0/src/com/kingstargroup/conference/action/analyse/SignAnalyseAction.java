/**
 * 
 */
package com.kingstargroup.conference.action.analyse;

import java.util.ArrayList;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.common.ParamUtil;
import com.kingstargroup.conference.hibernate.form.TConference;
import com.kingstargroup.conference.util.AnalyseUtil;

/**
 * @author 王莹
 *
 */
public class SignAnalyseAction extends Action {

	public ActionForward execute(
			ActionMapping mapping,
			ActionForm form,
			HttpServletRequest request,
			HttpServletResponse response) {
		String conId = ParamUtil.getString(request, "conId");
		String duty = ParamUtil.getString(request, "duty");
		String status = ParamUtil.getString(request, "status");
		String query = ParamUtil.getString(request, "query");
		try {
			request.setAttribute("conflist", AnalyseUtil.getAllConfenece());
			request.setAttribute("statlist", AnalyseUtil.getAllSignStatus());
		} catch(Exception e) {
			return mapping.findForward("error");
		}
		
		if("1".equals(query)) {
			request.setAttribute("conference", getConference(conId));		
			request.setAttribute("concount", getAtteCount(conId, duty, status));
			request.setAttribute("result", getAttendeeList(conId, duty, status));
		}		
		return mapping.findForward("querysign");
	}
	
	private ArrayList getAtteCount(String conId, String duty, String status) {
		try {			
			if(!"".equals(conId)) {
			//	return AnalyseUtil.getAtteCount(Integer.valueOf(conId), duty, status);
				return AnalyseUtil.getAtteCount(Integer.valueOf(conId));
			}
			return null;
		} catch(Exception e) {
			return null;
		}
	}
	
	/**
	 * Description:按主键查询会议信息
	 * @param conId
	 * @return
	 */
	private TConference getConference(String conId) {
		if(!"".equals(conId)) {
			return AnalyseUtil.getConference(Long.valueOf(conId));
		} else {
			return null;	
		}
	}
	
	/**
	 * Description:按会议编号查询与会者信息
	 * @param conId, sign
	 * @return
	 */
	private List getAttendeeList(String conId, String duty, String sign) {
		if(!"".equals(conId)) {
			return AnalyseUtil.getAttendeeList(Integer.valueOf(conId), duty, sign);
		}
		return null;
	}
}
