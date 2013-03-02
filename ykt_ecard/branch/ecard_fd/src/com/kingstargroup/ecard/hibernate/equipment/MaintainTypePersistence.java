package com.kingstargroup.ecard.hibernate.equipment;

import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.ecard.common.BasicPersistence;
import com.kingstargroup.ecard.exceptions.DBSystemException;

public class MaintainTypePersistence extends BasicPersistence {

	public  void  addMaintainType(MaintainType maintainType)throws DBSystemException {
		Session s = getSession();
		try{
			s.saveOrUpdate(maintainType);
		}catch (HibernateException ex) {			
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	public  List  getMaintainTypeByMaintainId(Integer  maintainId)throws DBSystemException {
		Session s = getSession();
		try{
			StringBuffer Hql = new StringBuffer(" from MaintainType m where m.maintainId.id="+maintainId);
			Query query = s.createQuery(Hql.toString());
			return query.list();
		}catch (HibernateException ex) {			
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	public void deleteMaintainTypeByMaintain(MaintainType maintainType) throws DBSystemException {
		try{
		    delete(maintainType);
		}catch (HibernateException ex) {			
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		}
	}
	private static final Log _log = LogFactory.getLog(MaintainTypePersistence.class);

}
