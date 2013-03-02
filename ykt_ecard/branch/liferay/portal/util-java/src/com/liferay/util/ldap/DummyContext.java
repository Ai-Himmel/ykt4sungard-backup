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

package com.liferay.util.ldap;

import java.util.Hashtable;

import javax.naming.Context;
import javax.naming.Name;
import javax.naming.NameParser;
import javax.naming.NamingEnumeration;
import javax.naming.NamingException;
import javax.naming.OperationNotSupportedException;

/**
 * <a href="DummyContext.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DummyContext implements Context {

	public Object addToEnvironment(String propName, Object propVal)
		throws NamingException {

		throw new OperationNotSupportedException();
	}

	public void bind(Name name, Object obj) throws NamingException {
		throw new OperationNotSupportedException();
	}

	public void bind(String name, Object obj) throws NamingException {
		throw new OperationNotSupportedException();
	}

	public void close() throws NamingException {
		throw new OperationNotSupportedException();
	}

	public Name composeName(Name name, Name prefix) throws NamingException {
		throw new OperationNotSupportedException();
	}

	public String composeName(String name, String prefix)
		throws NamingException {

		throw new OperationNotSupportedException();
	}

	public Context createSubcontext(Name name) throws NamingException {
		throw new OperationNotSupportedException();
	}

	public Context createSubcontext(String name) throws NamingException {
		throw new OperationNotSupportedException();
	}

	public void destroySubcontext(Name name) throws NamingException {
		throw new OperationNotSupportedException();
	}

	public void destroySubcontext(String name) throws NamingException {
		throw new OperationNotSupportedException();
	}

	public Hashtable getEnvironment() throws NamingException {
		throw new OperationNotSupportedException();
	}

	public String getNameInNamespace() throws NamingException {
		throw new OperationNotSupportedException();
	}

	public NameParser getNameParser(Name name) throws NamingException {
		throw new OperationNotSupportedException();
	}

	public NameParser getNameParser(String name) throws NamingException {
		throw new OperationNotSupportedException();
	}

	public NamingEnumeration list(Name name) throws NamingException {
		throw new OperationNotSupportedException();
	}

	public NamingEnumeration list(String name) throws NamingException {
		throw new OperationNotSupportedException();
	}

	public NamingEnumeration listBindings(Name name) throws NamingException {
		throw new OperationNotSupportedException();
	}

	public NamingEnumeration listBindings(String name)
		throws NamingException {

		throw new OperationNotSupportedException();
	}

	public Object lookup(Name name) throws NamingException {
		throw new OperationNotSupportedException();
	}

	public Object lookup(String name) throws NamingException {
		throw new OperationNotSupportedException();
	}

	public Object lookupLink(Name name) throws NamingException {
		throw new OperationNotSupportedException();
	}

	public Object lookupLink(String name) throws NamingException {
		throw new OperationNotSupportedException();
	}

	public void rebind(Name name, Object obj) throws NamingException {
		throw new OperationNotSupportedException();
	}

	public void rebind(String name, Object obj) throws NamingException {
		throw new OperationNotSupportedException();
	}

	public Object removeFromEnvironment(String propName)
		throws NamingException {

		throw new OperationNotSupportedException();
	}

	public void rename(Name oldName, Name newName) throws NamingException {
		throw new OperationNotSupportedException();
	}

	public void rename(String oldName, String newName)
		throws NamingException {

		throw new OperationNotSupportedException();
	}

	public void unbind(Name name) throws NamingException {
		throw new OperationNotSupportedException();
	}

	public void unbind(String name) throws NamingException {
		throw new OperationNotSupportedException();
	}

}