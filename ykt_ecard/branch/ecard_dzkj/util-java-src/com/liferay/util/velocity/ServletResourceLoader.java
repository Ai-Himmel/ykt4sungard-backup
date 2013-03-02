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

package com.liferay.util.velocity;

import java.io.InputStream;

import javax.servlet.ServletContext;

import org.apache.commons.collections.ExtendedProperties;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.velocity.exception.ResourceNotFoundException;
import org.apache.velocity.runtime.resource.Resource;
import org.apache.velocity.runtime.resource.loader.FileResourceLoader;

/**
 * <a href="ServletResourceLoader.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.6 $
 *
 */
public class ServletResourceLoader extends FileResourceLoader {

	public static final String CONTEXT_SEPARATOR = "_CONTEXT_";

	public void init(ExtendedProperties props) {
	}

	public InputStream getResourceStream(String source)
		throws ResourceNotFoundException {

		_log.debug("Get " + source);

		ServletContext ctx = null;

		int pos = source.indexOf(CONTEXT_SEPARATOR);

		if (pos != -1) {
			String ctxName = source.substring(0, pos);

			ctx = VelocityContextPool.get(ctxName);

			if (ctx != null) {
				source = source.substring(
					pos + CONTEXT_SEPARATOR.length(), source.length());

				_log.debug(
					source + " is associated with the servlet context " + ctx);
			}
		}

		InputStream is = null;

		if (ctx != null) {
			is = ctx.getResourceAsStream(source);
		}

		if ((is == null) && (source.equals("VM_global_library.vm"))) {
			_log.warn(
				"Getting VM_global_library.vm from default the class loader");

			is = getClass().getClassLoader().getResourceAsStream(source);
		}

		if (is == null) {
			throw new ResourceNotFoundException(source);
		}

		return is;
	}

	public boolean isSourceModified(Resource resource) {
		return false;
	}

	public long getLastModified(Resource resource) {
		return 0;
	}

	private static final Log _log =
		LogFactory.getLog(ServletResourceLoader.class);

	private ServletContext _ctx;

}