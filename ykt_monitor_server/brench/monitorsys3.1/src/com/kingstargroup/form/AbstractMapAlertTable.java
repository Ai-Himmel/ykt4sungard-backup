package com.kingstargroup.form;

/**
 * AbstractMapAlertTable entity provides the base persistence definition of the
 * MapAlertTable entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractMapAlertTable implements java.io.Serializable {

	// Fields

	private long id;
	private String parameter;
	private String name;
	private long phonealert;
	private long mailalert;
	private long note;

	// Constructors

	/** default constructor */
	public AbstractMapAlertTable() {
	}

	/** full constructor */
	public AbstractMapAlertTable(String parameter, String name,
			long phonealert, long mailalert, long note) {
		this.parameter = parameter;
		this.name = name;
		this.phonealert = phonealert;
		this.mailalert = mailalert;
		this.note = note;
	}

	// Property accessors

	public long getId() {
		return this.id;
	}

	public void setId(long id) {
		this.id = id;
	}

	public String getParameter() {
		return this.parameter;
	}

	public void setParameter(String parameter) {
		this.parameter = parameter;
	}

	public String getName() {
		return this.name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public long getPhonealert() {
		return this.phonealert;
	}

	public void setPhonealert(long phonealert) {
		this.phonealert = phonealert;
	}

	public long getMailalert() {
		return this.mailalert;
	}

	public void setMailalert(long mailalert) {
		this.mailalert = mailalert;
	}

	public long getNote() {
		return this.note;
	}

	public void setNote(long note) {
		this.note = note;
	}

}