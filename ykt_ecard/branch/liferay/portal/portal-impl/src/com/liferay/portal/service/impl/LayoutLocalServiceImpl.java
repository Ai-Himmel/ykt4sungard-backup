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

package com.liferay.portal.service.impl;

import com.liferay.portal.LayoutFriendlyURLException;
import com.liferay.portal.LayoutHiddenException;
import com.liferay.portal.LayoutImportException;
import com.liferay.portal.LayoutParentLayoutIdException;
import com.liferay.portal.LayoutTypeException;
import com.liferay.portal.NoSuchLayoutException;
import com.liferay.portal.NoSuchPortletPreferencesException;
import com.liferay.portal.PortalException;
import com.liferay.portal.RequiredLayoutException;
import com.liferay.portal.SystemException;
import com.liferay.portal.comm.CommLink;
import com.liferay.portal.kernel.language.LanguageUtil;
import com.liferay.portal.kernel.lar.PortletDataContext;
import com.liferay.portal.kernel.lar.PortletDataHandler;
import com.liferay.portal.kernel.lar.PortletDataHandlerKeys;
import com.liferay.portal.kernel.lar.UserIdStrategy;
import com.liferay.portal.kernel.portlet.FriendlyURLMapper;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.LocaleUtil;
import com.liferay.portal.kernel.util.MethodWrapper;
import com.liferay.portal.kernel.util.ReleaseInfo;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.kernel.zip.ZipReader;
import com.liferay.portal.kernel.zip.ZipWriter;
import com.liferay.portal.lar.AlwaysCurrentUserIdStrategy;
import com.liferay.portal.lar.CurrentUserIdStrategy;
import com.liferay.portal.lar.PortletDataContextImpl;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.LayoutReference;
import com.liferay.portal.model.LayoutSet;
import com.liferay.portal.model.LayoutTypePortlet;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.model.PortletPreferences;
import com.liferay.portal.model.Resource;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.Theme;
import com.liferay.portal.model.User;
import com.liferay.portal.model.impl.ColorSchemeImpl;
import com.liferay.portal.model.impl.GroupImpl;
import com.liferay.portal.model.impl.LayoutImpl;
import com.liferay.portal.model.impl.PortletImpl;
import com.liferay.portal.model.impl.ResourceImpl;
import com.liferay.portal.security.permission.ResourceActionsUtil;
import com.liferay.portal.service.LayoutLocalServiceUtil;
import com.liferay.portal.service.base.LayoutLocalServiceBaseImpl;
import com.liferay.portal.service.permission.PortletPermissionUtil;
import com.liferay.portal.theme.ThemeLoader;
import com.liferay.portal.theme.ThemeLoaderFactory;
import com.liferay.portal.util.ContentUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portal.util.PropsValues;
import com.liferay.portal.util.comparator.LayoutPriorityComparator;
import com.liferay.portal.velocity.VelocityContextPool;
import com.liferay.portlet.PortletPreferencesImpl;
import com.liferay.portlet.PortletPreferencesSerializer;
import com.liferay.portlet.documentlibrary.NoSuchFolderException;
import com.liferay.portlet.documentlibrary.model.DLFolder;
import com.liferay.portlet.documentlibrary.model.impl.DLFolderImpl;
import com.liferay.util.CollectionFactory;
import com.liferay.util.FileUtil;
import com.liferay.util.MapUtil;
import com.liferay.util.Normalizer;
import com.liferay.util.Time;
import com.liferay.util.xml.XMLFormatter;

import com.thoughtworks.xstream.XStream;

import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.StringReader;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.Properties;
import java.util.Set;

import javax.servlet.ServletContext;

import org.apache.commons.lang.time.StopWatch;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.dom4j.Document;
import org.dom4j.DocumentHelper;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 * <a href="LayoutLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Joel Kozikowski
 * @author Charles May
 * @author Raymond Augé
 * @author Jorge Ferrer
 * @author Bruno Farache
 *
 */
public class LayoutLocalServiceImpl extends LayoutLocalServiceBaseImpl {

	public Layout addLayout(
			long userId, long groupId, boolean privateLayout,
			long parentLayoutId, String name, String title, String description,
			String type, boolean hidden, String friendlyURL)
		throws PortalException, SystemException {

		Map localeNamesMap = new HashMap();

		Locale defaultLocale = LocaleUtil.getDefault();

		localeNamesMap.put(defaultLocale, name);

		return addLayout(
			userId, groupId, privateLayout, parentLayoutId, localeNamesMap,
			new HashMap(), description, type, hidden, friendlyURL);
	}

	public Layout addLayout(
			long userId, long groupId, boolean privateLayout,
			long parentLayoutId, Map localeNamesMap, Map localeTitlesMap,
			String description, String type, boolean hidden, String friendlyURL)
		throws PortalException, SystemException {

		return addLayout(
			userId, groupId, privateLayout, parentLayoutId, localeNamesMap,
			localeTitlesMap, description, type, hidden, friendlyURL,
			DLFolderImpl.DEFAULT_PARENT_FOLDER_ID);
	}

	public Layout addLayout(
			long userId, long groupId, boolean privateLayout,
			long parentLayoutId, String name, String title, String description,
			String type, boolean hidden, String friendlyURL, long dlFolderId)
		throws PortalException, SystemException {

		Map localeNamesMap = new HashMap();

		Locale defaultLocale = LocaleUtil.getDefault();

		localeNamesMap.put(defaultLocale, name);

		return addLayout(
			userId, groupId, privateLayout, parentLayoutId, localeNamesMap,
			new HashMap(), description, type, hidden, friendlyURL, dlFolderId);
	}

	public Layout addLayout(
			long userId, long groupId, boolean privateLayout,
			long parentLayoutId, Map localeNamesMap, Map localeTitlesMap,
			String description, String type, boolean hidden, String friendlyURL,
			long dlFolderId)
		throws PortalException, SystemException {

		// Layout

		User user = userPersistence.findByPrimaryKey(userId);
		long layoutId = getNextLayoutId(groupId, privateLayout);
		parentLayoutId = getParentLayoutId(
			groupId, privateLayout, parentLayoutId);
		friendlyURL = getFriendlyURL(friendlyURL);
		int priority = getNextPriority(groupId, privateLayout, parentLayoutId);

		validate(
			groupId, privateLayout, layoutId, parentLayoutId, type, hidden,
			friendlyURL);

		long plid = counterLocalService.increment();

		Layout layout = layoutPersistence.create(plid);

		layout.setGroupId(groupId);
		layout.setCompanyId(user.getCompanyId());
		layout.setPrivateLayout(privateLayout);
		layout.setLayoutId(layoutId);
		layout.setParentLayoutId(parentLayoutId);
		layout.setDescription(description);
		layout.setType(type);
		layout.setHidden(hidden);
		layout.setFriendlyURL(friendlyURL);
		layout.setPriority(priority);
		layout.setDlFolderId(dlFolderId);

		setLocalizedAttributes(layout, localeNamesMap, localeTitlesMap);

		layoutPersistence.update(layout);

		// Resources

		resourceLocalService.addResources(
			user.getCompanyId(), groupId, user.getUserId(),
			Layout.class.getName(), layout.getPlid(), false, true, true);

		// Layout set

		layoutSetLocalService.updatePageCount(groupId, privateLayout);

		return layout;
	}

	public void deleteLayout(long plid)
		throws PortalException, SystemException {

		Layout layout = layoutPersistence.findByPrimaryKey(plid);

		deleteLayout(layout, true);
	}

	public void deleteLayout(long groupId, boolean privateLayout, long layoutId)
		throws PortalException, SystemException {

		Layout layout = layoutPersistence.findByG_P_L(
			groupId, privateLayout, layoutId);

		deleteLayout(layout, true);
	}

	public void deleteLayout(Layout layout, boolean updateLayoutSet)
		throws PortalException, SystemException {

		// Child layouts

		List childLayouts = layoutPersistence.findByG_P_P(
			layout.getGroupId(), layout.isPrivateLayout(),
			layout.getLayoutId());

		for (int i = 0; i < childLayouts.size(); i++) {
			Layout childLayout = (Layout)childLayouts.get(i);

			deleteLayout(childLayout, updateLayoutSet);
		}

		// Portlet preferences

		portletPreferencesLocalService.deletePortletPreferences(
			PortletKeys.PREFS_OWNER_ID_DEFAULT,
			PortletKeys.PREFS_OWNER_TYPE_LAYOUT, layout.getPlid());

		// Ratings

		ratingsStatsLocalService.deleteStats(
			Layout.class.getName(), layout.getPlid());

		// Message boards

		mbMessageLocalService.deleteDiscussionMessages(
			Layout.class.getName(), layout.getPlid());

		// Journal content searches

		journalContentSearchLocalService.deleteLayoutContentSearches(
			layout.getGroupId(), layout.isPrivateLayout(),
			layout.getLayoutId());

		// Icon

		ImageLocalUtil.deleteImage(layout.getIconImageId());

		// Resources

		String primKey = layout.getPlid() + PortletImpl.LAYOUT_SEPARATOR + "%";

		Iterator itr = resourceFinder.findByC_P(
			layout.getCompanyId(), primKey).iterator();

		while (itr.hasNext()) {
			Resource resource = (Resource)itr.next();

			resourceLocalService.deleteResource(resource);
		}

		resourceLocalService.deleteResource(
			layout.getCompanyId(), Layout.class.getName(),
			ResourceImpl.SCOPE_INDIVIDUAL, layout.getPlid());

		// Layout

		layoutPersistence.remove(layout.getPlid());

		// Layout set

		if (updateLayoutSet) {
			layoutSetLocalService.updatePageCount(
				layout.getGroupId(), layout.isPrivateLayout());
		}
	}

	public void deleteLayouts(long groupId, boolean privateLayout)
		throws PortalException, SystemException {

		// Layouts

		List layouts = layoutPersistence.findByG_P_P(
			groupId, privateLayout, LayoutImpl.DEFAULT_PARENT_LAYOUT_ID);

		Iterator itr = layouts.iterator();

		while (itr.hasNext()) {
			Layout layout = (Layout)itr.next();

			try {
				deleteLayout(layout, false);
			}
			catch (NoSuchLayoutException nsle) {
			}
		}

		// Layout set

		layoutSetLocalService.updatePageCount(groupId, privateLayout);
	}

	public byte[] exportLayouts(
			long groupId, boolean privateLayout, Map parameterMap)
		throws PortalException, SystemException {

		return exportLayouts(groupId, privateLayout, null, parameterMap);
	}

