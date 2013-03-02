/*
 * Copyright 2000-2001,2004 The Apache Software Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* 

 */

package org.apache.wsrp4j.consumer;

/**
 * <p>This interface provides a method performing Consumer URLRewriting.</p>
 *
 * @author  <a href="mailto:stefan.behl@de.ibm.com">Stefan Behl</a>
 *
 * @version 1.1
 */
public interface URLRewriter {

	/**
	 * Sets the URLGenerator to be used.
	 */
	public void setURLGenerator(URLGenerator urlGenerator);

	/**
	 * Parses the entire markup and rewrites all found URLs. The URLs to be
	 * rewritten are enclosed by the tokens "wsrp-rewrite" and "/wsrp-rewrite".
	 *
	 * @param  markup           The markup to be parsed for URLs
	 *                          to be rewritten.
	 *
	 * @return String representing markup incl. complete URLs.
	 */
	public String rewriteURLs(String markup);

}