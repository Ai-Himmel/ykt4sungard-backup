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

package com.liferay.portal.tools;

import com.liferay.portal.model.ColorScheme;
import com.liferay.portal.model.Theme;
import com.liferay.portal.util.EntityResolver;
import com.liferay.util.ColorUtil;
import com.liferay.util.FileUtil;
import com.liferay.util.GetterUtil;
import com.liferay.util.ImageUtil;
import com.liferay.util.NullSafeProperties;
import com.liferay.util.PropertiesUtil;
import com.liferay.util.StringUtil;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.image.BufferedImage;
import java.awt.image.MemoryImageSource;
import java.awt.image.PixelGrabber;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import java.util.Enumeration;
import java.util.Iterator;
import java.util.Properties;

import javax.imageio.ImageIO;

import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 * <a href="ColorSchemeBuilder.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @author  Keith R. Davis
 * @author  Ming-Gih Lam
 * @author  David Truong
 * @version $Revision: 1.32 $
 *
 */
public class ColorSchemeBuilder {

	public static void main(String[] args) {
		boolean overwrite = GetterUtil.get(
			System.getProperty("color.scheme.builder.overwrite"), false);

		try {
			ColorSchemeBuilder.build(
				"WEB-INF/liferay-look-and-feel.xml", overwrite);
			ColorSchemeBuilder.build(
				"WEB-INF/liferay-look-and-feel-ext.xml", overwrite);
		}
		catch (IOException ioe) {
			ioe.printStackTrace();
		}
	}

	public static void build(String lookAndFeelFileName, boolean overwrite)
		throws IOException {

		_instance._build(lookAndFeelFileName, overwrite);
	}

	//
	// Images
	//

	public static void createButton(
			OutputStream out, String hex1, String hex2)
		throws IOException {

		int buttonHeight = 20;

		BufferedImage image =
			new BufferedImage(1, buttonHeight, BufferedImage.TYPE_INT_ARGB);
		Graphics g = image.getGraphics();

		int[] rgb1 = ColorUtil.getRGB(hex1);
		int[] rgb2 = ColorUtil.getRGB(hex2);

		Color lightColor1 = ColorUtil.lighter(rgb1, 0.75);
		Color lightColor2 = ColorUtil.lighter(rgb2, 0.25);

		for (int i = 0; i <= buttonHeight; i++) {
			g.setColor(
				ColorUtil.blend(lightColor1, lightColor2,
					((double)(i))/(double)(buttonHeight * 2)));
			g.fillRect(0, i, 1, 1);
		}

		ImageUtil.encodeGIF(image, out);
	}

	public static void createGradient(
			OutputStream out, String hex1, String hex2)
		throws IOException {

		int gradientHeight = 27;

		BufferedImage image =
			new BufferedImage(1, gradientHeight, BufferedImage.TYPE_INT_ARGB);
		Graphics g = image.getGraphics();

		int[] rgb1 = ColorUtil.getRGB(hex1);
		int[] rgb2 = ColorUtil.getRGB(hex2);

		for (int i = 0; i <= gradientHeight; i++) {
			g.setColor(
				ColorUtil.blend(rgb1, rgb2, ((double)(i))/gradientHeight));
			g.fillRect(0, i, 1, 1);
		}

		ImageUtil.encodeGIF(image, out);
	}

	public static void createTab(
			InputStream in, OutputStream out, String hex)
		throws IOException {

		int oldColorRGB = new Color(255, 0, 255).getRGB();

		int[] rgb = ColorUtil.getRGB(hex);
		int newColorRGB = new Color(rgb[0], rgb[1], rgb[2]).getRGB();

		BufferedImage oldImage = ImageIO.read(in);
		oldImage.flush();

		BufferedImage newImage =
			replacePixels(oldImage, oldColorRGB, newColorRGB);

		ImageUtil.encodeGIF(newImage, out);
	}

	public static void createDottedX(OutputStream out, String hex)
		throws IOException {

		BufferedImage image =
			new BufferedImage(6, 1, BufferedImage.TYPE_INT_ARGB);
		Graphics g = image.getGraphics();

		int[] rgb = ColorUtil.getRGB(hex);
		g.setColor(new Color(rgb[0], rgb[1], rgb[2]));

		g.fillRect(0, 0, 3, 1);

		ImageUtil.encodeGIF(image, out);
	}

	public static void createDottedY(OutputStream out, String hex)
		throws IOException {

		BufferedImage image =
			new BufferedImage(1, 6, BufferedImage.TYPE_INT_ARGB);
		Graphics g = image.getGraphics();

		int[] rgb = ColorUtil.getRGB(hex);
		g.setColor(new Color(rgb[0], rgb[1], rgb[2]));

		g.fillRect(0, 0, 1, 3);

		ImageUtil.encodeGIF(image, out);
	}

