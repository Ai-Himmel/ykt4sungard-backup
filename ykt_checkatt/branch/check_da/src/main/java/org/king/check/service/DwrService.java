package org.king.check.service;

import java.util.List;
import java.util.Map;

public interface DwrService {
    public Map getBuildList(String areaCode) throws Exception;

    public Map getRoomList(String build) throws Exception;

    public Map getRoomnameList(String build) throws Exception;

    public Map getDeviceList(String roomid) throws Exception;

    /**
     * 通过班级信息找到所有的校区
     *
     * @return .
     */
//    public List findAreaFromDepartment();

    /**
     * 找到院系
     *
     * @return .
     */
    public List findFaculty();

    /**
     * 通过院系找到校区
     */
    public List findAreaFromDepartment(String pid);

    /**
     * 根据校区代码和院系代码查找班级
     *
     * @param areaCode 校区代码
     * @param pid  院系代码父节点
     * @param filter   值为1时，添加权限过滤，否则，查出所有的
     * @return .
     */
    public List findDepartment(String areaCode, String pid, String filter);

    /**
     * 根据校区代码，院系代码，班级代码查找课程
     *
     * @param areaCode 校区代码
     * @param pid  院系代码父节点
     * @param deptId   班级代码
     * @param filter   值为1时，添加权限过滤，否则，查出所有的
     * @return .
     */
    public List findCourse(String areaCode, String pid, String deptId, String filter);
}
