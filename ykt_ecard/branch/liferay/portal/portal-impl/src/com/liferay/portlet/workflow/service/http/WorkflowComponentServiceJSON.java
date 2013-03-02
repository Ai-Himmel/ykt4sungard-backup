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

package com.liferay.portlet.workflow.service.http;

import com.liferay.portlet.workflow.service.WorkflowComponentServiceUtil;

/**
 * <a href="WorkflowComponentServiceJSON.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides a JSON utility for the
 * <code>com.liferay.portlet.workflow.service.WorkflowComponentServiceUtil</code>
 * service utility. The static methods of this class calls the same methods of
 * the service utility. However, the signatures are different because it is
 * difficult for JSON to support certain types.
 * </p>
 *
 * <p>
 * ServiceBuilder follows certain rules in translating the methods. For example,
 * if the method in the service utility returns a <code>java.util.List</code>,
 * that is translated to a <code>org.json.JSONArray</code>. If the method in the
 * service utility returns a <code>com.liferay.portlet.workflow.model.WorkflowComponent</code>,
 * that is translated to a <code>org.json.JSONObject</code>. Methods that JSON
 * cannot safely use are skipped. The logic for the translation is encapsulated
 * in <code>com.liferay.portlet.workflow.service.http.WorkflowComponentJSONSerializer</code>.
 * </p>
 *
 * <p>
 * This allows you to call the the backend services directly from JavaScript.
 * See <code>portal-web/docroot/html/portlet/tags_admin/unpacked.js</code> for a
 * reference of how that portlet uses the generated JavaScript in
 * <code>portal-web/docroot/html/js/service.js</code> to call the backend
 * services directly from JavaScript.
 * </p>
 *
 * <p>
 * The JSON utility is only generated for remote services.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.workflow.service.WorkflowComponentServiceUtil
 * @see com.liferay.portlet.workflow.service.http.WorkflowComponentJSONSerializer
 *
 */
public class WorkflowComponentServiceJSON {
	public static java.util.List getCurrentTasks(long instanceId, long tokenId)
		throws java.rmi.RemoteException, 
			com.liferay.portal.kernel.jbi.WorkflowComponentException {
		java.util.List returnValue = WorkflowComponentServiceUtil.getCurrentTasks(instanceId,
				tokenId);

		return returnValue;
	}

	public static java.lang.String getCurrentTasksXml(long instanceId,
		long tokenId)
		throws java.rmi.RemoteException, 
			com.liferay.portal.kernel.jbi.WorkflowComponentException {
		java.lang.String returnValue = WorkflowComponentServiceUtil.getCurrentTasksXml(instanceId,
				tokenId);

		return returnValue;
	}

	public static java.lang.String deploy(java.lang.String xml)
		throws java.rmi.RemoteException, 
			com.liferay.portal.kernel.jbi.WorkflowComponentException {
		java.lang.String returnValue = WorkflowComponentServiceUtil.deploy(xml);

		return returnValue;
	}

	public static java.lang.Object getDefinition(long definitionId)
		throws java.rmi.RemoteException, 
			com.liferay.portal.kernel.jbi.WorkflowComponentException {
		java.lang.Object returnValue = WorkflowComponentServiceUtil.getDefinition(definitionId);

		return returnValue;
	}

	public static java.util.List getDefinitions(long definitionId,
		java.lang.String name, int begin, int end)
		throws java.rmi.RemoteException, 
			com.liferay.portal.kernel.jbi.WorkflowComponentException {
		java.util.List returnValue = WorkflowComponentServiceUtil.getDefinitions(definitionId,
				name, begin, end);

		return returnValue;
	}

	public static java.lang.String getDefinitionsXml(long definitionId,
		java.lang.String name, int begin, int end)
		throws java.rmi.RemoteException, 
			com.liferay.portal.kernel.jbi.WorkflowComponentException {
		java.lang.String returnValue = WorkflowComponentServiceUtil.getDefinitionsXml(definitionId,
				name, begin, end);

		return returnValue;
	}

	public static int getDefinitionsCount(long definitionId,
		java.lang.String name)
		throws java.rmi.RemoteException, 
			com.liferay.portal.kernel.jbi.WorkflowComponentException {
		int returnValue = WorkflowComponentServiceUtil.getDefinitionsCount(definitionId,
				name);

		return returnValue;
	}

	public static java.lang.String getDefinitionsCountXml(long definitionId,
		java.lang.String name)
		throws java.rmi.RemoteException, 
			com.liferay.portal.kernel.jbi.WorkflowComponentException {
		java.lang.String returnValue = WorkflowComponentServiceUtil.getDefinitionsCountXml(definitionId,
				name);

		return returnValue;
	}

