/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.security.domain.ProtectedResource.java
 * 创建日期： 2006-4-20 9:34:00
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-4-20 9:34:00      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
package org.king.security.domain;

/**
 * <p> ProtectedResource.java </p>
 * <p> {功能说明} </p>
 *
 * <p><a href="ProtectedResource.java.html"><i>查看源代码</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-20
 * 
 *
 */
public class ProtectedResource {

	/** xml tag constants */
	public static final String PROPERTY_PROTECTED_RESOURCE = "ProtectedResource";

	/** DOCUMENT ME! */
	public static final String PROPERTY_CODE = "code";

	/** DOCUMENT ME! */
	public static final String PROPERTY_URL = "url";

	/** DOCUMENT ME! */
	public static final String PROPERTY_NAME = "name";

	/** DOCUMENT ME! */
	private String code;

	/** description */
	private String name;

	/** url of the protected resource, such as "post.go" */
	private String url;

	/**
	 * Creates a new ProtectedResource object.
	 * 
	 * @param arg0
	 *            DOCUMENT ME!
	 * @param arg1
	 *            DOCUMENT ME!
	 * @param arg2
	 *            DOCUMENT ME!
	 */
	public ProtectedResource(final String arg0, final String arg1,
			final String arg2) {
		this.code = arg0;
		this.url = arg2;
		this.name = arg1;
	}

	/**
	 * set box
	 * 
	 * @param arg0
	 *            box
	 */
	public final void setCode(final String arg0) {
		this.code = arg0;
	}

	/**
	 * DOCUMENT ME!
	 * 
	 * @return DOCUMENT ME!
	 */
	public final String getCode() {
		return code;
	}

	/**
	 * DOCUMENT ME!
	 * 
	 * @param arg0
	 *            DOCUMENT ME!
	 */
	public final void setName(final String arg0) {
		this.name = arg0;
	}

	/**
	 * DOCUMENT ME!
	 * 
	 * @return DOCUMENT ME!
	 */
	public final String getName() {
		return name;
	}

	/**
	 * set url
	 * 
	 * @param arg0
	 *            url
	 */
	public final void setUrl(final String arg0) {
		this.url = arg0;
	}

	/**
	 * DOCUMENT ME!
	 * 
	 * @return DOCUMENT ME!
	 */
	public final String getUrl() {
		return url;
	}

	/**
	 * DOCUMENT ME!
	 * 
	 * @return DOCUMENT ME!
	 */
	public final String toString() {
		return code + "\n" + name + "\n" + url;
	}
}
