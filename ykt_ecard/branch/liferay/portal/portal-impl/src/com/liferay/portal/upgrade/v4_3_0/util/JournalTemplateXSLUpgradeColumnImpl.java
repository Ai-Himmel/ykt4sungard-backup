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

package com.liferay.portal.upgrade.v4_3_0.util;

import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.upgrade.util.BaseUpgradeColumnImpl;
import com.liferay.portal.upgrade.util.UpgradeColumn;

/**
 * <a href="JournalTemplateXSLUpgradeColumnImpl.java.html"><b><i>View Source</i>
 * </b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class JournalTemplateXSLUpgradeColumnImpl extends BaseUpgradeColumnImpl {

	public JournalTemplateXSLUpgradeColumnImpl(UpgradeColumn templateIdColumn) {
		super("xsl");

		_templateIdColumn = templateIdColumn;
	}

	public Object getNewValue(Object oldValue) throws Exception {
		String xsl = (String)oldValue;

		return formatXSL(xsl);
	}

	protected String formatXSL(String xsl) throws Exception {
		/*if (xsl.indexOf("\\n") != -1) {
			xsl = StringUtil.replace(
				xsl, new String[] {"\\n", "\\r"}, new String[] {"\n", "\r"});
		}*/

		String templateId = (String)_templateIdColumn.getOldValue();

		if (templateId.equals("BASIC-BANNER")) {

			// 4.3 defaults to XHTML 1.0 Transitional and requires stricter CSS

			xsl = StringUtil.replace(
				xsl,
				"background-repeat: no-repeat; width: 520; height: 175;",
				"background-repeat: no-repeat; width: 520px; height: 175px;");
		}

		return xsl;
	}

	private UpgradeColumn _templateIdColumn;

}