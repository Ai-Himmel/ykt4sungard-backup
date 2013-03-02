/**
 * 
 */
package com.kingstargroup.conference.action.analyse;

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
public class AtteAnalyseAction extends Action {

	public ActionForward execute(
			ActionMapping mapping,
			ActionForm form,
			HttpServletRequest request,
			HttpServletResponse response) {
		String listId = ParamUtil.getString(request, "listId");
		String conid = ParamUtil.getString(request, "conId");
		String query = ParamUtil.getString(request, "query");
		try {
			request.setAttribute("conflist", AnalyseUtil.getAllConfenece());
			request.setAttribute("listid", listId);
			request.setAttribute("conid", conid);
		} catch(Exception e) {
			return mapping.findForward("error");
		}
		if("1".equals(query)) {
			request.setAttribute("conference", getConference(conid));		
			request.setAttribute("concount", getAtteCount(conid));
			request.setAttribute("result", getAttendeeList(conid, listId));
		}		
		return mapping.findForward("queryanalyse");
	}

	/**
	 * Description:按主键查询会议信息
	 * @param conId
	 * @return
	 */
	private TConference getConference(String conId) {
		if(!"".equals(conId)) {
			return AnalyseUtil.getConference(Integer.valueOf(conId));
		} else {
			return null;	
		}
	}
	
	/**
	 * Description:按会议编号查询与会者统计信息
	 * @param conId
	 * @return
	 */
	private List getAtteCount(String conId) {
		if(!"".equals(conId)) {			
			return AnalyseUtil.getAtteCount(Integer.valueOf(conId));
		} else {
			return null;	
		}
	}
	
	/**
	 * Description:按会议编号查询与会者信息
	 * @param conId, sign
	 * @return
	 */
	private List getAttendeeList(String conId, String sign) {
		if(!"".equals(conId)) {
			return AnalyseUtil.getAttendeeList(Integer.valueOf(conId), sign);
		} else {
			return null;	
		}
	}	

}