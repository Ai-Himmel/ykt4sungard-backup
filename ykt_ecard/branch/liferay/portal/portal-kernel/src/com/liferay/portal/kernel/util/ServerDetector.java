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

package com.liferay.portal.kernel.util;

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;

/**
 * <a href="ServerDetector.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ServerDetector {

	public static final String GERONIMO_CLASS =
		"/org/apache/geronimo/system/main/Daemon.class";

	public static final String GERONIMO_ID = "geronimo";

	public static final String GLASSFISH_CLASS =
		"/com/sun/appserv/ClassLoaderUtil.class";

	public static final String GLASSFISH_ID = "glassfish";

	public static final String JBOSS_CLASS = "/org/jboss/Main.class";

	public static final String JBOSS_ID = "jboss";

	public static final String JETTY_CLASS = "/org/mortbay/jetty/Server.class";

	public static final String JETTY_ID = "jetty";

	public static final String JONAS_CLASS =
		"/org/objectweb/jonas/server/Server.class";

	public static final String JONAS_ID = "jonas";

	public static final String OC4J_CLASS =
		"oracle.oc4j.util.ClassUtils";

	public static final String OC4J_ID = "oc4j";

	public static final String ORION_CLASS =
		"/com/evermind/server/ApplicationServer.class";

	public static final String ORION_ID = "orion";

	public static final String PRAMATI_CLASS = "/com/pramati/Server.class";

	public static final String PRAMATI_ID = "pramati";

	public static final String RESIN_CLASS =
		"/com/caucho/server/resin/Resin.class";

	public static final String RESIN_ID = "resin";

	public static final String REXIP_CLASS = "/com/tcc/Main.class";

	public static final String REXIP_ID = "rexip";

	public static final String SUN7_CLASS =
		"/com/iplanet/ias/tools/cli/IasAdminMain.class";

	public static final String SUN7_ID = "sun7";

	public static final String SUN8_CLASS =
		"/com/sun/enterprise/cli/framework/CLIMain.class";

	public static final String SUN8_ID = "sun8";

	public static final String TOMCAT_BOOTSTRAP_CLASS =
		"/org/apache/catalina/startup/Bootstrap.class";

	public static final String TOMCAT_EMBEDDED_CLASS =
		"/org/apache/catalina/startup/Embedded.class";

	public static final String TOMCAT_ID = "tomcat";

	public static final String WEBLOGIC_CLASS = "/weblogic/Server.class";

	public static final String WEBLOGIC_ID = "weblogic";

	public static final String WEBSPHERE_CLASS =
		"/com/ibm/websphere/product/VersionInfo.class";

	public static final String WEBSPHERE_ID = "websphere";

	public static String getServerId() {
		ServerDetector sd = _instance;

		if (sd._serverId == null) {
			if (ServerDetector.isGeronimo()) {
				sd._serverId = GERONIMO_ID;
			}
			else if (ServerDetector.isGlassfish()) {
				sd._serverId = GLASSFISH_ID;
			}
			else if (ServerDetector.isJBoss()) {
				sd._serverId = JBOSS_ID;
			}
			else if (ServerDetector.isJOnAS()) {
				sd._serverId = JONAS_ID;
			}
			else if (ServerDetector.isOC4J()) {
				sd._serverId = OC4J_ID;
			}
			else if (ServerDetector.isOrion()) {
				sd._serverId = ORION_ID;
			}
			else if (ServerDetector.isPramati()) {
				sd._serverId = PRAMATI_ID;
			}
			else if (ServerDetector.isResin()) {
				sd._serverId = RESIN_ID;
			}
			else if (ServerDetector.isRexIP()) {
				sd._serverId = REXIP_ID;
			}
			else if (ServerDetector.isSun7()) {
				sd._serverId = SUN7_ID;
			}
			else if (ServerDetector.isSun8()) {
				sd._serverId = SUN8_ID;
			}
			else if (ServerDetector.isWebLogic()) {
				sd._serverId = WEBLOGIC_ID;
			}
			else if (ServerDetector.isWebSphere()) {
				sd._serverId = WEBSPHERE_ID;
			}

			if (ServerDetector.isJetty()) {
				if (sd._serverId == null) {
					sd._serverId = JETTY_ID;
				}
				else {
					sd._serverId += "-" + JETTY_ID;
				}
			}
			else if (ServerDetector.isTomcat()) {
				if (sd._serverId == null) {
					sd._serverId = TOMCAT_ID;
				}
				else {
					sd._serverId += "-" + TOMCAT_ID;
				}
			}

			if (_log.isInfoEnabled()) {
				_log.info("Detected server " + sd._serverId);
			}

			if (sd._serverId == null) {
				throw new RuntimeException("Server is not supported");
			}
		}

		return sd._serverId;
	}

	public static boolean isGeronimo() {
		ServerDetector sd = _instance;

		if (sd._geronimo == null) {
			sd._geronimo = _detect(GERONIMO_CLASS);
		}

		return sd._geronimo.booleanValue();
	}

	public static boolean isGlassfish() {
		ServerDetector sd = _instance;

		if (sd._glassfish == null) {
			sd._glassfish = _detect(GLASSFISH_CLASS);
		}

		return sd._glassfish.booleanValue();
	}

	public static boolean isJBoss() {
		ServerDetector sd = _instance;

		if (sd._jBoss == null) {
			sd._jBoss = _detect(JBOSS_CLASS);
		}

		return sd._jBoss.booleanValue();
	}

	public static boolean isJetty() {
		ServerDetector sd = _instance;

		if (sd._jetty == null) {
			sd._jetty = _detect(JETTY_CLASS);
		}

		return sd._jetty.booleanValue();
	}

	public static boolean isJOnAS() {
		ServerDetector sd = _instance;

		if (sd._jonas == null) {
			sd._jonas = _detect(JONAS_CLASS);
		}

		return sd._jonas.booleanValue();
	}

	public static boolean isOC4J() {
		ServerDetector sd = _instance;

		if (sd._oc4j == null) {
			sd._oc4j = _detect(OC4J_CLASS);
		}

		return sd._oc4j.booleanValue();
	}

	public static boolean isOrion() {
		ServerDetector sd = _instance;

		if (sd._orion == null) {
			sd._orion = _detect(ORION_CLASS);
		}

		return sd._orion.booleanValue();
	}

	public static boolean isPramati() {
		ServerDetector sd = _instance;

		if (sd._pramati == null) {
			sd._pramati = _detect(PRAMATI_CLASS);
		}

		return sd._pramati.booleanValue();
	}

	public static boolean isResin() {
		ServerDetector sd = _instance;

		if (sd._resin == null) {
			sd._resin = _detect(RESIN_CLASS);
		}

		return sd._resin.booleanValue();
	}

	public static boolean isRexIP() {
		ServerDetector sd = _instance;

		if (sd._rexIP == null) {
			sd._rexIP = _detect(REXIP_CLASS);
		}

		return sd._rexIP.booleanValue();
	}

	public static boolean isSun() {
		if (isSun7() || isSun8()) {
			return true;
		}
		else {
			return false;
		}
	}

	public static boolean isSun7() {
		ServerDetector sd = _instance;

		if (sd._sun7 == null) {
			sd._sun7 = _detect(SUN7_CLASS);
		}

		return sd._sun7.booleanValue();
	}

	public static boolean isSun8() {
		ServerDetector sd = _instance;

		if (sd._sun8 == null) {
			sd._sun8 = _detect(SUN8_CLASS);
		}

		return sd._sun8.booleanValue();
	}

	public static boolean isTomcat() {
		ServerDetector sd = _instance;

		if (sd._tomcat == null) {
			sd._tomcat = _detect(TOMCAT_BOOTSTRAP_CLASS);
		}

		if (sd._tomcat == null) {
			sd._tomcat = _detect(TOMCAT_EMBEDDED_CLASS);
		}

		return sd._tomcat.booleanValue();
	}

	public static boolean isWebLogic() {
		ServerDetector sd = _instance;

		if (sd._webLogic == null) {
			sd._webLogic = _detect(WEBLOGIC_CLASS);
		}

		return sd._webLogic.booleanValue();
	}

	public static boolean isWebSphere() {
		ServerDetector sd = _instance;

		if (sd._webSphere == null) {
			sd._webSphere = _detect(WEBSPHERE_CLASS);
		}

		return sd._webSphere.booleanValue();
	}

	private static Boolean _detect(String className) {
		try {
			ClassLoader.getSystemClassLoader().loadClass(className);

			return Boolean.TRUE;
		}
		catch (ClassNotFoundException cnfe) {
			ServerDetector sd = _instance;

			Class c = sd.getClass();

			if (c.getResource(className) != null) {
				return Boolean.TRUE;
			}
			else {
				return Boolean.FALSE;
			}
		}
	}

	private ServerDetector() {
	}

	private static Log _log = LogFactoryUtil.getLog(ServerDetector.class);

	private static ServerDetector _instance = new ServerDetector();

	private String _serverId;
	private Boolean _geronimo;
	private Boolean _glassfish;
	private Boolean _jBoss;
	private Boolean _jetty;
	private Boolean _jonas;
	private Boolean _oc4j;
	private Boolean _orion;
	private Boolean _pramati;
	private Boolean _resin;
	private Boolean _rexIP;
	private Boolean _sun7;
	private Boolean _sun8;
	private Boolean _tomcat;
	private Boolean _webLogic;
	private Boolean _webSphere;

}