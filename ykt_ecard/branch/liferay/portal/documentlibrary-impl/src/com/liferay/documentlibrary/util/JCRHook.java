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

package com.liferay.documentlibrary.util;

import com.liferay.documentlibrary.DuplicateDirectoryException;
import com.liferay.documentlibrary.DuplicateFileException;
import com.liferay.documentlibrary.NoSuchDirectoryException;
import com.liferay.documentlibrary.NoSuchFileException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.jcr.JCRConstants;
import com.liferay.portal.jcr.JCRFactory;
import com.liferay.portal.jcr.JCRFactoryUtil;
import com.liferay.portal.kernel.search.SearchException;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.lucene.LuceneUtil;

import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.InputStream;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;

import javax.jcr.Node;
import javax.jcr.NodeIterator;
import javax.jcr.PathNotFoundException;
import javax.jcr.Property;
import javax.jcr.RepositoryException;
import javax.jcr.Session;
import javax.jcr.version.Version;
import javax.jcr.version.VersionHistory;
import javax.jcr.version.VersionIterator;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.lucene.document.Document;
import org.apache.lucene.index.IndexWriter;

/**
 * <a href="JCRHook.java.html"><b><i>View Source</i></b></a>
 *
 * @author Michael Young
 * @author Brian Wing Shun Chan
 *
 */
public class JCRHook extends BaseHook {

	public void addDirectory(long companyId, long repositoryId, String dirName)
		throws PortalException, SystemException {

		Session session = null;

		try {
			session = JCRFactoryUtil.createSession();

			Node rootNode = getRootNode(session, companyId);
			Node repositoryNode = getFolderNode(rootNode, repositoryId);

			if (repositoryNode.hasNode(dirName)) {
				throw new DuplicateDirectoryException(dirName);
			}
			else {
				String[] dirNameArray = StringUtil.split(dirName, "/");

				Node dirNode = repositoryNode;

				for (int i = 0; i < dirNameArray.length; i++) {
					if (Validator.isNotNull(dirNameArray[i])) {
						if (dirNode.hasNode(dirNameArray[i])) {
							dirNode = dirNode.getNode(dirNameArray[i]);
						}
						else {
							dirNode = dirNode.addNode(
								dirNameArray[i], JCRConstants.NT_FOLDER);
						}
					}
				}

				session.save();
			}
		}
		catch (RepositoryException re) {
			throw new SystemException(re);
		}
		finally {
			if (session != null) {
				session.logout();
			}
		}
	}

	public void addFile(
			long companyId, String portletId, long groupId, long repositoryId,
			String fileName, String properties, String[] tagsEntries,
			InputStream is)
		throws PortalException, SystemException {

		Session session = null;

		try {
			session = JCRFactoryUtil.createSession();

			Node rootNode = getRootNode(session, companyId);
			Node repositoryNode = getFolderNode(rootNode, repositoryId);

			if (repositoryNode.hasNode(fileName)) {
				throw new DuplicateFileException(fileName);
			}
			else {
				Node fileNode = repositoryNode.addNode(
					fileName, JCRConstants.NT_FILE);

				Node contentNode = fileNode.addNode(
					JCRConstants.JCR_CONTENT, JCRConstants.NT_RESOURCE);

				contentNode.addMixin(JCRConstants.MIX_VERSIONABLE);
				contentNode.setProperty(
					JCRConstants.JCR_MIME_TYPE, "text/plain");
				contentNode.setProperty(JCRConstants.JCR_DATA, is);
				contentNode.setProperty(
					JCRConstants.JCR_LAST_MODIFIED, Calendar.getInstance());

				session.save();

				Version version = contentNode.checkin();

				contentNode.getVersionHistory().addVersionLabel(
					version.getName(), String.valueOf(DEFAULT_VERSION), false);

				Indexer.addFile(
					companyId, portletId, groupId, repositoryId, fileName,
					properties, tagsEntries);
			}
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}
		catch (RepositoryException re) {
			throw new SystemException(re);
		}
		finally {
			if (session != null) {
				session.logout();
			}
		}
	}

