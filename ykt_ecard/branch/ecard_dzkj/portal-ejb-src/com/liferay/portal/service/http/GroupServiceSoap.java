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

package com.liferay.portal.service.http;

import com.liferay.portal.service.spring.GroupServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="GroupServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class GroupServiceSoap {
	public static com.liferay.portal.model.GroupModel addGroup(
		java.lang.String name, java.lang.String friendlyURL)
		throws RemoteException {
		try {
			com.liferay.portal.model.Group returnValue = GroupServiceUtil.addGroup(name,
					friendlyURL);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean addRoles(java.lang.String groupId,
		java.util.List roles) throws RemoteException {
		try {
			boolean returnValue = GroupServiceUtil.addRoles(groupId, roles);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean addUsers(java.lang.String groupId,
		java.util.List users) throws RemoteException {
		try {
			boolean returnValue = GroupServiceUtil.addUsers(groupId, users);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteGroup(java.lang.String groupId)
		throws RemoteException {
		try {
			GroupServiceUtil.deleteGroup(groupId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean exists(java.lang.String name)
		throws RemoteException {
		try {
			boolean returnValue = GroupServiceUtil.exists(name);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.GroupModel getGroupById(
		java.lang.String groupId) throws RemoteException {
		try {
			com.liferay.portal.model.Group returnValue = GroupServiceUtil.getGroupById(groupId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.GroupModel getGroupByName(
		java.lang.String name) throws RemoteException {
		try {
			com.liferay.portal.model.Group returnValue = GroupServiceUtil.getGroupByName(name);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.GroupModel[] getLayouts(
		java.lang.String groupId, java.lang.String parentLayoutId)
		throws RemoteException {
		try {
			java.util.List returnValue = GroupServiceUtil.getLayouts(groupId,
					parentLayoutId);

			return (com.liferay.portal.model.Group[])returnValue.toArray(new com.liferay.portal.model.Group[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getLayoutsSize(java.lang.String groupId)
		throws RemoteException {
		try {
			int returnValue = GroupServiceUtil.getLayoutsSize(groupId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.GroupModel[] getRoles(
		java.lang.String groupId) throws RemoteException {
		try {
			java.util.List returnValue = GroupServiceUtil.getRoles(groupId);

			return (com.liferay.portal.model.Group[])returnValue.toArray(new com.liferay.portal.model.Group[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.GroupModel[] getRoles(
		java.lang.String groupId, int begin, int end) throws RemoteException {
		try {
			java.util.List returnValue = GroupServiceUtil.getRoles(groupId,
					begin, end);

			return (com.liferay.portal.model.Group[])returnValue.toArray(new com.liferay.portal.model.Group[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getRolesSize(java.lang.String groupId)
		throws RemoteException {
		try {
			int returnValue = GroupServiceUtil.getRolesSize(groupId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.GroupModel[] getUsers(
		java.lang.String groupId) throws RemoteException {
		try {
			java.util.List returnValue = GroupServiceUtil.getUsers(groupId);

			return (com.liferay.portal.model.Group[])returnValue.toArray(new com.liferay.portal.model.Group[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.GroupModel[] getUsers(
		java.lang.String groupId, int begin, int end) throws RemoteException {
		try {
			java.util.List returnValue = GroupServiceUtil.getUsers(groupId,
					begin, end);

			return (com.liferay.portal.model.Group[])returnValue.toArray(new com.liferay.portal.model.Group[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getUsersSize(java.lang.String groupId)
		throws RemoteException {
		try {
			int returnValue = GroupServiceUtil.getUsersSize(groupId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean removeRoles(java.lang.String groupId,
		java.lang.String[] roleIds) throws RemoteException {
		try {
			boolean returnValue = GroupServiceUtil.removeRoles(groupId, roleIds);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean removeUsers(java.lang.String groupId,
		java.lang.String[] userIds) throws RemoteException {
		try {
			boolean returnValue = GroupServiceUtil.removeUsers(groupId, userIds);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.GroupModel renameGroupById(
		java.lang.String groupId, java.lang.String newName)
		throws RemoteException {
		try {
			com.liferay.portal.model.Group returnValue = GroupServiceUtil.renameGroupById(groupId,
					newName);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.GroupModel renameGroupByName(
		java.lang.String oldName, java.lang.String newName)
		throws RemoteException {
		try {
			com.liferay.portal.model.Group returnValue = GroupServiceUtil.renameGroupByName(oldName,
					newName);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void setLayouts(java.lang.String groupId,
		java.lang.String parentLayoutId, java.lang.String[] layoutIds)
		throws RemoteException {
		try {
			GroupServiceUtil.setLayouts(groupId, parentLayoutId, layoutIds);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void setRoles(java.lang.String groupId,
		java.lang.String[] roleIds) throws RemoteException {
		try {
			GroupServiceUtil.setRoles(groupId, roleIds);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void setUsers(java.lang.String groupId,
		java.lang.String[] userIds) throws RemoteException {
		try {
			GroupServiceUtil.setUsers(groupId, userIds);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.GroupModel updateFriendlyURL(
		java.lang.String groupId, java.lang.String friendlyURL)
		throws RemoteException {
		try {
			com.liferay.portal.model.Group returnValue = GroupServiceUtil.updateFriendlyURL(groupId,
					friendlyURL);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.GroupModel updateLookAndFeel(
		java.lang.String groupId, java.lang.String themeId,
		java.lang.String colorSchemeId) throws RemoteException {
		try {
			com.liferay.portal.model.Group returnValue = GroupServiceUtil.updateLookAndFeel(groupId,
					themeId, colorSchemeId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasAdmin(java.lang.String groupId)
		throws RemoteException {
		try {
			boolean returnValue = GroupServiceUtil.hasAdmin(groupId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}