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

package com.liferay.portal.model.impl;

import com.liferay.portal.kernel.bean.ReadOnlyBeanHandler;
import com.liferay.portal.kernel.util.DateUtil;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.MembershipRequest;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

import java.util.Date;

/**
 * <a href="MembershipRequestModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>MembershipRequest</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.MembershipRequest
 * @see com.liferay.portal.service.model.MembershipRequestModel
 * @see com.liferay.portal.service.model.impl.MembershipRequestImpl
 *
 */
public class MembershipRequestModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "MembershipRequest";
	public static final Object[][] TABLE_COLUMNS = {
			{ "membershipRequestId", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "userId", new Integer(Types.BIGINT) },
			

			{ "createDate", new Integer(Types.TIMESTAMP) },
			

			{ "groupId", new Integer(Types.BIGINT) },
			

			{ "comments", new Integer(Types.VARCHAR) },
			

			{ "replyComments", new Integer(Types.VARCHAR) },
			

			{ "replyDate", new Integer(Types.TIMESTAMP) },
			

			{ "replierUserId", new Integer(Types.BIGINT) },
			

			{ "statusId", new Integer(Types.INTEGER) }
		};
	public static final String TABLE_SQL_CREATE = "create table MembershipRequest (membershipRequestId LONG not null primary key,companyId LONG,userId LONG,createDate DATE null,groupId LONG,comments STRING null,replyComments STRING null,replyDate DATE null,replierUserId LONG,statusId INTEGER)";
	public static final String TABLE_SQL_DROP = "drop table MembershipRequest";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portal.model.MembershipRequest"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portal.model.MembershipRequest"));

	public MembershipRequestModelImpl() {
	}

	public long getPrimaryKey() {
		return _membershipRequestId;
	}

	public void setPrimaryKey(long pk) {
		setMembershipRequestId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_membershipRequestId);
	}

	public long getMembershipRequestId() {
		return _membershipRequestId;
	}

	public void setMembershipRequestId(long membershipRequestId) {
		if (membershipRequestId != _membershipRequestId) {
			_membershipRequestId = membershipRequestId;
		}
	}

	public long getCompanyId() {
		return _companyId;
	}

	public void setCompanyId(long companyId) {
		if (companyId != _companyId) {
			_companyId = companyId;
		}
	}

	public long getUserId() {
		return _userId;
	}

	public void setUserId(long userId) {
		if (userId != _userId) {
			_userId = userId;
		}
	}

	public Date getCreateDate() {
		return _createDate;
	}

	public void setCreateDate(Date createDate) {
		if (((createDate == null) && (_createDate != null)) ||
				((createDate != null) && (_createDate == null)) ||
				((createDate != null) && (_createDate != null) &&
				!createDate.equals(_createDate))) {
			_createDate = createDate;
		}
	}

	public long getGroupId() {
		return _groupId;
	}

	public void setGroupId(long groupId) {
		if (groupId != _groupId) {
			_groupId = groupId;
		}
	}

	public String getComments() {
		return GetterUtil.getString(_comments);
	}

	public void setComments(String comments) {
		if (((comments == null) && (_comments != null)) ||
				((comments != null) && (_comments == null)) ||
				((comments != null) && (_comments != null) &&
				!comments.equals(_comments))) {
			_comments = comments;
		}
	}

	public String getReplyComments() {
		return GetterUtil.getString(_replyComments);
	}

	public void setReplyComments(String replyComments) {
		if (((replyComments == null) && (_replyComments != null)) ||
				((replyComments != null) && (_replyComments == null)) ||
				((replyComments != null) && (_replyComments != null) &&
				!replyComments.equals(_replyComments))) {
			_replyComments = replyComments;
		}
	}

	public Date getReplyDate() {
		return _replyDate;
	}

	public void setReplyDate(Date replyDate) {
		if (((replyDate == null) && (_replyDate != null)) ||
				((replyDate != null) && (_replyDate == null)) ||
				((replyDate != null) && (_replyDate != null) &&
				!replyDate.equals(_replyDate))) {
			_replyDate = replyDate;
		}
	}

	public long getReplierUserId() {
		return _replierUserId;
	}

	public void setReplierUserId(long replierUserId) {
		if (replierUserId != _replierUserId) {
			_replierUserId = replierUserId;
		}
	}

	public int getStatusId() {
		return _statusId;
	}

	public void setStatusId(int statusId) {
		if (statusId != _statusId) {
			_statusId = statusId;
		}
	}

	public MembershipRequest toEscapedModel() {
		if (isEscapedModel()) {
			return (MembershipRequest)this;
		}
		else {
			MembershipRequest model = new MembershipRequestImpl();

			model.setEscapedModel(true);

			model.setMembershipRequestId(getMembershipRequestId());
			model.setCompanyId(getCompanyId());
			model.setUserId(getUserId());
			model.setCreateDate(getCreateDate());
			model.setGroupId(getGroupId());
			model.setComments(Html.escape(getComments()));
			model.setReplyComments(Html.escape(getReplyComments()));
			model.setReplyDate(getReplyDate());
			model.setReplierUserId(getReplierUserId());
			model.setStatusId(getStatusId());

			model = (MembershipRequest)Proxy.newProxyInstance(MembershipRequest.class.getClassLoader(),
					new Class[] { MembershipRequest.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		MembershipRequestImpl clone = new MembershipRequestImpl();

		clone.setMembershipRequestId(getMembershipRequestId());
		clone.setCompanyId(getCompanyId());
		clone.setUserId(getUserId());
		clone.setCreateDate(getCreateDate());
		clone.setGroupId(getGroupId());
		clone.setComments(getComments());
		clone.setReplyComments(getReplyComments());
		clone.setReplyDate(getReplyDate());
		clone.setReplierUserId(getReplierUserId());
		clone.setStatusId(getStatusId());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		MembershipRequestImpl membershipRequest = (MembershipRequestImpl)obj;

		int value = 0;

		value = DateUtil.compareTo(getCreateDate(),
				membershipRequest.getCreateDate());

		value = value * -1;

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		MembershipRequestImpl membershipRequest = null;

		try {
			membershipRequest = (MembershipRequestImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = membershipRequest.getPrimaryKey();

		if (getPrimaryKey() == pk) {
			return true;
		}
		else {
			return false;
		}
	}

	public int hashCode() {
		return (int)getPrimaryKey();
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