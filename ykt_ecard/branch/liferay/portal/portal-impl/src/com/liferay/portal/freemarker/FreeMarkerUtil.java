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

package com.liferay.portal.freemarker;

import freemarker.cache.ClassTemplateLoader;

import freemarker.template.Configuration;
import freemarker.template.DefaultObjectWrapper;
import freemarker.template.Template;

import java.io.StringWriter;
import java.io.Writer;

/**
 * <a href="FreeMarkerUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Tariq Dweik
 * @author Brian Wing Shun Chan
 *
 */
public class FreeMarkerUtil {

	public static String process(String name, Object context)
		throws Exception {

		StringWriter writer = new StringWriter();

		process(name, context, writer);

		return writer.toString();
	}

	public static void process(String name, Object context, Writer writer)
		throws Exception {

		Template template = _getConfiguration().getTemplate(name);

		template.process(context, writer);
	}

	private static Configuration _getConfiguration() {
		if (_configuration == null) {
			_configuration = new Configuration();

			_configuration.setObjectWrapper(new DefaultObjectWrapper());
			_configuration.setTemplateLoader(
				new ClassTemplateLoader(FreeMarkerUtil.class, "/"));
		}

		return _configuration;
	}

	private static Configuration _configuration;

}