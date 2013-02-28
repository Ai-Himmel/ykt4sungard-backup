package org.king.framework.web.filter.compression;

import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.zip.GZIPOutputStream;

public class CompressionResponseStream extends ServletOutputStream {
    protected GZIPOutputStream gzipstream = null;

    protected HttpServletResponse response = null;

    protected ServletOutputStream output = null;

    protected byte[] buffer = null;

    protected boolean closed = false;

    protected int bufferCount = 0;

    protected int compressionThreshold = 0;

    protected int length = -1;

    private int debug = 0;

    public CompressionResponseStream(HttpServletResponse response)
            throws IOException {
        closed = false;
        this.response = response;
        output = response.getOutputStream();
    }

    public void setDebugLevel(int debug) {
        this.debug = debug;
    }

    public void close()
            throws IOException {
        if (debug > 1) {
            System.out.println("close() @ CompressionResponseStream");
        }

        if (closed) {
            throw new IOException("This output stream has already been closed");
        }

        if (gzipstream != null) {
            flushToGZip();
            gzipstream.close();
            gzipstream = null;
        } else if (bufferCount > 0) {
            if (debug > 2) {
                System.out.print("output.write(");
                System.out.write(buffer, 0, bufferCount);
                System.out.println(")");
            }

            output.write(buffer, 0, bufferCount);
            bufferCount = 0;
        }

        output.close();
        closed = true;
    }

    public boolean closed() {
        return closed;
    }

    public void flush()
            throws IOException {
        if (debug > 1) {
            System.out.println("flush() @ CompressionResponseStream");
        }

        if (closed) {
            throw new IOException("Cannot flush a closed output stream");
        }

        if (gzipstream != null)
            gzipstream.flush();
    }

    public void flushToGZip()
            throws IOException {
        if (debug > 1) {
            System.out.println("flushToGZip() @ CompressionResponseStream");
        }

        if (bufferCount > 0) {
            if (debug > 1) {
                System.out.println("flushing out to GZipStream, bufferCount = " + bufferCount);
            }

            writeToGZip(buffer, 0, bufferCount);
            bufferCount = 0;
        }
    }

    public void write(int b)
            throws IOException {
        if (debug > 1) {
            System.out.println("write " + b + " in CompressionResponseStream ");
        }

        if (closed) {
            throw new IOException("Cannot write to a closed output stream");
        }

        if (bufferCount >= buffer.length) {
            flushToGZip();
        }

        buffer[(bufferCount++)] = (byte) b;
    }

    public void write(byte[] b)
            throws IOException {
        write(b, 0, b.length);
    }

    public void write(byte[] b, int off, int len)
            throws IOException {
        if (debug > 1) {
            System.out.println("write, bufferCount = " + bufferCount + " len = " + len + " off = " + off);
        }

        if (debug > 2) {
            System.out.print("write(");
            System.out.write(b, off, len);
            System.out.println(")");
        }

        if (closed) {
            throw new IOException("Cannot write to a closed output stream");
        }

        if (len == 0) {
            return;
        }

        if (len <= buffer.length - bufferCount) {
            System.arraycopy(b, off, buffer, bufferCount, len);
            bufferCount += len;

            return;
        }

        flushToGZip();

        if (len <= buffer.length - bufferCount) {
            System.arraycopy(b, off, buffer, bufferCount, len);
            bufferCount += len;

            return;
        }

        writeToGZip(b, off, len);
    }

    public void writeToGZip(byte[] b, int off, int len)
            throws IOException {
        if (debug > 1) {
            System.out.println("writeToGZip, len = " + len);
        }

        if (debug > 2) {
            System.out.print("writeToGZip(");
            System.out.write(b, off, len);
            System.out.println(")");
        }

        if (gzipstream == null) {
            if (debug > 1) {
                System.out.println("new GZIPOutputStream");
            }

            response.addHeader("Content-Encoding", "gzip");
            gzipstream = new GZIPOutputStream(output);
        }

        gzipstream.write(b, off, len);
    }

    protected void setBuffer(int threshold) {
        compressionThreshold = threshold;
        buffer = new byte[compressionThreshold];

        if (debug > 1)
            System.out.println("buffer is set to " + compressionThreshold);
    }
}