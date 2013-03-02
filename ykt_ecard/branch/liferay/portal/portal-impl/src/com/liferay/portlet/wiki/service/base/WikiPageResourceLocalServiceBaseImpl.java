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

package com.liferay.portlet.wiki.service.base;

import com.liferay.counter.service.CounterLocalService;
import com.liferay.counter.service.CounterLocalServiceFactory;
import com.liferay.counter.service.CounterService;
import com.liferay.counter.service.CounterServiceFactory;

import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.dao.DynamicQueryInitializer;

import com.liferay.portlet.wiki.model.WikiPageResource;
import com.liferay.portlet.wiki.model.impl.WikiPageResourceImpl;
import com.liferay.portlet.wiki.service.WikiNodeLocalService;
import com.liferay.portlet.wiki.service.WikiNodeLocalServiceFactory;
import com.liferay.portlet.wiki.service.WikiNodeService;
import com.liferay.portlet.wiki.service.WikiNodeServiceFactory;
import com.liferay.portlet.wiki.service.WikiPageLocalService;
import com.liferay.portlet.wiki.service.WikiPageLocalServiceFactory;
import com.liferay.portlet.wiki.service.WikiPageResourceLocalService;
import com.liferay.portlet.wiki.service.WikiPageService;
import com.liferay.portlet.wiki.service.WikiPageServiceFactory;
import com.liferay.portlet.wiki.service.persistence.WikiNodePersistence;
import com.liferay.portlet.wiki.service.persistence.WikiNodeUtil;
import com.liferay.portlet.wiki.service.persistence.WikiPageFinder;
import com.liferay.portlet.wiki.service.persistence.WikiPageFinderUtil;
import com.liferay.portlet.wiki.service.persistence.WikiPagePersistence;
import com.liferay.portlet.wiki.service.persistence.WikiPageResourcePersistence;
import com.liferay.portlet.wiki.service.persistence.WikiPageResourceUtil;
import com.liferay.portlet.wiki.service.persistence.WikiPageUtil;

import org.springframework.beans.factory.InitializingBean;

import java.util.List;

