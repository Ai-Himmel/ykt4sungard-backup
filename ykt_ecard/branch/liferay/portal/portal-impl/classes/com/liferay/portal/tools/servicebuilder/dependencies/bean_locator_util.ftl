package ${beanLocatorUtilPackage};

import ${springUtilPackage}.SpringUtil;
import com.liferay.util.CollectionFactory;

import java.util.Set;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.springframework.context.ApplicationContext;

public class BeanLocatorUtil {

	public static Object locate(String name) {
		if (_beans.contains(name)) {
			if (_log.isWarnEnabled()) {
				_log.warn("Cache the reference to " + name + " for better performance");
			}
		}

		ApplicationContext ctx = SpringUtil.getContext();

		if (_log.isDebugEnabled()) {
			_log.debug("Locating " + name);
		}

		Object obj = ctx.getBean(name);

		_beans.add(name);

		return obj;
	}

	private static Log _log = LogFactory.getLog(BeanLocatorUtil.class);

	private static Set _beans = CollectionFactory.getHashSet();

}