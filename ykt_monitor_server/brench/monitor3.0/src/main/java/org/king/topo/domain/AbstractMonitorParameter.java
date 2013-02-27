package org.king.topo.domain;

/**
 * AbstractMonitorParameter entity provides the base persistence definition of
 * the MonitorParameter entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractMonitorParameter extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private Integer id;
	private String parameter;
	private String parametervalue;
	private String parametername;
	private String parameterunit;

	// Constructors

	/** default constructor */
	public AbstractMonitorParameter() {
	}

	/** full constructor */
	public AbstractMonitorParameter(String parameter, String parametervalue,
			String parametername, String parameterunit) {
		this.parameter = parameter;
		this.parametervalue = parametervalue;
		this.parametername = parametername;
		this.parameterunit = parameterunit;
	}

	// Property accessors

	public Integer getId() {
		return this.id;
	}

	public void setId(Integer id) {
		this.id = id;
	}

	public String getParameter() {
		return this.parameter;
	}

	public void setParameter(String parameter) {
		this.parameter = parameter;
	}

	public String getParametervalue() {
		return this.parametervalue;
	}

	public void setParametervalue(String parametervalue) {
		this.parametervalue = parametervalue;
	}

	public String getParametername() {
		return this.parametername;
	}

	public void setParametername(String parametername) {
		this.parametername = parametername;
	}

	public String getParameterunit() {
		return this.parameterunit;
	}

	public void setParameterunit(String parameterunit) {
		this.parameterunit = parameterunit;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime * result + ((id == null) ? 0 : id.hashCode());
		result = prime * result
				+ ((parameter == null) ? 0 : parameter.hashCode());
		result = prime * result
				+ ((parametername == null) ? 0 : parametername.hashCode());
		result = prime * result
				+ ((parameterunit == null) ? 0 : parameterunit.hashCode());
		result = prime * result
				+ ((parametervalue == null) ? 0 : parametervalue.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (getClass() != obj.getClass())
			return false;
		AbstractMonitorParameter other = (AbstractMonitorParameter) obj;
		if (id == null) {
			if (other.id != null)
				return false;
		} else if (!id.equals(other.id))
			return false;
		if (parameter == null) {
			if (other.parameter != null)
				return false;
		} else if (!parameter.equals(other.parameter))
			return false;
		if (parametername == null) {
			if (other.parametername != null)
				return false;
		} else if (!parametername.equals(other.parametername))
			return false;
		if (parameterunit == null) {
			if (other.parameterunit != null)
				return false;
		} else if (!parameterunit.equals(other.parameterunit))
			return false;
		if (parametervalue == null) {
			if (other.parametervalue != null)
				return false;
		} else if (!parametervalue.equals(other.parametervalue))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "AbstractMonitorParameter [id=" + id + ", parameter="
				+ parameter + ", parametername=" + parametername
				+ ", parameterunit=" + parameterunit + ", parametervalue="
				+ parametervalue + "]";
	}
}