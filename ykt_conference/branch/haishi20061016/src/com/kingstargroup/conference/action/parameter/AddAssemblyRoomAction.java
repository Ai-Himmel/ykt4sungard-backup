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
 * @author hjw
 * 
 */
public class AddAssemblyRoomAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, 
			ActionForm form,
			HttpServletRequest request, 
			HttpServletResponse response) 
			throws Exception {
		String roomId = ParamUtil.getString(request, "roomid");
		String roomName = ParamUtil.getString(request, "roomname");
		String con = ParamUtil.getString(request, "contain");
		String address = ParamUtil.getString(request, "address");
		Integer contain;		
		if("".equals(con)) {
			contain = null;
		} else {
			contain = Integer.valueOf(con);
		}
		AssemblyRoomDAO dao = AssemblyRoomDAO.getInstance();
		try{
			if (dao.findByPrimaryKey(TAssemblyRoom.class,roomId)!=null){
				SessionErrors.add(request, "assemblyroom.failed.roomid");
				return mapping.getInputForward();
			}
			List list = dao.getAssemblyRoom("", roomName, "", null);
			if (!list.isEmpty()){
				SessionErrors.add(request, "assemblyroom.failed.name");
				return mapping.getInputForward();
			}
			if (ParameterUtil.createAssemblyRoom(roomId,roomName,contain,address)){
				return mapping.findForward("viewassemblyroom");
			}
			return mapping.findForward("error");
		}
		catch (Exception e) {
			return mapping.findForward("error");
		}
	}


}