	public byte[] exportLayouts(
			long groupId, boolean privateLayout, long[] layoutIds,
			Map parameterMap)
		throws PortalException, SystemException {

		boolean exportPermissions = MapUtil.getBoolean(
			parameterMap, PortletDataHandlerKeys.PERMISSIONS);
		boolean exportUserPermissions = MapUtil.getBoolean(
			parameterMap, PortletDataHandlerKeys.USER_PERMISSIONS);
		boolean exportPortletData = MapUtil.getBoolean(
			parameterMap, PortletDataHandlerKeys.PORTLET_DATA);
		boolean exportPortletSetup = MapUtil.getBoolean(
			parameterMap, PortletDataHandlerKeys.PORTLET_SETUP);
		boolean exportPortletUserPreferences = MapUtil.getBoolean(
			parameterMap, PortletDataHandlerKeys.PORTLET_USER_PREFERENCES);
		boolean exportTheme = MapUtil.getBoolean(
			parameterMap, PortletDataHandlerKeys.THEME);

		if (_log.isDebugEnabled()) {
			_log.debug("Export permissions " + exportPermissions);
			_log.debug("Export user permissions " + exportUserPermissions);
			_log.debug("Export portlet data " + exportPortletData);
			_log.debug("Export portlet setup " + exportPortletSetup);
			_log.debug(
				"Export portlet user preferences " +
					exportPortletUserPreferences);
			_log.debug("Export theme " + exportTheme);
		}

		StopWatch stopWatch = null;

		if (_log.isInfoEnabled()) {
			stopWatch = new StopWatch();

			stopWatch.start();
		}

		LayoutCache layoutCache = new LayoutCache();

		LayoutSet layoutSet = layoutSetLocalService.getLayoutSet(
			groupId, privateLayout);

		long companyId = layoutSet.getCompanyId();
		long defaultUserId = userLocalService.getDefaultUserId(companyId);

		ZipWriter zipWriter = new ZipWriter();

		PortletDataContext context = new PortletDataContextImpl(
			companyId, groupId, parameterMap, CollectionFactory.getHashSet(),
			zipWriter);

		Group guestGroup = groupLocalService.getGroup(
			companyId, GroupImpl.GUEST);

		// Build compatibility

		Document doc = DocumentHelper.createDocument();

		Element root = doc.addElement("root");

		Element header = root.addElement("header");

		header.addAttribute(
			"build-number", String.valueOf(ReleaseInfo.getBuildNumber()));
		header.addAttribute("group-id", String.valueOf(groupId));
		header.addAttribute("private-layout", String.valueOf(privateLayout));
		header.addAttribute("export-date", Time.getRFC822());
		header.addAttribute("theme-id", layoutSet.getThemeId());
		header.addAttribute("color-scheme-id", layoutSet.getColorSchemeId());
		header.addAttribute("type", "layouts");

		// Layouts

		Set portletIds = new LinkedHashSet();

		List layouts = null;

		if ((layoutIds == null) || (layoutIds.length == 0)) {
			layouts = getLayouts(groupId, privateLayout);
		}
		else {
			layouts = getLayouts(groupId, privateLayout, layoutIds);
		}

		Iterator itr = layouts.iterator();

		while (itr.hasNext()) {
			Layout layout = (Layout)itr.next();

			context.setPlid(layout.getPlid());

			Element layoutEl = root.addElement("layout");

			layoutEl.addAttribute(
				"layout-id", String.valueOf(layout.getLayoutId()));
			layoutEl.addElement("parent-layout-id").addText(
				String.valueOf(layout.getParentLayoutId()));
			layoutEl.addElement("name").addCDATA(layout.getName());
			layoutEl.addElement("title").addCDATA(layout.getTitle());
			layoutEl.addElement("type").addText(layout.getType());
			layoutEl.addElement("type-settings").addCDATA(
				layout.getTypeSettings());
			layoutEl.addElement("hidden").addText(
				String.valueOf(layout.getHidden()));
			layoutEl.addElement("friendly-url").addText(
				layout.getFriendlyURL());
			layoutEl.addElement("theme-id").addText(layout.getThemeId());
			layoutEl.addElement("color-scheme-id").addText(
				layout.getColorSchemeId());
			layoutEl.addElement("priority").addText(
				String.valueOf(layout.getPriority()));

			Element permissionsEl = layoutEl.addElement("permissions");

			// Layout permissions

			if (exportPermissions) {
				exportLayoutPermissions(
					layoutCache, companyId, groupId, guestGroup, layout,
					permissionsEl, exportUserPermissions);
			}

			if (layout.getType().equals(LayoutImpl.TYPE_PORTLET)) {
				LayoutTypePortlet layoutTypePortlet =
					(LayoutTypePortlet)layout.getLayoutType();

				// The order of the export is important. You must always export
				// the portlet data first, then the portlet preferences, then
				// the portlet permissions. The export of the portlet data
				// process may modify the portlet preferences, and those changes
				// should be included in the exported LAR.

				// Portlet data

				if (exportPortletData) {
					exportPortletData(
						context, layout, layoutTypePortlet, layoutEl);
				}

				// Portlet preferences

				if (exportPortletSetup) {
					exportPortletPreferences(
						PortletKeys.PREFS_OWNER_ID_DEFAULT,
						PortletKeys.PREFS_OWNER_TYPE_LAYOUT, false,
						layout.getPlid(), layoutTypePortlet, layoutEl);

					exportPortletPreferences(
						layout.getGroupId(),
						PortletKeys.PREFS_OWNER_TYPE_GROUP, false,
						layout.getPlid(), layoutTypePortlet, layoutEl);

					exportPortletPreferences(
						layout.getCompanyId(),
						PortletKeys.PREFS_OWNER_TYPE_COMPANY, false,
						layout.getPlid(), layoutTypePortlet, layoutEl);
				}

				if (exportPortletUserPreferences) {
					exportPortletPreferences(
						defaultUserId, PortletKeys.PREFS_OWNER_TYPE_USER,
						true, layout.getPlid(), layoutTypePortlet,
						layoutEl);
				}

				// Portlet permissions

				if (exportPermissions) {
					exportPortletPermissions(
						layoutCache, companyId, groupId, guestGroup,
						layout, layoutTypePortlet, portletIds, permissionsEl,
						exportUserPermissions);
				}
			}
		}

		// Portlet preferences

		if (exportPortletUserPreferences) {
			exportPortletPreferences(
				groupId, PortletKeys.PREFS_OWNER_TYPE_GROUP,
				PortletKeys.PREFS_PLID_SHARED, false, root);

		}

		Element rolesEl = root.addElement("roles");

		// Layout roles

		if (exportPermissions) {
			exportLayoutRoles(layoutCache, companyId, groupId, rolesEl);
		}

		// Portlet roles

		if (exportPermissions) {
			exportPortletRoles(
				layoutCache, companyId, groupId, portletIds, rolesEl);
		}

		// Comments

		exportComments(context, root);

		// Ratings

		exportRatings(context, root);

		// Tags

		exportTags(context, root);

		// Look and feel

		byte[] themeZip = null;

		try {
			if (exportTheme) {
				themeZip = exportTheme(layoutSet);
			}
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}

		// XML

		if (_log.isInfoEnabled()) {
			_log.info("Exporting layouts takes " + stopWatch.getTime() + " ms");
		}

		// Zip

		try {
			zipWriter.addEntry("layouts.xml", XMLFormatter.toString(doc));

			if (themeZip != null) {
				zipWriter.addEntry("theme.zip", themeZip);
			}

			return zipWriter.finish();
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}
	}

	public byte[] exportPortletInfo(
			long plid, String portletId, Map parameterMap)
		throws PortalException, SystemException {

		boolean exportPortletSetup = MapUtil.getBoolean(
			parameterMap, PortletDataHandlerKeys.PORTLET_SETUP);
		boolean exportPortletUserPreferences = MapUtil.getBoolean(
			parameterMap, PortletDataHandlerKeys.PORTLET_USER_PREFERENCES);

		StopWatch stopWatch = null;

		if (_log.isInfoEnabled()) {
			stopWatch = new StopWatch();

			stopWatch.start();
		}

		Layout layout = LayoutLocalServiceUtil.getLayout(plid);

		if (!layout.getType().equals(LayoutImpl.TYPE_PORTLET)) {
			throw new LayoutImportException(
				"Layout type " + layout.getType() + " is not valid");
		}

		LayoutTypePortlet layoutTypePortlet =
			(LayoutTypePortlet)layout.getLayoutType();

		if (!layoutTypePortlet.hasPortletId(portletId)) {
			throw new LayoutImportException(
				"The specified layout does not have portlet " + portletId);
		}

		long companyId = layout.getCompanyId();
		long defaultUserId = userLocalService.getDefaultUserId(companyId);

		ZipWriter zipWriter = new ZipWriter();

		PortletDataContext context = new PortletDataContextImpl(
			companyId, layout.getGroupId(), parameterMap,
			CollectionFactory.getHashSet(), zipWriter);

		context.setPlid(plid);

		// Build compatibility

		Document doc = DocumentHelper.createDocument();

		Element root = doc.addElement("root");

		Element header = root.addElement("header");

		header.addAttribute(
			"build-number", String.valueOf(ReleaseInfo.getBuildNumber()));
		header.addAttribute("group-id", String.valueOf(layout.getGroupId()));
		header.addAttribute("export-date", Time.getRFC822());
		header.addAttribute("type", "portlet");

		// Data

		PortletPreferences portletPreferences = (PortletPreferences)
			portletPreferencesLocalService.getPortletPreferences(plid).get(0);

		javax.portlet.PortletPreferences jxPrefs =
			portletPreferencesLocalService.getPreferences(
				layout.getCompanyId(), portletPreferences.getOwnerId(),
				portletPreferences.getOwnerType(), plid, portletId);

		exportPortletData(context, portletId, jxPrefs, root);

		// Comments

		exportComments(context, root);

		// Ratings

		exportRatings(context, root);

		// Tags

		exportTags(context, root);

		// Portlet preferences

		if (exportPortletSetup) {
			exportPortletPreferences(
				PortletKeys.PREFS_OWNER_ID_DEFAULT,
				PortletKeys.PREFS_OWNER_TYPE_LAYOUT, false, layout, portletId,
				root);

			exportPortletPreferences(
				layout.getGroupId(), PortletKeys.PREFS_OWNER_TYPE_GROUP, false,
				layout, portletId, root);

			exportPortletPreferences(
				layout.getCompanyId(), PortletKeys.PREFS_OWNER_TYPE_COMPANY,
				false, layout, portletId, root);
		}

		if (exportPortletUserPreferences) {
			exportPortletPreferences(
				defaultUserId, PortletKeys.PREFS_OWNER_TYPE_USER,
				true, layout, portletId, root);
		}

		// XML

		if (_log.isInfoEnabled()) {
			_log.info(
				"Exporting portlet info takes " + stopWatch.getTime() + " ms");
		}

		// Zip

		try {
			zipWriter.addEntry("portlet.xml", XMLFormatter.toString(doc));

			return zipWriter.finish();
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}
	}

	public long getDefaultPlid(long groupId) throws SystemException {
		if (groupId > 0) {
			List layouts = layoutPersistence.findByGroupId(groupId, 0, 1);

			if (layouts.size() > 0) {
				Layout layout = (Layout)layouts.get(0);

				return layout.getPlid();
			}
		}

		return LayoutImpl.DEFAULT_PLID;
	}

	public long getDefaultPlid(long groupId, boolean privateLayout)
		throws SystemException {

		if (groupId > 0) {
			List layouts = layoutPersistence.findByG_P(
				groupId, privateLayout, 0, 1);

			if (layouts.size() > 0) {
				Layout layout = (Layout)layouts.get(0);

				return layout.getPlid();
			}
		}

		return LayoutImpl.DEFAULT_PLID;
	}

	public Layout getDLFolderLayout(long dlFolderId)
		throws PortalException, SystemException {

		return layoutPersistence.findByDLFolderId(dlFolderId);
	}

	public Layout getFriendlyURLLayout(
			long groupId, boolean privateLayout, String friendlyURL)
		throws PortalException, SystemException {

		if (Validator.isNull(friendlyURL)) {
			throw new NoSuchLayoutException();
		}

		friendlyURL = getFriendlyURL(friendlyURL);

		return layoutPersistence.findByG_P_F(
			groupId, privateLayout, friendlyURL);
	}

	public Layout getLayout(long plid)
		throws PortalException, SystemException {

		return layoutPersistence.findByPrimaryKey(plid);
	}

	public Layout getLayout(long groupId, boolean privateLayout, long layoutId)
		throws PortalException, SystemException {

		return layoutPersistence.findByG_P_L(groupId, privateLayout, layoutId);
	}

	public Layout getLayoutByIconImageId(long iconImageId)
		throws PortalException, SystemException {

		return layoutPersistence.findByIconImageId(iconImageId);
	}

	public List getLayouts(long groupId, boolean privateLayout)
		throws SystemException {

		return layoutPersistence.findByG_P(groupId, privateLayout);
	}

	public List getLayouts(
			long groupId, boolean privateLayout, long parentLayoutId)
		throws SystemException {

		return layoutPersistence.findByG_P_P(
			groupId, privateLayout, parentLayoutId);
	}

	public List getLayouts(
			long groupId, boolean privateLayout, long parentLayoutId, int begin,
			int end)
		throws SystemException {

		return layoutPersistence.findByG_P_P(
			groupId, privateLayout, parentLayoutId, begin, end);
	}

	public List getLayouts(
			long groupId, boolean privateLayout, long[] layoutIds)
		throws PortalException, SystemException {

		List layouts = new ArrayList();

		for (int i = 0; i < layoutIds.length; i++) {
			Layout layout = getLayout(groupId, privateLayout, layoutIds[i]);

			layouts.add(layout);
		}

		return layouts;
	}

	public LayoutReference[] getLayouts(
			long companyId, String portletId, String prefsKey,
			String prefsValue)
		throws SystemException {

		List list = layoutFinder.findByC_P_P(
			companyId, portletId, prefsKey, prefsValue);

		return (LayoutReference[])list.toArray(new LayoutReference[0]);
	}

	public void importLayouts(
			long userId, long groupId, boolean privateLayout, Map parameterMap,
			File file)
		throws PortalException, SystemException {

		try {
			importLayouts(
				userId, groupId, privateLayout, parameterMap,
				new FileInputStream(file));
		}
		catch (FileNotFoundException fnfe) {
			throw new SystemException(fnfe);
		}
	}

