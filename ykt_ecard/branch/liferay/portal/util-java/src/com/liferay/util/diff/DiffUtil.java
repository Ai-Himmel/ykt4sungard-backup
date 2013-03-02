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

package com.liferay.util.diff;

import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.util.FileUtil;

import java.io.Reader;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.incava.util.diff.Diff;
import org.incava.util.diff.Difference;

/**
 * <a href="DiffUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * This class can compare two different versions of a text. Source refers to
 * the earliest version of the text and target refers to a modified version of
 * source. Changes are considered either as a removal from the source or as an
 * addition to the target. This class detects changes to an entire line and also
 * detects changes within lines, such as, removal or addition of characters.
 * Take a look at <code>DiffTest</code> to see the expected inputs and outputs.
 * </p>
 *
 * @author Bruno Farache
 *
 */
public class DiffUtil {

	public static final String OPEN_INS = "<ins>";

	public static final String CLOSE_INS = "</ins>";

	public static final String OPEN_DEL = "<del>";

	public static final String CLOSE_DEL = "</del>";

	public static final String CONTEXT_LINE = "#context#line#";

	/**
	 * This is a diff method with default values.
	 *
	 * @param		source the <code>Reader</code> of the source text
	 * @param		target the <code>Reader</code> of the target text
	 * @return		an array containing two lists of <code>DiffResults</code>,
	 * 				the first element contains DiffResults related to changes
	 * 				in source and the second element to changes in target
	 */
	public static List[] diff(Reader source, Reader target) {
		int margin = 2;

		return diff(
			source, target, OPEN_INS, CLOSE_INS, OPEN_DEL, CLOSE_DEL, margin);
	}

	/**
	 * The main entrance of this class. This method will compare the two texts,
	 * highlight the changes by enclosing them with markers and return a list
	 * of <code>DiffResults</code>.
	 *
	 * @param		source the <code>Reader</code> of the source text, this can
	 *				be for example, an instance of FileReader or StringReader
	 * @param		target the <code>Reader</code> of the target text
	 * @param		addedMarkerStart the initial marker for highlighting
	 * 				additions
	 * @param		addedMarkerEnd the end marker for highlighting additions
	 * @param		deletedMarkerStart the initial marker for highlighting
	 * 				removals
	 * @param		deletedMarkerEnd the end marker for highlighting removals
	 * @param		margin the number of lines that will be added before the
	 * 				first changed line
	 * @return		an array containing two lists of <code>DiffResults</code>,
	 * 				the first element contains DiffResults related to changes
	 * 				in source and the second element to changes in target
	 */
	public static List[] diff(
		Reader source, Reader target, String addedMarkerStart,
		String addedMarkerEnd, String deletedMarkerStart,
		String deletedMarkerEnd, int margin) {

		List sourceResults = new ArrayList();
		List targetResults = new ArrayList();

		List[] results = new List[] {sourceResults, targetResults};

		// Convert the texts to Lists where each element are lines of the texts.

		List sourceStringList = FileUtil.toList(source);
		List targetStringList = FileUtil.toList(target);

		// Make a a Diff of these lines and iterate over their Differences.

		Diff diff = new Diff(sourceStringList, targetStringList);

		List differences = diff.diff();

		Iterator itr = differences.iterator();

		while (itr.hasNext()) {
			Difference difference = (Difference)itr.next();

			if (difference.getAddedEnd() == Difference.NONE) {

				// Lines were deleted from source only.

				_highlightLines(
					sourceStringList, deletedMarkerStart,
					deletedMarkerEnd, difference.getDeletedStart(),
					difference.getDeletedEnd());

				margin = _calculateMargin(
					sourceResults, targetResults, difference.getDeletedStart(),
					difference.getAddedStart(), margin);

				List changedLines = _addMargins(
					sourceResults, sourceStringList,
					difference.getDeletedStart(), margin);

				_addResults(
					sourceResults, sourceStringList, changedLines,
					difference.getDeletedStart(), difference.getDeletedEnd());

				changedLines = _addMargins(
					targetResults, targetStringList, difference.getAddedStart(),
					margin);

				int deletedLines =
					difference.getDeletedEnd() + 1 -
						difference.getDeletedStart();

				for (int i = 0; i < deletedLines; i++) {
					changedLines.add(CONTEXT_LINE);
				}

				DiffResult diffResult = new DiffResult(
					difference.getDeletedStart(), changedLines);

				targetResults.add(diffResult);
			}
			else if (difference.getDeletedEnd() == Difference.NONE) {

				// Lines were added to target only.

				_highlightLines(
					targetStringList, addedMarkerStart, addedMarkerEnd,
					difference.getAddedStart(), difference.getAddedEnd());

				margin = _calculateMargin(
					sourceResults, targetResults, difference.getDeletedStart(),
					difference.getAddedStart(), margin);

				List changedLines = _addMargins(
					sourceResults, sourceStringList,
					difference.getDeletedStart(), margin);

				int addedLines =
					difference.getAddedEnd() + 1 - difference.getAddedStart();

				for (int i = 0; i < addedLines; i++) {
					changedLines.add(CONTEXT_LINE);
				}

				DiffResult diffResult = new DiffResult(
					difference.getAddedStart(), changedLines);

				sourceResults.add(diffResult);

				changedLines = _addMargins(
					targetResults, targetStringList, difference.getAddedStart(),
					margin);

				_addResults(
					targetResults, targetStringList, changedLines,
					difference.getAddedStart(), difference.getAddedEnd());
			}
			else {

				// Lines were deleted from source and added to target at the
				// same position. It needs to check for characters differences.

				_checkCharDiffs(
					sourceResults, targetResults, sourceStringList,
					targetStringList, addedMarkerStart, addedMarkerEnd,
					deletedMarkerStart, deletedMarkerEnd, difference, margin);
			}
		}

		return results;
	}

