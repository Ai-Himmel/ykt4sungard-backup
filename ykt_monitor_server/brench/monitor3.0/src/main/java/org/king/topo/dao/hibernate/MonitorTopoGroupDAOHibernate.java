package org.king.topo.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.topo.dao.MonitorTopoGroupDAO;
import org.king.topo.domain.MonitorTopoGroup;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * A data access object (DAO) providing persistence and search support for
 * MonitorTopoGroup entities. Transaction control of the save(), update() and
 * delete() operations can directly support Spring container-managed
 * transactions or they can be augmented to handle user-managed Spring
 * transactions. Each of these methods provides additional information for how
 * to configure it for the desired type of transaction control.
 * 
 * @see org.king.topo.domain.MonitorTopoGroup
 * @author MyEclipse Persistence Tools
 */

public class MonitorTopoGroupDAOHibernate implements MonitorTopoGroupDAO {
	private static final Logger log = LoggerFactory
			.getLogger(MonitorTopoGroupDAOHibernate.class);

	private BaseDAO baseDAO;

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorTopoGroupDAO#setBaseDAO(org.king.framework
	 * .dao.BaseDAO)
	 */
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorTopoGroupDAO#find(org.king.framework
	 * .dao.MyQuery)
	 */
	public List find(MyQuery myQuery) {
		log.debug("finding MonitorTopoGroup instance by myQuery");
		return baseDAO.findEntity(myQuery);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorTopoGroupDAO#find(java.lang.String)
	 */
	public List find(String query) {
		log.debug("finding MonitorTopoGroup instance by query");
		return baseDAO.findEntity(query);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorTopoGroupDAO#get(java.io.Serializable)
	 */
	public MonitorTopoGroup get(Serializable id) {
		log.debug("getting MonitorTopoGroup instance by id");
		return (MonitorTopoGroup) baseDAO.getEntity(MonitorTopoGroup.class, id);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.topo.dao.hibernate.MonitorTopoGroupDAO#getAll()
	 */
	public List getAll() {
		log.debug("getting MonitorTopoGroup all");
		String allHql = "from MonitorTopoGroup";
		return baseDAO.findEntity(allHql);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorTopoGroupDAO#save(org.king.topo.domain
	 * .MonitorTopoGroup)
	 */
	public void save(MonitorTopoGroup transientInstance) {
		log.debug("saving MonitorTopoGroup instance");
		baseDAO.saveEntity(transientInstance);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorTopoGroupDAO#update(org.king.topo.
	 * domain.MonitorTopoGroup)
	 */
	public void update(MonitorTopoGroup transientInstance) {
		log.debug("updating MonitorTopoGroup instance");
		baseDAO.updateEntity(transientInstance);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorTopoGroupDAO#delete(org.king.topo.
	 * domain.MonitorTopoGroup)
	 */
	public void delete(MonitorTopoGroup persistentInstance) {
		log.debug("deleting MonitorTopoGroup instance");
		baseDAO.removeEntity(persistentInstance);
	}

	public List getAllTopoGroupWithLocationOrder() {
		log.debug("getting MonitorTopoGroup all");
		String allHql = "from MonitorTopoGroup order by location.locationid,groupyindex,groupxindex,devicegroupid ";
		return baseDAO.findEntity(allHql);
	}

	public int getXWidthbyLocationAndYindex(Integer location, Integer yindex) {
		String hql = "select sum(b.groupwidth) from MonitorTopoGroup a,MonitorTopoGroupInfo b where a.devicegroupid=b.devicegroupid and a.location.locationid="+location+" and a.groupyindex="+yindex;
		List list = baseDAO.findEntity(hql);
		if(list!=null&&list.size()>0){
			return Integer.parseInt(list.get(0).toString());			
		}
		return 0;
	}

	public int getYHeightbyLocation(Integer location) {
		int ret =0;
		for(int i=location-2;i>0;i-=2){
			String hql = "select sum(max(b.groupheight)) from MonitorTopoGroup a,MonitorTopoGroupInfo b where a.devicegroupid=b.devicegroupid and a.location.locationid="+i+" and a.groupyindex in (select distinct c.groupyindex from MonitorTopoGroup c where c.location.locationid="+i+") group by a.groupyindex";
			List list = baseDAO.findEntity(hql);
			if(list!=null&&list.size()>0){
				ret += Integer.parseInt(list.get(0).toString());			
			}
		}
		return ret;
	}
}