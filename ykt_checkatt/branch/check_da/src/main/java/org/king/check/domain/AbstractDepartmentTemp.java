package org.king.check.domain;

import java.io.Serializable;

/**
 * .
 * User: Yiming.You
 * Date: 2010-12-18
 */
public class AbstractDepartmentTemp implements Serializable {
    private String id;
    private Long deleteTime;

    public AbstractDepartmentTemp() {
    }

    public AbstractDepartmentTemp(String id, Long deleteTime) {
        this.id = id;
        this.deleteTime = deleteTime;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public Long getDeleteTime() {
        return deleteTime;
    }

    public void setDeleteTime(Long deleteTime) {
        this.deleteTime = deleteTime;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        AbstractDepartmentTemp that = (AbstractDepartmentTemp) o;

        if (deleteTime != null ? !deleteTime.equals(that.deleteTime) : that.deleteTime != null) return false;
        if (id != null ? !id.equals(that.id) : that.id != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = id != null ? id.hashCode() : 0;
        result = 31 * result + (deleteTime != null ? deleteTime.hashCode() : 0);
        return result;
    }

    @Override
    public String toString() {
        return "AbstractDepartmentTemp{" +
                "id='" + id + '\'' +
                ", deleteTime=" + deleteTime +
                '}';
    }
}
