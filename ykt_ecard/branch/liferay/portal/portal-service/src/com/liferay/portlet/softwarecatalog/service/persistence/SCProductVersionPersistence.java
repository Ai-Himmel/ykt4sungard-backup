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
 * <a href="SCProductVersionPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public interface SCProductVersionPersistence {
	public com.liferay.portlet.softwarecatalog.model.SCProductVersion create(
		long productVersionId);

	public com.liferay.portlet.softwarecatalog.model.SCProductVersion remove(
		long productVersionId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException;

	public com.liferay.portlet.softwarecatalog.model.SCProductVersion remove(
		com.liferay.portlet.softwarecatalog.model.SCProductVersion scProductVersion)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.softwarecatalog.model.SCProductVersion update(
		com.liferay.portlet.softwarecatalog.model.SCProductVersion scProductVersion)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.softwarecatalog.model.SCProductVersion update(
		com.liferay.portlet.softwarecatalog.model.SCProductVersion scProductVersion,
		boolean merge) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.softwarecatalog.model.SCProductVersion updateImpl(
		com.liferay.portlet.softwarecatalog.model.SCProductVersion scProductVersion,
		boolean merge) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.softwarecatalog.model.SCProductVersion findByPrimaryKey(
		long productVersionId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException;

	public com.liferay.portlet.softwarecatalog.model.SCProductVersion fetchByPrimaryKey(
		long productVersionId) throws com.liferay.portal.SystemException;

	public java.util.List findByProductEntryId(long productEntryId)
		throws com.liferay.portal.SystemException;

	public java.util.List findByProductEntryId(long productEntryId, int begin,
		int end) throws com.liferay.portal.SystemException;

	public java.util.List findByProductEntryId(long productEntryId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.softwarecatalog.model.SCProductVersion findByProductEntryId_First(
		long productEntryId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException;

	public com.liferay.portlet.softwarecatalog.model.SCProductVersion findByProductEntryId_Last(
		long productEntryId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException;

	public com.liferay.portlet.softwarecatalog.model.SCProductVersion[] findByProductEntryId_PrevAndNext(
		long productVersionId, long productEntryId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException;

	public com.liferay.portlet.softwarecatalog.model.SCProductVersion findByDirectDownloadURL(
		java.lang.String directDownloadURL)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException;

	public com.liferay.portlet.softwarecatalog.model.SCProductVersion fetchByDirectDownloadURL(
		java.lang.String directDownloadURL)
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

	public void removeByProductEntryId(long productEntryId)
		throws com.liferay.portal.SystemException;

	public void removeByDirectDownloadURL(java.lang.String directDownloadURL)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException;

	public void removeAll() throws com.liferay.portal.SystemException;

	public int countByProductEntryId(long productEntryId)
		throws com.liferay.portal.SystemException;

	public int countByDirectDownloadURL(java.lang.String directDownloadURL)
		throws com.liferay.portal.SystemException;

	public int countAll() throws com.liferay.portal.SystemException;

	public java.util.List getSCFrameworkVersions(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException;

	public java.util.List getSCFrameworkVersions(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException;

	public java.util.List getSCFrameworkVersions(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException;

	public int getSCFrameworkVersionsSize(long pk)
		throws com.liferay.portal.SystemException;

	public boolean containsSCFrameworkVersion(long pk, long scFrameworkVersionPK)
		throws com.liferay.portal.SystemException;

	public boolean containsSCFrameworkVersions(long pk)
		throws com.liferay.portal.SystemException;

	public void addSCFrameworkVersion(long pk, long scFrameworkVersionPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException;

	public void addSCFrameworkVersion(long pk,
		com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion scFrameworkVersion)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException;

	public void addSCFrameworkVersions(long pk, long[] scFrameworkVersionPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException;

	public void addSCFrameworkVersions(long pk,
		java.util.List scFrameworkVersions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException;

	public void clearSCFrameworkVersions(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException;

	public void removeSCFrameworkVersion(long pk, long scFrameworkVersionPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException;

	public void removeSCFrameworkVersion(long pk,
		com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion scFrameworkVersion)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException;

	public void removeSCFrameworkVersions(long pk, long[] scFrameworkVersionPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException;

	public void removeSCFrameworkVersions(long pk,
		java.util.List scFrameworkVersions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException;

	public void setSCFrameworkVersions(long pk, long[] scFrameworkVersionPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException;

	public void setSCFrameworkVersions(long pk,
		java.util.List scFrameworkVersions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException;
}