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

package com.liferay.portlet.tags.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.Group;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.tags.model.TagsAsset;
import com.liferay.portlet.tags.model.TagsAssetDisplay;
import com.liferay.portlet.tags.model.TagsAssetType;
import com.liferay.portlet.tags.service.base.TagsAssetServiceBaseImpl;
import com.liferay.util.RSSUtil;

import com.sun.syndication.feed.synd.SyndContent;
import com.sun.syndication.feed.synd.SyndContentImpl;
import com.sun.syndication.feed.synd.SyndEntry;
import com.sun.syndication.feed.synd.SyndEntryImpl;
import com.sun.syndication.feed.synd.SyndFeed;
import com.sun.syndication.feed.synd.SyndFeedImpl;
import com.sun.syndication.io.FeedException;

import java.io.IOException;

import java.util.ArrayList;
import java.util.Date;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="TagsAssetServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Jorge Ferrer
 *
 */
public class TagsAssetServiceImpl extends TagsAssetServiceBaseImpl {

	public void deleteAsset(long assetId)
		throws PortalException, SystemException {

		tagsAssetLocalService.deleteAsset(assetId);
	}

	public TagsAsset getAsset(long assetId)
		throws PortalException, SystemException {

		return tagsAssetLocalService.getAsset(assetId);
	}

	public String getAssetsRSS(
			long groupId, long[] classNameIds, long[] entryIds,
			long[] notEntryIds, boolean andOperator, String orderByCol1,
			String orderByCol2, String orderByType1, String orderByType2,
			boolean excludeZeroViewCount, Date publishDate, Date expirationDate,
			int max, String type, double version, String displayStyle,
			String feedURL, String entryURL)
		throws PortalException, SystemException {

		Group group = groupPersistence.findByPrimaryKey(groupId);

		String name = group.getName();

		List assets = tagsAssetLocalService.getAssets(
			groupId, classNameIds, entryIds, notEntryIds, andOperator,
			orderByCol1, orderByCol2, orderByType1, orderByType2,
			excludeZeroViewCount, publishDate, expirationDate, 0, max);

		return exportToRSS(
			name, null, type, version, displayStyle, feedURL, entryURL, assets);
	}

	public TagsAssetType[] getAssetTypes(String languageId) {
		return tagsAssetLocalService.getAssetTypes(languageId);
	}

	public TagsAssetDisplay[] getCompanyAssetDisplays(
			long companyId, int begin, int end, String languageId)
		throws PortalException, SystemException {

		return tagsAssetLocalService.getCompanyAssetDisplays(
			companyId, begin, end, languageId);
	}

	public List getCompanyAssets(long companyId, int begin, int end)
		throws SystemException {

		return tagsAssetLocalService.getCompanyAssets(companyId, begin, end);
	}

	public int getCompanyAssetsCount(long companyId) throws SystemException {
		return tagsAssetLocalService.getCompanyAssetsCount(companyId);
	}

	public String getCompanyAssetsRSS(
			long companyId, int max, String type, double version,
			String displayStyle, String feedURL, String entryURL)
		throws PortalException, SystemException {

		Company company = companyPersistence.findByPrimaryKey(companyId);

		String name = company.getName();

		List assets = getCompanyAssets(companyId, 0, max);

		return exportToRSS(
			name, null, type, version, displayStyle, feedURL, entryURL, assets);
	}

	public TagsAsset incrementViewCounter(String className, long classPK)
		throws PortalException, SystemException {

		return tagsAssetLocalService.incrementViewCounter(className, classPK);
	}

	public TagsAssetDisplay[] searchAssetDisplays(
			long companyId, String portletId, String keywords,
			String languageId, int begin, int end)
		throws PortalException, SystemException {

		return tagsAssetLocalService.searchAssetDisplays(
			companyId, portletId, keywords, languageId, begin, end);
	}

	public int searchAssetDisplaysCount(
			long companyId, String portletId, String keywords,
			String languageId)
		throws SystemException {

		return tagsAssetLocalService.searchAssetDisplaysCount(
			companyId, portletId, keywords, languageId);
	}

	public TagsAsset updateAsset(
			long groupId, String className, long classPK, String[] entryNames,
			Date startDate, Date endDate, Date publishDate, Date expirationDate,
			String mimeType, String title, String description, String summary,
			String url, int height, int width, Integer priority)
		throws PortalException, SystemException {

		return tagsAssetLocalService.updateAsset(
			getUserId(), groupId, className, classPK, entryNames, startDate,
			endDate, publishDate, expirationDate, mimeType, title, description,
			summary, url, height, width, priority);
	}

	protected String exportToRSS(
			String name, String description, String type, double version,
			String displayStyle, String feedURL, String entryURL, List assets)
		throws SystemException {

		SyndFeed syndFeed = new SyndFeedImpl();

		syndFeed.setFeedType(type + "_" + version);
		syndFeed.setTitle(name);
		syndFeed.setLink(feedURL);
		syndFeed.setDescription(GetterUtil.getString(description, name));

		List entries = new ArrayList();

		syndFeed.setEntries(entries);

		Iterator itr = assets.iterator();

		while (itr.hasNext()) {
			TagsAsset asset = (TagsAsset)itr.next();

			String author = PortalUtil.getUserName(
				asset.getUserId(), asset.getUserName());

			String link = entryURL + "assetId=" + asset.getAssetId();

			String value = asset.getSummary();

			SyndEntry syndEntry = new SyndEntryImpl();

			syndEntry.setAuthor(author);
			syndEntry.setTitle(asset.getTitle());
			syndEntry.setLink(link);
			syndEntry.setPublishedDate(asset.getCreateDate());

			SyndContent syndContent = new SyndContentImpl();

			syndContent.setType("html");
			syndContent.setValue(value);

			syndEntry.setDescription(syndContent);

			entries.add(syndEntry);
		}

		try {
			return RSSUtil.export(syndFeed);
		}
		catch (FeedException fe) {
			throw new SystemException(fe);
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}
	}

}