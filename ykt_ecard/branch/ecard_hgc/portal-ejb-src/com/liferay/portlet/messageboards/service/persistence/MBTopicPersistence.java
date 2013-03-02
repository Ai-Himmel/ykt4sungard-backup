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

package com.liferay.portlet.messageboards.service.persistence;

import com.liferay.portal.SystemException;
import com.liferay.portal.service.persistence.BasePersistence;
import com.liferay.portal.util.HibernateUtil;

import com.liferay.portlet.messageboards.NoSuchTopicException;

import com.liferay.util.StringPool;
import com.liferay.util.dao.hibernate.OrderByComparator;
import com.liferay.util.lang.FastStringBuffer;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.ScrollableResults;
import org.hibernate.Session;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="MBTopicPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class MBTopicPersistence extends BasePersistence {
	public com.liferay.portlet.messageboards.model.MBTopic create(
		String topicId) {
		return new com.liferay.portlet.messageboards.model.MBTopic(topicId);
	}

	public com.liferay.portlet.messageboards.model.MBTopic remove(
		String topicId) throws NoSuchTopicException, SystemException {
		Session session = null;

		try {
			session = openSession();

			MBTopicHBM mbTopicHBM = (MBTopicHBM)session.get(MBTopicHBM.class,
					topicId);

			if (mbTopicHBM == null) {
				_log.warn("No MBTopic exists with the primary key of " +
					topicId.toString());
				throw new NoSuchTopicException(topicId.toString());
			}

			com.liferay.portlet.messageboards.model.MBTopic mbTopic = MBTopicHBMUtil.model(mbTopicHBM);
			session.delete(mbTopicHBM);
			session.flush();
			MBTopicPool.remove(topicId);

			return mbTopic;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.messageboards.model.MBTopic update(
		com.liferay.portlet.messageboards.model.MBTopic mbTopic)
		throws SystemException {
		Session session = null;

		try {
			if (mbTopic.isNew() || mbTopic.isModified()) {
				session = openSession();

				if (mbTopic.isNew()) {
					MBTopicHBM mbTopicHBM = new MBTopicHBM(mbTopic.getTopicId(),
							mbTopic.getPortletId(), mbTopic.getGroupId(),
							mbTopic.getCompanyId(), mbTopic.getUserId(),
							mbTopic.getUserName(), mbTopic.getCreateDate(),
							mbTopic.getModifiedDate(), mbTopic.getReadRoles(),
							mbTopic.getWriteRoles(), mbTopic.getName(),
							mbTopic.getDescription(), mbTopic.getLastPostDate());
					session.save(mbTopicHBM);
					session.flush();
				}
				else {
					MBTopicHBM mbTopicHBM = (MBTopicHBM)session.get(MBTopicHBM.class,
							mbTopic.getPrimaryKey());

					if (mbTopicHBM != null) {
						mbTopicHBM.setPortletId(mbTopic.getPortletId());
						mbTopicHBM.setGroupId(mbTopic.getGroupId());
						mbTopicHBM.setCompanyId(mbTopic.getCompanyId());
						mbTopicHBM.setUserId(mbTopic.getUserId());
						mbTopicHBM.setUserName(mbTopic.getUserName());
						mbTopicHBM.setCreateDate(mbTopic.getCreateDate());
						mbTopicHBM.setModifiedDate(mbTopic.getModifiedDate());
						mbTopicHBM.setReadRoles(mbTopic.getReadRoles());
						mbTopicHBM.setWriteRoles(mbTopic.getWriteRoles());
						mbTopicHBM.setName(mbTopic.getName());
						mbTopicHBM.setDescription(mbTopic.getDescription());
						mbTopicHBM.setLastPostDate(mbTopic.getLastPostDate());
						session.flush();
					}
					else {
						mbTopicHBM = new MBTopicHBM(mbTopic.getTopicId(),
								mbTopic.getPortletId(), mbTopic.getGroupId(),
								mbTopic.getCompanyId(), mbTopic.getUserId(),
								mbTopic.getUserName(), mbTopic.getCreateDate(),
								mbTopic.getModifiedDate(),
								mbTopic.getReadRoles(),
								mbTopic.getWriteRoles(), mbTopic.getName(),
								mbTopic.getDescription(),
								mbTopic.getLastPostDate());
						session.save(mbTopicHBM);
						session.flush();
					}
				}

				mbTopic.setNew(false);
				mbTopic.setModified(false);
				mbTopic.protect();
				MBTopicPool.put(mbTopic.getPrimaryKey(), mbTopic);
			}

			return mbTopic;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.messageboards.model.MBTopic findByPrimaryKey(
		String topicId) throws NoSuchTopicException, SystemException {
		com.liferay.portlet.messageboards.model.MBTopic mbTopic = MBTopicPool.get(topicId);
		Session session = null;

		try {
			if (mbTopic == null) {
				session = openSession();

				MBTopicHBM mbTopicHBM = (MBTopicHBM)session.get(MBTopicHBM.class,
						topicId);

				if (mbTopicHBM == null) {
					_log.warn("No MBTopic exists with the primary key of " +
						topicId.toString());
					throw new NoSuchTopicException(topicId.toString());
				}

				mbTopic = MBTopicHBMUtil.model(mbTopicHBM);
			}

			return mbTopic;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByGroupId(String groupId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBTopic IN CLASS com.liferay.portlet.messageboards.service.persistence.MBTopicHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				MBTopicHBM mbTopicHBM = (MBTopicHBM)itr.next();
				list.add(MBTopicHBMUtil.model(mbTopicHBM));
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

	public List findByGroupId(String groupId, int begin, int end)
		throws SystemException {
		return findByGroupId(groupId, begin, end, null);
	}

	public List findByGroupId(String groupId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBTopic IN CLASS com.liferay.portlet.messageboards.service.persistence.MBTopicHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					MBTopicHBM mbTopicHBM = (MBTopicHBM)itr.next();
					list.add(MBTopicHBMUtil.model(mbTopicHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						MBTopicHBM mbTopicHBM = (MBTopicHBM)sr.get(0);
						list.add(MBTopicHBMUtil.model(mbTopicHBM));

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

	public com.liferay.portlet.messageboards.model.MBTopic findByGroupId_First(
		String groupId, OrderByComparator obc)
		throws NoSuchTopicException, SystemException {
		List list = findByGroupId(groupId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchTopicException();
		}
		else {
			return (com.liferay.portlet.messageboards.model.MBTopic)list.get(0);
		}
	}

	public com.liferay.portlet.messageboards.model.MBTopic findByGroupId_Last(
		String groupId, OrderByComparator obc)
		throws NoSuchTopicException, SystemException {
		int count = countByGroupId(groupId);
		List list = findByGroupId(groupId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchTopicException();
		}
		else {
			return (com.liferay.portlet.messageboards.model.MBTopic)list.get(0);
		}
	}

	public com.liferay.portlet.messageboards.model.MBTopic[] findByGroupId_PrevAndNext(
		String topicId, String groupId, OrderByComparator obc)
		throws NoSuchTopicException, SystemException {
		com.liferay.portlet.messageboards.model.MBTopic mbTopic = findByPrimaryKey(topicId);
		int count = countByGroupId(groupId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBTopic IN CLASS com.liferay.portlet.messageboards.service.persistence.MBTopicHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

			com.liferay.portlet.messageboards.model.MBTopic[] array = new com.liferay.portlet.messageboards.model.MBTopic[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					MBTopicHBM mbTopicHBM = (MBTopicHBM)sr.get(0);

					if (mbTopicHBM == null) {
						break;
					}

					com.liferay.portlet.messageboards.model.MBTopic curMBTopic = MBTopicHBMUtil.model(mbTopicHBM);
					int value = obc.compare(mbTopic, curMBTopic);

					if (value == 0) {
						if (!mbTopic.equals(curMBTopic)) {
							break;
						}

						array[1] = curMBTopic;

						if (sr.previous()) {
							array[0] = MBTopicHBMUtil.model((MBTopicHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = MBTopicHBMUtil.model((MBTopicHBM)sr.get(
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

	public List findByCompanyId(String companyId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBTopic IN CLASS com.liferay.portlet.messageboards.service.persistence.MBTopicHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				MBTopicHBM mbTopicHBM = (MBTopicHBM)itr.next();
				list.add(MBTopicHBMUtil.model(mbTopicHBM));
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
				"FROM MBTopic IN CLASS com.liferay.portlet.messageboards.service.persistence.MBTopicHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate DESC");
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
					MBTopicHBM mbTopicHBM = (MBTopicHBM)itr.next();
					list.add(MBTopicHBMUtil.model(mbTopicHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						MBTopicHBM mbTopicHBM = (MBTopicHBM)sr.get(0);
						list.add(MBTopicHBMUtil.model(mbTopicHBM));

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

	public com.liferay.portlet.messageboards.model.MBTopic findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchTopicException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchTopicException();
		}
		else {
			return (com.liferay.portlet.messageboards.model.MBTopic)list.get(0);
		}
	}

	public com.liferay.portlet.messageboards.model.MBTopic findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchTopicException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchTopicException();
		}
		else {
			return (com.liferay.portlet.messageboards.model.MBTopic)list.get(0);
		}
	}

	public com.liferay.portlet.messageboards.model.MBTopic[] findByCompanyId_PrevAndNext(
		String topicId, String companyId, OrderByComparator obc)
		throws NoSuchTopicException, SystemException {
		com.liferay.portlet.messageboards.model.MBTopic mbTopic = findByPrimaryKey(topicId);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBTopic IN CLASS com.liferay.portlet.messageboards.service.persistence.MBTopicHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portlet.messageboards.model.MBTopic[] array = new com.liferay.portlet.messageboards.model.MBTopic[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					MBTopicHBM mbTopicHBM = (MBTopicHBM)sr.get(0);

					if (mbTopicHBM == null) {
						break;
					}

					com.liferay.portlet.messageboards.model.MBTopic curMBTopic = MBTopicHBMUtil.model(mbTopicHBM);
					int value = obc.compare(mbTopic, curMBTopic);

					if (value == 0) {
						if (!mbTopic.equals(curMBTopic)) {
							break;
						}

						array[1] = curMBTopic;

						if (sr.previous()) {
							array[0] = MBTopicHBMUtil.model((MBTopicHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = MBTopicHBMUtil.model((MBTopicHBM)sr.get(
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

	public List findByP_G_C_R(String portletId, String groupId,
		String companyId, String[] readRolesArray) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBTopic IN CLASS com.liferay.portlet.messageboards.service.persistence.MBTopicHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("(");

			if (readRolesArray.length > 0) {
				for (int i = 0; i < readRolesArray.length; i++) {
					query.append("readRoles LIKE ?");
					query.append(" OR ");
					query.append("readRoles LIKE ?");

					if ((i + 1) != readRolesArray.length) {
						query.append(" OR ");
					}
				}
			}
			else {
				query.append("readRoles = ");
				query.append("readRoles");
			}

			query.append(")");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);

			for (int i = 0; i < readRolesArray.length; i++) {
				q.setString(queryPos++,
					readRolesArray[i] + StringPool.COMMA + StringPool.PERCENT);
				q.setString(queryPos++,
					StringPool.PERCENT + StringPool.COMMA + readRolesArray[i] +
					StringPool.COMMA + StringPool.PERCENT);
			}

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				MBTopicHBM mbTopicHBM = (MBTopicHBM)itr.next();
				list.add(MBTopicHBMUtil.model(mbTopicHBM));
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

	public List findByP_G_C_R(String portletId, String groupId,
		String companyId, String[] readRolesArray, int begin, int end)
		throws SystemException {
		return findByP_G_C_R(portletId, groupId, companyId, readRolesArray,
			begin, end, null);
	}

	public List findByP_G_C_R(String portletId, String groupId,
		String companyId, String[] readRolesArray, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBTopic IN CLASS com.liferay.portlet.messageboards.service.persistence.MBTopicHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("(");

			if (readRolesArray.length > 0) {
				for (int i = 0; i < readRolesArray.length; i++) {
					query.append("readRoles LIKE ?");
					query.append(" OR ");
					query.append("readRoles LIKE ?");

					if ((i + 1) != readRolesArray.length) {
						query.append(" OR ");
					}
				}
			}
			else {
				query.append("readRoles = ");
				query.append("readRoles");
			}

			query.append(")");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);

			for (int i = 0; i < readRolesArray.length; i++) {
				q.setString(queryPos++,
					readRolesArray[i] + StringPool.COMMA + StringPool.PERCENT);
				q.setString(queryPos++,
					StringPool.PERCENT + StringPool.COMMA + readRolesArray[i] +
					StringPool.COMMA + StringPool.PERCENT);
			}

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					MBTopicHBM mbTopicHBM = (MBTopicHBM)itr.next();
					list.add(MBTopicHBMUtil.model(mbTopicHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						MBTopicHBM mbTopicHBM = (MBTopicHBM)sr.get(0);
						list.add(MBTopicHBMUtil.model(mbTopicHBM));

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

	public com.liferay.portlet.messageboards.model.MBTopic findByP_G_C_R_First(
		String portletId, String groupId, String companyId,
		String[] readRolesArray, OrderByComparator obc)
		throws NoSuchTopicException, SystemException {
		List list = findByP_G_C_R(portletId, groupId, companyId,
				readRolesArray, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchTopicException();
		}
		else {
			return (com.liferay.portlet.messageboards.model.MBTopic)list.get(0);
		}
	}

	public com.liferay.portlet.messageboards.model.MBTopic findByP_G_C_R_Last(
		String portletId, String groupId, String companyId,
		String[] readRolesArray, OrderByComparator obc)
		throws NoSuchTopicException, SystemException {
		int count = countByP_G_C_R(portletId, groupId, companyId, readRolesArray);
		List list = findByP_G_C_R(portletId, groupId, companyId,
				readRolesArray, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchTopicException();
		}
		else {
			return (com.liferay.portlet.messageboards.model.MBTopic)list.get(0);
		}
	}

	public com.liferay.portlet.messageboards.model.MBTopic[] findByP_G_C_R_PrevAndNext(
		String topicId, String portletId, String groupId, String companyId,
		String[] readRolesArray, OrderByComparator obc)
		throws NoSuchTopicException, SystemException {
		com.liferay.portlet.messageboards.model.MBTopic mbTopic = findByPrimaryKey(topicId);
		int count = countByP_G_C_R(portletId, groupId, companyId, readRolesArray);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBTopic IN CLASS com.liferay.portlet.messageboards.service.persistence.MBTopicHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("(");

			if (readRolesArray.length > 0) {
				for (int i = 0; i < readRolesArray.length; i++) {
					query.append("readRoles LIKE ?");
					query.append(" OR ");
					query.append("readRoles LIKE ?");

					if ((i + 1) != readRolesArray.length) {
						query.append(" OR ");
					}
				}
			}
			else {
				query.append("readRoles = ");
				query.append("readRoles");
			}

			query.append(")");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);

			for (int i = 0; i < readRolesArray.length; i++) {
				q.setString(queryPos++,
					readRolesArray[i] + StringPool.COMMA + StringPool.PERCENT);
				q.setString(queryPos++,
					StringPool.PERCENT + StringPool.COMMA + readRolesArray[i] +
					StringPool.COMMA + StringPool.PERCENT);
			}

			com.liferay.portlet.messageboards.model.MBTopic[] array = new com.liferay.portlet.messageboards.model.MBTopic[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					MBTopicHBM mbTopicHBM = (MBTopicHBM)sr.get(0);

					if (mbTopicHBM == null) {
						break;
					}

					com.liferay.portlet.messageboards.model.MBTopic curMBTopic = MBTopicHBMUtil.model(mbTopicHBM);
					int value = obc.compare(mbTopic, curMBTopic);

					if (value == 0) {
						if (!mbTopic.equals(curMBTopic)) {
							break;
						}

						array[1] = curMBTopic;

						if (sr.previous()) {
							array[0] = MBTopicHBMUtil.model((MBTopicHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = MBTopicHBMUtil.model((MBTopicHBM)sr.get(
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
				"FROM MBTopic IN CLASS com.liferay.portlet.messageboards.service.persistence.MBTopicHBM ");
			query.append("ORDER BY ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				MBTopicHBM mbTopicHBM = (MBTopicHBM)itr.next();
				list.add(MBTopicHBMUtil.model(mbTopicHBM));
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

	public void removeByGroupId(String groupId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBTopic IN CLASS com.liferay.portlet.messageboards.service.persistence.MBTopicHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				MBTopicHBM mbTopicHBM = (MBTopicHBM)itr.next();
				MBTopicPool.remove((String)mbTopicHBM.getPrimaryKey());
				session.delete(mbTopicHBM);
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

	public void removeByCompanyId(String companyId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBTopic IN CLASS com.liferay.portlet.messageboards.service.persistence.MBTopicHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				MBTopicHBM mbTopicHBM = (MBTopicHBM)itr.next();
				MBTopicPool.remove((String)mbTopicHBM.getPrimaryKey());
				session.delete(mbTopicHBM);
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

	public void removeByP_G_C_R(String portletId, String groupId,
		String companyId, String[] readRolesArray) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBTopic IN CLASS com.liferay.portlet.messageboards.service.persistence.MBTopicHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("(");

			if (readRolesArray.length > 0) {
				for (int i = 0; i < readRolesArray.length; i++) {
					query.append("readRoles LIKE ?");
					query.append(" OR ");
					query.append("readRoles LIKE ?");

					if ((i + 1) != readRolesArray.length) {
						query.append(" OR ");
					}
				}
			}
			else {
				query.append("readRoles = ");
				query.append("readRoles");
			}

			query.append(")");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);

			for (int i = 0; i < readRolesArray.length; i++) {
				q.setString(queryPos++,
					readRolesArray[i] + StringPool.COMMA + StringPool.PERCENT);
				q.setString(queryPos++,
					StringPool.PERCENT + StringPool.COMMA + readRolesArray[i] +
					StringPool.COMMA + StringPool.PERCENT);
			}

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				MBTopicHBM mbTopicHBM = (MBTopicHBM)itr.next();
				MBTopicPool.remove((String)mbTopicHBM.getPrimaryKey());
				session.delete(mbTopicHBM);
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

	public int countByGroupId(String groupId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM MBTopic IN CLASS com.liferay.portlet.messageboards.service.persistence.MBTopicHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

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

	public int countByCompanyId(String companyId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM MBTopic IN CLASS com.liferay.portlet.messageboards.service.persistence.MBTopicHBM WHERE ");
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

	public int countByP_G_C_R(String portletId, String groupId,
		String companyId, String[] readRolesArray) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM MBTopic IN CLASS com.liferay.portlet.messageboards.service.persistence.MBTopicHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("(");

			if (readRolesArray.length > 0) {
				for (int i = 0; i < readRolesArray.length; i++) {
					query.append("readRoles LIKE ?");
					query.append(" OR ");
					query.append("readRoles LIKE ?");

					if ((i + 1) != readRolesArray.length) {
						query.append(" OR ");
					}
				}
			}
			else {
				query.append("readRoles = ");
				query.append("readRoles");
			}

			query.append(")");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);

			for (int i = 0; i < readRolesArray.length; i++) {
				q.setString(queryPos++,
					readRolesArray[i] + StringPool.COMMA + StringPool.PERCENT);
				q.setString(queryPos++,
					StringPool.PERCENT + StringPool.COMMA + readRolesArray[i] +
					StringPool.COMMA + StringPool.PERCENT);
			}

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

	private static final Log _log = LogFactory.getLog(MBTopicPersistence.class);
}