package org.king.template.dao.hibernate;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.hibernate.BaseDAOHibernate;
import org.king.template.dao.MonitorHostTemplateDAO;
import org.king.template.domain.MonitorHostTemplate;
import org.king.utils.PaginationUtil;

import java.io.Serializable;
import java.util.List;

/**
 * Data access object (DAO) for domain model class MonitorHostTemplate.
 *
 * @author MyEclipse - Hibernate Tools
 * @see org.king.template.dao.hibernate.MonitorHostTemplate
 */
public class MonitorHostTemplateDAOHibernate implements MonitorHostTemplateDAO {

    private static final Log log = LogFactory.getLog(MonitorHostTemplateDAOHibernate.class);

    private BaseDAO baseDAO;

    public void setBaseDAO(BaseDAO baseDAO) {
        this.baseDAO = baseDAO;
    }

    public BaseDAO getBaseDAO() {
        return baseDAO;
    }

    public List find(MyQuery myQuery) {
        log.debug("finding MonitorHostTemplate instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }

    public List find(String query) {
        log.debug("finding MonitorHostTemplate instance by query");
        return baseDAO.findEntity(query);
    }

    public MonitorHostTemplate get(Serializable id) {
        log.debug("getting MonitorHostTemplate instance by id");
        return (MonitorHostTemplate) baseDAO.getEntity(MonitorHostTemplate.class, id);
    }

    public List getAll() {
        log.debug("getting MonitorHostTemplate all");
        String allHql = "from MonitorHostTemplate";
        return baseDAO.findEntity(allHql);
    }

    public void save(MonitorHostTemplate transientInstance) {
        log.debug("saving MonitorHostTemplate instance");
        baseDAO.saveEntity(transientInstance);
    }

    public void update(MonitorHostTemplate transientInstance) {
        log.debug("updating MonitorHostTemplate instance");
        baseDAO.updateEntity(transientInstance);
    }


    public void delete(MonitorHostTemplate persistentInstance) {
        log.debug("deleting MonitorHostTemplate instance");
        baseDAO.removeEntity(persistentInstance);
    }

    public void findMonitorHostTemplateByPage(DBPaginatedList page, MyQuery myQuery) {
        PaginationUtil.executeHibernatePage(page, (BaseDAOHibernate) baseDAO, myQuery);
    }

    /**
     * 根据模板名字判断该模板是否已存在
     *
     * @param templateName
     * @return
     */
    public boolean isExistMonitorHostTemplate(String templateName) {
        StringBuffer hql = new StringBuffer("from MonitorHostTemplate t where t.templateName='");
        hql.append(templateName);
        hql.append("'");

        List result = baseDAO.findEntity(hql.toString());
        if (result != null && result.size() > 0) {
            return true;
        }
        return false;
    }
}