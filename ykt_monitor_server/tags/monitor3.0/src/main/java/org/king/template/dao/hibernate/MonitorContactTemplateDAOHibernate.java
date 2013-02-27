package org.king.template.dao.hibernate;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.hibernate.BaseDAOHibernate;
import org.king.template.dao.MonitorContactTemplateDAO;
import org.king.template.domain.MonitorContactTemplate;
import org.king.utils.PaginationUtil;

import java.io.Serializable;
import java.util.List;

/**
 * Data access object (DAO) for domain model class MonitorContactTemplate.
 *
 * @author MyEclipse - Hibernate Tools
 * @see org.king.template.dao.hibernate.MonitorContactTemplate
 */
public class MonitorContactTemplateDAOHibernate implements MonitorContactTemplateDAO {

    private static final Log log = LogFactory.getLog(MonitorContactTemplateDAOHibernate.class);

    private BaseDAO baseDAO;

    public void setBaseDAO(BaseDAO baseDAO) {
        this.baseDAO = baseDAO;
    }

    public List find(MyQuery myQuery) {
        log.debug("finding MonitorContactTemplate instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }

    public List find(String query) {
        log.debug("finding MonitorContactTemplate instance by query");
        return baseDAO.findEntity(query);
    }

    public MonitorContactTemplate get(Serializable id) {
        log.debug("getting MonitorContactTemplate instance by id");
        return (MonitorContactTemplate) baseDAO.getEntity(MonitorContactTemplate.class, id);
    }

    public List getAll() {
        log.debug("getting MonitorContactTemplate all");
        String allHql = "from MonitorContactTemplate";
        return baseDAO.findEntity(allHql);
    }

    public void save(MonitorContactTemplate transientInstance) {
        log.debug("saving MonitorContactTemplate instance");
        baseDAO.saveEntity(transientInstance);
    }

    public void update(MonitorContactTemplate transientInstance) {
        log.debug("updating MonitorContactTemplate instance");
        baseDAO.updateEntity(transientInstance);
    }


    public void delete(MonitorContactTemplate persistentInstance) {
        log.debug("deleting MonitorContactTemplate instance");
        baseDAO.removeEntity(persistentInstance);
    }

    public void findMonitorContactTemplateByPage(DBPaginatedList page, MyQuery myQuery) {
        PaginationUtil.executeHibernatePage(page, (BaseDAOHibernate) baseDAO, myQuery);
    }

    /**
     * 根据模板名字判断该模板是否已存在
     *
     * @param templateName
     * @return
     */
    public boolean isExistMonitorContactTemplate(String templateName) {
        StringBuffer hql = new StringBuffer("from MonitorContactTemplate t where t.templateName='");
        hql.append(templateName);
        hql.append("'");

        List result = baseDAO.findEntity(hql.toString());
        return result != null && result.size() > 0;
    }
}