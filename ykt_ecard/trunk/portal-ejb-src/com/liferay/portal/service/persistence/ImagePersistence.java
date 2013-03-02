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

import com.liferay.portal.NoSuchImageException;
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
 * <a href="ImagePersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ImagePersistence extends BasePersistence {
	public com.liferay.portal.model.Image create(String imageId) {
		return new com.liferay.portal.model.Image(imageId);
	}

	public com.liferay.portal.model.Image remove(String imageId)
		throws NoSuchImageException, SystemException {
		Session session = null;

		try {
			session = openSession();

			ImageHBM imageHBM = (ImageHBM)session.get(ImageHBM.class, imageId);

			if (imageHBM == null) {
				_log.warn("No Image exists with the primary key of " +
					imageId.toString());
				throw new NoSuchImageException(imageId.toString());
			}

			com.liferay.portal.model.Image image = ImageHBMUtil.model(imageHBM);
			session.delete(imageHBM);
			session.flush();
			ImagePool.remove(imageId);

			return image;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portal.model.Image update(
		com.liferay.portal.model.Image image) throws SystemException {
		Session session = null;

		try {
			if (image.isNew() || image.isModified()) {
				session = openSession();

				if (image.isNew()) {
					ImageHBM imageHBM = new ImageHBM(image.getImageId(),
							image.getModifiedDate(), image.getText());
					session.save(imageHBM);
					session.flush();
				}
				else {
					ImageHBM imageHBM = (ImageHBM)session.get(ImageHBM.class,
							image.getPrimaryKey());

					if (imageHBM != null) {
						imageHBM.setModifiedDate(image.getModifiedDate());
						imageHBM.setText(image.getText());
						session.flush();
					}
					else {
						imageHBM = new ImageHBM(image.getImageId(),
								image.getModifiedDate(), image.getText());
						session.save(imageHBM);
						session.flush();
					}
				}

				image.setNew(false);
				image.setModified(false);
				image.protect();
				ImagePool.put(image.getPrimaryKey(), image);
			}

			return image;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portal.model.Image findByPrimaryKey(String imageId)
		throws NoSuchImageException, SystemException {
		com.liferay.portal.model.Image image = ImagePool.get(imageId);
		Session session = null;

		try {
			if (image == null) {
				session = openSession();

				ImageHBM imageHBM = (ImageHBM)session.get(ImageHBM.class,
						imageId);

				if (imageHBM == null) {
					_log.warn("No Image exists with the primary key of " +
						imageId.toString());
					throw new NoSuchImageException(imageId.toString());
				}

				image = ImageHBMUtil.model(imageHBM);
			}

			return image;
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
				"FROM Image IN CLASS com.liferay.portal.service.persistence.ImageHBM ");
			query.append("ORDER BY ");
			query.append("imageId ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ImageHBM imageHBM = (ImageHBM)itr.next();
				list.add(ImageHBMUtil.model(imageHBM));
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

	private static final Log _log = LogFactory.getLog(ImagePersistence.class);
}