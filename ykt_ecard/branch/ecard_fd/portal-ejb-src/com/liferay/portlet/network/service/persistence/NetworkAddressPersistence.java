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

package com.liferay.portlet.network.service.persistence;

import com.liferay.portal.SystemException;
import com.liferay.portal.service.persistence.BasePersistence;
import com.liferay.portal.util.HibernateUtil;

import com.liferay.portlet.network.NoSuchAddressException;

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
 * <a href="NetworkAddressPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class NetworkAddressPersistence extends BasePersistence {
	public com.liferay.portlet.network.model.NetworkAddress create(
		String addressId) {
		return new com.liferay.portlet.network.model.NetworkAddress(addressId);
	}

	public com.liferay.portlet.network.model.NetworkAddress remove(
		String addressId) throws NoSuchAddressException, SystemException {
		Session session = null;

		try {
			session = openSession();

			NetworkAddressHBM networkAddressHBM = (NetworkAddressHBM)session.get(NetworkAddressHBM.class,
					addressId);

			if (networkAddressHBM == null) {
				_log.warn("No NetworkAddress exists with the primary key of " +
					addressId.toString());
				throw new NoSuchAddressException(addressId.toString());
			}

			com.liferay.portlet.network.model.NetworkAddress networkAddress = NetworkAddressHBMUtil.model(networkAddressHBM);
			session.delete(networkAddressHBM);
			session.flush();
			NetworkAddressPool.remove(addressId);

			return networkAddress;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.network.model.NetworkAddress update(
		com.liferay.portlet.network.model.NetworkAddress networkAddress)
		throws SystemException {
		Session session = null;

		try {
			if (networkAddress.isNew() || networkAddress.isModified()) {
				session = openSession();

				if (networkAddress.isNew()) {
					NetworkAddressHBM networkAddressHBM = new NetworkAddressHBM(networkAddress.getAddressId(),
							networkAddress.getUserId(),
							networkAddress.getCreateDate(),
							networkAddress.getModifiedDate(),
							networkAddress.getName(), networkAddress.getUrl(),
							networkAddress.getComments(),
							networkAddress.getContent(),
							networkAddress.getStatus(),
							networkAddress.getLastUpdated(),
							networkAddress.getNotifyBy(),
							networkAddress.getInterval(),
							networkAddress.getActive());
					session.save(networkAddressHBM);
					session.flush();
				}
				else {
					NetworkAddressHBM networkAddressHBM = (NetworkAddressHBM)session.get(NetworkAddressHBM.class,
							networkAddress.getPrimaryKey());

					if (networkAddressHBM != null) {
						networkAddressHBM.setUserId(networkAddress.getUserId());
						networkAddressHBM.setCreateDate(networkAddress.getCreateDate());
						networkAddressHBM.setModifiedDate(networkAddress.getModifiedDate());
						networkAddressHBM.setName(networkAddress.getName());
						networkAddressHBM.setUrl(networkAddress.getUrl());
						networkAddressHBM.setComments(networkAddress.getComments());
						networkAddressHBM.setContent(networkAddress.getContent());
						networkAddressHBM.setStatus(networkAddress.getStatus());
						networkAddressHBM.setLastUpdated(networkAddress.getLastUpdated());
						networkAddressHBM.setNotifyBy(networkAddress.getNotifyBy());
						networkAddressHBM.setInterval(networkAddress.getInterval());
						networkAddressHBM.setActive(networkAddress.getActive());
						session.flush();
					}
					else {
						networkAddressHBM = new NetworkAddressHBM(networkAddress.getAddressId(),
								networkAddress.getUserId(),
								networkAddress.getCreateDate(),
								networkAddress.getModifiedDate(),
								networkAddress.getName(),
								networkAddress.getUrl(),
								networkAddress.getComments(),
								networkAddress.getContent(),
								networkAddress.getStatus(),
								networkAddress.getLastUpdated(),
								networkAddress.getNotifyBy(),
								networkAddress.getInterval(),
								networkAddress.getActive());
						session.save(networkAddressHBM);
						session.flush();
					}
				}

				networkAddress.setNew(false);
				networkAddress.setModified(false);
				networkAddress.protect();
				NetworkAddressPool.put(networkAddress.getPrimaryKey(),
					networkAddress);
			}

			return networkAddress;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.network.model.NetworkAddress findByPrimaryKey(
		String addressId) throws NoSuchAddressException, SystemException {
		com.liferay.portlet.network.model.NetworkAddress networkAddress = NetworkAddressPool.get(addressId);
		Session session = null;

		try {
			if (networkAddress == null) {
				session = openSession();

				NetworkAddressHBM networkAddressHBM = (NetworkAddressHBM)session.get(NetworkAddressHBM.class,
						addressId);

				if (networkAddressHBM == null) {
					_log.warn(
						"No NetworkAddress exists with the primary key of " +
						addressId.toString());
					throw new NoSuchAddressException(addressId.toString());
				}

				networkAddress = NetworkAddressHBMUtil.model(networkAddressHBM);
			}

			return networkAddress;
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
				"FROM NetworkAddress IN CLASS com.liferay.portlet.network.service.persistence.NetworkAddressHBM WHERE ");
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
				NetworkAddressHBM networkAddressHBM = (NetworkAddressHBM)itr.next();
				list.add(NetworkAddressHBMUtil.model(networkAddressHBM));
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
				"FROM NetworkAddress IN CLASS com.liferay.portlet.network.service.persistence.NetworkAddressHBM WHERE ");
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
					NetworkAddressHBM networkAddressHBM = (NetworkAddressHBM)itr.next();
					list.add(NetworkAddressHBMUtil.model(networkAddressHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						NetworkAddressHBM networkAddressHBM = (NetworkAddressHBM)sr.get(0);
						list.add(NetworkAddressHBMUtil.model(networkAddressHBM));

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

	public com.liferay.portlet.network.model.NetworkAddress findByUserId_First(
		String userId, OrderByComparator obc)
		throws NoSuchAddressException, SystemException {
		List list = findByUserId(userId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchAddressException();
		}
		else {
			return (com.liferay.portlet.network.model.NetworkAddress)list.get(0);
		}
	}

	public com.liferay.portlet.network.model.NetworkAddress findByUserId_Last(
		String userId, OrderByComparator obc)
		throws NoSuchAddressException, SystemException {
		int count = countByUserId(userId);
		List list = findByUserId(userId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchAddressException();
		}
		else {
			return (com.liferay.portlet.network.model.NetworkAddress)list.get(0);
		}
	}

	public com.liferay.portlet.network.model.NetworkAddress[] findByUserId_PrevAndNext(
		String addressId, String userId, OrderByComparator obc)
		throws NoSuchAddressException, SystemException {
		com.liferay.portlet.network.model.NetworkAddress networkAddress = findByPrimaryKey(addressId);
		int count = countByUserId(userId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM NetworkAddress IN CLASS com.liferay.portlet.network.service.persistence.NetworkAddressHBM WHERE ");
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

			com.liferay.portlet.network.model.NetworkAddress[] array = new com.liferay.portlet.network.model.NetworkAddress[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					NetworkAddressHBM networkAddressHBM = (NetworkAddressHBM)sr.get(0);

					if (networkAddressHBM == null) {
						break;
					}

					com.liferay.portlet.network.model.NetworkAddress curNetworkAddress =
						NetworkAddressHBMUtil.model(networkAddressHBM);
					int value = obc.compare(networkAddress, curNetworkAddress);

					if (value == 0) {
						if (!networkAddress.equals(curNetworkAddress)) {
							break;
						}

						array[1] = curNetworkAddress;

						if (sr.previous()) {
							array[0] = NetworkAddressHBMUtil.model((NetworkAddressHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = NetworkAddressHBMUtil.model((NetworkAddressHBM)sr.get(
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
				"FROM NetworkAddress IN CLASS com.liferay.portlet.network.service.persistence.NetworkAddressHBM ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				NetworkAddressHBM networkAddressHBM = (NetworkAddressHBM)itr.next();
				list.add(NetworkAddressHBMUtil.model(networkAddressHBM));
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

	public void removeByUserId(String userId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM NetworkAddress IN CLASS com.liferay.portlet.network.service.persistence.NetworkAddressHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				NetworkAddressHBM networkAddressHBM = (NetworkAddressHBM)itr.next();
				NetworkAddressPool.remove((String)networkAddressHBM.getPrimaryKey());
				session.delete(networkAddressHBM);
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

	public int countByUserId(String userId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM NetworkAddress IN CLASS com.liferay.portlet.network.service.persistence.NetworkAddressHBM WHERE ");
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

	private static final Log _log = LogFactory.getLog(NetworkAddressPersistence.class);
}