package org.king.check.domain;

/**
 * AbstractTCourseplanclassId entity provides the base persistence definition of
 * the TCourseplanclassId entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractTCourseplanclassId  implements
		java.io.Serializable {

	// Fields

	private String planid;
	private String classno;

	// Constructors

	/** default constructor */
	public AbstractTCourseplanclassId() {
	}

	/** full constructor */
	public AbstractTCourseplanclassId(String planid, String classno) {
		this.planid = planid;
		this.classno = classno;
	}

	// Property accessors

	public String getPlanid() {
		return this.planid;
	}

	public void setPlanid(String planid) {
		this.planid = planid;
	}

	public String getClassno() {
		return this.classno;
	}

	public void setClassno(String classno) {
		this.classno = classno;
	}

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractTCourseplanclassId))
			return false;
		AbstractTCourseplanclassId castOther = (AbstractTCourseplanclassId) other;

		return ((this.getPlanid() == castOther.getPlanid()) || (this
				.getPlanid() != null
				&& castOther.getPlanid() != null && this.getPlanid().equals(
				castOther.getPlanid())))
				&& ((this.getClassno() == castOther.getClassno()) || (this
						.getClassno() != null
						&& castOther.getClassno() != null && this.getClassno()
						.equals(castOther.getClassno())));
	}

	public int hashCode() {
		int result = 17;

		result = 37 * result
				+ (getPlanid() == null ? 0 : this.getPlanid().hashCode());
		result = 37 * result
				+ (getClassno() == null ? 0 : this.getClassno().hashCode());
		return result;
	}

}