/**
 * 
 */
package com.kingstargroup.conference.action.parameter;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.common.ParamUtil;
import com.kingstargroup.conference.common.SessionErrors;
import com.kingstargroup.conference.dao.ConferenceTypeDAO;
import com.kingstargroup.conference.hibernate.form.TConferenceType;
import com.kingstargroup.conference.util.ParameterUtil;
/**
 * @author Õı”®
 *
 */
public class ModifyConferenceTypeAction extends Action {
	
	public ActionForward execute(
			ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		String conftypeid = ParamUtil.getString(request, "typeid");		
		String conftypename = ParamUtil.getString(request, "contypename");
		String comments = ParamUtil.getString(request, "comments");
		Integer id;
		if("".equals(conftypeid)) {
			return mapping.findForward("error");
		}
		id = Integer.valueOf(conftypeid);
		ConferenceTypeDAO dao = ConferenceTypeDAO.getInstance();
		String oldname = "";
		
		try {
			if(dao.findByPrimaryKey(TConferenceType.class, id) != null) {
				oldname = ((TConferenceType)dao.findByPrimaryKey(TConferenceType.class, id)).getTypeName();			
			}
			if(!oldname.equals(conftypename)) {
				List list = ParameterUtil.getConferenceType(conftypename);
				if (!list.isEmpty()) {
					SessionErrors.add(request, "conftype.failed.typename");
					return mapping.getInputForward();
				}
			}
			
			if ( ParameterUtil.modifyConferenceType(id, conftypename, comments) ) {
				return mapping.findForward("viewconftype");
			}
			return mapping.findForward("error");
		} catch (Exception e) {
			e.printStackTrace();
			return mapping.findForward("error");
		}
	}

}
