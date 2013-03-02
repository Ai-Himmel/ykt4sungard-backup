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

import com.liferay.portal.NoSuchUserException;
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
 * <a href="UserPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class UserPersistence extends BasePersistence {
	public com.liferay.portal.model.User create(String userId) {
		return new com.liferay.portal.model.User(userId);
	}

	public com.liferay.portal.model.User remove(String userId)
		throws NoSuchUserException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, userId);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					userId.toString());
				throw new NoSuchUserException(userId.toString());
			}

			com.liferay.portal.model.User user = UserHBMUtil.model(userHBM);
			session.delete(userHBM);
			session.flush();
			UserPool.remove(userId);

			return user;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portal.model.User update(
		com.liferay.portal.model.User user) throws SystemException {
		Session session = null;

		try {
			if (user.isNew() || user.isModified()) {
				session = openSession();

				if (user.isNew()) {
					UserHBM userHBM = new UserHBM(user.getUserId(),
							user.getCompanyId(), user.getPassword(),
							user.getPasswordEncrypted(),
							user.getPasswordExpirationDate(),
							user.getPasswordReset(), user.getFirstName(),
							user.getMiddleName(), user.getLastName(),
							user.getNickName(), user.getMale(),
							user.getBirthday(), user.getEmailAddress(),
							user.getSmsId(), user.getAimId(), user.getIcqId(),
							user.getMsnId(), user.getYmId(),
							user.getFavoriteActivity(),
							user.getFavoriteBibleVerse(),
							user.getFavoriteFood(), user.getFavoriteMovie(),
							user.getFavoriteMusic(), user.getLanguageId(),
							user.getTimeZoneId(), user.getThemeId(),
							user.getColorSchemeId(), user.getGreeting(),
							user.getResolution(), user.getComments(),
							user.getCreateDate(), user.getLoginDate(),
							user.getLoginIP(), user.getLastLoginDate(),
							user.getLastLoginIP(),
							user.getFailedLoginAttempts(),
							user.getAgreedToTermsOfUse(), user.getActive());
					session.save(userHBM);
					session.flush();
				}
				else {
					UserHBM userHBM = (UserHBM)session.get(UserHBM.class,
							user.getPrimaryKey());

					if (userHBM != null) {
						userHBM.setCompanyId(user.getCompanyId());
						userHBM.setPassword(user.getPassword());
						userHBM.setPasswordEncrypted(user.getPasswordEncrypted());
						userHBM.setPasswordExpirationDate(user.getPasswordExpirationDate());
						userHBM.setPasswordReset(user.getPasswordReset());
						userHBM.setFirstName(user.getFirstName());
						userHBM.setMiddleName(user.getMiddleName());
						userHBM.setLastName(user.getLastName());
						userHBM.setNickName(user.getNickName());
						userHBM.setMale(user.getMale());
						userHBM.setBirthday(user.getBirthday());
						userHBM.setEmailAddress(user.getEmailAddress());
						userHBM.setSmsId(user.getSmsId());
						userHBM.setAimId(user.getAimId());
						userHBM.setIcqId(user.getIcqId());
						userHBM.setMsnId(user.getMsnId());
						userHBM.setYmId(user.getYmId());
						userHBM.setFavoriteActivity(user.getFavoriteActivity());
						userHBM.setFavoriteBibleVerse(user.getFavoriteBibleVerse());
						userHBM.setFavoriteFood(user.getFavoriteFood());
						userHBM.setFavoriteMovie(user.getFavoriteMovie());
						userHBM.setFavoriteMusic(user.getFavoriteMusic());
						userHBM.setLanguageId(user.getLanguageId());
						userHBM.setTimeZoneId(user.getTimeZoneId());
						userHBM.setThemeId(user.getThemeId());
						userHBM.setColorSchemeId(user.getColorSchemeId());
						userHBM.setGreeting(user.getGreeting());
						userHBM.setResolution(user.getResolution());
						userHBM.setComments(user.getComments());
						userHBM.setCreateDate(user.getCreateDate());
						userHBM.setLoginDate(user.getLoginDate());
						userHBM.setLoginIP(user.getLoginIP());
						userHBM.setLastLoginDate(user.getLastLoginDate());
						userHBM.setLastLoginIP(user.getLastLoginIP());
						userHBM.setFailedLoginAttempts(user.getFailedLoginAttempts());
						userHBM.setAgreedToTermsOfUse(user.getAgreedToTermsOfUse());
						userHBM.setActive(user.getActive());
						session.update(userHBM);
						session.flush();
					}
					else {
						userHBM = new UserHBM(user.getUserId(),
								user.getCompanyId(), user.getPassword(),
								user.getPasswordEncrypted(),
								user.getPasswordExpirationDate(),
								user.getPasswordReset(), user.getFirstName(),
								user.getMiddleName(), user.getLastName(),
								user.getNickName(), user.getMale(),
								user.getBirthday(), user.getEmailAddress(),
								user.getSmsId(), user.getAimId(),
								user.getIcqId(), user.getMsnId(),
								user.getYmId(), user.getFavoriteActivity(),
								user.getFavoriteBibleVerse(),
								user.getFavoriteFood(),
								user.getFavoriteMovie(),
								user.getFavoriteMusic(), user.getLanguageId(),
								user.getTimeZoneId(), user.getThemeId(),
								user.getColorSchemeId(), user.getGreeting(),
								user.getResolution(), user.getComments(),
								user.getCreateDate(), user.getLoginDate(),
								user.getLoginIP(), user.getLastLoginDate(),
								user.getLastLoginIP(),
								user.getFailedLoginAttempts(),
								user.getAgreedToTermsOfUse(), user.getActive());
						session.save(userHBM);
						session.flush();
					}
				}

				user.setNew(false);
				user.setModified(false);
				user.protect();
				UserPool.put(user.getPrimaryKey(), user);
			}

			return user;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List getGroups(String pk)
		throws NoSuchUserException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT groupHBM FROM ");
			query.append(com.liferay.portal.service.persistence.UserHBM.class.getName());
			query.append(" userHBM ");
			query.append("JOIN userHBM.groups AS groupHBM ");
			query.append("WHERE userHBM.userId = ? ");
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
		throws NoSuchUserException, SystemException {
		return getGroups(pk, begin, end, null);
	}

	public List getGroups(String pk, int begin, int end, OrderByComparator obc)
		throws NoSuchUserException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT groupHBM FROM ");
			query.append(com.liferay.portal.service.persistence.UserHBM.class.getName());
			query.append(" userHBM ");
			query.append("JOIN userHBM.groups AS groupHBM ");
			query.append("WHERE userHBM.userId = ? ");

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
			query.append(com.liferay.portal.service.persistence.UserHBM.class.getName());
			query.append(" userHBM ");
			query.append("JOIN userHBM.groups AS groupHBM ");
			query.append("WHERE userHBM.userId = ? ");

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
		throws NoSuchUserException, com.liferay.portal.NoSuchGroupException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
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

			userHBM.setGroups(groupsSet);
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
		throws NoSuchUserException, com.liferay.portal.NoSuchGroupException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
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

			userHBM.setGroups(groupsSet);
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
		throws NoSuchUserException, com.liferay.portal.NoSuchGroupException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			com.liferay.portal.service.persistence.GroupHBM groupHBM = null;
			groupHBM = (com.liferay.portal.service.persistence.GroupHBM)session.get(com.liferay.portal.service.persistence.GroupHBM.class,
					groupPK);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					groupPK.toString());
				throw new com.liferay.portal.NoSuchGroupException(groupPK.toString());
			}

			boolean value = userHBM.getGroups().add(groupHBM);
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
		throws NoSuchUserException, com.liferay.portal.NoSuchGroupException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
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

			boolean value = userHBM.getGroups().add(groupHBM);
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
		throws NoSuchUserException, com.liferay.portal.NoSuchGroupException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
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

				if (userHBM.getGroups().add(groupHBM)) {
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
		throws NoSuchUserException, com.liferay.portal.NoSuchGroupException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
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

				if (userHBM.getGroups().add(groupHBM)) {
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
		throws NoSuchUserException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			userHBM.getGroups().clear();
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
		throws NoSuchUserException, com.liferay.portal.NoSuchGroupException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			com.liferay.portal.service.persistence.GroupHBM groupHBM = null;
			groupHBM = (com.liferay.portal.service.persistence.GroupHBM)session.get(com.liferay.portal.service.persistence.GroupHBM.class,
					groupPK);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					groupPK.toString());
				throw new com.liferay.portal.NoSuchGroupException(groupPK.toString());
			}

			Collection c = userHBM.getGroups();

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
		throws NoSuchUserException, com.liferay.portal.NoSuchGroupException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
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

			Collection c = userHBM.getGroups();

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
		throws NoSuchUserException, com.liferay.portal.NoSuchGroupException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			com.liferay.portal.service.persistence.GroupHBM groupHBM = null;
			groupHBM = (com.liferay.portal.service.persistence.GroupHBM)session.get(com.liferay.portal.service.persistence.GroupHBM.class,
					groupPK);

			if (groupHBM == null) {
				_log.warn("No Group exists with the primary key of " +
					groupPK.toString());
				throw new com.liferay.portal.NoSuchGroupException(groupPK.toString());
			}

			boolean value = userHBM.getGroups().remove(groupHBM);
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
		throws NoSuchUserException, com.liferay.portal.NoSuchGroupException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
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

			boolean value = userHBM.getGroups().remove(groupHBM);
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
		throws NoSuchUserException, com.liferay.portal.NoSuchGroupException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
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

				if (userHBM.getGroups().remove(groupHBM)) {
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
		throws NoSuchUserException, com.liferay.portal.NoSuchGroupException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
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

				if (userHBM.getGroups().remove(groupHBM)) {
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

	public List getRoles(String pk) throws NoSuchUserException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT roleHBM FROM ");
			query.append(com.liferay.portal.service.persistence.UserHBM.class.getName());
			query.append(" userHBM ");
			query.append("JOIN userHBM.roles AS roleHBM ");
			query.append("WHERE userHBM.userId = ? ");
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
		throws NoSuchUserException, SystemException {
		return getRoles(pk, begin, end, null);
	}

	public List getRoles(String pk, int begin, int end, OrderByComparator obc)
		throws NoSuchUserException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT roleHBM FROM ");
			query.append(com.liferay.portal.service.persistence.UserHBM.class.getName());
			query.append(" userHBM ");
			query.append("JOIN userHBM.roles AS roleHBM ");
			query.append("WHERE userHBM.userId = ? ");

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
			query.append(com.liferay.portal.service.persistence.UserHBM.class.getName());
			query.append(" userHBM ");
			query.append("JOIN userHBM.roles AS roleHBM ");
			query.append("WHERE userHBM.userId = ? ");

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
		throws NoSuchUserException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
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

			userHBM.setRoles(rolesSet);
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
		throws NoSuchUserException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
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

			userHBM.setRoles(rolesSet);
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
		throws NoSuchUserException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			com.liferay.portal.service.persistence.RoleHBM roleHBM = null;
			roleHBM = (com.liferay.portal.service.persistence.RoleHBM)session.get(com.liferay.portal.service.persistence.RoleHBM.class,
					rolePK);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					rolePK.toString());
				throw new com.liferay.portal.NoSuchRoleException(rolePK.toString());
			}

			boolean value = userHBM.getRoles().add(roleHBM);
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
		throws NoSuchUserException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
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

			boolean value = userHBM.getRoles().add(roleHBM);
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
		throws NoSuchUserException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
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

				if (userHBM.getRoles().add(roleHBM)) {
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
		throws NoSuchUserException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
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

				if (userHBM.getRoles().add(roleHBM)) {
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
		throws NoSuchUserException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			userHBM.getRoles().clear();
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
		throws NoSuchUserException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			com.liferay.portal.service.persistence.RoleHBM roleHBM = null;
			roleHBM = (com.liferay.portal.service.persistence.RoleHBM)session.get(com.liferay.portal.service.persistence.RoleHBM.class,
					rolePK);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					rolePK.toString());
				throw new com.liferay.portal.NoSuchRoleException(rolePK.toString());
			}

			Collection c = userHBM.getRoles();

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
		throws NoSuchUserException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
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

			Collection c = userHBM.getRoles();

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
		throws NoSuchUserException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			com.liferay.portal.service.persistence.RoleHBM roleHBM = null;
			roleHBM = (com.liferay.portal.service.persistence.RoleHBM)session.get(com.liferay.portal.service.persistence.RoleHBM.class,
					rolePK);

			if (roleHBM == null) {
				_log.warn("No Role exists with the primary key of " +
					rolePK.toString());
				throw new com.liferay.portal.NoSuchRoleException(rolePK.toString());
			}

			boolean value = userHBM.getRoles().remove(roleHBM);
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
		throws NoSuchUserException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
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

			boolean value = userHBM.getRoles().remove(roleHBM);
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
		throws NoSuchUserException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
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

				if (userHBM.getRoles().remove(roleHBM)) {
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
		throws NoSuchUserException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
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

				if (userHBM.getRoles().remove(roleHBM)) {
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

	public List getProjProjects(String pk)
		throws NoSuchUserException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT projProjectHBM FROM ");
			query.append(com.liferay.portal.service.persistence.UserHBM.class.getName());
			query.append(" userHBM ");
			query.append("JOIN userHBM.projProjects AS projProjectHBM ");
			query.append("WHERE userHBM.userId = ? ");
			query.append("ORDER BY ");
			query.append("projProjectHBM.name ASC");

			Query q = session.createQuery(query.toString());
			q.setString(0, pk);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				com.liferay.portlet.project.service.persistence.ProjProjectHBM projProjectHBM =
					(com.liferay.portlet.project.service.persistence.ProjProjectHBM)itr.next();
				list.add(com.liferay.portlet.project.service.persistence.ProjProjectHBMUtil.model(
						projProjectHBM));
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

	public List getProjProjects(String pk, int begin, int end)
		throws NoSuchUserException, SystemException {
		return getProjProjects(pk, begin, end, null);
	}

	public List getProjProjects(String pk, int begin, int end,
		OrderByComparator obc) throws NoSuchUserException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT projProjectHBM FROM ");
			query.append(com.liferay.portal.service.persistence.UserHBM.class.getName());
			query.append(" userHBM ");
			query.append("JOIN userHBM.projProjects AS projProjectHBM ");
			query.append("WHERE userHBM.userId = ? ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("projProjectHBM.name ASC");
			}

			Query q = session.createQuery(query.toString());
			q.setString(0, pk);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					com.liferay.portlet.project.service.persistence.ProjProjectHBM projProjectHBM =
						(com.liferay.portlet.project.service.persistence.ProjProjectHBM)itr.next();
					list.add(com.liferay.portlet.project.service.persistence.ProjProjectHBMUtil.model(
							projProjectHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						com.liferay.portlet.project.service.persistence.ProjProjectHBM projProjectHBM =
							(com.liferay.portlet.project.service.persistence.ProjProjectHBM)sr.get(0);
						list.add(com.liferay.portlet.project.service.persistence.ProjProjectHBMUtil.model(
								projProjectHBM));

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

	public int getProjProjectsSize(String pk) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) FROM ");
			query.append(com.liferay.portal.service.persistence.UserHBM.class.getName());
			query.append(" userHBM ");
			query.append("JOIN userHBM.projProjects AS projProjectHBM ");
			query.append("WHERE userHBM.userId = ? ");

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

	public void setProjProjects(String pk, String[] pks)
		throws NoSuchUserException, 
			com.liferay.portlet.project.NoSuchProjectException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			Set projProjectsSet = new HashSet();

			for (int i = 0; (pks != null) && (i < pks.length); i++) {
				com.liferay.portlet.project.service.persistence.ProjProjectHBM projProjectHBM =
					(com.liferay.portlet.project.service.persistence.ProjProjectHBM)session.get(com.liferay.portlet.project.service.persistence.ProjProjectHBM.class,
						pks[i]);

				if (projProjectHBM == null) {
					_log.warn("No ProjProject exists with the primary key of " +
						pks[i].toString());
					throw new com.liferay.portlet.project.NoSuchProjectException(pks[i].toString());
				}

				projProjectsSet.add(projProjectHBM);
			}

			userHBM.setProjProjects(projProjectsSet);
			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void setProjProjects(String pk, List projProjects)
		throws NoSuchUserException, 
			com.liferay.portlet.project.NoSuchProjectException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			Set projProjectsSet = new HashSet();
			Iterator itr = projProjects.iterator();

			while (itr.hasNext()) {
				com.liferay.portlet.project.model.ProjProject projProject = (com.liferay.portlet.project.model.ProjProject)itr.next();
				com.liferay.portlet.project.service.persistence.ProjProjectHBM projProjectHBM =
					(com.liferay.portlet.project.service.persistence.ProjProjectHBM)session.get(com.liferay.portlet.project.service.persistence.ProjProjectHBM.class,
						projProject.getPrimaryKey());

				if (projProjectHBM == null) {
					_log.warn("No ProjProject exists with the primary key of " +
						projProject.getPrimaryKey().toString());
					throw new com.liferay.portlet.project.NoSuchProjectException(projProject.getPrimaryKey()
																							.toString());
				}

				projProjectsSet.add(projProjectHBM);
			}

			userHBM.setProjProjects(projProjectsSet);
			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean addProjProject(String pk, String projProjectPK)
		throws NoSuchUserException, 
			com.liferay.portlet.project.NoSuchProjectException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			com.liferay.portlet.project.service.persistence.ProjProjectHBM projProjectHBM =
				null;
			projProjectHBM = (com.liferay.portlet.project.service.persistence.ProjProjectHBM)session.get(com.liferay.portlet.project.service.persistence.ProjProjectHBM.class,
					projProjectPK);

			if (projProjectHBM == null) {
				_log.warn("No ProjProject exists with the primary key of " +
					projProjectPK.toString());
				throw new com.liferay.portlet.project.NoSuchProjectException(projProjectPK.toString());
			}

			boolean value = userHBM.getProjProjects().add(projProjectHBM);
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

	public boolean addProjProject(String pk,
		com.liferay.portlet.project.model.ProjProject projProject)
		throws NoSuchUserException, 
			com.liferay.portlet.project.NoSuchProjectException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			com.liferay.portlet.project.service.persistence.ProjProjectHBM projProjectHBM =
				null;
			projProjectHBM = (com.liferay.portlet.project.service.persistence.ProjProjectHBM)session.get(com.liferay.portlet.project.service.persistence.ProjProjectHBM.class,
					projProject.getPrimaryKey());

			if (projProjectHBM == null) {
				_log.warn("No ProjProject exists with the primary key of " +
					projProject.getPrimaryKey().toString());
				throw new com.liferay.portlet.project.NoSuchProjectException(projProject.getPrimaryKey()
																						.toString());
			}

			boolean value = userHBM.getProjProjects().add(projProjectHBM);
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

	public boolean addProjProjects(String pk, String[] projProjectPKs)
		throws NoSuchUserException, 
			com.liferay.portlet.project.NoSuchProjectException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < projProjectPKs.length; i++) {
				com.liferay.portlet.project.service.persistence.ProjProjectHBM projProjectHBM =
					null;
				projProjectHBM = (com.liferay.portlet.project.service.persistence.ProjProjectHBM)session.get(com.liferay.portlet.project.service.persistence.ProjProjectHBM.class,
						projProjectPKs[i]);

				if (projProjectHBM == null) {
					_log.warn("No ProjProject exists with the primary key of " +
						projProjectPKs[i].toString());
					throw new com.liferay.portlet.project.NoSuchProjectException(projProjectPKs[i].toString());
				}

				if (userHBM.getProjProjects().add(projProjectHBM)) {
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

	public boolean addProjProjects(String pk, List projProjects)
		throws NoSuchUserException, 
			com.liferay.portlet.project.NoSuchProjectException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < projProjects.size(); i++) {
				com.liferay.portlet.project.model.ProjProject projProject = (com.liferay.portlet.project.model.ProjProject)projProjects.get(i);
				com.liferay.portlet.project.service.persistence.ProjProjectHBM projProjectHBM =
					(com.liferay.portlet.project.service.persistence.ProjProjectHBM)session.get(com.liferay.portlet.project.service.persistence.ProjProjectHBM.class,
						projProject.getPrimaryKey());

				if (projProjectHBM == null) {
					_log.warn("No ProjProject exists with the primary key of " +
						projProject.getPrimaryKey().toString());
					throw new com.liferay.portlet.project.NoSuchProjectException(projProject.getPrimaryKey()
																							.toString());
				}

				if (userHBM.getProjProjects().add(projProjectHBM)) {
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

	public void clearProjProjects(String pk)
		throws NoSuchUserException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			userHBM.getProjProjects().clear();
			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean containsProjProject(String pk, String projProjectPK)
		throws NoSuchUserException, 
			com.liferay.portlet.project.NoSuchProjectException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			com.liferay.portlet.project.service.persistence.ProjProjectHBM projProjectHBM =
				null;
			projProjectHBM = (com.liferay.portlet.project.service.persistence.ProjProjectHBM)session.get(com.liferay.portlet.project.service.persistence.ProjProjectHBM.class,
					projProjectPK);

			if (projProjectHBM == null) {
				_log.warn("No ProjProject exists with the primary key of " +
					projProjectPK.toString());
				throw new com.liferay.portlet.project.NoSuchProjectException(projProjectPK.toString());
			}

			Collection c = userHBM.getProjProjects();

			return c.contains(projProjectHBM);
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean containsProjProject(String pk,
		com.liferay.portlet.project.model.ProjProject projProject)
		throws NoSuchUserException, 
			com.liferay.portlet.project.NoSuchProjectException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			com.liferay.portlet.project.service.persistence.ProjProjectHBM projProjectHBM =
				null;
			projProjectHBM = (com.liferay.portlet.project.service.persistence.ProjProjectHBM)session.get(com.liferay.portlet.project.service.persistence.ProjProjectHBM.class,
					projProject.getPrimaryKey());

			if (projProjectHBM == null) {
				_log.warn("No ProjProject exists with the primary key of " +
					projProject.getPrimaryKey().toString());
				throw new com.liferay.portlet.project.NoSuchProjectException(projProject.getPrimaryKey()
																						.toString());
			}

			Collection c = userHBM.getProjProjects();

			return c.contains(projProjectHBM);
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean removeProjProject(String pk, String projProjectPK)
		throws NoSuchUserException, 
			com.liferay.portlet.project.NoSuchProjectException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			com.liferay.portlet.project.service.persistence.ProjProjectHBM projProjectHBM =
				null;
			projProjectHBM = (com.liferay.portlet.project.service.persistence.ProjProjectHBM)session.get(com.liferay.portlet.project.service.persistence.ProjProjectHBM.class,
					projProjectPK);

			if (projProjectHBM == null) {
				_log.warn("No ProjProject exists with the primary key of " +
					projProjectPK.toString());
				throw new com.liferay.portlet.project.NoSuchProjectException(projProjectPK.toString());
			}

			boolean value = userHBM.getProjProjects().remove(projProjectHBM);
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

	public boolean removeProjProject(String pk,
		com.liferay.portlet.project.model.ProjProject projProject)
		throws NoSuchUserException, 
			com.liferay.portlet.project.NoSuchProjectException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			com.liferay.portlet.project.service.persistence.ProjProjectHBM projProjectHBM =
				null;
			projProjectHBM = (com.liferay.portlet.project.service.persistence.ProjProjectHBM)session.get(com.liferay.portlet.project.service.persistence.ProjProjectHBM.class,
					projProject.getPrimaryKey());

			if (projProjectHBM == null) {
				_log.warn("No ProjProject exists with the primary key of " +
					projProject.getPrimaryKey().toString());
				throw new com.liferay.portlet.project.NoSuchProjectException(projProject.getPrimaryKey()
																						.toString());
			}

			boolean value = userHBM.getProjProjects().remove(projProjectHBM);
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

	public boolean removeProjProjects(String pk, String[] projProjectPKs)
		throws NoSuchUserException, 
			com.liferay.portlet.project.NoSuchProjectException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < projProjectPKs.length; i++) {
				com.liferay.portlet.project.service.persistence.ProjProjectHBM projProjectHBM =
					null;
				projProjectHBM = (com.liferay.portlet.project.service.persistence.ProjProjectHBM)session.get(com.liferay.portlet.project.service.persistence.ProjProjectHBM.class,
						projProjectPKs[i]);

				if (projProjectHBM == null) {
					_log.warn("No ProjProject exists with the primary key of " +
						projProjectPKs[i].toString());
					throw new com.liferay.portlet.project.NoSuchProjectException(projProjectPKs[i].toString());
				}

				if (userHBM.getProjProjects().remove(projProjectHBM)) {
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

	public boolean removeProjProjects(String pk, List projProjects)
		throws NoSuchUserException, 
			com.liferay.portlet.project.NoSuchProjectException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < projProjects.size(); i++) {
				com.liferay.portlet.project.model.ProjProject projProject = (com.liferay.portlet.project.model.ProjProject)projProjects.get(i);
				com.liferay.portlet.project.service.persistence.ProjProjectHBM projProjectHBM =
					(com.liferay.portlet.project.service.persistence.ProjProjectHBM)session.get(com.liferay.portlet.project.service.persistence.ProjProjectHBM.class,
						projProject.getPrimaryKey());

				if (projProjectHBM == null) {
					_log.warn("No ProjProject exists with the primary key of " +
						projProject.getPrimaryKey().toString());
					throw new com.liferay.portlet.project.NoSuchProjectException(projProject.getPrimaryKey()
																							.toString());
				}

				if (userHBM.getProjProjects().remove(projProjectHBM)) {
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

	public List getProjTasks(String pk)
		throws NoSuchUserException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT projTaskHBM FROM ");
			query.append(com.liferay.portal.service.persistence.UserHBM.class.getName());
			query.append(" userHBM ");
			query.append("JOIN userHBM.projTasks AS projTaskHBM ");
			query.append("WHERE userHBM.userId = ? ");
			query.append("ORDER BY ");
			query.append("projTaskHBM.estimatedEndDate ASC").append(", ");
			query.append("projTaskHBM.name ASC");

			Query q = session.createQuery(query.toString());
			q.setString(0, pk);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				com.liferay.portlet.project.service.persistence.ProjTaskHBM projTaskHBM =
					(com.liferay.portlet.project.service.persistence.ProjTaskHBM)itr.next();
				list.add(com.liferay.portlet.project.service.persistence.ProjTaskHBMUtil.model(
						projTaskHBM));
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

	public List getProjTasks(String pk, int begin, int end)
		throws NoSuchUserException, SystemException {
		return getProjTasks(pk, begin, end, null);
	}

	public List getProjTasks(String pk, int begin, int end,
		OrderByComparator obc) throws NoSuchUserException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT projTaskHBM FROM ");
			query.append(com.liferay.portal.service.persistence.UserHBM.class.getName());
			query.append(" userHBM ");
			query.append("JOIN userHBM.projTasks AS projTaskHBM ");
			query.append("WHERE userHBM.userId = ? ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("projTaskHBM.estimatedEndDate ASC").append(", ");
				query.append("projTaskHBM.name ASC");
			}

			Query q = session.createQuery(query.toString());
			q.setString(0, pk);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					com.liferay.portlet.project.service.persistence.ProjTaskHBM projTaskHBM =
						(com.liferay.portlet.project.service.persistence.ProjTaskHBM)itr.next();
					list.add(com.liferay.portlet.project.service.persistence.ProjTaskHBMUtil.model(
							projTaskHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						com.liferay.portlet.project.service.persistence.ProjTaskHBM projTaskHBM =
							(com.liferay.portlet.project.service.persistence.ProjTaskHBM)sr.get(0);
						list.add(com.liferay.portlet.project.service.persistence.ProjTaskHBMUtil.model(
								projTaskHBM));

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

	public int getProjTasksSize(String pk) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) FROM ");
			query.append(com.liferay.portal.service.persistence.UserHBM.class.getName());
			query.append(" userHBM ");
			query.append("JOIN userHBM.projTasks AS projTaskHBM ");
			query.append("WHERE userHBM.userId = ? ");

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

	public void setProjTasks(String pk, String[] pks)
		throws NoSuchUserException, 
			com.liferay.portlet.project.NoSuchTaskException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			Set projTasksSet = new HashSet();

			for (int i = 0; (pks != null) && (i < pks.length); i++) {
				com.liferay.portlet.project.service.persistence.ProjTaskHBM projTaskHBM =
					(com.liferay.portlet.project.service.persistence.ProjTaskHBM)session.get(com.liferay.portlet.project.service.persistence.ProjTaskHBM.class,
						pks[i]);

				if (projTaskHBM == null) {
					_log.warn("No ProjTask exists with the primary key of " +
						pks[i].toString());
					throw new com.liferay.portlet.project.NoSuchTaskException(pks[i].toString());
				}

				projTasksSet.add(projTaskHBM);
			}

			userHBM.setProjTasks(projTasksSet);
			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void setProjTasks(String pk, List projTasks)
		throws NoSuchUserException, 
			com.liferay.portlet.project.NoSuchTaskException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			Set projTasksSet = new HashSet();
			Iterator itr = projTasks.iterator();

			while (itr.hasNext()) {
				com.liferay.portlet.project.model.ProjTask projTask = (com.liferay.portlet.project.model.ProjTask)itr.next();
				com.liferay.portlet.project.service.persistence.ProjTaskHBM projTaskHBM =
					(com.liferay.portlet.project.service.persistence.ProjTaskHBM)session.get(com.liferay.portlet.project.service.persistence.ProjTaskHBM.class,
						projTask.getPrimaryKey());

				if (projTaskHBM == null) {
					_log.warn("No ProjTask exists with the primary key of " +
						projTask.getPrimaryKey().toString());
					throw new com.liferay.portlet.project.NoSuchTaskException(projTask.getPrimaryKey()
																					  .toString());
				}

				projTasksSet.add(projTaskHBM);
			}

			userHBM.setProjTasks(projTasksSet);
			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean addProjTask(String pk, String projTaskPK)
		throws NoSuchUserException, 
			com.liferay.portlet.project.NoSuchTaskException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			com.liferay.portlet.project.service.persistence.ProjTaskHBM projTaskHBM =
				null;
			projTaskHBM = (com.liferay.portlet.project.service.persistence.ProjTaskHBM)session.get(com.liferay.portlet.project.service.persistence.ProjTaskHBM.class,
					projTaskPK);

			if (projTaskHBM == null) {
				_log.warn("No ProjTask exists with the primary key of " +
					projTaskPK.toString());
				throw new com.liferay.portlet.project.NoSuchTaskException(projTaskPK.toString());
			}

			boolean value = userHBM.getProjTasks().add(projTaskHBM);
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

	public boolean addProjTask(String pk,
		com.liferay.portlet.project.model.ProjTask projTask)
		throws NoSuchUserException, 
			com.liferay.portlet.project.NoSuchTaskException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			com.liferay.portlet.project.service.persistence.ProjTaskHBM projTaskHBM =
				null;
			projTaskHBM = (com.liferay.portlet.project.service.persistence.ProjTaskHBM)session.get(com.liferay.portlet.project.service.persistence.ProjTaskHBM.class,
					projTask.getPrimaryKey());

			if (projTaskHBM == null) {
				_log.warn("No ProjTask exists with the primary key of " +
					projTask.getPrimaryKey().toString());
				throw new com.liferay.portlet.project.NoSuchTaskException(projTask.getPrimaryKey()
																				  .toString());
			}

			boolean value = userHBM.getProjTasks().add(projTaskHBM);
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

	public boolean addProjTasks(String pk, String[] projTaskPKs)
		throws NoSuchUserException, 
			com.liferay.portlet.project.NoSuchTaskException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < projTaskPKs.length; i++) {
				com.liferay.portlet.project.service.persistence.ProjTaskHBM projTaskHBM =
					null;
				projTaskHBM = (com.liferay.portlet.project.service.persistence.ProjTaskHBM)session.get(com.liferay.portlet.project.service.persistence.ProjTaskHBM.class,
						projTaskPKs[i]);

				if (projTaskHBM == null) {
					_log.warn("No ProjTask exists with the primary key of " +
						projTaskPKs[i].toString());
					throw new com.liferay.portlet.project.NoSuchTaskException(projTaskPKs[i].toString());
				}

				if (userHBM.getProjTasks().add(projTaskHBM)) {
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

	public boolean addProjTasks(String pk, List projTasks)
		throws NoSuchUserException, 
			com.liferay.portlet.project.NoSuchTaskException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < projTasks.size(); i++) {
				com.liferay.portlet.project.model.ProjTask projTask = (com.liferay.portlet.project.model.ProjTask)projTasks.get(i);
				com.liferay.portlet.project.service.persistence.ProjTaskHBM projTaskHBM =
					(com.liferay.portlet.project.service.persistence.ProjTaskHBM)session.get(com.liferay.portlet.project.service.persistence.ProjTaskHBM.class,
						projTask.getPrimaryKey());

				if (projTaskHBM == null) {
					_log.warn("No ProjTask exists with the primary key of " +
						projTask.getPrimaryKey().toString());
					throw new com.liferay.portlet.project.NoSuchTaskException(projTask.getPrimaryKey()
																					  .toString());
				}

				if (userHBM.getProjTasks().add(projTaskHBM)) {
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

	public void clearProjTasks(String pk)
		throws NoSuchUserException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			userHBM.getProjTasks().clear();
			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean containsProjTask(String pk, String projTaskPK)
		throws NoSuchUserException, 
			com.liferay.portlet.project.NoSuchTaskException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			com.liferay.portlet.project.service.persistence.ProjTaskHBM projTaskHBM =
				null;
			projTaskHBM = (com.liferay.portlet.project.service.persistence.ProjTaskHBM)session.get(com.liferay.portlet.project.service.persistence.ProjTaskHBM.class,
					projTaskPK);

			if (projTaskHBM == null) {
				_log.warn("No ProjTask exists with the primary key of " +
					projTaskPK.toString());
				throw new com.liferay.portlet.project.NoSuchTaskException(projTaskPK.toString());
			}

			Collection c = userHBM.getProjTasks();

			return c.contains(projTaskHBM);
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean containsProjTask(String pk,
		com.liferay.portlet.project.model.ProjTask projTask)
		throws NoSuchUserException, 
			com.liferay.portlet.project.NoSuchTaskException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			com.liferay.portlet.project.service.persistence.ProjTaskHBM projTaskHBM =
				null;
			projTaskHBM = (com.liferay.portlet.project.service.persistence.ProjTaskHBM)session.get(com.liferay.portlet.project.service.persistence.ProjTaskHBM.class,
					projTask.getPrimaryKey());

			if (projTaskHBM == null) {
				_log.warn("No ProjTask exists with the primary key of " +
					projTask.getPrimaryKey().toString());
				throw new com.liferay.portlet.project.NoSuchTaskException(projTask.getPrimaryKey()
																				  .toString());
			}

			Collection c = userHBM.getProjTasks();

			return c.contains(projTaskHBM);
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean removeProjTask(String pk, String projTaskPK)
		throws NoSuchUserException, 
			com.liferay.portlet.project.NoSuchTaskException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			com.liferay.portlet.project.service.persistence.ProjTaskHBM projTaskHBM =
				null;
			projTaskHBM = (com.liferay.portlet.project.service.persistence.ProjTaskHBM)session.get(com.liferay.portlet.project.service.persistence.ProjTaskHBM.class,
					projTaskPK);

			if (projTaskHBM == null) {
				_log.warn("No ProjTask exists with the primary key of " +
					projTaskPK.toString());
				throw new com.liferay.portlet.project.NoSuchTaskException(projTaskPK.toString());
			}

			boolean value = userHBM.getProjTasks().remove(projTaskHBM);
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

	public boolean removeProjTask(String pk,
		com.liferay.portlet.project.model.ProjTask projTask)
		throws NoSuchUserException, 
			com.liferay.portlet.project.NoSuchTaskException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			com.liferay.portlet.project.service.persistence.ProjTaskHBM projTaskHBM =
				null;
			projTaskHBM = (com.liferay.portlet.project.service.persistence.ProjTaskHBM)session.get(com.liferay.portlet.project.service.persistence.ProjTaskHBM.class,
					projTask.getPrimaryKey());

			if (projTaskHBM == null) {
				_log.warn("No ProjTask exists with the primary key of " +
					projTask.getPrimaryKey().toString());
				throw new com.liferay.portlet.project.NoSuchTaskException(projTask.getPrimaryKey()
																				  .toString());
			}

			boolean value = userHBM.getProjTasks().remove(projTaskHBM);
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

	public boolean removeProjTasks(String pk, String[] projTaskPKs)
		throws NoSuchUserException, 
			com.liferay.portlet.project.NoSuchTaskException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < projTaskPKs.length; i++) {
				com.liferay.portlet.project.service.persistence.ProjTaskHBM projTaskHBM =
					null;
				projTaskHBM = (com.liferay.portlet.project.service.persistence.ProjTaskHBM)session.get(com.liferay.portlet.project.service.persistence.ProjTaskHBM.class,
						projTaskPKs[i]);

				if (projTaskHBM == null) {
					_log.warn("No ProjTask exists with the primary key of " +
						projTaskPKs[i].toString());
					throw new com.liferay.portlet.project.NoSuchTaskException(projTaskPKs[i].toString());
				}

				if (userHBM.getProjTasks().remove(projTaskHBM)) {
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

	public boolean removeProjTasks(String pk, List projTasks)
		throws NoSuchUserException, 
			com.liferay.portlet.project.NoSuchTaskException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserHBM userHBM = (UserHBM)session.get(UserHBM.class, pk);

			if (userHBM == null) {
				_log.warn("No User exists with the primary key of " +
					pk.toString());
				throw new NoSuchUserException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < projTasks.size(); i++) {
				com.liferay.portlet.project.model.ProjTask projTask = (com.liferay.portlet.project.model.ProjTask)projTasks.get(i);
				com.liferay.portlet.project.service.persistence.ProjTaskHBM projTaskHBM =
					(com.liferay.portlet.project.service.persistence.ProjTaskHBM)session.get(com.liferay.portlet.project.service.persistence.ProjTaskHBM.class,
						projTask.getPrimaryKey());

				if (projTaskHBM == null) {
					_log.warn("No ProjTask exists with the primary key of " +
						projTask.getPrimaryKey().toString());
					throw new com.liferay.portlet.project.NoSuchTaskException(projTask.getPrimaryKey()
																					  .toString());
				}

				if (userHBM.getProjTasks().remove(projTaskHBM)) {
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

	public com.liferay.portal.model.User findByPrimaryKey(String userId)
		throws NoSuchUserException, SystemException {
		com.liferay.portal.model.User user = UserPool.get(userId);
		Session session = null;

		try {
			if (user == null) {
				session = openSession();

				UserHBM userHBM = (UserHBM)session.get(UserHBM.class, userId);

				if (userHBM == null) {
					_log.warn("No User exists with the primary key of " +
						userId.toString());
					throw new NoSuchUserException(userId.toString());
				}

				user = UserHBMUtil.model(userHBM);
			}

			return user;
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
				"FROM User_ IN CLASS com.liferay.portal.service.persistence.UserHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("firstName ASC").append(", ");
			query.append("middleName ASC").append(", ");
			query.append("lastName ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				UserHBM userHBM = (UserHBM)itr.next();
				list.add(UserHBMUtil.model(userHBM));
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
				"FROM User_ IN CLASS com.liferay.portal.service.persistence.UserHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("firstName ASC").append(", ");
				query.append("middleName ASC").append(", ");
				query.append("lastName ASC");
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
					UserHBM userHBM = (UserHBM)itr.next();
					list.add(UserHBMUtil.model(userHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						UserHBM userHBM = (UserHBM)sr.get(0);
						list.add(UserHBMUtil.model(userHBM));

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

	public com.liferay.portal.model.User findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchUserException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchUserException();
		}
		else {
			return (com.liferay.portal.model.User)list.get(0);
		}
	}

	public com.liferay.portal.model.User findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchUserException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchUserException();
		}
		else {
			return (com.liferay.portal.model.User)list.get(0);
		}
	}

	public com.liferay.portal.model.User[] findByCompanyId_PrevAndNext(
		String userId, String companyId, OrderByComparator obc)
		throws NoSuchUserException, SystemException {
		com.liferay.portal.model.User user = findByPrimaryKey(userId);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM User_ IN CLASS com.liferay.portal.service.persistence.UserHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("firstName ASC").append(", ");
				query.append("middleName ASC").append(", ");
				query.append("lastName ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portal.model.User[] array = new com.liferay.portal.model.User[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					UserHBM userHBM = (UserHBM)sr.get(0);

					if (userHBM == null) {
						break;
					}

					com.liferay.portal.model.User curUser = UserHBMUtil.model(userHBM);
					int value = obc.compare(user, curUser);

					if (value == 0) {
						if (!user.equals(curUser)) {
							break;
						}

						array[1] = curUser;

						if (sr.previous()) {
							array[0] = UserHBMUtil.model((UserHBM)sr.get(0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = UserHBMUtil.model((UserHBM)sr.get(0));
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

	public com.liferay.portal.model.User findByC_U(String companyId,
		String userId) throws NoSuchUserException, SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM User_ IN CLASS com.liferay.portal.service.persistence.UserHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("firstName ASC").append(", ");
			query.append("middleName ASC").append(", ");
			query.append("lastName ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			if (!itr.hasNext()) {
				throw new NoSuchUserException();
			}

			UserHBM userHBM = (UserHBM)itr.next();

			return UserHBMUtil.model(userHBM);
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByC_P(String companyId, String password)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM User_ IN CLASS com.liferay.portal.service.persistence.UserHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("password_ = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("firstName ASC").append(", ");
			query.append("middleName ASC").append(", ");
			query.append("lastName ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, password);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				UserHBM userHBM = (UserHBM)itr.next();
				list.add(UserHBMUtil.model(userHBM));
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

	public List findByC_P(String companyId, String password, int begin, int end)
		throws SystemException {
		return findByC_P(companyId, password, begin, end, null);
	}

	public List findByC_P(String companyId, String password, int begin,
		int end, OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM User_ IN CLASS com.liferay.portal.service.persistence.UserHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("password_ = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("firstName ASC").append(", ");
				query.append("middleName ASC").append(", ");
				query.append("lastName ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, password);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					UserHBM userHBM = (UserHBM)itr.next();
					list.add(UserHBMUtil.model(userHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						UserHBM userHBM = (UserHBM)sr.get(0);
						list.add(UserHBMUtil.model(userHBM));

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

	public com.liferay.portal.model.User findByC_P_First(String companyId,
		String password, OrderByComparator obc)
		throws NoSuchUserException, SystemException {
		List list = findByC_P(companyId, password, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchUserException();
		}
		else {
			return (com.liferay.portal.model.User)list.get(0);
		}
	}

	public com.liferay.portal.model.User findByC_P_Last(String companyId,
		String password, OrderByComparator obc)
		throws NoSuchUserException, SystemException {
		int count = countByC_P(companyId, password);
		List list = findByC_P(companyId, password, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchUserException();
		}
		else {
			return (com.liferay.portal.model.User)list.get(0);
		}
	}

	public com.liferay.portal.model.User[] findByC_P_PrevAndNext(
		String userId, String companyId, String password, OrderByComparator obc)
		throws NoSuchUserException, SystemException {
		com.liferay.portal.model.User user = findByPrimaryKey(userId);
		int count = countByC_P(companyId, password);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM User_ IN CLASS com.liferay.portal.service.persistence.UserHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("password_ = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("firstName ASC").append(", ");
				query.append("middleName ASC").append(", ");
				query.append("lastName ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, password);

			com.liferay.portal.model.User[] array = new com.liferay.portal.model.User[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					UserHBM userHBM = (UserHBM)sr.get(0);

					if (userHBM == null) {
						break;
					}

					com.liferay.portal.model.User curUser = UserHBMUtil.model(userHBM);
					int value = obc.compare(user, curUser);

					if (value == 0) {
						if (!user.equals(curUser)) {
							break;
						}

						array[1] = curUser;

						if (sr.previous()) {
							array[0] = UserHBMUtil.model((UserHBM)sr.get(0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = UserHBMUtil.model((UserHBM)sr.get(0));
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

	public com.liferay.portal.model.User findByC_EA(String companyId,
		String emailAddress) throws NoSuchUserException, SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM User_ IN CLASS com.liferay.portal.service.persistence.UserHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("emailAddress = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("firstName ASC").append(", ");
			query.append("middleName ASC").append(", ");
			query.append("lastName ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, emailAddress);

			Iterator itr = q.list().iterator();

			if (!itr.hasNext()) {
				throw new NoSuchUserException();
			}

			UserHBM userHBM = (UserHBM)itr.next();

			return UserHBMUtil.model(userHBM);
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
				"FROM User_ IN CLASS com.liferay.portal.service.persistence.UserHBM ");
			query.append("ORDER BY ");
			query.append("firstName ASC").append(", ");
			query.append("middleName ASC").append(", ");
			query.append("lastName ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				UserHBM userHBM = (UserHBM)itr.next();
				list.add(UserHBMUtil.model(userHBM));
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
				"FROM User_ IN CLASS com.liferay.portal.service.persistence.UserHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("firstName ASC").append(", ");
			query.append("middleName ASC").append(", ");
			query.append("lastName ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				UserHBM userHBM = (UserHBM)itr.next();
				UserPool.remove((String)userHBM.getPrimaryKey());
				session.delete(userHBM);
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

	public void removeByC_U(String companyId, String userId)
		throws NoSuchUserException, SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM User_ IN CLASS com.liferay.portal.service.persistence.UserHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("firstName ASC").append(", ");
			query.append("middleName ASC").append(", ");
			query.append("lastName ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				UserHBM userHBM = (UserHBM)itr.next();
				UserPool.remove((String)userHBM.getPrimaryKey());
				session.delete(userHBM);
			}

			session.flush();
		}
		catch (HibernateException he) {
			if (he instanceof ObjectNotFoundException) {
				throw new NoSuchUserException();
			}
			else {
				throw new SystemException(he);
			}
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void removeByC_P(String companyId, String password)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM User_ IN CLASS com.liferay.portal.service.persistence.UserHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("password_ = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("firstName ASC").append(", ");
			query.append("middleName ASC").append(", ");
			query.append("lastName ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, password);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				UserHBM userHBM = (UserHBM)itr.next();
				UserPool.remove((String)userHBM.getPrimaryKey());
				session.delete(userHBM);
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

	public void removeByC_EA(String companyId, String emailAddress)
		throws NoSuchUserException, SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM User_ IN CLASS com.liferay.portal.service.persistence.UserHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("emailAddress = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("firstName ASC").append(", ");
			query.append("middleName ASC").append(", ");
			query.append("lastName ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, emailAddress);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				UserHBM userHBM = (UserHBM)itr.next();
				UserPool.remove((String)userHBM.getPrimaryKey());
				session.delete(userHBM);
			}

			session.flush();
		}
		catch (HibernateException he) {
			if (he instanceof ObjectNotFoundException) {
				throw new NoSuchUserException();
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
				"FROM User_ IN CLASS com.liferay.portal.service.persistence.UserHBM WHERE ");
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

	public int countByC_U(String companyId, String userId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM User_ IN CLASS com.liferay.portal.service.persistence.UserHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
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

	public int countByC_P(String companyId, String password)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM User_ IN CLASS com.liferay.portal.service.persistence.UserHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("password_ = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, password);

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

	public int countByC_EA(String companyId, String emailAddress)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM User_ IN CLASS com.liferay.portal.service.persistence.UserHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("emailAddress = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, emailAddress);

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

	private static final Log _log = LogFactory.getLog(UserPersistence.class);
}