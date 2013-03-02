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

import com.liferay.portlet.messageboards.NoSuchThreadException;

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
 * <a href="MBThreadPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class MBThreadPersistence extends BasePersistence {
	public com.liferay.portlet.messageboards.model.MBThread create(
		String threadId) {
		return new com.liferay.portlet.messageboards.model.MBThread(threadId);
	}

	public com.liferay.portlet.messageboards.model.MBThread remove(
		String threadId) throws NoSuchThreadException, SystemException {
		Session session = null;

		try {
			session = openSession();

			MBThreadHBM mbThreadHBM = (MBThreadHBM)session.get(MBThreadHBM.class,
					threadId);

			if (mbThreadHBM == null) {
				_log.warn("No MBThread exists with the primary key of " +
					threadId.toString());
				throw new NoSuchThreadException(threadId.toString());
			}

			com.liferay.portlet.messageboards.model.MBThread mbThread = MBThreadHBMUtil.model(mbThreadHBM);
			session.delete(mbThreadHBM);
			session.flush();
			MBThreadPool.remove(threadId);

			return mbThread;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.messageboards.model.MBThread update(
		com.liferay.portlet.messageboards.model.MBThread mbThread)
		throws SystemException {
		Session session = null;

		try {
			if (mbThread.isNew() || mbThread.isModified()) {
				session = openSession();

				if (mbThread.isNew()) {
					MBThreadHBM mbThreadHBM = new MBThreadHBM(mbThread.getThreadId(),
							mbThread.getRootMessageId(), mbThread.getTopicId(),
							mbThread.getMessageCount(),
							mbThread.getLastPostDate());
					session.save(mbThreadHBM);
					session.flush();
				}
				else {
					MBThreadHBM mbThreadHBM = (MBThreadHBM)session.get(MBThreadHBM.class,
							mbThread.getPrimaryKey());

					if (mbThreadHBM != null) {
						mbThreadHBM.setRootMessageId(mbThread.getRootMessageId());
						mbThreadHBM.setTopicId(mbThread.getTopicId());
						mbThreadHBM.setMessageCount(mbThread.getMessageCount());
						mbThreadHBM.setLastPostDate(mbThread.getLastPostDate());
						session.flush();
					}
					else {
						mbThreadHBM = new MBThreadHBM(mbThread.getThreadId(),
								mbThread.getRootMessageId(),
								mbThread.getTopicId(),
								mbThread.getMessageCount(),
								mbThread.getLastPostDate());
						session.save(mbThreadHBM);
						session.flush();
					}
				}

				mbThread.setNew(false);
				mbThread.setModified(false);
				mbThread.protect();
				MBThreadPool.put(mbThread.getPrimaryKey(), mbThread);
			}

			return mbThread;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.messageboards.model.MBThread findByPrimaryKey(
		String threadId) throws NoSuchThreadException, SystemException {
		com.liferay.portlet.messageboards.model.MBThread mbThread = MBThreadPool.get(threadId);
		Session session = null;

		try {
			if (mbThread == null) {
				session = openSession();

				MBThreadHBM mbThreadHBM = (MBThreadHBM)session.get(MBThreadHBM.class,
						threadId);

				if (mbThreadHBM == null) {
					_log.warn("No MBThread exists with the primary key of " +
						threadId.toString());
					throw new NoSuchThreadException(threadId.toString());
				}

				mbThread = MBThreadHBMUtil.model(mbThreadHBM);
			}

			return mbThread;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByTopicId(String topicId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBThread IN CLASS com.liferay.portlet.messageboards.service.persistence.MBThreadHBM WHERE ");
			query.append("topicId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("lastPostDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, topicId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				MBThreadHBM mbThreadHBM = (MBThreadHBM)itr.next();
				list.add(MBThreadHBMUtil.model(mbThreadHBM));
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

	public List findByTopicId(String topicId, int begin, int end)
		throws SystemException {
		return findByTopicId(topicId, begin, end, null);
	}

	public List findByTopicId(String topicId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBThread IN CLASS com.liferay.portlet.messageboards.service.persistence.MBThreadHBM WHERE ");
			query.append("topicId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("lastPostDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, topicId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					MBThreadHBM mbThreadHBM = (MBThreadHBM)itr.next();
					list.add(MBThreadHBMUtil.model(mbThreadHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						MBThreadHBM mbThreadHBM = (MBThreadHBM)sr.get(0);
						list.add(MBThreadHBMUtil.model(mbThreadHBM));

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

	public com.liferay.portlet.messageboards.model.MBThread findByTopicId_First(
		String topicId, OrderByComparator obc)
		throws NoSuchThreadException, SystemException {
		List list = findByTopicId(topicId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchThreadException();
		}
		else {
			return (com.liferay.portlet.messageboards.model.MBThread)list.get(0);
		}
	}

	public com.liferay.portlet.messageboards.model.MBThread findByTopicId_Last(
		String topicId, OrderByComparator obc)
		throws NoSuchThreadException, SystemException {
		int count = countByTopicId(topicId);
		List list = findByTopicId(topicId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchThreadException();
		}
		else {
			return (com.liferay.portlet.messageboards.model.MBThread)list.get(0);
		}
	}

	public com.liferay.portlet.messageboards.model.MBThread[] findByTopicId_PrevAndNext(
		String threadId, String topicId, OrderByComparator obc)
		throws NoSuchThreadException, SystemException {
		com.liferay.portlet.messageboards.model.MBThread mbThread = findByPrimaryKey(threadId);
		int count = countByTopicId(topicId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBThread IN CLASS com.liferay.portlet.messageboards.service.persistence.MBThreadHBM WHERE ");
			query.append("topicId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("lastPostDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, topicId);

			com.liferay.portlet.messageboards.model.MBThread[] array = new com.liferay.portlet.messageboards.model.MBThread[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					MBThreadHBM mbThreadHBM = (MBThreadHBM)sr.get(0);

					if (mbThreadHBM == null) {
						break;
					}

					com.liferay.portlet.messageboards.model.MBThread curMBThread =
						MBThreadHBMUtil.model(mbThreadHBM);
					int value = obc.compare(mbThread, curMBThread);

					if (value == 0) {
						if (!mbThread.equals(curMBThread)) {
							break;
						}

						array[1] = curMBThread;

						if (sr.previous()) {
							array[0] = MBThreadHBMUtil.model((MBThreadHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = MBThreadHBMUtil.model((MBThreadHBM)sr.get(
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
				"FROM MBThread IN CLASS com.liferay.portlet.messageboards.service.persistence.MBThreadHBM ");
			query.append("ORDER BY ");
			query.append("lastPostDate DESC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				MBThreadHBM mbThreadHBM = (MBThreadHBM)itr.next();
				list.add(MBThreadHBMUtil.model(mbThreadHBM));
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

	public void removeByTopicId(String topicId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBThread IN CLASS com.liferay.portlet.messageboards.service.persistence.MBThreadHBM WHERE ");
			query.append("topicId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("lastPostDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, topicId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				MBThreadHBM mbThreadHBM = (MBThreadHBM)itr.next();
				MBThreadPool.remove((String)mbThreadHBM.getPrimaryKey());
				session.delete(mbThreadHBM);
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

	public int countByTopicId(String topicId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM MBThread IN CLASS com.liferay.portlet.messageboards.service.persistence.MBThreadHBM WHERE ");
			query.append("topicId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, topicId);

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

	private static final Log _log = LogFactory.getLog(MBThreadPersistence.class);
}