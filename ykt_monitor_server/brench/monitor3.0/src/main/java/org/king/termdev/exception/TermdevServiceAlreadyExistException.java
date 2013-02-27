package org.king.termdev.exception;

import org.king.framework.exception.BaseException;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-10
 */
public class TermdevServiceAlreadyExistException extends BaseException {
    /**
     *
     */
    public TermdevServiceAlreadyExistException() {
        super();
    }

    /**
     * @param s
     */
    public TermdevServiceAlreadyExistException(String s) {
        super(s);
    }

    /**
     * @param s
     * @param e
     */
    public TermdevServiceAlreadyExistException(String s, Throwable e) {
        super(s, e);
    }

    /**
     * @param e
     */
    public TermdevServiceAlreadyExistException(Throwable e) {
        super(e);
    }
}
