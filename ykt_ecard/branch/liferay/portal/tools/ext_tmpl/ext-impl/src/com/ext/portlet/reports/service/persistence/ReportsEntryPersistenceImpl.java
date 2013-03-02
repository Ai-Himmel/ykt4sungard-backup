package com.ext.portlet.reports.service.persistence;

import com.ext.portlet.reports.NoSuchEntryException;
import com.ext.portlet.reports.model.ReportsEntry;
import com.ext.portlet.reports.model.impl.ReportsEntryImpl;
import com.ext.portlet.reports.model.impl.ReportsEntryModelImpl;

import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.dao.DynamicQuery;
import com.liferay.portal.kernel.dao.DynamicQueryInitializer;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.ModelListener;
import com.liferay.portal.service.persistence.BasePersistence;
import com.liferay.portal.spring.hibernate.FinderCache;
import com.liferay.portal.spring.hibernate.HibernateUtil;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.dao.hibernate.QueryUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.Query;
import org.hibernate.Session;

import java.util.Collections;
import java.util.Iterator;
import java.util.List;


public class ReportsEntryPersistenceImpl extends BasePersistence
    implements ReportsEntryPersistence {
    private static final String _LISTENER = GetterUtil.getString(PropsUtil.get(
                "value.object.listener.com.ext.portlet.reports.model.ReportsEntry"));
    private static Log _log = LogFactory.getLog(ReportsEntryPersistenceImpl.class);

    public ReportsEntry create(String entryId) {
        ReportsEntry reportsEntry = new ReportsEntryImpl();

        reportsEntry.setNew(true);
        reportsEntry.setPrimaryKey(entryId);

        return reportsEntry;
    }

    public ReportsEntry remove(String entryId)
        throws NoSuchEntryException, SystemException {
        Session session = null;

        try {
            session = openSession();

            ReportsEntry reportsEntry = (ReportsEntry) session.get(ReportsEntryImpl.class,
                    entryId);

            if (reportsEntry == null) {
                if (_log.isWarnEnabled()) {
                    _log.warn("No ReportsEntry exists with the primary key " +
                        entryId);
                }

                throw new NoSuchEntryException(
                    "No ReportsEntry exists with the primary key " + entryId);
            }

            return remove(reportsEntry);
        } catch (NoSuchEntryException nsee) {
            throw nsee;
        } catch (Exception e) {
            throw HibernateUtil.processException(e);
        } finally {
            closeSession(session);
        }
    }

    public ReportsEntry remove(ReportsEntry reportsEntry)
        throws SystemException {
        ModelListener listener = _getListener();

        if (listener != null) {
            listener.onBeforeRemove(reportsEntry);
        }

        reportsEntry = removeImpl(reportsEntry);

        if (listener != null) {
            listener.onAfterRemove(reportsEntry);
        }

        return reportsEntry;
    }

    protected ReportsEntry removeImpl(ReportsEntry reportsEntry)
        throws SystemException {
        Session session = null;

        try {
            session = openSession();

            session.delete(reportsEntry);

            session.flush();

            return reportsEntry;
        } catch (Exception e) {
            throw HibernateUtil.processException(e);
        } finally {
            closeSession(session);

            FinderCache.clearCache(ReportsEntry.class.getName());
        }
    }

    public ReportsEntry update(ReportsEntry reportsEntry)
        throws SystemException {
        return update(reportsEntry, false);
    }

    public ReportsEntry update(ReportsEntry reportsEntry, boolean merge)
        throws SystemException {
        ModelListener listener = _getListener();

        boolean isNew = reportsEntry.isNew();

        if (listener != null) {
            if (isNew) {
                listener.onBeforeCreate(reportsEntry);
            } else {
                listener.onBeforeUpdate(reportsEntry);
            }
        }

        reportsEntry = updateImpl(reportsEntry, merge);

        if (listener != null) {
            if (isNew) {
                listener.onAfterCreate(reportsEntry);
            } else {
                listener.onAfterUpdate(reportsEntry);
            }
        }

        return reportsEntry;
    }

    public ReportsEntry updateImpl(
        com.ext.portlet.reports.model.ReportsEntry reportsEntry, boolean merge)
        throws SystemException {
        Session session = null;

        try {
            session = openSession();

            if (merge) {
                session.merge(reportsEntry);
            } else {
                if (reportsEntry.isNew()) {
                    session.save(reportsEntry);
                }
            }

            session.flush();

            reportsEntry.setNew(false);

            return reportsEntry;
        } catch (Exception e) {
            throw HibernateUtil.processException(e);
        } finally {
            closeSession(session);

            FinderCache.clearCache(ReportsEntry.class.getName());
        }
    }

    public ReportsEntry findByPrimaryKey(String entryId)
        throws NoSuchEntryException, SystemException {
        ReportsEntry reportsEntry = fetchByPrimaryKey(entryId);

        if (reportsEntry == null) {
            if (_log.isWarnEnabled()) {
                _log.warn("No ReportsEntry exists with the primary key " +
                    entryId);
            }

            throw new NoSuchEntryException(
                "No ReportsEntry exists with the primary key " + entryId);
        }

        return reportsEntry;
    }

    public ReportsEntry fetchByPrimaryKey(String entryId)
        throws SystemException {
        Session session = null;

        try {
            session = openSession();

            return (ReportsEntry) session.get(ReportsEntryImpl.class, entryId);
        } catch (Exception e) {
            throw HibernateUtil.processException(e);
        } finally {
            closeSession(session);
        }
    }

    public List findByCompanyId(String companyId) throws SystemException {
        boolean finderClassNameCacheEnabled = ReportsEntryModelImpl.CACHE_ENABLED;
        String finderClassName = ReportsEntry.class.getName();
        String finderMethodName = "findByCompanyId";
        String[] finderParams = new String[] { String.class.getName() };
        Object[] finderArgs = new Object[] { companyId };

        Object result = null;

        if (finderClassNameCacheEnabled) {
            result = FinderCache.getResult(finderClassName, finderMethodName,
                    finderParams, finderArgs, getSessionFactory());
        }

        if (result == null) {
            Session session = null;

            try {
                session = openSession();

                StringMaker query = new StringMaker();

                query.append(
                    "FROM com.ext.portlet.reports.model.ReportsEntry WHERE ");

                if (companyId == null) {
                    query.append("companyId IS NULL");
                } else {
                    query.append("companyId = ?");
                }

                query.append(" ");

                query.append("ORDER BY ");

                query.append("name ASC");

                Query q = session.createQuery(query.toString());

                int queryPos = 0;

                if (companyId != null) {
                    q.setString(queryPos++, companyId);
                }

                List list = q.list();

                FinderCache.putResult(finderClassNameCacheEnabled,
                    finderClassName, finderMethodName, finderParams,
                    finderArgs, list);

                return list;
            } catch (Exception e) {
                throw HibernateUtil.processException(e);
            } finally {
                closeSession(session);
            }
        } else {
            return (List) result;
        }
    }

    public List findByCompanyId(String companyId, int begin, int end)
        throws SystemException {
        return findByCompanyId(companyId, begin, end, null);
    }

    public List findByCompanyId(String companyId, int begin, int end,
        OrderByComparator obc) throws SystemException {
        boolean finderClassNameCacheEnabled = ReportsEntryModelImpl.CACHE_ENABLED;
        String finderClassName = ReportsEntry.class.getName();
        String finderMethodName = "findByCompanyId";
        String[] finderParams = new String[] {
                String.class.getName(),
                
                "java.lang.Integer", "java.lang.Integer",
                "com.liferay.portal.kernel.util.OrderByComparator"
            };
        Object[] finderArgs = new Object[] {
                companyId,
                
                String.valueOf(begin), String.valueOf(end), String.valueOf(obc)
            };

        Object result = null;

        if (finderClassNameCacheEnabled) {
            result = FinderCache.getResult(finderClassName, finderMethodName,
                    finderParams, finderArgs, getSessionFactory());
        }

        if (result == null) {
            Session session = null;

            try {
                session = openSession();

                StringMaker query = new StringMaker();

                query.append(
                    "FROM com.ext.portlet.reports.model.ReportsEntry WHERE ");

                if (companyId == null) {
                    query.append("companyId IS NULL");
                } else {
                    query.append("companyId = ?");
                }

                query.append(" ");

                if (obc != null) {
                    query.append("ORDER BY ");
                    query.append(obc.getOrderBy());
                }
                else {
                    query.append("ORDER BY ");

                    query.append("name ASC");
                }

                Query q = session.createQuery(query.toString());

                int queryPos = 0;

                if (companyId != null) {
                    q.setString(queryPos++, companyId);
                }

                List list = QueryUtil.list(q, getDialect(), begin, end);

                FinderCache.putResult(finderClassNameCacheEnabled,
                    finderClassName, finderMethodName, finderParams,
                    finderArgs, list);

                return list;
            } catch (Exception e) {
                throw HibernateUtil.processException(e);
            } finally {
                closeSession(session);
            }
        } else {
            return (List) result;
        }
    }

    public ReportsEntry findByCompanyId_First(String companyId,
        OrderByComparator obc) throws NoSuchEntryException, SystemException {
        List list = findByCompanyId(companyId, 0, 1, obc);

        if (list.size() == 0) {
            StringMaker msg = new StringMaker();

            msg.append("No ReportsEntry exists with the key {");

            msg.append("companyId=" + companyId);

            msg.append(StringPool.CLOSE_CURLY_BRACE);

            throw new NoSuchEntryException(msg.toString());
        } else {
            return (ReportsEntry) list.get(0);
        }
    }

    public ReportsEntry findByCompanyId_Last(String companyId,
        OrderByComparator obc) throws NoSuchEntryException, SystemException {
        int count = countByCompanyId(companyId);

        List list = findByCompanyId(companyId, count - 1, count, obc);

        if (list.size() == 0) {
            StringMaker msg = new StringMaker();

            msg.append("No ReportsEntry exists with the key {");

            msg.append("companyId=" + companyId);

            msg.append(StringPool.CLOSE_CURLY_BRACE);

            throw new NoSuchEntryException(msg.toString());
        } else {
            return (ReportsEntry) list.get(0);
        }
    }

    public ReportsEntry[] findByCompanyId_PrevAndNext(String entryId,
        String companyId, OrderByComparator obc)
        throws NoSuchEntryException, SystemException {
        ReportsEntry reportsEntry = findByPrimaryKey(entryId);

        int count = countByCompanyId(companyId);

        Session session = null;

        try {
            session = openSession();

            StringMaker query = new StringMaker();

            query.append(
                "FROM com.ext.portlet.reports.model.ReportsEntry WHERE ");

            if (companyId == null) {
                query.append("companyId IS NULL");
            } else {
                query.append("companyId = ?");
            }

            query.append(" ");

            if (obc != null) {
                query.append("ORDER BY ");
                query.append(obc.getOrderBy());
            }
            else {
                query.append("ORDER BY ");

                query.append("name ASC");
            }

            Query q = session.createQuery(query.toString());

            int queryPos = 0;

            if (companyId != null) {
                q.setString(queryPos++, companyId);
            }

            Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
                    reportsEntry);

            ReportsEntry[] array = new ReportsEntryImpl[3];

            array[0] = (ReportsEntry) objArray[0];
            array[1] = (ReportsEntry) objArray[1];
            array[2] = (ReportsEntry) objArray[2];

            return array;
        } catch (Exception e) {
            throw HibernateUtil.processException(e);
        } finally {
            closeSession(session);
        }
    }

    public List findByUserId(String userId) throws SystemException {
        boolean finderClassNameCacheEnabled = ReportsEntryModelImpl.CACHE_ENABLED;
        String finderClassName = ReportsEntry.class.getName();
        String finderMethodName = "findByUserId";
        String[] finderParams = new String[] { String.class.getName() };
        Object[] finderArgs = new Object[] { userId };

        Object result = null;

        if (finderClassNameCacheEnabled) {
            result = FinderCache.getResult(finderClassName, finderMethodName,
                    finderParams, finderArgs, getSessionFactory());
        }

        if (result == null) {
            Session session = null;

            try {
                session = openSession();

                StringMaker query = new StringMaker();

                query.append(
                    "FROM com.ext.portlet.reports.model.ReportsEntry WHERE ");

                if (userId == null) {
                    query.append("userId IS NULL");
                } else {
                    query.append("userId = ?");
                }

                query.append(" ");

                query.append("ORDER BY ");

                query.append("name ASC");

                Query q = session.createQuery(query.toString());

                int queryPos = 0;

                if (userId != null) {
                    q.setString(queryPos++, userId);
                }

                List list = q.list();

                FinderCache.putResult(finderClassNameCacheEnabled,
                    finderClassName, finderMethodName, finderParams,
                    finderArgs, list);

                return list;
            } catch (Exception e) {
                throw HibernateUtil.processException(e);
            } finally {
                closeSession(session);
            }
        } else {
            return (List) result;
        }
    }

    public List findByUserId(String userId, int begin, int end)
        throws SystemException {
        return findByUserId(userId, begin, end, null);
    }

    public List findByUserId(String userId, int begin, int end,
        OrderByComparator obc) throws SystemException {
        boolean finderClassNameCacheEnabled = ReportsEntryModelImpl.CACHE_ENABLED;
        String finderClassName = ReportsEntry.class.getName();
        String finderMethodName = "findByUserId";
        String[] finderParams = new String[] {
                String.class.getName(),
                
                "java.lang.Integer", "java.lang.Integer",
                "com.liferay.portal.kernel.util.OrderByComparator"
            };
        Object[] finderArgs = new Object[] {
                userId,
                
                String.valueOf(begin), String.valueOf(end), String.valueOf(obc)
            };

        Object result = null;

        if (finderClassNameCacheEnabled) {
            result = FinderCache.getResult(finderClassName, finderMethodName,
                    finderParams, finderArgs, getSessionFactory());
        }

        if (result == null) {
            Session session = null;

            try {
                session = openSession();

                StringMaker query = new StringMaker();

                query.append(
                    "FROM com.ext.portlet.reports.model.ReportsEntry WHERE ");

                if (userId == null) {
                    query.append("userId IS NULL");
                } else {
                    query.append("userId = ?");
                }

                query.append(" ");

                if (obc != null) {
                    query.append("ORDER BY ");
                    query.append(obc.getOrderBy());
                }
                else {
                    query.append("ORDER BY ");

                    query.append("name ASC");
                }

                Query q = session.createQuery(query.toString());

                int queryPos = 0;

                if (userId != null) {
                    q.setString(queryPos++, userId);
                }

                List list = QueryUtil.list(q, getDialect(), begin, end);

                FinderCache.putResult(finderClassNameCacheEnabled,
                    finderClassName, finderMethodName, finderParams,
                    finderArgs, list);

                return list;
            } catch (Exception e) {
                throw HibernateUtil.processException(e);
            } finally {
                closeSession(session);
            }
        } else {
            return (List) result;
        }
    }

    public ReportsEntry findByUserId_First(String userId, OrderByComparator obc)
        throws NoSuchEntryException, SystemException {
        List list = findByUserId(userId, 0, 1, obc);

        if (list.size() == 0) {
            StringMaker msg = new StringMaker();

            msg.append("No ReportsEntry exists with the key {");

            msg.append("userId=" + userId);

            msg.append(StringPool.CLOSE_CURLY_BRACE);

            throw new NoSuchEntryException(msg.toString());
        } else {
            return (ReportsEntry) list.get(0);
        }
    }

    public ReportsEntry findByUserId_Last(String userId, OrderByComparator obc)
        throws NoSuchEntryException, SystemException {
        int count = countByUserId(userId);

        List list = findByUserId(userId, count - 1, count, obc);

        if (list.size() == 0) {
            StringMaker msg = new StringMaker();

            msg.append("No ReportsEntry exists with the key {");

            msg.append("userId=" + userId);

            msg.append(StringPool.CLOSE_CURLY_BRACE);

            throw new NoSuchEntryException(msg.toString());
        } else {
            return (ReportsEntry) list.get(0);
        }
    }

    public ReportsEntry[] findByUserId_PrevAndNext(String entryId,
        String userId, OrderByComparator obc)
        throws NoSuchEntryException, SystemException {
        ReportsEntry reportsEntry = findByPrimaryKey(entryId);

        int count = countByUserId(userId);

        Session session = null;

        try {
            session = openSession();

            StringMaker query = new StringMaker();

            query.append(
                "FROM com.ext.portlet.reports.model.ReportsEntry WHERE ");

            if (userId == null) {
                query.append("userId IS NULL");
            } else {
                query.append("userId = ?");
            }

            query.append(" ");

            if (obc != null) {
                query.append("ORDER BY ");
                query.append(obc.getOrderBy());
            }
            else {
                query.append("ORDER BY ");

                query.append("name ASC");
            }

            Query q = session.createQuery(query.toString());

            int queryPos = 0;

            if (userId != null) {
                q.setString(queryPos++, userId);
            }

            Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
                    reportsEntry);

            ReportsEntry[] array = new ReportsEntryImpl[3];

            array[0] = (ReportsEntry) objArray[0];
            array[1] = (ReportsEntry) objArray[1];
            array[2] = (ReportsEntry) objArray[2];

            return array;
        } catch (Exception e) {
            throw HibernateUtil.processException(e);
        } finally {
            closeSession(session);
        }
    }

    public List findWithDynamicQuery(DynamicQueryInitializer queryInitializer)
        throws SystemException {
        Session session = null;

        try {
            session = openSession();

            DynamicQuery query = queryInitializer.initialize(session);

            return query.list();
        } catch (Exception e) {
            throw HibernateUtil.processException(e);
        } finally {
            closeSession(session);
        }
    }

    public List findWithDynamicQuery(DynamicQueryInitializer queryInitializer,
        int begin, int end) throws SystemException {
        Session session = null;

        try {
            session = openSession();

            DynamicQuery query = queryInitializer.initialize(session);

            query.setLimit(begin, end);

            return query.list();
        } catch (Exception e) {
            throw HibernateUtil.processException(e);
        } finally {
            closeSession(session);
        }
    }

    public List findAll() throws SystemException {
        return findAll(QueryUtil.ALL_POS, QueryUtil.ALL_POS, null);
    }

    public List findAll(int begin, int end) throws SystemException {
        return findAll(begin, end, null);
    }

    public List findAll(int begin, int end, OrderByComparator obc)
        throws SystemException {
        boolean finderClassNameCacheEnabled = ReportsEntryModelImpl.CACHE_ENABLED;
        String finderClassName = ReportsEntry.class.getName();
        String finderMethodName = "findAll";
        String[] finderParams = new String[] {
                "java.lang.Integer", "java.lang.Integer",
                "com.liferay.portal.kernel.util.OrderByComparator"
            };
        Object[] finderArgs = new Object[] {
                String.valueOf(begin), String.valueOf(end), String.valueOf(obc)
            };

        Object result = null;

        if (finderClassNameCacheEnabled) {
            result = FinderCache.getResult(finderClassName, finderMethodName,
                    finderParams, finderArgs, getSessionFactory());
        }

        if (result == null) {
            Session session = null;

            try {
                session = openSession();

                StringMaker query = new StringMaker();

                query.append("FROM com.ext.portlet.reports.model.ReportsEntry ");

                if (obc != null) {
                    query.append("ORDER BY ");
                    query.append(obc.getOrderBy());
                }
                else {
                    query.append("ORDER BY ");

                    query.append("name ASC");
                }

                Query q = session.createQuery(query.toString());

                List list = QueryUtil.list(q, getDialect(), begin, end);

                if (obc == null) {
                    Collections.sort(list);
                }

                FinderCache.putResult(finderClassNameCacheEnabled,
                    finderClassName, finderMethodName, finderParams,
                    finderArgs, list);

                return list;
            } catch (Exception e) {
                throw HibernateUtil.processException(e);
            } finally {
                closeSession(session);
            }
        } else {
            return (List) result;
        }
    }

    public void removeByCompanyId(String companyId) throws SystemException {
        Iterator itr = findByCompanyId(companyId).iterator();

        while (itr.hasNext()) {
            ReportsEntry reportsEntry = (ReportsEntry) itr.next();

            remove(reportsEntry);
        }
    }

    public void removeByUserId(String userId) throws SystemException {
        Iterator itr = findByUserId(userId).iterator();

        while (itr.hasNext()) {
            ReportsEntry reportsEntry = (ReportsEntry) itr.next();

            remove(reportsEntry);
        }
    }

    public void removeAll() throws SystemException {
        Iterator itr = findAll().iterator();

        while (itr.hasNext()) {
            remove((ReportsEntry) itr.next());
        }
    }

    public int countByCompanyId(String companyId) throws SystemException {
        boolean finderClassNameCacheEnabled = ReportsEntryModelImpl.CACHE_ENABLED;
        String finderClassName = ReportsEntry.class.getName();
        String finderMethodName = "countByCompanyId";
        String[] finderParams = new String[] { String.class.getName() };
        Object[] finderArgs = new Object[] { companyId };

        Object result = null;

        if (finderClassNameCacheEnabled) {
            result = FinderCache.getResult(finderClassName, finderMethodName,
                    finderParams, finderArgs, getSessionFactory());
        }

        if (result == null) {
            Session session = null;

            try {
                session = openSession();

                StringMaker query = new StringMaker();

                query.append("SELECT COUNT(*) ");
                query.append(
                    "FROM com.ext.portlet.reports.model.ReportsEntry WHERE ");

                if (companyId == null) {
                    query.append("companyId IS NULL");
                } else {
                    query.append("companyId = ?");
                }

                query.append(" ");

                Query q = session.createQuery(query.toString());

                int queryPos = 0;

                if (companyId != null) {
                    q.setString(queryPos++, companyId);
                }

                Long count = null;

                Iterator itr = q.list().iterator();

                if (itr.hasNext()) {
                    count = (Long) itr.next();
                }

                if (count == null) {
                    count = new Long(0);
                }

                FinderCache.putResult(finderClassNameCacheEnabled,
                    finderClassName, finderMethodName, finderParams,
                    finderArgs, count);

                return count.intValue();
            } catch (Exception e) {
                throw HibernateUtil.processException(e);
            } finally {
                closeSession(session);
            }
        } else {
            return ((Long) result).intValue();
        }
    }

    public int countByUserId(String userId) throws SystemException {
        boolean finderClassNameCacheEnabled = ReportsEntryModelImpl.CACHE_ENABLED;
        String finderClassName = ReportsEntry.class.getName();
        String finderMethodName = "countByUserId";
        String[] finderParams = new String[] { String.class.getName() };
        Object[] finderArgs = new Object[] { userId };

        Object result = null;

        if (finderClassNameCacheEnabled) {
            result = FinderCache.getResult(finderClassName, finderMethodName,
                    finderParams, finderArgs, getSessionFactory());
        }

        if (result == null) {
            Session session = null;

            try {
                session = openSession();

                StringMaker query = new StringMaker();

                query.append("SELECT COUNT(*) ");
                query.append(
                    "FROM com.ext.portlet.reports.model.ReportsEntry WHERE ");

                if (userId == null) {
                    query.append("userId IS NULL");
                } else {
                    query.append("userId = ?");
                }

                query.append(" ");

                Query q = session.createQuery(query.toString());

                int queryPos = 0;

                if (userId != null) {
                    q.setString(queryPos++, userId);
                }

                Long count = null;

                Iterator itr = q.list().iterator();

                if (itr.hasNext()) {
                    count = (Long) itr.next();
                }

                if (count == null) {
                    count = new Long(0);
                }

                FinderCache.putResult(finderClassNameCacheEnabled,
                    finderClassName, finderMethodName, finderParams,
                    finderArgs, count);

                return count.intValue();
            } catch (Exception e) {
                throw HibernateUtil.processException(e);
            } finally {
                closeSession(session);
            }
        } else {
            return ((Long) result).intValue();
        }
    }

    public int countAll() throws SystemException {
        boolean finderClassNameCacheEnabled = ReportsEntryModelImpl.CACHE_ENABLED;
        String finderClassName = ReportsEntry.class.getName();
        String finderMethodName = "countAll";
        String[] finderParams = new String[] {  };
        Object[] finderArgs = new Object[] {  };

        Object result = null;

        if (finderClassNameCacheEnabled) {
            result = FinderCache.getResult(finderClassName, finderMethodName,
                    finderParams, finderArgs, getSessionFactory());
        }

        if (result == null) {
            Session session = null;

            try {
                session = openSession();

                Query q = session.createQuery(
                        "SELECT COUNT(*) FROM com.ext.portlet.reports.model.ReportsEntry");

                Long count = null;

                Iterator itr = q.list().iterator();

                if (itr.hasNext()) {
                    count = (Long) itr.next();
                }

                if (count == null) {
                    count = new Long(0);
                }

                FinderCache.putResult(finderClassNameCacheEnabled,
                    finderClassName, finderMethodName, finderParams,
                    finderArgs, count);

                return count.intValue();
            } catch (Exception e) {
                throw HibernateUtil.processException(e);
            } finally {
                closeSession(session);
            }
        } else {
            return ((Long) result).intValue();
        }
    }

    protected void initDao() {
    }

    private static ModelListener _getListener() {
        if (Validator.isNotNull(_LISTENER)) {
            try {
                return (ModelListener) Class.forName(_LISTENER).newInstance();
            } catch (Exception e) {
                _log.error(e);
            }
        }

        return null;
    }
}
