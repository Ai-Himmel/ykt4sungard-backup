package org.king.termdev.service;

import java.util.Date;
import java.util.List;
import java.util.Map;
import java.util.Set;

import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.exception.BusinessException;
import org.king.termdev.domain.MonitorDevtem;
import org.king.termdev.domain.MonitorTermdevService;
import org.king.termdev.domain.MonitorTermdevchecks;
import org.king.termdev.domain.MonitorTermdeviceStatus;
import org.king.termdev.domain.MonitorTermdevserviceStatus;
import org.king.termdev.exception.TermdevServiceAlreadyExistException;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-10
 */
public interface TermdevService {
    public void saveMonitorTermdevService(MonitorTermdevService monitorTermdevService) throws TermdevServiceAlreadyExistException;

    public List findAllMonitorTermdevService();

    public void findMonitorTermdevServiceByPage(DBPaginatedList page, MonitorTermdevService monitorTermdevService);

    public MonitorTermdevService findMonitorTermdevServiceById(Integer id);

    public void updateMonitorTermdevService(MonitorTermdevService monitorTermdevService);

    public void deleteMonitorTermdevService(Integer id);

    public void findMonitorTermdevserviceStatusByPage(DBPaginatedList page, MonitorTermdevserviceStatus monitorTermdevserviceStatus);

    public String[][] calculateTermdevserviceStatus();

    public void findMonitorTermdeviceStatusByPage(DBPaginatedList page, String[] conditions);

    public String[][] calculateTermdeviceStatus();

    /**
     * Description: 返回状态表所有信息
     *
     * @param @return
     * @return List
     *         Modify History: 2010-7-16 Linqing.He create
     */
    public List getAllTermdevStatus();

    /**
     * Description: sql查询列表
     *
     * @param @param  sql
     * @param @return
     * @return List
     *         Modify History: 2010-7-19 Linqing.He create
     */
    public List getSqlList(String sql);

    public MonitorTermdeviceStatus getMonitorTermdeviceStatus(Integer deviceid);

    public void updateMonitormonitorTermdeviceStatus(MonitorTermdeviceStatus monitorTermdeviceStatus);

    public void saveMonitormonitorTermdeviceStatus(MonitorTermdeviceStatus monitorTermdeviceStatus);

    public void findTDeviceByPage(DBPaginatedList page, String[] args);

    public String getTemplateIdByDeviceid(Integer deviceid);

    public Map getDeviceType();

    public MonitorDevtem getMonitorDevtem(Integer deviceid);

    public void saveOrUpdateMonitorDevtem(MonitorDevtem monitorDevtem);

    public String getTDeviceName(Integer deviceid);

    public List findBindingDevice(Integer templateId);

    public String getDeviceXmlTree(Integer templateId);

    public void updateBindingDevice(Integer templateId, Set devices);

    public void findTermdevHistoryStatusByPage(DBPaginatedList page, Object[] conditions);

    public void findMonitorTermdevchecksByPage(DBPaginatedList page, Object[] conditions);

    public List findMonitorTermdevchecks(Integer deviceid, Date startTime, Date endTime);
    
    /**
    * Description: 保存设备监控记录
    * @param @throws BusinessException
    * @return void
    * Modify History: 2010-8-18 Linqing.He create
    */
    public void saveMonitorTermdevchecks(MonitorTermdevchecks MTdevchecks) throws  BusinessException;
    public void updateMonitorTermdevchecks(MonitorTermdevchecks MTdevchecks) throws  BusinessException;
    public MonitorTermdevchecks getLattestMonitorTermdevchecks(Integer Objectid);

	public List categorizeDeviceStatus();
    /**
    * Description: 查找黑名单版本错误warning设备记录
    * @param @param blackSheet
    * @param @return
    * @return List
    * Modify History: 2010-9-10 Linqing.He create
    */
    public List findBsverErrorWarningList(String blackSheet_warning_sherold,String blackSheet_critical_sherold);
    public List findBsverErrorCriticalList(String blackSheet_warning_sherold,String blackSheet_critical_sherold);
    public String getmaxVolumeTimeFromTcardVer();
    public String getVolumeFromTcardVer(String blackSheet_sherold,String max_blackSheet_sherold);
}
