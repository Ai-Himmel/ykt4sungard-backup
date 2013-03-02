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

import com.liferay.portal.NoSuchColorSchemeException;
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
 * <a href="ColorSchemePersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ColorSchemePersistence extends BasePersistence {
	public com.liferay.portal.model.ColorScheme create(String colorSchemeId) {
		return new com.liferay.portal.model.ColorScheme(colorSchemeId);
	}

	public com.liferay.portal.model.ColorScheme remove(String colorSchemeId)
		throws NoSuchColorSchemeException, SystemException {
		Session session = null;

		try {
			session = openSession();

			ColorSchemeHBM colorSchemeHBM = (ColorSchemeHBM)session.get(ColorSchemeHBM.class,
					colorSchemeId);

			if (colorSchemeHBM == null) {
				_log.warn("No ColorScheme exists with the primary key of " +
					colorSchemeId.toString());
				throw new NoSuchColorSchemeException(colorSchemeId.toString());
			}

			com.liferay.portal.model.ColorScheme colorScheme = ColorSchemeHBMUtil.model(colorSchemeHBM);
			session.delete(colorSchemeHBM);
			session.flush();
			ColorSchemePool.remove(colorSchemeId);

			return colorScheme;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portal.model.ColorScheme update(
		com.liferay.portal.model.ColorScheme colorScheme)
		throws SystemException {
		Session session = null;

		try {
			if (colorScheme.isNew() || colorScheme.isModified()) {
				session = openSession();

				if (colorScheme.isNew()) {
					ColorSchemeHBM colorSchemeHBM = new ColorSchemeHBM(colorScheme.getColorSchemeId(),
							colorScheme.getSettings());
					session.save(colorSchemeHBM);
					session.flush();
				}
				else {
					ColorSchemeHBM colorSchemeHBM = (ColorSchemeHBM)session.get(ColorSchemeHBM.class,
							colorScheme.getPrimaryKey());

					if (colorSchemeHBM != null) {
						colorSchemeHBM.setSettings(colorScheme.getSettings());
						session.flush();
					}
					else {
						colorSchemeHBM = new ColorSchemeHBM(colorScheme.getColorSchemeId(),
								colorScheme.getSettings());
						session.save(colorSchemeHBM);
						session.flush();
					}
				}

				colorScheme.setNew(false);
				colorScheme.setModified(false);
				colorScheme.protect();
				ColorSchemePool.put(colorScheme.getPrimaryKey(), colorScheme);
			}

			return colorScheme;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portal.model.ColorScheme findByPrimaryKey(
		String colorSchemeId)
		throws NoSuchColorSchemeException, SystemException {
		com.liferay.portal.model.ColorScheme colorScheme = ColorSchemePool.get(colorSchemeId);
		Session session = null;

		try {
			if (colorScheme == null) {
				session = openSession();

				ColorSchemeHBM colorSchemeHBM = (ColorSchemeHBM)session.get(ColorSchemeHBM.class,
						colorSchemeId);

				if (colorSchemeHBM == null) {
					_log.warn("No ColorScheme exists with the primary key of " +
						colorSchemeId.toString());
					throw new NoSuchColorSchemeException(colorSchemeId.toString());
				}

				colorScheme = ColorSchemeHBMUtil.model(colorSchemeHBM);
			}

			return colorScheme;
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
				"FROM ColorScheme IN CLASS com.liferay.portal.service.persistence.ColorSchemeHBM ");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ColorSchemeHBM colorSchemeHBM = (ColorSchemeHBM)itr.next();
				list.add(ColorSchemeHBMUtil.model(colorSchemeHBM));
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

	private static final Log _log = LogFactory.getLog(ColorSchemePersistence.class);
}