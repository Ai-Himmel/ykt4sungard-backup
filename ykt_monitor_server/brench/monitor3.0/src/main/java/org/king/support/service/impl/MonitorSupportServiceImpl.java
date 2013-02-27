package org.king.support.service.impl;

import java.util.ArrayList;
import java.util.List;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.common.displaytag.DBPaginatedList;
import org.king.common.query.QueryTranslate;
import org.king.framework.exception.BusinessException;
import org.king.framework.service.impl.BaseService;
import org.king.host.dao.MonitorHostDAO;
import org.king.host.dao.MonitorHostscheduleddowntimeDAO;
import org.king.host.domain.MonitorHost;
import org.king.hostservice.dao.MonitorServiceDAO;
import org.king.hostservice.dao.MonitorSrvScheduleddowntimeDAO;
import org.king.hostservice.domain.MonitorService;
import org.king.support.dao.MonitorCommandsDAO;
import org.king.support.dao.MonitorContactDAO;
import org.king.support.dao.MonitorContactgroupsDAO;
import org.king.support.dao.MonitorNotificationsDAO;
import org.king.support.dao.MonitorRuntimevariablesDAO;
import org.king.support.dao.MonitorTimedeventqueueDAO;
import org.king.support.domain.MonitorContact;
import org.king.support.domain.MonitorContactgroups;
import org.king.support.domain.MonitorNotifications;
import org.king.support.domain.MonitorRuntimevariables;
import org.king.support.domain.MonitorTimedeventqueue;
import org.king.support.exception.ContactAlreadyExistException;
import org.king.support.exception.ContactgroupsAlreadyExistException;
import org.king.support.exception.RuntimevariablesAlreadyExistException;
import org.king.support.service.MonitorSupportService;
import org.king.template.dao.MonitorTermdevTemplateDAO;
import org.king.template.domain.MonitorTermdevTemplate;
import org.king.termdev.dao.MonitorDevscheduleddowntimeDAO;
import org.king.termdev.dao.MonitorTermdevchecksDAO;
import org.king.termdev.dao.MonitorTermdeviceStatusDAO;
import org.king.termdev.domain.MonitorTermdevchecks;
import org.king.termdev.domain.MonitorTermdeviceStatus;
import org.king.utils.DateUtil;
import org.king.utils.ResultTransform;


public class MonitorSupportServiceImpl extends BaseService implements MonitorSupportService {

    private static Log log = LogFactory.getLog(MonitorSupportServiceImpl.class);

    private MonitorTimedeventqueueDAO monitorTimedeventqueueDAO;
    private MonitorHostDAO monitorHostDAO;
    private MonitorServiceDAO monitorServiceDAO;
    private MonitorCommandsDAO monitorCommandsDAO;
    private MonitorContactDAO monitorContactDAO;
    private MonitorRuntimevariablesDAO monitorRuntimevariablesDAO;
    private MonitorContactgroupsDAO monitorContactgroupsDAO;
    private MonitorTermdevTemplateDAO monitorTermdevTemplateDAO;
    private MonitorNotificationsDAO monitorNotificationsDAO;
    private MonitorHostscheduleddowntimeDAO monitorHostscheduleddowntimeDAO;
    private MonitorSrvScheduleddowntimeDAO monitorSrvScheduleddowntimeDAO;
    private MonitorDevscheduleddowntimeDAO monitorDevscheduleddowntimeDAO;
    private MonitorTermdevchecksDAO monitorTermdevchecksDAO;
    private MonitorTermdeviceStatusDAO monitorTermdeviceStatusDAO;


    public void setMonitorTermdevchecksDAO(
			MonitorTermdevchecksDAO monitorTermdevchecksDAO) {
		this.monitorTermdevchecksDAO = monitorTermdevchecksDAO;
	}


	public void setMonitorTermdeviceStatusDAO(
			MonitorTermdeviceStatusDAO monitorTermdeviceStatusDAO) {
		this.monitorTermdeviceStatusDAO = monitorTermdeviceStatusDAO;
	}


	public void setMonitorTimedeventqueueDAO(
            MonitorTimedeventqueueDAO monitorTimedeventqueueDAO) {
        this.monitorTimedeventqueueDAO = monitorTimedeventqueueDAO;
    }


