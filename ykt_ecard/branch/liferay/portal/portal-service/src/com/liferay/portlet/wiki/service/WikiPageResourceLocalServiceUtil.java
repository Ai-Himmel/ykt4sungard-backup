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

package com.liferay.portlet.wiki.service;


/**
 * <a href="WikiPageResourceLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.wiki.service.WikiPageResourceLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.wiki.service.WikiPageResourceLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.wiki.service.WikiPageResourceLocalService
 * @see com.liferay.portlet.wiki.service.WikiPageResourceLocalServiceFactory
 *
 */
public class WikiPageResourceLocalServiceUtil {
	public static com.liferay.portlet.wiki.model.WikiPageResource addWikiPageResource(
		com.liferay.portlet.wiki.model.WikiPageResource model)
		throws com.liferay.portal.SystemException {
		WikiPageResourceLocalService wikiPageResourceLocalService = WikiPageResourceLocalServiceFactory.getService();

		return wikiPageResourceLocalService.addWikiPageResource(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		WikiPageResourceLocalService wikiPageResourceLocalService = WikiPageResourceLocalServiceFactory.getService();

		return wikiPageResourceLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		WikiPageResourceLocalService wikiPageResourceLocalService = WikiPageResourceLocalServiceFactory.getService();

		return wikiPageResourceLocalService.dynamicQuery(queryInitializer,
			begin, end);
	}

	public static com.liferay.portlet.wiki.model.WikiPageResource updateWikiPageResource(
		com.liferay.portlet.wiki.model.WikiPageResource model)
		throws com.liferay.portal.SystemException {
		WikiPageResourceLocalService wikiPageResourceLocalService = WikiPageResourceLocalServiceFactory.getService();

		return wikiPageResourceLocalService.updateWikiPageResource(model);
	}

	public static com.liferay.portlet.wiki.service.persistence.WikiNodePersistence getWikiNodePersistence() {
		WikiPageResourceLocalService wikiPageResourceLocalService = WikiPageResourceLocalServiceFactory.getService();

		return wikiPageResourceLocalService.getWikiNodePersistence();
	}

	public static void setWikiNodePersistence(
		com.liferay.portlet.wiki.service.persistence.WikiNodePersistence wikiNodePersistence) {
		WikiPageResourceLocalService wikiPageResourceLocalService = WikiPageResourceLocalServiceFactory.getService();

		wikiPageResourceLocalService.setWikiNodePersistence(wikiNodePersistence);
	}

	public static com.liferay.portlet.wiki.service.persistence.WikiPagePersistence getWikiPagePersistence() {
		WikiPageResourceLocalService wikiPageResourceLocalService = WikiPageResourceLocalServiceFactory.getService();

		return wikiPageResourceLocalService.getWikiPagePersistence();
	}

	public static void setWikiPagePersistence(
		com.liferay.portlet.wiki.service.persistence.WikiPagePersistence wikiPagePersistence) {
		WikiPageResourceLocalService wikiPageResourceLocalService = WikiPageResourceLocalServiceFactory.getService();

		wikiPageResourceLocalService.setWikiPagePersistence(wikiPagePersistence);
	}

	public static com.liferay.portlet.wiki.service.persistence.WikiPageFinder getWikiPageFinder() {
		WikiPageResourceLocalService wikiPageResourceLocalService = WikiPageResourceLocalServiceFactory.getService();

		return wikiPageResourceLocalService.getWikiPageFinder();
	}

	public static void setWikiPageFinder(
		com.liferay.portlet.wiki.service.persistence.WikiPageFinder wikiPageFinder) {
		WikiPageResourceLocalService wikiPageResourceLocalService = WikiPageResourceLocalServiceFactory.getService();

		wikiPageResourceLocalService.setWikiPageFinder(wikiPageFinder);
	}

	public static com.liferay.portlet.wiki.service.persistence.WikiPageResourcePersistence getWikiPageResourcePersistence() {
		WikiPageResourceLocalService wikiPageResourceLocalService = WikiPageResourceLocalServiceFactory.getService();

		return wikiPageResourceLocalService.getWikiPageResourcePersistence();
	}

	public static void setWikiPageResourcePersistence(
		com.liferay.portlet.wiki.service.persistence.WikiPageResourcePersistence wikiPageResourcePersistence) {
		WikiPageResourceLocalService wikiPageResourceLocalService = WikiPageResourceLocalServiceFactory.getService();

		wikiPageResourceLocalService.setWikiPageResourcePersistence(wikiPageResourcePersistence);
	}

	public static void afterPropertiesSet() {
		WikiPageResourceLocalService wikiPageResourceLocalService = WikiPageResourceLocalServiceFactory.getService();

		wikiPageResourceLocalService.afterPropertiesSet();
	}

	public static void deletePageResource(long nodeId, java.lang.String title)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiPageResourceLocalService wikiPageResourceLocalService = WikiPageResourceLocalServiceFactory.getService();

		wikiPageResourceLocalService.deletePageResource(nodeId, title);
	}

	public static com.liferay.portlet.wiki.model.WikiPageResource getPageResource(
		long pageResourceId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiPageResourceLocalService wikiPageResourceLocalService = WikiPageResourceLocalServiceFactory.getService();

		return wikiPageResourceLocalService.getPageResource(pageResourceId);
	}

	public static long getPageResourcePrimKey(long nodeId,
		java.lang.String title)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiPageResourceLocalService wikiPageResourceLocalService = WikiPageResourceLocalServiceFactory.getService();

		return wikiPageResourceLocalService.getPageResourcePrimKey(nodeId, title);
	}
}