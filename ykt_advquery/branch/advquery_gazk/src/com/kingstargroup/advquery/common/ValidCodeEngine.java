/**
 * 
 */
package com.kingstargroup.advquery.common;

import java.awt.Color;
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
import com.octo.captcha.component.wordgenerator.DictionaryWordGenerator;
import com.octo.captcha.component.wordgenerator.FileDictionnary;
import com.octo.captcha.engine.image.ListImageCaptchaEngine;
import com.octo.captcha.image.gimpy.GimpyFactory;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: ValidCodeEngine.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-11-14  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class ValidCodeEngine extends ListImageCaptchaEngine {

	protected void buildInitialFactories() {
		EmbossFilter emboss = new EmbossFilter();
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
		com.octo.captcha.component.image.deformation.ImageDeformation waterDef
		    = new ImageDeformationByFilters(new ImageFilter[] { water });
		com.octo.captcha.component.image.deformation.ImageDeformation embossDef
		    = new ImageDeformationByFilters(new ImageFilter[] { emboss });
		com.octo.captcha.component.image.deformation.ImageDeformation rippleDefBack
		    = new ImageDeformationByFilters(new ImageFilter[] { rippleBack });
		com.octo.captcha.component.image.deformation.ImageDeformation cristalDef
		    = new ImageDeformationByFilters(new ImageFilter[] { crystal });
		com.octo.captcha.component.image.deformation.ImageDeformation weavesDef
		    = new ImageDeformationByFilters(new ImageFilter[] { weaves });
		com.octo.captcha.component.image.deformation.ImageDeformation none
		    = new ImageDeformationByFilters(null);
		com.octo.captcha.component.wordgenerator.WordGenerator words
		    = new DictionaryWordGenerator(new FileDictionnary("toddlist"));
		com.octo.captcha.component.image.textpaster.TextPaster paster
		    = new SimpleTextPaster(new Integer(4), new Integer(7), Color.BLACK);
		com.octo.captcha.component.image.backgroundgenerator.BackgroundGenerator back
		    = new UniColorBackgroundGenerator(new Integer(200),
						      new Integer(100), Color.white);
		com.octo.captcha.component.image.fontgenerator.FontGenerator font
		    = new RandomFontGenerator(new Integer(45),
							       new Integer(45));
		com.octo.captcha.component.image.wordtoimage.WordToImage word2image
		    = new ComposedWordToImage(font, back, paster);
		//addFactory(new GimpyFactory(words, word2image));
		word2image
		    = new DeformedComposedWordToImage(font, back, paster, rippleDef,
						      waterDef, embossDef);
		//addFactory(new GimpyFactory(words, word2image));		
		word2image = new DeformedComposedWordToImage(font, back, paster,
							     rippleDefBack, cristalDef,
							     rippleDef);
		addFactory(new GimpyFactory(words, word2image));
		word2image
		    = new DeformedComposedWordToImage(font, back, paster,
						      rippleDefBack, none, weavesDef);
		//addFactory(new GimpyFactory(words, word2image));
	}
}