    public void setMonitorHostDAO(MonitorHostDAO monitorHostDAO) {
        this.monitorHostDAO = monitorHostDAO;
    }


    public void setMonitorServiceDAO(MonitorServiceDAO monitorServiceDAO) {
        this.monitorServiceDAO = monitorServiceDAO;
    }

    public void setMonitorCommandsDAO(MonitorCommandsDAO monitorCommandsDAO) {
        this.monitorCommandsDAO = monitorCommandsDAO;
    }

    public void setMonitorContactDAO(MonitorContactDAO monitorContactDAO) {
        this.monitorContactDAO = monitorContactDAO;
    }

    public void setMonitorRuntimevariablesDAO(MonitorRuntimevariablesDAO monitorRuntimevariablesDAO) {
        this.monitorRuntimevariablesDAO = monitorRuntimevariablesDAO;
    }

    public void setMonitorContactgroupsDAO(MonitorContactgroupsDAO monitorContactgroupsDAO) {
        this.monitorContactgroupsDAO = monitorContactgroupsDAO;
    }

    public void setMonitorTermdevTemplateDAO(
            MonitorTermdevTemplateDAO monitorTermdevTemplateDAO) {
        this.monitorTermdevTemplateDAO = monitorTermdevTemplateDAO;
    }

    public void setMonitorNotificationsDAO(
            MonitorNotificationsDAO monitorNotificationsDAO) {
        this.monitorNotificationsDAO = monitorNotificationsDAO;
    }


    public MonitorHostscheduleddowntimeDAO getMonitorHostscheduleddowntimeDAO() {
        return monitorHostscheduleddowntimeDAO;
    }


    public void setMonitorHostscheduleddowntimeDAO(
            MonitorHostscheduleddowntimeDAO monitorHostscheduleddowntimeDAO) {
        this.monitorHostscheduleddowntimeDAO = monitorHostscheduleddowntimeDAO;
    }


    public void setMonitorSrvScheduleddowntimeDAO(
            MonitorSrvScheduleddowntimeDAO monitorSrvScheduleddowntimeDAO) {
        this.monitorSrvScheduleddowntimeDAO = monitorSrvScheduleddowntimeDAO;
    }


    public void setMonitorDevscheduleddowntimeDAO(
            MonitorDevscheduleddowntimeDAO monitorDevscheduleddowntimeDAO) {
        this.monitorDevscheduleddowntimeDAO = monitorDevscheduleddowntimeDAO;
    }


