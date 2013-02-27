/* 
 * $Header: /home/cvs/jakarta-commons/dbutils/src/java/org/apache/commons/dbutils/wrappers/SqlNullCheckedResultSet.java,v 1.3 2003/11/09 18:18:04 dgraham Exp $
 * $Revision: 1.3 $
 * $Date: 2003/11/09 18:18:04 $
 * 
 * ====================================================================
 * 
 * The Apache Software License, Version 1.1
 *
 * Copyright (c) 2003 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution, if
 *    any, must include the following acknowledgement:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgement may appear in the software itself,
 *    if and wherever such third-party acknowledgements normally appear.
 *
 * 4. The names "The Jakarta Project", "Commons", and "Apache Software
 *    Foundation" must not be used to endorse or promote products derived
 *    from this software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache"
 *    nor may "Apache" appear in their names without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

package org.apache.commons.dbutils.wrappers;

import java.io.InputStream;
import java.io.Reader;
import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.math.BigDecimal;
import java.net.URL;
import java.sql.Blob;
import java.sql.Clob;
import java.sql.Date;
import java.sql.Ref;
import java.sql.ResultSet;
import java.sql.Time;
import java.sql.Timestamp;
import java.util.HashMap;
import java.util.Map;

import org.apache.commons.dbutils.ProxyFactory;

/**
 * Decorates a <code>ResultSet</code> with checks for a SQL NULL value on each
 * <code>getXXX</code> method. If a column value obtained by a 
 * <code>getXXX</code> method is not SQL NULL, the column value is returned. If
 * the column value is SQL null, an alternate value is returned. The alternate
 * value defaults to the Java <code>null</code> value, which can be overridden
 * for instances of the class.
 * 
 * <p>
 * Usage example:
 * <blockquote>
 * <pre>
 * Connection conn = // somehow get a connection
 * Statement stmt = conn.createStatement();
 * ResultSet rs = stmt.executeQuery("SELECT col1, col2 FROM table1");
 * 
 * // Wrap the result set for SQL NULL checking
 * SqlNullCheckedResultSet wrapper = new SqlNullCheckedResultSet(rs);
 * wrapper.setNullString("---N/A---"); // Set null string
 * wrapper.setNullInt(-999); // Set null integer
 * rs = ProxyFactory.instance().createResultSet(wrapper);
 * 
 * while (rs.next()) {
 *     // If col1 is SQL NULL, value returned will be "---N/A---"
 *     String col1 = rs.getString("col1");
 *     // If col2 is SQL NULL, value returned will be -999
 *     int col2 = rs.getInt("col2");
 * }
 * rs.close();
 * </pre>
 * </blockquote>
 * </p>
 *
 * @author  <a href="stevencaswell@apache.org">Steven Caswell</a>
 * @author David Graham
 * @version $Id: SqlNullCheckedResultSet.java,v 1.3 2003/11/09 18:18:04 dgraham Exp $
 */
public class SqlNullCheckedResultSet implements InvocationHandler {

    /**
     * Maps normal method names (ie. "getBigDecimal") to the corresponding null
     * Method object (ie. getNullBigDecimal).
     */
    private static final Map nullMethods = new HashMap();

    static {
        Method[] methods = SqlNullCheckedResultSet.class.getMethods();
        for (int i = 0; i < methods.length; i++) {
            String methodName = methods[i].getName();

            if (methodName.startsWith("getNull")) {
                String normalName = "get" + methodName.substring(7);
                nullMethods.put(normalName, methods[i]);
            }
        }
    }

    /**
     * The factory to create proxies with.
     */
    private static final ProxyFactory factory = ProxyFactory.instance();

    /**
     * Wraps the <code>ResultSet</code> in an instance of this class.  This is
     * equivalent to:
     * <pre>
     * ProxyFactory.instance().createResultSet(new SqlNullCheckedResultSet(rs));
     * </pre>
     * 
     * @param rs The <code>ResultSet</code> to wrap.
     */
    public static ResultSet wrap(ResultSet rs) {
        return factory.createResultSet(new SqlNullCheckedResultSet(rs));
    }

