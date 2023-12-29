import fs from 'fs';

function readFile(file) {
    let fileContents = fs
        .readFileSync(file, 'utf-8')
        .trim()
        .split('\n')
        .map((entry) => {
            return entry.split(' ');
        });
    return fileContents;
}

function populateRow(rowAbove) {
    let row = [];
    let allZero = true;
    let i = 0;
    while (i < rowAbove.length - 1) {
        let diff = rowAbove[i + 1] - rowAbove[i];
        row.push(diff);
        allZero = allZero ? diff === 0 : allZero;
        i++;
    }
    return allZero ? 0 : populateRow(row) + row.pop();
}

export { readFile, populateRow };
