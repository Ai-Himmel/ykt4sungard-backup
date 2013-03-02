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

package com.liferay.portlet.journal.service.persistence;

import java.util.Date;

/**
 * <a href="JournalArticleHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class JournalArticleHBM {
	protected JournalArticleHBM() {
	}

	protected JournalArticleHBM(JournalArticlePK pk) {
		_articleId = pk.articleId;
		_version = pk.version;
	}

	protected JournalArticleHBM(String articleId, double version,
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

	protected void setPrimaryKey(JournalArticlePK pk) {
		_articleId = pk.articleId;
		_version = pk.version;
	}

	protected String getArticleId() {
		return _articleId;
	}

	protected void setArticleId(String articleId) {
		_articleId = articleId;
	}

	protected double getVersion() {
		return _version;
	}

	protected void setVersion(double version) {
		_version = version;
	}

	protected String getPortletId() {
		return _portletId;
	}

	protected void setPortletId(String portletId) {
		_portletId = portletId;
	}

	protected String getGroupId() {
		return _groupId;
	}

	protected void setGroupId(String groupId) {
		_groupId = groupId;
	}

	protected String getCompanyId() {
		return _companyId;
	}

	protected void setCompanyId(String companyId) {
		_companyId = companyId;
	}

	protected String getUserId() {
		return _userId;
	}

	protected void setUserId(String userId) {
		_userId = userId;
	}

	protected String getUserName() {
		return _userName;
	}

	protected void setUserName(String userName) {
		_userName = userName;
	}

	protected Date getCreateDate() {
		return _createDate;
	}

	protected void setCreateDate(Date createDate) {
		_createDate = createDate;
	}

	protected Date getModifiedDate() {
		return _modifiedDate;
	}

	protected void setModifiedDate(Date modifiedDate) {
		_modifiedDate = modifiedDate;
	}

	protected String getTitle() {
		return _title;
	}

	protected void setTitle(String title) {
		_title = title;
	}

	protected String getContent() {
		return _content;
	}

	protected void setContent(String content) {
		_content = content;
	}

	protected String getType() {
		return _type;
	}

	protected void setType(String type) {
		_type = type;
	}

	protected String getStructureId() {
		return _structureId;
	}

	protected void setStructureId(String structureId) {
		_structureId = structureId;
	}

	protected String getTemplateId() {
		return _templateId;
	}

	protected void setTemplateId(String templateId) {
		_templateId = templateId;
	}

	protected Date getDisplayDate() {
		return _displayDate;
	}

	protected void setDisplayDate(Date displayDate) {
		_displayDate = displayDate;
	}

	protected Date getExpirationDate() {
		return _expirationDate;
	}

	protected void setExpirationDate(Date expirationDate) {
		_expirationDate = expirationDate;
	}

	protected boolean getApproved() {
		return _approved;
	}

	protected void setApproved(boolean approved) {
		_approved = approved;
	}

	protected String getApprovedByUserId() {
		return _approvedByUserId;
	}

	protected void setApprovedByUserId(String approvedByUserId) {
		_approvedByUserId = approvedByUserId;
	}

	protected String getApprovedByUserName() {
		return _approvedByUserName;
	}

	protected void setApprovedByUserName(String approvedByUserName) {
		_approvedByUserName = approvedByUserName;
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