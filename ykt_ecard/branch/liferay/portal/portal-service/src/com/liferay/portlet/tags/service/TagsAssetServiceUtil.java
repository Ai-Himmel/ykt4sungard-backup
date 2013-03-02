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

package com.liferay.portlet.tags.service;


/**
 * <a href="TagsAssetServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.tags.service.TagsAssetService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.tags.service.TagsAssetServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.tags.service.TagsAssetService
 * @see com.liferay.portlet.tags.service.TagsAssetServiceFactory
 *
 */
public class TagsAssetServiceUtil {
	public static void deleteAsset(long assetId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		TagsAssetService tagsAssetService = TagsAssetServiceFactory.getService();

		tagsAssetService.deleteAsset(assetId);
	}

	public static com.liferay.portlet.tags.model.TagsAsset getAsset(
		long assetId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		TagsAssetService tagsAssetService = TagsAssetServiceFactory.getService();

		return tagsAssetService.getAsset(assetId);
	}

	public static java.lang.String getAssetsRSS(long groupId,
		long[] classNameIds, long[] entryIds, long[] notEntryIds,
		boolean andOperator, java.lang.String orderByCol1,
		java.lang.String orderByCol2, java.lang.String orderByType1,
		java.lang.String orderByType2, boolean excludeZeroViewCount,
		java.util.Date publishDate, java.util.Date expirationDate, int max,
		java.lang.String type, double version, java.lang.String displayStyle,
		java.lang.String feedURL, java.lang.String entryURL)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		TagsAssetService tagsAssetService = TagsAssetServiceFactory.getService();

		return tagsAssetService.getAssetsRSS(groupId, classNameIds, entryIds,
			notEntryIds, andOperator, orderByCol1, orderByCol2, orderByType1,
			orderByType2, excludeZeroViewCount, publishDate, expirationDate,
			max, type, version, displayStyle, feedURL, entryURL);
	}

	public static com.liferay.portlet.tags.model.TagsAssetType[] getAssetTypes(
		java.lang.String languageId) throws java.rmi.RemoteException {
		TagsAssetService tagsAssetService = TagsAssetServiceFactory.getService();

		return tagsAssetService.getAssetTypes(languageId);
	}

	public static com.liferay.portlet.tags.model.TagsAssetDisplay[] getCompanyAssetDisplays(
		long companyId, int begin, int end, java.lang.String languageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		TagsAssetService tagsAssetService = TagsAssetServiceFactory.getService();

		return tagsAssetService.getCompanyAssetDisplays(companyId, begin, end,
			languageId);
	}

	public static java.util.List getCompanyAssets(long companyId, int begin,
		int end)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException {
		TagsAssetService tagsAssetService = TagsAssetServiceFactory.getService();

		return tagsAssetService.getCompanyAssets(companyId, begin, end);
	}

	public static int getCompanyAssetsCount(long companyId)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException {
		TagsAssetService tagsAssetService = TagsAssetServiceFactory.getService();

		return tagsAssetService.getCompanyAssetsCount(companyId);
	}

	public static java.lang.String getCompanyAssetsRSS(long companyId, int max,
		java.lang.String type, double version, java.lang.String displayStyle,
		java.lang.String feedURL, java.lang.String entryURL)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		TagsAssetService tagsAssetService = TagsAssetServiceFactory.getService();

		return tagsAssetService.getCompanyAssetsRSS(companyId, max, type,
			version, displayStyle, feedURL, entryURL);
	}

	public static com.liferay.portlet.tags.model.TagsAsset incrementViewCounter(
		java.lang.String className, long classPK)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		TagsAssetService tagsAssetService = TagsAssetServiceFactory.getService();

		return tagsAssetService.incrementViewCounter(className, classPK);
	}

	public static com.liferay.portlet.tags.model.TagsAssetDisplay[] searchAssetDisplays(
		long companyId, java.lang.String portletId, java.lang.String keywords,
		java.lang.String languageId, int begin, int end)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		TagsAssetService tagsAssetService = TagsAssetServiceFactory.getService();

		return tagsAssetService.searchAssetDisplays(companyId, portletId,
			keywords, languageId, begin, end);
	}

	public static int searchAssetDisplaysCount(long companyId,
		java.lang.String portletId, java.lang.String keywords,
		java.lang.String languageId)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException {
		TagsAssetService tagsAssetService = TagsAssetServiceFactory.getService();

		return tagsAssetService.searchAssetDisplaysCount(companyId, portletId,
			keywords, languageId);
	}

	public static com.liferay.portlet.tags.model.TagsAsset updateAsset(
		long groupId, java.lang.String className, long classPK,
		java.lang.String[] entryNames, java.util.Date startDate,
		java.util.Date endDate, java.util.Date publishDate,
		java.util.Date expirationDate, java.lang.String mimeType,
		java.lang.String title, java.lang.String description,
		java.lang.String summary, java.lang.String url, int height, int width,
		java.lang.Integer priority)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		TagsAssetService tagsAssetService = TagsAssetServiceFactory.getService();

		return tagsAssetService.updateAsset(groupId, className, classPK,
			entryNames, startDate, endDate, publishDate, expirationDate,
			mimeType, title, description, summary, url, height, width, priority);
	}
}