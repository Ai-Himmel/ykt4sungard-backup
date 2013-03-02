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

import java.io.Serializable;

import java.util.ArrayList;
import java.util.List;

/**
 * <a href="PasswordPolicyRelSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portal.service.http.PasswordPolicyRelServiceSoap</code>.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.http.PasswordPolicyRelServiceSoap
 *
 */
public class PasswordPolicyRelSoap implements Serializable {
	public static PasswordPolicyRelSoap toSoapModel(PasswordPolicyRel model) {
		PasswordPolicyRelSoap soapModel = new PasswordPolicyRelSoap();

		soapModel.setPasswordPolicyRelId(model.getPasswordPolicyRelId());
		soapModel.setPasswordPolicyId(model.getPasswordPolicyId());
		soapModel.setClassNameId(model.getClassNameId());
		soapModel.setClassPK(model.getClassPK());

		return soapModel;
	}

	public static PasswordPolicyRelSoap[] toSoapModels(List models) {
		List soapModels = new ArrayList(models.size());

		for (int i = 0; i < models.size(); i++) {
			PasswordPolicyRel model = (PasswordPolicyRel)models.get(i);

			soapModels.add(toSoapModel(model));
		}

		return (PasswordPolicyRelSoap[])soapModels.toArray(new PasswordPolicyRelSoap[0]);
	}

	public PasswordPolicyRelSoap() {
	}

	public long getPrimaryKey() {
		return _passwordPolicyRelId;
	}

	public void setPrimaryKey(long pk) {
		setPasswordPolicyRelId(pk);
	}

	public long getPasswordPolicyRelId() {
		return _passwordPolicyRelId;
	}

	public void setPasswordPolicyRelId(long passwordPolicyRelId) {
		_passwordPolicyRelId = passwordPolicyRelId;
	}

	public long getPasswordPolicyId() {
		return _passwordPolicyId;
	}

	public void setPasswordPolicyId(long passwordPolicyId) {
		_passwordPolicyId = passwordPolicyId;
	}

	public long getClassNameId() {
		return _classNameId;
	}

	public void setClassNameId(long classNameId) {
		_classNameId = classNameId;
	}

	public long getClassPK() {
		return _classPK;
	}

	public void setClassPK(long classPK) {
		_classPK = classPK;
	}

	private long _passwordPolicyRelId;
	private long _passwordPolicyId;
	private long _classNameId;
	private long _classPK;
}