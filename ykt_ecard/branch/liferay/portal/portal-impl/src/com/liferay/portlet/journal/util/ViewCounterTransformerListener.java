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

package com.liferay.portlet.journal.util;

import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;

import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ViewCounterTransformerListener.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Raymond Augé
 *
 */
public class ViewCounterTransformerListener extends TransformerListener {

	public String onXml(String s) {
		if (_log.isDebugEnabled()) {
			_log.debug("onXml");
		}

		return s;
	}

	public String onScript(String s) {
		if (_log.isDebugEnabled()) {
			_log.debug("onScript");
		}

		return s;
	}

	public String onOutput(String s) {
		if (_log.isDebugEnabled()) {
			_log.debug("onOutput");
		}

		return replaceViewCounterToken(s);
	}

	/**
	 * Replace the counter token with the increment call.
	 *
	 * @param		s the given string
	 * @return		the processed string
	 */
	protected String replaceViewCounterToken(String s) {
		Map tokens = getTokens();

		String articleResourcePK = (String)tokens.get("article_resource_pk");

		String counterToken = StringPool.AT + "view_counter" + StringPool.AT;

		StringMaker sm = new StringMaker();

		sm.append("<script type=\"text/javascript\">");
		sm.append("Liferay.Service.Tags.TagsAsset.incrementViewCounter");
		sm.append("({className:'");
		sm.append("com.liferay.portlet.journal.model.JournalArticle', ");
		sm.append("classPK:");
		sm.append(articleResourcePK);
		sm.append("});");
		sm.append("</script>");

		s = StringUtil.replace(s, counterToken, sm.toString());

		return s;
	}

	private static Log _log =
		LogFactory.getLog(ViewCounterTransformerListener.class);

}