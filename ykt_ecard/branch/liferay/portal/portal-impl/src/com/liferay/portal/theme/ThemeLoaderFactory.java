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

package com.liferay.portal.theme;

import com.liferay.portal.velocity.VelocityContextPool;
import com.liferay.util.CollectionFactory;

import java.util.Iterator;
import java.util.Map;

import javax.servlet.ServletContext;

/**
 * <a href="ThemeLoaderFactory.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ThemeLoaderFactory {

	public static void init(
		String servletContextName, ServletContext ctx, String[] xmls) {

		VelocityContextPool.put(servletContextName, ctx);

		ThemeLoader themeLoader = new ThemeLoader(
			servletContextName, ctx, xmls);

		_themeLoaders.put(servletContextName, themeLoader);
	}

	public static boolean destroy(String servletContextName) {
		ThemeLoader themeLoader =
			(ThemeLoader)_themeLoaders.remove(servletContextName);

		if (themeLoader == null) {
			return false;
		}
		else {
			VelocityContextPool.remove(servletContextName);

			themeLoader.destroy();

			return true;
		}
	}

	public static ThemeLoader getDefaultThemeLoader() {
		ThemeLoader themeLoader = null;

		Iterator itr = _themeLoaders.entrySet().iterator();

		if (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			themeLoader = (ThemeLoader)entry.getValue();
		}

		return themeLoader;
	}

	public static ThemeLoader getThemeLoader(String servletContextName) {
		return (ThemeLoader)_themeLoaders.get(servletContextName);
	}

	public static void loadThemes() {
		Iterator itr = _themeLoaders.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			ThemeLoader themeLoader = (ThemeLoader)entry.getValue();

			themeLoader.loadThemes();
		}
	}

	private static Map _themeLoaders = CollectionFactory.getHashMap();

}