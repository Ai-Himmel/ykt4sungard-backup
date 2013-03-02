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
import com.kingstargroup.conference.util.ParameterUtil;

public class DeleteDelegateNameAction extends Action {

	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		String[] ids = request.getParameterValues("ids_allbox");
		if (ids != null) {		
			try {
				List list;
				int count = ids.length;
				for(int i=0; i<count; i++) {
					list = ParameterUtil.getConfDlgt(ids[i]);
					if(!list.isEmpty()) {
						SessionErrors.add(request, "delegate.failed.delete");
						return mapping.getInputForward();
					}
				}
				
				ParameterUtil.deleteDelegates(ids);
			} catch (Exception e) {
				e.printStackTrace();
				return mapping.findForward("error");
			}
		}
		return mapping.findForward("viewdelegate");	
	}
}
