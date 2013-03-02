/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package com.liferay.portlet.project.service.persistence;

import com.liferay.portal.SystemException;
import com.liferay.portal.service.persistence.BasePersistence;
import com.liferay.portal.util.HibernateUtil;

import com.liferay.portlet.project.NoSuchTaskException;

import com.liferay.util.dao.hibernate.OrderByComparator;
import com.liferay.util.lang.FastStringBuffer;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.ScrollableResults;
import org.hibernate.Session;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

/**
 * <a href="ProjTaskPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ProjTaskPersistence extends BasePersistence {
	public com.liferay.portlet.project.model.ProjTask create(String taskId) {
		return new com.liferay.portlet.project.model.ProjTask(taskId);
	}

	public com.liferay.portlet.project.model.ProjTask remove(String taskId)
		throws NoSuchTaskException, SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjTaskHBM projTaskHBM = (ProjTaskHBM)session.get(ProjTaskHBM.class,
					taskId);

			if (projTaskHBM == null) {
				_log.warn("No ProjTask exists with the primary key of " +
					taskId.toString());
				throw new NoSuchTaskException(taskId.toString());
			}

			com.liferay.portlet.project.model.ProjTask projTask = ProjTaskHBMUtil.model(projTaskHBM);
			session.delete(projTaskHBM);
			session.flush();
			ProjTaskPool.remove(taskId);

			return projTask;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.project.model.ProjTask update(
		com.liferay.portlet.project.model.ProjTask projTask)
		throws SystemException {
		Session session = null;

		try {
			if (projTask.isNew() || projTask.isModified()) {
				session = openSession();

				if (projTask.isNew()) {
					ProjTaskHBM projTaskHBM = new ProjTaskHBM(projTask.getTaskId(),
							projTask.getCompanyId(), projTask.getUserId(),
							projTask.getUserName(), projTask.getCreateDate(),
							projTask.getModifiedDate(),
							projTask.getProjectId(), projTask.getName(),
							projTask.getDescription(), projTask.getComments(),
							projTask.getEstimatedDuration(),
							projTask.getEstimatedEndDate(),
							projTask.getActualDuration(),
							projTask.getActualEndDate(), projTask.getStatus());
					session.save(projTaskHBM);
					session.flush();
				}
				else {
					ProjTaskHBM projTaskHBM = (ProjTaskHBM)session.get(ProjTaskHBM.class,
							projTask.getPrimaryKey());

					if (projTaskHBM != null) {
						projTaskHBM.setCompanyId(projTask.getCompanyId());
						projTaskHBM.setUserId(projTask.getUserId());
						projTaskHBM.setUserName(projTask.getUserName());
						projTaskHBM.setCreateDate(projTask.getCreateDate());
						projTaskHBM.setModifiedDate(projTask.getModifiedDate());
						projTaskHBM.setProjectId(projTask.getProjectId());
						projTaskHBM.setName(projTask.getName());
						projTaskHBM.setDescription(projTask.getDescription());
						projTaskHBM.setComments(projTask.getComments());
						projTaskHBM.setEstimatedDuration(projTask.getEstimatedDuration());
						projTaskHBM.setEstimatedEndDate(projTask.getEstimatedEndDate());
						projTaskHBM.setActualDuration(projTask.getActualDuration());
						projTaskHBM.setActualEndDate(projTask.getActualEndDate());
						projTaskHBM.setStatus(projTask.getStatus());
						session.flush();
					}
					else {
						projTaskHBM = new ProjTaskHBM(projTask.getTaskId(),
								projTask.getCompanyId(), projTask.getUserId(),
								projTask.getUserName(),
								projTask.getCreateDate(),
								projTask.getModifiedDate(),
								projTask.getProjectId(), projTask.getName(),
								projTask.getDescription(),
								projTask.getComments(),
								projTask.getEstimatedDuration(),
								projTask.getEstimatedEndDate(),
								projTask.getActualDuration(),
								projTask.getActualEndDate(),
								projTask.getStatus());
						session.save(projTaskHBM);
						session.flush();
					}
				}

				projTask.setNew(false);
				projTask.setModified(false);
				projTask.protect();
				ProjTaskPool.put(projTask.getPrimaryKey(), projTask);
			}

			return projTask;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List getUsers(String pk) throws NoSuchTaskException, SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjTaskHBM projTaskHBM = (ProjTaskHBM)session.get(ProjTaskHBM.class,
					pk);

			if (projTaskHBM == null) {
				_log.warn("No ProjTask exists with the primary key of " +
					pk.toString());
				throw new NoSuchTaskException(pk.toString());
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT userHBM FROM ");
			query.append(com.liferay.portlet.project.service.persistence.ProjTaskHBM.class.getName());
			query.append(" projTaskHBM ");
			query.append("JOIN projTaskHBM.users AS userHBM ");
			query.append("WHERE projTaskHBM.taskId = ? ");
			query.append("ORDER BY ");
			query.append("userHBM.firstName ASC").append(", ");
			query.append("userHBM.middleName ASC").append(", ");
			query.append("userHBM.lastName ASC");

			Query q = session.createQuery(query.toString());
			q.setString(0, pk);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				com.liferay.portal.service.persistence.UserHBM userHBM = (com.liferay.portal.service.persistence.UserHBM)itr.next();
				list.add(com.liferay.portal.service.persistence.UserHBMUtil.model(
						userHBM));
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List getUsers(String pk, int begin, int end)
		throws NoSuchTaskException, SystemException {
		return getUsers(pk, begin, end, null);
	}

	public List getUsers(String pk, int begin, int end, OrderByComparator obc)
		throws NoSuchTaskException, SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjTaskHBM projTaskHBM = (ProjTaskHBM)session.get(ProjTaskHBM.class,
					pk);

			if (projTaskHBM == null) {
				_log.warn("No ProjTask exists with the primary key of " +
					pk.toString());
				throw new NoSuchTaskException(pk.toString());
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT userHBM FROM ");
			query.append(com.liferay.portlet.project.service.persistence.ProjTaskHBM.class.getName());
			query.append(" projTaskHBM ");
			query.append("JOIN projTaskHBM.users AS userHBM ");
			query.append("WHERE projTaskHBM.taskId = ? ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("userHBM.firstName ASC").append(", ");
				query.append("userHBM.middleName ASC").append(", ");
				query.append("userHBM.lastName ASC");
			}

			Query q = session.createQuery(query.toString());
			q.setString(0, pk);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					com.liferay.portal.service.persistence.UserHBM userHBM = (com.liferay.portal.service.persistence.UserHBM)itr.next();
					list.add(com.liferay.portal.service.persistence.UserHBMUtil.model(
							userHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						com.liferay.portal.service.persistence.UserHBM userHBM = (com.liferay.portal.service.persistence.UserHBM)sr.get(0);
						list.add(com.liferay.portal.service.persistence.UserHBMUtil.model(
								userHBM));

						if (!sr.next()) {
							break;
						}
					}
				}
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public int getUsersSize(String pk) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) FROM ");
			query.append(com.liferay.portlet.project.service.persistence.ProjTaskHBM.class.getName());
			query.append(" projTaskHBM ");
			query.append("JOIN projTaskHBM.users AS userHBM ");
			query.append("WHERE projTaskHBM.taskId = ? ");

			Query q = session.createQuery(query.toString());
			q.setString(0, pk);

			Iterator itr = q.iterate();

			if (itr.hasNext()) {
				Integer count = (Integer)itr.next();

				if (count != null) {
					return count.intValue();
				}
			}

			return 0;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void setUsers(String pk, String[] pks)
		throws NoSuchTaskException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjTaskHBM projTaskHBM = (ProjTaskHBM)session.get(ProjTaskHBM.class,
					pk);

			if (projTaskHBM == null) {
				_log.warn("No ProjTask exists with the primary key of " +
					pk.toString());
				throw new NoSuchTaskException(pk.toString());
			}

			Set usersSet = new HashSet();

			for (int i = 0; (pks != null) && (i < pks.length); i++) {
				com.liferay.portal.service.persistence.UserHBM userHBM = (com.liferay.portal.service.persistence.UserHBM)session.get(com.liferay.portal.service.persistence.UserHBM.class,
						pks[i]);

				if (userHBM == null) {
					_log.warn("No User exists with the primary key of " +
						pks[i].toString());
					throw new com.liferay.portal.NoSuchUserException(pks[i].toString());
				}

				usersSet.add(userHBM);
			}

			projTaskHBM.setUsers(usersSet);
			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void setUsers(String pk, List users)
		throws NoSuchTaskException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjTaskHBM projTaskHBM = (ProjTaskHBM)session.get(ProjTaskHBM.class,
					pk);

			if (projTaskHBM == null) {
				_log.warn("No ProjTask exists with the primary key of " +
					pk.toString());
				throw new NoSuchTaskException(pk.toString());
			}

			Set usersSet = new HashSet();
			Iterator itr = users.iterator();

			while (itr.hasNext()) {
				com.liferay.portal.model.User user = (com.liferay.portal.model.User)itr.next();
				com.liferay.portal.service.persistence.UserHBM userHBM = (com.liferay.portal.service.persistence.UserHBM)session.get(com.liferay.portal.service.persistence.UserHBM.class,
						user.getPrimaryKey());

				if (userHBM == null) {
					_log.warn("No User exists with the primary key of " +
						user.getPrimaryKey().toString());
					throw new com.liferay.portal.NoSuchUserException(user.getPrimaryKey()
																		 .toString());
				}

				usersSet.add(userHBM);
			}

			projTaskHBM.setUsers(usersSet);
			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean addUser(String pk, String userPK)
		throws NoSuchTaskException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjTaskHBM projTaskHBM = (ProjTaskHBM)session.get(ProjTaskHBM.class,
					pk);

			if (projTaskHBM == null) {
				_log.warn("No ProjTask exists with the primary key of " +
					pk.toString());
				throw new NoSuchTaskException(pk.toString());
			}

			com.liferay.portal.service.persistence.UserHBM userHBM = null;
			userHBM = (com.liferay.portal.service.persistence.UserHBM)session.get(com.liferay.portal.service.persistence.UserHBM.class,
					userPK);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					userPK.toString());
				throw new com.liferay.portal.NoSuchUserException(userPK.toString());
			}

			boolean value = projTaskHBM.getUsers().add(userHBM);
			session.flush();

			return value;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean addUser(String pk, com.liferay.portal.model.User user)
		throws NoSuchTaskException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjTaskHBM projTaskHBM = (ProjTaskHBM)session.get(ProjTaskHBM.class,
					pk);

			if (projTaskHBM == null) {
				_log.warn("No ProjTask exists with the primary key of " +
					pk.toString());
				throw new NoSuchTaskException(pk.toString());
			}

			com.liferay.portal.service.persistence.UserHBM userHBM = null;
			userHBM = (com.liferay.portal.service.persistence.UserHBM)session.get(com.liferay.portal.service.persistence.UserHBM.class,
					user.getPrimaryKey());

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					user.getPrimaryKey().toString());
				throw new com.liferay.portal.NoSuchUserException(user.getPrimaryKey()
																	 .toString());
			}

			boolean value = projTaskHBM.getUsers().add(userHBM);
			session.flush();

			return value;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean addUsers(String pk, String[] userPKs)
		throws NoSuchTaskException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjTaskHBM projTaskHBM = (ProjTaskHBM)session.get(ProjTaskHBM.class,
					pk);

			if (projTaskHBM == null) {
				_log.warn("No ProjTask exists with the primary key of " +
					pk.toString());
				throw new NoSuchTaskException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < userPKs.length; i++) {
				com.liferay.portal.service.persistence.UserHBM userHBM = null;
				userHBM = (com.liferay.portal.service.persistence.UserHBM)session.get(com.liferay.portal.service.persistence.UserHBM.class,
						userPKs[i]);

				if (userHBM == null) {
					_log.warn("No User exists with the primary key of " +
						userPKs[i].toString());
					throw new com.liferay.portal.NoSuchUserException(userPKs[i].toString());
				}

				if (projTaskHBM.getUsers().add(userHBM)) {
					value = true;
				}
			}

			session.flush();

			return value;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean addUsers(String pk, List users)
		throws NoSuchTaskException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjTaskHBM projTaskHBM = (ProjTaskHBM)session.get(ProjTaskHBM.class,
					pk);

			if (projTaskHBM == null) {
				_log.warn("No ProjTask exists with the primary key of " +
					pk.toString());
				throw new NoSuchTaskException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < users.size(); i++) {
				com.liferay.portal.model.User user = (com.liferay.portal.model.User)users.get(i);
				com.liferay.portal.service.persistence.UserHBM userHBM = (com.liferay.portal.service.persistence.UserHBM)session.get(com.liferay.portal.service.persistence.UserHBM.class,
						user.getPrimaryKey());

				if (userHBM == null) {
					_log.warn("No User exists with the primary key of " +
						user.getPrimaryKey().toString());
					throw new com.liferay.portal.NoSuchUserException(user.getPrimaryKey()
																		 .toString());
				}

				if (projTaskHBM.getUsers().add(userHBM)) {
					value = true;
				}
			}

			session.flush();

			return value;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void clearUsers(String pk)
		throws NoSuchTaskException, SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjTaskHBM projTaskHBM = (ProjTaskHBM)session.get(ProjTaskHBM.class,
					pk);

			if (projTaskHBM == null) {
				_log.warn("No ProjTask exists with the primary key of " +
					pk.toString());
				throw new NoSuchTaskException(pk.toString());
			}

			projTaskHBM.getUsers().clear();
			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean containsUser(String pk, String userPK)
		throws NoSuchTaskException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjTaskHBM projTaskHBM = (ProjTaskHBM)session.get(ProjTaskHBM.class,
					pk);

			if (projTaskHBM == null) {
				_log.warn("No ProjTask exists with the primary key of " +
					pk.toString());
				throw new NoSuchTaskException(pk.toString());
			}

			com.liferay.portal.service.persistence.UserHBM userHBM = null;
			userHBM = (com.liferay.portal.service.persistence.UserHBM)session.get(com.liferay.portal.service.persistence.UserHBM.class,
					userPK);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					userPK.toString());
				throw new com.liferay.portal.NoSuchUserException(userPK.toString());
			}

			Collection c = projTaskHBM.getUsers();

			return c.contains(userHBM);
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean containsUser(String pk, com.liferay.portal.model.User user)
		throws NoSuchTaskException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjTaskHBM projTaskHBM = (ProjTaskHBM)session.get(ProjTaskHBM.class,
					pk);

			if (projTaskHBM == null) {
				_log.warn("No ProjTask exists with the primary key of " +
					pk.toString());
				throw new NoSuchTaskException(pk.toString());
			}

			com.liferay.portal.service.persistence.UserHBM userHBM = null;
			userHBM = (com.liferay.portal.service.persistence.UserHBM)session.get(com.liferay.portal.service.persistence.UserHBM.class,
					user.getPrimaryKey());

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					user.getPrimaryKey().toString());
				throw new com.liferay.portal.NoSuchUserException(user.getPrimaryKey()
																	 .toString());
			}

			Collection c = projTaskHBM.getUsers();

			return c.contains(userHBM);
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean removeUser(String pk, String userPK)
		throws NoSuchTaskException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjTaskHBM projTaskHBM = (ProjTaskHBM)session.get(ProjTaskHBM.class,
					pk);

			if (projTaskHBM == null) {
				_log.warn("No ProjTask exists with the primary key of " +
					pk.toString());
				throw new NoSuchTaskException(pk.toString());
			}

			com.liferay.portal.service.persistence.UserHBM userHBM = null;
			userHBM = (com.liferay.portal.service.persistence.UserHBM)session.get(com.liferay.portal.service.persistence.UserHBM.class,
					userPK);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					userPK.toString());
				throw new com.liferay.portal.NoSuchUserException(userPK.toString());
			}

			boolean value = projTaskHBM.getUsers().remove(userHBM);
			session.flush();

			return value;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean removeUser(String pk, com.liferay.portal.model.User user)
		throws NoSuchTaskException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjTaskHBM projTaskHBM = (ProjTaskHBM)session.get(ProjTaskHBM.class,
					pk);

			if (projTaskHBM == null) {
				_log.warn("No ProjTask exists with the primary key of " +
					pk.toString());
				throw new NoSuchTaskException(pk.toString());
			}

			com.liferay.portal.service.persistence.UserHBM userHBM = null;
			userHBM = (com.liferay.portal.service.persistence.UserHBM)session.get(com.liferay.portal.service.persistence.UserHBM.class,
					user.getPrimaryKey());

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					user.getPrimaryKey().toString());
				throw new com.liferay.portal.NoSuchUserException(user.getPrimaryKey()
																	 .toString());
			}

			boolean value = projTaskHBM.getUsers().remove(userHBM);
			session.flush();

			return value;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean removeUsers(String pk, String[] userPKs)
		throws NoSuchTaskException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjTaskHBM projTaskHBM = (ProjTaskHBM)session.get(ProjTaskHBM.class,
					pk);

			if (projTaskHBM == null) {
				_log.warn("No ProjTask exists with the primary key of " +
					pk.toString());
				throw new NoSuchTaskException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < userPKs.length; i++) {
				com.liferay.portal.service.persistence.UserHBM userHBM = null;
				userHBM = (com.liferay.portal.service.persistence.UserHBM)session.get(com.liferay.portal.service.persistence.UserHBM.class,
						userPKs[i]);

				if (userHBM == null) {
					_log.warn("No User exists with the primary key of " +
						userPKs[i].toString());
					throw new com.liferay.portal.NoSuchUserException(userPKs[i].toString());
				}

				if (projTaskHBM.getUsers().remove(userHBM)) {
					value = true;
				}
			}

			session.flush();

			return value;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean removeUsers(String pk, List users)
		throws NoSuchTaskException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjTaskHBM projTaskHBM = (ProjTaskHBM)session.get(ProjTaskHBM.class,
					pk);

			if (projTaskHBM == null) {
				_log.warn("No ProjTask exists with the primary key of " +
					pk.toString());
				throw new NoSuchTaskException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < users.size(); i++) {
				com.liferay.portal.model.User user = (com.liferay.portal.model.User)users.get(i);
				com.liferay.portal.service.persistence.UserHBM userHBM = (com.liferay.portal.service.persistence.UserHBM)session.get(com.liferay.portal.service.persistence.UserHBM.class,
						user.getPrimaryKey());

				if (userHBM == null) {
					_log.warn("No User exists with the primary key of " +
						user.getPrimaryKey().toString());
					throw new com.liferay.portal.NoSuchUserException(user.getPrimaryKey()
																		 .toString());
				}

				if (projTaskHBM.getUsers().remove(userHBM)) {
					value = true;
				}
			}

			session.flush();

			return value;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.project.model.ProjTask findByPrimaryKey(
		String taskId) throws NoSuchTaskException, SystemException {
		com.liferay.portlet.project.model.ProjTask projTask = ProjTaskPool.get(taskId);
		Session session = null;

		try {
			if (projTask == null) {
				session = openSession();

				ProjTaskHBM projTaskHBM = (ProjTaskHBM)session.get(ProjTaskHBM.class,
						taskId);

				if (projTaskHBM == null) {
					_log.warn("No ProjTask exists with the primary key of " +
						taskId.toString());
					throw new NoSuchTaskException(taskId.toString());
				}

				projTask = ProjTaskHBMUtil.model(projTaskHBM);
			}

			return projTask;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByCompanyId(String companyId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTask IN CLASS com.liferay.portlet.project.service.persistence.ProjTaskHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("estimatedEndDate ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ProjTaskHBM projTaskHBM = (ProjTaskHBM)itr.next();
				list.add(ProjTaskHBMUtil.model(projTaskHBM));
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByCompanyId(String companyId, int begin, int end)
		throws SystemException {
		return findByCompanyId(companyId, begin, end, null);
	}

	public List findByCompanyId(String companyId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTask IN CLASS com.liferay.portlet.project.service.persistence.ProjTaskHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("estimatedEndDate ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					ProjTaskHBM projTaskHBM = (ProjTaskHBM)itr.next();
					list.add(ProjTaskHBMUtil.model(projTaskHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ProjTaskHBM projTaskHBM = (ProjTaskHBM)sr.get(0);
						list.add(ProjTaskHBMUtil.model(projTaskHBM));

						if (!sr.next()) {
							break;
						}
					}
				}
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.project.model.ProjTask findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchTaskException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchTaskException();
		}
		else {
			return (com.liferay.portlet.project.model.ProjTask)list.get(0);
		}
	}

	public com.liferay.portlet.project.model.ProjTask findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchTaskException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchTaskException();
		}
		else {
			return (com.liferay.portlet.project.model.ProjTask)list.get(0);
		}
	}

	public com.liferay.portlet.project.model.ProjTask[] findByCompanyId_PrevAndNext(
		String taskId, String companyId, OrderByComparator obc)
		throws NoSuchTaskException, SystemException {
		com.liferay.portlet.project.model.ProjTask projTask = findByPrimaryKey(taskId);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTask IN CLASS com.liferay.portlet.project.service.persistence.ProjTaskHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("estimatedEndDate ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portlet.project.model.ProjTask[] array = new com.liferay.portlet.project.model.ProjTask[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ProjTaskHBM projTaskHBM = (ProjTaskHBM)sr.get(0);

					if (projTaskHBM == null) {
						break;
					}

					com.liferay.portlet.project.model.ProjTask curProjTask = ProjTaskHBMUtil.model(projTaskHBM);
					int value = obc.compare(projTask, curProjTask);

					if (value == 0) {
						if (!projTask.equals(curProjTask)) {
							break;
						}

						array[1] = curProjTask;

						if (sr.previous()) {
							array[0] = ProjTaskHBMUtil.model((ProjTaskHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ProjTaskHBMUtil.model((ProjTaskHBM)sr.get(
										0));
						}

						break;
					}

					if (count == 1) {
						break;
					}

					count = (int)Math.ceil(count / 2.0);

					if (value < 0) {
						if (!sr.scroll(count * -1)) {
							break;
						}
					}
					else {
						if (!sr.scroll(count)) {
							break;
						}
					}
				}
			}

			return array;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByUserId(String userId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTask IN CLASS com.liferay.portlet.project.service.persistence.ProjTaskHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("estimatedEndDate ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ProjTaskHBM projTaskHBM = (ProjTaskHBM)itr.next();
				list.add(ProjTaskHBMUtil.model(projTaskHBM));
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByUserId(String userId, int begin, int end)
		throws SystemException {
		return findByUserId(userId, begin, end, null);
	}

	public List findByUserId(String userId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTask IN CLASS com.liferay.portlet.project.service.persistence.ProjTaskHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("estimatedEndDate ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					ProjTaskHBM projTaskHBM = (ProjTaskHBM)itr.next();
					list.add(ProjTaskHBMUtil.model(projTaskHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ProjTaskHBM projTaskHBM = (ProjTaskHBM)sr.get(0);
						list.add(ProjTaskHBMUtil.model(projTaskHBM));

						if (!sr.next()) {
							break;
						}
					}
				}
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.project.model.ProjTask findByUserId_First(
		String userId, OrderByComparator obc)
		throws NoSuchTaskException, SystemException {
		List list = findByUserId(userId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchTaskException();
		}
		else {
			return (com.liferay.portlet.project.model.ProjTask)list.get(0);
		}
	}

	public com.liferay.portlet.project.model.ProjTask findByUserId_Last(
		String userId, OrderByComparator obc)
		throws NoSuchTaskException, SystemException {
		int count = countByUserId(userId);
		List list = findByUserId(userId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchTaskException();
		}
		else {
			return (com.liferay.portlet.project.model.ProjTask)list.get(0);
		}
	}

	public com.liferay.portlet.project.model.ProjTask[] findByUserId_PrevAndNext(
		String taskId, String userId, OrderByComparator obc)
		throws NoSuchTaskException, SystemException {
		com.liferay.portlet.project.model.ProjTask projTask = findByPrimaryKey(taskId);
		int count = countByUserId(userId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTask IN CLASS com.liferay.portlet.project.service.persistence.ProjTaskHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("estimatedEndDate ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			com.liferay.portlet.project.model.ProjTask[] array = new com.liferay.portlet.project.model.ProjTask[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ProjTaskHBM projTaskHBM = (ProjTaskHBM)sr.get(0);

					if (projTaskHBM == null) {
						break;
					}

					com.liferay.portlet.project.model.ProjTask curProjTask = ProjTaskHBMUtil.model(projTaskHBM);
					int value = obc.compare(projTask, curProjTask);

					if (value == 0) {
						if (!projTask.equals(curProjTask)) {
							break;
						}

						array[1] = curProjTask;

						if (sr.previous()) {
							array[0] = ProjTaskHBMUtil.model((ProjTaskHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ProjTaskHBMUtil.model((ProjTaskHBM)sr.get(
										0));
						}

						break;
					}

					if (count == 1) {
						break;
					}

					count = (int)Math.ceil(count / 2.0);

					if (value < 0) {
						if (!sr.scroll(count * -1)) {
							break;
						}
					}
					else {
						if (!sr.scroll(count)) {
							break;
						}
					}
				}
			}

			return array;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByProjectId(String projectId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTask IN CLASS com.liferay.portlet.project.service.persistence.ProjTaskHBM WHERE ");
			query.append("projectId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("estimatedEndDate ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, projectId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ProjTaskHBM projTaskHBM = (ProjTaskHBM)itr.next();
				list.add(ProjTaskHBMUtil.model(projTaskHBM));
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByProjectId(String projectId, int begin, int end)
		throws SystemException {
		return findByProjectId(projectId, begin, end, null);
	}

	public List findByProjectId(String projectId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTask IN CLASS com.liferay.portlet.project.service.persistence.ProjTaskHBM WHERE ");
			query.append("projectId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("estimatedEndDate ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, projectId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					ProjTaskHBM projTaskHBM = (ProjTaskHBM)itr.next();
					list.add(ProjTaskHBMUtil.model(projTaskHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ProjTaskHBM projTaskHBM = (ProjTaskHBM)sr.get(0);
						list.add(ProjTaskHBMUtil.model(projTaskHBM));

						if (!sr.next()) {
							break;
						}
					}
				}
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.project.model.ProjTask findByProjectId_First(
		String projectId, OrderByComparator obc)
		throws NoSuchTaskException, SystemException {
		List list = findByProjectId(projectId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchTaskException();
		}
		else {
			return (com.liferay.portlet.project.model.ProjTask)list.get(0);
		}
	}

	public com.liferay.portlet.project.model.ProjTask findByProjectId_Last(
		String projectId, OrderByComparator obc)
		throws NoSuchTaskException, SystemException {
		int count = countByProjectId(projectId);
		List list = findByProjectId(projectId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchTaskException();
		}
		else {
			return (com.liferay.portlet.project.model.ProjTask)list.get(0);
		}
	}

	public com.liferay.portlet.project.model.ProjTask[] findByProjectId_PrevAndNext(
		String taskId, String projectId, OrderByComparator obc)
		throws NoSuchTaskException, SystemException {
		com.liferay.portlet.project.model.ProjTask projTask = findByPrimaryKey(taskId);
		int count = countByProjectId(projectId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTask IN CLASS com.liferay.portlet.project.service.persistence.ProjTaskHBM WHERE ");
			query.append("projectId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("estimatedEndDate ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, projectId);

			com.liferay.portlet.project.model.ProjTask[] array = new com.liferay.portlet.project.model.ProjTask[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ProjTaskHBM projTaskHBM = (ProjTaskHBM)sr.get(0);

					if (projTaskHBM == null) {
						break;
					}

					com.liferay.portlet.project.model.ProjTask curProjTask = ProjTaskHBMUtil.model(projTaskHBM);
					int value = obc.compare(projTask, curProjTask);

					if (value == 0) {
						if (!projTask.equals(curProjTask)) {
							break;
						}

						array[1] = curProjTask;

						if (sr.previous()) {
							array[0] = ProjTaskHBMUtil.model((ProjTaskHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ProjTaskHBMUtil.model((ProjTaskHBM)sr.get(
										0));
						}

						break;
					}

					if (count == 1) {
						break;
					}

					count = (int)Math.ceil(count / 2.0);

					if (value < 0) {
						if (!sr.scroll(count * -1)) {
							break;
						}
					}
					else {
						if (!sr.scroll(count)) {
							break;
						}
					}
				}
			}

			return array;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByC_S(String companyId, int status)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTask IN CLASS com.liferay.portlet.project.service.persistence.ProjTaskHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("status = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("estimatedEndDate ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setInteger(queryPos++, status);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ProjTaskHBM projTaskHBM = (ProjTaskHBM)itr.next();
				list.add(ProjTaskHBMUtil.model(projTaskHBM));
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByC_S(String companyId, int status, int begin, int end)
		throws SystemException {
		return findByC_S(companyId, status, begin, end, null);
	}

	public List findByC_S(String companyId, int status, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTask IN CLASS com.liferay.portlet.project.service.persistence.ProjTaskHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("status = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("estimatedEndDate ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setInteger(queryPos++, status);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					ProjTaskHBM projTaskHBM = (ProjTaskHBM)itr.next();
					list.add(ProjTaskHBMUtil.model(projTaskHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ProjTaskHBM projTaskHBM = (ProjTaskHBM)sr.get(0);
						list.add(ProjTaskHBMUtil.model(projTaskHBM));

						if (!sr.next()) {
							break;
						}
					}
				}
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.project.model.ProjTask findByC_S_First(
		String companyId, int status, OrderByComparator obc)
		throws NoSuchTaskException, SystemException {
		List list = findByC_S(companyId, status, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchTaskException();
		}
		else {
			return (com.liferay.portlet.project.model.ProjTask)list.get(0);
		}
	}

	public com.liferay.portlet.project.model.ProjTask findByC_S_Last(
		String companyId, int status, OrderByComparator obc)
		throws NoSuchTaskException, SystemException {
		int count = countByC_S(companyId, status);
		List list = findByC_S(companyId, status, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchTaskException();
		}
		else {
			return (com.liferay.portlet.project.model.ProjTask)list.get(0);
		}
	}

	public com.liferay.portlet.project.model.ProjTask[] findByC_S_PrevAndNext(
		String taskId, String companyId, int status, OrderByComparator obc)
		throws NoSuchTaskException, SystemException {
		com.liferay.portlet.project.model.ProjTask projTask = findByPrimaryKey(taskId);
		int count = countByC_S(companyId, status);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTask IN CLASS com.liferay.portlet.project.service.persistence.ProjTaskHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("status = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("estimatedEndDate ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setInteger(queryPos++, status);

			com.liferay.portlet.project.model.ProjTask[] array = new com.liferay.portlet.project.model.ProjTask[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ProjTaskHBM projTaskHBM = (ProjTaskHBM)sr.get(0);

					if (projTaskHBM == null) {
						break;
					}

					com.liferay.portlet.project.model.ProjTask curProjTask = ProjTaskHBMUtil.model(projTaskHBM);
					int value = obc.compare(projTask, curProjTask);

					if (value == 0) {
						if (!projTask.equals(curProjTask)) {
							break;
						}

						array[1] = curProjTask;

						if (sr.previous()) {
							array[0] = ProjTaskHBMUtil.model((ProjTaskHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ProjTaskHBMUtil.model((ProjTaskHBM)sr.get(
										0));
						}

						break;
					}

					if (count == 1) {
						break;
					}

					count = (int)Math.ceil(count / 2.0);

					if (value < 0) {
						if (!sr.scroll(count * -1)) {
							break;
						}
					}
					else {
						if (!sr.scroll(count)) {
							break;
						}
					}
				}
			}

			return array;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByU_S(String userId, int status) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTask IN CLASS com.liferay.portlet.project.service.persistence.ProjTaskHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("status = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("estimatedEndDate ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setInteger(queryPos++, status);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ProjTaskHBM projTaskHBM = (ProjTaskHBM)itr.next();
				list.add(ProjTaskHBMUtil.model(projTaskHBM));
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByU_S(String userId, int status, int begin, int end)
		throws SystemException {
		return findByU_S(userId, status, begin, end, null);
	}

	public List findByU_S(String userId, int status, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTask IN CLASS com.liferay.portlet.project.service.persistence.ProjTaskHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("status = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("estimatedEndDate ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setInteger(queryPos++, status);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					ProjTaskHBM projTaskHBM = (ProjTaskHBM)itr.next();
					list.add(ProjTaskHBMUtil.model(projTaskHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ProjTaskHBM projTaskHBM = (ProjTaskHBM)sr.get(0);
						list.add(ProjTaskHBMUtil.model(projTaskHBM));

						if (!sr.next()) {
							break;
						}
					}
				}
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.project.model.ProjTask findByU_S_First(
		String userId, int status, OrderByComparator obc)
		throws NoSuchTaskException, SystemException {
		List list = findByU_S(userId, status, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchTaskException();
		}
		else {
			return (com.liferay.portlet.project.model.ProjTask)list.get(0);
		}
	}

	public com.liferay.portlet.project.model.ProjTask findByU_S_Last(
		String userId, int status, OrderByComparator obc)
		throws NoSuchTaskException, SystemException {
		int count = countByU_S(userId, status);
		List list = findByU_S(userId, status, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchTaskException();
		}
		else {
			return (com.liferay.portlet.project.model.ProjTask)list.get(0);
		}
	}

	public com.liferay.portlet.project.model.ProjTask[] findByU_S_PrevAndNext(
		String taskId, String userId, int status, OrderByComparator obc)
		throws NoSuchTaskException, SystemException {
		com.liferay.portlet.project.model.ProjTask projTask = findByPrimaryKey(taskId);
		int count = countByU_S(userId, status);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTask IN CLASS com.liferay.portlet.project.service.persistence.ProjTaskHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("status = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("estimatedEndDate ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setInteger(queryPos++, status);

			com.liferay.portlet.project.model.ProjTask[] array = new com.liferay.portlet.project.model.ProjTask[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ProjTaskHBM projTaskHBM = (ProjTaskHBM)sr.get(0);

					if (projTaskHBM == null) {
						break;
					}

					com.liferay.portlet.project.model.ProjTask curProjTask = ProjTaskHBMUtil.model(projTaskHBM);
					int value = obc.compare(projTask, curProjTask);

					if (value == 0) {
						if (!projTask.equals(curProjTask)) {
							break;
						}

						array[1] = curProjTask;

						if (sr.previous()) {
							array[0] = ProjTaskHBMUtil.model((ProjTaskHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ProjTaskHBMUtil.model((ProjTaskHBM)sr.get(
										0));
						}

						break;
					}

					if (count == 1) {
						break;
					}

					count = (int)Math.ceil(count / 2.0);

					if (value < 0) {
						if (!sr.scroll(count * -1)) {
							break;
						}
					}
					else {
						if (!sr.scroll(count)) {
							break;
						}
					}
				}
			}

			return array;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findAll() throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTask IN CLASS com.liferay.portlet.project.service.persistence.ProjTaskHBM ");
			query.append("ORDER BY ");
			query.append("estimatedEndDate ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ProjTaskHBM projTaskHBM = (ProjTaskHBM)itr.next();
				list.add(ProjTaskHBMUtil.model(projTaskHBM));
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void removeByCompanyId(String companyId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTask IN CLASS com.liferay.portlet.project.service.persistence.ProjTaskHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("estimatedEndDate ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ProjTaskHBM projTaskHBM = (ProjTaskHBM)itr.next();
				ProjTaskPool.remove((String)projTaskHBM.getPrimaryKey());
				session.delete(projTaskHBM);
			}

			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void removeByUserId(String userId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTask IN CLASS com.liferay.portlet.project.service.persistence.ProjTaskHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("estimatedEndDate ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ProjTaskHBM projTaskHBM = (ProjTaskHBM)itr.next();
				ProjTaskPool.remove((String)projTaskHBM.getPrimaryKey());
				session.delete(projTaskHBM);
			}

			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void removeByProjectId(String projectId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTask IN CLASS com.liferay.portlet.project.service.persistence.ProjTaskHBM WHERE ");
			query.append("projectId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("estimatedEndDate ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, projectId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ProjTaskHBM projTaskHBM = (ProjTaskHBM)itr.next();
				ProjTaskPool.remove((String)projTaskHBM.getPrimaryKey());
				session.delete(projTaskHBM);
			}

			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void removeByC_S(String companyId, int status)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTask IN CLASS com.liferay.portlet.project.service.persistence.ProjTaskHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("status = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("estimatedEndDate ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setInteger(queryPos++, status);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ProjTaskHBM projTaskHBM = (ProjTaskHBM)itr.next();
				ProjTaskPool.remove((String)projTaskHBM.getPrimaryKey());
				session.delete(projTaskHBM);
			}

			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void removeByU_S(String userId, int status)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTask IN CLASS com.liferay.portlet.project.service.persistence.ProjTaskHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("status = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("estimatedEndDate ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setInteger(queryPos++, status);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ProjTaskHBM projTaskHBM = (ProjTaskHBM)itr.next();
				ProjTaskPool.remove((String)projTaskHBM.getPrimaryKey());
				session.delete(projTaskHBM);
			}

			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public int countByCompanyId(String companyId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM ProjTask IN CLASS com.liferay.portlet.project.service.persistence.ProjTaskHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			if (itr.hasNext()) {
				Integer count = (Integer)itr.next();

				if (count != null) {
					return count.intValue();
				}
			}

			return 0;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public int countByUserId(String userId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM ProjTask IN CLASS com.liferay.portlet.project.service.persistence.ProjTaskHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			if (itr.hasNext()) {
				Integer count = (Integer)itr.next();

				if (count != null) {
					return count.intValue();
				}
			}

			return 0;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public int countByProjectId(String projectId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM ProjTask IN CLASS com.liferay.portlet.project.service.persistence.ProjTaskHBM WHERE ");
			query.append("projectId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, projectId);

			Iterator itr = q.list().iterator();

			if (itr.hasNext()) {
				Integer count = (Integer)itr.next();

				if (count != null) {
					return count.intValue();
				}
			}

			return 0;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public int countByC_S(String companyId, int status)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM ProjTask IN CLASS com.liferay.portlet.project.service.persistence.ProjTaskHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("status = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setInteger(queryPos++, status);

			Iterator itr = q.list().iterator();

			if (itr.hasNext()) {
				Integer count = (Integer)itr.next();

				if (count != null) {
					return count.intValue();
				}
			}

			return 0;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public int countByU_S(String userId, int status) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM ProjTask IN CLASS com.liferay.portlet.project.service.persistence.ProjTaskHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("status = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setInteger(queryPos++, status);

			Iterator itr = q.list().iterator();

			if (itr.hasNext()) {
				Integer count = (Integer)itr.next();

				if (count != null) {
					return count.intValue();
				}
			}

			return 0;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	private static final Log _log = LogFactory.getLog(ProjTaskPersistence.class);
}