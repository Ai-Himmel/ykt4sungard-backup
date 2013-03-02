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

package com.liferay.portal.security.jaas.ext.jonas;

import com.liferay.portal.kernel.util.MethodCache;
import com.liferay.portal.kernel.util.ReflectionUtil;
import com.liferay.portal.security.jaas.ext.BasicLoginModule;

import java.lang.reflect.Method;

import java.security.Principal;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="PortalLoginModule.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortalLoginModule extends BasicLoginModule {

	public boolean commit() {
		boolean commitValue = super.commit();

		if (commitValue) {
			getSubject().getPrincipals().add(getPrincipal());
			getSubject().getPrivateCredentials().add(getPassword());

			Principal group = (Principal)ReflectionUtil.newInstance(
				_JGROUP, "Roles");
			Object role = ReflectionUtil.newInstance(_JROLE, "users");

			try {
				Method method = MethodCache.get(
					_JGROUP, "addMember", new Class[] {role.getClass()});

				method.invoke(group, new Object[] {role});
			}
			catch (Exception e) {
				_log.error(e, e);
			}

			getSubject().getPrincipals().add(group);
		}

		return commitValue;
	}

	protected Principal getPortalPrincipal(String name) {
		return (Principal)ReflectionUtil.newInstance(_JPRINCIPAL, name);
	}

	private static final String _JGROUP =
		"org.objectweb.jonas.security.auth.JGroup";

	private static final String _JPRINCIPAL =
		"org.objectweb.jonas.security.auth.JPrincipal";

	private static final String _JROLE =
		"org.objectweb.jonas.security.auth.JRole";

 	private static Log _log = LogFactory.getLog(PortalLoginModule.class);

}