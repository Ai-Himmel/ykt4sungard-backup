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
 * <a href="SCProductScreenshotPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public interface SCProductScreenshotPersistence {
	public com.liferay.portlet.softwarecatalog.model.SCProductScreenshot create(
		long productScreenshotId);

	public com.liferay.portlet.softwarecatalog.model.SCProductScreenshot remove(
		long productScreenshotId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductScreenshotException;

	public com.liferay.portlet.softwarecatalog.model.SCProductScreenshot remove(
		com.liferay.portlet.softwarecatalog.model.SCProductScreenshot scProductScreenshot)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.softwarecatalog.model.SCProductScreenshot update(
		com.liferay.portlet.softwarecatalog.model.SCProductScreenshot scProductScreenshot)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.softwarecatalog.model.SCProductScreenshot update(
		com.liferay.portlet.softwarecatalog.model.SCProductScreenshot scProductScreenshot,
		boolean merge) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.softwarecatalog.model.SCProductScreenshot updateImpl(
		com.liferay.portlet.softwarecatalog.model.SCProductScreenshot scProductScreenshot,
		boolean merge) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.softwarecatalog.model.SCProductScreenshot findByPrimaryKey(
		long productScreenshotId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductScreenshotException;

	public com.liferay.portlet.softwarecatalog.model.SCProductScreenshot fetchByPrimaryKey(
		long productScreenshotId) throws com.liferay.portal.SystemException;

	public java.util.List findByProductEntryId(long productEntryId)
		throws com.liferay.portal.SystemException;

	public java.util.List findByProductEntryId(long productEntryId, int begin,
		int end) throws com.liferay.portal.SystemException;

	public java.util.List findByProductEntryId(long productEntryId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.softwarecatalog.model.SCProductScreenshot findByProductEntryId_First(
		long productEntryId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductScreenshotException;

	public com.liferay.portlet.softwarecatalog.model.SCProductScreenshot findByProductEntryId_Last(
		long productEntryId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductScreenshotException;

	public com.liferay.portlet.softwarecatalog.model.SCProductScreenshot[] findByProductEntryId_PrevAndNext(
		long productScreenshotId, long productEntryId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductScreenshotException;

	public com.liferay.portlet.softwarecatalog.model.SCProductScreenshot findByThumbnailId(
		long thumbnailId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductScreenshotException;

	public com.liferay.portlet.softwarecatalog.model.SCProductScreenshot fetchByThumbnailId(
		long thumbnailId) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.softwarecatalog.model.SCProductScreenshot findByFullImageId(
		long fullImageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductScreenshotException;

	public com.liferay.portlet.softwarecatalog.model.SCProductScreenshot fetchByFullImageId(
		long fullImageId) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.softwarecatalog.model.SCProductScreenshot findByP_P(
		long productEntryId, int priority)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductScreenshotException;

	public com.liferay.portlet.softwarecatalog.model.SCProductScreenshot fetchByP_P(
		long productEntryId, int priority)
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

	public void removeByThumbnailId(long thumbnailId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductScreenshotException;

	public void removeByFullImageId(long fullImageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductScreenshotException;

	public void removeByP_P(long productEntryId, int priority)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductScreenshotException;

	public void removeAll() throws com.liferay.portal.SystemException;

	public int countByProductEntryId(long productEntryId)
		throws com.liferay.portal.SystemException;

	public int countByThumbnailId(long thumbnailId)
		throws com.liferay.portal.SystemException;

	public int countByFullImageId(long fullImageId)
		throws com.liferay.portal.SystemException;

	public int countByP_P(long productEntryId, int priority)
		throws com.liferay.portal.SystemException;

	public int countAll() throws com.liferay.portal.SystemException;
}