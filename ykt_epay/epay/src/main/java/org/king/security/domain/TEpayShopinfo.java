package org.king.security.domain;


/**
 * TEpayShopinfo entity. @author MyEclipse Persistence Tools
 */

public class TEpayShopinfo implements java.io.Serializable {

	// Fields

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private Long shopid;
	private String showname;
	private String key;
	private Integer ischeck;
	private String checkurl;

	// Constructors

	/** default constructor */
	public TEpayShopinfo() {
	}

	/** minimal constructor */
	public TEpayShopinfo(Long shopid) {
		this.shopid = shopid;
	}

	/** full constructor */
	public TEpayShopinfo(Long shopid, String showname, String key,
			Integer ischeck, String checkurl) {
		this.shopid = shopid;
		this.showname = showname;
		this.key = key;
		this.ischeck = ischeck;
		this.checkurl = checkurl;
	}

	// Property accessors

	public Long getShopid() {
		return this.shopid;
	}

	public void setShopid(Long shopid) {
		this.shopid = shopid;
	}

	public String getShowname() {
		return this.showname;
	}

	public void setShowname(String showname) {
		this.showname = showname;
	}

	public String getKey() {
		return this.key;
	}

	public void setKey(String key) {
		this.key = key;
	}

	public Integer getIscheck() {
		return this.ischeck;
	}

	public void setIscheck(Integer ischeck) {
		this.ischeck = ischeck;
	}

	public String getCheckurl() {
		return this.checkurl;
	}

	public void setCheckurl(String checkurl) {
		this.checkurl = checkurl;
	}

}