	private static List _addMargins(
		List results, List stringList, int beginPos, int margin) {

		List changedLines = new ArrayList();

		if (margin == 0 || beginPos == 0) {
			return changedLines;
		}

		int i = beginPos - margin;

		for (; i < 0; i++) {
			changedLines.add(CONTEXT_LINE);
		}

		for (; i < beginPos; i++) {
			if (i < stringList.size()) {
				changedLines.add(stringList.get(i));
			}
		}

		return changedLines;
	}

	private static void _addResults(
		List results, List stringList, List changedLines, int start, int end) {

		changedLines.addAll(stringList.subList(start, end + 1));

		DiffResult diffResult = new DiffResult(
			start, changedLines);

		results.add(diffResult);
	}

	private static int _calculateMargin(
		List sourceResults, List targetResults, int sourceBeginPos,
		int targetBeginPos, int margin) {

		int sourceMargin = _checkOverlapping(
			sourceResults, sourceBeginPos, margin);
		int targetMargin = _checkOverlapping(
			targetResults, targetBeginPos, margin);

		if (sourceMargin < targetMargin) {
			return sourceMargin;
		}

		return targetMargin;
	}

	private static void _checkCharDiffs(
		List sourceResults, List targetResults, List sourceStringList,
		List targetStringList, String addedMarkerStart, String addedMarkerEnd,
		String deletedMarkerStart, String deletedMarkerEnd,
		Difference difference, int margin) {

		boolean aligned = false;

		int i = difference.getDeletedStart();
		int j = difference.getAddedStart();

		// A line with changed characters may have its position shifted some
		// lines above or below. These for loops will try to align these lines.
		// While these lines are not aligned, highlight them as either additions
		// or deletions.

		for (; i <= difference.getDeletedEnd(); i++) {
			for (; j <= difference.getAddedEnd(); j++) {
				if (_lineDiff(
						sourceResults, targetResults, sourceStringList,
						targetStringList, addedMarkerStart, addedMarkerEnd,
						deletedMarkerStart, deletedMarkerEnd, i, j, false)) {

					aligned = true;

					break;
				}
				else {
					_highlightLines(
						targetStringList, addedMarkerStart, addedMarkerEnd, j,
						j);

					DiffResult targetResult = new DiffResult(
						j, targetStringList.subList(j, j + 1));

					targetResults.add(targetResult);

					sourceResults.add(new DiffResult(j, CONTEXT_LINE));
				}
			}

			if (aligned) {
				 break;
			}
			else {
				_highlightLines(
					sourceStringList, deletedMarkerStart, deletedMarkerEnd, i,
					i);

				DiffResult sourceResult = new DiffResult(
					i, sourceStringList.subList(i, i + 1));

				sourceResults.add(sourceResult);

				targetResults.add(new DiffResult(i, CONTEXT_LINE));
			}
		}

		i = i + 1;
		j = j + 1;

		// Lines are aligned, check for differences of the following lines.

		for (; i <= difference.getDeletedEnd() && j <= difference.getAddedEnd();
				i++, j++) {

			_lineDiff(
				sourceResults, targetResults, sourceStringList,
				targetStringList, addedMarkerStart, addedMarkerEnd,
				deletedMarkerStart, deletedMarkerEnd, i, j, true);
		}

		// After the for loop above, some lines might remained unchecked.
		// They are considered as deletions or additions.

		for (; i <= difference.getDeletedEnd();i++) {
			_highlightLines(
				sourceStringList, deletedMarkerStart, deletedMarkerEnd, i, i);

			DiffResult sourceResult = new DiffResult(
				i, sourceStringList.subList(i, i + 1));

			sourceResults.add(sourceResult);

			targetResults.add(new DiffResult(i, CONTEXT_LINE));
		}

		for (; j <= difference.getAddedEnd(); j++) {
			_highlightLines(
				targetStringList, addedMarkerStart, addedMarkerEnd, j, j);

			DiffResult targetResult = new DiffResult(
				j, targetStringList.subList(j, j + 1));

			targetResults.add(targetResult);

			sourceResults.add(new DiffResult(j, CONTEXT_LINE));
		}
	}