	public static void createTopLeft(OutputStream out, String hex1, String hex2)
		throws IOException {

		BufferedImage image =
			new BufferedImage(5, 5, BufferedImage.TYPE_INT_ARGB);
		Graphics g = image.getGraphics();

		int[] rgb = ColorUtil.getRGB(hex1);
		g.setColor(new Color(rgb[0], rgb[1], rgb[2]));

		g.fillRect(3, 0, 2, 1);
		g.fillRect(1, 1, 4, 2);
		g.fillRect(0, 3, 5, 2);

		rgb = ColorUtil.getRGB(hex2);
		g.setColor(new Color(rgb[0], rgb[1], rgb[2]));

		g.fillRect(3, 0, 2, 1);
		g.fillRect(2, 1, 2, 1);
		g.fillRect(1, 1, 1, 3);
		g.fillRect(0, 3, 1, 2);

		ImageUtil.encodeGIF(image, out);
	}

	public static void createTopRight(
			OutputStream out, String hex1, String hex2)
		throws IOException {

		BufferedImage image =
			new BufferedImage(5, 5, BufferedImage.TYPE_INT_ARGB);
		Graphics g = image.getGraphics();

		int[] rgb = ColorUtil.getRGB(hex1);
		g.setColor(new Color(rgb[0], rgb[1], rgb[2]));

		g.fillRect(0, 0, 2, 1);
		g.fillRect(0, 1, 4, 2);
		g.fillRect(0, 3, 5, 2);

		rgb = ColorUtil.getRGB(hex2);
		g.setColor(new Color(rgb[0], rgb[1], rgb[2]));

		g.fillRect(0, 0, 2, 1);
		g.fillRect(1, 1, 2, 1);
		g.fillRect(3, 1, 1, 3);
		g.fillRect(4, 3, 1, 2);

		ImageUtil.encodeGIF(image, out);
	}

	public static void createBottomLeft(
			OutputStream out, String hex1, String hex2)
		throws IOException {

		BufferedImage image =
			new BufferedImage(5, 5, BufferedImage.TYPE_INT_ARGB);
		Graphics g = image.getGraphics();

		int[] rgb = ColorUtil.getRGB(hex1);
		g.setColor(new Color(rgb[0], rgb[1], rgb[2]));

		g.fillRect(0, 0, 5, 2);
		g.fillRect(1, 2, 4, 2);
		g.fillRect(3, 4, 2, 1);

		rgb = ColorUtil.getRGB(hex2);
		g.setColor(new Color(rgb[0], rgb[1], rgb[2]));

		g.fillRect(0, 0, 1, 2);
		g.fillRect(1, 1, 1, 3);
		g.fillRect(2, 3, 2, 1);
		g.fillRect(3, 4, 2, 1);

		ImageUtil.encodeGIF(image, out);
	}

	public static void createBottomRight(
			OutputStream out, String hex1, String hex2)
		throws IOException {

		BufferedImage image =
			new BufferedImage(5, 5, BufferedImage.TYPE_INT_ARGB);
		Graphics g = image.getGraphics();

		int[] rgb = ColorUtil.getRGB(hex1);
		g.setColor(new Color(rgb[0], rgb[1], rgb[2]));

		g.fillRect(0, 0, 5, 2);
		g.fillRect(0, 2, 4, 2);
		g.fillRect(0, 4, 2, 1);

		rgb = ColorUtil.getRGB(hex2);
		g.setColor(new Color(rgb[0], rgb[1], rgb[2]));

		g.fillRect(4, 0, 1, 2);
		g.fillRect(3, 1, 1, 3);
		g.fillRect(1, 3, 2, 1);
		g.fillRect(0, 4, 2, 1);

		ImageUtil.encodeGIF(image, out);
	}

