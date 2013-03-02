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

import java.util.ArrayList;
import java.util.List;

/**
 * <a href="WorkflowDefinitionSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author Charles May
 *
 */
public class WorkflowDefinitionSoap extends WorkflowDefinition {

	public static WorkflowDefinitionSoap toSoapModel(WorkflowDefinition model) {
		WorkflowDefinitionSoap soapModel = new WorkflowDefinitionSoap();

		soapModel.setDefinitionId(model.getDefinitionId());
		soapModel.setName(model.getName());
		soapModel.setType(model.getType());
		soapModel.setVersion(model.getVersion());
		soapModel.setXml(model.getXml());

		return soapModel;
	}

	public static WorkflowDefinitionSoap[] toSoapModels(List models) {
		List soapModels = new ArrayList(models.size());

		for (int i = 0; i < models.size(); i++) {
			WorkflowDefinition model = (WorkflowDefinition)models.get(i);

			soapModels.add(toSoapModel(model));
		}

		return (WorkflowDefinitionSoap[])soapModels.toArray(
			new WorkflowDefinitionSoap[0]);
	}

	public WorkflowDefinitionSoap() {
	}

}