	public static java.lang.String getDefinitionXml(long definitionId)
		throws java.rmi.RemoteException, 
			com.liferay.portal.kernel.jbi.WorkflowComponentException {
		java.lang.String returnValue = WorkflowComponentServiceUtil.getDefinitionXml(definitionId);

		return returnValue;
	}

	public static java.util.List getInstances(long definitionId,
		long instanceId, java.lang.String definitionName,
		java.lang.String definitionVersion, java.lang.String startDateGT,
		java.lang.String startDateLT, java.lang.String endDateGT,
		java.lang.String endDateLT, boolean hideEndedTasks,
		boolean retrieveUserInstances, boolean andOperator, int begin, int end)
		throws java.rmi.RemoteException, 
			com.liferay.portal.kernel.jbi.WorkflowComponentException {
		java.util.List returnValue = WorkflowComponentServiceUtil.getInstances(definitionId,
				instanceId, definitionName, definitionVersion, startDateGT,
				startDateLT, endDateGT, endDateLT, hideEndedTasks,
				retrieveUserInstances, andOperator, begin, end);

		return returnValue;
	}

	public static int getInstancesCount(long definitionId, long instanceId,
		java.lang.String definitionName, java.lang.String definitionVersion,
		java.lang.String startDateGT, java.lang.String startDateLT,
		java.lang.String endDateGT, java.lang.String endDateLT,
		boolean hideEndedTasks, boolean retrieveUserInstances,
		boolean andOperator)
		throws java.rmi.RemoteException, 
			com.liferay.portal.kernel.jbi.WorkflowComponentException {
		int returnValue = WorkflowComponentServiceUtil.getInstancesCount(definitionId,
				instanceId, definitionName, definitionVersion, startDateGT,
				startDateLT, endDateGT, endDateLT, hideEndedTasks,
				retrieveUserInstances, andOperator);

		return returnValue;
	}

	public static java.lang.String getInstancesCountXml(long definitionId,
		long instanceId, java.lang.String definitionName,
		java.lang.String definitionVersion, java.lang.String startDateGT,
		java.lang.String startDateLT, java.lang.String endDateGT,
		java.lang.String endDateLT, boolean hideEndedTasks,
		boolean retrieveUserInstances, boolean andOperator)
		throws java.rmi.RemoteException, 
			com.liferay.portal.kernel.jbi.WorkflowComponentException {
		java.lang.String returnValue = WorkflowComponentServiceUtil.getInstancesCountXml(definitionId,
				instanceId, definitionName, definitionVersion, startDateGT,
				startDateLT, endDateGT, endDateLT, hideEndedTasks,
				retrieveUserInstances, andOperator);

		return returnValue;
	}

	public static java.lang.String getInstancesXml(long definitionId,
		long instanceId, java.lang.String definitionName,
		java.lang.String definitionVersion, java.lang.String startDateGT,
		java.lang.String startDateLT, java.lang.String endDateGT,
		java.lang.String endDateLT, boolean hideEndedTasks,
		boolean retrieveUserInstances, boolean andOperator, int begin, int end)
		throws java.rmi.RemoteException, 
			com.liferay.portal.kernel.jbi.WorkflowComponentException {
		java.lang.String returnValue = WorkflowComponentServiceUtil.getInstancesXml(definitionId,
				instanceId, definitionName, definitionVersion, startDateGT,
				startDateLT, endDateGT, endDateLT, hideEndedTasks,
				retrieveUserInstances, andOperator, begin, end);

		return returnValue;
	}

	public static com.liferay.portlet.workflow.model.WorkflowTask getTask(
		long taskId)
		throws java.rmi.RemoteException, 
			com.liferay.portal.kernel.jbi.WorkflowComponentException {
		com.liferay.portlet.workflow.model.WorkflowTask returnValue = WorkflowComponentServiceUtil.getTask(taskId);

		return returnValue;
	}

	public static java.lang.String getTaskXml(long taskId)
		throws java.rmi.RemoteException, 
			com.liferay.portal.kernel.jbi.WorkflowComponentException {
		java.lang.String returnValue = WorkflowComponentServiceUtil.getTaskXml(taskId);

		return returnValue;
	}

	public static java.util.List getTaskFormElements(long taskId)
		throws java.rmi.RemoteException, 
			com.liferay.portal.kernel.jbi.WorkflowComponentException {
		java.util.List returnValue = WorkflowComponentServiceUtil.getTaskFormElements(taskId);

		return returnValue;
	}

	public static java.lang.String getTaskFormElementsXml(long taskId)
		throws java.rmi.RemoteException, 
			com.liferay.portal.kernel.jbi.WorkflowComponentException {
		java.lang.String returnValue = WorkflowComponentServiceUtil.getTaskFormElementsXml(taskId);

		return returnValue;
	}

