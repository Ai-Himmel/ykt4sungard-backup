package org.king.check.util;

import org.king.check.door.PersonsTaskBiz;

/**
 * .
 * User: Yiming.You
 * Date: 2010-12-19
 */
public class TransferDepartment extends Thread {
    private Long deleteTime;

    public TransferDepartment(Long deleteTime) {
        this.deleteTime = deleteTime;
        start();
    }

    public void run() {
        try {
            System.out.println("-----begin--transfer---");
            PersonsTaskBiz.transferDepartment(deleteTime);
            System.out.println("-------over---");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
