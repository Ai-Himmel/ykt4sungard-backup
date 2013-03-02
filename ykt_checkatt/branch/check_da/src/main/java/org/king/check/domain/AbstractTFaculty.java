package org.king.check.domain;

import java.io.Serializable;

/**
 * .
 * User: Yiming.You
 * Date: 2010-12-26
 */
public class AbstractTFaculty implements Serializable {

    private String id;

    private String pid;

    private String name;

    private String value;

    private String pname;

    public AbstractTFaculty() {
    }

    public AbstractTFaculty(String id, String pid, String name, String value,String pname) {
        this.id = id;
        this.pid = pid;
        this.name = name;
        this.value = value;
        this.pname = pname;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getPid() {
        return pid;
    }

    public void setPid(String pid) {
        this.pid = pid;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getValue() {
        return value;
    }

    public void setValue(String value) {
        this.value = value;
    }

    public String getPname() {
        return pname;
    }

    public void setPname(String pname) {
        this.pname = pname;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        AbstractTFaculty that = (AbstractTFaculty) o;

        if (id != null ? !id.equals(that.id) : that.id != null) return false;
        if (name != null ? !name.equals(that.name) : that.name != null) return false;
        if (pid != null ? !pid.equals(that.pid) : that.pid != null) return false;
        if (pname != null ? !pname.equals(that.pname) : that.pname != null) return false;
        if (value != null ? !value.equals(that.value) : that.value != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = id != null ? id.hashCode() : 0;
        result = 31 * result + (pid != null ? pid.hashCode() : 0);
        result = 31 * result + (name != null ? name.hashCode() : 0);
        result = 31 * result + (value != null ? value.hashCode() : 0);
        result = 31 * result + (pname != null ? pname.hashCode() : 0);
        return result;
    }

    @Override
    public String toString() {
        return "AbstractTFaculty{" +
                "id='" + id + '\'' +
                ", pid='" + pid + '\'' +
                ", name='" + name + '\'' +
                ", value='" + value + '\'' +
                ", pname='" + pname + '\'' +
                '}';
    }
}
