package org.king.check.student.web.action;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.*;
import org.king.check.domain.TRoom;
import org.king.check.service.AreaService;
import org.king.check.service.DepartmentService;
import org.king.check.service.RoomService;
import org.king.framework.web.action.BaseAction;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.ArrayList;
import java.util.List;

public class ClassdevAction extends BaseAction {

    private static final Log log = LogFactory.getLog(ClassdevAction.class);

    private RoomService roomService;

    private DepartmentService departmentService;

    private AreaService areaService;

    public void setRoomService(RoomService roomService) {
        this.roomService = roomService;
    }

    public void setDepartmentService(DepartmentService departmentService) {
        this.departmentService = departmentService;
    }

    public void setAreaService(AreaService areaService) {
        this.areaService = areaService;
    }

    public ActionForward list(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        DynaActionForm dform = (DynaActionForm) form;
        String schoolarea = dform.getString("schoolarea");
        String build = dform.getString("build");
        String roomname = dform.getString("roomname");
        ActionMessages messages = new ActionMessages();

        List areaList = new ArrayList();
        List buildList = new ArrayList();
        List roomnameList = new ArrayList();
        List list = new ArrayList();

        try {
            // 校区列表
            areaList = departmentService.findAreaFromDepartment();
		    // 楼宇列表
            if(StringUtils.isNotBlank(schoolarea)){
                buildList = roomService.getBuildList(schoolarea);
            }
            if(StringUtils.isNotBlank(build)){
                roomnameList = roomService.getRoomNameList(build);
            }
            list = roomService.getClassDevList(schoolarea, build, roomname);
        } catch (Exception e) {
            e.printStackTrace();
            messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage("查询出现异常"));
        }
        saveMessages(request, messages);

        request.setAttribute("areaList", areaList);
        request.setAttribute("buildList", buildList);
        request.setAttribute("roomnameList", roomnameList);
        request.setAttribute("classDevList", list);
        return mapping.findForward("list");
    }

    public ActionForward edit(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        DynaActionForm dform = (DynaActionForm) form;
        ActionMessages messages = new ActionMessages();
        String roomid = request.getParameter("roomid");
        dform.set("roomid", roomid);
        TRoom troom = roomService.getRoom(roomid);
        request.setAttribute("troom", troom);
        dform.set("roomname",troom.getRoomName());
        dform.set("build",troom.getBuild());
        dform.set("schoolarea",troom.getSchoolArea().getAreaCode());
        List binddevList = new ArrayList();
        List unbinddevList = new ArrayList();
        List areaList = new ArrayList();
        try {
            areaList = departmentService.findAreaFromDepartment();
            binddevList = roomService.getBindDevList(roomid);
            unbinddevList = roomService.getUnbindDevList();
        } catch (Exception e) {
            e.printStackTrace();
            messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage("获取设备列表失败"));
        }
        saveMessages(request, messages);
        request.setAttribute("troom", troom);
        request.setAttribute("binddevList", binddevList);
        request.setAttribute("unbinddevList", unbinddevList);
        request.setAttribute("areaList", areaList);
        return mapping.findForward("edit");
    }

    public ActionForward save(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        DynaActionForm dform = (DynaActionForm) form;
        String roomid = dform.getString("roomid");
        String roomname = dform.getString("roomname");
        String[] binddeviceArr = request.getParameterValues("binddevice");
        String schoolarea = dform.getString("schoolarea");
        String build = dform.getString("build");
        ActionMessages messages = new ActionMessages();

        try {
            TRoom room = roomService.getRoom(roomid);
            room.setRoomName(roomname);
            room.setBuild(build);
            if(!room.getSchoolArea().getAreaCode().equals(schoolarea)){
                room.setSchoolArea(areaService.getArea(schoolarea));
            }
            roomService.saveRoom(room);
            roomService.saveBindDevList(roomid, binddeviceArr);
            dform.set("roomname","");
            dform.set("build","");
            dform.set("schoolarea","");
        } catch (Exception e) {
            e.printStackTrace();
            messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage("保存设备绑定信息失败"));
        }
        saveMessages(request, messages);
        return list(mapping, form, request, response);
    }

    public ActionForward deleteTerm(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        return list(mapping, form, request, response);
    }
}
