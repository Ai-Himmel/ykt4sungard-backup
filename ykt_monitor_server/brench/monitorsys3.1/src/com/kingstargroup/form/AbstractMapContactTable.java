package com.kingstargroup.form;

/**
 * AbstractMapContactTable entity provides the base persistence definition of
 * the MapContactTable entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractMapContactTable implements java.io.Serializable {

	// Fields

	private long id;
	private String contactname;
	private String contactgender;
	private String contactcompany;
	private String weekdays;
	private String starttime;
	private String endtime;
	private String email;
	private String cellphone;

	// Constructors

	/** default constructor */
	public AbstractMapContactTable() {
	}

	/** full constructor */
	public AbstractMapContactTable(String contactname, String contactgender,
			String contactcompany, String weekdays, String starttime,
			String endtime, String email, String cellphone) {
		this.contactname = contactname;
		this.contactgender = contactgender;
		this.contactcompany = contactcompany;
		this.weekdays = weekdays;
		this.starttime = starttime;
		this.endtime = endtime;
		this.email = email;
		this.cellphone = cellphone;
	}

	// Property accessors

	public long getId() {
		return this.id;
	}

	public void setId(long id) {
		this.id = id;
	}

	public String getContactname() {
		return this.contactname;
	}

	public void setContactname(String contactname) {
		this.contactname = contactname;
	}

	public String getContactgender() {
		return this.contactgender;
	}

	public void setContactgender(String contactgender) {
		this.contactgender = contactgender;
	}

	public String getContactcompany() {
		return this.contactcompany;
	}

	public void setContactcompany(String contactcompany) {
		this.contactcompany = contactcompany;
	}

	public String getWeekdays() {
		return this.weekdays;
	}

	public void setWeekdays(String weekdays) {
		this.weekdays = weekdays;
	}

	public String getStarttime() {
		return this.starttime;
	}

	public void setStarttime(String starttime) {
		this.starttime = starttime;
	}

	public String getEndtime() {
		return this.endtime;
	}

	public void setEndtime(String endtime) {
		this.endtime = endtime;
	}

	public String getEmail() {
		return this.email;
	}

	public void setEmail(String email) {
		this.email = email;
	}

	public String getCellphone() {
		return this.cellphone;
	}

	public void setCellphone(String cellphone) {
		this.cellphone = cellphone;
	}

}