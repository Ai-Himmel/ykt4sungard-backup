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

package com.liferay.portlet.workflow.model;

import java.io.Serializable;

import java.util.List;

/**
 * <a href="WorkflowToken.java.html"><b><i>View Source</i></b></a>
 *
 * @author Charles May
 *
 */
public class WorkflowToken implements Serializable {

	public WorkflowToken() {
	}

	public long getTokenId() {
		return _tokenId;
	}

	public void setTokenId(long tokenId) {
		_tokenId = tokenId;
	}

	public String getName() {
		return _name;
	}

	public void setName(String name) {
		_name = name;
	}

	public String getType() {
		return _type;
	}

	public void setType(String type) {
		_type = type;
	}

	public List getTasks() {
		return _tasks;
	}

	public void setTasks(List tasks) {
		_tasks = tasks;
	}

	public List getChildren() {
		return _children;
	}

	public void setChildren(List children) {
		_children = children;
	}

	private long _tokenId;
	private String _name;
	private String _type;
	private List _tasks;
	private List _children;

}