package org.king.topo.domain;


/**
 * AbstractMonitorTopoDeviceDic entity provides the base persistence definition
 * of the MonitorTopoDeviceDic entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractMonitorTopoDeviceDic extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private Integer id;
	private Integer devphytype;
	private String devtypecode;
	private String devtypename;
	private String deviceimage;
	private Integer imagewidth;
	private Integer imageheight;

	// Constructors

	/** default constructor */
	public AbstractMonitorTopoDeviceDic() {
	}

	/** minimal constructor */
	public AbstractMonitorTopoDeviceDic(Integer devphytype,
			String devtypecode) {
		this.devphytype = devphytype;
		this.devtypecode = devtypecode;
	}

	/** full constructor */
	public AbstractMonitorTopoDeviceDic(Integer devphytype,
			String devtypecode,String devtypename, String deviceimage, Integer imagewidth,
			Integer imageheight) {
		this.devphytype = devphytype;
		this.devtypecode = devtypecode;
		this.devtypename = devtypename;
		this.deviceimage = deviceimage;
		this.imagewidth = imagewidth;
		this.imageheight = imageheight;
	}

	// Property accessors

	public Integer getId() {
		return this.id;
	}

	public void setId(Integer id) {
		this.id = id;
	}

	public Integer getDevphytype() {
		return this.devphytype;
	}

	public void setDevphytype(Integer devphytype) {
		this.devphytype = devphytype;
	}

	public String getDevtypecode() {
		return this.devtypecode;
	}

	public void setDevtypecode(String devtypecode) {
		this.devtypecode = devtypecode;
	}

	public String getDevtypename() {
		return devtypename;
	}

	public void setDevtypename(String devtypename) {
		this.devtypename = devtypename;
	}

	public String getDeviceimage() {
		return this.deviceimage;
	}

	public void setDeviceimage(String deviceimage) {
		this.deviceimage = deviceimage;
	}

	public Integer getImagewidth() {
		return this.imagewidth;
	}

	public void setImagewidth(Integer imagewidth) {
		this.imagewidth = imagewidth;
	}

	public Integer getImageheight() {
		return this.imageheight;
	}

	public void setImageheight(Integer imageheight) {
		this.imageheight = imageheight;
	}

	@Override
	public String toString() {
		return "AbstractMonitorTopoDeviceDic [deviceimage=" + deviceimage
				+ ", devphytype=" + devphytype + ", devtypecode=" + devtypecode
				+ ", devtypename=" + devtypename + ", id=" + id
				+ ", imageheight=" + imageheight + ", imagewidth=" + imagewidth
				+ "]";
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime * result
				+ ((deviceimage == null) ? 0 : deviceimage.hashCode());
		result = prime * result
				+ ((devphytype == null) ? 0 : devphytype.hashCode());
		result = prime * result
				+ ((devtypecode == null) ? 0 : devtypecode.hashCode());
		result = prime * result
				+ ((devtypename == null) ? 0 : devtypename.hashCode());
		result = prime * result + ((id == null) ? 0 : id.hashCode());
		result = prime * result
				+ ((imageheight == null) ? 0 : imageheight.hashCode());
		result = prime * result
				+ ((imagewidth == null) ? 0 : imagewidth.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!(obj instanceof AbstractMonitorTopoDeviceDic))
			return false;
		AbstractMonitorTopoDeviceDic other = (AbstractMonitorTopoDeviceDic) obj;
		if (deviceimage == null) {
			if (other.deviceimage != null)
				return false;
		} else if (!deviceimage.equals(other.deviceimage))
			return false;
		if (devphytype == null) {
			if (other.devphytype != null)
				return false;
		} else if (!devphytype.equals(other.devphytype))
			return false;
		if (devtypecode == null) {
			if (other.devtypecode != null)
				return false;
		} else if (!devtypecode.equals(other.devtypecode))
			return false;
		if (devtypename == null) {
			if (other.devtypename != null)
				return false;
		} else if (!devtypename.equals(other.devtypename))
			return false;
		if (id == null) {
			if (other.id != null)
				return false;
		} else if (!id.equals(other.id))
			return false;
		if (imageheight == null) {
			if (other.imageheight != null)
				return false;
		} else if (!imageheight.equals(other.imageheight))
			return false;
		if (imagewidth == null) {
			if (other.imagewidth != null)
				return false;
		} else if (!imagewidth.equals(other.imagewidth))
			return false;
		return true;
	}

	

}