    private InputStream nullAsciiStream = null;
    private BigDecimal nullBigDecimal = null;
    private InputStream nullBinaryStream = null;
    private Blob nullBlob = null;
    private boolean nullBoolean = false;
    private byte nullByte = 0;
    private byte[] nullBytes = null;
    private Reader nullCharacterStream = null;
    private Clob nullClob = null;
    private Date nullDate = null;
    private double nullDouble = 0.0;
    private float nullFloat = 0.0f;
    private int nullInt = 0;
    private long nullLong = 0;
    private Object nullObject = null;
    private Ref nullRef = null;
    private short nullShort = 0;
    private String nullString = null;
    private Time nullTime = null;
    private Timestamp nullTimestamp = null;
    private URL nullURL = null;

    /**
     * The wrapped result. 
     */
    private final ResultSet rs;

    /**
     * Constructs a new instance of
     * <code>SqlNullCheckedResultSet</code>
     * to wrap the specified <code>ResultSet</code>.
     */
    public SqlNullCheckedResultSet(ResultSet rs) {
        super();
        this.rs = rs;
    }

    /**
     * Returns the value when a SQL null is encountered as the result of
     * invoking a <code>getAsciiStream</code> method.
     *
     * @return the value
     */
    public InputStream getNullAsciiStream() {
        return this.nullAsciiStream;
    }

    /**
     * Returns the value when a SQL null is encountered as the result of
     * invoking a <code>getBigDecimal</code> method.
     *
     * @return the value
     */
    public BigDecimal getNullBigDecimal() {
        return this.nullBigDecimal;
    }

    /**
     * Returns the value when a SQL null is encountered as the result of
     * invoking a <code>getBinaryStream</code> method.
     *
     * @return the value
     */
    public InputStream getNullBinaryStream() {
        return this.nullBinaryStream;
    }

    /**
     * Returns the value when a SQL null is encountered as the result of
     * invoking a <code>getBlob</code> method.
     *
     * @return the value
     */
    public Blob getNullBlob() {
        return this.nullBlob;
    }

    /**
     * Returns the value when a SQL null is encountered as the result of
     * invoking a <code>getBoolean</code> method.
     *
     * @return the value
     */
    public boolean getNullBoolean() {
        return this.nullBoolean;
    }

    /**
     * Returns the value when a SQL null is encountered as the result of
     * invoking a <code>getByte</code> method.
     *
     * @return the value
     */
    public byte getNullByte() {
        return this.nullByte;
    }

    /**
     * Returns the value when a SQL null is encountered as the result of
     * invoking a <code>getBytes</code> method.
     *
     * @return the value
     */
    public byte[] getNullBytes() {
        return this.nullBytes;
    }

    /**
     * Returns the value when a SQL null is encountered as the result of
     * invoking a <code>getCharacterStream</code> method.
     *
     * @return the value
     */
    public Reader getNullCharacterStream() {
        return this.nullCharacterStream;
    }

    /**
     * Returns the value when a SQL null is encountered as the result of
     * invoking a <code>getClob</code> method.
     *
     * @return the value
     */
    public Clob getNullClob() {
        return this.nullClob;
    }

    /**
     * Returns the value when a SQL null is encountered as the result of
     * invoking a <code>getDate</code> method.
     *
     * @return the value
     */
    public Date getNullDate() {
        return this.nullDate;
    }

    /**
     * Returns the value when a SQL null is encountered as the result of
     * invoking a <code>getDouble</code> method.
     *
     * @return the value
     */
    public double getNullDouble() {
        return this.nullDouble;
    }

    /**
     * Returns the value when a SQL null is encountered as the result of
     * invoking a <code>getFloat</code> method.
     *
     * @return the value
     */
    public float getNullFloat() {
        return this.nullFloat;
    }

    /**
     * Returns the value when a SQL null is encountered as the result of
     * invoking a <code>getInt</code> method.
     *
     * @return the value
     */
    public int getNullInt() {
        return this.nullInt;
    }

