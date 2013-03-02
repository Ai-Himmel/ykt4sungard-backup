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
 * <a href="JournalTemplateHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class JournalTemplateHBM {
	protected JournalTemplateHBM() {
	}

	protected JournalTemplateHBM(String templateId) {
		_templateId = templateId;
	}

	protected JournalTemplateHBM(String templateId, String portletId,
		String groupId, String companyId, String userId, String userName,
		Date createDate, Date modifiedDate, String structureId, String name,
		String description, String xsl, boolean smallImage, String smallImageURL) {
		_templateId = templateId;
		_portletId = portletId;
		_groupId = groupId;
		_companyId = companyId;
		_userId = userId;
		_userName = userName;
		_createDate = createDate;
		_modifiedDate = modifiedDate;
		_structureId = structureId;
		_name = name;
		_description = description;
		_xsl = xsl;
		_smallImage = smallImage;
		_smallImageURL = smallImageURL;
	}

	public String getPrimaryKey() {
		return _templateId;
	}

	protected void setPrimaryKey(String pk) {
		_templateId = pk;
	}

	protected String getTemplateId() {
		return _templateId;
	}

	protected void setTemplateId(String templateId) {
		_templateId = templateId;
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

	protected String getStructureId() {
		return _structureId;
	}

	protected void setStructureId(String structureId) {
		_structureId = structureId;
	}

	protected String getName() {
		return _name;
	}

	protected void setName(String name) {
		_name = name;
	}

	protected String getDescription() {
		return _description;
	}

	protected void setDescription(String description) {
		_description = description;
	}

	protected String getXsl() {
		return _xsl;
	}

	protected void setXsl(String xsl) {
		_xsl = xsl;
	}

	protected boolean getSmallImage() {
		return _smallImage;
	}

	protected void setSmallImage(boolean smallImage) {
		_smallImage = smallImage;
	}

	protected String getSmallImageURL() {
		return _smallImageURL;
	}

	protected void setSmallImageURL(String smallImageURL) {
		_smallImageURL = smallImageURL;
	}

	private String _templateId;
	private String _portletId;
	private String _groupId;
	private String _companyId;
	private String _userId;
	private String _userName;
	private Date _createDate;
	private Date _modifiedDate;
	private String _structureId;
	private String _name;
	private String _description;
	private String _xsl;
	private boolean _smallImage;
	private String _smallImageURL;
}