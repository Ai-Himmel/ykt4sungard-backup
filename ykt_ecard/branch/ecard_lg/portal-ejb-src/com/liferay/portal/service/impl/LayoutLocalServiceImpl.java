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

import com.liferay.portal.LayoutFriendlyURLException;
import com.liferay.portal.LayoutNameException;
import com.liferay.portal.LayoutTypeException;
import com.liferay.portal.NoSuchLayoutException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.User;
import com.liferay.portal.service.persistence.GroupUtil;
import com.liferay.portal.service.persistence.LayoutPK;
import com.liferay.portal.service.persistence.LayoutUtil;
import com.liferay.portal.service.persistence.UserUtil;
import com.liferay.portal.service.spring.LayoutLocalService;
import com.liferay.portal.service.spring.PortletPreferencesLocalServiceUtil;
import com.liferay.util.StringPool;
import com.liferay.util.Validator;

import java.util.List;

/**
 * <a href="LayoutLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class LayoutLocalServiceImpl implements LayoutLocalService {

	// Business methods

	public Layout addGroupLayout(
			String groupId, String parentLayoutId, String name, String type)
		throws PortalException, SystemException {

		Group group = GroupUtil.findByPrimaryKey(groupId);

		LayoutPK pk = new LayoutPK(
			_getNextGroupLayoutId(groupId), Layout.GROUP + groupId);
		String companyId = group.getCompanyId();
		int priority = _getNextPriority(Layout.GROUP + groupId, parentLayoutId);

		return _addLayout(pk, companyId, parentLayoutId, name, type, priority);
	}

	public Layout addUserLayout(
			String userId, String parentLayoutId, String name, String type)
		throws PortalException, SystemException {

		User user = UserUtil.findByPrimaryKey(userId);

		LayoutPK pk = new LayoutPK(_getNextUserLayoutId(userId), userId);
		String companyId = user.getCompanyId();
		int priority = _getNextPriority(userId, parentLayoutId);

		return _addLayout(pk, companyId, parentLayoutId, name, type, priority);
	}

	public void deleteAll(String userId) throws SystemException {
		LayoutUtil.removeByUserId(userId);
	}

	public void deleteLayout(LayoutPK pk)
		throws PortalException, SystemException {

		Layout layout = LayoutUtil.findByPrimaryKey(pk);

		deleteLayout(layout);
	}

	public void deleteLayout(Layout layout)
		throws PortalException, SystemException {

		// Delete child layouts

		List childLayouts = LayoutUtil.findByU_P(
			layout.getUserId(), layout.getLayoutId());

		for (int i = 0; i < childLayouts.size(); i++) {
			Layout childLayout = (Layout)childLayouts.get(i);

			deleteLayout(childLayout);
		}

		// Delete layout's portlet preferences

		PortletPreferencesLocalServiceUtil.deleteAllByLayout(
			layout.getPrimaryKey());

		// Delete layout

		LayoutUtil.remove(layout.getPrimaryKey());
	}

	public Layout getLayout(LayoutPK pk)
		throws PortalException, SystemException {

		return LayoutUtil.findByPrimaryKey(pk);
	}

	public Layout getLayoutByFriendlyURL(String groupId, String friendlyURL)
		throws PortalException, SystemException {

		if (Validator.isNull(friendlyURL)) {
			throw new NoSuchLayoutException();
		}

		return LayoutUtil.findByU_F(Layout.GROUP + groupId, friendlyURL);
	}

	public List getLayouts(String userId) throws SystemException {
		return LayoutUtil.findByUserId(userId);
	}

	public Layout updateLayout(
			LayoutPK pk, String name, String typeSettings, String friendlyURL)
		throws PortalException, SystemException {

		_validate(name);

		if (Layout.isGroup(pk.layoutId)) {
			_validate(pk, friendlyURL);
		}
		else {
			friendlyURL = null;
		}

		Layout layout = LayoutUtil.findByPrimaryKey(pk);

		layout.setName(name);
		layout.setTypeSettings(typeSettings);
		layout.setFriendlyURL(friendlyURL);

		LayoutUtil.update(layout);

		return layout;
	}

	public Layout updateLayout(LayoutPK pk, String typeSettings)
		throws PortalException, SystemException {

		Layout layout = LayoutUtil.findByPrimaryKey(pk);

		layout.setTypeSettings(typeSettings);

		LayoutUtil.update(layout);

		return layout;
	}

	// Private methods

	private Layout _addLayout(
			LayoutPK pk, String companyId, String parentLayoutId, String name,
			String type, int priority)
		throws PortalException, SystemException {

		parentLayoutId = _getParentLayoutId(pk.userId, parentLayoutId);

		_validate(name);

		if ((parentLayoutId.equals(Layout.DEFAULT_PARENT_LAYOUT_ID)) &&
			(LayoutUtil.countByU_P(pk.userId, parentLayoutId) == 0) &&
			(!type.equals(Layout.TYPE_PORTLET))) {

			throw new LayoutTypeException();
		}

		Layout layout = LayoutUtil.create(pk);

		layout.setCompanyId(companyId);
		layout.setParentLayoutId(parentLayoutId);
		layout.setName(name);
		layout.setType(type);
		layout.setPriority(priority);

		LayoutUtil.update(layout);

		return layout;
	}

	private String _getNextGroupLayoutId(String groupId)
		throws SystemException {

		int layoutId = 0;

		List layouts = LayoutUtil.findByUserId(Layout.GROUP + groupId);

		for (int i = 0; i < layouts.size(); i++) {
			Layout curLayout = (Layout)layouts.get(i);

			String curLayoutId = curLayout.getLayoutId();

			int x = Integer.parseInt(curLayoutId.substring(
				groupId.length() + 1, curLayoutId.length()));

			if (x > layoutId) {
				layoutId = x;
			}
		}

		return groupId + "." + Integer.toString(++layoutId);
	}

	private String _getNextUserLayoutId(String userId) throws SystemException {
		int layoutId = 0;

		List layouts = LayoutUtil.findByUserId(userId);

		for (int i = 0; i < layouts.size(); i++) {
			Layout curLayout = (Layout)layouts.get(i);

			String curLayoutId = curLayout.getLayoutId();

			int x = Integer.parseInt(curLayoutId);

			if (x > layoutId) {
				layoutId = x;
			}
		}

		return Integer.toString(++layoutId);
	}

	private int _getNextPriority(String userId, String parentLayoutId)
		throws SystemException {

		List layouts = LayoutUtil.findByU_P(userId, parentLayoutId);

		if (layouts.size() == 0) {
			return 0;
		}

		Layout layout = (Layout)layouts.get(layouts.size() - 1);

		return layout.getPriority() + 1;
	}

	private String _getParentLayoutId(String userId, String parentLayoutId)
		throws PortalException, SystemException {

		if (!parentLayoutId.equals(Layout.DEFAULT_PARENT_LAYOUT_ID)) {

			// Ensure parent layout exists

			try {
				Layout layout = LayoutUtil.findByPrimaryKey(
					new LayoutPK(parentLayoutId, userId));
			}
			catch (NoSuchLayoutException nsfe) {
				parentLayoutId = Layout.DEFAULT_PARENT_LAYOUT_ID;
			}
		}

		return parentLayoutId;
	}

	private void _validate(String name) throws PortalException {
		if (Validator.isNull(name) || name.endsWith(StringPool.STAR)) {
			throw new LayoutNameException();
		}
	}

	private void _validate(LayoutPK pk, String friendlyURL)
		throws PortalException, SystemException {

		if (Validator.isNotNull(friendlyURL)) {
			int exceptionType =
				LayoutFriendlyURLException.validate(friendlyURL);

			if (exceptionType != -1) {
				throw new LayoutFriendlyURLException(exceptionType);
			}

			try {
				Layout layout = LayoutUtil.findByU_F(pk.userId, friendlyURL);

				if (!layout.getLayoutId().equals(pk.layoutId)) {
					throw new LayoutFriendlyURLException(
						LayoutFriendlyURLException.DUPLICATE);
				}
			}
			catch (NoSuchLayoutException nsle) {
			}
		}
	}

}