	public void importLayouts(
			long userId, long groupId, boolean privateLayout, Map parameterMap,
			InputStream is)
		throws PortalException, SystemException {

		boolean deleteMissingLayouts = MapUtil.getBoolean(
			parameterMap, PortletDataHandlerKeys.DELETE_MISSING_LAYOUTS,
			Boolean.TRUE.booleanValue());
		boolean deletePortletData = MapUtil.getBoolean(
			parameterMap, PortletDataHandlerKeys.DELETE_PORTLET_DATA);
		boolean importPermissions = MapUtil.getBoolean(
			parameterMap, PortletDataHandlerKeys.PERMISSIONS);
		boolean importUserPermissions = MapUtil.getBoolean(
			parameterMap, PortletDataHandlerKeys.PERMISSIONS);
		boolean importPortletData = MapUtil.getBoolean(
			parameterMap, PortletDataHandlerKeys.PORTLET_DATA);
		boolean importPortletSetup = MapUtil.getBoolean(
			parameterMap, PortletDataHandlerKeys.PORTLET_SETUP);
		boolean importPortletUserPreferences = MapUtil.getBoolean(
			parameterMap, PortletDataHandlerKeys.PORTLET_USER_PREFERENCES);
		boolean importTheme = MapUtil.getBoolean(
			parameterMap, PortletDataHandlerKeys.THEME);
		String userIdStrategy = MapUtil.getString(
			parameterMap, PortletDataHandlerKeys.USER_ID_STRATEGY);

		if (_log.isDebugEnabled()) {
			_log.debug("Delete portlet data " + deletePortletData);
			_log.debug("Import permissions " + importPermissions);
			_log.debug("Import user permissions " + importUserPermissions);
			_log.debug("Import portlet data " + importPortletData);
			_log.debug("Import portlet setup " + importPortletSetup);
			_log.debug(
				"Import portlet user preferences " +
					importPortletUserPreferences);
			_log.debug("Import theme " + importTheme);
		}

		StopWatch stopWatch = null;

		if (_log.isInfoEnabled()) {
			stopWatch = new StopWatch();

			stopWatch.start();
		}

        LayoutCache layoutCache = new LayoutCache();

		LayoutSet layoutSet = layoutSetLocalService.getLayoutSet(
			groupId, privateLayout);

		long companyId = layoutSet.getCompanyId();

		User user = userPersistence.findByPrimaryKey(userId);

		// User ID strategy

		UserIdStrategy strategy = null;

		if (UserIdStrategy.ALWAYS_CURRENT_USER_ID.equals(userIdStrategy)) {
			strategy = new AlwaysCurrentUserIdStrategy(user);
		}
		else if (UserIdStrategy.CURRENT_USER_ID.equals(userIdStrategy)) {
			strategy = new CurrentUserIdStrategy(user);
		}

		ZipReader zipReader = new ZipReader(is);

		PortletDataContext context = new PortletDataContextImpl(
			companyId, groupId, parameterMap, CollectionFactory.getHashSet(),
			strategy, zipReader);

		Group guestGroup = groupLocalService.getGroup(
			companyId, GroupImpl.GUEST);

		// Zip

		Element root = null;
		byte[] themeZip = null;

		try {

			// XML

			String xml = zipReader.getEntryAsString("layouts.xml");

			SAXReader reader = new SAXReader();

			Document doc = reader.read(new StringReader(xml));

			root = doc.getRootElement();

			// Look and feel

			if (importTheme) {
				themeZip = zipReader.getEntryAsByteArray("theme.zip");
			}
		}
		catch (Exception e) {
			throw new SystemException(e);
		}

		// Build compatibility

		Element header = (Element)root.element("header");

		int buildNumber = ReleaseInfo.getBuildNumber();

		int importBuildNumber = GetterUtil.getInteger(
			header.attributeValue("build-number"));

		if (buildNumber != importBuildNumber) {
			throw new LayoutImportException(
				"LAR build number " + importBuildNumber + " does not match " +
					"portal build number " + buildNumber);
		}

		// Look and feel

		String themeId = header.attributeValue("theme-id");
		String colorSchemeId = header.attributeValue("color-scheme-id");

		boolean useThemeZip = false;

		if (themeZip != null) {
			try {
				String importThemeId = importTheme(layoutSet, themeZip);

				if (importThemeId != null) {
					themeId = importThemeId;
					colorSchemeId =
						ColorSchemeImpl.getDefaultRegularColorSchemeId();

					useThemeZip = true;
				}

				if (_log.isDebugEnabled()) {
					_log.debug(
						"Importing theme takes " + stopWatch.getTime() + " ms");
				}
			}
			catch (Exception e) {
				throw new SystemException(e);
			}
		}

		boolean wapTheme = false;

		layoutSetLocalService.updateLookAndFeel(
			groupId, privateLayout, themeId, colorSchemeId, StringPool.BLANK,
			wapTheme);

		// Read comments, ratings, and tags to make them available to the data
		// handlers through the context

		readComments(context, root);
		readRatings(context, root);
		readTags(context, root);

		// Layouts

		Set newLayoutIds = CollectionFactory.getHashSet();

		Iterator itr = root.elements("layout").iterator();

		if (_log.isDebugEnabled()) {
			if (itr.hasNext()) {
				_log.debug("Importing layouts");
			}
		}

		while (itr.hasNext()) {
			Element layoutEl = (Element)itr.next();

			long layoutId = GetterUtil.getInteger(
				layoutEl.attributeValue("layout-id"));
			long parentLayoutId = GetterUtil.getInteger(
				layoutEl.elementText("parent-layout-id"));

			if (_log.isDebugEnabled()) {
				_log.debug(
					"Importing layout with layout id " + layoutId +
						" and parent layout id " + parentLayoutId);
			}

			String name = layoutEl.elementText("name");
			String title = layoutEl.elementText("title");
			String type = layoutEl.elementText("type");
			String typeSettings = layoutEl.elementText("type-settings");
			boolean hidden = GetterUtil.getBoolean(
				layoutEl.elementText("hidden"));
			String friendlyURL = layoutEl.elementText("friendly-url");

			if (useThemeZip) {
				themeId = StringPool.BLANK;
				colorSchemeId = StringPool.BLANK;
			}
			else {
				themeId = layoutEl.elementText("theme-id");
				colorSchemeId = layoutEl.elementText("color-scheme-id");
			}

			int priority = GetterUtil.getInteger(
				layoutEl.elementText("priority"));

			Layout layout = layoutPersistence.fetchByG_P_L(
				groupId, privateLayout, layoutId);

			if (_log.isDebugEnabled()) {
				if (layout == null) {
					_log.debug(
						"Layout with {groupId=" + groupId + ",privateLayout=" +
							privateLayout + ",layoutId=" + layoutId +
								"} does not exist");
				}
				else {
					_log.debug(
						"Layout with {groupId=" + groupId + ",privateLayout=" +
							privateLayout + ",layoutId=" + layoutId +
								"} exists");
				}
			}

			if (layout == null) {
				long plid = counterLocalService.increment();

				layout = layoutPersistence.create(plid);

				layout.setGroupId(groupId);
				layout.setPrivateLayout(privateLayout);
				layout.setLayoutId(layoutId);
			}

			layout.setCompanyId(user.getCompanyId());
			layout.setParentLayoutId(parentLayoutId);
			layout.setName(name);
			layout.setTitle(title);
			layout.setType(type);
			layout.setTypeSettings(typeSettings);
			layout.setHidden(hidden);
			layout.setFriendlyURL(friendlyURL);
			layout.setThemeId(themeId);
			layout.setColorSchemeId(colorSchemeId);
			layout.setPriority(priority);

			fixTypeSettings(layout);

			layoutPersistence.update(layout);

			context.setPlid(layout.getPlid());

			newLayoutIds.add(new Long(layoutId));

			Element permissionsEl = layoutEl.element("permissions");

			// Layout permissions

			if (importPermissions) {
				importLayoutPermissions(
					layoutCache, companyId, groupId, guestGroup, layout,
					permissionsEl, importUserPermissions);
			}

			// The order of the import is important. You must always import
			// the portlet preferences first, then the portlet data, then
			// the portlet permissions. The import of the portlet data
			// assumes that portlet preferences already exist.

			// Delete portlet data

			if (deletePortletData) {
				deletePortletData(context, layout, layoutEl);
			}

			// Portlet preferences

			importPortletPreferences(
				layoutSet.getCompanyId(), layout.getPlid(), layoutEl,
				importPortletSetup, importPortletUserPreferences);

			// Portlet data

			if (importPortletData) {
				importPortletData(context, layout, layoutEl);
			}

			// Portlet permissions

			if (importPermissions) {
				importPortletPermissions(
					layoutCache, companyId, groupId, guestGroup, layout,
					permissionsEl, importUserPermissions);
			}
		}

		Element rolesEl = (Element)root.element("roles");

		// Layout roles

		if (importPermissions) {
			importLayoutRoles(layoutCache, companyId, groupId, rolesEl);
		}

		// Portlet roles

		if (importPermissions) {
			importPortletRoles(layoutCache, companyId, groupId, rolesEl);
		}

		// Delete missing layouts

		if (deleteMissingLayouts) {
			deleteMissingLayouts(groupId, privateLayout, newLayoutIds);
		}

		// Page count

		layoutSetLocalService.updatePageCount(groupId, privateLayout);

		if (_log.isInfoEnabled()) {
			_log.info("Importing layouts takes " + stopWatch.getTime() + " ms");
		}
	}

	public void importPortletInfo(
			long userId, long plid, String portletId, Map parameterMap,
			File file)
		throws PortalException, SystemException {

		try {
			importPortletInfo(
				userId, plid, portletId, parameterMap,
				new FileInputStream(file));
		}
		catch (FileNotFoundException fnfe) {
			throw new SystemException(fnfe);
		}
	}

	public void importPortletInfo(
			long userId, long plid, String portletId, Map parameterMap,
			InputStream is)
		throws PortalException, SystemException {

		boolean deletePortletData = MapUtil.getBoolean(
			parameterMap, PortletDataHandlerKeys.DELETE_PORTLET_DATA);
		boolean importPortletData = MapUtil.getBoolean(
			parameterMap, PortletDataHandlerKeys.PORTLET_DATA);
		boolean importPortletSetup = MapUtil.getBoolean(
			parameterMap, PortletDataHandlerKeys.PORTLET_SETUP);
		boolean importUserPreferences = MapUtil.getBoolean(
			parameterMap, PortletDataHandlerKeys.PORTLET_USER_PREFERENCES);
		String userIdStrategy = MapUtil.getString(
			parameterMap, PortletDataHandlerKeys.USER_ID_STRATEGY);

		StopWatch stopWatch = null;

		if (_log.isInfoEnabled()) {
			stopWatch = new StopWatch();

			stopWatch.start();
		}

		Layout layout = LayoutLocalServiceUtil.getLayout(plid);

		long companyId = layout.getCompanyId();

		User user = userPersistence.findByPrimaryKey(userId);

		// User ID strategy

		UserIdStrategy strategy = null;

		if (UserIdStrategy.ALWAYS_CURRENT_USER_ID.equals(userIdStrategy)) {
			strategy = new AlwaysCurrentUserIdStrategy(user);
		}
		else if (UserIdStrategy.CURRENT_USER_ID.equals(userIdStrategy)) {
			strategy = new CurrentUserIdStrategy(user);
		}

		ZipReader zipReader = new ZipReader(is);

		PortletDataContext context = new PortletDataContextImpl(
			companyId, layout.getGroupId(), parameterMap,
			CollectionFactory.getHashSet(), strategy, zipReader);

		context.setPlid(plid);

		// Zip

		Element root = null;

		try {

			// XML

			String xml = zipReader.getEntryAsString("portlet.xml");

			SAXReader reader = new SAXReader();

			Document doc = reader.read(new StringReader(xml));

			root = doc.getRootElement();
		}
		catch (Exception e) {
			throw new SystemException(e);
		}

		// Build compatibility

		Element header = (Element)root.element("header");

		int buildNumber = ReleaseInfo.getBuildNumber();

		int importBuildNumber = GetterUtil.getInteger(
			header.attributeValue("build-number"));

		if (buildNumber != importBuildNumber) {
			throw new LayoutImportException(
				"LAR build number " + importBuildNumber + " does not match " +
					"portal build number " + buildNumber);
		}

		String type = header.attributeValue("type");

		if (!type.equals("portlet")) {
			throw new LayoutImportException(
				"Invalid type of LAR file (" + type + ")");
		}

		// Read comments, ratings, and tags to make them available to the data
		// handlers through the context

		readComments(context, root);
		readRatings(context, root);
		readTags(context, root);

		// Delete portlet data

		if (_log.isDebugEnabled()) {
			_log.debug("Deleting portlet data");
		}

		if (deletePortletData) {
			deletePortletData(context, layout, root);
		}

		// Portlet preferences

		importPortletPreferences(
			layout.getCompanyId(), plid, root, importPortletSetup,
			importUserPreferences);

		// Portlet data

		if (_log.isDebugEnabled()) {
			_log.debug("Importing portlet data");
		}

		if (importPortletData) {
			importPortletData(context, layout, root);
		}

		if (_log.isInfoEnabled()) {
			_log.info(
				"Importing portlet data takes " + stopWatch.getTime() + " ms");
		}
	}

