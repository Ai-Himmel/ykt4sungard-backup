package org.king.check.dao;

import org.king.check.domain.TTeacherClassTemp;
import org.king.framework.dao.MyQuery;

import java.io.Serializable;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-12-16
 */
public interface TeacherClassTempDAO {
    public List find(MyQuery myQuery);

    public List find(String query);

    public List getAll();

    public void update(TTeacherClassTemp transientInstance);

    public void delete(TTeacherClassTemp transientInstance);

    public void save(TTeacherClassTemp transientInstance);
}
