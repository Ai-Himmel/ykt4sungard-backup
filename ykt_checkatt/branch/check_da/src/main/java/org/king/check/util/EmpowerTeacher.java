package org.king.check.util;

import org.king.check.door.PersonsTaskBiz;

/**
 * .
 * User: Yiming.You
 * Date: 2010-12-22
 */
public class EmpowerTeacher extends Thread {
    public EmpowerTeacher() {
        start();
    }

    @Override
    public void run() {
        try {
            PersonsTaskBiz.empowerTeacher();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