	public void setLayouts(
			long groupId, boolean privateLayout, long parentLayoutId,
			long[] layoutIds)
		throws PortalException, SystemException {

		if (layoutIds == null) {
			return;
		}

		if (parentLayoutId == LayoutImpl.DEFAULT_PARENT_LAYOUT_ID) {
			if (layoutIds.length < 1) {
				throw new RequiredLayoutException(
					RequiredLayoutException.AT_LEAST_ONE);
			}

			Layout layout = layoutPersistence.findByG_P_L(
				groupId, privateLayout, layoutIds[0]);

			if (!layout.getType().equals(LayoutImpl.TYPE_PORTLET)) {
				throw new RequiredLayoutException(
					RequiredLayoutException.FIRST_LAYOUT_TYPE);
			}

			if (layout.isHidden()) {
				throw new RequiredLayoutException(
					RequiredLayoutException.FIRST_LAYOUT_HIDDEN);
			}
		}

		Set layoutIdsSet = new LinkedHashSet();

		for (int i = 0; i < layoutIds.length; i++) {
			layoutIdsSet.add(new Long(layoutIds[i]));
		}

		Set newLayoutIdsSet = CollectionFactory.getHashSet();

		Iterator itr = layoutPersistence.findByG_P_P(
			groupId, privateLayout, parentLayoutId).iterator();

		while (itr.hasNext()) {
			Layout layout = (Layout)itr.next();

			Long layoutIdObj = new Long(layout.getLayoutId());

			if (!layoutIdsSet.contains(layoutIdObj)) {
				deleteLayout(layout, true);
			}
			else {
				newLayoutIdsSet.add(layoutIdObj);
			}
		}

		int priority = 0;

		itr = layoutIdsSet.iterator();

		while (itr.hasNext()) {
			Long layoutIdObj = (Long)itr.next();

			Layout layout = layoutPersistence.findByG_P_L(
				groupId, privateLayout, layoutIdObj.longValue());

			layout.setPriority(priority++);

			layoutPersistence.update(layout);
		}

		layoutSetLocalService.updatePageCount(groupId, privateLayout);
	}

	public Layout updateLayout(
			long groupId, boolean privateLayout, long layoutId,
			long parentLayoutId, Map localeNamesMap, Map localeTitlesMap,
			String description, String type, boolean hidden, String friendlyURL)
		throws PortalException, SystemException {

		return updateLayout(
			groupId, privateLayout, layoutId, parentLayoutId, localeNamesMap,
			localeTitlesMap, description, type, hidden, friendlyURL, null,
			null);
	}

	public Layout updateLayout(
			long groupId, boolean privateLayout, long layoutId,
			long parentLayoutId, Map localeNamesMap, Map localeTitlesMap,
			String description, String type, boolean hidden, String friendlyURL,
			Boolean iconImage, byte[] iconBytes)
		throws PortalException, SystemException {

		// Layout

		parentLayoutId = getParentLayoutId(
			groupId, privateLayout, parentLayoutId);
		friendlyURL = getFriendlyURL(friendlyURL);

		validate(
			groupId, privateLayout, layoutId, parentLayoutId, type, hidden,
			friendlyURL);

		validateParentLayoutId(
			groupId, privateLayout, layoutId, parentLayoutId);

		Layout layout = layoutPersistence.findByG_P_L(
			groupId, privateLayout, layoutId);

		if (parentLayoutId != layout.getParentLayoutId()) {
			layout.setPriority(
				getNextPriority(groupId, privateLayout, parentLayoutId));
		}

		layout.setParentLayoutId(parentLayoutId);
		layout.setDescription(description);
		layout.setType(type);
		layout.setHidden(hidden);
		layout.setFriendlyURL(friendlyURL);

		setLocalizedAttributes(layout, localeNamesMap, localeTitlesMap);

		if (iconImage != null) {
			layout.setIconImage(iconImage.booleanValue());

			if (iconImage.booleanValue()) {
				long iconImageId = layout.getIconImageId();

				if (iconImageId <= 0) {
					iconImageId = counterLocalService.increment();

					layout.setIconImageId(iconImageId);
				}
			}
		}

		layoutPersistence.update(layout);

		// Icon

		if (iconImage != null) {
			if (!iconImage.booleanValue()) {
				ImageLocalUtil.deleteImage(layout.getIconImageId());
			}
			else if ((iconBytes != null) && (iconBytes.length > 0)) {
				ImageLocalUtil.updateImage(layout.getIconImageId(), iconBytes);
			}
		}

		try {
			if (layout.getDlFolderId() > 0) {
				DLFolder folder = dlFolderLocalService.getFolder(
					layout.getDlFolderId());

				dlFolderLocalService.updateFolder(
					folder.getFolderId(), folder.getParentFolderId(),
					layout.getName(LocaleUtil.getDefault()),
					folder.getDescription());
			}
		}
		catch (NoSuchFolderException nsfe) {
		}

		return layout;
	}

	public Layout updateLayout(
			long groupId, boolean privateLayout, long layoutId,
			String typeSettings)
		throws PortalException, SystemException {

		Layout layout = layoutPersistence.findByG_P_L(
			groupId, privateLayout, layoutId);

		layout.setTypeSettings(typeSettings);

		layoutPersistence.update(layout);

		return layout;
	}

	public Layout updateLookAndFeel(
			long groupId, boolean privateLayout, long layoutId, String themeId,
			String colorSchemeId, String css, boolean wapTheme)
		throws PortalException, SystemException {

		Layout layout = layoutPersistence.findByG_P_L(
			groupId, privateLayout, layoutId);

		if (wapTheme) {
			layout.setWapThemeId(themeId);
			layout.setWapColorSchemeId(colorSchemeId);
		}
		else {
			layout.setThemeId(themeId);
			layout.setColorSchemeId(colorSchemeId);
			layout.setCss(css);
		}

		layoutPersistence.update(layout);

		return layout;
	}

	public Layout updateName(long plid, String name, String languageId)
		throws PortalException, SystemException {

		Layout layout = layoutPersistence.findByPrimaryKey(plid);

		return updateName(layout, name, languageId);
	}

	public Layout updateName(
			long groupId, boolean privateLayout, long layoutId, String name,
			String languageId)
		throws PortalException, SystemException {

		Layout layout = layoutPersistence.findByG_P_L(
			groupId, privateLayout, layoutId);

		return updateName(layout, name, languageId);
	}

	public Layout updateName(Layout layout, String name, String languageId)
		throws PortalException, SystemException {

		layout.setName(name, LocaleUtil.fromLanguageId(languageId));

		layoutPersistence.update(layout);

		try {
			if (layout.getDlFolderId() > 0) {
				DLFolder folder = dlFolderLocalService.getFolder(
					layout.getDlFolderId());

				dlFolderLocalService.updateFolder(
					folder.getFolderId(), folder.getParentFolderId(),
					layout.getName(LocaleUtil.getDefault()),
					folder.getDescription());
			}
		}
		catch (NoSuchFolderException nsfe) {
		}

		return layout;
	}

	public Layout updateParentLayoutId(long plid, long parentPlid)
		throws PortalException, SystemException {

		Layout layout = layoutPersistence.findByPrimaryKey(plid);

		long parentLayoutId = LayoutImpl.DEFAULT_PARENT_LAYOUT_ID;

		if (parentPlid > 0) {
			try {
				Layout parentLayout = layoutPersistence.findByPrimaryKey(
					parentPlid);

				parentLayoutId = parentLayout.getLayoutId();
			}
			catch (NoSuchLayoutException nsle) {
			}
		}

		parentLayoutId = getParentLayoutId(
			layout.getGroupId(), layout.isPrivateLayout(), parentLayoutId);

		validateParentLayoutId(
			layout.getGroupId(), layout.isPrivateLayout(), layout.getLayoutId(),
			parentLayoutId);

		if (parentLayoutId != layout.getParentLayoutId()) {
			int priority = getNextPriority(
				layout.getGroupId(), layout.isPrivateLayout(), parentLayoutId);

			layout.setPriority(priority);
		}

		layout.setParentLayoutId(parentLayoutId);

		layoutPersistence.update(layout);

		return layout;
	}

	public Layout updateParentLayoutId(
			long groupId, boolean privateLayout, long layoutId,
			long parentLayoutId)
		throws PortalException, SystemException {

		parentLayoutId = getParentLayoutId(
			groupId, privateLayout, parentLayoutId);

		validateParentLayoutId(
			groupId, privateLayout, layoutId, parentLayoutId);

		Layout layout = layoutPersistence.findByG_P_L(
			groupId, privateLayout, layoutId);

		if (parentLayoutId != layout.getParentLayoutId()) {
			layout.setPriority(
				getNextPriority(groupId, privateLayout, parentLayoutId));
		}

		layout.setParentLayoutId(parentLayoutId);

		layoutPersistence.update(layout);

		return layout;
	}

	public Layout updatePriority(long plid, int priority)
		throws PortalException, SystemException {

		Layout layout = layoutPersistence.findByPrimaryKey(plid);

		return updatePriority(layout, priority);
	}

	public Layout updatePriority(
			long groupId, boolean privateLayout, long layoutId, int priority)
		throws PortalException, SystemException {

		Layout layout = layoutPersistence.findByG_P_L(
			groupId, privateLayout, layoutId);

		return updatePriority(layout, priority);
	}

	public Layout updatePriority(Layout layout, int priority)
		throws PortalException, SystemException {

		if (layout.getPriority() == priority) {
			return layout;
		}

		boolean lessThan = false;

		if (layout.getPriority() < priority) {
			lessThan = true;
		}

		layout.setPriority(priority);

		layoutPersistence.update(layout);

		priority = 0;

		List layouts = layoutPersistence.findByG_P_P(
			layout.getGroupId(), layout.isPrivateLayout(),
			layout.getParentLayoutId());

		Collections.sort(
			layouts, new LayoutPriorityComparator(layout, lessThan));

		Iterator itr = layouts.iterator();

		while (itr.hasNext()) {
			Layout curLayout = (Layout)itr.next();

			curLayout.setPriority(priority++);

			layoutPersistence.update(curLayout);

			if (curLayout.equals(layout)) {
				layout = curLayout;
			}
		}

		return layout;
	}

	protected void deleteMissingLayouts(
			long groupId, boolean privateLayout, Set newLayoutIds)
		throws PortalException, SystemException {

		// Layouts

		if (_log.isDebugEnabled()) {
			if (newLayoutIds.size() > 0) {
				_log.debug("Delete missing layouts");
			}
		}

		List layouts = layoutPersistence.findByG_P(groupId, privateLayout);

		Iterator itr = layouts.iterator();

		while (itr.hasNext()) {
			Layout layout = (Layout)itr.next();

			if (!newLayoutIds.contains(new Long(layout.getLayoutId()))) {
				try {
					deleteLayout(layout, false);
				}
				catch (NoSuchLayoutException nsle) {
				}
			}
		}

		// Layout set

		layoutSetLocalService.updatePageCount(groupId, privateLayout);
	}

	protected void deletePortletData(
			PortletDataContext context, Layout layout, Element parentEl)
		throws PortalException, SystemException {

		Iterator itr = parentEl.elements("portlet-data").iterator();

		while (itr.hasNext()) {
			Element el = (Element)itr.next();

			String portletId = el.attributeValue("portlet-id");

			try {
				PortletPreferences portletPreferences =
					portletPreferencesPersistence.findByO_O_P_P(
						PortletKeys.PREFS_OWNER_ID_DEFAULT,
						PortletKeys.PREFS_OWNER_TYPE_LAYOUT, layout.getPlid(),
						portletId);

				String preferences = deletePortletData(
					context, portletId, portletPreferences, el);

				if (preferences != null) {
					portletPreferences.setPreferences(preferences);

					portletPreferencesPersistence.update(portletPreferences);
				}
			}
			catch (NoSuchPortletPreferencesException nsppe) {
			}
		}
	}

	protected String deletePortletData(
			PortletDataContext context, String portletId,
			PortletPreferences portletPreferences, Element parentEl)
		throws PortalException, SystemException {

		Portlet portlet = portletLocalService.getPortletById(
			context.getCompanyId(), portletId);

		if (portlet == null) {
			if (_log.isDebugEnabled()) {
				_log.debug(
					"Do not delete portlet data for " + portletId +
						" because the portlet does not exist");
			}

			return null;
		}

		PortletDataHandler portletDataHandler =
			portlet.getPortletDataHandlerInstance();

		if (portletDataHandler == null) {
			if (_log.isDebugEnabled()) {
				_log.debug(
					"Do not delete portlet data for " + portletId +
						" because the portlet does not have a " +
							"PortletDataHandler");
			}

			return null;
		}

		if (_log.isDebugEnabled()) {
			_log.debug("Deleting data for " + portletId);
		}

		PortletPreferencesImpl prefsImpl =
			(PortletPreferencesImpl)PortletPreferencesSerializer.fromDefaultXML(
				portletPreferences.getPreferences());

		prefsImpl = (PortletPreferencesImpl)portletDataHandler.deleteData(
			context, portletId, prefsImpl);

		if (prefsImpl == null) {
			return null;
		}

		return PortletPreferencesSerializer.toXML(prefsImpl);
	}

