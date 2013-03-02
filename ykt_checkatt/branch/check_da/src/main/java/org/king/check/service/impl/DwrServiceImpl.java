package org.king.check.service.impl;

import org.apache.commons.lang.StringUtils;
import org.directwebremoting.WebContextFactory;
import org.king.check.dao.RoomDAO;
import org.king.check.service.DepartmentService;
import org.king.check.service.DwrService;
import org.king.security.domain.Account;

import javax.servlet.http.HttpSession;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class DwrServiceImpl implements DwrService {

    private RoomDAO roomDAO;

    private DepartmentService departmentService;

    public void setRoomDAO(RoomDAO roomDAO) {
        this.roomDAO = roomDAO;
    }

    public void setDepartmentService(DepartmentService departmentService) {
        this.departmentService = departmentService;
    }

    /**
     * 根据校区查找该校区内的所有楼宇
     *
     * @param areaCode .
     * @return .
     */
    public Map getBuildList(String areaCode) {
        if (StringUtils.isEmpty(areaCode)) {
            return new HashMap();
        }

        Map result;
        List list = roomDAO.find("select distinct new map(a.build as build) from TRoom a where a.schoolArea.areaCode='"
                + areaCode + "'");
        if (list != null && list.size() > 0) {
            result = new HashMap();
            for (int i = 0; i < list.size(); i++) {
                Map map = (Map) list.get(i);
                result.put(map.get("build"), map.get("build"));
            }
        } else {
            result = new HashMap();
        }
        return result;
    }

    /**
     * 根据楼宇查找在该楼宇内的所有房间
     *
     * @param build .
     * @return .
     * @throws Exception .
     */
    public Map getRoomList(String build) throws Exception {
        if (StringUtils.isEmpty(build)) {
            return new HashMap();
        }
        Map result;

        List list = roomDAO.find("select distinct new map(a.roomId as roomid,a.roomName as roomname) from TRoom a where a.build='"
                + build + "'");
        if (list != null && list.size() > 0) {
            result = new HashMap();
            for (int i = 0; i < list.size(); i++) {
                Map map = (Map) list.get(i);
                result.put(map.get("roomid"), map.get("roomname"));
            }
        } else {
            result = new HashMap();
        }
        return result;
    }

    /**
     * 根据楼宇查找在该楼宇内的所有房间
     *
     * @param build .
     * @return .
     * @throws Exception .
     */
    public Map getRoomnameList(String build) throws Exception {
        if (StringUtils.isEmpty(build)) {
            return new HashMap();
        }
        Map result;

        List list = roomDAO.find("select distinct new map(a.roomName as roomname) from TRoom a where a.build='"
                + build + "'");
        if (list != null && list.size() > 0) {
            result = new HashMap();
            for (int i = 0; i < list.size(); i++) {
                Map map = (Map) list.get(i);
                result.put(map.get("roomname"), map.get("roomname"));
            }
        } else {
            result = new HashMap();
        }
        return result;
    }

    /**
     * 根据房间查找和该房间关联的所有设备
     *
     * @param roomid .
     * @return .
     * @throws Exception
     */
    public Map getDeviceList(String roomid) throws Exception {
        if (StringUtils.isEmpty(roomid)) {
            return new HashMap();
        }
        Map result;

        List list = roomDAO.find("select distinct new map(d.deviceid as deviceid,d.devicename as devicename) from TDevice d,TRoomdevice rd where rd.id.deviceId=d.deviceid and rd.id.roomId='"
                + roomid + "'");
        if (list != null && list.size() > 0) {
            result = new HashMap();
            for (int i = 0; i < list.size(); i++) {
                Map map = (Map) list.get(i);
                result.put(map.get("deviceid"), map.get("devicename"));

            }
        } else {
            result = new HashMap();
        }
        return result;
    }

    /**
     * 通过班级信息找到所有的校区
     *
     * @return .
     */
    /*public List findAreaFromDepartment() {
        return departmentService.findAreaFromDepartment();
    }*/

    /**
     * 通过班级信息找到学院
     *
     * @return .
     */
    public List findFaculty() {
        return departmentService.findFaculty();
    }

    public List findAreaFromDepartment(String pid) {
        if (StringUtils.isBlank(pid)) {
            return null;
        }
        return departmentService.findAreaFromDepartment(pid);
    }

    /**
     * 根据校区代码和院系代码查找班级
     *
     * @param areaCode 校区代码
     * @param pid  院系代码父节点
     * @param filter   值为1时，添加权限过滤，否则，查出所有的
     * @return .
     */
    public List findDepartment(String areaCode, String pid, String filter) {
        if (StringUtils.isBlank(areaCode)) {
            return null;
        }
        if ("1".equals(filter)) {
            HttpSession session = WebContextFactory.get().getSession();
            Account account = (Account) session.getAttribute("accountPerson");
            return departmentService.findDepartment(areaCode, pid, account);
        } else {
            return departmentService.findDepartment(areaCode, pid);
        }
    }

    /**
     * 根据校区代码，院系代码，班级代码查找课程
     *
     * @param areaCode 校区代码
     * @param pid  院系代码父节点
     * @param deptId   班级代码
     * @param filter   值为1时，添加权限过滤，否则，查出所有的
     * @return .
     */
    public List findCourse(String areaCode, String pid, String deptId, String filter) {
        if ("1".equals(filter)) {
            HttpSession session = WebContextFactory.get().getSession();
            Account account = (Account) session.getAttribute("accountPerson");
            return departmentService.findCourse(areaCode, pid, deptId, account);
        } else {
            return departmentService.findCourse(areaCode, pid, deptId);
        }
    }
}
