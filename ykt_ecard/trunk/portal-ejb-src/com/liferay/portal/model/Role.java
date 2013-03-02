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

package com.liferay.portal.model;

import com.liferay.portal.util.RoleNames;

/**
 * <a href="Role.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.15 $
 *
 */
public class Role extends RoleModel {

	public static final String ADMINISTRATOR = RoleNames.ADMINISTRATOR;

	public static final String BOOKMARKS_ADMIN = RoleNames.BOOKMARKS_ADMIN;

	public static final String CALENDAR_ADMIN = RoleNames.CALENDAR_ADMIN;

	public static final String DOCUMENT_LIBRARY_ADMIN =
		RoleNames.DOCUMENT_LIBRARY_ADMIN;

	public static final String GUEST = RoleNames.GUEST;

	public static final String JOURNAL_ADMIN = RoleNames.JOURNAL_ADMIN;

	public static final String JOURNAL_DESIGNER = RoleNames.JOURNAL_DESIGNER;

	public static final String JOURNAL_EDITOR = RoleNames.JOURNAL_EDITOR;

	public static final String JOURNAL_WRITER = RoleNames.JOURNAL_WRITER;

	public static final String MESSAGE_BOARDS_ADMIN =
		RoleNames.MESSAGE_BOARDS_ADMIN;

	public static final String POLLS_ADMIN = RoleNames.POLLS_ADMIN;

	public static final String POWER_USER = RoleNames.POWER_USER;

	public static final String PROJECT_ADMIN = RoleNames.PROJECT_ADMIN;

	public static final String SHOPPING_ADMIN = RoleNames.SHOPPING_ADMIN;

	public static final String USER = RoleNames.USER;

	public static final String WIKI_ADMIN = RoleNames.WIKI_ADMIN;

	public static final String[] SYSTEM_ROLES = RoleNames.SYSTEM_ROLES;

	public Role() {
		super();
	}

	public Role(String roleId) {
		super(roleId);
	}

	public Role(String roleId, String companyId, String name) {
		super(roleId, companyId, name);
	}

}