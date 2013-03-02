<#include "copyright.txt" parse="false">


package ${springUtilPackage};

import ${propsUtilPackage}.PropsUtil;
import com.liferay.util.spring.context.LazyClassPathApplicationContext;

import org.springframework.context.ApplicationContext;

/**
 * <a href="SpringUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Michael Young
 *
 */
public class SpringUtil {

	public static ApplicationContext getContext() {
		if (_ctx == null) {
			_ctx = new LazyClassPathApplicationContext(
				PropsUtil.getArray(PropsUtil.SPRING_CONFIGS));
		}

		return _ctx;
	}

	private static ApplicationContext _ctx = null;

}