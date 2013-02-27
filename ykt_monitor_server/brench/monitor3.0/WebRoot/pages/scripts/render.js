function renderTable(tableName) {
    var table = document.getElementById(tableName);
    if (table) {
        var rowCount = table.rows.length;
        var cellCount = table.rows[0].cells.length;
        for (var i = 1; i < rowCount; i++) {
            var row = table.rows[i];
            if (hasFunction("renderRow")) {
                renderRow(row);
            }
            for (var j = 0; j < cellCount; j++) {
                var cell = row.cells[j];
                if (hasFunction("renderCell")) {
                    renderCell(row, cell);
                }
            }
        }
    }
}

function hasFunction(name) {
    var result = false;
    try {
        if (typeof(eval(name)) == "function") {
            result = true;
        }
    } catch(e) {
    }
    return result;
}

function mergeTable(tableName, cellIndex) {
    var table = document.getElementById(tableName);
    if (table) {
        var i,j;
        var rowSpan;
        var tempValue;
        for (i = 0; i < table.rows.length; i++) {
            rowSpan = 1;
            tempValue = table.rows[i].cells[cellIndex].innerText;
            for (j = i + 1; j < table.rows.length; j++) {
                if (tempValue == table.rows[j].cells[cellIndex].innerText) {
                    rowSpan++;
                    //table.rows[j].cells[cellIndex].style.display = "none";
                    table.rows[j].cells[cellIndex].bgColor = "white";
                    table.rows[j].cells[cellIndex].innerText = "";
                } else {
                    break;
                }
            }
            if(rowSpan>1){
                //table.rows[i].cells[cellIndex].rowSpan = rowSpan;
                table.rows[i].cells[cellIndex].bgColor = "darkgray";
            }
            i = j - 1;
        }
    }
}