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

package com.liferay.util.bridges.jsf.common;

import com.liferay.portal.kernel.language.LanguageUtil;
import com.liferay.portal.kernel.util.StringPool;

import java.util.ArrayList;
import java.util.Locale;

import javax.faces.context.FacesContext;
import javax.faces.model.SelectItem;

/**
 * <a href="SelectItemList.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * This class provides a convenient way of building lists of JSF SelectItem
 * objects, and convenience method for operating against them.
 * </p>
 *
 * @author Neil Griffin
 *
 */
public class SelectItemList extends ArrayList {

	public void prependEmptySelectItem(FacesContext facesContext) {
		Locale locale = facesContext.getExternalContext().getRequestLocale();

		Object value = StringPool.BLANK;
		String label = LanguageUtil.get(locale, "select");

		add(0, new SelectItem(value, label));
	}

}