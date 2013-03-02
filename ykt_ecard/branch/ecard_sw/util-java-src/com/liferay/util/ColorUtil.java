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

import com.liferay.util.lang.FastStringBuffer;

import java.awt.Color;

/**
 * <a href="ColorUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @author  Ming-Gih Lam
 * @author  David Truong
 * @version $Revision: 1.11 $
 *
 */
public class ColorUtil {

	public static Color blend(int[] color1, int[] color2, double ratio) {
		Color blended = new Color(
			(int)(((color2[0]-color1[0]) * ratio) + color1[0]),
			(int)(((color2[1]-color1[1]) * ratio) + color1[1]),
			(int)(((color2[2]-color1[2]) * ratio) + color1[2]));

		return blended;
	}

	public static Color blend (Color color1, Color color2, double ratio){
		int[] rgb1 = {color1.getRed(), color1.getGreen(), color1.getBlue()};
		int[] rgb2 = {color2.getRed(), color2.getGreen(), color2.getBlue()};

		return blend(rgb1, rgb2, ratio);
	}

	public static Color darker(int[] color, double ratio) {
		Color darkened = new Color(
			(int)(color[0] - (color[0] * ratio)),
			(int)(color[1] - (color[1] * ratio)),
			(int)(color[2] - (color[2] * ratio)));

		return darkened;
	}

	public static String getHex(int[] rgb) {
		FastStringBuffer sb = new FastStringBuffer();

		sb.append("#");

		sb.append(
			_KEY.substring(
				(int)Math.floor(rgb[0] / 16),
				(int)Math.floor(rgb[0] / 16) + 1));

		sb.append(_KEY.substring(rgb[0] % 16, (rgb[0] % 16) + 1));

		sb.append(
			_KEY.substring(
				(int)Math.floor(rgb[1] / 16),
				(int)Math.floor(rgb[1] / 16) + 1));

		sb.append(_KEY.substring(rgb[1] % 16, (rgb[1] % 16) + 1));

		sb.append(
			_KEY.substring(
				(int)Math.floor(rgb[2] / 16),
				(int)Math.floor(rgb[2] / 16) + 1));

		sb.append(_KEY.substring(rgb[2] % 16, (rgb[2] % 16) + 1));

		return sb.toString();
	}

	public static int[] getRGB(String hex) {
		if (hex.startsWith("#")) {
			hex = hex.substring(1, hex.length()).toUpperCase();
		}
		else {
			hex = hex.toUpperCase();
		}

		int[] hexArray = new int[6];

		if (hex.length() == 6) {
			char[] c = hex.toCharArray();

			for (int i = 0; i < hex.length(); i++) {
				if (c[i] == 'A') {
					hexArray[i] = 10;
				}
				else if (c[i] == 'B') {
					hexArray[i] = 11;
				}
				else if (c[i] == 'C') {
					hexArray[i] = 12;
				}
				else if (c[i] == 'D') {
					hexArray[i] = 13;
				}
				else if (c[i] == 'E') {
					hexArray[i] = 14;
				}
				else if (c[i] == 'F') {
					hexArray[i] = 15;
				}
				else {
					hexArray[i] =
						GetterUtil.getInteger(new Character(c[i]).toString());
				}
			}
		}

		int[] rgb = new int[3];
		rgb[0] = (hexArray[0] * 16) + hexArray[1];
		rgb[1] = (hexArray[2] * 16) + hexArray[3];
		rgb[2] = (hexArray[4] * 16) + hexArray[5];

		return rgb;
	}

	public static Color lighter(int[] color, double ratio) {
		Color lightened = new Color(
			(int)(((0xFF - color[0]) * ratio) + color[0]),
			(int)(((0xFF - color[1]) * ratio) + color[1]),
			(int)(((0xFF - color[2]) * ratio) + color[2]));

		return lightened;
	}

	private static final String _KEY = "0123456789ABCDEF";

}