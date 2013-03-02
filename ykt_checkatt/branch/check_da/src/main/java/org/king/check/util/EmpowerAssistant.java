package org.king.check.util;

import org.king.check.door.PersonsTaskBiz;

/**
 * .
 * User: Yiming.You
 * Date: 2010-12-22
 */
public class EmpowerAssistant extends Thread {
    public EmpowerAssistant() {
        start();
    }

    @Override
    public void run() {
        try {
            PersonsTaskBiz.empowerAssistant();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
