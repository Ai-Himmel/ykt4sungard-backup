package org.king.check.dao;

import org.king.check.domain.TCourseplanTemp;
import org.king.framework.dao.MyQuery;

import java.io.Serializable;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2011-3-4
 */
public interface CourseplanTempDAO {
    public void save(TCourseplanTemp entiry);

    public void update(TCourseplanTemp entiry);

    public TCourseplanTemp get(Serializable id);

    public List find(String query);

    public List find(MyQuery myQuery);

    public void delete(TCourseplanTemp entity);
}
