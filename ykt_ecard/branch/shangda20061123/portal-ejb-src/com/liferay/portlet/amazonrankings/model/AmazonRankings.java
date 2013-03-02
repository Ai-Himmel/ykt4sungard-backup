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

package com.liferay.portlet.amazonrankings.model;

import java.io.Serializable;

import java.util.Date;

/**
 * <a href="AmazonRankings.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class AmazonRankings implements Comparable, Serializable {

	public AmazonRankings(String isbn, String productName, String catalog,
							   String[] authors, Date releaseDate,
							   String releaseDateAsString, String manufacturer,
							   String smallImageURL, String mediumImageURL,
							   String largeImageURL, double listPrice,
							   double ourPrice, double usedPrice,
							   double collectiblePrice,
							   double thirdPartyNewPrice, int salesRank,
							   String media, String availability) {

		_isbn = isbn;
		_productName = productName;
		_catalog = catalog;
		_authors = authors;
		_releaseDate = releaseDate;
		_releaseDateAsString = releaseDateAsString;
		_manufacturer = manufacturer;
		_smallImageURL = smallImageURL;
		_mediumImageURL = mediumImageURL;
		_largeImageURL = largeImageURL;
		_listPrice = listPrice;
		_ourPrice = ourPrice;
		_usedPrice = usedPrice;
		_collectiblePrice = collectiblePrice;
		_thirdPartyNewPrice = thirdPartyNewPrice;
		_salesRank = salesRank;
		_media = media;
		_availability = availability;
	}

	public String getISBN() {
		return _isbn;
	}

	public void setISBN(String isbn) {
		_isbn = isbn;
	}

	public String getProductName() {
		return _productName;
	}

	public void setProductName(String productName) {
		_productName = productName;
	}

	public String getCatalog() {
		return _catalog;
	}

	public void setCatalog(String catalog) {
		_catalog = catalog;
	}

	public String[] getAuthors() {
		return _authors;
	}

	public void setAuthors(String[] authors) {
		_authors = authors;
	}

	public Date getReleaseDate() {
		return _releaseDate;
	}

	public void setReleaseDate(Date releaseDate) {
		_releaseDate = releaseDate;
	}

	public String getReleaseDateAsString() {
		return _releaseDateAsString;
	}

	public void setReleaseDateAsString(String releaseDateAsString) {
		_releaseDateAsString = releaseDateAsString;
	}

	public String getManufacturer() {
		return _manufacturer;
	}

	public void setManufacturer(String manufacturer) {
		_manufacturer = manufacturer;
	}

	public String getSmallImageURL() {
		return _smallImageURL;
	}

	public void setSmallImageURL(String smallImageURL) {
		_smallImageURL = smallImageURL;
	}

	public String getMediumImageURL() {
		return _mediumImageURL;
	}

	public void setMediumImageURL(String mediumImageURL) {
		_mediumImageURL = mediumImageURL;
	}

	public String getLargeImageURL() {
		return _largeImageURL;
	}

	public void setLargeImageURL(String largeImageURL) {
		_largeImageURL = largeImageURL;
	}

	public double getListPrice() {
		return _listPrice;
	}

	public void setListPrice(double listPrice) {
		_listPrice = listPrice;
	}

	public double getOurPrice() {
		return _ourPrice;
	}

	public void setOurPrice(double ourPrice) {
		_ourPrice = ourPrice;
	}

	public double getUsedPrice() {
		return _usedPrice;
	}

	public void setUsedPrice(double usedPrice) {
		_usedPrice = usedPrice;
	}

	public double getCollectiblePrice() {
		return _collectiblePrice;
	}

	public void setCollectiblePrice(double collectiblePrice) {
		_collectiblePrice = collectiblePrice;
	}

	public double getThirdPartyNewPrice() {
		return _thirdPartyNewPrice;
	}

	public void setThirdPartyNewPrice(double thirdPartyNewPrice) {
		_thirdPartyNewPrice = thirdPartyNewPrice;
	}

	public int getSalesRank() {
		return _salesRank;
	}

	public void setSalesRank(int salesRank) {
		_salesRank = salesRank;
	}

	public String getMedia() {
		return _media;
	}

	public void setMedia(String media) {
		_media = media;
	}

	public String getAvailability() {
		return _availability;
	}

	public void setAvailability(String availability) {
		_availability = availability;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		AmazonRankings amazonRankings = (AmazonRankings)obj;

		if (getSalesRank() > amazonRankings.getSalesRank()) {
			return 1;
		}
		else if (getSalesRank() < amazonRankings.getSalesRank()) {
			return -1;
		}
		else {
			return getReleaseDate().compareTo(amazonRankings.getReleaseDate());
		}
	}

	private String _isbn;
	private String _productName;
	private String _catalog;
	private String[] _authors;
	private Date _releaseDate;
	private String _releaseDateAsString;
	private String _manufacturer;
	private String _smallImageURL;
	private String _mediumImageURL;
	private String _largeImageURL;
	private double _listPrice;
	private double _ourPrice;
	private double _usedPrice;
	private double _collectiblePrice;
	private double _thirdPartyNewPrice;
	private int _salesRank;
	private String _media;
	private String _availability;

}