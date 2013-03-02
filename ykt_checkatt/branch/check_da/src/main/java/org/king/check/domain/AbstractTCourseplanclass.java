package org.king.check.domain;

/**
 * AbstractTCourseplanclass entity provides the base persistence definition of
 * the TCourseplanclass entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractTCourseplanclass  implements
		java.io.Serializable {

	// Fields

	private TCourseplanclassId id;

	// Constructors

	/** default constructor */
	public AbstractTCourseplanclass() {
	}

	/** full constructor */
	public AbstractTCourseplanclass(TCourseplanclassId id) {
		this.id = id;
	}

	// Property accessors

	public TCourseplanclassId getId() {
		return this.id;
	}

	public void setId(TCourseplanclassId id) {
		this.id = id;
	}

}