	protected static BufferedImage replacePixels(
		BufferedImage image, int oldColorRGB, int newColorRGB) {

		int imageHeight = image.getHeight();
		int imageWidth = image.getWidth();

		int[] pixels = new int[imageWidth * imageHeight];

		Toolkit toolkit = Toolkit.getDefaultToolkit();

		Image tmpImage = toolkit.createImage(image.getSource());

		PixelGrabber grabber = new PixelGrabber(
			tmpImage, 0, 0, imageWidth, imageHeight, pixels, 0, imageWidth);

		try {
			if (!grabber.grabPixels()) {
				throw new InterruptedException();
			}
		}
		catch (InterruptedException ie) {
			ie.printStackTrace();
		}

		for (int y = 0; y < imageHeight; y++) {
			for (int x = 0; x < imageWidth; x++) {
				if (pixels[(y * imageWidth) + x] == oldColorRGB) {
					pixels[(y * imageWidth) + x] = newColorRGB;
				}
			}
		}

		tmpImage = toolkit.createImage(new MemoryImageSource(
			imageWidth, imageHeight, pixels, 0, imageWidth));

		BufferedImage newImage = new BufferedImage(
			imageWidth, imageHeight, BufferedImage.TYPE_INT_ARGB);

		Graphics2D g2d = newImage.createGraphics();
		g2d.drawImage(tmpImage, 0, 0, imageWidth, imageHeight, null);
		g2d.dispose();

		newImage.flush();

		return newImage;
	}

	private ColorSchemeBuilder() {
	}

