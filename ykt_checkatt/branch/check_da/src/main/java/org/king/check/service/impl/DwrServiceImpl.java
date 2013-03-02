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
     * ����У�����Ҹ�У���ڵ�����¥��
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
     * ����¥������ڸ�¥���ڵ����з���
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
     * ����¥������ڸ�¥���ڵ����з���
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
     * ���ݷ�����Һ͸÷�������������豸
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
     * ͨ���༶��Ϣ�ҵ����е�У��
     *
     * @return .
     */
    /*public List findAreaFromDepartment() {
        return departmentService.findAreaFromDepartment();
    }*/

    /**
     * ͨ���༶��Ϣ�ҵ�ѧԺ
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
     * ����У�������Ժϵ������Ұ༶
     *
     * @param areaCode У������
     * @param pid  Ժϵ���븸�ڵ�
     * @param filter   ֵΪ1ʱ�����Ȩ�޹��ˣ����򣬲�����е�
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
     * ����У�����룬Ժϵ���룬�༶������ҿγ�
     *
     * @param areaCode У������
     * @param pid  Ժϵ���븸�ڵ�
     * @param deptId   �༶����
     * @param filter   ֵΪ1ʱ�����Ȩ�޹��ˣ����򣬲�����е�
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