/**
 * <a href="WikiPageResourceLocalServiceBaseImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public abstract class WikiPageResourceLocalServiceBaseImpl
	implements WikiPageResourceLocalService, InitializingBean {
	public WikiPageResource addWikiPageResource(WikiPageResource model)
		throws SystemException {
		WikiPageResource wikiPageResource = new WikiPageResourceImpl();

		wikiPageResource.setNew(true);

		wikiPageResource.setResourcePrimKey(model.getResourcePrimKey());
		wikiPageResource.setNodeId(model.getNodeId());
		wikiPageResource.setTitle(model.getTitle());

		return wikiPageResourcePersistence.update(wikiPageResource);
	}

	public List dynamicQuery(DynamicQueryInitializer queryInitializer)
		throws SystemException {
		return wikiPageResourcePersistence.findWithDynamicQuery(queryInitializer);
	}

	public List dynamicQuery(DynamicQueryInitializer queryInitializer,
		int begin, int end) throws SystemException {
		return wikiPageResourcePersistence.findWithDynamicQuery(queryInitializer,
			begin, end);
	}

	public WikiPageResource updateWikiPageResource(WikiPageResource model)
		throws SystemException {
		WikiPageResource wikiPageResource = new WikiPageResourceImpl();

		wikiPageResource.setNew(false);

		wikiPageResource.setResourcePrimKey(model.getResourcePrimKey());
		wikiPageResource.setNodeId(model.getNodeId());
		wikiPageResource.setTitle(model.getTitle());

		return wikiPageResourcePersistence.update(wikiPageResource);
	}

	public WikiNodeLocalService getWikiNodeLocalService() {
		return wikiNodeLocalService;
	}

	public void setWikiNodeLocalService(
		WikiNodeLocalService wikiNodeLocalService) {
		this.wikiNodeLocalService = wikiNodeLocalService;
	}

	public WikiNodeService getWikiNodeService() {
		return wikiNodeService;
	}

	public void setWikiNodeService(WikiNodeService wikiNodeService) {
		this.wikiNodeService = wikiNodeService;
	}

	public WikiNodePersistence getWikiNodePersistence() {
		return wikiNodePersistence;
	}

	public void setWikiNodePersistence(WikiNodePersistence wikiNodePersistence) {
		this.wikiNodePersistence = wikiNodePersistence;
	}

	public WikiPageLocalService getWikiPageLocalService() {
		return wikiPageLocalService;
	}

	public void setWikiPageLocalService(
		WikiPageLocalService wikiPageLocalService) {
		this.wikiPageLocalService = wikiPageLocalService;
	}

	public WikiPageService getWikiPageService() {
		return wikiPageService;
	}

	public void setWikiPageService(WikiPageService wikiPageService) {
		this.wikiPageService = wikiPageService;
	}

	public WikiPagePersistence getWikiPagePersistence() {
		return wikiPagePersistence;
	}

	public void setWikiPagePersistence(WikiPagePersistence wikiPagePersistence) {
		this.wikiPagePersistence = wikiPagePersistence;
	}

	public WikiPageFinder getWikiPageFinder() {
		return wikiPageFinder;
	}

	public void setWikiPageFinder(WikiPageFinder wikiPageFinder) {
		this.wikiPageFinder = wikiPageFinder;
	}

	public WikiPageResourcePersistence getWikiPageResourcePersistence() {
		return wikiPageResourcePersistence;
	}

	public void setWikiPageResourcePersistence(
		WikiPageResourcePersistence wikiPageResourcePersistence) {
		this.wikiPageResourcePersistence = wikiPageResourcePersistence;
	}

	public CounterLocalService getCounterLocalService() {
		return counterLocalService;
	}

	public void setCounterLocalService(CounterLocalService counterLocalService) {
		this.counterLocalService = counterLocalService;
	}

	public CounterService getCounterService() {
		return counterService;
	}

	public void setCounterService(CounterService counterService) {
		this.counterService = counterService;
	}

	public void afterPropertiesSet() {
		if (wikiNodeLocalService == null) {
			wikiNodeLocalService = WikiNodeLocalServiceFactory.getImpl();
		}

		if (wikiNodeService == null) {
			wikiNodeService = WikiNodeServiceFactory.getImpl();
		}

		if (wikiNodePersistence == null) {
			wikiNodePersistence = WikiNodeUtil.getPersistence();
		}

		if (wikiPageLocalService == null) {
			wikiPageLocalService = WikiPageLocalServiceFactory.getImpl();
		}

		if (wikiPageService == null) {
			wikiPageService = WikiPageServiceFactory.getImpl();
		}

		if (wikiPagePersistence == null) {
			wikiPagePersistence = WikiPageUtil.getPersistence();
		}

		if (wikiPageFinder == null) {
			wikiPageFinder = WikiPageFinderUtil.getFinder();
		}

		if (wikiPageResourcePersistence == null) {
			wikiPageResourcePersistence = WikiPageResourceUtil.getPersistence();
		}

		if (counterLocalService == null) {
			counterLocalService = CounterLocalServiceFactory.getImpl();
		}

		if (counterService == null) {
			counterService = CounterServiceFactory.getImpl();
		}
	}

	protected WikiNodeLocalService wikiNodeLocalService;
	protected WikiNodeService wikiNodeService;
	protected WikiNodePersistence wikiNodePersistence;
	protected WikiPageLocalService wikiPageLocalService;
	protected WikiPageService wikiPageService;
	protected WikiPagePersistence wikiPagePersistence;
	protected WikiPageFinder wikiPageFinder;
	protected WikiPageResourcePersistence wikiPageResourcePersistence;
	protected CounterLocalService counterLocalService;
	protected CounterService counterService;
}