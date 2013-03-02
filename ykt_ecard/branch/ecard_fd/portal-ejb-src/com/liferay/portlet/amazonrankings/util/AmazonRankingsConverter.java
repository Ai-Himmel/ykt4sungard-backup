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

package com.liferay.portlet.amazonrankings.util;

import com.liferay.portal.util.WebCacheable;
import com.liferay.portlet.amazonrankings.model.AmazonRankings;
import com.liferay.util.ConverterException;
import com.liferay.util.GetterUtil;
import com.liferay.util.Time;

import java.net.URL;

import java.text.SimpleDateFormat;

import java.util.Date;
import java.util.List;
import java.util.Locale;

import org.dom4j.Document;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 * <a href="AmazonRankingsConverter.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class AmazonRankingsConverter implements WebCacheable {

	public AmazonRankingsConverter(String isbn) {
		_isbn = isbn;
	}

	public Object convert(String id) throws ConverterException {
		String isbn = _isbn;

		AmazonRankings amazonRankings = null;

		try {
			URL url = new URL(
				"http://xml.amazon.com/onca/xml2?t=webservices-20&dev-t=" +
					AmazonRankingsUtil.getAmazonKey() + "&AsinSearch=" + isbn +
						"&type=heavy&f=xml");

			SAXReader reader = new SAXReader();

			Document doc = reader.read(url);

			Element details = (Element)doc.getRootElement().elements(
				"Details").iterator().next();

			String productName = details.elementText("ProductName");
			String catalog = details.elementText("Catalog");

			List authorsList = details.element("Authors").elements("Author");

			String[] authors = new String[authorsList.size()];

			for (int i = 0; i < authorsList.size(); i++) {
				Element author = (Element)authorsList.get(i);

				authors[i] = author.getTextTrim();
			}

			String releaseDateAsString = details.elementText("ReleaseDate");
			Date releaseDate = GetterUtil.getDate(
				releaseDateAsString,
				new SimpleDateFormat("dd MMMMM,yyyy", Locale.US));
			String manufacturer = details.elementText("Manufacturer");
			String smallImageURL = details.elementText("ImageUrlSmall");
			String mediumImageURL = details.elementText("ImageUrlMedium");
			String largeImageURL = details.elementText("ImageUrlLarge");
			double listPrice = GetterUtil.getDouble(
				details.elementText("ListPrice"));
			double ourPrice = GetterUtil.getDouble(
				details.elementText("OurPrice"), listPrice);
			double usedPrice = GetterUtil.getDouble(
				details.elementText("UsedPrice"));
			double collectiblePrice = GetterUtil.getDouble(
				details.elementText("CollectiblePrice"));
			double thirdPartyNewPrice = GetterUtil.getDouble(
				details.elementText("ThirdPartyNewPrice"));
			int salesRank = GetterUtil.getInteger(
				details.elementText("SalesRank"));
			String media = details.elementText("Media");
			String availability = details.elementText("Availability");

			amazonRankings = new AmazonRankings(
				isbn, productName, catalog, authors, releaseDate,
				releaseDateAsString, manufacturer, smallImageURL,
				mediumImageURL, largeImageURL, listPrice, ourPrice, usedPrice,
				collectiblePrice, thirdPartyNewPrice, salesRank, media,
				availability);
		}
		catch (Exception e) {
			throw new ConverterException(isbn + " " + e.toString());
		}

		return amazonRankings;
	}

	public long getRefreshTime() {
		return _REFRESH_TIME;
	}

	private static final long _REFRESH_TIME = Time.MINUTE * 20;

	private String _isbn;

}