	private static int _checkOverlapping(
		List results, int beginPos, int margin) {

		if (results.size() == 0 || (beginPos - margin) < 0) {
			return margin;
		}

		DiffResult lastDiff = (DiffResult)results.get(results.size() - 1);

		if (lastDiff.getChangedLines().size() == 0) {
			return margin;
		}

		int lastChangedLine = (lastDiff.getLineNumber() - 1) +
			lastDiff.getChangedLines().size();

		int currentChangedLine = beginPos - margin;

		if ((lastDiff.getChangedLines().size() == 1) &&
			(lastDiff.getChangedLines().get(0).equals(CONTEXT_LINE))) {

			currentChangedLine = currentChangedLine + 1;
		}

		if (currentChangedLine < lastChangedLine) {
			return margin + currentChangedLine - lastChangedLine;
		}

		return margin;
	}

	private static void _highlightChars(
		List stringList, String markerStart, String markerEnd, int beginPos,
		int endPos) {

		String start = markerStart + stringList.get(beginPos);

		stringList.set(beginPos, start);

		String end = stringList.get(endPos) + markerEnd;

		stringList.set(endPos, end);
	}

	private static void _highlightLines(
		List stringList, String markerStart, String markerEnd, int beginPos,
		int endPos) {

		for (int i = beginPos; i <= endPos; i++) {
			stringList.set(i, markerStart + stringList.get(i) + markerEnd);
		}
	}

	private static boolean _lineDiff(
		List sourceResults, List targetResults, List sourceStringList,
		List targetStringList, String addedMarkerStart, String addedMarkerEnd,
		String deletedMarkerStart, String deletedMarkerEnd,
		int sourceChangedLine, int targetChangedLine, boolean aligned) {

		String source = (String)sourceStringList.get(sourceChangedLine);
		String target = (String)targetStringList.get(targetChangedLine);

		// Convert the lines to lists where each element are chars of the lines.

		List sourceList = _toList(source);
		List targetList = _toList(target);

		Diff diff = new Diff(sourceList, targetList);

		List differences = diff.diff();

		Iterator itr = differences.iterator();

		int deletedChars = 0;
		int addedChars = 0;

		// The following while loop will calculate how many characters of
		// the source line need to be changed to be equals to the target line.

		while (itr.hasNext() && !aligned) {
			Difference difference = (Difference)itr.next();

			if (difference.getDeletedEnd() != Difference.NONE) {
				deletedChars =
					deletedChars +
					(difference.getDeletedEnd() -
						difference.getDeletedStart() + 1);
			}

			if (difference.getAddedEnd() != Difference.NONE) {
				addedChars =
					addedChars +
					(difference.getAddedEnd() - difference.getAddedStart() + 1);
			}
		}

		// If a lot of changes were needed (more than half of the source line
		// length), consider this as not aligned yet.

		if ((deletedChars > (sourceList.size() / 2)) ||
			(addedChars > sourceList.size() / 2)) {

			return false;
		}

		itr = differences.iterator();

		boolean sourceChanged = false;
		boolean targetChanged = false;

		// Iterate over Differences between chars of these lines.

		while (itr.hasNext()) {
			Difference difference = (Difference)itr.next();

			if (difference.getAddedEnd() == Difference.NONE) {

				// Chars were deleted from source only.

				_highlightChars(
					sourceList, deletedMarkerStart,
					deletedMarkerEnd, difference.getDeletedStart(),
					difference.getDeletedEnd());

				sourceChanged = true;
			}
			else if (difference.getDeletedEnd() == Difference.NONE) {

				// Chars were added to target only.

				_highlightChars(
					targetList, addedMarkerStart, addedMarkerEnd,
					difference.getAddedStart(), difference.getAddedEnd());

				targetChanged = true;
			}
			else {

				// Chars were both deleted and added.

				_highlightChars(
					sourceList, deletedMarkerStart,
					deletedMarkerEnd, difference.getDeletedStart(),
					difference.getDeletedEnd());

				sourceChanged = true;

				_highlightChars(
					targetList, addedMarkerStart, addedMarkerEnd,
					difference.getAddedStart(), difference.getAddedEnd());

				targetChanged = true;
			}
		}

		if (sourceChanged) {
			DiffResult sourceResult = new DiffResult(
				sourceChangedLine, _toString(sourceList));

			sourceResults.add(sourceResult);

			if (!targetChanged) {
				DiffResult targetResult = new DiffResult(
					targetChangedLine, target);

				targetResults.add(targetResult);
			}
		}

		if (targetChanged) {
			if (!sourceChanged) {
				DiffResult sourceResult = new DiffResult(
					sourceChangedLine, source);

				sourceResults.add(sourceResult);
			}

			DiffResult targetResult = new DiffResult(
				targetChangedLine, _toString(targetList));

			targetResults.add(targetResult);
		}

		return true;
	}

	private static List _toList(String line) {
		String[] stringArray = line.split(StringPool.BLANK);

		List result = new ArrayList();

		for (int i = 1; i < stringArray.length; i++) {
			result.add(stringArray[i]);
		}

		return result;
	}

	private static String _toString(List line) {
		StringMaker sm = new StringMaker();

		Iterator itr = line.iterator();

		while (itr.hasNext()) {
			sm.append((String)itr.next());
		}

		return sm.toString();
	}

}