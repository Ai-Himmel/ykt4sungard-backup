/**
 * Copyright (c) 2000-2008 Liferay, Inc. All rights reserved.
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

/**
 * <a href="CompanyPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public interface CompanyPersistence {
	public com.liferay.portal.model.Company create(long companyId);

	public com.liferay.portal.model.Company remove(long companyId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchCompanyException;

	public com.liferay.portal.model.Company remove(
		com.liferay.portal.model.Company company)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.Company update(
		com.liferay.portal.model.Company company)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.Company update(
		com.liferay.portal.model.Company company, boolean merge)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.Company updateImpl(
		com.liferay.portal.model.Company company, boolean merge)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.Company findByPrimaryKey(long companyId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchCompanyException;

	public com.liferay.portal.model.Company fetchByPrimaryKey(long companyId)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.Company findByWebId(java.lang.String webId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchCompanyException;

	public com.liferay.portal.model.Company fetchByWebId(java.lang.String webId)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.Company findByVirtualHost(
		java.lang.String virtualHost)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchCompanyException;

	public com.liferay.portal.model.Company fetchByVirtualHost(
		java.lang.String virtualHost) throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.Company findByMx(java.lang.String mx)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchCompanyException;

	public com.liferay.portal.model.Company fetchByMx(java.lang.String mx)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.Company findByLogoId(long logoId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchCompanyException;

	public com.liferay.portal.model.Company fetchByLogoId(long logoId)
		throws com.liferay.portal.SystemException;

	public java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException;

	public java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException;

	public java.util.List findAll() throws com.liferay.portal.SystemException;

	public java.util.List findAll(int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findAll(int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public void removeByWebId(java.lang.String webId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchCompanyException;

	public void removeByVirtualHost(java.lang.String virtualHost)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchCompanyException;

	public void removeByMx(java.lang.String mx)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchCompanyException;

	public void removeByLogoId(long logoId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchCompanyException;

	public void removeAll() throws com.liferay.portal.SystemException;

	public int countByWebId(java.lang.String webId)
		throws com.liferay.portal.SystemException;

	public int countByVirtualHost(java.lang.String virtualHost)
		throws com.liferay.portal.SystemException;

	public int countByMx(java.lang.String mx)
		throws com.liferay.portal.SystemException;

	public int countByLogoId(long logoId)
		throws com.liferay.portal.SystemException;

	public int countAll() throws com.liferay.portal.SystemException;
}