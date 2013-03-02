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

package com.liferay.portlet.journal.model;

import com.liferay.portal.model.BaseModel;
import com.liferay.portal.util.PropsUtil;

import com.liferay.portlet.journal.service.persistence.JournalArticlePK;

import com.liferay.util.GetterUtil;
import com.liferay.util.Xss;

import java.util.Date;

/**
 * <a href="JournalArticleModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.83 $
 *
 */
public class JournalArticleModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portlet.journal.model.JournalArticle"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portlet.journal.model.JournalArticle"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.journal.model.JournalArticle"),
			XSS_ALLOW);
	public static boolean XSS_ALLOW_ARTICLEID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.journal.model.JournalArticle.articleId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_PORTLETID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.journal.model.JournalArticle.portletId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_GROUPID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.journal.model.JournalArticle.groupId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_COMPANYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.journal.model.JournalArticle.companyId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.journal.model.JournalArticle.userId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERNAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.journal.model.JournalArticle.userName"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_TITLE = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.journal.model.JournalArticle.title"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_CONTENT = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.journal.model.JournalArticle.content"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_TYPE = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.journal.model.JournalArticle.type"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_STRUCTUREID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.journal.model.JournalArticle.structureId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_TEMPLATEID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.journal.model.JournalArticle.templateId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_APPROVEDBYUSERID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.journal.model.JournalArticle.approvedByUserId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_APPROVEDBYUSERNAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.journal.model.JournalArticle.approvedByUserName"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.journal.model.JournalArticleModel"));

	public JournalArticleModel() {
	}

	public JournalArticleModel(JournalArticlePK pk) {
		_articleId = pk.articleId;
		_version = pk.version;
		setNew(true);
	}

	public JournalArticleModel(String articleId, double version,
		String portletId, String groupId, String companyId, String userId,
		String userName, Date createDate, Date modifiedDate, String title,
		String content, String type, String structureId, String templateId,
		Date displayDate, Date expirationDate, boolean approved,
		String approvedByUserId, String approvedByUserName) {
		_articleId = articleId;
		_version = version;
		_portletId = portletId;
		_groupId = groupId;
		_companyId = companyId;
		_userId = userId;
		_userName = userName;
		_createDate = createDate;
		_modifiedDate = modifiedDate;
		_title = title;
		_content = content;
		_type = type;
		_structureId = structureId;
		_templateId = templateId;
		_displayDate = displayDate;
		_expirationDate = expirationDate;
		_approved = approved;
		_approvedByUserId = approvedByUserId;
		_approvedByUserName = approvedByUserName;
	}

	public JournalArticlePK getPrimaryKey() {
		return new JournalArticlePK(_articleId, _version);
	}

	public String getArticleId() {
		return _articleId;
	}

	public void setArticleId(String articleId) {
		if (((articleId == null) && (_articleId != null)) ||
				((articleId != null) && (_articleId == null)) ||
				((articleId != null) && (_articleId != null) &&
				!articleId.equals(_articleId))) {
			if (!XSS_ALLOW_ARTICLEID) {
				articleId = Xss.strip(articleId);
			}

			_articleId = articleId;
			setModified(true);
		}
	}

	public double getVersion() {
		return _version;
	}

	public void setVersion(double version) {
		if (version != _version) {
			_version = version;
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

	public String getTitle() {
		return _title;
	}

	public void setTitle(String title) {
		if (((title == null) && (_title != null)) ||
				((title != null) && (_title == null)) ||
				((title != null) && (_title != null) && !title.equals(_title))) {
			if (!XSS_ALLOW_TITLE) {
				title = Xss.strip(title);
			}

			_title = title;
			setModified(true);
		}
	}

	public String getContent() {
		return _content;
	}

	public void setContent(String content) {
		if (((content == null) && (_content != null)) ||
				((content != null) && (_content == null)) ||
				((content != null) && (_content != null) &&
				!content.equals(_content))) {
			if (!XSS_ALLOW_CONTENT) {
				content = Xss.strip(content);
			}

			_content = content;
			setModified(true);
		}
	}

	public String getType() {
		return _type;
	}

	public void setType(String type) {
		if (((type == null) && (_type != null)) ||
				((type != null) && (_type == null)) ||
				((type != null) && (_type != null) && !type.equals(_type))) {
			if (!XSS_ALLOW_TYPE) {
				type = Xss.strip(type);
			}

			_type = type;
			setModified(true);
		}
	}

	public String getStructureId() {
		return _structureId;
	}

	public void setStructureId(String structureId) {
		if (((structureId == null) && (_structureId != null)) ||
				((structureId != null) && (_structureId == null)) ||
				((structureId != null) && (_structureId != null) &&
				!structureId.equals(_structureId))) {
			if (!XSS_ALLOW_STRUCTUREID) {
				structureId = Xss.strip(structureId);
			}

			_structureId = structureId;
			setModified(true);
		}
	}

	public String getTemplateId() {
		return _templateId;
	}

	public void setTemplateId(String templateId) {
		if (((templateId == null) && (_templateId != null)) ||
				((templateId != null) && (_templateId == null)) ||
				((templateId != null) && (_templateId != null) &&
				!templateId.equals(_templateId))) {
			if (!XSS_ALLOW_TEMPLATEID) {
				templateId = Xss.strip(templateId);
			}

			_templateId = templateId;
			setModified(true);
		}
	}

	public Date getDisplayDate() {
		return _displayDate;
	}

	public void setDisplayDate(Date displayDate) {
		if (((displayDate == null) && (_displayDate != null)) ||
				((displayDate != null) && (_displayDate == null)) ||
				((displayDate != null) && (_displayDate != null) &&
				!displayDate.equals(_displayDate))) {
			_displayDate = displayDate;
			setModified(true);
		}
	}

	public Date getExpirationDate() {
		return _expirationDate;
	}

	public void setExpirationDate(Date expirationDate) {
		if (((expirationDate == null) && (_expirationDate != null)) ||
				((expirationDate != null) && (_expirationDate == null)) ||
				((expirationDate != null) && (_expirationDate != null) &&
				!expirationDate.equals(_expirationDate))) {
			_expirationDate = expirationDate;
			setModified(true);
		}
	}

	public boolean getApproved() {
		return _approved;
	}

	public boolean isApproved() {
		return _approved;
	}

	public void setApproved(boolean approved) {
		if (approved != _approved) {
			_approved = approved;
			setModified(true);
		}
	}

	public String getApprovedByUserId() {
		return _approvedByUserId;
	}

	public void setApprovedByUserId(String approvedByUserId) {
		if (((approvedByUserId == null) && (_approvedByUserId != null)) ||
				((approvedByUserId != null) && (_approvedByUserId == null)) ||
				((approvedByUserId != null) && (_approvedByUserId != null) &&
				!approvedByUserId.equals(_approvedByUserId))) {
			if (!XSS_ALLOW_APPROVEDBYUSERID) {
				approvedByUserId = Xss.strip(approvedByUserId);
			}

			_approvedByUserId = approvedByUserId;
			setModified(true);
		}
	}

	public String getApprovedByUserName() {
		return _approvedByUserName;
	}

	public void setApprovedByUserName(String approvedByUserName) {
		if (((approvedByUserName == null) && (_approvedByUserName != null)) ||
				((approvedByUserName != null) && (_approvedByUserName == null)) ||
				((approvedByUserName != null) && (_approvedByUserName != null) &&
				!approvedByUserName.equals(_approvedByUserName))) {
			if (!XSS_ALLOW_APPROVEDBYUSERNAME) {
				approvedByUserName = Xss.strip(approvedByUserName);
			}

			_approvedByUserName = approvedByUserName;
			setModified(true);
		}
	}

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new JournalArticle(getArticleId(), getVersion(), getPortletId(),
			getGroupId(), getCompanyId(), getUserId(), getUserName(),
			getCreateDate(), getModifiedDate(), getTitle(), getContent(),
			getType(), getStructureId(), getTemplateId(), getDisplayDate(),
			getExpirationDate(), getApproved(), getApprovedByUserId(),
			getApprovedByUserName());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		JournalArticle journalArticle = (JournalArticle)obj;
		int value = 0;
		value = getArticleId().compareTo(journalArticle.getArticleId());

		if (value != 0) {
			return value;
		}

		if (getVersion() < journalArticle.getVersion()) {
			value = -1;
		}
		else if (getVersion() > journalArticle.getVersion()) {
			value = 1;
		}
		else {
			value = 0;
		}

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

		JournalArticle journalArticle = null;

		try {
			journalArticle = (JournalArticle)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		JournalArticlePK pk = journalArticle.getPrimaryKey();

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

	private String _articleId;
	private double _version;
	private String _portletId;
	private String _groupId;
	private String _companyId;
	private String _userId;
	private String _userName;
	private Date _createDate;
	private Date _modifiedDate;
	private String _title;
	private String _content;
	private String _type;
	private String _structureId;
	private String _templateId;
	private Date _displayDate;
	private Date _expirationDate;
	private boolean _approved;
	private String _approvedByUserId;
	private String _approvedByUserName;
}