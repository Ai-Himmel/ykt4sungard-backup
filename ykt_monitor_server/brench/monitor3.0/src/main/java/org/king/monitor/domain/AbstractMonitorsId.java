package org.king.monitor.domain;

/**
 * AbstractMonitorsId entity provides the base persistence definition of the
 * MonitorsId entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractMonitorsId implements java.io.Serializable {

	// Fields

	private String host;
	private String category;
	private String entry;

	// Constructors

	/** default constructor */
	public AbstractMonitorsId() {
	}

	/** full constructor */
	public AbstractMonitorsId(String host, String category, String entry) {
		this.host = host;
		this.category = category;
		this.entry = entry;
	}

	// Property accessors

	public String getHost() {
		return this.host;
	}

	public void setHost(String host) {
		this.host = host;
	}

	public String getCategory() {
		return this.category;
	}

	public void setCategory(String category) {
		this.category = category;
	}

	public String getEntry() {
		return this.entry;
	}

	public void setEntry(String entry) {
		this.entry = entry;
	}

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractMonitorsId))
			return false;
		AbstractMonitorsId castOther = (AbstractMonitorsId) other;

		return ((this.getHost() == castOther.getHost()) || (this.getHost() != null
				&& castOther.getHost() != null && this.getHost().equals(
				castOther.getHost())))
				&& ((this.getCategory() == castOther.getCategory()) || (this
						.getCategory() != null
						&& castOther.getCategory() != null && this
						.getCategory().equals(castOther.getCategory())))
				&& ((this.getEntry() == castOther.getEntry()) || (this
						.getEntry() != null
						&& castOther.getEntry() != null && this.getEntry()
						.equals(castOther.getEntry())));
	}

	public int hashCode() {
		int result = 17;

		result = 37 * result
				+ (getHost() == null ? 0 : this.getHost().hashCode());
		result = 37 * result
				+ (getCategory() == null ? 0 : this.getCategory().hashCode());
		result = 37 * result
				+ (getEntry() == null ? 0 : this.getEntry().hashCode());
		return result;
	}

}