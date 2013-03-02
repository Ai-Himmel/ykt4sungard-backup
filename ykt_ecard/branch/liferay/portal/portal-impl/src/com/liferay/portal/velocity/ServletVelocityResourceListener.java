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

import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.util.PortalUtil;

import java.io.ByteArrayInputStream;
import java.io.InputStream;

import javax.servlet.ServletContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.velocity.exception.ResourceNotFoundException;

/**
 * <a href="ServletVelocityResourceListener.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Alexander Chow
 *
 */
public class ServletVelocityResourceListener extends VelocityResourceListener {

	public InputStream getResourceStream(String source)
		throws ResourceNotFoundException {

		InputStream is = null;

		int pos = source.indexOf(SERVLET_SEPARATOR);

		if (pos != -1) {
			String ctxName = source.substring(0, pos);

			if (Validator.isNull(ctxName)) {
				ctxName = PortalUtil.getPathContext();
			}

			ServletContext ctx = VelocityContextPool.get(ctxName);

			if (ctx != null) {
				String name =
					source.substring(pos + SERVLET_SEPARATOR.length());

				if (_log.isDebugEnabled()) {
					_log.debug(
						name + " is associated with the servlet context " +
							ctxName + " " + ctx);
				}

				is = ctx.getResourceAsStream(name);

				if ((is == null) && (name.endsWith("/init_custom.vm"))) {
					if (_log.isWarnEnabled()) {
						_log.warn(
							"The template " + name + " should be created");
					}

					is = new ByteArrayInputStream(new byte[0]);
				}
			}
			else {
				_log.error(
					source + " is not valid because " + ctxName +
						" does not map to a servlet context");
			}
		}

		return is;
	}

	private static Log _log =
		LogFactory.getLog(ServletVelocityResourceListener.class);

}