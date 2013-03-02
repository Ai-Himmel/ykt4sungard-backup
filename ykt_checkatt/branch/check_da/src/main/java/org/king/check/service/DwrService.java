package org.king.check.service;

import java.util.List;
import java.util.Map;

public interface DwrService {
    public Map getBuildList(String areaCode) throws Exception;

    public Map getRoomList(String build) throws Exception;

    public Map getRoomnameList(String build) throws Exception;

    public Map getDeviceList(String roomid) throws Exception;

    /**
     * ͨ���༶��Ϣ�ҵ����е�У��
     *
     * @return .
     */
//    public List findAreaFromDepartment();

    /**
     * �ҵ�Ժϵ
     *
     * @return .
     */
    public List findFaculty();

    /**
     * ͨ��Ժϵ�ҵ�У��
     */
    public List findAreaFromDepartment(String pid);

    /**
     * ����У�������Ժϵ������Ұ༶
     *
     * @param areaCode У������
     * @param pid  Ժϵ���븸�ڵ�
     * @param filter   ֵΪ1ʱ�����Ȩ�޹��ˣ����򣬲�����е�
     * @return .
     */
    public List findDepartment(String areaCode, String pid, String filter);

    /**
     * ����У�����룬Ժϵ���룬�༶������ҿγ�
     *
     * @param areaCode У������
     * @param pid  Ժϵ���븸�ڵ�
     * @param deptId   �༶����
     * @param filter   ֵΪ1ʱ�����Ȩ�޹��ˣ����򣬲�����е�
     * @return .
     */
    public List findCourse(String areaCode, String pid, String deptId, String filter);
}
