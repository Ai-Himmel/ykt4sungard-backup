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

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Layout;
import com.liferay.portal.service.persistence.GroupUtil;
import com.liferay.portal.service.persistence.LayoutPK;
import com.liferay.portal.service.persistence.LayoutUtil;
import com.liferay.portal.service.spring.LayoutLocalServiceUtil;
import com.liferay.portal.service.spring.LayoutService;

/**
 * <a href="LayoutServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class LayoutServiceImpl extends PrincipalBean implements LayoutService {

	// Business methods

	public Layout addGroupLayout(
			String groupId, String parentLayoutId, String name, String type)
		throws PortalException, SystemException {

		Group group = GroupUtil.findByPrimaryKey(groupId);

		if (!hasAdministrator(group.getCompanyId())) {
			throw new PrincipalException();
		}

		return LayoutLocalServiceUtil.addGroupLayout(
			groupId, parentLayoutId, name, type);
	}

	public Layout addUserLayout(String parentLayoutId, String name, String type)
		throws PortalException, SystemException {

		return LayoutLocalServiceUtil.addUserLayout(
			getUserId(), parentLayoutId, name, type);
	}

	public void deleteLayout(LayoutPK pk)
		throws PortalException, SystemException {

		if (!hasWrite(pk)) {
			throw new PrincipalException();
		}

		LayoutLocalServiceUtil.deleteLayout(pk);
	}

	public Layout getLayout(LayoutPK pk)
		throws PortalException, SystemException {

		return LayoutLocalServiceUtil.getLayout(pk);
	}

	public Layout updateLayout(
			LayoutPK pk, String name, String typeSettings, String friendlyURL)
		throws PortalException, SystemException {

		if (!hasWrite(pk)) {
			throw new PrincipalException();
		}

		return LayoutLocalServiceUtil.updateLayout(
			pk, name, typeSettings, friendlyURL);
	}

	public Layout updateLayout(LayoutPK pk, String typeSettings)
		throws PortalException, SystemException {

		if (!hasWrite(pk)) {
			throw new PrincipalException();
		}

		return LayoutLocalServiceUtil.updateLayout(pk, typeSettings);
	}

	// Permission methods

	public boolean hasWrite(LayoutPK pk)
		throws PortalException, SystemException {

		if (getUserId().equals(pk.userId)) {
			return true;
		}
		else {
			Layout layout = LayoutUtil.findByPrimaryKey(pk);

			if (hasAdministrator(layout.getCompanyId())) {
				return true;
			}
		}

		return false;
	}

}