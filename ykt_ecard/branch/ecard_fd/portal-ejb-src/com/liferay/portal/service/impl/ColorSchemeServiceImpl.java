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

package com.liferay.portal.service.impl;

import com.liferay.portal.NoSuchColorSchemeException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.ColorScheme;
import com.liferay.portal.model.Theme;
import com.liferay.portal.service.persistence.ColorSchemeUtil;
import com.liferay.portal.service.spring.ColorSchemeLocalServiceUtil;
import com.liferay.portal.service.spring.ColorSchemeService;
import com.liferay.portal.service.spring.ThemeServiceUtil;

import java.util.List;
import java.util.Map;

/**
 * <a href="ColorSchemeServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.182 $
 *
 */
public class ColorSchemeServiceImpl extends PrincipalBean
	implements ColorSchemeService {

	// Business methods

	public ColorScheme getColorScheme(String themeId, String colorSchemeId)
		throws SystemException {

		Theme theme = ThemeServiceUtil.getTheme(themeId);

		Map colorSchemesPool = theme.getColorSchemesMap();

		ColorScheme colorScheme = (ColorScheme)colorSchemesPool.get(
			colorSchemeId);

		if (colorScheme == null) {
			try {
				colorScheme = ColorSchemeUtil.findByPrimaryKey(colorSchemeId);
			}
			catch (NoSuchColorSchemeException nscse) {
			}
		}

		if (colorScheme == null) {
			List colorSchemes = theme.getColorSchemes();

			if (colorSchemes.size() > 0) {
				colorScheme = (ColorScheme)colorSchemes.get(0);
			}
		}

		if (colorScheme == null) {
			colorScheme = (ColorScheme)colorSchemesPool.get(
				ColorScheme.DEFAULT_COLOR_SCHEME_ID);
		}

		if (colorScheme == null) {
			colorScheme = ColorScheme.NULL_COLOR_SCHEME;
		}

		return colorScheme;
	}

	public ColorScheme updateColorScheme(String colorSchemeId, String settings)
		throws PortalException, SystemException {

		return ColorSchemeLocalServiceUtil.updateColorScheme(
			colorSchemeId, settings);
	}

}