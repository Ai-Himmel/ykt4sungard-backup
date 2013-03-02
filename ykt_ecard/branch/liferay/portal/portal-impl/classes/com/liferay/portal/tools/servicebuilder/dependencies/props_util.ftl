package ${propsUtilPackage};

import com.germinus.easyconf.ComponentProperties;
import com.liferay.util.ExtPropertiesLoader;
import java.util.Properties;

public class PropsUtil {

	public static final String SPRING_CONFIGS = "spring.configs";

	public static final String SPRING_HIBERNATE_DATA_SOURCE = "spring.hibernate.data.source";

	public static final String SPRING_HIBERNATE_SESSION_FACTORY = "spring.hibernate.session.factory";

	public static final String HIBERNATE_CONFIGS = "hibernate.configs";

	public static final String VALUE_OBJECT_FINDER_CACHE_ENABLED = "value.object.finder.cache.enabled";

	public static boolean containsKey(String key) {
		return _getInstance().containsKey(key);
	}

	public static String get(String key) {
		return _getInstance().get(key);
	}

	public static void set(String key, String value) {
		_getInstance().set(key, value);
	}

	public static String[] getArray(String key) {
		return _getInstance().getArray(key);
	}

	public static Properties getProperties() {
		return _getInstance().getProperties();
	}

	public static ComponentProperties getComponentProperties() {
		return _getInstance().getComponentProperties();
	}

	private static ExtPropertiesLoader _getInstance() {
		return ExtPropertiesLoader.getInstance("portlet-service");
	}

}