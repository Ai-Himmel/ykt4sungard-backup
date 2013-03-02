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
 * <a href="SCProductVersionUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class SCProductVersionUtil {
	public static com.liferay.portlet.softwarecatalog.model.SCProductVersion create(
		long productVersionId) {
		return getPersistence().create(productVersionId);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCProductVersion remove(
		long productVersionId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException {
		return getPersistence().remove(productVersionId);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCProductVersion remove(
		com.liferay.portlet.softwarecatalog.model.SCProductVersion scProductVersion)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(scProductVersion);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCProductVersion update(
		com.liferay.portlet.softwarecatalog.model.SCProductVersion scProductVersion)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(scProductVersion);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCProductVersion update(
		com.liferay.portlet.softwarecatalog.model.SCProductVersion scProductVersion,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().update(scProductVersion, merge);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCProductVersion updateImpl(
		com.liferay.portlet.softwarecatalog.model.SCProductVersion scProductVersion,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(scProductVersion, merge);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCProductVersion findByPrimaryKey(
		long productVersionId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException {
		return getPersistence().findByPrimaryKey(productVersionId);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCProductVersion fetchByPrimaryKey(
		long productVersionId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(productVersionId);
	}

	public static java.util.List findByProductEntryId(long productEntryId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByProductEntryId(productEntryId);
	}

	public static java.util.List findByProductEntryId(long productEntryId,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByProductEntryId(productEntryId, begin, end);
	}

	public static java.util.List findByProductEntryId(long productEntryId,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByProductEntryId(productEntryId, begin,
			end, obc);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCProductVersion findByProductEntryId_First(
		long productEntryId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException {
		return getPersistence().findByProductEntryId_First(productEntryId, obc);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCProductVersion findByProductEntryId_Last(
		long productEntryId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException {
		return getPersistence().findByProductEntryId_Last(productEntryId, obc);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCProductVersion[] findByProductEntryId_PrevAndNext(
		long productVersionId, long productEntryId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException {
		return getPersistence().findByProductEntryId_PrevAndNext(productVersionId,
			productEntryId, obc);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCProductVersion findByDirectDownloadURL(
		java.lang.String directDownloadURL)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException {
		return getPersistence().findByDirectDownloadURL(directDownloadURL);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCProductVersion fetchByDirectDownloadURL(
		java.lang.String directDownloadURL)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByDirectDownloadURL(directDownloadURL);
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

	public static void removeByProductEntryId(long productEntryId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByProductEntryId(productEntryId);
	}

	public static void removeByDirectDownloadURL(
		java.lang.String directDownloadURL)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException {
		getPersistence().removeByDirectDownloadURL(directDownloadURL);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByProductEntryId(long productEntryId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByProductEntryId(productEntryId);
	}

	public static int countByDirectDownloadURL(
		java.lang.String directDownloadURL)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByDirectDownloadURL(directDownloadURL);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static java.util.List getSCFrameworkVersions(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException {
		return getPersistence().getSCFrameworkVersions(pk);
	}

	public static java.util.List getSCFrameworkVersions(long pk, int begin,
		int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException {
		return getPersistence().getSCFrameworkVersions(pk, begin, end);
	}

	public static java.util.List getSCFrameworkVersions(long pk, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException {
		return getPersistence().getSCFrameworkVersions(pk, begin, end, obc);
	}

	public static int getSCFrameworkVersionsSize(long pk)
		throws com.liferay.portal.SystemException {
		return getPersistence().getSCFrameworkVersionsSize(pk);
	}

	public static boolean containsSCFrameworkVersion(long pk,
		long scFrameworkVersionPK) throws com.liferay.portal.SystemException {
		return getPersistence().containsSCFrameworkVersion(pk,
			scFrameworkVersionPK);
	}

	public static boolean containsSCFrameworkVersions(long pk)
		throws com.liferay.portal.SystemException {
		return getPersistence().containsSCFrameworkVersions(pk);
	}

	public static void addSCFrameworkVersion(long pk, long scFrameworkVersionPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		getPersistence().addSCFrameworkVersion(pk, scFrameworkVersionPK);
	}

	public static void addSCFrameworkVersion(long pk,
		com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion scFrameworkVersion)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		getPersistence().addSCFrameworkVersion(pk, scFrameworkVersion);
	}

	public static void addSCFrameworkVersions(long pk,
		long[] scFrameworkVersionPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		getPersistence().addSCFrameworkVersions(pk, scFrameworkVersionPKs);
	}

	public static void addSCFrameworkVersions(long pk,
		java.util.List scFrameworkVersions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		getPersistence().addSCFrameworkVersions(pk, scFrameworkVersions);
	}

	public static void clearSCFrameworkVersions(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException {
		getPersistence().clearSCFrameworkVersions(pk);
	}

	public static void removeSCFrameworkVersion(long pk,
		long scFrameworkVersionPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		getPersistence().removeSCFrameworkVersion(pk, scFrameworkVersionPK);
	}

	public static void removeSCFrameworkVersion(long pk,
		com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion scFrameworkVersion)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		getPersistence().removeSCFrameworkVersion(pk, scFrameworkVersion);
	}

	public static void removeSCFrameworkVersions(long pk,
		long[] scFrameworkVersionPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		getPersistence().removeSCFrameworkVersions(pk, scFrameworkVersionPKs);
	}

	public static void removeSCFrameworkVersions(long pk,
		java.util.List scFrameworkVersions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		getPersistence().removeSCFrameworkVersions(pk, scFrameworkVersions);
	}

	public static void setSCFrameworkVersions(long pk,
		long[] scFrameworkVersionPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		getPersistence().setSCFrameworkVersions(pk, scFrameworkVersionPKs);
	}

	public static void setSCFrameworkVersions(long pk,
		java.util.List scFrameworkVersions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException {
		getPersistence().setSCFrameworkVersions(pk, scFrameworkVersions);
	}

	public static SCProductVersionPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(SCProductVersionPersistence persistence) {
		_persistence = persistence;
	}

	private static SCProductVersionUtil _getUtil() {
		if (_util == null) {
			_util = (SCProductVersionUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = SCProductVersionUtil.class.getName();
	private static SCProductVersionUtil _util;
	private SCProductVersionPersistence _persistence;
}