	protected void exportComments(PortletDataContext context, Element root)
		throws SystemException {

		try {
			XStream xStream = new XStream();

			Map commentsMap = context.getComments();

			Iterator itr = commentsMap.keySet().iterator();

			while (itr.hasNext()) {
				String key = (String)itr.next();

				String[] comment = key.split(StringPool.POUND);

				Element el = root.addElement("comments");

				el.addAttribute("class-name", comment[0]);
				el.addAttribute("class-pk", comment[1]);

				List messages = (List)commentsMap.get(key);

				String xml = xStream.toXML(messages);

				Document tempDoc = PortalUtil.readDocumentFromXML(xml);

				el.content().add(tempDoc.getRootElement().createCopy());
			}
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
	}

	protected Element exportGroupPermissions(
			long companyId, long groupId, String resourceName,
			String resourcePrimKey, Element parentEl, String elName)
		throws PortalException, SystemException {

		Element el = parentEl.addElement(elName);

		List permissions = permissionLocalService.getGroupPermissions(
			groupId, companyId, resourceName, ResourceImpl.SCOPE_INDIVIDUAL,
			resourcePrimKey);

		List actions = ResourceActionsUtil.getActions(permissions);

		for (int i = 0; i < actions.size(); i++) {
			String action = (String)actions.get(i);

			Element actionKeyEl = el.addElement("action-key");

			actionKeyEl.addText(action);
		}

		return el;
	}

	protected void exportGroupRoles(
			LayoutCache layoutCache, long companyId, long groupId,
			String resourceName, String entityName, Element parentEl)
		throws PortalException, SystemException {

		List roles = layoutCache.getGroupRoles(groupId);

		Element groupEl = exportRoles(
			companyId, resourceName, ResourceImpl.SCOPE_GROUP,
			String.valueOf(groupId), parentEl, entityName + "-roles", roles);

		if (groupEl.elements().isEmpty()) {
			parentEl.remove(groupEl);
		}
	}

	protected void exportInheritedPermissions(
			LayoutCache layoutCache, long companyId, String resourceName,
			String resourcePrimKey, Element parentEl, String entityName)
		throws PortalException, SystemException {

		Element entityPermissionsEl = DocumentHelper.createElement(
			entityName + "-permissions");

		Map entityMap = layoutCache.getEntityMap(companyId, entityName);

		Iterator itr = entityMap.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			String name = entry.getKey().toString();

			long entityGroupId = ((Long)entry.getValue()).longValue();

			Element entityEl = exportGroupPermissions(
				companyId, entityGroupId, resourceName, resourcePrimKey,
				entityPermissionsEl, entityName + "-actions");

			if (entityEl.elements().isEmpty()) {
				entityPermissionsEl.remove(entityEl);
			}
			else {
				entityEl.addAttribute("name", name);
			}
		}

		if (!entityPermissionsEl.elements().isEmpty()) {
			parentEl.add(entityPermissionsEl);
		}
	}

	protected void exportInheritedRoles(
			LayoutCache layoutCache, long companyId, long groupId,
			String resourceName, String entityName, Element parentEl)
		throws PortalException, SystemException {

		Element entityRolesEl = DocumentHelper.createElement(
			entityName + "-roles");

		Map entityMap = layoutCache.getEntityMap(companyId, entityName);

		Iterator itr = entityMap.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			String name = entry.getKey().toString();

			long entityGroupId = ((Long)entry.getValue()).longValue();

			List entityRoles = layoutCache.getGroupRoles(entityGroupId);

			Element entityEl = exportRoles(
				companyId, resourceName, ResourceImpl.SCOPE_GROUP,
				String.valueOf(groupId), entityRolesEl, entityName,
				entityRoles);

			if (entityEl.elements().isEmpty()) {
				entityRolesEl.remove(entityEl);
			}
			else {
				entityEl.addAttribute("name", name);
			}
		}

