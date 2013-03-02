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

package com.liferay.portlet.weather.util;

import com.liferay.portal.util.WebCacheable;
import com.liferay.portlet.weather.model.Weather;
import com.liferay.util.ConverterException;
import com.liferay.util.Html;
import com.liferay.util.Http;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.Time;

import java.net.URL;

import java.util.Vector;

import org.apache.soap.Constants;
import org.apache.soap.rpc.Call;
import org.apache.soap.rpc.Parameter;
import org.apache.soap.rpc.Response;

/**
 * <a href="WeatherConverter.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.15 $
 *
 */
public class WeatherConverter implements WebCacheable {

	public WeatherConverter(String zip) {
		_zip = zip;
	}

	public Object convert(String id) throws ConverterException {
		Weather weather = null;

		try {
			if (_DEFAULT_TYPE == _TYPE_NWS) {
				String text = Http.URLtoString(
					"http://www.srh.noaa.gov/zipcity.php?inputstring=" + _zip);

				int pos = text.indexOf("currentconds.jpg");

				int x = text.indexOf("&deg;F", pos);
				int y = text.substring(0, x).lastIndexOf(">") + 1;

				weather = new Weather(
					_zip, Float.parseFloat(text.substring(y, x)));
			}
			else  if (_DEFAULT_TYPE == _TYPE_XMETHODS) {
				URL url = new URL(
					"http://services.xmethods.com:80/soap/servlet/rpcrouter");

				Call call = new Call ();
				call.setEncodingStyleURI(Constants.NS_URI_SOAP_ENC);
				call.setTargetObjectURI("urn:xmethods-Temperature");
				call.setMethodName("getTemp");

				Vector params = new Vector ();
				params.addElement(
					new Parameter("zipcode", String.class, _zip, null));

				call.setParams (params);

				Response resp = call.invoke(url, StringPool.BLANK);

				if (resp.generatedFault()) {
					throw new Exception();
				}
				else {
					Parameter result = resp.getReturnValue ();
					Float temperature = (Float)result.getValue();

					weather = new Weather(_zip, temperature.floatValue());
				}
			}
			else if (_DEFAULT_TYPE == _TYPE_WEATHER_CHANNEL) {
				String text = Http.URLtoString(
					"http://www.weather.com/search/search?where=" +
					Http.encodeURL(_zip));

				int x = text.indexOf("<!-- insert wx icon -->") + 23;

				String iconURL = text.substring(
					text.indexOf("http://", x),
					text.indexOf(".gif", x) + 4);
				iconURL = StringUtil.replace(iconURL, "/52/", "/31/");

				x = text.indexOf("<!-- insert current temp -->") + 28;
				int y = text.indexOf("&deg;F", x);

				float temperature = Float.parseFloat(text.substring(x, y));

				weather = new Weather(_zip, iconURL, temperature);
			}
			else if (_DEFAULT_TYPE == _TYPE_YAHOO) {
				String text = Html.stripComments(Http.URLtoString(
					"http://search.weather.yahoo.com/search/weather2?p=" +
					Http.encodeURL(_zip)));

				int x = text.indexOf("<b>", text.indexOf("Currently:")) + 3;
				int y = text.indexOf("&deg;", x);

				float temperature = Float.parseFloat(
					text.substring(x, y).trim());

				String iconURL = text.substring(
					text.indexOf("http://", x),
					text.indexOf(".gif", x) + 4);

				iconURL = StringUtil.replace(iconURL, "/52/", "/31/");

				weather = new Weather(_zip, iconURL, temperature);
			}
		}
		catch (Exception e) {
			throw new ConverterException(_zip + " " + e.toString());
		}

		return weather;
	}

	public long getRefreshTime() {
		return _REFRESH_TIME;
	}

	private static final long _REFRESH_TIME = Time.MINUTE * 20;

	public static final int _TYPE_NWS = 1;

	public static final int _TYPE_XMETHODS = 2;

	public static final int _TYPE_WEATHER_CHANNEL = 3;

	public static final int _TYPE_YAHOO = 4;

	public static final int _DEFAULT_TYPE = _TYPE_YAHOO;

	private String _zip;

}