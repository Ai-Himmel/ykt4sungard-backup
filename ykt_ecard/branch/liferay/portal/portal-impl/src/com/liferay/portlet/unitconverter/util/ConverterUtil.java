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

package com.liferay.portlet.unitconverter.util;

import com.liferay.portlet.unitconverter.model.Conversion;

/**
 * <a href="ConverterUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author James Lefeu
 *
 */
public class ConverterUtil {

	public static int TEMPERATURE_CELSIUS = 1;

	public static int TEMPERATURE_FAHRENHEIHT = 2;

	public static Conversion getConversion(int type, int fromId,
										   int toId, double fromValue) {
		double toValue = 0;

		if (type == 0) {
			toValue = convertLength(fromId, toId, fromValue);
		}
		else if (type == 1) {
			toValue = convertArea(fromId, toId, fromValue);
		}
		else if (type == 2) {
			toValue = convertVolume(fromId, toId, fromValue);
		}
		else if (type == 3) {
			toValue = convertMass(fromId, toId, fromValue);
		}
		else if (type == 4) {
			toValue = convertTemperature(fromId, toId, fromValue);
		}

		return new Conversion(type, fromId, toId, fromValue, toValue);
	}

	public static double convertArea(int fromId, int toId, double fromValue) {
		return (fromValue / _AREA[fromId]) * _AREA[toId];
	}

	public static double convertLength(int fromId, int toId, double fromValue) {
		return (fromValue / _LENGTH[fromId]) * _LENGTH[toId];
	}

	public static double convertMass(int fromId, int toId, double fromValue) {
		return (fromValue / _MASS[fromId]) * _MASS[toId];
	}

	public static double convertTemperature(int fromId, int toId,
											double fromValue) {
		return _fromTemperature(toId, _toTemperature(fromId, fromValue));
	}

	public static double convertVolume(int fromId, int toId, double fromValue) {
		return (fromValue / _VOLUME[fromId]) * _VOLUME[toId];
	}

	private final static double _fromTemperature(int toId, double fromValue){
		if (toId == 0) {
			return fromValue;					// Kelvin
		}
		else if (toId == 1) {
			return fromValue - 273.15;			// Celsius
		}
		else if (toId == 2) {
			return (1.8 * fromValue) - 459.67;	// Fahrenheit
		}
		else if (toId == 3) {
			return 1.8 * fromValue;				// Rankine
		}
		else if (toId == 4) {
			return .8 * (fromValue - 273.15);	// R�aumure
		}
		else {
			return 0;
		}
	}

	private final static double _toTemperature(int fromId, double fromValue) {
		if (fromId == 0) {						// Kelvin
			return fromValue;
		}
		else if (fromId == 1) {					// Celsius
			return fromValue + 273.15;
		}
		else if (fromId == 2) { 				// Fahrenheit
			return .5555555555 * (fromValue + 459.67);
		}
		else if (fromId == 3) { 				// Rankine
			return .5555555555 * fromValue;
		}
		else if (fromId == 4) {
			return (1.25 * fromValue) + 273.15;	// R�aumure
		}
		else {
			return 0;
		}
	}

	private final static double _AREA[] = new double[] {
		1.0,				// Square Kilometer
		1000000.0,			// Square Meter
		10000000000.0,		// Square Centimeter
		1000000000000.0,	// Square Millimeter
		10763910,			// Square Foot
		1550003000,			// Square Inch
		1195990,			// Square Yard
		0.3861022,			// Square Mile
		100,				// Hectare
		247.1054,			// Acre
	};

	private final static double _LENGTH[] = new double[] {
		1.0,				// Meter
		1000.0,				// Millimeter
		100.0,				// Centimeter
		0.001,				// Kilometer
		3.28084,			// Foot
		39.37008,			// Inch
		1.093613,			// Yard
		0.000621,			// Mile
		2.187227,			// Cubit
		4.374453,			// Talent
		13.12336			// Handbreath
	};

	private final static double _MASS[] = new double[] {
		1.0,				// Kilogram
		2.204623,			// Pound
		0.00110,			// Ton
		0.02939497,			// Talent
		1.763698,			// Mina
		88.18491, 			// Shekel
		132.2774, 			// Pim
		176.2698, 			// Beka
		1763.698, 			// Gerah
	};

	private final static double _VOLUME[] = new double[] {
		1.0,				// Liter
		1000,				// Cubic Centimeter
		61.02374,			// Cubic Inch (Liquid Measure)
		1.816166,			// Pint (Dry Measure)
		0.004729599,		// Cor (Homer)
		0.009459198,		// Lethek
		0.04729599,			// Ephah
		0.141888,			// Seah
		0.4729599,			// Omer
		0.851328,			// Cab
		0.04402868,			// Bath
		0.2641721,			// Hin
		3.170065,			// Log
	};

}