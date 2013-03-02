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

import com.liferay.portal.NoSuchReleaseException;
import com.liferay.portal.SystemException;
import com.liferay.portal.service.persistence.BasePersistence;
import com.liferay.portal.util.HibernateUtil;

import com.liferay.util.lang.FastStringBuffer;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="ReleasePersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ReleasePersistence extends BasePersistence {
	public com.liferay.portal.model.Release create(String releaseId) {
		return new com.liferay.portal.model.Release(releaseId);
	}

	public com.liferay.portal.model.Release remove(String releaseId)
		throws NoSuchReleaseException, SystemException {
		Session session = null;

		try {
			session = openSession();

			ReleaseHBM releaseHBM = (ReleaseHBM)session.get(ReleaseHBM.class,
					releaseId);

			if (releaseHBM == null) {
				_log.warn("No Release exists with the primary key of " +
					releaseId.toString());
				throw new NoSuchReleaseException(releaseId.toString());
			}

			com.liferay.portal.model.Release release = ReleaseHBMUtil.model(releaseHBM);
			session.delete(releaseHBM);
			session.flush();
			ReleasePool.remove(releaseId);

			return release;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portal.model.Release update(
		com.liferay.portal.model.Release release) throws SystemException {
		Session session = null;

		try {
			if (release.isNew() || release.isModified()) {
				session = openSession();

				if (release.isNew()) {
					ReleaseHBM releaseHBM = new ReleaseHBM(release.getReleaseId(),
							release.getCreateDate(), release.getModifiedDate(),
							release.getBuildNumber(), release.getBuildDate());
					session.save(releaseHBM);
					session.flush();
				}
				else {
					ReleaseHBM releaseHBM = (ReleaseHBM)session.get(ReleaseHBM.class,
							release.getPrimaryKey());

					if (releaseHBM != null) {
						releaseHBM.setCreateDate(release.getCreateDate());
						releaseHBM.setModifiedDate(release.getModifiedDate());
						releaseHBM.setBuildNumber(release.getBuildNumber());
						releaseHBM.setBuildDate(release.getBuildDate());
						session.flush();
					}
					else {
						releaseHBM = new ReleaseHBM(release.getReleaseId(),
								release.getCreateDate(),
								release.getModifiedDate(),
								release.getBuildNumber(), release.getBuildDate());
						session.save(releaseHBM);
						session.flush();
					}
				}

				release.setNew(false);
				release.setModified(false);
				release.protect();
				ReleasePool.put(release.getPrimaryKey(), release);
			}

			return release;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portal.model.Release findByPrimaryKey(String releaseId)
		throws NoSuchReleaseException, SystemException {
		com.liferay.portal.model.Release release = ReleasePool.get(releaseId);
		Session session = null;

		try {
			if (release == null) {
				session = openSession();

				ReleaseHBM releaseHBM = (ReleaseHBM)session.get(ReleaseHBM.class,
						releaseId);

				if (releaseHBM == null) {
					_log.warn("No Release exists with the primary key of " +
						releaseId.toString());
					throw new NoSuchReleaseException(releaseId.toString());
				}

				release = ReleaseHBMUtil.model(releaseHBM);
			}

			return release;
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
				"FROM Release_ IN CLASS com.liferay.portal.service.persistence.ReleaseHBM ");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ReleaseHBM releaseHBM = (ReleaseHBM)itr.next();
				list.add(ReleaseHBMUtil.model(releaseHBM));
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

	private static final Log _log = LogFactory.getLog(ReleasePersistence.class);
}