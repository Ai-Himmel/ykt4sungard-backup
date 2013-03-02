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
import com.liferay.portal.service.persistence.ColorSchemeUtil;
import com.liferay.portal.service.spring.ColorSchemeLocalService;

/**
 * <a href="ColorSchemeLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ColorSchemeLocalServiceImpl implements ColorSchemeLocalService {

	// Business methods

	public void deleteColorScheme(String colorSchemeId) throws SystemException {
		ImageLocalUtil.remove(colorSchemeId + ".tab_join_left_multi_on.gif");
		ImageLocalUtil.remove(colorSchemeId + ".tab_join_left_on.gif");
		ImageLocalUtil.remove(colorSchemeId + ".tab_join_right_multi_off.gif");
		ImageLocalUtil.remove(colorSchemeId + ".tab_join_right_multi_on.gif");
		ImageLocalUtil.remove(colorSchemeId + ".tab_join_right_off.gif");
		ImageLocalUtil.remove(colorSchemeId + ".tab_join_right_on.gif");
		ImageLocalUtil.remove(colorSchemeId + ".tab_left_multi_off.gif");
		ImageLocalUtil.remove(colorSchemeId + ".tab_left_multi_on.gif");
		ImageLocalUtil.remove(colorSchemeId + ".tab_left_off.gif");
		ImageLocalUtil.remove(colorSchemeId + ".tab_left_on.gif");
		ImageLocalUtil.remove(colorSchemeId + ".tab_middle_multi_off.gif");
		ImageLocalUtil.remove(colorSchemeId + ".tab_middle_off.gif");
		ImageLocalUtil.remove(colorSchemeId + ".tab_middle_on.gif");
		ImageLocalUtil.remove(colorSchemeId + ".tab_right_multi_off.gif");
		ImageLocalUtil.remove(colorSchemeId + ".tab_right_multi_on.gif");
		ImageLocalUtil.remove(colorSchemeId + ".tab_right_off.gif");
		ImageLocalUtil.remove(colorSchemeId + ".tab_right_on.gif");
		ImageLocalUtil.remove(colorSchemeId + ".tab_right_single_off.gif");
		ImageLocalUtil.remove(colorSchemeId + ".tab_right_single_on.gif");

		ImageLocalUtil.remove(colorSchemeId + ".alpha_dotted_x.gif");
		ImageLocalUtil.remove(colorSchemeId + ".alpha_dotted_y.gif");
		ImageLocalUtil.remove(colorSchemeId + ".alpha_edge_ul.gif");
		ImageLocalUtil.remove(colorSchemeId + ".alpha_edge_ur.gif");
		ImageLocalUtil.remove(colorSchemeId + ".alpha_edge_bl.gif");
		ImageLocalUtil.remove(colorSchemeId + ".alpha_edge_br.gif");

		ImageLocalUtil.remove(colorSchemeId + ".beta_dotted_x.gif");
		ImageLocalUtil.remove(colorSchemeId + ".beta_dotted_y.gif");
		ImageLocalUtil.remove(colorSchemeId + ".beta_edge_ul.gif");
		ImageLocalUtil.remove(colorSchemeId + ".beta_edge_ur.gif");
		ImageLocalUtil.remove(colorSchemeId + ".beta_edge_bl.gif");
		ImageLocalUtil.remove(colorSchemeId + ".beta_edge_br.gif");

		ImageLocalUtil.remove(colorSchemeId + ".gamma_dotted_x.gif");
		ImageLocalUtil.remove(colorSchemeId + ".gamma_dotted_y.gif");
		ImageLocalUtil.remove(colorSchemeId + ".gamma_edge_ul.gif");
		ImageLocalUtil.remove(colorSchemeId + ".gamma_edge_ur.gif");
		ImageLocalUtil.remove(colorSchemeId + ".gamma_edge_bl.gif");
		ImageLocalUtil.remove(colorSchemeId + ".gamma_edge_br.gif");

		ImageLocalUtil.remove(colorSchemeId + ".bg_dotted_x.gif");
		ImageLocalUtil.remove(colorSchemeId + ".bg_dotted_y.gif");
		ImageLocalUtil.remove(colorSchemeId + ".bg_edge_ul.gif");
		ImageLocalUtil.remove(colorSchemeId + ".bg_edge_ur.gif");
		ImageLocalUtil.remove(colorSchemeId + ".bg_edge_bl.gif");
		ImageLocalUtil.remove(colorSchemeId + ".bg_edge_br.gif");

		try {
			ColorSchemeUtil.remove(colorSchemeId);
		}
		catch (NoSuchColorSchemeException nsse) {
		}
	}

	public ColorScheme updateColorScheme(String colorSchemeId, String settings)
		throws PortalException, SystemException {

		deleteColorScheme(colorSchemeId);

		ColorScheme colorScheme = ColorSchemeUtil.create(colorSchemeId);

		/*alphaBackground = _formatColor(alphaBackground);
		alphaForeground = _formatColor(alphaForeground);
		betaBackground = _formatColor(betaBackground);
		betaForeground = _formatColor(betaForeground);
		gammaBackground = _formatColor(gammaBackground);
		gammaForeground = _formatColor(gammaForeground);
		bgBackground = _formatColor(bgBackground);
		bgForeground = _formatColor(bgForeground);
		href = _formatColor(href);
		negAlert = _formatColor(negAlert);
		posAlert = _formatColor(posAlert);*/

		colorScheme.setSettings(settings);

		ColorSchemeUtil.update(colorScheme);

		return colorScheme;
	}

	// Private methods

	private String _formatColor(String hex) {
		if (!hex.startsWith("#")) {
			hex = "#" + hex;
		}

		return hex.toUpperCase();
	}

}