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

package com.liferay.portlet.journal.util;

import java.util.ArrayList;
import java.util.List;

/**
 * <a href="TemplateNode.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public class TemplateNode {

	public TemplateNode(String name, String data, String type) {
		_name = name;
		_data = data;
		_type = type;
		_options = new ArrayList();
		_children = new ArrayList();
	}

	public String getName() {
		return _name;
	}

	public String getData() {
		return _data;
	}

	public String getType() {
		return _type;
	}

	public void appendOption(String option) {
		_options.add(option);
	}

	public void appendOptions(List options) {
		_options.addAll(options);
	}

	public List getOptions() {
		return _options;
	}

	public void appendChild(TemplateNode child) {
		_children.add(child);
	}

	public void appendChildren(List children) {
		_children.addAll(children);
	}

	public List getChildren() {
		return _children;
	}

	private String _name;
	private String _data;
	private String _type;
	private List _options;
	private List _children;

}