    public List initMonitorTask() throws BusinessException {
        //��������������������ն��豸���ճ̼ƻ�����
        //ֻ�����ն˼������ճ̼ƻ�
        //��Ϊֻ�м������ʱ���й�ϵ����Ҫ�����ԣ�������Ҫ��¼
        List queueList = monitorTimedeventqueueDAO.getAll();
        for (int i = 0; i < queueList.size(); i++) {
            MonitorTimedeventqueue mt = (MonitorTimedeventqueue) queueList.get(i);
            if (mt.getEventType() != 4) {
                monitorTimedeventqueueDAO.delete(mt);
                queueList.remove(i);
                i--;
            }
        }
        List hostList = monitorHostDAO.getAll();
        String nowtime = DateUtil.getNow();
        for (int i = 0; i < hostList.size(); i++) {
            //�����������
            MonitorHost mh = (MonitorHost) hostList.get(i);
            MonitorTimedeventqueue newMT = new MonitorTimedeventqueue();
            newMT.setEventType(1);
            newMT.setObjectId(mh.getHostId());
            newMT.setQueueTime(nowtime);
            newMT.setRecurringEvent(1);
            newMT.setScheduledTime(DateUtil.getNewTime(nowtime, 60 + i * 3));
            monitorTimedeventqueueDAO.save(newMT);
        }

        List serviceList = monitorServiceDAO.getAll();
        for (int i = 0; i < serviceList.size(); i++) {
            //��������������
            MonitorService ms = (MonitorService) serviceList.get(i);
            MonitorTimedeventqueue newMT = new MonitorTimedeventqueue();
            newMT.setEventType(2);
            newMT.setObjectId(ms.getServiceId());
            newMT.setQueueTime(nowtime);
            newMT.setRecurringEvent(1);
            newMT.setScheduledTime(DateUtil.getNewTime(nowtime, 120 + i * 3));
            monitorTimedeventqueueDAO.save(newMT);
        }

        //�豸����
        List termdevtemplateList = monitorTermdevTemplateDAO.getAll();
        for (int i = 0; i < termdevtemplateList.size(); i++) {
            MonitorTermdevTemplate mttemplate = (MonitorTermdevTemplate) termdevtemplateList.get(i);
            MonitorTimedeventqueue termdev = new MonitorTimedeventqueue();
            termdev.setEventType(3);
            termdev.setObjectId(mttemplate.getTemplateId());
            termdev.setQueueTime(nowtime);
            termdev.setRecurringEvent(1);
            termdev.setScheduledTime(DateUtil.getNewTime(nowtime, 180 + i * 3));
            monitorTimedeventqueueDAO.save(termdev);
        }

/*
        if (queueList == null || queueList.size() == 0) {
            //�豸�����
            MonitorTimedeventqueue termservice1 = new MonitorTimedeventqueue();
            termservice1.setEventType(4);
            termservice1.setObjectId(-1);
            termservice1.setQueueTime(nowtime);
            termservice1.setRecurringEvent(1);
            termservice1.setScheduledTime(DateUtil.getNewTime(nowtime, 240));
            monitorTimedeventqueueDAO.save(termservice1);
            MonitorTimedeventqueue termservice2 = new MonitorTimedeventqueue();
            termservice2.setEventType(4);
            termservice2.setObjectId(-2);
            termservice2.setQueueTime(nowtime);
            termservice2.setRecurringEvent(1);
            termservice2.setScheduledTime(DateUtil.getNewTime(nowtime, 270));
            monitorTimedeventqueueDAO.save(termservice2);
            MonitorTimedeventqueue termservice3 = new MonitorTimedeventqueue();
            termservice3.setEventType(4);
            termservice3.setObjectId(-3);
            termservice3.setQueueTime(nowtime);
            termservice3.setRecurringEvent(1);
            termservice3.setScheduledTime(DateUtil.getNewTime(nowtime, 300));
            monitorTimedeventqueueDAO.save(termservice3);
            MonitorTimedeventqueue termservice4 = new MonitorTimedeventqueue();
            termservice4.setEventType(4);
            termservice4.setObjectId(-4);
            termservice4.setQueueTime(nowtime);
            termservice4.setRecurringEvent(1);
            termservice4.setScheduledTime(DateUtil.getNewTime(nowtime, 330));
            monitorTimedeventqueueDAO.save(termservice4);

        }
        
        */
        
        //֪ͨ����
        MonitorTimedeventqueue termdev = new MonitorTimedeventqueue();
        termdev.setEventType(5);
        termdev.setObjectId(-1);
        termdev.setQueueTime(nowtime);
        termdev.setRecurringEvent(1);
        termdev.setScheduledTime(DateUtil.getNewTime(nowtime, 360));
        monitorTimedeventqueueDAO.save(termdev);


        return monitorTimedeventqueueDAO.getAll();


    }

    /**
     * ���Ҳ�ͬ���͵�����
     *
     * @param configType .
     * @return .
     * @throws BusinessException
     */
    public List findMonitorCommands(Integer configType) throws BusinessException {
        String hql = "from MonitorCommands t where t.configType=" + configType.intValue();
        return monitorCommandsDAO.find(hql);
    }

    /**
     * ������ϵ��
     *
     * @param monitorContact .
     */
    public void saveMonitorContact(MonitorContact monitorContact) throws ContactAlreadyExistException {
        if (monitorContactDAO.isExistMonitorContact(monitorContact.getContactName())) {
            throw new ContactAlreadyExistException("����ϵ�������ѱ�ʹ�ã�");
        }
        monitorContactDAO.save(monitorContact);
    }

    public List findAllMonitorContact() {
        return monitorContactDAO.getAll();
    }
    
    public List findMonitorContactByGroup(Integer groupid){
    	return monitorContactDAO.findContactBygroup(groupid);
    }

