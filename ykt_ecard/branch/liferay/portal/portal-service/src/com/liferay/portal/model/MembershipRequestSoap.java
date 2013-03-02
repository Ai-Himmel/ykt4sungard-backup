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

package com.liferay.portal.model;

import java.io.Serializable;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

/**
 * <a href="MembershipRequestSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portal.service.http.MembershipRequestServiceSoap</code>.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.http.MembershipRequestServiceSoap
 *
 */
public class MembershipRequestSoap implements Serializable {
	public static MembershipRequestSoap toSoapModel(MembershipRequest model) {
		MembershipRequestSoap soapModel = new MembershipRequestSoap();

		soapModel.setMembershipRequestId(model.getMembershipRequestId());
		soapModel.setCompanyId(model.getCompanyId());
		soapModel.setUserId(model.getUserId());
		soapModel.setCreateDate(model.getCreateDate());
		soapModel.setGroupId(model.getGroupId());
		soapModel.setComments(model.getComments());
		soapModel.setReplyComments(model.getReplyComments());
		soapModel.setReplyDate(model.getReplyDate());
		soapModel.setReplierUserId(model.getReplierUserId());
		soapModel.setStatusId(model.getStatusId());

		return soapModel;
	}

	public static MembershipRequestSoap[] toSoapModels(List models) {
		List soapModels = new ArrayList(models.size());

		for (int i = 0; i < models.size(); i++) {
			MembershipRequest model = (MembershipRequest)models.get(i);

			soapModels.add(toSoapModel(model));
		}

		return (MembershipRequestSoap[])soapModels.toArray(new MembershipRequestSoap[0]);
	}

	public MembershipRequestSoap() {
	}

	public long getPrimaryKey() {
		return _membershipRequestId;
	}

	public void setPrimaryKey(long pk) {
		setMembershipRequestId(pk);
	}

	public long getMembershipRequestId() {
		return _membershipRequestId;
	}

	public void setMembershipRequestId(long membershipRequestId) {
		_membershipRequestId = membershipRequestId;
	}

	public long getCompanyId() {
		return _companyId;
	}

	public void setCompanyId(long companyId) {
		_companyId = companyId;
	}

	public long getUserId() {
		return _userId;
	}

	public void setUserId(long userId) {
		_userId = userId;
	}

	public Date getCreateDate() {
		return _createDate;
	}

	public void setCreateDate(Date createDate) {
		_createDate = createDate;
	}

	public long getGroupId() {
		return _groupId;
	}

	public void setGroupId(long groupId) {
		_groupId = groupId;
	}

	public String getComments() {
		return _comments;
	}

	public void setComments(String comments) {
		_comments = comments;
	}

	public String getReplyComments() {
		return _replyComments;
	}

	public void setReplyComments(String replyComments) {
		_replyComments = replyComments;
	}

	public Date getReplyDate() {
		return _replyDate;
	}

	public void setReplyDate(Date replyDate) {
		_replyDate = replyDate;
	}

	public long getReplierUserId() {
		return _replierUserId;
	}

	public void setReplierUserId(long replierUserId) {
		_replierUserId = replierUserId;
	}

	public int getStatusId() {
		return _statusId;
	}

	public void setStatusId(int statusId) {
		_statusId = statusId;
	}

	private long _membershipRequestId;
	private long _companyId;
	private long _userId;
	private Date _createDate;
	private long _groupId;
	private String _comments;
	private String _replyComments;
	private Date _replyDate;
	private long _replierUserId;
	private int _statusId;
}