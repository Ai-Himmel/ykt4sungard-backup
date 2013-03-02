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

package com.liferay.portlet.documentlibrary.service;


/**
 * <a href="DLFileRankLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.documentlibrary.service.DLFileRankLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.documentlibrary.service.DLFileRankLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.documentlibrary.service.DLFileRankLocalService
 * @see com.liferay.portlet.documentlibrary.service.DLFileRankLocalServiceFactory
 *
 */
public class DLFileRankLocalServiceUtil {
	public static com.liferay.portlet.documentlibrary.model.DLFileRank addDLFileRank(
		com.liferay.portlet.documentlibrary.model.DLFileRank model)
		throws com.liferay.portal.SystemException {
		DLFileRankLocalService dlFileRankLocalService = DLFileRankLocalServiceFactory.getService();

		return dlFileRankLocalService.addDLFileRank(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		DLFileRankLocalService dlFileRankLocalService = DLFileRankLocalServiceFactory.getService();

		return dlFileRankLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		DLFileRankLocalService dlFileRankLocalService = DLFileRankLocalServiceFactory.getService();

		return dlFileRankLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileRank updateDLFileRank(
		com.liferay.portlet.documentlibrary.model.DLFileRank model)
		throws com.liferay.portal.SystemException {
		DLFileRankLocalService dlFileRankLocalService = DLFileRankLocalServiceFactory.getService();

		return dlFileRankLocalService.updateDLFileRank(model);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryPersistence getDLFileEntryPersistence() {
		DLFileRankLocalService dlFileRankLocalService = DLFileRankLocalServiceFactory.getService();

		return dlFileRankLocalService.getDLFileEntryPersistence();
	}

	public static void setDLFileEntryPersistence(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryPersistence dlFileEntryPersistence) {
		DLFileRankLocalService dlFileRankLocalService = DLFileRankLocalServiceFactory.getService();

		dlFileRankLocalService.setDLFileEntryPersistence(dlFileEntryPersistence);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryFinder getDLFileEntryFinder() {
		DLFileRankLocalService dlFileRankLocalService = DLFileRankLocalServiceFactory.getService();

		return dlFileRankLocalService.getDLFileEntryFinder();
	}

	public static void setDLFileEntryFinder(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryFinder dlFileEntryFinder) {
		DLFileRankLocalService dlFileRankLocalService = DLFileRankLocalServiceFactory.getService();

		dlFileRankLocalService.setDLFileEntryFinder(dlFileEntryFinder);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryAndShortcutFinder getDLFileEntryAndShortcutFinder() {
		DLFileRankLocalService dlFileRankLocalService = DLFileRankLocalServiceFactory.getService();

		return dlFileRankLocalService.getDLFileEntryAndShortcutFinder();
	}

	public static void setDLFileEntryAndShortcutFinder(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryAndShortcutFinder dlFileEntryAndShortcutFinder) {
		DLFileRankLocalService dlFileRankLocalService = DLFileRankLocalServiceFactory.getService();

		dlFileRankLocalService.setDLFileEntryAndShortcutFinder(dlFileEntryAndShortcutFinder);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileRankPersistence getDLFileRankPersistence() {
		DLFileRankLocalService dlFileRankLocalService = DLFileRankLocalServiceFactory.getService();

		return dlFileRankLocalService.getDLFileRankPersistence();
	}

	public static void setDLFileRankPersistence(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileRankPersistence dlFileRankPersistence) {
		DLFileRankLocalService dlFileRankLocalService = DLFileRankLocalServiceFactory.getService();

		dlFileRankLocalService.setDLFileRankPersistence(dlFileRankPersistence);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileRankFinder getDLFileRankFinder() {
		DLFileRankLocalService dlFileRankLocalService = DLFileRankLocalServiceFactory.getService();

		return dlFileRankLocalService.getDLFileRankFinder();
	}

	public static void setDLFileRankFinder(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileRankFinder dlFileRankFinder) {
		DLFileRankLocalService dlFileRankLocalService = DLFileRankLocalServiceFactory.getService();

		dlFileRankLocalService.setDLFileRankFinder(dlFileRankFinder);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileShortcutPersistence getDLFileShortcutPersistence() {
		DLFileRankLocalService dlFileRankLocalService = DLFileRankLocalServiceFactory.getService();

		return dlFileRankLocalService.getDLFileShortcutPersistence();
	}

	public static void setDLFileShortcutPersistence(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileShortcutPersistence dlFileShortcutPersistence) {
		DLFileRankLocalService dlFileRankLocalService = DLFileRankLocalServiceFactory.getService();

		dlFileRankLocalService.setDLFileShortcutPersistence(dlFileShortcutPersistence);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileShortcutFinder getDLFileShortcutFinder() {
		DLFileRankLocalService dlFileRankLocalService = DLFileRankLocalServiceFactory.getService();

		return dlFileRankLocalService.getDLFileShortcutFinder();
	}

	public static void setDLFileShortcutFinder(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileShortcutFinder dlFileShortcutFinder) {
		DLFileRankLocalService dlFileRankLocalService = DLFileRankLocalServiceFactory.getService();

		dlFileRankLocalService.setDLFileShortcutFinder(dlFileShortcutFinder);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionPersistence getDLFileVersionPersistence() {
		DLFileRankLocalService dlFileRankLocalService = DLFileRankLocalServiceFactory.getService();

		return dlFileRankLocalService.getDLFileVersionPersistence();
	}

	public static void setDLFileVersionPersistence(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionPersistence dlFileVersionPersistence) {
		DLFileRankLocalService dlFileRankLocalService = DLFileRankLocalServiceFactory.getService();

		dlFileRankLocalService.setDLFileVersionPersistence(dlFileVersionPersistence);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFolderPersistence getDLFolderPersistence() {
		DLFileRankLocalService dlFileRankLocalService = DLFileRankLocalServiceFactory.getService();

		return dlFileRankLocalService.getDLFolderPersistence();
	}

	public static void setDLFolderPersistence(
		com.liferay.portlet.documentlibrary.service.persistence.DLFolderPersistence dlFolderPersistence) {
		DLFileRankLocalService dlFileRankLocalService = DLFileRankLocalServiceFactory.getService();

		dlFileRankLocalService.setDLFolderPersistence(dlFolderPersistence);
	}

	public static void afterPropertiesSet() {
		DLFileRankLocalService dlFileRankLocalService = DLFileRankLocalServiceFactory.getService();

		dlFileRankLocalService.afterPropertiesSet();
	}

	public static void deleteFileRanks(long userId)
		throws com.liferay.portal.SystemException {
		DLFileRankLocalService dlFileRankLocalService = DLFileRankLocalServiceFactory.getService();

		dlFileRankLocalService.deleteFileRanks(userId);
	}

	public static void deleteFileRanks(long folderId, java.lang.String name)
		throws com.liferay.portal.SystemException {
		DLFileRankLocalService dlFileRankLocalService = DLFileRankLocalServiceFactory.getService();

		dlFileRankLocalService.deleteFileRanks(folderId, name);
	}

	public static java.util.List getFileRanks(long groupId, long userId)
		throws com.liferay.portal.SystemException {
		DLFileRankLocalService dlFileRankLocalService = DLFileRankLocalServiceFactory.getService();

		return dlFileRankLocalService.getFileRanks(groupId, userId);
	}

	public static java.util.List getFileRanks(long groupId, long userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		DLFileRankLocalService dlFileRankLocalService = DLFileRankLocalServiceFactory.getService();

		return dlFileRankLocalService.getFileRanks(groupId, userId, begin, end);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileRank updateFileRank(
		long groupId, long companyId, long userId, long folderId,
		java.lang.String name)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileRankLocalService dlFileRankLocalService = DLFileRankLocalServiceFactory.getService();

		return dlFileRankLocalService.updateFileRank(groupId, companyId,
			userId, folderId, name);
	}
}