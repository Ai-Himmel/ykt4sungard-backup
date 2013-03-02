/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

package com.liferay.util;

/**
 * <a href="ServerDetector.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.20 $
 *
 */
public class ServerDetector {

	public static final String JBOSS_CLASS = "/org/jboss/Main.class";

	public static final String JETTY_CLASS = "/org/mortbay/jetty/Server.class";

	public static final String JONAS_CLASS =
		"/org/objectweb/jonas/server/Server.class";

	public static final String OC4J_CLASS =
		"/oracle/jsp/oc4jutil/Oc4jUtil.class";

	public static final String ORION_CLASS =
		"/com/evermind/server/ApplicationServer.class";

	public static final String PRAMATI_CLASS = "/com/pramati/Server.class";

	public static final String RESIN_CLASS =
		"/com/caucho/server/resin/Resin.class";

	public static final String REXIP_CLASS = "/com/tcc/Main.class";

	public static final String SUN7_CLASS =
		"/com/iplanet/ias/tools/cli/IasAdminMain.class";

	public static final String SUN8_CLASS =
		"/com/sun/enterprise/cli/framework/CLIMain.class";

	public static final String TOMCAT_CLASS =
		"/org/apache/catalina/startup/Bootstrap.class";

	public static final String WEBLOGIC_CLASS = "/weblogic/Server.class";

	public static final String WEBSPHERE_CLASS =
		"/com/ibm/websphere/product/VersionInfo.class";

	public static boolean isJBoss() {
		ServerDetector sd = _instance;

		if (sd._jBoss == null) {
			Class c = sd.getClass();

			if (c.getResource(JBOSS_CLASS) != null) {
				sd._jBoss = Boolean.TRUE;
			}
			else {
				sd._jBoss = Boolean.FALSE;
			}
		}

		return sd._jBoss.booleanValue();
	}

	public static boolean isJetty() {
		ServerDetector sd = _instance;

		if (sd._jetty == null) {
			Class c = sd.getClass();

			if (c.getResource(JETTY_CLASS) != null) {
				sd._jetty = Boolean.TRUE;
			}
			else {
				sd._jetty = Boolean.FALSE;
			}
		}

		return sd._jetty.booleanValue();
	}

	public static boolean isJOnAS() {
		ServerDetector sd = _instance;

		if (sd._jonas == null) {
			Class c = sd.getClass();

			if (c.getResource(JONAS_CLASS) != null) {
				sd._jonas = Boolean.TRUE;
			}
			else {
				sd._jonas = Boolean.FALSE;
			}
		}

		return sd._jonas.booleanValue();
	}

	public static boolean isOC4J() {
		ServerDetector sd = _instance;

		if (sd._oc4j == null) {
			Class c = sd.getClass();

			if (c.getResource(OC4J_CLASS) != null) {
				sd._oc4j = Boolean.TRUE;
			}
			else {
				sd._oc4j = Boolean.FALSE;
			}
		}

		return sd._oc4j.booleanValue();
	}

	public static boolean isOrion() {
		ServerDetector sd = _instance;

		if (sd._orion == null) {
			Class c = sd.getClass();

			if (c.getResource(ORION_CLASS) != null) {
				sd._orion = Boolean.TRUE;
			}
			else {
				sd._orion = Boolean.FALSE;
			}
		}

		return sd._orion.booleanValue();
	}

	public static boolean isPramati() {
		ServerDetector sd = _instance;

		if (sd._pramati == null) {
			Class c = sd.getClass();

			if (c.getResource(PRAMATI_CLASS) != null) {
				sd._pramati = Boolean.TRUE;
			}
			else {
				sd._pramati = Boolean.FALSE;
			}
		}

		return sd._pramati.booleanValue();
	}

	public static boolean isResin() {
		ServerDetector sd = _instance;

		if (sd._resin == null) {
			Class c = sd.getClass();

			if (c.getResource(RESIN_CLASS) != null) {
				sd._resin = Boolean.TRUE;
			}
			else {
				sd._resin = Boolean.FALSE;
			}
		}

		return sd._resin.booleanValue();
	}

	public static boolean isRexIP() {
		ServerDetector sd = _instance;

		if (sd._rexIP == null) {
			Class c = sd.getClass();

			if (c.getResource(REXIP_CLASS) != null) {
				sd._rexIP = Boolean.TRUE;
			}
			else {
				sd._rexIP = Boolean.FALSE;
			}
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
			Class c = sd.getClass();

			if (c.getResource(SUN7_CLASS) != null) {
				sd._sun7 = Boolean.TRUE;
			}
			else {
				sd._sun7 = Boolean.FALSE;
			}
		}

		return sd._sun7.booleanValue();
	}

	public static boolean isSun8() {
		ServerDetector sd = _instance;

		if (sd._sun8 == null) {
			Class c = sd.getClass();

			if (c.getResource(SUN8_CLASS) != null) {
				sd._sun8 = Boolean.TRUE;
			}
			else {
				sd._sun8 = Boolean.FALSE;
			}
		}

		return sd._sun8.booleanValue();
	}

	public static boolean isTomcat() {
		ServerDetector sd = _instance;

		if (sd._tomcat == null) {
			Class c = sd.getClass();

			if (c.getResource(TOMCAT_CLASS) != null) {
				sd._tomcat = Boolean.TRUE;
			}
			else {
				sd._tomcat = Boolean.FALSE;
			}
		}

		return sd._tomcat.booleanValue();
	}

	public static boolean isWebLogic() {
		ServerDetector sd = _instance;

		if (sd._webLogic == null) {
			Class c = sd.getClass();

			if (c.getResource(WEBLOGIC_CLASS) != null) {
				sd._webLogic = Boolean.TRUE;
			}
			else {
				sd._webLogic = Boolean.FALSE;
			}
		}

		return sd._webLogic.booleanValue();
	}

	public static boolean isWebSphere() {
		ServerDetector sd = _instance;

		if (sd._webSphere == null) {
			Class c = sd.getClass();

			if (c.getResource(WEBSPHERE_CLASS) != null) {
				sd._webSphere = Boolean.TRUE;
			}
			else {
				sd._webSphere = Boolean.FALSE;
			}
		}

		return sd._webSphere.booleanValue();
	}

	private ServerDetector() {
	}

	private static ServerDetector _instance = new ServerDetector();

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