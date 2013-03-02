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

import com.liferay.portal.MembershipRequestCommentsException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.language.LanguageUtil;
import com.liferay.portal.kernel.mail.MailMessage;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.MembershipRequest;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.User;
import com.liferay.portal.model.UserGroupRole;
import com.liferay.portal.model.impl.MembershipRequestImpl;
import com.liferay.portal.model.impl.RoleImpl;
import com.liferay.portal.service.base.MembershipRequestLocalServiceBaseImpl;
import com.liferay.portal.util.PrefsPropsUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.util.UniqueList;

import java.io.IOException;

import java.util.Date;
import java.util.Iterator;
import java.util.List;

import javax.mail.internet.InternetAddress;

/**
 * <a href="MembershipRequestLocalServiceImpl.java.html"><b><i>View Source</i>
 * </b></a>
 *
 * @author Jorge Ferrer
 *
 */
public class MembershipRequestLocalServiceImpl
	extends MembershipRequestLocalServiceBaseImpl {

	public MembershipRequest addMembershipRequest(
			long userId, long groupId, String comments)
		throws PortalException, SystemException {

		User user = userPersistence.findByPrimaryKey(userId);
		Date now = new Date();

		validate(comments);

		long membershipRequestId = counterLocalService.increment();

		MembershipRequest membershipRequest =
			membershipRequestPersistence.create(membershipRequestId);

		membershipRequest.setCompanyId(user.getCompanyId());
		membershipRequest.setUserId(userId);
		membershipRequest.setCreateDate(now);
		membershipRequest.setGroupId(groupId);
		membershipRequest.setComments(comments);
		membershipRequest.setStatusId(MembershipRequestImpl.STATUS_PENDING);

		membershipRequestPersistence.update(membershipRequest);

		notifyCommunityAdministrators(membershipRequest);

		return membershipRequest;
	}

	public MembershipRequest getMembershipRequest(long membershipRequestId)
		throws PortalException, SystemException {

		return membershipRequestPersistence.findByPrimaryKey(
			membershipRequestId);
	}

	public void deleteMembershipRequests(long groupId) throws SystemException {
		membershipRequestPersistence.removeByGroupId(groupId);
	}

	public void deleteMembershipRequests(long groupId, int statusId)
		throws SystemException {

		membershipRequestPersistence.removeByG_S(groupId, statusId);
	}

	public List search(long groupId, int status, int begin, int end)
		throws SystemException {

		return membershipRequestPersistence.findByG_S(
			groupId, status, begin, end);
	}

	public int searchCount(long groupId, int status) throws SystemException {
		return membershipRequestPersistence.countByG_S(groupId, status);
	}

	public void updateStatus(
			long replierUserId, long membershipRequestId, String replyComments,
			int statusId)
		throws PortalException, SystemException {

		validate(replyComments);

		MembershipRequest membershipRequest =
			membershipRequestPersistence.findByPrimaryKey(
				membershipRequestId);

		membershipRequest.setReplyComments(replyComments);
		membershipRequest.setReplyDate(new Date());
		membershipRequest.setReplierUserId(replierUserId);
		membershipRequest.setStatusId(statusId);

		membershipRequestPersistence.update(membershipRequest);

		if (statusId == MembershipRequestImpl.STATUS_APPROVED) {
			long[] addUserIds = new long[] {membershipRequest.getUserId()};

			userLocalService.addGroupUsers(
				membershipRequest.getGroupId(), addUserIds);
		}

		notify(
			membershipRequest.getUserId(), membershipRequest,
			PropsUtil.COMMUNITIES_EMAIL_MEMBERSHIP_REPLY_SUBJECT,
			PropsUtil.COMMUNITIES_EMAIL_MEMBERSHIP_REPLY_BODY);
	}

	protected void notify(
			long userId, MembershipRequest membershipRequest,
			String subjectProperty, String bodyProperty)
		throws PortalException, SystemException {

		try {
			Company company = companyPersistence.findByPrimaryKey(
				membershipRequest.getCompanyId());

			Group group = groupPersistence.findByPrimaryKey(
				membershipRequest.getGroupId());

			User user = userPersistence.findByPrimaryKey(userId);

			String fromName = PrefsPropsUtil.getString(
				membershipRequest.getCompanyId(),
				PropsUtil.COMMUNITIES_EMAIL_FROM_NAME);

			String fromAddress = PrefsPropsUtil.getString(
				membershipRequest.getCompanyId(),
				PropsUtil.COMMUNITIES_EMAIL_FROM_ADDRESS);

			String toName = user.getFullName();
			String toAddress = user.getEmailAddress();

			String subject = PrefsPropsUtil.getContent(
				membershipRequest.getCompanyId(), subjectProperty);

			String body = PrefsPropsUtil.getContent(
				membershipRequest.getCompanyId(), bodyProperty);

			String statusKey = null;

			if (membershipRequest.getStatusId() ==
					MembershipRequestImpl.STATUS_APPROVED) {

				statusKey = "approved";
			}
			else if (membershipRequest.getStatusId() ==
						MembershipRequestImpl.STATUS_DENIED) {

				statusKey = "denied";
			}
			else {
				statusKey = "pending";
			}

			subject = StringUtil.replace(
				subject,
				new String[] {
					"[$COMMUNITY_NAME$]",
					"[$COMPANY_ID$]",
					"[$COMPANY_MX$]",
					"[$COMPANY_NAME$]",
					"[$FROM_ADDRESS$]",
					"[$FROM_NAME$]",
					"[$PORTAL_URL$]",
					"[$STATUS$]",
					"[$TO_NAME$]",
					"[$USER_ADDRESS$]",
					"[$USER_NAME$]",
				},
				new String[] {
					group.getName(),
					String.valueOf(company.getCompanyId()),
					company.getMx(),
					company.getName(),
					fromAddress,
					fromName,
					company.getVirtualHost(),
					LanguageUtil.get(user.getLocale(), statusKey),
					toName,
					user.getEmailAddress(),
					user.getFullName()
				});

			body = StringUtil.replace(
				body,
				new String[] {
					"[$COMMENTS$]",
					"[$COMMUNITY_NAME$]",
					"[$COMPANY_ID$]",
					"[$COMPANY_MX$]",
					"[$COMPANY_NAME$]",
					"[$FROM_ADDRESS$]",
					"[$FROM_NAME$]",
					"[$PORTAL_URL$]",
					"[$REPLY_COMMENTS$]",
					"[$STATUS$]",
					"[$TO_NAME$]",
					"[$USER_ADDRESS$]",
					"[$USER_NAME$]",
				},
				new String[] {
					membershipRequest.getComments(),
					group.getName(),
					String.valueOf(company.getCompanyId()),
					company.getMx(),
					company.getName(),
					fromAddress,
					fromName,
					company.getVirtualHost(),
					membershipRequest.getReplyComments(),
					LanguageUtil.get(user.getLocale(), statusKey),
					toName,
					user.getEmailAddress(),
					user.getFullName()
				});

			InternetAddress from = new InternetAddress(fromAddress, fromName);

			InternetAddress to = new InternetAddress(toAddress, toName);

			MailMessage message = new MailMessage(
				from, to, subject, body, true);

			mailService.sendEmail(message);
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}
	}

	protected void notifyCommunityAdministrators(
			MembershipRequest membershipRequest)
		throws PortalException, SystemException {

		List admins = new UniqueList();

		Role communityAdminRole = roleLocalService.getRole(
			membershipRequest.getCompanyId(), RoleImpl.COMMUNITY_ADMINISTRATOR);

		List communityAdmins =
			userGroupRoleLocalService.getUserGroupRolesByGroupAndRole(
				membershipRequest.getGroupId(), communityAdminRole.getRoleId());

		admins.addAll(communityAdmins);

		Role communityOwnerRole = rolePersistence.findByC_N(
			membershipRequest.getCompanyId(), RoleImpl.COMMUNITY_OWNER);

		List communityOwners =
			userGroupRoleLocalService.getUserGroupRolesByGroupAndRole(
				membershipRequest.getGroupId(), communityOwnerRole.getRoleId());

		admins.addAll(communityOwners);

		Iterator itr = admins.iterator();

		while (itr.hasNext()) {
			UserGroupRole userGroupRole = (UserGroupRole)itr.next();

			notify(
				userGroupRole.getUserId(), membershipRequest,
				PropsUtil.COMMUNITIES_EMAIL_MEMBERSHIP_REQUEST_SUBJECT,
				PropsUtil.COMMUNITIES_EMAIL_MEMBERSHIP_REQUEST_BODY);
		}
	}

	protected void validate(String comments)
		throws PortalException, SystemException {

		if ((Validator.isNull(comments)) || (Validator.isNumber(comments))) {
			throw new MembershipRequestCommentsException();
		}
	}

}