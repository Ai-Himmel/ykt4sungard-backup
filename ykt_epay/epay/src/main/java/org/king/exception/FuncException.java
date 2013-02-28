package org.king.exception;

/**
 * .
 * User: Yiming.You
 * Date: 2011-10-26
 */
public class FuncException extends Exception {
    public FuncException() {
    }

    public FuncException(String message) {
        super(message);
    }

    public FuncException(String message, Throwable cause) {
        super(message, cause);
    }

    public FuncException(Throwable cause) {
        super(cause);
    }
}
