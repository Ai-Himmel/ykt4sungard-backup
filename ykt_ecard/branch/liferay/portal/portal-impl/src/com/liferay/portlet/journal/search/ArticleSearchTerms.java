/**
 * Copyright (c) 2000-2008 Liferay, Inc. All rights reserved.
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

package com.liferay.portlet.journal.search;

import com.liferay.portal.kernel.dao.DAOParamUtil;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.util.PortalUtil;

import java.util.Date;

import javax.portlet.RenderRequest;

/**
 * <a href="ArticleSearchTerms.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ArticleSearchTerms extends ArticleDisplayTerms {

	public ArticleSearchTerms(RenderRequest req) {
		super(req);

		groupId = ParamUtil.getLong(
			req, GROUP_ID, PortalUtil.getPortletGroupId(req));
		articleId = DAOParamUtil.getLike(req, ARTICLE_ID);
		version = ParamUtil.getDouble(req, VERSION);
		title = DAOParamUtil.getLike(req, TITLE);
		description = DAOParamUtil.getLike(req, DESCRIPTION);
		content = DAOParamUtil.getLike(req, CONTENT);
		type = DAOParamUtil.getString(req, TYPE);
		structureId = DAOParamUtil.getString(req, STRUCTURE_ID);
		templateId = DAOParamUtil.getString(req, TEMPLATE_ID);
		status = ParamUtil.getString(req, STATUS);
	}

	public void setGroupId(long groupId) {
		this.groupId = groupId;
	}

	public Double getVersionObj() {
		if (version == 0) {
			return null;
		}
		else {
			return new Double(version);
		}
	}

	public void setType(String type) {
		this.type = type;
	}

	public void setStatus(String status) {
		this.status = status;
	}

	public Boolean getApprovedObj() {
		if (status.equals("approved")) {
			return Boolean.TRUE;
		}
		else if (status.equals("not-approved")) {
			return Boolean.FALSE;
		}
		else if (status.equals("expired")) {
			return Boolean.FALSE;
		}
		else if (status.equals("review")) {
			return null;
		}
		else {
			return null;
		}
	}

	public Boolean getExpiredObj() {
		if (status.equals("approved")) {
			return Boolean.FALSE;
		}
		else if (status.equals("not-approved")) {
			return Boolean.FALSE;
		}
		else if (status.equals("expired")) {
			return Boolean.TRUE;
		}
		else if (status.equals("review")) {
			return Boolean.FALSE;
		}
		else {
			return null;
		}
	}

	public Date getReviewDate() {
		if (status.equals("review")) {
			return new Date();
		}
		else {
			return null;
		}
	}

}