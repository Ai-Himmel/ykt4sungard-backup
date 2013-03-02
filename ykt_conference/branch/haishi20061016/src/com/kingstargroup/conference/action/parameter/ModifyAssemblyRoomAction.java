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
import com.kingstargroup.conference.dao.AssemblyRoomDAO;
import com.kingstargroup.conference.hibernate.form.TAssemblyRoom;
import com.kingstargroup.conference.util.ParameterUtil;

/**
 * @author Õı”®
 *
 */
public class ModifyAssemblyRoomAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, 
			ActionForm form,
			HttpServletRequest request, 
			HttpServletResponse response) 
			throws Exception {
		String roomId = ParamUtil.getString(request, "roomid");
		String roomName = ParamUtil.getString(request, "roomname");
		String address = ParamUtil.getString(request, "address");
		String contain = ParamUtil.getString(request, "contain");
		Integer con;
		if("".equals(contain)) {
			con = null;
		} else {
			con = Integer.valueOf(contain);
		}
		AssemblyRoomDAO dao = AssemblyRoomDAO.getInstance();
		try {
			TAssemblyRoom asseroom = (TAssemblyRoom) dao.findByPrimaryKey(TAssemblyRoom.class,roomId);
			if(!roomName.equals(asseroom.getRoomName())) {
				List list = dao.getAssemblyRoom("", roomName, "", null);
				if (!list.isEmpty()){
					SessionErrors.add(request, "assemblyroom.failed.name");
					return mapping.getInputForward();
				}
			}
			if ( ParameterUtil.modifyAssemblyRoom(roomId, roomName, address, con, null) ) {
				return mapping.findForward("viewassemblyroom");
			}
		} catch (Exception e) {
			e.printStackTrace();
			return mapping.findForward("error");
		}
		return null;
	}
}
