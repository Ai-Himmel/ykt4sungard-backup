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

package com.liferay.portal.model;

import java.io.IOException;
import java.io.Serializable;

import java.util.List;

import javax.servlet.ServletContext;

/**
 * <a href="LayoutTemplate.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public interface LayoutTemplate extends Comparable, Plugin, Serializable {

	public String getLayoutTemplateId();

	public boolean getStandard();

	public boolean isStandard();

	public void setStandard(boolean standard);

	public String getName();

	public void setName(String name);

	public String getTemplatePath();

	public void setTemplatePath(String templatePath);

	public String getWapTemplatePath();

	public void setWapTemplatePath(String wapWapTemplatePath);

	public String getThumbnailPath();

	public void setThumbnailPath(String thumbnailPath);

	public String getContent();

	public void setContent(String content);

	public boolean hasSetContent();

	public String getUncachedContent() throws IOException;

	public String getWapContent();

	public void setWapContent(String wapContent);

	public boolean hasSetWapContent();

	public String getUncachedWapContent() throws IOException;

	public List getColumns();

	public void setColumns(List columns);

	public void setServletContext(ServletContext ctx);

	public String getServletContextName();

	public void setServletContextName(String servletContextName);

	public boolean getWARFile();

	public boolean isWARFile();

	public String getContextPath();

}