    /**
     * Returns the value when a SQL null is encountered as the result of
     * invoking a <code>getLong</code> method.
     *
     * @return the value
     */
    public long getNullLong() {
        return this.nullLong;
    }

    /**
     * Returns the value when a SQL null is encountered as the result of
     * invoking a <code>getObject</code> method.
     *
     * @return the value
     */
    public Object getNullObject() {
        return this.nullObject;
    }

    /**
     * Returns the value when a SQL null is encountered as the result of
     * invoking a <code>getRef</code> method.
     *
     * @return the value
     */
    public Ref getNullRef() {
        return this.nullRef;
    }

    /**
     * Returns the value when a SQL null is encountered as the result of
     * invoking a <code>getShort</code> method.
     *
     * @return the value
     */
    public short getNullShort() {
        return this.nullShort;
    }

    /**
     * Returns the value when a SQL null is encountered as the result of
     * invoking a <code>getString</code> method.
     *
     * @return the value
     */
    public String getNullString() {
        return this.nullString;
    }

    /**
     * Returns the value when a SQL null is encountered as the result of
     * invoking a <code>getTime</code> method.
     *
     * @return the value
     */
    public Time getNullTime() {
        return this.nullTime;
    }

    /**
     * Returns the value when a SQL null is encountered as the result of
     * invoking a <code>getTimestamp</code> method.
     *
     * @return the value
     */
    public Timestamp getNullTimestamp() {
        return this.nullTimestamp;
    }

    /**
     * Returns the value when a SQL null is encountered as the result of
     * invoking a <code>getURL</code> method.
     *
     * @return the value
     */
    public URL getNullURL() {
        return this.nullURL;
    }

    /**
     * Intercepts calls to <code>get*</code> methods and calls the appropriate
     * <code>getNull*</code> method if the <code>ResultSet</code> returned
     * <code>null</code>.
     * 
     * @throws Throwable
     * @see java.lang.reflect.InvocationHandler#invoke(java.lang.Object, java.lang.reflect.Method, java.lang.Object[])
     */
    public Object invoke(Object proxy, Method method, Object[] args)
        throws Throwable {

        Object result = method.invoke(this.rs, args);

        Method nullMethod = (Method) nullMethods.get(method.getName());

        // Check nullMethod != null first so that we don't call wasNull()
        // before a true getter method was invoked on the ResultSet.
        return (nullMethod != null && this.rs.wasNull())
            ? nullMethod.invoke(this, null)
            : result;
    }

    /**
     * Sets the value to return when a SQL null is encountered as the result of
     * invoking a <code>getAsciiStream</code> method.
     *
     * @param nullAsciiStream the value
     */
    public void setNullAsciiStream(InputStream nullAsciiStream) {
        this.nullAsciiStream = nullAsciiStream;
    }

    /**
     * Sets the value to return when a SQL null is encountered as the result of
     * invoking a <code>getBigDecimal</code> method.
     *
     * @param nullBigDecimal the value
     */
    public void setNullBigDecimal(BigDecimal nullBigDecimal) {
        this.nullBigDecimal = nullBigDecimal;
    }

    /**
     * Sets the value to return when a SQL null is encountered as the result of
     * invoking a <code>getBinaryStream</code> method.
     *
     * @param nullBinaryStream the value
     */
    public void setNullBinaryStream(InputStream nullBinaryStream) {
        this.nullBinaryStream = nullBinaryStream;
    }

    /**
     * Sets the value to return when a SQL null is encountered as the result of
     * invoking a <code>getBlob</code> method.
     *
     * @param nullBlob the value
     */
    public void setNullBlob(Blob nullBlob) {
        this.nullBlob = nullBlob;
    }

    /**
     * Sets the value to return when a SQL null is encountered as the result of
     * invoking a <code>getBoolean</code> method.
     *
     * @param nullBoolean the value
     */
    public void setNullBoolean(boolean nullBoolean) {
        this.nullBoolean = nullBoolean;
    }

