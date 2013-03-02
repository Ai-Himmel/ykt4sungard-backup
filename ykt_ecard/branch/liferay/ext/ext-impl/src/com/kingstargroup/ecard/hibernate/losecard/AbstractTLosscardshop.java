package com.kingstargroup.ecard.hibernate.losecard;
// default package

/**
 * AbstractTLosscardshop entity provides the base persistence definition of the
 * TLosscardshop entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractTLosscardshop implements java.io.Serializable {

	// Fields

	private String shopcode;
	private String shopname;
	private String addr;
	private String tel;
	private String getcardplace;
	private String lastsaved;

	// Constructors

	/** default constructor */
	public AbstractTLosscardshop() {
	}

	/** minimal constructor */
	public AbstractTLosscardshop(String shopcode) {
		this.shopcode = shopcode;
	}

	/** full constructor */
	public AbstractTLosscardshop(String shopcode, String shopname, String addr,
			String tel, String getcardplace, String lastsaved) {
		this.shopcode = shopcode;
		this.shopname = shopname;
		this.addr = addr;
		this.tel = tel;
		this.getcardplace = getcardplace;
		this.lastsaved = lastsaved;
	}

	// Property accessors

	public String getShopcode() {
		return this.shopcode;
	}

	public void setShopcode(String shopcode) {
		this.shopcode = shopcode;
	}

	public String getShopname() {
		return this.shopname;
	}

	public void setShopname(String shopname) {
		this.shopname = shopname;
	}

	public String getAddr() {
		return this.addr;
	}

	public void setAddr(String addr) {
		this.addr = addr;
	}

	public String getTel() {
		return this.tel;
	}

	public void setTel(String tel) {
		this.tel = tel;
	}

	public String getGetcardplace() {
		return this.getcardplace;
	}

	public void setGetcardplace(String getcardplace) {
		this.getcardplace = getcardplace;
	}

	public String getLastsaved() {
		return this.lastsaved;
	}

	public void setLastsaved(String lastsaved) {
		this.lastsaved = lastsaved;
	}

	
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((addr == null) ? 0 : addr.hashCode());
		result = prime * result
				+ ((getcardplace == null) ? 0 : getcardplace.hashCode());
		result = prime * result
				+ ((lastsaved == null) ? 0 : lastsaved.hashCode());
		result = prime * result
				+ ((shopcode == null) ? 0 : shopcode.hashCode());
		result = prime * result
				+ ((shopname == null) ? 0 : shopname.hashCode());
		result = prime * result + ((tel == null) ? 0 : tel.hashCode());
		return result;
	}

	
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		AbstractTLosscardshop other = (AbstractTLosscardshop) obj;
		if (addr == null) {
			if (other.addr != null)
				return false;
		} else if (!addr.equals(other.addr))
			return false;
		if (getcardplace == null) {
			if (other.getcardplace != null)
				return false;
		} else if (!getcardplace.equals(other.getcardplace))
			return false;
		if (lastsaved == null) {
			if (other.lastsaved != null)
				return false;
		} else if (!lastsaved.equals(other.lastsaved))
			return false;
		if (shopcode == null) {
			if (other.shopcode != null)
				return false;
		} else if (!shopcode.equals(other.shopcode))
			return false;
		if (shopname == null) {
			if (other.shopname != null)
				return false;
		} else if (!shopname.equals(other.shopname))
			return false;
		if (tel == null) {
			if (other.tel != null)
				return false;
		} else if (!tel.equals(other.tel))
			return false;
		return true;
	}

}