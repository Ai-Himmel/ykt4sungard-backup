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

import com.kingstargroup.conference.common.SessionErrors;
import com.kingstargroup.conference.util.AttendeeUtil;
import com.kingstargroup.conference.util.ParameterUtil;

/**
 * @author Õı”®
 *
 */
public class DeleteAttGroupNameAction extends Action {

	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		String[] ids = request.getParameterValues("ids_allbox");
		if (ids != null) {		
			try {
				List list;
				int count = ids.length;
				int id;
				for(int i=0; i<count; i++) {
					id = Integer.parseInt(ids[i]);
					list = AttendeeUtil.getCustListByGroupId(id);
					if(!list.isEmpty()) {
						SessionErrors.add(request, "attgroupname.failed.delete");
						return mapping.getInputForward();
					}
				}
				
				ParameterUtil.deleteAttGroupName(ids);
			} catch (Exception e) {
				e.printStackTrace();
				return mapping.findForward("error");
			}
		}
		return mapping.findForward("viewattgroupname");	
	}
}
