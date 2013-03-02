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

import com.liferay.portlet.project.NoSuchProjectException;

import com.liferay.util.dao.hibernate.OrderByComparator;
import com.liferay.util.lang.FastStringBuffer;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.HibernateException;
import org.hibernate.ObjectNotFoundException;
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
 * <a href="ProjProjectPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ProjProjectPersistence extends BasePersistence {
	public com.liferay.portlet.project.model.ProjProject create(
		String projectId) {
		return new com.liferay.portlet.project.model.ProjProject(projectId);
	}

	public com.liferay.portlet.project.model.ProjProject remove(
		String projectId) throws NoSuchProjectException, SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjProjectHBM projProjectHBM = (ProjProjectHBM)session.get(ProjProjectHBM.class,
					projectId);

			if (projProjectHBM == null) {
				_log.warn("No ProjProject exists with the primary key of " +
					projectId.toString());
				throw new NoSuchProjectException(projectId.toString());
			}

			com.liferay.portlet.project.model.ProjProject projProject = ProjProjectHBMUtil.model(projProjectHBM);
			session.delete(projProjectHBM);
			session.flush();
			ProjProjectPool.remove(projectId);

			return projProject;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.project.model.ProjProject update(
		com.liferay.portlet.project.model.ProjProject projProject)
		throws SystemException {
		Session session = null;

		try {
			if (projProject.isNew() || projProject.isModified()) {
				session = openSession();

				if (projProject.isNew()) {
					ProjProjectHBM projProjectHBM = new ProjProjectHBM(projProject.getProjectId(),
							projProject.getCompanyId(),
							projProject.getUserId(), projProject.getUserName(),
							projProject.getCreateDate(),
							projProject.getModifiedDate(),
							projProject.getFirmId(), projProject.getCode(),
							projProject.getName(), projProject.getDescription());
					session.save(projProjectHBM);
					session.flush();
				}
				else {
					ProjProjectHBM projProjectHBM = (ProjProjectHBM)session.get(ProjProjectHBM.class,
							projProject.getPrimaryKey());

					if (projProjectHBM != null) {
						projProjectHBM.setCompanyId(projProject.getCompanyId());
						projProjectHBM.setUserId(projProject.getUserId());
						projProjectHBM.setUserName(projProject.getUserName());
						projProjectHBM.setCreateDate(projProject.getCreateDate());
						projProjectHBM.setModifiedDate(projProject.getModifiedDate());
						projProjectHBM.setFirmId(projProject.getFirmId());
						projProjectHBM.setCode(projProject.getCode());
						projProjectHBM.setName(projProject.getName());
						projProjectHBM.setDescription(projProject.getDescription());
						session.flush();
					}
					else {
						projProjectHBM = new ProjProjectHBM(projProject.getProjectId(),
								projProject.getCompanyId(),
								projProject.getUserId(),
								projProject.getUserName(),
								projProject.getCreateDate(),
								projProject.getModifiedDate(),
								projProject.getFirmId(), projProject.getCode(),
								projProject.getName(),
								projProject.getDescription());
						session.save(projProjectHBM);
						session.flush();
					}
				}

				projProject.setNew(false);
				projProject.setModified(false);
				projProject.protect();
				ProjProjectPool.put(projProject.getPrimaryKey(), projProject);
			}

			return projProject;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List getUsers(String pk)
		throws NoSuchProjectException, SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjProjectHBM projProjectHBM = (ProjProjectHBM)session.get(ProjProjectHBM.class,
					pk);

			if (projProjectHBM == null) {
				_log.warn("No ProjProject exists with the primary key of " +
					pk.toString());
				throw new NoSuchProjectException(pk.toString());
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT userHBM FROM ");
			query.append(com.liferay.portlet.project.service.persistence.ProjProjectHBM.class.getName());
			query.append(" projProjectHBM ");
			query.append("JOIN projProjectHBM.users AS userHBM ");
			query.append("WHERE projProjectHBM.projectId = ? ");
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
		throws NoSuchProjectException, SystemException {
		return getUsers(pk, begin, end, null);
	}

	public List getUsers(String pk, int begin, int end, OrderByComparator obc)
		throws NoSuchProjectException, SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjProjectHBM projProjectHBM = (ProjProjectHBM)session.get(ProjProjectHBM.class,
					pk);

			if (projProjectHBM == null) {
				_log.warn("No ProjProject exists with the primary key of " +
					pk.toString());
				throw new NoSuchProjectException(pk.toString());
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT userHBM FROM ");
			query.append(com.liferay.portlet.project.service.persistence.ProjProjectHBM.class.getName());
			query.append(" projProjectHBM ");
			query.append("JOIN projProjectHBM.users AS userHBM ");
			query.append("WHERE projProjectHBM.projectId = ? ");

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
			query.append(com.liferay.portlet.project.service.persistence.ProjProjectHBM.class.getName());
			query.append(" projProjectHBM ");
			query.append("JOIN projProjectHBM.users AS userHBM ");
			query.append("WHERE projProjectHBM.projectId = ? ");

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
		throws NoSuchProjectException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjProjectHBM projProjectHBM = (ProjProjectHBM)session.get(ProjProjectHBM.class,
					pk);

			if (projProjectHBM == null) {
				_log.warn("No ProjProject exists with the primary key of " +
					pk.toString());
				throw new NoSuchProjectException(pk.toString());
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

			projProjectHBM.setUsers(usersSet);
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
		throws NoSuchProjectException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjProjectHBM projProjectHBM = (ProjProjectHBM)session.get(ProjProjectHBM.class,
					pk);

			if (projProjectHBM == null) {
				_log.warn("No ProjProject exists with the primary key of " +
					pk.toString());
				throw new NoSuchProjectException(pk.toString());
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

			projProjectHBM.setUsers(usersSet);
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
		throws NoSuchProjectException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjProjectHBM projProjectHBM = (ProjProjectHBM)session.get(ProjProjectHBM.class,
					pk);

			if (projProjectHBM == null) {
				_log.warn("No ProjProject exists with the primary key of " +
					pk.toString());
				throw new NoSuchProjectException(pk.toString());
			}

			com.liferay.portal.service.persistence.UserHBM userHBM = null;
			userHBM = (com.liferay.portal.service.persistence.UserHBM)session.get(com.liferay.portal.service.persistence.UserHBM.class,
					userPK);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					userPK.toString());
				throw new com.liferay.portal.NoSuchUserException(userPK.toString());
			}

			boolean value = projProjectHBM.getUsers().add(userHBM);
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
		throws NoSuchProjectException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjProjectHBM projProjectHBM = (ProjProjectHBM)session.get(ProjProjectHBM.class,
					pk);

			if (projProjectHBM == null) {
				_log.warn("No ProjProject exists with the primary key of " +
					pk.toString());
				throw new NoSuchProjectException(pk.toString());
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

			boolean value = projProjectHBM.getUsers().add(userHBM);
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
		throws NoSuchProjectException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjProjectHBM projProjectHBM = (ProjProjectHBM)session.get(ProjProjectHBM.class,
					pk);

			if (projProjectHBM == null) {
				_log.warn("No ProjProject exists with the primary key of " +
					pk.toString());
				throw new NoSuchProjectException(pk.toString());
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

				if (projProjectHBM.getUsers().add(userHBM)) {
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
		throws NoSuchProjectException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjProjectHBM projProjectHBM = (ProjProjectHBM)session.get(ProjProjectHBM.class,
					pk);

			if (projProjectHBM == null) {
				_log.warn("No ProjProject exists with the primary key of " +
					pk.toString());
				throw new NoSuchProjectException(pk.toString());
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

				if (projProjectHBM.getUsers().add(userHBM)) {
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
		throws NoSuchProjectException, SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjProjectHBM projProjectHBM = (ProjProjectHBM)session.get(ProjProjectHBM.class,
					pk);

			if (projProjectHBM == null) {
				_log.warn("No ProjProject exists with the primary key of " +
					pk.toString());
				throw new NoSuchProjectException(pk.toString());
			}

			projProjectHBM.getUsers().clear();
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
		throws NoSuchProjectException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjProjectHBM projProjectHBM = (ProjProjectHBM)session.get(ProjProjectHBM.class,
					pk);

			if (projProjectHBM == null) {
				_log.warn("No ProjProject exists with the primary key of " +
					pk.toString());
				throw new NoSuchProjectException(pk.toString());
			}

			com.liferay.portal.service.persistence.UserHBM userHBM = null;
			userHBM = (com.liferay.portal.service.persistence.UserHBM)session.get(com.liferay.portal.service.persistence.UserHBM.class,
					userPK);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					userPK.toString());
				throw new com.liferay.portal.NoSuchUserException(userPK.toString());
			}

			Collection c = projProjectHBM.getUsers();

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
		throws NoSuchProjectException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjProjectHBM projProjectHBM = (ProjProjectHBM)session.get(ProjProjectHBM.class,
					pk);

			if (projProjectHBM == null) {
				_log.warn("No ProjProject exists with the primary key of " +
					pk.toString());
				throw new NoSuchProjectException(pk.toString());
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

			Collection c = projProjectHBM.getUsers();

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
		throws NoSuchProjectException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjProjectHBM projProjectHBM = (ProjProjectHBM)session.get(ProjProjectHBM.class,
					pk);

			if (projProjectHBM == null) {
				_log.warn("No ProjProject exists with the primary key of " +
					pk.toString());
				throw new NoSuchProjectException(pk.toString());
			}

			com.liferay.portal.service.persistence.UserHBM userHBM = null;
			userHBM = (com.liferay.portal.service.persistence.UserHBM)session.get(com.liferay.portal.service.persistence.UserHBM.class,
					userPK);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					userPK.toString());
				throw new com.liferay.portal.NoSuchUserException(userPK.toString());
			}

			boolean value = projProjectHBM.getUsers().remove(userHBM);
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
		throws NoSuchProjectException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjProjectHBM projProjectHBM = (ProjProjectHBM)session.get(ProjProjectHBM.class,
					pk);

			if (projProjectHBM == null) {
				_log.warn("No ProjProject exists with the primary key of " +
					pk.toString());
				throw new NoSuchProjectException(pk.toString());
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

			boolean value = projProjectHBM.getUsers().remove(userHBM);
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
		throws NoSuchProjectException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjProjectHBM projProjectHBM = (ProjProjectHBM)session.get(ProjProjectHBM.class,
					pk);

			if (projProjectHBM == null) {
				_log.warn("No ProjProject exists with the primary key of " +
					pk.toString());
				throw new NoSuchProjectException(pk.toString());
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

				if (projProjectHBM.getUsers().remove(userHBM)) {
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
		throws NoSuchProjectException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjProjectHBM projProjectHBM = (ProjProjectHBM)session.get(ProjProjectHBM.class,
					pk);

			if (projProjectHBM == null) {
				_log.warn("No ProjProject exists with the primary key of " +
					pk.toString());
				throw new NoSuchProjectException(pk.toString());
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

				if (projProjectHBM.getUsers().remove(userHBM)) {
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

	public com.liferay.portlet.project.model.ProjProject findByPrimaryKey(
		String projectId) throws NoSuchProjectException, SystemException {
		com.liferay.portlet.project.model.ProjProject projProject = ProjProjectPool.get(projectId);
		Session session = null;

		try {
			if (projProject == null) {
				session = openSession();

				ProjProjectHBM projProjectHBM = (ProjProjectHBM)session.get(ProjProjectHBM.class,
						projectId);

				if (projProjectHBM == null) {
					_log.warn("No ProjProject exists with the primary key of " +
						projectId.toString());
					throw new NoSuchProjectException(projectId.toString());
				}

				projProject = ProjProjectHBMUtil.model(projProjectHBM);
			}

			return projProject;
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
				"FROM ProjProject IN CLASS com.liferay.portlet.project.service.persistence.ProjProjectHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ProjProjectHBM projProjectHBM = (ProjProjectHBM)itr.next();
				list.add(ProjProjectHBMUtil.model(projProjectHBM));
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
				"FROM ProjProject IN CLASS com.liferay.portlet.project.service.persistence.ProjProjectHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
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
					ProjProjectHBM projProjectHBM = (ProjProjectHBM)itr.next();
					list.add(ProjProjectHBMUtil.model(projProjectHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ProjProjectHBM projProjectHBM = (ProjProjectHBM)sr.get(0);
						list.add(ProjProjectHBMUtil.model(projProjectHBM));

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

	public com.liferay.portlet.project.model.ProjProject findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchProjectException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchProjectException();
		}
		else {
			return (com.liferay.portlet.project.model.ProjProject)list.get(0);
		}
	}

	public com.liferay.portlet.project.model.ProjProject findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchProjectException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchProjectException();
		}
		else {
			return (com.liferay.portlet.project.model.ProjProject)list.get(0);
		}
	}

	public com.liferay.portlet.project.model.ProjProject[] findByCompanyId_PrevAndNext(
		String projectId, String companyId, OrderByComparator obc)
		throws NoSuchProjectException, SystemException {
		com.liferay.portlet.project.model.ProjProject projProject = findByPrimaryKey(projectId);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjProject IN CLASS com.liferay.portlet.project.service.persistence.ProjProjectHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portlet.project.model.ProjProject[] array = new com.liferay.portlet.project.model.ProjProject[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ProjProjectHBM projProjectHBM = (ProjProjectHBM)sr.get(0);

					if (projProjectHBM == null) {
						break;
					}

					com.liferay.portlet.project.model.ProjProject curProjProject =
						ProjProjectHBMUtil.model(projProjectHBM);
					int value = obc.compare(projProject, curProjProject);

					if (value == 0) {
						if (!projProject.equals(curProjProject)) {
							break;
						}

						array[1] = curProjProject;

						if (sr.previous()) {
							array[0] = ProjProjectHBMUtil.model((ProjProjectHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ProjProjectHBMUtil.model((ProjProjectHBM)sr.get(
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
				"FROM ProjProject IN CLASS com.liferay.portlet.project.service.persistence.ProjProjectHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ProjProjectHBM projProjectHBM = (ProjProjectHBM)itr.next();
				list.add(ProjProjectHBMUtil.model(projProjectHBM));
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
				"FROM ProjProject IN CLASS com.liferay.portlet.project.service.persistence.ProjProjectHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
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
					ProjProjectHBM projProjectHBM = (ProjProjectHBM)itr.next();
					list.add(ProjProjectHBMUtil.model(projProjectHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ProjProjectHBM projProjectHBM = (ProjProjectHBM)sr.get(0);
						list.add(ProjProjectHBMUtil.model(projProjectHBM));

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

	public com.liferay.portlet.project.model.ProjProject findByUserId_First(
		String userId, OrderByComparator obc)
		throws NoSuchProjectException, SystemException {
		List list = findByUserId(userId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchProjectException();
		}
		else {
			return (com.liferay.portlet.project.model.ProjProject)list.get(0);
		}
	}

	public com.liferay.portlet.project.model.ProjProject findByUserId_Last(
		String userId, OrderByComparator obc)
		throws NoSuchProjectException, SystemException {
		int count = countByUserId(userId);
		List list = findByUserId(userId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchProjectException();
		}
		else {
			return (com.liferay.portlet.project.model.ProjProject)list.get(0);
		}
	}

	public com.liferay.portlet.project.model.ProjProject[] findByUserId_PrevAndNext(
		String projectId, String userId, OrderByComparator obc)
		throws NoSuchProjectException, SystemException {
		com.liferay.portlet.project.model.ProjProject projProject = findByPrimaryKey(projectId);
		int count = countByUserId(userId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjProject IN CLASS com.liferay.portlet.project.service.persistence.ProjProjectHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			com.liferay.portlet.project.model.ProjProject[] array = new com.liferay.portlet.project.model.ProjProject[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ProjProjectHBM projProjectHBM = (ProjProjectHBM)sr.get(0);

					if (projProjectHBM == null) {
						break;
					}

					com.liferay.portlet.project.model.ProjProject curProjProject =
						ProjProjectHBMUtil.model(projProjectHBM);
					int value = obc.compare(projProject, curProjProject);

					if (value == 0) {
						if (!projProject.equals(curProjProject)) {
							break;
						}

						array[1] = curProjProject;

						if (sr.previous()) {
							array[0] = ProjProjectHBMUtil.model((ProjProjectHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ProjProjectHBMUtil.model((ProjProjectHBM)sr.get(
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

	public List findByFirmId(String firmId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjProject IN CLASS com.liferay.portlet.project.service.persistence.ProjProjectHBM WHERE ");
			query.append("firmId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, firmId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ProjProjectHBM projProjectHBM = (ProjProjectHBM)itr.next();
				list.add(ProjProjectHBMUtil.model(projProjectHBM));
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

	public List findByFirmId(String firmId, int begin, int end)
		throws SystemException {
		return findByFirmId(firmId, begin, end, null);
	}

	public List findByFirmId(String firmId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjProject IN CLASS com.liferay.portlet.project.service.persistence.ProjProjectHBM WHERE ");
			query.append("firmId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, firmId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					ProjProjectHBM projProjectHBM = (ProjProjectHBM)itr.next();
					list.add(ProjProjectHBMUtil.model(projProjectHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ProjProjectHBM projProjectHBM = (ProjProjectHBM)sr.get(0);
						list.add(ProjProjectHBMUtil.model(projProjectHBM));

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

	public com.liferay.portlet.project.model.ProjProject findByFirmId_First(
		String firmId, OrderByComparator obc)
		throws NoSuchProjectException, SystemException {
		List list = findByFirmId(firmId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchProjectException();
		}
		else {
			return (com.liferay.portlet.project.model.ProjProject)list.get(0);
		}
	}

	public com.liferay.portlet.project.model.ProjProject findByFirmId_Last(
		String firmId, OrderByComparator obc)
		throws NoSuchProjectException, SystemException {
		int count = countByFirmId(firmId);
		List list = findByFirmId(firmId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchProjectException();
		}
		else {
			return (com.liferay.portlet.project.model.ProjProject)list.get(0);
		}
	}

	public com.liferay.portlet.project.model.ProjProject[] findByFirmId_PrevAndNext(
		String projectId, String firmId, OrderByComparator obc)
		throws NoSuchProjectException, SystemException {
		com.liferay.portlet.project.model.ProjProject projProject = findByPrimaryKey(projectId);
		int count = countByFirmId(firmId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjProject IN CLASS com.liferay.portlet.project.service.persistence.ProjProjectHBM WHERE ");
			query.append("firmId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, firmId);

			com.liferay.portlet.project.model.ProjProject[] array = new com.liferay.portlet.project.model.ProjProject[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ProjProjectHBM projProjectHBM = (ProjProjectHBM)sr.get(0);

					if (projProjectHBM == null) {
						break;
					}

					com.liferay.portlet.project.model.ProjProject curProjProject =
						ProjProjectHBMUtil.model(projProjectHBM);
					int value = obc.compare(projProject, curProjProject);

					if (value == 0) {
						if (!projProject.equals(curProjProject)) {
							break;
						}

						array[1] = curProjProject;

						if (sr.previous()) {
							array[0] = ProjProjectHBMUtil.model((ProjProjectHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ProjProjectHBMUtil.model((ProjProjectHBM)sr.get(
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

	public com.liferay.portlet.project.model.ProjProject findByC_C(
		String companyId, String code)
		throws NoSuchProjectException, SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjProject IN CLASS com.liferay.portlet.project.service.persistence.ProjProjectHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("code = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, code);

			Iterator itr = q.list().iterator();

			if (!itr.hasNext()) {
				throw new NoSuchProjectException();
			}

			ProjProjectHBM projProjectHBM = (ProjProjectHBM)itr.next();

			return ProjProjectHBMUtil.model(projProjectHBM);
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
				"FROM ProjProject IN CLASS com.liferay.portlet.project.service.persistence.ProjProjectHBM ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ProjProjectHBM projProjectHBM = (ProjProjectHBM)itr.next();
				list.add(ProjProjectHBMUtil.model(projProjectHBM));
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
				"FROM ProjProject IN CLASS com.liferay.portlet.project.service.persistence.ProjProjectHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ProjProjectHBM projProjectHBM = (ProjProjectHBM)itr.next();
				ProjProjectPool.remove((String)projProjectHBM.getPrimaryKey());
				session.delete(projProjectHBM);
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
				"FROM ProjProject IN CLASS com.liferay.portlet.project.service.persistence.ProjProjectHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ProjProjectHBM projProjectHBM = (ProjProjectHBM)itr.next();
				ProjProjectPool.remove((String)projProjectHBM.getPrimaryKey());
				session.delete(projProjectHBM);
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

	public void removeByFirmId(String firmId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjProject IN CLASS com.liferay.portlet.project.service.persistence.ProjProjectHBM WHERE ");
			query.append("firmId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, firmId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ProjProjectHBM projProjectHBM = (ProjProjectHBM)itr.next();
				ProjProjectPool.remove((String)projProjectHBM.getPrimaryKey());
				session.delete(projProjectHBM);
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

	public void removeByC_C(String companyId, String code)
		throws NoSuchProjectException, SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjProject IN CLASS com.liferay.portlet.project.service.persistence.ProjProjectHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("code = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, code);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ProjProjectHBM projProjectHBM = (ProjProjectHBM)itr.next();
				ProjProjectPool.remove((String)projProjectHBM.getPrimaryKey());
				session.delete(projProjectHBM);
			}

			session.flush();
		}
		catch (HibernateException he) {
			if (he instanceof ObjectNotFoundException) {
				throw new NoSuchProjectException();
			}
			else {
				throw new SystemException(he);
			}
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
				"FROM ProjProject IN CLASS com.liferay.portlet.project.service.persistence.ProjProjectHBM WHERE ");
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
				"FROM ProjProject IN CLASS com.liferay.portlet.project.service.persistence.ProjProjectHBM WHERE ");
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

	public int countByFirmId(String firmId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM ProjProject IN CLASS com.liferay.portlet.project.service.persistence.ProjProjectHBM WHERE ");
			query.append("firmId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, firmId);

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

	public int countByC_C(String companyId, String code)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM ProjProject IN CLASS com.liferay.portlet.project.service.persistence.ProjProjectHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("code = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, code);

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

	private static final Log _log = LogFactory.getLog(ProjProjectPersistence.class);
}