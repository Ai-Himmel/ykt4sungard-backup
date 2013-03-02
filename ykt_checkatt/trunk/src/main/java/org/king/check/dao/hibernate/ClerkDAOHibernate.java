package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.king.check.dao.ClerkDAO;
import org.king.check.domain.Tclerkinfo;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.util.MyUtils;

/**
 * Data access object (DAO) for domain model class Clerk.
 * 
 * @see org.king.check.dao.hibernate.Clerk
 * @author MyEclipse - Hibernate Tools
 */
public class ClerkDAOHibernate implements ClerkDAO {

	//private static final Log log = LogFactory.getLog(ClerkDAOHibernate.class);

	protected void initDao() {
		// do nothing
	}

	private BaseDAO baseDAO;

	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	public List find(MyQuery myQuery) {
		return baseDAO.findEntity(myQuery);
	}

	public List find(String query) {
		return baseDAO.findEntity(query);
	}

	public Tclerkinfo get(Serializable id) {
		return (Tclerkinfo) baseDAO.getEntity(Tclerkinfo.class, id);
	}

	public List getAll() {
		String allHql = "from Tclerkinfo";
		return baseDAO.findEntity(allHql);
	}

	public void save(Tclerkinfo transientInstance) {
		baseDAO.saveEntity(transientInstance);
	}

	public void update(Tclerkinfo transientInstance) {
		baseDAO.updateEntity(transientInstance);
	}

	public void delete(Tclerkinfo persistentInstance) {
		baseDAO.removeEntity(persistentInstance);
	}

	public boolean isExist(Integer clerkId) {
		boolean flage = false;
		if (MyUtils.isBlank(clerkId)) {
			return flage;
		}
		List ret = baseDAO
				.findEntity("select a.custId from Tclerkinfo a where a.custId="
						+ clerkId);
		flage = ret.size() > 0 ? true : false;
		return flage;
	}

}