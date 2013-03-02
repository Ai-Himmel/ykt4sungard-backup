/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.portal.DuplicateGroupException;
import com.liferay.portal.GroupFriendlyURLException;
import com.liferay.portal.GroupNameException;
import com.liferay.portal.NoSuchGroupException;
import com.liferay.portal.PortalException;
import com.liferay.portal.RequiredGroupException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.ColorScheme;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.LayoutTypePortlet;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.Theme;
import com.liferay.portal.model.User;
import com.liferay.portal.service.persistence.GroupUtil;
import com.liferay.portal.service.persistence.LayoutUtil;
import com.liferay.portal.service.spring.ColorSchemeServiceUtil;
import com.liferay.portal.service.spring.GroupLocalService;
import com.liferay.portal.service.spring.LayoutLocalServiceUtil;
import com.liferay.portal.service.spring.UserLocalServiceUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portlet.bookmarks.service.spring.BookmarksEntryLocalServiceUtil;
import com.liferay.portlet.bookmarks.service.spring.BookmarksFolderLocalServiceUtil;
import com.liferay.portlet.calendar.service.spring.CalEventLocalServiceUtil;
import com.liferay.portlet.documentlibrary.service.spring.DLRepositoryLocalServiceUtil;
import com.liferay.portlet.imagegallery.service.spring.IGFolderLocalServiceUtil;
import com.liferay.portlet.journal.service.spring.JournalArticleLocalServiceUtil;
import com.liferay.portlet.messageboards.service.spring.MBTopicLocalServiceUtil;
import com.liferay.portlet.polls.service.spring.PollsQuestionLocalServiceUtil;
import com.liferay.util.CollectionFactory;
import com.liferay.util.SimpleCachePool;
import com.liferay.util.StringPool;
import com.liferay.util.Validator;

import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 * <a href="GroupLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.5 $
 *
 */
public class GroupLocalServiceImpl implements GroupLocalService {

	// Business methods

	public Group addGroup(String companyId, String name, String friendlyURL)
		throws PortalException, SystemException {

		validate(companyId, name);
		validate(null, companyId, friendlyURL);

		String groupId = Long.toString(CounterServiceUtil.increment(
			Group.class.getName()));

		Group group = GroupUtil.create(groupId);

		group.setCompanyId(companyId);
		group.setParentGroupId(Group.DEFAULT_PARENT_GROUP_ID);
		group.setName(name);
		group.setFriendlyURL(friendlyURL);
		group.setThemeId(Theme.DEFAULT_THEME_ID);
		group.setColorSchemeId(ColorScheme.DEFAULT_COLOR_SCHEME_ID);

		GroupUtil.update(group);

		return group;
	}

	public boolean addRole(String groupId, String roleId)
		throws PortalException, SystemException {

		return GroupUtil.addRole(groupId, roleId);
	}

	public boolean addRole(String groupId, Role role)
		throws PortalException, SystemException {

		return GroupUtil.addRole(groupId, role);
	}

	public boolean addRoles(String groupId, String[] roleIds)
		throws PortalException, SystemException {

		return GroupUtil.addRoles(groupId, roleIds);
	}

	public boolean addRoles(String groupId, List roles)
		throws PortalException, SystemException {

		return GroupUtil.addRoles(groupId, roles);
	}

	public boolean addUser(String groupId, String userId)
		throws PortalException, SystemException {

		return GroupUtil.addUser(groupId, userId);
	}

	public boolean addUser(String groupId, User user)
		throws PortalException, SystemException {

		return GroupUtil.addUser(groupId, user);
	}

	public boolean addUsers(String groupId, String[] userIds)
		throws PortalException, SystemException {

		return GroupUtil.addUsers(groupId, userIds);
	}

	public boolean addUsers(String groupId, List users)
		throws PortalException, SystemException {

		return GroupUtil.addUsers(groupId, users);
	}

