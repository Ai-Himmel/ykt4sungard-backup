/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

package com.liferay.portal.mycaptcha;

import java.awt.Color;
import java.awt.Font;
import java.awt.image.ImageFilter;

import com.jhlabs.image.CrystalizeFilter;
import com.jhlabs.image.EmbossFilter;
import com.jhlabs.image.RippleFilter;
import com.jhlabs.image.SphereFilter;
import com.jhlabs.image.TwirlFilter;
import com.jhlabs.image.WaterFilter;
import com.jhlabs.image.WeaveFilter;
import com.octo.captcha.component.image.backgroundgenerator.UniColorBackgroundGenerator;
import com.octo.captcha.component.image.deformation.ImageDeformationByFilters;
import com.octo.captcha.component.image.fontgenerator.RandomFontGenerator;
import com.octo.captcha.component.image.textpaster.SimpleTextPaster;
import com.octo.captcha.component.image.wordtoimage.ComposedWordToImage;
import com.octo.captcha.component.image.wordtoimage.DeformedComposedWordToImage;
import com.octo.captcha.component.word.FileDictionary;
import com.octo.captcha.component.word.wordgenerator.DictionaryWordGenerator;
import com.octo.captcha.component.word.wordgenerator.WordGenerator;
import com.octo.captcha.engine.image.ListImageCaptchaEngine;
import com.octo.captcha.image.gimpy.GimpyFactory;

/**
 * <a href="MultipleGimpyEngine.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.5 $
 *
 */
public class MyImageCaptchaEngine extends ListImageCaptchaEngine {
	protected void buildInitialFactories() {
//		EmbossFilter emboss = new EmbossFilter();
		SphereFilter sphere = new SphereFilter();
		RippleFilter rippleBack = new RippleFilter();
		RippleFilter ripple = new RippleFilter();
		TwirlFilter twirl = new TwirlFilter();
		WaterFilter water = new WaterFilter();
		WeaveFilter weaves = new WeaveFilter();
		CrystalizeFilter crystal = new CrystalizeFilter();
		ripple.setWaveType(3);
		ripple.setXAmplitude(3.0);
		ripple.setYAmplitude(3.0);
		ripple.setXWavelength(20.0);
		ripple.setYWavelength(10.0);
		ripple.setEdgeAction(1);
		rippleBack.setWaveType(3);
		rippleBack.setXAmplitude(5.0);
		rippleBack.setYAmplitude(5.0);
		rippleBack.setXWavelength(10.0);
		rippleBack.setYWavelength(10.0);
		rippleBack.setEdgeAction(1);
		water.setAmplitude(1.0);
		water.setAntialias(true);
		water.setWavelength(20.0);
		twirl.setAngle(0.0);
		sphere.setRefractionIndex(1.0);
		weaves.setUseImageColors(true);
		crystal.setScale(0.5);
		crystal.setGridType(0);
		crystal.setFadeEdges(false);
		crystal.setEdgeThickness(0.20000000298023224);
		crystal.setRandomness(0.10000000149011612);
		com.octo.captcha.component.image.deformation.ImageDeformation rippleDef
		    = new ImageDeformationByFilters(new ImageFilter[] { ripple });
//		com.octo.captcha.component.image.deformation.ImageDeformation waterDef
//		    = new ImageDeformationByFilters(new ImageFilter[] { water });
//		com.octo.captcha.component.image.deformation.ImageDeformation embossDef
//		    = new ImageDeformationByFilters(new ImageFilter[] { emboss });
		com.octo.captcha.component.image.deformation.ImageDeformation rippleDefBack
		    = new ImageDeformationByFilters(new ImageFilter[] { rippleBack });
		com.octo.captcha.component.image.deformation.ImageDeformation cristalDef
		    = new ImageDeformationByFilters(new ImageFilter[] { crystal });
//		com.octo.captcha.component.image.deformation.ImageDeformation weavesDef
//		    = new ImageDeformationByFilters(new ImageFilter[] { weaves });
//		com.octo.captcha.component.image.deformation.ImageDeformation none
//		    = new ImageDeformationByFilters(null);
		WordGenerator words
		    = new DictionaryWordGenerator(new FileDictionary("toddlist"));
		com.octo.captcha.component.image.textpaster.TextPaster paster
		    = new SimpleTextPaster(new Integer(4), new Integer(7), Color.BLACK);
		com.octo.captcha.component.image.backgroundgenerator.BackgroundGenerator back
		    = new UniColorBackgroundGenerator(new Integer(200),
						      new Integer(100), Color.white);
		Font[] fontsList = new Font[] {
	               new Font("Arial", 0, 10),
	               new Font("Tahoma", 0, 10),
	               new Font("Verdana", 0, 10),
	            };
	         
		com.octo.captcha.component.image.fontgenerator.FontGenerator font
	    =new RandomFontGenerator(new Integer(40), new Integer(50), fontsList);
//
//		com.octo.captcha.component.image.fontgenerator.FontGenerator font
//		    = new RandomFontGenerator(new Integer(60),
//							       new Integer(50));
		com.octo.captcha.component.image.wordtoimage.WordToImage word2image
		    = new ComposedWordToImage(font, back, paster);
		//addFactory(new GimpyFactory(words, word2image));
//		word2image
//		    = new DeformedComposedWordToImage(font, back, paster, rippleDef,
//						      waterDef, embossDef);
//		addFactory(new GimpyFactory(words, word2image));		
		word2image = new DeformedComposedWordToImage(font, back, paster,
							     rippleDefBack, cristalDef,
							     rippleDef);
		addFactory(new GimpyFactory(words, word2image));
//		word2image
//		    = new DeformedComposedWordToImage(font, back, paster,
//						      rippleDefBack, none, weavesDef);
//		addFactory(new GimpyFactory(words, word2image));
	}

}