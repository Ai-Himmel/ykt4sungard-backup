package org.king.template.service.impl;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.common.displaytag.DBPaginatedList;
import org.king.common.query.QueryTranslate;
import org.king.framework.exception.BusinessException;
import org.king.framework.service.impl.BaseService;
import org.king.support.dao.MonitorCommandsDAO;
import org.king.template.dao.*;
import org.king.template.domain.*;
import org.king.template.exception.TemplateAlreadyExistException;
import org.king.template.service.TemplateService;
import org.king.utils.Contants;
import org.king.utils.ResultTransform;

import java.util.ArrayList;
import java.util.List;

/**
 * 模板操作功能类.
 * User: Yiming.You
 * Date: 2010-7-1
 */
public class TemplateServiceImpl extends BaseService implements TemplateService {
    private static Log log = LogFactory.getLog(TemplateServiceImpl.class);

    private MonitorHostTemplateDAO monitorHostTemplateDAO;

    private MonitorServiceTemplateDAO monitorServiceTemplateDAO;

    private MonitorContactTemplateDAO monitorContactTemplateDAO;

    private MonitorTimePeriodsDAO monitorTimePeriodsDAO;

    private MonitorTermdevTemplateDAO monitorTermdevTemplateDAO;

    private MonitorCommandsDAO monitorCommandsDAO;

    public void setMonitorServiceTemplateDAO(MonitorServiceTemplateDAO monitorServiceTemplateDAO) {
        this.monitorServiceTemplateDAO = monitorServiceTemplateDAO;
    }

    public void setMonitorHostTemplateDAO(MonitorHostTemplateDAO monitorHostTemplateDAO) {
        this.monitorHostTemplateDAO = monitorHostTemplateDAO;
    }

    public void setMonitorContactTemplateDAO(MonitorContactTemplateDAO monitorContactTemplateDAO) {
        this.monitorContactTemplateDAO = monitorContactTemplateDAO;
    }

    public void setMonitorTimePeriodsDAO(MonitorTimePeriodsDAO monitorTimePeriodsDAO) {
        this.monitorTimePeriodsDAO = monitorTimePeriodsDAO;
    }

    public void setMonitorTermdevTemplateDAO(MonitorTermdevTemplateDAO monitorTermdevTemplateDAO) {
        this.monitorTermdevTemplateDAO = monitorTermdevTemplateDAO;
    }

    public void setMonitorCommandsDAO(MonitorCommandsDAO monitorCommandsDAO) {
        this.monitorCommandsDAO = monitorCommandsDAO;
    }

    /**
     * 保存主机模板
     *
     * @param monitorHostTemplate .
     */
    public void saveMonitorHostTemplate(MonitorHostTemplate monitorHostTemplate) throws TemplateAlreadyExistException {
        if (monitorHostTemplateDAO.isExistMonitorHostTemplate(monitorHostTemplate.getTemplateName())) {
            throw new TemplateAlreadyExistException("该模板名称已被使用！");
        }
        monitorHostTemplateDAO.save(monitorHostTemplate);
    }

    public List findAllMonitorHostTemplate() {
        return monitorHostTemplateDAO.getAll();
    }

    /**
     * 分页查找MonitorHostTemplate对象，查询条件MyQuery统一在service中构造并初始化
     *
     * @param page 。
     */
    public void findMonitorHostTemplateByPage(DBPaginatedList page, MonitorHostTemplate monitorHostTemplate) {
        String hql = "from MonitorHostTemplate";
        QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString(hql);
        queryTranslate.setOffset(true);
        queryTranslate.setPageStartNo((page.getPageNumber() - 1) * page.getObjectsPerPage());
        queryTranslate.setPageSize(page.getObjectsPerPage());

        //添加查询条件
        if (StringUtils.isNotBlank(monitorHostTemplate.getTemplateName())) {
            queryTranslate.addLikeCondition("templateName", monitorHostTemplate.getTemplateName());
        }
        if (monitorHostTemplate.getContactGroups().getContactgroupId() != null) {
            queryTranslate.addEqualCondition("contactGroups.contactgroupId", monitorHostTemplate.getContactGroups().getContactgroupId());
        }
        if (monitorHostTemplate.getHostgroups().getHostgroupId() != null) {
            queryTranslate.addEqualCondition("hostgroups.hostgroupId", monitorHostTemplate.getHostgroups().getHostgroupId());
        }

        //设置排序规则
        if (StringUtils.isNotBlank(page.getSortCriterion())) {
            queryTranslate.setOrderby(" order by " + page.getSortCriterion() + " " + page.getOrder());
        }
        monitorHostTemplateDAO.findMonitorHostTemplateByPage(page, queryTranslate);
    }

