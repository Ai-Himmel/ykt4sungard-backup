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

package com.liferay.portal.kernel.jbi;

import java.util.List;
import java.util.Map;

/**
 * <a href="WorkflowComponent.java.html"><b><i>View Source</i></b></a>
 *
 * @author Charles May
 *
 */
public interface WorkflowComponent {

	public String deploy(String xml) throws WorkflowComponentException;

	public List getCurrentTasks(long instanceId, long tokenId)
		throws WorkflowComponentException;

	public String getCurrentTasksXml(long instanceId, long tokenId)
		throws WorkflowComponentException;

	public Object getDefinition(long definitionId)
		throws WorkflowComponentException;

	public List getDefinitions(
			long definitionId, String name, int begin, int end)
		throws WorkflowComponentException;

	public String getDefinitionsXml(
			long definitionId, String name, int begin, int end)
		throws WorkflowComponentException;

	public int getDefinitionsCount(long definitionId, String name)
		throws WorkflowComponentException;

	public String getDefinitionsCountXml(long definitionId, String name)
		throws WorkflowComponentException;

	public String getDefinitionXml(long definitionId)
		throws WorkflowComponentException;

	public List getInstances(
			long definitionId, long instanceId, String definitionName,
			String definitionVersion, String startDateGT, String startDateLT,
			String endDateGT, String endDateLT, boolean hideEndedTasks,
			boolean retrieveUserInstances, boolean andOperator, int begin,
			int end)
		throws WorkflowComponentException;

	public int getInstancesCount(
			long definitionId, long instanceId, String definitionName,
			String definitionVersion, String startDateGT, String startDateLT,
			String endDateGT, String endDateLT, boolean hideEndedTasks,
			boolean retrieveUserInstances, boolean andOperator)
		throws WorkflowComponentException;

	public String getInstancesCountXml(
			long definitionId, long instanceId, String definitionName,
			String definitionVersion, String startDateGT, String startDateLT,
			String endDateGT, String endDateLT, boolean hideEndedTasks,
			boolean retrieveUserInstances, boolean andOperator)
		throws WorkflowComponentException;

	public String getInstancesXml(
			long definitionId, long instanceId, String definitionName,
			String definitionVersion, String startDateGT, String startDateLT,
			String endDateGT, String endDateLT, boolean hideEndedTasks,
			boolean retrieveUserInstances, boolean andOperator, int begin,
			int end)
		throws WorkflowComponentException;

	public List getTaskFormElements(long taskId)
		throws WorkflowComponentException;

	public String getTaskFormElementsXml(long taskId)
		throws WorkflowComponentException;

	public List getTaskTransitions(long taskId)
		throws WorkflowComponentException;

	public String getTaskTransitionsXml(long taskId)
		throws WorkflowComponentException;

	public List getUserTasks(
			long instanceId, String taskName, String definitionName,
			String assignedTo, String createDateGT, String createDateLT,
			String startDateGT, String startDateLT, String endDateGT,
			String endDateLT, boolean hideEndedTasks, boolean andOperator,
			int begin, int end)
		throws WorkflowComponentException;

	public int getUserTasksCount(
			long instanceId, String taskName, String definitionName,
			String assignedTo, String createDateGT, String createDateLT,
			String startDateGT, String startDateLT, String endDateGT,
			String endDateLT, boolean hideEndedTasks, boolean andOperator)
		throws WorkflowComponentException;

	public String getUserTasksCountXml(
			long instanceId, String taskName, String definitionName,
			String assignedTo, String createDateGT, String createDateLT,
			String startDateGT, String startDateLT, String endDateGT,
			String endDateLT, boolean hideEndedTasks, boolean andOperator)
		throws WorkflowComponentException;

	public String getUserTasksXml(
			long instanceId, String taskName, String definitionName,
			String assignedTo, String createDateGT, String createDateLT,
			String startDateGT, String startDateLT, String endDateGT,
			String endDateLT, boolean hideEndedTasks, boolean andOperator,
			int begin, int end)
		throws WorkflowComponentException;

	public void signalInstance(long instanceId)
		throws WorkflowComponentException;

	public void signalToken(long instanceId, long tokenId)
		throws WorkflowComponentException;

	public String startWorkflow(long definitionId)
		throws WorkflowComponentException;

	public Map updateTask(long taskId, String transition, Map parameterMap)
		throws WorkflowComponentException;

	public String updateTaskXml(
			long taskId, String transition, Map parameterMap)
		throws WorkflowComponentException;

}