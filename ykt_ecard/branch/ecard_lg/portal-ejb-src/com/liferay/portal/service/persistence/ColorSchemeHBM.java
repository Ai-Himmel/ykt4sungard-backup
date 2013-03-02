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
 * <a href="ColorSchemeHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ColorSchemeHBM {
	protected ColorSchemeHBM() {
	}

	protected ColorSchemeHBM(String colorSchemeId) {
		_colorSchemeId = colorSchemeId;
	}

	protected ColorSchemeHBM(String colorSchemeId, String settings) {
		_colorSchemeId = colorSchemeId;
		_settings = settings;
	}

	public String getPrimaryKey() {
		return _colorSchemeId;
	}

	protected void setPrimaryKey(String pk) {
		_colorSchemeId = pk;
	}

	protected String getColorSchemeId() {
		return _colorSchemeId;
	}

	protected void setColorSchemeId(String colorSchemeId) {
		_colorSchemeId = colorSchemeId;
	}

	protected String getSettings() {
		return _settings;
	}

	protected void setSettings(String settings) {
		_settings = settings;
	}

	private String _colorSchemeId;
	private String _settings;
}