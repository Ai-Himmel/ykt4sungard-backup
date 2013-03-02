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

import com.liferay.portal.NoSuchCompanyException;
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
 * <a href="CompanyPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class CompanyPersistence extends BasePersistence {
	public com.liferay.portal.model.Company create(String companyId) {
		return new com.liferay.portal.model.Company(companyId);
	}

	public com.liferay.portal.model.Company remove(String companyId)
		throws NoSuchCompanyException, SystemException {
		Session session = null;

		try {
			session = openSession();

			CompanyHBM companyHBM = (CompanyHBM)session.get(CompanyHBM.class,
					companyId);

			if (companyHBM == null) {
				_log.warn("No Company exists with the primary key of " +
					companyId.toString());
				throw new NoSuchCompanyException(companyId.toString());
			}

			com.liferay.portal.model.Company company = CompanyHBMUtil.model(companyHBM);
			session.delete(companyHBM);
			session.flush();
			CompanyPool.remove(companyId);

			return company;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portal.model.Company update(
		com.liferay.portal.model.Company company) throws SystemException {
		Session session = null;

		try {
			if (company.isNew() || company.isModified()) {
				session = openSession();

				if (company.isNew()) {
					CompanyHBM companyHBM = new CompanyHBM(company.getCompanyId(),
							company.getKey(), company.getPortalURL(),
							company.getHomeURL(), company.getMx(),
							company.getName(), company.getShortName(),
							company.getType(), company.getSize(),
							company.getStreet(), company.getCity(),
							company.getState(), company.getZip(),
							company.getPhone(), company.getFax(),
							company.getEmailAddress());
					session.save(companyHBM);
					session.flush();
				}
				else {
					CompanyHBM companyHBM = (CompanyHBM)session.get(CompanyHBM.class,
							company.getPrimaryKey());

					if (companyHBM != null) {
						companyHBM.setKey(company.getKey());
						companyHBM.setPortalURL(company.getPortalURL());
						companyHBM.setHomeURL(company.getHomeURL());
						companyHBM.setMx(company.getMx());
						companyHBM.setName(company.getName());
						companyHBM.setShortName(company.getShortName());
						companyHBM.setType(company.getType());
						companyHBM.setSize(company.getSize());
						companyHBM.setStreet(company.getStreet());
						companyHBM.setCity(company.getCity());
						companyHBM.setState(company.getState());
						companyHBM.setZip(company.getZip());
						companyHBM.setPhone(company.getPhone());
						companyHBM.setFax(company.getFax());
						companyHBM.setEmailAddress(company.getEmailAddress());
						session.flush();
					}
					else {
						companyHBM = new CompanyHBM(company.getCompanyId(),
								company.getKey(), company.getPortalURL(),
								company.getHomeURL(), company.getMx(),
								company.getName(), company.getShortName(),
								company.getType(), company.getSize(),
								company.getStreet(), company.getCity(),
								company.getState(), company.getZip(),
								company.getPhone(), company.getFax(),
								company.getEmailAddress());
						session.save(companyHBM);
						session.flush();
					}
				}

				company.setNew(false);
				company.setModified(false);
				company.protect();
				CompanyPool.put(company.getPrimaryKey(), company);
			}

			return company;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portal.model.Company findByPrimaryKey(String companyId)
		throws NoSuchCompanyException, SystemException {
		com.liferay.portal.model.Company company = CompanyPool.get(companyId);
		Session session = null;

		try {
			if (company == null) {
				session = openSession();

				CompanyHBM companyHBM = (CompanyHBM)session.get(CompanyHBM.class,
						companyId);

				if (companyHBM == null) {
					_log.warn("No Company exists with the primary key of " +
						companyId.toString());
					throw new NoSuchCompanyException(companyId.toString());
				}

				company = CompanyHBMUtil.model(companyHBM);
			}

			return company;
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
				"FROM Company IN CLASS com.liferay.portal.service.persistence.CompanyHBM ");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				CompanyHBM companyHBM = (CompanyHBM)itr.next();
				list.add(CompanyHBMUtil.model(companyHBM));
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

	private static final Log _log = LogFactory.getLog(CompanyPersistence.class);
}