    /**
     * ��ҳ����MonitorContact���󣬲�ѯ����MyQueryͳһ��service�й��첢��ʼ��
     *
     * @param page ��
     */
    public void findMonitorContactByPage(DBPaginatedList page, MonitorContact monitorContact) {
        String hql = "from MonitorContact";
        QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString(hql);
        queryTranslate.setOffset(true);
        queryTranslate.setPageStartNo((page.getPageNumber() - 1) * page.getObjectsPerPage());
        queryTranslate.setPageSize(page.getObjectsPerPage());

        if (StringUtils.isNotBlank(monitorContact.getContactName())) {
            queryTranslate.addLikeCondition("contactName", monitorContact.getContactName());
        }

        //�����������
        if (StringUtils.isNotBlank(page.getSortCriterion())) {
            queryTranslate.setOrderby(" order by " + page.getSortCriterion() + " " + page.getOrder());
        }
        monitorContactDAO.findMonitorContactByPage(page, queryTranslate);
    }

    /**
     * ����id������ϵ��
     *
     * @param id .
     * @return .
     */
    public MonitorContact findMonitorContactById(Integer id) {
        return monitorContactDAO.get(id);
    }

    /**
     * ������ϵ��
     *
     * @param monitorContact .
     */
    public void updateMonitorContact(MonitorContact monitorContact) {
        monitorContactDAO.update(monitorContact);
    }

    /**
     * ����idɾ����ϵ��
     *
     * @param id .
     */
    public void deleteMonitorContact(Integer id) {
        monitorContactDAO.delete(findMonitorContactById(id));
    }

    /**
     * �������б���
     *
     * @param monitorRuntimevariables .
     */
    public void saveMonitorRuntimevariables(MonitorRuntimevariables monitorRuntimevariables) throws RuntimevariablesAlreadyExistException {
        if (monitorRuntimevariablesDAO.isExistMonitorRuntimevariables(monitorRuntimevariables.getVarname())) {
            throw new RuntimevariablesAlreadyExistException("�ò��������ѱ�ʹ�ã�");
        }
        monitorRuntimevariablesDAO.save(monitorRuntimevariables);
    }

    public List findAllMonitorRuntimevariables() {
        return monitorRuntimevariablesDAO.getAll();
    }

    /**
     * ��ҳ����MonitorRuntimevariables���󣬲�ѯ����MyQueryͳһ��service�й��첢��ʼ��
     *
     * @param page ��
     */
    public void findMonitorRuntimevariablesByPage(DBPaginatedList page, MonitorRuntimevariables monitorRuntimevariables) {
        String hql = "from MonitorRuntimevariables";
        QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString(hql);
        queryTranslate.setOffset(true);
        queryTranslate.setPageStartNo((page.getPageNumber() - 1) * page.getObjectsPerPage());
        queryTranslate.setPageSize(page.getObjectsPerPage());

        //��Ӳ�ѯ����
        if (StringUtils.isNotBlank(monitorRuntimevariables.getVarname())) {
            queryTranslate.addLikeCondition("varname", monitorRuntimevariables.getVarname());
        }

        //�����������
        if (StringUtils.isNotBlank(page.getSortCriterion())) {
            queryTranslate.setOrderby(" order by " + page.getSortCriterion() + " " + page.getOrder());
        }
        monitorRuntimevariablesDAO.findMonitorRuntimevariablesByPage(page, queryTranslate);
    }

    /**
     * ����id���ұ���
     *
     * @param id .
     * @return .
     */
    public MonitorRuntimevariables findMonitorRuntimevariablesById(Integer id) {
        return monitorRuntimevariablesDAO.get(id);
    }

    /**
     * �������б���
     *
     * @param monitorRuntimevariables .
     */
    public void updateMonitorRuntimevariables(MonitorRuntimevariables monitorRuntimevariables) {
        monitorRuntimevariablesDAO.update(monitorRuntimevariables);
    }

    /**
     * ����idɾ�����б���
     *
     * @param id .
     */
    public void deleteMonitorRuntimevariables(Integer id) {
        monitorRuntimevariablesDAO.delete(findMonitorRuntimevariablesById(id));
    }

    /**
     * ����id������ϵ�������
     *
     * @param id .
     * @return
     */
    public MonitorContactgroups getMonitorContactgroups(Integer id) {
        return monitorContactgroupsDAO.get(id);
    }

