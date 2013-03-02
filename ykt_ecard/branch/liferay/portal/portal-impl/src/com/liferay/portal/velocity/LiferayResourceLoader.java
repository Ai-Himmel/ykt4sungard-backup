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

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.util.PropsUtil;

import java.io.InputStream;

import org.apache.commons.collections.ExtendedProperties;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.velocity.exception.ResourceNotFoundException;
import org.apache.velocity.runtime.resource.Resource;
import org.apache.velocity.runtime.resource.loader.ResourceLoader;

/**
 * <a href="LiferayResourceLoader.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class LiferayResourceLoader extends ResourceLoader {

	private static VelocityResourceListener[] _listeners =
		new VelocityResourceListener[0];

	public static void setListeners(String[] listeners) {
		_listeners = new VelocityResourceListener[listeners.length];

		for (int i = 0; i < listeners.length; i++) {
			try {
				_listeners[i] = (VelocityResourceListener)Class.forName(
					listeners[i]).newInstance();
			}
			catch (Exception ex) {
				_log.error(ex);

				_listeners[i] = null;
			}
		}
	}

	public void init(ExtendedProperties props) {
		boolean cachingOn = GetterUtil.getBoolean(PropsUtil.get(
			PropsUtil.VELOCITY_ENGINE_RESOURCE_MANAGER_CACHE_ENABLED));
		int modificationCheckInterval = GetterUtil.getInteger(PropsUtil.get(
			PropsUtil.
				VELOCITY_ENGINE_RESOURCE_MANAGER_MODIFICATION_CHECK_INTERVAL));

		setCachingOn(cachingOn);
		setModificationCheckInterval(modificationCheckInterval);
	}

	public InputStream getResourceStream(String source)
		throws ResourceNotFoundException {

		if (_log.isDebugEnabled()) {
			_log.debug("Get resource for " + source);
		}

		InputStream is = null;

		for (int i = 0; (is == null) && (i < _listeners.length); i++) {
			if (_listeners[i] != null) {
				if (is == null) {
					is = _listeners[i].getResourceStream(source);
				}
			}
		}

		if (is == null) {
			_log.error("Failed to get " + source);

			throw new ResourceNotFoundException(source);
		}

		if (_log.isDebugEnabled()) {
			_log.debug("Successfully got " + source);
		}

		return is;
	}

	public long getLastModified(Resource resource) {
		if (_log.isDebugEnabled()) {
			_log.debug("Get last modified for " + resource.getName());
		}

		return 0;
	}

	public boolean isSourceModified(Resource resource) {
		if (_log.isDebugEnabled()) {
			_log.debug("Check modified status for " + resource.getName());
		}

		return false;
	}

	private static Log _log = LogFactory.getLog(LiferayResourceLoader.class);

}