	public void checkRoot(long companyId) throws SystemException {
		Session session = null;

		try {
			session = JCRFactoryUtil.createSession();

			getRootNode(session, companyId);

			session.save();
		}
		catch (RepositoryException re) {
			throw new SystemException(re);
		}
		finally {
			if (session != null) {
				session.logout();
			}
		}
	}

	public void deleteDirectory(
			long companyId, String portletId, long repositoryId, String dirName)
		throws PortalException, SystemException {

		Session session = null;

		try {
			session = JCRFactoryUtil.createSession();

			Node rootNode = getRootNode(session, companyId);
			Node repositoryNode = getFolderNode(rootNode, repositoryId);
			Node dirNode = repositoryNode.getNode(dirName);

			deleteDirectory(companyId, portletId, repositoryId, dirNode);

			dirNode.remove();

			session.save();
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}
		catch (PathNotFoundException pnfe) {
			throw new NoSuchDirectoryException(dirName);
		}
		catch (RepositoryException e) {
			throw new PortalException(e);
		}
		finally {
			if (session != null) {
				session.logout();
			}
		}
	}

	public void deleteFile(
			long companyId, String portletId, long repositoryId,
			String fileName)
		throws PortalException, SystemException {

		Session session = null;

		// A bug in Jackrabbit requires us to create a dummy node and delete the
		// version tree manually to successfully delete a file

		// Create a dummy node

		try {
			session = JCRFactoryUtil.createSession();

			Node rootNode = getRootNode(session, companyId);
			Node repositoryNode = getFolderNode(rootNode, repositoryId);
			Node fileNode = repositoryNode.getNode(fileName);
			Node contentNode = fileNode.getNode(JCRConstants.JCR_CONTENT);

			contentNode.checkout();

			contentNode.setProperty(JCRConstants.JCR_MIME_TYPE, "text/plain");
			contentNode.setProperty(JCRConstants.JCR_DATA, "");
			contentNode.setProperty(
				JCRConstants.JCR_LAST_MODIFIED, Calendar.getInstance());

			session.save();

			Version version = contentNode.checkin();

			contentNode.getVersionHistory().addVersionLabel(
				version.getName(), "0.0", false);
		}
		catch (PathNotFoundException pnfe) {
			throw new NoSuchFileException(fileName);
		}
		catch (RepositoryException re) {
			throw new SystemException(re);
		}
		finally {
			if (session != null) {
				session.logout();
			}
		}

		// Delete version tree

		try {
			session = JCRFactoryUtil.createSession();

			Node rootNode = getRootNode(session, companyId);
			Node repositoryNode = getFolderNode(rootNode, repositoryId);
			Node fileNode = repositoryNode.getNode(fileName);
			Node contentNode = fileNode.getNode(JCRConstants.JCR_CONTENT);

			VersionHistory versionHistory = contentNode.getVersionHistory();

			VersionIterator itr = versionHistory.getAllVersions();

			while (itr.hasNext()){
				Version version = itr.nextVersion();

				if (itr.getPosition() == itr.getSize()) {
					break;
				}
				else {
					if (!StringUtils.equals(
							JCRConstants.JCR_ROOT_VERSION, version.getName())) {

						versionHistory.removeVersion(version.getName());
					}
				}
			}

			session.save();
		}
		catch (PathNotFoundException pnfe) {
			throw new NoSuchFileException(fileName);
		}
		catch (RepositoryException re) {
			throw new SystemException(re);
		}
		finally {
			if (session != null) {
				session.logout();
			}
		}

		// Delete file

		try {
			session = JCRFactoryUtil.createSession();

			Node rootNode = getRootNode(session, companyId);
			Node repositoryNode = getFolderNode(rootNode, repositoryId);
			Node fileNode = repositoryNode.getNode(fileName);

			Indexer.deleteFile(companyId, portletId, repositoryId, fileName);

			fileNode.remove();

			session.save();
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}
		catch (PathNotFoundException pnfe) {
			throw new NoSuchFileException(fileName);
		}
		catch (RepositoryException re) {
			throw new SystemException(re);
		}
		finally {
			if (session != null) {
				session.logout();
			}
		}
	}