    /**
     * Sets the value to return when a SQL null is encountered as the result of
     * invoking a <code>getByte</code> method.
     *
     * @param nullByte the value
     */
    public void setNullByte(byte nullByte) {
        this.nullByte = nullByte;
    }

    /**
     * Sets the value to return when a SQL null is encountered as the result of
     * invoking a <code>getBytes</code> method.
     *
     * @param nullBytes the value
     */
    public void setNullBytes(byte[] nullBytes) {
        this.nullBytes = nullBytes;
    }

    /**
     * Sets the value to return when a SQL null is encountered as the result of
     * invoking a <code>getCharacterStream</code> method.
     *
     * @param nullCharacterStream the value
     */
    public void setNullCharacterStream(Reader nullCharacterStream) {
        this.nullCharacterStream = nullCharacterStream;
    }

    /**
     * Sets the value to return when a SQL null is encountered as the result of
     * invoking a <code>getClob</code> method.
     *
     * @param nullClob the value
     */
    public void setNullClob(Clob nullClob) {
        this.nullClob = nullClob;
    }

    /**
     * Sets the value to return when a SQL null is encountered as the result of
     * invoking a <code>getDate</code> method.
     *
     * @param nullDate the value
     */
    public void setNullDate(Date nullDate) {
        this.nullDate = nullDate;
    }

    /**
     * Sets the value to return when a SQL null is encountered as the result of
     * invoking a <code>getDouble</code> method.
     *
     * @param nullDouble the value
     */
    public void setNullDouble(double nullDouble) {
        this.nullDouble = nullDouble;
    }

    /**
     * Sets the value to return when a SQL null is encountered as the result of
     * invoking a <code>getFloat</code> method.
     *
     * @param nullFloat the value
     */
    public void setNullFloat(float nullFloat) {
        this.nullFloat = nullFloat;
    }

    /**
     * Sets the value to return when a SQL null is encountered as the result of
     * invoking a <code>getInt</code> method.
     *
     * @param nullInt the value
     */
    public void setNullInt(int nullInt) {
        this.nullInt = nullInt;
    }

    /**
     * Sets the value to return when a SQL null is encountered as the result of
     * invoking a <code>getLong</code> method.
     *
     * @param nullLong the value
     */
    public void setNullLong(long nullLong) {
        this.nullLong = nullLong;
    }

    /**
     * Sets the value to return when a SQL null is encountered as the result of
     * invoking a <code>getObject</code> method.
     *
     * @param nullObject the value
     */
    public void setNullObject(Object nullObject) {
        this.nullObject = nullObject;
    }

    /**
     * Sets the value to return when a SQL null is encountered as the result of
     * invoking a <code>getRef</code> method.
     *
     * @param nullRef the value
     */
    public void setNullRef(Ref nullRef) {
        this.nullRef = nullRef;
    }

    /**
     * Sets the value to return when a SQL null is encountered as the result of
     * invoking a <code>getShort</code> method.
     *
     * @param nullShort the value
     */
    public void setNullShort(short nullShort) {
        this.nullShort = nullShort;
    }

    /**
     * Sets the value to return when a SQL null is encountered as the result of
     * invoking a <code>getString</code> method.
     *
     * @param nullString the value
     */
    public void setNullString(String nullString) {
        this.nullString = nullString;
    }

    /**
     * Sets the value to return when a SQL null is encountered as the result of
     * invoking a <code>getTime</code> method.
     *
     * @param nullTime the value
     */
    public void setNullTime(Time nullTime) {
        this.nullTime = nullTime;
    }

    /**
     * Sets the value to return when a SQL null is encountered as the result of
     * invoking a <code>getTimestamp</code> method.
     *
     * @param nullTimestamp the value
     */
    public void setNullTimestamp(Timestamp nullTimestamp) {
        this.nullTimestamp = nullTimestamp;
    }

    /**
     * Sets the value to return when a SQL null is encountered as the result of
     * invoking a <code>getURL</code> method.
     *
     * @param nullURL the value
     */
    public void setNullURL(URL nullURL) {
        this.nullURL = nullURL;
    }

}
