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

package com.liferay.portal.service.persistence;

import com.liferay.portal.NoSuchRoleException;
import com.liferay.portal.SystemException;
import com.liferay.portal.service.persistence.BasePersistence;
import com.liferay.portal.util.HibernateUtil;

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
 * <a href="RolePersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class RolePersistence extends BasePersistence {
	public com.liferay.portal.model.Role create(String roleId) {
		return new com.liferay.portal.model.Role(roleId);
	}

	public com.liferay.portal.model.Role remove(String roleId)
		throws NoSuchRoleException, SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, roleId);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					roleId.toString());
				throw new NoSuchRoleException(roleId.toString());
			}

			com.liferay.portal.model.Role role = RoleHBMUtil.model(roleHBM);
			session.delete(roleHBM);
			session.flush();
			RolePool.remove(roleId);

			return role;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portal.model.Role update(
		com.liferay.portal.model.Role role) throws SystemException {
		Session session = null;

		try {
			if (role.isNew() || role.isModified()) {
				session = openSession();

				if (role.isNew()) {
					RoleHBM roleHBM = new RoleHBM(role.getRoleId(),
							role.getCompanyId(), role.getName());
					session.save(roleHBM);
					session.flush();
				}
				else {
					RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class,
							role.getPrimaryKey());

					if (roleHBM != null) {
						roleHBM.setCompanyId(role.getCompanyId());
						roleHBM.setName(role.getName());
						session.flush();
					}
					else {
						roleHBM = new RoleHBM(role.getRoleId(),
								role.getCompanyId(), role.getName());
						session.save(roleHBM);
						session.flush();
					}
				}

				role.setNew(false);
				role.setModified(false);
				role.protect();
				RolePool.put(role.getPrimaryKey(), role);
			}

			return role;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List getGroups(String pk)
		throws NoSuchRoleException, SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT groupHBM FROM ");
			query.append(com.liferay.portal.service.persistence.RoleHBM.class.getName());
			query.append(" roleHBM ");
			query.append("JOIN roleHBM.groups AS groupHBM ");
			query.append("WHERE roleHBM.roleId = ? ");
			query.append("ORDER BY ");
			query.append("groupHBM.name ASC");

			Query q = session.createQuery(query.toString());
			q.setString(0, pk);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				com.liferay.portal.service.persistence.GroupHBM groupHBM = (com.liferay.portal.service.persistence.GroupHBM)itr.next();
				list.add(com.liferay.portal.service.persistence.GroupHBMUtil.model(
						groupHBM));
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

	public List getGroups(String pk, int begin, int end)
		throws NoSuchRoleException, SystemException {
		return getGroups(pk, begin, end, null);
	}

	public List getGroups(String pk, int begin, int end, OrderByComparator obc)
		throws NoSuchRoleException, SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT groupHBM FROM ");
			query.append(com.liferay.portal.service.persistence.RoleHBM.class.getName());
			query.append(" roleHBM ");
			query.append("JOIN roleHBM.groups AS groupHBM ");
			query.append("WHERE roleHBM.roleId = ? ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("groupHBM.name ASC");
			}

			Query q = session.createQuery(query.toString());
			q.setString(0, pk);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					com.liferay.portal.service.persistence.GroupHBM groupHBM = (com.liferay.portal.service.persistence.GroupHBM)itr.next();
					list.add(com.liferay.portal.service.persistence.GroupHBMUtil.model(
							groupHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						com.liferay.portal.service.persistence.GroupHBM groupHBM =
							(com.liferay.portal.service.persistence.GroupHBM)sr.get(0);
						list.add(com.liferay.portal.service.persistence.GroupHBMUtil.model(
								groupHBM));

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

	public int getGroupsSize(String pk) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) FROM ");
			query.append(com.liferay.portal.service.persistence.RoleHBM.class.getName());
			query.append(" roleHBM ");
			query.append("JOIN roleHBM.groups AS groupHBM ");
			query.append("WHERE roleHBM.roleId = ? ");

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

	public void setGroups(String pk, String[] pks)
		throws NoSuchRoleException, com.liferay.portal.NoSuchGroupException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
			}

			Set groupsSet = new HashSet();

			for (int i = 0; (pks != null) && (i < pks.length); i++) {
				com.liferay.portal.service.persistence.GroupHBM groupHBM = (com.liferay.portal.service.persistence.GroupHBM)session.get(com.liferay.portal.service.persistence.GroupHBM.class,
						pks[i]);

				if (groupHBM == null) {
					_log.warn("No Group exists with the primary key of " +
						pks[i].toString());
					throw new com.liferay.portal.NoSuchGroupException(pks[i].toString());
				}

				groupsSet.add(groupHBM);
			}

			roleHBM.setGroups(groupsSet);
			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void setGroups(String pk, List groups)
		throws NoSuchRoleException, com.liferay.portal.NoSuchGroupException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
			}

			Set groupsSet = new HashSet();
			Iterator itr = groups.iterator();

			while (itr.hasNext()) {
				com.liferay.portal.model.Group group = (com.liferay.portal.model.Group)itr.next();
				com.liferay.portal.service.persistence.GroupHBM groupHBM = (com.liferay.portal.service.persistence.GroupHBM)session.get(com.liferay.portal.service.persistence.GroupHBM.class,
						group.getPrimaryKey());

				if (groupHBM == null) {
					_log.warn("No Group exists with the primary key of " +
						group.getPrimaryKey().toString());
					throw new com.liferay.portal.NoSuchGroupException(group.getPrimaryKey()
																		   .toString());
				}

				groupsSet.add(groupHBM);
			}

			roleHBM.setGroups(groupsSet);
			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean addGroup(String pk, String groupPK)
		throws NoSuchRoleException, com.liferay.portal.NoSuchGroupException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
			}

			com.liferay.portal.service.persistence.GroupHBM groupHBM = null;
			groupHBM = (com.liferay.portal.service.persistence.GroupHBM)session.get(com.liferay.portal.service.persistence.GroupHBM.class,
					groupPK);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					groupPK.toString());
				throw new com.liferay.portal.NoSuchGroupException(groupPK.toString());
			}

			boolean value = roleHBM.getGroups().add(groupHBM);
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

	public boolean addGroup(String pk, com.liferay.portal.model.Group group)
		throws NoSuchRoleException, com.liferay.portal.NoSuchGroupException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
			}

			com.liferay.portal.service.persistence.GroupHBM groupHBM = null;
			groupHBM = (com.liferay.portal.service.persistence.GroupHBM)session.get(com.liferay.portal.service.persistence.GroupHBM.class,
					group.getPrimaryKey());

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					group.getPrimaryKey().toString());
				throw new com.liferay.portal.NoSuchGroupException(group.getPrimaryKey()
																	   .toString());
			}

			boolean value = roleHBM.getGroups().add(groupHBM);
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

	public boolean addGroups(String pk, String[] groupPKs)
		throws NoSuchRoleException, com.liferay.portal.NoSuchGroupException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < groupPKs.length; i++) {
				com.liferay.portal.service.persistence.GroupHBM groupHBM = null;
				groupHBM = (com.liferay.portal.service.persistence.GroupHBM)session.get(com.liferay.portal.service.persistence.GroupHBM.class,
						groupPKs[i]);

				if (groupHBM == null) {
					_log.warn("No Group exists with the primary key of " +
						groupPKs[i].toString());
					throw new com.liferay.portal.NoSuchGroupException(groupPKs[i].toString());
				}

				if (roleHBM.getGroups().add(groupHBM)) {
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

	public boolean addGroups(String pk, List groups)
		throws NoSuchRoleException, com.liferay.portal.NoSuchGroupException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < groups.size(); i++) {
				com.liferay.portal.model.Group group = (com.liferay.portal.model.Group)groups.get(i);
				com.liferay.portal.service.persistence.GroupHBM groupHBM = (com.liferay.portal.service.persistence.GroupHBM)session.get(com.liferay.portal.service.persistence.GroupHBM.class,
						group.getPrimaryKey());

				if (groupHBM == null) {
					_log.warn("No Group exists with the primary key of " +
						group.getPrimaryKey().toString());
					throw new com.liferay.portal.NoSuchGroupException(group.getPrimaryKey()
																		   .toString());
				}

				if (roleHBM.getGroups().add(groupHBM)) {
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

	public void clearGroups(String pk)
		throws NoSuchRoleException, SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
			}

			roleHBM.getGroups().clear();
			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean containsGroup(String pk, String groupPK)
		throws NoSuchRoleException, com.liferay.portal.NoSuchGroupException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
			}

			com.liferay.portal.service.persistence.GroupHBM groupHBM = null;
			groupHBM = (com.liferay.portal.service.persistence.GroupHBM)session.get(com.liferay.portal.service.persistence.GroupHBM.class,
					groupPK);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					groupPK.toString());
				throw new com.liferay.portal.NoSuchGroupException(groupPK.toString());
			}

			Collection c = roleHBM.getGroups();

			return c.contains(groupHBM);
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean containsGroup(String pk, com.liferay.portal.model.Group group)
		throws NoSuchRoleException, com.liferay.portal.NoSuchGroupException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
			}

			com.liferay.portal.service.persistence.GroupHBM groupHBM = null;
			groupHBM = (com.liferay.portal.service.persistence.GroupHBM)session.get(com.liferay.portal.service.persistence.GroupHBM.class,
					group.getPrimaryKey());

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					group.getPrimaryKey().toString());
				throw new com.liferay.portal.NoSuchGroupException(group.getPrimaryKey()
																	   .toString());
			}

			Collection c = roleHBM.getGroups();

			return c.contains(groupHBM);
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean removeGroup(String pk, String groupPK)
		throws NoSuchRoleException, com.liferay.portal.NoSuchGroupException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
			}

			com.liferay.portal.service.persistence.GroupHBM groupHBM = null;
			groupHBM = (com.liferay.portal.service.persistence.GroupHBM)session.get(com.liferay.portal.service.persistence.GroupHBM.class,
					groupPK);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					groupPK.toString());
				throw new com.liferay.portal.NoSuchGroupException(groupPK.toString());
			}

			boolean value = roleHBM.getGroups().remove(groupHBM);
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

	public boolean removeGroup(String pk, com.liferay.portal.model.Group group)
		throws NoSuchRoleException, com.liferay.portal.NoSuchGroupException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
			}

			com.liferay.portal.service.persistence.GroupHBM groupHBM = null;
			groupHBM = (com.liferay.portal.service.persistence.GroupHBM)session.get(com.liferay.portal.service.persistence.GroupHBM.class,
					group.getPrimaryKey());

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					group.getPrimaryKey().toString());
				throw new com.liferay.portal.NoSuchGroupException(group.getPrimaryKey()
																	   .toString());
			}

			boolean value = roleHBM.getGroups().remove(groupHBM);
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

	public boolean removeGroups(String pk, String[] groupPKs)
		throws NoSuchRoleException, com.liferay.portal.NoSuchGroupException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < groupPKs.length; i++) {
				com.liferay.portal.service.persistence.GroupHBM groupHBM = null;
				groupHBM = (com.liferay.portal.service.persistence.GroupHBM)session.get(com.liferay.portal.service.persistence.GroupHBM.class,
						groupPKs[i]);

				if (groupHBM == null) {
					_log.warn("No Group exists with the primary key of " +
						groupPKs[i].toString());
					throw new com.liferay.portal.NoSuchGroupException(groupPKs[i].toString());
				}

				if (roleHBM.getGroups().remove(groupHBM)) {
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

	public boolean removeGroups(String pk, List groups)
		throws NoSuchRoleException, com.liferay.portal.NoSuchGroupException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < groups.size(); i++) {
				com.liferay.portal.model.Group group = (com.liferay.portal.model.Group)groups.get(i);
				com.liferay.portal.service.persistence.GroupHBM groupHBM = (com.liferay.portal.service.persistence.GroupHBM)session.get(com.liferay.portal.service.persistence.GroupHBM.class,
						group.getPrimaryKey());

				if (groupHBM == null) {
					_log.warn("No Group exists with the primary key of " +
						group.getPrimaryKey().toString());
					throw new com.liferay.portal.NoSuchGroupException(group.getPrimaryKey()
																		   .toString());
				}

				if (roleHBM.getGroups().remove(groupHBM)) {
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

	public List getUsers(String pk) throws NoSuchRoleException, SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT userHBM FROM ");
			query.append(com.liferay.portal.service.persistence.RoleHBM.class.getName());
			query.append(" roleHBM ");
			query.append("JOIN roleHBM.users AS userHBM ");
			query.append("WHERE roleHBM.roleId = ? ");
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
		throws NoSuchRoleException, SystemException {
		return getUsers(pk, begin, end, null);
	}

	public List getUsers(String pk, int begin, int end, OrderByComparator obc)
		throws NoSuchRoleException, SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT userHBM FROM ");
			query.append(com.liferay.portal.service.persistence.RoleHBM.class.getName());
			query.append(" roleHBM ");
			query.append("JOIN roleHBM.users AS userHBM ");
			query.append("WHERE roleHBM.roleId = ? ");

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
			query.append(com.liferay.portal.service.persistence.RoleHBM.class.getName());
			query.append(" roleHBM ");
			query.append("JOIN roleHBM.users AS userHBM ");
			query.append("WHERE roleHBM.roleId = ? ");

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
		throws NoSuchRoleException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
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

			roleHBM.setUsers(usersSet);
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
		throws NoSuchRoleException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
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

			roleHBM.setUsers(usersSet);
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
		throws NoSuchRoleException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
			}

			com.liferay.portal.service.persistence.UserHBM userHBM = null;
			userHBM = (com.liferay.portal.service.persistence.UserHBM)session.get(com.liferay.portal.service.persistence.UserHBM.class,
					userPK);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					userPK.toString());
				throw new com.liferay.portal.NoSuchUserException(userPK.toString());
			}

			boolean value = roleHBM.getUsers().add(userHBM);
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
		throws NoSuchRoleException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
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

			boolean value = roleHBM.getUsers().add(userHBM);
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
		throws NoSuchRoleException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
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

				if (roleHBM.getUsers().add(userHBM)) {
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
		throws NoSuchRoleException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
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

				if (roleHBM.getUsers().add(userHBM)) {
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
		throws NoSuchRoleException, SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
			}

			roleHBM.getUsers().clear();
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
		throws NoSuchRoleException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
			}

			com.liferay.portal.service.persistence.UserHBM userHBM = null;
			userHBM = (com.liferay.portal.service.persistence.UserHBM)session.get(com.liferay.portal.service.persistence.UserHBM.class,
					userPK);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					userPK.toString());
				throw new com.liferay.portal.NoSuchUserException(userPK.toString());
			}

			Collection c = roleHBM.getUsers();

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
		throws NoSuchRoleException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
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

			Collection c = roleHBM.getUsers();

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
		throws NoSuchRoleException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
			}

			com.liferay.portal.service.persistence.UserHBM userHBM = null;
			userHBM = (com.liferay.portal.service.persistence.UserHBM)session.get(com.liferay.portal.service.persistence.UserHBM.class,
					userPK);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					userPK.toString());
				throw new com.liferay.portal.NoSuchUserException(userPK.toString());
			}

			boolean value = roleHBM.getUsers().remove(userHBM);
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
		throws NoSuchRoleException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
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

			boolean value = roleHBM.getUsers().remove(userHBM);
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
		throws NoSuchRoleException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
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

				if (roleHBM.getUsers().remove(userHBM)) {
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
		throws NoSuchRoleException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, pk);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					pk.toString());
				throw new NoSuchRoleException(pk.toString());
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

				if (roleHBM.getUsers().remove(userHBM)) {
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

	public com.liferay.portal.model.Role findByPrimaryKey(String roleId)
		throws NoSuchRoleException, SystemException {
		com.liferay.portal.model.Role role = RolePool.get(roleId);
		Session session = null;

		try {
			if (role == null) {
				session = openSession();

				RoleHBM roleHBM = (RoleHBM)session.get(RoleHBM.class, roleId);

				if (roleHBM == null) {
					_log.warn("No Role exists with the primary key of " +
						roleId.toString());
					throw new NoSuchRoleException(roleId.toString());
				}

				role = RoleHBMUtil.model(roleHBM);
			}

			return role;
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
				"FROM Role_ IN CLASS com.liferay.portal.service.persistence.RoleHBM WHERE ");
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
				RoleHBM roleHBM = (RoleHBM)itr.next();
				list.add(RoleHBMUtil.model(roleHBM));
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
				"FROM Role_ IN CLASS com.liferay.portal.service.persistence.RoleHBM WHERE ");
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
					RoleHBM roleHBM = (RoleHBM)itr.next();
					list.add(RoleHBMUtil.model(roleHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						RoleHBM roleHBM = (RoleHBM)sr.get(0);
						list.add(RoleHBMUtil.model(roleHBM));

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

	public com.liferay.portal.model.Role findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchRoleException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchRoleException();
		}
		else {
			return (com.liferay.portal.model.Role)list.get(0);
		}
	}

	public com.liferay.portal.model.Role findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchRoleException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchRoleException();
		}
		else {
			return (com.liferay.portal.model.Role)list.get(0);
		}
	}

	public com.liferay.portal.model.Role[] findByCompanyId_PrevAndNext(
		String roleId, String companyId, OrderByComparator obc)
		throws NoSuchRoleException, SystemException {
		com.liferay.portal.model.Role role = findByPrimaryKey(roleId);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Role_ IN CLASS com.liferay.portal.service.persistence.RoleHBM WHERE ");
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

			com.liferay.portal.model.Role[] array = new com.liferay.portal.model.Role[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					RoleHBM roleHBM = (RoleHBM)sr.get(0);

					if (roleHBM == null) {
						break;
					}

					com.liferay.portal.model.Role curRole = RoleHBMUtil.model(roleHBM);
					int value = obc.compare(role, curRole);

					if (value == 0) {
						if (!role.equals(curRole)) {
							break;
						}

						array[1] = curRole;

						if (sr.previous()) {
							array[0] = RoleHBMUtil.model((RoleHBM)sr.get(0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = RoleHBMUtil.model((RoleHBM)sr.get(0));
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

	public com.liferay.portal.model.Role findByC_N(String companyId, String name)
		throws NoSuchRoleException, SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Role_ IN CLASS com.liferay.portal.service.persistence.RoleHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("name = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, name);

			Iterator itr = q.list().iterator();

			if (!itr.hasNext()) {
				throw new NoSuchRoleException();
			}

			RoleHBM roleHBM = (RoleHBM)itr.next();

			return RoleHBMUtil.model(roleHBM);
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
				"FROM Role_ IN CLASS com.liferay.portal.service.persistence.RoleHBM ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				RoleHBM roleHBM = (RoleHBM)itr.next();
				list.add(RoleHBMUtil.model(roleHBM));
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
				"FROM Role_ IN CLASS com.liferay.portal.service.persistence.RoleHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				RoleHBM roleHBM = (RoleHBM)itr.next();
				RolePool.remove((String)roleHBM.getPrimaryKey());
				session.delete(roleHBM);
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

	public void removeByC_N(String companyId, String name)
		throws NoSuchRoleException, SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Role_ IN CLASS com.liferay.portal.service.persistence.RoleHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("name = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, name);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				RoleHBM roleHBM = (RoleHBM)itr.next();
				RolePool.remove((String)roleHBM.getPrimaryKey());
				session.delete(roleHBM);
			}

			session.flush();
		}
		catch (HibernateException he) {
			if (he instanceof ObjectNotFoundException) {
				throw new NoSuchRoleException();
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
				"FROM Role_ IN CLASS com.liferay.portal.service.persistence.RoleHBM WHERE ");
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

	public int countByC_N(String companyId, String name)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM Role_ IN CLASS com.liferay.portal.service.persistence.RoleHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("name = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, name);

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

	private static final Log _log = LogFactory.getLog(RolePersistence.class);
}