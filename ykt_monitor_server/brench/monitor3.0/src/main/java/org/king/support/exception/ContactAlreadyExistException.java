package org.king.support.exception;

import org.king.framework.exception.BaseException;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-9
 */
public class ContactAlreadyExistException extends BaseException {
    /**
     *
     */
    public ContactAlreadyExistException() {
        super();
    }

    /**
     * @param s
     */
    public ContactAlreadyExistException(String s) {
        super(s);
    }

    /**
     * @param s
     * @param e
     */
    public ContactAlreadyExistException(String s, Throwable e) {
        super(s, e);
    }

    /**
     * @param e
     */
    public ContactAlreadyExistException(Throwable e) {
        super(e);
    }
}