	public static java.util.List getTaskTransitions(long taskId)
		throws java.rmi.RemoteException, 
			com.liferay.portal.kernel.jbi.WorkflowComponentException {
		java.util.List returnValue = WorkflowComponentServiceUtil.getTaskTransitions(taskId);

		return returnValue;
	}

	public static java.lang.String getTaskTransitionsXml(long taskId)
		throws java.rmi.RemoteException, 
			com.liferay.portal.kernel.jbi.WorkflowComponentException {
		java.lang.String returnValue = WorkflowComponentServiceUtil.getTaskTransitionsXml(taskId);

		return returnValue;
	}

	public static java.util.List getUserTasks(long instanceId,
		java.lang.String taskName, java.lang.String definitionName,
		java.lang.String assignedTo, java.lang.String createDateGT,
		java.lang.String createDateLT, java.lang.String startDateGT,
		java.lang.String startDateLT, java.lang.String endDateGT,
		java.lang.String endDateLT, boolean hideEndedTasks,
		boolean andOperator, int begin, int end)
		throws java.rmi.RemoteException, 
			com.liferay.portal.kernel.jbi.WorkflowComponentException {
		java.util.List returnValue = WorkflowComponentServiceUtil.getUserTasks(instanceId,
				taskName, definitionName, assignedTo, createDateGT,
				createDateLT, startDateGT, startDateLT, endDateGT, endDateLT,
				hideEndedTasks, andOperator, begin, end);

		return returnValue;
	}

	public static int getUserTasksCount(long instanceId,
		java.lang.String taskName, java.lang.String definitionName,
		java.lang.String assignedTo, java.lang.String createDateGT,
		java.lang.String createDateLT, java.lang.String startDateGT,
		java.lang.String startDateLT, java.lang.String endDateGT,
		java.lang.String endDateLT, boolean hideEndedTasks, boolean andOperator)
		throws java.rmi.RemoteException, 
			com.liferay.portal.kernel.jbi.WorkflowComponentException {
		int returnValue = WorkflowComponentServiceUtil.getUserTasksCount(instanceId,
				taskName, definitionName, assignedTo, createDateGT,
				createDateLT, startDateGT, startDateLT, endDateGT, endDateLT,
				hideEndedTasks, andOperator);

		return returnValue;
	}

	public static java.lang.String getUserTasksCountXml(long instanceId,
		java.lang.String taskName, java.lang.String definitionName,
		java.lang.String assignedTo, java.lang.String createDateGT,
		java.lang.String createDateLT, java.lang.String startDateGT,
		java.lang.String startDateLT, java.lang.String endDateGT,
		java.lang.String endDateLT, boolean hideEndedTasks, boolean andOperator)
		throws java.rmi.RemoteException, 
			com.liferay.portal.kernel.jbi.WorkflowComponentException {
		java.lang.String returnValue = WorkflowComponentServiceUtil.getUserTasksCountXml(instanceId,
				taskName, definitionName, assignedTo, createDateGT,
				createDateLT, startDateGT, startDateLT, endDateGT, endDateLT,
				hideEndedTasks, andOperator);

		return returnValue;
	}

	public static java.lang.String getUserTasksXml(long instanceId,
		java.lang.String taskName, java.lang.String definitionName,
		java.lang.String assignedTo, java.lang.String createDateGT,
		java.lang.String createDateLT, java.lang.String startDateGT,
		java.lang.String startDateLT, java.lang.String endDateGT,
		java.lang.String endDateLT, boolean hideEndedTasks,
		boolean andOperator, int begin, int end)
		throws java.rmi.RemoteException, 
			com.liferay.portal.kernel.jbi.WorkflowComponentException {
		java.lang.String returnValue = WorkflowComponentServiceUtil.getUserTasksXml(instanceId,
				taskName, definitionName, assignedTo, createDateGT,
				createDateLT, startDateGT, startDateLT, endDateGT, endDateLT,
				hideEndedTasks, andOperator, begin, end);

		return returnValue;
	}

	public static void signalInstance(long instanceId)
		throws java.rmi.RemoteException, 
			com.liferay.portal.kernel.jbi.WorkflowComponentException {
		WorkflowComponentServiceUtil.signalInstance(instanceId);
	}

	public static void signalToken(long instanceId, long tokenId)
		throws java.rmi.RemoteException, 
			com.liferay.portal.kernel.jbi.WorkflowComponentException {
		WorkflowComponentServiceUtil.signalToken(instanceId, tokenId);
	}

	public static java.lang.String startWorkflow(long definitionId)
		throws java.rmi.RemoteException, 
			com.liferay.portal.kernel.jbi.WorkflowComponentException {
		java.lang.String returnValue = WorkflowComponentServiceUtil.startWorkflow(definitionId);

		return returnValue;
	}
}