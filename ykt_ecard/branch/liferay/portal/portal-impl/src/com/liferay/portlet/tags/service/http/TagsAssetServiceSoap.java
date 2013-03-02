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

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;

import com.liferay.portlet.tags.service.TagsAssetServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="TagsAssetServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides a SOAP utility for the
 * <code>com.liferay.portlet.tags.service.TagsAssetServiceUtil</code> service
 * utility. The static methods of this class calls the same methods of the
 * service utility. However, the signatures are different because it is
 * difficult for SOAP to support certain types.
 * </p>
 *
 * <p>
 * ServiceBuilder follows certain rules in translating the methods. For example,
 * if the method in the service utility returns a <code>java.util.List</code>,
 * that is translated to an array of
 * <code>com.liferay.portlet.tags.model.TagsAssetSoap</code>. If the method in the
 * service utility returns a <code>com.liferay.portlet.tags.model.TagsAsset</code>,
 * that is translated to a <code>com.liferay.portlet.tags.model.TagsAssetSoap</code>.
 * Methods that SOAP cannot safely wire are skipped.
 * </p>
 *
 * <p>
 * The benefits of using the SOAP utility is that it is cross platform
 * compatible. SOAP allows different languages like Java, .NET, C++, PHP, and
 * even Perl, to call the generated services. One drawback of SOAP is that it is
 * slow because it needs to serialize all calls into a text format (XML).
 * </p>
 *
 * <p>
 * You can see a list of services at
 * http://localhost:8080/tunnel-web/secure/axis. Set the property
 * <code>tunnel.servlet.hosts.allowed</code> in portal.properties to configure
 * security.
 * </p>
 *
 * <p>
 * The SOAP utility is only generated for remote services.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.tags.service.TagsAssetServiceUtil
 * @see com.liferay.portlet.tags.service.http.TagsAssetServiceHttp
 * @see com.liferay.portlet.tags.service.model.TagsAssetSoap
 *
 */
public class TagsAssetServiceSoap {
	public static void deleteAsset(long assetId) throws RemoteException {
		try {
			TagsAssetServiceUtil.deleteAsset(assetId);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.tags.model.TagsAssetSoap getAsset(
		long assetId) throws RemoteException {
		try {
			com.liferay.portlet.tags.model.TagsAsset returnValue = TagsAssetServiceUtil.getAsset(assetId);

			return com.liferay.portlet.tags.model.TagsAssetSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static java.lang.String getAssetsRSS(long groupId,
		long[] classNameIds, long[] entryIds, long[] notEntryIds,
		boolean andOperator, java.lang.String orderByCol1,
		java.lang.String orderByCol2, java.lang.String orderByType1,
		java.lang.String orderByType2, boolean excludeZeroViewCount,
		java.util.Date publishDate, java.util.Date expirationDate, int max,
		java.lang.String type, double version, java.lang.String displayStyle,
		java.lang.String feedURL, java.lang.String entryURL)
		throws RemoteException {
		try {
			java.lang.String returnValue = TagsAssetServiceUtil.getAssetsRSS(groupId,
					classNameIds, entryIds, notEntryIds, andOperator,
					orderByCol1, orderByCol2, orderByType1, orderByType2,
					excludeZeroViewCount, publishDate, expirationDate, max,
					type, version, displayStyle, feedURL, entryURL);

			return returnValue;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.tags.model.TagsAssetType[] getAssetTypes(
		java.lang.String languageId) throws RemoteException {
		try {
			com.liferay.portlet.tags.model.TagsAssetType[] returnValue = TagsAssetServiceUtil.getAssetTypes(languageId);

			return returnValue;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.tags.model.TagsAssetDisplay[] getCompanyAssetDisplays(
		long companyId, int begin, int end, java.lang.String languageId)
		throws RemoteException {
		try {
			com.liferay.portlet.tags.model.TagsAssetDisplay[] returnValue = TagsAssetServiceUtil.getCompanyAssetDisplays(companyId,
					begin, end, languageId);

			return returnValue;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.tags.model.TagsAssetSoap[] getCompanyAssets(
		long companyId, int begin, int end) throws RemoteException {
		try {
			java.util.List returnValue = TagsAssetServiceUtil.getCompanyAssets(companyId,
					begin, end);

			return com.liferay.portlet.tags.model.TagsAssetSoap.toSoapModels(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static int getCompanyAssetsCount(long companyId)
		throws RemoteException {
		try {
			int returnValue = TagsAssetServiceUtil.getCompanyAssetsCount(companyId);

			return returnValue;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static java.lang.String getCompanyAssetsRSS(long companyId, int max,
		java.lang.String type, double version, java.lang.String displayStyle,
		java.lang.String feedURL, java.lang.String entryURL)
		throws RemoteException {
		try {
			java.lang.String returnValue = TagsAssetServiceUtil.getCompanyAssetsRSS(companyId,
					max, type, version, displayStyle, feedURL, entryURL);

			return returnValue;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.tags.model.TagsAssetSoap incrementViewCounter(
		java.lang.String className, long classPK) throws RemoteException {
		try {
			com.liferay.portlet.tags.model.TagsAsset returnValue = TagsAssetServiceUtil.incrementViewCounter(className,
					classPK);

			return com.liferay.portlet.tags.model.TagsAssetSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.tags.model.TagsAssetDisplay[] searchAssetDisplays(
		long companyId, java.lang.String portletId, java.lang.String keywords,
		java.lang.String languageId, int begin, int end)
		throws RemoteException {
		try {
			com.liferay.portlet.tags.model.TagsAssetDisplay[] returnValue = TagsAssetServiceUtil.searchAssetDisplays(companyId,
					portletId, keywords, languageId, begin, end);

			return returnValue;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static int searchAssetDisplaysCount(long companyId,
		java.lang.String portletId, java.lang.String keywords,
		java.lang.String languageId) throws RemoteException {
		try {
			int returnValue = TagsAssetServiceUtil.searchAssetDisplaysCount(companyId,
					portletId, keywords, languageId);

			return returnValue;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.tags.model.TagsAssetSoap updateAsset(
		long groupId, java.lang.String className, long classPK,
		java.lang.String[] entryNames, java.util.Date startDate,
		java.util.Date endDate, java.util.Date publishDate,
		java.util.Date expirationDate, java.lang.String mimeType,
		java.lang.String title, java.lang.String description,
		java.lang.String summary, java.lang.String url, int height, int width,
		java.lang.Integer priority) throws RemoteException {
		try {
			com.liferay.portlet.tags.model.TagsAsset returnValue = TagsAssetServiceUtil.updateAsset(groupId,
					className, classPK, entryNames, startDate, endDate,
					publishDate, expirationDate, mimeType, title, description,
					summary, url, height, width, priority);

			return com.liferay.portlet.tags.model.TagsAssetSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	private static Log _log = LogFactoryUtil.getLog(TagsAssetServiceSoap.class);
}