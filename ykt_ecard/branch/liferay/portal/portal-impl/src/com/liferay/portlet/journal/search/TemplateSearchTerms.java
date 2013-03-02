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

import javax.portlet.RenderRequest;

/**
 * <a href="TemplateSearchTerms.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class TemplateSearchTerms extends TemplateDisplayTerms {

	public TemplateSearchTerms(RenderRequest req) {
		super(req);

		groupId = ParamUtil.getLong(
			req, GROUP_ID, PortalUtil.getPortletGroupId(req));
		templateId = DAOParamUtil.getLike(req, TEMPLATE_ID);
		structureId = DAOParamUtil.getString(req, STRUCTURE_ID);
		name = DAOParamUtil.getLike(req, NAME);
		description = DAOParamUtil.getLike(req, DESCRIPTION);
	}

	public void setStructureId(String structureId) {
		this.structureId = structureId;
	}

	public String getStructureIdComparator() {
		return structureIdComparator;
	}

	public void setStructureIdComparator(String structureIdComparator) {
		this.structureIdComparator = structureIdComparator;
	}

	protected String structureIdComparator;

}