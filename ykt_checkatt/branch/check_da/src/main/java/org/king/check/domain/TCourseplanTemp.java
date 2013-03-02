package org.king.check.domain;

/**
 * .
 * User: Yiming.You
 * Date: 2011-3-3
 */
public class TCourseplanTemp extends AbstractTCourseplanTemp {
    public TCourseplanTemp() {
    }

    public TCourseplanTemp(Long id, String term, String faculty, String area, String building, String room, String course, String stuempno, String custname, String deptname, String deptcode, String week, String beginWeek, String endWeek, String beginClass, String endClass, String ischeck, String isopen, String remark, String status, String checkInfo, String syncDate) {
        super(id, term, faculty, area, building, room, course, stuempno, custname, deptname, deptcode, week, beginWeek, endWeek, beginClass, endClass, ischeck, isopen, remark, status, checkInfo, syncDate);
    }
}
