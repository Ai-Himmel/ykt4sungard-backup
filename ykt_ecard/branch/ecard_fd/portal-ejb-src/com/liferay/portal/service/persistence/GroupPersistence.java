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

import com.liferay.portal.NoSuchGroupException;
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
 * <a href="GroupPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class GroupPersistence extends BasePersistence {
	public com.liferay.portal.model.Group create(String groupId) {
		return new com.liferay.portal.model.Group(groupId);
	}

	public com.liferay.portal.model.Group remove(String groupId)
		throws NoSuchGroupException, SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, groupId);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					groupId.toString());
				throw new NoSuchGroupException(groupId.toString());
			}

			com.liferay.portal.model.Group group = GroupHBMUtil.model(groupHBM);
			session.delete(groupHBM);
			session.flush();
			GroupPool.remove(groupId);

			return group;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portal.model.Group update(
		com.liferay.portal.model.Group group) throws SystemException {
		Session session = null;

		try {
			if (group.isNew() || group.isModified()) {
				session = openSession();

				if (group.isNew()) {
					GroupHBM groupHBM = new GroupHBM(group.getGroupId(),
							group.getCompanyId(), group.getParentGroupId(),
							group.getName(), group.getFriendlyURL(),
							group.getThemeId(), group.getColorSchemeId());
					session.save(groupHBM);
					session.flush();
				}
				else {
					GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class,
							group.getPrimaryKey());

					if (groupHBM != null) {
						groupHBM.setCompanyId(group.getCompanyId());
						groupHBM.setParentGroupId(group.getParentGroupId());
						groupHBM.setName(group.getName());
						groupHBM.setFriendlyURL(group.getFriendlyURL());
						groupHBM.setThemeId(group.getThemeId());
						groupHBM.setColorSchemeId(group.getColorSchemeId());
						session.flush();
					}
					else {
						groupHBM = new GroupHBM(group.getGroupId(),
								group.getCompanyId(), group.getParentGroupId(),
								group.getName(), group.getFriendlyURL(),
								group.getThemeId(), group.getColorSchemeId());
						session.save(groupHBM);
						session.flush();
					}
				}

				group.setNew(false);
				group.setModified(false);
				group.protect();
				GroupPool.put(group.getPrimaryKey(), group);
			}

			return group;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List getRoles(String pk)
		throws NoSuchGroupException, SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT roleHBM FROM ");
			query.append(com.liferay.portal.service.persistence.GroupHBM.class.getName());
			query.append(" groupHBM ");
			query.append("JOIN groupHBM.roles AS roleHBM ");
			query.append("WHERE groupHBM.groupId = ? ");
			query.append("ORDER BY ");
			query.append("roleHBM.name ASC");

			Query q = session.createQuery(query.toString());
			q.setString(0, pk);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				com.liferay.portal.service.persistence.RoleHBM roleHBM = (com.liferay.portal.service.persistence.RoleHBM)itr.next();
				list.add(com.liferay.portal.service.persistence.RoleHBMUtil.model(
						roleHBM));
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

	public List getRoles(String pk, int begin, int end)
		throws NoSuchGroupException, SystemException {
		return getRoles(pk, begin, end, null);
	}

	public List getRoles(String pk, int begin, int end, OrderByComparator obc)
		throws NoSuchGroupException, SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT roleHBM FROM ");
			query.append(com.liferay.portal.service.persistence.GroupHBM.class.getName());
			query.append(" groupHBM ");
			query.append("JOIN groupHBM.roles AS roleHBM ");
			query.append("WHERE groupHBM.groupId = ? ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("roleHBM.name ASC");
			}

			Query q = session.createQuery(query.toString());
			q.setString(0, pk);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					com.liferay.portal.service.persistence.RoleHBM roleHBM = (com.liferay.portal.service.persistence.RoleHBM)itr.next();
					list.add(com.liferay.portal.service.persistence.RoleHBMUtil.model(
							roleHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						com.liferay.portal.service.persistence.RoleHBM roleHBM = (com.liferay.portal.service.persistence.RoleHBM)sr.get(0);
						list.add(com.liferay.portal.service.persistence.RoleHBMUtil.model(
								roleHBM));

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

	public int getRolesSize(String pk) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) FROM ");
			query.append(com.liferay.portal.service.persistence.GroupHBM.class.getName());
			query.append(" groupHBM ");
			query.append("JOIN groupHBM.roles AS roleHBM ");
			query.append("WHERE groupHBM.groupId = ? ");

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

	public void setRoles(String pk, String[] pks)
		throws NoSuchGroupException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
			}

			Set rolesSet = new HashSet();

			for (int i = 0; (pks != null) && (i < pks.length); i++) {
				com.liferay.portal.service.persistence.RoleHBM roleHBM = (com.liferay.portal.service.persistence.RoleHBM)session.get(com.liferay.portal.service.persistence.RoleHBM.class,
						pks[i]);

				if (roleHBM == null) {
					_log.warn("No Role exists with the primary key of " +
						pks[i].toString());
					throw new com.liferay.portal.NoSuchRoleException(pks[i].toString());
				}

				rolesSet.add(roleHBM);
			}

			groupHBM.setRoles(rolesSet);
			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void setRoles(String pk, List roles)
		throws NoSuchGroupException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
			}

			Set rolesSet = new HashSet();
			Iterator itr = roles.iterator();

			while (itr.hasNext()) {
				com.liferay.portal.model.Role role = (com.liferay.portal.model.Role)itr.next();
				com.liferay.portal.service.persistence.RoleHBM roleHBM = (com.liferay.portal.service.persistence.RoleHBM)session.get(com.liferay.portal.service.persistence.RoleHBM.class,
						role.getPrimaryKey());

				if (roleHBM == null) {
					_log.warn("No Role exists with the primary key of " +
						role.getPrimaryKey().toString());
					throw new com.liferay.portal.NoSuchRoleException(role.getPrimaryKey()
																		 .toString());
				}

				rolesSet.add(roleHBM);
			}

			groupHBM.setRoles(rolesSet);
			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean addRole(String pk, String rolePK)
		throws NoSuchGroupException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
			}

			com.liferay.portal.service.persistence.RoleHBM roleHBM = null;
			roleHBM = (com.liferay.portal.service.persistence.RoleHBM)session.get(com.liferay.portal.service.persistence.RoleHBM.class,
					rolePK);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					rolePK.toString());
				throw new com.liferay.portal.NoSuchRoleException(rolePK.toString());
			}

			boolean value = groupHBM.getRoles().add(roleHBM);
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

	public boolean addRole(String pk, com.liferay.portal.model.Role role)
		throws NoSuchGroupException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
			}

			com.liferay.portal.service.persistence.RoleHBM roleHBM = null;
			roleHBM = (com.liferay.portal.service.persistence.RoleHBM)session.get(com.liferay.portal.service.persistence.RoleHBM.class,
					role.getPrimaryKey());

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					role.getPrimaryKey().toString());
				throw new com.liferay.portal.NoSuchRoleException(role.getPrimaryKey()
																	 .toString());
			}

			boolean value = groupHBM.getRoles().add(roleHBM);
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

	public boolean addRoles(String pk, String[] rolePKs)
		throws NoSuchGroupException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < rolePKs.length; i++) {
				com.liferay.portal.service.persistence.RoleHBM roleHBM = null;
				roleHBM = (com.liferay.portal.service.persistence.RoleHBM)session.get(com.liferay.portal.service.persistence.RoleHBM.class,
						rolePKs[i]);

				if (roleHBM == null) {
					_log.warn("No Role exists with the primary key of " +
						rolePKs[i].toString());
					throw new com.liferay.portal.NoSuchRoleException(rolePKs[i].toString());
				}

				if (groupHBM.getRoles().add(roleHBM)) {
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

	public boolean addRoles(String pk, List roles)
		throws NoSuchGroupException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < roles.size(); i++) {
				com.liferay.portal.model.Role role = (com.liferay.portal.model.Role)roles.get(i);
				com.liferay.portal.service.persistence.RoleHBM roleHBM = (com.liferay.portal.service.persistence.RoleHBM)session.get(com.liferay.portal.service.persistence.RoleHBM.class,
						role.getPrimaryKey());

				if (roleHBM == null) {
					_log.warn("No Role exists with the primary key of " +
						role.getPrimaryKey().toString());
					throw new com.liferay.portal.NoSuchRoleException(role.getPrimaryKey()
																		 .toString());
				}

				if (groupHBM.getRoles().add(roleHBM)) {
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

	public void clearRoles(String pk)
		throws NoSuchGroupException, SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
			}

			groupHBM.getRoles().clear();
			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean containsRole(String pk, String rolePK)
		throws NoSuchGroupException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
			}

			com.liferay.portal.service.persistence.RoleHBM roleHBM = null;
			roleHBM = (com.liferay.portal.service.persistence.RoleHBM)session.get(com.liferay.portal.service.persistence.RoleHBM.class,
					rolePK);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					rolePK.toString());
				throw new com.liferay.portal.NoSuchRoleException(rolePK.toString());
			}

			Collection c = groupHBM.getRoles();

			return c.contains(roleHBM);
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean containsRole(String pk, com.liferay.portal.model.Role role)
		throws NoSuchGroupException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
			}

			com.liferay.portal.service.persistence.RoleHBM roleHBM = null;
			roleHBM = (com.liferay.portal.service.persistence.RoleHBM)session.get(com.liferay.portal.service.persistence.RoleHBM.class,
					role.getPrimaryKey());

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					role.getPrimaryKey().toString());
				throw new com.liferay.portal.NoSuchRoleException(role.getPrimaryKey()
																	 .toString());
			}

			Collection c = groupHBM.getRoles();

			return c.contains(roleHBM);
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean removeRole(String pk, String rolePK)
		throws NoSuchGroupException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
			}

			com.liferay.portal.service.persistence.RoleHBM roleHBM = null;
			roleHBM = (com.liferay.portal.service.persistence.RoleHBM)session.get(com.liferay.portal.service.persistence.RoleHBM.class,
					rolePK);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					rolePK.toString());
				throw new com.liferay.portal.NoSuchRoleException(rolePK.toString());
			}

			boolean value = groupHBM.getRoles().remove(roleHBM);
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

	public boolean removeRole(String pk, com.liferay.portal.model.Role role)
		throws NoSuchGroupException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
			}

			com.liferay.portal.service.persistence.RoleHBM roleHBM = null;
			roleHBM = (com.liferay.portal.service.persistence.RoleHBM)session.get(com.liferay.portal.service.persistence.RoleHBM.class,
					role.getPrimaryKey());

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					role.getPrimaryKey().toString());
				throw new com.liferay.portal.NoSuchRoleException(role.getPrimaryKey()
																	 .toString());
			}

			boolean value = groupHBM.getRoles().remove(roleHBM);
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

	public boolean removeRoles(String pk, String[] rolePKs)
		throws NoSuchGroupException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < rolePKs.length; i++) {
				com.liferay.portal.service.persistence.RoleHBM roleHBM = null;
				roleHBM = (com.liferay.portal.service.persistence.RoleHBM)session.get(com.liferay.portal.service.persistence.RoleHBM.class,
						rolePKs[i]);

				if (roleHBM == null) {
					_log.warn("No Role exists with the primary key of " +
						rolePKs[i].toString());
					throw new com.liferay.portal.NoSuchRoleException(rolePKs[i].toString());
				}

				if (groupHBM.getRoles().remove(roleHBM)) {
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

	public boolean removeRoles(String pk, List roles)
		throws NoSuchGroupException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < roles.size(); i++) {
				com.liferay.portal.model.Role role = (com.liferay.portal.model.Role)roles.get(i);
				com.liferay.portal.service.persistence.RoleHBM roleHBM = (com.liferay.portal.service.persistence.RoleHBM)session.get(com.liferay.portal.service.persistence.RoleHBM.class,
						role.getPrimaryKey());

				if (roleHBM == null) {
					_log.warn("No Role exists with the primary key of " +
						role.getPrimaryKey().toString());
					throw new com.liferay.portal.NoSuchRoleException(role.getPrimaryKey()
																		 .toString());
				}

				if (groupHBM.getRoles().remove(roleHBM)) {
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

	public List getUsers(String pk)
		throws NoSuchGroupException, SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT userHBM FROM ");
			query.append(com.liferay.portal.service.persistence.GroupHBM.class.getName());
			query.append(" groupHBM ");
			query.append("JOIN groupHBM.users AS userHBM ");
			query.append("WHERE groupHBM.groupId = ? ");
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
		throws NoSuchGroupException, SystemException {
		return getUsers(pk, begin, end, null);
	}

	public List getUsers(String pk, int begin, int end, OrderByComparator obc)
		throws NoSuchGroupException, SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT userHBM FROM ");
			query.append(com.liferay.portal.service.persistence.GroupHBM.class.getName());
			query.append(" groupHBM ");
			query.append("JOIN groupHBM.users AS userHBM ");
			query.append("WHERE groupHBM.groupId = ? ");

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
			query.append(com.liferay.portal.service.persistence.GroupHBM.class.getName());
			query.append(" groupHBM ");
			query.append("JOIN groupHBM.users AS userHBM ");
			query.append("WHERE groupHBM.groupId = ? ");

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
		throws NoSuchGroupException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
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

			groupHBM.setUsers(usersSet);
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
		throws NoSuchGroupException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
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

			groupHBM.setUsers(usersSet);
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
		throws NoSuchGroupException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
			}

			com.liferay.portal.service.persistence.UserHBM userHBM = null;
			userHBM = (com.liferay.portal.service.persistence.UserHBM)session.get(com.liferay.portal.service.persistence.UserHBM.class,
					userPK);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					userPK.toString());
				throw new com.liferay.portal.NoSuchUserException(userPK.toString());
			}

			boolean value = groupHBM.getUsers().add(userHBM);
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
		throws NoSuchGroupException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
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

			boolean value = groupHBM.getUsers().add(userHBM);
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
		throws NoSuchGroupException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
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

				if (groupHBM.getUsers().add(userHBM)) {
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
		throws NoSuchGroupException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
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

				if (groupHBM.getUsers().add(userHBM)) {
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
		throws NoSuchGroupException, SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
			}

			groupHBM.getUsers().clear();
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
		throws NoSuchGroupException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
			}

			com.liferay.portal.service.persistence.UserHBM userHBM = null;
			userHBM = (com.liferay.portal.service.persistence.UserHBM)session.get(com.liferay.portal.service.persistence.UserHBM.class,
					userPK);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					userPK.toString());
				throw new com.liferay.portal.NoSuchUserException(userPK.toString());
			}

			Collection c = groupHBM.getUsers();

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
		throws NoSuchGroupException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
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

			Collection c = groupHBM.getUsers();

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
		throws NoSuchGroupException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
			}

			com.liferay.portal.service.persistence.UserHBM userHBM = null;
			userHBM = (com.liferay.portal.service.persistence.UserHBM)session.get(com.liferay.portal.service.persistence.UserHBM.class,
					userPK);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					userPK.toString());
				throw new com.liferay.portal.NoSuchUserException(userPK.toString());
			}

			boolean value = groupHBM.getUsers().remove(userHBM);
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
		throws NoSuchGroupException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
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

			boolean value = groupHBM.getUsers().remove(userHBM);
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
		throws NoSuchGroupException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
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

				if (groupHBM.getUsers().remove(userHBM)) {
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
		throws NoSuchGroupException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class, pk);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					pk.toString());
				throw new NoSuchGroupException(pk.toString());
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

				if (groupHBM.getUsers().remove(userHBM)) {
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

	public com.liferay.portal.model.Group findByPrimaryKey(String groupId)
		throws NoSuchGroupException, SystemException {
		com.liferay.portal.model.Group group = GroupPool.get(groupId);
		Session session = null;

		try {
			if (group == null) {
				session = openSession();

				GroupHBM groupHBM = (GroupHBM)session.get(GroupHBM.class,
						groupId);

				if (groupHBM == null) {
					_log.warn("No Group exists with the primary key of " +
						groupId.toString());
					throw new NoSuchGroupException(groupId.toString());
				}

				group = GroupHBMUtil.model(groupHBM);
			}

			return group;
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
				"FROM Group_ IN CLASS com.liferay.portal.service.persistence.GroupHBM WHERE ");
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
				GroupHBM groupHBM = (GroupHBM)itr.next();
				list.add(GroupHBMUtil.model(groupHBM));
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
				"FROM Group_ IN CLASS com.liferay.portal.service.persistence.GroupHBM WHERE ");
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
					GroupHBM groupHBM = (GroupHBM)itr.next();
					list.add(GroupHBMUtil.model(groupHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						GroupHBM groupHBM = (GroupHBM)sr.get(0);
						list.add(GroupHBMUtil.model(groupHBM));

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

	public com.liferay.portal.model.Group findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchGroupException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchGroupException();
		}
		else {
			return (com.liferay.portal.model.Group)list.get(0);
		}
	}

	public com.liferay.portal.model.Group findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchGroupException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchGroupException();
		}
		else {
			return (com.liferay.portal.model.Group)list.get(0);
		}
	}

	public com.liferay.portal.model.Group[] findByCompanyId_PrevAndNext(
		String groupId, String companyId, OrderByComparator obc)
		throws NoSuchGroupException, SystemException {
		com.liferay.portal.model.Group group = findByPrimaryKey(groupId);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Group_ IN CLASS com.liferay.portal.service.persistence.GroupHBM WHERE ");
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

			com.liferay.portal.model.Group[] array = new com.liferay.portal.model.Group[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					GroupHBM groupHBM = (GroupHBM)sr.get(0);

					if (groupHBM == null) {
						break;
					}

					com.liferay.portal.model.Group curGroup = GroupHBMUtil.model(groupHBM);
					int value = obc.compare(group, curGroup);

					if (value == 0) {
						if (!group.equals(curGroup)) {
							break;
						}

						array[1] = curGroup;

						if (sr.previous()) {
							array[0] = GroupHBMUtil.model((GroupHBM)sr.get(0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = GroupHBMUtil.model((GroupHBM)sr.get(0));
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

	public com.liferay.portal.model.Group findByC_N(String companyId,
		String name) throws NoSuchGroupException, SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Group_ IN CLASS com.liferay.portal.service.persistence.GroupHBM WHERE ");
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
				throw new NoSuchGroupException();
			}

			GroupHBM groupHBM = (GroupHBM)itr.next();

			return GroupHBMUtil.model(groupHBM);
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portal.model.Group findByC_F(String companyId,
		String friendlyURL) throws NoSuchGroupException, SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Group_ IN CLASS com.liferay.portal.service.persistence.GroupHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("friendlyURL = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, friendlyURL);

			Iterator itr = q.list().iterator();

			if (!itr.hasNext()) {
				throw new NoSuchGroupException();
			}

			GroupHBM groupHBM = (GroupHBM)itr.next();

			return GroupHBMUtil.model(groupHBM);
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
				"FROM Group_ IN CLASS com.liferay.portal.service.persistence.GroupHBM ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				GroupHBM groupHBM = (GroupHBM)itr.next();
				list.add(GroupHBMUtil.model(groupHBM));
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
				"FROM Group_ IN CLASS com.liferay.portal.service.persistence.GroupHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				GroupHBM groupHBM = (GroupHBM)itr.next();
				GroupPool.remove((String)groupHBM.getPrimaryKey());
				session.delete(groupHBM);
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
		throws NoSuchGroupException, SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Group_ IN CLASS com.liferay.portal.service.persistence.GroupHBM WHERE ");
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
				GroupHBM groupHBM = (GroupHBM)itr.next();
				GroupPool.remove((String)groupHBM.getPrimaryKey());
				session.delete(groupHBM);
			}

			session.flush();
		}
		catch (HibernateException he) {
			if (he instanceof ObjectNotFoundException) {
				throw new NoSuchGroupException();
			}
			else {
				throw new SystemException(he);
			}
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void removeByC_F(String companyId, String friendlyURL)
		throws NoSuchGroupException, SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Group_ IN CLASS com.liferay.portal.service.persistence.GroupHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("friendlyURL = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, friendlyURL);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				GroupHBM groupHBM = (GroupHBM)itr.next();
				GroupPool.remove((String)groupHBM.getPrimaryKey());
				session.delete(groupHBM);
			}

			session.flush();
		}
		catch (HibernateException he) {
			if (he instanceof ObjectNotFoundException) {
				throw new NoSuchGroupException();
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
				"FROM Group_ IN CLASS com.liferay.portal.service.persistence.GroupHBM WHERE ");
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
				"FROM Group_ IN CLASS com.liferay.portal.service.persistence.GroupHBM WHERE ");
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

	public int countByC_F(String companyId, String friendlyURL)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM Group_ IN CLASS com.liferay.portal.service.persistence.GroupHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("friendlyURL = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, friendlyURL);

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

	private static final Log _log = LogFactory.getLog(GroupPersistence.class);
}