	public void deleteFile(
			long companyId, String portletId, long repositoryId,
			String fileName, double versionNumber)
		throws PortalException, SystemException {

		String versionLabel = String.valueOf(versionNumber);

		Session session = null;

		try {
			session = JCRFactoryUtil.createSession();

			Node rootNode = getRootNode(session, companyId);
			Node repositoryNode = getFolderNode(rootNode, repositoryId);
			Node fileNode = repositoryNode.getNode(fileName);
			Node contentNode = fileNode.getNode(JCRConstants.JCR_CONTENT);

			VersionHistory versionHistory = contentNode.getVersionHistory();

			Version version = versionHistory.getVersionByLabel(versionLabel);

			versionHistory.removeVersion(version.getName());

			session.save();
		}
		catch (PathNotFoundException pnfe) {
			throw new NoSuchFileException(fileName);
		}
		catch (RepositoryException re) {
			throw new SystemException(re);
		}
		finally {
			if (session != null) {
				session.logout();
			}
		}
	}

	public InputStream getFileAsStream(
			long companyId, long repositoryId, String fileName,
			double versionNumber)
		throws PortalException, SystemException {

		InputStream is = null;

		Session session = null;

		try {
			session = JCRFactoryUtil.createSession();

			Node contentNode = getFileContentNode(
				session, companyId, repositoryId, fileName, versionNumber);

			Property data = contentNode.getProperty(JCRConstants.JCR_DATA);

			is = new BufferedInputStream(data.getStream());
		}
		catch (RepositoryException re) {
			throw new SystemException(re);
		}
		finally {
			if (session != null) {
				session.logout();
			}
		}

		return is;
	}

	public String[] getFileNames(
			long companyId, long repositoryId, String dirName)
		throws PortalException, SystemException {

		List fileNames = new ArrayList();

		Session session = null;

		try {
			session = JCRFactoryUtil.createSession();

			Node rootNode = getRootNode(session, companyId);
			Node repositoryNode = getFolderNode(rootNode, repositoryId);
			Node dirNode = repositoryNode.getNode(dirName);

			NodeIterator itr = dirNode.getNodes();

			while (itr.hasNext()) {
				Node node = (Node)itr.next();

				if (node.getPrimaryNodeType().getName().equals(
						JCRConstants.NT_FILE)) {

					fileNames.add(dirName + "/" + node.getName());
				}
			}
		}
		catch (PathNotFoundException pnfe) {
			throw new NoSuchDirectoryException(dirName);
		}
		catch (RepositoryException re) {
			throw new SystemException(re);
		}
		finally {
			if (session != null) {
				session.logout();
			}
		}

		return (String[])fileNames.toArray(new String[0]);
	}

	public long getFileSize(
			long companyId, long repositoryId, String fileName)
		throws PortalException, SystemException {

		long size;

		Session session = null;

		try {
			session = JCRFactoryUtil.createSession();

			Node contentNode = getFileContentNode(
				session, companyId, repositoryId, fileName, 0);

			size = contentNode.getProperty(JCRConstants.JCR_DATA).getLength();
		}
		catch (RepositoryException re) {
			throw new SystemException(re);
		}
		finally {
			if (session != null) {
				session.logout();
			}
		}

		return size;
	}

	public boolean hasFile(
			long companyId, long repositoryId, String fileName,
			double versionNumber)
		throws PortalException, SystemException {

		try {
			getFileContentNode(
				companyId, repositoryId, fileName, versionNumber);
		}
		catch (NoSuchFileException nsfe) {
			return false;
		}

		return true;
	}

	public void move(String srcDir, String destDir) throws SystemException {
		Session session = null;

		try {
			session = JCRFactoryUtil.createSession();

			session.move(srcDir, destDir);

			session.save();
		}
		catch (RepositoryException re) {
			throw new SystemException(re);
		}
		finally {
			if (session != null) {
				session.logout();
			}
		}
	}

