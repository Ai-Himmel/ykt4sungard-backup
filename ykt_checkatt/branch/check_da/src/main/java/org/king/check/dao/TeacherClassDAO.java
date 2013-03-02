package org.king.check.dao;

import org.king.check.common.ec.DBPageLimit;
import org.king.check.domain.TTeacherClass;
import org.king.framework.dao.MyQuery;

import java.io.Serializable;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-12-17
 */
public interface TeacherClassDAO {
    public List find(MyQuery myQuery);

    public List find(String query);

    public List getAll();

    public void update(TTeacherClass transientInstance);

    public void delete(TTeacherClass transientInstance);

    public void save(TTeacherClass transientInstance);

    public TTeacherClass get(Integer custid, String deptId);

    public TTeacherClass get(String stuempno,String deptId);

    public TTeacherClass get(Serializable id);

    public void findTeacherClassByPage(DBPageLimit page, MyQuery myQuery);
}
