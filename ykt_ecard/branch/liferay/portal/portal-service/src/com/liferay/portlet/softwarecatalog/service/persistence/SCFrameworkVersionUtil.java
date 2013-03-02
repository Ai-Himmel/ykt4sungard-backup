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

package com.liferay.portlet.softwarecatalog.service.persistence;

/**
 * <a href="SCFrameworkVersionUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class SCFrameworkVersionUtil {
	public static com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion create(
		long frameworkVersionId) {
		return getPersistence().create(frameworkVersionId);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion remove(
		long frameworkVersionId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		return getPersistence().remove(frameworkVersionId);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion remove(
		com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion scFrameworkVersion)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(scFrameworkVersion);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion update(
		com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion scFrameworkVersion)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(scFrameworkVersion);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion update(
		com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion scFrameworkVersion,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().update(scFrameworkVersion, merge);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion updateImpl(
		com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion scFrameworkVersion,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(scFrameworkVersion, merge);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion findByPrimaryKey(
		long frameworkVersionId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		return getPersistence().findByPrimaryKey(frameworkVersionId);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion fetchByPrimaryKey(
		long frameworkVersionId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(frameworkVersionId);
	}

	public static java.util.List findByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByGroupId(groupId);
	}

	public static java.util.List findByGroupId(long groupId, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByGroupId(groupId, begin, end);
	}

	public static java.util.List findByGroupId(long groupId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByGroupId(groupId, begin, end, obc);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion findByGroupId_First(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		return getPersistence().findByGroupId_First(groupId, obc);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion findByGroupId_Last(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		return getPersistence().findByGroupId_Last(groupId, obc);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion[] findByGroupId_PrevAndNext(
		long frameworkVersionId, long groupId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		return getPersistence().findByGroupId_PrevAndNext(frameworkVersionId,
			groupId, obc);
	}

	public static java.util.List findByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(long companyId, int begin,
		int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(long companyId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion findByCompanyId_First(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		return getPersistence().findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion findByCompanyId_Last(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		return getPersistence().findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion[] findByCompanyId_PrevAndNext(
		long frameworkVersionId, long companyId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		return getPersistence().findByCompanyId_PrevAndNext(frameworkVersionId,
			companyId, obc);
	}

	public static java.util.List findByG_A(long groupId, boolean active)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_A(groupId, active);
	}

	public static java.util.List findByG_A(long groupId, boolean active,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByG_A(groupId, active, begin, end);
	}

	public static java.util.List findByG_A(long groupId, boolean active,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_A(groupId, active, begin, end, obc);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion findByG_A_First(
		long groupId, boolean active,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		return getPersistence().findByG_A_First(groupId, active, obc);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion findByG_A_Last(
		long groupId, boolean active,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		return getPersistence().findByG_A_Last(groupId, active, obc);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion[] findByG_A_PrevAndNext(
		long frameworkVersionId, long groupId, boolean active,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		return getPersistence().findByG_A_PrevAndNext(frameworkVersionId,
			groupId, active, obc);
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

	public static void removeByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByGroupId(groupId);
	}

	public static void removeByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByCompanyId(companyId);
	}

	public static void removeByG_A(long groupId, boolean active)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByG_A(groupId, active);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByGroupId(groupId);
	}

	public static int countByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByCompanyId(companyId);
	}

	public static int countByG_A(long groupId, boolean active)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByG_A(groupId, active);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static java.util.List getSCProductVersions(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		return getPersistence().getSCProductVersions(pk);
	}

	public static java.util.List getSCProductVersions(long pk, int begin,
		int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		return getPersistence().getSCProductVersions(pk, begin, end);
	}

	public static java.util.List getSCProductVersions(long pk, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		return getPersistence().getSCProductVersions(pk, begin, end, obc);
	}

	public static int getSCProductVersionsSize(long pk)
		throws com.liferay.portal.SystemException {
		return getPersistence().getSCProductVersionsSize(pk);
	}

	public static boolean containsSCProductVersion(long pk,
		long scProductVersionPK) throws com.liferay.portal.SystemException {
		return getPersistence().containsSCProductVersion(pk, scProductVersionPK);
	}

	public static boolean containsSCProductVersions(long pk)
		throws com.liferay.portal.SystemException {
		return getPersistence().containsSCProductVersions(pk);
	}

	public static void addSCProductVersion(long pk, long scProductVersionPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		getPersistence().addSCProductVersion(pk, scProductVersionPK);
	}

	public static void addSCProductVersion(long pk,
		com.liferay.portlet.softwarecatalog.model.SCProductVersion scProductVersion)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		getPersistence().addSCProductVersion(pk, scProductVersion);
	}

	public static void addSCProductVersions(long pk, long[] scProductVersionPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		getPersistence().addSCProductVersions(pk, scProductVersionPKs);
	}

	public static void addSCProductVersions(long pk,
		java.util.List scProductVersions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		getPersistence().addSCProductVersions(pk, scProductVersions);
	}

	public static void clearSCProductVersions(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		getPersistence().clearSCProductVersions(pk);
	}

	public static void removeSCProductVersion(long pk, long scProductVersionPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		getPersistence().removeSCProductVersion(pk, scProductVersionPK);
	}

	public static void removeSCProductVersion(long pk,
		com.liferay.portlet.softwarecatalog.model.SCProductVersion scProductVersion)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		getPersistence().removeSCProductVersion(pk, scProductVersion);
	}

	public static void removeSCProductVersions(long pk,
		long[] scProductVersionPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		getPersistence().removeSCProductVersions(pk, scProductVersionPKs);
	}

	public static void removeSCProductVersions(long pk,
		java.util.List scProductVersions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		getPersistence().removeSCProductVersions(pk, scProductVersions);
	}

	public static void setSCProductVersions(long pk, long[] scProductVersionPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		getPersistence().setSCProductVersions(pk, scProductVersionPKs);
	}

	public static void setSCProductVersions(long pk,
		java.util.List scProductVersions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		getPersistence().setSCProductVersions(pk, scProductVersions);
	}

	public static SCFrameworkVersionPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(SCFrameworkVersionPersistence persistence) {
		_persistence = persistence;
	}

	private static SCFrameworkVersionUtil _getUtil() {
		if (_util == null) {
			_util = (SCFrameworkVersionUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = SCFrameworkVersionUtil.class.getName();
	private static SCFrameworkVersionUtil _util;
	private SCFrameworkVersionPersistence _persistence;
}