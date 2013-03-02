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

package com.liferay.portlet.taggedcontent.util;

import com.liferay.portal.kernel.util.ArrayUtil;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.PortletPreferencesFactoryUtil;
import com.liferay.portlet.tags.model.TagsAsset;
import com.liferay.portlet.tags.service.TagsAssetLocalServiceUtil;
import com.liferay.util.CollectionFactory;
import com.liferay.util.xml.XMLFormatter;

import java.io.IOException;

import java.util.Map;

import javax.portlet.ActionRequest;
import javax.portlet.PortletPreferences;
import javax.portlet.PortletRequest;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.dom4j.Document;
import org.dom4j.DocumentFactory;
import org.dom4j.Element;

/**
 * <a href="AssetPublisherUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Raymond Augé
 *
 */
public class AssetPublisherUtil {

	public static void addAndStoreSelection(
			ActionRequest req, String className, long classPK, int assetOrder)
		throws Exception {

		String referringPortletResource =
			ParamUtil.getString(req, "referringPortletResource");

		if (Validator.isNull(referringPortletResource)) {
			return;
		}

		TagsAsset asset = TagsAssetLocalServiceUtil.getAsset(
			className, classPK);

		PortletPreferences prefs =
			PortletPreferencesFactoryUtil.getPortletSetup(
				req, referringPortletResource, true, true);

		addSelection(className, asset.getAssetId(), assetOrder, prefs);

		prefs.store();
	}

	public static void addSelection(ActionRequest req, PortletPreferences prefs)
		throws Exception {

		String assetType = ParamUtil.getString(req, "assetType");
		long assetId = ParamUtil.getLong(req, "assetId");
		int assetOrder = ParamUtil.getInteger(req, "assetOrder");

		addSelection(assetType, assetId, assetOrder, prefs);
	}

	public static void addSelection(
			String assetType, long assetId, int assetOrder,
			PortletPreferences prefs)
		throws Exception {

		String[] manualEntries = prefs.getValues(
			"manual-entries", new String[0]);

		String assetConfig = _assetConfiguration(assetType, assetId);

		if (assetOrder > -1) {
			manualEntries[assetOrder] = assetConfig;
		}
		else {
			manualEntries = ArrayUtil.append(manualEntries, assetConfig);
		}

		prefs.setValues("manual-entries", manualEntries);
	}

	public static void addRecentFolderId(
		PortletRequest req, String className, long classPK) {

		_getRecentFolderIds(req).put(className, new Long(classPK));
	}

	public static long getRecentFolderId(PortletRequest req, String className) {
		Long classPK = (Long)_getRecentFolderIds(req).get(className);

		if (classPK == null) {
			return 0;
		}
		else {
			return classPK.longValue();
		}
	}

	private static String _assetConfiguration(String assetType, long assetId) {
		String xml = null;

		try {
			DocumentFactory docFactory = DocumentFactory.getInstance();

			Document doc = docFactory.createDocument("UTF-8");

			Element asset = doc.addElement("asset");

			asset.addElement("asset-type").addText(assetType);
			asset.addElement("asset-id").addText(String.valueOf(assetId));

			xml = XMLFormatter.toString(doc, StringPool.BLANK);
		}
		catch (IOException ioe) {
			if (_log.isWarnEnabled()) {
				_log.warn(ioe);
			}
		}

		return xml;
	}

	private static Map _getRecentFolderIds(PortletRequest req) {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		HttpSession ses = httpReq.getSession();

		ThemeDisplay themeDisplay = (ThemeDisplay)req.getAttribute(
			WebKeys.THEME_DISPLAY);

		String key =
			AssetPublisherUtil.class + "_" + themeDisplay.getPortletGroupId();

		Map recentFolderIds = (Map)ses.getAttribute(key);

		if (recentFolderIds == null) {
			recentFolderIds = CollectionFactory.getHashMap();
		}

		ses.setAttribute(key, recentFolderIds);

		return recentFolderIds;
	}

	private static Log _log = LogFactory.getLog(AssetPublisherUtil.class);

}