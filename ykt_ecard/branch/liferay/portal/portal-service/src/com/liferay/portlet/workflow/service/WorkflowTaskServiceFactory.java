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

package com.liferay.portlet.workflow.service;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;

/**
 * <a href="WorkflowTaskServiceFactory.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is responsible for the lookup of the implementation for
 * <code>com.liferay.portlet.workflow.service.WorkflowTaskService</code>.
 * Spring manages the lookup and lifecycle of the beans. This means you can
 * modify the Spring configuration files to return a different implementation or
 * to inject additional behavior.
 * </p>
 *
 * <p>
 * See the <code>spring.configs</code> property in portal.properties for
 * additional information on how to customize the Spring XML files.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.workflow.service.WorkflowTaskService
 * @see com.liferay.portlet.workflow.service.WorkflowTaskServiceUtil
 *
 */
public class WorkflowTaskServiceFactory {
	public static WorkflowTaskService getService() {
		return _getFactory()._service;
	}

	public static WorkflowTaskService getImpl() {
		if (_impl == null) {
			_impl = (WorkflowTaskService)BeanLocatorUtil.locate(_IMPL);
		}

		return _impl;
	}

	public static WorkflowTaskService getTxImpl() {
		if (_txImpl == null) {
			_txImpl = (WorkflowTaskService)BeanLocatorUtil.locate(_TX_IMPL);
		}

		return _txImpl;
	}

	public void setService(WorkflowTaskService service) {
		_service = service;
	}

	private static WorkflowTaskServiceFactory _getFactory() {
		if (_factory == null) {
			_factory = (WorkflowTaskServiceFactory)BeanLocatorUtil.locate(_FACTORY);
		}

		return _factory;
	}

	private static final String _FACTORY = WorkflowTaskServiceFactory.class.getName();
	private static final String _IMPL = WorkflowTaskService.class.getName() +
		".impl";
	private static final String _TX_IMPL = WorkflowTaskService.class.getName() +
		".transaction";
	private static WorkflowTaskServiceFactory _factory;
	private static WorkflowTaskService _impl;
	private static WorkflowTaskService _txImpl;
	private WorkflowTaskService _service;
}