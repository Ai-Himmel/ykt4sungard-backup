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

package com.liferay.portal.velocity;

import com.liferay.portal.theme.ThemeLoader;
import com.liferay.portal.theme.ThemeLoaderFactory;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.velocity.exception.ResourceNotFoundException;

/**
 * <a href="ThemeLoaderVelocityResourceListener.java.html"><b><i>View Source</i>
 * </b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ThemeLoaderVelocityResourceListener
	extends VelocityResourceListener {

	public InputStream getResourceStream(String source)
		throws ResourceNotFoundException {

		InputStream is = null;

		try {
			int pos = source.indexOf(THEME_LOADER_SEPARATOR);

			if (pos != -1) {
				String ctxName = source.substring(0, pos);

				ThemeLoader themeLoader = ThemeLoaderFactory.getThemeLoader(
					ctxName);

				if (themeLoader != null) {
					String name =
						source.substring(pos + THEME_LOADER_SEPARATOR.length());

					String themesPath = themeLoader.getThemesPath();

					if (name.startsWith(themesPath)) {
						name = name.substring(
							themesPath.length(), name.length());
					}

					if (_log.isDebugEnabled()) {
						_log.debug(
							name + " is associated with the theme loader " +
								ctxName + " " + themeLoader);
					}

					is = new FileInputStream(
						themeLoader.getFileStorage().getPath() + name);
				}
				else {
					_log.error(
						source + " is not valid because " + ctxName +
							" does not map to a theme loader");
				}
			}
		}
		catch (FileNotFoundException fnfe) {
			throw new ResourceNotFoundException(source);
		}

		return is;
	}

	private static Log _log =
		LogFactory.getLog(ThemeLoaderVelocityResourceListener.class);

}