    /**
     * ������ϵ����
     *
     * @param monitorContactgroups .
     * @throws ContactgroupsAlreadyExistException
     *          .
     */
    public void saveMonitorContactgroups(MonitorContactgroups monitorContactgroups) throws ContactgroupsAlreadyExistException {
        if (monitorContactgroupsDAO.isExistMonitorContactgroups(monitorContactgroups.getContactgroupName())) {
            throw new ContactgroupsAlreadyExistException("����ϵ�����ѱ�ʹ�ã�");
        }
        monitorContactgroupsDAO.save(monitorContactgroups);
    }

    /**
     * �������е���ϵ����
     *
     * @return .
     * @throws BusinessException .
     */
    public List findAllMonitorContactgroups() throws BusinessException {
        return monitorContactgroupsDAO.getAll();
    }

    /**
     * ������ϵ����
     *
     * @param monitorContactgroups .
     */
    public void updateMonitorContactgroups(MonitorContactgroups monitorContactgroups) throws ContactgroupsAlreadyExistException {
        String hql = "from MonitorContactgroups t where t.contactgroupId<>" + monitorContactgroups.getContactgroupId() + " and t.contactgroupName='" + monitorContactgroups.getContactgroupName() + "'";
        List result = monitorContactgroupsDAO.find(hql);
        if (result != null && result.size() > 0) {
            throw new ContactgroupsAlreadyExistException("����ϵ�����Ѵ��ڣ�");
        }
        monitorContactgroupsDAO.update(monitorContactgroups);
    }

    /**
     * ��������ɾ����ϵ�������
     *
     * @param id .
     */
    public void deleteMonitorContactgroups(Integer id) throws BusinessException {
        if (isRelatedContactgroups(id)) {
            throw new BusinessException("����ϵ�����ѱ�������");
        }
        monitorContactgroupsDAO.delete(getMonitorContactgroups(id));
    }

    /**
     * ������ϵ�����Ƿ�����ʵ�����
     * ���ܹ�����ʵ���У�MonitorHostTemplate,MonitorServiceTemplate,MonitorTermdevTemplate,MonitorHost,MonitorService,MonitorContact
     *
     * @param groupId .
     * @return .
     */
    private boolean isRelatedContactgroups(Integer groupId) {
        List list = new ArrayList();
        list.add("select count(t.templateId) from MonitorHostTemplate t where t.contactGroups.contactgroupId=" + groupId);
        list.add("select count(t.templateId) from MonitorServiceTemplate t where t.contactGroups.contactgroupId=" + groupId);
        list.add("select count(t.templateId) from MonitorTermdevTemplate t where t.contactGroups.contactgroupId=" + groupId);
        list.add("select count(t.hostId) from MonitorHost t where t.contactGroups.contactgroupId=" + groupId);
        list.add("select count(t.serviceId) from MonitorService t where t.contactGroups.contactgroupId=" + groupId);
        list.add("select count(t.contactId) from MonitorContact t where t.contactGroups.contactgroupId=" + groupId);
        for (int i = 0; i < list.size(); i++) {
            String hql = list.get(i).toString();
            if (ResultTransform.getCount(monitorContactgroupsDAO.find(hql)).intValue() > 0) {
                return true;
            }
        }
        return false;
    }

    /**
     * ��ҳ����MonitorContactgroups���󣬲�ѯ����MyQueryͳһ��service�й��첢��ʼ��
     *
     * @param page                 .
     * @param monitorContactgroups .
     */
    public void findMonitorContactgroupsByPage(DBPaginatedList page, MonitorContactgroups monitorContactgroups) {
        String hql = "from MonitorContactgroups";
        QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString(hql);
        queryTranslate.setOffset(true);
        queryTranslate.setPageStartNo((page.getPageNumber() - 1) * page.getObjectsPerPage());
        queryTranslate.setPageSize(page.getObjectsPerPage());

        //��Ӳ�ѯ����
        if (StringUtils.isNotBlank(monitorContactgroups.getContactgroupName())) {
            queryTranslate.addLikeCondition("contactgroupName", monitorContactgroups.getContactgroupName());
        }

        //�����������
        if (StringUtils.isNotBlank(page.getSortCriterion())) {
            queryTranslate.setOrderby(" order by " + page.getSortCriterion() + " " + page.getOrder());
        }
        monitorContactgroupsDAO.findMonitorContactgroupsByPage(page, queryTranslate);
    }


