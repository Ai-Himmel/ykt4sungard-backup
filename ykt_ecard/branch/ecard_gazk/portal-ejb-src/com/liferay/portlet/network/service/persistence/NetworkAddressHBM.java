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

package com.liferay.portlet.network.service.persistence;

import java.util.Date;

/**
 * <a href="NetworkAddressHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class NetworkAddressHBM {
	protected NetworkAddressHBM() {
	}

	protected NetworkAddressHBM(String addressId) {
		_addressId = addressId;
	}

	protected NetworkAddressHBM(String addressId, String userId,
		Date createDate, Date modifiedDate, String name, String url,
		String comments, String content, int status, Date lastUpdated,
		String notifyBy, long interval, boolean active) {
		_addressId = addressId;
		_userId = userId;
		_createDate = createDate;
		_modifiedDate = modifiedDate;
		_name = name;
		_url = url;
		_comments = comments;
		_content = content;
		_status = status;
		_lastUpdated = lastUpdated;
		_notifyBy = notifyBy;
		_interval = interval;
		_active = active;
	}

	public String getPrimaryKey() {
		return _addressId;
	}

	protected void setPrimaryKey(String pk) {
		_addressId = pk;
	}

	protected String getAddressId() {
		return _addressId;
	}

	protected void setAddressId(String addressId) {
		_addressId = addressId;
	}

	protected String getUserId() {
		return _userId;
	}

	protected void setUserId(String userId) {
		_userId = userId;
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

	protected String getName() {
		return _name;
	}

	protected void setName(String name) {
		_name = name;
	}

	protected String getUrl() {
		return _url;
	}

	protected void setUrl(String url) {
		_url = url;
	}

	protected String getComments() {
		return _comments;
	}

	protected void setComments(String comments) {
		_comments = comments;
	}

	protected String getContent() {
		return _content;
	}

	protected void setContent(String content) {
		_content = content;
	}

	protected int getStatus() {
		return _status;
	}

	protected void setStatus(int status) {
		_status = status;
	}

	protected Date getLastUpdated() {
		return _lastUpdated;
	}

	protected void setLastUpdated(Date lastUpdated) {
		_lastUpdated = lastUpdated;
	}

	protected String getNotifyBy() {
		return _notifyBy;
	}

	protected void setNotifyBy(String notifyBy) {
		_notifyBy = notifyBy;
	}

	protected long getInterval() {
		return _interval;
	}

	protected void setInterval(long interval) {
		_interval = interval;
	}

	protected boolean getActive() {
		return _active;
	}

	protected void setActive(boolean active) {
		_active = active;
	}

	private String _addressId;
	private String _userId;
	private Date _createDate;
	private Date _modifiedDate;
	private String _name;
	private String _url;
	private String _comments;
	private String _content;
	private int _status;
	private Date _lastUpdated;
	private String _notifyBy;
	private long _interval;
	private boolean _active;
}