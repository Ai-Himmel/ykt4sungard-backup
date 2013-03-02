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

package com.liferay.portlet.project.model;

import java.util.Date;

/**
 * <a href="ProjTask.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Myunghun Kim
 * @version $Revision: 1.9 $
 *
 */
public class ProjTask extends ProjTaskModel {

	public static final String[] RELATIONSHIPS = {
		"associated", "assigned", "created"
	};

	public static final int RELATIONSHIP_ANY = -1;

	public static final int RELATIONSHIP_ASSOCIATED = 0;

	public static final int RELATIONSHIP_ASSIGNED = 1;

	public static final int RELATIONSHIP_CREATED = 2;

	public static final String[] STATUSES = {
		"new", "assigned", "in-progress", "on-hold", "completed"
	};

	public static final int STATUS_ANY = -1;

	public static final int STATUS_NEW = 0;

	public static final int STATUS_ASSIGNED = 1;

	public static final int STATUS_IN_PROGRESS = 2;

	public static final int STATUS_ON_HOLD = 3;

	public static final int STATUS_COMPLETED = 4;

	public ProjTask() {
		super();
	}

	public ProjTask(String taskId) {
		super(taskId);
	}

	public ProjTask(String taskId, String companyId, String userId,
					String userName, Date createDate, Date modifiedDate,
					String projectId, String name, String description,
					String comments, int estimatedDuration,
					Date estimatedEndDate, int actualDuration,
					Date actualEndDate, int status) {

		super(taskId, companyId, userId, userName, createDate, modifiedDate,
			  projectId, name, description, comments, estimatedDuration,
			  estimatedEndDate, actualDuration, actualEndDate, status);
	}

}