	public void reIndex(String[] ids) throws SearchException {
		long companyId = GetterUtil.getLong(ids[0]);
		String portletId = ids[1];
		long groupId = GetterUtil.getLong(ids[2]);
		long repositoryId = GetterUtil.getLong(ids[3]);

		IndexWriter writer = null;

		Session session = null;

		try {
			writer = LuceneUtil.getWriter(companyId);

			session = JCRFactoryUtil.createSession();

			Node rootNode = getRootNode(session, companyId);
			Node repositoryNode = getFolderNode(rootNode, repositoryId);

			NodeIterator itr = repositoryNode.getNodes();

			while (itr.hasNext()) {
				Node node = (Node)itr.next();

				if (node.getPrimaryNodeType().getName().equals(
						JCRConstants.NT_FILE)) {

					try {
						Document doc = Indexer.getAddFileDocument(
							companyId, portletId, groupId, repositoryId,
							node.getName());

						writer.addDocument(doc);
					}
					catch (Exception e1) {
						_log.error("Reindexing " + node.getName(), e1);
					}
				}
			}
		}
		catch (Exception e2) {
			throw new SearchException(e2);
		}
		finally {
			try {
				if (session != null) {
					session.logout();
				}
			}
			catch (Exception e) {
				_log.error(e);
			}

			try {
				if (writer != null) {
					LuceneUtil.write(companyId);
				}
			}
			catch (Exception e) {
				_log.error(e);
			}
		}
	}

	public void updateFile(
			long companyId, String portletId, long groupId, long repositoryId,
			String fileName, double versionNumber, String sourceFileName,
			String properties, String[] tagsEntries, InputStream is)
		throws PortalException, SystemException {

		String versionLabel = String.valueOf(versionNumber);

		Session session = null;

		try {
			session = JCRFactoryUtil.createSession();

			Node rootNode = getRootNode(session, companyId);
			Node repositoryNode = getFolderNode(rootNode, repositoryId);
			Node fileNode = repositoryNode.getNode(fileName);
			Node contentNode = fileNode.getNode(JCRConstants.JCR_CONTENT);

			contentNode.checkout();

			contentNode.setProperty(JCRConstants.JCR_MIME_TYPE, "text/plain");
			contentNode.setProperty(JCRConstants.JCR_DATA, is);
			contentNode.setProperty(
				JCRConstants.JCR_LAST_MODIFIED, Calendar.getInstance());

			session.save();

			Version version = contentNode.checkin();

			contentNode.getVersionHistory().addVersionLabel(
				version.getName(), versionLabel, false);

			Indexer.updateFile(
				companyId, portletId, groupId, repositoryId, fileName,
				properties, tagsEntries);
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}
		catch (PathNotFoundException pnfe) {
			throw new NoSuchFileException(fileName);
		}
		catch (RepositoryException re) {
			throw new SystemException(re);
		}
		finally {
			if (session != null) {
				session.logout();
			}
		}
	}

	public void updateFile(
			long companyId, String portletId, long groupId, long repositoryId,
			long newRepositoryId, String fileName)
		throws PortalException, SystemException {

		Session session = null;

		try {
			session = JCRFactoryUtil.createSession();

			Node rootNode = getRootNode(session, companyId);
			Node repositoryNode = getFolderNode(rootNode, repositoryId);
			Node fileNode = repositoryNode.getNode(fileName);
			Node contentNode = fileNode.getNode(JCRConstants.JCR_CONTENT);

			Node newRepositoryNode = getFolderNode(rootNode, newRepositoryId);

			if (newRepositoryNode.hasNode(fileName)) {
				throw new DuplicateFileException(fileName);
			}
			else {
				Node newFileNode = newRepositoryNode.addNode(
					fileName, JCRConstants.NT_FILE);

				Node newContentNode = newFileNode.addNode(
					JCRConstants.JCR_CONTENT, JCRConstants.NT_RESOURCE);

				VersionHistory versionHistory = contentNode.getVersionHistory();

				String[] versionLabels = versionHistory.getVersionLabels();

				for (int i = (versionLabels.length - 1); i >= 0; i--) {
					Version version = versionHistory.getVersionByLabel(
						versionLabels[i]);

					Node frozenContentNode = version.getNode(
						JCRConstants.JCR_FROZEN_NODE);

					if (i == (versionLabels.length - 1)) {
						newContentNode.addMixin(JCRConstants.MIX_VERSIONABLE);
					}
					else {
						newContentNode.checkout();
					}

					newContentNode.setProperty(
						JCRConstants.JCR_MIME_TYPE, "text/plain");
					newContentNode.setProperty(
						JCRConstants.JCR_DATA,
						frozenContentNode.getProperty(
							JCRConstants.JCR_DATA).getStream());
					newContentNode.setProperty(
						JCRConstants.JCR_LAST_MODIFIED, Calendar.getInstance());

					session.save();

					Version newVersion = newContentNode.checkin();

					newContentNode.getVersionHistory().addVersionLabel(
						newVersion.getName(), versionLabels[i], false);
				}

				fileNode.remove();

				session.save();

				try {
					Indexer.deleteFile(
						companyId, portletId, repositoryId, fileName);
				}
				catch (IOException ioe) {
				}

				Indexer.addFile(
					companyId, portletId, groupId, newRepositoryId, fileName);
			}
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}
		catch (PathNotFoundException pnfe) {
			throw new NoSuchFileException(fileName);
		}
		catch (RepositoryException re) {
			throw new SystemException(re);
		}
		finally {
			if (session != null) {
				session.logout();
			}
		}
	}

