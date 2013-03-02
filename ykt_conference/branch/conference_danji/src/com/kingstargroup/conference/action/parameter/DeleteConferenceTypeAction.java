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
import com.kingstargroup.conference.util.ParameterUtil;
import com.kingstargroup.conference.hibernate.form.TConferenceType;;

/**
 * @author Õı”®
 * 
 */
public class DeleteConferenceTypeAction extends Action {

	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		String typename = ParamUtil.getString(request, "contypename");
		String[] ids = null;
		ids = request.getParameterValues("ids_allbox");
		if (ids != null) {		
			try {
				List list;
				int count = ids.length;
				String id, name;
				ConferenceTypeDAO dao = ConferenceTypeDAO.getInstance();
				for(int i=0; i<count; i++) {
					id = ids[i];
					if(!"".equals(id)) {
						name = ((TConferenceType) dao.findByPrimaryKey(TConferenceType.class, Integer.valueOf(id))).getTypeName();					
						list = ParameterUtil.getConferenceByType(name);
						if(!list.isEmpty()) {
							SessionErrors.add(request, "conftype.failed.delete");
							return mapping.getInputForward();
						}
					}
				}
				
				ParameterUtil.deleteConferenceType(ids);
			} catch (Exception e) {
				e.printStackTrace();
				return mapping.findForward("error");
			}
		}

		return mapping.findForward("viewconftype");		
	}
}
