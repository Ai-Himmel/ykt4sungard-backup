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

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portal.model.MembershipRequest;
import com.liferay.portal.service.base.MembershipRequestServiceBaseImpl;
import com.liferay.portal.service.permission.GroupPermissionUtil;

/**
 * <a href="MembershipRequestServiceImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Jorge Ferrer
 *
 */
public class MembershipRequestServiceImpl
	extends MembershipRequestServiceBaseImpl {

	public MembershipRequest addMembershipRequest(long groupId, String comments)
		throws PortalException, SystemException {

		return membershipRequestLocalService.addMembershipRequest(
			getUserId(), groupId, comments);
	}

	public void deleteMembershipRequests(long groupId, int statusId)
		throws PortalException, SystemException {

		GroupPermissionUtil.check(
			getPermissionChecker(), groupId, ActionKeys.ASSIGN_MEMBERS);

		membershipRequestLocalService.deleteMembershipRequests(
			groupId, statusId);
	}

	public MembershipRequest getMembershipRequest(long membershipRequestId)
		throws SystemException, PortalException {

		return membershipRequestLocalService.getMembershipRequest(
			membershipRequestId);
	}

	public void updateStatus(
			long membershipRequestId, String reviewComments, int statusId)
		throws PortalException, SystemException {

		MembershipRequest membershipRequest =
			membershipRequestPersistence.findByPrimaryKey(membershipRequestId);

		GroupPermissionUtil.check(
			getPermissionChecker(), membershipRequest.getGroupId(),
			ActionKeys.ASSIGN_MEMBERS);

		membershipRequestLocalService.updateStatus(
			getUserId(), membershipRequestId, reviewComments, statusId);
	}

}