		if (!entityRolesEl.elements().isEmpty()) {
			parentEl.add(entityRolesEl);
		}
	}

	protected void exportLayoutPermissions(
			LayoutCache layoutCache, long companyId, long groupId,
			Group guestGroup, Layout layout, Element permissionsEl,
			boolean exportUserPermissions)
		throws PortalException, SystemException {

		String resourceName = Layout.class.getName();
		String resourcePrimKey = String.valueOf(layout.getPlid());

		exportGroupPermissions(
			companyId, groupId, resourceName, resourcePrimKey, permissionsEl,
			"community-actions");

		if (groupId != guestGroup.getGroupId()) {
			exportGroupPermissions(
				companyId, guestGroup.getGroupId(), resourceName,
				resourcePrimKey, permissionsEl, "guest-actions");
		}

		if (exportUserPermissions) {
			exportUserPermissions(
				layoutCache, companyId, groupId, resourceName, resourcePrimKey,
				permissionsEl);
		}

		exportInheritedPermissions(
			layoutCache, companyId, resourceName, resourcePrimKey,
			permissionsEl, "organization");

		exportInheritedPermissions(
			layoutCache, companyId, resourceName, resourcePrimKey,
			permissionsEl, "location");

		exportInheritedPermissions(
			layoutCache, companyId, resourceName, resourcePrimKey,
			permissionsEl, "user-group");
	}

	protected void exportLayoutRoles(
			LayoutCache layoutCache, long companyId, long groupId,
			Element rolesEl)
		throws PortalException, SystemException {

		String resourceName = Layout.class.getName();

		exportGroupRoles(
			layoutCache, companyId, groupId, resourceName, "community",
			rolesEl);

		exportUserRoles(layoutCache, companyId, groupId, resourceName, rolesEl);

		exportInheritedRoles(
			layoutCache, companyId, groupId, resourceName, "organization",
			rolesEl);

		exportInheritedRoles(
			layoutCache, companyId, groupId, resourceName, "location", rolesEl);

		exportInheritedRoles(
			layoutCache, companyId, groupId, resourceName, "user-group",
			rolesEl);
	}

	protected void exportPortletData(
			PortletDataContext context, Layout layout,
			LayoutTypePortlet layoutTypePortlet, Element parentEl)
		throws PortalException, SystemException {

		Iterator itr = portletPreferencesLocalService.getPortletPreferences(
			layout.getPlid()).iterator();

		while (itr.hasNext()) {
			PortletPreferences portletPreferences =
				(PortletPreferences)itr.next();

			javax.portlet.PortletPreferences jxPrefs =
				portletPreferencesLocalService.getPreferences(
					layout.getCompanyId(), portletPreferences.getOwnerId(),
					portletPreferences.getOwnerType(),
					portletPreferences.getPlid(),
					portletPreferences.getPortletId());

			String portletId = portletPreferences.getPortletId();

			if (layoutTypePortlet.hasPortletId(portletId)) {
				exportPortletData(context, portletId, jxPrefs, parentEl);
			}
		}
	}

	protected void exportPortletData(
			PortletDataContext context, String portletId,
			javax.portlet.PortletPreferences portletPreferences,
			Element parentEl)
		throws PortalException, SystemException {

		Portlet portlet = portletLocalService.getPortletById(
			context.getCompanyId(), portletId);

		if (portlet == null) {
			if (_log.isDebugEnabled()) {
				_log.debug(
					"Do not export portlet data for " + portletId +
						" because the portlet does not exist");
			}

			return;
		}

		PortletDataHandler portletDataHandler =
			portlet.getPortletDataHandlerInstance();

		if (portletDataHandler == null) {
			return;
		}

		if (_log.isDebugEnabled()) {
			_log.debug("Exporting data for " + portletId);
		}

		Map parameterMap = context.getParameterMap();

		boolean exportData = false;

		if (MapUtil.getBoolean(
				parameterMap,
				PortletDataHandlerKeys.PORTLET_DATA + "_" + portletId) ||
			MapUtil.getBoolean(
				parameterMap, PortletDataHandlerKeys.PORTLET_DATA_ALL)) {

			exportData = true;
		}

		if (!exportData) {
			if (_log.isDebugEnabled()) {
				_log.debug(
					"Not exporting data for " + portletId +
						" because it was not selected by the user");
			}

			return;
		}

		String data = portletDataHandler.exportData(
			context, portletId, portletPreferences);

		if (data == null) {
			if (_log.isDebugEnabled()) {
				_log.debug(
					"Not exporting data for " + portletId +
						" because null data was returned");
			}

			return;
		}

		Element el = parentEl.addElement("portlet-data");

		el.addAttribute("portlet-id", portletId);
		el.addCDATA(data);
	}

	protected void exportPortletPermissions(
			LayoutCache layoutCache, long companyId, long groupId,
			Group guestGroup, Layout layout,
			LayoutTypePortlet layoutTypePortlet, Set portletIds,
			Element permissionsEl, boolean exportUserPermissions)
		throws PortalException, SystemException {

		Iterator itr = layoutTypePortlet.getPortletIds().iterator();

		while (itr.hasNext()) {
			String portletId = (String)itr.next();

			if (!portletIds.contains(portletId)) {
				portletIds.add(portletId);
			}

			if (layoutTypePortlet.hasPortletId(portletId)) {
				String resourceName = PortletImpl.getRootPortletId(portletId);
				String resourcePrimKey = PortletPermissionUtil.getPrimaryKey(
					layout.getPlid(), portletId);

				Element portletEl = permissionsEl.addElement("portlet");

				portletEl.addAttribute("portlet-id", portletId);

				exportGroupPermissions(
					companyId, groupId, resourceName, resourcePrimKey,
					portletEl, "community-actions");

				if (groupId != guestGroup.getGroupId()) {
					exportGroupPermissions(
						companyId, guestGroup.getGroupId(), resourceName,
						resourcePrimKey, portletEl, "guest-actions");
				}

				if (exportUserPermissions) {
					exportUserPermissions(
						layoutCache, companyId, groupId, resourceName,
						resourcePrimKey, portletEl);
				}

				exportInheritedPermissions(
					layoutCache, companyId, resourceName, resourcePrimKey,
					portletEl, "organization");

				exportInheritedPermissions(
					layoutCache, companyId, resourceName, resourcePrimKey,
					portletEl, "location");

				exportInheritedPermissions(
					layoutCache, companyId, resourceName, resourcePrimKey,
					portletEl, "user-group");
			}
		}
	}

	protected void exportPortletPreferences(
			long ownerId, int ownerType, long plid, boolean defaultUser,
			Element parentEl)
		throws PortalException, SystemException {

		exportPortletPreferences(
			ownerId, ownerType, defaultUser, plid, null, parentEl);
	}

	protected void exportPortletPreferences(
			long ownerId, int ownerType, boolean defaultUser, long plid,
			LayoutTypePortlet layoutTypePortlet, Element parentEl)
		throws PortalException, SystemException {

		Iterator itr = portletPreferencesLocalService.getPortletPreferences(
			ownerId, ownerType, plid).iterator();

		while (itr.hasNext()) {
			PortletPreferences portletPreferences =
				(PortletPreferences)itr.next();

			String portletId = portletPreferences.getPortletId();

			if ((layoutTypePortlet == null) ||
				(layoutTypePortlet.hasPortletId(portletId))) {

				Element el = parentEl.addElement("portlet-preferences");

				el.addAttribute("owner-id", String.valueOf(ownerId));
				el.addAttribute("owner-type", String.valueOf(ownerType));
				el.addAttribute("default-user", String.valueOf(defaultUser));
				el.addAttribute("plid", String.valueOf(plid));
				el.addAttribute("portlet-id", portletId);
				el.addElement("preferences").addCDATA(
					portletPreferences.getPreferences());
			}
		}
	}

	protected void exportPortletPreferences(
			long ownerId, int ownerType, boolean defaultUser, Layout layout,
	        String portletId, Element parentEl)
		throws PortalException, SystemException {

		PortletPreferences portletPreferences = null;

		long plid = layout.getPlid();

		if ((ownerType == PortletKeys.PREFS_OWNER_TYPE_COMPANY) ||
			(ownerType == PortletKeys.PREFS_OWNER_TYPE_GROUP)) {

			plid = PortletKeys.PREFS_OWNER_ID_DEFAULT;
		}

		try {
			portletPreferences =
				portletPreferencesLocalService.getPortletPreferences(
					ownerId, ownerType, plid, portletId);

			LayoutTypePortlet layoutTypePortlet =
				(LayoutTypePortlet)layout.getLayoutType();

			if ((layoutTypePortlet == null) ||
				(layoutTypePortlet.hasPortletId(portletId))) {

				Element el = parentEl.addElement("portlet-preferences");

				el.addAttribute("owner-id", String.valueOf(ownerId));
				el.addAttribute("owner-type", String.valueOf(ownerType));
				el.addAttribute("default-user", String.valueOf(defaultUser));
				el.addAttribute("plid", String.valueOf(plid));
				el.addAttribute("portlet-id", portletId);
				el.addElement("preferences").addCDATA(
					portletPreferences.getPreferences());
			}
		}
		catch (NoSuchPortletPreferencesException nsppe) {
		}
	}

	protected void exportPortletRoles(
			LayoutCache layoutCache, long companyId, long groupId,
			Set portletIds, Element rolesEl)
		throws PortalException, SystemException {

		Iterator itr = portletIds.iterator();

		while (itr.hasNext()) {
			String portletId = (String)itr.next();

			String resourceName = PortletImpl.getRootPortletId(portletId);

			Element portletEl = rolesEl.addElement("portlet");

			portletEl.addAttribute("portlet-id", portletId);

			exportGroupRoles(
				layoutCache, companyId, groupId, resourceName, "community",
				portletEl);

			exportUserRoles(
				layoutCache, companyId, groupId, resourceName, portletEl);

			exportInheritedRoles(
				layoutCache, companyId, groupId, resourceName, "organization",
				portletEl);

			exportInheritedRoles(
				layoutCache, companyId, groupId, resourceName, "location",
				portletEl);

			exportInheritedRoles(
				layoutCache, companyId, groupId, resourceName, "user-group",
				portletEl);

			if (portletEl.elements().isEmpty()) {
				rolesEl.remove(portletEl);
			}
		}
	}

	protected Element exportRoles(
			long companyId, String resourceName, int scope,
			String resourcePrimKey, Element parentEl, String elName,
			List roles)
		throws PortalException, SystemException {

		Element el = parentEl.addElement(elName);

		Map resourceRoles = roleLocalService.getResourceRoles(
			companyId, resourceName, scope, resourcePrimKey);

		Iterator itr = resourceRoles.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			String roleName = entry.getKey().toString();

			if (hasRole(roles, roleName)) {
				Element roleEl = el.addElement("role");

				roleEl.addAttribute("name", roleName);

				List actions = (List)entry.getValue();

				for (int i = 0; i < actions.size(); i++) {
					String action = (String)actions.get(i);

					Element actionKeyEl = roleEl.addElement("action-key");

					actionKeyEl.addText(action);
					actionKeyEl.addAttribute("scope", String.valueOf(scope));
				}
			}
		}

		return el;
	}

	protected void exportRatings(PortletDataContext context, Element root)
		throws SystemException {

		try {
			XStream xStream = new XStream();

			Map ratingsEntriesMap = context.getRatingsEntries();

			Iterator itr = ratingsEntriesMap.keySet().iterator();

			while (itr.hasNext()) {
				String key = (String)itr.next();

				String[] ratingsEntry = key.split(StringPool.POUND);

				Element el = root.addElement("ratings");

				el.addAttribute("class-name", ratingsEntry[0]);
				el.addAttribute("class-pk", ratingsEntry[1]);

				List ratingsEntries = (List)ratingsEntriesMap.get(key);

				String xml = xStream.toXML(ratingsEntries);

				Document tempDoc = PortalUtil.readDocumentFromXML(xml);

				el.content().add(tempDoc.getRootElement().createCopy());
			}
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
	}

	protected void exportTags(PortletDataContext context, Element root) {
		Map tagsEntries = context.getTagsEntries();

		Iterator itr = tagsEntries.keySet().iterator();

		while (itr.hasNext()) {
			String key = (String)itr.next();

			String[] tagsEntry = key.split(StringPool.POUND);

			Element el = root.addElement("tags");

			el.addAttribute("class-name", tagsEntry[0]);
			el.addAttribute("class-pk", tagsEntry[1]);
			el.addAttribute(
				"entries",
				StringUtil.merge((String[])tagsEntries.get(key), ","));
		}
	}

	protected byte[] exportTheme(LayoutSet layoutSet)
		throws IOException, PortalException, SystemException {

		Theme theme = layoutSet.getTheme();

		ZipWriter zipWriter = new ZipWriter();

		String lookAndFeelXML = ContentUtil.get(
			"com/liferay/portal/dependencies/liferay-look-and-feel.xml.tmpl");

		lookAndFeelXML = StringUtil.replace(
			lookAndFeelXML,
			new String[] {
				"[$TEMPLATE_EXTENSION$]", "[$VIRTUAL_PATH$]"
			},
			new String[] {
				theme.getTemplateExtension(), theme.getVirtualPath()
			}
		);

		zipWriter.addEntry("liferay-look-and-feel.xml", lookAndFeelXML);

		String servletContextName = theme.getServletContextName();

		ServletContext ctx = VelocityContextPool.get(servletContextName);

		if (ctx == null) {
			if (_log.isWarnEnabled()) {
				_log.warn(
					"Servlet context not found for theme " +
						theme.getThemeId());
			}

			return null;
		}

		File cssPath = null;
		File imagesPath = null;
		File javaScriptPath = null;
		File templatesPath = null;

		if (!theme.isLoadFromServletContext()) {
			ThemeLoader themeLoader = ThemeLoaderFactory.getThemeLoader(
				servletContextName);

			if (themeLoader == null) {
				_log.error(
					servletContextName + " does not map to a theme loader");
			}
			else {
				String realPath =
					themeLoader.getFileStorage().getPath() + "/" +
						theme.getName();

				cssPath = new File(realPath + "/css");
				imagesPath = new File(realPath + "/images");
				javaScriptPath = new File(realPath + "/javascript");
				templatesPath = new File(realPath + "/templates");
			}
		}
		else {
			cssPath = new File(ctx.getRealPath(theme.getCssPath()));
			imagesPath = new File(ctx.getRealPath(theme.getImagesPath()));
			javaScriptPath = new File(
				ctx.getRealPath(theme.getJavaScriptPath()));
			templatesPath = new File(ctx.getRealPath(theme.getTemplatesPath()));
		}

		exportThemeFiles("css", cssPath, zipWriter);
		exportThemeFiles("images", imagesPath, zipWriter);
		exportThemeFiles("javascript", javaScriptPath, zipWriter);
		exportThemeFiles("templates", templatesPath, zipWriter);

		return zipWriter.finish();
	}

	protected void exportThemeFiles(String path, File dir, ZipWriter zipWriter)
		throws IOException {

		if ((dir == null) || (!dir.exists())) {
			return;
		}

		File[] files = dir.listFiles();

		for (int i = 0; i < files.length; i++) {
			File file = files[i];

			if (file.isDirectory()) {
				exportThemeFiles(path + "/" + file.getName(), file, zipWriter);
			}
			else {
				zipWriter.addEntry(
					path + "/" + file.getName(), FileUtil.getBytes(file));
			}
		}
	}

	protected void exportUserPermissions(
			LayoutCache layoutCache, long companyId, long groupId,
			String resourceName, String resourcePrimKey, Element parentEl)
		throws PortalException, SystemException {

		StopWatch stopWatch = null;

		if (_log.isDebugEnabled()) {
			stopWatch = new StopWatch();

			stopWatch.start();
		}

		Element userPermissionsEl = DocumentHelper.createElement(
			"user-permissions");

		List users = layoutCache.getGroupUsers(groupId);

		for (int i = 0; i < users.size(); i++) {
			User user = (User)users.get(i);

			String emailAddress = user.getEmailAddress();

			Element userActionsEl =
				DocumentHelper.createElement("user-actions");

			List permissions = permissionLocalService.getUserPermissions(
				user.getUserId(), companyId, resourceName,
				ResourceImpl.SCOPE_INDIVIDUAL, resourcePrimKey);

			List actions = ResourceActionsUtil.getActions(permissions);

			for (int j = 0; j < actions.size(); j++) {
				String action = (String)actions.get(j);

				Element actionKeyEl = userActionsEl.addElement("action-key");

				actionKeyEl.addText(action);
			}

			if (!userActionsEl.elements().isEmpty()) {
				userActionsEl.addAttribute("email-address", emailAddress);
				userPermissionsEl.add(userActionsEl);
			}
		}

		if (!userPermissionsEl.elements().isEmpty()) {
			parentEl.add(userPermissionsEl);
		}

		if (_log.isDebugEnabled()) {
			_log.debug(
				"Export user permissions for {" + resourceName + ", " +
					resourcePrimKey + "} with " + users.size() +
						" users takes " + stopWatch.getTime() + " ms");
		}
	}

	protected void exportUserRoles(
			LayoutCache layoutCache, long companyId, long groupId,
			String resourceName, Element parentEl)
		throws PortalException, SystemException {

		Element userRolesEl = DocumentHelper.createElement("user-roles");

		List users = layoutCache.getGroupUsers(groupId);

		for (int i = 0; i < users.size(); i++) {
			User user = (User)users.get(i);

			long userId = user.getUserId();
			String emailAddress = user.getEmailAddress();

			List userRoles = layoutCache.getUserRoles(userId);

			Element userEl = exportRoles(
				companyId, resourceName, ResourceImpl.SCOPE_GROUP,
				String.valueOf(groupId), userRolesEl, "user", userRoles);

			if (userEl.elements().isEmpty()) {
				userRolesEl.remove(userEl);
			}
			else {
				userEl.addAttribute("email-address", emailAddress);
			}
		}

		if (!userRolesEl.elements().isEmpty()) {
			parentEl.add(userRolesEl);
		}
	}

	protected void fixTypeSettings(Layout layout) {
		if (layout.getType().equals(LayoutImpl.TYPE_URL)) {
			Properties typeSettings = layout.getTypeSettingsProperties();

			String url = GetterUtil.getString(typeSettings.getProperty("url"));

			String friendlyURLPrivateGroupPath =
				PropsValues.LAYOUT_FRIENDLY_URL_PRIVATE_GROUP_SERVLET_MAPPING;
			String friendlyURLPrivateUserPath =
				PropsValues.LAYOUT_FRIENDLY_URL_PRIVATE_USER_SERVLET_MAPPING;
			String friendlyURLPublicPath =
				PropsValues.LAYOUT_FRIENDLY_URL_PUBLIC_SERVLET_MAPPING;

			if (url.startsWith(friendlyURLPrivateGroupPath) ||
				url.startsWith(friendlyURLPrivateUserPath) ||
				url.startsWith(friendlyURLPublicPath)) {

				int x = url.indexOf(StringPool.SLASH, 1);

				if (x > 0) {
					int y = url.indexOf(StringPool.SLASH, x + 1);

					if (y > x) {
						String fixedUrl = url.substring(0, x) +

						layout.getGroup().getFriendlyURL() +

						url.substring(y);

						typeSettings.setProperty("url", fixedUrl);
					}
				}
			}
		}
	}

	protected List getActions(Element el) {
		List actions = new ArrayList();

		Iterator itr = el.elements("action-key").iterator();

		while (itr.hasNext()) {
			Element actionEl = (Element)itr.next();

			actions.add(actionEl.getText());
		}

		return actions;
	}

	protected String getFriendlyURL(String friendlyURL) {
		return Normalizer.normalizeToAscii(friendlyURL.trim().toLowerCase());
	}

	protected long getNextLayoutId(long groupId, boolean privateLayout)
		throws SystemException {

		long layoutId = 0;

		List layouts = layoutPersistence.findByG_P(groupId, privateLayout);

		for (int i = 0; i < layouts.size(); i++) {
			Layout curLayout = (Layout)layouts.get(i);

			long curLayoutId = curLayout.getLayoutId();

			if (curLayoutId > layoutId) {
				layoutId = curLayoutId;
			}
		}

		return ++layoutId;
	}

	protected int getNextPriority(
			long groupId, boolean privateLayout, long parentLayoutId)
		throws SystemException {

		List layouts = layoutPersistence.findByG_P_P(
			groupId, privateLayout, parentLayoutId);

		if (layouts.size() == 0) {
			return 0;
		}

		Layout layout = (Layout)layouts.get(layouts.size() - 1);

		return layout.getPriority() + 1;
	}

	protected long getParentLayoutId(
			long groupId, boolean privateLayout, long parentLayoutId)
		throws PortalException, SystemException {

		if (parentLayoutId != LayoutImpl.DEFAULT_PARENT_LAYOUT_ID) {

			// Ensure parent layout exists

			try {
				layoutPersistence.findByG_P_L(
					groupId, privateLayout, parentLayoutId);
			}
			catch (NoSuchLayoutException nsfe) {
				parentLayoutId = LayoutImpl.DEFAULT_PARENT_LAYOUT_ID;
			}
		}

		return parentLayoutId;
	}

	protected boolean hasRole(List roles, String roleName) {
		if ((roles == null) || (roles.size() == 0)) {
			return false;
		}

		for (int i = 0; i < roles.size(); i++) {
			Role role = (Role)roles.get(i);

			if (role.getName().equals(roleName)) {
				return true;
			}
		}

		return false;
	}

	protected void importGroupPermissions(
			LayoutCache layoutCache, long companyId, long groupId,
			String resourceName, String resourcePrimKey, Element parentEl,
			String elName, boolean portletActions)
		throws PortalException, SystemException {

		Element actionEl = parentEl.element(elName);

		if (actionEl == null) {
			return;
		}

		List actions = getActions(actionEl);

		Resource resource = layoutCache.getResource(
			companyId, groupId, resourceName, ResourceImpl.SCOPE_INDIVIDUAL,
			resourcePrimKey, portletActions);

		permissionLocalService.setGroupPermissions(
			groupId, (String[])actions.toArray(new String[0]),
			resource.getResourceId());
	}

	protected void importGroupRoles(
			LayoutCache layoutCache, long companyId, long groupId,
			String resourceName, String entityName,
			Element parentEl)
		throws PortalException, SystemException {

		Element entityRolesEl = parentEl.element(entityName + "-roles");

		if (entityRolesEl == null) {
			return;
		}

		importRolePermissions(
			layoutCache, companyId, resourceName, ResourceImpl.SCOPE_GROUP,
			String.valueOf(groupId), entityRolesEl, true);
	}

	protected void importInheritedPermissions(
			LayoutCache layoutCache, long companyId, String resourceName,
			String resourcePrimKey, Element permissionsEl, String entityName,
			boolean portletActions)
		throws PortalException, SystemException {

		Element entityPermissionsEl = permissionsEl.element(
			entityName + "-permissions");

		if (entityPermissionsEl == null) {
			return;
		}

		List actionsEls = entityPermissionsEl.elements(
			entityName + "-actions");

		for (int i = 0; i < actionsEls.size(); i++) {
			Element actionEl = (Element)actionsEls.get(i);

			String name = actionEl.attributeValue("name");

			long entityGroupId = layoutCache.getEntityGroupId(
				companyId, entityName, name);

			if (entityGroupId == 0) {
				_log.warn(
					"Ignore inherited permissions for entity " + entityName +
						" with name " + name);
			}
			else {
				Element parentEl = DocumentHelper.createElement("parent");

				parentEl.add(actionEl.createCopy());

				importGroupPermissions(
					layoutCache, companyId, entityGroupId, resourceName,
					resourcePrimKey, parentEl, entityName + "-actions",
					portletActions);
			}
		}
	}

	protected void importInheritedRoles(
			LayoutCache layoutCache, long companyId, long groupId,
			String resourceName, String entityName, Element parentEl)
		throws PortalException, SystemException {

		Element entityRolesEl = parentEl.element(entityName + "-roles");

		if (entityRolesEl == null) {
			return;
		}

		List entityEls = entityRolesEl.elements(entityName);

		for (int i = 0; i < entityEls.size(); i++) {
			Element entityEl = (Element)entityEls.get(i);

			String name = entityEl.attributeValue("name");

			long entityGroupId = layoutCache.getEntityGroupId(
				companyId, entityName, name);

			if (entityGroupId == 0) {
				_log.warn(
					"Ignore inherited roles for entity " + entityName +
						" with name " + name);
			}
			else {
				importRolePermissions(
					layoutCache, companyId, resourceName,
					ResourceImpl.SCOPE_GROUP, String.valueOf(groupId), entityEl,
					false);
			}
		}
	}

	protected void importLayoutPermissions(
			LayoutCache layoutCache, long companyId, long groupId,
			Group guestGroup, Layout layout, Element permissionsEl,
			boolean importUserPermissions)
		throws PortalException, SystemException {

		String resourceName = Layout.class.getName();
		String resourcePrimKey = String.valueOf(layout.getPlid());

		importGroupPermissions(
			layoutCache, companyId, groupId, resourceName, resourcePrimKey,
			permissionsEl, "community-actions", false);

		if (groupId != guestGroup.getGroupId()) {
			importGroupPermissions(
				layoutCache, companyId, guestGroup.getGroupId(), resourceName,
				resourcePrimKey, permissionsEl, "guest-actions", false);
		}

		if (importUserPermissions) {
			importUserPermissions(
				layoutCache, companyId, groupId, resourceName, resourcePrimKey,
				permissionsEl, false);
		}

		importInheritedPermissions(
			layoutCache, companyId, resourceName, resourcePrimKey,
			permissionsEl, "organization", false);

		importInheritedPermissions(
			layoutCache, companyId, resourceName, resourcePrimKey,
			permissionsEl, "location", false);

		importInheritedPermissions(
			layoutCache, companyId, resourceName, resourcePrimKey,
			permissionsEl, "user-group", false);
	}

	protected void importLayoutRoles(
			LayoutCache layoutCache, long companyId, long groupId,
			Element rolesEl)
		throws PortalException, SystemException {

		String resourceName = Layout.class.getName();

		importGroupRoles(
			layoutCache, companyId, groupId, resourceName, "community",
			rolesEl);

		importUserRoles(layoutCache, companyId, groupId, resourceName, rolesEl);

		importInheritedRoles(
			layoutCache, companyId, groupId, resourceName, "organization",
			rolesEl);

		importInheritedRoles(
			layoutCache, companyId, groupId, resourceName, "location", rolesEl);

		importInheritedRoles(
			layoutCache, companyId, groupId, resourceName, "user-group",
			rolesEl);
	}

	protected void importPortletData(
			PortletDataContext context, Layout layout, Element parentEl)
		throws PortalException, SystemException {

		Iterator itr = parentEl.elements("portlet-data").iterator();

		while (itr.hasNext()) {
			Element el = (Element)itr.next();

			String portletId = el.attributeValue("portlet-id");

			try {
				PortletPreferences portletPreferences =
					portletPreferencesPersistence.findByO_O_P_P(
						PortletKeys.PREFS_OWNER_ID_DEFAULT,
						PortletKeys.PREFS_OWNER_TYPE_LAYOUT, layout.getPlid(),
						portletId);

				String preferences = importPortletData(
					context, portletId, portletPreferences, el);

				if (preferences != null) {
					portletPreferences.setPreferences(preferences);

					portletPreferencesPersistence.update(portletPreferences);
				}
			}
			catch (NoSuchPortletPreferencesException nsppe) {
			}
		}
	}

	protected String importPortletData(
			PortletDataContext context, String portletId,
			PortletPreferences portletPreferences, Element parentEl)
		throws PortalException, SystemException {

		Portlet portlet = portletLocalService.getPortletById(
			context.getCompanyId(), portletId);

		if (portlet == null) {
			if (_log.isDebugEnabled()) {
				_log.debug(
					"Do not import portlet data for " + portletId +
						" because the portlet does not exist");
			}

			return null;
		}

		PortletDataHandler portletDataHandler =
			portlet.getPortletDataHandlerInstance();

		if (portletDataHandler == null) {
			if (_log.isDebugEnabled()) {
				_log.debug(
					"Do not import portlet data for " + portletId +
						" because the portlet does not have a " +
							"PortletDataHandler");
			}

			return null;
		}

		if (_log.isDebugEnabled()) {
			_log.debug("Importing data for " + portletId);
		}

		PortletPreferencesImpl prefsImpl =
			(PortletPreferencesImpl)PortletPreferencesSerializer.fromDefaultXML(
				portletPreferences.getPreferences());

		prefsImpl = (PortletPreferencesImpl)portletDataHandler.importData(
			context, portletId, prefsImpl, parentEl.getText());

		if (prefsImpl == null) {
			return null;
		}

		return PortletPreferencesSerializer.toXML(prefsImpl);
	}

	protected void importPortletPermissions(
			LayoutCache layoutCache, long companyId, long groupId,
			Group guestGroup, Layout layout, Element permissionsEl,
			boolean importUserPermissions)
		throws PortalException, SystemException {

		Iterator itr = permissionsEl.elements("portlet").iterator();

		while (itr.hasNext()) {
			Element portletEl = (Element)itr.next();

			String portletId = portletEl.attributeValue("portlet-id");

			String resourceName = PortletImpl.getRootPortletId(portletId);
			String resourcePrimKey = PortletPermissionUtil.getPrimaryKey(
				layout.getPlid(), portletId);

			Portlet portlet = portletLocalService.getPortletById(
				companyId, resourceName);

			if (portlet == null) {
				if (_log.isDebugEnabled()) {
					_log.debug(
						"Do not import portlet permissions for " + portletId +
							" because the portlet does not exist");
				}
			}
			else {
				importGroupPermissions(
					layoutCache, companyId, groupId, resourceName,
					resourcePrimKey, portletEl, "community-actions", true);

				if (groupId != guestGroup.getGroupId()) {
					importGroupPermissions(
						layoutCache, companyId, guestGroup.getGroupId(),
						resourceName, resourcePrimKey, portletEl,
						"guest-actions", true);
				}

				if (importUserPermissions) {
					importUserPermissions(
						layoutCache, companyId, groupId, resourceName,
						resourcePrimKey, portletEl, true);
				}

				importInheritedPermissions(
					layoutCache, companyId, resourceName, resourcePrimKey,
					portletEl, "organization", true);

				importInheritedPermissions(
					layoutCache, companyId, resourceName, resourcePrimKey,
					portletEl, "location", true);

				importInheritedPermissions(
					layoutCache, companyId, resourceName, resourcePrimKey,
					portletEl, "user-group", true);
			}
		}
	}

	protected void importPortletPreferences(
			long companyId, long plid, Element parentEl,
			boolean importPortletSetup, boolean importUserPreferences)
		throws PortalException, SystemException {

		long defaultUserId = userLocalService.getDefaultUserId(companyId);

		Iterator itr = parentEl.elements("portlet-preferences").iterator();

		while (itr.hasNext()) {
			Element el = (Element)itr.next();

			long ownerId = GetterUtil.getLong(el.attributeValue("owner-id"));
			int ownerType = GetterUtil.getInteger(
				el.attributeValue("owner-type"));

			if (ownerType == PortletKeys.PREFS_OWNER_TYPE_COMPANY) {
				continue;
			}

			if ((ownerType != PortletKeys.PREFS_OWNER_TYPE_USER) &&
				!importPortletSetup) {

				continue;
			}

			if ((ownerType == PortletKeys.PREFS_OWNER_TYPE_USER) &&
				(ownerId != PortletKeys.PREFS_OWNER_ID_DEFAULT) &&
				!importUserPreferences) {

				continue;
			}

			if (ownerType == PortletKeys.PREFS_OWNER_TYPE_GROUP) {
				plid = PortletKeys.PREFS_PLID_SHARED;
			}

			boolean defaultUser = GetterUtil.getBoolean(
				el.attributeValue("default-user"));
			String portletId = el.attributeValue("portlet-id");
			String preferences = el.elementText("preferences");

			if (defaultUser) {
				ownerId = defaultUserId;
			}

			try {
				portletPreferencesLocalService.deletePortletPreferences(
					ownerId, ownerType, plid, portletId);
			}
			catch (NoSuchPortletPreferencesException nsppe) {
			}

			long portletPreferencesId = counterLocalService.increment();

			PortletPreferences portletPreferences =
				portletPreferencesPersistence.create(portletPreferencesId);

			portletPreferences.setOwnerId(ownerId);
			portletPreferences.setOwnerType(ownerType);
			portletPreferences.setPlid(plid);
			portletPreferences.setPortletId(portletId);

			portletPreferences.setPreferences(preferences);

			portletPreferencesPersistence.update(portletPreferences);
		}
	}

	protected void importPortletRoles(
			LayoutCache layoutCache, long companyId, long groupId,
			Element rolesEl)
		throws PortalException, SystemException {

		Iterator itr = rolesEl.elements("portlet").iterator();

		while (itr.hasNext()) {
			Element portletEl = (Element)itr.next();

			String portletId = portletEl.attributeValue("portlet-id");

			String resourceName = PortletImpl.getRootPortletId(portletId);

			Portlet portlet = portletLocalService.getPortletById(
				companyId, resourceName);

			if (portlet == null) {
				if (_log.isDebugEnabled()) {
					_log.debug(
						"Do not import portlet roles for " + portletId +
							" because the portlet does not exist");
				}
			}
			else {
				importGroupRoles(
					layoutCache, companyId, groupId, resourceName, "community",
					portletEl);

				importUserRoles(
					layoutCache, companyId, groupId, resourceName, portletEl);

				importInheritedRoles(
					layoutCache, companyId, groupId, resourceName,
					"organization", portletEl);

				importInheritedRoles(
					layoutCache, companyId, groupId, resourceName, "location",
					portletEl);

				importInheritedRoles(
					layoutCache, companyId, groupId, resourceName, "user-group",
					portletEl);
			}
		}
	}

	protected void importRolePermissions(
			LayoutCache layoutCache, long companyId, String resourceName,
			int scope, String resourcePrimKey, Element parentEl,
			boolean communityRole)
		throws PortalException, SystemException {

		List roleEls = parentEl.elements("role");

		for (int i = 0; i < roleEls.size(); i++) {
			Element roleEl = (Element)roleEls.get(i);

			String roleName = roleEl.attributeValue("name");

			Role role = layoutCache.getRole(companyId, roleName);

			if (role == null) {
				_log.warn(
					"Ignoring permissions for role with name " + roleName);
			}
			else {
				List actions = getActions(roleEl);

				permissionLocalService.setRolePermissions(
					role.getRoleId(), companyId, resourceName, scope,
					resourcePrimKey, (String[])actions.toArray(new String[0]));

				if (communityRole) {
					long[] groupIds = {GetterUtil.getLong(resourcePrimKey)};

					groupLocalService.addRoleGroups(role.getRoleId(), groupIds);
				}
			}
		}
	}

	protected String importTheme(LayoutSet layoutSet, byte[] themeZip)
		throws IOException {

		ThemeLoader themeLoader = ThemeLoaderFactory.getDefaultThemeLoader();

		if (themeLoader == null) {
			_log.error("No theme loaders are deployed");

			return null;
		}

		ZipReader zipReader = new ZipReader(new ByteArrayInputStream(themeZip));

		Map entries = zipReader.getEntries();

		String lookAndFeelXML = new String(
			(byte[])entries.get("liferay-look-and-feel.xml"));

		String themeId = String.valueOf(layoutSet.getGroupId());

		if (layoutSet.isPrivateLayout()) {
			themeId += "-private";
		}
		else {
			themeId += "-public";
		}

		if (PropsValues.THEME_LOADER_NEW_THEME_ID_ON_IMPORT) {
			Date now = new Date();

			themeId += "-" + Time.getShortTimestamp(now);
		}

		String themeName = themeId;

		lookAndFeelXML = StringUtil.replace(
			lookAndFeelXML,
			new String[] {
				"[$GROUP_ID$]", "[$THEME_ID$]", "[$THEME_NAME$]"
			},
			new String[] {
				String.valueOf(layoutSet.getGroupId()), themeId, themeName
			}
		);

		FileUtil.deltree(themeLoader.getFileStorage() + "/" + themeId);

		Iterator itr = entries.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			String key = (String)entry.getKey();
			byte[] value = (byte[])entry.getValue();

			if (key.equals("liferay-look-and-feel.xml")) {
				value = lookAndFeelXML.getBytes();
			}

			FileUtil.write(
				themeLoader.getFileStorage() + "/" + themeId + "/" + key,
				value);
		}

		themeLoader.loadThemes();

		CommLink commLink = CommLink.getInstance();

		MethodWrapper methodWrapper = new MethodWrapper(
			ThemeLoaderFactory.class.getName(), "loadThemes");

		commLink.send(methodWrapper);

		themeId +=
			PortletImpl.WAR_SEPARATOR + themeLoader.getServletContextName();

		return PortalUtil.getJsSafePortletId(themeId);
	}

	protected void importUserPermissions(
			LayoutCache layoutCache, long companyId, long groupId,
			String resourceName, String resourcePrimKey, Element parentEl,
			boolean portletActions)
		throws PortalException, SystemException {

		Element userPermissionsEl = parentEl.element("user-permissions");

		if (userPermissionsEl == null) {
			return;
		}

		List userActionsEls = userPermissionsEl.elements("user-actions");

		for (int i = 0; i < userActionsEls.size(); i++) {
			Element userActionsEl = (Element)userActionsEls.get(i);

			String emailAddress = userActionsEl.attributeValue("email-address");

			User user = layoutCache.getUser(companyId, groupId, emailAddress);

			if (user == null) {
				if (_log.isWarnEnabled()) {
					_log.warn(
						"Ignoring permissions for user with email address " +
							emailAddress);
				}
			}
			else {
				List actions = getActions(userActionsEl);

				Resource resource = layoutCache.getResource(
					companyId, groupId, resourceName,
					ResourceImpl.SCOPE_INDIVIDUAL, resourcePrimKey,
					portletActions);

				permissionLocalService.setUserPermissions(
					user.getUserId(), (String[])actions.toArray(new String[0]),
					resource.getResourceId());
			}
		}
	}

	protected void importUserRoles(
			LayoutCache layoutCache, long companyId, long groupId,
			String resourceName, Element parentEl)
		throws PortalException, SystemException {

		Element userRolesEl = parentEl.element("user-roles");

		if (userRolesEl == null) {
			return;
		}

		LinkedHashMap params = new LinkedHashMap();

		params.put("usersGroups", new Long(groupId));

		List userEls = userRolesEl.elements("user");

		for (int i = 0; i < userEls.size(); i++) {
			Element userEl = (Element)userEls.get(i);

			String emailAddress = userEl.attributeValue("email-address");

			User user = layoutCache.getUser(companyId, groupId, emailAddress);

			if (user == null) {
				if (_log.isWarnEnabled()) {
					_log.warn(
						"Ignoring roles for user with email address " +
							emailAddress);
				}
			}
			else {
				importRolePermissions(
					layoutCache, companyId, resourceName,
					ResourceImpl.SCOPE_GROUP, String.valueOf(groupId), userEl,
					false);
			}
		}
	}

	protected boolean isDescendant(Layout layout, long layoutId)
		throws PortalException, SystemException {

		if (layout.getLayoutId() == layoutId) {
			return true;
		}
		else {
			Iterator itr = layout.getChildren().iterator();

			while (itr.hasNext()) {
				Layout childLayout = (Layout)itr.next();

				if (isDescendant(childLayout, layoutId)) {
					return true;
				}
			}

			return false;
		}
	}

	protected void readComments(PortletDataContext context, Element root)
		throws PortalException, SystemException {

		try {
			XStream xStream = new XStream();

			Iterator itr = root.elements("comments").iterator();

			while (itr.hasNext()) {
				Element el = (Element)itr.next();

				String className = GetterUtil.getString(
					el.attributeValue("class-name"));
				long classPK = GetterUtil.getLong(
					el.attributeValue("class-pk"));

				Element messagesListEl = el.element("list");

				Document tempDoc = DocumentHelper.createDocument();

				tempDoc.content().add(messagesListEl.createCopy());

				List messages = (List)xStream.fromXML(
					XMLFormatter.toString(tempDoc));

				context.addComments(className, new Long(classPK), messages);
			}
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
	}

	protected void readRatings(PortletDataContext context, Element root)
		throws PortalException, SystemException {

		try {
			XStream xStream = new XStream();

			Iterator itr = root.elements("ratings").iterator();

			while (itr.hasNext()) {
				Element el = (Element)itr.next();

				String className = GetterUtil.getString(
					el.attributeValue("class-name"));
				long classPK = GetterUtil.getLong(
					el.attributeValue("class-pk"));

				Element entriesListEl = el.element("list");

				Document tempDoc = DocumentHelper.createDocument();

				tempDoc.content().add(entriesListEl.createCopy());

				List entries = (List)xStream.fromXML(
					XMLFormatter.toString(tempDoc));

				context.addRatingsEntries(
					className, new Long(classPK), entries);
			}
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
	}

	protected void readTags(PortletDataContext context, Element root)
		throws PortalException, SystemException {

		Iterator itr = root.elements("tags").iterator();

		while (itr.hasNext()) {
			Element el = (Element)itr.next();

			String className = GetterUtil.getString(
				el.attributeValue("class-name"));
			long classPK = GetterUtil.getLong(el.attributeValue("class-pk"));
			String entries = GetterUtil.getString(el.attributeValue("entries"));

			context.addTagsEntries(
				className, new Long(classPK), StringUtil.split(entries, ","));
		}
	}

	protected void setLocalizedAttributes(
		Layout layout, Map localeNamesMap, Map localeTitlesMap) {

		Locale[] locales = LanguageUtil.getAvailableLocales();

		for (int i = 0; i < locales.length; i++) {
			String name = (String)localeNamesMap.get(locales[i]);
			String title = (String)localeTitlesMap.get(locales[i]);

			layout.setName(name, locales[i]);
			layout.setTitle(title, locales[i]);
		}
	}

	protected void validate(
			long groupId, boolean privateLayout, long layoutId,
			long parentLayoutId, String type, boolean hidden,
			String friendlyURL)
		throws PortalException, SystemException {

		boolean firstLayout = false;

		if (parentLayoutId == LayoutImpl.DEFAULT_PARENT_LAYOUT_ID) {
			List layouts = layoutPersistence.findByG_P_P(
				groupId, privateLayout, parentLayoutId, 0, 1);

			if (layouts.size() == 0) {
				firstLayout = true;
			}
			else {
				long firstLayoutId = ((Layout)layouts.get(0)).getLayoutId();

				if (firstLayoutId == layoutId) {
					firstLayout = true;
				}
			}
		}

		if (firstLayout) {
			validateFirstLayout(type, hidden);
		}

		if (!PortalUtil.isLayoutParentable(type)) {
			if (layoutPersistence.countByG_P_P(
					groupId, privateLayout, layoutId) > 0) {

				throw new LayoutTypeException(
					LayoutTypeException.NOT_PARENTABLE);
			}
		}

		if (Validator.isNotNull(friendlyURL)) {
			int exceptionType = LayoutImpl.validateFriendlyURL(friendlyURL);

			if (exceptionType != -1) {
				throw new LayoutFriendlyURLException(exceptionType);
			}

			try {
				Layout layout = layoutPersistence.findByG_P_F(
					groupId, privateLayout, friendlyURL);

				if (layout.getLayoutId() != layoutId) {
					throw new LayoutFriendlyURLException(
						LayoutFriendlyURLException.DUPLICATE);
				}
			}
			catch (NoSuchLayoutException nsle) {
			}

			LayoutImpl.validateFriendlyURLKeyword(friendlyURL);

			List friendlyURLMappers =
				portletLocalService.getFriendlyURLMappers();

			Iterator itr = friendlyURLMappers.iterator();

			while (itr.hasNext()) {
				FriendlyURLMapper friendlyURLMapper =
					(FriendlyURLMapper)itr.next();

				if (friendlyURL.indexOf(friendlyURLMapper.getMapping()) != -1) {
					LayoutFriendlyURLException lfurle =
						new LayoutFriendlyURLException(
							LayoutFriendlyURLException.KEYWORD_CONFLICT);

					lfurle.setKeywordConflict(friendlyURLMapper.getMapping());

					throw lfurle;
				}
			}

		}
	}

	protected void validateFirstLayout(String type, boolean hidden)
		throws PortalException {

		if (!type.equals(LayoutImpl.TYPE_PORTLET)) {
			throw new LayoutTypeException(LayoutTypeException.FIRST_LAYOUT);
		}

		if (hidden) {
			throw new LayoutHiddenException();
		}
	}

	protected void validateParentLayoutId(
			long groupId, boolean privateLayout, long layoutId,
			long parentLayoutId)
		throws PortalException, SystemException {

		Layout layout = layoutPersistence.findByG_P_L(
			groupId, privateLayout, layoutId);

		if (parentLayoutId != layout.getParentLayoutId()) {

			// Layouts can always be moved to the root level

			if (parentLayoutId == LayoutImpl.DEFAULT_PARENT_LAYOUT_ID) {
				return;
			}

			// Layout cannot become a child of a layout that is not parentable

			Layout parentLayout = layoutPersistence.findByG_P_L(
				groupId, privateLayout, parentLayoutId);

			if (!PortalUtil.isLayoutParentable(parentLayout)) {
				throw new LayoutParentLayoutIdException(
					LayoutParentLayoutIdException.NOT_PARENTABLE);
			}

			// Layout cannot become descendant of itself

			if (isDescendant(layout, parentLayoutId)) {
				throw new LayoutParentLayoutIdException(
					LayoutParentLayoutIdException.SELF_DESCENDANT);
			}

			// If layout is moved, the new first layout must be valid

			if (layout.getParentLayoutId() ==
					LayoutImpl.DEFAULT_PARENT_LAYOUT_ID) {

				List layouts = layoutPersistence.findByG_P_P(
					groupId, privateLayout,
					LayoutImpl.DEFAULT_PARENT_LAYOUT_ID, 0, 2);

				// You can only reach this point if there are more than two
				// layouts at the root level because of the descendant check

				long firstLayoutId = ((Layout)layouts.get(0)).getLayoutId();

				if (firstLayoutId == layoutId) {
					Layout secondLayout = (Layout)layouts.get(1);

					try {
						validateFirstLayout(
							secondLayout.getType(), secondLayout.getHidden());
					}
					catch (LayoutHiddenException lhe) {
						throw new LayoutParentLayoutIdException(
							LayoutParentLayoutIdException.FIRST_LAYOUT_HIDDEN);
					}
					catch (LayoutTypeException lte) {
						throw new LayoutParentLayoutIdException(
							LayoutParentLayoutIdException.FIRST_LAYOUT_TYPE);
					}
				}
			}
		}
	}

	private static Log _log = LogFactory.getLog(LayoutLocalServiceImpl.class);

}