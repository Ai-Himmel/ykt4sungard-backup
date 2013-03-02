package org.king.check.domain;

/**
 * .
 * User: Yiming.You
 * Date: 2010-12-16
 */
public class AbstractTTeacherClassTemp implements java.io.Serializable {
    private Integer id;
    private Integer operId;
    private String stuempno;
    private String deptId;
    private String counselor;
    private String areaCode;
    private String custname;
    private String deptName;
    private String areaName;

    public AbstractTTeacherClassTemp() {
    }

    public AbstractTTeacherClassTemp(Integer id, Integer operId, String stuempno, String deptId, String counselor, String areaCode, String custname, String deptName, String areaName) {
        this.id = id;
        this.operId = operId;
        this.stuempno = stuempno;
        this.deptId = deptId;
        this.counselor = counselor;
        this.areaCode = areaCode;
        this.custname = custname;
        this.deptName = deptName;
        this.areaName = areaName;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public Integer getOperId() {
        return operId;
    }

    public void setOperId(Integer operId) {
        this.operId = operId;
    }

    public String getStuempno() {
        return stuempno;
    }

    public void setStuempno(String stuempno) {
        this.stuempno = stuempno;
    }

    public String getDeptId() {
        return deptId;
    }

    public void setDeptId(String deptId) {
        this.deptId = deptId;
    }

    public String getCounselor() {
        return counselor;
    }

    public void setCounselor(String counselor) {
        this.counselor = counselor;
    }

    public String getAreaCode() {
        return areaCode;
    }

    public void setAreaCode(String areaCode) {
        this.areaCode = areaCode;
    }

    public String getCustname() {
        return custname;
    }

    public void setCustname(String custname) {
        this.custname = custname;
    }

    public String getDeptName() {
        return deptName;
    }

    public void setDeptName(String deptName) {
        this.deptName = deptName;
    }

    public String getAreaName() {
        return areaName;
    }

    public void setAreaName(String areaName) {
        this.areaName = areaName;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        AbstractTTeacherClassTemp that = (AbstractTTeacherClassTemp) o;

        if (areaCode != null ? !areaCode.equals(that.areaCode) : that.areaCode != null) return false;
        if (areaName != null ? !areaName.equals(that.areaName) : that.areaName != null) return false;
        if (counselor != null ? !counselor.equals(that.counselor) : that.counselor != null) return false;
        if (custname != null ? !custname.equals(that.custname) : that.custname != null) return false;
        if (deptId != null ? !deptId.equals(that.deptId) : that.deptId != null) return false;
        if (deptName != null ? !deptName.equals(that.deptName) : that.deptName != null) return false;
        if (id != null ? !id.equals(that.id) : that.id != null) return false;
        if (operId != null ? !operId.equals(that.operId) : that.operId != null) return false;
        if (stuempno != null ? !stuempno.equals(that.stuempno) : that.stuempno != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = id != null ? id.hashCode() : 0;
        result = 31 * result + (operId != null ? operId.hashCode() : 0);
        result = 31 * result + (stuempno != null ? stuempno.hashCode() : 0);
        result = 31 * result + (deptId != null ? deptId.hashCode() : 0);
        result = 31 * result + (counselor != null ? counselor.hashCode() : 0);
        result = 31 * result + (areaCode != null ? areaCode.hashCode() : 0);
        result = 31 * result + (custname != null ? custname.hashCode() : 0);
        result = 31 * result + (deptName != null ? deptName.hashCode() : 0);
        result = 31 * result + (areaName != null ? areaName.hashCode() : 0);
        return result;
    }

    @Override
    public String toString() {
        return "AbstractTTeacherClassTemp{" +
                "id=" + id +
                ", operId=" + operId +
                ", stuempno='" + stuempno + '\'' +
                ", deptId='" + deptId + '\'' +
                ", counselor='" + counselor + '\'' +
                ", areaCode='" + areaCode + '\'' +
                ", custname='" + custname + '\'' +
                ", deptName='" + deptName + '\'' +
                ", areaName='" + areaName + '\'' +
                '}';
    }
}
