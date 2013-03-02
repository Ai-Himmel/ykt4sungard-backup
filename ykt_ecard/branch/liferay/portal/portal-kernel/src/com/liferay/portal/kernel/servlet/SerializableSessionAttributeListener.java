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

package com.liferay.portal.kernel.servlet;

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;

import java.io.Serializable;

import javax.servlet.http.HttpSessionAttributeListener;
import javax.servlet.http.HttpSessionBindingEvent;

/**
 * <a href="SerializableSessionAttributeListener.java.html"><b><i>View Source
 * </i></b></a>
 *
 * @author Bruno Farache
 *
 */

public class SerializableSessionAttributeListener
	implements HttpSessionAttributeListener {

	public void attributeAdded(HttpSessionBindingEvent event) {
		Object obj = event.getValue();

		if (!(obj instanceof Serializable)){
			_log.error(
				obj.getClass().getName() +
					" is not serializable and will prevent this session from " +
						"being replicated");
		}
	}

	public void attributeRemoved(HttpSessionBindingEvent event) {
	}

	public void attributeReplaced(HttpSessionBindingEvent event) {
		attributeAdded(event);
	}

	private static Log _log =
		LogFactoryUtil.getLog(SerializableSessionAttributeListener.class);

}