	public void checkSystemGroups(String companyId) throws SystemException {
		Set existingGroups = CollectionFactory.getHashSet();

		Iterator itr = GroupUtil.findByCompanyId(companyId).iterator();

		while (itr.hasNext()) {
			Group group = (Group)itr.next();

			existingGroups.add(group.getName());
		}

		String[] systemGroups = PortalUtil.getSystemGroups();

		for (int i = 0; i < systemGroups.length; i++) {
			if (!existingGroups.contains(systemGroups[i])) {

				// Add system group

				String groupId = Long.toString(CounterServiceUtil.increment(
					Group.class.getName()));

				Group group = GroupUtil.create(groupId);

				group.setCompanyId(companyId);
				group.setParentGroupId(Group.DEFAULT_PARENT_GROUP_ID);
				group.setName(systemGroups[i]);
				group.setThemeId(Theme.DEFAULT_THEME_ID);
				group.setColorSchemeId(ColorScheme.DEFAULT_COLOR_SCHEME_ID);

				GroupUtil.update(group);
			}
		}
	}

	public void deleteGroup(String groupId)
		throws PortalException, SystemException {

		Group group = GroupUtil.findByPrimaryKey(groupId);

		if (PortalUtil.isSystemGroup(group.getName())) {
			throw new RequiredGroupException();
		}

		// Delete group's layouts

		Iterator itr = LayoutUtil.findByUserId(
			Layout.GROUP + groupId).iterator();

		while (itr.hasNext()) {
			Layout layout = (Layout)itr.next();

			LayoutLocalServiceUtil.deleteLayout(layout.getPrimaryKey());
		}

		// Delete group's bookmarks entries and folders

		BookmarksEntryLocalServiceUtil.deleteAllByGroup(groupId);
		BookmarksFolderLocalServiceUtil.deleteAllByGroup(groupId);

		// Delete groups's calendar events

		CalEventLocalServiceUtil.deleteAllByGroup(groupId);

		// Delete group's document library repositories

		DLRepositoryLocalServiceUtil.deleteAll(groupId);

		// Delete group's image gallery folders

		IGFolderLocalServiceUtil.deleteAll(groupId);

		// Delete group's journal articles

		JournalArticleLocalServiceUtil.deleteAll(groupId);

		// Delete group's message boards topics

		MBTopicLocalServiceUtil.deleteAll(groupId);

		// Delete group's polls questions

		PollsQuestionLocalServiceUtil.deleteAll(groupId);

		// Delete group

		GroupUtil.remove(groupId);
	}

	public boolean deleteRole(String groupId, String roleId)
		throws PortalException, SystemException {

		return GroupUtil.removeRole(groupId, roleId);
	}

	public boolean deleteRole(String groupId, Role role)
		throws PortalException, SystemException {

		return GroupUtil.removeRole(groupId, role);
	}

	public boolean deleteUser(String groupId, String userId)
		throws PortalException, SystemException {

		return GroupUtil.removeUser(groupId, userId);
	}

	public boolean deleteUser(String groupId, User user)
		throws PortalException, SystemException {

		return GroupUtil.removeUser(groupId, user);
	}

	public boolean exists(String companyId, String name)
		throws SystemException {

		Iterator itr = GroupUtil.findByCompanyId(companyId).iterator();

		while (itr.hasNext()) {
			Group group = (Group)itr.next();

			if (group.getName().equalsIgnoreCase(name)) {
				return true;
			}
		}

		return false;
	}

	public boolean exists(String companyId, String[] names)
		throws SystemException {

		for (int i = 0; i < names.length; i++) {
			if (!exists(companyId, names[i])) {
				return false;
			}
		}

		return true;
	}

	public Group getGroupByFriendlyURL(String companyId, String friendlyURL)
		throws PortalException, SystemException {

		if (Validator.isNull(friendlyURL)) {
			throw new NoSuchGroupException();
		}

		return GroupUtil.findByC_F(companyId, friendlyURL);
	}

	public Group getGroupById(String groupId)
		throws PortalException, SystemException {

		return GroupUtil.findByPrimaryKey(groupId);
	}

	public Group getGroupByName(String companyId, String name)
		throws PortalException, SystemException {

		if (PortalUtil.isSystemGroup(name)) {
			Map groupsPool = _getGroupsPool(companyId);

			Group group = (Group)groupsPool.get(name);

			if (group == null) {
				group = GroupUtil.findByC_N(companyId, name);

				groupsPool.put(name, group);
			}

			return group;
		}
		else {
			return GroupUtil.findByC_N(companyId, name);
		}
	}

