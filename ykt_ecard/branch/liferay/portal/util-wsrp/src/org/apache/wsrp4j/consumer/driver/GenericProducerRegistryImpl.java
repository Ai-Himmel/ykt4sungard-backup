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

package org.apache.wsrp4j.consumer.driver;

import java.util.Hashtable;
import java.util.Iterator;

import org.apache.wsrp4j.consumer.Producer;
import org.apache.wsrp4j.consumer.ProducerRegistry;

public abstract class GenericProducerRegistryImpl implements ProducerRegistry {

	private Hashtable producers = null;

	public GenericProducerRegistryImpl() {
		producers = new Hashtable();
	}

	/**
	 * Add a producer to the registry
	 *
	 * @param producer The producer to add
	 */
	public void addProducer(Producer producer) {
		if (producer != null) {
			producers.put(producer.getID(), producer);
		}
	}

	/**
	 * Get the producer for the given URL
	 * 
	 * @param id The ID of the producer
	 * 
	 * @return The producer with the given ID
	 **/
	public Producer getProducer(String id) {

		return (Producer) producers.get(id);
	}

	/**
	 * Get all producer in the registry
	 * 
	 * @return Iterator with all producers
	 **/
	public Iterator getAllProducers() {
		return producers.values().iterator();
	}

	/**
	 * Remove the producer with the given ID from the registry
	 * 
	 * @param id The ID of the producer
	 * 
	 * @return The producer which had been mapped to this id or 
	 *         null if no producer was found with this id
	 **/
	public Producer removeProducer(String id) {
		return (Producer) producers.remove(id);
	}

	/**
	 * Remove all producer objects from the registry
	 **/
	public void removeAllProducers() {
		producers.clear();
	}

	/**
	 * Check if a producer with the given ID exists in the registry.
	 * 
	 * @param id The ID of the producer
	 * 
	 * @return True if producer exists with this ID
	 **/
	public boolean existsProducer(String id) {
		return producers.containsKey(id);
	}
}