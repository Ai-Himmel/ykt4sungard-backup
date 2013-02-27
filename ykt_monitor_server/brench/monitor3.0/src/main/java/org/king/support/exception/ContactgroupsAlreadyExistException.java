package org.king.support.exception;

import org.king.framework.exception.BaseException;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-28
 */
public class ContactgroupsAlreadyExistException extends BaseException {
    /**
     *
     */
    public ContactgroupsAlreadyExistException() {
        super();
    }

    /**
     * @param s
     */
    public ContactgroupsAlreadyExistException(String s) {
        super(s);
    }

    /**
     * @param s
     * @param e
     */
    public ContactgroupsAlreadyExistException(String s, Throwable e) {
        super(s, e);
    }

    /**
     * @param e
     */
    public ContactgroupsAlreadyExistException(Throwable e) {
        super(e);
    }
}