    /**
     * 根据id查找主机模板对象
     *
     * @param templateId .
     * @return .
     */
    public MonitorHostTemplate findMonitorHostTemplateById(Integer templateId) {
        return monitorHostTemplateDAO.get(templateId);
    }

    /**
     * 更新主机模板对象
     *
     * @param monitorHostTemplate .
     */
    public void updateMonitorHostTemplate(MonitorHostTemplate monitorHostTemplate) {
        monitorHostTemplateDAO.update(monitorHostTemplate);
    }

    /**
     * 根据id删除主机模板对象
     *
     * @param templateId .
     */
    public void deleteMonitorHostTemplate(Integer templateId) {
        monitorHostTemplateDAO.delete(findMonitorHostTemplateById(templateId));
    }

    /**
     * 保存服务模板
     *
     * @param monitorServiceTemplate .
     */
    public void saveMonitorServiceTemplate(MonitorServiceTemplate monitorServiceTemplate) throws TemplateAlreadyExistException {
        monitorServiceTemplateDAO.save(monitorServiceTemplate);
    }

    /**
     * 查找所有服务模板
     *
     * @return .
     */
    public List findAllMonitorServiceTemplate() {
        return monitorServiceTemplateDAO.getAll();
    }

    /**
     * 分页查找MonitorServiceTemplate对象，查询条件MyQuery统一在service中构造并初始化
     *
     * @param page 。
     */
    public void findMonitorServiceTemplateByPage(DBPaginatedList page, MonitorServiceTemplate monitorServiceTemplate) {
        String hql = "from MonitorServiceTemplate";
        QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString(hql);
        queryTranslate.setOffset(true);
        queryTranslate.setPageStartNo((page.getPageNumber() - 1) * page.getObjectsPerPage());
        queryTranslate.setPageSize(page.getObjectsPerPage());

        //添加查询条件
        if (StringUtils.isNotBlank(monitorServiceTemplate.getTemplateName())) {
            queryTranslate.addLikeCondition("templateName", monitorServiceTemplate.getTemplateName());
        }
        if (monitorServiceTemplate.getContactGroups().getContactgroupId() != null) {
            queryTranslate.addEqualCondition("contactGroups.contactgroupId", monitorServiceTemplate.getContactGroups().getContactgroupId());
        }

        //设置排序规则
        if (StringUtils.isNotBlank(page.getSortCriterion())) {
            queryTranslate.setOrderby(" order by " + page.getSortCriterion() + " " + page.getOrder());
        }
        monitorServiceTemplateDAO.findMonitorServiceTemplateByPage(page, queryTranslate);
    }

    /**
     * 根据id查找服务模板对象
     *
     * @param templateId .
     * @return .
     */
    public MonitorServiceTemplate findMonitorServiceTemplateById(Integer templateId) {
        return monitorServiceTemplateDAO.get(templateId);
    }

    /**
     * 更新服务模板对象
     *
     * @param monitorServiceTemplate .
     */
    public void updateMonitorServiceTemplate(MonitorServiceTemplate monitorServiceTemplate) {
        monitorServiceTemplateDAO.update(monitorServiceTemplate);
    }

    /**
     * 根据id删除服务模板对象
     *
     * @param templateId .
     */
    public void deleteMonitorServiceTemplate(Integer templateId) {
        monitorServiceTemplateDAO.delete(findMonitorServiceTemplateById(templateId));
    }

