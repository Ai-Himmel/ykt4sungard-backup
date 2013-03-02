/**
 * Copyright (c) 2000-2008 Liferay, Inc. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package com.liferay.util;

import com.sun.imageio.plugins.gif.GIFImageReader;
import com.sun.imageio.plugins.jpeg.JPEGImageReader;
import com.sun.imageio.plugins.png.PNGImageReader;
import com.sun.media.jai.codec.ImageCodec;
import com.sun.media.jai.codec.ImageDecoder;

import java.awt.geom.AffineTransform;
import java.awt.image.AffineTransformOp;
import java.awt.image.BufferedImage;
import java.awt.image.DataBuffer;
import java.awt.image.RenderedImage;
import java.awt.image.SampleModel;

import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import java.util.Iterator;

import javax.imageio.ImageIO;
import javax.imageio.ImageReader;
import javax.imageio.stream.FileCacheImageInputStream;

import javax.media.jai.RenderedImageAdapter;

import net.jmge.gif.Gif89Encoder;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ImageUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ImageUtil {

	public static final String TYPE_BMP = "bmp";

	public static final String TYPE_GIF = "gif";

	public static final String TYPE_JPEG = "jpeg";

	public static final String TYPE_PNG = "png";

	public static final String TYPE_TIFF = "tiff";

	public static final String TYPE_NOT_AVAILABLE = "na";

	public static void encodeGIF(RenderedImage renderedImage, OutputStream out)
		throws IOException {

		Gif89Encoder encoder = new Gif89Encoder(
			getBufferedImage(renderedImage));

		encoder.encode(out);
	}

	public static void encodeWBMP(RenderedImage renderedImage, OutputStream out)
		throws InterruptedException, IOException {

		BufferedImage bufferedImage = getBufferedImage(renderedImage);

		SampleModel sampleModel = bufferedImage.getSampleModel();

		int type = sampleModel.getDataType();

		if ((bufferedImage.getType() != BufferedImage.TYPE_BYTE_BINARY) ||
			(type < DataBuffer.TYPE_BYTE) || (type > DataBuffer.TYPE_INT) ||
			(sampleModel.getNumBands() != 1) ||
			(sampleModel.getSampleSize(0) != 1)) {

			BufferedImage binaryImage = new BufferedImage(
				bufferedImage.getWidth(), bufferedImage.getHeight(),
				BufferedImage.TYPE_BYTE_BINARY);

			binaryImage.getGraphics().drawImage(bufferedImage, 0, 0, null);

			renderedImage = binaryImage;
		}

		if (!ImageIO.write(renderedImage, "wbmp", out)) {

			// See http://www.jguru.com/faq/view.jsp?EID=127723

			out.write(0);
			out.write(0);
			out.write(_toMultiByte(bufferedImage.getWidth()));
			out.write(_toMultiByte(bufferedImage.getHeight()));

			DataBuffer dataBuffer = bufferedImage.getData().getDataBuffer();

			int size = dataBuffer.getSize();

			for (int i = 0; i < size; i++) {
				out.write((byte)dataBuffer.getElem(i));
			}
		}
	}

	public static BufferedImage getBufferedImage(RenderedImage renderedImage) {
		if (renderedImage instanceof BufferedImage) {
			return (BufferedImage)renderedImage;
		}
		else {
			RenderedImageAdapter adapter = new RenderedImageAdapter(
				renderedImage);

			return adapter.getAsBufferedImage();
		}
	}

	public static ImageBag read(File file) throws IOException {
		return read(FileUtil.getBytes(file));
	}

	public static ImageBag read(byte[] bytes) throws IOException {
		RenderedImage renderedImage = null;
		String type = TYPE_NOT_AVAILABLE;

		InputStream is = null;
		FileCacheImageInputStream fcis = null;

		try {
			is = new ByteArrayInputStream(bytes);
			fcis = new FileCacheImageInputStream(is, null);

			Iterator itr = ImageIO.getImageReaders(fcis);

			while (itr.hasNext()) {
				ImageReader reader = (ImageReader)itr.next();

				if (reader instanceof GIFImageReader) {
					type = TYPE_GIF;
				}
				else if (reader instanceof JPEGImageReader) {
					type = TYPE_JPEG;
				}
				else if (reader instanceof PNGImageReader) {
					type = TYPE_PNG;
				}

				reader.dispose();
			}

			if (!type.equals(TYPE_NOT_AVAILABLE)) {
				renderedImage = ImageIO.read(fcis);
			}

			if (renderedImage == null) {
				renderedImage = _getRenderedImage("BMP", bytes);

				if (renderedImage != null) {
					type = TYPE_BMP;
				}
			}

			if (renderedImage == null) {
				renderedImage = _getRenderedImage("TIFF", bytes);

				if (renderedImage != null) {
					type = TYPE_TIFF;
				}
			}

			if (renderedImage == null) {
				renderedImage = _getRenderedImage("GIF", bytes);

				if (renderedImage != null) {
					type = TYPE_GIF;
				}
			}

			if (renderedImage == null) {
				renderedImage = _getRenderedImage("JPEG", bytes);

				if (renderedImage != null) {
					type = TYPE_JPEG;
				}
			}

			if (renderedImage == null) {
				renderedImage = _getRenderedImage("PNG", bytes);

				if (renderedImage != null) {
					type = TYPE_PNG;
				}
			}
		}
		finally {
			if (is != null) {
				try {
					is.close();
				}
				catch (IOException ioe) {
					if (_log.isWarnEnabled()) {
						_log.warn(ioe);
					}
				}
			}

			if (fcis != null) {
				try {
					fcis.close();
				}
				catch (IOException ioe) {
					if (_log.isDebugEnabled()) {
						_log.debug(ioe);
					}
				}
			}
		}

		return new ImageBag(renderedImage, type);
	}

	public static RenderedImage scale(
		RenderedImage renderedImage, double factor) {

		AffineTransformOp op = new AffineTransformOp(
			AffineTransform.getScaleInstance(factor, factor), null);

		BufferedImage bufferedImage = getBufferedImage(renderedImage);

		return op.filter(bufferedImage, null);
	}

	public static RenderedImage scale(
		RenderedImage renderedImage, int maxHeight, int maxWidth) {

		int imageHeight = renderedImage.getHeight();
		int imageWidth = renderedImage.getWidth();

		if (maxHeight == 0) {
			maxHeight = imageHeight;
		}

		if (maxWidth == 0) {
			maxWidth = imageWidth;
		}

		if ((imageHeight <= maxHeight) && (imageWidth <= maxWidth)) {
			return renderedImage;
		}

		double factor = 0.1;

		int heightDelta = imageHeight - maxHeight;
		int widthDelta = imageWidth - maxWidth;

		if (heightDelta > widthDelta) {
			factor = (double)maxHeight / imageHeight;
		}
		else {
			factor = (double)maxWidth / imageWidth;
		}

		return scale(renderedImage, factor);
	}

	private static RenderedImage _getRenderedImage(String name, byte[] bytes) {
		RenderedImage renderedImage = null;

		InputStream is = null;

		try {
			is = new ByteArrayInputStream(bytes);

			ImageDecoder decoder = ImageCodec.createImageDecoder(
				name, is, null);

			renderedImage = decoder.decodeAsRenderedImage();
		}
		catch (Exception e) {
			if (_log.isDebugEnabled()) {
				_log.debug(name + ": " + e.getMessage());
			}
		}
		finally {
			if (is != null) {
				try {
					is.close();
				}
				catch (IOException ioe) {
					if (_log.isWarnEnabled()) {
						_log.warn(ioe);
					}
				}
			}
		}

		return renderedImage;
	}

	private static byte[] _toMultiByte(int intValue) {
		int numBits = 32;
		int mask = 0x80000000;

		while (mask != 0 && (intValue & mask) == 0) {
			numBits--;
			mask >>>= 1;
		}

		int numBitsLeft = numBits;
		byte[] multiBytes = new byte[(numBitsLeft + 6) / 7];

		int maxIndex = multiBytes.length - 1;

		for (int b = 0; b <= maxIndex; b++) {
			multiBytes[b] = (byte)((intValue >>> ((maxIndex - b) * 7)) & 0x7f);

			if (b != maxIndex) {
				multiBytes[b] |= (byte)0x80;
			}
		}

		return multiBytes;
	}

	private static Log _log = LogFactory.getLog(ImageUtil.class);

}