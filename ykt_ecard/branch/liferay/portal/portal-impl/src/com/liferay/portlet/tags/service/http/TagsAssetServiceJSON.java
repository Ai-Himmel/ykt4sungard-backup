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

package com.liferay.portlet.tags.service.http;

import com.liferay.portlet.tags.service.TagsAssetServiceUtil;

import org.json.JSONArray;
import org.json.JSONObject;

/**
 * <a href="TagsAssetServiceJSON.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides a JSON utility for the
 * <code>com.liferay.portlet.tags.service.TagsAssetServiceUtil</code>
 * service utility. The static methods of this class calls the same methods of
 * the service utility. However, the signatures are different because it is
 * difficult for JSON to support certain types.
 * </p>
 *
 * <p>
 * ServiceBuilder follows certain rules in translating the methods. For example,
 * if the method in the service utility returns a <code>java.util.List</code>,
 * that is translated to a <code>org.json.JSONArray</code>. If the method in the
 * service utility returns a <code>com.liferay.portlet.tags.model.TagsAsset</code>,
 * that is translated to a <code>org.json.JSONObject</code>. Methods that JSON
 * cannot safely use are skipped. The logic for the translation is encapsulated
 * in <code>com.liferay.portlet.tags.service.http.TagsAssetJSONSerializer</code>.
 * </p>
 *
 * <p>
 * This allows you to call the the backend services directly from JavaScript.
 * See <code>portal-web/docroot/html/portlet/tags_admin/unpacked.js</code> for a
 * reference of how that portlet uses the generated JavaScript in
 * <code>portal-web/docroot/html/js/service.js</code> to call the backend
 * services directly from JavaScript.
 * </p>
 *
 * <p>
 * The JSON utility is only generated for remote services.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.tags.service.TagsAssetServiceUtil
 * @see com.liferay.portlet.tags.service.http.TagsAssetJSONSerializer
 *
 */
public class TagsAssetServiceJSON {
	public static void deleteAsset(long assetId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		TagsAssetServiceUtil.deleteAsset(assetId);
	}

	public static JSONObject getAsset(long assetId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		com.liferay.portlet.tags.model.TagsAsset returnValue = TagsAssetServiceUtil.getAsset(assetId);

		return TagsAssetJSONSerializer.toJSONObject(returnValue);
	}

	public static java.lang.String getAssetsRSS(long groupId,
		long[] classNameIds, long[] entryIds, long[] notEntryIds,
		boolean andOperator, java.lang.String orderByCol1,
		java.lang.String orderByCol2, java.lang.String orderByType1,
		java.lang.String orderByType2, boolean excludeZeroViewCount,
		java.util.Date publishDate, java.util.Date expirationDate, int max,
		java.lang.String type, double version, java.lang.String displayStyle,
		java.lang.String feedURL, java.lang.String entryURL)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		java.lang.String returnValue = TagsAssetServiceUtil.getAssetsRSS(groupId,
				classNameIds, entryIds, notEntryIds, andOperator, orderByCol1,
				orderByCol2, orderByType1, orderByType2, excludeZeroViewCount,
				publishDate, expirationDate, max, type, version, displayStyle,
				feedURL, entryURL);

		return returnValue;
	}

	public static com.liferay.portlet.tags.model.TagsAssetType[] getAssetTypes(
		java.lang.String languageId) throws java.rmi.RemoteException {
		com.liferay.portlet.tags.model.TagsAssetType[] returnValue = TagsAssetServiceUtil.getAssetTypes(languageId);

		return returnValue;
	}

	public static com.liferay.portlet.tags.model.TagsAssetDisplay[] getCompanyAssetDisplays(
		long companyId, int begin, int end, java.lang.String languageId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		com.liferay.portlet.tags.model.TagsAssetDisplay[] returnValue = TagsAssetServiceUtil.getCompanyAssetDisplays(companyId,
				begin, end, languageId);

		return returnValue;
	}

	public static JSONArray getCompanyAssets(long companyId, int begin, int end)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException {
		java.util.List returnValue = TagsAssetServiceUtil.getCompanyAssets(companyId,
				begin, end);

		return TagsAssetJSONSerializer.toJSONArray(returnValue);
	}

	public static int getCompanyAssetsCount(long companyId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException {
		int returnValue = TagsAssetServiceUtil.getCompanyAssetsCount(companyId);

		return returnValue;
	}

	public static java.lang.String getCompanyAssetsRSS(long companyId, int max,
		java.lang.String type, double version, java.lang.String displayStyle,
		java.lang.String feedURL, java.lang.String entryURL)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		java.lang.String returnValue = TagsAssetServiceUtil.getCompanyAssetsRSS(companyId,
				max, type, version, displayStyle, feedURL, entryURL);

		return returnValue;
	}

	public static JSONObject incrementViewCounter(java.lang.String className,
		long classPK)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		com.liferay.portlet.tags.model.TagsAsset returnValue = TagsAssetServiceUtil.incrementViewCounter(className,
				classPK);

		return TagsAssetJSONSerializer.toJSONObject(returnValue);
	}

	public static com.liferay.portlet.tags.model.TagsAssetDisplay[] searchAssetDisplays(
		long companyId, java.lang.String portletId, java.lang.String keywords,
		java.lang.String languageId, int begin, int end)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		com.liferay.portlet.tags.model.TagsAssetDisplay[] returnValue = TagsAssetServiceUtil.searchAssetDisplays(companyId,
				portletId, keywords, languageId, begin, end);

		return returnValue;
	}

	public static int searchAssetDisplaysCount(long companyId,
		java.lang.String portletId, java.lang.String keywords,
		java.lang.String languageId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException {
		int returnValue = TagsAssetServiceUtil.searchAssetDisplaysCount(companyId,
				portletId, keywords, languageId);

		return returnValue;
	}

	public static JSONObject updateAsset(long groupId,
		java.lang.String className, long classPK,
		java.lang.String[] entryNames, java.util.Date startDate,
		java.util.Date endDate, java.util.Date publishDate,
		java.util.Date expirationDate, java.lang.String mimeType,
		java.lang.String title, java.lang.String description,
		java.lang.String summary, java.lang.String url, int height, int width,
		java.lang.Integer priority)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		com.liferay.portlet.tags.model.TagsAsset returnValue = TagsAssetServiceUtil.updateAsset(groupId,
				className, classPK, entryNames, startDate, endDate,
				publishDate, expirationDate, mimeType, title, description,
				summary, url, height, width, priority);

		return TagsAssetJSONSerializer.toJSONObject(returnValue);
	}
}