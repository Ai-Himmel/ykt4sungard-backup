package org.king.classmanage.domain;

import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.LockMode;
import org.hibernate.criterion.Example;
import org.springframework.context.ApplicationContext;
import org.springframework.orm.hibernate3.support.HibernateDaoSupport;

/**
 * Data access object (DAO) for domain model class Managermodel.
 * @see org.king.classmanage.domain.Managermodel
 * @author MyEclipse - Hibernate Tools
 */
public class ManagermodelDAO extends HibernateDaoSupport {

    private static final Log log = LogFactory.getLog(ManagermodelDAO.class);

	protected void initDao() {
		//do nothing
	}
    
    public void save(Managermodel transientInstance) {
        log.debug("saving Managermodel instance");
        try {
            getHibernateTemplate().saveOrUpdate(transientInstance);
            log.debug("save successful");
        } catch (RuntimeException re) {
            log.error("save failed", re);
            throw re;
        }
    }
    
	public void delete(Managermodel persistentInstance) {
        log.debug("deleting Managermodel instance");
        try {
            getHibernateTemplate().delete(persistentInstance);
            log.debug("delete successful");
        } catch (RuntimeException re) {
            log.error("delete failed", re);
            throw re;
        }
    }
    
    public Managermodel findById( java.lang.String id) {
        log.debug("getting Managermodel instance with id: " + id);
        try {
            Managermodel instance = (Managermodel) getHibernateTemplate()
                    .get("org.king.classmanage.domain.Managermodel", id);
            return instance;
        } catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
    
    
    public List findByExample(Managermodel instance) {
        log.debug("finding Managermodel instance by example");
        try {
            List results = getSession()
                    .createCriteria("org.king.classmanage.domain.Managermodel")
                    .add(Example.create(instance))
            .list();
            log.debug("find by example successful, result size: " + results.size());
            return results;
        } catch (RuntimeException re) {
            log.error("find by example failed", re);
            throw re;
        }
    }    
    
    public Managermodel merge(Managermodel detachedInstance) {
        log.debug("merging Managermodel instance");
        try {
            Managermodel result = (Managermodel) getHibernateTemplate()
                    .merge(detachedInstance);
            log.debug("merge successful");
            return result;
        } catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }

    public void attachDirty(Managermodel instance) {
        log.debug("attaching dirty Managermodel instance");
        try {
            getHibernateTemplate().saveOrUpdate(instance);
            log.debug("attach successful");
        } catch (RuntimeException re) {
            log.error("attach failed", re);
            throw re;
        }
    }
    
    public void attachClean(Managermodel instance) {
        log.debug("attaching clean Managermodel instance");
        try {
            getHibernateTemplate().lock(instance, LockMode.NONE);
            log.debug("attach successful");
        } catch (RuntimeException re) {
            log.error("attach failed", re);
            throw re;
        }
    }

	public static ManagermodelDAO getFromApplicationContext(ApplicationContext ctx) {
    	return (ManagermodelDAO) ctx.getBean("ManagermodelDAO");
	}
}