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

package com.liferay.portal.model;

import com.liferay.portal.kernel.events.Action;
import com.liferay.portal.kernel.events.ActionException;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.service.LayoutLocalServiceUtil;
import com.liferay.portlet.journal.NoSuchContentSearchException;
import com.liferay.portlet.journal.service.JournalContentSearchLocalServiceUtil;

import java.util.Properties;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * <a href="LayoutTypeArticleConfigurationDeleteAction.java.html"><b><i>View
 * Source</i></b></a>
 *
 * @author Raymond Augé
 *
 */
public class LayoutTypeArticleConfigurationDeleteAction extends Action {

	public void run(HttpServletRequest req, HttpServletResponse res)
		throws ActionException {

		try {
			long groupId = ParamUtil.getLong(req, "groupId");
			boolean privateLayout = ParamUtil.getBoolean(req, "privateLayout");
			long layoutId = ParamUtil.getLong(req, "layoutId");

			Layout layout = LayoutLocalServiceUtil.getLayout(
				groupId, privateLayout, layoutId);

			Properties typeSettingsProperties =
				layout.getTypeSettingsProperties();

			String articleId = typeSettingsProperties.getProperty("article-id");

			if (Validator.isNull(articleId)) {
				return;
			}

			try {
				JournalContentSearchLocalServiceUtil.deleteArticleContentSearch(
					layout.getGroupId(), layout.isPrivateLayout(),
					layout.getLayoutId(), StringPool.BLANK, articleId);
			}
			catch (NoSuchContentSearchException nscse) {
			}
		}
		catch (Exception e) {
			throw new ActionException(e);
		}
	}

}