    /**
     * 保存联系人模板
     *
     * @param monitorContactTemplate .
     */
    public void saveMonitorContactTemplate(MonitorContactTemplate monitorContactTemplate) throws TemplateAlreadyExistException {
        if (monitorContactTemplateDAO.isExistMonitorContactTemplate(monitorContactTemplate.getTemplateName())) {
            throw new TemplateAlreadyExistException("该模板名称已被使用！");
        }
        monitorContactTemplateDAO.save(monitorContactTemplate);
    }

    public List findAllMonitorContactTemplate() {
        return monitorContactTemplateDAO.getAll();
    }

    /**
     * 分页查找MonitorContactTemplate对象，查询条件MyQuery统一在service中构造并初始化
     *
     * @param page .
     */
    public void findMonitorContactTemplateByPage(DBPaginatedList page, MonitorContactTemplate monitorContactTemplate) {
        String hql = "from MonitorContactTemplate";
        QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString(hql);
        queryTranslate.setOffset(true);
        queryTranslate.setPageStartNo((page.getPageNumber() - 1) * page.getObjectsPerPage());
        queryTranslate.setPageSize(page.getObjectsPerPage());

        //添加查询条件
        if (StringUtils.isNotBlank(monitorContactTemplate.getTemplateName())) {
            queryTranslate.addLikeCondition("templateName", monitorContactTemplate.getTemplateName());
        }
        if (StringUtils.isNotBlank(monitorContactTemplate.getHostNotificationOptions())) {
            queryTranslate.addLikeCondition("hostNotificationOptions", monitorContactTemplate.getHostNotificationOptions());
        }
        if (StringUtils.isNotBlank(monitorContactTemplate.getServiceNotificationOptions())) {
            queryTranslate.addLikeCondition("serviceNotificationOptions", monitorContactTemplate.getServiceNotificationOptions());
        }

        //设置排序规则
        if (StringUtils.isNotBlank(page.getSortCriterion())) {
            queryTranslate.setOrderby(" order by " + page.getSortCriterion() + " " + page.getOrder());
        }
        monitorContactTemplateDAO.findMonitorContactTemplateByPage(page, queryTranslate);
    }

    /**
     * 根据id查找联系人模板对象
     *
     * @param templateId .
     * @return .
     */
    public MonitorContactTemplate findMonitorContactTemplateById(Integer templateId) {
        return monitorContactTemplateDAO.get(templateId);
    }

    /**
     * 更新联系人模板对象
     *
     * @param monitorContactTemplate .
     */
    public void updateMonitorContactTemplate(MonitorContactTemplate monitorContactTemplate) {
        monitorContactTemplateDAO.update(monitorContactTemplate);
    }

    /**
     * 根据id删除联系人模板对象
     *
     * @param templateId .
     */
    public void deleteMonitorContactTemplate(Integer templateId) {
        monitorContactTemplateDAO.delete(findMonitorContactTemplateById(templateId));
    }

    /**
     * 保存时间域模板
     *
     * @param monitorTimePeriods .
     */
    public void saveMonitorTimePeriods(MonitorTimePeriods monitorTimePeriods) throws TemplateAlreadyExistException {
        if (monitorTimePeriodsDAO.isExistMonitorTimePeriods(monitorTimePeriods.getAlias())) {
            throw new TemplateAlreadyExistException("该模板名称已被使用！");
        }
        monitorTimePeriodsDAO.save(monitorTimePeriods);
    }

    public List findAllMonitorTimePeriods() {
        return monitorTimePeriodsDAO.getAll();
    }

