package org.king.support.service;

import java.util.List;

import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.exception.BusinessException;
import org.king.framework.service.Service;
import org.king.support.domain.MonitorContact;
import org.king.support.domain.MonitorContactgroups;
import org.king.support.domain.MonitorNotifications;
import org.king.support.domain.MonitorRuntimevariables;
import org.king.support.domain.MonitorTimedeventqueue;
import org.king.support.exception.ContactAlreadyExistException;
import org.king.support.exception.ContactgroupsAlreadyExistException;
import org.king.support.exception.RuntimevariablesAlreadyExistException;
import org.king.termdev.domain.MonitorTermdevchecks;
import org.king.termdev.domain.MonitorTermdeviceStatus;


/**
 * Copyright (C), 2000-2010, Kingstar Co., Ltd.
 * File name: org.king.support.service.MonitorSupportService.java
 * Description: TODO
 * Modify History（或Change Log）:
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				       2010-7-7  Linqing.He
 * <p/>
 *
 * @author Linqing.He
 * @version 1.0
 * @since 1.0
 */
public interface MonitorSupportService extends Service {


    /**
     * Description: 系统启动之初，初始化任务队列
     *
     * @param @throws BusinessException
     * @return void
     *         Modify History: 2010-7-7 Linqing.He create
     */
    public List initMonitorTask() throws BusinessException;

    public List findMonitorCommands(Integer configType) throws BusinessException;

    public void saveMonitorContact(MonitorContact monitorContact) throws ContactAlreadyExistException;

    public List findAllMonitorContact();

    public void findMonitorContactByPage(DBPaginatedList page, MonitorContact monitorContact);

    public MonitorContact findMonitorContactById(Integer id);

    public void updateMonitorContact(MonitorContact monitorContact);

    public void deleteMonitorContact(Integer id);

    public void saveMonitorRuntimevariables(MonitorRuntimevariables monitorRuntimevariables) throws RuntimevariablesAlreadyExistException;

    public List findAllMonitorRuntimevariables();

    public void findMonitorRuntimevariablesByPage(DBPaginatedList page, MonitorRuntimevariables monitorRuntimevariables);

    public MonitorRuntimevariables findMonitorRuntimevariablesById(Integer id);

    public void updateMonitorRuntimevariables(MonitorRuntimevariables monitorRuntimevariables);
    
    public MonitorRuntimevariables findMonitorRuntimevariablesByName(String varname);

    public void deleteMonitorRuntimevariables(Integer id);

    public MonitorContactgroups getMonitorContactgroups(Integer id);

    public void saveMonitorContactgroups(MonitorContactgroups monitorContactgroups) throws ContactgroupsAlreadyExistException;

    public List findAllMonitorContactgroups() throws BusinessException;

    public void updateMonitorContactgroups(MonitorContactgroups monitorContactgroups) throws ContactgroupsAlreadyExistException;

    public void deleteMonitorContactgroups(Integer id) throws BusinessException;

    public void findMonitorContactgroupsByPage(DBPaginatedList page, MonitorContactgroups monitorContactgroups);
    
    public MonitorTimedeventqueue findMonitorTimedeventqueueByObjectAndType(Integer objectId,Integer eventType);
    
    public void saveMonitorTimedeventqueue(MonitorTimedeventqueue mt);
    
    public void deleteMonitorTimedeventqueue(MonitorTimedeventqueue mt);
    
    public void updateMonitorTimedeventqueue(MonitorTimedeventqueue mt);
    
    public void saveMonitorNotifications(MonitorNotifications mn);
    public void updateMonitorNotifications(MonitorNotifications mn);
    public void deleteMonitorNotifications(MonitorNotifications mn);
    public List getMonitorNotificationsByFlag(Integer sendOrNot);
    
    public boolean checkHostDowntime(Integer objectid, String nowtime);
    public boolean checkHostserviceDowntime(Integer objectid, String nowtime);
    public boolean checkDevDowntime(Integer objectid, String nowtime);
    
    public List findMonitorContactBygroup(Integer groupid);
    
    public MonitorTermdevchecks findLastMonitorTermdevchecksByTermid(Integer id);
    public List findMonitorTermdeviceStatusOffTemplate();
    public void deleteMonitorTermdeviceStatusOffTemplate(MonitorTermdeviceStatus MTs);
    public void updateLastMonitorTermdevchecks(MonitorTermdevchecks MTc);
    
}
