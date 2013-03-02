<#include "copyright.txt" parse="false">


package ${springHibernatePackage};

import com.liferay.portal.kernel.util.Validator;
import ${propsUtilPackage}.PropsUtil;

import java.io.InputStream;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.cfg.Configuration;
import org.hibernate.cfg.Environment;

/**
 * <a href="HibernateConfiguration.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class HibernateConfiguration extends org.springframework.orm.hibernate3.LocalSessionFactoryBean {

	protected Configuration newConfiguration() {
		Configuration cfg = new Configuration();

		try {
			ClassLoader classLoader = getClass().getClassLoader();

			String[] configs = PropsUtil.getArray(PropsUtil.HIBERNATE_CONFIGS);

			for (int i = 0; i < configs.length; i++) {
				try {
					InputStream is =
						classLoader.getResourceAsStream(configs[i]);

					if (is != null) {
						cfg = cfg.addInputStream(is);

						is.close();
					}
				}
				catch (Exception e) {
					e.printStackTrace();
				}
			}

			cfg.setProperties(PropsUtil.getProperties());
		}
		catch (Exception e) {
			_log.error(e, e);
		}

		return cfg;
	}

	protected void postProcessConfiguration(Configuration cfg) {

		// Make sure that the Hibernate settings from PropsUtil are set. See the
		// buildSessionFactory implementation in the LocalSessionFactoryBean
		// class to understand how Spring automates a lot of configuration for
		// Hibernate.

		String connectionReleaseMode = PropsUtil.get(
			Environment.RELEASE_CONNECTIONS);

		if (Validator.isNotNull(connectionReleaseMode)) {
			cfg.setProperty(
				Environment.RELEASE_CONNECTIONS, connectionReleaseMode);
		}
	}

	private static Log _log = LogFactory.getLog(HibernateConfiguration.class);

}