	protected void deleteDirectory(
			long companyId, String portletId, long repositoryId, Node dirNode)
		throws IOException {

		try {
			NodeIterator itr = dirNode.getNodes();

			while (itr.hasNext()) {
				Node node = (Node)itr.next();

				String primaryNodeTypeName =
					node.getPrimaryNodeType().getName();

				if (primaryNodeTypeName.equals(JCRConstants.NT_FOLDER)) {
					deleteDirectory(companyId, portletId, repositoryId, node);
				}
				else if (primaryNodeTypeName.equals(JCRConstants.NT_FILE)) {
					Indexer.deleteFile(
						companyId, portletId, repositoryId, node.getName());
				}
			}

			Indexer.deleteFile(
				companyId, portletId, repositoryId, dirNode.getName());
		}
		catch (RepositoryException e) {
			_log.error(e);
		}
	}

	protected Node getFileContentNode(
			long companyId, long repositoryId, String fileName,
			double versionNumber)
		throws PortalException, SystemException {

		Node contentNode = null;

		Session session = null;

		try {
			session = JCRFactoryUtil.createSession();

			contentNode = getFileContentNode(
				session, companyId, repositoryId, fileName, versionNumber);
		}
		catch (RepositoryException re) {
			throw new SystemException(re);
		}
		finally {
			if (session != null) {
				session.logout();
			}
		}

		return contentNode;
	}

	protected Node getFileContentNode(
			Session session, long companyId, long repositoryId,
			String fileName, double versionNumber)
		throws PortalException, SystemException {

		String versionLabel = String.valueOf(versionNumber);

		Node contentNode = null;

		try {
			Node rootNode = getRootNode(session, companyId);
			Node repositoryNode = getFolderNode(rootNode, repositoryId);
			Node fileNode = repositoryNode.getNode(fileName);
			contentNode = fileNode.getNode(JCRConstants.JCR_CONTENT);

			if (versionNumber > 0) {
				VersionHistory versionHistory =
					contentNode.getVersionHistory();

				Version version = versionHistory.getVersionByLabel(
					versionLabel);

				contentNode = version.getNode(JCRConstants.JCR_FROZEN_NODE);
			}
		}
		catch (PathNotFoundException pnfe) {
			throw new NoSuchFileException(fileName);
		}
		catch (RepositoryException re) {
			throw new SystemException(re);
		}

		return contentNode;
	}

	protected Node getFolderNode(Node node, long name)
		throws RepositoryException {

		return getFolderNode(node, String.valueOf(name));
	}

	protected Node getFolderNode(Node node, String name)
		throws RepositoryException {

		Node folderNode = null;

		if (node.hasNode(name)) {
			folderNode = node.getNode(name);
		}
		else {
			folderNode = node.addNode(name, JCRConstants.NT_FOLDER);
		}

		return folderNode;
	}

	protected Node getRootNode(Session session, long companyId)
		throws RepositoryException {

		Node companyNode = getFolderNode(session.getRootNode(), companyId);

		return getFolderNode(companyNode, JCRFactory.NODE_DOCUMENTLIBRARY);
	}

	private static Log _log = LogFactory.getLog(JCRHook.class);

}