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
 * <a href="DLFileVersionLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.documentlibrary.service.DLFileVersionLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.documentlibrary.service.DLFileVersionLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.documentlibrary.service.DLFileVersionLocalService
 * @see com.liferay.portlet.documentlibrary.service.DLFileVersionLocalServiceFactory
 *
 */
public class DLFileVersionLocalServiceUtil {
	public static com.liferay.portlet.documentlibrary.model.DLFileVersion addDLFileVersion(
		com.liferay.portlet.documentlibrary.model.DLFileVersion model)
		throws com.liferay.portal.SystemException {
		DLFileVersionLocalService dlFileVersionLocalService = DLFileVersionLocalServiceFactory.getService();

		return dlFileVersionLocalService.addDLFileVersion(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		DLFileVersionLocalService dlFileVersionLocalService = DLFileVersionLocalServiceFactory.getService();

		return dlFileVersionLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		DLFileVersionLocalService dlFileVersionLocalService = DLFileVersionLocalServiceFactory.getService();

		return dlFileVersionLocalService.dynamicQuery(queryInitializer, begin,
			end);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileVersion updateDLFileVersion(
		com.liferay.portlet.documentlibrary.model.DLFileVersion model)
		throws com.liferay.portal.SystemException {
		DLFileVersionLocalService dlFileVersionLocalService = DLFileVersionLocalServiceFactory.getService();

		return dlFileVersionLocalService.updateDLFileVersion(model);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryPersistence getDLFileEntryPersistence() {
		DLFileVersionLocalService dlFileVersionLocalService = DLFileVersionLocalServiceFactory.getService();

		return dlFileVersionLocalService.getDLFileEntryPersistence();
	}

	public static void setDLFileEntryPersistence(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryPersistence dlFileEntryPersistence) {
		DLFileVersionLocalService dlFileVersionLocalService = DLFileVersionLocalServiceFactory.getService();

		dlFileVersionLocalService.setDLFileEntryPersistence(dlFileEntryPersistence);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryFinder getDLFileEntryFinder() {
		DLFileVersionLocalService dlFileVersionLocalService = DLFileVersionLocalServiceFactory.getService();

		return dlFileVersionLocalService.getDLFileEntryFinder();
	}

	public static void setDLFileEntryFinder(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryFinder dlFileEntryFinder) {
		DLFileVersionLocalService dlFileVersionLocalService = DLFileVersionLocalServiceFactory.getService();

		dlFileVersionLocalService.setDLFileEntryFinder(dlFileEntryFinder);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryAndShortcutFinder getDLFileEntryAndShortcutFinder() {
		DLFileVersionLocalService dlFileVersionLocalService = DLFileVersionLocalServiceFactory.getService();

		return dlFileVersionLocalService.getDLFileEntryAndShortcutFinder();
	}

	public static void setDLFileEntryAndShortcutFinder(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryAndShortcutFinder dlFileEntryAndShortcutFinder) {
		DLFileVersionLocalService dlFileVersionLocalService = DLFileVersionLocalServiceFactory.getService();

		dlFileVersionLocalService.setDLFileEntryAndShortcutFinder(dlFileEntryAndShortcutFinder);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileRankPersistence getDLFileRankPersistence() {
		DLFileVersionLocalService dlFileVersionLocalService = DLFileVersionLocalServiceFactory.getService();

		return dlFileVersionLocalService.getDLFileRankPersistence();
	}

	public static void setDLFileRankPersistence(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileRankPersistence dlFileRankPersistence) {
		DLFileVersionLocalService dlFileVersionLocalService = DLFileVersionLocalServiceFactory.getService();

		dlFileVersionLocalService.setDLFileRankPersistence(dlFileRankPersistence);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileRankFinder getDLFileRankFinder() {
		DLFileVersionLocalService dlFileVersionLocalService = DLFileVersionLocalServiceFactory.getService();

		return dlFileVersionLocalService.getDLFileRankFinder();
	}

	public static void setDLFileRankFinder(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileRankFinder dlFileRankFinder) {
		DLFileVersionLocalService dlFileVersionLocalService = DLFileVersionLocalServiceFactory.getService();

		dlFileVersionLocalService.setDLFileRankFinder(dlFileRankFinder);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileShortcutPersistence getDLFileShortcutPersistence() {
		DLFileVersionLocalService dlFileVersionLocalService = DLFileVersionLocalServiceFactory.getService();

		return dlFileVersionLocalService.getDLFileShortcutPersistence();
	}

	public static void setDLFileShortcutPersistence(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileShortcutPersistence dlFileShortcutPersistence) {
		DLFileVersionLocalService dlFileVersionLocalService = DLFileVersionLocalServiceFactory.getService();

		dlFileVersionLocalService.setDLFileShortcutPersistence(dlFileShortcutPersistence);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileShortcutFinder getDLFileShortcutFinder() {
		DLFileVersionLocalService dlFileVersionLocalService = DLFileVersionLocalServiceFactory.getService();

		return dlFileVersionLocalService.getDLFileShortcutFinder();
	}

	public static void setDLFileShortcutFinder(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileShortcutFinder dlFileShortcutFinder) {
		DLFileVersionLocalService dlFileVersionLocalService = DLFileVersionLocalServiceFactory.getService();

		dlFileVersionLocalService.setDLFileShortcutFinder(dlFileShortcutFinder);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionPersistence getDLFileVersionPersistence() {
		DLFileVersionLocalService dlFileVersionLocalService = DLFileVersionLocalServiceFactory.getService();

		return dlFileVersionLocalService.getDLFileVersionPersistence();
	}

	public static void setDLFileVersionPersistence(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionPersistence dlFileVersionPersistence) {
		DLFileVersionLocalService dlFileVersionLocalService = DLFileVersionLocalServiceFactory.getService();

		dlFileVersionLocalService.setDLFileVersionPersistence(dlFileVersionPersistence);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFolderPersistence getDLFolderPersistence() {
		DLFileVersionLocalService dlFileVersionLocalService = DLFileVersionLocalServiceFactory.getService();

		return dlFileVersionLocalService.getDLFolderPersistence();
	}

	public static void setDLFolderPersistence(
		com.liferay.portlet.documentlibrary.service.persistence.DLFolderPersistence dlFolderPersistence) {
		DLFileVersionLocalService dlFileVersionLocalService = DLFileVersionLocalServiceFactory.getService();

		dlFileVersionLocalService.setDLFolderPersistence(dlFolderPersistence);
	}

	public static void afterPropertiesSet() {
		DLFileVersionLocalService dlFileVersionLocalService = DLFileVersionLocalServiceFactory.getService();

		dlFileVersionLocalService.afterPropertiesSet();
	}

	public static java.util.List getFileVersions(long folderId,
		java.lang.String name) throws com.liferay.portal.SystemException {
		DLFileVersionLocalService dlFileVersionLocalService = DLFileVersionLocalServiceFactory.getService();

		return dlFileVersionLocalService.getFileVersions(folderId, name);
	}
}