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

import javax.naming.Name;
import javax.naming.NamingEnumeration;
import javax.naming.NamingException;
import javax.naming.OperationNotSupportedException;
import javax.naming.directory.Attributes;
import javax.naming.directory.DirContext;
import javax.naming.directory.ModificationItem;
import javax.naming.directory.SearchControls;

/**
 * <a href="DummyDirContext.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DummyDirContext extends DummyContext implements DirContext {

	public void bind(Name name, Object obj, Attributes attrs)
		throws NamingException {

		throw new OperationNotSupportedException();
	}

	public void bind(String name, Object obj, Attributes attrs)
		throws NamingException {

		throw new OperationNotSupportedException();
	}

	public DirContext createSubcontext(Name name, Attributes attrs)
		throws NamingException {

		throw new OperationNotSupportedException();
	}

	public DirContext createSubcontext(String name, Attributes attrs)
		throws NamingException {

		throw new OperationNotSupportedException();
	}

	public Attributes getAttributes(Name name) throws NamingException {
		throw new OperationNotSupportedException();
	}

	public Attributes getAttributes(String name) throws NamingException {
		throw new OperationNotSupportedException();
	}

	public Attributes getAttributes(Name name, String[] attrIds)
		throws NamingException {

		throw new OperationNotSupportedException();
	}

	public Attributes getAttributes(String name, String[] attrIds)
		throws NamingException {

		throw new OperationNotSupportedException();
	}

	public DirContext getSchema(Name name) throws NamingException {
		throw new OperationNotSupportedException();
	}

	public DirContext getSchema(String name) throws NamingException {
		throw new OperationNotSupportedException();
	}

	public DirContext getSchemaClassDefinition(Name name)
		throws NamingException {

		throw new OperationNotSupportedException();
	}

	public DirContext getSchemaClassDefinition(String name)
		throws NamingException {

		throw new OperationNotSupportedException();
	}

	public void modifyAttributes(
			Name name, int modificationOp, Attributes attrs)
		throws NamingException {

		throw new OperationNotSupportedException();
	}

	public void modifyAttributes(
			String name, int modificationOp, Attributes attrs)
		throws NamingException {

		throw new OperationNotSupportedException();
	}

	public void modifyAttributes(Name name, ModificationItem[] mods)
		throws NamingException {

		throw new OperationNotSupportedException();
	}

	public void modifyAttributes(String name, ModificationItem[] mods)
		throws NamingException {

		throw new OperationNotSupportedException();
	}

	public void rebind(Name name, Object obj, Attributes attrs)
		throws NamingException {

		throw new OperationNotSupportedException();
	}

	public void rebind(String name, Object obj, Attributes attrs)
		throws NamingException {

		throw new OperationNotSupportedException();
	}

	public NamingEnumeration search(
			Name name, Attributes matchingAttributes,
			String[] attributesToReturn)
		throws NamingException {

		throw new OperationNotSupportedException();
	}

	public NamingEnumeration search(
			String name, Attributes matchingAttributes,
			String[] attributesToReturn)
		throws NamingException {

		throw new OperationNotSupportedException();
	}

	public NamingEnumeration search(Name name, Attributes matchingAttributes)
		throws NamingException {

		throw new OperationNotSupportedException();
	}

	public NamingEnumeration search(String name, Attributes matchingAttributes)
		throws NamingException {

		throw new OperationNotSupportedException();
	}

	public NamingEnumeration search(
			Name name, String filter, SearchControls cons)
		throws NamingException {

		throw new OperationNotSupportedException();
	}

	public NamingEnumeration search(
			String name, String filter, SearchControls cons)
		throws NamingException {

		throw new OperationNotSupportedException();
	}

	public NamingEnumeration search(
			Name name, String filterExpr, Object[] filterArgs,
			SearchControls cons)
		throws NamingException {

		throw new OperationNotSupportedException();
	}

	public NamingEnumeration search(
			String name, String filterExpr, Object[] filterArgs,
			SearchControls cons)
		throws NamingException {

		throw new OperationNotSupportedException();
	}

}