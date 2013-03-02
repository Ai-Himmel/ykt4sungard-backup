<#include "copyright.txt" parse="false">


package ${packagePath};

import com.liferay.portal.PortalException;

/**
 * <a href="${exception}Exception.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ${exception}Exception extends PortalException {

	public ${exception}Exception() {
		super();
	}

	public ${exception}Exception(String msg) {
		super(msg);
	}

	public ${exception}Exception(String msg, Throwable cause) {
		super(msg, cause);
	}

	public ${exception}Exception(Throwable cause) {
		super(cause);
	}

}