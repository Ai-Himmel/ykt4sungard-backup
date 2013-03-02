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

package com.liferay.portlet.biblejournal.service.persistence;

import java.util.Date;
import java.util.Set;

/**
 * <a href="BJEntryHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BJEntryHBM {
	protected BJEntryHBM() {
	}

	protected BJEntryHBM(String entryId) {
		_entryId = entryId;
	}

	protected BJEntryHBM(String entryId, String companyId, String userId,
		Date createDate, Date modifiedDate, String name, String content,
		String versesInput) {
		_entryId = entryId;
		_companyId = companyId;
		_userId = userId;
		_createDate = createDate;
		_modifiedDate = modifiedDate;
		_name = name;
		_content = content;
		_versesInput = versesInput;
	}

	public String getPrimaryKey() {
		return _entryId;
	}

	protected void setPrimaryKey(String pk) {
		_entryId = pk;
	}

	protected String getEntryId() {
		return _entryId;
	}

	protected void setEntryId(String entryId) {
		_entryId = entryId;
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

	protected String getContent() {
		return _content;
	}

	protected void setContent(String content) {
		_content = content;
	}

	protected String getVersesInput() {
		return _versesInput;
	}

	protected void setVersesInput(String versesInput) {
		_versesInput = versesInput;
	}

	protected Set getVerses() {
		return _verses;
	}

	protected void setVerses(Set verses) {
		_verses = verses;
	}

	protected Set getTopics() {
		return _topics;
	}

	protected void setTopics(Set topics) {
		_topics = topics;
	}

	private String _entryId;
	private String _companyId;
	private String _userId;
	private Date _createDate;
	private Date _modifiedDate;
	private String _name;
	private String _content;
	private String _versesInput;
	private Set _verses;
	private Set _topics;
}