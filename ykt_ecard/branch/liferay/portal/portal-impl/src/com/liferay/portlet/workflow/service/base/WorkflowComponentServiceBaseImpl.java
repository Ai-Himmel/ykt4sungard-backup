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

package com.liferay.portlet.workflow.service.base;

import com.liferay.portal.service.impl.PrincipalBean;

import com.liferay.portlet.workflow.service.WorkflowComponentService;
import com.liferay.portlet.workflow.service.WorkflowDefinitionService;
import com.liferay.portlet.workflow.service.WorkflowDefinitionServiceFactory;
import com.liferay.portlet.workflow.service.WorkflowInstanceService;
import com.liferay.portlet.workflow.service.WorkflowInstanceServiceFactory;
import com.liferay.portlet.workflow.service.WorkflowTaskService;
import com.liferay.portlet.workflow.service.WorkflowTaskServiceFactory;

import org.springframework.beans.factory.InitializingBean;

/**
 * <a href="WorkflowComponentServiceBaseImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public abstract class WorkflowComponentServiceBaseImpl extends PrincipalBean
	implements WorkflowComponentService, InitializingBean {
	public WorkflowDefinitionService getWorkflowDefinitionService() {
		return workflowDefinitionService;
	}

	public void setWorkflowDefinitionService(
		WorkflowDefinitionService workflowDefinitionService) {
		this.workflowDefinitionService = workflowDefinitionService;
	}

	public WorkflowInstanceService getWorkflowInstanceService() {
		return workflowInstanceService;
	}

	public void setWorkflowInstanceService(
		WorkflowInstanceService workflowInstanceService) {
		this.workflowInstanceService = workflowInstanceService;
	}

	public WorkflowTaskService getWorkflowTaskService() {
		return workflowTaskService;
	}

	public void setWorkflowTaskService(WorkflowTaskService workflowTaskService) {
		this.workflowTaskService = workflowTaskService;
	}

	public void afterPropertiesSet() {
		if (workflowDefinitionService == null) {
			workflowDefinitionService = WorkflowDefinitionServiceFactory.getImpl();
		}

		if (workflowInstanceService == null) {
			workflowInstanceService = WorkflowInstanceServiceFactory.getImpl();
		}

		if (workflowTaskService == null) {
			workflowTaskService = WorkflowTaskServiceFactory.getImpl();
		}
	}

	protected WorkflowDefinitionService workflowDefinitionService;
	protected WorkflowInstanceService workflowInstanceService;
	protected WorkflowTaskService workflowTaskService;
}