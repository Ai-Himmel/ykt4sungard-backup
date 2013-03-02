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

package com.liferay.portal.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.ClassName;
import com.liferay.portal.model.ModelHintsUtil;
import com.liferay.portal.model.impl.ClassNameImpl;
import com.liferay.portal.service.base.ClassNameLocalServiceBaseImpl;
import com.liferay.util.CollectionFactory;

import java.util.List;
import java.util.Map;

/**
 * <a href="ClassNameLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ClassNameLocalServiceImpl extends ClassNameLocalServiceBaseImpl {

	public void checkClassNames() throws PortalException, SystemException {
		List models = ModelHintsUtil.getModels();

		for (int i = 0; i < models.size(); i++) {
			String value = (String)models.get(i);

			getClassName(value);
		}
	}

	public ClassName getClassName(long classNameId)
		throws PortalException, SystemException {

		return classNamePersistence.findByPrimaryKey(classNameId);
	}

	public ClassName getClassName(String value)
		throws PortalException, SystemException {

		if (Validator.isNull(value)) {
			return _nullClassName;
		}

		// Always cache the class name. This table exists to improve
		// performance. Create the class name if one does not exist.

		ClassName classNameModel = (ClassName)_classNames.get(value);

		if (classNameModel == null) {
			classNameModel = classNamePersistence.fetchByValue(value);

			if (classNameModel == null) {
				long classNameId = counterLocalService.increment();

				classNameModel = classNamePersistence.create(classNameId);

				classNameModel.setValue(value);

				classNamePersistence.update(classNameModel);
			}

			_classNames.put(value, classNameModel);
		}

		return classNameModel;
	}

	private static ClassName _nullClassName = new ClassNameImpl();
	private static Map _classNames = CollectionFactory.getSyncHashMap();

}