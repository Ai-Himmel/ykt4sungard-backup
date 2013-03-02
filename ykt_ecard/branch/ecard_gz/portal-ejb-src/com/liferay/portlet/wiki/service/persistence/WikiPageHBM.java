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

package com.liferay.portlet.wiki.service.persistence;

import java.util.Date;

/**
 * <a href="WikiPageHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class WikiPageHBM {
	protected WikiPageHBM() {
	}

	protected WikiPageHBM(WikiPagePK pk) {
		_nodeId = pk.nodeId;
		_title = pk.title;
		_version = pk.version;
	}

	protected WikiPageHBM(String nodeId, String title, double version,
		String companyId, String userId, String userName, Date createDate,
		String content, String format, boolean head) {
		_nodeId = nodeId;
		_title = title;
		_version = version;
		_companyId = companyId;
		_userId = userId;
		_userName = userName;
		_createDate = createDate;
		_content = content;
		_format = format;
		_head = head;
	}

	public WikiPagePK getPrimaryKey() {
		return new WikiPagePK(_nodeId, _title, _version);
	}

	protected void setPrimaryKey(WikiPagePK pk) {
		_nodeId = pk.nodeId;
		_title = pk.title;
		_version = pk.version;
	}

	protected String getNodeId() {
		return _nodeId;
	}

	protected void setNodeId(String nodeId) {
		_nodeId = nodeId;
	}

	protected String getTitle() {
		return _title;
	}

	protected void setTitle(String title) {
		_title = title;
	}

	protected double getVersion() {
		return _version;
	}

	protected void setVersion(double version) {
		_version = version;
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

	protected String getContent() {
		return _content;
	}

	protected void setContent(String content) {
		_content = content;
	}

	protected String getFormat() {
		return _format;
	}

	protected void setFormat(String format) {
		_format = format;
	}

	protected boolean getHead() {
		return _head;
	}

	protected void setHead(boolean head) {
		_head = head;
	}

	private String _nodeId;
	private String _title;
	private double _version;
	private String _companyId;
	private String _userId;
	private String _userName;
	private Date _createDate;
	private String _content;
	private String _format;
	private boolean _head;
}