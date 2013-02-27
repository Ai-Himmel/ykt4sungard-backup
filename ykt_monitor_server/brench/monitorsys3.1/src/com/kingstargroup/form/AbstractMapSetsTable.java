package com.kingstargroup.form;

/**
 * AbstractMapSetsTable entity provides the base persistence definition of the
 * MapSetsTable entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractMapSetsTable implements java.io.Serializable {

	// Fields

	private long id;
	private long devid;
	private String setsid;
	private String setname;
	private String fatherid;
	private String settype;
	private long setstatus;
	private double xcoor;
	private double ycoor;
	private String feature;

	// Constructors

	/** default constructor */
	public AbstractMapSetsTable() {
	}

	/** minimal constructor */
	public AbstractMapSetsTable(long id) {
		this.id = id;
	}

	/** full constructor */
	public AbstractMapSetsTable(long id, long devid, String setsid, String setname,
			String fatherid, String settype, long setstatus, double xcoor,
			double ycoor, String feature) {
		this.id = id;
		this.devid = devid;
		this.setsid = setsid;
		this.setname = setname;
		this.fatherid = fatherid;
		this.settype = settype;
		this.setstatus = setstatus;
		this.xcoor = xcoor;
		this.ycoor = ycoor;
		this.feature = feature;
	}

	// Property accessors

	public long getId() {
		return this.id;
	}

	public void setId(long id) {
		this.id = id;
	}

	/**
	 * @return the devid
	 */
	public long getDevid() {
		return devid;
	}

	/**
	 * @param devid the devid to set
	 */
	public void setDevid(long devid) {
		this.devid = devid;
	}

	public String getSetsid() {
		return this.setsid;
	}

	public void setSetsid(String setsid) {
		this.setsid = setsid;
	}

	public String getSetname() {
		return this.setname;
	}

	public void setSetname(String setname) {
		this.setname = setname;
	}

	public String getFatherid() {
		return this.fatherid;
	}

	public void setFatherid(String fatherid) {
		this.fatherid = fatherid;
	}

	public String getSettype() {
		return this.settype;
	}

	public void setSettype(String settype) {
		this.settype = settype;
	}

	public long getSetstatus() {
		return this.setstatus;
	}

	public void setSetstatus(long setstatus) {
		this.setstatus = setstatus;
	}

	public double getXcoor() {
		return this.xcoor;
	}

	public void setXcoor(double xcoor) {
		this.xcoor = xcoor;
	}

	public double getYcoor() {
		return this.ycoor;
	}

	public void setYcoor(double ycoor) {
		this.ycoor = ycoor;
	}

	public String getFeature() {
		return this.feature;
	}

	public void setFeature(String feature) {
		this.feature = feature;
	}

}