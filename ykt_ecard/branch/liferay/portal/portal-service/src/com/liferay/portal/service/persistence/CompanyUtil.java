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
 * <a href="CompanyUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CompanyUtil {
	public static com.liferay.portal.model.Company create(long companyId) {
		return getPersistence().create(companyId);
	}

	public static com.liferay.portal.model.Company remove(long companyId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchCompanyException {
		return getPersistence().remove(companyId);
	}

	public static com.liferay.portal.model.Company remove(
		com.liferay.portal.model.Company company)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(company);
	}

	public static com.liferay.portal.model.Company update(
		com.liferay.portal.model.Company company)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(company);
	}

	public static com.liferay.portal.model.Company update(
		com.liferay.portal.model.Company company, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(company, merge);
	}

	public static com.liferay.portal.model.Company updateImpl(
		com.liferay.portal.model.Company company, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(company, merge);
	}

	public static com.liferay.portal.model.Company findByPrimaryKey(
		long companyId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchCompanyException {
		return getPersistence().findByPrimaryKey(companyId);
	}

	public static com.liferay.portal.model.Company fetchByPrimaryKey(
		long companyId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(companyId);
	}

	public static com.liferay.portal.model.Company findByWebId(
		java.lang.String webId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchCompanyException {
		return getPersistence().findByWebId(webId);
	}

	public static com.liferay.portal.model.Company fetchByWebId(
		java.lang.String webId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByWebId(webId);
	}

	public static com.liferay.portal.model.Company findByVirtualHost(
		java.lang.String virtualHost)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchCompanyException {
		return getPersistence().findByVirtualHost(virtualHost);
	}

	public static com.liferay.portal.model.Company fetchByVirtualHost(
		java.lang.String virtualHost) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByVirtualHost(virtualHost);
	}

	public static com.liferay.portal.model.Company findByMx(java.lang.String mx)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchCompanyException {
		return getPersistence().findByMx(mx);
	}

	public static com.liferay.portal.model.Company fetchByMx(
		java.lang.String mx) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByMx(mx);
	}

	public static com.liferay.portal.model.Company findByLogoId(long logoId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchCompanyException {
		return getPersistence().findByLogoId(logoId);
	}

	public static com.liferay.portal.model.Company fetchByLogoId(long logoId)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByLogoId(logoId);
	}

	public static java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		return getPersistence().findWithDynamicQuery(queryInitializer);
	}

	public static java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findWithDynamicQuery(queryInitializer, begin,
			end);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		return getPersistence().findAll();
	}

	public static java.util.List findAll(int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findAll(begin, end);
	}

	public static java.util.List findAll(int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findAll(begin, end, obc);
	}

	public static void removeByWebId(java.lang.String webId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchCompanyException {
		getPersistence().removeByWebId(webId);
	}

	public static void removeByVirtualHost(java.lang.String virtualHost)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchCompanyException {
		getPersistence().removeByVirtualHost(virtualHost);
	}

	public static void removeByMx(java.lang.String mx)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchCompanyException {
		getPersistence().removeByMx(mx);
	}

	public static void removeByLogoId(long logoId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchCompanyException {
		getPersistence().removeByLogoId(logoId);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByWebId(java.lang.String webId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByWebId(webId);
	}

	public static int countByVirtualHost(java.lang.String virtualHost)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByVirtualHost(virtualHost);
	}

	public static int countByMx(java.lang.String mx)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByMx(mx);
	}

	public static int countByLogoId(long logoId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByLogoId(logoId);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static CompanyPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(CompanyPersistence persistence) {
		_persistence = persistence;
	}

	private static CompanyUtil _getUtil() {
		if (_util == null) {
			_util = (CompanyUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = CompanyUtil.class.getName();
	private static CompanyUtil _util;
	private CompanyPersistence _persistence;
}