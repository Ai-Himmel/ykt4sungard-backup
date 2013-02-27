package com.kingstargroup.form;

/**
 * AbstractMapParamTable entity provides the base persistence definition of the
 * MapParamTable entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractMapParamTable implements java.io.Serializable {

	// Fields

	private long id;
	private String parameter;
	private double value;
	private String name;
	private String unit;
	private long flag;

	// Constructors

	/** default constructor */
	public AbstractMapParamTable() {
	}

	/** full constructor */
	public AbstractMapParamTable(String parameter, double value, String name,
			String unit, long flag) {
		this.parameter = parameter;
		this.value = value;
		this.name = name;
		this.unit = unit;
		this.flag = flag;
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

	public double getValue() {
		return this.value;
	}

	public void setValue(double value) {
		this.value = value;
	}

	public String getName() {
		return this.name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getUnit() {
		return this.unit;
	}

	public void setUnit(String unit) {
		this.unit = unit;
	}

	public long getFlag() {
		return this.flag;
	}

	public void setFlag(long flag) {
		this.flag = flag;
	}

}