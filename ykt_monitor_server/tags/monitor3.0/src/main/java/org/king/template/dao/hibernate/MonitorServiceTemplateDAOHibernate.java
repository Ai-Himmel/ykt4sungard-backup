package org.king.template.dao.hibernate;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.hibernate.BaseDAOHibernate;
import org.king.template.dao.MonitorServiceTemplateDAO;
import org.king.template.domain.MonitorServiceTemplate;
import org.king.utils.PaginationUtil;

import java.io.Serializable;
import java.util.List;

/**
 * Data access object (DAO) for domain model class MonitorServiceTemplate.
 *
 * @author MyEclipse - Hibernate Tools
 * @see org.king.template.dao.hibernate.MonitorServiceTemplate
 */
public class MonitorServiceTemplateDAOHibernate implements MonitorServiceTemplateDAO {

    private static final Log log = LogFactory.getLog(MonitorServiceTemplateDAOHibernate.class);


    private BaseDAO baseDAO;

    public void setBaseDAO(BaseDAO baseDAO) {
        this.baseDAO = baseDAO;
    }

    public List find(MyQuery myQuery) {
        log.debug("finding MonitorServiceTemplate instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }

    public List find(String query) {
        log.debug("finding MonitorServiceTemplate instance by query");
        return baseDAO.findEntity(query);
    }

    public MonitorServiceTemplate get(Serializable id) {
        log.debug("getting MonitorServiceTemplate instance by id");
        return (MonitorServiceTemplate) baseDAO.getEntity(MonitorServiceTemplate.class, id);
    }

    public List getAll() {
        log.debug("getting MonitorServiceTemplate all");
        String allHql = "from MonitorServiceTemplate";
        return baseDAO.findEntity(allHql);
    }

    public void save(MonitorServiceTemplate transientInstance) {
        log.debug("saving MonitorServiceTemplate instance");
        baseDAO.saveEntity(transientInstance);
    }

    public void update(MonitorServiceTemplate transientInstance) {
        log.debug("updating MonitorServiceTemplate instance");
        baseDAO.updateEntity(transientInstance);
    }


    public void delete(MonitorServiceTemplate persistentInstance) {
        log.debug("deleting MonitorServiceTemplate instance");
        baseDAO.removeEntity(persistentInstance);
    }

    public void findMonitorServiceTemplateByPage(DBPaginatedList page, MyQuery myQuery) {
        PaginationUtil.executeHibernatePage(page, (BaseDAOHibernate) baseDAO, myQuery);
    }

    /**
     * 根据模板名字判断该模板是否已存在
     *
     * @param templateName
     * @return
     */
    public boolean isExistMonitorServiceTemplate(String templateName) {
        StringBuffer hql = new StringBuffer("from MonitorServiceTemplate t where t.templateName='");
        hql.append(templateName);
        hql.append("'");

        List result = baseDAO.findEntity(hql.toString());
        if (result != null && result.size() > 0) {
            return true;
        }
        return false;
    }
}