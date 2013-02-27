package org.king.monitor.domain;

/**
 * AbstractMapStateDic entity provides the base persistence definition of the
 * MapStateDic entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractMapStateDic implements java.io.Serializable {

	// Fields

	private long id;
	private String stateid;
	private String statename;
	private String tagcode;
	private long showcolor;
	private long errornot;
	private String errorcode;

	// Constructors

	/** default constructor */
	public AbstractMapStateDic() {
	}

	/** full constructor */
	public AbstractMapStateDic(String stateid, String statename,
			String tagcode, long showcolor, long errornot, String errorcode) {
		this.stateid = stateid;
		this.statename = statename;
		this.tagcode = tagcode;
		this.showcolor = showcolor;
		this.errornot = errornot;
		this.errorcode = errorcode;
	}

	// Property accessors

	public long getId() {
		return this.id;
	}

	public void setId(long id) {
		this.id = id;
	}

	public String getStateid() {
		return this.stateid;
	}

	public void setStateid(String stateid) {
		this.stateid = stateid;
	}

	public String getStatename() {
		return this.statename;
	}

	public void setStatename(String statename) {
		this.statename = statename;
	}

	public String getTagcode() {
		return this.tagcode;
	}

	public void setTagcode(String tagcode) {
		this.tagcode = tagcode;
	}

	public long getShowcolor() {
		return this.showcolor;
	}

	public void setShowcolor(long showcolor) {
		this.showcolor = showcolor;
	}

	public long getErrornot() {
		return this.errornot;
	}

	public void setErrornot(long errornot) {
		this.errornot = errornot;
	}

	public String getErrorcode() {
		return this.errorcode;
	}

	public void setErrorcode(String errorcode) {
		this.errorcode = errorcode;
	}

}