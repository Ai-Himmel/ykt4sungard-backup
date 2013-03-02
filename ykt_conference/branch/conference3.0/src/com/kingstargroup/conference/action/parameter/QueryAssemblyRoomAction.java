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
import com.kingstargroup.conference.util.ParameterUtil;

/**
 * @author Õı”®
 *
 */
public class QueryAssemblyRoomAction extends Action {
	
	public ActionForward execute(
			ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		String roomId = ParamUtil.getString(request, "roomId");
		String roomName = ParamUtil.getString(request, "roomName");
		String address = ParamUtil.getString(request, "address");
		String contain = ParamUtil.getString(request, "contain");
		Long con = "".equals(contain)? null:Long.valueOf(contain);
		try {
			List result = ParameterUtil.getAssemblyRoom(roomId, roomName, address, con);
			request.setAttribute("result",result);
			
			request.setAttribute("roomId",roomId);
			request.setAttribute("roomName",roomName);
			request.setAttribute("address",address);
			request.setAttribute("contain",contain);
			
			return mapping.findForward("viewassemblyroom");			
		} catch (Exception e) {
			e.printStackTrace();
			return mapping.findForward("error");
		}
	}
}
