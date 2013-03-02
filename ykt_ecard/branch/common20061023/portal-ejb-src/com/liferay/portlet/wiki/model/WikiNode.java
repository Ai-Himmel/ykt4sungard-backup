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

package com.liferay.portlet.wiki.model;

import com.liferay.portal.model.Group;
import com.liferay.portal.util.PortletKeys;

import java.util.Date;

/**
 * <a href="WikiNode.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.7 $
 *
 */
public class WikiNode extends WikiNodeModel {

	public WikiNode() {
		super();
	}

	public WikiNode(String nodeId) {
		super(nodeId);
	}

	public WikiNode(String nodeId, String companyId, String userId,
					String userName, Date createDate, Date modifiedDate,
					String readRoles, String writeRoles, String name,
					String description, boolean sharing, Date lastPostDate) {

		super(nodeId, companyId, userId, userName, createDate, modifiedDate,
			  readRoles, writeRoles, name, description, sharing, lastPostDate);
	}

	public String getPortletId() {
		return PortletKeys.WIKI;
	}

	public String getGroupId() {
		return Group.DEFAULT_PARENT_GROUP_ID;
	}

}