	public String getGroupId(String companyId, String name)
		throws SystemException {

		Iterator itr = GroupUtil.findByCompanyId(companyId).iterator();

		while (itr.hasNext()) {
			Group group = (Group)itr.next();

			if (group.getName().equalsIgnoreCase(name)) {
				return group.getGroupId();
			}
		}

		return null;
	}

	public List getLayouts(String groupId, String parentLayoutId)
		throws PortalException, SystemException {

		List layouts = LayoutUtil.findByU_P(
			Layout.GROUP + groupId, parentLayoutId);

		if ((layouts.size() == 0) &&
			(parentLayoutId.equals(Layout.DEFAULT_PARENT_LAYOUT_ID))) {

			Group group = GroupUtil.findByPrimaryKey(groupId);

			Group generalGuestGroup = getGroupByName(
				group.getCompanyId(), Group.GENERAL_GUEST);

			Group generalUserGroup = getGroupByName(
				group.getCompanyId(), Group.GENERAL_USER);

			String[] defaultPortletIds = null;
			String defaultLayoutName = null;

			if (generalGuestGroup.getGroupId().equals(groupId)) {
				defaultPortletIds = PropsUtil.getArray(
					PropsUtil.DEFAULT_GUEST_LAYOUT_PORTLET_KEYS);
				defaultLayoutName = PropsUtil.get(
					PropsUtil.DEFAULT_GUEST_LAYOUT_NAME);
			}
			else if (generalUserGroup.getGroupId().equals(groupId)) {
				defaultPortletIds = PropsUtil.getArray(
					PropsUtil.DEFAULT_USER_LAYOUT_PORTLET_KEYS);
				defaultLayoutName = PropsUtil.get(
					PropsUtil.DEFAULT_USER_LAYOUT_NAME);
			}

			if ((defaultPortletIds != null) && (defaultLayoutName != null)) {
				Layout layout = LayoutLocalServiceUtil.addGroupLayout(
					groupId, Layout.DEFAULT_PARENT_LAYOUT_ID, defaultLayoutName,
					Layout.TYPE_PORTLET);

				LayoutTypePortlet layoutType =
					(LayoutTypePortlet)layout.getLayoutType();

				for (int i = 0; i < defaultPortletIds.length; i++) {
					layoutType.addPortletId(defaultPortletIds[i]);
				}

				LayoutLocalServiceUtil.updateLayout(
					layout.getPrimaryKey(), layout.getTypeSettings());
			}
		}

		return layouts;
	}

	public int getLayoutsSize(String groupId) throws SystemException {
		return LayoutUtil.countByUserId(Layout.GROUP + groupId);
	}

	public List getRoles(String groupId)
		throws PortalException, SystemException {

		return GroupUtil.getRoles(groupId);
	}

	public List getRoles(String groupId, int begin, int end)
		throws PortalException, SystemException {

		return GroupUtil.getRoles(groupId, begin, end);
	}

	public int getRolesSize(String groupId) throws SystemException {
		return GroupUtil.getRolesSize(groupId);
	}

	public List getUsers(String groupId)
		throws PortalException, SystemException {

		return GroupUtil.getUsers(groupId);
	}

	public List getUsers(String groupId, int begin, int end)
		throws PortalException, SystemException {

		return GroupUtil.getUsers(groupId, begin, end);
	}

	public int getUsersSize(String groupId) throws SystemException {
		return GroupUtil.getUsersSize(groupId);
	}

	public boolean removeRoles(String groupId, String[] roleIds)
		throws PortalException, SystemException {

		return GroupUtil.removeRoles(groupId, roleIds);
	}

	public boolean removeRoles(String groupId, List roles)
		throws PortalException, SystemException {

		return GroupUtil.removeRoles(groupId, roles);
	}

	public boolean removeUsers(String groupId, String[] userIds)
		throws PortalException, SystemException {

		return GroupUtil.removeUsers(groupId, userIds);
	}

	public boolean removeUsers(String groupId, List users)
		throws PortalException, SystemException {

		return GroupUtil.removeUsers(groupId, users);
	}