    public MonitorTimedeventqueue findMonitorTimedeventqueueByObjectAndType(
            Integer objectId, Integer eventType) {
        return monitorTimedeventqueueDAO.findMonitorTimedeventqueueByObjectAndType(objectId, eventType);
    }


    public void saveMonitorTimedeventqueue(MonitorTimedeventqueue mt) {
        monitorTimedeventqueueDAO.save(mt);
    }


    public void deleteMonitorTimedeventqueue(MonitorTimedeventqueue mt) {
        monitorTimedeventqueueDAO.delete(mt);

    }


    public void updateMonitorTimedeventqueue(MonitorTimedeventqueue mt) {
        monitorTimedeventqueueDAO.update(mt);

    }

    /**
     * Description: ����֪ͨ��Ϣ
     *
     * @param @param mn
     * @return void
     *         Modify History: 2010-8-10 Linqing.He create
     */
    public void saveMonitorNotifications(MonitorNotifications mn) {
        monitorNotificationsDAO.save(mn);
    }

    /**
     * Description: ����֪ͨ��Ϣ
     *
     * @param @param mn
     * @return void
     *         Modify History: 2010-8-10 Linqing.He create
     */
    public void updateMonitorNotifications(MonitorNotifications mn) {
        monitorNotificationsDAO.update(mn);
    }

    /**
     * Description: ɾ��֪ͨ��Ϣ
     *
     * @param @param mn
     * @return void
     *         Modify History: 2010-8-10 Linqing.He create
     */
    public void deleteMonitorNotifications(MonitorNotifications mn) {
        monitorNotificationsDAO.delete(mn);
    }


    /* (non-Javadoc)
      * @see org.king.support.service.MonitorSupportService#checkdowntime(java.lang.Integer, java.lang.String)
      */

    public boolean checkHostDowntime(Integer objectid, String nowtime) {
        return monitorHostscheduleddowntimeDAO.checkHostDowntime(objectid, nowtime);
    }

    public boolean checkHostserviceDowntime(Integer objectid, String nowtime) {
        return monitorSrvScheduleddowntimeDAO.checkSrvDowntime(objectid, nowtime);
    }

    public boolean checkDevDowntime(Integer objectid, String nowtime) {
        return monitorDevscheduleddowntimeDAO.checkDevDowntime(objectid, nowtime);
    }


	public List getMonitorNotificationsByFlag(Integer sendOrNot) {
		List list = monitorNotificationsDAO.find("from MonitorNotifications where sendOrNot="+sendOrNot+" order by notificationType,contactGroup.contactgroupId");
		return list;
	}
	
	 public List findMonitorContactBygroup(Integer groupid){
		 List list = monitorContactDAO.findContactBygroup(groupid);
		 return list;
	 }


	public MonitorTermdevchecks findLastMonitorTermdevchecksByTermid(Integer id) {
		// TODO Auto-generated method stub
		List list = monitorTermdevchecksDAO.find("from MonitorTermdevchecks where deviceId="+id+" and (endTime is null or endTime='')");
		if(list!=null&&list.size()>0){
			return (MonitorTermdevchecks)list.get(0);
		}
		return null;
	}


	public List findMonitorTermdeviceStatusOffTemplate() {
		// TODO Auto-generated method stub
		List list = monitorTermdeviceStatusDAO.find("from MonitorTermdeviceStatus a where a.deviceId not in(select md.deviceid from MonitorDevtem md)");
		return list;
	}


	public void deleteMonitorTermdeviceStatusOffTemplate(MonitorTermdeviceStatus MTs) {
		monitorTermdeviceStatusDAO.delete(MTs);
	}


	public void updateLastMonitorTermdevchecks(MonitorTermdevchecks MTc) {
		monitorTermdevchecksDAO.update(MTc);		
	}


	public MonitorRuntimevariables findMonitorRuntimevariablesByName(
			String varname) {
		List list = monitorRuntimevariablesDAO.find("from MonitorRuntimevariables where varname='"+varname+"'");
		if(list!=null&&list.size()>0){
			return (MonitorRuntimevariables)list.get(0);
		}
		return null;
	}

}
