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

package com.liferay.portlet.journalcontent;

import com.liferay.portal.kernel.portlet.PortletLayoutListener;
import com.liferay.portal.kernel.portlet.PortletLayoutListenerException;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Layout;
import com.liferay.portal.service.LayoutLocalServiceUtil;
import com.liferay.portlet.PortletPreferencesFactoryUtil;
import com.liferay.portlet.journal.NoSuchContentSearchException;
import com.liferay.portlet.journal.service.JournalContentSearchLocalServiceUtil;

import javax.portlet.PortletPreferences;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="JournalContentPortletLayoutListener.java.html"><b><i>View Source</i>
 * </b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class JournalContentPortletLayoutListener
	implements PortletLayoutListener {

	public void onAddToLayout(String portletId, long plid)
		throws PortletLayoutListenerException {

		if (_log.isDebugEnabled()) {
			_log.debug("Add " + portletId + " to layout " + plid);
		}
	}

	public void onMoveInLayout(String portletId, long plid)
		throws PortletLayoutListenerException {

		if (_log.isDebugEnabled()) {
			_log.debug("Move " + portletId + " from in " + plid);
		}
	}

	public void onRemoveFromLayout(String portletId, long plid)
		throws PortletLayoutListenerException {

		if (_log.isDebugEnabled()) {
			_log.debug("Remove " + portletId + " from layout " + plid);
		}

		try {
			deleteContentSearch(portletId, plid);
		}
		catch (Exception e) {
			throw new PortletLayoutListenerException(e);
		}
	}

	protected void deleteContentSearch(String portletId, long plid)
		throws Exception {

		Layout layout = LayoutLocalServiceUtil.getLayout(plid);

		PortletPreferences prefs =
			PortletPreferencesFactoryUtil.getPortletSetup(
				layout, portletId, true, true, StringPool.BLANK);

		String articleId = (String)prefs.getValue("article-id", null);

		if (Validator.isNull(articleId)) {
			return;
		}

		try {
			JournalContentSearchLocalServiceUtil.deleteArticleContentSearch(
				layout.getGroupId(), layout.isPrivateLayout(),
				layout.getLayoutId(), portletId, articleId);
		}
		catch (NoSuchContentSearchException nscse) {
		}
	}

	private static Log _log =
		LogFactory.getLog(JournalContentPortletLayoutListener.class);

}