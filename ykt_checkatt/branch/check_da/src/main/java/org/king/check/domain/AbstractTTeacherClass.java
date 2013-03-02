package org.king.check.domain;

/**
 * .
 * User: Yiming.You
 * Date: 2010-12-16
 */
public class AbstractTTeacherClass implements java.io.Serializable {
    private String id;
    private Integer custid;
    private String stuempno;
    private String deptId;

    public AbstractTTeacherClass() {
    }

    public AbstractTTeacherClass(String id, Integer custid, String stuempno, String deptId) {
        this.id = id;
        this.custid = custid;
        this.stuempno = stuempno;
        this.deptId = deptId;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public Integer getCustid() {
        return custid;
    }

    public void setCustid(Integer custid) {
        this.custid = custid;
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

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        AbstractTTeacherClass that = (AbstractTTeacherClass) o;

        if (custid != null ? !custid.equals(that.custid) : that.custid != null) return false;
        if (deptId != null ? !deptId.equals(that.deptId) : that.deptId != null) return false;
        if (id != null ? !id.equals(that.id) : that.id != null) return false;
        if (stuempno != null ? !stuempno.equals(that.stuempno) : that.stuempno != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = id != null ? id.hashCode() : 0;
        result = 31 * result + (custid != null ? custid.hashCode() : 0);
        result = 31 * result + (stuempno != null ? stuempno.hashCode() : 0);
        result = 31 * result + (deptId != null ? deptId.hashCode() : 0);
        return result;
    }

    @Override
    public String toString() {
        return "AbstractTTeacherClass{" +
                "id='" + id + '\'' +
                ", custid=" + custid +
                ", stuempno='" + stuempno + '\'' +
                ", deptId='" + deptId + '\'' +
                '}';
    }
}
