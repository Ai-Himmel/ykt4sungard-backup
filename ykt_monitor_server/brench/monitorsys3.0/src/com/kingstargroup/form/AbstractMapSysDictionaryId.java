package com.kingstargroup.form;

/**
 * AbstractMapSysDictionaryId entity provides the base persistence definition of
 * the MapSysDictionaryId entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractMapSysDictionaryId implements
		java.io.Serializable {

	// Fields

	private long dictNo;
	private String dictValue;

	// Constructors

	/** default constructor */
	public AbstractMapSysDictionaryId() {
	}

	/** full constructor */
	public AbstractMapSysDictionaryId(long dictNo, String dictValue) {
		this.dictNo = dictNo;
		this.dictValue = dictValue;
	}

	// Property accessors

	public long getDictNo() {
		return this.dictNo;
	}

	public void setDictNo(long dictNo) {
		this.dictNo = dictNo;
	}

	public String getDictValue() {
		return this.dictValue;
	}

	public void setDictValue(String dictValue) {
		this.dictValue = dictValue;
	}

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractMapSysDictionaryId))
			return false;
		AbstractMapSysDictionaryId castOther = (AbstractMapSysDictionaryId) other;

		return (this.getDictNo() == castOther.getDictNo())
				&& ((this.getDictValue() == castOther.getDictValue()) || (this
						.getDictValue() != null
						&& castOther.getDictValue() != null && this
						.getDictValue().equals(castOther.getDictValue())));
	}

	public int hashCode() {
		int result = 17;

		result = 37 * result + (int) this.getDictNo();
		result = 37 * result
				+ (getDictValue() == null ? 0 : this.getDictValue().hashCode());
		return result;
	}

}