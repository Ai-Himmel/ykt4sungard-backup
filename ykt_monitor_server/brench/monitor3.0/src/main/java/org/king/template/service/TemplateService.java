package org.king.template.service;

import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.exception.BusinessException;
import org.king.framework.service.Service;
import org.king.template.domain.*;
import org.king.template.exception.TemplateAlreadyExistException;

import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-1
 */
public interface TemplateService extends Service {
    public void saveMonitorHostTemplate(MonitorHostTemplate monitorHostTemplate) throws TemplateAlreadyExistException;

    public List findAllMonitorHostTemplate();

    public void findMonitorHostTemplateByPage(DBPaginatedList page, MonitorHostTemplate monitorHostTemplate);

    public MonitorHostTemplate findMonitorHostTemplateById(Integer templateId);

    public void updateMonitorHostTemplate(MonitorHostTemplate monitorHostTemplate);

    public void deleteMonitorHostTemplate(Integer templateId);

    public void saveMonitorServiceTemplate(MonitorServiceTemplate monitorServiceTemplate) throws TemplateAlreadyExistException;

    public List findAllMonitorServiceTemplate();

    public void findMonitorServiceTemplateByPage(DBPaginatedList page, MonitorServiceTemplate monitorServiceTemplate);

    public MonitorServiceTemplate findMonitorServiceTemplateById(Integer templateId);

    public void updateMonitorServiceTemplate(MonitorServiceTemplate monitorServiceTemplate);

    public void deleteMonitorServiceTemplate(Integer templateId);

    public void saveMonitorContactTemplate(MonitorContactTemplate monitorContactTemplate) throws TemplateAlreadyExistException;

    public List findAllMonitorContactTemplate();

    public void findMonitorContactTemplateByPage(DBPaginatedList page, MonitorContactTemplate monitorContactTemplate);

    public MonitorContactTemplate findMonitorContactTemplateById(Integer templateId);

    public void updateMonitorContactTemplate(MonitorContactTemplate monitorContactTemplate);

    public void deleteMonitorContactTemplate(Integer templateId);

    public void saveMonitorTimePeriods(MonitorTimePeriods monitorTimePeriods) throws TemplateAlreadyExistException;

    public List findAllMonitorTimePeriods();

    public void findMonitorTimePeriodsByPage(DBPaginatedList page, MonitorTimePeriods monitorTimePeriods);

    public MonitorTimePeriods findMonitorTimePeriodsById(Integer periodId);

    public void updateMonitorTimePeriods(MonitorTimePeriods monitorTimePeriods);

    public void deleteMonitorTimePeriods(Integer periodId) throws BusinessException;

    public void saveMonitorTermdevTemplate(MonitorTermdevTemplate monitorTermdevTemplate) throws TemplateAlreadyExistException;

    public List findAllMonitorTermdevTemplate();

    public void findMonitorTermdevTemplateByPage(DBPaginatedList page, MonitorTermdevTemplate monitorTermdevTemplate);

    public MonitorTermdevTemplate findMonitorTermdevTemplateById(Integer templateId);
    
    public MonitorTermdevTemplateAll findMonitorTermdevTemplateAllById(Integer templateId);
    
    public MonitorTermdevTemplate getEnableMonitorTermdevTemplate();

    public void updateMonitorTermdevTemplate(MonitorTermdevTemplate monitorTermdevTemplate);
    
    public void updateMonitorTermdevTemplateAll(MonitorTermdevTemplateAll monitorTermdevTemplateAll);

    public void deleteMonitorTermdevTemplate(Integer templateId) throws BusinessException;

    public String[] getNotifyHostCommands();

    public String[] getNotifyServiceCommands();
}
