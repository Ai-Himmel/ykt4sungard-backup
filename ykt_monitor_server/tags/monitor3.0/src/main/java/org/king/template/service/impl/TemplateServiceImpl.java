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
 * ģ�����������.
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
     * ��������ģ��
     *
     * @param monitorHostTemplate .
     */
    public void saveMonitorHostTemplate(MonitorHostTemplate monitorHostTemplate) throws TemplateAlreadyExistException {
        if (monitorHostTemplateDAO.isExistMonitorHostTemplate(monitorHostTemplate.getTemplateName())) {
            throw new TemplateAlreadyExistException("��ģ�������ѱ�ʹ�ã�");
        }
        monitorHostTemplateDAO.save(monitorHostTemplate);
    }

    public List findAllMonitorHostTemplate() {
        return monitorHostTemplateDAO.getAll();
    }

    /**
     * ��ҳ����MonitorHostTemplate���󣬲�ѯ����MyQueryͳһ��service�й��첢��ʼ��
     *
     * @param page ��
     */
    public void findMonitorHostTemplateByPage(DBPaginatedList page, MonitorHostTemplate monitorHostTemplate) {
        String hql = "from MonitorHostTemplate";
        QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString(hql);
        queryTranslate.setOffset(true);
        queryTranslate.setPageStartNo((page.getPageNumber() - 1) * page.getObjectsPerPage());
        queryTranslate.setPageSize(page.getObjectsPerPage());

        //��Ӳ�ѯ����
        if (StringUtils.isNotBlank(monitorHostTemplate.getTemplateName())) {
            queryTranslate.addLikeCondition("templateName", monitorHostTemplate.getTemplateName());
        }
        if (monitorHostTemplate.getContactGroups().getContactgroupId() != null) {
            queryTranslate.addEqualCondition("contactGroups.contactgroupId", monitorHostTemplate.getContactGroups().getContactgroupId());
        }
        if (monitorHostTemplate.getHostgroups().getHostgroupId() != null) {
            queryTranslate.addEqualCondition("hostgroups.hostgroupId", monitorHostTemplate.getHostgroups().getHostgroupId());
        }

        //�����������
        if (StringUtils.isNotBlank(page.getSortCriterion())) {
            queryTranslate.setOrderby(" order by " + page.getSortCriterion() + " " + page.getOrder());
        }
        monitorHostTemplateDAO.findMonitorHostTemplateByPage(page, queryTranslate);
    }

    /**
     * ����id��������ģ�����
     *
     * @param templateId .
     * @return .
     */
    public MonitorHostTemplate findMonitorHostTemplateById(Integer templateId) {
        return monitorHostTemplateDAO.get(templateId);
    }

    /**
     * ��������ģ�����
     *
     * @param monitorHostTemplate .
     */
    public void updateMonitorHostTemplate(MonitorHostTemplate monitorHostTemplate) {
        monitorHostTemplateDAO.update(monitorHostTemplate);
    }

    /**
     * ����idɾ������ģ�����
     *
     * @param templateId .
     */
    public void deleteMonitorHostTemplate(Integer templateId) {
        monitorHostTemplateDAO.delete(findMonitorHostTemplateById(templateId));
    }

    /**
     * �������ģ��
     *
     * @param monitorServiceTemplate .
     */
    public void saveMonitorServiceTemplate(MonitorServiceTemplate monitorServiceTemplate) throws TemplateAlreadyExistException {
        monitorServiceTemplateDAO.save(monitorServiceTemplate);
    }

    /**
     * �������з���ģ��
     *
     * @return .
     */
    public List findAllMonitorServiceTemplate() {
        return monitorServiceTemplateDAO.getAll();
    }

    /**
     * ��ҳ����MonitorServiceTemplate���󣬲�ѯ����MyQueryͳһ��service�й��첢��ʼ��
     *
     * @param page ��
     */
    public void findMonitorServiceTemplateByPage(DBPaginatedList page, MonitorServiceTemplate monitorServiceTemplate) {
        String hql = "from MonitorServiceTemplate";
        QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString(hql);
        queryTranslate.setOffset(true);
        queryTranslate.setPageStartNo((page.getPageNumber() - 1) * page.getObjectsPerPage());
        queryTranslate.setPageSize(page.getObjectsPerPage());

        //��Ӳ�ѯ����
        if (StringUtils.isNotBlank(monitorServiceTemplate.getTemplateName())) {
            queryTranslate.addLikeCondition("templateName", monitorServiceTemplate.getTemplateName());
        }
        if (monitorServiceTemplate.getContactGroups().getContactgroupId() != null) {
            queryTranslate.addEqualCondition("contactGroups.contactgroupId", monitorServiceTemplate.getContactGroups().getContactgroupId());
        }

        //�����������
        if (StringUtils.isNotBlank(page.getSortCriterion())) {
            queryTranslate.setOrderby(" order by " + page.getSortCriterion() + " " + page.getOrder());
        }
        monitorServiceTemplateDAO.findMonitorServiceTemplateByPage(page, queryTranslate);
    }

    /**
     * ����id���ҷ���ģ�����
     *
     * @param templateId .
     * @return .
     */
    public MonitorServiceTemplate findMonitorServiceTemplateById(Integer templateId) {
        return monitorServiceTemplateDAO.get(templateId);
    }

    /**
     * ���·���ģ�����
     *
     * @param monitorServiceTemplate .
     */
    public void updateMonitorServiceTemplate(MonitorServiceTemplate monitorServiceTemplate) {
        monitorServiceTemplateDAO.update(monitorServiceTemplate);
    }

    /**
     * ����idɾ������ģ�����
     *
     * @param templateId .
     */
    public void deleteMonitorServiceTemplate(Integer templateId) {
        monitorServiceTemplateDAO.delete(findMonitorServiceTemplateById(templateId));
    }

    /**
     * ������ϵ��ģ��
     *
     * @param monitorContactTemplate .
     */
    public void saveMonitorContactTemplate(MonitorContactTemplate monitorContactTemplate) throws TemplateAlreadyExistException {
        if (monitorContactTemplateDAO.isExistMonitorContactTemplate(monitorContactTemplate.getTemplateName())) {
            throw new TemplateAlreadyExistException("��ģ�������ѱ�ʹ�ã�");
        }
        monitorContactTemplateDAO.save(monitorContactTemplate);
    }

    public List findAllMonitorContactTemplate() {
        return monitorContactTemplateDAO.getAll();
    }

    /**
     * ��ҳ����MonitorContactTemplate���󣬲�ѯ����MyQueryͳһ��service�й��첢��ʼ��
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

        //��Ӳ�ѯ����
        if (StringUtils.isNotBlank(monitorContactTemplate.getTemplateName())) {
            queryTranslate.addLikeCondition("templateName", monitorContactTemplate.getTemplateName());
        }
        if (StringUtils.isNotBlank(monitorContactTemplate.getHostNotificationOptions())) {
            queryTranslate.addLikeCondition("hostNotificationOptions", monitorContactTemplate.getHostNotificationOptions());
        }
        if (StringUtils.isNotBlank(monitorContactTemplate.getServiceNotificationOptions())) {
            queryTranslate.addLikeCondition("serviceNotificationOptions", monitorContactTemplate.getServiceNotificationOptions());
        }

        //�����������
        if (StringUtils.isNotBlank(page.getSortCriterion())) {
            queryTranslate.setOrderby(" order by " + page.getSortCriterion() + " " + page.getOrder());
        }
        monitorContactTemplateDAO.findMonitorContactTemplateByPage(page, queryTranslate);
    }

    /**
     * ����id������ϵ��ģ�����
     *
     * @param templateId .
     * @return .
     */
    public MonitorContactTemplate findMonitorContactTemplateById(Integer templateId) {
        return monitorContactTemplateDAO.get(templateId);
    }

    /**
     * ������ϵ��ģ�����
     *
     * @param monitorContactTemplate .
     */
    public void updateMonitorContactTemplate(MonitorContactTemplate monitorContactTemplate) {
        monitorContactTemplateDAO.update(monitorContactTemplate);
    }

    /**
     * ����idɾ����ϵ��ģ�����
     *
     * @param templateId .
     */
    public void deleteMonitorContactTemplate(Integer templateId) {
        monitorContactTemplateDAO.delete(findMonitorContactTemplateById(templateId));
    }

    /**
     * ����ʱ����ģ��
     *
     * @param monitorTimePeriods .
     */
    public void saveMonitorTimePeriods(MonitorTimePeriods monitorTimePeriods) throws TemplateAlreadyExistException {
        if (monitorTimePeriodsDAO.isExistMonitorTimePeriods(monitorTimePeriods.getAlias())) {
            throw new TemplateAlreadyExistException("��ģ�������ѱ�ʹ�ã�");
        }
        monitorTimePeriodsDAO.save(monitorTimePeriods);
    }

    public List findAllMonitorTimePeriods() {
        return monitorTimePeriodsDAO.getAll();
    }

    /**
     * ��ҳ����MonitorTimePeriods���󣬲�ѯ����MyQueryͳһ��service�й��첢��ʼ��
     *
     * @param page ��
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

        //�����������
        if (StringUtils.isNotBlank(page.getSortCriterion())) {
            queryTranslate.setOrderby(" order by " + page.getSortCriterion() + " " + page.getOrder());
        }
        monitorTimePeriodsDAO.findMonitorTimePeriodsByPage(page, queryTranslate);
    }

    /**
     * ����id����ʱ����ģ�����
     *
     * @param periodId .
     * @return .
     */
    public MonitorTimePeriods findMonitorTimePeriodsById(Integer periodId) {
        return monitorTimePeriodsDAO.get(periodId);
    }

    /**
     * ����ʱ����ģ�����
     *
     * @param monitorTimePeriods .
     */
    public void updateMonitorTimePeriods(MonitorTimePeriods monitorTimePeriods) {
        monitorTimePeriodsDAO.update(monitorTimePeriods);
    }

    /**
     * ����idɾ��ʱ����ģ�����
     *
     * @param periodId .
     */
    public void deleteMonitorTimePeriods(Integer periodId) throws BusinessException {
        if (isRelatedTimePeriods(periodId)) {
            throw new BusinessException("��ʱ�����ѱ�����!");
        }
        monitorTimePeriodsDAO.delete(findMonitorTimePeriodsById(periodId));
    }

    /**
     * ����ʱ�����Ƿ�����ʵ�����
     * ���ܹ�����ʵ���У�MonitorHostTemplate,MonitorServiceTemplate,MonitorTermdevTemplate,MonitorHost,MonitorService
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
     * ����������ģ��
     *
     * @param monitorTermdevTemplate .
     */
    public void saveMonitorTermdevTemplate(MonitorTermdevTemplate monitorTermdevTemplate) throws TemplateAlreadyExistException {
        if (monitorTermdevTemplateDAO.isExistMonitorTermdevTemplate(monitorTermdevTemplate.getTemplateName())) {
            throw new TemplateAlreadyExistException("��ģ�������ѱ�ʹ�ã�");
        }
        monitorTermdevTemplateDAO.save(monitorTermdevTemplate);
    }


    public List findAllMonitorTermdevTemplate() {
        return monitorTermdevTemplateDAO.getAll();
    }

    /**
     * ��ҳ����MonitorTermdevTemplate���󣬲�ѯ����MyQueryͳһ��service�й��첢��ʼ��
     *
     * @param page ��
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

        //�����������
        if (StringUtils.isNotBlank(page.getSortCriterion())) {
            queryTranslate.setOrderby(" order by " + page.getSortCriterion() + " " + page.getOrder());
        }
        monitorTermdevTemplateDAO.findMonitorTermdevTemplateByPage(page, queryTranslate);
    }

    /**
     * ����id���Ҽ������ģ�����
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
     * ��ѯ������豸ģ��
     *
     * @see org.king.template.service.TemplateService#getEnableMonitorTermdevTemplate()
     */
    public MonitorTermdevTemplate getEnableMonitorTermdevTemplate() {
        return monitorTermdevTemplateDAO.getEnableMonitorTermdevTemplate();
    }

    /**
     * ���¼������ģ�����
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
     * ����idɾ���������ģ�����
     *
     * @param templateId .
     */
    public void deleteMonitorTermdevTemplate(Integer templateId) throws BusinessException {
        if (isRelatedTermdevTemplate(templateId)) {
            throw new BusinessException("���豸ģ���ѱ�������");
        }
        monitorTermdevTemplateDAO.delete(findMonitorTermdevTemplateById(templateId));
    }

    /**
     * ����豸ģ���Ƿ�����ʵ�����
     * �豸ģ����ܺ��豸����
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
     * �������֪ͨ����
     *
     * @return .
     */
    public String[] getNotifyHostCommands() {
        return new String[]{Contants.NOTIFY_HOST_BY_EMAIL, Contants.NOTIFY_HOST_BY_SMS, ""};
    }

    /**
     * ��÷���֪ͨ����
     *
     * @return .
     */
    public String[] getNotifyServiceCommands() {
        return new String[]{Contants.NOTIFY_SERVICE_BY_EMAIL, Contants.NOTIFY_SERVICE_BY_SMS};
    }
}
