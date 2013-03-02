package com.kingstargroup.ecard.hibernate.card;

/**
 * AbstractTDept entity provides the base persistence definition of the TDept
 * entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTDept implements java.io.Serializable {

	// Fields

	private String deptcode;
	private String areacode;
	private String deptname;
	private String deptename;
	private String deptfullname;
	private String fdeptcode;
	private Long deptlevel;
	private String olddeptcode;
	private String useflag;
	private String lastsaved;

	// Constructors

	/** default constructor */
	public AbstractTDept() {
	}

	/** minimal constructor */
	public AbstractTDept(String deptcode) {
		this.deptcode = deptcode;
	}

	/** full constructor */
	public AbstractTDept(String deptcode, String areacode, String deptname,
			String deptename, String deptfullname, String fdeptcode,
			Long deptlevel, String olddeptcode, String useflag, String lastsaved) {
		this.deptcode = deptcode;
		this.areacode = areacode;
		this.deptname = deptname;
		this.deptename = deptename;
		this.deptfullname = deptfullname;
		this.fdeptcode = fdeptcode;
		this.deptlevel = deptlevel;
		this.olddeptcode = olddeptcode;
		this.useflag = useflag;
		this.lastsaved = lastsaved;
	}

	// Property accessors

	public String getDeptcode() {
		return this.deptcode;
	}

	public void setDeptcode(String deptcode) {
		this.deptcode = deptcode;
	}

	public String getAreacode() {
		return this.areacode;
	}

	public void setAreacode(String areacode) {
		this.areacode = areacode;
	}

	public String getDeptname() {
		return this.deptname;
	}

	public void setDeptname(String deptname) {
		this.deptname = deptname;
	}

	public String getDeptename() {
		return this.deptename;
	}

	public void setDeptename(String deptename) {
		this.deptename = deptename;
	}

	public String getDeptfullname() {
		return this.deptfullname;
	}

	public void setDeptfullname(String deptfullname) {
		this.deptfullname = deptfullname;
	}

	public String getFdeptcode() {
		return this.fdeptcode;
	}

	public void setFdeptcode(String fdeptcode) {
		this.fdeptcode = fdeptcode;
	}

	public Long getDeptlevel() {
		return this.deptlevel;
	}

	public void setDeptlevel(Long deptlevel) {
		this.deptlevel = deptlevel;
	}

	public String getOlddeptcode() {
		return this.olddeptcode;
	}

	public void setOlddeptcode(String olddeptcode) {
		this.olddeptcode = olddeptcode;
	}

	public String getUseflag() {
		return this.useflag;
	}

	public void setUseflag(String useflag) {
		this.useflag = useflag;
	}

	public String getLastsaved() {
		return this.lastsaved;
	}

	public void setLastsaved(String lastsaved) {
		this.lastsaved = lastsaved;
	}

}