	private void _build(String lookAndFeelFileName, boolean overwrite)
		throws IOException {

		String rootDir = "../";
		String portalWebDir = "portal-web/docroot/";

		if (!FileUtil.exists(
				rootDir + portalWebDir + "WEB-INF/web.xml")) {

			portalWebDir = "ext-web/tmp/";
		}

		File lookAndFeelFile = new File(
			rootDir + portalWebDir + lookAndFeelFileName);
		if (!lookAndFeelFile.exists()) {
			return;
		}

		String outDirectory =
			rootDir + portalWebDir + "html/themes/classic/color_schemes/";

		SAXReader reader = new SAXReader();
		reader.setEntityResolver(new EntityResolver());

		Document doc = null;

		try {
			doc = reader.read(lookAndFeelFile);
		}
		catch (DocumentException de) {
			de.printStackTrace();
		}

		Element root = doc.getRootElement();

		Element classicThemeEl = null;

		Iterator itr = root.elements("theme").iterator();

		while (itr.hasNext()) {
			Element theme = (Element)itr.next();

			String id = theme.attributeValue("id");

			if (id.equals(Theme.DEFAULT_THEME_ID)) {
				classicThemeEl = theme;
			}
		}

		if (classicThemeEl == null) {
			return;
		}

		itr = classicThemeEl.elements("color-scheme").iterator();

		while (itr.hasNext()) {
			Element colorScheme = (Element)itr.next();

			String id = colorScheme.attributeValue("id");
			String settings = colorScheme.getText();

			Properties p = new NullSafeProperties();

			PropertiesUtil.load(p, settings);
			PropertiesUtil.trimKeys(p);

			if (overwrite || !new File(outDirectory + id).exists()) {
				File file = new File(outDirectory + id);
				file.mkdirs();

				OutputStream os = null;

				// Button

				os = new FileOutputStream(
					outDirectory + id + "/button_gradient.gif");
				createButton(
					os,
					p.getProperty(ColorScheme.PORTLET_MENU_BG),
					p.getProperty(ColorScheme.PORTLET_TITLE_BG));
				os.close();

				// Tabs

				_createTabFile(
					"tab_join_left_multi_on.gif",
					outDirectory + id,
					p.getProperty(ColorScheme.LAYOUT_TAB_SELECTED_BG));

				_createTabFile(
					"tab_join_left_on.gif",
					outDirectory + id,
					p.getProperty(ColorScheme.LAYOUT_TAB_SELECTED_BG));

				_createTabFile(
					"tab_join_right_multi_off.gif",
					outDirectory + id,
					p.getProperty(ColorScheme.LAYOUT_TAB_SELECTED_BG));

				_createTabFile(
					"tab_join_right_multi_on.gif",
					outDirectory + id,
					p.getProperty(ColorScheme.LAYOUT_TAB_SELECTED_BG));

				_createTabFile(
					"tab_join_right_off.gif",
					outDirectory + id,
					p.getProperty(ColorScheme.LAYOUT_TAB_SELECTED_BG));

				_createTabFile(
					"tab_join_right_on.gif",
					outDirectory + id,
					p.getProperty(ColorScheme.LAYOUT_TAB_SELECTED_BG));

				_createTabFile(
					"tab_left_multi_off.gif",
					outDirectory + id,
					p.getProperty(ColorScheme.LAYOUT_TAB_SELECTED_BG));

				_createTabFile(
					"tab_left_multi_on.gif",
					outDirectory + id,
					p.getProperty(ColorScheme.LAYOUT_TAB_SELECTED_BG));

				_createTabFile(
					"tab_left_off.gif",
					outDirectory + id,
					p.getProperty(ColorScheme.LAYOUT_TAB_SELECTED_BG));

				_createTabFile(
					"tab_left_on.gif",
					outDirectory + id,
					p.getProperty(ColorScheme.LAYOUT_TAB_SELECTED_BG));

				_createTabFile(
					"tab_middle_multi_off.gif",
					outDirectory + id,
					p.getProperty(ColorScheme.LAYOUT_TAB_SELECTED_BG));

				_createTabFile(
					"tab_middle_off.gif",
					outDirectory + id,
					p.getProperty(ColorScheme.LAYOUT_TAB_SELECTED_BG));

				_createTabFile(
					"tab_middle_on.gif",
					outDirectory + id,
					p.getProperty(ColorScheme.LAYOUT_TAB_SELECTED_BG));

				_createTabFile(
					"tab_right_multi_off.gif",
					outDirectory + id,
					p.getProperty(ColorScheme.LAYOUT_TAB_SELECTED_BG));

				_createTabFile(
					"tab_right_multi_on.gif",
					outDirectory + id,
					p.getProperty(ColorScheme.LAYOUT_TAB_SELECTED_BG));

				_createTabFile(
					"tab_right_off.gif",
					outDirectory + id,
					p.getProperty(ColorScheme.LAYOUT_TAB_SELECTED_BG));

				_createTabFile(
					"tab_right_on.gif",
					outDirectory + id,
					p.getProperty(ColorScheme.LAYOUT_TAB_SELECTED_BG));

				_createTabFile(
					"tab_right_single_off.gif",
					outDirectory + id,
					p.getProperty(ColorScheme.LAYOUT_TAB_SELECTED_BG));

				_createTabFile(
					"tab_right_single_on.gif",
					outDirectory + id,
					p.getProperty(ColorScheme.LAYOUT_TAB_SELECTED_BG));

				// Dotted X and Y

				Enumeration enu = p.propertyNames();

				while (enu.hasMoreElements()) {
					String key = (String)enu.nextElement();

					if (key.endsWith("-bg")) {
						String fileName =
							outDirectory + id + "/" +
								StringUtil.replace(key, "-", "_");

						os = new FileOutputStream(fileName + "_x.gif");
						createDottedX(os, p.getProperty(key));
						os.close();

						os = new FileOutputStream(fileName + "_y.gif");
						createDottedY(os, p.getProperty(key));
						os.close();
					}
				}

				// Gradients

				os = new FileOutputStream(
					outDirectory + id + "/portlet_title_bg_gradient.gif");
				createGradient(
					os,
					p.getProperty(ColorScheme.PORTLET_MENU_BG),
					p.getProperty(ColorScheme.PORTLET_TITLE_BG));
				os.close();

				os = new FileOutputStream(
					outDirectory + id + "/portlet_menu_bg_gradient.gif");
				createGradient(
					os,
					p.getProperty(ColorScheme.LAYOUT_BG),
					p.getProperty(ColorScheme.PORTLET_MENU_BG));
				os.close();

				// Rounded corners

				os = new FileOutputStream(
					outDirectory + id + "/portlet_corner_ul.gif");
				createTopLeft(
					os,
					p.getProperty(ColorScheme.PORTLET_BG),
					p.getProperty(ColorScheme.PORTLET_TITLE_BG));
				os.close();

				os = new FileOutputStream(
					outDirectory + id + "/portlet_corner_ur.gif");
				createTopRight(
					os,
					p.getProperty(ColorScheme.PORTLET_BG),
					p.getProperty(ColorScheme.PORTLET_TITLE_BG));
				os.close();

				os = new FileOutputStream(
					outDirectory + id + "/portlet_corner_bl.gif");
				createBottomLeft(
					os,
					p.getProperty(ColorScheme.PORTLET_BG),
					p.getProperty(ColorScheme.PORTLET_TITLE_BG));
				os.close();

				os = new FileOutputStream(
					outDirectory + id + "/portlet_corner_br.gif");
				createBottomRight(
					os,
					p.getProperty(ColorScheme.PORTLET_BG),
					p.getProperty(ColorScheme.PORTLET_TITLE_BG));
				os.close();
			}
		}
	}

	private void _createTabFile(
			String fileName, String outDirectory, String background)
		throws IOException {

		InputStream is = new BufferedInputStream(
			getClass().getClassLoader().getResourceAsStream(
				"tmpl/themes/classic/color_schemes/" + fileName));
		OutputStream os = new FileOutputStream(
			outDirectory + "/" + fileName);

		createTab(is, os, background);

		is.close();
		os.close();
	}

	private static ColorSchemeBuilder _instance = new ColorSchemeBuilder();

}