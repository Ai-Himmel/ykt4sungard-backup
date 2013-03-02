<#include "copyright.txt" parse="false">


package ${basePersistencePackage};

import ${springHibernatePackage}.HibernateUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.HibernateException;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.connection.ConnectionProvider;
import org.hibernate.dialect.Dialect;
import org.hibernate.engine.SessionFactoryImplementor;

import org.springframework.jdbc.core.support.JdbcDaoSupport;

/**
 * <a href="BasePersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class BasePersistence extends JdbcDaoSupport {

	public SessionFactory getSessionFactory() {
		return _sessionFactory;
	}

	public void setSessionFactory(SessionFactory sessionFactory) {
		_sessionFactory = (SessionFactoryImplementor)sessionFactory;
		_dialect = _sessionFactory.getDialect();

		if (_log.isDebugEnabled()) {
			ConnectionProvider provider =
				_sessionFactory.getConnectionProvider();

			_log.debug("Connection provider " + provider.getClass().getName());
			_log.debug("Dialect " + _dialect.getClass().getName());
		}
	}

	protected Dialect getDialect() {
		return _dialect;
	}

	public void closeSession(Session session) {
		HibernateUtil.closeSession(session);
	}

	protected Session openSession() throws HibernateException {
		return HibernateUtil.openSession(_sessionFactory);
	}

	protected Session openSession(SessionFactory sessionFactory)
		throws HibernateException {

		return HibernateUtil.openSession(sessionFactory);
	}

	private static Log _log = LogFactory.getLog(BasePersistence.class);

	private SessionFactoryImplementor _sessionFactory;
	private Dialect _dialect;

}