    /**
     * 分页查找MonitorTimePeriods对象，查询条件MyQuery统一在service中构造并初始化
     *
     * @param page 。
     */
    public void findMonitorTimePeriodsByPage(DBPaginatedList page, MonitorTimePeriods monitorTimePeriods) {
        String hql = "from MonitorTimePeriods";
        QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString(hql);
        queryTranslate.setOffset(true);
        queryTranslate.setPageStartNo((page.getPageNumber() - 1) * page.getObjectsPerPage());
        queryTranslate.setPageSize(page.getObjectsPerPage());

        if (StringUtils.isNotBlank(monitorTimePeriods.getAlias())) {
            queryTranslate.addLikeCondition("alias", monitorTimePeriods.getAlias());
        }

        //设置排序规则
        if (StringUtils.isNotBlank(page.getSortCriterion())) {
            queryTranslate.setOrderby(" order by " + page.getSortCriterion() + " " + page.getOrder());
        }
        monitorTimePeriodsDAO.findMonitorTimePeriodsByPage(page, queryTranslate);
    }

    /**
     * 根据id查找时间域模板对象
     *
     * @param periodId .
     * @return .
     */
    public MonitorTimePeriods findMonitorTimePeriodsById(Integer periodId) {
        return monitorTimePeriodsDAO.get(periodId);
    }

    /**
     * 更新时间域模板对象
     *
     * @param monitorTimePeriods .
     */
    public void updateMonitorTimePeriods(MonitorTimePeriods monitorTimePeriods) {
        monitorTimePeriodsDAO.update(monitorTimePeriods);
    }

    /**
     * 根据id删除时间域模板对象
     *
     * @param periodId .
     */
    public void deleteMonitorTimePeriods(Integer periodId) throws BusinessException {
        if (isRelatedTimePeriods(periodId)) {
            throw new BusinessException("该时间域已被关联!");
        }
        monitorTimePeriodsDAO.delete(findMonitorTimePeriodsById(periodId));
    }

    /**
     * 检查该时间域是否被其他实体关联
     * 可能关联的实体有：MonitorHostTemplate,MonitorServiceTemplate,MonitorTermdevTemplate,MonitorHost,MonitorService
     *
     * @param periodId .
     * @return .
     */
    private boolean isRelatedTimePeriods(Integer periodId) {
        List list = new ArrayList();
        list.add("select count(t.templateId) from MonitorHostTemplate t where t.notificationTimeperiod.timeperiodId=" + periodId + " or t.checkTimeperiod.timeperiodId=" + periodId);
        list.add("select count(t.templateId) from MonitorServiceTemplate t where t.notificationTimeperiod.timeperiodId=" + periodId + " or t.checkTimeperiod.timeperiodId=" + periodId);
        list.add("select count(t.templateId) from MonitorTermdevTemplate t where t.notificationPeriod.timeperiodId=" + periodId + " or t.checkPeriod.timeperiodId=" + periodId);
        list.add("select count(t.hostId) from MonitorHost t where t.notificationTimeperiod.timeperiodId=" + periodId + " or t.checkTimeperiod.timeperiodId=" + periodId);
        list.add("select count(t.serviceId) from MonitorService t where t.notificationTimeperiod.timeperiodId=" + periodId + " or t.checkTimeperiod.timeperiodId=" + periodId);
        for (int i = 0; i < list.size(); i++) {
            String hql = list.get(i).toString();
            if (ResultTransform.getCount(monitorTimePeriodsDAO.find(hql)).intValue() > 0) {
                return true;
            }
        }
        return false;
    }

    /**
     * 保存监控配置模板
     *
     * @param monitorTermdevTemplate .
     */
    public void saveMonitorTermdevTemplate(MonitorTermdevTemplate monitorTermdevTemplate) throws TemplateAlreadyExistException {
        if (monitorTermdevTemplateDAO.isExistMonitorTermdevTemplate(monitorTermdevTemplate.getTemplateName())) {
            throw new TemplateAlreadyExistException("该模板名称已被使用！");
        }
        monitorTermdevTemplateDAO.save(monitorTermdevTemplate);
    }


    public List findAllMonitorTermdevTemplate() {
        return monitorTermdevTemplateDAO.getAll();
    }

