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

package com.liferay.portal.service.persistence;

/**
 * <a href="LayoutHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class LayoutHBM {
	protected LayoutHBM() {
	}

	protected LayoutHBM(LayoutPK pk) {
		_layoutId = pk.layoutId;
		_userId = pk.userId;
	}

	protected LayoutHBM(String layoutId, String userId, String companyId,
		String parentLayoutId, String name, String type, String typeSettings,
		String friendlyURL, int priority) {
		_layoutId = layoutId;
		_userId = userId;
		_companyId = companyId;
		_parentLayoutId = parentLayoutId;
		_name = name;
		_type = type;
		_typeSettings = typeSettings;
		_friendlyURL = friendlyURL;
		_priority = priority;
	}

	public LayoutPK getPrimaryKey() {
		return new LayoutPK(_layoutId, _userId);
	}

	protected void setPrimaryKey(LayoutPK pk) {
		_layoutId = pk.layoutId;
		_userId = pk.userId;
	}

	protected String getLayoutId() {
		return _layoutId;
	}

	protected void setLayoutId(String layoutId) {
		_layoutId = layoutId;
	}

	protected String getUserId() {
		return _userId;
	}

	protected void setUserId(String userId) {
		_userId = userId;
	}

	protected String getCompanyId() {
		return _companyId;
	}

	protected void setCompanyId(String companyId) {
		_companyId = companyId;
	}

	protected String getParentLayoutId() {
		return _parentLayoutId;
	}

	protected void setParentLayoutId(String parentLayoutId) {
		_parentLayoutId = parentLayoutId;
	}

	protected String getName() {
		return _name;
	}

	protected void setName(String name) {
		_name = name;
	}

	protected String getType() {
		return _type;
	}

	protected void setType(String type) {
		_type = type;
	}

	protected String getTypeSettings() {
		return _typeSettings;
	}

	protected void setTypeSettings(String typeSettings) {
		_typeSettings = typeSettings;
	}

	protected String getFriendlyURL() {
		return _friendlyURL;
	}

	protected void setFriendlyURL(String friendlyURL) {
		_friendlyURL = friendlyURL;
	}

	protected int getPriority() {
		return _priority;
	}

	protected void setPriority(int priority) {
		_priority = priority;
	}

	private String _layoutId;
	private String _userId;
	private String _companyId;
	private String _parentLayoutId;
	private String _name;
	private String _type;
	private String _typeSettings;
	private String _friendlyURL;
	private int _priority;
}