	public Group renameGroupById(String groupId, String newName)
		throws PortalException, SystemException {

		Group group = GroupUtil.findByPrimaryKey(groupId);

		if (group.getName().equalsIgnoreCase(newName)) {
			return group;
		}

		if (PortalUtil.isSystemGroup(group.getName())) {
			throw new RequiredGroupException();
		}

		validate(group.getCompanyId(), newName);

		group.setName(newName);

		GroupUtil.update(group);

		return group;
	}

	public Group renameGroupByName(
			String companyId, String oldName, String newName)
		throws PortalException, SystemException {

		if (oldName.equalsIgnoreCase(newName)) {
			return GroupUtil.findByPrimaryKey(getGroupId(companyId, oldName));
		}

		try {
			validate(companyId, oldName);
		}
		catch (DuplicateGroupException dge) {
			if (PortalUtil.isSystemGroup(oldName)) {
				throw new RequiredGroupException();
			}

			validate(companyId, newName);

			Group group = GroupUtil.findByPrimaryKey(
				getGroupId(companyId, oldName));

			group.setName(newName);

			GroupUtil.update(group);

			return group;
		}

		throw new NoSuchGroupException();
	}

	public void setLayouts(
			String groupId, String parentLayoutId, String[] layoutIds)
		throws PortalException, SystemException {

		UserLocalServiceUtil.setLayouts(
			Layout.GROUP + groupId, parentLayoutId, layoutIds);
	}

	public void setRoles(String groupId, String[] roleIds)
		throws PortalException, SystemException {

		GroupUtil.setRoles(groupId, roleIds);
	}

	public void setRoles(String groupId, List roles)
		throws PortalException, SystemException {

		GroupUtil.setRoles(groupId, roles);
	}

	public void setUsers(String groupId, String[] userIds)
		throws PortalException, SystemException {

		GroupUtil.setUsers(groupId, userIds);
	}

	public void setUsers(String groupId, List users)
		throws PortalException, SystemException {

		GroupUtil.setUsers(groupId, users);
	}

	public Group updateFriendlyURL(String groupId, String friendlyURL)
		throws PortalException, SystemException {

		Group group = GroupUtil.findByPrimaryKey(groupId);

		validate(groupId, group.getCompanyId(), friendlyURL);

		group.setFriendlyURL(friendlyURL);

		GroupUtil.update(group);

		return group;
	}

	public Group updateLookAndFeel(
			String groupId, String themeId, String colorSchemeId)
		throws PortalException, SystemException {

		colorSchemeId = ColorSchemeServiceUtil.getColorScheme(
			themeId, colorSchemeId).getColorSchemeId();

		Group group = GroupUtil.findByPrimaryKey(groupId);

		group.setThemeId(themeId);
		group.setColorSchemeId(colorSchemeId);

		GroupUtil.update(group);

		return group;
	}

	public void validate(String companyId, String name)
		throws PortalException, SystemException {

		if ((Validator.isNull(name)) || (Validator.isNumber(name)) ||
			(name.indexOf(StringPool.COMMA) != -1) ||
			(name.indexOf(StringPool.STAR) != -1) ||
			(name.equalsIgnoreCase("Desktop"))) {

			throw new GroupNameException();
		}
		else if (exists(companyId, name)) {
			throw new DuplicateGroupException();
		}
	}

	public void validate(
			String groupId, String companyId, String friendlyURL)
		throws PortalException, SystemException {

		if (Validator.isNotNull(friendlyURL)) {
			int exceptionType = GroupFriendlyURLException.validate(friendlyURL);

			if (exceptionType != -1) {
				throw new GroupFriendlyURLException(exceptionType);
			}

			try {
				Group group = GroupUtil.findByC_F(companyId, friendlyURL);

				if ((groupId == null) || !group.getGroupId().equals(groupId)) {
					throw new GroupFriendlyURLException(
						GroupFriendlyURLException.DUPLICATE);
				}
			}
			catch (NoSuchGroupException nsle) {
			}
		}
	}

	// Private methods

	private Map _getGroupsPool(String id) {
		String scpId = GroupLocalServiceImpl.class.getName() + "." + id;

		Map groupsPool = (Map)SimpleCachePool.get(scpId);

		if (groupsPool == null) {
			groupsPool = CollectionFactory.getSyncHashMap();

			SimpleCachePool.put(scpId, groupsPool);
		}

		return groupsPool;
	}

}