    /**
     * 分页查找MonitorTermdevTemplate对象，查询条件MyQuery统一在service中构造并初始化
     *
     * @param page 。
     */
    public void findMonitorTermdevTemplateByPage(DBPaginatedList page, MonitorTermdevTemplate monitorTermdevTemplate) {
        String hql = "from MonitorTermdevTemplate";
        QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString(hql);
        queryTranslate.setOffset(true);
        queryTranslate.setPageStartNo((page.getPageNumber() - 1) * page.getObjectsPerPage());
        queryTranslate.setPageSize(page.getObjectsPerPage());

        if (StringUtils.isNotBlank(monitorTermdevTemplate.getTemplateName())) {
            queryTranslate.addLikeCondition("templateName", monitorTermdevTemplate.getTemplateName());
        }
        if (monitorTermdevTemplate.getContactGroups().getContactgroupId()!=null) {
            queryTranslate.addLikeCondition("contactGroups.contactgroupId", monitorTermdevTemplate.getContactGroups().getContactgroupId());
        }

        //设置排序规则
        if (StringUtils.isNotBlank(page.getSortCriterion())) {
            queryTranslate.setOrderby(" order by " + page.getSortCriterion() + " " + page.getOrder());
        }
        monitorTermdevTemplateDAO.findMonitorTermdevTemplateByPage(page, queryTranslate);
    }

    /**
     * 根据id查找监控配置模板对象
     *
     * @param templateId .
     * @return .
     */
    public MonitorTermdevTemplate findMonitorTermdevTemplateById(Integer templateId) {
        return monitorTermdevTemplateDAO.get(templateId);
    }

    public MonitorTermdevTemplateAll findMonitorTermdevTemplateAllById(Integer templateId) {
        return monitorTermdevTemplateDAO.getTermdevTemplateAll(templateId);
    }

    /**
     * 查询激活的设备模板
     *
     * @see org.king.template.service.TemplateService#getEnableMonitorTermdevTemplate()
     */
    public MonitorTermdevTemplate getEnableMonitorTermdevTemplate() {
        return monitorTermdevTemplateDAO.getEnableMonitorTermdevTemplate();
    }

    /**
     * 更新监控配置模板对象
     *
     * @param monitorTermdevTemplate .
     */
    public void updateMonitorTermdevTemplate(MonitorTermdevTemplate monitorTermdevTemplate) {
        monitorTermdevTemplateDAO.update(monitorTermdevTemplate);
    }

    public void updateMonitorTermdevTemplateAll(MonitorTermdevTemplateAll monitorTermdevTemplateAll) {
        monitorTermdevTemplateDAO.updateTermdevTemplateAll(monitorTermdevTemplateAll);
    }

    /**
     * 根据id删除监控配置模板对象
     *
     * @param templateId .
     */
    public void deleteMonitorTermdevTemplate(Integer templateId) throws BusinessException {
        if (isRelatedTermdevTemplate(templateId)) {
            throw new BusinessException("该设备模板已被关联！");
        }
        monitorTermdevTemplateDAO.delete(findMonitorTermdevTemplateById(templateId));
    }

    /**
     * 检查设备模板是否被其他实体关联
     * 设备模板可能和设备关联
     *
     * @param templateId .
     * @return .
     */
    private boolean isRelatedTermdevTemplate(Integer templateId) {
        String hql = "select count(t.deviceid) from MonitorDevtem t where t.templateid=" + templateId;
        if (ResultTransform.getCount(monitorTimePeriodsDAO.find(hql)).intValue() > 0) {
            return true;
        }
        return false;
    }

    /**
     * 获得主机通知命令
     *
     * @return .
     */
    public String[] getNotifyHostCommands() {
        return new String[]{Contants.NOTIFY_HOST_BY_EMAIL, Contants.NOTIFY_HOST_BY_SMS, ""};
    }

    /**
     * 获得服务通知命令
     *
     * @return .
     */
    public String[] getNotifyServiceCommands() {
        return new String[]{Contants.NOTIFY_SERVICE_BY_EMAIL, Contants.NOTIFY_SERVICE_BY_SMS};
    }
}
