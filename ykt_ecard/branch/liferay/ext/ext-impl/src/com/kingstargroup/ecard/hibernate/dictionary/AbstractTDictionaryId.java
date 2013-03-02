package com.kingstargroup.ecard.hibernate.dictionary;

/**
 * AbstractTDictionaryId entity provides the base persistence definition of the
 * TDictionaryId entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTDictionaryId implements java.io.Serializable {

	// Fields

	private Long dicttype;
	private String dictval;

	// Constructors

	/** default constructor */
	public AbstractTDictionaryId() {
	}

	/** full constructor */
	public AbstractTDictionaryId(Long dicttype, String dictval) {
		this.dicttype = dicttype;
		this.dictval = dictval;
	}

	// Property accessors

	public Long getDicttype() {
		return this.dicttype;
	}

	public void setDicttype(Long dicttype) {
		this.dicttype = dicttype;
	}

	public String getDictval() {
		return this.dictval;
	}

	public void setDictval(String dictval) {
		this.dictval = dictval;
	}

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractTDictionaryId))
			return false;
		AbstractTDictionaryId castOther = (AbstractTDictionaryId) other;

		return ((this.getDicttype() == castOther.getDicttype()) || (this
				.getDicttype() != null
				&& castOther.getDicttype() != null && this.getDicttype()
				.equals(castOther.getDicttype())))
				&& ((this.getDictval() == castOther.getDictval()) || (this
						.getDictval() != null
						&& castOther.getDictval() != null && this.getDictval()
						.equals(castOther.getDictval())));
	}

	public int hashCode() {
		int result = 17;

		result = 37 * result
				+ (getDicttype() == null ? 0 : this.getDicttype().hashCode());
		result = 37 * result
				+ (getDictval() == null ? 0 : this.getDictval().hashCode());
		return result;
	}

}