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

package com.liferay.util.servlet.filters;

import java.util.Collections;
import java.util.Enumeration;
import java.util.LinkedHashMap;
import java.util.Map;

import javax.servlet.FilterConfig;
import javax.servlet.ServletContext;

/**
 * <a href="DynamicFilterConfig.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Bruno Farache
 *
 */
public class DynamicFilterConfig implements FilterConfig {

	public DynamicFilterConfig(FilterConfig config) {
		Enumeration enu = config.getInitParameterNames();

        while (enu.hasMoreElements()) {
        	String name = (String)enu.nextElement();

            addInitParameter(name, config.getInitParameter(name));
        }
	}

	public DynamicFilterConfig(String filterName, ServletContext ctx) {
		_filterName = filterName;
		_ctx = ctx;
	}

	public String getFilterName() {
		return _filterName;
	}

	public ServletContext getServletContext() {
		return _ctx;
	}

	public void addInitParameter(String name, String value) {
		_parameters.put(name, value);
	}

	public String getInitParameter(String name) {
		return (String)_parameters.get(name);
	}

	public Enumeration getInitParameterNames() {
		return Collections.enumeration(_parameters.keySet());
	}

	private String _filterName;
	private ServletContext _ctx;
	private Map _parameters = new LinkedHashMap();

}