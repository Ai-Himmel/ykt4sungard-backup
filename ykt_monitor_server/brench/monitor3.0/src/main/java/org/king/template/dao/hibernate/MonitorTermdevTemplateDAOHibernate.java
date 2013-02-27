package org.king.template.dao.hibernate;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.hibernate.BaseDAOHibernate;
import org.king.template.dao.MonitorTermdevTemplateDAO;
import org.king.template.domain.MonitorTermdevTemplate;
import org.king.template.domain.MonitorTermdevTemplateAll;
import org.king.utils.PaginationUtil;

import java.io.Serializable;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-7
 */
public class MonitorTermdevTemplateDAOHibernate implements MonitorTermdevTemplateDAO {

    private static final Log log = LogFactory.getLog(MonitorTermdevTemplateDAOHibernate.class);

    private BaseDAO baseDAO;

    public void setBaseDAO(BaseDAO baseDAO) {
        this.baseDAO = baseDAO;
    }

    public List find(MyQuery myQuery) {
        log.debug("finding MonitorTermdevTemplate instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }

    public List find(String query) {
        log.debug("finding MonitorTermdevTemplate instance by query");
        return baseDAO.findEntity(query);
    }

    public MonitorTermdevTemplate get(Serializable id) {
        log.debug("getting MonitorTermdevTemplate instance by id");
        Object temp = null;
        try {
			temp = baseDAO.getEntity(MonitorTermdevTemplate.class, id);
		} catch (Exception e) {
			// TODO: handle exception
		}
		if(temp!=null){
			return (MonitorTermdevTemplate) temp;
		}
        return null;
    }

    public MonitorTermdevTemplate getEnableMonitorTermdevTemplate() {
        List list = baseDAO.findEntity("from MonitorTermdevTemplate a");
        if (list != null && list.size() > 0) {
            return (MonitorTermdevTemplate) list.get(0);
        } else {
            MonitorTermdevTemplate monitorTermdevTemplate = new MonitorTermdevTemplate();
            monitorTermdevTemplate.setTemplateName("default");
            monitorTermdevTemplate.setCheckCommand("");
            monitorTermdevTemplate.setCheckInterval(Double.valueOf(5));
            monitorTermdevTemplate.setMaxCheckAttempts(3);
            monitorTermdevTemplate.setRetryInterval(Double.valueOf(1));
            return monitorTermdevTemplate;
        }
    }

    public List getAll() {
        log.debug("getting MonitorTermdevTemplate all");
        String allHql = "from MonitorTermdevTemplate";
        return baseDAO.findEntity(allHql);
    }

    public void save(MonitorTermdevTemplate transientInstance) {
        log.debug("saving MonitorTermdevTemplate instance");
        baseDAO.saveEntity(transientInstance);
    }

    public void update(MonitorTermdevTemplate transientInstance) {
        log.debug("updating MonitorTermdevTemplate instance");
        baseDAO.updateEntity(transientInstance);
    }


    public void delete(MonitorTermdevTemplate persistentInstance) {
        log.debug("deleting MonitorTermdevTemplate instance");
        baseDAO.removeEntity(persistentInstance);
    }

    public void findMonitorTermdevTemplateByPage(DBPaginatedList page, MyQuery myQuery) {
        PaginationUtil.executeHibernatePage(page, (BaseDAOHibernate) baseDAO, myQuery);
    }

    /**
     * 根据模板名字判断该模板是否已存在
     *
     * @param templateName
     * @return
     */
    public boolean isExistMonitorTermdevTemplate(String templateName) {
        StringBuffer hql = new StringBuffer("from MonitorTermdevTemplate t where t.templateName='");
        hql.append(templateName);
        hql.append("'");

        List result = baseDAO.findEntity(hql.toString());
        if (result != null && result.size() > 0) {
            return true;
        }
        return false;
    }

	public MonitorTermdevTemplateAll getTermdevTemplateAll(Serializable id) {
		  log.debug("getting MonitorTermdevTemplateAll instance by id");
	        Object temp = null;
	        try {
				temp = baseDAO.getEntity(MonitorTermdevTemplateAll.class, id);
			} catch (Exception e) {
				// TODO: handle exception
			}
			if(temp!=null){
				return (MonitorTermdevTemplateAll) temp;
			}
	        return null;
	}

	public void updateTermdevTemplateAll(
			MonitorTermdevTemplateAll transientInstance) {
		  log.debug("updating MonitorTermdevTemplateall instance");
	      baseDAO.updateEntity(transientInstance);		
	}
}
