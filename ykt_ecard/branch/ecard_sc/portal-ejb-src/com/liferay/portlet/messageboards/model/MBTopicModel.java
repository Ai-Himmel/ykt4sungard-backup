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

package com.liferay.portlet.messageboards.model;

import com.liferay.portal.model.BaseModel;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.Xss;

import java.util.Date;

/**
 * <a href="MBTopicModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.79 $
 *
 */
public class MBTopicModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portlet.messageboards.model.MBTopic"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portlet.messageboards.model.MBTopic"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBTopic"),
			XSS_ALLOW);
	public static boolean XSS_ALLOW_TOPICID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBTopic.topicId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_PORTLETID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBTopic.portletId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_GROUPID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBTopic.groupId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_COMPANYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBTopic.companyId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBTopic.userId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERNAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBTopic.userName"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_READROLES = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBTopic.readRoles"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_WRITEROLES = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBTopic.writeRoles"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_NAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBTopic.name"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_DESCRIPTION = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBTopic.description"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.messageboards.model.MBTopicModel"));

	public MBTopicModel() {
	}

	public MBTopicModel(String topicId) {
		_topicId = topicId;
		setNew(true);
	}

	public MBTopicModel(String topicId, String portletId, String groupId,
		String companyId, String userId, String userName, Date createDate,
		Date modifiedDate, String readRoles, String writeRoles, String name,
		String description, Date lastPostDate) {
		_topicId = topicId;
		_portletId = portletId;
		_groupId = groupId;
		_companyId = companyId;
		_userId = userId;
		_userName = userName;
		_createDate = createDate;
		_modifiedDate = modifiedDate;
		_readRoles = readRoles;
		_writeRoles = writeRoles;
		_name = name;
		_description = description;
		_lastPostDate = lastPostDate;
	}

	public String getPrimaryKey() {
		return _topicId;
	}

	public String getTopicId() {
		return _topicId;
	}

	public void setTopicId(String topicId) {
		if (((topicId == null) && (_topicId != null)) ||
				((topicId != null) && (_topicId == null)) ||
				((topicId != null) && (_topicId != null) &&
				!topicId.equals(_topicId))) {
			if (!XSS_ALLOW_TOPICID) {
				topicId = Xss.strip(topicId);
			}

			_topicId = topicId;
			setModified(true);
		}
	}

	public String getPortletId() {
		return _portletId;
	}

	public void setPortletId(String portletId) {
		if (((portletId == null) && (_portletId != null)) ||
				((portletId != null) && (_portletId == null)) ||
				((portletId != null) && (_portletId != null) &&
				!portletId.equals(_portletId))) {
			if (!XSS_ALLOW_PORTLETID) {
				portletId = Xss.strip(portletId);
			}

			_portletId = portletId;
			setModified(true);
		}
	}

	public String getGroupId() {
		return _groupId;
	}

	public void setGroupId(String groupId) {
		if (((groupId == null) && (_groupId != null)) ||
				((groupId != null) && (_groupId == null)) ||
				((groupId != null) && (_groupId != null) &&
				!groupId.equals(_groupId))) {
			if (!XSS_ALLOW_GROUPID) {
				groupId = Xss.strip(groupId);
			}

			_groupId = groupId;
			setModified(true);
		}
	}

	public String getCompanyId() {
		return _companyId;
	}

	public void setCompanyId(String companyId) {
		if (((companyId == null) && (_companyId != null)) ||
				((companyId != null) && (_companyId == null)) ||
				((companyId != null) && (_companyId != null) &&
				!companyId.equals(_companyId))) {
			if (!XSS_ALLOW_COMPANYID) {
				companyId = Xss.strip(companyId);
			}

			_companyId = companyId;
			setModified(true);
		}
	}

	public String getUserId() {
		return _userId;
	}

	public void setUserId(String userId) {
		if (((userId == null) && (_userId != null)) ||
				((userId != null) && (_userId == null)) ||
				((userId != null) && (_userId != null) &&
				!userId.equals(_userId))) {
			if (!XSS_ALLOW_USERID) {
				userId = Xss.strip(userId);
			}

			_userId = userId;
			setModified(true);
		}
	}

	public String getUserName() {
		return _userName;
	}

	public void setUserName(String userName) {
		if (((userName == null) && (_userName != null)) ||
				((userName != null) && (_userName == null)) ||
				((userName != null) && (_userName != null) &&
				!userName.equals(_userName))) {
			if (!XSS_ALLOW_USERNAME) {
				userName = Xss.strip(userName);
			}

			_userName = userName;
			setModified(true);
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
			setModified(true);
		}
	}

	public Date getModifiedDate() {
		return _modifiedDate;
	}

	public void setModifiedDate(Date modifiedDate) {
		if (((modifiedDate == null) && (_modifiedDate != null)) ||
				((modifiedDate != null) && (_modifiedDate == null)) ||
				((modifiedDate != null) && (_modifiedDate != null) &&
				!modifiedDate.equals(_modifiedDate))) {
			_modifiedDate = modifiedDate;
			setModified(true);
		}
	}

	public String getReadRoles() {
		return _readRoles;
	}

	public void setReadRoles(String readRoles) {
		if (((readRoles == null) && (_readRoles != null)) ||
				((readRoles != null) && (_readRoles == null)) ||
				((readRoles != null) && (_readRoles != null) &&
				!readRoles.equals(_readRoles))) {
			if (!XSS_ALLOW_READROLES) {
				readRoles = Xss.strip(readRoles);
			}

			_readRoles = readRoles;
			setModified(true);
		}
	}

	public String getWriteRoles() {
		return _writeRoles;
	}

	public void setWriteRoles(String writeRoles) {
		if (((writeRoles == null) && (_writeRoles != null)) ||
				((writeRoles != null) && (_writeRoles == null)) ||
				((writeRoles != null) && (_writeRoles != null) &&
				!writeRoles.equals(_writeRoles))) {
			if (!XSS_ALLOW_WRITEROLES) {
				writeRoles = Xss.strip(writeRoles);
			}

			_writeRoles = writeRoles;
			setModified(true);
		}
	}

	public String getName() {
		return _name;
	}

	public void setName(String name) {
		if (((name == null) && (_name != null)) ||
				((name != null) && (_name == null)) ||
				((name != null) && (_name != null) && !name.equals(_name))) {
			if (!XSS_ALLOW_NAME) {
				name = Xss.strip(name);
			}

			_name = name;
			setModified(true);
		}
	}

	public String getDescription() {
		return _description;
	}

	public void setDescription(String description) {
		if (((description == null) && (_description != null)) ||
				((description != null) && (_description == null)) ||
				((description != null) && (_description != null) &&
				!description.equals(_description))) {
			if (!XSS_ALLOW_DESCRIPTION) {
				description = Xss.strip(description);
			}

			_description = description;
			setModified(true);
		}
	}

	public Date getLastPostDate() {
		return _lastPostDate;
	}

	public void setLastPostDate(Date lastPostDate) {
		if (((lastPostDate == null) && (_lastPostDate != null)) ||
				((lastPostDate != null) && (_lastPostDate == null)) ||
				((lastPostDate != null) && (_lastPostDate != null) &&
				!lastPostDate.equals(_lastPostDate))) {
			_lastPostDate = lastPostDate;
			setModified(true);
		}
	}

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new MBTopic(getTopicId(), getPortletId(), getGroupId(),
			getCompanyId(), getUserId(), getUserName(), getCreateDate(),
			getModifiedDate(), getReadRoles(), getWriteRoles(), getName(),
			getDescription(), getLastPostDate());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		MBTopic mbTopic = (MBTopic)obj;
		int value = 0;
		value = getCreateDate().compareTo(mbTopic.getCreateDate());
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

		MBTopic mbTopic = null;

		try {
			mbTopic = (MBTopic)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		String pk = mbTopic.getPrimaryKey();

		if (getPrimaryKey().equals(pk)) {
			return true;
		}
		else {
			return false;
		}
	}

	public int hashCode() {
		return getPrimaryKey().hashCode();
	}

	private String _topicId;
	private String _portletId;
	private String _groupId;
	private String _companyId;
	private String _userId;
	private String _userName;
	private Date _createDate;
	private Date _modifiedDate;
	private String _readRoles;
	private String _writeRoles;
	private String _name;
	private String _description;
	private Date _lastPostDate;
}