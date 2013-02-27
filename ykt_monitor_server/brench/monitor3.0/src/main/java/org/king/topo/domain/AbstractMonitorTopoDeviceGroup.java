package org.king.topo.domain;


/**
 * AbstractMonitorTopoDeviceGroup entity provides the base persistence
 * definition of the MonitorTopoDeviceGroup entity. @author MyEclipse
 * Persistence Tools
 */

public abstract class AbstractMonitorTopoDeviceGroup extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private MonitorTopoDeviceGroupId id;

	// Constructors

	/** default constructor */
	public AbstractMonitorTopoDeviceGroup() {
	}

	/** full constructor */
	public AbstractMonitorTopoDeviceGroup(MonitorTopoDeviceGroupId id) {
		this.id = id;
	}

	// Property accessors

	public MonitorTopoDeviceGroupId getId() {
		return this.id;
	}

	public void setId(MonitorTopoDeviceGroupId id) {
		this.id = id;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime * result + ((id == null) ? 0 : id.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (getClass() != obj.getClass())
			return false;
		AbstractMonitorTopoDeviceGroup other = (AbstractMonitorTopoDeviceGroup) obj;
		if (id == null) {
			if (other.id != null)
				return false;
		} else if (!id.equals(other.id))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "AbstractMonitorTopoDeviceGroup [id=" + id + "]";
	}
}